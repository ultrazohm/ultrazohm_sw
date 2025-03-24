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

#include "uz_zero_injection_based_pwm.h"
#include "../uz_HAL.h"
#include <math.h>
#include "../uz_signals/uz_signals.h"

#define SQRT_3_HALF sqrt(3.0f)/2.0f

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
	else //if((input.a < input.c && input.c < input.b)|| (input.a > input.c && input.c > input.b) ){
	{
		return input.c;
	}
}

struct uz_DutyCycle_2x3ph_t  uz_CSVPWM_24_2L_1ML_1M_v2_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// reference in abc1abc2
	uz_6ph_abc_t u_abc1abc2_ref = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	// alpha-beta in both systems
	uz_3ph_alphabeta_t u_alphabeta_ref_sys1 = uz_transformation_3ph_abc_to_alphabeta(u_abc_sys1);
	uz_3ph_alphabeta_t u_alphabeta_ref_sys2 = uz_transformation_3ph_abc_to_alphabeta(u_abc_sys2);

	// angle in both systems
	float theta_1 = atan2f(u_alphabeta_ref_sys1.beta, u_alphabeta_ref_sys1.alpha);
	float theta_2 = atan2f(u_alphabeta_ref_sys2.beta, u_alphabeta_ref_sys2.alpha);

	theta_1 = fmod(theta_1+2*M_PI, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	theta_2 = fmod(theta_2+2*M_PI, 2.0f*M_PI/3.0f);


	// get sector
	int sector_24_sys1 = floor( theta_1/(M_PI/12.0f) - fmod(theta_1, M_PI/12.0f) ) + 1;
	if(sector_24_sys1 > 24){
		sector_24_sys1 = 1;
	}
	// get sector
	int sector_24_sys2 = floor( theta_2/(M_PI/12.0f) - fmod(theta_2, M_PI/12.0f) ) + 1;
	if(sector_24_sys2 > 24){
		sector_24_sys2 = 1;
	}

	// calculation of zero sequence
	float u_n1 = 0;
	float u_n2 = 0;

	float u_max1 = uz_getmax_3ph_abc(u_abc_sys1);
	float u_min1 = uz_getmin_3ph_abc(u_abc_sys1);
	float u_mid1 = uz_getmid_3ph_abc(u_abc_sys1);

	if (sector_24_sys1 <= 1){
	    u_n1 = u_max1 * (sqrt(3)/2-1);
	}
	else if (sector_24_sys1 == 2){
	    u_n1 = u_mid1/2;
	}
	else if (sector_24_sys1 == 3){
	    u_n1 = u_mid1/2;
	}
	else if (sector_24_sys1 == 4 || sector_24_sys1 == 5){
	    u_n1 = u_min1 * (SQRT_3_HALF-1.0f);
	}
	else if (sector_24_sys1 == 6 || sector_24_sys1 == 7){
	    u_n1 = u_mid1/2;
	}
	else if (sector_24_sys1 >= 8){
	    u_n1 = u_max1 * (SQRT_3_HALF-1.0f);
	}




	// adding zero sequence
	output.system1.DutyCycle_A = (u_abc1abc2_ref.a1 + u_n1) / V_DC_Volts + 0.5f;
	output.system1.DutyCycle_B = (u_abc1abc2_ref.b1 + u_n1) / V_DC_Volts + 0.5f;
	output.system1.DutyCycle_C = (u_abc1abc2_ref.c1 + u_n1) / V_DC_Volts + 0.5f;
	output.system2.DutyCycle_A = (u_abc1abc2_ref.a2 + u_n2) / V_DC_Volts + 0.5f;
	output.system2.DutyCycle_B = (u_abc1abc2_ref.b2 + u_n2) / V_DC_Volts + 0.5f;
	output.system2.DutyCycle_C = (u_abc1abc2_ref.c2 + u_n2) / V_DC_Volts + 0.5f;

	// saturation
	output.system1.DutyCycle_A = uz_signals_saturation(output.system1.DutyCycle_A, 1.0f, 0.0f);
	output.system1.DutyCycle_B = uz_signals_saturation(output.system1.DutyCycle_B, 1.0f, 0.0f);
	output.system1.DutyCycle_C = uz_signals_saturation(output.system1.DutyCycle_C, 1.0f, 0.0f);
	output.system2.DutyCycle_A = uz_signals_saturation(output.system2.DutyCycle_A, 1.0f, 0.0f);
	output.system2.DutyCycle_B = uz_signals_saturation(output.system2.DutyCycle_B, 1.0f, 0.0f);
	output.system2.DutyCycle_C = uz_signals_saturation(output.system2.DutyCycle_C, 1.0f, 0.0f);


	return output;
}
