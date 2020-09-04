/******************************************************************************
*
* pwm.h
*
* Copyright (C) 2020 UltraZohm Community, All rights reserved.
*
*  Created on: 19.03.2020
*      Author: Eyke Liegmann (EL)
*
******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "xparameters.h"
#include "PWM_SS_3L_ip_addr.h"
#include "xil_io.h"
#include <math.h>

// PWM Module base adresses
#define PWM_base_adr				XPAR_GATES_PWM_SS_3L_IP_0_BASEADDR
#define PWM_reg_reset				PWM_base_adr + IPCore_Reset_PWM_SS_3L_ip
#define PWM_reg_enable				PWM_base_adr + PWM_en_AXI_Data_PWM_SS_3L_ip
#define PWM_reg_mode				PWM_base_adr + Mode_AXI_Data_PWM_SS_3L_ip
#define PWM_reg_counter_max			PWM_base_adr + PWM_counter_max_value_int_AXI_Data_PWM_SS_3L_ip
#define PWM_reg_min_pulse_width		PWM_base_adr + PWM_min_pulse_width_percent_AXI_Data_PWM_SS_3L_ip
#define PWM_reg_dutyA				PWM_base_adr + m_u1_norm_AXI_Data_PWM_SS_3L_ip
#define PWM_reg_dutyB				PWM_base_adr + m_u2_norm_AXI_Data_PWM_SS_3L_ip
#define PWM_reg_dutyC				PWM_base_adr + m_u3_norm_AXI_Data_PWM_SS_3L_ip
#define PWM_reg_TriStateA			PWM_base_adr + TriState_HB1_AXI_Data_PWM_SS_3L_ip
#define PWM_reg_TriStateB			PWM_base_adr + TriState_HB2_AXI_Data_PWM_SS_3L_ip
#define PWM_reg_TriStateC			PWM_base_adr + TriState_HB3_AXI_Data_PWM_SS_3L_ip


void Initialize_PWM_SS_Control();									// INit for the PWM modulation IP-Block
void SetDutyCycle(float duty_A, float duty_B, float duty_C);

#endif /* PWM_H_ */
