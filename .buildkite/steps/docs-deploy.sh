#!/bin/bash

set -eo pipefail
set -x

BRANCH=${BRANCH:-${BUILDKITE_BRANCH:master}}
export WEBSERVER=es15.siteground.eu

echo "--- Deploying $PROJECT..."


buildkite-agent artifact download site.tar.gz . --build ${BUILDKITE_BUILD_ID}
tar xzf site.tar.gz

ls -l build
cd build/
export WEBSERVER=es15.siteground.eu

echo "--- Deploying $PROJECT..."
rsync -avz site/ $WEBSERVER:~/www/docs.feelpp.org

rm -rf build .antora-cache
