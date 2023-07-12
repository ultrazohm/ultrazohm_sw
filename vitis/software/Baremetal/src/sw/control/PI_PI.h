#pragma once
#include "control.h"

// PI KP and KI
#define PI_PI_KP_X1 1.0f
#define PI_PI_KI_X1 1.0f
#define PI_PI_KP_Y1 1.0f
#define PI_PI_KI_Y1 1.0f
#define PI_PI_KP_X2 1.0f
#define PI_PI_KI_X2 1.0f
#define PI_PI_KP_Y2 1.0f
#define PI_PI_KI_Y2 1.0f
#define PI_PI_KP_X3 1.0f
#define PI_PI_KI_X3 1.0f
#define PI_PI_KP_Y3 1.0f
#define PI_PI_KI_Y3 1.0f

uz_CurrentControl_t* init_PI_PI_cc_xy1(void);
uz_CurrentControl_t* init_PI_PI_cc_xy2(void);
uz_CurrentControl_t* init_PI_PI_cc_xy3(void);


uz_9ph_abc_t step_controllers_PI_PI(DS_Data* Data, struct pointers_PI_PI objects);
void reset_controllers_PI_PI(struct pointers_PI_PI objects);
