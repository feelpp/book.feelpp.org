#!/bin/bash

set -eo pipefail
set -x

BRANCH=${BRANCH:-${BUILDKITE_BRANCH:master}}

echo "--- Deploying $PROJECT..."
rsync -avz _site/ $WEBSERVER:~/public_html/${PROJECT}
