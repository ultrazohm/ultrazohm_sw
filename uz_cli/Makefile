# Run inside uz_cli, or use: make -C uz_cli <target>
CARGO ?= cargo
MATURIN ?= maturin
WHEEL_DIR ?= target/wheels

.DEFAULT_GOAL := help
.PHONY: help wheel native cli all
# Wheel packaging and native builds share Cargo outputs. Avoid overwriting a
# Python-enabled library while Maturin is packaging it, even with make -j.
.NOTPARALLEL:

help:
	@echo "make wheel   Build the Python wheel (includes the native extension and CLI entry point)"
	@echo "make cli     Build the standalone executable (no Python required to run it)"
	@echo "make native  Build Rust library artifacts without Python bindings"
	@echo "make all     Build all three outputs"

wheel:
	$(MATURIN) build --release --locked --out "$(WHEEL_DIR)"

cli:
	$(CARGO) build --release --locked --bin ultrazohm

native:
	$(CARGO) build --release --locked --lib

all: wheel cli native
