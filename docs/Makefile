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

clean:
	 rm -r build

doxygen:
	 doxygen doxygen_baremetal_r5

doxygen_clean:
	 rm -r doxygen_output

# Taken from here since I'm not sure how to ensure the proper environment for ceedling otherwise https://stackoverflow.com/questions/10566532/how-can-bash-execute-a-command-in-a-different-directory-context
ceedling_tests:
	(cd ../vitis/software/Baremetal/; ceedling test:all) 

ceedling_clean:
	(cd ../vitis/software/Baremetal/; ceedling clobber)

ceedling_test_output:
	rm -rf ceedling_test_output
	mkdir -p ceedling_test_output
	cd ../vitis/software/Baremetal/test && find . -type d -exec mkdir -p ../../../../docs/ceedling_test_output/{} \;

docs_with_ceedling_tests:
	make ceedling_test_output
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

