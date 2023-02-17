#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_nn_layer.h"
#include "uz_matrix.h"
#include "uz_nn_activation_functions.h"

#define NUMBER_OF_INPUTS 3U
#define NUMBER_OF_NEURONS_IN_LAYER 4U

float x[NUMBER_OF_INPUTS] = {1.0f, 2.0f, 3.0f};
float w[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_LAYER] = {0.5377f, 1.8339f, -2.2588f, 0.8622f,
                                                          0.3188f, -1.3077f, -0.4336f, 0.3426f,
                                                          3.5784f, 2.7694f, -1.3499f, 3.0349f};
float b[NUMBER_OF_NEURONS_IN_LAYER] = {1.0f, -2.0f, 3.0f, -4.0f};
float out[NUMBER_OF_NEURONS_IN_LAYER] = {0};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_nn_layer_init(void)
{
    struct uz_nn_layer_config config = {
        .activation_function = activation_ReLU,
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
    float b0[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    struct uz_nn_layer_config config = {
        .activation_function = activation_linear,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(w),
        .length_of_bias = UZ_MATRIX_SIZE(b0),
        .length_of_output = UZ_MATRIX_SIZE(out),
        .weights = w,
        .bias = b0,
        .output = out};
    uz_nn_layer_t *layer = uz_nn_layer_init(config);
    float expected[4] = {11.9105f, 7.5267f, -7.1757f, 10.6521f};

    struct uz_matrix_t input_matrix = {0};
    uz_matrix_t *input = uz_matrix_init(&input_matrix, x, UZ_MATRIX_SIZE(x), 1, NUMBER_OF_INPUTS);

    uz_nn_layer_ff(layer, input);
    uz_matrix_t *result = uz_nn_layer_get_output_data(layer);
    for (uint32_t i = 0U; i < 4U; i++)
    {
        TEST_ASSERT_EQUAL_FLOAT(expected[i], uz_matrix_get_element_zero_based(result, 0, i));
    }
}

void test_uz_nn_layer_matrix_multiply_with_bias(void)
{
    float b0[4] = {1.0f, -2.0f, 3.0f, -4.0f};
    struct uz_nn_layer_config config = {
        .activation_function = activation_linear,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(w),
        .length_of_bias = UZ_MATRIX_SIZE(b0),
        .length_of_output = UZ_MATRIX_SIZE(out),
        .weights = w,
        .bias = b0,
        .output = out};

    uz_nn_layer_t *layer = uz_nn_layer_init(config);
    float expected[4] = {12.9105f, 5.5267f, -4.1757f, 6.6521f};
    struct uz_matrix_t input_matrix = {0};
    uz_matrix_t *input = uz_matrix_init(&input_matrix, x, UZ_MATRIX_SIZE(x), 1, NUMBER_OF_INPUTS);
    uz_nn_layer_ff(layer, input);
    uz_matrix_t *result = uz_nn_layer_get_output_data(layer);
    for (uint32_t i = 0U; i < 4U; i++)
    {
        TEST_ASSERT_EQUAL_FLOAT(expected[i], uz_matrix_get_element_zero_based(result, 0, i));
    }
}

void test_uz_nn_layer_ff_relu(void)
{
    float b0[4] = {1.0f, -2.0f, 3.0f, -4.0f};
    struct uz_nn_layer_config config = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(w),
        .length_of_bias = UZ_MATRIX_SIZE(b0),
        .length_of_output = UZ_MATRIX_SIZE(out),
        .weights = w,
        .bias = b0,
        .output = out};

    uz_nn_layer_t *layer = uz_nn_layer_init(config);
    float expected[4] = {12.9105f, 5.5267f, 0.0f, 6.6521f};
    struct uz_matrix_t input_matrix = {0};
    uz_matrix_t *input = uz_matrix_init(&input_matrix, x, UZ_MATRIX_SIZE(x), 1, NUMBER_OF_INPUTS);
    uz_nn_layer_ff(layer, input);
    uz_matrix_t *result = uz_nn_layer_get_output_data(layer);
    for (uint32_t i = 0U; i < 4U; i++)
    {
        TEST_ASSERT_EQUAL_FLOAT(expected[i], uz_matrix_get_element_zero_based(result, 0, i));
    }
}

#endif // TEST
