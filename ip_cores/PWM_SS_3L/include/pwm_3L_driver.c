/******************************************************************************
 *
 * pwm.c
 *
 * Copyright (C) 2020 UltraZohm Community, All rights reserved.
 *
 *  Created on: 06.04.2020
 *      Author: Eyke Liegmann (EL)
 *
 ******************************************************************************/

#include "include/pwm.h"

//----------------------------------------------------
// INITIALIZE PWM AND SS CONTROL MODULE
//----------------------------------------------------
void Initialize_PWM_SS_Control(){

	// switching frequency
	float f_switching_Hz = 100e3; //desired switching frequency in Hz - range between 100Hz to 100kHz
	const float f_ip_core_clk = 100e6; // IP Core clock is 100MHz - check in Vivado

	float t_switching_s = 1/f_switching_Hz; // switching period in seconds
	float pwm_counter_max_value = t_switching_s*f_ip_core_clk/2; // division by 2 because we use a triangular counter, which counts up and down

	// minimum on-time in between 0 and 1.0, same logic as duty cycle
	float min_pulse_width  	 = 0.02;
	int   min_pulse_width_fp = (int) ldexpf(min_pulse_width, 12); // in fixed-point

	// Mode is set to 0, which is the Mode for switch signals from the PWM module with reference from AXI
	//0 = PWM with modulation amplitude via AXI
	//1 = PWM with modulation amplitude via FPGA
	//2 = Control signals via FPGA (e.g. FCS-MPC)
	Xil_Out32(PWM_reg_mode, 0);

	// set PWM carrier Period
	Xil_Out32(PWM_reg_counter_max , (int) pwm_counter_max_value);

	// set minimal pulse width in percent
	Xil_Out32(PWM_reg_min_pulse_width , min_pulse_width_fp);

	//enable PWM IP Core
	Xil_Out32(PWM_reg_enable, 1);

	// Set zero duty cycles
	SetDutyCycle(0.0f, 0.0f, 0.0f);

	print("PWM Module initialized\n\r");
}

// duty cycles in the rage of -1.0 to 1.0
void SetDutyCycle(float duty_A, float duty_B, float duty_C){
	int duty_A_fp = (int) ldexpf(duty_A,12);
	int duty_B_fp = (int) ldexpf(duty_B,12);
	int duty_C_fp = (int) ldexpf(duty_C,12);

	Xil_Out32( PWM_reg_dutyA ,duty_A_fp);
	Xil_Out32( PWM_reg_dutyB ,duty_B_fp);
	Xil_Out32( PWM_reg_dutyC ,duty_C_fp);
}
