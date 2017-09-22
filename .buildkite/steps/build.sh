#!/bin/bash

set -eo pipefail
set -x

BRANCH=${BRANCH:-${BUILDKITE_BRANCH:master}}

echo "--- Building $PROJECT..."
bundle config --local github.https true
bundle --path=.bundle/gems --binstubs=.bundle/.bin
bundle exec jekyll build
tar czf site.tar.gz _site/
buildkite-agent artifact upload site.tar.gz
