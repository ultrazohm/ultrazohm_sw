/*
 * Copyright Contributors to the UltraZohm project.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stddef.h>
#include <string.h>
#include "../../uz_global_configuration.h"
#if UZ_PT1_REPLAY == 1U
#include "uz_actor_pt1_replay.h"
#include "uz_actor_pt1_example.h"
#include "pt1_ddpg/pt1_ddpg_config.h"
#include "pt1_dqn/pt1_dqn_config.h"
#include "../../uz_HAL.h"
#include <math.h>
#include <stdint.h>

#define UZ_ACTOR_PT1_EPISODE_COUNT 6U
#define UZ_ACTOR_PT1_STEPS_PER_EPISODE 500U
#define UZ_ACTOR_PT1_Q_VALUE_COUNT 3U
#define UZ_ACTOR_PT1_PARAMETER_WEIGHTS 0U
#define UZ_ACTOR_PT1_PARAMETER_BIAS 1U
/* Integers up to this bound are represented exactly by the float32 protocol. */
#define UZ_ACTOR_PT1_MAX_PARAMETER_COUNT 16777216U

enum uz_actor_pt1_update_error {
	UZ_ACTOR_PT1_UPDATE_OK,
	UZ_ACTOR_PT1_UPDATE_INVALID_SELECTOR,
	UZ_ACTOR_PT1_UPDATE_WRONG_ORDER,
	UZ_ACTOR_PT1_UPDATE_NONFINITE,
	UZ_ACTOR_PT1_UPDATE_INCOMPLETE,
	UZ_ACTOR_PT1_UPDATE_ABORTED
};

struct uz_actor_pt1_update_state {
	bool active;
	bool target_valid;
	bool dqn_ready;
	bool ddpg_ready;
	enum uz_actor_pt1_replay_actor target;
	enum uz_actor_pt1_update_error error;
	uint32_t layer;
	uint32_t kind;
	uint32_t index;
	uint32_t next_field;
	uint32_t received;
	uint32_t expected;
};

static uz_actor_pt1_example_t dqn = {0};
static uz_actor_pt1_example_t ddpg = {0};
static enum uz_actor_pt1_replay_actor active_actor = UZ_PT1_REPLAY_IDLE;
static enum uz_actor_pt1_replay_actor selected_actor = UZ_PT1_REPLAY_DQN;
static bool manual_mode = false;
static float manual_reference = 0.0f;
static uint32_t sample = 0U;
#if UZ_PT1_TRAINING == 1U
static uint32_t random_uint32(void);

static float dqn_epsilon = 0.0f;
static uint32_t random_state = 1U;

/* Deterministic xorshift32 stream, kept across collection batches. */
static uint32_t random_uint32(void) {
	random_state ^= random_state << 13;
	random_state ^= random_state >> 17;
	random_state ^= random_state << 5;
	return random_state;
}

void uz_actor_pt1_replay_set_epsilon(float epsilon) {
	if ((active_actor == UZ_PT1_REPLAY_IDLE) && isfinite(epsilon) &&
	    (epsilon >= 0.0f) && (epsilon <= 1.0f)) {
		dqn_epsilon = epsilon;
	}
}
#endif
static struct uz_actor_pt1_update_state update = {
        .active = false,
        .target_valid = true,
        .dqn_ready = true,
        .ddpg_ready = true,
        .target = UZ_PT1_REPLAY_DQN,
        .error = UZ_ACTOR_PT1_UPDATE_OK,
        .layer = 0U,
        .kind = UZ_ACTOR_PT1_PARAMETER_WEIGHTS,
        .index = 0U,
        .next_field = UZ_ACTOR_PT1_UPDATE_FIELD_LAYER,
        .received = 0U,
        .expected = 0U,
};

/* JavaScope/uz_cli require writable float storage; these are output mirrors. */
struct uz_actor_pt1_replay_signals uz_actor_pt1_replay_signals = {0};
struct uz_actor_pt1_update_status uz_actor_pt1_update_status = {.target = 1.0f};

static const struct uz_exported_actor_config *uz_actor_pt1_get_update_config(void);
static void uz_actor_pt1_publish_update_status(void);
static uint32_t uz_actor_pt1_count_parameters(const struct uz_exported_actor_config *config);
static bool uz_actor_pt1_parameters_are_ready(enum uz_actor_pt1_replay_actor actor);
static void uz_actor_pt1_set_parameters_ready(bool ready);
static bool uz_actor_pt1_selector_is_valid(float value, uint32_t count);
static uint32_t uz_actor_pt1_selector_count(uint32_t field);
static uint32_t uz_actor_pt1_parameter_position(void);
static void uz_actor_pt1_update_target(float value);
static void uz_actor_pt1_update_selector(uint32_t field, float value);
static void uz_actor_pt1_write_parameter(float value);
static void uz_actor_pt1_publish_sample(uz_actor_pt1_example_t *example, uint32_t episode, uint32_t step, float reference);
static void uz_actor_pt1_publish_action(const uz_exported_actor_t *actor);
static void uz_actor_pt1_step_active(void);

static const struct uz_exported_actor_config *uz_actor_pt1_get_update_config(void) {
	const struct uz_exported_actor_config *config = &pt1_dqn_config;
	uz_assert((update.target == UZ_PT1_REPLAY_DQN) || (update.target == UZ_PT1_REPLAY_DDPG));
	if (update.target == UZ_PT1_REPLAY_DDPG) {
		config = &pt1_ddpg_config;
	}
	return config;
}

static void uz_actor_pt1_publish_update_status(void) {
	uz_actor_pt1_update_status.active = update.active ? 1.0f : 0.0f;
	uz_actor_pt1_update_status.target = (update.target == UZ_PT1_REPLAY_DQN) ? 1.0f : 2.0f;
	uz_actor_pt1_update_status.received = (float)update.received;
	uz_actor_pt1_update_status.expected = (float)update.expected;
	switch (update.error) {
	case UZ_ACTOR_PT1_UPDATE_OK:
		uz_actor_pt1_update_status.error = 0.0f;
		break;
	case UZ_ACTOR_PT1_UPDATE_INVALID_SELECTOR:
		uz_actor_pt1_update_status.error = 1.0f;
		break;
	case UZ_ACTOR_PT1_UPDATE_WRONG_ORDER:
		uz_actor_pt1_update_status.error = 2.0f;
		break;
	case UZ_ACTOR_PT1_UPDATE_NONFINITE:
		uz_actor_pt1_update_status.error = 3.0f;
		break;
	case UZ_ACTOR_PT1_UPDATE_INCOMPLETE:
		uz_actor_pt1_update_status.error = 4.0f;
		break;
	case UZ_ACTOR_PT1_UPDATE_ABORTED:
		uz_actor_pt1_update_status.error = 5.0f;
		break;
	default:
		uz_assert(false);
		break;
	}
}

static uint32_t uz_actor_pt1_count_parameters(const struct uz_exported_actor_config *config) {
	uint32_t count = 0U;
	for (uint32_t i = 0U; i < config->layer_count; ++i) {
		const struct uz_nn_layer_config *layer = &config->layers[i];
		uz_assert_not_NULL(layer->weights);
		uz_assert_not_NULL(layer->bias);
		uz_assert(layer->length_of_weights > 0U);
		uz_assert(layer->length_of_bias > 0U);
		uz_assert(layer->length_of_weights <= (UZ_ACTOR_PT1_MAX_PARAMETER_COUNT - count));
		count += layer->length_of_weights;
		uz_assert(layer->length_of_bias <= (UZ_ACTOR_PT1_MAX_PARAMETER_COUNT - count));
		count += layer->length_of_bias;
	}
	return count;
}

static bool uz_actor_pt1_parameters_are_ready(enum uz_actor_pt1_replay_actor actor) {
	bool ready = false;
	if (actor == UZ_PT1_REPLAY_DQN) {
		ready = update.dqn_ready;
	} else if (actor == UZ_PT1_REPLAY_DDPG) {
		ready = update.ddpg_ready;
	} else {
		/* Invalid and idle actors cannot enter inference. */
	}
	return ready;
}

static void uz_actor_pt1_set_parameters_ready(bool ready) {
	if (update.target == UZ_PT1_REPLAY_DQN) {
		update.dqn_ready = ready;
	} else {
		update.ddpg_ready = ready;
	}
}

static bool uz_actor_pt1_selector_is_valid(float value, uint32_t count) {
	bool valid = false;
	uz_assert(count <= UZ_ACTOR_PT1_MAX_PARAMETER_COUNT);
	if ((isfinite(value) != 0) && (value >= 0.0f) && (value < (float)count)) {
		/* Nonnegative, integral and bounded before float-to-index conversion. */
		valid = !(floorf(value) < value);
	}
	return valid;
}

static void uz_actor_pt1_update_target(float value) {
	if (!update.active) {
		/* Only integral selectors 1 (DQN) and 2 (DDPG) identify upload targets. */
		update.target_valid = uz_actor_pt1_selector_is_valid(value, 3U) && (value >= 1.0f);
		if (update.target_valid) {
			update.target = (value < 2.0f) ? UZ_PT1_REPLAY_DQN : UZ_PT1_REPLAY_DDPG;
		} else {
			update.error = UZ_ACTOR_PT1_UPDATE_INVALID_SELECTOR;
		}
	}
}

static uint32_t uz_actor_pt1_selector_count(uint32_t field) {
	const struct uz_exported_actor_config *config = uz_actor_pt1_get_update_config();
	uint32_t count = config->layer_count;
	if (field == UZ_ACTOR_PT1_UPDATE_FIELD_TYPE) {
		count = 2U;
	} else if (field == UZ_ACTOR_PT1_UPDATE_FIELD_INDEX) {
		const struct uz_nn_layer_config *layer = &config->layers[update.layer];
		count = (update.kind == UZ_ACTOR_PT1_PARAMETER_WEIGHTS) ? layer->length_of_weights : layer->length_of_bias;
	} else {
		/* The next-field state machine only admits the layer field here. */
	}
	return count;
}

static void uz_actor_pt1_update_selector(uint32_t field, float value) {
	const uint32_t count = uz_actor_pt1_selector_count(field);
	if (uz_actor_pt1_selector_is_valid(value, count)) {
		/* The protocol carries integer selectors as floats; validation precedes conversion. */
		const uint32_t selector = (uint32_t)value;
		switch (field) {
		case UZ_ACTOR_PT1_UPDATE_FIELD_LAYER:
			update.layer = selector;
			break;
		case UZ_ACTOR_PT1_UPDATE_FIELD_TYPE:
			update.kind = selector;
			break;
		case UZ_ACTOR_PT1_UPDATE_FIELD_INDEX:
			update.index = selector;
			break;
		default:
			update.error = UZ_ACTOR_PT1_UPDATE_WRONG_ORDER;
			break;
		}
		++update.next_field;
	} else {
		update.error = UZ_ACTOR_PT1_UPDATE_INVALID_SELECTOR;
	}
}

static uint32_t uz_actor_pt1_parameter_position(void) {
	const struct uz_exported_actor_config *config = uz_actor_pt1_get_update_config();
	const struct uz_nn_layer_config *layer = &config->layers[update.layer];
	uint32_t position = update.index;
	for (uint32_t i = 0U; i < update.layer; ++i) {
		position += config->layers[i].length_of_weights + config->layers[i].length_of_bias;
	}
	if (update.kind == UZ_ACTOR_PT1_PARAMETER_BIAS) {
		position += layer->length_of_weights;
	}
	return position;
}

static void uz_actor_pt1_write_parameter(float value) {
	const uint32_t position = uz_actor_pt1_parameter_position();
	/* Count only ordered unique writes, never duplicate/skipped parameters. */
	if ((position == update.received) && (update.received < update.expected)) {
		const struct uz_exported_actor_config *config = uz_actor_pt1_get_update_config();
		const struct uz_nn_layer_config *layer = &config->layers[update.layer];
		float *values = (update.kind == UZ_ACTOR_PT1_PARAMETER_WEIGHTS) ? layer->weights : layer->bias;
		values[update.index] = value;
		++update.received;
		update.next_field = UZ_ACTOR_PT1_UPDATE_FIELD_LAYER;
	} else {
		update.error = UZ_ACTOR_PT1_UPDATE_WRONG_ORDER;
	}
}

void uz_actor_pt1_update_begin(void) {
	uz_actor_pt1_replay_stop();
	if (update.target_valid) {
		const struct uz_exported_actor_config *config = uz_actor_pt1_get_update_config();
		uz_actor_pt1_set_parameters_ready(false);
		update.received = 0U;
		update.next_field = UZ_ACTOR_PT1_UPDATE_FIELD_LAYER;
		update.expected = uz_actor_pt1_count_parameters(config);
		update.error = UZ_ACTOR_PT1_UPDATE_OK;
		update.active = true;
	} else {
		update.error = UZ_ACTOR_PT1_UPDATE_INVALID_SELECTOR;
	}
	uz_actor_pt1_publish_update_status();
}

void uz_actor_pt1_update_field(uint32_t field, float value) {
	if (field == UZ_ACTOR_PT1_UPDATE_FIELD_TARGET) {
		uz_actor_pt1_update_target(value);
	} else if (update.active && (update.error == UZ_ACTOR_PT1_UPDATE_OK)) {
		if (isfinite(value) == 0) {
			update.error = UZ_ACTOR_PT1_UPDATE_NONFINITE;
		} else if (field != update.next_field) {
			update.error = UZ_ACTOR_PT1_UPDATE_WRONG_ORDER;
		} else if (field < UZ_ACTOR_PT1_UPDATE_FIELD_VALUE) {
			uz_actor_pt1_update_selector(field, value);
		} else {
			uz_actor_pt1_write_parameter(value);
		}
	} else {
		/* Stopped or rejected uploads ignore data until a new begin command. */
	}
	uz_actor_pt1_publish_update_status();
}

void uz_actor_pt1_update_finish(void) {
	if (update.active && (update.error == UZ_ACTOR_PT1_UPDATE_OK)) {
		if ((update.received == update.expected) && (update.next_field == UZ_ACTOR_PT1_UPDATE_FIELD_LAYER)) {
			uz_actor_pt1_example_reset(&dqn, 0.0f);
			uz_actor_pt1_example_reset(&ddpg, 0.0f);
			uz_actor_pt1_set_parameters_ready(true);
			update.active = false;
		} else {
			update.error = UZ_ACTOR_PT1_UPDATE_INCOMPLETE;
		}
	}
	uz_actor_pt1_publish_update_status();
}

bool uz_actor_pt1_update_is_active(void) {
	return update.active;
}

void uz_actor_pt1_replay_init(float control_frequency_hz) {
	uz_assert(isfinite(control_frequency_hz));
	uz_assert(control_frequency_hz > 0.0f);
	uz_assert(fabsf(control_frequency_hz - pt1_dqn_config.control_frequency_hz) <= 0.01f);
	uz_assert(fabsf(control_frequency_hz - pt1_ddpg_config.control_frequency_hz) <= 0.01f);
	uz_actor_pt1_example_init(&dqn, &pt1_dqn_config, 1.0f, 0.002f);
	uz_actor_pt1_example_init(&ddpg, &pt1_ddpg_config, 1.0f, 0.002f);
	uz_actor_pt1_publish_update_status();
}

void uz_actor_pt1_replay_start(enum uz_actor_pt1_replay_actor actor) {
	const bool ready = uz_actor_pt1_parameters_are_ready(actor);
	if ((!update.active) && ready && (manual_mode || (active_actor == UZ_PT1_REPLAY_IDLE))) {
		selected_actor = actor;
		active_actor = actor;
		sample = 0U;
	}
}

void uz_actor_pt1_replay_stop(void) {
	if (update.active) {
		update.active = false;
		update.error = UZ_ACTOR_PT1_UPDATE_ABORTED;
	}
	active_actor = UZ_PT1_REPLAY_IDLE;
	manual_mode = false;
	uz_actor_pt1_replay_signals.actor = 0.0f;
	uz_actor_pt1_publish_update_status();
}

void uz_actor_pt1_replay_toggle_manual(void) {
	const bool ready = uz_actor_pt1_parameters_are_ready(selected_actor);
	if ((!update.active) && ready) {
		if (manual_mode) {
			uz_actor_pt1_replay_stop();
		} else {
			manual_mode = true;
			uz_actor_pt1_replay_start(selected_actor);
		}
	}
}

void uz_actor_pt1_replay_set_reference(float reference) {
	if (isfinite(reference) != 0) {
		manual_reference = reference;
	}
}

bool uz_actor_pt1_replay_is_manual(void) {
	return manual_mode;
}

enum uz_actor_pt1_replay_actor uz_actor_pt1_replay_get_active_actor(void) {
	return active_actor;
}

static void uz_actor_pt1_publish_action(const uz_exported_actor_t *actor) {
	uz_actor_pt1_replay_signals.action_value = actor->requested[0];
	uz_actor_pt1_replay_signals.action_index = 0.0f;
	for (uint32_t i = 0U; i < UZ_ACTOR_PT1_Q_VALUE_COUNT; ++i) {
		uz_actor_pt1_replay_signals.q_values[i] = 0.0f;
	}
	if (active_actor == UZ_PT1_REPLAY_DQN) {
		const uz_matrix_t *output = uz_nn_get_output_data(actor->network);
		uz_actor_pt1_replay_signals.action_index = (float)actor->action_index;
		for (uint32_t i = 0U; i < UZ_ACTOR_PT1_Q_VALUE_COUNT; ++i) {
			uz_actor_pt1_replay_signals.q_values[i] = uz_matrix_get_element_zero_based(output, 0U, i);
		}
	}
}

static void uz_actor_pt1_publish_sample(uz_actor_pt1_example_t *example, uint32_t episode, uint32_t step, float reference) {
	const float previous_output = example->output;
	float output = uz_actor_pt1_example_step(example, reference);
#if UZ_PT1_TRAINING == 1U
	/* PT1 DQN has no delay or limiter. Replace the greedy command before
	 * committing the plant transition; retain the network Q values. */
	if ((active_actor == UZ_PT1_REPLAY_DQN) && (dqn_epsilon > 0.0f) &&
	    ((float)(random_uint32() >> 8) * (1.0f / 16777216.0f) < dqn_epsilon)) {
		const uint32_t action = random_uint32() % 3U;
		const float command = (float)action - 1.0f;
		example->actor.action_index = action;
		example->actor.requested[0] = command;
		example->actor.limited[0] = command;
		example->actor.applied[0] = command;
		example->actor.state.applied_voltage[0] = command;
		output = previous_output + example->step_fraction * ((example->gain * command) - previous_output);
		example->output = output;
	}
	uz_actor_pt1_replay_signals.next_y = output;
	uz_actor_pt1_replay_signals.epsilon = (active_actor == UZ_PT1_REPLAY_DQN) ? dqn_epsilon : 0.0f;
#endif
	const float error_after = reference - output;
	const uint32_t episode_number = episode + 1U;
	uz_actor_pt1_replay_signals.actor = (active_actor == UZ_PT1_REPLAY_DQN) ? 1.0f : 2.0f;
	if (manual_mode) {
		uz_actor_pt1_replay_signals.actor += 2.0f;
	}
	uz_actor_pt1_replay_signals.time = (float)sample;
	uz_actor_pt1_replay_signals.episode = (float)episode_number;
	uz_actor_pt1_replay_signals.episode_k = (float)step;
	uz_actor_pt1_replay_signals.y = previous_output;
	uz_actor_pt1_replay_signals.reference = reference;
	uz_actor_pt1_replay_signals.error = reference - previous_output;
	uz_actor_pt1_replay_signals.reward = -error_after * error_after;
	uz_actor_pt1_replay_signals.done = ((!manual_mode) && ((step + 1U) == UZ_ACTOR_PT1_STEPS_PER_EPISODE)) ? 1.0f : 0.0f;
	uz_actor_pt1_publish_action(&example->actor);
}

static void uz_actor_pt1_step_active(void) {
	static const float references[UZ_ACTOR_PT1_EPISODE_COUNT] = {-1.0f, 0.0f, 0.5f, 0.1f, 0.2f, 1.0f};

	const uint32_t episode = manual_mode ? 0U : (sample / UZ_ACTOR_PT1_STEPS_PER_EPISODE);
	if (episode < UZ_ACTOR_PT1_EPISODE_COUNT) {
		uz_actor_pt1_example_t *example = (active_actor == UZ_PT1_REPLAY_DQN) ? &dqn : &ddpg;
		const uint32_t step = manual_mode ? sample : (sample % UZ_ACTOR_PT1_STEPS_PER_EPISODE);
		const float reference = manual_mode ? manual_reference : references[episode];
		if (step == 0U) {
			uz_actor_pt1_example_reset(example, 0.0f);
		}
		uz_actor_pt1_publish_sample(example, episode, step, reference);
		/* Saturate the diagnostic counter instead of wrapping/resetting the plant. */
		if (sample < UINT32_MAX) {
			++sample;
		}
	} else {
		uz_actor_pt1_replay_stop();
	}
}

void uz_actor_pt1_replay_step(void) {
	if (active_actor != UZ_PT1_REPLAY_IDLE) {
		uz_actor_pt1_step_active();
	}
}
#endif
