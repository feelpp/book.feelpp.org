// REMIND: once released we should use https://github.com/feelpp/feelpp-asciidoctor-extensions/blob/main/src/plotly.js
const crypto = require('node:crypto')

module.exports.register = function register(registry, context = {}) {
  registry.docinfoProcessor(function () {
    const self = this
    self.atLocation('head')
    self.process(function () {
      return `
<script src="https://cdn.jsdelivr.net/npm/plotly.js-dist-min@2" charset="utf-8"></script>
<script src="https://cdn.jsdelivr.net/npm/d3@7" charset="utf-8"></script>
`
    })
  })
  registry.block('plotly', function () {
    const self = this
    self.onContext(['listing', 'literal'])
    self.positionalAttributes(['target'])
    self.process((parent, reader, attrs) => {
      const target = attrs.target
      const generatedId = attrs.id || `ploty_${crypto.randomUUID()}`
      const definition = reader.$read()
      const result = `
<div id="${generatedId}"></div>
<script>
  d3.csv("${target}")
    .then((d) => {
      ${definition}

      Plotly.newPlot('${generatedId}', data, layout, { showLink: false, responsive: true })
    })
    .catch((err) => {
      console.log('Unable to get data', err)
    })
</script>`
      const block = self.createPassBlock(parent, result, attrs)
      block.addRole('plotly')
      return block
    })
  })
}
