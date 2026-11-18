/*
 * Copyright Contributors to the UltraZohm project.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stddef.h>
#include <string.h>
#include "../uz_global_configuration.h"
#if UZ_NN_MAX_INSTANCES > 0U
#include "uz_exported_actor.h"
#include "../uz_HAL.h"
#include <math.h>
#include <stdint.h>

static int32_t uz_exported_actor_get_sign(float value);
static void uz_exported_actor_validate_config(const struct uz_exported_actor_config *config);
static void uz_exported_actor_limit_axes(const struct uz_exported_actor_config *config,
                                         const struct uz_exported_actor_signals *signals,
                                         const float requested[UZ_EXPORTED_ACTOR_MAX_COMMANDS],
                                         float limited[UZ_EXPORTED_ACTOR_MAX_COMMANDS]);
static void uz_exported_actor_select_action(uz_exported_actor_t *self, const uz_matrix_t *output,
                                            float action[UZ_EXPORTED_ACTOR_MAX_COMMANDS]);

static int32_t uz_exported_actor_get_sign(float value) {
	int32_t sign = 0;
	if (value > 0.0f) {
		sign = 1;
	} else if (value < 0.0f) {
		sign = -1;
	} else {
		/* Zero must remain distinct from either direction in the limiter. */
	}
	return sign;
}

static void uz_exported_actor_validate_config(const struct uz_exported_actor_config *config) {
	uz_assert_not_NULL(config);
	uz_assert(config->abi == UZ_EXPORTED_ACTOR_ABI);
	uz_assert_not_NULL(config->layers);
	uz_assert_not_NULL(config->observations);
	uz_assert(config->observe != NULL);
	uz_assert(config->advance != NULL);
	uz_assert(config->map_action != NULL);
	uz_assert((config->layer_count > 1U) && (config->layer_count < UZ_NN_MAX_LAYER));
	uz_assert((config->command_count > 0U) && (config->command_count <= UZ_EXPORTED_ACTOR_MAX_COMMANDS));
	uz_assert(config->delay_steps <= UZ_EXPORTED_ACTOR_MAX_DELAY_STEPS);
	uz_assert(config->input_count > 0U);
	uz_assert(config->output_count > 0U);
	uz_assert(config->input_count == config->layers[0].number_of_inputs);
	uz_assert(config->output_count == config->layers[config->layer_count - 1U].number_of_neurons);
	uz_assert(isfinite(config->control_frequency_hz));
	uz_assert(config->control_frequency_hz > 0.0f);
	uz_assert((config->limiter == UZ_ACTOR_NO_LIMITER) ||
	          (config->limiter == UZ_ACTOR_AXIS_PRIORITY) || (config->limiter == UZ_ACTOR_RADIAL));
	if (config->discrete_actions == NULL) {
		uz_assert(config->output_count == config->command_count);
	} else {
		/* Prove that flattened discrete-action indexing cannot overflow. */
		uz_assert(config->output_count <= (UINT32_MAX / config->command_count));
	}
	if (config->limiter != UZ_ACTOR_NO_LIMITER) {
		uz_assert(config->command_count == UZ_EXPORTED_ACTOR_MAX_COMMANDS);
		uz_assert(isfinite(config->voltage_limit));
		uz_assert(config->voltage_limit >= 0.0f);
	}
}

void uz_exported_actor_init(uz_exported_actor_t *self, const struct uz_exported_actor_config *config,
                            float actual_frequency_hz) {
	uz_assert_not_NULL(self);
	uz_exported_actor_validate_config(config);
	uz_assert(isfinite(actual_frequency_hz));
	uz_assert(actual_frequency_hz > 0.0f);
	uz_assert(fabsf(actual_frequency_hz - config->control_frequency_hz) <= (config->control_frequency_hz * 1.0e-6f));
	self->config = config;
	self->network = uz_nn_init(config->layers, config->layer_count);
	const uz_matrix_t *input_matrix = uz_matrix_init(&self->input_matrix, config->observations,
	                                                 config->input_count, 1U, config->input_count);
	uz_assert(input_matrix == &self->input_matrix);
	uz_exported_actor_reset(self, NULL);
}

void uz_exported_actor_reset(uz_exported_actor_t *self, const struct uz_exported_actor_state *initial) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(self->config);
	if (initial != NULL) {
		self->state = *initial;
	} else {
		const struct uz_exported_actor_state reset_state = {
		        .integral = {self->config->initial_integral[0], self->config->initial_integral[1]},
		        .applied_voltage = {0.0f, 0.0f},
		        .queue = {{0.0f, 0.0f}, {0.0f, 0.0f}}};
		self->state = reset_state;
	}
	for (uint32_t i = 0U; i < UZ_EXPORTED_ACTOR_MAX_COMMANDS; ++i) {
		self->requested[i] = 0.0f;
		self->limited[i] = 0.0f;
		self->applied[i] = self->state.applied_voltage[i];
	}
	self->saturated = false;
	self->action_index = 0U;
}

static void uz_exported_actor_limit_axes(const struct uz_exported_actor_config *config,
                                         const struct uz_exported_actor_signals *signals,
                                         const float requested[UZ_EXPORTED_ACTOR_MAX_COMMANDS],
                                         float limited[UZ_EXPORTED_ACTOR_MAX_COMMANDS]) {
	const float maximum = config->voltage_limit;
	const float iq = config->limiter_reference_current ? signals->reference[1] : signals->current[1];
	const int32_t speed_sign = uz_exported_actor_get_sign(signals->speed_rpm);
	const int32_t current_sign = uz_exported_actor_get_sign(iq);
	const uint32_t priority = (speed_sign == current_sign) ? 0U : 1U;
	const uint32_t other = 1U - priority;
	const int32_t other_sign = uz_exported_actor_get_sign(requested[other]);
	const float other_direction = (float)other_sign;
	limited[priority] = fminf(fmaxf(requested[priority], -0.95f * maximum), 0.95f * maximum);
	limited[other] = other_direction * sqrtf(fmaxf((maximum * maximum) - (limited[priority] * limited[priority]), 0.0f));
}

void uz_exported_actor_limit(const struct uz_exported_actor_config *config,
                             const struct uz_exported_actor_signals *signals,
                             const float requested[UZ_EXPORTED_ACTOR_MAX_COMMANDS],
                             float limited[UZ_EXPORTED_ACTOR_MAX_COMMANDS], bool *saturated) {
	uz_assert_not_NULL(config);
	uz_assert_not_NULL(signals);
	uz_assert_not_NULL(requested);
	uz_assert_not_NULL(limited);
	uz_assert_not_NULL(saturated);
	limited[0] = requested[0];
	limited[1] = requested[1];
	*saturated = false;
	if (config->limiter != UZ_ACTOR_NO_LIMITER) {
		uz_assert((config->limiter == UZ_ACTOR_RADIAL) || (config->limiter == UZ_ACTOR_AXIS_PRIORITY));
		uz_assert(isfinite(config->voltage_limit));
		uz_assert(config->voltage_limit >= 0.0f);
		const float magnitude = sqrtf((requested[0] * requested[0]) + (requested[1] * requested[1]));
		const float maximum = config->voltage_limit;
		*saturated = magnitude > maximum;
		if (*saturated) {
			if (config->limiter == UZ_ACTOR_RADIAL) {
				limited[0] *= maximum / magnitude;
				limited[1] *= maximum / magnitude;
			} else {
				uz_exported_actor_limit_axes(config, signals, requested, limited);
			}
		}
	}
}

static void uz_exported_actor_select_action(uz_exported_actor_t *self, const uz_matrix_t *output,
                                            float action[UZ_EXPORTED_ACTOR_MAX_COMMANDS]) {
	const struct uz_exported_actor_config *config = self->config;
	if (config->discrete_actions != NULL) {
		uint32_t best = 0U;
		for (uint32_t i = 1U; i < config->output_count; ++i) {
			const float candidate = uz_matrix_get_element_zero_based(output, 0U, i);
			const float previous = uz_matrix_get_element_zero_based(output, 0U, best);
			if (candidate > previous) {
				best = i;
			}
		}
		self->action_index = best; /* Strict > preserves first-index tie breaking. */
		for (uint32_t i = 0U; i < config->command_count; ++i) {
			action[i] = config->discrete_actions[(best * config->command_count) + i];
		}
	} else {
		for (uint32_t i = 0U; i < config->command_count; ++i) {
			action[i] = uz_matrix_get_element_zero_based(output, 0U, i);
		}
	}
}

void uz_exported_actor_sample(uz_exported_actor_t *self, struct uz_exported_actor_signals signals) {
	uz_assert_not_NULL(self);
	const struct uz_exported_actor_config *config = self->config;
	uz_assert_not_NULL(config);
	for (uint32_t i = 0U; i < UZ_EXPORTED_ACTOR_MAX_COMMANDS; ++i) {
		signals.applied_voltage[i] = self->state.applied_voltage[i];
	}
	config->observe(&signals, &self->state, config->observations);
	for (uint32_t i = 0U; i < config->input_count; ++i) {
		uz_assert(isfinite(config->observations[i]));
	}
	uz_nn_ff(self->network, &self->input_matrix);
	const uz_matrix_t *output = uz_nn_get_output_data(self->network);
	for (uint32_t i = 0U; i < config->output_count; ++i) {
		const float value = uz_matrix_get_element_zero_based(output, 0U, i);
		uz_assert(isfinite(value));
	}
	float action[UZ_EXPORTED_ACTOR_MAX_COMMANDS] = {0.0f, 0.0f};
	uz_exported_actor_select_action(self, output, action);
	config->map_action(action, self->requested);
	for (uint32_t i = 0U; i < config->command_count; ++i) {
		uz_assert(isfinite(self->requested[i]));
	}
	uz_exported_actor_limit(config, &signals, self->requested, self->limited, &self->saturated);
	config->advance(&signals, &self->state, self->saturated);
	for (uint32_t i = 0U; i < config->command_count; ++i) {
		if (config->delay_steps == 0U) {
			self->applied[i] = self->limited[i];
		} else {
			self->applied[i] = self->state.queue[config->delay_steps - 1U][i];
		}
		self->state.queue[1][i] = self->state.queue[0][i];
		self->state.queue[0][i] = self->limited[i];
		self->state.applied_voltage[i] = self->applied[i];
	}
}
#endif
