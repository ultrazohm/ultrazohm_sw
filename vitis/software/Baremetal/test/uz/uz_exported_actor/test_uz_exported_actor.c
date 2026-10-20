#ifdef TEST
#include "unity.h"
#include "uz_exported_actor.h"
#include "pt1_dqn_config.h"
#include "pmsm_td3_config.h"
#include "test_assert_with_exception.h"
#include <math.h>
#include <stddef.h>
TEST_SOURCE_FILE("uz_nn.c")
TEST_SOURCE_FILE("uz_nn_layer.c")
TEST_SOURCE_FILE("uz_nn_activation_functions.c")
TEST_SOURCE_FILE("uz_matrix.c")
TEST_SOURCE_FILE("pt1_dqn_config.c")
TEST_SOURCE_FILE("pmsm_td3_config.c")
void setUp(void) {}
void tearDown(void) {}

void test_frequency_contract_is_enforced(void) {
    uz_exported_actor_t actor;
    TEST_ASSERT_FAIL_ASSERT(uz_exported_actor_init(&actor, &pt1_dqn_config, 5000.0f));
}

void test_first_index_wins_equal_dqn_values(void) {
    float w1[2] = {0}, b1[1] = {0}, y1[1] = {0};
    float w2[3] = {0}, b2[3] = {0}, y2[3] = {0};
    float observations[2] = {0};
    struct uz_nn_layer_config layers[UZ_NN_MAX_LAYER] = {
        {.activation_function=activation_ReLU, .number_of_neurons=1U, .number_of_inputs=2U,
         .length_of_weights=2U, .length_of_bias=1U, .length_of_output=1U, .weights=w1, .bias=b1, .output=y1},
        {.activation_function=activation_linear, .number_of_neurons=3U, .number_of_inputs=1U,
         .length_of_weights=3U, .length_of_bias=3U, .length_of_output=3U, .weights=w2, .bias=b2, .output=y2}};
    struct uz_exported_actor_config config = pt1_dqn_config;
    config.layers=layers; config.layer_count=2U; config.observations=observations;
    uz_exported_actor_t actor;
    uz_exported_actor_init(&actor, &config, 10000.0f);
    uz_exported_actor_sample(&actor, (struct uz_exported_actor_signals){.output=.2f, .reference={.5f,0.0f}});
    TEST_ASSERT_EQUAL_UINT32(0U, actor.action_index);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, actor.applied[0]);
}

void test_axis_priority_uses_selected_current_and_preserves_zero_sign(void) {
    struct uz_exported_actor_config config = pmsm_td3_config;
    config.voltage_limit = 10.0f;
    struct uz_exported_actor_signals signals = {.current={0.0f,2.0f}, .reference={0.0f,-2.0f}, .speed_rpm=100.0f};
    float request[2] = {8.0f,9.0f}, limited[2]; bool saturated;
    config.limiter_reference_current=false;
    uz_exported_actor_limit(&config,&signals,request,limited,&saturated);
    TEST_ASSERT_TRUE(saturated); TEST_ASSERT_EQUAL_FLOAT(8.0f,limited[0]); TEST_ASSERT_EQUAL_FLOAT(6.0f,limited[1]);
    config.limiter_reference_current=true;
    uz_exported_actor_limit(&config,&signals,request,limited,&saturated);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-5f,sqrtf(19.0f),limited[0]); TEST_ASSERT_EQUAL_FLOAT(9.0f,limited[1]);
    signals.speed_rpm=0.0f; signals.reference[1]=0.0f;
    uz_exported_actor_limit(&config,&signals,request,limited,&saturated);
    TEST_ASSERT_EQUAL_FLOAT(8.0f,limited[0]);
    config.limiter=UZ_ACTOR_RADIAL;
    uz_exported_actor_limit(&config,&signals,request,limited,&saturated);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-5f,10.0f,sqrtf(limited[0]*limited[0]+limited[1]*limited[1]));
}

void test_clamping_integrator_reset_and_delay_queue(void) {
    struct uz_exported_actor_config config = pmsm_td3_config;
    config.delay_steps=2U;
    uz_exported_actor_t actor;
    uz_exported_actor_init(&actor,&config,10000.0f);
    struct uz_exported_actor_signals signals = {.reference={1.0f,2.0f}};
    config.advance(&signals,&actor.state,false);
    TEST_ASSERT_TRUE(actor.state.integral[0]>0.0f);
    float integral = actor.state.integral[0];
    config.advance(&signals,&actor.state,true);
    TEST_ASSERT_EQUAL_FLOAT(integral,actor.state.integral[0]);
    struct uz_exported_actor_state initial = {.applied_voltage={3.0f,4.0f}, .queue={{5.0f,6.0f},{7.0f,8.0f}}};
    uz_exported_actor_reset(&actor,&initial);
    uz_exported_actor_sample(&actor,signals);
    TEST_ASSERT_EQUAL_FLOAT(7.0f,actor.applied[0]);
    TEST_ASSERT_EQUAL_FLOAT(8.0f,actor.applied[1]);
    TEST_ASSERT_EQUAL_FLOAT(5.0f,actor.state.queue[1][0]);
    uz_exported_actor_sample(&actor,signals);
    TEST_ASSERT_EQUAL_FLOAT(5.0f,actor.applied[0]);
    uz_exported_actor_reset(&actor,NULL);
    TEST_ASSERT_EQUAL_FLOAT(0.0f,actor.state.integral[0]);
    TEST_ASSERT_EQUAL_FLOAT(0.0f,actor.applied[0]);
    TEST_ASSERT_EQUAL_FLOAT(0.0f,actor.state.queue[0][0]);
}
#endif
