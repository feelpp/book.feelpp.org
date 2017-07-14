#!/bin/bash

set -eo pipefail
set -x

BRANCH=${BRANCH:-${BUILDKITE_BRANCH:master}}

echo "--- Deploying $PROJECT..."
rsync -avz _site/ es15.siteground.eu:~/public_html/book.feelpp.org
