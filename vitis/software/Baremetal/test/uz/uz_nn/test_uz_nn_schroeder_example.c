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
#define NUMBER_OF_EPOCHS 200

// stuff for training and update
// sumout
float s_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float s_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float s_3[NUMBER_OF_OUTPUTS] = {0};

//derivate matrix activation, Dimension muss noch angepasst werden
float d_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float d_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float d_3[NUMBER_OF_OUTPUTS * NUMBER_OF_OUTPUTS] = {0};
//deltas
float delta_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float delta_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float delta_3[NUMBER_OF_OUTPUTS] = {0};

//cache gradients, Gräße entspricht delta des aktuellen layers * größe des Outputs des vorherigen layers
float cacheg_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_INPUTS] = {0};
float cacheg_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float cacheg_3[NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};

//Gradienten
float g_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER + NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_INPUTS] = {0};
float g_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER + NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float g_3[NUMBER_OF_OUTPUTS+NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};

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
// error
float e_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER]={0.0f};
float e_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER]={0.0f};
float e_3[NUMBER_OF_OUTPUTS]={0.0f};

// Temporary buffer storage

float T1[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float T2[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {0};
float T3[4] = {0}; // eigentlich nicht nötig da man cachebackprop im letzten layer nicht benötigt, aber fest definiert in layerconfig
float gradmat[13] = {
#include "schroeder_weights/gradmat.csv"
};
struct uz_nn_layer_config config[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_tanh,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_cachegradcolumns = NUMBER_OF_INPUTS,
        .number_of_temporarycolumns = 2,
        .number_of_temporaryrows = 2,
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
      .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
      .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
      .number_of_temporarycolumns = 1,
      .number_of_temporaryrows = 2,
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
   .number_of_cachegradrows = NUMBER_OF_OUTPUTS,
   .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
   .number_of_temporarycolumns = 2,
   .number_of_temporaryrows = 2,
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
   .error= e_3}};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_nn_schroder_gradients(void)
{
uz_nn_t* gradientnet = uz_nn_init(config,NUMBER_OF_HIDDEN_LAYER);
    // uz_nn_t* testlooper = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER);
    // testing around with derivatemat declaration
    struct uz_matrix_t x_matrix={0};
    uz_matrix_t* eingabe=uz_matrix_init(&x_matrix,&x[0],1,1,NUMBER_OF_INPUTS);
    uz_nn_ff(gradientnet,eingabe);
    uz_matrix_t* output=uz_nn_get_output_data(gradientnet);
    float result=uz_matrix_get_element_zero_based(output,0,0);
    float error = reference_output[0]- result;
    float const *ptr = &error;
    uz_nn_backward_pass(gradientnet,ptr,eingabe);
    // extract gradient to uz_matrix and then into array to check with unity fct
    uz_matrix_t* gradhelp1 = uz_nn_get_gradient_data(gradientnet,1); 
    uz_matrix_t* gradhelp2 = uz_nn_get_gradient_data(gradientnet,2); 
    uz_matrix_t* gradhelp3 = uz_nn_get_gradient_data(gradientnet,3); 
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
     for(int i=0;i< (int)(sizeof(gradmat) / sizeof(float));i++) {
        TEST_ASSERT_FLOAT_WITHIN(1e-02f, gradmat[i], gradhelper[i]);
    }
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
    for (size_t i = 0; i < 13; i++)
    {
    struct uz_matrix_t x_matrix={0};
    uz_matrix_t* eingabe=uz_matrix_init(&x_matrix,&x[i],1,1,NUMBER_OF_INPUTS);
    uz_nn_ff(test,eingabe);
    uz_matrix_t* output=uz_nn_get_output_data(test);
    float result=uz_matrix_get_element_zero_based(output,0,0);
    float error = reference_output[i]- result;
    uz_nn_backward_pass(test,&error,eingabe);
    uz_matrix_t* gradhelp1 = uz_nn_get_gradient_data(test,1); // index 1-3 verwenden für nn mit 3 layern
    THETAhelper[i] = uz_matrix_get_element_zero_based(gradhelp1,0,0);// THETA 1,1 
    biashelper[i] = uz_matrix_get_element_zero_based(gradhelp1,2,0);// bias 1,1
    sumtheta += THETAhelper[i];
    sumbias += biashelper[i];
    printf("sumthteta = %.2f \n", (double)sumtheta);
    printf("sumbias = %.2f \n", (double)sumbias);
    }
    avgbias = sumbias / 13.0f;
    avgtheta = sumtheta / 13.0f;
    printf("Mittelwert von thetagrad = %.2f \n", (double)avgtheta);
    printf("Mittelwert von biasgrad = %.2f \n", (double)avgbias);
    //Lernrate festlegen
    float lernrate = 2.0f;
    // updaten aller parameter mit den funktionen für das ganze netz
    // in diesem Beispiel sind die lokalen Gradienten des letzten Trainingspaars gespeichert, deshalb müssen
    // an dieser stelle  alle Gradienten zu null gesetzt und dann im nächsten schritt die parameter avgbias und avgtheta als Gradient gesetzt und dann kann mit uz_gradient_descent geupdatet werden
    uz_nn_set_gradients_zero(test); // alles zu null setzen
    struct uz_matrix_t avg_matrix={0};
    float avg_data[4]={avgtheta, 0.0f, avgbias, 0.0f};
    uz_matrix_t* gradmax=uz_matrix_init(&avg_matrix,&avg_data,4,4,1);
    uz_nn_set_gradient_matrix(test, gradmax, 1);
    uz_nn_gradient_descent(test, lernrate);
    //Update THETA 1,1 und bias 1,1 mit den berechneten Gradienten und einer Schrittweite von eta = 2
    //uz_nn_update(test,avgtheta,avgbias,lernrate);
    //Funktion die die daten exportiert und in die .csv Dateien überschreibt
    //uz_nn_schroeder_export(test);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Zeit des Tests = %.6f \n", (double)seconds);
}
#endif // TEST
