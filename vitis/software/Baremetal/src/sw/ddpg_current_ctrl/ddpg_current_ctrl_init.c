#include "../../main.h"
extern DS_Data Global_Data;

#define NUMBER_OF_INPUTS 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64

static float x[NUMBER_OF_INPUTS] = {0};
static float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
	#include "ac_layer1_weights.csv"
};
static float b_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
	#include "ac_layer1_bias.csv"
};
static float y_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float w_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
	#include "ac_layer_out_weights.csv"
};
static float b_2[NUMBER_OF_OUTPUTS] = {
	#include "ac_layer_out_bias.csv"
};
static float y_2[NUMBER_OF_OUTPUTS] = {0};

struct uz_nn_layer_config config[2] = {
[0] = {
    .activation_function = activation_ReLU,
    .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .number_of_inputs = NUMBER_OF_INPUTS,
    .length_of_weights = UZ_MATRIX_SIZE(w_1),
    .length_of_bias = UZ_MATRIX_SIZE(b_1),
    .length_of_output = UZ_MATRIX_SIZE(y_1),
    .weights = w_1,
    .bias = b_1,
    .output = y_1},
[1] = {.activation_function = activation_tanh,
        .number_of_neurons = NUMBER_OF_OUTPUTS,
        .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .length_of_weights = UZ_MATRIX_SIZE(w_2),
        .length_of_bias = UZ_MATRIX_SIZE(b_2),
        .length_of_output = UZ_MATRIX_SIZE(y_2),
        .weights = w_2,
        .bias = b_2,
        .output = y_2}
};

struct uz_matrix_t input_matrix = {0};

void ddpg_current_ctrl_init(void){
Global_Data.objects.matrix_input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
Global_Data.objects.nn_layer = uz_nn_init(config, 2); //Warning is a GCC 11 bug
}
