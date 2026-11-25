/*
 * Copyright Contributors to the UltraZohm project.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stddef.h>
#include <string.h>
#include "../../uz_global_configuration.h"
#if UZ_NN_MAX_INSTANCES > 0U
#include "uz_actor_pt1_example.h"
#include "../../uz_HAL.h"
#include <math.h>

void uz_actor_pt1_example_init(uz_actor_pt1_example_t *self, const struct uz_exported_actor_config *config, float gain,
                               float time_constant_s) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(config);
	uz_assert(isfinite(gain));
	uz_assert(isfinite(time_constant_s));
	uz_assert(time_constant_s > 0.0f);
	uz_assert(config->command_count == 1U);
	uz_exported_actor_init(&self->actor, config, config->control_frequency_hz);
	self->gain = gain;
	const float normalized_time_constant = config->control_frequency_hz * time_constant_s;
	uz_assert(isfinite(normalized_time_constant));
	uz_assert(normalized_time_constant > 0.0f);
	self->step_fraction = -expm1f(-1.0f / normalized_time_constant);
	uz_actor_pt1_example_reset(self, 0.0f);
}

void uz_actor_pt1_example_reset(uz_actor_pt1_example_t *self, float initial_output) {
	uz_assert_not_NULL(self);
	uz_assert(isfinite(initial_output));
	self->output = initial_output;
	uz_exported_actor_reset(&self->actor, NULL);
}

float uz_actor_pt1_example_step(uz_actor_pt1_example_t *self, float reference) {
	uz_assert_not_NULL(self);
	uz_assert(isfinite(reference));
	const struct uz_exported_actor_signals signals = {.output = self->output, .reference = {reference, 0.0f}};
	uz_exported_actor_sample(&self->actor, signals);
	self->output += self->step_fraction * ((self->gain * self->actor.applied[0]) - self->output);
	return self->output;
}
#endif
