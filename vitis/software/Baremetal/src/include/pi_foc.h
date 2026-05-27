#pragma once

#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"


 uz_CurrentControl_t* current_ctrl_left_init(void);
 uz_CurrentControl_t* current_ctrl_right_init(void);
 uz_SetPoint_t* setpoint_ctrl_left_init(void);
 uz_SpeedControl_t* speed_ctrl_left_init(void);
 uz_IIR_Filter_t* speed_filt_left_init(void);
 uz_SetPoint_t* setpoint_ctrl_right_init(void);
 uz_SpeedControl_t* speed_ctrl_right_init(void);
 uz_IIR_Filter_t* speed_filt_right_init(void);
 uz_pmsmModel_t* init_pmsm_cil(void);

