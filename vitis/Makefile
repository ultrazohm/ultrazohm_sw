.DEFAULT_GOAL := help
# These operations share Vitis metadata and must not run concurrently, even -j.
.NOTPARALLEL:
PROFILE ?= Run_UltraZohm
export PROFILE

.PHONY: help generate generate-open open build run flash build-run
help:
	@echo 'generate       Create/build an empty workspace without opening Vitis'
	@echo 'generate-open  Create/build an empty workspace and open Vitis'
	@echo 'open           Open the existing workspace in Vitis'
	@echo 'build          Build platform/BSPs, all applications and system projects'
	@echo 'flash          Incrementally build, then JTAG program and run'
	@echo 'run / build-run Aliases for flash'
	@echo 'PROFILE=Run_UltraZohm (default; Debug profiles currently require GUI)'
generate:
	./run_generate_workspace.sh --headless
generate-open:
	./run_generate_workspace.sh
open:
	./open_vitis.sh
build:
	./build_workspace.sh
flash:
	./run_workspace.sh "$$PROFILE"
run build-run: flash
