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
#include "../IP_Cores/PWM_SS_3L_ip_addr.h"

#define PWM_3L_ENABLE 	1
#define PWM_3L_DISABLE 	0

//==============================================================================================================================================================
// Methods for three-level PWM IP core
void PWM_3L_Initialize(DS_Data* data);	// Init for the PWM modulation IP-Block
void PWM_3L_SetDutyCycle(float duty_A, float duty_B, float duty_C);
void PWM_3L_SetStatus(Xint32 PWM_en);
void PWM_3L_SetMode(int PWM_mode);
void PWM_3L_SetCarrierFrequency(float PWM_freq);
void PWM_3L_SetMinimumPulseWidth(float PWM_min_pulse_width);
void PWM_3L_SetTriState(int TriState_A, int TriState_B, int TriState_C);
void PWM_3L_Calculate_DutyCycle_open_loop_sin(DS_Data* data);

//==============================================================================================================================================================
// registers of three-level PWM module
#define PWM_3L_base_adr					XPAR_GATES_3L_PWM_SS_3L_IP_0_BASEADDR // PWM Module base addresses
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



#endif /* PWM_H_ */
