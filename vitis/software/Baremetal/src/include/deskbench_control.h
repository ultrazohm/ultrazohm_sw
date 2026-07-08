#pragma once

#include "../globalData.h"

void deskbench_control_init(DS_Data *data);
void deskbench_update_measurements(DS_Data *data);
void deskbench_enter_idle(DS_Data *data);
void deskbench_enter_running(DS_Data *data);
void deskbench_control_step(DS_Data *data);
