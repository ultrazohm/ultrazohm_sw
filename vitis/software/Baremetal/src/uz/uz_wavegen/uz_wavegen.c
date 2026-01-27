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


    // uz_3ph_abc_t sine_output = {
   //     .a = amplitude * sinf(angle) + offset,
   //      .b = amplitude * sinf(angle - (2.0f * UZ_PIf / 3.0f)) + offset,
   //      .c = amplitude * sinf(angle - (4.0f * UZ_PIf / 3.0f)) + offset};

    float v1 = amplitude * sinf(angle) + offset;
    float v2 = amplitude * sinf(angle - (2.0f * UZ_PIf / 3.0f)) + offset;
    float v3 = amplitude * sinf(angle - (4.0f * UZ_PIf / 3.0f)) + offset;

    int PWM_mode = 1; // 0 SPWM // 1 Negative-DPWM // 2 Positive-Negative DPWM

    if (PWM_mode == 0) // 0 SPWM
    {
       //
    }
    else if (PWM_mode == 1) // 1 Negative-DPWM
    {
        //float cm = (v1 < v2) ? ((v1 < v3) ? v1 : v3) : ((v2 < v3) ? v2 : v3); to find the minimum, did not work
        float cm = fminf(fminf(v1, v2), v3);
        v1 = v1 - cm;
        v2 = v2 - cm;
        v3 = v3 - cm;

    }
    else // 2 Positive-Negative DPWM
    {

    	    float v1_bid = v1*2.0f-1.0f;
    	    float v2_bid = v2*2.0f-1.0f;
    	    float v3_bid = v3*2.0f-1.0f;

    	    float u_min = fminf(fminf(v1_bid, v2_bid), v3_bid);
    	    float u_max = fmaxf(fmaxf(v1_bid, v2_bid), v3_bid);

    	    float u_max_abs = fmaxf(fmaxf(fabsf(v1_bid), fabsf(v2_bid)), fabsf(v3_bid));

    	    float val = u_max - fabsf(u_min);
    	   // float sign_value = 1.0f;

    	    //if (val < 0) {sign_value = -1.0f;}
    	   float sign_value = (val > 0.0f) ? 1.0f : ((val < 0.0f) ? -1.0f : 0.0f);
    	    float cm_pn_clamping = 0.5f+(0.5f-u_max_abs)*sign_value;

    	    if (cm_pn_clamping >= 0.5f) {cm_pn_clamping = cm_pn_clamping -1.0f;}

    	    //cm_pn_clamping = cm_pn_clamping*0.5f+0.5f;


    	  float v1_final = v1_bid + cm_pn_clamping;
    	  float v2_final = v2_bid + cm_pn_clamping;
    	  float v3_final = v3_bid + cm_pn_clamping;

    	  float v1_final_final = v1_final*0.5+0.5;
    	   float v2_final_final = v2_final*0.5+0.5;
    	   float v3_final_final = v3_final*0.5+0.5;


    	   v1_final_final = fminf(fmaxf(v1_final_final, 0.0f), 1.0f);
    	   v2_final_final = fminf(fmaxf(v2_final_final, 0.0f), 1.0f);
    	   v3_final_final = fminf(fmaxf(v3_final_final, 0.0f), 1.0f);

           v1 = v1_final_final;
           v2 = v2_final_final;
           v3 = v3_final_final;

    }


    uz_3ph_abc_t sine_output = {
    	.a = v1,
        .b = v2,
        .c = v3};

    return sine_output;
}


