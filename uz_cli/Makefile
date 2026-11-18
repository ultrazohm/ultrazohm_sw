# Shortcut for Linux: make -C uz_cli TASK runs python3 tasks.py TASK.
# All logic lives in tasks.py, which Windows and CI run directly; make (or make help) lists the tasks.
# tasks.py phrases its help as make commands when called from here.
export UZ_TASKS_VIA_MAKE := 1
.PHONY: help start
help:
	@python3 tasks.py
start:
	python3 tasks.py start $(or $(filter local release prerelease,$(MAKECMDGOALS)),local) $(ARGS)

# Treat the mode as an argument to start, not as another task.
ifneq ($(filter start,$(MAKECMDGOALS)),)
ifneq ($(word 2,$(filter local release prerelease,$(MAKECMDGOALS))),)
$(error Choose exactly one of local, release or prerelease for start)
endif
.PHONY: local release prerelease
local release prerelease:
	@:
endif

%:
	python3 tasks.py $@ $(ARGS)
