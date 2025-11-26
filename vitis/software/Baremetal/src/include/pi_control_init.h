#pragma once

#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
#include "../IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"

 uz_CurrentControl_t* current_ctrl_left_init(void);
 uz_CurrentControl_t* current_ctrl_right_init(void);
 uz_SetPoint_t* setpoint_ctrl_left_init(void);
 uz_SpeedControl_t* speed_ctrl_left_init(void);
 uz_pmsmModel_t* init_pmsm_cil(void);
