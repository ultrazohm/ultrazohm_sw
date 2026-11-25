/* Copyright Contributors to the UltraZohm project. SPDX-License-Identifier: Apache-2.0 */
#ifdef TEST
#include "unity.h"
#include "uz_actor_pt1_replay.h"
#include "fixtures/pt1_dqn_trace.h"
#include "fixtures/pt1_ddpg_trace.h"
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
	uz_actor_pt1_replay_set_epsilon(0.0f);
}

void tearDown(void) {
	uz_actor_pt1_replay_stop();
	uz_actor_pt1_replay_set_epsilon(0.0f);
}

void test_dqn_and_ddpg_replay_preserve_all_reference_samples_and_completion(void) {
	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DQN);
	for (uint32_t k = 0U; k < PT1_DQN_TRACE_ROWS; ++k) {
		uz_actor_pt1_replay_step();
		TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_actor_pt1_replay_signals.actor);
		TEST_ASSERT_EQUAL_FLOAT((float)k, uz_actor_pt1_replay_signals.time);
		TEST_ASSERT_EQUAL_FLOAT(pt1_dqn_trace[k][1], uz_actor_pt1_replay_signals.reference);
		TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, pt1_dqn_trace[k][2], uz_actor_pt1_replay_signals.y);
		TEST_ASSERT_EQUAL_FLOAT(pt1_dqn_trace[k][5], uz_actor_pt1_replay_signals.action_index);
		TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, pt1_dqn_trace[k][3], uz_actor_pt1_replay_signals.action_value);
		const float done = (((k + 1U) % 500U) == 0U) ? 1.0f : 0.0f;
		TEST_ASSERT_EQUAL_FLOAT(done, uz_actor_pt1_replay_signals.done);
	}
	uz_actor_pt1_replay_step();
	TEST_ASSERT_EQUAL(UZ_PT1_REPLAY_IDLE, uz_actor_pt1_replay_get_active_actor());
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_replay_signals.actor);

	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DDPG);
	for (uint32_t k = 0U; k < PT1_DDPG_TRACE_ROWS; ++k) {
		uz_actor_pt1_replay_step();
		TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_actor_pt1_replay_signals.actor);
		TEST_ASSERT_EQUAL_FLOAT((float)k, uz_actor_pt1_replay_signals.time);
		TEST_ASSERT_EQUAL_FLOAT(pt1_ddpg_trace[k][1], uz_actor_pt1_replay_signals.reference);
		TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, pt1_ddpg_trace[k][2], uz_actor_pt1_replay_signals.y);
		TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, pt1_ddpg_trace[k][3], uz_actor_pt1_replay_signals.action_value);
		TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_replay_signals.action_index);
		for (uint32_t i = 0U; i < 3U; ++i) {
			TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_replay_signals.q_values[i]);
		}
	}
	uz_actor_pt1_replay_step();
	TEST_ASSERT_EQUAL(UZ_PT1_REPLAY_IDLE, uz_actor_pt1_replay_get_active_actor());
}

void test_manual_mode_preserves_reference_switches_actor_and_stops(void) {
	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DQN);
	uz_actor_pt1_replay_set_reference(0.5f);
	uz_actor_pt1_replay_toggle_manual();
	uz_actor_pt1_replay_set_reference(NAN);
	for (uint32_t k = 0U; k < 3001U; ++k) {
		uz_actor_pt1_replay_step();
	}
	TEST_ASSERT_TRUE(uz_actor_pt1_replay_is_manual());
	TEST_ASSERT_EQUAL_FLOAT(3.0f, uz_actor_pt1_replay_signals.actor);
	TEST_ASSERT_EQUAL_FLOAT(0.5f, uz_actor_pt1_replay_signals.reference);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_replay_signals.done);
	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DDPG);
	uz_actor_pt1_replay_step();
	TEST_ASSERT_EQUAL_FLOAT(4.0f, uz_actor_pt1_replay_signals.actor);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_replay_signals.time);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_replay_signals.y);
	uz_actor_pt1_replay_toggle_manual();
	TEST_ASSERT_FALSE(uz_actor_pt1_replay_is_manual());
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_replay_signals.actor);
}
#if UZ_PT1_TRAINING == 1U
void test_exploration_logs_the_action_actually_applied_and_complete_transition(void) {
	uz_actor_pt1_replay_set_epsilon(1.0f);
	uz_actor_pt1_replay_start(UZ_PT1_REPLAY_DQN);
	/* Changes while running must be ignored. */
	uz_actor_pt1_replay_set_epsilon(0.0f);
	bool seen[3] = {false, false, false};
	float previous_next = 0.0f;
	for (uint32_t k = 0U; k < 500U; ++k) {
		uz_actor_pt1_replay_step();
		const struct uz_actor_pt1_replay_signals *s = &uz_actor_pt1_replay_signals;
		TEST_ASSERT_EQUAL_FLOAT(1.0f, s->epsilon);
		TEST_ASSERT_EQUAL_FLOAT(previous_next, s->y);
		TEST_ASSERT_TRUE(s->action_index >= 0.0f && s->action_index <= 2.0f);
		seen[(uint32_t)s->action_index] = true;
		TEST_ASSERT_EQUAL_FLOAT(s->action_index - 1.0f, s->action_value);
		const float expected = s->y + (-expm1f(-0.05f)) * (s->action_value - s->y);
		TEST_ASSERT_FLOAT_WITHIN(1.0e-6f, expected, s->next_y);
		const float error = s->reference - s->next_y;
		TEST_ASSERT_FLOAT_WITHIN(1.0e-6f, -error * error, s->reward);
		previous_next = s->next_y;
	}
	TEST_ASSERT_TRUE(seen[0] && seen[1] && seen[2]);
	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_actor_pt1_replay_signals.done);
	uz_actor_pt1_replay_step();
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_actor_pt1_replay_signals.y);
}

#endif

#endif
