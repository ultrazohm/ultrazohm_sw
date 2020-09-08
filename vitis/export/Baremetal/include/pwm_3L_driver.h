/******************************************************************************
*
* pwm_3L_driver.h
*
* Copyright (C) 2020 UltraZohm Community, All rights reserved.
*
*  Created on: 19.03.2020
*      Author: Eyke Liegmann (EL)
*
******************************************************************************/

#ifndef PWM_3L_H_
#define PWM_3L_H_

#include "../defines.h"
#include "../main.h"
#include "../IP_cores/PWM_SS_3L_ip_addr.h"


// PWM Module base addresses
#define PWM_3L_base_adr					XPAR_GATES_3L_PWM_SS_3L_IP_0_BASEADDR
#define PWM_3L_reg_reset				PWM_3L_base_adr + IPCore_Reset_PWM_SS_3L_ip
#define PWM_3L_reg_enable				PWM_3L_base_adr + PWM_en_AXI_Data_PWM_SS_3L_ip
#define PWM_3L_reg_mode					PWM_3L_base_adr + Mode_AXI_Data_PWM_SS_3L_ip
#define PWM_3L_reg_counter_max			PWM_3L_base_adr + PWM_counter_max_value_int_AXI_Data_PWM_SS_3L_ip
#define PWM_3L_reg_min_pulse_width		PWM_3L_base_adr + PWM_min_pulse_width_0to1_AXI_Data_PWM_SS_3L_ip
#define PWM_3L_reg_dutyA				PWM_3L_base_adr + m_u1_norm_AXI_Data_PWM_SS_3L_ip
#define PWM_3L_reg_dutyB				PWM_3L_base_adr + m_u2_norm_AXI_Data_PWM_SS_3L_ip
#define PWM_3L_reg_dutyC				PWM_3L_base_adr + m_u3_norm_AXI_Data_PWM_SS_3L_ip
#define PWM_3L_reg_TriStateA			PWM_3L_base_adr + TriState_HB1_AXI_Data_PWM_SS_3L_ip
#define PWM_3L_reg_TriStateB			PWM_3L_base_adr + TriState_HB2_AXI_Data_PWM_SS_3L_ip
#define PWM_3L_reg_TriStateC			PWM_3L_base_adr + TriState_HB3_AXI_Data_PWM_SS_3L_ip


void PWM_3L_Initialize();	// Init for the PWM modulation IP-Block
void PWM_3L_SetDutyCycle(float duty_A, float duty_B, float duty_C);

#endif /* PWM_H_ */
