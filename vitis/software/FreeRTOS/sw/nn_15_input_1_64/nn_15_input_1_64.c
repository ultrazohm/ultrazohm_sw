// configuration of neural network
#define NUMBER_OF_INPUTS_15N 15
#define NUMBER_OF_OUTPUTS 4
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64

#include "../../main.h"

#if NN_15_INPUT_1_64==1

// config structs neural network
// read in weights and bias from .csv
//for 15 observations
float x_15[NUMBER_OF_INPUTS_15N] = {0};
static float w_1_15[NUMBER_OF_INPUTS_15N * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
	#include "ac_layer1_weights.csv"
};

static float b_1_15[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
	#include "ac_layer1_bias.csv"
};

static float y_1_15[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float w_2_15[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
	#include "ac_layer_out_weights.csv"
};
static float b_2_15[NUMBER_OF_OUTPUTS] = {
	#include "ac_layer_out_bias.csv"
};

static float y_2_15[NUMBER_OF_OUTPUTS] = {0};

// initialize config struct and activation function
struct uz_nn_layer_config config_15nn[2] = {
[0] = {
    .activation_function = activation_ReLU,
    .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .number_of_inputs = NUMBER_OF_INPUTS_15N,
    .length_of_weights = UZ_MATRIX_SIZE(w_1_15),
    .length_of_bias = UZ_MATRIX_SIZE(b_1_15),
    .length_of_output = UZ_MATRIX_SIZE(y_1_15),
    .weights = w_1_15,
    .bias = b_1_15,
    .output = y_1_15},
[1] = {
	.activation_function = activation_tanh,
    .number_of_neurons = NUMBER_OF_OUTPUTS,
    .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .length_of_weights = UZ_MATRIX_SIZE(w_2_15),
    .length_of_bias = UZ_MATRIX_SIZE(b_2_15),
    .length_of_output = UZ_MATRIX_SIZE(y_2_15),
    .weights = w_2_15,
    .bias = b_2_15,
    .output = y_2_15}
};


struct uz_matrix_t input_matrix_15n={0};


uz_matrix_t * nn_15_input_1_64_init(void){


return(uz_matrix_init(&input_matrix_15n,x_15,UZ_MATRIX_SIZE(x_15),1U,NUMBER_OF_INPUTS_15N));
}

uz_nn_t * nn_15_input_layer_1_64_init(void) {
	return(uz_nn_init(config_15nn, 2U));
}


#endif
