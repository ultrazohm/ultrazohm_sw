# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = source
BUILDDIR      = build

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

# Delete build folder before make
.PHONY: clean

auto_generate_available_machines:
	PYTHONPATH=../pyuzlib/src python3 -m pyuzlib.machine_catalog

check_available_machines:
	PYTHONPATH=../pyuzlib/src python3 -m pyuzlib.machine_catalog --inventory-output /tmp/available_machines_check.csv --header-output /tmp/uz_available_machines_check.h
	grep -v "^/\* Generated machine inventory:" /tmp/uz_available_machines_check.h > /tmp/uz_available_machines_check_stripped.h
	grep -v "^/\* Generated machine inventory:" ../vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_available_machines_auto_generated.h > /tmp/uz_available_machines_committed_stripped.h
	diff /tmp/uz_available_machines_check_stripped.h /tmp/uz_available_machines_committed_stripped.h
	diff /tmp/available_machines_check.csv source/software/control/uz_pmsm/available_machines.csv
	@echo "Generated artifacts are up-to-date."

auto_generate_flux_maps:
	PYTHONPATH=../pyuzlib/src python3 -m pyuzlib.flux_map_catalog

check_flux_maps:
	PYTHONPATH=../pyuzlib/src python3 -m pyuzlib.flux_map_catalog --header-output /tmp/uz_pmsm_flux_maps_check.h --diffind-header-output /tmp/uz_pmsm_differential_inductances_check.h
	diff /tmp/uz_pmsm_flux_maps_check.h ../vitis/software/Baremetal/src/uz/uz_pmsm_flux_map/uz_pmsm_flux_maps_auto_generated.h
	diff /tmp/uz_pmsm_differential_inductances_check.h ../vitis/software/Baremetal/src/uz/uz_pmsm_differential_inductance/uz_pmsm_differential_inductances_auto_generated.h
	@echo "Generated flux-map and differential-inductance headers are up-to-date."

clean:
	 rm -r build

doxygen:
	 doxygen doxygen_baremetal_r5

doxygen_clean:
	 rm -r doxygen_output

# Taken from here since I'm not sure how to ensure the proper environment for ceedling otherwise https://stackoverflow.com/questions/10566532/how-can-bash-execute-a-command-in-a-different-directory-context
# The CSV-exporting tests write into ceedling_test_output, so the directory tree is (re)created first.
.PHONY: ceedling_tests ceedling_test_output
ceedling_tests: ceedling_test_output
	(cd ../vitis/software/Baremetal/; ceedling test:all)

ceedling_clean:
	(cd ../vitis/software/Baremetal/; ceedling clobber)

ceedling_test_output:
	rm -rf ceedling_test_output
	mkdir -p ceedling_test_output
	cd ../vitis/software/Baremetal/test && find . -type d -exec mkdir -p ../../../../docs/ceedling_test_output/{} \;

docs_with_ceedling_tests:
	make ceedling_tests
	make doxygen
	make html SPHINXOPTS="-W --keep-going -n"

docs:
	make doxygen
	make html SPHINXOPTS="-W --keep-going -n"

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

livehtml:
	sphinx-autobuild "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

