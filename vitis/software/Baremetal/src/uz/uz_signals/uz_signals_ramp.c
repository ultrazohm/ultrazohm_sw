/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2026
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
#include <math.h>
#include <stdbool.h>

#if UZ_RAMP_MAX_INSTANCES > 0U

struct uz_ramp_t {
	bool is_ready;
	struct uz_ramp_config config;
	float current_output;
};

static size_t uz_ramp_instance_counter = 0U;
static uz_ramp_t uz_ramp_instances[UZ_RAMP_MAX_INSTANCES] = {0};

static uz_ramp_t *uz_ramp_allocation(void);

static uz_ramp_t *uz_ramp_allocation(void)
{
	uz_assert(uz_ramp_instance_counter < UZ_RAMP_MAX_INSTANCES);
	uz_ramp_t *self = &uz_ramp_instances[uz_ramp_instance_counter];
	uz_assert_false(self->is_ready);
	uz_ramp_instance_counter++;
	self->is_ready = true;
	return (self);
}

uz_ramp_t *uz_ramp_init(struct uz_ramp_config config)
{
	uz_assert(config.maximum_slope_per_second >= 0.0f);
	uz_assert(config.sample_time_seconds > 0.0f);

	uz_ramp_t *self = uz_ramp_allocation();
	self->config = config;
	self->current_output = config.initial_value;
	return (self);
}

float uz_ramp(uz_ramp_t *self, float reference_value)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);

	const float maximum_step = self->config.maximum_slope_per_second * self->config.sample_time_seconds;
	const float delta = reference_value - self->current_output;

	if (fabsf(delta) <= maximum_step) {
		self->current_output = reference_value;
	} else if (delta > 0.0f) {
		self->current_output += maximum_step;
	} else {
		self->current_output -= maximum_step;
	}

	return (self->current_output);
}

void uz_ramp_set_to_value_instant(uz_ramp_t *self, float value)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->current_output = value;
}

void uz_ramp_reset(uz_ramp_t *self)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->current_output = 0.0f;
}
#endif
