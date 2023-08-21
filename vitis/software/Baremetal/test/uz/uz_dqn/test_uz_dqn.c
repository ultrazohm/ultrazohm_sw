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
#include "mtwister.h"

//eps greedy test
#define NUMBER_OF_EPSGREEDYSTEPS 1000
float epsmat[NUMBER_OF_EPSGREEDYSTEPS] = {
#include "epsmat.csv"
};
// buffer
#define EXPERIENCE_BUFFER_LENGTH 10
#define MINIBATCHSIZE 5
#define NUMBER_OF_EPOCHS 200
#define TARGET_UPDATE_FREQUENCY 10
// nn
#define NUMBER_OF_INPUTS 2
#define NUMBER_OF_OUTPUTS 1
#define NUMBER_OF_HIDDEN_LAYER 3
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 3

//dqn
#define DQN_FREQUENCY 100
float discountfact = 0.98f;
float lernrate = 0.005f;
// target 
float ts_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float ts_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float ts_3[NUMBER_OF_OUTPUTS] = {0};

float tx[NUMBER_OF_INPUTS] = {0};
float tw_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float tb_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float ty_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float tw_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float tb_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float ty_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float tw_3[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};
float tb_3[NUMBER_OF_OUTPUTS] = {0};
float ty_3[NUMBER_OF_OUTPUTS] = {0};
// critic
float cs_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float cs_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float cs_3[NUMBER_OF_OUTPUTS] = {0};

//deltas
float delta_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float delta_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float delta_3[NUMBER_OF_OUTPUTS] = {0};

//cache gradients, Gräße entspricht delta des aktuellen layers * größe des Outputs des vorherigen layers
float cacheg_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0};
float cacheg_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float cacheg_3[NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};

//Gradienten
float g_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0};
float g_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float g_3[NUMBER_OF_OUTPUTS+NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};

float cx[NUMBER_OF_INPUTS] = {
1.0f,2.0f
};

float creference_output[NUMBER_OF_OUTPUTS]= {
2.0f
};

float cw_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
0.8f,0.1f,0.6f,0.9f,0.9f,0.1f
};
float cb_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
0.8f,1.0f,0.7f
};
float cy_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};


float cw_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
0.3f,1.0f,1.0f,0.5f,0.2f,0.5f,1.0f,1.0f,0.8f
};
float cb_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
0.0f,0.8f,0.9f
};
float cy_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};


float cw_3[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
0.1f,0.4f,0.9f
};
float cb_3[NUMBER_OF_OUTPUTS] = {
0.7f
};
float cy_3[NUMBER_OF_OUTPUTS] = {0};
// error
float e_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER]={0.0f};
float e_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER]={0.0f};
float e_3[NUMBER_OF_OUTPUTS]={0.0f};

// Temporary buffer storage

float T1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float T2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};
float T3[4] = {0}; // eigentlich nicht nötig da man cachebackprop im letzten layer nicht benötigt, aber fest definiert in layerconfig
// stuff for buffer
float reward[EXPERIENCE_BUFFER_LENGTH] = {1.0f,2.0f,3.0f};
float qvalues[EXPERIENCE_BUFFER_LENGTH] = {1.0f,2.0f,3.0f};
int32_t action[EXPERIENCE_BUFFER_LENGTH] = {0,5,50};
float observation[NUMBER_OF_INPUTS*EXPERIENCE_BUFFER_LENGTH] = {2.0f,3.0f,6.0f,5.0f,7.0f,12.0f};

float x_array[NUMBER_OF_INPUTS * MINIBATCHSIZE] = {2.0f,1.5f,5.0f,2.5f,5.8f,6.0f,5.0f,7.0f,5.0f,50.0f};

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
    [1] = {.activation_function = activation_ReLU,      
      .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .length_of_weights = UZ_MATRIX_SIZE(tw_2),
      .length_of_bias = UZ_MATRIX_SIZE(tb_2),
      .length_of_output = UZ_MATRIX_SIZE(ty_2),
      .length_of_sumout = UZ_MATRIX_SIZE(ts_2),
      .weights = tw_2,
      .bias = tb_2,
      .output = ty_2,
      .sumout = ts_2},
    [2] = {.activation_function = activation_linear,    
   .number_of_neurons = NUMBER_OF_OUTPUTS,
   .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
   .length_of_weights = UZ_MATRIX_SIZE(tw_3),
   .length_of_bias = UZ_MATRIX_SIZE(tb_3),
   .length_of_output = UZ_MATRIX_SIZE(ty_3),
   .length_of_sumout = UZ_MATRIX_SIZE(ts_3),
   .weights = tw_3,
   .bias = tb_3,
   .output = ty_3,
   .sumout = ts_3}};
//config critic
struct uz_nn_layer_config config_critic[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_cachegradcolumns = NUMBER_OF_INPUTS,
        .number_of_temporaryrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_temporarycolumns = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
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
      .activation_function = activation_ReLU, 
      .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_temporaryrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_temporarycolumns = NUMBER_OF_OUTPUTS,
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
      .error=e_2},
  [2] = {.activation_function = activation_linear,
   .number_of_neurons = NUMBER_OF_OUTPUTS,
   .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
   .number_of_cachegradrows = NUMBER_OF_OUTPUTS,
   .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
   .number_of_temporarycolumns = 2,
   .number_of_temporaryrows = 2,
   .length_of_weights = UZ_MATRIX_SIZE(cw_3),
   .length_of_bias = UZ_MATRIX_SIZE(cb_3),
   .length_of_output = UZ_MATRIX_SIZE(cy_3),
   .length_of_sumout = UZ_MATRIX_SIZE(cs_3),
   .length_of_delta = UZ_MATRIX_SIZE(delta_3),
   .length_of_gradients = UZ_MATRIX_SIZE(g_3),
   .length_of_error = UZ_MATRIX_SIZE(e_3),
   .length_of_temporarybackprop = UZ_MATRIX_SIZE(T3),
   .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_3),
   .weights = cw_3,
   .bias = cb_3,
   .output = cy_3,
   .sumout = cs_3,
   .delta = delta_3, 
   .temporarybackprop = T3,
   .gradients = g_3,
   .cachegradients = cacheg_3,
   .error= e_3}
  };
//config buffer
struct uz_dqn_experience_replay_config configbuffer = {
        .length_of_buffer = UZ_MATRIX_SIZE(reward),
        .columns_of_observations = NUMBER_OF_INPUTS,
        .reward = reward,
        .qvalues = qvalues,
        .observations = observation,
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
    uz_dqn_t* testdqn = uz_dqn_init(lernrate,discountfact,config_critic,config_target, NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH,0); 
}

void test_calc_reward_with_penalty(void)
{
    float ts = 0.05f;
    float theta = 0.08f;
    float position = 0.8f;
    float velocity = 12.0f;
    bool pen = false;
    float reward = calculate_reward_pendulum(ts, theta, position, velocity, pen);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f, -4.48f, reward);
}

void test_uz_dqn_copy_nn(void){
    // uz_dqn_t* dqn = uz_dqn_init(&lernrate,&discountfact,config_critic,config_target, NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH,0); 
    // uz_nn_copy(dqn->critic,dqn->critic_target_net);
    // TEST_ASSERT_EQUAL_FLOAT_ARRAY(cw_1,tw_1,UZ_MATRIX_SIZE(cw_1));
    // TEST_ASSERT_EQUAL_FLOAT_ARRAY(cw_2,tw_2,UZ_MATRIX_SIZE(cw_2));
    // TEST_ASSERT_EQUAL_FLOAT_ARRAY(cw_3,tw_3,UZ_MATRIX_SIZE(cw_3));
    // TEST_ASSERT_EQUAL_FLOAT_ARRAY(cb_1,tb_1,UZ_MATRIX_SIZE(cb_1));
    // TEST_ASSERT_EQUAL_FLOAT_ARRAY(cb_2,tb_2,UZ_MATRIX_SIZE(cb_2));
    // TEST_ASSERT_EQUAL_FLOAT_ARRAY(cb_3,tb_3,UZ_MATRIX_SIZE(cb_3));
    uz_dqn_t* dqn = uz_dqn_init(lernrate,discountfact,config_critic,config_target, NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH,0); 
    float targsmoothfact = 0.05f;
    uz_nn_target_update(dqn->critic,dqn->critic_target_net,periodic,&targsmoothfact);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(cw_1,tw_1,UZ_MATRIX_SIZE(cw_1));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(cw_2,tw_2,UZ_MATRIX_SIZE(cw_2));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(cw_3,tw_3,UZ_MATRIX_SIZE(cw_3));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(cb_1,tb_1,UZ_MATRIX_SIZE(cb_1));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(cb_2,tb_2,UZ_MATRIX_SIZE(cb_2));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(cb_3,tb_3,UZ_MATRIX_SIZE(cb_3));
}
void test_calc_reward_without_penalty(void)
{
    float ts = 0.1f;
    float theta = 0.98f;
    float position = 0.2f;
    float velocity = 2.0f;
    bool pen = true;
    float reward = calculate_reward_pendulum(ts, theta, position, velocity, pen);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f, -1019.84f, reward);
}
 void test_uz_dqn_calc_loss_terminal(void)
 {
    uz_dqn_t* dqn = uz_dqn_init(lernrate,discountfact,config_critic,config_target, NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH,0); 
    float reward = 2.0f;
    float qval = 10.0f;
    float qvalplus1 = 5.5f;
    bool terminal = false;
    float loss = calculate_loss_dqn(dqn, dqn->discount_factor, reward,qval, qvalplus1, terminal);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f, 6.8121, loss);
 }

  void test_uz_dqn_calc_loss_non_terminal(void)
 {
    uz_dqn_t* dqn = uz_dqn_init(lernrate,discountfact,config_critic,config_target, NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH,0); 
    float reward = -3.0f;
    float qval = 7.0f;
    float qvalplus1 = 4.5f;
    bool terminal = true;
    float loss = calculate_loss_dqn(dqn, dqn->discount_factor, reward, qval, qvalplus1,terminal);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f, 100.0f, loss);
 }
void test_uz_dqn_1_step(void)
{
    uz_dqn_t* testdqn = uz_dqn_init(lernrate,discountfact,config_critic,config_target, NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH,0); 
    // random indizes for sample from buffer
    uint32_t r[MINIBATCHSIZE] = {1,0,1,0,1}; 
    uint32_t *indizes = r;
    struct uz_matrix_t x_matrix={0};
    uz_matrix_t* input=uz_matrix_init(&x_matrix,cx,2,1,NUMBER_OF_INPUTS);
    uz_nn_ff(testdqn->critic,input);
    uz_matrix_t* outputdqn=uz_nn_get_output_data(testdqn->critic);
    float qvalue = uz_matrix_get_max_value(outputdqn);
    uint32_t action = uz_matrix_get_max_index(outputdqn);
    float reward = calculate_reward_pendulum(0.01f, 0.1f, 0.05f, 0.3f, false);
    uz_dqn_push_to_buffer(testdqn->experience_buffer,&reward,&qvalue,&action,input);
    uz_dqn_push_to_buffer(testdqn->experience_buffer,&reward,&qvalue,&action,input);
    uz_dqn_push_to_buffer(testdqn->experience_buffer,&reward,&qvalue,&action,input);
    // jetzt sind drei gleiche werte im buffer, sample minibatch mit zwei gleichen werten aus buffer
    // arrays anlegen
    float getbackrew[MINIBATCHSIZE]= {0.0f};
    float* rew = getbackrew;
    float getbackqval[MINIBATCHSIZE]= {0.0f};
    float* qval = getbackqval;
    float getbackqvalplus1[MINIBATCHSIZE]= {0.0f};
    float* qvalplus1 = getbackqvalplus1;
    int32_t getbackact[MINIBATCHSIZE] = {0};
    int32_t* act = getbackact;
    float getbackobbs[NUMBER_OF_INPUTS*MINIBATCHSIZE] = {0.0f};
    struct uz_matrix_t getbackobs_matrix = {0};
    uz_matrix_t *obs= uz_matrix_init(&getbackobs_matrix, getbackobbs, UZ_MATRIX_SIZE(getbackobbs), MINIBATCHSIZE, NUMBER_OF_INPUTS);
    uz_dqn_get_minibatch_from_buffer(testdqn->experience_buffer,rew,qval,qvalplus1,act,obs,MINIBATCHSIZE,NUMBER_OF_INPUTS,indizes);
    bool terminal = false;
    float loss = calculate_loss_dqn(testdqn, testdqn->discount_factor, reward, *qval, *qvalplus1, terminal);
    uz_nn_backward_pass(testdqn->critic,&loss,input);
    float lernrate = 0.0001f;
    uz_nn_gradient_descent(testdqn->critic,lernrate);
}
void test_uz_dqn_train_episodes(void)
{
    enum target_update periodic;
    float targsmoothfact = 0.05f;
    // Zuerst alles definieren und anlegen
    uz_dqn_t* testdqn = uz_dqn_init(lernrate,discountfact,config_critic,config_target, NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH,0); 
    // random indizes for sample from buffer
    uint32_t r[MINIBATCHSIZE] = {1,2,4,5,0}; 
    uint32_t *indizes = r;
    // arrays anlegen für extrahieren aus dem Buffer
    float getbackrew[MINIBATCHSIZE]= {0.0f};
    float* rew = getbackrew;
    float getbackqval[MINIBATCHSIZE]= {0.0f};
    float* qval = getbackqval;
    float getbackqvalplus1[MINIBATCHSIZE]= {0.0f};
    float* qvalplus1 = getbackqvalplus1;
    int32_t getbackact[MINIBATCHSIZE] = {0};
    int32_t* act = getbackact;
    float getbackobbs[NUMBER_OF_INPUTS*MINIBATCHSIZE] = {0.0f};
    struct uz_matrix_t getbackobs_matrix = {0};
    uz_matrix_t *obs= uz_matrix_init(&getbackobs_matrix, getbackobbs, UZ_MATRIX_SIZE(getbackobbs), MINIBATCHSIZE, NUMBER_OF_INPUTS);
    struct uz_matrix_t input_matrix={0};
    uz_matrix_t* input=uz_matrix_init(&input_matrix, x_array,UZ_MATRIX_SIZE(x_array),MINIBATCHSIZE,NUMBER_OF_INPUTS);
    float X_data[NUMBER_OF_INPUTS] = {0.0f};
    struct uz_matrix_t input_vec= {0};
    uz_matrix_t *X = uz_matrix_init(&input_vec, X_data, UZ_MATRIX_SIZE(X_data), 1, UZ_MATRIX_SIZE(X_data));
    for (size_t i = 0; i < NUMBER_OF_EPOCHS; i++)
    {
    for(uint32_t j=0; j<MINIBATCHSIZE;j++){
    uz_matrix_get_row_vector_zero_based(input,X,j);
    uz_nn_ff(testdqn->critic,X);
    uz_matrix_t* outputdqn=uz_nn_get_output_data(testdqn->critic);
    float qvalue = uz_matrix_get_max_value(outputdqn);
    uint32_t action = uz_matrix_get_max_index(outputdqn);
    float reward = calculate_reward_pendulum(1/DQN_FREQUENCY, 0.1f, 0.05f, 0.3f, false);
    uz_dqn_push_to_buffer(testdqn->experience_buffer,&reward,&qvalue,&action,X);
    uz_dqn_get_minibatch_from_buffer(testdqn->experience_buffer,rew,qval,qvalplus1,act,obs,MINIBATCHSIZE,NUMBER_OF_INPUTS,indizes);
    bool terminal = false;
    float loss = calculate_derv_loss_dqn(testdqn, testdqn->discount_factor,*rew,*qval,*qvalplus1,terminal);
    uz_nn_backward_pass_mini_batch(testdqn->critic,&loss,X);  
    printf("loss nach Episode  %d ist = %.8f \n",(int)i, (double)loss);  
    }
    uz_nn_gradient_descent_mini_batch(testdqn->critic,testdqn->lernrate,MINIBATCHSIZE);
    uz_nn_set_gradients_zero(testdqn->critic);
    // Targetupdate 
    if (TARGET_UPDATE_FREQUENCY % NUMBER_OF_EPOCHS == 0){
    uz_nn_target_update(testdqn->critic,testdqn->critic_target_net,periodic_smoothing, &targsmoothfact);
    }
    }
}
void test_calc_epsilon_greedy_assert_start_greater_min(void)
{
float epsilon_start = 0.3f;
float epsilon_min = 0.5f;
float epsilon_decay = 0.09f;
TEST_ASSERT_FAIL_ASSERT(calc_epsilon_greedy(epsilon_start, epsilon_min, epsilon_decay));
}

void test_calc_epsilon_greedy_assert_decay(void)
{
float epsilon_start = 0.8f;
float epsilon_min = 0.2f;
float epsilon_decay = 1.5f;
TEST_ASSERT_FAIL_ASSERT(calc_epsilon_greedy(epsilon_start, epsilon_min, epsilon_decay));
}

void test_calc_epsilon_assert_negative(void)
{
float epsilon_start = 1.5f;
float epsilon_min = 0.2f;
float epsilon_decay = -1.5f;
TEST_ASSERT_FAIL_ASSERT(calc_epsilon_greedy(epsilon_start, epsilon_min, epsilon_decay));
}

void test_calc_epsilon_greedy_check_values(void)
{
float epsilon_start = 0.9f;
float epsilon_min = 0.05f;
float epsilon_decay = 0.002f;
// Test if epsilon_min is calculated right
for(uint32_t i=0U;i<NUMBER_OF_EPSGREEDYSTEPS;i++){
float epsilon = calc_epsilon_greedy(epsilon_start, epsilon_min, epsilon_decay);
epsilon_start = epsilon;
TEST_ASSERT_FLOAT_WITHIN(1e-05f,epsmat[i],epsilon);
}
}

void test_rand_mtwister(void)
{
  // use mtwister, calculate double between 0 and 1 and scale it to Randmax
  //double randmax = 500; seedRand(0) 
  MTRand r = seedRand(1);
  int i;
  for(i=0; i<15; i++) {
    // uint kann nicht in der Funktion gecastet werden, sonst kann man nichts mehr skalieren, es kommt nur 0 und 1 raus
    uint32_t randuint = (uint32_t)(genRand(&r) * EXPERIENCE_BUFFER_LENGTH + 1);
    float randfloat = (genRand_float(&r) * EXPERIENCE_BUFFER_LENGTH + 1);
    double randdouble = (genRand(&r) * EXPERIENCE_BUFFER_LENGTH + 1);
    printf("%d\n", randuint);
    printf("%f\n", (double)randfloat);
    printf("%f\n", randdouble);
  }
  return 0;
}

#endif // TEST
