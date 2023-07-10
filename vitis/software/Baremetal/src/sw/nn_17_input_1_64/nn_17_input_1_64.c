// configuration of neural network
#define NUMBER_OF_INPUTS 17
#define NUMBER_OF_OUTPUTS 4
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64

#include "../../main.h"
extern DS_Data Global_Data;

#if NN_17_INPUT_1_64==1

// config structs neural network
// read in weights and bias from .csv
//for 15 observations
float x_17[NUMBER_OF_INPUTS] = {0};
static float w_1_17[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
	#include "ac_layer1_weights.csv"
};

static float b_1_17[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
	#include "ac_layer1_bias.csv"
};

static float y_1_17[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float w_2_17[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
	#include "ac_layer_out_weights.csv"
};
static float b_2_17[NUMBER_OF_OUTPUTS] = {
	#include "ac_layer_out_bias.csv"
};

static float y_2_17[NUMBER_OF_OUTPUTS] = {0};

// initialize config struct and activation function
struct uz_nn_layer_config config_17nn[2] = {
[0] = {
    .activation_function = activation_ReLU,
    .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .number_of_inputs = NUMBER_OF_INPUTS,
    .length_of_weights = UZ_MATRIX_SIZE(w_1_17),
    .length_of_bias = UZ_MATRIX_SIZE(b_1_17),
    .length_of_output = UZ_MATRIX_SIZE(y_1_17),
    .weights = w_1_17,
    .bias = b_1_17,
    .output = y_1_17},
[1] = {
	.activation_function = activation_tanh,
    .number_of_neurons = NUMBER_OF_OUTPUTS,
    .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .length_of_weights = UZ_MATRIX_SIZE(w_2_17),
    .length_of_bias = UZ_MATRIX_SIZE(b_2_17),
    .length_of_output = UZ_MATRIX_SIZE(y_2_17),
    .weights = w_2_17,
    .bias = b_2_17,
    .output = y_2_17}
};


struct uz_matrix_t input_matrix_17n={0};

void nn_17_input_1_64_init(void){


Global_Data.objects.matrix_input_17n=uz_matrix_init(&input_matrix_17n,x_17,UZ_MATRIX_SIZE(x_17),1U,NUMBER_OF_INPUTS);
Global_Data.objects.nn_layer_17n = uz_nn_init(config_17nn, 2U); //Warning is a GCC 11 bug


}


#endif
