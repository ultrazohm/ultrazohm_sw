/******************************************************************************
 *
 * pwm_3L_driver.c
 *
 * Copyright (C) 2020 UltraZohm Community, All rights reserved.
 *
 *  Created on: 06.04.2020
 *      Author: Eyke Liegmann (EL)
 *
 ******************************************************************************/

#include "../include/pwm_3L_driver.h"

//----------------------------------------------------
// INITIALIZE PWM (three-level) AND SS CONTROL MODULE
//----------------------------------------------------
void PWM_3L_Initialize(DS_Data* data){

	// PWM enable is set to 0 and disable the PWM Module
	// Always enable PWM module to get interrupts
	PWM_3L_SetStatus(PWM_3L_ENABLE);

	// Mode is set to 0, which is the Mode for switch signals from the PWM module with reference from AXI
	//0 = PWM with modulation amplitude via AXI
	//1 = PWM with modulation amplitude via FPGA
	//2 = Control signals via FPGA (e.g. FCS-MPC)
	PWM_3L_SetMode(data->cw.switchingMode);

	// set PWM carrier frequency
	PWM_3L_SetCarrierFrequency(data->ctrl.pwmFrequency);

	// PWM minimum pulse width is set between 0-1
	PWM_3L_SetMinimumPulseWidth(data->rasv.pwmMinPulseWidth);

	// Set zero duty cycles
	PWM_3L_SetDutyCycle(data->rasv.halfBridge1DutyCycle,
						data->rasv.halfBridge2DutyCycle,
						data->rasv.halfBridge3DutyCycle);

	//Set the Tri-State to off (=default)
	PWM_3L_SetTriState(0,0,0);

	//print("PWM Module three-level initialized\n\r");
}

void PWM_3L_SetDutyCycle(float duty_A, float duty_B, float duty_C){
	// limit duty cycle to the rage of -1.0 to 1.0
	LIMIT(duty_A, -1.0, 1.0);
	LIMIT(duty_B, -1.0, 1.0);
	LIMIT(duty_C, -1.0, 1.0);

	// type conversion to fixed-point with 12 digits behind the comma
	Xint32 duty_A_fp = (Xint32) ldexpf(duty_A, Q12);
	Xint32 duty_B_fp = (Xint32) ldexpf(duty_B, Q12);
	Xint32 duty_C_fp = (Xint32) ldexpf(duty_C, Q12);

	// write modulation index to FPGA registers
	Xil_Out32( PWM_3L_reg_dutyA ,(Xint32) duty_A_fp);
	Xil_Out32( PWM_3L_reg_dutyB ,(Xint32) duty_B_fp);
	Xil_Out32( PWM_3L_reg_dutyC ,(Xint32) duty_C_fp);
}

void PWM_3L_SetStatus(Xint32 PWM_en){
	// to disable the PWM Module set 0
	// to enable  the PWM Module set 1
	Xil_Out32(PWM_3L_reg_enable, (Xint32) PWM_en);	// Input to the IP-Core
}

void PWM_3L_SetMode(int PWM_mode){
	//0 = PWM with modulation amplitude via AXI
	//1 = PWM with modulation amplitude via FPGA
	//2 = Control signals via FPGA (e.g. FCS-MPC)
	Xil_Out32(PWM_3L_reg_mode, (Xint32) PWM_mode);
}

void PWM_3L_SetCarrierFrequency(float PWM_freq){
	// Sets desired switching frequency in Hz - range between 100Hz to 100kHz
	float t_switching_s = 1/PWM_freq; // switching period in seconds
	float pwm_counter_max_value = t_switching_s*FPGA_100MHz/2; // division by 2 because we use a triangular counter, which counts up and down
	// set PWM carrier Period register
	Xil_Out32(PWM_3L_reg_counter_max , (Xint32) pwm_counter_max_value);
}

void PWM_3L_SetMinimumPulseWidth(float PWM_min_pulse_width){
	LIMIT(PWM_min_pulse_width, 0, 1);
	// minimum on-time in between 0 and 1.0, same logic as duty cycle
	int min_pulse_width_fp = (int) ldexpf(PWM_min_pulse_width, Q12); // conversion to fixed-point
	// set minimal pulse width in percent
	Xil_Out32(PWM_3L_reg_min_pulse_width , (Xint32) min_pulse_width_fp);
}

void PWM_3L_SetTriState(int TriState_A, int TriState_B, int TriState_C){

	Xil_Out32(PWM_3L_reg_TriStateA, (Xint32)TriState_A);
	Xil_Out32(PWM_3L_reg_TriStateB, (Xint32)TriState_B);
	Xil_Out32(PWM_3L_reg_TriStateC, (Xint32)TriState_C);
}

void PWM_3L_SetDutyCycle_open_loop_sin(DS_Data* data){
	//TODO: adjust pwmFrequency depending on the interrupt chosen in isr.h

	//Variables
	static long sample =0;
	float interrupt_freq = 	data->ctrl.pwmFrequency;
	float sin_amplitude = 	data->rasv.open_loop_sin_amplitude;
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

	duty_cycle_a = sin_amplitude * sinf(angle);
	duty_cycle_b = sin_amplitude * sinf(angle + 2*PI/3);
	duty_cycle_c = sin_amplitude * sinf(angle + 4*PI/3);

	PWM_SS_SetDutyCycle(duty_cycle_a, duty_cycle_b, duty_cycle_c);
}
