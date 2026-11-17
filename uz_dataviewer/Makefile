# Thin forwarder for Linux habit: make -C uz_dataviewer check == python3 uz_dataviewer/tasks.py check
# The tasks are implemented in tasks.py, which Windows and CI run directly.
# Pass a wheel with: make check ARGS="--cli-wheel PATH"
.PHONY: help
help:
	@python3 tasks.py --help
%:
	python3 tasks.py $@ $(ARGS)
