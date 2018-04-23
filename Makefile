HELP="Usage: make <option> \n\
\nOptions:\n\
\n\
\tinstall     - install required packages (bundler, npm required) \n\
\tbuild       - build the documentation \n\
\tclean       - clean gem lock file (redo install after) \n\
\tclean-all   - clean and remove local antora install \n\
\thelp        - print this help\n\n"

BUILD_DIR=./build
NPM_BIN=`npm bin`

all: help

install:
	npm init -y; \
	npm install --save . @antora/cli; \
	npm install --save . @antora/site-generator-default \
	npm install --save . live-server

build: clean
	${NPM_BIN}/antora --pull antora-local-feelpp-doc.yml
	@echo "INFO: File generated in 'build/build/site/feelpp-doc/'"

serve:
	${NPM_BIN}/live-server --wait=1000 build/site

sync: build
	#rsync -avz --delete build/site/ es15.siteground.eu:~/public_html/docs.feelpp.org/
	rsync -avz  --include '*/' --include '*.png' --include '*.jpg' --include '*.jpeg'  --exclude '*' build/site/ es15.siteground.eu:~/public_html/docs.feelpp.org/
clean:
	rm -rf build

clean-all: clean
	rm -rf node_modules

help:
	@printf ${HELP}
