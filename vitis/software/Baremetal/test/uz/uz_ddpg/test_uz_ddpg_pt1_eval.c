#ifdef TEST

#include "unity.h"

#include "uz_matrix.h"
#include "uz_nn.h"
#include "uz_nn_activation_functions.h"
#include "uz_nn_layer.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define DDPG_PT1_NUMBER_OF_INPUTS 2U
#define DDPG_PT1_NUMBER_OF_OUTPUTS 1U
#define DDPG_PT1_NUMBER_OF_LAYERS 3U
#define DDPG_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER 32U
#define DDPG_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER 32U

#define DDPG_PT1_GAIN 1.0f
#define DDPG_PT1_TIME_CONSTANT_S 0.002f
#define DDPG_PT1_CONTROL_FREQUENCY_HZ 10000.0f
#define DDPG_PT1_SAMPLE_TIME_S (1.0f / DDPG_PT1_CONTROL_FREQUENCY_HZ)
#define DDPG_PT1_EPISODE_SECONDS 0.05f
#define DDPG_PT1_STEPS_PER_EPISODE ((uint32_t)(DDPG_PT1_EPISODE_SECONDS * DDPG_PT1_CONTROL_FREQUENCY_HZ))
#define DDPG_PT1_EVAL_EPISODES 6U
#define DDPG_PT1_ACTION_MIN (-1.0f)
#define DDPG_PT1_ACTION_MAX 1.0f
#define DDPG_PT1_EVAL_LOG_PATH "../../../workshop/logs/ceedling_eval_log_ddpg.csv"

static float ddpg_pt1_input_data[DDPG_PT1_NUMBER_OF_INPUTS] = {0.0f};
static struct uz_matrix_t ddpg_pt1_input_matrix = {0};

static float ddpg_pt1_layer1_weights[DDPG_PT1_NUMBER_OF_INPUTS * DDPG_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer1_weights.csv"
};
static float ddpg_pt1_layer1_bias[DDPG_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer1_bias.csv"
};
static float ddpg_pt1_layer1_output[DDPG_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0.0f};

static float ddpg_pt1_layer2_weights[DDPG_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER * DDPG_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer2_weights.csv"
};
static float ddpg_pt1_layer2_bias[DDPG_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer2_bias.csv"
};
static float ddpg_pt1_layer2_output[DDPG_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0.0f};

static float ddpg_pt1_layer3_weights[DDPG_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER * DDPG_PT1_NUMBER_OF_OUTPUTS] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer3_weights.csv"
};
static float ddpg_pt1_layer3_bias[DDPG_PT1_NUMBER_OF_OUTPUTS] = {
#include "../../../../../../workshop/exported_paras_ddpg/layer3_bias.csv"
};
static float ddpg_pt1_layer3_output[DDPG_PT1_NUMBER_OF_OUTPUTS] = {0.0f};

static struct uz_nn_layer_config ddpg_pt1_layer_config[DDPG_PT1_NUMBER_OF_LAYERS] = {
    [0] = {.activation_function = activation_ReLU,
           .number_of_neurons = DDPG_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER,
           .number_of_inputs = DDPG_PT1_NUMBER_OF_INPUTS,
           .length_of_weights = UZ_MATRIX_SIZE(ddpg_pt1_layer1_weights),
           .length_of_bias = UZ_MATRIX_SIZE(ddpg_pt1_layer1_bias),
           .length_of_output = UZ_MATRIX_SIZE(ddpg_pt1_layer1_output),
           .weights = ddpg_pt1_layer1_weights,
           .bias = ddpg_pt1_layer1_bias,
           .output = ddpg_pt1_layer1_output},
    [1] = {.activation_function = activation_ReLU,
           .number_of_neurons = DDPG_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER,
           .number_of_inputs = DDPG_PT1_NUMBER_OF_NEURONS_IN_FIRST_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(ddpg_pt1_layer2_weights),
           .length_of_bias = UZ_MATRIX_SIZE(ddpg_pt1_layer2_bias),
           .length_of_output = UZ_MATRIX_SIZE(ddpg_pt1_layer2_output),
           .weights = ddpg_pt1_layer2_weights,
           .bias = ddpg_pt1_layer2_bias,
           .output = ddpg_pt1_layer2_output},
    [2] = {.activation_function = activation_tanh,
           .number_of_neurons = DDPG_PT1_NUMBER_OF_OUTPUTS,
           .number_of_inputs = DDPG_PT1_NUMBER_OF_NEURONS_IN_SECOND_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(ddpg_pt1_layer3_weights),
           .length_of_bias = UZ_MATRIX_SIZE(ddpg_pt1_layer3_bias),
           .length_of_output = UZ_MATRIX_SIZE(ddpg_pt1_layer3_output),
           .weights = ddpg_pt1_layer3_weights,
           .bias = ddpg_pt1_layer3_bias,
           .output = ddpg_pt1_layer3_output},
};

static const float ddpg_pt1_eval_references[DDPG_PT1_EVAL_EPISODES] = {-1.0, 0.0, 0.5, 0.1, 0.2, 1.0};

void setUp(void)
{
}

void tearDown(void)
{
}

static float ddpg_pt1_clamp_action(float action)
{
    if (action > DDPG_PT1_ACTION_MAX)
    {
        return DDPG_PT1_ACTION_MAX;
    }
    if (action < DDPG_PT1_ACTION_MIN)
    {
        return DDPG_PT1_ACTION_MIN;
    }
    return action;
}

static float ddpg_pt1_update(float y, float input)
{
    const float alpha = expf(-DDPG_PT1_SAMPLE_TIME_S / DDPG_PT1_TIME_CONSTANT_S);
    return (alpha * y) + ((1.0f - alpha) * DDPG_PT1_GAIN * input);
}

static float ddpg_pt1_reward(float y, float reference)
{
    const float error = reference - y;
    return -error * error;
}

static void ddpg_pt1_write_csv_header(FILE *file)
{
    fprintf(file, "time;episode;episode_k;y;reference;error;action_value;reward;");
    fprintf(file, "exploration_rate;terminated;truncated;done\n");
}

static void ddpg_pt1_write_csv_step(FILE *file,
                                    uint32_t time,
                                    uint32_t episode,
                                    uint32_t episode_k,
                                    float y,
                                    float reference,
                                    float action_value,
                                    float reward,
                                    float truncated)
{
    fprintf(file,
            "%lu;%lu;%lu;%.9g;%.9g;%.9g;%.9g;%.9g;%.9g;%.9g;%.9g;%.9g\n",
            (unsigned long)time,
            (unsigned long)episode,
            (unsigned long)episode_k,
            (double)y,
            (double)reference,
            (double)(reference - y),
            (double)action_value,
            (double)reward,
            0.0,
            0.0,
            (double)truncated,
            (double)truncated);
}

void test_uz_ddpg_pt1_eval_export_to_csv(void)
{
    uz_matrix_t *input = uz_matrix_init(&ddpg_pt1_input_matrix,
                                        ddpg_pt1_input_data,
                                        UZ_MATRIX_SIZE(ddpg_pt1_input_data),
                                        1U,
                                        DDPG_PT1_NUMBER_OF_INPUTS);
    uz_nn_t *network = uz_nn_init(ddpg_pt1_layer_config, DDPG_PT1_NUMBER_OF_LAYERS);
    FILE *file = fopen(DDPG_PT1_EVAL_LOG_PATH, "w");
    TEST_ASSERT_NOT_NULL(file);
    ddpg_pt1_write_csv_header(file);

    uint32_t time = 0U;
    for (uint32_t episode_index = 0U; episode_index < DDPG_PT1_EVAL_EPISODES; episode_index++)
    {
        float y = 0.0f;
        const float reference = ddpg_pt1_eval_references[episode_index];

        for (uint32_t episode_k = 0U; episode_k < DDPG_PT1_STEPS_PER_EPISODE; episode_k++)
        {
            ddpg_pt1_input_data[0] = y;
            ddpg_pt1_input_data[1] = reference;
            uz_nn_ff(network, input);

            uz_matrix_t *actor_output = uz_nn_get_output_data(network);
            const float action_value = ddpg_pt1_clamp_action(
                uz_matrix_get_element_zero_based(actor_output, 0U, 0U));

            const float next_y = ddpg_pt1_update(y, action_value);
            const float reward = ddpg_pt1_reward(next_y, reference);
            const float truncated = (episode_k + 1U) >= DDPG_PT1_STEPS_PER_EPISODE ? 1.0f : 0.0f;

            ddpg_pt1_write_csv_step(file,
                                    time,
                                    episode_index + 1U,
                                    episode_k,
                                    y,
                                    reference,
                                    action_value,
                                    reward,
                                    truncated);

            y = next_y;
            time++;
        }
    }

    TEST_ASSERT_EQUAL_INT(0, fclose(file));
}

#endif
