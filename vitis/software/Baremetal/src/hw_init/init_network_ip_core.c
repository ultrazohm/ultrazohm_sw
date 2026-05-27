#include "../uz/uz_nn/uz_nn.h"
#include "../IP_Cores/uz_NN_acc/uz_NN_acc.h"
#include "../main.h"
#include "../include/init_network_ip_core.h"
extern DS_Data Global_Data;

#define NUMBER_OF_INPUTS 9U
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 32U
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 32U
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_HIDDEN_LAYER 2

float x[NUMBER_OF_INPUTS] MEMORY_ALIGN = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {
#include "actor_weights_csv/weights_schicht_1.csv"
};
float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {
#include "actor_weights_csv/bias_schicht_1.csv"
};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {0};

float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {
#include "actor_weights_csv/weights_schicht_2.csv"
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {
#include "actor_weights_csv/bias_schicht_2.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {0};

float w_3[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {
#include "actor_weights_csv/weights_schicht_3.csv"
};
float b_3[NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {
#include "actor_weights_csv/bias_schicht_3.csv"
};
float y_3[NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {0};

struct uz_nn_layer_config software_nn_config[3] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(w_1),
        .length_of_bias = UZ_MATRIX_SIZE(b_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .weights = w_1,
        .bias = b_1,
        .output = y_1},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    //Note:Although IP-Core is hardcoded to activation_linear for the output the specified activation function for the last layer will be applied in software
    [2] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3}};

struct uz_matrix_t input_matrix MEMORY_ALIGN={0};
struct uz_matrix_t output_matrix MEMORY_ALIGN={0};

void init_network(void){
   Global_Data.objects.matrix_input_acc=uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
   Global_Data.objects.matrix_output_acc=uz_matrix_init(&output_matrix,y_3,UZ_MATRIX_SIZE(y_3),1U,NUMBER_OF_OUTPUTS);
   Global_Data.objects.nn_layer_acc = uz_nn_init(software_nn_config, 3U); //Warning is a GCC 11 bug

   struct uz_NN_acc_config_t IP_config = {
                   .software_network = Global_Data.objects.nn_layer_acc,
                   .base_address = XPAR_UZ_NN_2_32_0_S_AXI_CONTROL_BASEADDR
   };
   Global_Data.objects.NN_acc_Instance = uz_NN_acc_init(IP_config, Global_Data.objects.matrix_input_acc, Global_Data.objects.matrix_output_acc);
 }
