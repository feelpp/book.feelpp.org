HELP="Usage: make <option> \n\
\nOptions:\n\
\n\
\tinstall - install required packages (bundler, npm required) \n\
\tbuild   - build the documentation \n\
\tclean   - clean gem lock file (redo install after) \n\
\thelp    - print this help\n\n"

BUILD_DIR=./build

all: help

install:
	npm init -y; \
	npm install --save . @antora/cli; \
	npm install --save . @antora/site-generator-default \
	npm install --save . live-server

build: clean
	antora antora-local-feelpp-doc.yml
	@echo "INFO: File generated in 'build/build/site/feelpp-doc/'"

serve:
	live-server --wait=1000 build/site

clean:
	rm -rf build

clean-all: clean
	rm -rf node_modules

help:
	@printf ${HELP}
