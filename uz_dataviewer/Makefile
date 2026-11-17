# Shortcut for Linux: make -C uz_dataviewer TASK runs python3 tasks.py TASK.
# All logic lives in tasks.py, which Windows and CI run directly; make help lists the tasks.
# Extra arguments: make start ARGS="--dev-cli log.csv", make check ARGS="--cli-wheel PATH".
.PHONY: help
help:
	@python3 tasks.py --help
%:
	python3 tasks.py $@ $(ARGS)
