# Shortcut for Linux: make -C uz_cli TASK runs python3 tasks.py TASK.
# All logic lives in tasks.py, which Windows and CI run directly; make (or make help) lists the tasks.
# tasks.py phrases its help as make commands when called from here.
export UZ_TASKS_VIA_MAKE := 1
.PHONY: help
help:
	@python3 tasks.py
%:
	python3 tasks.py $@
