#pragma once

#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"


 uz_CurrentControl_t* current_ctrl_VA_init(void);
 uz_SetPoint_t* setpoint_ctrl_VA_init(void);
 uz_SpeedControl_t* speed_ctrl_VA_init(void);
 uz_IIR_Filter_t* speed_filt_VA_init(void);
 uz_IIR_Filter_t* speed_filt_IM_init(void);
 uz_IIR_Filter_t* slip_pct_filt_init(void);
