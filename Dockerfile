FROM node:8

RUN yarn --cache-folder=.yarn-cache add @antora/cli @antora/site-generator-default > /dev/null
ENV PATH /node_modules/.bin:$PATH
RUN mkdir /antora
WORKDIR /antora

ADD . /antora
