// configuration of neural network
#define NUMBER_OF_INPUTS_20N 20
#define NUMBER_OF_OUTPUTS 4
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64

#include "../../main.h"
extern DS_Data Global_Data;

#if NN_20_INPUT_1_64==1

// config structs neural network
// read in weights and bias from .csv
//for 15 observations
float x_20[NUMBER_OF_INPUTS_20N] = {0};
static float w_1_20[NUMBER_OF_INPUTS_20N * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
	#include "../../Matrix_B1_input.csv"
};

static float b_1_20[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};

static float y_1_20[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float w_2_20[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
	#include "../../Matrix_B2_input.csv"
};
static float b_2_20[NUMBER_OF_OUTPUTS] = {0};

static float y_2_20[NUMBER_OF_OUTPUTS] = {0};

// initialize config struct and activation function
struct uz_nn_layer_config config_20nn[2] = {
[0] = {
    .activation_function = activation_linear,
    .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .number_of_inputs = NUMBER_OF_INPUTS_20N,
    .length_of_weights = UZ_MATRIX_SIZE(w_1_20),
    .length_of_bias = UZ_MATRIX_SIZE(b_1_20),
    .length_of_output = UZ_MATRIX_SIZE(y_1_20),
    .weights = w_1_20,
    .bias = b_1_20,
    .output = y_1_20},
[1] = {
	.activation_function = activation_linear,
    .number_of_neurons = NUMBER_OF_OUTPUTS,
    .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .length_of_weights = UZ_MATRIX_SIZE(w_2_20),
    .length_of_bias = UZ_MATRIX_SIZE(b_2_20),
    .length_of_output = UZ_MATRIX_SIZE(y_2_20),
    .weights = w_2_20,
    .bias = b_2_20,
    .output = y_2_20}
};


struct uz_matrix_t input_matrix_20n={0};

void nn_20_input_1_64_init(void){


Global_Data.objects.matrix_input_20n=uz_matrix_init(&input_matrix_20n,x_20,UZ_MATRIX_SIZE(x_20),1U,NUMBER_OF_INPUTS_20N);
Global_Data.objects.nn_layer_20n = uz_nn_init(config_20nn, 2U); //Warning is a GCC 11 bug


}


#endif
