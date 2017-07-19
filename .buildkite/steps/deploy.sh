#!/bin/bash

set -eo pipefail
set -x

BRANCH=${BRANCH:-${BUILDKITE_BRANCH:master}}

echo "--- Deploying $PROJECT..."
buildkite-agent artifact download site.tar.gz . --build ${BUILDKITE_BUILD_ID}
rsync -avz _site/ $WEBSERVER:~/public_html/${PROJECT}
