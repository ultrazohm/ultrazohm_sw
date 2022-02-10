#ifdef TEST

#include "unity.h"

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
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_HIDDEN_LAYER 3

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

float w_data[32] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 32, 32};
float w_data_short[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
float w_data_short_expect[16] = {1,9,2,10,3,11,4,12,5,13,6,14,7,15,8,16};
float x_data[4] = {1, 2, 3, 4};
float bias_data[8] = {1, 2, 3, 4, 5, 6, 7, 8};

#define BASE_ADDRESS 0xF0000000
struct uz_mlp_three_layer_ip_config_t config = {
    .base_address = BASE_ADDRESS};

uz_mlp_three_layer_ip_t *successful_init(void);
uz_mlp_three_layer_ip_t *successful_init(void)
{
    uz_mlp_three_layer_ip_t *test = UZ_MLP_THREE_LAYER_IP_init(config);
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
    // Data 2
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[1]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 1);
    // Data 3 - this is the second pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[2]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    // Data 4- this is the second pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[3]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 2);
    // Data 5 - this is the third pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[4]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    // Data 6- this is the third pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[5]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 3);
    // Data 7 - this is the fourth pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[6]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);
    // Data 8- this is the fourth pcu
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 0);
    uz_mlp_three_layer_hw_write_bias_data_Expect(BASE_ADDRESS, bias_data[7]);
    uz_mlp_three_layer_hw_write_bias_address_Expect(BASE_ADDRESS, 1);
    uz_mlp_three_layer_hw_write_enable_bias_Expect(BASE_ADDRESS, 4);

    uz_mlp_three_layer_write_bias(test_instance, 4U, bias_matrix, 1);
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

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[1]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 1U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[2]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 1U);

        uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[3]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 1U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[4]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 1U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 2U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[5]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 2U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[6]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 2U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[7]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 2U);

        uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[8]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 1U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 3U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[9]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 3U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[10]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 3U);

        uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[11]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 3U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[12]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 1U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 4U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[13]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 2U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 4U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[14]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 3U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 4U);

    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 0U);
    uz_mlp_three_layer_hw_write_weight_data_Expect(BASE_ADDRESS, w_data_short_expect[15]);
    uz_mlp_three_layer_hw_write_weight_address_Expect(BASE_ADDRESS, 4U);
    uz_mlp_three_layer_hw_write_enable_weights_Expect(BASE_ADDRESS, 4U);


    uz_mlp_three_layer_write_weights(test_instance,4U,weight_matrix,1U);

}

// Expect:
// uz_mlp_three_layer_hw_write_weight_data is called with 9,9,17,25,2,10,18,26


#endif // TEST111150