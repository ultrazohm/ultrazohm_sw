#ifdef TEST
#pragma GCC optimize("02")

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include <time.h>


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

//cache gradients
float cacheg_1[2] = {0};
float cacheg_2[4] = {0};
float cacheg_3[2] = {0};

// error
float e_1[2]={1.0f};
float e_2[2]={1.0f};
float e_3[1]={1.0f};
// Cachebackprop

float C1[2 * 2] = {0};
float C2[2 * 1] = {0};
float C3[2 * 2] = {0};

// 13 Trainingsdaten aus Schroeder
float x[13] = {-5.0f,-4.17f,-3.33f,-2.5f,-1.67f,-0.83f,0.0f,0.83f,1.67f,2.50f,3.33f,4.17f,5.00f};
float reference_output [13] = {-4.41f,-4.35f,-4.27f,-4.12f,-3.84f,-3.09f,0.0f,3.09f,3.84f,4.12f,4.27f,4.35f,4.41f};

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
        .number_of_cachegradrows = 2,
        .number_of_cachegradcolumns = 1,
        .number_of_cachecolumns = 2,
        .length_of_weights = UZ_MATRIX_SIZE(w_1),
        .length_of_bias = UZ_MATRIX_SIZE(b_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .length_of_sumout = UZ_MATRIX_SIZE(s_1),
        .length_of_derivate_gradients= UZ_MATRIX_SIZE(d_1),
        .length_of_delta = UZ_MATRIX_SIZE(delta_1),
        .length_of_error = UZ_MATRIX_SIZE(e_1),
        .length_of_gradients = UZ_MATRIX_SIZE(g_1),
        .length_of_cachebackprop = UZ_MATRIX_SIZE(C1),
        .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_1),
        .weights = w_1,
        .bias = b_1,
        .output = y_1,
        .sumout = s_1,
        .derivate_gradients = d_1,
        .delta = delta_1,
        .cachebackprop = C1,
        .gradients = g_1,
        .cachegradients = cacheg_1,
        .error = e_1},
    [1] = {
      .activation_function = activation_tanh, 
      .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
      .number_of_inputs = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
      .number_of_cachegradrows = 2,
      .number_of_cachegradcolumns = 2,
      .number_of_cachecolumns = 1,
      .length_of_weights = UZ_MATRIX_SIZE(w_2),
      .length_of_bias = UZ_MATRIX_SIZE(b_2),
      .length_of_output = UZ_MATRIX_SIZE(y_2),
      .length_of_sumout = UZ_MATRIX_SIZE(s_2),
      .length_of_derivate_gradients = UZ_MATRIX_SIZE(d_2),
      .length_of_delta = UZ_MATRIX_SIZE(delta_2),
      .length_of_gradients = UZ_MATRIX_SIZE(g_2),
      .length_of_error = UZ_MATRIX_SIZE(e_2),
      .length_of_cachebackprop = UZ_MATRIX_SIZE(C2),
      .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_2),
      .weights = w_2,
      .bias = b_2,
      .output = y_2,
      .sumout = s_2,
      .derivate_gradients = d_2,
      .delta = delta_2,
      .cachebackprop = C2,
      .gradients = g_2,
      .cachegradients = cacheg_2,
      .error=e_2},
  [2] = {.activation_function = activation_linear,
   .number_of_neurons = NUMBER_OF_OUTPUTS,
   .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
   .number_of_cachegradrows = 2,
   .number_of_cachegradcolumns = 1,
   .number_of_cachecolumns = 2,
   .length_of_weights = UZ_MATRIX_SIZE(w_3),
   .length_of_bias = UZ_MATRIX_SIZE(b_3),
   .length_of_output = UZ_MATRIX_SIZE(y_3),
   .length_of_sumout = UZ_MATRIX_SIZE(s_3),
   .length_of_derivate_gradients = UZ_MATRIX_SIZE(d_3),
   .length_of_delta = UZ_MATRIX_SIZE(delta_3),
   .length_of_gradients = UZ_MATRIX_SIZE(g_3),
   .length_of_error = UZ_MATRIX_SIZE(e_3),
   .length_of_cachebackprop = UZ_MATRIX_SIZE(C3),
   .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_3),
   .weights = w_3,
   .bias = b_3,
   .output = y_3,
   .sumout = s_3,
   .derivate_gradients = d_3,
   .delta = delta_3, 
   .cachebackprop = C3,
   .gradients = g_3,
   .cachegradients = cacheg_3,
   .error= e_3}};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_nn_schroeder(void)
  {
    clock_t start = clock();
    float biashelper[13];
    float THETAhelper[13];
    float sumtheta = 0.0f;
    float sumbias = 0.0f;
    float avgtheta = 0.0f;
    float avgbias = 0.0f;
    //init nn
    uz_nn_t* test = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
    for (size_t i = 0; i < 13; ++i)
    {
    uz_nn_t* testlooper = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
    // testing around with derivatemat declaration
    struct uz_matrix_t x_matrix={0};
    uz_matrix_t* input=uz_matrix_init(&x_matrix,&x[i],1,1,NUMBER_OF_INPUTS);
    uz_nn_ff(testlooper,input);
    uz_nn_calc_gradients(testlooper,reference_output[i],input);
    uz_matrix_t* gradhelp1 = uz_nn_get_gradient_data(test,1); // index 1-3 verwenden für nn mit 3 layern
    THETAhelper[i] = uz_matrix_get_element_zero_based(gradhelp1,0,0);//THETA 1,1 
    biashelper[i] = uz_matrix_get_element_zero_based(gradhelp1,2,0);//bias 1,1
    sumtheta += THETAhelper[i];
    sumbias += biashelper[i];
    }
    //uz_nn_t* test = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
    avgbias = sumbias / 13.0f;
    avgtheta = sumtheta / 13.0f;
    printf("Mittelwert von thetagrad = %.2f \n", avgtheta);
    printf("Mittelwert von biasgrad = %.2f \n", avgbias);
    // Lernrate festlegen
    float lernrate = 2.0f;
    // Update THETA 1,1 mit den Berechneten Gradienten und einer Schrittweite von eta = 2
    uz_nn_update(test,avgtheta,avgbias,lernrate);
    clock_t end = clock();
    // Funktion die die daten exportiert und in die .csv Dateien überschreibt
    //uz_nn_export(test);
    /*Do something*/
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Zeit des Tests = %.6f \n", seconds);
}
#endif // TEST
