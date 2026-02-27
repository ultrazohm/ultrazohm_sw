#pragma once

#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_signals/uz_signals.h"

// Structure of controller: PI Control => G(s) = Kp + Ki/s

struct uz_IIR_Filter_t* uz_speed_prefilter_Last_init(void);
struct uz_IIR_Filter_t* uz_speed_prefilter_Pruef_init(void);
struct uz_SpeedControl_t* uz_speed_control_Last_init(void);
struct uz_SpeedControl_t* uz_speed_control_Pruef_init(void);
struct uz_SetPoint_t* uz_torque_to_current_converter_Last_init(void);
struct uz_SetPoint_t* uz_torque_to_current_converter_Pruef_init(void);
struct uz_CurrentControl_t* uz_current_control_Last_init(void);
struct uz_CurrentControl_t* uz_current_control_dq_Pruef_init(void);
struct uz_CurrentControl_t* uz_current_control_xy_Pruef_init(void);

