#!/bin/bash

set -eo pipefail
set -x

BRANCH=${BRANCH:-${BUILDKITE_BRANCH:master}}

echo "--- Building $PROJECT..."
jekyll build
tar czf site.tar.gz _site/
buildkite-agent artifact upload site.tar.gz
