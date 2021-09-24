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
    enum activation_function act = ReLU;
    uz_nn_layer_init(NUMBER_OF_NEURONS_IN_LAYER, NUMBER_OF_INPUTS, w, UZ_MATRIX_SIZE(w), b, UZ_MATRIX_SIZE(b), out, UZ_MATRIX_SIZE(out), act);
}

void test_uz_nn_layer_matrix_multiply_zero_bias(void)
{
    enum activation_function act = linear;
    float b0[4] = {0, 0, 0, 0};
    uz_nn_layer_t *layer = uz_nn_layer_init(NUMBER_OF_NEURONS_IN_LAYER, NUMBER_OF_INPUTS, w, UZ_MATRIX_SIZE(w), b0, UZ_MATRIX_SIZE(b0), out, UZ_MATRIX_SIZE(out), act);
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
    enum activation_function act = linear;
    float b0[4] = {1, -2, 3, -4};
    uz_nn_layer_t *layer = uz_nn_layer_init(NUMBER_OF_NEURONS_IN_LAYER, NUMBER_OF_INPUTS, w, UZ_MATRIX_SIZE(w), b0, UZ_MATRIX_SIZE(b0), out, UZ_MATRIX_SIZE(out), act);
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
    enum activation_function act = ReLU;
    float b0[4] = {1, -2, 3, -4};
    uz_nn_layer_t *layer = uz_nn_layer_init(NUMBER_OF_NEURONS_IN_LAYER, NUMBER_OF_INPUTS, w, UZ_MATRIX_SIZE(w), b0, UZ_MATRIX_SIZE(b0), out, UZ_MATRIX_SIZE(out), act);
    float expected[4] = {12.9105, 5.5267 , 0.0 , 6.6521};
    uz_nn_layer_ff(layer, input);
    uz_matrix_t *result = uz_nn_layer_get_output_data(layer);
    for (size_t i = 0; i < 4; i++)
    {
        TEST_ASSERT_EQUAL_FLOAT(expected[i], uz_matrix_get_element_zero_based(result, 0, i));
    }
}

#endif // TEST
