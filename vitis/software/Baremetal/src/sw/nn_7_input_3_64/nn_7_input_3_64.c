
// configuration of neural network
#define NUMBER_OF_INPUTS_9N 13
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64

#include "../../main.h"
#include "xparameters.h"
#include "../../IP_Cores/uz_mlp_three_layer/uz_mlp_three_layer.h"
#include "../../uz/uz_nn/uz_nn_activation_functions.h"
extern DS_Data Global_Data;

#if NN_7_INPUT_3_64 == 1

// config structs neural network
// read in weights and bias from .csv
// for 9 observations
float x_9[NUMBER_OF_INPUTS_9N] = {0};
static float w_1_9[NUMBER_OF_INPUTS_9N * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../../ac_layer1_weights.csv"
};

static float b_1_9[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../../ac_layer1_bias.csv"
};

static float y_1_9[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};

float w_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../../ac_layer2_weights.csv"
};
float b_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../../ac_layer2_bias.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};

float w_3[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../../ac_layer3_weights.csv"
};
float b_3[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../../ac_layer3_bias.csv"
};
float y_3[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};

// output
static float w_4_9[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../../ac_layer_out_weights.csv"
};

static float b_4_9[NUMBER_OF_OUTPUTS] = {
#include "../../ac_layer_out_bias.csv"
};

static float y_4_9[NUMBER_OF_OUTPUTS] = {0};

// initialize config struct and activation function
struct uz_nn_layer_config config_9nn[4] = {
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
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4_9), .length_of_bias = UZ_MATRIX_SIZE(b_4_9), .length_of_output = UZ_MATRIX_SIZE(y_4_9), .weights = w_4_9, .bias = b_4_9, .output = y_4_9}};

//// config structs neural network
//// read in weights and bias from .csv
////for 7 observations
// float x_7[NUMBER_OF_INPUTS_7N] = {0};
// static float w_1_7[NUMBER_OF_INPUTS_7N * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
//	#include "ac_layer1_weights.csv"
// };
//
// static float b_1_7[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
//	#include "ac_layer1_bias.csv"
// };
//
// static float y_1_7[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
// static float w_2_7[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
//	#include "ac_layer_out_weights.csv"
// };
// static float b_2_7[NUMBER_OF_OUTPUTS] = {
//	#include "ac_layer_out_bias.csv"
// };
// float y_2_7[NUMBER_OF_OUTPUTS] = {0};
//// initialize config struct and activation function
//

struct uz_matrix_t input_matrix_9n = {0};
struct uz_matrix_t output_data = {0};
uz_matrix_t *p_output_data;
float mlp_ip_output[2] = {0};
uz_mlp_three_layer_ip_t *mlp_ip_instance;
extern uz_matrix_t *matrix_output_7n;

void nn_7_input_3_64_init(void)
{

    Global_Data.objects.matrix_input_7n = uz_matrix_init(&input_matrix_9n, x_9, UZ_MATRIX_SIZE(x_9), 1U, NUMBER_OF_INPUTS_9N);
    Global_Data.objects.nn_layer_7n = uz_nn_init(config_9nn, 4U);

    struct uz_mlp_three_layer_ip_config_t config = {
        .base_address = XPAR_UZ_USER_UZ_MLP_THREE_LAYER_0_BASEADDR,
        .use_axi_input = true,
        .software_network = Global_Data.objects.nn_layer_7n};
    mlp_ip_instance = uz_mlp_three_layer_ip_init(config);
    p_output_data = uz_matrix_init(&output_data, mlp_ip_output, UZ_MATRIX_SIZE(mlp_ip_output), 1, UZ_MATRIX_SIZE(mlp_ip_output));

    //	while(1){
    //
    //
    //	uz_mlp_three_layer_ff_blocking(mlp_ip_instance, Global_Data.objects.matrix_input_9n, p_output_data);
    //// IP-Core only calculates with linear, tanh has to be added manually
    //	mlp_ip_output[0]=uz_nn_activation_function_tanh(mlp_ip_output[0])*27.71281f;
    //	mlp_ip_output[1]=uz_nn_activation_function_tanh(mlp_ip_output[1])*27.71281f;
    //
    //	uz_nn_ff(Global_Data.objects.nn_layer_9n, Global_Data.objects.matrix_input_9n);
    //	matrix_output_9n = uz_nn_get_output_data(Global_Data.objects.nn_layer_9n);
    //	uz_matrix_multiply_by_scalar(matrix_output_9n,27.71281f); // scaling layer of nn
    //	}
}

#endif

//    // y_4 (calculated by software network) is now "equal" (minus rounding error due to fixed point)
//    // to mlp_ip_output (calculated by IP-Core)
//    // Use uz_nn_get_output_data to get software nn data for further processing
// }
