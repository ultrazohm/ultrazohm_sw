#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"

#define NUMBER_OF_INPUTS 2
#define NUMBER_OF_OUTPUTS 1
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 3

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

void setUp(void)
{
}

void tearDown(void)
{
}

struct uz_nn_layer_config config[3] = {
    [0] = {
        .activation_function = ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(w_1),
        .length_of_bias = UZ_MATRIX_SIZE(b_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .weights = w_1,
        .bias = b_1,
        .output = y_1},
    [1] = {.activation_function = ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = linear, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3}};

void test_uz_nn_init(void)
{
    uz_nn_t *test = uz_nn_init(config, 3);
}


void test_uz_nn_ff(void)
{
    uz_matrix_t* input=uz_matrix_init(x,UZ_MATRIX_SIZE(x),1,2);
    uz_nn_t *test = uz_nn_init(config, 3);
    uz_nn_ff(test,input);
    float expected_result_first_layer[3]={10, 14, 18};
    float expected_result_second_layer[3]={28, 23, 0};
    float expected_result_output_layer[1]={846};

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_result_first_layer,y_1,UZ_MATRIX_SIZE(expected_result_first_layer));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_result_second_layer,y_2,UZ_MATRIX_SIZE(expected_result_second_layer));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_result_output_layer,y_3,UZ_MATRIX_SIZE(expected_result_output_layer));
}

#endif // TEST
