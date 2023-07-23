#pragma once
#include "control.h"

// resonant gains
#define PIR_PIR_GAIN_D 1.0f
#define PIR_PIR_GAIN_Q 1.0f
#define PIR_PIR_GAIN_X1 1.0f
#define PIR_PIR_GAIN_Y1 1.0f
#define PIR_PIR_GAIN_X2 1.0f
#define PIR_PIR_GAIN_Y2 1.0f
#define PIR_PIR_GAIN_X3 1.0f
#define PIR_PIR_GAIN_Y3 1.0f

uz_9ph_abc_t step_controllers_PIR_PIR(DS_Data* Data, struct pointers_PIR_PIR objects);
void reset_controllers_PIR_PIR(struct pointers_PIR_PIR objects);

uz_subspace_resonant_control* init_PIR_PIR_resonant_dq(void);
uz_subspace_resonant_control* init_PIR_PIR_resonant_xy1(void);
uz_subspace_resonant_control* init_PIR_PIR_resonant_xy2(void);
uz_subspace_resonant_control* init_PIR_PIR_resonant_xy3(void);
