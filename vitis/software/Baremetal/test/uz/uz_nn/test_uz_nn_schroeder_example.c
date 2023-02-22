#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"

#define NUMBER_OF_INPUTS 1
#define NUMBER_OF_OUTPUTS 1
#define NUMBER_OF_HIDDEN_LAYER 3
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 2
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 2

// stuff for training and update
// sumout
float s_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float s_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float s_3[NUMBER_OF_OUTPUTS] = {0};

//derivate matrix activation, Dimension muss noch angepasst werden
float d_1[UZ_MATRIX_SIZE(s_1) * UZ_MATRIX_SIZE(s_2)] = {0};
float d_2[UZ_MATRIX_SIZE(s_1) * UZ_MATRIX_SIZE(s_2)] = {0};
float d_3[UZ_MATRIX_SIZE(s_3)] = {0};
//deltas
float delta_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float delta_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float delta_3[NUMBER_OF_OUTPUTS] = {0};
//Gradienten
float g_1[4] = {0};
float g_2[6] = {0};
float g_3[3] = {0};
// error
float e_1[2]={1.0f};
float e_2[2]={1.0f};
float e_3[1]={1.0f};

float x[NUMBER_OF_INPUTS] = {-5.0f};
float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "schroeder_weights/layer1_weights.csv"
};
float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "schroeder_weights/layer1_bias.csv"
		};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};


float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "schroeder_weights/layer2_weights.csv"
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "schroeder_weights/layer2_bias.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};


float w_3[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {
#include "schroeder_weights/layer3_weights.csv"
};
float b_3[NUMBER_OF_OUTPUTS] = {
#include "schroeder_weights/layer3_bias.csv"
};
float y_3[NUMBER_OF_OUTPUTS] = {0};

struct uz_nn_layer_config config[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_tanh,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(w_1),
        .length_of_bias = UZ_MATRIX_SIZE(b_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .length_of_sumout = UZ_MATRIX_SIZE(s_1),
        .length_of_derivate_gradients= UZ_MATRIX_SIZE(d_1),
        .length_of_delta = UZ_MATRIX_SIZE(delta_1),
        .length_of_error = UZ_MATRIX_SIZE(e_1),
        .length_of_gradients = UZ_MATRIX_SIZE(g_1),
        .weights = w_1,
        .bias = b_1,
        .output = y_1,
        .sumout = s_1,
        .derivate_gradients = d_1,
        .delta = delta_1,
        .gradients = g_1,
        .error = e_1},
    [1] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .length_of_sumout = UZ_MATRIX_SIZE(s_2), .length_of_derivate_gradients = UZ_MATRIX_SIZE(d_2),.length_of_delta = UZ_MATRIX_SIZE(delta_2), .length_of_gradients = UZ_MATRIX_SIZE(g_2),.length_of_error = UZ_MATRIX_SIZE(e_2), .weights = w_2, .bias = b_2, .output = y_2, .sumout = s_2, .derivate_gradients = d_2, .delta = delta_2, .gradients = g_2, .error=e_2},
  [2] = {.activation_function = activation_linear, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .length_of_sumout = UZ_MATRIX_SIZE(s_3), .length_of_derivate_gradients = UZ_MATRIX_SIZE(d_3),.length_of_delta = UZ_MATRIX_SIZE(delta_3), .length_of_gradients = UZ_MATRIX_SIZE(g_3), .length_of_error = UZ_MATRIX_SIZE(e_3), .weights = w_3, .bias = b_3, .output = y_3, .sumout = s_3, .derivate_gradients = d_3,.delta = delta_3,  .gradients = g_3, .error= e_3}};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_nn_schroeder(void)
  {
    // testing around with derivatemat declaration
    struct uz_matrix_t x_matrix={0};
    uz_matrix_t* input=uz_matrix_init(&x_matrix, x,UZ_MATRIX_SIZE(x),1,NUMBER_OF_INPUTS);
    uz_nn_t* test = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
    uz_nn_ff(test,input);
    float expected_result= -1.52f; 
    uz_matrix_t* output=uz_nn_get_output_data(test);
    float result=uz_matrix_get_element_zero_based(output,0,0);
    TEST_ASSERT_FLOAT_WITHIN(0.4f,expected_result,result);
    // check outputs
    float outputhelper[UZ_MATRIX_SIZE(y_1)+UZ_MATRIX_SIZE(y_2)+UZ_MATRIX_SIZE(y_3)];
    uz_matrix_t* output1 = uz_nn_get_output_from_each_layer(test,1);
    uz_matrix_t* output2 = uz_nn_get_output_from_each_layer(test,2);
    uz_matrix_t* output3 = uz_nn_get_output_from_each_layer(test,3);
    outputhelper[0] = uz_matrix_get_element_zero_based(output1,0,0);
    outputhelper[1] = uz_matrix_get_element_zero_based(output1,0,1);
    outputhelper[2] = uz_matrix_get_element_zero_based(output2,0,0);
    outputhelper[3] = uz_matrix_get_element_zero_based(output2,0,1);
    outputhelper[4] = uz_matrix_get_element_zero_based(output3,0,0);   
    // check sumouts
    uz_matrix_t* sumout1=uz_nn_get_sumout_data(test,1);
    uz_matrix_t* sumout2=uz_nn_get_sumout_data(test,2);
    uz_matrix_t* sumout3=uz_nn_get_sumout_data(test,3);
    float sumouthelper[UZ_MATRIX_SIZE(s_1)+UZ_MATRIX_SIZE(s_2)+UZ_MATRIX_SIZE(s_3)];
    sumouthelper[0] = uz_matrix_get_element_zero_based(sumout1,0,0);
    sumouthelper[1] = uz_matrix_get_element_zero_based(sumout1,0,1);
    sumouthelper[2] = uz_matrix_get_element_zero_based(sumout2,0,0);
    sumouthelper[3] = uz_matrix_get_element_zero_based(sumout2,0,1);
    sumouthelper[4] = uz_matrix_get_element_zero_based(sumout3,0,0);
    // calculate output error
    const float reference_output = {-4.41f};
    uz_nn_backprop(test,reference_output);
    //check delta
    uz_matrix_t *deltahelper1 = uz_nn_get_delta_data(test,1); // index 1-3 verwenden für nn mit 3 layern
    uz_matrix_t *deltahelper2 = uz_nn_get_delta_data(test,2); // index 1-3 verwenden für nn mit 3 layern
    uz_matrix_t *deltahelper3 = uz_nn_get_delta_data(test,3); // index 1-3 verwenden für nn mit 3 layern
    float deltahelp[5];
    deltahelp[0] = uz_matrix_get_element_zero_based(deltahelper1,0,0);
    deltahelp[1] = uz_matrix_get_element_zero_based(deltahelper1,0,1);
    deltahelp[2] = uz_matrix_get_element_zero_based(deltahelper2,0,0);
    deltahelp[3] = uz_matrix_get_element_zero_based(deltahelper2,0,1);
    deltahelp[4] = uz_matrix_get_element_zero_based(deltahelper3,0,0);
    // check derivates
    uz_matrix_t* helper1 = uz_nn_get_derivate_data(test,1); // index 1-3 verwenden für nn mit 3 layern
    uz_matrix_t* helper2 = uz_nn_get_derivate_data(test,2); // index 1-3 verwenden für nn mit 3 layern
    uz_matrix_t* helper3 = uz_nn_get_derivate_data(test,3); // index 1-3 verwenden für nn mit 3 layern
    float derivatehelper[UZ_MATRIX_SIZE(d_1)+UZ_MATRIX_SIZE(d_2)+UZ_MATRIX_SIZE(d_3)];
    derivatehelper[0] = uz_matrix_get_element_zero_based(helper1,0,0);
    derivatehelper[1] = uz_matrix_get_element_zero_based(helper1,0,1);
    derivatehelper[2] = uz_matrix_get_element_zero_based(helper1,1,0);
    derivatehelper[3] = uz_matrix_get_element_zero_based(helper1,1,1);
    derivatehelper[4] = uz_matrix_get_element_zero_based(helper2,0,0);
    derivatehelper[5] = uz_matrix_get_element_zero_based(helper2,0,1);
    derivatehelper[6] = uz_matrix_get_element_zero_based(helper2,1,0);
    derivatehelper[7] = uz_matrix_get_element_zero_based(helper2,1,1);
    derivatehelper[8] = uz_matrix_get_element_zero_based(helper3,0,0);
    // check gradients
    uz_matrix_t* gradhelp1 = uz_nn_get_gradient_data(test,1); // index 1-3 verwenden für nn mit 3 layern
    uz_matrix_t* gradhelp2 = uz_nn_get_gradient_data(test,2); // index 1-3 verwenden für nn mit 3 layern
    uz_matrix_t* gradhelp3 = uz_nn_get_gradient_data(test,3); // index 1-3 verwenden für nn mit 3 layern
    float gradhelper[UZ_MATRIX_SIZE(g_1)+UZ_MATRIX_SIZE(g_2)+UZ_MATRIX_SIZE(g_3)];
    gradhelper[0] = uz_matrix_get_element_zero_based(gradhelp1,0,0);
    gradhelper[1] = uz_matrix_get_element_zero_based(gradhelp1,1,0);
    gradhelper[2] = uz_matrix_get_element_zero_based(gradhelp1,2,0);
    gradhelper[3] = uz_matrix_get_element_zero_based(gradhelp1,3,0);
    gradhelper[4] = uz_matrix_get_element_zero_based(gradhelp2,0,0);
    gradhelper[5] = uz_matrix_get_element_zero_based(gradhelp2,1,0);
    gradhelper[6] = uz_matrix_get_element_zero_based(gradhelp2,2,0);
    gradhelper[7] = uz_matrix_get_element_zero_based(gradhelp2,3,0);
    gradhelper[8] = uz_matrix_get_element_zero_based(gradhelp2,4,0);
    gradhelper[9] = uz_matrix_get_element_zero_based(gradhelp2,5,0);
    gradhelper[10] = uz_matrix_get_element_zero_based(gradhelp3,0,0);
    gradhelper[11] = uz_matrix_get_element_zero_based(gradhelp3,1,0);
    gradhelper[12] = uz_matrix_get_element_zero_based(gradhelp3,2,0);
    // Berechne lokale Gradienten

    // Trainiere einen step des Netzes 
 }

#endif // TEST
