.DEFAULT_GOAL := help
# These operations share Vitis metadata and must not run concurrently, even -j.
.NOTPARALLEL:
PROFILE ?= Run_UltraZohm
XSCT ?= xsct
# Invoke with make -C vitis <target> (or from the vitis directory).
ifeq ($(OS),Windows_NT)
CHECKED_XSCT := run_xsct_checked.bat
else
CHECKED_XSCT := bash ./run_xsct_checked.sh
endif
export XSCT

.PHONY: help generate generate-open open build build-clean run flash build-run
help:
	@echo 'generate       Create/build an empty workspace without opening Vitis'
	@echo 'generate-open  Create/build an empty workspace and open Vitis'
	@echo 'open           Open the existing workspace in Vitis'
	@echo 'build          Incrementally build applications and platform dependencies'
	@echo 'build-clean    Clean platform and applications, then rebuild'
	@echo 'flash          Incrementally build, then JTAG program and run'
	@echo 'run / build-run Aliases for flash'
	@echo 'PROFILE=Run_UltraZohm (default; Debug profiles currently require GUI)'
generate:
	$(CHECKED_XSCT) generate
generate-open:
	$(CHECKED_XSCT) generate-open
open:
	$(CHECKED_XSCT) open
build:
	$(CHECKED_XSCT) build
build-clean:
	$(CHECKED_XSCT) build-clean
flash:
	$(CHECKED_XSCT) flash "$(PROFILE)"
run build-run: flash
