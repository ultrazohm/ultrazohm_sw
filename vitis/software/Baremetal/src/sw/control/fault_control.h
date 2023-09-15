#pragma once
#include "../../uz/uz_VSD_9ph_FD_control/uz_VSD_9ph_FD.h"
#include "../../uz/uz_VSD_9ph_FD_control/uz_VSD_9ph_ML_MT_Control.h"
#include "../../IP_cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "control.h"
#include "../../uz/uz_Transformation/uz_Transformation.h"

void fault_control_open_switches(DS_Data* Data, uz_9ph_abc_t indices);
uz_9ph_alphabeta_t step_controllers_fault_control(DS_Data* Data, struct pointers_fault_control objects, uz_9ph_MLMT_kparameter_t k_param);
uz_9ph_dq_t combine_setpoints(uz_9ph_dq_t normal_controller, uz_9ph_alphabeta_t fault_controller);
uz_9ph_alphabeta_t reduce_controller_freedom_degrees(uz_9ph_alphabeta_t ref, int n_OPF);
uz_9ph_alphabeta_t reset_controllers_fault_control_and_tristate(struct pointers_fault_control objects, DS_Data* Data);
uz_3ph_dq_t derate_dq_setpoints(uz_3ph_dq_t user_setpoint, float derating);
