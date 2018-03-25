#!/bin/bash

set -eo pipefail
set -x

BRANCH=${BRANCH:-${BUILDKITE_BRANCH:master}}
echo "--- Building $PROJECT..."
antora --html-url-extension-style=indexify antora-github-feelpp-doc.yml
