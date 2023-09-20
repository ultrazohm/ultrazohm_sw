#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_dqn.h"
#include "uz_dqn.c"
#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include <stdlib.h>
#include "uz_mtwister.h"
#include "uz_environment.h"
#include <time.h>
#include <string.h>

// buffer
#define EXPERIENCE_BUFFER_LENGTH 20000
#define MINIBATCHSIZE 32
#define NUMBER_OF_EPOCHS 25
#define TARGET_UPDATE_FREQUENCY 1
// nn
#define NUMBEROFBITS 4
#define NUMBER_OF_INPUTS 8
#define NUMBER_OF_OUTPUTS 4
#define NUMBER_OF_HIDDEN_LAYER 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 256
#define NUMBEROFTESTSTEPS 50
// adam
float m[5000] = {0.0f};
float v[5000] = {0.0f};

float discountfact = 0.99f;
float lernrate = 0.001f;
// random array
uint32_t array[NUMBEROFBITS] = {0,1,0,0};
uint32_t tararray[NUMBEROFBITS] = {1,1,1,1};
float inarray[NUMBER_OF_INPUTS] = {10.0f};
 //conf envrionment
struct uz_dqn_environment_config configenv = {
    .bitlength = NUMBEROFBITS,
    .bitarray = array,
    .targetarray = tararray,
    .inarray = inarray,
    .max_steps = NUMBEROFBITS+3,
    .epsilon_start = 0.99f, 
    .epsilon_min = 0.01f, 
    .epsilon_decay = 0.001f
};
// debug stuff
float loss[NUMBER_OF_EPOCHS] = {0.0f};
float cumreward[NUMBER_OF_EPOCHS] = {0.0f};
float epsilonovertime[NUMBER_OF_EPOCHS] = {0.0f};
float cumreward_noexpl[NUMBEROFTESTSTEPS] = {0.0f};
//dqn
float X_dat[NUMBER_OF_INPUTS] = {0.0f};
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

//deltas
float delta_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float delta_2[NUMBER_OF_OUTPUTS] = {0};

//cache gradients, Gräße entspricht delta des aktuellen layers * größe des Outputs des vorherigen layers
float cacheg_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0};
float cacheg_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};

//Gradienten
float g_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0};
float g_2[NUMBER_OF_OUTPUTS + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};

float cx[NUMBER_OF_INPUTS] = {
1.0f,2.0f
};

float creference_output[NUMBER_OF_OUTPUTS]= {
2.0f
};

float cw_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0.0f};
float cb_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0.0f};
float cy_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0.0f};


float cw_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0.0f};
float cb_2[NUMBER_OF_OUTPUTS] = {0.0f};
float cy_2[NUMBER_OF_OUTPUTS] = {0.0f};

// error
float e_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER]={0.0f};
float e_2[NUMBER_OF_OUTPUTS]={0.0f};

// Temporary buffer storage

float T1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};
float T2[4] = {0};

// stuff for buffer
float reward[EXPERIENCE_BUFFER_LENGTH] = {0};
uint32_t action[EXPERIENCE_BUFFER_LENGTH] = {0};
float qvalues[EXPERIENCE_BUFFER_LENGTH] = {0};
float observation[NUMBER_OF_INPUTS*EXPERIENCE_BUFFER_LENGTH] = {0};
float vecobs[NUMBER_OF_INPUTS] = {0.0f};
float x_array[NUMBER_OF_INPUTS * MINIBATCHSIZE] = {0};

// config random
struct uz_mtwister_config cfg = {
  .seed = 123,
  .distribution = normal_distribution
};
//config target
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
    [1] = {.activation_function = activation_linear,      
      .number_of_neurons = NUMBER_OF_OUTPUTS,
      .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .length_of_weights = UZ_MATRIX_SIZE(tw_2),
      .length_of_bias = UZ_MATRIX_SIZE(tb_2),
      .length_of_output = UZ_MATRIX_SIZE(ty_2),
      .length_of_sumout = UZ_MATRIX_SIZE(ts_2),
      .weights = tw_2,
      .bias = tb_2,
      .output = ty_2,
      .sumout = ts_2}};
//config critic
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
        .weights = cw_1,
        .bias = cb_1,
        .output = cy_1,
        .sumout = cs_1,
        .delta = delta_1,
        .temporarybackprop = T1,
        .gradients = g_1,
        .cachegradients = cacheg_1,
        .error = e_1},
    [1] = {
      .activation_function = activation_linear, 
      .number_of_neurons = NUMBER_OF_OUTPUTS,
      .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_cachegradrows = NUMBER_OF_OUTPUTS,
      .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_temporaryrows = 2,
      .number_of_temporarycolumns = 2,
      .length_of_weights = UZ_MATRIX_SIZE(cw_2),
      .length_of_bias = UZ_MATRIX_SIZE(cb_2),
      .length_of_output = UZ_MATRIX_SIZE(cy_2),
      .length_of_sumout = UZ_MATRIX_SIZE(cs_2),
      .length_of_delta = UZ_MATRIX_SIZE(delta_2),
      .length_of_gradients = UZ_MATRIX_SIZE(g_2),
      .length_of_error = UZ_MATRIX_SIZE(e_2),
      .length_of_temporarybackprop = UZ_MATRIX_SIZE(T2),
      .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_2),
      .weights = cw_2,
      .bias = cb_2,
      .output = cy_2,
      .sumout = cs_2,
      .delta = delta_2,
      .temporarybackprop = T2,
      .gradients = g_2,
      .cachegradients = cacheg_2,
      .error=e_2}};

//config buffer
struct uz_dqn_experience_replay_config configbuffer = {
        .length_of_buffer = UZ_MATRIX_SIZE(reward),
        .columns_of_observations = NUMBER_OF_INPUTS,
        .reward = reward,
        .qvalues = qvalues,
        .observations = observation,
        .obsvec = vecobs,
        .actions = action
};
void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_dqn_init(void)
{
    uz_dqn_t* testdqn = uz_dqn_init(X_dat,lernrate,discountfact,config_critic,config_target,cfg,NUMBER_OF_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH,0,configenv); 
    float targsmoothfact = 0.05f;
    uz_nn_target_update(testdqn->critic,testdqn->critic_target_net,periodic_smoothing,&targsmoothfact);
}
void test_dqn_bitflip(void)
{
    uz_dqn_t* testdqn2 = uz_dqn_init(X_dat,lernrate,discountfact,config_critic,config_target,cfg,NUMBER_OF_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH,0,configenv); 
    float targsmoothfact = 0.05f;
    uz_nn_copy(testdqn2->critic,testdqn2->critic_target_net);
    uint32_t r[MINIBATCHSIZE] = {0}; 
    uint32_t *indizes = r;
    float getbackrew[MINIBATCHSIZE]= {0.0f};
    float getbackqval[MINIBATCHSIZE]= {0.0f};
    uint32_t getbackact[MINIBATCHSIZE] = {0};
    float* rew = getbackrew;
    float* qval = getbackqval;
    uint32_t* act = getbackact;
    float getbackobbspl1[NUMBER_OF_INPUTS*MINIBATCHSIZE] = {0.0f};
    struct uz_matrix_t getbackobs_matrixpl1 = {0};
    uz_matrix_t *obspl1= uz_matrix_init(&getbackobs_matrixpl1, getbackobbspl1, UZ_MATRIX_SIZE(getbackobbspl1), MINIBATCHSIZE, NUMBER_OF_INPUTS);
    //adam testing
    adam_optimizer_t *adam = uz_adam_init(m, v, lernrate/(float)MINIBATCHSIZE);
    // prefill buffer
    do{
    uz_dqn_environment_reset(testdqn2->env,&testdqn2->randinstance->seedRand);
    uz_dqn_sample_bitenv(testdqn2);
    } while (!testdqn2->experience_buffer->counterisfull && (testdqn2->experience_buffer->head< (20 * MINIBATCHSIZE)));
    // epsilon wieder auf startwert setzen
    testdqn2->env->epsilon_start = configenv.epsilon_start;
    for (uint32_t i = 0; i < NUMBER_OF_EPOCHS; i++)
    {
    uz_dqn_environment_reset(testdqn2->env,&testdqn2->randinstance->seedRand);
    uz_dqn_sample_bitenv(testdqn2);
    cumreward[i] = testdqn2->env->cumreward;
    epsilonovertime[i] = testdqn2->env->epsilon_start;
    genRand_uint32_t_array(r,&testdqn2->randinstance->seedRand,MINIBATCHSIZE,1,EXPERIENCE_BUFFER_LENGTH-1);
    uz_dqn_get_minibatch_from_buffer(testdqn2->experience_buffer,rew,qval,act,testdqn2->experience_buffer->vectorforobs,obspl1,MINIBATCHSIZE,indizes);
    loss[i] = uz_dqn_train4(testdqn2,rew,qval,act,obspl1,MINIBATCHSIZE,TARGET_UPDATE_FREQUENCY,i,targsmoothfact,adam); 
    }
    free(adam);
    // Verhalten des Agenten testen, nach dem Training
    for (size_t i = 0; i < NUMBEROFTESTSTEPS; i++)
    {
    uz_dqn_environment_reset(testdqn2->env,&testdqn2->randinstance->seedRand);
    uz_dqn_act_bitenv_no_exploration(testdqn2);
    cumreward_noexpl[i] = testdqn2->env->cumreward;
    }
    // export defines datum etc, neuer ordner um die sachen unterscheiden zu können
    // save loss and cumreward
    // time_t t = time(NULL);
    // struct tm *tm = localtime(&t);
    // char s[64];
    // size_t ret = strftime(s, sizeof(s), "%c", tm);
    // printf("%s\n", s);
    //make_directory(s);
    // strcat("test/uz/uz_dqn/loss256_clipped", s);
    // strcat(".csv",s);
    exportFloatArrayToCSV("test/uz/uz_dqn/loss256_clipped.csv", loss, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_dqn/cumreward256_clipped.csv", cumreward, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_dqn/epsilon256_clipped.csv", epsilonovertime, NUMBER_OF_EPOCHS);
    exportFloatArrayToCSV("test/uz/uz_dqn/cumreward256_nur_action.csv", cumreward_noexpl, NUMBEROFTESTSTEPS);
    // save param to .txt
    FILE* f = fopen("test/uz/uz_dqn/hyperparam.txt", "w");  // open the file for writing
    if (f != NULL)                       // check for success
    {
     fprintf(f,"Learnrate, Discount Factor, Hidden Layer,Bufferlength,Minibatchsize,Epochen,Targetupdatefrequency,Numberofbits,Numberofneuronsinhiddenlayer \n");
     fprintf(f,"%.6f,%.6f,%d,%d,%d,%d,%d,%d,%d\n", lernrate,discountfact,NUMBER_OF_HIDDEN_LAYER,EXPERIENCE_BUFFER_LENGTH,MINIBATCHSIZE,NUMBER_OF_EPOCHS,TARGET_UPDATE_FREQUENCY,NUMBEROFBITS,
     NUMBER_OF_NEURONS_IN_HIDDEN_LAYER);
     fclose(f);                       // close the file
     f = NULL;                        // set file handle to null since f is no longer valid
    }
    //uz_nn_trained_export(testdqn2->critic_target_net);
}
#endif // TEST
