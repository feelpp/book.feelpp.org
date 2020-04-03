#!/bin/bash

set -eo pipefail
set -x

BRANCH=${BRANCH:-${BUILDKITE_BRANCH:master}}
echo "--- Building $PROJECT..."
antora --version
antora --fetch --clean --html-url-extension-style=indexify antora-github-feelpp-doc.yml
ls -lrta

#tar  --exclude='*.png' --exclude="*.jpg" --exclude="*.jpeg" -c -z -f site.tar.gz build
tar -c -z -f site.tar.gz build
buildkite-agent artifact upload site.tar.gz --job $BUILDKITE_JOB_ID
