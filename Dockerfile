FROM node:10

RUN yarn global add @antora/cli@2.1 
RUN yarn global add @antora/site-generator-default@2.1
ENV PATH /node_modules/.bin:$PATH
RUN useradd -r -u 999 -d /home/buildkite-agent  buildkite-agent
RUN mkdir /antora && chown -R buildkite-agent /antora &&  mkdir /home/buildkite-agent && chown -R buildkite-agent /home/buildkite-agent
USER buildkite-agent
WORKDIR /antora

ADD . /antora
