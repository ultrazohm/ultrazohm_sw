/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Dennnis Hufnagel, Tobias Schindler
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
******************************************************************************
* Priyadharshini Ponraj- 03.12.2021
* modified on : 18-03-2022
******************************************************************************/
#include "uz_piController.h"
#include "uz_signals.h"

bool uz_PI_Controller_Clamping_Circuit(float preIntegrator, float preSat, float upper_limit, float lower_limit) {
	bool output = false;
	float value_after_deadzone = uz_signals_dead_zone(preSat, upper_limit, lower_limit);
	float sign_after_deadzone = uz_signals_get_sign_of_value(value_after_deadzone);
	float sign_preIntegrator = uz_signals_get_sign_of_value(preIntegrator);
	if ( (0.0f != value_after_deadzone) && (sign_after_deadzone == sign_preIntegrator) ) {
		output = true;
	} else {
		output = false;
	}
	return (output);
}
void uz_PI_Controller_sample(uz_PI_Controller_config* self,  bool I_rst, float referenceValue, float actualValue, bool ext_clamping, float *output) {
	#pragma HLS INTERFACE m_axi port=output offset=slave           bundle=Dout depth=50
	#pragma HLS INTERFACE s_axilite port=self                      bundle = Din
	#pragma HLS INTERFACE s_axilite port=referenceValue            bundle = Din
	#pragma HLS INTERFACE s_axilite port=actualValue               bundle = Din
	#pragma HLS INTERFACE s_axilite port=ext_clamping              bundle = Din
	#pragma HLS INTERFACE s_axilite port=I_rst                     bundle = Din
	#pragma HLS INTERFACE s_axilite port=return                    bundle = Din

	bool internal_clamping = false;
	static float I_sum;
	float error = referenceValue - actualValue;
	float old_I_sum = I_sum;
	float preIntegrator = error * self->Ki;
	float P_sum = error * self->Kp;
	float output_before_saturation = old_I_sum + P_sum;
	internal_clamping = uz_PI_Controller_Clamping_Circuit(preIntegrator, output_before_saturation, self->upper_limit, self->lower_limit);
	bool clamping_active  = (ext_clamping == true) || (internal_clamping == true); // clamping is active if internal clamping or external clamping is true
	if ( clamping_active ) {
		I_sum += 0.0f;
	} else {
		I_sum += preIntegrator * self->samplingTime_sec;
	}

	*output = uz_signals_saturation(output_before_saturation, self->upper_limit, self->lower_limit);

	if(I_rst){
		I_sum = 0.0f;
	    internal_clamping = false;
	}
}



