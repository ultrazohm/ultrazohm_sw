#ifdef TEST

#include "unity.h"

#include "uz_matrix.h"
#include "uz_nn.h"
#include "uz_nn_activation_functions.h"
#include "uz_nn_layer.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define DQN_PT1_NUMBER_OF_INPUTS 2U
#define DQN_PT1_NUMBER_OF_OUTPUTS 3U
#define DQN_PT1_NUMBER_OF_LAYERS 3U
#define DQN_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER 32U
#define DQN_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER 32U

#define DQN_PT1_GAIN 1.0f
#define DQN_PT1_TIME_CONSTANT_S 0.2f
#define DQN_PT1_CONTROL_FREQUENCY_HZ 100.0f
#define DQN_PT1_SAMPLE_TIME_S (1.0f / DQN_PT1_CONTROL_FREQUENCY_HZ)
#define DQN_PT1_EPISODE_SECONDS 2.0f
#define DQN_PT1_STEPS_PER_EPISODE ((uint32_t)(DQN_PT1_EPISODE_SECONDS * DQN_PT1_CONTROL_FREQUENCY_HZ))
#define DQN_PT1_EVAL_EPISODES 4U
#define DQN_PT1_EVAL_LOG_PATH "../../../workshop/logs/ceedling_eval_log.csv"

static float dqn_pt1_input_data[DQN_PT1_NUMBER_OF_INPUTS] = {0.0f};
static struct uz_matrix_t dqn_pt1_input_matrix = {0};

static float dqn_pt1_layer1_weights[DQN_PT1_NUMBER_OF_INPUTS * DQN_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../../workshop/exported_paras/layer1_weights.csv"
};
static float dqn_pt1_layer1_bias[DQN_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../../workshop/exported_paras/layer1_bias.csv"
};
static float dqn_pt1_layer1_output[DQN_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0.0f};

static float dqn_pt1_layer2_weights[DQN_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER * DQN_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../../workshop/exported_paras/layer2_weights.csv"
};
static float dqn_pt1_layer2_bias[DQN_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../../workshop/exported_paras/layer2_bias.csv"
};
static float dqn_pt1_layer2_output[DQN_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0.0f};

static float dqn_pt1_layer3_weights[DQN_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER * DQN_PT1_NUMBER_OF_OUTPUTS] = {
#include "../../../../../../workshop/exported_paras/layer3_weights.csv"
};
static float dqn_pt1_layer3_bias[DQN_PT1_NUMBER_OF_OUTPUTS] = {
#include "../../../../../../workshop/exported_paras/layer3_bias.csv"
};
static float dqn_pt1_layer3_output[DQN_PT1_NUMBER_OF_OUTPUTS] = {0.0f};

static struct uz_nn_layer_config dqn_pt1_layer_config[DQN_PT1_NUMBER_OF_LAYERS] = {
    [0] = {.activation_function = activation_ReLU,
           .number_of_neurons = DQN_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER,
           .number_of_inputs = DQN_PT1_NUMBER_OF_INPUTS,
           .length_of_weights = UZ_MATRIX_SIZE(dqn_pt1_layer1_weights),
           .length_of_bias = UZ_MATRIX_SIZE(dqn_pt1_layer1_bias),
           .length_of_output = UZ_MATRIX_SIZE(dqn_pt1_layer1_output),
           .weights = dqn_pt1_layer1_weights,
           .bias = dqn_pt1_layer1_bias,
           .output = dqn_pt1_layer1_output},
    [1] = {.activation_function = activation_ReLU,
           .number_of_neurons = DQN_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER,
           .number_of_inputs = DQN_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(dqn_pt1_layer2_weights),
           .length_of_bias = UZ_MATRIX_SIZE(dqn_pt1_layer2_bias),
           .length_of_output = UZ_MATRIX_SIZE(dqn_pt1_layer2_output),
           .weights = dqn_pt1_layer2_weights,
           .bias = dqn_pt1_layer2_bias,
           .output = dqn_pt1_layer2_output},
    [2] = {.activation_function = activation_linear,
           .number_of_neurons = DQN_PT1_NUMBER_OF_OUTPUTS,
           .number_of_inputs = DQN_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(dqn_pt1_layer3_weights),
           .length_of_bias = UZ_MATRIX_SIZE(dqn_pt1_layer3_bias),
           .length_of_output = UZ_MATRIX_SIZE(dqn_pt1_layer3_output),
           .weights = dqn_pt1_layer3_weights,
           .bias = dqn_pt1_layer3_bias,
           .output = dqn_pt1_layer3_output},
};

static const float dqn_pt1_action_values[DQN_PT1_NUMBER_OF_OUTPUTS] = {-1.0f, 0.0f, 1.0f};
static const float dqn_pt1_eval_references[DQN_PT1_EVAL_EPISODES] = {-1.0f, 0.0f, 0.5f, 1.0f};

void setUp(void)
{
}

void tearDown(void)
{
}

static float dqn_pt1_update(float y, float input)
{
    const float alpha = expf(-DQN_PT1_SAMPLE_TIME_S / DQN_PT1_TIME_CONSTANT_S);
    return (alpha * y) + ((1.0f - alpha) * DQN_PT1_GAIN * input);
}

static float dqn_pt1_reward(float y, float reference)
{
    const float error = reference - y;
    return -error * error;
}

static void dqn_pt1_write_csv_header(FILE *file)
{
    fprintf(file, "time,episode,episode_k,y,reference,error,action_index,action_value,reward,");
    fprintf(file, "q_action_minus_1,q_action_0,q_action_plus_1,greedy_action_index,");
    fprintf(file, "greedy_action_value,exploration_rate,terminated,truncated,done\n");
}

static void dqn_pt1_write_csv_step(FILE *file,
                                   uint32_t time,
                                   uint32_t episode,
                                   uint32_t episode_k,
                                   float y,
                                   float reference,
                                   uint32_t action_index,
                                   float action_value,
                                   float reward,
                                   float q_action_minus_1,
                                   float q_action_0,
                                   float q_action_plus_1,
                                   float truncated)
{
    fprintf(file,
            "%lu,%lu,%lu,%.9g,%.9g,%.9g,%lu,%.9g,%.9g,%.9g,%.9g,%.9g,%lu,%.9g,%.9g,%.9g,%.9g,%.9g\n",
            (unsigned long)time,
            (unsigned long)episode,
            (unsigned long)episode_k,
            (double)y,
            (double)reference,
            (double)(reference - y),
            (unsigned long)action_index,
            (double)action_value,
            (double)reward,
            (double)q_action_minus_1,
            (double)q_action_0,
            (double)q_action_plus_1,
            (unsigned long)action_index,
            (double)action_value,
            0.0,
            0.0,
            (double)truncated,
            (double)truncated);
}

void test_uz_dqn_pt1_eval_export_to_csv(void)
{
    uz_matrix_t *input = uz_matrix_init(&dqn_pt1_input_matrix,
                                        dqn_pt1_input_data,
                                        UZ_MATRIX_SIZE(dqn_pt1_input_data),
                                        1U,
                                        DQN_PT1_NUMBER_OF_INPUTS);
    uz_nn_t *network = uz_nn_init(dqn_pt1_layer_config, DQN_PT1_NUMBER_OF_LAYERS);
    FILE *file = fopen(DQN_PT1_EVAL_LOG_PATH, "w");
    TEST_ASSERT_NOT_NULL(file);
    dqn_pt1_write_csv_header(file);

    uint32_t time = 0U;
    for (uint32_t episode_index = 0U; episode_index < DQN_PT1_EVAL_EPISODES; episode_index++)
    {
        float y = 0.0f;
        const float reference = dqn_pt1_eval_references[episode_index];

        for (uint32_t episode_k = 0U; episode_k < DQN_PT1_STEPS_PER_EPISODE; episode_k++)
        {
            dqn_pt1_input_data[0] = y;
            dqn_pt1_input_data[1] = reference;
            uz_nn_ff(network, input);

            uz_matrix_t *q_values = uz_nn_get_output_data(network);
            const uint32_t action_index = uz_matrix_get_max_index(q_values);
            TEST_ASSERT_LESS_THAN_UINT32(DQN_PT1_NUMBER_OF_OUTPUTS, action_index);

            const float action_value = dqn_pt1_action_values[action_index];
            const float next_y = dqn_pt1_update(y, action_value);
            const float reward = dqn_pt1_reward(next_y, reference);
            const float truncated = (episode_k + 1U) >= DQN_PT1_STEPS_PER_EPISODE ? 1.0f : 0.0f;

            dqn_pt1_write_csv_step(file,
                                   time,
                                   episode_index + 1U,
                                   episode_k,
                                   y,
                                   reference,
                                   action_index,
                                   action_value,
                                   reward,
                                   uz_matrix_get_element_zero_based(q_values, 0U, 0U),
                                   uz_matrix_get_element_zero_based(q_values, 0U, 1U),
                                   uz_matrix_get_element_zero_based(q_values, 0U, 2U),
                                   truncated);

            y = next_y;
            time++;
        }
    }

    TEST_ASSERT_EQUAL_INT(0, fclose(file));
}

#endif
