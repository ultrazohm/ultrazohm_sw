/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Dennis Hufnagel
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

#if UZ_IIR_FILTER_MAX_INSTANCES > 0

typedef struct uz_IIR_Filter_t {
	bool is_ready;
	struct uz_IIR_Filter_config config;
	float dt;
	float alpha;
	float RC;
	float old_output;
	float old_input;
	bool first_step;
} uz_IIR_Filter_t;

static size_t uz_IIR_Filter_instance_counter = 0U;

static uz_IIR_Filter_t IIR_Filter_instances[UZ_IIR_FILTER_MAX_INSTANCES] = { 0 };


static uz_IIR_Filter_t* uz_IIR_Filter_allocation(void);

static uz_IIR_Filter_t* uz_IIR_Filter_allocation(void) {
 	uz_assert(uz_IIR_Filter_instance_counter < UZ_IIR_FILTER_MAX_INSTANCES);
	uz_IIR_Filter_t* self = &IIR_Filter_instances[uz_IIR_Filter_instance_counter];
 	uz_assert_false(self->is_ready);
	uz_IIR_Filter_instance_counter++;
 	self->is_ready = true;
 	return (self);
}

uz_IIR_Filter_t* uz_signals_IIR_Filter_init(struct uz_IIR_Filter_config config) {
	uz_IIR_Filter_t* self = uz_IIR_Filter_allocation();
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

float uz_signals_IIR_Filter_sample(uz_IIR_Filter_t* self, float input) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	float output = 0.0f;

	if(self->first_step) {
		if(self->config.selection == LowPass && self->first_step) {
			output = self->old_output + self->alpha * (input - self->old_output);
		} else if(self->config.selection == HighPass && self->first_step) {
			output = self->alpha * (self->old_output + input - self->old_input);
		}
		self->old_output = output;
		self->old_input = input;
	} else {
		self->old_output = input;
		self->old_input = input;
		self->first_step = true;
		output = input;
	}	
	return (output);
}

float uz_signals_IIR_Filter_reverse_sample(uz_IIR_Filter_t* self, float input) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	float output = 0.0f;
	if(self->first_step) {
		if(self->config.selection == LowPass && self->first_step) {
			output = (input - self->old_input) / self->alpha + self->old_input;
		} else if(self->config.selection == HighPass && self->first_step) {
			output = input / self->alpha + self->old_output - self->old_input;
		}
		self->old_output = output;
		self->old_input = input;
	} else {
		self->old_output = input;
		self->old_input = input;
		self->first_step = true;
		output = input;
	}
	return (output);
}

#endif