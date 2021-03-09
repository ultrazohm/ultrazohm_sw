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
* modified on : 06-03-2022
******************************************************************************/
#include "uz_piController.h"
#include "default_uz_global_configuration.h"

//********* should I declare the max instance macro here or get it through axi stream and remove global configurations.***********/
#if UZ_PI_CONTROLLER_MAX_INSTANCES > 0U  // executes the code only if the condition is true   0u- 0 unsigned


//#include "uz_HAL.h"
#include "uz_signals.h"
#include <math.h>
#include <stdlib.h>

struct uz_PI_Controller {
	bool is_ready;
	bool internal_clamping;
	float I_sum;
	struct uz_PI_Controller_config config;
};

static size_t instances_counter_PI_Controller = 0;
static uz_PI_Controller instances_PI_Controller[UZ_PI_CONTROLLER_MAX_INSTANCES] = { 0 }; // array with all zero elements
static uz_PI_Controller* uz_PI_Controller_allocation(void);  // Function declaration - return type,function name, parameters

static uz_PI_Controller* uz_PI_Controller_allocation(void) {  // Function Definition    // Memory allocation
	//uz_assert(instances_counter_PI_Controller < UZ_PI_CONTROLLER_MAX_INSTANCES);
	//do{
		//if(instances_counter_PI_Controller < UZ_PI_CONTROLLER_MAX_INSTANCES)
		//	{
			uz_PI_Controller* self = &instances_PI_Controller[instances_counter_PI_Controller];
			//uz_assert(self->is_ready == false);
			instances_counter_PI_Controller++;
			self->is_ready = true;
		//	}
	  // }while(0)
	return (self);
}

uz_PI_Controller* uz_PI_Controller_init(struct uz_PI_Controller_config config) {
	uz_PI_Controller* self = uz_PI_Controller_allocation();
	/*
    uz_assert(config.Ki >= 0.0f);
    uz_assert(config.Kp >= 0.0f);
    uz_assert(config.samplingTime_sec > 0.0f);
    uz_assert(config.upper_limit > config.lower_limit);
	uz_assert(config.lower_limit < config.upper_limit);
	*/
	self->config = config;
	return (self);
}

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

float uz_PI_Controller_sample(uz_PI_Controller* self, float referenceValue, float actualValue, bool ext_clamping) {
	/*#pragma HLS INTERFACE ap_none port = referenceValue
    #pragma HLS INTERFACE ap_none port = actualValue
	#pragma HLS INTERFACE ap_none port = ext_clamping*/


	#pragma HLS INTERFACE s_axilite port=referenceValue    bundle = param
	#pragma HLS INTERFACE s_axilite port=actualValue       bundle = param
	#pragma HLS INTERFACE s_axilite port=ext_clamping      bundle = param
	#pragma HLS INTERFACE s_axilite port=self              bundle = param

	//uz_assert_not_NULL(self);
	//uz_assert(self->is_ready);
	float error = referenceValue - actualValue;
	float old_I_sum = self->I_sum;
	float preIntegrator = error * self->config.Ki;
	float P_sum = error * self->config.Kp;
	float output_before_saturation = old_I_sum + P_sum;
	#pragma HLS INTERFACE ap_none port = output_before_saturation
	self->internal_clamping = uz_PI_Controller_Clamping_Circuit(preIntegrator, output_before_saturation, self->config.upper_limit, self->config.lower_limit);
	bool clamping_active  = (ext_clamping == true) || (self->internal_clamping == true); // clamping is active if internal clamping or external clamping is true
	if ( clamping_active ) {
		self->I_sum += 0.0f;
	} else {
		self->I_sum += preIntegrator * self->config.samplingTime_sec;
	}
	float output = uz_signals_saturation(output_before_saturation, self->config.upper_limit, self->config.lower_limit);
	return (output_before_saturation);
}


void uz_PI_Controller_reset(uz_PI_Controller* self){
	/*
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	*/
    self->I_sum = 0.0f;
	self->internal_clamping = false;
}

void uz_PI_Controller_set_Ki(uz_PI_Controller* self, float new_Ki){
	/*
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    uz_assert(new_Ki >= 0.0f);
    */
    self->config.Ki = new_Ki;
}

void uz_PI_Controller_set_Kp(uz_PI_Controller* self, float new_Kp){
	/*
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    uz_assert(new_Kp >= 0.0f);
    */
    self->config.Kp = new_Kp;
}

void uz_PI_Controller_update_limits(uz_PI_Controller* self, float upper_limit, float lower_limit){
	/*
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(upper_limit > lower_limit);
	uz_assert(lower_limit < upper_limit);
	*/
	self->config.upper_limit = upper_limit;
	self->config.lower_limit = lower_limit;
}
#endif
