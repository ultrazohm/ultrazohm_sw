#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"

#define NUMBER_OF_INPUTS 1
#define NUMBER_OF_OUTPUTS 1
#define NUMBER_OF_HIDDEN_LAYER 2
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 2
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 2

float x[NUMBER_OF_INPUTS] = {-5.0f};
float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "schroeder_weights/layer1_weights.csv"
};
float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "schroeder_weights/layer1_bias.csv"
		};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};

float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "schroeder_weights/layer2_weights.csv"
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "schroeder_weights/layer2_bias.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};

float w_3[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {
#include "schroeder_weights/layer3_weights.csv"
};
float b_3[NUMBER_OF_OUTPUTS] = {
#include "schroeder_weights/layer3_bias.csv"
};
float y_3[NUMBER_OF_OUTPUTS] = {0};

struct uz_nn_layer_config config[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_tanh,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(w_1),
        .length_of_bias = UZ_MATRIX_SIZE(b_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .weights = w_1,
        .bias = b_1,
        .output = y_1},
    [1] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
  [2] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3}};
void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_nn_schroeder(void)
{
    struct uz_matrix_t x_matrix={0};
    uz_matrix_t* input=uz_matrix_init(&x_matrix, x,UZ_MATRIX_SIZE(x),1,NUMBER_OF_INPUTS);
    uz_nn_t *test = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER );
    uz_nn_ff(test,input);
    float expected_result=-1.52f; // 
    uz_matrix_t* output=uz_nn_get_output_data(test);
    float result=uz_matrix_get_element_zero_based(output,0,0);
    TEST_ASSERT_EQUAL_FLOAT(expected_result,result);
}

#endif // TEST
