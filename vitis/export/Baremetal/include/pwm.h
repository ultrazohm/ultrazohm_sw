/******************************************************************************
 *
 * pwm.h
 *
 * Copyright (C) 2018 Institute ELSYS, TH Nürnberg, All rights reserved.
 *
 *  Created on: 12.11.2018
 *      Author: Sebastian Wendel (SW)
 *
******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "../main.h"
#include "../defines.h"
#include "../IP_Cores/PWM_and_SS_control_V3_ip_addr.h"		//Include from Simulink IP-Blocks for PWM and SS control

#define PWM_ENABLE 		1
#define PWM_DISABLE 	0

//==============================================================================================================================================================
// Methods for two-level PWM IP core
int  PWM_SS_Initialize(DS_Data* data);	// Init for the PWM modulation IP-Block
void PWM_SS_SetDutyCycle(float duty_A, float duty_B, float duty_C); // method to set duty cycle
void PWM_SS_SetStatus(Xint32 PWM_en);
void PWM_SS_SetMode(int PWM_mode);
void PWM_SS_SetCarrierFrequency(float PWM_freq_Hz);
void PWM_SS_SetMinimumPulseWidth(float PWM_min_pulse_width);
void PWM_SS_SetTriState(int TriState_A, int TriState_B, int TriState_C);
void PWM_SS_Calculate_DutyCycle_open_loop_sin(DS_Data* data);

//==============================================================================================================================================================
//IP-Block for the 2-level PWM with DutyCycle
#define PWM_BASE_ADDR					XPAR_GATES_PWM_AND_SS_CONTROL_V_0_BASEADDR
#define PWM_SS_Con_Enable_REG			PWM_BASE_ADDR + PWM_en_AXI_Data_PWM_and_SS_control_V3_ip                //data register for Inport PWM_en_AXI
#define PWM_SS_Con_Mode_REG				PWM_BASE_ADDR + Mode_AXI_Data_PWM_and_SS_control_V3_ip                  //data register for Inport Mode_AXI
#define PWM_SS_Con_Scal_f_car_REG		PWM_BASE_ADDR + Scal_f_carrier_AXI_Data_PWM_and_SS_control_V3_ip        //data register for Inport PWM_f_carrier_kHz_AXI
#define PWM_SS_Con_Scal_T_car_REG		PWM_BASE_ADDR + Scal_T_carrier_AXI_Data_PWM_and_SS_control_V3_ip        //data register for Inport PWM_T_carrier_us_AXI
#define PWM_SS_Con_min_pulse_REG		PWM_BASE_ADDR + PWM_min_pulse_width_AXI_Data_PWM_and_SS_control_V3_ip   //data register for Inport PWM_min_pulse_width_AXI
#define PWM_SS_Con_m_u1_norm_REG		PWM_BASE_ADDR + m_u1_norm_AXI_Data_PWM_and_SS_control_V3_ip             //data register for Inport m_u1_norm_AXI
#define PWM_SS_Con_m_u2_norm_REG		PWM_BASE_ADDR + m_u2_norm_AXI_Data_PWM_and_SS_control_V3_ip             //data register for Inport m_u2_norm_AXI
#define PWM_SS_Con_m_u3_norm_REG		PWM_BASE_ADDR + m_u3_norm_AXI_Data_PWM_and_SS_control_V3_ip             //data register for Inport m_u3_norm_AXI
#define PWM_SS_Con_Enable_Rd_REG		PWM_BASE_ADDR + PWM_en_rd_AXI_Data_PWM_and_SS_control_V3_ip             //data register for Outport PWM_en_rd_AXI
#define PWM_SS_Con_f_car_kHz_Rd_REG		PWM_BASE_ADDR + PWM_f_carrier_kHz_rd_AXI_Data_PWM_and_SS_control_V3_ip  //data register for Outport PWM_f_carrier_kHz_rd_AXI
#define PWM_SS_Con_T_car_us_Rd_REG		PWM_BASE_ADDR + PWM_T_carrier_us_rd_AXI_Data_PWM_and_SS_control_V3_ip   //data register for Outport PWM_T_carrier_us_rd_AXI
#define PWM_SS_Con_min_pulse_Rd_REG		PWM_BASE_ADDR + PWM_min_pulse_width_rd_AXI_Data_PWM_and_SS_control_V3_ip//data register for Outport PWM_min_pulse_width_rd_AXI
#define PWM_SS_Con_Mode_Rd_REG			PWM_BASE_ADDR + Mode_rd_AXI_Data_PWM_and_SS_control_V3_ip               //data register for Outport Mode_rd_AXI
#define PWM_SS_Con_TriState_HB1_REG		PWM_BASE_ADDR + TriState_HB1_AXI_Data_PWM_and_SS_control_V3_ip          //data register for Inport TriState_HB1_AXI
#define PWM_SS_Con_TriState_HB2_REG		PWM_BASE_ADDR + TriState_HB2_AXI_Data_PWM_and_SS_control_V3_ip          //data register for Inport TriState_HB2_AXI
#define PWM_SS_Con_TriState_HB3_REG		PWM_BASE_ADDR + TriState_HB3_AXI_Data_PWM_and_SS_control_V3_ip          //data register for Inport TriState_HB3_AXI


#endif /* PWM_H_ */
