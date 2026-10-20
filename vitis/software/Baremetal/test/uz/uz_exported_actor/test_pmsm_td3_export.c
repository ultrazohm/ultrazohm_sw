#ifdef TEST
#include "unity.h"
#include <math.h>
#include "uz_actor_pmsm_example.h"
#include "pmsm_td3_config.h"
#include "fixtures/pmsm_td3_trace.h"
TEST_SOURCE_FILE("uz_exported_actor.c")
TEST_SOURCE_FILE("uz_nn.c")
TEST_SOURCE_FILE("uz_nn_layer.c")
TEST_SOURCE_FILE("uz_nn_activation_functions.c")
TEST_SOURCE_FILE("uz_matrix.c")
TEST_SOURCE_FILE("pmsm_td3_config.c")
TEST_SOURCE_FILE("uz_pmsm_swmodel.c")
TEST_SOURCE_FILE("uz_PMSM_config.c")
TEST_SOURCE_FILE("uz_integrator.c")
static uz_actor_pmsm_example_t example;
void setUp(void) {}
void tearDown(void) {}
/* Closed-loop trajectories need not remain bitwise identical across JAX and C:
 * rounding at saturation boundaries can change subsequent controller states.
 * Separate strict replay tests below verify each subsystem against Python. */
void test_pmsm_td3_export_controls_swmodel_and_resets_repeatably(void) {
    static float first_run[PMSM_TD3_TRACE_ROWS][2];
    uz_actor_pmsm_example_init(&example, &pmsm_td3_config, pmsm_td3_plant, PMSM_TD3_OVERSAMPLING);
    for (uint32_t repeat = 0U; repeat < 2U; ++repeat) {
        uz_actor_pmsm_example_reset(&example);
        float previous_limited[2] = {0};
        float absolute_error = 0.0f;
        for (uint32_t k = 0U; k < PMSM_TD3_TRACE_ROWS; ++k) {
            const float *row = pmsm_td3_trace[k];
            float previous_integral[2] = {example.actor.state.integral[0], example.actor.state.integral[1]};
            float previous_applied[2] = {example.actor.applied[0], example.actor.applied[1]};
            struct uz_pmsm_swmodel_outputs_t output = uz_actor_pmsm_example_step(&example, row[0], row[1], row[2]);
            TEST_ASSERT_TRUE(isfinite(output.i_dq_A.d) && isfinite(output.i_dq_A.q));
            TEST_ASSERT_TRUE(fabsf(output.i_dq_A.d) < 16.0f && fabsf(output.i_dq_A.q) < 16.0f);
            float magnitude = sqrtf(example.actor.limited[0]*example.actor.limited[0]+example.actor.limited[1]*example.actor.limited[1]);
            TEST_ASSERT_TRUE(magnitude <= pmsm_td3_config.voltage_limit + 1.0e-4f);
            for (uint32_t i = 0U; i < 2U; ++i) {
                TEST_ASSERT_EQUAL_FLOAT(previous_limited[i], example.actor.applied[i]);
                TEST_ASSERT_FLOAT_WITHIN(1.0e-6f,previous_applied[i]/pmsm_td3_config.voltage_limit,pmsm_td3_config.observations[7U+i]);
                if (example.actor.saturated) { TEST_ASSERT_EQUAL_FLOAT(previous_integral[i],example.actor.state.integral[i]); }
                previous_limited[i]=example.actor.limited[i];
            }
            absolute_error += fabsf(row[0]-output.i_dq_A.d)+fabsf(row[1]-output.i_dq_A.q);
            if (repeat == 0U) { first_run[k][0]=output.i_dq_A.d; first_run[k][1]=output.i_dq_A.q; }
            else {
                TEST_ASSERT_EQUAL_FLOAT(first_run[k][0],output.i_dq_A.d);
                TEST_ASSERT_EQUAL_FLOAT(first_run[k][1],output.i_dq_A.q);
            }
        }
        /* Functional smoke bound for this fixture, not a hardware tuning claim. */
        TEST_ASSERT_TRUE(absolute_error/(2.0f*(float)PMSM_TD3_TRACE_ROWS) < 3.0f);
    }
}

void test_pmsm_swmodel_matches_python_for_identical_exported_voltage_trace(void) {
    uz_pmsm_swmodel_t *plant = uz_pmsm_swmodel_init(pmsm_td3_plant);
    for (uint32_t k = 0U; k < PMSM_TD3_TRACE_ROWS; ++k) {
        const float *row = pmsm_td3_trace[k];
        struct uz_pmsm_swmodel_inputs_t inputs = {.v_dq_V={.d=row[9],.q=row[10]},
            .omega_mech_1_s=row[2]*(6.2831853071795864769f/60.0f)};
        struct uz_pmsm_swmodel_outputs_t output = {0};
        for (uint32_t substep = 0U; substep < PMSM_TD3_OVERSAMPLING; ++substep) {
            output = uz_pmsm_swmodel_step(plant, inputs);
        }
        TEST_ASSERT_FLOAT_WITHIN(1.0e-4f, row[11], output.i_dq_A.d);
        TEST_ASSERT_FLOAT_WITHIN(1.0e-4f, row[12], output.i_dq_A.q);
    }
}

/* Replay identical physical inputs/state to isolate inference and adapter errors
 * from accumulated floating-point differences in the closed-loop plant. */
void test_pmsm_exported_contract_matches_python_each_tick(void) {
    uz_exported_actor_t actor;
    uz_exported_actor_init(&actor, &pmsm_td3_config, 10000.0f);
    for (uint32_t k = 0U; k < PMSM_TD3_TRACE_ROWS; ++k) {
        const float *row = pmsm_td3_trace[k];
        struct uz_exported_actor_state initial = {0};
        if (k > 0U) {
            for (uint32_t i = 0U; i < 2U; ++i) {
                initial.integral[i] = pmsm_td3_trace[k-1U][13U+i];
                initial.applied_voltage[i] = pmsm_td3_trace[k-1U][9U+i];
                initial.queue[0][i] = pmsm_td3_trace[k-1U][7U+i];
                if (k > 1U) { initial.queue[1][i] = pmsm_td3_trace[k-2U][7U+i]; }
            }
        }
        uz_exported_actor_reset(&actor, &initial);
        struct uz_exported_actor_signals signals = {.reference={row[0],row[1]}, .speed_rpm=row[2], .current={row[3],row[4]}};
        uz_exported_actor_sample(&actor, signals);
        for (uint32_t i = 0U; i < 9U; ++i) {
            TEST_ASSERT_FLOAT_WITHIN(2.0e-5f, row[16U+i], pmsm_td3_config.observations[i]);
        }
        uz_matrix_t *raw = uz_nn_get_output_data(actor.network);
        for (uint32_t i = 0U; i < 2U; ++i) {
            TEST_ASSERT_FLOAT_WITHIN(2.0e-5f, row[25U+i], uz_matrix_get_element_zero_based(raw, 0U, i));
            TEST_ASSERT_FLOAT_WITHIN(6.0e-4f, row[5U+i], actor.requested[i]);
            TEST_ASSERT_FLOAT_WITHIN(6.0e-4f, row[7U+i], actor.limited[i]);
            TEST_ASSERT_FLOAT_WITHIN(6.0e-4f, row[9U+i], actor.applied[i]);
            TEST_ASSERT_FLOAT_WITHIN(1.0e-7f, row[13U+i], actor.state.integral[i]);
        }
        TEST_ASSERT_EQUAL_INT((int)row[15], (int)actor.saturated);
    }
}
#endif
