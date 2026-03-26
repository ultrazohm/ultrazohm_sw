#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_array.h"
#include "uz_NN_acc.h"
#include "mock_uz_NN_acc_hw.h"
#include "uz_matrix.h"
#include "mock_xil_cache.h"
#include "test_assert_with_exception.h"

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
#define NUMBER_OF_NEURONS_IN_FOURTH_LAYER 64U
#define NUMBER_OF_NEURONS_IN_FIFTH_LAYER 64U
#define NUMBER_OF_NEURONS_IN_SIXTH_LAYER 64U
#define NUMBER_OF_NEURONS_IN_SEVENTH_LAYER 64U
#define NUMBER_OF_NEURONS_IN_EIGHTH_LAYER 64U
#define NUMBER_OF_NEURONS_IN_NINTH_LAYER 64U
#define NUMBER_OF_NEURONS_IN_TENTH_LAYER 64U


#define NUMBER_OF_OUTPUTS 4
#define NUMBER_OF_HIDDEN_LAYER 10

float x[NUMBER_OF_INPUTS] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f};
float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "../uz_mlp_three_layer/layer1_weights.csv"
};
float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "../uz_mlp_three_layer/layer1_bias.csv"
};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};

float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "../uz_mlp_three_layer/layer2_weights.csv"
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "../uz_mlp_three_layer/layer2_bias.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};

float w_3[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "../uz_mlp_three_layer/layer3_weights.csv"
};
float b_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] = {
#include "../uz_mlp_three_layer/layer3_bias.csv"
};
float y_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] = {0};

float w_4[NUMBER_OF_NEURONS_IN_FOURTH_LAYER * NUMBER_OF_NEURONS_IN_THIRD_LAYER] = {
#include "../uz_mlp_three_layer/layer2_weights.csv"
};
float b_4[NUMBER_OF_NEURONS_IN_FOURTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_bias.csv"
};
float y_4[NUMBER_OF_NEURONS_IN_FOURTH_LAYER] = {0};

float w_5[NUMBER_OF_NEURONS_IN_FIFTH_LAYER * NUMBER_OF_NEURONS_IN_FOURTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_weights.csv"
};
float b_5[NUMBER_OF_NEURONS_IN_FIFTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_bias.csv"
};
float y_5[NUMBER_OF_NEURONS_IN_FIFTH_LAYER] = {0};

float w_6[NUMBER_OF_NEURONS_IN_SIXTH_LAYER * NUMBER_OF_NEURONS_IN_FIFTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_weights.csv"
};
float b_6[NUMBER_OF_NEURONS_IN_SIXTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_bias.csv"
};
float y_6[NUMBER_OF_NEURONS_IN_SIXTH_LAYER] = {0};

float w_7[NUMBER_OF_NEURONS_IN_SEVENTH_LAYER * NUMBER_OF_NEURONS_IN_SIXTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_weights.csv"
};
float b_7[NUMBER_OF_NEURONS_IN_SEVENTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_bias.csv"
};
float y_7[NUMBER_OF_NEURONS_IN_SEVENTH_LAYER] = {0};

float w_8[NUMBER_OF_NEURONS_IN_EIGHTH_LAYER * NUMBER_OF_NEURONS_IN_SEVENTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_weights.csv"
};
float b_8[NUMBER_OF_NEURONS_IN_EIGHTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_bias.csv"
};
float y_8[NUMBER_OF_NEURONS_IN_EIGHTH_LAYER] = {0};

float w_9[NUMBER_OF_NEURONS_IN_NINTH_LAYER * NUMBER_OF_NEURONS_IN_EIGHTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_weights.csv"
};
float b_9[NUMBER_OF_NEURONS_IN_NINTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_bias.csv"
};
float y_9[NUMBER_OF_NEURONS_IN_NINTH_LAYER] = {0};

float w_10[NUMBER_OF_NEURONS_IN_TENTH_LAYER * NUMBER_OF_NEURONS_IN_NINTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_weights.csv"
};
float b_10[NUMBER_OF_NEURONS_IN_TENTH_LAYER] = {
#include "../uz_mlp_three_layer/layer3_bias.csv"
};
float y_10[NUMBER_OF_NEURONS_IN_TENTH_LAYER] = {0};

float w_out[NUMBER_OF_NEURONS_IN_TENTH_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../uz_mlp_three_layer/layer4_weights.csv"
};
float b_out[NUMBER_OF_OUTPUTS] = {
#include "../uz_mlp_three_layer/layer4_bias.csv"
};
float y_out[NUMBER_OF_OUTPUTS] = {0};
struct uz_nn_layer_config software_nn_config_10N[11] = {
    [0] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .number_of_inputs = NUMBER_OF_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(w_1), .length_of_bias = UZ_MATRIX_SIZE(b_1), .length_of_output = UZ_MATRIX_SIZE(y_1), .weights = w_1, .bias = b_1, .output = y_1},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4},
    [4] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_5), .length_of_bias = UZ_MATRIX_SIZE(b_5), .length_of_output = UZ_MATRIX_SIZE(y_5), .weights = w_5, .bias = b_5, .output = y_5},
    [5] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SIXTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_6), .length_of_bias = UZ_MATRIX_SIZE(b_6), .length_of_output = UZ_MATRIX_SIZE(y_6), .weights = w_6, .bias = b_6, .output = y_6},
    [6] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SEVENTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SEVENTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_7), .length_of_bias = UZ_MATRIX_SIZE(b_7), .length_of_output = UZ_MATRIX_SIZE(y_7), .weights = w_7, .bias = b_7, .output = y_7},
    [7] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_EIGHTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_EIGHTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_8), .length_of_bias = UZ_MATRIX_SIZE(b_8), .length_of_output = UZ_MATRIX_SIZE(y_8), .weights = w_8, .bias = b_8, .output = y_8},
    [8] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_NINTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_NINTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_9), .length_of_bias = UZ_MATRIX_SIZE(b_9), .length_of_output = UZ_MATRIX_SIZE(y_9), .weights = w_9, .bias = b_9, .output = y_9},
    [9] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_TENTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_TENTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_10), .length_of_bias = UZ_MATRIX_SIZE(b_10), .length_of_output = UZ_MATRIX_SIZE(y_10), .weights = w_10, .bias = b_10, .output = y_10},
    [10] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_TENTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_out), .length_of_bias = UZ_MATRIX_SIZE(b_out), .length_of_output = UZ_MATRIX_SIZE(y_out), .weights = w_out, .bias = b_out, .output = y_out}};
struct uz_nn_layer_config software_nn_config_9N[10] = {
    [0] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .number_of_inputs = NUMBER_OF_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(w_1), .length_of_bias = UZ_MATRIX_SIZE(b_1), .length_of_output = UZ_MATRIX_SIZE(y_1), .weights = w_1, .bias = b_1, .output = y_1},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4},
    [4] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_5), .length_of_bias = UZ_MATRIX_SIZE(b_5), .length_of_output = UZ_MATRIX_SIZE(y_5), .weights = w_5, .bias = b_5, .output = y_5},
    [5] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SIXTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_6), .length_of_bias = UZ_MATRIX_SIZE(b_6), .length_of_output = UZ_MATRIX_SIZE(y_6), .weights = w_6, .bias = b_6, .output = y_6},
    [6] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SEVENTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SEVENTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_7), .length_of_bias = UZ_MATRIX_SIZE(b_7), .length_of_output = UZ_MATRIX_SIZE(y_7), .weights = w_7, .bias = b_7, .output = y_7},
    [7] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_EIGHTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_EIGHTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_8), .length_of_bias = UZ_MATRIX_SIZE(b_8), .length_of_output = UZ_MATRIX_SIZE(y_8), .weights = w_8, .bias = b_8, .output = y_8},
    [8] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_NINTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_NINTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_9), .length_of_bias = UZ_MATRIX_SIZE(b_9), .length_of_output = UZ_MATRIX_SIZE(y_9), .weights = w_9, .bias = b_9, .output = y_9},
    [9] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_NINTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_out), .length_of_bias = UZ_MATRIX_SIZE(b_out), .length_of_output = UZ_MATRIX_SIZE(y_out), .weights = w_out, .bias = b_out, .output = y_out}};
struct uz_nn_layer_config software_nn_config_8N[9] = {
    [0] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .number_of_inputs = NUMBER_OF_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(w_1), .length_of_bias = UZ_MATRIX_SIZE(b_1), .length_of_output = UZ_MATRIX_SIZE(y_1), .weights = w_1, .bias = b_1, .output = y_1},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4},
    [4] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_5), .length_of_bias = UZ_MATRIX_SIZE(b_5), .length_of_output = UZ_MATRIX_SIZE(y_5), .weights = w_5, .bias = b_5, .output = y_5},
    [5] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SIXTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_6), .length_of_bias = UZ_MATRIX_SIZE(b_6), .length_of_output = UZ_MATRIX_SIZE(y_6), .weights = w_6, .bias = b_6, .output = y_6},
    [6] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SEVENTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SEVENTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_7), .length_of_bias = UZ_MATRIX_SIZE(b_7), .length_of_output = UZ_MATRIX_SIZE(y_7), .weights = w_7, .bias = b_7, .output = y_7},
    [7] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_EIGHTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_EIGHTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_8), .length_of_bias = UZ_MATRIX_SIZE(b_8), .length_of_output = UZ_MATRIX_SIZE(y_8), .weights = w_8, .bias = b_8, .output = y_8},
    [8] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_EIGHTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_out), .length_of_bias = UZ_MATRIX_SIZE(b_out), .length_of_output = UZ_MATRIX_SIZE(y_out), .weights = w_out, .bias = b_out, .output = y_out}};
struct uz_nn_layer_config software_nn_config_7N[8] = {
    [0] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .number_of_inputs = NUMBER_OF_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(w_1), .length_of_bias = UZ_MATRIX_SIZE(b_1), .length_of_output = UZ_MATRIX_SIZE(y_1), .weights = w_1, .bias = b_1, .output = y_1},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4},
    [4] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_5), .length_of_bias = UZ_MATRIX_SIZE(b_5), .length_of_output = UZ_MATRIX_SIZE(y_5), .weights = w_5, .bias = b_5, .output = y_5},
    [5] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SIXTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_6), .length_of_bias = UZ_MATRIX_SIZE(b_6), .length_of_output = UZ_MATRIX_SIZE(y_6), .weights = w_6, .bias = b_6, .output = y_6},
    [6] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SEVENTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SEVENTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_7), .length_of_bias = UZ_MATRIX_SIZE(b_7), .length_of_output = UZ_MATRIX_SIZE(y_7), .weights = w_7, .bias = b_7, .output = y_7},
    [7] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_SEVENTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_out), .length_of_bias = UZ_MATRIX_SIZE(b_out), .length_of_output = UZ_MATRIX_SIZE(y_out), .weights = w_out, .bias = b_out, .output = y_out}};
struct uz_nn_layer_config software_nn_config_6N[7] = {
    [0] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .number_of_inputs = NUMBER_OF_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(w_1), .length_of_bias = UZ_MATRIX_SIZE(b_1), .length_of_output = UZ_MATRIX_SIZE(y_1), .weights = w_1, .bias = b_1, .output = y_1},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4},
    [4] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_5), .length_of_bias = UZ_MATRIX_SIZE(b_5), .length_of_output = UZ_MATRIX_SIZE(y_5), .weights = w_5, .bias = b_5, .output = y_5},
    [5] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SIXTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_6), .length_of_bias = UZ_MATRIX_SIZE(b_6), .length_of_output = UZ_MATRIX_SIZE(y_6), .weights = w_6, .bias = b_6, .output = y_6},
    [6] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_SIXTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_out), .length_of_bias = UZ_MATRIX_SIZE(b_out), .length_of_output = UZ_MATRIX_SIZE(y_out), .weights = w_out, .bias = b_out, .output = y_out}};
struct uz_nn_layer_config software_nn_config_5N[6] = {
    [0] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .number_of_inputs = NUMBER_OF_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(w_1), .length_of_bias = UZ_MATRIX_SIZE(b_1), .length_of_output = UZ_MATRIX_SIZE(y_1), .weights = w_1, .bias = b_1, .output = y_1},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4},
    [4] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_5), .length_of_bias = UZ_MATRIX_SIZE(b_5), .length_of_output = UZ_MATRIX_SIZE(y_5), .weights = w_5, .bias = b_5, .output = y_5},
    [5] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIFTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_out), .length_of_bias = UZ_MATRIX_SIZE(b_out), .length_of_output = UZ_MATRIX_SIZE(y_out), .weights = w_out, .bias = b_out, .output = y_out}};
struct uz_nn_layer_config software_nn_config_4N[5] = {
    [0] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .number_of_inputs = NUMBER_OF_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(w_1), .length_of_bias = UZ_MATRIX_SIZE(b_1), .length_of_output = UZ_MATRIX_SIZE(y_1), .weights = w_1, .bias = b_1, .output = y_1},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4},
    [4] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_out), .length_of_bias = UZ_MATRIX_SIZE(b_out), .length_of_output = UZ_MATRIX_SIZE(y_out), .weights = w_out, .bias = b_out, .output = y_out}};
struct uz_nn_layer_config software_nn_config_3N[4] = {
    [0] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .number_of_inputs = NUMBER_OF_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(w_1), .length_of_bias = UZ_MATRIX_SIZE(b_1), .length_of_output = UZ_MATRIX_SIZE(y_1), .weights = w_1, .bias = b_1, .output = y_1},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_out), .length_of_bias = UZ_MATRIX_SIZE(b_out), .length_of_output = UZ_MATRIX_SIZE(y_out), .weights = w_out, .bias = b_out, .output = y_out}};
struct uz_nn_layer_config software_nn_config_2N[3] = {
    [0] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .number_of_inputs = NUMBER_OF_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(w_1), .length_of_bias = UZ_MATRIX_SIZE(b_1), .length_of_output = UZ_MATRIX_SIZE(y_1), .weights = w_1, .bias = b_1, .output = y_1},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_out), .length_of_bias = UZ_MATRIX_SIZE(b_out), .length_of_output = UZ_MATRIX_SIZE(y_out), .weights = w_out, .bias = b_out, .output = y_out}};
struct uz_nn_layer_config software_nn_config_1N[2] = {
    [0] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .number_of_inputs = NUMBER_OF_INPUTS, .length_of_weights = UZ_MATRIX_SIZE(w_1), .length_of_bias = UZ_MATRIX_SIZE(b_1), .length_of_output = UZ_MATRIX_SIZE(y_1), .weights = w_1, .bias = b_1, .output = y_1},
    [1] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_out), .length_of_bias = UZ_MATRIX_SIZE(b_out), .length_of_output = UZ_MATRIX_SIZE(y_out), .weights = w_out, .bias = b_out, .output = y_out}};

#define BASE_ADDRESS 0xF0000000
#define ZERO_BASE_ADDRESS 0x00000000
struct uz_matrix_t input_matrix={0};
struct uz_matrix_t output_matrix={0};
struct uz_NN_acc_config_t config = {
    .base_address = BASE_ADDRESS,
    .software_network = NULL};

uz_NN_acc_t *successful_init_10_layer(void);
uz_NN_acc_t *successful_init_10_layer(void) {
    config.software_network = uz_nn_init(software_nn_config_10N, 11);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS); 
    uz_NN_acc_hw_set_L_1_Weights_Data_Expect(BASE_ADDRESS,&w_1[0]);
    uz_NN_acc_hw_set_L_1_Bias_Data_Expect(BASE_ADDRESS,&b_1[0]);
    uz_NN_acc_hw_set_L_2_Weights_Data_Expect(BASE_ADDRESS,&w_2[0]);
    uz_NN_acc_hw_set_L_2_Bias_Data_Expect(BASE_ADDRESS,&b_2[0]);
    uz_NN_acc_hw_set_L_3_Weights_Data_Expect(BASE_ADDRESS,&w_3[0]);
    uz_NN_acc_hw_set_L_3_Bias_Data_Expect(BASE_ADDRESS,&b_3[0]);
    uz_NN_acc_hw_set_L_4_Weights_Data_Expect(BASE_ADDRESS,&w_4[0]);
    uz_NN_acc_hw_set_L_4_Bias_Data_Expect(BASE_ADDRESS,&b_4[0]);
    uz_NN_acc_hw_set_L_5_Weights_Data_Expect(BASE_ADDRESS,&w_5[0]);
    uz_NN_acc_hw_set_L_5_Bias_Data_Expect(BASE_ADDRESS,&b_5[0]);
    uz_NN_acc_hw_set_L_6_Weights_Data_Expect(BASE_ADDRESS,&w_6[0]);
    uz_NN_acc_hw_set_L_6_Bias_Data_Expect(BASE_ADDRESS,&b_6[0]);
    uz_NN_acc_hw_set_L_7_Weights_Data_Expect(BASE_ADDRESS,&w_7[0]);
    uz_NN_acc_hw_set_L_7_Bias_Data_Expect(BASE_ADDRESS,&b_7[0]);
    uz_NN_acc_hw_set_L_8_Weights_Data_Expect(BASE_ADDRESS,&w_8[0]);
    uz_NN_acc_hw_set_L_8_Bias_Data_Expect(BASE_ADDRESS,&b_8[0]);
    uz_NN_acc_hw_set_L_9_Weights_Data_Expect(BASE_ADDRESS,&w_9[0]);
    uz_NN_acc_hw_set_L_9_Bias_Data_Expect(BASE_ADDRESS,&b_9[0]);
    uz_NN_acc_hw_set_L_10_Weights_Data_Expect(BASE_ADDRESS,&w_10[0]);
    uz_NN_acc_hw_set_L_10_Bias_Data_Expect(BASE_ADDRESS,&b_10[0]);
    uz_NN_acc_hw_set_L_Output_Weights_Data_Expect(BASE_ADDRESS,&w_out[0]);
    uz_NN_acc_hw_set_L_Output_Bias_Data_Expect(BASE_ADDRESS,&b_out[0]);
    uz_NN_acc_hw_set_Observation_size_Expect(BASE_ADDRESS,NUMBER_OF_INPUTS);
    uz_NN_acc_hw_set_Observation_Data_Expect(BASE_ADDRESS,&x[0]);
    uz_NN_acc_hw_set_Action_size_Expect(BASE_ADDRESS,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Actions_Data_Expect(BASE_ADDRESS,&y_out[0]);
    Xil_DCacheFlushRange_CMockExpect(172,((INTPTR)((INTPTR*)output)),32U*4U);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_start_Expect(BASE_ADDRESS);
    uz_NN_acc_hw_get_copy_flag_out_ExpectAndReturn(BASE_ADDRESS,true); 
    uz_NN_acc_hw_get_matrices_updated_out_ExpectAndReturn(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,false);
    uz_NN_acc_hw_set_compute_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_t *instance = uz_NN_acc_init(config,input,output);
    return(instance);
}
uz_NN_acc_t *successful_init_9_layer(void);
uz_NN_acc_t *successful_init_9_layer(void) {
    config.software_network = uz_nn_init(software_nn_config_9N, 10);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS); 
    uz_NN_acc_hw_set_L_1_Weights_Data_Expect(BASE_ADDRESS,&w_1[0]);
    uz_NN_acc_hw_set_L_1_Bias_Data_Expect(BASE_ADDRESS,&b_1[0]);
    uz_NN_acc_hw_set_L_2_Weights_Data_Expect(BASE_ADDRESS,&w_2[0]);
    uz_NN_acc_hw_set_L_2_Bias_Data_Expect(BASE_ADDRESS,&b_2[0]);
    uz_NN_acc_hw_set_L_3_Weights_Data_Expect(BASE_ADDRESS,&w_3[0]);
    uz_NN_acc_hw_set_L_3_Bias_Data_Expect(BASE_ADDRESS,&b_3[0]);
    uz_NN_acc_hw_set_L_4_Weights_Data_Expect(BASE_ADDRESS,&w_4[0]);
    uz_NN_acc_hw_set_L_4_Bias_Data_Expect(BASE_ADDRESS,&b_4[0]);
    uz_NN_acc_hw_set_L_5_Weights_Data_Expect(BASE_ADDRESS,&w_5[0]);
    uz_NN_acc_hw_set_L_5_Bias_Data_Expect(BASE_ADDRESS,&b_5[0]);
    uz_NN_acc_hw_set_L_6_Weights_Data_Expect(BASE_ADDRESS,&w_6[0]);
    uz_NN_acc_hw_set_L_6_Bias_Data_Expect(BASE_ADDRESS,&b_6[0]);
    uz_NN_acc_hw_set_L_7_Weights_Data_Expect(BASE_ADDRESS,&w_7[0]);
    uz_NN_acc_hw_set_L_7_Bias_Data_Expect(BASE_ADDRESS,&b_7[0]);
    uz_NN_acc_hw_set_L_8_Weights_Data_Expect(BASE_ADDRESS,&w_8[0]);
    uz_NN_acc_hw_set_L_8_Bias_Data_Expect(BASE_ADDRESS,&b_8[0]);
    uz_NN_acc_hw_set_L_9_Weights_Data_Expect(BASE_ADDRESS,&w_9[0]);
    uz_NN_acc_hw_set_L_9_Bias_Data_Expect(BASE_ADDRESS,&b_9[0]);
    uz_NN_acc_hw_set_L_Output_Weights_Data_Expect(BASE_ADDRESS,&w_out[0]);
    uz_NN_acc_hw_set_L_Output_Bias_Data_Expect(BASE_ADDRESS,&b_out[0]);
    uz_NN_acc_hw_set_Observation_size_Expect(BASE_ADDRESS,NUMBER_OF_INPUTS);
    uz_NN_acc_hw_set_Observation_Data_Expect(BASE_ADDRESS,&x[0]);
    uz_NN_acc_hw_set_Action_size_Expect(BASE_ADDRESS,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Actions_Data_Expect(BASE_ADDRESS,&y_out[0]);
    Xil_DCacheFlushRange_CMockExpect(172,((INTPTR)((INTPTR*)output)),32U*4U);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_start_Expect(BASE_ADDRESS);
    uz_NN_acc_hw_get_copy_flag_out_ExpectAndReturn(BASE_ADDRESS,true); 
    uz_NN_acc_hw_get_matrices_updated_out_ExpectAndReturn(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,false);
    uz_NN_acc_hw_set_compute_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_t *instance = uz_NN_acc_init(config,input,output);
    return(instance);
}
uz_NN_acc_t *successful_init_8_layer(void);
uz_NN_acc_t *successful_init_8_layer(void) {
    config.software_network = uz_nn_init(software_nn_config_8N, 9);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS); 
    uz_NN_acc_hw_set_L_1_Weights_Data_Expect(BASE_ADDRESS,&w_1[0]);
    uz_NN_acc_hw_set_L_1_Bias_Data_Expect(BASE_ADDRESS,&b_1[0]);
    uz_NN_acc_hw_set_L_2_Weights_Data_Expect(BASE_ADDRESS,&w_2[0]);
    uz_NN_acc_hw_set_L_2_Bias_Data_Expect(BASE_ADDRESS,&b_2[0]);
    uz_NN_acc_hw_set_L_3_Weights_Data_Expect(BASE_ADDRESS,&w_3[0]);
    uz_NN_acc_hw_set_L_3_Bias_Data_Expect(BASE_ADDRESS,&b_3[0]);
    uz_NN_acc_hw_set_L_4_Weights_Data_Expect(BASE_ADDRESS,&w_4[0]);
    uz_NN_acc_hw_set_L_4_Bias_Data_Expect(BASE_ADDRESS,&b_4[0]);
    uz_NN_acc_hw_set_L_5_Weights_Data_Expect(BASE_ADDRESS,&w_5[0]);
    uz_NN_acc_hw_set_L_5_Bias_Data_Expect(BASE_ADDRESS,&b_5[0]);
    uz_NN_acc_hw_set_L_6_Weights_Data_Expect(BASE_ADDRESS,&w_6[0]);
    uz_NN_acc_hw_set_L_6_Bias_Data_Expect(BASE_ADDRESS,&b_6[0]);
    uz_NN_acc_hw_set_L_7_Weights_Data_Expect(BASE_ADDRESS,&w_7[0]);
    uz_NN_acc_hw_set_L_7_Bias_Data_Expect(BASE_ADDRESS,&b_7[0]);
    uz_NN_acc_hw_set_L_8_Weights_Data_Expect(BASE_ADDRESS,&w_8[0]);
    uz_NN_acc_hw_set_L_8_Bias_Data_Expect(BASE_ADDRESS,&b_8[0]);
    uz_NN_acc_hw_set_L_Output_Weights_Data_Expect(BASE_ADDRESS,&w_out[0]);
    uz_NN_acc_hw_set_L_Output_Bias_Data_Expect(BASE_ADDRESS,&b_out[0]);
    uz_NN_acc_hw_set_Observation_size_Expect(BASE_ADDRESS,NUMBER_OF_INPUTS);
    uz_NN_acc_hw_set_Observation_Data_Expect(BASE_ADDRESS,&x[0]);
    uz_NN_acc_hw_set_Action_size_Expect(BASE_ADDRESS,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Actions_Data_Expect(BASE_ADDRESS,&y_out[0]);
    Xil_DCacheFlushRange_CMockExpect(172,((INTPTR)((INTPTR*)output)),32U*4U);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_start_Expect(BASE_ADDRESS);
    uz_NN_acc_hw_get_copy_flag_out_ExpectAndReturn(BASE_ADDRESS,true); 
    uz_NN_acc_hw_get_matrices_updated_out_ExpectAndReturn(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,false);
    uz_NN_acc_hw_set_compute_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_t *instance = uz_NN_acc_init(config,input,output);
    return(instance);
}
uz_NN_acc_t *successful_init_7_layer(void);
uz_NN_acc_t *successful_init_7_layer(void) {
    config.software_network = uz_nn_init(software_nn_config_7N, 8);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS); 
    uz_NN_acc_hw_set_L_1_Weights_Data_Expect(BASE_ADDRESS,&w_1[0]);
    uz_NN_acc_hw_set_L_1_Bias_Data_Expect(BASE_ADDRESS,&b_1[0]);
    uz_NN_acc_hw_set_L_2_Weights_Data_Expect(BASE_ADDRESS,&w_2[0]);
    uz_NN_acc_hw_set_L_2_Bias_Data_Expect(BASE_ADDRESS,&b_2[0]);
    uz_NN_acc_hw_set_L_3_Weights_Data_Expect(BASE_ADDRESS,&w_3[0]);
    uz_NN_acc_hw_set_L_3_Bias_Data_Expect(BASE_ADDRESS,&b_3[0]);
    uz_NN_acc_hw_set_L_4_Weights_Data_Expect(BASE_ADDRESS,&w_4[0]);
    uz_NN_acc_hw_set_L_4_Bias_Data_Expect(BASE_ADDRESS,&b_4[0]);
    uz_NN_acc_hw_set_L_5_Weights_Data_Expect(BASE_ADDRESS,&w_5[0]);
    uz_NN_acc_hw_set_L_5_Bias_Data_Expect(BASE_ADDRESS,&b_5[0]);
    uz_NN_acc_hw_set_L_6_Weights_Data_Expect(BASE_ADDRESS,&w_6[0]);
    uz_NN_acc_hw_set_L_6_Bias_Data_Expect(BASE_ADDRESS,&b_6[0]);
    uz_NN_acc_hw_set_L_7_Weights_Data_Expect(BASE_ADDRESS,&w_7[0]);
    uz_NN_acc_hw_set_L_7_Bias_Data_Expect(BASE_ADDRESS,&b_7[0]);
    uz_NN_acc_hw_set_L_Output_Weights_Data_Expect(BASE_ADDRESS,&w_out[0]);
    uz_NN_acc_hw_set_L_Output_Bias_Data_Expect(BASE_ADDRESS,&b_out[0]);
    uz_NN_acc_hw_set_Observation_size_Expect(BASE_ADDRESS,NUMBER_OF_INPUTS);
    uz_NN_acc_hw_set_Observation_Data_Expect(BASE_ADDRESS,&x[0]);
    uz_NN_acc_hw_set_Action_size_Expect(BASE_ADDRESS,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Actions_Data_Expect(BASE_ADDRESS,&y_out[0]);
    Xil_DCacheFlushRange_CMockExpect(172,((INTPTR)((INTPTR*)output)),32U*4U);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_start_Expect(BASE_ADDRESS);
    uz_NN_acc_hw_get_copy_flag_out_ExpectAndReturn(BASE_ADDRESS,true); 
    uz_NN_acc_hw_get_matrices_updated_out_ExpectAndReturn(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,false);
    uz_NN_acc_hw_set_compute_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_t *instance = uz_NN_acc_init(config,input,output);
    return(instance);
}
uz_NN_acc_t *successful_init_6_layer(void);
uz_NN_acc_t *successful_init_6_layer(void) {
    config.software_network = uz_nn_init(software_nn_config_6N, 7);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS); 
    uz_NN_acc_hw_set_L_1_Weights_Data_Expect(BASE_ADDRESS,&w_1[0]);
    uz_NN_acc_hw_set_L_1_Bias_Data_Expect(BASE_ADDRESS,&b_1[0]);
    uz_NN_acc_hw_set_L_2_Weights_Data_Expect(BASE_ADDRESS,&w_2[0]);
    uz_NN_acc_hw_set_L_2_Bias_Data_Expect(BASE_ADDRESS,&b_2[0]);
    uz_NN_acc_hw_set_L_3_Weights_Data_Expect(BASE_ADDRESS,&w_3[0]);
    uz_NN_acc_hw_set_L_3_Bias_Data_Expect(BASE_ADDRESS,&b_3[0]);
    uz_NN_acc_hw_set_L_4_Weights_Data_Expect(BASE_ADDRESS,&w_4[0]);
    uz_NN_acc_hw_set_L_4_Bias_Data_Expect(BASE_ADDRESS,&b_4[0]);
    uz_NN_acc_hw_set_L_5_Weights_Data_Expect(BASE_ADDRESS,&w_5[0]);
    uz_NN_acc_hw_set_L_5_Bias_Data_Expect(BASE_ADDRESS,&b_5[0]);
    uz_NN_acc_hw_set_L_6_Weights_Data_Expect(BASE_ADDRESS,&w_6[0]);
    uz_NN_acc_hw_set_L_6_Bias_Data_Expect(BASE_ADDRESS,&b_6[0]);
    uz_NN_acc_hw_set_L_Output_Weights_Data_Expect(BASE_ADDRESS,&w_out[0]);
    uz_NN_acc_hw_set_L_Output_Bias_Data_Expect(BASE_ADDRESS,&b_out[0]);
    uz_NN_acc_hw_set_Observation_size_Expect(BASE_ADDRESS,NUMBER_OF_INPUTS);
    uz_NN_acc_hw_set_Observation_Data_Expect(BASE_ADDRESS,&x[0]);
    uz_NN_acc_hw_set_Action_size_Expect(BASE_ADDRESS,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Actions_Data_Expect(BASE_ADDRESS,&y_out[0]);
    Xil_DCacheFlushRange_CMockExpect(172,((INTPTR)((INTPTR*)output)),32U*4U);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_start_Expect(BASE_ADDRESS);
    uz_NN_acc_hw_get_copy_flag_out_ExpectAndReturn(BASE_ADDRESS,true); 
    uz_NN_acc_hw_get_matrices_updated_out_ExpectAndReturn(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,false);
    uz_NN_acc_hw_set_compute_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_t *instance = uz_NN_acc_init(config,input,output);
    return(instance);
}
uz_NN_acc_t *successful_init_5_layer(void);
uz_NN_acc_t *successful_init_5_layer(void) {
    config.software_network = uz_nn_init(software_nn_config_5N, 6);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS); 
    uz_NN_acc_hw_set_L_1_Weights_Data_Expect(BASE_ADDRESS,&w_1[0]);
    uz_NN_acc_hw_set_L_1_Bias_Data_Expect(BASE_ADDRESS,&b_1[0]);
    uz_NN_acc_hw_set_L_2_Weights_Data_Expect(BASE_ADDRESS,&w_2[0]);
    uz_NN_acc_hw_set_L_2_Bias_Data_Expect(BASE_ADDRESS,&b_2[0]);
    uz_NN_acc_hw_set_L_3_Weights_Data_Expect(BASE_ADDRESS,&w_3[0]);
    uz_NN_acc_hw_set_L_3_Bias_Data_Expect(BASE_ADDRESS,&b_3[0]);
    uz_NN_acc_hw_set_L_4_Weights_Data_Expect(BASE_ADDRESS,&w_4[0]);
    uz_NN_acc_hw_set_L_4_Bias_Data_Expect(BASE_ADDRESS,&b_4[0]);
    uz_NN_acc_hw_set_L_5_Weights_Data_Expect(BASE_ADDRESS,&w_5[0]);
    uz_NN_acc_hw_set_L_5_Bias_Data_Expect(BASE_ADDRESS,&b_5[0]);
    uz_NN_acc_hw_set_L_Output_Weights_Data_Expect(BASE_ADDRESS,&w_out[0]);
    uz_NN_acc_hw_set_L_Output_Bias_Data_Expect(BASE_ADDRESS,&b_out[0]);
    uz_NN_acc_hw_set_Observation_size_Expect(BASE_ADDRESS,NUMBER_OF_INPUTS);
    uz_NN_acc_hw_set_Observation_Data_Expect(BASE_ADDRESS,&x[0]);
    uz_NN_acc_hw_set_Action_size_Expect(BASE_ADDRESS,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Actions_Data_Expect(BASE_ADDRESS,&y_out[0]);
    Xil_DCacheFlushRange_CMockExpect(172,((INTPTR)((INTPTR*)output)),32U*4U);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_start_Expect(BASE_ADDRESS);
    uz_NN_acc_hw_get_copy_flag_out_ExpectAndReturn(BASE_ADDRESS,true); 
    uz_NN_acc_hw_get_matrices_updated_out_ExpectAndReturn(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,false);
    uz_NN_acc_hw_set_compute_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_t *instance = uz_NN_acc_init(config,input,output);
    return(instance);
}
uz_NN_acc_t *successful_init_4_layer(void);
uz_NN_acc_t *successful_init_4_layer(void) {
    config.software_network = uz_nn_init(software_nn_config_4N, 5);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS); 
    uz_NN_acc_hw_set_L_1_Weights_Data_Expect(BASE_ADDRESS,&w_1[0]);
    uz_NN_acc_hw_set_L_1_Bias_Data_Expect(BASE_ADDRESS,&b_1[0]);
    uz_NN_acc_hw_set_L_2_Weights_Data_Expect(BASE_ADDRESS,&w_2[0]);
    uz_NN_acc_hw_set_L_2_Bias_Data_Expect(BASE_ADDRESS,&b_2[0]);
    uz_NN_acc_hw_set_L_3_Weights_Data_Expect(BASE_ADDRESS,&w_3[0]);
    uz_NN_acc_hw_set_L_3_Bias_Data_Expect(BASE_ADDRESS,&b_3[0]);
    uz_NN_acc_hw_set_L_4_Weights_Data_Expect(BASE_ADDRESS,&w_4[0]);
    uz_NN_acc_hw_set_L_4_Bias_Data_Expect(BASE_ADDRESS,&b_4[0]);
    uz_NN_acc_hw_set_L_Output_Weights_Data_Expect(BASE_ADDRESS,&w_out[0]);
    uz_NN_acc_hw_set_L_Output_Bias_Data_Expect(BASE_ADDRESS,&b_out[0]);
    uz_NN_acc_hw_set_Observation_size_Expect(BASE_ADDRESS,NUMBER_OF_INPUTS);
    uz_NN_acc_hw_set_Observation_Data_Expect(BASE_ADDRESS,&x[0]);
    uz_NN_acc_hw_set_Action_size_Expect(BASE_ADDRESS,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Actions_Data_Expect(BASE_ADDRESS,&y_out[0]);
    Xil_DCacheFlushRange_CMockExpect(172,((INTPTR)((INTPTR*)output)),32U*4U);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_start_Expect(BASE_ADDRESS);
    uz_NN_acc_hw_get_copy_flag_out_ExpectAndReturn(BASE_ADDRESS,true); 
    uz_NN_acc_hw_get_matrices_updated_out_ExpectAndReturn(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,false);
    uz_NN_acc_hw_set_compute_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_t *instance = uz_NN_acc_init(config,input,output);
    return(instance);
}
uz_NN_acc_t *successful_init_3_layer(void);
uz_NN_acc_t *successful_init_3_layer(void) {
    config.software_network = uz_nn_init(software_nn_config_3N, 4);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS); 
    uz_NN_acc_hw_set_L_1_Weights_Data_Expect(BASE_ADDRESS,&w_1[0]);
    uz_NN_acc_hw_set_L_1_Bias_Data_Expect(BASE_ADDRESS,&b_1[0]);
    uz_NN_acc_hw_set_L_2_Weights_Data_Expect(BASE_ADDRESS,&w_2[0]);
    uz_NN_acc_hw_set_L_2_Bias_Data_Expect(BASE_ADDRESS,&b_2[0]);
    uz_NN_acc_hw_set_L_3_Weights_Data_Expect(BASE_ADDRESS,&w_3[0]);
    uz_NN_acc_hw_set_L_3_Bias_Data_Expect(BASE_ADDRESS,&b_3[0]);
    uz_NN_acc_hw_set_L_Output_Weights_Data_Expect(BASE_ADDRESS,&w_out[0]);
    uz_NN_acc_hw_set_L_Output_Bias_Data_Expect(BASE_ADDRESS,&b_out[0]);
    uz_NN_acc_hw_set_Observation_size_Expect(BASE_ADDRESS,NUMBER_OF_INPUTS);
    uz_NN_acc_hw_set_Observation_Data_Expect(BASE_ADDRESS,&x[0]);
    uz_NN_acc_hw_set_Action_size_Expect(BASE_ADDRESS,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Actions_Data_Expect(BASE_ADDRESS,&y_out[0]);
    Xil_DCacheFlushRange_CMockExpect(172,((INTPTR)((INTPTR*)output)),32U*4U);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_start_Expect(BASE_ADDRESS);
    uz_NN_acc_hw_get_copy_flag_out_ExpectAndReturn(BASE_ADDRESS,true); 
    uz_NN_acc_hw_get_matrices_updated_out_ExpectAndReturn(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,false);
    uz_NN_acc_hw_set_compute_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_t *instance = uz_NN_acc_init(config,input,output);
    return(instance);
}
uz_NN_acc_t *successful_init_2_layer(void);
uz_NN_acc_t *successful_init_2_layer(void) {
    config.software_network = uz_nn_init(software_nn_config_2N, 3);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS); 
    uz_NN_acc_hw_set_L_1_Weights_Data_Expect(BASE_ADDRESS,&w_1[0]);
    uz_NN_acc_hw_set_L_1_Bias_Data_Expect(BASE_ADDRESS,&b_1[0]);
    uz_NN_acc_hw_set_L_2_Weights_Data_Expect(BASE_ADDRESS,&w_2[0]);
    uz_NN_acc_hw_set_L_2_Bias_Data_Expect(BASE_ADDRESS,&b_2[0]);
    uz_NN_acc_hw_set_L_Output_Weights_Data_Expect(BASE_ADDRESS,&w_out[0]);
    uz_NN_acc_hw_set_L_Output_Bias_Data_Expect(BASE_ADDRESS,&b_out[0]);
    uz_NN_acc_hw_set_Observation_size_Expect(BASE_ADDRESS,NUMBER_OF_INPUTS);
    uz_NN_acc_hw_set_Observation_Data_Expect(BASE_ADDRESS,&x[0]);
    uz_NN_acc_hw_set_Action_size_Expect(BASE_ADDRESS,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Actions_Data_Expect(BASE_ADDRESS,&y_out[0]);
    Xil_DCacheFlushRange_CMockExpect(172,((INTPTR)((INTPTR*)output)),32U*4U);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_start_Expect(BASE_ADDRESS);
    uz_NN_acc_hw_get_copy_flag_out_ExpectAndReturn(BASE_ADDRESS,true); 
    uz_NN_acc_hw_get_matrices_updated_out_ExpectAndReturn(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,false);
    uz_NN_acc_hw_set_compute_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_t *instance = uz_NN_acc_init(config,input,output);
    return(instance);
}
uz_NN_acc_t *successful_init_1_layer(void);
uz_NN_acc_t *successful_init_1_layer(void) {
    config.software_network = uz_nn_init(software_nn_config_1N, 2);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS); 
    uz_NN_acc_hw_set_L_1_Weights_Data_Expect(BASE_ADDRESS,&w_1[0]);
    uz_NN_acc_hw_set_L_1_Bias_Data_Expect(BASE_ADDRESS,&b_1[0]);
    uz_NN_acc_hw_set_L_Output_Weights_Data_Expect(BASE_ADDRESS,&w_out[0]);
    uz_NN_acc_hw_set_L_Output_Bias_Data_Expect(BASE_ADDRESS,&b_out[0]);
    uz_NN_acc_hw_set_Observation_size_Expect(BASE_ADDRESS,NUMBER_OF_INPUTS);
    uz_NN_acc_hw_set_Observation_Data_Expect(BASE_ADDRESS,&x[0]);
    uz_NN_acc_hw_set_Action_size_Expect(BASE_ADDRESS,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Actions_Data_Expect(BASE_ADDRESS,&y_out[0]);
    Xil_DCacheFlushRange_CMockExpect(172,((INTPTR)((INTPTR*)output)),32U*4U);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_start_Expect(BASE_ADDRESS);
    uz_NN_acc_hw_get_copy_flag_out_ExpectAndReturn(BASE_ADDRESS,true); 
    uz_NN_acc_hw_get_matrices_updated_out_ExpectAndReturn(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,false);
    uz_NN_acc_hw_set_compute_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_t *instance = uz_NN_acc_init(config,input,output);
    return(instance);
}
void test_uz_NN_acc_init_successful(void) {
    successful_init_10_layer();
    successful_init_9_layer();
    successful_init_8_layer();
    successful_init_7_layer();
    successful_init_6_layer();
    successful_init_5_layer();
    successful_init_4_layer();
    successful_init_3_layer();
    successful_init_2_layer();
    successful_init_1_layer();
}

void test_uz_NN_acc_init_assert_base_address_ZERO(void) {
    config.base_address = ZERO_BASE_ADDRESS;
    config.software_network = uz_nn_init(software_nn_config_5N, 6);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS);
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_init_assert_Software_Network_NULL(void) {
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS);
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_init_assert_Observation_Null(void) {
    config.software_network = uz_nn_init(software_nn_config_5N, 6);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS);
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,NULL,output));
}

void test_uz_NN_acc_init_assert_Action_Null(void) {
    config.software_network = uz_nn_init(software_nn_config_5N, 6);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,NULL));
}

void test_uz_NN_acc_init_assert_Observation_size(void) {
    config.base_address = BASE_ADDRESS;
    config.software_network = uz_nn_init(software_nn_config_5N, 6);
    float x_test[40] = {0};
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x_test,UZ_MATRIX_SIZE(x_test),1U,40U);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_out,UZ_MATRIX_SIZE(y_out),1U,NUMBER_OF_OUTPUTS);
    //too many entries in observation (max=24)
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_init_assert_Action_size(void) {
    config.base_address = BASE_ADDRESS;
    config.software_network = uz_nn_init(software_nn_config_5N, 6);
    float y_test[30] = {0};
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_test,UZ_MATRIX_SIZE(y_test),1U,30U);
    //too many entries in action (max=12)
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}


void test_uz_NN_acc_ff_blocking_assert_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_ff_blocking(NULL));
}

void test_uz_NN_acc_ff_non_blocking_assert_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_ff_non_blocking(NULL));
}

void test_uz_NN_acc_get_result_blocking_assert_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_get_result_blocking(NULL));
}


#endif