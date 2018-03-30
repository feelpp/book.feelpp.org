FROM node:8

RUN yarn --cache-folder=.yarn-cache add @antora/cli @antora/site-generator-default > /dev/null
ENV PATH /node_modules/.bin:$PATH
RUN useradd -r -u 999 -d /home/buildkite-agent  buildkite-agent
RUN mkdir /antora && chown -R buildkite-agent /antora &&  mkdir /home/buildkite-agent && chown -R buildkite-agent /home/buildkite-agent
USER buildkite-agent
WORKDIR /antora

ADD . /antora
