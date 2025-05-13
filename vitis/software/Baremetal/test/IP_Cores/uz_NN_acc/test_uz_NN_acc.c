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
#define NUMBER_OF_OUTPUTS 4
#define NUMBER_OF_HIDDEN_LAYER 3

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
#include "../uz_mlp_three_layer/layer2_weights.csv"
};
float b_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] = {
#include "../uz_mlp_three_layer/layer3_bias.csv"
};
float y_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] = {0};

float w_4[NUMBER_OF_NEURONS_IN_THIRD_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../uz_mlp_three_layer/layer4_weights.csv"
};
float b_4[NUMBER_OF_OUTPUTS] = {
#include "../uz_mlp_three_layer/layer4_bias.csv"
};
float y_4[NUMBER_OF_OUTPUTS] = {0};
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
    [3] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4}};

#define BASE_ADDRESS 0xF0000000
#define ZERO_BASE_ADDRESS 0x00000000
struct uz_matrix_t input_matrix={0};
struct uz_matrix_t output_matrix={0};
struct uz_NN_acc_config_t config = {
    .base_address = BASE_ADDRESS,
    .software_network = NULL};

uz_NN_acc_t *successful_init(void);
uz_NN_acc_t *successful_init(void) {
    config.software_network = uz_nn_init(software_nn_config, 4);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_4,UZ_MATRIX_SIZE(y_4),1U,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Observation_size_Expect(BASE_ADDRESS,NUMBER_OF_INPUTS);
    uz_NN_acc_hw_set_Observation_Data_Expect(BASE_ADDRESS,&x[0]);
    uz_NN_acc_hw_set_L_1_Weights_Data_Expect(BASE_ADDRESS,&w_1[0]);
    uz_NN_acc_hw_set_L_1_Bias_Data_Expect(BASE_ADDRESS,&b_1[0]);
    uz_NN_acc_hw_set_L_2_Weights_Data_Expect(BASE_ADDRESS,&w_2[0]);
    uz_NN_acc_hw_set_L_2_Bias_Data_Expect(BASE_ADDRESS,&b_2[0]);
    uz_NN_acc_hw_set_L_3_Weights_Data_Expect(BASE_ADDRESS,&w_3[0]);
    uz_NN_acc_hw_set_L_3_Bias_Data_Expect(BASE_ADDRESS,&b_3[0]);
    uz_NN_acc_hw_set_L_Output_Weights_Data_Expect(BASE_ADDRESS,&w_4[0]);
    uz_NN_acc_hw_set_L_Output_Bias_Data_Expect(BASE_ADDRESS,&b_4[0]);
    uz_NN_acc_hw_set_Action_size_Expect(BASE_ADDRESS,NUMBER_OF_OUTPUTS);
    uz_NN_acc_hw_set_Actions_Data_Expect(BASE_ADDRESS,&y_4[0]);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_start_Expect(BASE_ADDRESS);
    uz_NN_acc_hw_get_copy_flag_out_ExpectAndReturn(BASE_ADDRESS,true); 
    uz_NN_acc_hw_get_matrices_updated_out_ExpectAndReturn(BASE_ADDRESS,true);
    uz_NN_acc_hw_set_copy_mats_flag_Expect(BASE_ADDRESS,false);
    uz_NN_acc_t *instance = uz_NN_acc_init(config,input,output);
    return(instance);
}

void test_uz_NN_acc_init_successful(void) {
    successful_init();
}

void test_uz_NN_acc_init_assert_base_address_ZERO(void) {
    config.base_address = ZERO_BASE_ADDRESS;
    config.software_network = uz_nn_init(software_nn_config, 4);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_4,UZ_MATRIX_SIZE(y_4),1U,NUMBER_OF_OUTPUTS);
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_init_assert_Software_Network_NULL(void) {
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_4,UZ_MATRIX_SIZE(y_4),1U,NUMBER_OF_OUTPUTS);
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_init_assert_Observation_Null(void) {
    config.software_network = uz_nn_init(software_nn_config, 4);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_4,UZ_MATRIX_SIZE(y_4),1U,NUMBER_OF_OUTPUTS);
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,NULL,output));
}

void test_uz_NN_acc_init_assert_Action_Null(void) {
    config.software_network = uz_nn_init(software_nn_config, 4);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,NULL));
}

void test_uz_NN_acc_init_assert_Number_of_Layers(void) {
    config.base_address = BASE_ADDRESS;
    struct uz_nn_layer_config software_nn_config_1[3] = {
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
    [2] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4}};

    config.software_network = uz_nn_init(software_nn_config_1, 3);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_4,UZ_MATRIX_SIZE(y_4),1U,NUMBER_OF_OUTPUTS);
    //Not enough layers
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));

    struct uz_nn_layer_config software_nn_config_2[5] = {
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
    [3] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [4] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4}};

    config.software_network = uz_nn_init(software_nn_config_2, 5);
    //Too many layers
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_init_assert_Observation_size(void) {
    config.base_address = BASE_ADDRESS;
    config.software_network = uz_nn_init(software_nn_config, 4);
    float x_test[30] = {0};
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x_test,UZ_MATRIX_SIZE(x_test),1U,30U);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_4,UZ_MATRIX_SIZE(y_4),1U,NUMBER_OF_OUTPUTS);
    //too many entries in observation (max=24)
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_init_assert_Action_size(void) {
    config.base_address = BASE_ADDRESS;
    config.software_network = uz_nn_init(software_nn_config, 4);
    float y_test[30] = {0};
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_test,UZ_MATRIX_SIZE(y_test),1U,30U);
    //too many entries in action (max=12)
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_init_assert_Size_L1_Weights_Bias(void) {
    config.base_address = BASE_ADDRESS;
    float w_1_test1[NUMBER_OF_INPUTS * 128U] = {0};
    float y_1_test1[128U] = {0};
    float b_1_test1[128U] = {0};
    struct uz_nn_layer_config software_nn_config_test1[4] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = 128U,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(w_1_test1),
        .length_of_bias = UZ_MATRIX_SIZE(b_1_test1),
        .length_of_output = UZ_MATRIX_SIZE(y_1_test1),
        .weights = w_1_test1,
        .bias = b_1_test1,
        .output = y_1_test1},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4}};

    config.software_network = uz_nn_init(software_nn_config_test1, 4);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_4,UZ_MATRIX_SIZE(y_4),1U,NUMBER_OF_OUTPUTS);
    //Different amount of neurons than 64
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));

    float w_1_test2[30U * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
    float y_1_test2[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
    float b_1_test2[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
    struct uz_nn_layer_config software_nn_config_test2[4] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_inputs = 30U,
        .length_of_weights = UZ_MATRIX_SIZE(w_1_test2),
        .length_of_bias = UZ_MATRIX_SIZE(b_1_test2),
        .length_of_output = UZ_MATRIX_SIZE(y_1_test2),
        .weights = w_1_test2,
        .bias = b_1_test2,
        .output = y_1_test2},
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4}};

    config.software_network = uz_nn_init(software_nn_config_test2, 4);
    //More than 24 observations
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_init_assert_Size_L2_Weights_Bias(void) {
    config.base_address = BASE_ADDRESS;
    float w_2_test1[128U * 128U] = {0};
    float y_2_test1[128U] = {0};
    float b_2_test1[128U] = {0};
    struct uz_nn_layer_config software_nn_config_test1[4] = {
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
    [1] = {.activation_function = activation_ReLU, .number_of_neurons = 128U, .number_of_inputs = 128U, .length_of_weights = UZ_MATRIX_SIZE(w_2_test1), .length_of_bias = UZ_MATRIX_SIZE(b_2_test1), .length_of_output = UZ_MATRIX_SIZE(y_2_test1), .weights = w_2_test1, .bias = b_2_test1, .output = y_2_test1},
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
    [3] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4}};

    config.software_network = uz_nn_init(software_nn_config_test1, 4);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_4,UZ_MATRIX_SIZE(y_4),1U,NUMBER_OF_OUTPUTS);
    //Different amount of neurons than 64
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_init_assert_Size_L3_Weights_Bias(void) {
    config.base_address = BASE_ADDRESS;
    float w_3_test1[128U * 128U] = {0};
    float y_3_test1[128U] = {0};
    float b_3_test1[128U] = {0};
    struct uz_nn_layer_config software_nn_config_test1[4] = {
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
    [2] = {.activation_function = activation_ReLU, .number_of_neurons = 128U, .number_of_inputs = 128U, .length_of_weights = UZ_MATRIX_SIZE(w_3_test1), .length_of_bias = UZ_MATRIX_SIZE(b_3_test1), .length_of_output = UZ_MATRIX_SIZE(y_3_test1), .weights = w_3_test1, .bias = b_3_test1, .output = y_3_test1},
    [3] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4}};

    config.software_network = uz_nn_init(software_nn_config_test1, 4);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_4,UZ_MATRIX_SIZE(y_4),1U,NUMBER_OF_OUTPUTS);
    //Different amount of neurons than 64
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_init_assert_Size_Loutput_Weights_Bias(void) {
    config.base_address = BASE_ADDRESS;
    float w_4_test1[NUMBER_OF_OUTPUTS * 128] = {0};
    float y_4_test1[NUMBER_OF_OUTPUTS] = {0};
    float b_4_test1[NUMBER_OF_OUTPUTS] = {0};
    struct uz_nn_layer_config software_nn_config_test1[4] = {
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
    [3] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = 128, .length_of_weights = UZ_MATRIX_SIZE(w_4_test1), .length_of_bias = UZ_MATRIX_SIZE(b_4_test1), .length_of_output = UZ_MATRIX_SIZE(y_4_test1), .weights = w_4_test1, .bias = b_4_test1, .output = y_4_test1}};

    config.software_network = uz_nn_init(software_nn_config_test1, 4);
    uz_matrix_t *input = uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
    uz_matrix_t *output = uz_matrix_init(&output_matrix,y_4_test1,UZ_MATRIX_SIZE(y_4_test1),1U,NUMBER_OF_OUTPUTS);
    //Different amount of neurons than 64
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));

    float w_4_test2[20U * NUMBER_OF_NEURONS_IN_THIRD_LAYER] = {0};
    float y_4_test2[20U] = {0};
    float b_4_test2[20U] = {0};
    struct uz_nn_layer_config software_nn_config_test2[4] = {
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
    [3] = {.activation_function = activation_tanh, .number_of_neurons = 20U, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4_test2), .length_of_bias = UZ_MATRIX_SIZE(b_4_test2), .length_of_output = UZ_MATRIX_SIZE(y_4_test2), .weights = w_4_test2, .bias = b_4_test2, .output = y_4_test2}};

    config.software_network = uz_nn_init(software_nn_config_test2, 4);
    //Different amount of neurons than 64
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_init(config,input,output));
}

void test_uz_NN_acc_ff_blocking_assert_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_ff_blocking(NULL));
}


#endif