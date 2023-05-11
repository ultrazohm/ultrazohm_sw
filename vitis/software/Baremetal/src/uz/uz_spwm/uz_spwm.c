/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2023 Valentin Hoppe
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
#ifndef UZ_SPWM_C
#define UZ_SPWM_C

#include "uz_spwm.h"
#include "../uz_signals/uz_signals.h"

struct uz_DutyCycle_t uz_spwm_dq(uz_3ph_dq_t input, float V_dc_volts, float theta_el_rad){
    return uz_spwm_abc(uz_transformation_3ph_dq_to_abc(input, theta_el_rad), V_dc_volts);
}

struct uz_DutyCycle_t uz_spwm_abc(uz_3ph_abc_t input, float V_dc_volts){
	//Uses continuous sinusoidal PWM (SPWM)
	struct uz_DutyCycle_t output = {
        .DutyCycle_A = ((input.a / (0.5f * V_dc_volts)) + 1.0f) * 0.5f,
        .DutyCycle_B = ((input.b / (0.5f * V_dc_volts)) + 1.0f) * 0.5f,
        .DutyCycle_C = ((input.c / (0.5f * V_dc_volts)) + 1.0f) * 0.5f};
	output.DutyCycle_A = uz_signals_saturation(output.DutyCycle_A, 1.0f, 0.0f);
	output.DutyCycle_B = uz_signals_saturation(output.DutyCycle_B, 1.0f, 0.0f);
	output.DutyCycle_C = uz_signals_saturation(output.DutyCycle_C, 1.0f, 0.0f);
	return(output);
}

struct uz_DutyCycle_2x3ph_t uz_spwm_abc_dq(uz_6ph_dq_t input, float V_dc_volts, float theta_el_rad){
	return uz_spwm_abc_6ph(uz_transformation_asym30deg_6ph_dq_to_abc(input, theta_el_rad), V_dc_volts);
}

struct uz_DutyCycle_2x3ph_t uz_spwm_abc_6ph(uz_6ph_abc_t input, float V_dc_volts){
	uz_3ph_abc_t abc_system1 = {
		.a = input.a1,
		.b = input.b1,
		.c = input.c1};
	uz_3ph_abc_t abc_system2 = {
		.a = input.a2,
		.b = input.b2,
		.c = input.c2};
    struct uz_DutyCycle_2x3ph_t output = {
        .system1 = uz_sinusoidal_pwm(abc_system1, V_dc_volts),
        .system2 = uz_sinusoidal_pwm(abc_system2, V_dc_volts)};
	return output;
}

#endif // UZ_SPWM_C