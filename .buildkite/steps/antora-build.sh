#!/bin/bash

set -eo pipefail
set -x

BRANCH=${BRANCH:-${BUILDKITE_BRANCH:master}}
echo "--- Install"
npm install
echo "--- Build"
npm run build
echo "--- Deploy"
rsync -avz --delete build/site/ $WEBSERVER:~/public_html/docs.feelpp.org

#tar  --exclude='*.png' --exclude="*.jpg" --exclude="*.jpeg" -c -z -f site.tar.gz build
#tar -c -z -f site.tar.gz build
#buildkite-agent artifact upload site.tar.gz --job $BUILDKITE_JOB_ID
