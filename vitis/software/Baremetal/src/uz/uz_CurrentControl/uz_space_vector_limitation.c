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

static uz_3ph_dq_t uz_limit_dq_prio_d_axis(uz_3ph_dq_t v_input_Volts, float V_SV_max);
static uz_3ph_dq_t uz_limit_dq_prio_q_axis(uz_3ph_dq_t v_input_Volts, float V_SV_max);
uz_3ph_dq_t uz_CurrentControl_SpaceVector_Limitation(uz_3ph_dq_t v_input_Volts, float V_dc_volts, float max_modulation_index, float omega_el_rad_per_sec, uz_3ph_dq_t i_actual_Ampere, bool* ext_clamping){
	uz_assert_not_NULL(ext_clamping);
	uz_assert(V_dc_volts > 0.0f);
	uz_3ph_dq_t v_output_Volts = {0};
  	float V_SV_max =V_dc_volts * max_modulation_index;
	float V_SV_abs = sqrtf(powf(v_input_Volts.d, 2.0f)  + powf(v_input_Volts.q, 2.0f) );
	bool if_omega_equal_q_current = (uz_signals_get_sign_of_value(omega_el_rad_per_sec) == uz_signals_get_sign_of_value(i_actual_Ampere.q));

	if ( V_SV_abs > V_SV_max ){
		//ext_clamping is a pointer, because it is needed for future time steps and the return of the function is already of type uz_3ph_dq_t
		*ext_clamping = true;
		if (if_omega_equal_q_current == true) {
			v_output_Volts = uz_limit_dq_prio_d_axis(v_input_Volts, V_SV_max);
		} else {
			v_output_Volts = uz_limit_dq_prio_q_axis(v_input_Volts, V_SV_max);
		}
	} else {
		v_output_Volts.d = v_input_Volts.d;
		v_output_Volts.q = v_input_Volts.q;
		*ext_clamping = false;
	}
	return (v_output_Volts);
}

static uz_3ph_dq_t uz_limit_dq_prio_d_axis(uz_3ph_dq_t v_input_Volts, float V_SV_max){
	uz_3ph_dq_t v_output_Volts = {0};
	if ( (fabsf(v_input_Volts.d) ) > (0.95f * V_SV_max) ) {
		v_output_Volts.d = uz_signals_get_sign_of_value(v_input_Volts.d) * 0.95f * V_SV_max;
		v_output_Volts.q = uz_signals_get_sign_of_value(v_input_Volts.q) * sqrtf(powf(V_SV_max, 2.0f) - powf(v_output_Volts.d, 2.0f));
	} else {
		v_output_Volts.d = v_input_Volts.d;
		v_output_Volts.q = uz_signals_get_sign_of_value(v_input_Volts.q) * sqrtf(powf(V_SV_max, 2.0f) - powf(v_output_Volts.d, 2.0f));
	}
	return(v_output_Volts);
}

static uz_3ph_dq_t uz_limit_dq_prio_q_axis(uz_3ph_dq_t v_input_Volts, float V_SV_max){
	uz_3ph_dq_t v_output_Volts = {0};
	if ( (fabsf(v_input_Volts.q) ) > (0.95f * V_SV_max) ) {
		v_output_Volts.q = uz_signals_get_sign_of_value(v_input_Volts.q) * 0.95f * V_SV_max;
		v_output_Volts.d = uz_signals_get_sign_of_value(v_input_Volts.d) * sqrtf(powf(V_SV_max, 2.0f) - powf(v_output_Volts.q, 2.0f));
	} else {
		v_output_Volts.q = v_input_Volts.q;
		v_output_Volts.d = uz_signals_get_sign_of_value(v_input_Volts.d) * sqrtf(powf(V_SV_max, 2.0f) - powf(v_output_Volts.q, 2.0f));
	}
	return(v_output_Volts);
}
