#include "uz_dqn_agent.h"
#include "../../include/pt1_control_config.h"

#if (PT1_CONTROL_AGENT == PT1_CONTROL_AGENT_DQN)

#include "../uz_HAL.h"
#include "../uz_matrix/uz_matrix.h"
#include "../uz_nn/uz_nn.h"

#include <stdbool.h>

#define UZ_DQN_NUMBER_OF_INPUTS 2U
#define UZ_DQN_NUMBER_OF_OUTPUTS 3U
#define UZ_DQN_NUMBER_OF_LAYERS 3U
#define UZ_DQN_NUMBER_OF_NEURONS_IN_FIRST_LAYER 32U
#define UZ_DQN_NUMBER_OF_NEURONS_IN_SECOND_LAYER 32U

static float dqn_layer1_weights[UZ_DQN_NUMBER_OF_INPUTS * UZ_DQN_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../../workshop/exported_paras/layer1_weights.csv"
};
static float dqn_layer1_bias[UZ_DQN_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../../workshop/exported_paras/layer1_bias.csv"
};
static float dqn_layer1_output[UZ_DQN_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0.0f};

static float dqn_layer2_weights[UZ_DQN_NUMBER_OF_NEURONS_IN_FIRST_LAYER * UZ_DQN_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../../workshop/exported_paras/layer2_weights.csv"
};
static float dqn_layer2_bias[UZ_DQN_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../../workshop/exported_paras/layer2_bias.csv"
};
static float dqn_layer2_output[UZ_DQN_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0.0f};

static float dqn_layer3_weights[UZ_DQN_NUMBER_OF_NEURONS_IN_SECOND_LAYER * UZ_DQN_NUMBER_OF_OUTPUTS] = {
#include "../../../../../../workshop/exported_paras/layer3_weights.csv"
};
static float dqn_layer3_bias[UZ_DQN_NUMBER_OF_OUTPUTS] = {
#include "../../../../../../workshop/exported_paras/layer3_bias.csv"
};
static float dqn_layer3_output[UZ_DQN_NUMBER_OF_OUTPUTS] = {0.0f};

static struct uz_nn_layer_config dqn_layer_config[UZ_DQN_NUMBER_OF_LAYERS] = {
    [0] = {.activation_function = activation_ReLU,
           .number_of_neurons = UZ_DQN_NUMBER_OF_NEURONS_IN_FIRST_LAYER,
           .number_of_inputs = UZ_DQN_NUMBER_OF_INPUTS,
           .length_of_weights = UZ_MATRIX_SIZE(dqn_layer1_weights),
           .length_of_bias = UZ_MATRIX_SIZE(dqn_layer1_bias),
           .length_of_output = UZ_MATRIX_SIZE(dqn_layer1_output),
           .weights = dqn_layer1_weights,
           .bias = dqn_layer1_bias,
           .output = dqn_layer1_output},
    [1] = {.activation_function = activation_ReLU,
           .number_of_neurons = UZ_DQN_NUMBER_OF_NEURONS_IN_SECOND_LAYER,
           .number_of_inputs = UZ_DQN_NUMBER_OF_NEURONS_IN_FIRST_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(dqn_layer2_weights),
           .length_of_bias = UZ_MATRIX_SIZE(dqn_layer2_bias),
           .length_of_output = UZ_MATRIX_SIZE(dqn_layer2_output),
           .weights = dqn_layer2_weights,
           .bias = dqn_layer2_bias,
           .output = dqn_layer2_output},
    [2] = {.activation_function = activation_linear,
           .number_of_neurons = UZ_DQN_NUMBER_OF_OUTPUTS,
           .number_of_inputs = UZ_DQN_NUMBER_OF_NEURONS_IN_SECOND_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(dqn_layer3_weights),
           .length_of_bias = UZ_MATRIX_SIZE(dqn_layer3_bias),
           .length_of_output = UZ_MATRIX_SIZE(dqn_layer3_output),
           .weights = dqn_layer3_weights,
           .bias = dqn_layer3_bias,
           .output = dqn_layer3_output},
};

struct uz_dqn_agent_t {
    bool is_ready;
    uz_nn_t *network;
    struct uz_matrix_t input_matrix;
    float input_data[UZ_DQN_NUMBER_OF_INPUTS];
};

static uz_dqn_agent_t dqn_agent = {0};
static const float dqn_action_values[UZ_DQN_NUMBER_OF_OUTPUTS] = {-1.0f, 0.0f, 1.0f};

uz_dqn_agent_t *uz_dqn_agent_init(void)
{
    uz_assert_false(dqn_agent.is_ready);
    dqn_agent.input_data[0] = 0.0f;
    dqn_agent.input_data[1] = 0.0f;
    uz_matrix_init(&dqn_agent.input_matrix, dqn_agent.input_data, UZ_MATRIX_SIZE(dqn_agent.input_data), 1U, UZ_DQN_NUMBER_OF_INPUTS);
    dqn_agent.network = uz_nn_init(dqn_layer_config, UZ_DQN_NUMBER_OF_LAYERS);
    dqn_agent.is_ready = true;
    return &dqn_agent;
}

float uz_dqn_agent_step(uz_dqn_agent_t *self, float actual_value, float reference_value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->input_data[0] = actual_value;
    self->input_data[1] = reference_value;
    uz_nn_ff(self->network, &self->input_matrix);
    uint32_t action_index = uz_matrix_get_max_index(uz_nn_get_output_data(self->network));
    uz_assert(action_index < UZ_DQN_NUMBER_OF_OUTPUTS);
    return dqn_action_values[action_index];
}

#endif
