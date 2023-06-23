const crypto = require('node:crypto')

module.exports.register = function register(registry, context = {}) {
  registry.treeProcessor(function () {
    const self = this
    self.process(function (doc) {
      const blocks = doc.findBy({role: 'vtkjs'})
      if (blocks.length > 0) {
        doc.setAttribute('page-vtkjs', '')
      }
      return doc
    })
  })
  registry.block('vtkjs', function () {
    const self = this
    self.onContext(['listing', 'literal'])
    self.positionalAttributes(['target'])
    self.process((parent, reader, attrs) => {
      const width = attrs.width || '100%'
      const height = attrs.height || '500px'
      const target = attrs.target
      const generatedId = attrs.id || `vtkjs_${crypto.randomUUID()}`
      const definition = reader.$read()
      const result = `
<div id="${generatedId}" style="height: ${height}; width: ${width};"></div>
<script>
feelppVtkJs.createSceneImporter("${generatedId}", {
  fileURL: "${target}",
  objects: ${definition}
})
</script>
`
      const block = self.createPassBlock(parent, result, attrs)
      block.addRole('vtkjs')
      return block
    })
  })
}
