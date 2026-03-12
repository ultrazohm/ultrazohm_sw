#include "../uz/uz_nn/uz_nn.h"
#include "../IP_Cores/uz_NN_acc/uz_NN_acc.h"
#include "../main.h"
#include "../include/init_NN_network_ip_core.h"
extern DS_Data Global_Data;


#if NN_3_64_SETUP==1
#define NUMBER_OF_INPUTS 7U  //Might need adjusting
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 64U
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 64U
#define NUMBER_OF_NEURONS_IN_THIRD_LAYER 64U
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_HIDDEN_LAYER 3

float x[NUMBER_OF_INPUTS] MEMORY_ALIGN = {0};
float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {
#include "Weights_Layer_1.csv"//TODO To be changed
};
float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {
#include "Bias_Layer_1.csv"//TODO To be changed
};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {0};

float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {
#include "Weights_Layer_2.csv"//TODO To be changed
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {
#include "Bias_Layer_2.csv"//TODO To be changed
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {0};

float w_3[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {
#include "Weights_Layer_3.csv"//TODO To be changed
};
float b_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] MEMORY_ALIGN = {
#include "Bias_Layer_3.csv"//TODO To be changed
};
float y_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] MEMORY_ALIGN = {0};

float w_4[NUMBER_OF_NEURONS_IN_THIRD_LAYER * NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {
#include "Weights_Layer_out.csv"//TODO To be changed
};
float b_4[NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {
#include "Bias_Layer_out.csv"//TODO To be changed
};
float y_4[NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {0};

struct uz_nn_layer_config software_nn_config[4] = {
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
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    //Note:Although IP-Core is hardcoded to activation_linear for the output the specified activation function for the last layer will be applied in software
    [3] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4}};

struct uz_matrix_t input_matrix MEMORY_ALIGN={0};
struct uz_matrix_t output_matrix MEMORY_ALIGN={0};

void init_NN_network_IP_core(void){
   Global_Data.objects.matrix_input_acc=uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
   Global_Data.objects.matrix_output_acc=uz_matrix_init(&output_matrix,y_4,UZ_MATRIX_SIZE(y_4),1U,NUMBER_OF_OUTPUTS);
   Global_Data.objects.nn_layer_acc = uz_nn_init(software_nn_config, 4U); //Warning is a GCC 11 bug

   struct uz_NN_acc_config_t IP_config = {
                   .software_network = Global_Data.objects.nn_layer_acc,
                   .base_address = XPAR_UZ_USER_UZ_NN_3_64_ACC_0_S_AXI_CONTROL_BASEADDR //May needs adjusting
   };
   Global_Data.objects.NN_acc_Instance = uz_NN_acc_init(IP_config, Global_Data.objects.matrix_input_acc, Global_Data.objects.matrix_output_acc);
 }

#endif

#if NN_5_64_SETUP==1
#define NUMBER_OF_INPUTS 7U  //Might need adjusting
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 64U
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 64U
#define NUMBER_OF_NEURONS_IN_THIRD_LAYER 64U
#define NUMBER_OF_NEURONS_IN_FOURTH_LAYER 64U
#define NUMBER_OF_NEURONS_IN_FITH_LAYER 64U
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_HIDDEN_LAYER 5

float x[NUMBER_OF_INPUTS] MEMORY_ALIGN = {0};
float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {
#include "Weights_Layer_1.csv"//TODO To be changed
};
float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {
#include "Bias_Layer_1.csv"//TODO To be changed
};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {0};

float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {
#include "Weights_Layer_2.csv"//TODO To be changed
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {
#include "Bias_Layer_2.csv"//TODO To be changed
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {0};

float w_3[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {
#include "Weights_Layer_3.csv"//TODO To be changed
};
float b_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] MEMORY_ALIGN = {
#include "Bias_Layer_3.csv"//TODO To be changed
};
float y_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] MEMORY_ALIGN = {0};

float w_4[NUMBER_OF_NEURONS_IN_THIRD_LAYER * NUMBER_OF_NEURONS_IN_FOURTH_LAYER] MEMORY_ALIGN = {
#include "Weights_Layer_4.csv"//TODO To be changed
};
float b_4[NUMBER_OF_NEURONS_IN_FOURTH_LAYER] MEMORY_ALIGN = {
#include "Bias_Layer_4.csv"//TODO To be changed
};
float y_4[NUMBER_OF_NEURONS_IN_FOURTH_LAYER] MEMORY_ALIGN = {0};

float w_5[NUMBER_OF_NEURONS_IN_FITH_LAYER * NUMBER_OF_NEURONS_IN_FOURTH_LAYER] MEMORY_ALIGN = {
#include "Weights_Layer_5.csv"//TODO To be changed
};
float b_5[NUMBER_OF_NEURONS_IN_FITH_LAYER] MEMORY_ALIGN = {
#include "Bias_Layer_5.csv"//TODO To be changed
};
float y_5[NUMBER_OF_NEURONS_IN_FITH_LAYER] MEMORY_ALIGN = {0};

float w_6[NUMBER_OF_NEURONS_IN_FITH_LAYER * NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {
#include "Weights_Layer_out.csv"//TODO To be changed
};
float b_6[NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {
#include "Bias_Layer_out.csv"//TODO To be changed
};
float y_6[NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {0};

struct uz_nn_layer_config software_nn_config[6] = {
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
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
	[3] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4},
	[4] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_FITH_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FOURTH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_5), .length_of_bias = UZ_MATRIX_SIZE(b_5), .length_of_output = UZ_MATRIX_SIZE(y_5), .weights = w_5, .bias = b_5, .output = y_5},
    //Note:Although IP-Core is hardcoded to activation_linear for the output the specified activation function for the last layer will be applied in software
    [5] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_FITH_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_6), .length_of_bias = UZ_MATRIX_SIZE(b_6), .length_of_output = UZ_MATRIX_SIZE(y_6), .weights = w_6, .bias = b_6, .output = y_6}};

struct uz_matrix_t input_matrix MEMORY_ALIGN={0};
struct uz_matrix_t output_matrix MEMORY_ALIGN={0};

void init_NN_network_IP_core(void){
   Global_Data.objects.matrix_input_acc=uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
   Global_Data.objects.matrix_output_acc=uz_matrix_init(&output_matrix,y_6,UZ_MATRIX_SIZE(y_6),1U,NUMBER_OF_OUTPUTS);
   Global_Data.objects.nn_layer_acc = uz_nn_init(software_nn_config, 6U); //Warning is a GCC 11 bug

   struct uz_NN_acc_config_t IP_config = {
                   .software_network = Global_Data.objects.nn_layer_acc,
                   .base_address = XPAR_UZ_USER_UZ_NN_5_64_0_S_AXI_CONTROL_BASEADDR //May needs adjusting
   };
   Global_Data.objects.NN_acc_Instance = uz_NN_acc_init(IP_config, Global_Data.objects.matrix_input_acc, Global_Data.objects.matrix_output_acc);
 }

#endif
