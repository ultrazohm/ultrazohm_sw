# Repository tooling; documentation builds remain in docs/Makefile.
PYTHON ?= python3
CEEDLING ?= ceedling

.PHONY: help pyuzlib-check-generated pyuzlib-check-machines pyuzlib-check-flux-maps pyuzlib-generate-machines pyuzlib-generate-machine-catalog pyuzlib-generate-flux-maps
.PHONY: ceedling-test

help:
	@echo "make pyuzlib-check-generated    Check all committed PMSM artifacts without writing them"
	@echo "make pyuzlib-generate-machines  Regenerate all committed PMSM artifacts"
	@echo "make ceedling-test             Run C tests (no documentation setup required)"

ceedling-test:
	cd vitis/software/Baremetal && $(CEEDLING) test:all

pyuzlib-check-generated: pyuzlib-check-machines pyuzlib-check-flux-maps

pyuzlib-check-machines:
	PYTHONPATH=pyuzlib/src $(PYTHON) -m pyuzlib.machine_catalog --check

pyuzlib-check-flux-maps:
	PYTHONPATH=pyuzlib/src $(PYTHON) -m pyuzlib.flux_map_catalog --check

pyuzlib-generate-machines: pyuzlib-generate-machine-catalog pyuzlib-generate-flux-maps

pyuzlib-generate-machine-catalog:
	PYTHONPATH=pyuzlib/src $(PYTHON) -m pyuzlib.machine_catalog

pyuzlib-generate-flux-maps:
	PYTHONPATH=pyuzlib/src $(PYTHON) -m pyuzlib.flux_map_catalog
