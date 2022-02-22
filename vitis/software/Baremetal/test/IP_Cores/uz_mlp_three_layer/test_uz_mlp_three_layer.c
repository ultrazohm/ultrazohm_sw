#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_array.h"
#include "uz_mlp_three_layer.h"
#include "mock_uz_mlp_three_layer_hw.h"
#include "uz_matrix.h"

void setUp(void)
{
}

void tearDown(void)
{
}

#define NUMBER_OF_INPUTS 13U
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 64U
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 64U
#define NUMBER_OF_NEURONS_IN_THIRD_LAYER 64U
#define NUMBER_OF_OUTPUTS 4
#define NUMBER_OF_HIDDEN_LAYER 3

float x[NUMBER_OF_INPUTS] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f};
float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "layer1_weights.csv"
};
float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "layer1_bias.csv"
};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};

float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "layer2_weights.csv"
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "layer2_bias.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};

float w_3[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "layer2_weights.csv"
};
float b_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] = {
#include "layer3_bias.csv"
};
float y_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] = {0};

float w_4[NUMBER_OF_NEURONS_IN_THIRD_LAYER * NUMBER_OF_OUTPUTS] = {
#include "layer4_weights.csv"
};
float b_4[NUMBER_OF_OUTPUTS] = {
#include "layer4_bias.csv"
};
float y_4[NUMBER_OF_OUTPUTS] = {0};

struct uz_nn_layer_config software_nn_config[4] = {
    [0] = {
        .activation_function = ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(w_1),
        .length_of_bias = UZ_MATRIX_SIZE(b_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .weights = w_1,
        .bias = b_1,
        .output = y_1},
    [1] = {.activation_function = ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = linear, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4}};

float w_data[32] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 32, 32};
float w_data_short[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
float w_data_short_expect[16] = {1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 8, 16};
float x_data[4] = {1, 2, 3, 4};
float bias_data[8] = {1, 2, 3, 4, 5, 6, 7, 8};

float bias_data_long[64] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                            17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                            31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 63};

#define BASE_ADDRESS 0xF0000000

struct uz_mlp_three_layer_ip_config_t config = {
    .base_address = BASE_ADDRESS,
    .software_network = NULL};

uz_mlp_three_layer_ip_t *successful_init(void);
uz_mlp_three_layer_ip_t *successful_init(void)
{
    config.software_network = uz_nn_init(software_nn_config, 4);
    uz_mlp_three_layer_ip_t *test = uz_mlp_three_layer_ip_init(config);
    return (test);
}

void test_uz_mlp_three_layer_write_bias_to_layer(void)
{
    uz_mlp_three_layer_ip_t *test_instance = successful_init();
    uz_matrix_t *bias_matrix = uz_matrix_init(bias_data, UZ_MATRIX_SIZE(bias_data), 1, UZ_MATRIX_SIZE(bias_data));

    // const uint32_t parallel_pcu = 4U;
    // const uint32_t layer = 1U;
    // uz_matrix_t *layer1_bias = uz_matrix_init(&b_1[0], UZ_MATRIX_SIZE(b_1), size_t rows, size_t columns);
    // uz_mlp_three_layer_write_bias(parallel_pcu,layer_)

    // Expect with PCU=4
    uz_mlp_three_layer_hw_write_layerNr_Expect(BASE_ADDRESS, 1);

    // Data 1
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[0]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // Data 2
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[1]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // Data 3 - this is the second pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[2]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // Data 4- this is the second pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[3]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // Data 5 - this is the third pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[4]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // Data 6- this is the third pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[5]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // Data 7 - this is the fourth pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[6]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // Data 8- this is the fourth pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[7]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_write_bias(test_instance, 4U, bias_matrix, 1);
}

void test_uz_mlp_three_layer_write_bias_to_layer_long(void)
{
    uz_mlp_three_layer_ip_t *test_instance = successful_init();
    uz_matrix_t *bias_matrix = uz_matrix_init(bias_data_long, UZ_MATRIX_SIZE(bias_data_long), 1, UZ_MATRIX_SIZE(bias_data_long));

    // Expect with PCU=8
    uz_mlp_three_layer_hw_write_layerNr_Expect(BASE_ADDRESS, 3);

    // Data 1
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[0]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // Data 2
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[1]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    //
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[2]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    //
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[3]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[4]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[5]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[6]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[7]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // PCU 2
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[8]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[9]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[10]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[11]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[12]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[13]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[14]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[15]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // PCU 3
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[16]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[17]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[18]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[19]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[20]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[21]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[22]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[23]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // PCU 4
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[24]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[25]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[26]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[27]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[28]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[29]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[30]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[31]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // PCU 5
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[32]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[33]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[34]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[35]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[36]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[37]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[38]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[39]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // PCU 6
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[40]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[41]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[42]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[43]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[44]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[45]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[46]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[47]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // PCU 7
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[48]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[49]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[50]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[51]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[52]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[53]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[54]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[55]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    // PCU 8
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[56]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 8);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[57]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 8);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[58]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 8);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[59]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 8);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[60]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 4);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 8);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[61]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 5);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 8);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[62]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 6);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 8);
    uz_array_float_t output_data;
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data_long[63]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 7);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 8);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_write_bias(test_instance, 8U, bias_matrix, 3);
}

void test_uz_mlp_three_layer_write_weights_to_layer(void)
{
    uz_mlp_three_layer_ip_t *test_instance = successful_init();
    // Test data with two rows and eight columns
    //
    // w= [1  2  3  4  5  6  7  8]
    //    [9 10 11 12 13 14 15 16]
    uz_matrix_t *weight_matrix = uz_matrix_init(w_data_short, UZ_MATRIX_SIZE(w_data_short), 2U, 8U);
    uz_mlp_three_layer_hw_write_layerNr_Expect(BASE_ADDRESS, 1U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[0]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 1U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 1U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[1]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 1U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[2]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 1U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[3]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 1U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[4]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 1U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[5]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[6]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[7]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[8]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 1U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[9]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[10]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[11]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[12]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 1U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[13]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[14]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[15]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);

    uz_mlp_three_layer_write_weights(test_instance, 4U, weight_matrix, 1U);
}

void test_uz_mlp_three_layer_set_parameters()
{
    uz_mlp_three_layer_ip_t *test_instance = successful_init();

    // Expected behavior
    // uz_mlp_three_layer_write_bias is called for each layer
    // weights is called for each layer

    // The functions "write weights" and "write bias" are tested individually since for the full example, this is not testable without just reproducing the for-loop 1:1 as it is in the implementation effectively expecting that the enable, bias and so on functions are called 10000 times
    // Some ideas on how to improve:
    // - split write bias/weights into dedicated .c file to make it possible to mock it
    // - https://stackoverflow.com/questions/40485835/how-to-mock-function-in-same-uut-in-c
    // - https://github.com/ThrowTheSwitch/Ceedling/issues/304
    uz_mlp_three_layer_hw_write_enable_bias_Ignore();
    uz_mlp_three_layer_hw_write_bias_data_Ignore();
    uz_mlp_three_layer_hw_write_bias_address_Ignore();
    uz_mlp_three_layer_hw_write_enable_weights_Ignore();
    uz_mlp_three_layer_hw_write_weight_data_Ignore();
    uz_mlp_three_layer_hw_write_weight_address_Ignore();

    // write bias
    uz_mlp_three_layer_hw_write_layerNr_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_layerNr_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_layerNr_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_layerNr_Expect(BASE_ADDRESS, 4);
    // then write weights
    uz_mlp_three_layer_hw_write_layerNr_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_layerNr_Expect(BASE_ADDRESS, 2);
    uz_mlp_three_layer_hw_write_layerNr_Expect(BASE_ADDRESS, 3);
    uz_mlp_three_layer_hw_write_layerNr_Expect(BASE_ADDRESS, 4);

    uz_mlp_three_layer_set_parameters(test_instance);
}

void test_uz_mlp_three_layer_calculate_forward_pass()
{

    uz_mlp_three_layer_ip_t *test_instance = successful_init();
    uz_matrix_t *input = uz_matrix_init(x, UZ_MATRIX_SIZE(x), 1, UZ_MATRIX_SIZE(x));

    uz_array_float_t input_data = {
        .data = &x[0],
        .length = UZ_ARRAY_SIZE(x)};

    uz_array_float_t output_data = {
        .data = &y_4[0],
        .length = UZ_ARRAY_SIZE(y_4)};

    uz_mlp_three_layer_hw_write_input_Expect(BASE_ADDRESS, input_data);
    uz_mlp_three_layer_hw_write_enable_nn_Expect(BASE_ADDRESS, true);
    uz_mlp_three_layer_hw_write_enable_nn_Expect(BASE_ADDRESS, false);
    uz_mlp_three_layer_hw_read_valid_output_ExpectAndReturn(BASE_ADDRESS, false); // Expects that the function is called multiple times and returns true at the 3. call
    uz_mlp_three_layer_hw_read_valid_output_ExpectAndReturn(BASE_ADDRESS, false);
    uz_mlp_three_layer_hw_read_valid_output_ExpectAndReturn(BASE_ADDRESS, true);

    // Return by pointer using ReturnThruPtr, see https://github.com/ThrowTheSwitch/CMock/issues/105
    // int qux = 4, baz = 5;
    //
    // foo_ExpectAndReturn(qux, &baz);
    // foo_IgnoreArg_b();
    // foo_ReturnThruPtr_b(&baz);
    //
    // bar()
    uz_mlp_three_layer_hw_read_output_Expect(BASE_ADDRESS, output_data);

    uz_mlp_three_layer_calculate_forward_pass(test_instance, input_data, output_data);
}

#endif // TEST111150