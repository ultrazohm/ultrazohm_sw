/* Copyright Contributors to the UltraZohm project. SPDX-License-Identifier: Apache-2.0 */
#ifdef TEST
#include "unity.h"
#include "uz_actor_pt1_replay.h"
#include "pt1_dqn_config.h"
#include "pt1_ddpg_config.h"
#include <math.h>
TEST_SOURCE_FILE("uz_actor_pt1_replay.c")
TEST_SOURCE_FILE("uz_actor_pt1_example.c")
TEST_SOURCE_FILE("uz_exported_actor.c")
TEST_SOURCE_FILE("uz_nn.c")
TEST_SOURCE_FILE("uz_nn_layer.c")
TEST_SOURCE_FILE("uz_nn_activation_functions.c")
TEST_SOURCE_FILE("uz_matrix.c")
TEST_SOURCE_FILE("pt1_dqn_config.c")
TEST_SOURCE_FILE("pt1_ddpg_config.c")

void setUp(void) {
	static bool initialized = false;
	if (!initialized) {
		uz_actor_pt1_replay_init(10000.0f);
		initialized = true;
	}
	uz_actor_pt1_replay_stop();
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_TARGET, 1.0f);
	uz_actor_pt1_update_begin();
}
void tearDown(void) {
	uz_actor_pt1_replay_stop();
}

static void write_parameter(uint32_t layer, uint32_t kind, uint32_t index, float value) {
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_LAYER, (float)layer);
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_TYPE, (float)kind);
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_INDEX, (float)index);
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_VALUE, value);
}

static void upload(const struct uz_exported_actor_config *config) {
	for (uint32_t i = 0U; i < config->layer_count; ++i) {
		const struct uz_nn_layer_config *layer = &config->layers[i];
		for (uint32_t j = 0U; j < layer->length_of_weights; ++j) {
			write_parameter(i, 0U, j, layer->weights[j]);
		}
		for (uint32_t j = 0U; j < layer->length_of_bias; ++j) {
			write_parameter(i, 1U, j, layer->bias[j]);
		}
	}
}

void test_upload_directly_writes_weights_and_blocks_control_until_complete(void) {
	float original = pt1_dqn_config.layers[0].weights[0];
	write_parameter(0U, 0U, 0U, original + 0.25f);
	TEST_ASSERT_EQUAL_FLOAT(original + 0.25f, pt1_dqn_config.layers[0].weights[0]);
	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_actor_pt1_update_status.received);
	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DQN);
	uz_actor_pt1_replay_toggle_manual();
	TEST_ASSERT_EQUAL(UZ_PT1_REPLAY_IDLE, uz_actor_pt1_replay_get_active_actor());
	TEST_ASSERT_FALSE(uz_actor_pt1_replay_is_manual());
	uz_actor_pt1_update_finish();
	TEST_ASSERT_EQUAL_FLOAT(4.0f, uz_actor_pt1_update_status.error);
	uz_actor_pt1_replay_stop();
	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DQN);
	TEST_ASSERT_EQUAL(UZ_PT1_REPLAY_IDLE, uz_actor_pt1_replay_get_active_actor());

	uz_actor_pt1_update_begin();
	// Restore the original first weight through the same upload path.
	write_parameter(0U, 0U, 0U, original);
	uz_actor_pt1_update_begin();
	upload(&pt1_dqn_config);
	TEST_ASSERT_EQUAL_FLOAT(1251.0f, uz_actor_pt1_update_status.received);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_update_status.error);
	uz_actor_pt1_update_finish();
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_update_status.active);
	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DQN);
	uz_actor_pt1_replay_step();
	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_actor_pt1_replay_signals.actor);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_replay_signals.time);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_replay_signals.y);
}

void test_upload_requires_fresh_fields_and_ordered_unique_parameters(void) {
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_VALUE, 1.0f);
	TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_actor_pt1_update_status.error);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_update_status.received);
	uz_actor_pt1_update_begin();
	write_parameter(0U, 0U, 1U, 1.0f);
	TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_actor_pt1_update_status.error);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_update_status.received);
	uz_actor_pt1_update_begin();
	float first = pt1_dqn_config.layers[0].weights[0];
	write_parameter(0U, 0U, 0U, first);
	write_parameter(0U, 0U, 0U, first);
	TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_actor_pt1_update_status.error);
	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_actor_pt1_update_status.received);
}

void test_upload_rejects_invalid_selectors_and_nonfinite_values(void) {
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_LAYER, -1.0f);
	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_actor_pt1_update_status.error);
	uz_actor_pt1_update_begin();
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_LAYER, 0.5f);
	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_actor_pt1_update_status.error);
	uz_actor_pt1_update_begin();
	write_parameter(0U, 0U, 64U, 1.0f);
	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_actor_pt1_update_status.error);
	uz_actor_pt1_update_begin();
	write_parameter(0U, 0U, 0U, NAN);
	TEST_ASSERT_EQUAL_FLOAT(3.0f, uz_actor_pt1_update_status.error);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_update_status.received);
	uz_actor_pt1_replay_stop();
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_TARGET, NAN);
	uz_actor_pt1_update_begin();
	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_actor_pt1_update_status.error);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_update_status.active);
}

void test_ddpg_upload_finishes_and_stop_aborts_an_incomplete_upload(void) {
	uz_actor_pt1_replay_stop();
	TEST_ASSERT_EQUAL_FLOAT(5.0f, uz_actor_pt1_update_status.error);
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_TARGET, 2.0f);
	uz_actor_pt1_update_begin();
	TEST_ASSERT_EQUAL_FLOAT(1185.0f, uz_actor_pt1_update_status.expected);
	upload(&pt1_ddpg_config);
	uz_actor_pt1_update_finish();
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_update_status.error);
	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DQN);
	TEST_ASSERT_EQUAL(UZ_PT1_REPLAY_IDLE, uz_actor_pt1_replay_get_active_actor());
	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DDPG);
	uz_actor_pt1_replay_toggle_manual();
	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DDPG);
	uz_actor_pt1_replay_step();
	TEST_ASSERT_EQUAL_FLOAT(4.0f, uz_actor_pt1_replay_signals.actor);
}
void test_upload_rejects_nonfinite_fractional_and_oversized_indices_without_writing(void) {
	const float invalid[] = {-1.0f, 0.5f, 64.0f, 4294967296.0f, INFINITY, -INFINITY, NAN};
	const float original = pt1_dqn_config.layers[0].weights[0];
	for (uint32_t i = 0U; i < (sizeof(invalid) / sizeof(invalid[0])); ++i) {
		uz_actor_pt1_update_begin();
		write_parameter(0U, 0U, 0U, original);
		write_parameter(0U, 0U, 1U, pt1_dqn_config.layers[0].weights[1]);
		uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_LAYER, 0.0f);
		uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_TYPE, 0.0f);
		uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_INDEX, invalid[i]);
		TEST_ASSERT_TRUE(uz_actor_pt1_update_status.error > 0.0f);
		TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_actor_pt1_update_status.received);
		TEST_ASSERT_EQUAL_FLOAT(original, pt1_dqn_config.layers[0].weights[0]);
	}
}

void test_upload_logic_uses_internal_state_instead_of_float_feedback_storage(void) {
	TEST_ASSERT_TRUE(uz_actor_pt1_update_is_active());
	uz_actor_pt1_update_status.active = 0.0f;
	uz_actor_pt1_update_status.target = 2.0f;
	uz_actor_pt1_update_status.received = 1251.0f;
	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DQN);
	TEST_ASSERT_EQUAL(UZ_PT1_REPLAY_IDLE, uz_actor_pt1_replay_get_active_actor());
	TEST_ASSERT_TRUE(uz_actor_pt1_update_is_active());
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_TARGET, 2.0f);
	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_actor_pt1_update_status.target);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_update_status.received);
	uz_actor_pt1_update_finish();
	TEST_ASSERT_EQUAL_FLOAT(4.0f, uz_actor_pt1_update_status.error);
}

void test_upload_rejects_invalid_targets_and_recovers_with_a_valid_target(void) {
	const float invalid_targets[] = {0.0f, -1.0f, 0.5f, 1.5f, 2.5f, 3.0f, INFINITY, -INFINITY, NAN};
	uz_actor_pt1_replay_stop();
	for (uint32_t i = 0U; i < (sizeof(invalid_targets) / sizeof(invalid_targets[0])); ++i) {
		uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_TARGET, invalid_targets[i]);
		uz_actor_pt1_update_begin();
		TEST_ASSERT_FALSE(uz_actor_pt1_update_is_active());
		TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_actor_pt1_update_status.error);
	}
	uz_actor_pt1_update_field(UZ_ACTOR_PT1_UPDATE_FIELD_TARGET, 2.0f);
	uz_actor_pt1_update_begin();
	TEST_ASSERT_TRUE(uz_actor_pt1_update_is_active());
	TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_actor_pt1_update_status.target);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_update_status.error);
	TEST_ASSERT_EQUAL_FLOAT(1185.0f, uz_actor_pt1_update_status.expected);
}
#endif
