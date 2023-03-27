// configuration of neural network
#define NUMBER_OF_INPUTS_9N 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 128

#include "../../main.h"

#if NN_9_INPUT_1_128==1

extern DS_Data Global_Data;

// config structs neural network
// read in weights and bias from .csv
//for 9 observations
float x_9[NUMBER_OF_INPUTS_9N] = {0};
static float w_1_9[NUMBER_OF_INPUTS_9N * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
	#include "../../ac_layer1_weights.csv"
};

static float b_1_9[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
	#include "../../ac_layer1_bias.csv"
};

static float y_1_9[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float w_2_9[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
	#include "../../ac_layer_out_weights.csv"
};
static float b_2_9[NUMBER_OF_OUTPUTS] = {
	#include "../../ac_layer_out_bias.csv"
};

static float y_2_9[NUMBER_OF_OUTPUTS] = {0};

// initialize config struct and activation function
struct uz_nn_layer_config config_9nn[2] = {
[0] = {
    .activation_function = activation_ReLU,
    .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .number_of_inputs = NUMBER_OF_INPUTS_9N,
    .length_of_weights = UZ_MATRIX_SIZE(w_1_9),
    .length_of_bias = UZ_MATRIX_SIZE(b_1_9),
    .length_of_output = UZ_MATRIX_SIZE(y_1_9),
    .weights = w_1_9,
    .bias = b_1_9,
    .output = y_1_9},
[1] = {
	.activation_function = activation_tanh,
    .number_of_neurons = NUMBER_OF_OUTPUTS,
    .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .length_of_weights = UZ_MATRIX_SIZE(w_2_9),
    .length_of_bias = UZ_MATRIX_SIZE(b_2_9),
    .length_of_output = UZ_MATRIX_SIZE(y_2_9),
    .weights = w_2_9,
    .bias = b_2_9,
    .output = y_2_9}
};

//// config structs neural network
//// read in weights and bias from .csv
////for 7 observations
//float x_7[NUMBER_OF_INPUTS_7N] = {0};
//static float w_1_7[NUMBER_OF_INPUTS_7N * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
//	#include "ac_layer1_weights.csv"
//};
//
//static float b_1_7[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
//	#include "ac_layer1_bias.csv"
//};
//
//static float y_1_7[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
//static float w_2_7[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
//	#include "ac_layer_out_weights.csv"
//};
//static float b_2_7[NUMBER_OF_OUTPUTS] = {
//	#include "ac_layer_out_bias.csv"
//};
//float y_2_7[NUMBER_OF_OUTPUTS] = {0};
//// initialize config struct and activation function
//

struct uz_matrix_t input_matrix_9n={0};

void nn_9_input_1_128_init(void){

Global_Data.objects.matrix_input_9n=uz_matrix_init(&input_matrix_9n,x_9,UZ_MATRIX_SIZE(x_9),1U,NUMBER_OF_INPUTS_9N);
Global_Data.objects.nn_layer_9n = uz_nn_init(config_9nn, 2U);

}

#endif
