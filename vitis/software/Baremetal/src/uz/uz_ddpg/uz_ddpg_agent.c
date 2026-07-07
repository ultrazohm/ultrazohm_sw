#include "uz_ddpg_agent.h"
#include "../../include/pt1_control_config.h"

#if (PT1_CONTROL_AGENT == PT1_CONTROL_AGENT_DDPG)

#include "../uz_HAL.h"
#include "../uz_matrix/uz_matrix.h"
#include "../uz_nn/uz_nn.h"

#include <stdbool.h>

#define UZ_DDPG_NUMBER_OF_INPUTS 2U
#define UZ_DDPG_NUMBER_OF_OUTPUTS 1U
#define UZ_DDPG_NUMBER_OF_LAYERS 3U
#define UZ_DDPG_NUMBER_OF_NEURONS_IN_FIRST_LAYER 32U
#define UZ_DDPG_NUMBER_OF_NEURONS_IN_SECOND_LAYER 32U

static float ddpg_layer1_weights[UZ_DDPG_NUMBER_OF_INPUTS * UZ_DDPG_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer1_weights.csv"
};
static float ddpg_layer1_bias[UZ_DDPG_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer1_bias.csv"
};
static float ddpg_layer1_output[UZ_DDPG_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0.0f};

static float ddpg_layer2_weights[UZ_DDPG_NUMBER_OF_NEURONS_IN_FIRST_LAYER * UZ_DDPG_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer2_weights.csv"
};
static float ddpg_layer2_bias[UZ_DDPG_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer2_bias.csv"
};
static float ddpg_layer2_output[UZ_DDPG_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0.0f};

static float ddpg_layer3_weights[UZ_DDPG_NUMBER_OF_NEURONS_IN_SECOND_LAYER * UZ_DDPG_NUMBER_OF_OUTPUTS] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer3_weights.csv"
};
static float ddpg_layer3_bias[UZ_DDPG_NUMBER_OF_OUTPUTS] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer3_bias.csv"
};
static float ddpg_layer3_output[UZ_DDPG_NUMBER_OF_OUTPUTS] = {0.0f};

static struct uz_nn_layer_config ddpg_layer_config[UZ_DDPG_NUMBER_OF_LAYERS] = {
    [0] = {.activation_function = activation_ReLU,
           .number_of_neurons = UZ_DDPG_NUMBER_OF_NEURONS_IN_FIRST_LAYER,
           .number_of_inputs = UZ_DDPG_NUMBER_OF_INPUTS,
           .length_of_weights = UZ_MATRIX_SIZE(ddpg_layer1_weights),
           .length_of_bias = UZ_MATRIX_SIZE(ddpg_layer1_bias),
           .length_of_output = UZ_MATRIX_SIZE(ddpg_layer1_output),
           .weights = ddpg_layer1_weights,
           .bias = ddpg_layer1_bias,
           .output = ddpg_layer1_output},
    [1] = {.activation_function = activation_ReLU,
           .number_of_neurons = UZ_DDPG_NUMBER_OF_NEURONS_IN_SECOND_LAYER,
           .number_of_inputs = UZ_DDPG_NUMBER_OF_NEURONS_IN_FIRST_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(ddpg_layer2_weights),
           .length_of_bias = UZ_MATRIX_SIZE(ddpg_layer2_bias),
           .length_of_output = UZ_MATRIX_SIZE(ddpg_layer2_output),
           .weights = ddpg_layer2_weights,
           .bias = ddpg_layer2_bias,
           .output = ddpg_layer2_output},
    [2] = {.activation_function = activation_tanh,
           .number_of_neurons = UZ_DDPG_NUMBER_OF_OUTPUTS,
           .number_of_inputs = UZ_DDPG_NUMBER_OF_NEURONS_IN_SECOND_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(ddpg_layer3_weights),
           .length_of_bias = UZ_MATRIX_SIZE(ddpg_layer3_bias),
           .length_of_output = UZ_MATRIX_SIZE(ddpg_layer3_output),
           .weights = ddpg_layer3_weights,
           .bias = ddpg_layer3_bias,
           .output = ddpg_layer3_output},
};

struct uz_ddpg_agent_t {
    bool is_ready;
    uz_nn_t *network;
    struct uz_matrix_t input_matrix;
    float input_data[UZ_DDPG_NUMBER_OF_INPUTS];
};

static uz_ddpg_agent_t ddpg_agent = {0};

static float clamp_action(float action)
{
    if (action > PT1_CONTROL_ACTION_MAX)
    {
        return PT1_CONTROL_ACTION_MAX;
    }
    if (action < PT1_CONTROL_ACTION_MIN)
    {
        return PT1_CONTROL_ACTION_MIN;
    }
    return action;
}

uz_ddpg_agent_t *uz_ddpg_agent_init(void)
{
    uz_assert_false(ddpg_agent.is_ready);
    ddpg_agent.input_data[0] = 0.0f;
    ddpg_agent.input_data[1] = 0.0f;
    uz_matrix_init(&ddpg_agent.input_matrix,
                   ddpg_agent.input_data,
                   UZ_MATRIX_SIZE(ddpg_agent.input_data),
                   1U,
                   UZ_DDPG_NUMBER_OF_INPUTS);
    ddpg_agent.network = uz_nn_init(ddpg_layer_config, UZ_DDPG_NUMBER_OF_LAYERS);
    ddpg_agent.is_ready = true;
    return &ddpg_agent;
}

float uz_ddpg_agent_step(uz_ddpg_agent_t *self, float actual_value, float reference_value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->input_data[0] = actual_value;
    self->input_data[1] = reference_value;
    uz_nn_ff(self->network, &self->input_matrix);

    uz_matrix_t *actor_output = uz_nn_get_output_data(self->network);
    const float action = uz_matrix_get_element_zero_based(actor_output, 0U, 0U);
    return clamp_action(action);
}

#endif
