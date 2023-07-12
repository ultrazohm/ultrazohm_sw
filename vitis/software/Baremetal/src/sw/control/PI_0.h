#pragma once
#include "control.h"
#include "../../globalData.h"


#define PI_PI_KP_D 1.0f
#define PI_PI_KI_D 1.0f
#define PI_PI_KP_Q 1.0f
#define PI_PI_KI_Q 1.0f

uz_CurrentControl_t* init_PI_0_cc_dq(void);
uz_9ph_abc_t step_controllers_PI_0(DS_Data* Data, uz_CurrentControl_t* object);
