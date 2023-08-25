#pragma once
#include "control.h"

// resonant gains
#define PI_R_GAIN_X1 50.0f
#define PI_R_GAIN_Y1 50.0f
#define PI_R_GAIN_X2 100.0f
#define PI_R_GAIN_Y2 100.0f
#define PI_R_GAIN_X3 100.0f
#define PI_R_GAIN_Y3 100.0f



uz_subspace_resonant_control* init_PI_R_resonant_XY1(void);
uz_subspace_resonant_control* init_PI_R_resonant_XY2(void);
uz_subspace_resonant_control* init_PI_R_resonant_XY3(void);

uz_9ph_dq_t step_controllers_PI_R(DS_Data* Data, struct pointers_PI_R objects);
void reset_controllers_PI_R(struct pointers_PI_R objects);
