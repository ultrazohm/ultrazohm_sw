#ifdef TEST

#include "unity.h"

#include "uz_ddpg_agent.h"
#include "uz_matrix.h"
#include "uz_nn.h"
#include "uz_nn_activation_functions.h"
#include "uz_nn_layer.h"

#include <math.h>
#include <stdint.h>

void setUp(void)
{
}

void tearDown(void)
{
}

// Two-layer actor whose scalar output is fully determined by the output-layer
// bias (all weights zero, first-layer bias positive so ReLU passes it through).
#define DDPG_TEST_INPUTS 2U
#define DDPG_TEST_HIDDEN 2U

static float ddpg_hidden_bias[DDPG_TEST_HIDDEN] = {1.0f, 1.0f};

void test_uz_ddpg_agent_returns_tanh_actor_output_within_bounds(void)
{
    static float hidden_weights[DDPG_TEST_INPUTS * DDPG_TEST_HIDDEN] = {0};
    static float hidden_output[DDPG_TEST_HIDDEN] = {0};
    static float output_weights[DDPG_TEST_HIDDEN * 1U] = {0};
    static float output_bias[1U] = {0.1f}; // tanh(0.1) ~= 0.09967, inside [-1, 1]
    static float output_output[1U] = {0};

    struct uz_nn_layer_config layers[2] = {
        [0] = {.activation_function = activation_ReLU,
               .number_of_neurons = DDPG_TEST_HIDDEN,
               .number_of_inputs = DDPG_TEST_INPUTS,
               .length_of_weights = UZ_MATRIX_SIZE(hidden_weights),
               .length_of_bias = UZ_MATRIX_SIZE(ddpg_hidden_bias),
               .length_of_output = UZ_MATRIX_SIZE(hidden_output),
               .weights = hidden_weights,
               .bias = ddpg_hidden_bias,
               .output = hidden_output},
        [1] = {.activation_function = activation_tanh,
               .number_of_neurons = 1U,
               .number_of_inputs = DDPG_TEST_HIDDEN,
               .length_of_weights = UZ_MATRIX_SIZE(output_weights),
               .length_of_bias = UZ_MATRIX_SIZE(output_bias),
               .length_of_output = UZ_MATRIX_SIZE(output_output),
               .weights = output_weights,
               .bias = output_bias,
               .output = output_output},
    };

    struct uz_ddpg_agent_config config = {
        .layers = layers,
        .number_of_layers = 2U,
        .action_min = -1.0f,
        .action_max = 1.0f,
    };

    uz_ddpg_agent_t *agent = uz_ddpg_agent_init(config);
    TEST_ASSERT_NOT_NULL(agent);
    TEST_ASSERT_FLOAT_WITHIN(1e-5f, tanhf(0.1f), uz_ddpg_agent_step(agent, 0.3f, -0.2f));
}

void test_uz_ddpg_agent_clamps_actor_output_to_action_max(void)
{
    static float hidden_weights[DDPG_TEST_INPUTS * DDPG_TEST_HIDDEN] = {0};
    static float hidden_output[DDPG_TEST_HIDDEN] = {0};
    static float output_weights[DDPG_TEST_HIDDEN * 1U] = {0};
    static float output_bias[1U] = {3.0f}; // tanh(3.0) ~= 0.995, above action_max 0.5
    static float output_output[1U] = {0};

    struct uz_nn_layer_config layers[2] = {
        [0] = {.activation_function = activation_ReLU,
               .number_of_neurons = DDPG_TEST_HIDDEN,
               .number_of_inputs = DDPG_TEST_INPUTS,
               .length_of_weights = UZ_MATRIX_SIZE(hidden_weights),
               .length_of_bias = UZ_MATRIX_SIZE(ddpg_hidden_bias),
               .length_of_output = UZ_MATRIX_SIZE(hidden_output),
               .weights = hidden_weights,
               .bias = ddpg_hidden_bias,
               .output = hidden_output},
        [1] = {.activation_function = activation_tanh,
               .number_of_neurons = 1U,
               .number_of_inputs = DDPG_TEST_HIDDEN,
               .length_of_weights = UZ_MATRIX_SIZE(output_weights),
               .length_of_bias = UZ_MATRIX_SIZE(output_bias),
               .length_of_output = UZ_MATRIX_SIZE(output_output),
               .weights = output_weights,
               .bias = output_bias,
               .output = output_output},
    };

    struct uz_ddpg_agent_config config = {
        .layers = layers,
        .number_of_layers = 2U,
        .action_min = -0.5f,
        .action_max = 0.5f,
    };

    uz_ddpg_agent_t *agent = uz_ddpg_agent_init(config);
    TEST_ASSERT_NOT_NULL(agent);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, uz_ddpg_agent_step(agent, 0.0f, 0.0f));
}

#endif
