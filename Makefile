.PHONY: world
world: deps
	@./node_modules/.bin/bsb -make-world -w -ws _

.PHONY: build
build: deps
	@./node_modules/.bin/bsb -make-world

.PHONY: docs
docs: build
	@./scripts/mk-docs.sh

.PHONY: deps
deps:
	yarn

.PHONY: serve
serve:
	@python -m SimpleHTTPServer $(PORT)

.PHONY: pkg
pkg: deps dist bundle
	@echo "lib/js/src/bundle.js → lib/dist/pkg.js..."
	@./node_modules/.bin/browserify \
		lib/js/src/bundle.js \
		-o lib/dist/pkg.js
	@echo "created lib/dist/pkg.js"

dist:
	@mkdir -p lib/dist

.PHONY: bundle
bundle: deps
	@./node_modules/.bin/rollup \
		lib/js/src/ReText_Render.bs.js \
		--file lib/js/src/bundle.js \
		--format es

.PHONY: clean
clean: deps
	@./node_modules/.bin/bsb -clean-world

.PHONY: cleanall
cleanall:
	rm -rf ./node_modules ./lib
