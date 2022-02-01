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

#define BASE_ADDRESS 0xF0000000
struct uz_mlp_three_layer_ip_config_t config = {
    .base_address = BASE_ADDRESS};

uz_mlp_three_layer_ip_t *successful_init(void);
uz_mlp_three_layer_ip_t *successful_init(void)
{
    uz_mlp_three_layer_ip_t *test = UZ_MLP_THREE_LAYER_IP_init(config);
    return (test);
};

void test_uz_mlp_three_layer_write_bias_to_layer(void)
{
    successful_init();
    // const uint32_t parallel_pcu = 4U;
    // const uint32_t layer = 1U;
    // uz_matrix_t *layer1_bias = uz_matrix_init(&b_1[0], UZ_MATRIX_SIZE(b_1), size_t rows, size_t columns);
    // uz_mlp_three_layer_write_bias(parallel_pcu,layer_)
}

#endif // TEST
