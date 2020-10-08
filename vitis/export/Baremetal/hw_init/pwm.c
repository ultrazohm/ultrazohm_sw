/******************************************************************************
*
* pwm.c
*
* Copyright (C) 2019 UltraZohm Community, All rights reserved.
*
*  Created on: 21.10.2018
*      Author: Sebastian Wendel (SW)
*
******************************************************************************/

#include "../include/pwm.h"

//----------------------------------------------------
// INITIALIZE PWM AND SS (switching state) CONTROL MODULE
//----------------------------------------------------
int PWM_SS_Initialize(DS_Data* data){

	int Status = 0;

	// PWM enable is set to 0 and disable the PWM Module
	//PWM_SS_SetStatus(data->cw.enableControl);
	// Always enable PWM module to get interrupts
	PWM_SS_SetStatus(PWM_ENABLE);

	// Mode is set to 0, which is the Mode for switch signals from the PWM module with reference from AXI
	PWM_SS_SetMode(data->cw.switchingMode);   // Input to the IP-Core

	// PWM carrier signal frequency is set to e.g. 100 kHz
	// PWM_SS_SetCarrierFrequency_Period(freq in Hz, period in us)
	PWM_SS_SetCarrierFrequency(data->ctrl.pwmFrequency);

	// PWM minimum pulse width is set between 0-1
	PWM_SS_SetMinimumPulseWidth(data->rasv.pwmMinPulseWidth);

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
	Xint32  m_u1_norm = (Xint32)(ldexpf(duty_A, Q12)); 			//shift 12 Bits //data register for Inport m_u1_norm_AXI
	Xint32  m_u2_norm = (Xint32)(ldexpf(duty_B, Q12)); 			//shift 12 Bits //data register for Inport m_u2_norm_AXI
	Xint32  m_u3_norm = (Xint32)(ldexpf(duty_C, Q12)); 			//shift 12 Bits //data register for Inport m_u3_norm_AXI

	// write modulation index to FPGA registers
	Xil_Out32(PWM_SS_Con_m_u1_norm_REG, (Xint32)m_u1_norm);
	Xil_Out32(PWM_SS_Con_m_u2_norm_REG, (Xint32)m_u2_norm);
	Xil_Out32(PWM_SS_Con_m_u3_norm_REG, (Xint32)m_u3_norm);
}



void PWM_SS_SetStatus(Xint32 PWM_en){
	// to disable the PWM Module set 0
	// to enable  the PWM Module set 1
	Xil_Out32(PWM_SS_Con_Enable_REG, PWM_en);	// Input to the IP-Core
}

void PWM_SS_SetMode(int PWM_mode){
	//0 = PWM with modulation amplitude via AXI
	//1 = PWM with modulation amplitude via FPGA
	//2 = Control signals via FPGA (e.g. FCS-MPC)
	Xil_Out32(PWM_SS_Con_Mode_REG, (Xint32)PWM_mode);  //data register for Inport Mode_AXI
}

void PWM_SS_SetCarrierFrequency(float PWM_freq_Hz){
	Xfloat32 PWM_Scal_f_carrier = (PWM_freq_Hz/(FPGA_100MHz*0.5));     		//data register for Inport PWM_f_carrier_kHz_AXI

	// PWM carrier signal frequency is set, e.g. 100 kHz
	Xil_Out32(PWM_SS_Con_Scal_f_car_REG, (Xint32)(ldexpf(PWM_Scal_f_carrier,Q26))); 		//shift 26 Bits

	// calculate PWM period in microseconds
	Xfloat32 PWM_period_us = 1.0f/(PWM_freq_Hz)*1e6;

	// Set carrier signal period time (T_carrier = 1/PWM_period)
	Xfloat32 PWM_Scal_T_carrier = (PWM_period_us*((FPGA_100MHz*1e-6)*0.5)); 	//data register for Inport PWM_T_carrier_us_AXI (The factor 1e-6 comes from the unit [us])

	// PWM carrier signal Period is set to 1/PWM_freq, e.g. 10 us
	Xil_Out32(PWM_SS_Con_Scal_T_car_REG, (Xint32)PWM_Scal_T_carrier);

}

void PWM_SS_SetMinimumPulseWidth(float PWM_min_pulse_width){
	LIMIT(PWM_min_pulse_width, 0, 1);
	// Set PWM minimum pulse width in percent, range is between 0-1
	Xint32 PWM_min_pulse_width_fp = (Xint32) (ldexpf(PWM_min_pulse_width,Q12)); 	//data register for Inport PWM_min_pulse_wiidth_AXI

	// Write register
	Xil_Out32(PWM_SS_Con_min_pulse_REG, (Xint32)PWM_min_pulse_width_fp);
}

void PWM_SS_SetTriState(int TriState_A, int TriState_B, int TriState_C){

	Xil_Out32(PWM_SS_Con_TriState_HB1_REG, (Xint32)TriState_A);
	Xil_Out32(PWM_SS_Con_TriState_HB2_REG, (Xint32)TriState_B);
	Xil_Out32(PWM_SS_Con_TriState_HB3_REG, (Xint32)TriState_C);
}


void PWM_SS_SetDutyCycle_open_loop_sin(DS_Data* data){
	//TODO: adjust pwmFrequency depending on the interrupt chosen in isr.h

	//Variables
	static long sample =0;
	float interrupt_freq = 	data->ctrl.pwmFrequency;
	float sin_amplitude = 	data->rasv.open_loop_sin_amplitude * 0.5;
	float sin_frequency = 	data->rasv.open_loop_sin_frequency;

	float duty_cycle_a, duty_cycle_b, duty_cycle_c;
	float angle;

	//Go back to 1st sample if end of sinewave is reached
	if(sample >= interrupt_freq/sin_frequency - 1)
		sample = 0;

	//Calculate angle and increase sample
	angle = 2.0*PI*sin_frequency/interrupt_freq*((float)(sample));
	//angle += phase; // add phase shift
	sample++;

	duty_cycle_a = 0.5 + sin_amplitude * sinf(angle);
	duty_cycle_b = 0.5 + sin_amplitude * sinf(angle + 2*PI/3);
	duty_cycle_c = 0.5 + sin_amplitude * sinf(angle + 4*PI/3);

	PWM_SS_SetDutyCycle(duty_cycle_a, duty_cycle_b, duty_cycle_c);
}
