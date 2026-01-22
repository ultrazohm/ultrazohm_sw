#pragma once

uz_CurrentControl_t* init_dq_FOC_Pruef(void);
uz_CurrentControl_t* init_xy_FOC_Pruef(void);
uz_CurrentControl_t* init_dq_FOC_Last(void);
uz_SetPoint_t* setpoint_ctrl_Last_init(void);
uz_SpeedControl_t* speed_ctrl_Last_init(void);
uz_pmsmModel_6ph_dqxy_t* pmsmModel_init(void);
