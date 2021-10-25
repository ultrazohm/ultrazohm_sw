/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Dennis Hufnagel
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

#include "uz_space_vector_limitation.h"

static struct uz_dq_t uz_limit_dq_prio_d_axis(struct uz_dq_t u_input_Volts, float U_SV_max);
static struct uz_dq_t uz_limit_dq_prio_q_axis(struct uz_dq_t u_input_Volts, float U_SV_max);
struct uz_dq_t uz_FOC_SpaceVector_Limitation(struct uz_dq_t u_input_Volts, float V_dc_volts, float omega_el_rad_per_sec, struct uz_dq_t i_actual_Ampere, bool* ext_clamping){
	uz_assert_not_NULL(ext_clamping);
	uz_assert(V_dc_volts > 0.0f);
	struct uz_dq_t u_output_Volts = {0};
  	float U_SV_max =V_dc_volts / sqrtf(3.0f);
	float U_SV_abs = sqrtf(powf(u_input_Volts.d, 2.0f)  + powf(u_input_Volts.q, 2.0f) );
	bool if_omega_equal_q_current = (uz_signals_get_sign_of_value(omega_el_rad_per_sec) == uz_signals_get_sign_of_value(i_actual_Ampere.q));

	if ( U_SV_abs > U_SV_max ){
		//ext_clamping is a pointer, because it is needed for future time steps and the return of the function is already of type uz_dq_t
		*ext_clamping = true;
		if (if_omega_equal_q_current == true) {
			u_output_Volts = uz_limit_dq_prio_d_axis(u_input_Volts, U_SV_max);
		} else {
			u_output_Volts = uz_limit_dq_prio_q_axis(u_input_Volts, U_SV_max);
		}
	} else {
		u_output_Volts.d = u_input_Volts.d;
		u_output_Volts.q = u_input_Volts.q;
		*ext_clamping = false;
	}
	return (u_output_Volts);
}

static struct uz_dq_t uz_limit_dq_prio_d_axis(struct uz_dq_t u_input_Volts, float U_SV_max){
	struct uz_dq_t u_output_Volts = {0};
	if ( (fabsf(u_input_Volts.d) ) > (0.95f * U_SV_max) ) {
		u_output_Volts.d = uz_signals_get_sign_of_value(u_input_Volts.d) * 0.95f * U_SV_max;
		u_output_Volts.q = uz_signals_get_sign_of_value(u_input_Volts.q) * sqrtf(powf(U_SV_max, 2.0f) - powf(u_output_Volts.d, 2.0f));
	} else {
		u_output_Volts.d = u_input_Volts.d;
		u_output_Volts.q = uz_signals_get_sign_of_value(u_input_Volts.q) * sqrtf(powf(U_SV_max, 2.0f) - powf(u_output_Volts.d, 2.0f));
	}
	return(u_output_Volts);
}

static struct uz_dq_t uz_limit_dq_prio_q_axis(struct uz_dq_t u_input_Volts, float U_SV_max){
	struct uz_dq_t u_output_Volts = {0};
	if ( (fabsf(u_input_Volts.q) ) > (0.95f * U_SV_max) ) {
		u_output_Volts.q = uz_signals_get_sign_of_value(u_input_Volts.q) * 0.95f * U_SV_max;
		u_output_Volts.d = uz_signals_get_sign_of_value(u_input_Volts.d) * sqrtf(powf(U_SV_max, 2.0f) - powf(u_output_Volts.q, 2.0f));
	} else {
		u_output_Volts.q = u_input_Volts.q;
		u_output_Volts.d = uz_signals_get_sign_of_value(u_input_Volts.d) * sqrtf(powf(U_SV_max, 2.0f) - powf(u_output_Volts.q, 2.0f));
	}
	return(u_output_Volts);
}
