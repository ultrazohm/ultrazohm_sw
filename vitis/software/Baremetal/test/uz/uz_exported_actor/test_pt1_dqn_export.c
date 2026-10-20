#ifdef TEST
#include "unity.h"
#include "uz_actor_pt1_example.h"
#include "pt1_dqn_config.h"
#include "fixtures/pt1_dqn_trace.h"
#include <math.h>
TEST_SOURCE_FILE("uz_exported_actor.c")
TEST_SOURCE_FILE("uz_nn.c")
TEST_SOURCE_FILE("uz_nn_layer.c")
TEST_SOURCE_FILE("uz_nn_activation_functions.c")
TEST_SOURCE_FILE("uz_matrix.c")
TEST_SOURCE_FILE("pt1_dqn_config.c")
static uz_actor_pt1_example_t example;
void setUp(void) {}
void tearDown(void) {}
void test_pt1_dqn_export_matches_python_closed_loop(void) {
    uz_actor_pt1_example_init(&example, &pt1_dqn_config, PT1_DQN_GAIN, PT1_DQN_TIME_CONSTANT);
    int episode = -1;
    for (uint32_t k = 0U; k < PT1_DQN_TRACE_ROWS; ++k) {
        const float *row = pt1_dqn_trace[k];
        if ((int)row[0] != episode) {
            episode = (int)row[0];
            uz_actor_pt1_example_reset(&example, 0.0f);
        }
        TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, row[2], example.output);
        float output = uz_actor_pt1_example_step(&example, row[1]);
        TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, row[3], example.actor.requested[0]);
        TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, row[4], output);
        TEST_ASSERT_TRUE(isfinite(output));
        for (uint32_t i = 0U; i < pt1_dqn_config.input_count; ++i) {
            TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, row[6U+i], pt1_dqn_config.observations[i]);
        }
        uz_matrix_t *raw = uz_nn_get_output_data(example.actor.network);
        for (uint32_t i = 0U; i < pt1_dqn_config.output_count; ++i) {
            TEST_ASSERT_FLOAT_WITHIN(2.0e-3f, row[8U+i], uz_matrix_get_element_zero_based(raw, 0U, i));
        }
        TEST_ASSERT_EQUAL_UINT32((uint32_t)row[5], example.actor.action_index);
    }
}
#endif
