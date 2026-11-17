# Shortcut for Linux: make -C uz_dataviewer TASK runs python3 tasks.py TASK.
# All logic lives in tasks.py, which Windows and CI run directly; make (or make help) lists the tasks.
# Extra arguments: make start ARGS="--dev-cli log.csv", make check ARGS="--cli-wheel PATH".
# tasks.py phrases its help as make commands when called from here.
export UZ_TASKS_VIA_MAKE := 1
.PHONY: help
help:
	@python3 tasks.py
%:
	python3 tasks.py $@ $(ARGS)
