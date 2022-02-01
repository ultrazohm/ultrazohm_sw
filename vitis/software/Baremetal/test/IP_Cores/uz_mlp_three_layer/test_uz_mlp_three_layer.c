#ifdef TEST

#include "unity.h"

#include "uz_mlp_three_layer.h"
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

void test_uz_mlp_three_layer_write_bias_to_layer(void)
{
    const uint32_t parallel_pcu=4U;
    const uint32_t layer=1U;
    uz_matrix_t* layer1_weights=uz_matrix_init(&w_1[0],UZ_MATRIX_SIZE(w_1), size_t rows, size_t columns);



}

#endif // TEST
