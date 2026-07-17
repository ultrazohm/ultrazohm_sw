#include "../include/dqn_pt1_control.h"
#include "../uz/uz_global_configuration.h"

#if (UZ_APP != UZ_APP_DESKBENCH)
#include "../IP_Cores/uz_plantPT1/uz_plantPT1.h"
#include "../uz/uz_nn/uz_nn.h"
#include "../uz/uz_matrix/uz_matrix.h"
#include "xparameters.h"
#include "../uz/uz_HAL.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// The agents are generic uz_nn wrappers; the concrete network (weights exported
// from training) and action space are owned here in the application layer and
// passed in via the agent config struct.
#if (PT1_CONTROL_AGENT == PT1_CONTROL_AGENT_DDPG)
#include "../uz/uz_ddpg/uz_ddpg_agent.h"

#define PT1_DDPG_NUMBER_OF_INPUTS 2U
#define PT1_DDPG_NUMBER_OF_OUTPUTS 1U
#define PT1_DDPG_NUMBER_OF_LAYERS 3U
#define PT1_DDPG_NEURONS_IN_FIRST_LAYER 32U
#define PT1_DDPG_NEURONS_IN_SECOND_LAYER 32U

static float ddpg_layer1_weights[PT1_DDPG_NUMBER_OF_INPUTS * PT1_DDPG_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../workshop/exported_paras_ddpg/layer1_weights.csv"
};
static float ddpg_layer1_bias[PT1_DDPG_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../workshop/exported_paras_ddpg/layer1_bias.csv"
};
static float ddpg_layer1_output[PT1_DDPG_NEURONS_IN_FIRST_LAYER] = {0.0f};

static float ddpg_layer2_weights[PT1_DDPG_NEURONS_IN_FIRST_LAYER * PT1_DDPG_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../workshop/exported_paras_ddpg/layer2_weights.csv"
};
static float ddpg_layer2_bias[PT1_DDPG_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../workshop/exported_paras_ddpg/layer2_bias.csv"
};
static float ddpg_layer2_output[PT1_DDPG_NEURONS_IN_SECOND_LAYER] = {0.0f};

static float ddpg_layer3_weights[PT1_DDPG_NEURONS_IN_SECOND_LAYER * PT1_DDPG_NUMBER_OF_OUTPUTS] = {
#include "../../../../../workshop/exported_paras_ddpg/layer3_weights.csv"
};
static float ddpg_layer3_bias[PT1_DDPG_NUMBER_OF_OUTPUTS] = {
#include "../../../../../workshop/exported_paras_ddpg/layer3_bias.csv"
};
static float ddpg_layer3_output[PT1_DDPG_NUMBER_OF_OUTPUTS] = {0.0f};

static struct uz_nn_layer_config ddpg_layers[PT1_DDPG_NUMBER_OF_LAYERS] = {
    [0] = {.activation_function = activation_ReLU,
           .number_of_neurons = PT1_DDPG_NEURONS_IN_FIRST_LAYER,
           .number_of_inputs = PT1_DDPG_NUMBER_OF_INPUTS,
           .length_of_weights = UZ_MATRIX_SIZE(ddpg_layer1_weights),
           .length_of_bias = UZ_MATRIX_SIZE(ddpg_layer1_bias),
           .length_of_output = UZ_MATRIX_SIZE(ddpg_layer1_output),
           .weights = ddpg_layer1_weights,
           .bias = ddpg_layer1_bias,
           .output = ddpg_layer1_output},
    [1] = {.activation_function = activation_ReLU,
           .number_of_neurons = PT1_DDPG_NEURONS_IN_SECOND_LAYER,
           .number_of_inputs = PT1_DDPG_NEURONS_IN_FIRST_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(ddpg_layer2_weights),
           .length_of_bias = UZ_MATRIX_SIZE(ddpg_layer2_bias),
           .length_of_output = UZ_MATRIX_SIZE(ddpg_layer2_output),
           .weights = ddpg_layer2_weights,
           .bias = ddpg_layer2_bias,
           .output = ddpg_layer2_output},
    [2] = {.activation_function = activation_tanh,
           .number_of_neurons = PT1_DDPG_NUMBER_OF_OUTPUTS,
           .number_of_inputs = PT1_DDPG_NEURONS_IN_SECOND_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(ddpg_layer3_weights),
           .length_of_bias = UZ_MATRIX_SIZE(ddpg_layer3_bias),
           .length_of_output = UZ_MATRIX_SIZE(ddpg_layer3_output),
           .weights = ddpg_layer3_weights,
           .bias = ddpg_layer3_bias,
           .output = ddpg_layer3_output},
};
#else
#include "../uz/uz_dqn/uz_dqn_agent.h"

#define PT1_DQN_NUMBER_OF_INPUTS 2U
#define PT1_DQN_NUMBER_OF_OUTPUTS 3U
#define PT1_DQN_NUMBER_OF_LAYERS 3U
#define PT1_DQN_NEURONS_IN_FIRST_LAYER 32U
#define PT1_DQN_NEURONS_IN_SECOND_LAYER 32U

static float dqn_layer1_weights[PT1_DQN_NUMBER_OF_INPUTS * PT1_DQN_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../workshop/exported_paras/layer1_weights.csv"
};
static float dqn_layer1_bias[PT1_DQN_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../workshop/exported_paras/layer1_bias.csv"
};
static float dqn_layer1_output[PT1_DQN_NEURONS_IN_FIRST_LAYER] = {0.0f};

static float dqn_layer2_weights[PT1_DQN_NEURONS_IN_FIRST_LAYER * PT1_DQN_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../workshop/exported_paras/layer2_weights.csv"
};
static float dqn_layer2_bias[PT1_DQN_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../workshop/exported_paras/layer2_bias.csv"
};
static float dqn_layer2_output[PT1_DQN_NEURONS_IN_SECOND_LAYER] = {0.0f};

static float dqn_layer3_weights[PT1_DQN_NEURONS_IN_SECOND_LAYER * PT1_DQN_NUMBER_OF_OUTPUTS] = {
#include "../../../../../workshop/exported_paras/layer3_weights.csv"
};
static float dqn_layer3_bias[PT1_DQN_NUMBER_OF_OUTPUTS] = {
#include "../../../../../workshop/exported_paras/layer3_bias.csv"
};
static float dqn_layer3_output[PT1_DQN_NUMBER_OF_OUTPUTS] = {0.0f};

static const float dqn_action_values[PT1_DQN_NUMBER_OF_OUTPUTS] = {-1.0f, 0.0f, 1.0f};

static struct uz_nn_layer_config dqn_layers[PT1_DQN_NUMBER_OF_LAYERS] = {
    [0] = {.activation_function = activation_ReLU,
           .number_of_neurons = PT1_DQN_NEURONS_IN_FIRST_LAYER,
           .number_of_inputs = PT1_DQN_NUMBER_OF_INPUTS,
           .length_of_weights = UZ_MATRIX_SIZE(dqn_layer1_weights),
           .length_of_bias = UZ_MATRIX_SIZE(dqn_layer1_bias),
           .length_of_output = UZ_MATRIX_SIZE(dqn_layer1_output),
           .weights = dqn_layer1_weights,
           .bias = dqn_layer1_bias,
           .output = dqn_layer1_output},
    [1] = {.activation_function = activation_ReLU,
           .number_of_neurons = PT1_DQN_NEURONS_IN_SECOND_LAYER,
           .number_of_inputs = PT1_DQN_NEURONS_IN_FIRST_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(dqn_layer2_weights),
           .length_of_bias = UZ_MATRIX_SIZE(dqn_layer2_bias),
           .length_of_output = UZ_MATRIX_SIZE(dqn_layer2_output),
           .weights = dqn_layer2_weights,
           .bias = dqn_layer2_bias,
           .output = dqn_layer2_output},
    [2] = {.activation_function = activation_linear,
           .number_of_neurons = PT1_DQN_NUMBER_OF_OUTPUTS,
           .number_of_inputs = PT1_DQN_NEURONS_IN_SECOND_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(dqn_layer3_weights),
           .length_of_bias = UZ_MATRIX_SIZE(dqn_layer3_bias),
           .length_of_output = UZ_MATRIX_SIZE(dqn_layer3_output),
           .weights = dqn_layer3_weights,
           .bias = dqn_layer3_bias,
           .output = dqn_layer3_output},
};
#endif

static const float pt1_eval_profile_references[] = {-1.0f, 0.0f, 0.5f, 0.1f, 0.2f, 1.0f};
#define PT1_EVAL_PROFILE_LENGTH ((uint32_t)(sizeof(pt1_eval_profile_references) / sizeof(pt1_eval_profile_references[0])))

static bool pt1_eval_profile_active = false;
static bool pt1_eval_profile_reset_pending = false;
static uint32_t pt1_eval_profile_episode_index = 0U;
static uint32_t pt1_eval_profile_step_counter = 0U;

static void finish_eval_profile(DS_Data *data);
static uint32_t get_eval_profile_episode_steps(const DS_Data *data);
static void prepare_eval_profile_episode(DS_Data *data);
static void set_reference_value(DS_Data *data);
static void advance_eval_profile(DS_Data *data);

void pt1_control_init(DS_Data *data)
{
    uz_assert_not_zero_uint32(XPAR_UZ_USER_UZ_PLANTMODEL_PT1_0_BASEADDR);
    data->objects.plant_pt1 = NULL;
    data->objects.dqn_agent = NULL;
    data->objects.ddpg_agent = NULL;

#if (PT1_CONTROL_AGENT == PT1_CONTROL_AGENT_DDPG)
    struct uz_ddpg_agent_config ddpg_config = {
        .layers = ddpg_layers,
        .number_of_layers = PT1_DDPG_NUMBER_OF_LAYERS,
        .action_min = PT1_CONTROL_ACTION_MIN,
        .action_max = PT1_CONTROL_ACTION_MAX,
    };
    data->objects.ddpg_agent = uz_ddpg_agent_init(ddpg_config);
#else
    struct uz_dqn_agent_config dqn_config = {
        .layers = dqn_layers,
        .number_of_layers = PT1_DQN_NUMBER_OF_LAYERS,
        .action_values = dqn_action_values,
        .number_of_actions = PT1_DQN_NUMBER_OF_OUTPUTS,
    };
    data->objects.dqn_agent = uz_dqn_agent_init(dqn_config);
#endif

    data->av.dqn_pt1_actual = 0.0f;
    data->av.dqn_pt1_reference = PT1_CONTROL_INITIAL_SETPOINT;
    data->av.dqn_pt1_javascope_setpoint = PT1_CONTROL_INITIAL_SETPOINT;
    data->av.dqn_pt1_action = 0.0f;
    finish_eval_profile(data);

    struct uz_plantPT1_config_t config = {
        .base_address = XPAR_UZ_USER_UZ_PLANTMODEL_PT1_0_BASEADDR,
        .ip_core_frequency_Hz = 100000000U,
        .gain = PT1_CONTROL_GAIN,
        .time_constant = PT1_CONTROL_TIME_CONSTANT_S,
    };

    data->objects.plant_pt1 = uz_plantPT1_init(config);
    uz_plantPT1_set_input(data->objects.plant_pt1, 0.0f);
    uz_plantPT1_reset_integrator(data->objects.plant_pt1);
}

void pt1_control_start_eval_profile(DS_Data *data)
{
    uz_assert_not_NULL(data);

    if (pt1_eval_profile_active)
    {
        return;
    }

    pt1_eval_profile_active = true;
    pt1_eval_profile_reset_pending = true;
    pt1_eval_profile_episode_index = 0U;
    pt1_eval_profile_step_counter = 0U;
    data->av.dqn_pt1_eval_profile_episode = 1.0f;
}

void pt1_control_step(DS_Data *data)
{
    uz_assert_not_NULL(data->objects.plant_pt1);

    if (pt1_eval_profile_active)
    {
        prepare_eval_profile_episode(data);
    }

    data->av.dqn_pt1_actual = uz_plantPT1_read_output(data->objects.plant_pt1);
    set_reference_value(data);

#if (PT1_CONTROL_AGENT == PT1_CONTROL_AGENT_DDPG)
    uz_assert_not_NULL(data->objects.ddpg_agent);
    data->av.dqn_pt1_action = uz_ddpg_agent_step(
        data->objects.ddpg_agent,
        data->av.dqn_pt1_actual,
        data->av.dqn_pt1_reference);
#else
    uz_assert_not_NULL(data->objects.dqn_agent);
    data->av.dqn_pt1_action = uz_dqn_agent_step(
        data->objects.dqn_agent,
        data->av.dqn_pt1_actual,
        data->av.dqn_pt1_reference);
#endif
    uz_plantPT1_set_input(data->objects.plant_pt1, data->av.dqn_pt1_action);
    advance_eval_profile(data);
}

void pt1_control_stop(DS_Data *data)
{
    finish_eval_profile(data);
    uz_assert_not_NULL(data->objects.plant_pt1);
    data->av.dqn_pt1_action = 0.0f;
    data->av.dqn_pt1_actual = uz_plantPT1_read_output(data->objects.plant_pt1);
    data->av.dqn_pt1_reference = data->av.dqn_pt1_javascope_setpoint;
    uz_plantPT1_set_input(data->objects.plant_pt1, 0.0f);
}

static void finish_eval_profile(DS_Data *data)
{
    pt1_eval_profile_active = false;
    pt1_eval_profile_reset_pending = false;
    pt1_eval_profile_episode_index = 0U;
    pt1_eval_profile_step_counter = 0U;
    data->av.dqn_pt1_eval_profile_episode = 0.0f;
}

static uint32_t get_eval_profile_episode_steps(const DS_Data *data)
{
    if (data->av.isr_samplerate_s <= 0.0f)
    {
        return 1U;
    }

    const float episode_steps = PT1_EVAL_PROFILE_EPISODE_SECONDS / data->av.isr_samplerate_s;
    if (episode_steps <= 1.0f)
    {
        return 1U;
    }

    return (uint32_t)(episode_steps + 0.5f);
}

static void prepare_eval_profile_episode(DS_Data *data)
{
    if (!pt1_eval_profile_reset_pending)
    {
        return;
    }

    data->av.dqn_pt1_action = 0.0f;
    uz_plantPT1_set_input(data->objects.plant_pt1, 0.0f);
    uz_plantPT1_reset_integrator(data->objects.plant_pt1);
    pt1_eval_profile_reset_pending = false;
}

static void set_reference_value(DS_Data *data)
{
    if (!pt1_eval_profile_active)
    {
        data->av.dqn_pt1_reference = data->av.dqn_pt1_javascope_setpoint;
        data->av.dqn_pt1_eval_profile_episode = 0.0f;
        return;
    }

    uz_assert(pt1_eval_profile_episode_index < PT1_EVAL_PROFILE_LENGTH);
    data->av.dqn_pt1_reference = pt1_eval_profile_references[pt1_eval_profile_episode_index];
    data->av.dqn_pt1_eval_profile_episode = (float)(pt1_eval_profile_episode_index + 1U);
}

static void advance_eval_profile(DS_Data *data)
{
    if (!pt1_eval_profile_active)
    {
        return;
    }

    pt1_eval_profile_step_counter++;
    if (pt1_eval_profile_step_counter < get_eval_profile_episode_steps(data))
    {
        return;
    }

    pt1_eval_profile_step_counter = 0U;
    if ((pt1_eval_profile_episode_index + 1U) >= PT1_EVAL_PROFILE_LENGTH)
    {
        finish_eval_profile(data);
        data->av.dqn_pt1_reference = data->av.dqn_pt1_javascope_setpoint;
        return;
    }

    pt1_eval_profile_episode_index++;
    pt1_eval_profile_reset_pending = true;
    data->av.dqn_pt1_eval_profile_episode = (float)(pt1_eval_profile_episode_index + 1U);
}

#else

void pt1_control_init(DS_Data *data)
{
    (void)data;
}

void pt1_control_step(DS_Data *data)
{
    (void)data;
}

void pt1_control_stop(DS_Data *data)
{
    (void)data;
}

void pt1_control_start_eval_profile(DS_Data *data)
{
    (void)data;
}

#endif
