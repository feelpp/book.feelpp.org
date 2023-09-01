'use strict'

function getToolboxPageModules(contentCatalog, version, tag) {
  const pages = contentCatalog.getPages(({asciidoc, out, src}) => {
    if (!out || !asciidoc) return
    if (src.version !== version || src.component !== 'toolboxes') return
    const pageTags = asciidoc.attributes['page-tags']
    return pageTags && pageTags.split(',').map((v) => v.trim()).includes(tag)
  })
  return pages.reduce((acc, page) => {
    const module = page.src.module;
    const pages = module in acc ? acc[module] : []
    pages.push(page)
    acc[module] = pages
    return acc
  }, {})
}

module.exports.register = (context) => {
  const logger = context.getLogger('toolbox-navigation')
  context.on('navigationBuilt', ({contentCatalog, navigationCatalog}) => {
    const toolboxComponent = contentCatalog.getComponent('toolboxes')
    if (toolboxComponent) {
      const componentVersions = toolboxComponent.versions
      logger.info(`Found ${componentVersions.length} component version(s) for the toolboxes component.`)
      for (const version of componentVersions.map((item) => item.version)) {
        const manualPageModules = getToolboxPageModules(contentCatalog, version, 'manual')
        const benchmarkPageModules = getToolboxPageModules(contentCatalog, version, 'benchmark')
        const casePageModules = getToolboxPageModules(contentCatalog, version, 'case')
        const urlRx = new RegExp(`\/toolboxes\/${version}\/(?<module>[^\/]+)\/`)
        logger.debug(`Get navigation for version: ${version}`)
        const nav = navigationCatalog.getNavigation('toolboxes', version)
        for (const entry of nav) {
          for (const item of entry.items) {
            if (item.url) {
              const found = item.url.match(urlRx)
              if (found) {
                const module = found.groups.module
                const manualPages = manualPageModules[module]
                const items = item.items || []
                if (manualPages && manualPages.length) {
                  logger.debug(`Found ${manualPages.length} manual page(s) for toolboxes@${module}:${version}.`)
                  items.push({
                    content: 'Manuals',
                    items: manualPages.map((page) => (
                      {
                        content: page.title,
                        url: page.pub.url,
                        urlType: 'internal'
                      }
                    ))
                  })
                }
                const benchmarkPages = benchmarkPageModules[module]
                if (benchmarkPages && benchmarkPages.length) {
                  logger.debug(`Found ${benchmarkPages.length} benchmark page(s) for toolboxes@${module}:${version}.`)
                  items.push({
                    content: 'Benchmarks',
                    items: benchmarkPages.map((page) => (
                      {
                        content: page.title,
                        url: page.pub.url,
                        urlType: 'internal'
                      }
                    ))
                  })
                }
                const casePages = casePageModules[module]
                if (casePages && casePages.length) {
                  logger.debug(`Found ${casePages.length} case page(s) for toolboxes@${module}:${version}.`)
                  items.push({
                    content: 'Cases',
                    items: casePages.map((page) => (
                      {
                        content: page.title,
                        url: page.pub.url,
                        urlType: 'internal'
                      }
                    ))
                  })
                }
                logger.info(`Update navigation items toolboxes@${module}:${version}`)
                item.items = items
              }
            }
          }
        }
      }
    } else {
      logger.info('Component toolboxes not found, skipping.')
    }
  })
}
