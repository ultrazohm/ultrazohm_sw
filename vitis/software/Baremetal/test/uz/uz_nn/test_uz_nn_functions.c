#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include "uz_sum.h"
#include "uz_codegen0_ert_rtw/uz_codegen0.h"
#include <time.h>


#define NUMBER_OF_INPUTS 1
#define NUMBER_OF_OUTPUTS 1
#define NUMBER_OF_HIDDEN_LAYER 3
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 10
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 10
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

//Gradienten 1
float g_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER + NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_INPUTS] = {
#include "functions_weights/grad1.csv"
};
float g_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER + NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/grad2.csv"
};
float g_3[NUMBER_OF_OUTPUTS+NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/grad3.csv"
};
//Gradienten 3
float g_12[NUMBER_OF_NEURONS_IN_FIRST_LAYER + NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_INPUTS] = {
#include "functions_weights/gradx1.csv"
};
float g_22[NUMBER_OF_NEURONS_IN_SECOND_LAYER + NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/gradx2.csv"
};
float g_32[NUMBER_OF_OUTPUTS+NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/gradx3.csv"
};


float x[NUMBER_OF_INPUTS] = {
#include "functions_weights/x1.csv"
};

float reference_output[NUMBER_OF_OUTPUTS]= {
#include "functions_weights/xout.csv"
};

float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/g1.csv"
};
float w_12[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/g12.csv"
};
float wx1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/wsoll1.csv"    
};
float wx12[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/wsoll12.csv"    
};
float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/b1.csv"
};
float b_12[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/b12.csv"
};
float bx1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/bsoll1.csv"
};
float bx12[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "functions_weights/bsoll12.csv"
};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};


float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/g2.csv"
};
float w_22[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/g22.csv"
};
float wx2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/wsoll2.csv"    
};
float wx22[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/wsoll22.csv"    
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/b2.csv"
};
float b_22[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/b22.csv"
};
float bx2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/bsoll2.csv"
};
float bx22[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "functions_weights/bsoll22.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};


float w_3[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {
#include "functions_weights/g3.csv"
};
float w_32[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {
#include "functions_weights/g32.csv"
};
float wx3[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {
#include "functions_weights/wsoll3.csv"    
};
float wx32[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {
#include "functions_weights/wsoll32.csv"    
};
float b_3[NUMBER_OF_OUTPUTS] = {
#include "functions_weights/b3.csv"
};
float b_32[NUMBER_OF_OUTPUTS] = {
#include "functions_weights/b32.csv"
};
float bx3[NUMBER_OF_OUTPUTS] = {
#include "functions_weights/bsoll3.csv"
};
float bx32[NUMBER_OF_OUTPUTS] = {
#include "functions_weights/bsoll32.csv"
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
        .length_of_bias = UZ_MATRIX_SIZE(b_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .length_of_sumout = UZ_MATRIX_SIZE(s_1),
        .length_of_derivate_gradients= UZ_MATRIX_SIZE(d_1),
        .length_of_delta = UZ_MATRIX_SIZE(delta_1),
        .length_of_error = UZ_MATRIX_SIZE(e_1),
        .length_of_gradients = UZ_MATRIX_SIZE(g_1),
        .length_of_temporarybackprop = UZ_MATRIX_SIZE(T1),
        .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_1),
        .weights = w_1,
        .bias = b_1,
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

struct uz_nn_layer_config config2[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_tanh,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_cachegradcolumns = NUMBER_OF_INPUTS,
        .number_of_temporaryrows = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_temporarycolumns = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
        .length_of_weights = UZ_MATRIX_SIZE(w_12),
        .length_of_bias = UZ_MATRIX_SIZE(b_12),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .length_of_sumout = UZ_MATRIX_SIZE(s_1),
        .length_of_derivate_gradients= UZ_MATRIX_SIZE(d_1),
        .length_of_delta = UZ_MATRIX_SIZE(delta_1),
        .length_of_error = UZ_MATRIX_SIZE(e_1),
        .length_of_gradients = UZ_MATRIX_SIZE(g_12),
        .length_of_temporarybackprop = UZ_MATRIX_SIZE(T1),
        .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_1),
        .weights = w_12,
        .bias = b_12,
        .output = y_1,
        .sumout = s_1,
        .derivate_gradients = d_1,
        .delta = delta_1,
        .temporarybackprop = T1,
        .gradients = g_12,
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
      .length_of_weights = UZ_MATRIX_SIZE(w_22),
      .length_of_bias = UZ_MATRIX_SIZE(b_22),
      .length_of_output = UZ_MATRIX_SIZE(y_2),
      .length_of_sumout = UZ_MATRIX_SIZE(s_2),
      .length_of_derivate_gradients = UZ_MATRIX_SIZE(d_2),
      .length_of_delta = UZ_MATRIX_SIZE(delta_2),
      .length_of_gradients = UZ_MATRIX_SIZE(g_22),
      .length_of_error = UZ_MATRIX_SIZE(e_2),
      .length_of_temporarybackprop = UZ_MATRIX_SIZE(T2),
      .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_2),
      .weights = w_22,
      .bias = b_22,
      .output = y_2,
      .sumout = s_2,
      .derivate_gradients = d_2,
      .delta = delta_2,
      .temporarybackprop = T2,
      .gradients = g_22,
      .cachegradients = cacheg_2,
      .error=e_2},
  [2] = {.activation_function = activation_linear,
   .number_of_neurons = NUMBER_OF_OUTPUTS,
   .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
   .number_of_cachegradrows = NUMBER_OF_OUTPUTS,
   .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
   .number_of_temporarycolumns = 2,
   .number_of_temporaryrows = 2,
   .length_of_weights = UZ_MATRIX_SIZE(w_32),
   .length_of_bias = UZ_MATRIX_SIZE(b_32),
   .length_of_output = UZ_MATRIX_SIZE(y_3),
   .length_of_sumout = UZ_MATRIX_SIZE(s_3),
   .length_of_derivate_gradients = UZ_MATRIX_SIZE(d_3),
   .length_of_delta = UZ_MATRIX_SIZE(delta_3),
   .length_of_gradients = UZ_MATRIX_SIZE(g_32),
   .length_of_error = UZ_MATRIX_SIZE(e_3),
   .length_of_temporarybackprop = UZ_MATRIX_SIZE(T3),
   .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_3),
   .weights = w_32,
   .bias = b_32,
   .output = y_3,
   .sumout = s_3,
   .derivate_gradients = d_3,
   .delta = delta_3, 
   .temporarybackprop = T3,
   .gradients = g_32,
   .cachegradients = cacheg_3,
   .error= e_3}
  };
float mse1[1] = {7};
float mse2[1] = {4};
float bmse3[3] = {8,7,9};
float bmse4[3] = {12,14,28};
void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_nn_mse_one(void)
{
    struct uz_matrix_t testmatrix1={0};
    uz_matrix_t* test1=uz_matrix_init(&testmatrix1, mse1,UZ_MATRIX_SIZE(mse1),1,UZ_MATRIX_SIZE(mse1));
    struct uz_matrix_t testmatrix2={0};
    uz_matrix_t* test2=uz_matrix_init(&testmatrix2, mse2,UZ_MATRIX_SIZE(mse2),1,UZ_MATRIX_SIZE(mse2));
    float msetest =  uz_nn_mse(test1,test2);
    float expected_result = 9;
    TEST_ASSERT_EQUAL_FLOAT(expected_result, msetest);
}
void test_uz_nn_mse_three(void)
{
    struct uz_matrix_t testmatrix3={0};
    uz_matrix_t* test3=uz_matrix_init(&testmatrix3, bmse3,UZ_MATRIX_SIZE(bmse3),1,UZ_MATRIX_SIZE(bmse3));
    struct uz_matrix_t testmatrix4={0};
    uz_matrix_t* test4=uz_matrix_init(&testmatrix4, bmse4,UZ_MATRIX_SIZE(bmse4),1,UZ_MATRIX_SIZE(bmse4));
    float msetest2 =  uz_nn_mse(test3,test4);
    float expected_result = 142;
    TEST_ASSERT_EQUAL_FLOAT(expected_result, msetest2);
}

void test_uz_nn_gradient_descent1(void)
{
    // Test 1: Gleiche Gradienten für bias und weights, LR 0.1
    uz_nn_t *test = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
    float lernrate = 0.1f;
    uz_nn_gradient_descent(test,lernrate);

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(w_1, wx1,10);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(w_2, wx2,100);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(w_3, wx3,10);

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(b_1, bx1,10);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(b_2, bx2,10);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(b_3, bx3,1);
}
void test_uz_nn_gradient_descent2(void)
{
    // Test 1: Unterschiedlicher Gradienten für bias und weights
    // prüfen der loopindizes, LR 0.5
    uz_nn_t *test2 = uz_nn_init(config2, NUMBER_OF_HIDDEN_LAYER);
    float lernrate = 0.5f;
    uz_nn_gradient_descent(test2,lernrate);

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(w_12, wx12,10);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(w_22, wx22,100);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(w_32, wx32,10);

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(b_12, bx12,10);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(b_22, bx22,10);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(b_32, bx32,1);
}
#endif // TEST
