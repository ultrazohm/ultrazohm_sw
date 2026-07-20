#pragma once

#include "../globalData.h"

void deskbench_control_init(DS_Data *data);
void deskbench_update_measurements(DS_Data *data);

void disable_prime_mover(DS_Data *data);
void disable_dut(DS_Data *data);
void enable_prime_mover(DS_Data *data);
void enable_dut(DS_Data *data);