require 'asciidoctor/extensions'

Asciidoctor::Extensions.register do
  treeprocessor do
    process do |document|
      puts "Processing #{document.attr 'docfile'}"
      nil
    end
  end
end
