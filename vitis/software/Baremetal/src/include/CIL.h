#pragma once
#include "init_CIL.h"
#include "../globalData.h"

enum target {CIL, testbench};

void uz_CIL_read_direction(struct CIL_objects objects, DS_Data* Data);
uz_9ph_abc_t uz_CIL_phase_currents(struct CIL_objects objects);
void uz_CIL_misc(struct CIL_objects objects, DS_Data* Data);
