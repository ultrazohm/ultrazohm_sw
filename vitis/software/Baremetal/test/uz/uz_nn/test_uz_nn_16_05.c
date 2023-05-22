#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include "uz_sum.h"
#include "uz_codegen0_ert_rtw/uz_codegen0.h"
#include <time.h>


#define NUMBER_OF_INPUTS 2
#define NUMBER_OF_OUTPUTS 1
#define NUMBER_OF_HIDDEN_LAYER 3
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 5
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 2

// stuff for training and update
// sumout
float s_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float s_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float s_3[NUMBER_OF_OUTPUTS] = {0};

//derivate matrix activation, Dimension = Sumout x Sumout 50x50=2500 z.B.
float d_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float d_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float d_3[NUMBER_OF_OUTPUTS * NUMBER_OF_OUTPUTS] = {0};
//deltas
float delta_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float delta_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float delta_3[NUMBER_OF_OUTPUTS] = {0};

//cache gradients, Gräße entspricht delta des aktuellen layers * größe des Outputs des vorherigen layers
float cacheg_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_INPUTS] = {0};
float cacheg_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float cacheg_3[NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};

//Gradienten
float g_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER + NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_INPUTS] = {0};
float g_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER + NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float g_3[NUMBER_OF_OUTPUTS+NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};

float x[NUMBER_OF_INPUTS] = {
#include "functions_weights/X_test1.csv"
};

float reference_output[NUMBER_OF_OUTPUTS]= {
#include "functions_weights/T_test1.csv"
};

float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/layer1_weights_test1.csv"
};
float bx_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/layer1_bias_test1.csv"
};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};


float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/layer2_weights_test1.csv"
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/layer2_bias_test1.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};


float w_3[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {
#include "functions_weights/layer3_weights_test1.csv"
};
float b_3[NUMBER_OF_OUTPUTS] = {
#include "functions_weights/layer3_bias_test1.csv"
};
float y_3[NUMBER_OF_OUTPUTS] = {0};
// error
float e_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER]={0.0f};
float e_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER]={0.0f};
float e_3[NUMBER_OF_OUTPUTS]={0.0f};

// Temporary buffer storage

float T1[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float T2[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {0};
float T3[4] = {0}; // eigentlich nicht nötig da man cachebackprop im letzten layer nicht benötigt, aber fest definiert in layerconfig

float gradtest1[30] = {
#include "functions_weights/gradmat.csv"
};

struct uz_nn_layer_config config[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_tanh,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_cachegradcolumns = NUMBER_OF_INPUTS,
        .number_of_temporaryrows = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_temporarycolumns = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
        .length_of_weights = UZ_MATRIX_SIZE(w_1),
        .length_of_bias = UZ_MATRIX_SIZE(bx_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .length_of_sumout = UZ_MATRIX_SIZE(s_1),
        .length_of_derivate_gradients= UZ_MATRIX_SIZE(d_1),
        .length_of_delta = UZ_MATRIX_SIZE(delta_1),
        .length_of_error = UZ_MATRIX_SIZE(e_1),
        .length_of_gradients = UZ_MATRIX_SIZE(g_1),
        .length_of_temporarybackprop = UZ_MATRIX_SIZE(T1),
        .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_1),
        .weights = w_1,
        .bias = bx_1,
        .output = y_1,
        .sumout = s_1,
        .derivate_gradients = d_1,
        .delta = delta_1,
        .temporarybackprop = T1,
        .gradients = g_1,
        .cachegradients = cacheg_1,
        .error = e_1},
    [1] = {
      .activation_function = activation_tanh, 
      .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
      .number_of_inputs = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
      .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
      .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
      .number_of_temporaryrows = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
      .number_of_temporarycolumns = NUMBER_OF_OUTPUTS,
      .length_of_weights = UZ_MATRIX_SIZE(w_2),
      .length_of_bias = UZ_MATRIX_SIZE(b_2),
      .length_of_output = UZ_MATRIX_SIZE(y_2),
      .length_of_sumout = UZ_MATRIX_SIZE(s_2),
      .length_of_derivate_gradients = UZ_MATRIX_SIZE(d_2),
      .length_of_delta = UZ_MATRIX_SIZE(delta_2),
      .length_of_gradients = UZ_MATRIX_SIZE(g_2),
      .length_of_error = UZ_MATRIX_SIZE(e_2),
      .length_of_temporarybackprop = UZ_MATRIX_SIZE(T2),
      .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_2),
      .weights = w_2,
      .bias = b_2,
      .output = y_2,
      .sumout = s_2,
      .derivate_gradients = d_2,
      .delta = delta_2,
      .temporarybackprop = T2,
      .gradients = g_2,
      .cachegradients = cacheg_2,
      .error=e_2},
  [2] = {.activation_function = activation_linear,
   .number_of_neurons = NUMBER_OF_OUTPUTS,
   .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
   .number_of_cachegradrows = NUMBER_OF_OUTPUTS,
   .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
   .number_of_temporarycolumns = 2,
   .number_of_temporaryrows = 2,
   .length_of_weights = UZ_MATRIX_SIZE(w_3),
   .length_of_bias = UZ_MATRIX_SIZE(b_3),
   .length_of_output = UZ_MATRIX_SIZE(y_3),
   .length_of_sumout = UZ_MATRIX_SIZE(s_3),
   .length_of_derivate_gradients = UZ_MATRIX_SIZE(d_3),
   .length_of_delta = UZ_MATRIX_SIZE(delta_3),
   .length_of_gradients = UZ_MATRIX_SIZE(g_3),
   .length_of_error = UZ_MATRIX_SIZE(e_3),
   .length_of_temporarybackprop = UZ_MATRIX_SIZE(T3),
   .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_3),
   .weights = w_3,
   .bias = b_3,
   .output = y_3,
   .sumout = s_3,
   .derivate_gradients = d_3,
   .delta = delta_3, 
   .temporarybackprop = T3,
   .gradients = g_3,
   .cachegradients = cacheg_3,
   .error= e_3}
  };

void setUp(void)
{
}

void tearDown(void)
{
}


void test_uz_nn_checkgradients_test1(void)
{
    uz_nn_t *nn1 = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
    struct uz_matrix_t x_matrix={0};
    uz_matrix_t* input=uz_matrix_init(&x_matrix,x,2,1,NUMBER_OF_INPUTS);
    struct uz_matrix_t refmatrix={0};
    uz_matrix_t* refout=uz_matrix_init(&refmatrix, reference_output,UZ_MATRIX_SIZE(reference_output),1,UZ_MATRIX_SIZE(reference_output));
    uz_nn_ff(nn1,input);
    uz_matrix_t* outputnn1=uz_nn_get_output_data(nn1);
    float result1=uz_matrix_get_element_zero_based(outputnn1,0,0);
    float msetest =  uz_nn_mse(outputnn1,refout);
    uz_nn_backward_pass(nn1,&msetest,input);
    uz_matrix_t* gradhelptest1 = uz_nn_get_gradient_data(nn1,1); // index 1-2 verwenden für nn mit 2 layern
    uz_matrix_t* gradhelptest2 = uz_nn_get_gradient_data(nn1,2);
    uz_matrix_t* gradhelptest3 = uz_nn_get_gradient_data(nn1,3);
    float gradhelpertest1[UZ_MATRIX_SIZE(g_1)+UZ_MATRIX_SIZE(g_2)+UZ_MATRIX_SIZE(g_3)];
     gradhelpertest1[0] = uz_matrix_get_element_zero_based(gradhelptest1,0,0);
     gradhelpertest1[1] = uz_matrix_get_element_zero_based(gradhelptest1,1,0);
     gradhelpertest1[2] = uz_matrix_get_element_zero_based(gradhelptest1,2,0);
     gradhelpertest1[3] = uz_matrix_get_element_zero_based(gradhelptest1,3,0);
     gradhelpertest1[4] = uz_matrix_get_element_zero_based(gradhelptest1,4,0);
     gradhelpertest1[5] = uz_matrix_get_element_zero_based(gradhelptest1,5,0);
     gradhelpertest1[6] = uz_matrix_get_element_zero_based(gradhelptest1,6,0);
     gradhelpertest1[7] = uz_matrix_get_element_zero_based(gradhelptest1,7,0);
     gradhelpertest1[8] = uz_matrix_get_element_zero_based(gradhelptest1,8,0);
     gradhelpertest1[9] = uz_matrix_get_element_zero_based(gradhelptest1,9,0);
     gradhelpertest1[10] = uz_matrix_get_element_zero_based(gradhelptest1,10,0);
     gradhelpertest1[11] = uz_matrix_get_element_zero_based(gradhelptest1,11,0);
     gradhelpertest1[12] = uz_matrix_get_element_zero_based(gradhelptest1,12,0);
     gradhelpertest1[13] = uz_matrix_get_element_zero_based(gradhelptest1,13,0);
     gradhelpertest1[14] = uz_matrix_get_element_zero_based(gradhelptest1,14,0);
     gradhelpertest1[15] = uz_matrix_get_element_zero_based(gradhelptest2,0,0);
     gradhelpertest1[16] = uz_matrix_get_element_zero_based(gradhelptest2,1,0);
     gradhelpertest1[17] = uz_matrix_get_element_zero_based(gradhelptest2,2,0);
     gradhelpertest1[18] = uz_matrix_get_element_zero_based(gradhelptest2,3,0);
     gradhelpertest1[19] = uz_matrix_get_element_zero_based(gradhelptest2,4,0);
     gradhelpertest1[20] = uz_matrix_get_element_zero_based(gradhelptest2,5,0);
     gradhelpertest1[21] = uz_matrix_get_element_zero_based(gradhelptest2,6,0);
     gradhelpertest1[22] = uz_matrix_get_element_zero_based(gradhelptest2,7,0);
     gradhelpertest1[23] = uz_matrix_get_element_zero_based(gradhelptest2,8,0);
     gradhelpertest1[24] = uz_matrix_get_element_zero_based(gradhelptest2,9,0);
     gradhelpertest1[25] = uz_matrix_get_element_zero_based(gradhelptest2,10,0);
     gradhelpertest1[26] = uz_matrix_get_element_zero_based(gradhelptest2,11,0);
     gradhelpertest1[27] = uz_matrix_get_element_zero_based(gradhelptest3,0,0);
     gradhelpertest1[28] = uz_matrix_get_element_zero_based(gradhelptest3,1,0);
     gradhelpertest1[29] = uz_matrix_get_element_zero_based(gradhelptest3,2,0);
     for(size_t i = 0;i< (int)(sizeof(gradhelpertest1) / sizeof(float));i++) {
        TEST_ASSERT_FLOAT_WITHIN(1e-02f, gradtest1[i], gradhelpertest1[i]);
    }
}

void test_uz_nn_checkgradients_test2(void)
{
// check cachegradients
   uz_nn_t *test2 = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
    struct uz_matrix_t x_matrix={0};
    uz_matrix_t* input=uz_matrix_init(&x_matrix,x,2,1,NUMBER_OF_INPUTS);
    uz_nn_ff(test2,input);
    uz_matrix_t* output=uz_nn_get_output_data(test2);
    float result2=uz_matrix_get_element_zero_based(output,0,0);
    float error2 = reference_output[0]- result2;
    uz_nn_backward_pass(test2,&error2,input);
    uz_matrix_t* cachegradhelp1= uz_nn_get_cachegradient_data(test2,1); // index 1-2 verwenden für nn mit 2 layern
    uz_matrix_t* cachegradhelp2 = uz_nn_get_cachegradient_data(test2,2);
}

void test_uz_nn_checkgradients_test3(void)
{
    // check delta
   uz_nn_t *test3 = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
    struct uz_matrix_t x_matrix={0};
    uz_matrix_t* input=uz_matrix_init(&x_matrix,x,2,1,NUMBER_OF_INPUTS);
    uz_nn_ff(test3,input);
    uz_matrix_t* output=uz_nn_get_output_data(test3);
    float result3=uz_matrix_get_element_zero_based(output,0,0);
    float error3 = reference_output[0]- result3;
    uz_nn_backward_pass(test3,&error3,input);
    uz_matrix_t* deltagradhelp1 = uz_nn_get_delta_data(test3,1); // index 1-2 verwenden für nn mit 2 layern
    uz_matrix_t* deltagradhelp2 = uz_nn_get_delta_data(test3,2);
}
#endif // TEST
