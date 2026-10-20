#ifdef TEST
#include "unity.h"
#include "export_struct_to_csv.h"
#include "uz_actor_pt1_example.h"
#include "pt1_ddpg_config.h"
#include "fixtures/pt1_ddpg_trace.h"
#include <math.h>
TEST_SOURCE_FILE("uz_exported_actor.c")
TEST_SOURCE_FILE("uz_nn.c")
TEST_SOURCE_FILE("uz_nn_layer.c")
TEST_SOURCE_FILE("uz_nn_activation_functions.c")
TEST_SOURCE_FILE("uz_matrix.c")
TEST_SOURCE_FILE("pt1_ddpg_config.c")
static uz_actor_pt1_example_t example;
void setUp(void) {}
static FILE *eval_log;
void tearDown(void) {
    /* Unity can abort the test on a parity failure; retain the partial trace. */
    if (eval_log != NULL) {
        int status = fclose(eval_log);
        eval_log = NULL;
        TEST_ASSERT_EQUAL_INT(0, status);
    }
}
void test_pt1_ddpg_export_matches_python_closed_loop(void) {
    uz_actor_pt1_example_init(&example, &pt1_ddpg_config, PT1_DDPG_GAIN, PT1_DDPG_TIME_CONSTANT);
    eval_log = open_csv_file_for_write("uz_exported_actor/pt1_ddpg_eval.csv");
    TEST_ASSERT_TRUE(fputs("time;episode;episode_k;y;reference;error;action_value;reward;exploration_rate;terminated;truncated;done\n", eval_log) >= 0);
    uint32_t episode_k = 0U;
    int episode = -1;
    for (uint32_t k = 0U; k < PT1_DDPG_TRACE_ROWS; ++k) {
        const float *row = pt1_ddpg_trace[k];
        if ((int)row[0] != episode) {
            episode = (int)row[0];
            episode_k = 0U;
            uz_actor_pt1_example_reset(&example, 0.0f);
        }
        TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, row[2], example.output);
        float y = example.output;
        float output = uz_actor_pt1_example_step(&example, row[1]);
        uz_matrix_t *raw = uz_nn_get_output_data(example.actor.network);
        int truncated = k + 1U == PT1_DDPG_TRACE_ROWS ||
                        (int)pt1_ddpg_trace[k + 1U][0] != episode;
        float error_after = row[1] - output;
        /* Workshop schema: pre-step y/error, post-step squared-error reward.
         * Values come from the C closed loop, not the Python reference trace. */
        TEST_ASSERT_TRUE(fprintf(eval_log,
            "%lu;%d;%lu;%.9g;%.9g;%.9g;%.9g;%.9g;0;0;%d;%d\n",
            (unsigned long)k, episode + 1, (unsigned long)episode_k,
            (double)y, (double)row[1], (double)(row[1] - y),
            (double)example.actor.requested[0], (double)(-error_after * error_after),
            truncated, truncated) >= 0);
        ++episode_k;
        TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, row[3], example.actor.requested[0]);
        TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, row[4], output);
        TEST_ASSERT_TRUE(isfinite(output));
        for (uint32_t i = 0U; i < pt1_ddpg_config.input_count; ++i) {
            TEST_ASSERT_FLOAT_WITHIN(2.0e-4f, row[6U+i], pt1_ddpg_config.observations[i]);
        }
        for (uint32_t i = 0U; i < pt1_ddpg_config.output_count; ++i) {
            TEST_ASSERT_FLOAT_WITHIN(2.0e-3f, row[8U+i], uz_matrix_get_element_zero_based(raw, 0U, i));
        }
    }
}
#endif
