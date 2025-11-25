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

#define ONE_DIVIDED_BY_SQRT_TWO  (1.0f / sqrtf(2.0f))

static uz_3ph_dq_t uz_limit_dq_prio_d_axis(uz_3ph_dq_t v_input_Volts, float V_SV_max, float V_SV_max_squared);
static uz_3ph_dq_t uz_limit_dq_prio_q_axis(uz_3ph_dq_t v_input_Volts, float V_SV_max, float V_SV_max_squared);
uz_3ph_dq_t uz_CurrentControl_SpaceVector_Limitation(uz_3ph_dq_t v_input_Volts, float V_dc_volts, float max_modulation_index, float omega_el_rad_per_sec, uz_3ph_dq_t i_ref_Ampere, bool* ext_clamping){
	uz_assert_not_NULL(ext_clamping);
	uz_assert(V_dc_volts > 0.0f);
	uz_assert(max_modulation_index > 0.0f);
	uz_3ph_dq_t v_output_Volts = {0};
  	float V_SV_max = V_dc_volts * max_modulation_index;
	float V_SV_max_squared = V_SV_max * V_SV_max;
	float V_SV_abs = sqrtf(v_input_Volts.d * v_input_Volts.d + v_input_Volts.q * v_input_Volts.q);
	bool if_omega_equal_q_current = (uz_signals_get_sign_of_value(omega_el_rad_per_sec) == uz_signals_get_sign_of_value(i_ref_Ampere.q));

	if ( V_SV_abs > V_SV_max ){
		//ext_clamping is a pointer, because it is needed for future time steps and the return of the function is already of type uz_3ph_dq_t
		*ext_clamping = true;
		if (if_omega_equal_q_current == true) {
			v_output_Volts = uz_limit_dq_prio_d_axis(v_input_Volts, V_SV_max, V_SV_max_squared);
		} else {
			v_output_Volts = uz_limit_dq_prio_q_axis(v_input_Volts, V_SV_max, V_SV_max_squared);
		}
	} else {
		v_output_Volts.d = v_input_Volts.d;
		v_output_Volts.q = v_input_Volts.q;
		*ext_clamping = false;
	}
	return (v_output_Volts);
}

static uz_3ph_dq_t uz_limit_dq_prio_d_axis(uz_3ph_dq_t v_input_Volts, float V_SV_max, float V_SV_max_squared){
	uz_3ph_dq_t v_output_Volts = {0};
	if ( (fabsf(v_input_Volts.d) ) > (0.95f * V_SV_max) ) {
		v_output_Volts.d = uz_signals_get_sign_of_value(v_input_Volts.d) * 0.95f * V_SV_max;
		v_output_Volts.q = uz_signals_get_sign_of_value(v_input_Volts.q) * sqrtf(V_SV_max_squared- (v_output_Volts.d * v_output_Volts.d));
	} else {
		v_output_Volts.d = v_input_Volts.d;
		v_output_Volts.q = uz_signals_get_sign_of_value(v_input_Volts.q) * sqrtf(V_SV_max_squared - (v_output_Volts.d * v_output_Volts.d));
	}
	return(v_output_Volts);
}

static uz_3ph_dq_t uz_limit_dq_prio_q_axis(uz_3ph_dq_t v_input_Volts, float V_SV_max, float V_SV_max_squared){
	uz_3ph_dq_t v_output_Volts = {0};
	if ( (fabsf(v_input_Volts.q) ) > (0.95f * V_SV_max) ) {
		v_output_Volts.q = uz_signals_get_sign_of_value(v_input_Volts.q) * 0.95f * V_SV_max;
		v_output_Volts.d = uz_signals_get_sign_of_value(v_input_Volts.d) * sqrtf(V_SV_max_squared - (v_output_Volts.q * v_output_Volts.q));
	} else {
		v_output_Volts.q = v_input_Volts.q;
		v_output_Volts.d = uz_signals_get_sign_of_value(v_input_Volts.d) * sqrtf(V_SV_max_squared- (v_output_Volts.q * v_output_Volts.q));
	}
	return(v_output_Volts);
}


uz_6ph_dq_t uz_6ph_Space_Vector_Limitation(uz_6ph_dq_t v_input_Volts, float V_dc_volts, float max_modulation_index, float omega_el_rad_per_sec, uz_6ph_dq_t i_ref_Ampere, bool* ext_clamping) {
	uz_assert_not_NULL(ext_clamping);
	uz_assert(V_dc_volts > 0.0f);
	uz_assert(max_modulation_index > 0.0f);
	uz_6ph_dq_t v_output_Volts = {0};
	float V_SV_max = V_dc_volts * max_modulation_index;
	float V_SV_max_squared = V_SV_max * V_SV_max;
	//because of geometric sum, if both subspaces are in the limit, max voltage per limitation equals V_SV_max / sqrt(2)
	float V_SV_max_xy = V_SV_max * ONE_DIVIDED_BY_SQRT_TWO;
	float V_SV_max_xy_squared = V_SV_max_xy * V_SV_max_xy;
	float V_SV_abs_xy = sqrtf(v_input_Volts.x * v_input_Volts.x + v_input_Volts.y * v_input_Volts.y);
	bool ext_clamping_dq = false;
	bool ext_clamping_xy = false;

	//Limit xy first, with priority to the y-axis
	if (V_SV_abs_xy > V_SV_max_xy){
		if ( (fabsf(v_input_Volts.y) ) > (0.95f * V_SV_max_xy) ) {
			v_output_Volts.y = uz_signals_get_sign_of_value(v_input_Volts.y) * 0.95f * V_SV_max_xy;
			v_output_Volts.x = uz_signals_get_sign_of_value(v_input_Volts.x) * sqrtf((V_SV_max_xy_squared) - (v_output_Volts.y * v_output_Volts.y));			
		} else {
			v_output_Volts.y = v_input_Volts.y;
			v_output_Volts.x = uz_signals_get_sign_of_value(v_input_Volts.x) * sqrtf((V_SV_max_xy_squared) - (v_output_Volts.y * v_output_Volts.y));
		}
		ext_clamping_xy = true;
	} else {
		v_output_Volts.x = v_input_Volts.x;
		v_output_Volts.y = v_input_Volts.y;	
	}
	
	//Limits dq-voltages to V_SV_max subtracted via the geometric sum by the xy-ref-voltages
	float V_SV_abs_ref_xy = sqrtf(v_output_Volts.x * v_output_Volts.x + v_output_Volts.y * v_output_Volts.y);
	float V_SV_abs_ref_xy_squared = V_SV_abs_ref_xy * V_SV_abs_ref_xy;
	float max_modulation_index_dq = max_modulation_index * (sqrtf(1.0f - (V_SV_abs_ref_xy_squared / V_SV_max_squared)));

	uz_3ph_dq_t v_input_dq_Volts = {.d = v_input_Volts.d,
									.q = v_input_Volts.q};
	uz_3ph_dq_t i_ref_dq_Ampere  = {.d = i_ref_Ampere.d,
									  .q = i_ref_Ampere.q};
	uz_3ph_dq_t v_output_dq_Volts = uz_CurrentControl_SpaceVector_Limitation(v_input_dq_Volts, V_dc_volts, max_modulation_index_dq, omega_el_rad_per_sec, i_ref_dq_Ampere, &ext_clamping_dq);

	v_output_Volts.d = v_output_dq_Volts.d;
	v_output_Volts.q = v_output_dq_Volts.q;
	if (ext_clamping_dq || ext_clamping_xy) {
		*ext_clamping = true;
	} else {
		*ext_clamping = false;
	}
	return(v_output_Volts);	
}
