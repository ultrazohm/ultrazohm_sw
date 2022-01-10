/******************************************************************************
* Copyright 2021 Eyke Liegmann
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

#include "../include/pwm_3L_driver.h"
extern float uz_isr_frequency_hz;
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
	PWM_3L_SetMode(0);

	// set PWM carrier frequency
	PWM_3L_SetCarrierFrequency(uz_isr_frequency_hz);

	// PWM minimum pulse width is set between 0-1
	float pwmMinPulseWidth=0.01;
	PWM_3L_SetMinimumPulseWidth(pwmMinPulseWidth);

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
	int32_t duty_A_fp = (int32_t) ldexpf(duty_A, Q12);
	int32_t duty_B_fp = (int32_t) ldexpf(duty_B, Q12);
	int32_t duty_C_fp = (int32_t) ldexpf(duty_C, Q12);

	// write modulation index to FPGA registers
	Xil_Out32( PWM_3L_reg_dutyA ,(int32_t) duty_A_fp);
	Xil_Out32( PWM_3L_reg_dutyB ,(int32_t) duty_B_fp);
	Xil_Out32( PWM_3L_reg_dutyC ,(int32_t) duty_C_fp);
}

void PWM_3L_SetStatus(int32_t PWM_en){
	// to disable the PWM Module set 0
	// to enable  the PWM Module set 1
	Xil_Out32(PWM_3L_reg_enable, (int32_t) PWM_en);	// Input to the IP-Core
}

void PWM_3L_SetMode(int32_t PWM_mode){
	//0 = PWM with modulation amplitude via AXI
	//1 = PWM with modulation amplitude via FPGA
	//2 = Control signals via FPGA (e.g. FCS-MPC)
	Xil_Out32(PWM_3L_reg_mode, (int32_t) PWM_mode);
}

void PWM_3L_SetCarrierFrequency(float PWM_freq){
	// Sets desired switching frequency in Hz - range between 100Hz to 100kHz
	float t_switching_s = 1/PWM_freq; // switching period in seconds
	float pwm_counter_max_value = t_switching_s*FPGA_100MHz/2; // division by 2 because we use a triangular counter, which counts up and down
	// set PWM carrier Period register
	Xil_Out32(PWM_3L_reg_counter_max , (int32_t) pwm_counter_max_value);
}

void PWM_3L_SetMinimumPulseWidth(float PWM_min_pulse_width){
	LIMIT(PWM_min_pulse_width, 0, 1);
	// minimum on-time in between 0 and 1.0, same logic as duty cycle
	int min_pulse_width_fp = (int) ldexpf(PWM_min_pulse_width, Q12); // conversion to fixed-point
	// set minimal pulse width in percent
	Xil_Out32(PWM_3L_reg_min_pulse_width , (int32_t) min_pulse_width_fp);
}

void PWM_3L_SetTriState(int32_t TriState_A, int32_t TriState_B, int32_t TriState_C){

	Xil_Out32(PWM_3L_reg_TriStateA, (int32_t)TriState_A);
	Xil_Out32(PWM_3L_reg_TriStateB, (int32_t)TriState_B);
	Xil_Out32(PWM_3L_reg_TriStateC, (int32_t)TriState_C);
}


