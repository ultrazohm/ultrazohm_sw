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
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

//struct uz_PWM_SS_2L_config_t config_D4 = {
//    .base_address = 0x0,              /**< Base address of the IP-Core */
//    .ip_clk_frequency_Hz= 100e6,      /**< Clock frequency of the IP-Core */
//    .Tristate_HB1 = false,                  /**< Tristate flag for half-bridge 1, true=on, false=off */
//    .Tristate_HB2 = false,                  /**< Tristate flag for half-bridge 2, true=on, false=off */
//    .Tristate_HB3 = false,                  /**< Tristate flag for half-bridge 3, true=on, false=off */
//    .min_pulse_width = 0.01,              /**< Minimum pulse width in percent, e.g. 0.01 */
//    .PWM_freq_Hz = 100e3,                  /**< Switching frequency of PWM mode in Hz */
//    .PWM_mode = normalized_input_via_AXI,/**< PWM mode selector\n
//                                        0 = normalized input of reference signal via AXI\n
//                                            e.g. a reference voltage value between 0 and 1\n
//                                        1 = normalized input of reference signal via FPGA\n
//                                            e.g. a reference voltage value between 0 and 1\n
//                                        2 = direct control of switching states via FPGA */
//    .PWM_en = true,                        /**< IP core enable flag\n
//                                         0=disable module, 1=enable module */
//    .use_external_counter = false,          /**< Flag for choosing the PWM counter source\n
//                                         0 = internal counter source of the instance\n
//                                         1 = counter at port count_in */
//    .init_dutyCyc_A = 0.0,               /**< Initial PWM duty cycle of half-bridge 1, 0...1 */
//    .init_dutyCyc_B = 0.0,               /**< Initial PWM duty cycle of half-bridge 2, 0...1 */
//    .init_dutyCyc_C = 0.0,               /**< Initial PWM duty cycle of half-bridge 3, 0...1 */
//};
//
//struct uz_PWM_SS_2L_config_t config_D3 = {
//    .base_address = 0x0,              /**< Base address of the IP-Core */
//    .ip_clk_frequency_Hz= 100e6,      /**< Clock frequency of the IP-Core */
//    .Tristate_HB1 = false,                  /**< Tristate flag for half-bridge 1, true=on, false=off */
//    .Tristate_HB2 = false,                  /**< Tristate flag for half-bridge 2, true=on, false=off */
//    .Tristate_HB3 = false,                  /**< Tristate flag for half-bridge 3, true=on, false=off */
//    .min_pulse_width = 0.01,              /**< Minimum pulse width in percent, e.g. 0.01 */
//    .PWM_freq_Hz = 100e3,                  /**< Switching frequency of PWM mode in Hz */
//    .PWM_mode = normalized_input_via_AXI,/**< PWM mode selector\n
//                                        0 = normalized input of reference signal via AXI\n
//                                            e.g. a reference voltage value between 0 and 1\n
//                                        1 = normalized input of reference signal via FPGA\n
//                                            e.g. a reference voltage value between 0 and 1\n
//                                        2 = direct control of switching states via FPGA */
//    .PWM_en = true,                        /**< IP core enable flag\n
//                                         0=disable module, 1=enable module */
//    .use_external_counter = true,          /**< Flag for choosing the PWM counter source\n
//                                         0 = internal counter source of the instance\n
//                                         1 = counter at port count_in */
//    .init_dutyCyc_A = 0.0,               /**< Initial PWM duty cycle of half-bridge 1, 0...1 */
//    .init_dutyCyc_B = 0.0,               /**< Initial PWM duty cycle of half-bridge 2, 0...1 */
//    .init_dutyCyc_C = 0.0,               /**< Initial PWM duty cycle of half-bridge 3, 0...1 */
//};

//uz_PWM_SS_2L_t *PWM_SS_2L_d4;
//uz_PWM_SS_2L_t *PWM_SS_2L_d3;

//----------------------------------------------------
// INITIALIZE PWM AND SS (switching state) CONTROL MODULE
//----------------------------------------------------
//int PWM_SS_Initialize(DS_Data* data){

//	PWM_SS_2L_d4 = uz_PWM_SS_2L_init(config_D4);
//	PWM_SS_2L_d3 = uz_PWM_SS_2L_init(config_D3);
//
//	int Status = 0;
//	// Always enable PWM module to get interrupts
//	PWM_SS_SetStatus(PWM_ENABLE);
//
//	// Mode is set to 0, which is the Mode for switch signals from the PWM module with reference from AXI
//	PWM_SS_SetMode(data->cw.switchingMode);   // Input to the IP-Core
//
//	// PWM carrier signal frequency is set to e.g. 100 kHz
//	// PWM_SS_SetCarrierFrequency_Period(freq in Hz, period in us)
//	PWM_SS_SetCarrierFrequency(data->ctrl.pwmFrequency);
//
//	// PWM minimum pulse width is set between 0-1
//	PWM_SS_SetMinimumPulseWidth(data->rasv.pwmMinPulseWidth);
//
//	// Reference for modulation amplitude (Duty Cycle) u1-u3  ->  value range must be inside 0-1
//	PWM_SS_SetDutyCycle(data->rasv.halfBridge1DutyCycle,
//						data->rasv.halfBridge2DutyCycle,
//						data->rasv.halfBridge3DutyCycle);
//
//	//Set the Tri-State to off (=default)
//	PWM_SS_SetTriState(0,0,0);
//
//	return Status;
//}
//
//void PWM_SS_SetDutyCycle(float duty_A, float duty_B, float duty_C){
//	// limit modulation index to the rage of 0 to 1.0
//	LIMIT(duty_A, 0, 1.0);
//	LIMIT(duty_B, 0, 1.0);
//	LIMIT(duty_C, 0, 1.0);
//
//	// type conversion to fixed-point with 12 digits behind the comma
//	int32_t  m_u1_norm = (int32_t)(ldexpf(duty_A, Q12)); 			//shift 12 Bits //data register for Inport m_u1_norm_AXI
//	int32_t  m_u2_norm = (int32_t)(ldexpf(duty_B, Q12)); 			//shift 12 Bits //data register for Inport m_u2_norm_AXI
//	int32_t  m_u3_norm = (int32_t)(ldexpf(duty_C, Q12)); 			//shift 12 Bits //data register for Inport m_u3_norm_AXI
//
//	// write modulation index to FPGA registers
//	Xil_Out32(PWM_SS_Con_m_u1_norm_REG, (int32_t)m_u1_norm);
//	Xil_Out32(PWM_SS_Con_m_u2_norm_REG, (int32_t)m_u2_norm);
//	Xil_Out32(PWM_SS_Con_m_u3_norm_REG, (int32_t)m_u3_norm);
//}
//
//
//
//void PWM_SS_SetStatus(int PWM_en){
//	// to disable the PWM Module set 0
//	// to enable  the PWM Module set 1
//	Xil_Out32(PWM_SS_Con_Enable_REG, PWM_en);	// Input to the IP-Core
//}
//
//void PWM_SS_SetMode(int PWM_mode){
//	//0 = PWM with modulation amplitude via AXI
//	//1 = PWM with modulation amplitude via FPGA
//	//2 = Control signals via FPGA (e.g. FCS-MPC)
//	Xil_Out32(PWM_SS_Con_Mode_REG, (int32_t)PWM_mode);  //data register for Inport Mode_AXI
//}
//
//void PWM_SS_SetCarrierFrequency(float PWM_freq_Hz){
//	float PWM_Scal_f_carrier = (PWM_freq_Hz/(FPGA_100MHz*0.5));     		//data register for Inport PWM_f_carrier_kHz_AXI
//
//	// PWM carrier signal frequency is set, e.g. 100 kHz
//	Xil_Out32(PWM_SS_Con_Scal_f_car_REG, (int32_t)(ldexpf(PWM_Scal_f_carrier,Q26))); 		//shift 26 Bits
//
//	// calculate PWM period in microseconds
//	float PWM_period_us = 1.0f/(PWM_freq_Hz)*1e6;
//
//	// Set carrier signal period time (T_carrier = 1/PWM_period)
//	float PWM_Scal_T_carrier = (PWM_period_us*((FPGA_100MHz*1e-6)*0.5)); 	//data register for Inport PWM_T_carrier_us_AXI (The factor 1e-6 comes from the unit [us])
//
//	// PWM carrier signal Period is set to 1/PWM_freq, e.g. 10 us
//	Xil_Out32(PWM_SS_Con_Scal_T_car_REG, (int32_t)PWM_Scal_T_carrier);
//
//}
//
//void PWM_SS_SetMinimumPulseWidth(float PWM_min_pulse_width){
//	LIMIT(PWM_min_pulse_width, 0, 1);
//	// Set PWM minimum pulse width in percent, range is between 0-1
//	int32_t PWM_min_pulse_width_fp = (int32_t) (ldexpf(PWM_min_pulse_width,Q12)); 	//data register for Inport PWM_min_pulse_wiidth_AXI
//
//	// Write register
//	Xil_Out32(PWM_SS_Con_min_pulse_REG, (int32_t)PWM_min_pulse_width_fp);
//}
//
//void PWM_SS_SetTriState(int TriState_A, int TriState_B, int TriState_C){
//
//	Xil_Out32(PWM_SS_Con_TriState_HB1_REG, (int32_t)TriState_A);
//	Xil_Out32(PWM_SS_Con_TriState_HB2_REG, (int32_t)TriState_B);
//	Xil_Out32(PWM_SS_Con_TriState_HB3_REG, (int32_t)TriState_C);
//}
//
//
//void PWM_SS_Calculate_DutyCycle_open_loop_sin(DS_Data* data){
//
//	//Variables
//	static long sample =0;
//	float interrupt_freq = 	data->ctrl.samplingFrequency;
//	float sin_amplitude = 	data->rasv.open_loop_sin_amplitude * 0.5; // modulation index
//	float sin_frequency = 	data->rasv.open_loop_sin_frequency;
//
//	//Go back to 1st sample if end of sinewave is reached
//	if(sample >= interrupt_freq/sin_frequency - 1)
//		sample = 0;
//
//	//Calculate angle and increase sample
//	float angle = 2.0*M_PI*sin_frequency/interrupt_freq*((float)(sample));
//	//angle += phase; // add phase shift
//	sample++;
//
//	// write duty cycles to Global_Data struct, in ISR these values are written down to the FPGA registers
//	data->rasv.halfBridge1DutyCycle = 0.5 + sin_amplitude * sinf(angle);
//	data->rasv.halfBridge2DutyCycle = 0.5 + sin_amplitude * sinf(angle + 2*M_PI/3);
//	data->rasv.halfBridge3DutyCycle = 0.5 + sin_amplitude * sinf(angle + 4*M_PI/3);
//}