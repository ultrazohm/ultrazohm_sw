#ifdef TEST

#include "unity.h"

#include "uz_dqn_agent.h"
#include "uz_matrix.h"
#include "uz_nn.h"
#include "uz_nn_activation_functions.h"
#include "uz_nn_layer.h"

#include <stdint.h>

void setUp(void)
{
}

void tearDown(void)
{
}

// Builds a two-layer network whose output is fully determined by the second
// layer's bias (all weights zero, first-layer bias positive so ReLU passes it
// through). This makes the greedy action index predictable regardless of input.
#define DQN_TEST_INPUTS 2U
#define DQN_TEST_HIDDEN 2U

static float bias_driven_hidden_bias[DQN_TEST_HIDDEN] = {1.0f, 1.0f};

void test_uz_dqn_agent_returns_greedy_action_from_configured_table(void)
{
    static float hidden_weights[DQN_TEST_INPUTS * DQN_TEST_HIDDEN] = {0};
    static float hidden_output[DQN_TEST_HIDDEN] = {0};

    const uint32_t number_of_actions = 3U;
    static float output_weights[DQN_TEST_HIDDEN * 3U] = {0};
    static float output_bias[3U] = {0.0f, 5.0f, 0.0f}; // argmax -> index 1
    static float output_output[3U] = {0};
    static const float action_values[3U] = {-1.0f, 0.0f, 1.0f};

    struct uz_nn_layer_config layers[2] = {
        [0] = {.activation_function = activation_ReLU,
               .number_of_neurons = DQN_TEST_HIDDEN,
               .number_of_inputs = DQN_TEST_INPUTS,
               .length_of_weights = UZ_MATRIX_SIZE(hidden_weights),
               .length_of_bias = UZ_MATRIX_SIZE(bias_driven_hidden_bias),
               .length_of_output = UZ_MATRIX_SIZE(hidden_output),
               .weights = hidden_weights,
               .bias = bias_driven_hidden_bias,
               .output = hidden_output},
        [1] = {.activation_function = activation_linear,
               .number_of_neurons = 3U,
               .number_of_inputs = DQN_TEST_HIDDEN,
               .length_of_weights = UZ_MATRIX_SIZE(output_weights),
               .length_of_bias = UZ_MATRIX_SIZE(output_bias),
               .length_of_output = UZ_MATRIX_SIZE(output_output),
               .weights = output_weights,
               .bias = output_bias,
               .output = output_output},
    };

    struct uz_dqn_agent_config config = {
        .layers = layers,
        .number_of_layers = 2U,
        .action_values = action_values,
        .number_of_actions = number_of_actions,
    };

    uz_dqn_agent_t *agent = uz_dqn_agent_init(config);
    TEST_ASSERT_NOT_NULL(agent);
    // Greedy index is 1 regardless of the observation.
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_dqn_agent_step(agent, 0.42f, -0.13f));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_dqn_agent_step(agent, -5.0f, 5.0f));
}

// Two independent agents with different action-space sizes prove the instance
// pool and per-instance configuration.
void test_uz_dqn_agent_multiple_instances_have_independent_action_spaces(void)
{
    static float hidden_weights_a[DQN_TEST_INPUTS * DQN_TEST_HIDDEN] = {0};
    static float hidden_output_a[DQN_TEST_HIDDEN] = {0};
    static float output_weights_a[DQN_TEST_HIDDEN * 2U] = {0};
    static float output_bias_a[2U] = {7.0f, 0.0f}; // argmax -> 0
    static float output_output_a[2U] = {0};
    static const float action_values_a[2U] = {10.0f, 20.0f};

    static float hidden_weights_b[DQN_TEST_INPUTS * DQN_TEST_HIDDEN] = {0};
    static float hidden_output_b[DQN_TEST_HIDDEN] = {0};
    static float output_weights_b[DQN_TEST_HIDDEN * 3U] = {0};
    static float output_bias_b[3U] = {0.0f, 0.0f, 9.0f}; // argmax -> 2
    static float output_output_b[3U] = {0};
    static const float action_values_b[3U] = {-1.0f, 0.0f, 1.0f};

    struct uz_nn_layer_config layers_a[2] = {
        [0] = {.activation_function = activation_ReLU, .number_of_neurons = DQN_TEST_HIDDEN, .number_of_inputs = DQN_TEST_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(hidden_weights_a), .length_of_bias = UZ_MATRIX_SIZE(bias_driven_hidden_bias), .length_of_output = UZ_MATRIX_SIZE(hidden_output_a), .weights = hidden_weights_a, .bias = bias_driven_hidden_bias, .output = hidden_output_a},
        [1] = {.activation_function = activation_linear, .number_of_neurons = 2U, .number_of_inputs = DQN_TEST_HIDDEN, .length_of_weights = UZ_MATRIX_SIZE(output_weights_a), .length_of_bias = UZ_MATRIX_SIZE(output_bias_a), .length_of_output = UZ_MATRIX_SIZE(output_output_a), .weights = output_weights_a, .bias = output_bias_a, .output = output_output_a},
    };
    struct uz_nn_layer_config layers_b[2] = {
        [0] = {.activation_function = activation_ReLU, .number_of_neurons = DQN_TEST_HIDDEN, .number_of_inputs = DQN_TEST_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(hidden_weights_b), .length_of_bias = UZ_MATRIX_SIZE(bias_driven_hidden_bias), .length_of_output = UZ_MATRIX_SIZE(hidden_output_b), .weights = hidden_weights_b, .bias = bias_driven_hidden_bias, .output = hidden_output_b},
        [1] = {.activation_function = activation_linear, .number_of_neurons = 3U, .number_of_inputs = DQN_TEST_HIDDEN, .length_of_weights = UZ_MATRIX_SIZE(output_weights_b), .length_of_bias = UZ_MATRIX_SIZE(output_bias_b), .length_of_output = UZ_MATRIX_SIZE(output_output_b), .weights = output_weights_b, .bias = output_bias_b, .output = output_output_b},
    };

    struct uz_dqn_agent_config config_a = {.layers = layers_a, .number_of_layers = 2U, .action_values = action_values_a, .number_of_actions = 2U};
    struct uz_dqn_agent_config config_b = {.layers = layers_b, .number_of_layers = 2U, .action_values = action_values_b, .number_of_actions = 3U};

    uz_dqn_agent_t *agent_a = uz_dqn_agent_init(config_a);
    uz_dqn_agent_t *agent_b = uz_dqn_agent_init(config_b);
    TEST_ASSERT_NOT_NULL(agent_a);
    TEST_ASSERT_NOT_NULL(agent_b);
    TEST_ASSERT_TRUE(agent_a != agent_b);

    TEST_ASSERT_EQUAL_FLOAT(10.0f, uz_dqn_agent_step(agent_a, 0.0f, 0.0f));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_dqn_agent_step(agent_b, 0.0f, 0.0f));
}

#endif
