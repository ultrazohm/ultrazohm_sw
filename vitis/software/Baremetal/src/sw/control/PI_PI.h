#pragma once
#include "control.h"

// PI KP and KI
#define PI_PI_KP_X1 4.8525f
#define PI_PI_KI_X1 852.7500f
#define PI_PI_KP_Y1 3.6353f
#define PI_PI_KI_Y1 852.7500f
#define PI_PI_KP_X2 5.0358f
#define PI_PI_KI_X2 852.7500f
#define PI_PI_KP_Y2 5.2915f
#define PI_PI_KI_Y2 852.7500f
#define PI_PI_KP_X3 4.8122f
#define PI_PI_KI_X3 852.7500f
#define PI_PI_KP_Y3 7.5422f
#define PI_PI_KI_Y3 852.7500f

uz_CurrentControl_t* init_PI_PI_cc_xy1(void);
uz_CurrentControl_t* init_PI_PI_cc_xy2(void);
uz_CurrentControl_t* init_PI_PI_cc_xy3(void);


uz_9ph_dq_t step_controllers_PI_PI(DS_Data* Data, struct pointers_PI_PI objects);
void reset_controllers_PI_PI(struct pointers_PI_PI objects);
