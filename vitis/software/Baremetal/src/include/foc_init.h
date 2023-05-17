#pragma once

#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
 uz_CurrentControl_t* current_ctrl_d1_init(void);
 uz_CurrentControl_t* current_ctrl_d2_init(void);
 uz_SetPoint_t* setpoint_ctrl_d1_init(void);

 uz_SpeedControl_t* speed_ctrl_d1_init(void);
