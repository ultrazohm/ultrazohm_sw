/******************************************************************************
* Copyright 2021 Sebastian Wendel, Eyke Liegmann, Tobias Schindler
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#include "../include/pwm.h"
extern float uz_isr_frequency_hz;
//----------------------------------------------------
// INITIALIZE PWM AND SS (switching state) CONTROL MODULE
//----------------------------------------------------
int PWM_SS_Initialize(DS_Data* data){

	int Status = 0;
	// Always enable PWM module to get interrupts
	PWM_SS_SetStatus(PWM_ENABLE);

	// Mode is set to 0, which is the Mode for switch signals from the PWM module with reference from AXI
	PWM_SS_SetMode(0);   // Input to the IP-Core

	// PWM carrier signal frequency is set to e.g. 100 kHz
	// PWM_SS_SetCarrierFrequency_Period(freq in Hz, period in us)
	PWM_SS_SetCarrierFrequency(uz_isr_frequency_hz);

	// PWM minimum pulse width is set between 0-1
	PWM_SS_SetMinimumPulseWidth(0.01f);

	// Reference for modulation amplitude (Duty Cycle) u1-u3  ->  value range must be inside 0-1
	PWM_SS_SetDutyCycle(data->rasv.halfBridge1DutyCycle,
						data->rasv.halfBridge2DutyCycle,
						data->rasv.halfBridge3DutyCycle);

	//Set the Tri-State to off (=default)
	PWM_SS_SetTriState(0,0,0);

	return Status;
}

void PWM_SS_SetDutyCycle(float duty_A, float duty_B, float duty_C){
	// limit modulation index to the rage of 0 to 1.0
	LIMIT(duty_A, 0, 1.0);
	LIMIT(duty_B, 0, 1.0);
	LIMIT(duty_C, 0, 1.0);

	// type conversion to fixed-point with 12 digits behind the comma
	int32_t  m_u1_norm = (int32_t)(ldexpf(duty_A, Q12)); 			//shift 12 Bits //data register for Inport m_u1_norm_AXI
	int32_t  m_u2_norm = (int32_t)(ldexpf(duty_B, Q12)); 			//shift 12 Bits //data register for Inport m_u2_norm_AXI
	int32_t  m_u3_norm = (int32_t)(ldexpf(duty_C, Q12)); 			//shift 12 Bits //data register for Inport m_u3_norm_AXI

	// write modulation index to FPGA registers
	Xil_Out32(PWM_SS_Con_m_u1_norm_REG, (int32_t)m_u1_norm);
	Xil_Out32(PWM_SS_Con_m_u2_norm_REG, (int32_t)m_u2_norm);
	Xil_Out32(PWM_SS_Con_m_u3_norm_REG, (int32_t)m_u3_norm);
}



void PWM_SS_SetStatus(int PWM_en){
	// to disable the PWM Module set 0
	// to enable  the PWM Module set 1
	Xil_Out32(PWM_SS_Con_Enable_REG, PWM_en);	// Input to the IP-Core
}

void PWM_SS_SetMode(int PWM_mode){
	//0 = PWM with modulation amplitude via AXI
	//1 = PWM with modulation amplitude via FPGA
	//2 = Control signals via FPGA (e.g. FCS-MPC)
	Xil_Out32(PWM_SS_Con_Mode_REG, (int32_t)PWM_mode);  //data register for Inport Mode_AXI
}

void PWM_SS_SetCarrierFrequency(float PWM_freq_Hz){
	float PWM_Scal_f_carrier = (PWM_freq_Hz/(FPGA_100MHz*0.5));     		//data register for Inport PWM_f_carrier_kHz_AXI

	// PWM carrier signal frequency is set, e.g. 100 kHz
	Xil_Out32(PWM_SS_Con_Scal_f_car_REG, (int32_t)(ldexpf(PWM_Scal_f_carrier,Q26))); 		//shift 26 Bits

	// calculate PWM period in microseconds
	float PWM_period_us = 1.0f/(PWM_freq_Hz)*1e6;

	// Set carrier signal period time (T_carrier = 1/PWM_period)
	float PWM_Scal_T_carrier = (PWM_period_us*((FPGA_100MHz*1e-6)*0.5)); 	//data register for Inport PWM_T_carrier_us_AXI (The factor 1e-6 comes from the unit [us])

	// PWM carrier signal Period is set to 1/PWM_freq, e.g. 10 us
	Xil_Out32(PWM_SS_Con_Scal_T_car_REG, (int32_t)PWM_Scal_T_carrier);

}

void PWM_SS_SetMinimumPulseWidth(float PWM_min_pulse_width){
	LIMIT(PWM_min_pulse_width, 0, 1);
	// Set PWM minimum pulse width in percent, range is between 0-1
	int32_t PWM_min_pulse_width_fp = (int32_t) (ldexpf(PWM_min_pulse_width,Q12)); 	//data register for Inport PWM_min_pulse_wiidth_AXI

	// Write register
	Xil_Out32(PWM_SS_Con_min_pulse_REG, (int32_t)PWM_min_pulse_width_fp);
}

void PWM_SS_SetTriState(int TriState_A, int TriState_B, int TriState_C){

	Xil_Out32(PWM_SS_Con_TriState_HB1_REG, (int32_t)TriState_A);
	Xil_Out32(PWM_SS_Con_TriState_HB2_REG, (int32_t)TriState_B);
	Xil_Out32(PWM_SS_Con_TriState_HB3_REG, (int32_t)TriState_C);
}

