#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"

#define NUMBER_OF_INPUTS 2
#define NUMBER_OF_OUTPUTS 1
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 3

float s_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float s_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float s_3[NUMBER_OF_OUTPUTS] = {0};
float delta_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float delta_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float delta_3[NUMBER_OF_OUTPUTS] = {0};
float cacheg_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0};
float cacheg_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float cacheg_3[NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};

//Gradienten
float g_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0};
float g_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float g_3[NUMBER_OF_OUTPUTS+NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};

float x[NUMBER_OF_INPUTS] = {1, 2};
float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {1, 2, 3, 4, 5, 6};
float b_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {1, 2, 3};
float y_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float w_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {-7, -8, -9, -10, -11, -12, 13, 14, -15};
float b_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {4, 5, 6};
float y_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float w_3[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {16, 17, -18};
float b_3[NUMBER_OF_OUTPUTS] = {7};
float y_3[NUMBER_OF_OUTPUTS] = {0};

float e_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER]={0.0f};
float e_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER]={0.0f};
float e_3[NUMBER_OF_OUTPUTS]={0.0f};
float T1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float T2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};
float T3[4] = {0}; // eigentlich nicht nötig da man cachebackprop im letzten layer nicht benötigt, aber fest definiert in layerconfig

void setUp(void)
{
}

void tearDown(void)
{
}

struct uz_nn_layer_config config[3] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_cachegradcolumns = NUMBER_OF_INPUTS,
        .number_of_temporaryrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_temporarycolumns = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .length_of_weights = UZ_MATRIX_SIZE(w_1),
        .length_of_bias = UZ_MATRIX_SIZE(b_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .length_of_sumout = UZ_MATRIX_SIZE(s_1),
        .length_of_delta = UZ_MATRIX_SIZE(delta_1),
        .length_of_error = UZ_MATRIX_SIZE(e_1),
        .length_of_gradients = UZ_MATRIX_SIZE(g_1),
        .length_of_temporarybackprop = UZ_MATRIX_SIZE(T1),
        .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_1),
        .weights = w_1,
        .bias = b_1,
        .output = y_1,
        .sumout = s_1,
        .delta = delta_1,
        .temporarybackprop = T1,
        .gradients = g_1,
        .cachegradients = cacheg_1,
        .error = e_1},
    [1] = {.activation_function = activation_ReLU,      
      .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_temporaryrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
      .number_of_temporarycolumns = NUMBER_OF_OUTPUTS,
      .length_of_weights = UZ_MATRIX_SIZE(w_2),
      .length_of_bias = UZ_MATRIX_SIZE(b_2),
      .length_of_output = UZ_MATRIX_SIZE(y_2),
      .length_of_sumout = UZ_MATRIX_SIZE(s_2),
      .length_of_delta = UZ_MATRIX_SIZE(delta_2),
      .length_of_gradients = UZ_MATRIX_SIZE(g_2),
      .length_of_error = UZ_MATRIX_SIZE(e_2),
      .length_of_temporarybackprop = UZ_MATRIX_SIZE(T2),
      .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_2),
      .weights = w_2,
      .bias = b_2,
      .output = y_2,
      .sumout = s_2,
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
   .length_of_weights = UZ_MATRIX_SIZE(w_3),
   .length_of_bias = UZ_MATRIX_SIZE(b_3),
   .length_of_output = UZ_MATRIX_SIZE(y_3),
   .length_of_sumout = UZ_MATRIX_SIZE(s_3),
   .length_of_delta = UZ_MATRIX_SIZE(delta_3),
   .length_of_gradients = UZ_MATRIX_SIZE(g_3),
   .length_of_error = UZ_MATRIX_SIZE(e_3),
   .length_of_temporarybackprop = UZ_MATRIX_SIZE(T3),
   .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_3),
   .weights = w_3,
   .bias = b_3,
   .output = y_3,
   .sumout = s_3,
   .delta = delta_3, 
   .temporarybackprop = T3,
   .gradients = g_3,
   .cachegradients = cacheg_3,
   .error= e_3}};
void test_uz_nn_init(void)
{
    uz_nn_init(config, 3);
}

void test_uz_nn_ff(void)
{
    struct uz_matrix_t input_matrix = {0};
    uz_matrix_t *input = uz_matrix_init(&input_matrix, x, UZ_MATRIX_SIZE(x), 1, 2);
    uz_nn_t *test = uz_nn_init(config, 3);
    uz_nn_ff(test, input);
    float expected_result_first_layer[3] = {10, 14, 18};
    float expected_result_second_layer[3] = {28, 23, 0};
    float expected_result_output_layer[1] = {846};

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_result_first_layer, y_1, UZ_MATRIX_SIZE(expected_result_first_layer));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_result_second_layer, y_2, UZ_MATRIX_SIZE(expected_result_second_layer));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_result_output_layer, y_3, UZ_MATRIX_SIZE(expected_result_output_layer));

    float expected_result = 846;
    uz_matrix_t *output = uz_nn_get_output_data(test);
    float result = uz_matrix_get_element_zero_based(output, 0, 0);
    TEST_ASSERT_EQUAL_FLOAT(expected_result, result);
}

void test_uz_nn_get_number_of_layer(void){
    uz_nn_t *test = uz_nn_init(config, 3);
    uint32_t number_of_layer=uz_nn_get_number_of_layer(test);
    TEST_ASSERT_EQUAL(number_of_layer,3);
}

void test_uz_nn_get_number_of_inputs(void){
    uz_nn_t *test = uz_nn_init(config, 3);
    uint32_t number_of_inputs=uz_nn_get_number_of_inputs(test);
    TEST_ASSERT_EQUAL(number_of_inputs,NUMBER_OF_INPUTS);
}

void test_uz_nn_get_number_of_outputs(void){
    uz_nn_t *test = uz_nn_init(config, 3);
    uint32_t number_of_outputs=uz_nn_get_number_of_outputs(test);
    TEST_ASSERT_EQUAL(number_of_outputs,NUMBER_OF_OUTPUTS);
}

#endif // TEST
