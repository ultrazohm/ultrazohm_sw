#ifdef TEST

#include "unity.h"

#include "uz_environment_pt1.h"
#include "export_array.h"
#include "uz_integrator.h"
#include "uz_matrix.h"
#include "uz_dqn.h"
#include "uz_dqn_expirience_buffer.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_array.h"
#include "uz_matrix.h"
#include "uz_mtwister.h"
#include "uz_environment_bitflip.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "export_array.h"

void save_values(float savecritic[], float savetarget[], float critic[], float target[], uint32_t step, uint32_t size);

void setUp(void)
{
}

void tearDown(void)
{
}

#define EXPERIENCE_BUFFER_LENGTH 5000U
#define MINIBATCHSIZE 8U
#define NUMBER_OF_EPOCHS 200U
#define TARGET_UPDATE_FREQUENCY 200U
// nn
#define NUMBER_OF_INPUTS 2U
#define NUMBER_OF_OUTPUTS 3U
#define NUMBER_OF_HIDDEN_LAYER 2U
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 128U
#define NUMBEROFTESTSTEPS 50U

float discountfact = 0.99f;
float lernrate = 0.002f;

float epsilon_start = 0.99f;
float epsilon_min = 0.0000000001f;
float epsilon_decay = 0.0001f;

// adam
float m1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0.0f};
float m2[NUMBER_OF_OUTPUTS + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0.0f};
float v1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0.0f};
float v2[NUMBER_OF_OUTPUTS + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0.0f};

// debug stuff
float Q_Target[NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS] = {0.0f};
float Q_Critic[NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS] = {0.0f};
float loss[NUMBER_OF_EPOCHS] = {0.0f};
float cumreward[NUMBER_OF_EPOCHS] = {0.0f};
float globalrewardr[NUMBER_OF_EPOCHS] = {0.0f};
float epsilonovertime[NUMBER_OF_EPOCHS] = {0.0f};
float cumreward_noexpl[NUMBEROFTESTSTEPS] = {0.0f};
// dqn
float X_dat[NUMBER_OF_INPUTS] = {0.0f};
float X1_dat[NUMBER_OF_INPUTS] = {0.0f};
// target
float ts_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float ts_2[NUMBER_OF_OUTPUTS] = {0};

float tx[NUMBER_OF_INPUTS] = {0};
float tw_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float tb_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float ty_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float tw_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};
float tb_2[NUMBER_OF_OUTPUTS] = {0};
float ty_2[NUMBER_OF_OUTPUTS] = {0};

// copy
float copy_ts_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float copy_ts_2[NUMBER_OF_OUTPUTS] = {0};

float copy_tx[NUMBER_OF_INPUTS] = {0};
float copy_tw_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float copy_tb_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float copy_ty_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float copy_tw_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};
float copy_tb_2[NUMBER_OF_OUTPUTS] = {0};
float copy_ty_2[NUMBER_OF_OUTPUTS] = {0};
// critic
float cs_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float cs_2[NUMBER_OF_OUTPUTS] = {0};

// deltas
float delta_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float delta_2[NUMBER_OF_OUTPUTS] = {0};

// cache gradients, Gräße entspricht delta des aktuellen layers * größe des Outputs des vorherigen layers
float cacheg_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0};
float cacheg_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};

// Gradienten
float g_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0};
float g_2[NUMBER_OF_OUTPUTS + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};

float cx[NUMBER_OF_INPUTS] = {0};
float creference_output[NUMBER_OF_OUTPUTS] = {0};

float cw_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0.0f};
float cb_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0.0f};
float cy_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0.0f};

float cw_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0.0f};
float cb_2[NUMBER_OF_OUTPUTS] = {0.0f};
float cy_2[NUMBER_OF_OUTPUTS] = {0.0f};

// error
float e_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0.0f};
float e_2[NUMBER_OF_OUTPUTS] = {0.0f};

// Temporary buffer storage

float T1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};
float T2[4] = {0};

// stuff for buffer
float reward[EXPERIENCE_BUFFER_LENGTH] = {0.0f};
uint32_t action[EXPERIENCE_BUFFER_LENGTH] = {0};
float observation[NUMBER_OF_INPUTS * EXPERIENCE_BUFFER_LENGTH] = {0.0f};
float observation1[NUMBER_OF_INPUTS * EXPERIENCE_BUFFER_LENGTH] = {0.0f};
float vecobs[NUMBER_OF_INPUTS] = {0.0f};
float vecobs1[NUMBER_OF_INPUTS] = {0.0f};

// config random

// config target
struct uz_nn_layer_config config_target[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(tw_1),
        .length_of_bias = UZ_MATRIX_SIZE(tb_1),
        .length_of_output = UZ_MATRIX_SIZE(ty_1),
        .length_of_sumout = UZ_MATRIX_SIZE(ts_1),
        .weights = tw_1,
        .bias = tb_1,
        .output = ty_1,
        .sumout = ts_1},
    [1] = {.activation_function = activation_linear, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .length_of_weights = UZ_MATRIX_SIZE(tw_2), .length_of_bias = UZ_MATRIX_SIZE(tb_2), .length_of_output = UZ_MATRIX_SIZE(ty_2), .length_of_sumout = UZ_MATRIX_SIZE(ts_2), .weights = tw_2, .bias = tb_2, .output = ty_2, .sumout = ts_2}};

// config copy
struct uz_nn_layer_config config_copy[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(copy_tw_1),
        .length_of_bias = UZ_MATRIX_SIZE(copy_tb_1),
        .length_of_output = UZ_MATRIX_SIZE(copy_ty_1),
        .length_of_sumout = UZ_MATRIX_SIZE(copy_ts_1),
        .weights = copy_tw_1,
        .bias = copy_tb_1,
        .output = copy_ty_1,
        .sumout = copy_ts_1},
    [1] = {.activation_function = activation_linear, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .length_of_weights = UZ_MATRIX_SIZE(copy_tw_2), .length_of_bias = UZ_MATRIX_SIZE(copy_tb_2), .length_of_output = UZ_MATRIX_SIZE(copy_ty_2), .length_of_sumout = UZ_MATRIX_SIZE(copy_ts_2), .weights = copy_tw_2, .bias = copy_tb_2, .output = copy_ty_2, .sumout = copy_ts_2}};

// config critic
struct uz_nn_layer_config config_critic[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_cachegradcolumns = NUMBER_OF_INPUTS,
        .number_of_temporaryrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_temporarycolumns = NUMBER_OF_OUTPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(cw_1),
        .length_of_bias = UZ_MATRIX_SIZE(cb_1),
        .length_of_output = UZ_MATRIX_SIZE(cy_1),
        .length_of_sumout = UZ_MATRIX_SIZE(cs_1),
        .length_of_delta = UZ_MATRIX_SIZE(delta_1),
        .length_of_error = UZ_MATRIX_SIZE(e_1),
        .length_of_gradients = UZ_MATRIX_SIZE(g_1),
        .length_of_temporarybackprop = UZ_MATRIX_SIZE(T1),
        .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_1),
        .m = m1,
        .v = v1,
        .weights = cw_1,
        .bias = cb_1,
        .output = cy_1,
        .sumout = cs_1,
        .delta = delta_1,
        .temporarybackprop = T1,
        .gradients = g_1,
        .cachegradients = cacheg_1,
        .error = e_1},
    [1] = {.activation_function = activation_linear, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .number_of_cachegradrows = NUMBER_OF_OUTPUTS, .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .number_of_temporaryrows = 2, .number_of_temporarycolumns = 2, .length_of_weights = UZ_MATRIX_SIZE(cw_2), .length_of_bias = UZ_MATRIX_SIZE(cb_2), .length_of_output = UZ_MATRIX_SIZE(cy_2), .length_of_sumout = UZ_MATRIX_SIZE(cs_2), .length_of_delta = UZ_MATRIX_SIZE(delta_2), .length_of_gradients = UZ_MATRIX_SIZE(g_2), .length_of_error = UZ_MATRIX_SIZE(e_2), .length_of_temporarybackprop = UZ_MATRIX_SIZE(T2), .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_2), .m = m2, .v = v2, .weights = cw_2, .bias = cb_2, .output = cy_2, .sumout = cs_2, .delta = delta_2, .temporarybackprop = T2, .gradients = g_2, .cachegradients = cacheg_2, .error = e_2}};

// config buffer
struct uz_dqn_experience_replay_config configbuffer = {
    .length_of_buffer = EXPERIENCE_BUFFER_LENGTH,
    .columns_of_observations = NUMBER_OF_INPUTS,
    .reward = reward,
    .observations = observation,
    .observations1 = observation1,
    .obsvec = vecobs,
    .obsvec1 = vecobs1,
    .actions = action};

#define DAUER 1000
void test_uz_environment_pt1_one_input(void)
{
    float array[2] = {0};
    float gain = 1.0f;
    float time_constant = 0.005f;
    float integration_time = 0.0001f;
    uz_environment_pt1_t *pt1 = uz_environment_pt1_init(gain, time_constant, integration_time, array);
    float current_value[DAUER] = {0.0f};
    for (uint32_t i = 0; i < DAUER; i++)
    {
        current_value[i] = uz_environment_pt1_step(pt1, 1.0f);
    }
    char filepath[] = "test/uz/uz_environment_pt1/pt1.csv";
    export_histogram(current_value, DAUER, filepath);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, current_value[DAUER - 1]);
}

void test_uz_environment_pt1_dqn_zero(void)
{
    float array[2] = {0};
    float gain = 1.0f;
    float time_constant = 0.5f;
    float integration_time = 0.0001f;
    uz_environment_pt1_t *pt1 = uz_environment_pt1_init(gain, time_constant, integration_time, array);
    float current_value[100000] = {0.0f};
    for (uint32_t i = 0; i < 100000; i++)
    {
        uz_environment_pt1_dqn_step(pt1, 0U, 0.0f);
        current_value[i] = uz_environment_pt1_get_output(pt1);
    }
    // char filepath[] = "test/uz/uz_environment_pt1/pt1.csv";
    // export_histogram(current_value, 100000, filepath);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, current_value[100000 - 1]);
}

void test_uz_environment_pt1_dqn_one(void)
{
    float array[2] = {0};
    float gain = 1.0f;
    float time_constant = 0.5f;
    float integration_time = 0.0001f;
    uz_environment_pt1_t *pt1 = uz_environment_pt1_init(gain, time_constant, integration_time, array);
    float current_value[100000] = {0.0f};
    for (uint32_t i = 0; i < 100000; i++)
    {
        uz_environment_pt1_dqn_step(pt1, 1U, 0.0f);
        current_value[i] = uz_environment_pt1_get_output(pt1);
    }
    // char filepath[] = "test/uz/uz_environment_pt1/pt1.csv";
    //  export_histogram(current_value, 100000, filepath);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, current_value[100000 - 1]);
}

void test_uz_environment_pt1_dqn_two(void)
{
    float array[2] = {0};
    float gain = 1.0f;
    float time_constant = 0.5f;
    float integration_time = 0.0001f;
    uz_environment_pt1_t *pt1 = uz_environment_pt1_init(gain, time_constant, integration_time, array);
    float current_value[100000] = {0.0f};
    for (uint32_t i = 0; i < 100000; i++)
    {
        uz_environment_pt1_dqn_step(pt1, 2U, 0.0f);
        current_value[i] = uz_environment_pt1_get_output(pt1);
    }
    //  char filepath[] = "test/uz/uz_environment_pt1/pt1.csv";
    // export_histogram(current_value, 100000, filepath);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0f, current_value[100000 - 1]);
}

void test_dqn_pt1_synchron(void)
{
    float targsmoothfact = 0.05f;
    float error[NUMBER_OF_OUTPUTS] = {0.0f};
    float array[2] = {0};
    float gain = 1.0f;
    float time_constant = 0.005f;
    float integration_time = 0.0001f;
    uz_environment_pt1_t *pt1 = uz_environment_pt1_init(gain, time_constant, integration_time, array);
    uz_mtwister_t *random_generator = uz_mtwister_init(10U);
    uz_dqn_t *testdqn2 = uz_dqn_init(X_dat, X1_dat, lernrate, discountfact, config_critic, config_target, 2U, NUMBER_OF_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH, MINIBATCHSIZE, TARGET_UPDATE_FREQUENCY, targsmoothfact, epsilon_start, epsilon_min, epsilon_decay, periodic, error,config_copy);
    ///////////////// Training loop///////////////////////////////////////////////////////////////////////////////////////////
    for (uint32_t epoch = 0; epoch < NUMBER_OF_EPOCHS; epoch++)
    {
        float setpoint = uz_mtwister_random_uniform_float(random_generator);
        uz_environment_pt1_reset(pt1);
        loss[epoch] = uz_environment_pt1_step_one_episode(testdqn2, 500U, true, pt1, setpoint, false, NULL, NULL, NULL,10);
        cumreward[epoch] = uz_environment_pt1_get_cumulative_reward(pt1);
        if (epoch == 0)
        {
            globalrewardr[epoch] = uz_environment_pt1_get_cumulative_reward(pt1);
        }
        else
        {
            globalrewardr[epoch] = 0.99f * globalrewardr[epoch - 1] + 0.01f * uz_environment_pt1_get_cumulative_reward(pt1);
        }
        epsilonovertime[epoch] = uz_dqn_get_epsilon(testdqn2);
        save_values(Q_Critic, Q_Target, cy_2, ty_2, epoch, NUMBER_OF_OUTPUTS);
    }

    uz_dqn_set_epsilon(testdqn2, 0.0f, 0.0f, 0.0f);

    float log_error[1000U] = {0.0f};
    float log_input[1000U] = {0.0f};
    float log_output[1000U] = {1.0f};
    uz_environment_pt1_reset(pt1);
    uz_environment_pt1_step_one_episode(testdqn2, 1000U, false, pt1, 0.5f, true, log_error, log_input, log_output,10);

    char filepath[] = "test/uz/uz_environment_pt1/pt1_dqn_output.csv";
    char filepath1[] = "test/uz/uz_environment_pt1/pt1_dqn_input.csv";
    char filepath2[] = "test/uz/uz_environment_pt1/pt1_dqn_error.csv";
    export_histogram(log_output, 1000U, filepath);
    export_histogram(log_input, 1000U, filepath1);
    export_histogram(log_error, 1000U, filepath2);

    exportFloatArrayToCSV("test/uz/uz_environment_pt1/loss256_clipped.csv", loss, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/cumreward256_clipped.csv", cumreward, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/QTarget.csv", Q_Target, NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/QCritic.csv", Q_Critic, NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/globalrewardr.csv", globalrewardr, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/epsilon256_clipped.csv", epsilonovertime, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/cumreward256_nur_action.csv", cumreward_noexpl, NUMBEROFTESTSTEPS);
    FILE *f = fopen("test/uz/uz_environment_pt1/hyperparam.txt", "w"); // open the file for writing
    if (f != NULL)                                                     // check for success
    {
        fprintf(f, "Learnrate, Discount Factor,Epsilon_start,Epsilon_min,Epsilon_decay,Hidden Layer,Bufferlength,Minibatchsize,Epochen,Targetupdatefrequency,Numberofbits,Numberofneuronsinhiddenlayer \n");
        fprintf(f, "%.6f,%.6f,%.6f,%.6f,%.6f,%d,%d,%d,%d,%d,%d,%d\n", (double)lernrate, (double)discountfact, (double)epsilon_start, (double)epsilon_min, (double)epsilon_decay, NUMBER_OF_HIDDEN_LAYER, EXPERIENCE_BUFFER_LENGTH, MINIBATCHSIZE, NUMBER_OF_EPOCHS, TARGET_UPDATE_FREQUENCY, 2,
                NUMBER_OF_NEURONS_IN_HIDDEN_LAYER);
        fclose(f); // close the file
        f = NULL;  // set file handle to null since f is no longer valid
    }
}

void test_dqn_pt1_asynchron(void)
{
    float targsmoothfact = 0.05f;
    float error[NUMBER_OF_OUTPUTS] = {0.0f};
    float array[2] = {0};
    float gain = 1.0f;
    float time_constant = 0.005f;
    float integration_time = 0.0001f;
    uint32_t max_steps=500U;
    uz_environment_pt1_t *pt1 = uz_environment_pt1_init(gain, time_constant, integration_time, array);
    uz_mtwister_t *random_generator = uz_mtwister_init(10U);
    uz_dqn_t *testdqn2 = uz_dqn_init(X_dat, X1_dat, lernrate, discountfact, config_critic, config_target, 2U, NUMBER_OF_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH, MINIBATCHSIZE, TARGET_UPDATE_FREQUENCY, targsmoothfact, epsilon_start, epsilon_min, epsilon_decay, periodic, error,config_copy);
    ///////////////// Training loop///////////////////////////////////////////////////////////////////////////////////////////
    bool first_episode = true;
    uz_matrix_t *env_state =NULL;
    for (uint32_t epoch = 0; epoch < NUMBER_OF_EPOCHS; epoch++)
    {
        float setpoint = uz_mtwister_random_uniform_float(random_generator);
        uz_environment_pt1_reset(pt1);
        // Step Environment x-times
        // each y-steps, do control
        float cum_loss = 0.0f;
        /////////////////////////////////////////// Start episode loop
        for (uint32_t t = 0; t < max_steps; t++)
        {
            if (first_episode)
            {
                first_episode = false;
            }
            else
            {
                env_state = uz_environment_pt1_get_state(pt1);
                // Sample environment at k+1
                uz_dqn_sample_observation_k_1(testdqn2, env_state);
                float reward = uz_environment_pt1_get_reward(pt1);
                uz_dqn_set_reward(testdqn2, reward);
                uz_dqn_push_to_buffer(testdqn2);
            }

            // sample observation of the environment at k=0
            env_state = uz_environment_pt1_get_state(pt1);
            uz_dqn_sample_observation_k_0(testdqn2, env_state);
            uint32_t action = uz_dqn_determine_action(testdqn2);
            for (uint32_t time_step = 0; time_step < 10; time_step++)
            {
                uz_environment_pt1_dqn_step(pt1, action, setpoint);
            }
            cum_loss = uz_dqn_update(testdqn2);
        }
        cumreward[epoch] = uz_environment_pt1_get_cumulative_reward(pt1);
        if (epoch == 0)
        {
            globalrewardr[epoch] = uz_environment_pt1_get_cumulative_reward(pt1);
        }
        else
        {
            globalrewardr[epoch] = 0.99f * globalrewardr[epoch - 1] + 0.01f * uz_environment_pt1_get_cumulative_reward(pt1);
        }
        epsilonovertime[epoch] = uz_dqn_get_epsilon(testdqn2);
        save_values(Q_Critic, Q_Target, cy_2, ty_2, epoch, NUMBER_OF_OUTPUTS);
    }

    uz_dqn_set_epsilon(testdqn2, 0.0f, 0.0f, 0.0f);

    float log_error[1000U] = {0.0f};
    float log_input[1000U] = {0.0f};
    float log_output[1000U] = {1.0f};
    uz_environment_pt1_reset(pt1);
    uz_environment_pt1_step_one_episode(testdqn2, 1000U, false, pt1, 0.5f, true, log_error, log_input, log_output,10);

    char filepath[] = "test/uz/uz_environment_pt1/pt1_asyn_dqn_output.csv";
    char filepath1[] = "test/uz/uz_environment_pt1/pt1_asyn_dqn_input.csv";
    char filepath2[] = "test/uz/uz_environment_pt1/pt1_asyn_dqn_error.csv";
    export_histogram(log_output, 1000U, filepath);
    export_histogram(log_input, 1000U, filepath1);
    export_histogram(log_error, 1000U, filepath2);

    exportFloatArrayToCSV("test/uz/uz_environment_pt1/asyn_loss256_clipped.csv", loss, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/asyn_cumreward256_clipped.csv", cumreward, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/asyn_QTarget.csv", Q_Target, NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/asyn_QCritic.csv", Q_Critic, NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/asyn_globalrewardr.csv", globalrewardr, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/asyn_epsilon256_clipped.csv", epsilonovertime, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_environment_pt1/asyn_cumreward256_nur_action.csv", cumreward_noexpl, NUMBEROFTESTSTEPS);
    FILE *f = fopen("test/uz/uz_environment_pt1/asyn_hyperparam.txt", "w"); // open the file for writing
    if (f != NULL)                                                     // check for success
    {
        fprintf(f, "Learnrate, Discount Factor,Epsilon_start,Epsilon_min,Epsilon_decay,Hidden Layer,Bufferlength,Minibatchsize,Epochen,Targetupdatefrequency,Numberofbits,Numberofneuronsinhiddenlayer \n");
        fprintf(f, "%.6f,%.6f,%.6f,%.6f,%.6f,%d,%d,%d,%d,%d,%d,%d\n", (double)lernrate, (double)discountfact, (double)epsilon_start, (double)epsilon_min, (double)epsilon_decay, NUMBER_OF_HIDDEN_LAYER, EXPERIENCE_BUFFER_LENGTH, MINIBATCHSIZE, NUMBER_OF_EPOCHS, TARGET_UPDATE_FREQUENCY, 2,
                NUMBER_OF_NEURONS_IN_HIDDEN_LAYER);
        fclose(f); // close the file
        f = NULL;  // set file handle to null since f is no longer valid
    }
}

void save_values(float savecritic[], float savetarget[], float critic[], float target[], uint32_t step, uint32_t size)
{
    // Save values from the current step into the larger arrays
    for (uint32_t i = 0U; i < size; i++)
    {
        savecritic[step * size + i] = critic[i];
        savetarget[step * size + i] = target[i];
    }
}

#endif // TEST
