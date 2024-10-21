// configuration of neural network
#define NUMBER_OF_INPUTS 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64

#include "../../main.h"
extern DS_Data Global_Data;

#if NN_9_INPUT_1_64==1

// config structs neural network
// read in weights and bias from .csv
// for 9 observations



float x[NUMBER_OF_INPUTS] = {0};
static float weights1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../../experiments/e113_new_methodology_sigmoid_750k/best_agent/ac_layer1_weights.csv"
};

static float bias1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../../experiments/e113_new_methodology_sigmoid_750k/best_agent/ac_layer1_bias.csv"
};

static float output1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float weights2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../../experiments/e113_new_methodology_sigmoid_750k/best_agent/ac_layer_out_weights.csv"
};
static float bias2[NUMBER_OF_OUTPUTS] = {
#include "../../experiments/e113_new_methodology_sigmoid_750k/best_agent/ac_layer_out_bias.csv"
};

static float output2[NUMBER_OF_OUTPUTS] = {0};

// initialize config struct and activation function
struct uz_nn_layer_config config_nn[2] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(weights1),
        .length_of_bias = UZ_MATRIX_SIZE(bias1),
        .length_of_output = UZ_MATRIX_SIZE(output1),
        .weights = weights1,
        .bias = bias1,
        .output = output1},
    [1] = {
    	.activation_function = activation_tanh,
    	.number_of_neurons = NUMBER_OF_OUTPUTS,
		.number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
		.length_of_weights = UZ_MATRIX_SIZE(weights2),
		.length_of_bias = UZ_MATRIX_SIZE(bias2),
		.length_of_output = UZ_MATRIX_SIZE(output2),
		.weights = weights2,
		.bias = bias2,
		.output = output2}};

struct uz_matrix_t input_matrix = {0};

void nn_init(void)
{

    Global_Data.objects.matrix_input = uz_matrix_init(&input_matrix, x, UZ_MATRIX_SIZE(x), 1U, NUMBER_OF_INPUTS);
    Global_Data.objects.nn_layer = uz_nn_init(config_nn, 2U);
}

#endif

