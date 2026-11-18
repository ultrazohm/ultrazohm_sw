.DEFAULT_GOAL := help
# These operations share Vitis metadata and must not run concurrently, even -j.
.NOTPARALLEL:
PROFILE ?= Run_UltraZohm
XSCT ?= xsct
VITIS ?= vitis
WORKSPACE := $(if $(UZ_WORKSPACE_ROOT),$(UZ_WORKSPACE_ROOT)/vitis/workspace,$(CURDIR)/workspace)
# Invoke with make -C vitis <target> (or from the vitis directory).
SCRIPT := ../tcl_scripts/vitis_headless.tcl

.PHONY: help generate generate-open open build build-clean clean-workspace run flash build-run
help:
	@echo 'generate       Create/build an empty workspace without opening Vitis'
	@echo 'generate-open  Create/build an empty workspace and open Vitis'
	@echo 'open           Open the existing workspace in Vitis'
	@echo 'build          Incrementally build applications and platform dependencies'
	@echo 'build-clean    Clean platform and applications, then rebuild'
	@echo 'clean-workspace Delete workspace contents except create_Vitis_workspace_here.txt (close Vitis first)'
	@echo 'flash          Incrementally build, then JTAG program and run'
	@echo 'run / build-run Aliases for flash'
	@echo 'PROFILE=Run_UltraZohm (default; Debug profiles currently require GUI)'
generate:
	"$(XSCT)" -nodisp "$(SCRIPT)" generate
generate-open:
	@command -v "$(VITIS)" >/dev/null 2>&1 || { echo 'ERROR: Vitis GUI launcher not found; load the Vitis environment or set VITIS=path/to/vitis.' >&2; exit 1; }
	"$(XSCT)" -nodisp "$(SCRIPT)" generate
	"$(VITIS)" -workspace "$(WORKSPACE)"
open:
	@test -d "$(WORKSPACE)" || { echo 'ERROR: Workspace not found; run make generate first.' >&2; exit 1; }
	"$(VITIS)" -workspace "$(WORKSPACE)"
build:
	"$(XSCT)" -nodisp "$(SCRIPT)" build
build-clean:
	"$(XSCT)" -nodisp "$(SCRIPT)" build-clean
clean-workspace:
	@case "$(WORKSPACE)" in */vitis/workspace) ;; *) echo 'ERROR: Refusing to clean a path outside vitis/workspace.' >&2; exit 1 ;; esac
	@test ! -L "$(WORKSPACE)" || { echo 'ERROR: Refusing to clean a symlinked workspace.' >&2; exit 1; }
	@cd "$(WORKSPACE)" && find . -mindepth 1 -maxdepth 1 ! -name create_Vitis_workspace_here.txt -exec rm -rf -- {} +
	@echo 'Workspace cleaned; create_Vitis_workspace_here.txt preserved.'
flash:
	"$(XSCT)" -nodisp "$(SCRIPT)" flash "$(PROFILE)"
run build-run: flash
