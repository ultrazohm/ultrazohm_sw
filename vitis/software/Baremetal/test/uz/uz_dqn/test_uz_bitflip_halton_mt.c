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

#include <assert.h>

// void test_multi_export(void)
// {
//     float data_1[5] = {1, 2, 3, 4, 5};
//     float data_2[5] = {5, 4, 3, 2, 1};
//     uz_array_float_t export_array[2] = {
//         {.data = data_1, .length = UZ_ARRAY_SIZE(data_1)},
//         {.data = data_2, .length = UZ_ARRAY_SIZE(data_2)}};
//     char header[] = {"Test 1,Test 2\n"};
//     char absolute_path[] = "test/uz/uz_dqn/export_test2.csv";
//     export_helper_float2(export_array, 2, header, absolute_path);
// }

void export_abitrary_number_of_arrays(uz_array_float_t **export_array, size_t length_of_export_array, char table_header[], char absolute_path[], uint32_t index);
void train_bitflip(uint32_t number_of_epochs, uz_environment_bitflip_t *env, uz_prng_t *env_prng, uz_dqn_t *dqn, uz_array_float_t episode_loss, uz_array_float_t cumulative_reward, uz_array_float_t global_reward_metric, uz_array_float_t epsilon_per_epsiode);

void eval_steps_bitflip(uz_dqn_t *dqn, uz_environment_bitflip_t *env, uz_array_float_t reward_log, uint32_t number_of_eval_episodes, uz_prng_t *prng);

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

struct experiment_config
{
    struct uz_dqn_prng_config_t init_config;
    struct uz_dqn_prng_config_t training_config;
    struct uz_dqn_prng_config_t exploration_config;
    struct uz_dqn_prng_config_t environment_config;
    uint64_t *init_seeds;
    uint64_t *exploration_seeds;
    uint64_t *training_seeds;
    uint64_t *environment_seeds;
    size_t number_of_seeds;
};

uint64_t halton_seed[10] = {13, 17, 19, 23, 29, 31, 37, 41, 43, 47};                                 // 6. to 15. prime number
uint64_t xoshiro_seed[10] = {0, 59994356, 96162775, 58988824, 66869139, 20, 17, 23605, 50, 258116};  // arbitrary numbers with large and small seeds
uint64_t pcg_seed[10] = {0, 59994356, 96162775, 58988824, 66869139, 20, 17, 23605, 50, 258116};      // arbitrary numbers with large and small seeds
uint64_t mtwister_seed[10] = {0, 59994356, 96162775, 58988824, 66869139, 20, 17, 23605, 50, 258116}; // arbitrary numbers with large and small seeds
uint64_t squares_seed[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};                                          // take key's from list
uint64_t environment_seed[10] = {41850483U, 41850483U, 41850483U, 41850483U, 41850483U, 41850483U, 41850483U, 41850483U, 41850483U, 41850483U};

void do_experiment(char training_absolute_path[], char eval_absolute_path[], struct experiment_config);
struct experiment_config get_exp_config(enum uz_prng_generator init_generator, enum uz_prng_generator exploration_generator, enum uz_prng_generator training_generator, enum uz_prng_generator env_generator);

void test_dqn_bitflip_halton(void)
{
    char training_absolute_path[] = "test/uz/uz_dqn/halton2_training";
    char eval_absolute_path[] = "test/uz/uz_dqn/halton2_eval";
    struct experiment_config exp = get_exp_config(uz_prng_generator_mtwister, uz_prng_generator_mtwister, uz_prng_generator_mtwister, uz_prng_generator_mtwister);
    do_experiment(training_absolute_path, eval_absolute_path, exp);
}

struct experiment_config get_exp_config(enum uz_prng_generator init_generator, enum uz_prng_generator exploration_generator, enum uz_prng_generator training_generator, enum uz_prng_generator env_generator)
{

    struct experiment_config exp = {0};
    exp.number_of_seeds = 10;

    switch (init_generator)
    {
    case uz_prng_generator_halton:
        exp.init_config.random_seed = halton_seed[0];
        exp.init_config.uz_prng_type = uz_prng_generator_halton;
        exp.init_seeds = halton_seed;
        break;
    case uz_prng_generator_mtwister:
        exp.init_config.random_seed = mtwister_seed[0];
        exp.init_config.uz_prng_type = uz_prng_generator_mtwister;
        exp.init_seeds = mtwister_seed;
        break;
    case uz_prng_generator_squares:
        exp.init_config.random_seed = squares_seed[0];
        exp.init_config.uz_prng_type = uz_prng_generator_squares;
        exp.init_seeds = squares_seed;
        break;
    case uz_prng_generator_pcg:
        exp.init_config.random_seed = pcg_seed[0];
        exp.init_config.uz_prng_type = uz_prng_generator_pcg;
        exp.init_seeds = pcg_seed;
        break;
    case uz_prng_generator_xoshiro:
        exp.init_config.random_seed = xoshiro_seed[0];
        exp.init_config.uz_prng_type = uz_prng_generator_xoshiro;
        exp.init_seeds = xoshiro_seed;
        break;
    default:
        break;
    }

    switch (training_generator)
    {
    case uz_prng_generator_halton:
        exp.training_config.random_seed = halton_seed[0];
        exp.training_config.uz_prng_type = uz_prng_generator_halton;
        exp.training_seeds = halton_seed;
        break;
    case uz_prng_generator_mtwister:
        exp.training_config.random_seed = mtwister_seed[0];
        exp.training_config.uz_prng_type = uz_prng_generator_mtwister;
        exp.training_seeds = mtwister_seed;
        break;
    case uz_prng_generator_squares:
        exp.training_config.random_seed = squares_seed[0];
        exp.training_config.uz_prng_type = uz_prng_generator_squares;
        exp.training_seeds = squares_seed;
        break;
    case uz_prng_generator_pcg:
        exp.training_config.random_seed = pcg_seed[0];
        exp.training_config.uz_prng_type = uz_prng_generator_pcg;
        exp.training_seeds = pcg_seed;
        break;
    case uz_prng_generator_xoshiro:
        exp.training_config.random_seed = xoshiro_seed[0];
        exp.training_config.uz_prng_type = uz_prng_generator_xoshiro;
        exp.training_seeds = xoshiro_seed;
        break;
    default:
        break;
    }

    switch (exploration_generator)
    {
    case uz_prng_generator_halton:
        exp.exploration_config.random_seed = halton_seed[0];
        exp.exploration_config.uz_prng_type = uz_prng_generator_halton;
        exp.exploration_seeds = halton_seed;
        break;
    case uz_prng_generator_mtwister:
        exp.exploration_config.random_seed = mtwister_seed[0];
        exp.exploration_config.uz_prng_type = uz_prng_generator_mtwister;
        exp.exploration_seeds = mtwister_seed;
        break;
    case uz_prng_generator_squares:
        exp.exploration_config.random_seed = squares_seed[0];
        exp.exploration_config.uz_prng_type = uz_prng_generator_squares;
        exp.exploration_seeds = squares_seed;
        break;
    case uz_prng_generator_pcg:
        exp.exploration_config.random_seed = pcg_seed[0];
        exp.exploration_config.uz_prng_type = uz_prng_generator_pcg;
        exp.exploration_seeds = pcg_seed;
        break;
    case uz_prng_generator_xoshiro:
        exp.exploration_config.random_seed = xoshiro_seed[0];
        exp.exploration_config.uz_prng_type = uz_prng_generator_xoshiro;
        exp.exploration_seeds = xoshiro_seed;
        break;
    default:
        break;
    }

    switch (env_generator)
    {
    case uz_prng_generator_halton:
        exp.environment_config.random_seed = halton_seed[0];
        exp.environment_config.uz_prng_type = uz_prng_generator_halton;
        exp.environment_seeds = environment_seed;
        break;
    case uz_prng_generator_mtwister:
        exp.environment_config.random_seed = mtwister_seed[0];
        exp.environment_config.uz_prng_type = uz_prng_generator_mtwister;
        exp.environment_seeds = environment_seed;
        break;
    case uz_prng_generator_squares:
        exp.environment_config.random_seed = squares_seed[0];
        exp.environment_config.uz_prng_type = uz_prng_generator_squares;
        exp.environment_seeds = environment_seed;
        break;
    case uz_prng_generator_pcg:
        exp.environment_config.random_seed = pcg_seed[0];
        exp.environment_config.uz_prng_type = uz_prng_generator_pcg;
        exp.environment_seeds = environment_seed;
        break;
    case uz_prng_generator_xoshiro:
        exp.environment_config.random_seed = xoshiro_seed[0];
        exp.environment_config.uz_prng_type = uz_prng_generator_xoshiro;
        exp.environment_seeds = environment_seed;
        break;
    default:
        break;
    }
    return exp;
}

void do_experiment(char training_absolute_path[], char eval_absolute_path[], struct experiment_config exp)
{
    char training_header[] = {"episode_loss,cumulative_reward,global_reward_metric,epsilon_per_epsiode\n"};
    char eval_header[] = {"cumulative_reward\n"};
    float Q_Target[NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS] = {0.0f};
    float Q_Critic[NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS] = {0.0f};
    float cumreward_noexpl[NUMBEROFTESTSTEPS] = {0.0f};
    uz_array_float_t evaluation_run_reward = {
        .data = cumreward_noexpl,
        .length = UZ_ARRAY_SIZE(cumreward_noexpl)};

    float loss[NUMBER_OF_EPOCHS] = {0.0f};
    float cumreward[NUMBER_OF_EPOCHS] = {0.0f};
    float globalrewardr[NUMBER_OF_EPOCHS] = {0.0f};
    float epsilonovertime[NUMBER_OF_EPOCHS] = {0.0f};
    //
    uz_array_float_t episode_loss = {.data = loss, .length = UZ_ARRAY_SIZE(loss)};
    uz_array_float_t episode_loss_eval = {.data = cumreward_noexpl, .length = UZ_ARRAY_SIZE(cumreward_noexpl)};
    uz_array_float_t cumulative_reward = {.data = cumreward, .length = UZ_ARRAY_SIZE(cumreward)};
    uz_array_float_t global_reward_metric = {.data = globalrewardr, .length = UZ_ARRAY_SIZE(globalrewardr)};
    uz_array_float_t epsilon_per_epsiode = {.data = epsilonovertime, .length = UZ_ARRAY_SIZE(epsilonovertime)};

    uz_array_float_t *training_log[4] = {
        &episode_loss,
        &cumulative_reward,
        &global_reward_metric,
        &epsilon_per_epsiode};
    uz_array_float_t *evaluation_log[1] = {
        &episode_loss_eval};
    float targsmoothfact = 0.05f;
    uz_prng_t *environment_twister = uz_prng_init(exp.environment_config.uz_prng_type, uz_prng_float_scale_fp_multiply, exp.environment_seeds[0]);
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
            .prng_init = exp.init_config,
            .prng_exploration = exp.exploration_config,
            .prng_training = exp.training_config};
    uz_dqn_t *testdqn2 = uz_dqn_init(dqn_config);
    uz_prng_reset(environment_twister, exp.environment_seeds[0]);

    for (uint32_t seed_index = 0; seed_index < exp.number_of_seeds; seed_index++)
    {
        uz_dqn_set_prng_seeds(testdqn2, exp.init_seeds[seed_index], exp.exploration_seeds[seed_index], exp.training_seeds[seed_index]);
        uz_prng_reset(environment_twister, exp.environment_seeds[seed_index]);
        uz_dqn_reset(testdqn2, epsilon_start);
        uz_dqn_set_epsilon(testdqn2, epsilon_start, epsilon_min, epsilon_decay); // Required because epsilon is set to 0 for eval

        train_bitflip(NUMBER_OF_EPOCHS, env, environment_twister, testdqn2, episode_loss, cumulative_reward, global_reward_metric, epsilon_per_epsiode);
        eval_steps_bitflip(testdqn2, env, evaluation_run_reward, NUMBEROFTESTSTEPS, environment_twister);

        export_abitrary_number_of_arrays(training_log, 4, training_header, training_absolute_path, seed_index);
        export_abitrary_number_of_arrays(evaluation_log, 1, eval_header, eval_absolute_path, seed_index);
    }
}

// NUMBER_OF_EPOCHS,
void train_bitflip(uint32_t number_of_epochs, uz_environment_bitflip_t *env, uz_prng_t *env_prng, uz_dqn_t *dqn, uz_array_float_t episode_loss, uz_array_float_t cumulative_reward, uz_array_float_t global_reward_metric, uz_array_float_t epsilon_per_epsiode)
{

    for (uint32_t epoch = 0; epoch < number_of_epochs; epoch++)
    {
        uz_environment_bitflip_reset(env, env_prng);
        episode_loss.data[epoch] = uz_environment_bitflip_step_one_episode(dqn, true, env);
        cumulative_reward.data[epoch] = uz_environment_bitflip_get_cumulative_reward(env);
        if (epoch == 0)
        {
            global_reward_metric.data[epoch] = uz_environment_bitflip_get_cumulative_reward(env);
        }
        else
        {
            global_reward_metric.data[epoch] = 0.99f * global_reward_metric.data[epoch - 1] + 0.01f * uz_environment_bitflip_get_cumulative_reward(env);
        }
        epsilon_per_epsiode.data[epoch] = uz_dqn_get_epsilon(dqn);
    }
}

void eval_steps_bitflip(uz_dqn_t *dqn, uz_environment_bitflip_t *env, uz_array_float_t reward_log, uint32_t number_of_eval_episodes, uz_prng_t *prng)
{
    assert(dqn != NULL);
    assert(env != NULL);
    assert(reward_log.length == number_of_eval_episodes);

    uz_dqn_set_epsilon(dqn, 0.0f, 0.0f, 0.0f);
    for (size_t i = 0; i < number_of_eval_episodes; i++)
    {
        uz_environment_bitflip_reset(env, prng);
        uz_environment_bitflip_step_one_episode(dqn, false, env);
        reward_log.data[i] = uz_environment_bitflip_get_cumulative_reward(env);
    }
}

void export_abitrary_number_of_arrays(uz_array_float_t **export_array, size_t length_of_export_array, char table_header[], char absolute_path[], uint32_t index)
{
    assert(export_array != NULL);
    for (size_t i = 0; i < length_of_export_array; i++)
    {
        assert(export_array[0]->length == export_array[i]->length);
    }

    char path[1000];
    char str2[1000];
    strcpy(path, absolute_path);

    sprintf(str2, "_%d.csv", index);
    strcat(path, str2);

    char string_buffer[1000] = {0};
    char string_buffer2[1000] = {0};
    char newline[] = "\n";
    char comma[] = ",";

    FILE *file1 = fopen(path, "w");
    if (file1 != NULL)
    {
        // Write header
        fprintf(file1, table_header);
        for (uint32_t i = 0; i < export_array[0]->length; i++)
        {
            // Build full string with all exported arrays
            for (size_t j = 0; j < length_of_export_array; j++)
            {
                sprintf(string_buffer, "%.8f", (double)export_array[j]->data[i]);
                if (j < (length_of_export_array - 1))
                { // No comma in last line
                    strcat(string_buffer, comma);
                }
                strcat(string_buffer2, string_buffer);
            }
            strcat(string_buffer2, newline);
            fprintf(file1, string_buffer2);
            string_buffer2[0] = '\0'; // Resets the string_buffer2 after each line
        }
    }
}

#endif // TEST
