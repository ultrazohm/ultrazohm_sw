# Run in the rebuilt dev container or CI image. Container startup is external.
.DEFAULT_GOAL := extension-build
.PHONY: extension-build extension-test
PYTHON ?= python
TARGET ?= all
OUTPUT ?= $(CURDIR)/dist
export UZ_BUILD_CACHE ?= $(CURDIR)/.build-cache

extension-build:
	$(PYTHON) tools/build.py --target "$(TARGET)" --output "$(OUTPUT)"

extension-test:
	$(PYTHON) tools/build.py --target linux-x64 --test --output "$(OUTPUT)"
