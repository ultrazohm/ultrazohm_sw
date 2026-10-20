#include "../uz_global_configuration.h"
#if UZ_NN_MAX_INSTANCES > 0U
#include "uz_exported_actor.h"
#include "../uz_HAL.h"
#include <math.h>
#include <stddef.h>

static float sign_zero(float x) { return (x > 0.0f) ? 1.0f : ((x < 0.0f) ? -1.0f : 0.0f); }

void uz_exported_actor_init(uz_exported_actor_t *self, const struct uz_exported_actor_config *config, float actual_frequency_hz) {
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(config);
    uz_assert(config->abi == UZ_EXPORTED_ACTOR_ABI);
    uz_assert(config->command_count > 0U && config->command_count <= 2U);
    uz_assert(config->delay_steps <= 2U);
    uz_assert(isfinite(actual_frequency_hz));
    uz_assert(fabsf(actual_frequency_hz - config->control_frequency_hz) <= config->control_frequency_hz * 1.0e-6f);
    self->config = config;
    self->network = uz_nn_init(config->layers, config->layer_count);
    uz_matrix_init(&self->input_matrix, config->observations, config->input_count, 1U, config->input_count);
    uz_exported_actor_reset(self, NULL);
}

void uz_exported_actor_reset(uz_exported_actor_t *self, const struct uz_exported_actor_state *initial) {
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(self->config);
    self->state = initial != NULL ? *initial : (struct uz_exported_actor_state){
        .integral = {self->config->initial_integral[0], self->config->initial_integral[1]}};
    for (uint32_t i = 0U; i < 2U; ++i) {
        self->requested[i] = 0.0f;
        self->limited[i] = 0.0f;
        self->applied[i] = self->state.applied_voltage[i];
    }
    self->saturated = false;
    self->action_index = 0U;
}

void uz_exported_actor_limit(const struct uz_exported_actor_config *config,
    const struct uz_exported_actor_signals *signals, const float requested[2], float limited[2], bool *saturated) {
    limited[0] = requested[0]; limited[1] = requested[1];
    *saturated = false;
    if (config->limiter == UZ_ACTOR_NO_LIMITER) { return; }
    float magnitude = sqrtf(requested[0]*requested[0] + requested[1]*requested[1]);
    float maximum = config->voltage_limit;
    *saturated = magnitude > maximum;
    if (!*saturated) { return; }
    if (config->limiter == UZ_ACTOR_RADIAL) {
        limited[0] *= maximum / magnitude;
        limited[1] *= maximum / magnitude;
        return;
    }
    float iq = config->limiter_reference_current ? signals->reference[1] : signals->current[1];
    uint32_t priority = (sign_zero(signals->speed_rpm) == sign_zero(iq)) ? 0U : 1U;
    uint32_t other = 1U - priority;
    limited[priority] = fminf(fmaxf(requested[priority], -0.95f*maximum), 0.95f*maximum);
    limited[other] = sign_zero(requested[other])*sqrtf(fmaxf(maximum*maximum-limited[priority]*limited[priority], 0.0f));
}

void uz_exported_actor_sample(uz_exported_actor_t *self, struct uz_exported_actor_signals signals) {
    uz_assert_not_NULL(self);
    const struct uz_exported_actor_config *config = self->config;
    uz_assert_not_NULL(config);
    for (uint32_t i = 0U; i < 2U; ++i) { signals.applied_voltage[i] = self->state.applied_voltage[i]; }
    config->observe(&signals, &self->state, config->observations);
    for (uint32_t i = 0U; i < config->input_count; ++i) { uz_assert(isfinite(config->observations[i])); }
    uz_nn_ff(self->network, &self->input_matrix);
    uz_matrix_t *output = uz_nn_get_output_data(self->network);
    for (uint32_t i = 0U; i < config->output_count; ++i) { uz_assert(isfinite(uz_matrix_get_element_zero_based(output, 0U, i))); }
    float action[2] = {0.0f, 0.0f};
    if (config->discrete_actions != NULL) {
        uint32_t best = 0U;
        for (uint32_t i = 1U; i < config->output_count; ++i) {
            if (uz_matrix_get_element_zero_based(output, 0U, i) > uz_matrix_get_element_zero_based(output, 0U, best)) { best = i; }
        }
        self->action_index = best; /* Strict > preserves first-index tie breaking. */
        for (uint32_t i = 0U; i < config->command_count; ++i) { action[i] = config->discrete_actions[best*config->command_count+i]; }
    } else {
        for (uint32_t i = 0U; i < config->command_count; ++i) { action[i] = uz_matrix_get_element_zero_based(output, 0U, i); }
    }
    config->map_action(action, self->requested);
    for (uint32_t i = 0U; i < config->command_count; ++i) { uz_assert(isfinite(self->requested[i])); }
    uz_exported_actor_limit(config, &signals, self->requested, self->limited, &self->saturated);
    config->advance(&signals, &self->state, self->saturated);
    for (uint32_t i = 0U; i < config->command_count; ++i) {
        self->applied[i] = config->delay_steps == 0U ? self->limited[i] : self->state.queue[config->delay_steps-1U][i];
        self->state.queue[1][i] = self->state.queue[0][i];
        self->state.queue[0][i] = self->limited[i];
        self->state.applied_voltage[i] = self->applied[i];
    }
}
#endif
