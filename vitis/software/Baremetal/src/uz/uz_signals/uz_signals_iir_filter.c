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

typedef struct uz_IIR_Filter_t
{
    bool is_ready;
    struct uz_IIR_Filter_config config;
    float dt;
    float alpha;
    float RC;
    float D;
    float omega_0;
    float a1;
    float a2;
    float b0;
    float b1;
    float b2;
    float old_output[2];
    float old_input[2];
    bool first_step;
    bool second_step;
} uz_IIR_Filter_t;

static size_t uz_IIR_Filter_instance_counter = 0U;

static uz_IIR_Filter_t IIR_Filter_instances[UZ_IIR_FILTER_MAX_INSTANCES] = {0};

static uz_IIR_Filter_t *uz_IIR_Filter_allocation(void);

static uz_IIR_Filter_t *uz_IIR_Filter_allocation(void)
{
    uz_assert(uz_IIR_Filter_instance_counter < UZ_IIR_FILTER_MAX_INSTANCES);
    uz_IIR_Filter_t *self = &IIR_Filter_instances[uz_IIR_Filter_instance_counter];
    uz_assert_false(self->is_ready);
    uz_IIR_Filter_instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_IIR_Filter_t *uz_signals_IIR_Filter_init(struct uz_IIR_Filter_config config)
{
    uz_IIR_Filter_t *self = uz_IIR_Filter_allocation();
    uz_assert(config.sample_frequency_Hz > 0.0f);
    uz_assert(config.sample_frequency_Hz > (2.0f * config.cutoff_frequency_Hz));
    uz_assert(config.sample_frequency_Hz > (2.0f * config.pass_frequency_Hz));

    switch (config.selection)
    {
    case LowPass_first_order:
        uz_assert(config.cutoff_frequency_Hz > 0.0f);
        self->RC = 1.0f / (config.cutoff_frequency_Hz * 2.0f * UZ_PIf);
        self->dt = 1.0f / config.sample_frequency_Hz;
        self->alpha = self->dt / (self->RC + self->dt);
        break;
    case HighPass_first_order:
        uz_assert(config.cutoff_frequency_Hz > 0.0f);
        self->RC = 1.0f / (config.cutoff_frequency_Hz * 2.0f * UZ_PIf);
        self->dt = 1.0f / config.sample_frequency_Hz;
        self->alpha = self->RC / (self->RC + self->dt);
        break;
    case BandPass_second_order:
    	uz_assert(config.pass_frequency_Hz > 0.0f);
    	self->dt = 1.0f / config.sample_frequency_Hz;
    	self->omega_0 = config.pass_frequency_Hz * 2.0f * UZ_PIf;
    	self->D = config.damping;
    	self->alpha = self->omega_0 * self->omega_0 * self->dt * self->dt + 4.0f * self->D * self->omega_0 * self->dt + 4.0f;
    	self->a1 = -(2.0f * self->omega_0 * self->omega_0 * self->dt * self->dt - 8.0f) / self->alpha;
    	self->a2 = -(self->omega_0 * self->omega_0 * self->dt * self->dt - 4.0f * self->D * self->omega_0 * self->dt + 4.0f) / self->alpha;
    	self->b0 = (4.0f * self->D * self->omega_0 * self->dt) / self->alpha;
    	self->b1 = 0.0f;
    	self->b2 = -(4.0f * self->D * self->omega_0 * self->dt) / self->alpha;
    	break;
    default:
        break;
    }
    self->config = config;
    self->first_step = true; // Call after the init is the first call
    self->second_step = true;
    return (self);
}

float uz_signals_IIR_Filter_sample(uz_IIR_Filter_t *self, float input)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    float output = 0.0f;
    // There are no old steps if it's the first/second step, thus filter is not calculated but only "old" values are set
    if (self->first_step)
    {
        self->old_output[0] = input;
        self->old_input[0] = input;
        self->first_step = false;
        output = input;
    }
    else
    {
        switch (self->config.selection)
        {
        case LowPass_first_order:
            output = self->old_output[0] + self->alpha * (input - self->old_output[0]);
            self->old_output[0] = output;
            self->old_input[0] = input;
            break;
        case HighPass_first_order:
            output = self->alpha * (self->old_output[0] + input - self->old_input[0]);
            self->old_output[0] = output;
            self->old_input[0] = input;
            break;
        case BandPass_second_order:
        	if (self->second_step)
        	{
        		self->old_output[1] = self->old_output[0];
        		self->old_input[1] = self->old_input[0];
        		self->old_output[0] = input;
        		self->old_input[0] = input;
        		self->second_step = false;
        		output = input;
        	}
        	else
        	{
        		output = self->b0 * input + self->b2 * self->old_input[1] + self->a1 * self->old_output[0] + self->a2 * self->old_output[1];
        		self->old_output[1] = self->old_output[0];
        		self->old_input[1] = self->old_input[0];
        		self->old_output[0] = output;
        		self->old_input[0] = input;
        	}
        	break;
        default:
            break;
        }
    }
    return (output);
}

float uz_signals_IIR_Filter_reverse_sample(uz_IIR_Filter_t *self, float input)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    float output = 0.0f;
    if (self->first_step)
    {
        self->old_output[0] = input;
        self->old_input[0] = input;
        self->first_step = false;
        output = input;
    }
    else
    {
        switch (self->config.selection)
        {
        case LowPass_first_order:
            output = (input - self->old_input[0]) / self->alpha + self->old_input[0];
            break;
        case HighPass_first_order:
            output = input / self->alpha + self->old_output[0] - self->old_input[0];
            break;
        default:
            break;
        }
        self->old_output[0] = output;
        self->old_input[0] = input;
    }
    return (output);
}

void uz_signals_IIR_Filter_set_lowpass(uz_IIR_Filter_t* self, float cutoff_frequency_Hz){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    uz_assert(cutoff_frequency_Hz > 0.0f);
    uz_assert(self->config.sample_frequency_Hz > (2.0f * cutoff_frequency_Hz));
    self->RC = 1.0f / (cutoff_frequency_Hz * 2.0f * UZ_PIf);
    self->dt = 1.0f / self->config.sample_frequency_Hz;
    self->alpha = self->dt / (self->RC + self->dt);
}

void uz_signals_IIR_Filter_set_bandpass(uz_IIR_Filter_t* self, float pass_frequency_Hz, float damping){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    uz_assert(pass_frequency_Hz > 0.0f);
    uz_assert(self->config.sample_frequency_Hz > (2.0f * pass_frequency_Hz));
    uz_assert(damping > 0.0f);
    self->config.pass_frequency_Hz = pass_frequency_Hz;
    self->D = damping;
    self->dt = 1.0f / self->config.sample_frequency_Hz;
    self->omega_0 = self->config.pass_frequency_Hz * 2.0f * UZ_PIf;
    self->alpha = self->omega_0 * self->omega_0 * self->dt * self->dt + 4.0f * self->D * self->omega_0 * self->dt + 4.0f;
    self->a1 = -(2.0f * self->omega_0 * self->omega_0 * self->dt * self->dt - 8.0f) / self->alpha;
    self->a2 = -(self->omega_0 * self->omega_0 * self->dt * self->dt - 4.0f * self->D * self->omega_0 * self->dt + 4.0f) / self->alpha;
    self->b0 = (4.0f * self->D * self->omega_0 * self->dt) / self->alpha;
    self->b1 = 0.0f;
    self->b2 = -(4.0f * self->D * self->omega_0 * self->dt) / self->alpha;
}

#endif