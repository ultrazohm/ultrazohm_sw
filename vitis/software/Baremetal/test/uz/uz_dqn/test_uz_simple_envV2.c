#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_dqn.h"
#include "uz_dqn_expirience_buffer.h"
#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include <stdlib.h>
#include "uz_mtwister.h"
#include "uz_environment.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>

// buffer
#define EXPERIENCE_BUFFER_LENGTH 6000U
#define MINIBATCHSIZE 16U
#define NUMBER_OF_EPOCHS 200000U
#define TARGET_UPDATE_FREQUENCY 20U
// nn
#define NUMBER_OF_INPUTS 4U
#define NUMBER_OF_OUTPUTS 3U
#define NUMBER_OF_HIDDEN_LAYER 2U
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 16U
#define NUMBEROFTESTSTEPS 50U
#define NUMBEROFBITS 2U

float discountfact = 0.0f;
float lernrate = 0.001f;
// env array
uint32_t array[NUMBEROFBITS] = {0, 1};
uint32_t tararray[NUMBEROFBITS] = {1, 1};
float inarray[NUMBER_OF_INPUTS] = {1.0f, 1.0f, 1.0f, 1.0f};
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
    .max_steps = 1,
    .epsilon_start = 0.99f,
    .epsilon_min = 0.00000001f,
    .epsilon_decay = 0.00007f};
// debug stuff
float Q_Target[NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS] = {0.0f};
float Q_Critic[NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS] = {0.0f};
float loss[NUMBER_OF_EPOCHS] = {0.0f};
float cumreward[NUMBER_OF_EPOCHS] = {0.0f};
float globalrewardr[NUMBER_OF_EPOCHS] = {0.0f};
float epsilonovertime[NUMBER_OF_EPOCHS] = {0.0f};
float cumreward_noexpl[NUMBEROFTESTSTEPS] = {0.0f};
// dqn
float X_dat[NUMBER_OF_INPUTS] = {1.0f, 1.0f, 1.0f, 1.0f};
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
float reward[EXPERIENCE_BUFFER_LENGTH] = {0};
uint32_t action[EXPERIENCE_BUFFER_LENGTH] = {0};
float observation[NUMBER_OF_INPUTS * EXPERIENCE_BUFFER_LENGTH] = {0};
float observation1[NUMBER_OF_INPUTS * EXPERIENCE_BUFFER_LENGTH] = {0};
float vecobs[NUMBER_OF_INPUTS] = {0.0f};
float vecobs1[NUMBER_OF_INPUTS] = {0.0f};
float x_array[NUMBER_OF_INPUTS * MINIBATCHSIZE] = {0};

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
void test_dqn_simple(void)
{
    float targsmoothfact = 0.05f;
    uz_dqn_t *simpledqn = uz_dqn_init(X_dat, lernrate, discountfact, config_critic, config_target, 123U, NUMBER_OF_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH, configenv, MINIBATCHSIZE, TARGET_UPDATE_FREQUENCY, targsmoothfact);
    uz_nn_copy(simpledqn->critic, simpledqn->critic_target_net);
    float error[NUMBER_OF_OUTPUTS] = {0.0f};
    // // prefill buffer
    // do
    // {
    //     uz_dqn_sample_simple(simpledqn);
    // } while ((!simpledqn->experience_buffer->counterisfull) && (simpledqn->experience_buffer->head < (3U * MINIBATCHSIZE)));
    // simpledqn->env->epsilon_start = configenv.epsilon_start;
    for (uint32_t epoch = 0U; epoch < NUMBER_OF_EPOCHS; epoch++)
    {
        loss[epoch] = uz_dqn_step_adam_simple_no_array(simpledqn, error, epoch);
        cumreward[epoch] = simpledqn->env->cumreward;
        if (epoch == 0U)
        {
            globalrewardr[epoch] = simpledqn->env->cumreward;
        }
        else
        {
            globalrewardr[epoch] = 0.99f * globalrewardr[epoch - 1] + 0.01f * simpledqn->env->cumreward;
        }
        epsilonovertime[epoch] = simpledqn->env->epsilon_start;
        save_values(Q_Critic, Q_Target, cy_2, ty_2, epoch, NUMBER_OF_OUTPUTS);
    }

    TEST_ASSERT_FLOAT_WITHIN(0.0001f,3.0f, Q_Critic[NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS - 1]);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f,2.0f, Q_Critic[NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS - 2]);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f,1.0f, Q_Critic[NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS - 3]);

    exportFloatArrayToCSV("test/uz/uz_dqn/simple/losssimple.csv", loss, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_dqn/simple/QTarget.csv", Q_Target, NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS);
    exportFloatArrayToCSV("test/uz/uz_dqn/simple/QCritic.csv", Q_Critic, NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS);
    exportFloatArrayToCSV("test/uz/uz_dqn/simple/cumrewardsimple.csv", cumreward, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_dqn/simple/globalrewardrsimple.csv", globalrewardr, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_dqn/simple/epsilonsimple.csv", epsilonovertime, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_dqn/simple/cumrewardsimple_nur_action.csv", cumreward_noexpl, NUMBEROFTESTSTEPS);

    FILE *f = fopen("test/uz/uz_dqn/simple/hyperparam.txt", "w"); // open the file for writing
    if (f != NULL)                                                // check for success
    {
        fprintf(f, "Learnrate, Discount Factor,Epsilon_start,Epsilon_min,Epsilon_decay,Hidden Layer,Bufferlength,Minibatchsize,Epochen,Targetupdatefrequency,Numberofbits,Numberofneuronsinhiddenlayer \n");
        fprintf(f, "%.6f,%.6f,%.6f,%.6f,%.6f,%d,%d,%d,%d,%d,%d,%d\n", (double)lernrate, (double)discountfact, (double)configenv.epsilon_start, (double)configenv.epsilon_min, (double)configenv.epsilon_decay, NUMBER_OF_HIDDEN_LAYER, EXPERIENCE_BUFFER_LENGTH, MINIBATCHSIZE, NUMBER_OF_EPOCHS, TARGET_UPDATE_FREQUENCY, NUMBEROFBITS, NUMBER_OF_NEURONS_IN_HIDDEN_LAYER);
        fclose(f); // close the file
        f = NULL;  // set file handle to null since f is no longer valid
    }
}
#endif