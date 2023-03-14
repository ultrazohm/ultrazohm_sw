#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include <time.h>


#define NUMBER_OF_INPUTS 13
#define NUMBER_OF_OUTPUTS 1
#define NUMBER_OF_HIDDEN_LAYER 3
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 50
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 20
// stuff for training and update
// sumout
float s_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float s_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float s_3[NUMBER_OF_OUTPUTS] = {0};

//derivate matrix activation, Dimension = Sumout x Sumout 50x50=2500 z.B.
float d_1[UZ_MATRIX_SIZE(s_1) * UZ_MATRIX_SIZE(s_1)] = {0};
float d_2[UZ_MATRIX_SIZE(s_2) * UZ_MATRIX_SIZE(s_2)] = {0};
float d_3[UZ_MATRIX_SIZE(s_3) * UZ_MATRIX_SIZE(s_3)] = {0};
//deltas
float delta_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float delta_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float delta_3[NUMBER_OF_OUTPUTS] = {0};

//cache gradients, Gräße entspricht delta des aktuellen layers * größe des Outputs des vorherigen layers
float cacheg_1[UZ_MATRIX_SIZE(delta_1) * NUMBER_OF_INPUTS] = {0};
float cacheg_2[UZ_MATRIX_SIZE(delta_2) * UZ_MATRIX_SIZE(s_1)] = {0};
float cacheg_3[UZ_MATRIX_SIZE(delta_3) * UZ_MATRIX_SIZE(s_2)] = {0};

//Gradienten
float g_1[UZ_MATRIX_SIZE(delta_1)+UZ_MATRIX_SIZE(cacheg_1)] = {0};
float g_2[UZ_MATRIX_SIZE(delta_2)+UZ_MATRIX_SIZE(cacheg_2)] = {0};
float g_3[UZ_MATRIX_SIZE(delta_3)+UZ_MATRIX_SIZE(cacheg_3)] = {0};

// 13 Trainingsdaten aus Matlab(1-13)
float x[NUMBER_OF_INPUTS] = {
#include "matlab_weights/X_input.csv"
};
float reference_output[NUMBER_OF_OUTPUTS]= {
#include "matlab_weights/T_output.csv"
};

float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "matlab_weights/layer1_weights.csv"
};
float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "matlab_weights/layer1_bias.csv"
		};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};


float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "matlab_weights/layer2_weights.csv"
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "matlab_weights/layer2_bias.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};


float w_3[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {
#include "matlab_weights/layer3_weights.csv"
};
float b_3[NUMBER_OF_OUTPUTS] = {
#include "matlab_weights/layer3_bias.csv"
};
float y_3[NUMBER_OF_OUTPUTS] = {0};
// error
float e_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER]={0.0f};
float e_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER]={0.0f};
float e_3[NUMBER_OF_OUTPUTS]={0.0f};
// Temporary buffer storage

float T1[UZ_MATRIX_SIZE(w_2)] = {0};
float T2[UZ_MATRIX_SIZE(w_3)] = {0};
float T3[4] = {0}; // eigentlich nicht nötig da man cachebackprop im letzten layer nicht benötigt, aber fest definiert in layerconfig
struct uz_nn_layer_config config[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_tanh,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .number_of_cachegradrows = 650,
        .number_of_cachegradcolumns = 1,
        .number_of_temporarycolumns = 500,
        .length_of_weights = UZ_MATRIX_SIZE(w_1),
        .length_of_bias = UZ_MATRIX_SIZE(b_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .length_of_sumout = UZ_MATRIX_SIZE(s_1),
        .length_of_derivate_gradients= UZ_MATRIX_SIZE(d_1),
        .length_of_delta = UZ_MATRIX_SIZE(delta_1),
        .length_of_error = UZ_MATRIX_SIZE(e_1),
        .length_of_gradients = UZ_MATRIX_SIZE(g_1),
        .length_of_temporarybackprop = UZ_MATRIX_SIZE(T1),
        .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_1),
        .weights = w_1,
        .bias = b_1,
        .output = y_1,
        .sumout = s_1,
        .derivate_gradients = d_1,
        .delta = delta_1,
        .temporarybackprop = T1,
        .gradients = g_1,
        .cachegradients = cacheg_1,
        .error = e_1},
    [1] = {
      .activation_function = activation_tanh, 
      .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
      .number_of_inputs = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
      .number_of_cachegradrows = 1000,
      .number_of_cachegradcolumns = 1,
      .number_of_temporarycolumns = 10,
      .length_of_weights = UZ_MATRIX_SIZE(w_2),
      .length_of_bias = UZ_MATRIX_SIZE(b_2),
      .length_of_output = UZ_MATRIX_SIZE(y_2),
      .length_of_sumout = UZ_MATRIX_SIZE(s_2),
      .length_of_derivate_gradients = UZ_MATRIX_SIZE(d_2),
      .length_of_delta = UZ_MATRIX_SIZE(delta_2),
      .length_of_gradients = UZ_MATRIX_SIZE(g_2),
      .length_of_error = UZ_MATRIX_SIZE(e_2),
      .length_of_temporarybackprop = UZ_MATRIX_SIZE(T2),
      .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_2),
      .weights = w_2,
      .bias = b_2,
      .output = y_2,
      .sumout = s_2,
      .derivate_gradients = d_2,
      .delta = delta_2,
      .temporarybackprop = T2,
      .gradients = g_2,
      .cachegradients = cacheg_2,
      .error=e_2},
  [2] = {.activation_function = activation_linear,
   .number_of_neurons = NUMBER_OF_OUTPUTS,
   .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
   .number_of_cachegradrows = 20,
   .number_of_cachegradcolumns = 1,
   .number_of_temporarycolumns = 2,
   .length_of_weights = UZ_MATRIX_SIZE(w_3),
   .length_of_bias = UZ_MATRIX_SIZE(b_3),
   .length_of_output = UZ_MATRIX_SIZE(y_3),
   .length_of_sumout = UZ_MATRIX_SIZE(s_3),
   .length_of_derivate_gradients = UZ_MATRIX_SIZE(d_3),
   .length_of_delta = UZ_MATRIX_SIZE(delta_3),
   .length_of_gradients = UZ_MATRIX_SIZE(g_3),
   .length_of_error = UZ_MATRIX_SIZE(e_3),
   .length_of_temporarybackprop = UZ_MATRIX_SIZE(T3),
   .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_3),
   .weights = w_3,
   .bias = b_3,
   .output = y_3,
   .sumout = s_3,
   .derivate_gradients = d_3,
   .delta = delta_3, 
   .temporarybackprop = T3,
   .gradients = g_3,
   .cachegradients = cacheg_3,
   .error= e_3}
  };

void setUp(void)
{
}

void tearDown(void)
{
}


void test_uz_nn_matlab(void)
  {
     clock_t start = clock();
//     float biashelper[13];
//     float THETAhelper[13];
//     float sumtheta = 0.0f;
//     float sumbias = 0.0f;
//     float avgtheta = 0.0f;
//     float avgbias = 0.0f;
//     init nn
//     for (size_t i = 0; i < 13; i++)
//     {
//     uz_nn_t* testlooper = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
//     testing around with derivatemat declaration
       uz_nn_t* test = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
       struct uz_matrix_t x_matrix={0};
       uz_matrix_t* input=uz_matrix_init(&x_matrix, x,UZ_MATRIX_SIZE(x),1,13);
       uz_nn_ff(test,input);
       // check output
       uz_matrix_t* output=uz_nn_get_output_data(test);
//       uz_nn_calc_gradients(test,*reference_output,input);
//     uz_matrix_t* gradhelp1 = uz_nn_get_gradient_data(test,1); // index 1-3 verwenden für nn mit 3 layern
//     THETAhelper[i] = uz_matrix_get_element_zero_based(gradhelp1,0,0);//THETA 1,1 
//     biashelper[i] = uz_matrix_get_element_zero_based(gradhelp1,2,0);//bias 1,1
//     sumtheta += THETAhelper[i];
//     sumbias += biashelper[i];
//     }
//     uz_nn_t* test = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
//     avgbias = sumbias / 13.0f;
//     avgtheta = sumtheta / 13.0f;
//     printf("Mittelwert von thetagrad = %.2f \n", avgtheta);
//     printf("Mittelwert von biasgrad = %.2f \n", avgbias);
//     Lernrate festlegen
//     float lernrate = 2.0f;
//     Update THETA 1,1 mit den Berechneten Gradienten und einer Schrittweite von eta = 2
//     uz_nn_update(test,avgtheta,avgbias,lernrate);
     clock_t end = clock();
//     Funktion die die daten exportiert und in die .csv Dateien überschreibt
//     uz_nn_export(test);
//     /*Do something*/
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Zeit des Tests = %.6f \n", seconds);
 }
#endif // TEST
