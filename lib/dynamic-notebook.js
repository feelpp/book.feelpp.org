/* global Opal */
const child_process = require('node:child_process')

const conumRx = /\s*<i class="conum" data-value="[0-9]+"><\/i><b>[^>]+<\/b>/g
const figShowRx = /fig.show\(\)/g
const plotterShowRx = /plotter.show\(\)/g
const pyvistaContainerRx = /^var container = document\.querySelector\('.content'\);$/m
const pyvistaScriptRx = /(?<script><script .*<\/script>)/ms
const pyvistaFaviconRx = /n\.setAttribute\("href","https:\/\/kitware.github.io\/vtk-js\/icon\/favicon-".concat\(t,"x"\).concat\(t,".png"\)\),/

const ipythonTemplate = (pyCodes) => {
  return `from IPython.core.interactiveshell import InteractiveShell
from IPython.utils.capture import capture_output
import json
import sys

shell = InteractiveShell()
results = []

shell.run_cell('%colors nocolor')

${pyCodes.map((pyCode, index) => {
    return `
with capture_output() as io${index}:
    r${index} = shell.run_cell(${pyCode})
    results.append({
        'success': r${index}.success,
        'stderr': io${index}.stderr,
        'stdout': io${index}.stdout
    })

`
  }).join('')}

sys.stderr.write(json.dumps(results))
`
}

/**
 * Executes Python code blocks that have the "dynamic" option.
 * The code blocks are executed in the order of their definition in the AsciiDoc document.
 *
 * We rely on IPython to execute code blocks, which allow to have access to variables defined in previous blocks.
 *
 * NOTE: Code blocks that generate a Plotly chart must end with `fig.show()`.
 * This statement will be replaced by `fig.write_html(file=sys.stdout, include_plotlyjs=False)`.
 * Please note that, Plotly.js must be available in the HTML page, otherwise the chart won't show.
 *
 * NOTE: Code blocks that generate a PyVista chart must end with `plotter.show()`.
 * This statement will be replaced by `sys.stdout.write(plotter.export_html(None).getvalue())`.
 *
 * PREREQUISITES:
 * - python3 must be in the PATH
 * - https://pypi.org/project/ipython/ must be installed and available in the python3 environment
 * - all required dependencies must be installed and available in the python3 environment (for instance, if you are using pandas, you must install it)
 */
module.exports.register = function register(registry) {
  const logger = Opal.Asciidoctor.LoggerManager.getLogger()
  registry.treeProcessor(function () {
    const self = this
    self.process(function (doc) {
      const blocks = doc.findBy({context: 'listing', style: 'source'})
        .filter((b) => b.getAttribute('language') === 'python' && b.isOption('dynamic'))
      if (blocks && blocks.length > 0 && doc.getAttribute('dynamic-blocks') !== undefined) {
        const ipython = ipythonTemplate(blocks.map((b) => {
          const code = b.getContent()
            .replaceAll(conumRx, '')
            .replaceAll(figShowRx, `import sys
fig.write_html(file=sys.stdout, include_plotlyjs=False)`)
            .replaceAll(plotterShowRx, `import sys
sys.stdout.write(plotter.export_html(None).getvalue())`)
          return JSON.stringify(code)
        }))
        logger.info('processing dynamic blocks...')
        const result = child_process.spawnSync('python3', ['-'], {
          shell: false,
          input: ipython,
          stdio: ['pipe', 'pipe', 'pipe'],
          maxBuffer: 1024 * 1024 * 50
        })
        if (result.status !== 0) {
          // something went wrong!
        } else {
          const response = JSON.parse(result.stderr.toString('utf8'))
          for (const [index, block] of blocks.entries()) {
            try {
              const parent = block.getParent()
              const parentBlocks = parent.getBlocks()
              const blockIndex = parentBlocks['$find_index'](block) + 1
              const exampleBlock = self.createExampleBlock(block, '', {'collapsible-option': ''}, {'content_model': 'compound'})
              exampleBlock.setTitle('Results')
              // option for raw content (Plotly)
              let source = response[index].stdout.toString('utf8')
              if (block.isOption('raw')) {
                if (block.getAttribute('output') === 'pyvista') {
                  source = source.replace(pyvistaContainerRx, `var container = document.getElementById('pyvista-${index}')`)
                  source = source.replace(pyvistaFaviconRx, '')
                  const found = source.match(pyvistaScriptRx)
                  if (found) {
                    const script = found.groups['script']
                    exampleBlock.append(self.createPassBlock(exampleBlock, `<div id="pyvista-${index}" style="position: relative; height: 500px; border: 1px solid #cecece;"></div>
<script>
const resizeObserver = new ResizeObserver((entries) => {
  for (const entry of entries) {
    // make sure that the canvas will be resized accordingly
    window.dispatchEvent(new Event('resize'))
  }
})
resizeObserver.observe(document.getElementById('pyvista-${index}'))
</script>
${script}`, {role: 'dynamic-py-result'}))
                  }
                } else {
                  exampleBlock.append(self.createPassBlock(exampleBlock, source, {role: 'dynamic-py-result'}))
                }
              } else {
                exampleBlock.append(self.createLiteralBlock(exampleBlock, source, {role: 'dynamic-py-result'}))
              }
              parentBlocks.splice(blockIndex, 0, exampleBlock)
            } catch (err) {
              logger.error({ err })
            }
          }
        }
      }
      return doc
    })
  })
}
