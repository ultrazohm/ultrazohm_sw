# Shortcut for Linux: make -C uz_cli TASK runs python3 tasks.py TASK.
# All logic lives in tasks.py, which Windows and CI run directly; make help lists the tasks.
.PHONY: help
help:
	@python3 tasks.py --help
%:
	python3 tasks.py $@
