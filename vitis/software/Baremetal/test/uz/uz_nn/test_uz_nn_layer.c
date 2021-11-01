#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_nn_layer.h"
#include "uz_matrix.h"
#include "uz_nn_activation_functions.h"

#define NUMBER_OF_INPUTS 3
#define NUMBER_OF_NEURONS_IN_LAYER 4

float x[NUMBER_OF_INPUTS] = {1, 2, 3};
float w[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_LAYER] = {0.5377, 1.8339, -2.2588, 0.8622,
                                                          0.3188, -1.3077, -0.4336, 0.3426,
                                                          3.5784, 2.7694, -1.3499, 3.0349};
float b[NUMBER_OF_NEURONS_IN_LAYER] = {1, -2, 3, -4};
float out[NUMBER_OF_NEURONS_IN_LAYER] = {0};
uz_matrix_t *input = 0;


void setUp(void)
{
    input = uz_matrix_init(x, UZ_MATRIX_SIZE(x), 1, NUMBER_OF_INPUTS);
}

void tearDown(void)
{
}


void test_uz_nn_layer_init(void)
{
    struct uz_nn_layer_config config = {
    .activation_function = ReLU,
    .number_of_neurons = NUMBER_OF_NEURONS_IN_LAYER,
    .number_of_inputs = NUMBER_OF_INPUTS,
    .length_of_weights = UZ_MATRIX_SIZE(w),
    .length_of_bias = UZ_MATRIX_SIZE(b),
    .length_of_output = UZ_MATRIX_SIZE(out),
    .weights = w,
    .bias = b,
    .output = out};
    uz_nn_layer_init(config);
}

void test_uz_nn_layer_matrix_multiply_zero_bias(void)
{
    float b0[4] = {0, 0, 0, 0};

    struct uz_nn_layer_config config = {
    .activation_function = linear,
    .number_of_neurons = NUMBER_OF_NEURONS_IN_LAYER,
    .number_of_inputs = NUMBER_OF_INPUTS,
    .length_of_weights = UZ_MATRIX_SIZE(w),
    .length_of_bias = UZ_MATRIX_SIZE(b0),
    .length_of_output = UZ_MATRIX_SIZE(out),
    .weights = w,
    .bias = b0,
    .output = out};
    uz_nn_layer_t *layer = uz_nn_layer_init(config);
    float expected[4] = {11.9105, 7.5267, -7.1757, 10.6521};
    uz_nn_layer_ff(layer, input);
    uz_matrix_t *result = uz_nn_layer_get_output_data(layer);
    for (size_t i = 0; i < 4; i++)
    {
        TEST_ASSERT_EQUAL_FLOAT(expected[i], uz_matrix_get_element_zero_based(result, 0, i));
    }
}

void test_uz_nn_layer_matrix_multiply_with_bias(void)
{
    float b0[4] = {1, -2, 3, -4};
    struct uz_nn_layer_config config = {
    .activation_function = linear,
    .number_of_neurons = NUMBER_OF_NEURONS_IN_LAYER,
    .number_of_inputs = NUMBER_OF_INPUTS,
    .length_of_weights = UZ_MATRIX_SIZE(w),
    .length_of_bias = UZ_MATRIX_SIZE(b0),
    .length_of_output = UZ_MATRIX_SIZE(out),
    .weights = w,
    .bias = b0,
    .output = out};

    uz_nn_layer_t *layer = uz_nn_layer_init(config);
    float expected[4] = {12.9105, 5.5267 , -4.1757 , 6.6521};
    uz_nn_layer_ff(layer, input);
    uz_matrix_t *result = uz_nn_layer_get_output_data(layer);
    for (size_t i = 0; i < 4; i++)
    {
        TEST_ASSERT_EQUAL_FLOAT(expected[i], uz_matrix_get_element_zero_based(result, 0, i));
    }
}

void test_uz_nn_layer_ff_relu(void)
{
        float b0[4] = {1, -2, 3, -4};
        struct uz_nn_layer_config config = {
    .activation_function = ReLU,
    .number_of_neurons = NUMBER_OF_NEURONS_IN_LAYER,
    .number_of_inputs = NUMBER_OF_INPUTS,
    .length_of_weights = UZ_MATRIX_SIZE(w),
    .length_of_bias = UZ_MATRIX_SIZE(b0),
    .length_of_output = UZ_MATRIX_SIZE(out),
    .weights = w,
    .bias = b0,
    .output = out};

    uz_nn_layer_t *layer = uz_nn_layer_init(config);
    float expected[4] = {12.9105, 5.5267 , 0.0 , 6.6521};
    uz_nn_layer_ff(layer, input);
    uz_matrix_t *result = uz_nn_layer_get_output_data(layer);
    for (size_t i = 0; i < 4; i++)
    {
        TEST_ASSERT_EQUAL_FLOAT(expected[i], uz_matrix_get_element_zero_based(result, 0, i));
    }
}

#endif // TEST