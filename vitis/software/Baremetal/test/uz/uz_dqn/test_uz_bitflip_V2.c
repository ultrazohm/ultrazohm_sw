#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_dqn.h"
#include "uz_dqn_expirience_buffer.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_array.h"
#include "uz_matrix.h"
#include "uz_prng.h"
#include "uz_environment_bitflip.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "export_array.h"

#include "uz_prng.h"
#include "../uz_prng_squares/uz_prng_squares.h"
#include "../uz_prng_halton/uz_prng_halton.h"
#include "../uz_prng_mtwister/uz_prng_mtwister.h"
#include "../uz_prng_pcg/uz_prng_pcg.h"
#include "../uz_prng_xoshiro/uz_prng_xoshiro.h"
#include "mt19937.h"
#include "splitmix64.h"
#include "xoshiro128plusplus.h"

void uz_nn_trained_export(uz_nn_t *self);

// buffer
#define EXPERIENCE_BUFFER_LENGTH 50000U
#define MINIBATCHSIZE 8U
#define NUMBER_OF_EPOCHS 5000U
#define TARGET_UPDATE_FREQUENCY 20U
// nn
#define NUMBEROFBITS 4U
#define NUMBER_OF_INPUTS 8U
#define NUMBER_OF_OUTPUTS 4U
#define NUMBER_OF_HIDDEN_LAYER 2U
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 128U
#define NUMBEROFTESTSTEPS 50U

float discountfact = 0.99f;
float lernrate = 0.002f;

float epsilon_start = 0.99f;
float epsilon_min = 0.0000000001f;
float epsilon_decay = 0.001f;

// random array
uint32_t array[NUMBEROFBITS] = {0U, 0U, 0U, 0U};
uint32_t tararray[NUMBEROFBITS] = {1U, 1U, 1U, 1U};
float inarray[NUMBER_OF_INPUTS] = {0.0f};
// conf envrionment

// adam
float m1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0.0f};
float m2[NUMBER_OF_OUTPUTS + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0.0f};
float v1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0.0f};
float v2[NUMBER_OF_OUTPUTS + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0.0f};

struct uz_dqn_environment_config configenv = {
    .bitlength = NUMBEROFBITS,
    .bitarray = array,
    .targetarray = tararray,
    .inarray = inarray,
    .max_steps = NUMBEROFBITS + 3};
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
void setUp(void)
{
}

void tearDown(void)
{
}
// void test_uz_dqn_init(void)
// {
//     uz_dqn_t *testdqn = uz_dqn_init(X_dat, lernrate, discountfact, config_critic, config_target, 2U, NUMBER_OF_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH, configenv);
//     float targsmoothfact = 0.05f;
//     uz_nn_target_update(testdqn->critic, testdqn->critic_target_net, smoothing, targsmoothfact);
// }

void test_dqn_bitflip(void)
{
    float targsmoothfact = 0.05f;
    uz_prng_t *environment_twister = uz_prng_init(uz_prng_generator_mtwister, uz_prng_float_scale_fp_multiply, 41850483U);
    float error[NUMBER_OF_OUTPUTS] = {0.0f};

    uz_environment_bitflip_t *env = uz_environment_bitflip_init(configenv);

    struct uz_dqn_config_t dqn_config =
        {
            .observation_data = X_dat,
            .observation_k1_data = X1_dat,
            .buffer_config = configbuffer,
            .length_of_buffer = EXPERIENCE_BUFFER_LENGTH,
            .error = error,
            .training = {
                .learn_rate = lernrate,
                .discount_factor = discountfact,
                .minibatch_size = MINIBATCHSIZE,
                .target_update_frequency = TARGET_UPDATE_FREQUENCY,
                .target_smooth_factor = targsmoothfact,
                .update_mechanism = periodic},
            .network = {.config_critic = config_critic, .config_target = config_critic, .config_copy = config_copy, .number_of_layer = NUMBER_OF_HIDDEN_LAYER},
            .exploration = {.epsilon_start = epsilon_start, .epsilon_min = epsilon_min, .epsilon_decay = epsilon_decay},
            .prng_init = {.random_seed = 9U, .uz_prng_type = uz_prng_generator_mtwister},
            .prng_exploration = {.random_seed = 9U, .uz_prng_type = uz_prng_generator_halton},
            .prng_training = {.random_seed = 7U, .uz_prng_type = uz_prng_generator_mtwister}};
    uz_dqn_t *testdqn2 = uz_dqn_init(dqn_config);
    //  prefill buffer
    //  do{
    //  uz_dqn_environment_reset(testdqn2->env,&testdqn2->randinstance->seedRand);
    //  uz_dqn_sample_bitenv(testdqn2);
    //  } while ((!testdqn2->experience_buffer->counterisfull) && (testdqn2->experience_buffer->head< (3 * MINIBATCHSIZE)));
    //  testdqn2->env->epsilon_start = configenv.epsilon_start;
    for (uint32_t epoch = 0; epoch < NUMBER_OF_EPOCHS; epoch++)
    {
        uz_environment_bitflip_reset(env, environment_twister);
        loss[epoch] = uz_environment_bitflip_step_one_episode(testdqn2, configenv.max_steps, true, env);
        cumreward[epoch] = uz_environment_bitflip_get_cumulative_reward(env);
        if (epoch == 0)
        {
            globalrewardr[epoch] = uz_environment_bitflip_get_cumulative_reward(env);
        }
        else
        {
            globalrewardr[epoch] = 0.99f * globalrewardr[epoch - 1] + 0.01f * uz_environment_bitflip_get_cumulative_reward(env);
        }
        epsilonovertime[epoch] = uz_dqn_get_epsilon(testdqn2);
        uz_environment_bitflip_save_values(Q_Critic, Q_Target, cy_2, ty_2, epoch, NUMBER_OF_OUTPUTS);
    }

    uz_dqn_set_epsilon(testdqn2, 0.0f, 0.0f, 0.0f);
    for (size_t i = 0; i < NUMBEROFTESTSTEPS; i++)
    {
        uz_environment_bitflip_reset(env, environment_twister);
        uz_environment_bitflip_step_one_episode(testdqn2, configenv.max_steps, false, env);
        cumreward_noexpl[i] = uz_environment_bitflip_get_cumulative_reward(env);
    }

    exportFloatArrayToCSV("test/uz/uz_dqn/loss256_clipped.csv", loss, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_dqn/cumreward256_clipped.csv", cumreward, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_dqn/QTarget.csv", Q_Target, NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS);
    exportFloatArrayToCSV("test/uz/uz_dqn/QCritic.csv", Q_Critic, NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS);
    exportFloatArrayToCSV("test/uz/uz_dqn/globalrewardr.csv", globalrewardr, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_dqn/epsilon256_clipped.csv", epsilonovertime, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_dqn/cumreward256_nur_action.csv", cumreward_noexpl, NUMBEROFTESTSTEPS);
    FILE *f = fopen("test/uz/uz_dqn/hyperparam.txt", "w"); // open the file for writing
    if (f != NULL)                                         // check for success
    {
        fprintf(f, "Learnrate, Discount Factor,Epsilon_start,Epsilon_min,Epsilon_decay,Hidden Layer,Bufferlength,Minibatchsize,Epochen,Targetupdatefrequency,Numberofbits,Numberofneuronsinhiddenlayer \n");
        fprintf(f, "%.6f,%.6f,%.6f,%.6f,%.6f,%d,%d,%d,%d,%d,%d,%d\n", (double)lernrate, (double)discountfact, (double)epsilon_start, (double)epsilon_min, (double)epsilon_decay, NUMBER_OF_HIDDEN_LAYER, EXPERIENCE_BUFFER_LENGTH, MINIBATCHSIZE, NUMBER_OF_EPOCHS, TARGET_UPDATE_FREQUENCY, NUMBEROFBITS,
                NUMBER_OF_NEURONS_IN_HIDDEN_LAYER);
        fclose(f); // close the file
        f = NULL;  // set file handle to null since f is no longer valid
    }
    uz_nn_trained_export(uz_dqn_get_critic_net(testdqn2));

    for (size_t i = 0; i < NUMBEROFTESTSTEPS; i++)
    {
        TEST_ASSERT_EQUAL_FLOAT(1.0f, cumreward_noexpl[i]);
    }
}

void uz_nn_trained_export(uz_nn_t *self)
{
    char *fname = "test/uz/uz_dqn/trained_layer1_weights.csv";
    uz_nn_layer_matrix_export(uz_nn_get_weight_matrix(self, 1U), fname);
    char *fname1 = "test/uz/uz_dqn/trained_layer2_weights.csv";
    uz_nn_layer_matrix_export(uz_nn_get_weight_matrix(self, 2U), fname1);
    char *fname3 = "test/uz/uz_dqn/trained_layer1_bias.csv";
    uz_nn_layer_matrix_export(uz_nn_get_bias_matrix(self, 1U), fname3);
    char *fname4 = "test/uz/uz_dqn/trained_layer2_bias.csv";
    uz_nn_layer_matrix_export(uz_nn_get_bias_matrix(self, 2U), fname4);
}

#endif // TEST
