# Run inside uz_cli, or use: make -C uz_cli <target>
# CI runs the same targets in the dev container's ci stage (.devcontainer/Dockerfile).
CARGO ?= cargo
MATURIN ?= maturin
UV ?= uv
PYTHON_VERSION ?= 3.12
WHEEL_DIR ?= target/wheels
DEBUG_WHEEL_DIR := target/wheels-debug
RELEASE_WHEEL_DIR ?= target/wheels-release
CI_VENV := target/ci-venv
RELEASE_VENV := target/release-venv
UNITTEST_FLAGS ?= -v
# Oldest glibc supported by published Linux wheels; zig links against it from any host.
MANYLINUX ?= manylinux_2_28

ROOT := $(abspath ..)
UNITTEST := -m unittest discover -s uz_cli/tests $(UNITTEST_FLAGS)

.DEFAULT_GOAL := help
.PHONY: help wheel native cli all clean fmt-check clippy test debug-wheel integration check \
        release-wheel release-check
# Wheel packaging and native builds share Cargo outputs. Avoid overwriting a
# Python-enabled library while Maturin is packaging it, even with make -j.
.NOTPARALLEL:

help:
	@echo "make wheel          Build the Python wheel for this machine (native extension and CLI entry point)"
	@echo "make cli            Build the standalone executable (no Python required to run it)"
	@echo "make native         Build Rust library artifacts without Python bindings"
	@echo "make all            Build all three outputs"
	@echo "make check          Formatting, clippy, Rust tests and Python integration tests (as CI)"
	@echo "make release-wheel  Build the portable $(MANYLINUX) release wheel into $(RELEASE_WHEEL_DIR)"
	@echo "make release-check  Install that release wheel in a fresh environment and run the integration tests"
	@echo "make clean          Remove target/ including build artifacts, wheels and test environments"

wheel:
	$(MATURIN) build --release --locked --out "$(WHEEL_DIR)"

cli:
	$(CARGO) build --release --locked --bin ultrazohm

native:
	$(CARGO) build --release --locked --lib

all: wheel cli native

clean:
	$(CARGO) clean --target-dir target

fmt-check:
	$(CARGO) fmt --check

clippy:
	$(CARGO) clippy --all-targets --features python --locked -- -D warnings

test:
	$(CARGO) test --locked

debug-wheel:
	rm -rf "$(DEBUG_WHEEL_DIR)"
	$(MATURIN) build --locked --out "$(DEBUG_WHEEL_DIR)"

# Integration tests run twice: against the cargo-built executable and against
# the console command installed by the wheel. Both use loopback simulators.
integration: debug-wheel
	$(CARGO) build --locked
	rm -rf "$(CI_VENV)"
	$(UV) venv --quiet --python "$(PYTHON_VERSION)" "$(CI_VENV)"
	$(UV) pip install --quiet --python "$(CI_VENV)/bin/python" "$(DEBUG_WHEEL_DIR)"/ultrazohm-*.whl polars packaging
	cd "$(ROOT)" && "$(abspath $(CI_VENV))/bin/python" $(UNITTEST)
	cd "$(ROOT)" && UZ_CLI_BIN="$(abspath $(CI_VENV))/bin/ultrazohm" "$(abspath $(CI_VENV))/bin/python" $(UNITTEST)

check: fmt-check clippy test integration

release-wheel:
	rm -rf "$(RELEASE_WHEEL_DIR)"
	$(MATURIN) build --release --locked --zig --compatibility $(MANYLINUX) --out "$(RELEASE_WHEEL_DIR)"

release-check:
	@set -- "$(RELEASE_WHEEL_DIR)"/ultrazohm-*.whl; \
	    if [ "$$#" -ne 1 ] || [ ! -f "$$1" ]; then \
	        echo "Expected exactly one wheel in $(RELEASE_WHEEL_DIR); run make release-wheel" >&2; exit 1; fi
	rm -rf "$(RELEASE_VENV)"
	$(UV) venv --quiet --python "$(PYTHON_VERSION)" "$(RELEASE_VENV)"
	$(UV) pip install --quiet --python "$(RELEASE_VENV)/bin/python" "$(RELEASE_WHEEL_DIR)"/ultrazohm-*.whl polars packaging
	cd "$(ROOT)" && UZ_CLI_BIN="$(abspath $(RELEASE_VENV))/bin/ultrazohm" "$(abspath $(RELEASE_VENV))/bin/python" $(UNITTEST)
