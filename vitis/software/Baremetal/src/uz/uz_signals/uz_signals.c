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


#include "uz_signals.h"
#include "../uz_global_configuration.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"

typedef struct uz_Filter_1st_t {
	bool is_ready;
	struct uz_Filter_1st_config config;
	float dt;
	float alpha;
	float RC;
	float old_output;
	float old_input;
	bool first_step;
} uz_Filter_1st_t;

static size_t uz_Filter_1st_instance_counter = 0U;

static uz_Filter_1st_t instances[UZ_FILTER_1ST_ORDER_INSTANCES] = { 0 };


static uz_Filter_1st_t* uz_Filter_1st_allocation(void);

static uz_Filter_1st_t* uz_Filter_1st_allocation(void) {
 	uz_assert(uz_Filter_1st_instance_counter < UZ_FILTER_1ST_ORDER_INSTANCES);
	uz_Filter_1st_t* self = &instances[uz_Filter_1st_instance_counter];
 	uz_assert_false(self->is_ready);
	uz_Filter_1st_instance_counter++;
 	self->is_ready = true;
 	return (self);
}

uz_Filter_1st_t* uz_Filter_1st_init(struct uz_Filter_1st_config config) {
	uz_Filter_1st_t* self = uz_Filter_1st_allocation();
	uz_assert(config.sample_frequency_Hz > 0.0f);
	uz_assert(config.cutoff_frequency_Hz > 0.0f);
	uz_assert(config.sample_frequency_Hz > (2.0f * config.cutoff_frequency_Hz));
	self->RC = 1.0f / (config.cutoff_frequency_Hz * 2.0f * UZ_PIf );
	self->dt = 1.0f / config.sample_frequency_Hz;
	if (config.selection == LowPass) {
		self->alpha = self->dt / (self->RC + self->dt);
	} else if (config.selection == HighPass) {
		self->alpha = self->RC / (self->RC + self->dt);
	}
	self->config = config;
  	return (self);

}

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

float uz_signals_Filter_1st_sample(uz_Filter_1st_t* self, float input) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	float output = 0.0f;
	if (!self->first_step) {
		self->old_output = input;
		self->first_step = true;
	}
	if(self->config.selection == LowPass) {
		output = self->old_output + self->alpha * (input - self->old_output);
	} else {
		output = self->alpha * (self->old_output + input - self->old_input);
	}
	self->old_output = output;
	self->old_input = input;
	return (output);
}

float uz_signals_Filter_1st_reverse_sample(uz_Filter_1st_t* self, float input) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	float output = 0.0f;
	if (!self->first_step) {
		self->old_output = input;
		self->old_input = input;
		self->first_step = true;
	}
	if(self->config.selection == LowPass) {
		output = (input - (1.0f - self->alpha) * self->old_input) / self->alpha;
	} else {
		output = input / self->alpha - self->old_output + self->old_input;
	}
	self->old_output = output;
	self->old_input = input;
	return (output);
}
