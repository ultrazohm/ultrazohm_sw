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


#include "uz_wavegen.h"
#include <math.h>
#include <stdlib.h>
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include "../uz_SystemTime/uz_SystemTime.h"

float uz_wavegen_sine(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
	float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
	float angle = 2.0f * UZ_PIf * t_Sec * frequency_Hz;
	return (amplitude * sinf(angle));
}

float uz_wavegen_sine_with_offset(float amplitude, float frequency_Hz, float offset) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
	float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
	float angle = 2.0f * UZ_PIf * t_Sec * frequency_Hz;
	return ((amplitude * sinf(angle)) + offset);
}

float uz_wavegen_sawtooth(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
	float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t_Sec, 1.0f / frequency_Hz);
	return (sample * amplitude * frequency_Hz);
}

float uz_wavegen_sawtooth_with_offset(float amplitude, float frequency_Hz, float offset) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
	float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t_Sec, 1.0f / frequency_Hz);
	return ( (sample * amplitude * frequency_Hz) + offset);
}

float uz_wavegen_pulse(float amplitude, float frequency_Hz, float duty_cycle) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(duty_cycle >= 0.0f);
	uz_assert(duty_cycle <= 1.0f);
	uz_assert(amplitude != 0.0f);
	float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t_Sec, 1.0f / frequency_Hz);
	float output=0.0f;
	if (sample > (1.0f / frequency_Hz * duty_cycle) ) {
		output = 0.0f;
	}else{
		output=amplitude;
	}
	return (output);
}

float uz_wavegen_square(float amplitude, float frequency_Hz, float duty_cycle) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(duty_cycle >= 0.0f);
	uz_assert(duty_cycle <= 1.0f);
	uz_assert(amplitude != 0.0f);
	float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t_Sec, 1.0f / frequency_Hz);
	float output=0.0f;
	if (sample > (1.0f / frequency_Hz * duty_cycle) ) {
		output = amplitude * -1.0f;
	} else{
		output = amplitude;
	}
	return (output);
}

float uz_wavegen_triangle(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
	float triangle_wave = 0.0f;
	float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t_Sec, 1.0f / frequency_Hz);
	if (sample > (1.0f / frequency_Hz * 0.5f) ) {
		triangle_wave = (2.0f * amplitude) - (2.0f * sample * amplitude * frequency_Hz);
	} else {
		triangle_wave = 2.0f * sample * amplitude * frequency_Hz;
	}
	return (triangle_wave);
}

float uz_wavegen_triangle_with_offset(float amplitude, float frequency_Hz, float offset) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
	float triangle_wave = 0.0f;
	float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t_Sec, 1.0f / frequency_Hz);
	if (sample > (1.0f / frequency_Hz * 0.5f) ) {
		triangle_wave = ((2.0f * amplitude) - (2.0f * sample * amplitude * frequency_Hz)) + offset;
	} else {
		triangle_wave = (2.0f * sample * amplitude * frequency_Hz) + offset;
	}
	return (triangle_wave);
}

float uz_wavegen_white_noise(float amplitude) {
	uz_assert(amplitude != 0.0f);
	return (amplitude * ( ((float)rand() / (float)RAND_MAX * 2.0f) - 1.0f) );
}

uz_3ph_abc_t uz_wavegen_three_phase_sample(float amplitude, float frequency_Hz, float offset)
{
    uz_assert(frequency_Hz > 0.0f);
    float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
    float angle = 2.0f * UZ_PIf * t_Sec * frequency_Hz;
    uz_3ph_abc_t sine_output = {
        .a = amplitude * sinf(angle) + offset,
        .b = amplitude * sinf(angle - (2.0f * UZ_PIf / 3.0f)) + offset,
        .c = amplitude * sinf(angle - (4.0f * UZ_PIf / 3.0f)) + offset};
    return sine_output;
}
