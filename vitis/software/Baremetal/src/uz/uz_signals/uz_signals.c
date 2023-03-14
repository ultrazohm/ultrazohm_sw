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
#include <math.h>

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
	uz_assert(upper_limit > lower_limit);
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

float uz_signals_wrap(float number, float limit){
	uz_assert(limit > 0.0f);
    if((number < limit) && (number >= 0.0f)){
        return (number);
	}
    else {
		float rem = remainderf(number, limit);
		if((rem < limit) && (rem >= 0.0f)){
			return (rem);
		}
		else{
			return (rem + limit);
		}
	}
}

#endif