/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Dennis Hufnagel, Tobias Schindler
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
#ifndef UZ_SIGNALS_H
#define UZ_SIGNALS_H

#include "uz_signals.h"
#include "../uz_global_configuration.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"


float uz_signals_dead_zone(float input, float upper_threshold, float lower_threshold) {
	uz_assert(upper_threshold > lower_threshold);
    float output=0.0f;
	if ( (input >= lower_threshold) && (input <= upper_threshold) ) {
		output = 0.0f;
	} else if (input > upper_threshold) {
		output = input - upper_threshold;
	} else {
		output = input - lower_threshold;
	}
	return (output);
}

float uz_signals_get_sign_of_value(float input) {
	float sign=0.0f;
	if (input < 0.0f){
		sign = -1.0f;
	}
	else if (input > 0.0f) {
		sign = 1.0f;
	} else {
		sign = 0.0f;
	}
	return (sign);
}
float uz_signals_saturation(float input, float upper_limit, float lower_limit) {
	uz_assert(upper_limit >= lower_limit);
	float output=0.0f;
	if (input > upper_limit) {
		output = upper_limit;
	} else if (input < lower_limit) {
		output = lower_limit;
	} else{
		output=input;
	}
	return (output);
}

struct uz_DutyCycle_t uz_sinusoidal_pwm(uz_3ph_abc_t input, float V_dc_volts){
	//Uses continuous sinusoidal PWM (SPWM)
	struct uz_DutyCycle_t output = {0};
	output.DutyCycle_A = ( (input.a / (0.5f * V_dc_volts) ) +1.0f) * 0.5f;
	output.DutyCycle_B = ( (input.b / (0.5f * V_dc_volts) ) +1.0f) * 0.5f;
	output.DutyCycle_C = ( (input.c / (0.5f * V_dc_volts) ) +1.0f) * 0.5f;
	output.DutyCycle_A = uz_signals_saturation(output.DutyCycle_A, 1.0f, 0.0f);
	output.DutyCycle_B = uz_signals_saturation(output.DutyCycle_B, 1.0f, 0.0f);
	output.DutyCycle_C = uz_signals_saturation(output.DutyCycle_C, 1.0f, 0.0f);
	return(output);
}

struct uz_DutyCycle_2x3ph_t uz_sinusoidal_pwm_6ph(uz_6ph_abc_t input, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};
	uz_3ph_abc_t abc_system1 = {
		.a = input.a1,
		.b = input.b1,
		.c = input.c1};
	uz_3ph_abc_t abc_system2 = {
		.a = input.a2,
		.b = input.b2,
		.c = input.c2};
	output.system1 = uz_sinusoidal_pwm(abc_system1, V_dc_volts);
	output.system2 = uz_sinusoidal_pwm(abc_system2, V_dc_volts);
	return output;
}

#endif