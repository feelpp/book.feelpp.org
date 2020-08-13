#!/bin/bash

set -eo pipefail
set -x

BRANCH=${BRANCH:-${BUILDKITE_BRANCH:master}}
echo "--- Building $PROJECT..."
npm i asciidoctor asciidoctor-kroki
antora --version
antora --fetch --clean --html-url-extension-style=indexify site.yml
ls -lrta

#tar  --exclude='*.png' --exclude="*.jpg" --exclude="*.jpeg" -c -z -f site.tar.gz build
tar -c -z -f site.tar.gz build
buildkite-agent artifact upload site.tar.gz --job $BUILDKITE_JOB_ID
