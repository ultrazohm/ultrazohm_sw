.DEFAULT_GOAL := help
# These operations share Vitis metadata and must not run concurrently, even -j.
.NOTPARALLEL:
PROFILE ?= Run_UltraZohm
XSCT ?= xsct
# Invoke with make -C vitis <target> (or from the vitis directory).
SCRIPT := ../tcl_scripts/vitis_headless.tcl
ifeq ($(OS),Windows_NT)
XSCT_FLAGS :=
GUI_FLAGS :=
else
XSCT_FLAGS := -norlwrap
# Keep the caller's display for the GUI; Tcl validates it before generation.
GUI_FLAGS := -nodisp
endif

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
	"$(XSCT)" $(XSCT_FLAGS) "$(SCRIPT)" generate
generate-open:
	"$(XSCT)" $(XSCT_FLAGS) $(GUI_FLAGS) "$(SCRIPT)" generate-open
open:
	"$(XSCT)" $(XSCT_FLAGS) $(GUI_FLAGS) "$(SCRIPT)" open
build:
	"$(XSCT)" $(XSCT_FLAGS) "$(SCRIPT)" build
build-clean:
	"$(XSCT)" $(XSCT_FLAGS) "$(SCRIPT)" build-clean
flash:
	"$(XSCT)" $(XSCT_FLAGS) "$(SCRIPT)" flash "$(PROFILE)"
run build-run: flash
