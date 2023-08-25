#pragma once
#include "control.h"
#include "../../globalData.h"


#define PI_PI_KP_D 7.3967f
#define PI_PI_KI_D 852.7500f
#define PI_PI_KP_Q 9.500f
#define PI_PI_KI_Q 852.7500f

uz_CurrentControl_t* init_PI_0_cc_dq(void);
uz_9ph_dq_t step_controllers_PI_0(DS_Data* Data, uz_CurrentControl_t* object);
