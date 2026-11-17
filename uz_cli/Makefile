# Thin forwarder for Linux habit: make -C uz_cli check == python3 uz_cli/tasks.py check
# The tasks are implemented in tasks.py, which Windows and CI run directly.
.PHONY: help
help:
	@python3 tasks.py --help
%:
	python3 tasks.py $@
