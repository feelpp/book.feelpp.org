#!/bin/bash

set -eo pipefail
set -x

BRANCH=${BRANCH:-${BUILDKITE_BRANCH:master}}
export WEBSERVER=es15.siteground.eu

echo "--- Deploying $PROJECT..."

buildkite-agent artifact download "build/*" build/
ls -l build
cd build/
export WEBSERVER=es15.siteground.eu

echo "--- Deploying $PROJECT..."
rsync -avz site/ $WEBSERVER:~/public_html/docs.feelpp.org

rm -rf build .antora-cache
