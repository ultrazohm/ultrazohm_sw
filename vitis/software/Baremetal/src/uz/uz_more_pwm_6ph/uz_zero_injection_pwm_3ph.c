/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2025 Josef Knoblach
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
#include "uz_zero_injection_pwm_3ph.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_HAL.h"
#include <math.h>
#include "../uz_6ph_SVPWM/uz_pwm_help_functions.h"



int signf(float num) {
    return (num >= 0) - (num < 0); // sign of zero is defined as positive
}

float uz_getmax_3ph_abc(uz_3ph_abc_t input){
	float temp = 0.0f;

	if(input.a > input.b){
		temp = input.a;
	}else{
		temp = input.b;
	}
	if(input.c > temp){
		temp = input.c;
	}
	return temp;
}


int uz_getmax_3ph_abc_abs_index(uz_3ph_abc_t input){
	int index = 3;
	float temp = 0.0f;

	input.a = fabsf(input.a);
	input.b = fabsf(input.b);
	input.c = fabsf(input.c);

	if(input.a > input.b){
		index = 1;
		temp = input.a;
	}else{
		index = 2;
		temp = input.b;
	}
	if(input.c > temp){
		index = 3;
	}
	return index;
}

float uz_getmin_3ph_abc(uz_3ph_abc_t input){
	float temp = 0.0f;

	if(input.a < input.b){
		temp = input.a;
	}else{
		temp = input.b;
	}
	if(input.c < temp){
		temp = input.c;
	}
	return temp;
}


float uz_getmid_3ph_abc(uz_3ph_abc_t input){

	if((input.a < input.b && input.b < input.c)|| (input.a > input.b && input.b > input.c) ){
		return input.b;
	}
	else if((input.b < input.a && input.a < input.c)|| (input.b > input.a && input.a > input.c) ){
		return input.a;
	}
	else
	{
		return input.c;
	}
}

static float uz_getmid_abs_3ph_abc(uz_3ph_abc_t input){

	if((fabsf(input.a) < fabsf(input.b) && fabsf(input.b) < fabsf(input.c))|| (fabsf(input.a) > fabsf(input.b) && fabsf(input.b) > fabsf(input.c)) ){
		return input.b;
	}
	else if((fabsf(input.b) < fabsf(input.a) && fabsf(input.a) < fabsf(input.c))|| (fabsf(input.b) > fabsf(input.a) && fabsf(input.a) > fabsf(input.c)) ){
		return input.a;
	}
	else
	{
		return input.c;
	}
}




struct uz_DutyCycle_t uz_PWM_THI_1_4_abc_3ph(uz_3ph_abc_t u_abc_ref, float V_dc_volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	// get angle of reference in alpha-beta plane
	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	// amplitude
	float Amp = sqrtf(powf(u_alphabeta_ref.alpha,2) + powf(u_alphabeta_ref.beta,2));

	// zero sequence 3. Harmonic
	float u_n = -(Amp/4)*cosf(3*theta);

	return uz_add_zerosequence_and_saturate_3ph(u_abc_ref, u_n, V_dc_volts);
}


struct uz_DutyCycle_t uz_PWM_THI_1_6_abc_3ph(uz_3ph_abc_t u_abc_ref, float V_dc_volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	// get angle of reference in alpha-beta plane
	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	// amplitude
	float Amp = sqrtf(powf(u_alphabeta_ref.alpha,2) + powf(u_alphabeta_ref.beta,2));

	// zero sequence 3. Harmonic
	float u_n = -(Amp/6)*cosf(3*theta);

	return uz_add_zerosequence_and_saturate_3ph(u_abc_ref, u_n, V_dc_volts);
}


struct uz_DutyCycle_t uz_SVM_abc_3ph(uz_3ph_abc_t u_abc_ref, float V_dc_volts){
	// zero sequence
	float u_n = -(uz_getmax_3ph_abc(u_abc_ref) + uz_getmin_3ph_abc(u_abc_ref))/2.0f;

	return uz_add_zerosequence_and_saturate_3ph(u_abc_ref, u_n, V_dc_volts);
}


struct uz_DutyCycle_t uz_GDPWM_abc_3ph(uz_3ph_abc_t u_abc_ref, float phi_rad, float V_dc_volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	// get angle of reference in alpha-beta plane
	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	theta = fmod(theta, 2.0f*M_PI/3.0f);

	float u_n = 0.0f;
	if( (M_PI/6.0f + phi_rad < theta && theta < M_PI/6.0f + phi_rad + M_PI/3.0f) || (M_PI/6 + phi_rad -2.0f*M_PI/3.0f < theta && theta < M_PI/6.0f + phi_rad + M_PI/3.0f -2.0f*M_PI/3.0f) ){
	    u_n = -uz_getmax_3ph_abc(u_abc_ref) + V_dc_volts/2.0f;
	}	else{
	    u_n = -uz_getmin_3ph_abc(u_abc_ref) - V_dc_volts/2.0f;
	}

	return uz_add_zerosequence_and_saturate_3ph(u_abc_ref, u_n, V_dc_volts);
}






struct uz_DutyCycle_t uz_GDPWM_abc_3ph_V2(uz_3ph_abc_t u_abc_ref, float phi_rad, float V_dc_volts){
	// https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=720446

	uz_3ph_abc_t u_abc_ref_x;

	u_abc_ref_x.a = u_abc_ref.a*cosf(phi_rad) - 1.0f/sqrtf(3.0f)*(u_abc_ref.c-u_abc_ref.b)*sinf(phi_rad);
	u_abc_ref_x.b = u_abc_ref.b*cosf(phi_rad) + (1.0f/2.0f*1/sqrtf(3.0f)*(u_abc_ref.c-u_abc_ref.b) -sqrtf(3.0f)/2.0f*u_abc_ref.a)*sinf(phi_rad);
	u_abc_ref_x.c = -u_abc_ref_x.a - u_abc_ref_x.b;

	int u_max_index = uz_getmax_3ph_abc_abs_index(u_abc_ref_x);

	float u_selected = 0.0f;

	if (u_max_index == 1){
		u_selected = u_abc_ref.a;
	}
	else if(u_max_index == 2){
		u_selected = u_abc_ref.b;
	}
	else if(u_max_index == 3.0){
		u_selected = u_abc_ref.c;
	}

	// calculate zero sequence component
	float u_n = signf(u_selected)*V_dc_volts/2.0f - u_selected;

	return uz_add_zerosequence_and_saturate_3ph(u_abc_ref, u_n, V_dc_volts);
}










struct uz_DutyCycle_t uz_DPWM0_abc_3ph(uz_3ph_abc_t u_abc_ref, float V_dc_volts){

	//return uz_GDPWM_abc_3ph(u_abc_ref, M_PI/6.0f, V_dc_volts);

	return uz_GDPWM_abc_3ph_V2(u_abc_ref, -M_PI/6.0f, V_dc_volts);
}

struct uz_DutyCycle_t uz_DPWM1_abc_3ph(uz_3ph_abc_t u_abc_ref, float V_dc_volts){
	// return uz_GDPWM_abc_3ph(u_abc_ref, M_PI/3.0f, V_dc_volts);

	float ref_max = uz_getmax_3ph_abc(u_abc_ref);
	float ref_min = uz_getmin_3ph_abc(u_abc_ref);

	float u_n = 0.0f;
	if(fabsf(ref_max) > fabsf(ref_min)){
		u_n = -(ref_max - V_dc_volts/2.0f);
	}else{
		u_n = -(ref_min + V_dc_volts/2.0f);
	}

	return uz_add_zerosequence_and_saturate_3ph(u_abc_ref, u_n, V_dc_volts);
}

struct uz_DutyCycle_t uz_DPWM1PHI_abc_3ph(uz_3ph_abc_t u_abc_ref, float V_dc_volts){

	 return uz_GDPWM_abc_3ph_V2(u_abc_ref, 0.0f, V_dc_volts);

	//return uz_GDPWM_abc_3ph(u_abc_ref, M_PI/3.0f, V_dc_volts);

}

struct uz_DutyCycle_t uz_DPWM2_abc_3ph(uz_3ph_abc_t u_abc_ref, float V_dc_volts){

	//return uz_GDPWM_abc_3ph(u_abc_ref, -M_PI/6.0f, V_dc_volts);

	return uz_GDPWM_abc_3ph_V2(u_abc_ref, M_PI/6.0f, V_dc_volts);
}

struct uz_DutyCycle_t uz_DPWM3_abc_3ph(uz_3ph_abc_t u_abc_ref, float V_dc_volts){
	// return uz_GDPWM_abc_3ph(u_abc_ref, 0.0f, V_dc_volts);

	float ref_mid = uz_getmid_abs_3ph_abc(u_abc_ref); // mid from absolute values of reference

	float u_n = signf(ref_mid)*V_dc_volts/2.0f - ref_mid;

	return uz_add_zerosequence_and_saturate_3ph(u_abc_ref, u_n, V_dc_volts);
}

struct uz_DutyCycle_t uz_DPWM3PHI_abc_3ph(uz_3ph_abc_t u_abc_ref, float V_dc_volts){

	return uz_GDPWM_abc_3ph(u_abc_ref, 0.0f, V_dc_volts);
}

struct uz_DutyCycle_t uz_DPWM_MAX_abc_3ph(uz_3ph_abc_t u_abc_ref, float V_dc_volts){

	float u_n = V_dc_volts/2.0f - uz_getmax_3ph_abc(u_abc_ref);

	return uz_add_zerosequence_and_saturate_3ph(u_abc_ref, u_n, V_dc_volts);
}

struct uz_DutyCycle_t uz_DPWM_MIN_abc_3ph(uz_3ph_abc_t u_abc_ref, float V_dc_volts){

	float u_n = -V_dc_volts/2.0f - uz_getmin_3ph_abc(u_abc_ref);

	return uz_add_zerosequence_and_saturate_3ph(u_abc_ref, u_n, V_dc_volts);
}
