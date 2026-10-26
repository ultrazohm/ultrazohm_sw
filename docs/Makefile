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

# PMSM catalog targets forward to the root Makefile.
.PHONY: auto_generate_available_machines check_available_machines auto_generate_flux_maps check_flux_maps
auto_generate_available_machines:
	$(MAKE) -C .. pyuzlib-generate-machine-catalog

check_available_machines:
	$(MAKE) -C .. pyuzlib-check-machines

auto_generate_flux_maps:
	$(MAKE) -C .. pyuzlib-generate-flux-maps

check_flux_maps:
	$(MAKE) -C .. pyuzlib-check-flux-maps

# Umbrella targets: regenerate/verify every committed PMSM artifact (canonical CSVs, scalar
# machine catalog, flux-map and differential-inductance headers) in one command. CI uses the equivalent
# root pyuzlib-check-generated target. The explicit recipe and .PHONY entry keep the catch-all
# "%: Makefile" (sphinx-build) rule below from matching these recipe-less names.
.PHONY: auto_generate_all check_all
auto_generate_all:
	$(MAKE) -C .. pyuzlib-generate-machines

check_all:
	$(MAKE) -C .. pyuzlib-check-generated

clean:
	 rm -r build

doxygen:
	 doxygen doxygen_baremetal_r5

doxygen_clean:
	 rm -r doxygen_output

ceedling_clean:
	cd ../vitis/software/Baremetal && ceedling clobber

.PHONY: ceedling_clean docs
docs:
	$(MAKE) doxygen
	$(MAKE) html SPHINXOPTS="-W --keep-going -n"

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

livehtml:
	sphinx-autobuild "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
