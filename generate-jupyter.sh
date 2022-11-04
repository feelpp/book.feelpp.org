#! /bin/sh

dir=${1:-.}
for i in $(find $dir -name "*.adoc" | grep pages ); do 
    if grep ":page-jupyter:" $i; then   
        echo "Generating Jupyter Notebook for $i: "
        ipynb=$(echo $i | sed 's/.*\/pages\///' )
        dir=$(dirname $ipynb)
        mkdir -p jupyter/$dir
        echo "generating jupyter/$dir/$(basename $ipynb .adoc).ipynb..."
        pwd
        asciidoctor -r asciidoctor-jupyter -b jupyter $i -o jupyter/$dir/$(basename $ipynb .adoc).ipynb
    fi; 
done