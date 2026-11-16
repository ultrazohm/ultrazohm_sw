# Run inside uz_dataviewer, or use: make -C uz_dataviewer <target>
# CI runs the same targets in the dev container's ci stage (.devcontainer/Dockerfile);
# only the portable Linux bundle is built in an older Ubuntu container.
UV ?= uv
PYTHON_VERSION ?= 3.12
# Separate from .venv, which the launchers own together with the selected CLI wheel.
VENV ?= .venv-ci
WEB_VENV ?= .venv-web
BUILD_VENV ?= .venv-build
# Matching CLI wheel. Empty: build one from ../uz_cli (debug for tests, release for bundles).
CLI_WHEEL ?=
PLAYWRIGHT ?= playwright==1.64.1
# Installs Chromium's system libraries (needs root, as in the containers). Clear to skip.
PLAYWRIGHT_DEPS ?= --with-deps

PY := $(abspath $(VENV))/bin/python
BUNDLE := dist/uz_dataviewer/uz_dataviewer
SYNC := $(UV) sync --locked --extra dev --python $(PYTHON_VERSION) --no-build-package imgui-bundle

.DEFAULT_GOAL := help
.PHONY: help sync cli-wheel lint test check web web-smoke bundle bundle-smoke clean

help:
	@echo "make check         Lint and full test suite with a matching CLI wheel (as CI)"
	@echo "make lint          ruff over sources, tests and build scripts"
	@echo "make test          pytest, including live tests against the matching CLI wheel"
	@echo "make web-smoke     Generate the browser app and load it in headless Chromium"
	@echo "make bundle        PyInstaller desktop bundle in dist/ (portable only when built on old glibc)"
	@echo "make bundle-smoke  Start the bundle and its live workers against the simulator"
	@echo "make clean         Remove the CI/web/build environments, build/native and dist/"
	@echo "CLI_WHEEL=PATH     Use this CLI wheel instead of building one from ../uz_cli"

sync:
	UV_PROJECT_ENVIRONMENT="$(abspath $(VENV))" $(SYNC)

# uv sync removes packages outside the lockfile, so install the wheel after syncing.
cli-wheel: sync
ifeq ($(strip $(CLI_WHEEL)),)
	$(MAKE) -C ../uz_cli debug-wheel
	$(UV) pip install --quiet --python "$(PY)" --no-deps --reinstall ../uz_cli/target/wheels-debug/ultrazohm-*.whl
else
	$(UV) pip install --quiet --python "$(PY)" --no-deps --reinstall "$(CLI_WHEEL)"
endif

lint: sync
	"$(PY)" -m ruff check src tests build examples launch.py

test: cli-wheel
	"$(PY)" -m pytest -q

check: lint test

web:
	$(UV) run --no-project --python $(PYTHON_VERSION) python build/gen_web.py

web-smoke: web
	[ -x "$(WEB_VENV)/bin/python" ] || $(UV) venv --quiet --python $(PYTHON_VERSION) "$(WEB_VENV)"
	$(UV) pip install --quiet --python "$(WEB_VENV)/bin/python" "$(PLAYWRIGHT)"
	"$(WEB_VENV)/bin/python" -m playwright install $(PLAYWRIGHT_DEPS) chromium
	"$(WEB_VENV)/bin/python" build/smoke_web.py

bundle:
ifeq ($(strip $(CLI_WHEEL)),)
	$(MAKE) -C ../uz_cli release-wheel
	UV_PROJECT_ENVIRONMENT="$(abspath $(BUILD_VENV))" UZ_CLI_WHEEL="$$(ls ../uz_cli/target/wheels-release/ultrazohm-*.whl)" \
	    bash build/build_native.sh
else
	UV_PROJECT_ENVIRONMENT="$(abspath $(BUILD_VENV))" UZ_CLI_WHEEL="$(abspath $(CLI_WHEEL))" bash build/build_native.sh
endif

bundle-smoke:
	"$(abspath $(BUILD_VENV))/bin/python" build/smoke_binary.py "$(BUNDLE)"
	"$(abspath $(BUILD_VENV))/bin/python" build/smoke_live.py "$(BUNDLE)"

clean:
	rm -rf "$(VENV)" "$(WEB_VENV)" "$(BUILD_VENV)" build/native dist web
