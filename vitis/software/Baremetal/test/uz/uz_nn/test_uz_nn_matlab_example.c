#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include "../uz_mtwister/uz_mtwister.h"
#include "uz_sum.h"
#include "uz_codegen0_ert_rtw/uz_codegen0.h"
#include <time.h>
#include <stdlib.h>

#define NUMBER_OF_INPUTS 13
#define NUMBER_OF_OUTPUTS 1
#define NUMBER_OF_HIDDEN_LAYER 3
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 50
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 20
#define NUMBER_OF_EPOCHS 200
#define MINI_BATCH_SIZE 252

// sumout
float s_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float s_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float s_3[NUMBER_OF_OUTPUTS] = {0};

//deltas
float delta_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float delta_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float delta_3[NUMBER_OF_OUTPUTS] = {0};

//cache gradients, Größe entspricht delta des aktuellen layers * größe des Outputs des vorherigen layers
float cacheg_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_INPUTS] = {0};
float cacheg_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float cacheg_3[NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};

//Gradienten, nur zu Debug Zwecken
float g_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER + NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_INPUTS] = {0};
float g_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER + NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};
float g_3[NUMBER_OF_OUTPUTS+NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
// adam
float m1[NUMBER_OF_NEURONS_IN_FIRST_LAYER + NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_INPUTS] = {0.0f};
float v1[NUMBER_OF_NEURONS_IN_FIRST_LAYER + NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_INPUTS] = {0.0f};
float m2[NUMBER_OF_NEURONS_IN_SECOND_LAYER + NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0.0f};
float v2[NUMBER_OF_NEURONS_IN_SECOND_LAYER + NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0.0f};
float m3[NUMBER_OF_OUTPUTS+NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0.0f};
float v3[NUMBER_OF_OUTPUTS+NUMBER_OF_OUTPUTS * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0.0f};
// 13 Trainingsvektordaten aus Matlab(1-13)
float x[NUMBER_OF_INPUTS] = {
#include "matlab_weights/X_inputvec.csv"
};

float x_mat[NUMBER_OF_INPUTS * MINI_BATCH_SIZE] = {
#include "matlab_weights/X_input.csv"
};
// Sollausgabe (1 Ausgabewert) aus Matlab
float reference_output[NUMBER_OF_OUTPUTS]= {
#include "matlab_weights/T_outputvec.csv"
};

float reference_mat[NUMBER_OF_OUTPUTS * MINI_BATCH_SIZE]= {
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

float T1[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};
float T2[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {0};
float T3[4] = {0}; // eigentlich nicht nötig da man cachebackprop im letzten layer nicht benötigt, aber fest definiert in layerconfig

float msetest [MINI_BATCH_SIZE] = {0.0f};
float msederv [MINI_BATCH_SIZE] = {0.0f};
float msebatch [NUMBER_OF_EPOCHS] = {0.0f};

float mse_mb_train[NUMBER_OF_EPOCHS] = {
#include "matlab_weights/mse_mini_batch_train.csv"
};

struct uz_nn_layer_config config[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_tanh,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_cachegradcolumns = NUMBER_OF_INPUTS,
        .number_of_temporaryrows = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
        .number_of_temporarycolumns = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
        .length_of_weights = UZ_MATRIX_SIZE(w_1),
        .length_of_bias = UZ_MATRIX_SIZE(b_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .length_of_sumout = UZ_MATRIX_SIZE(s_1),
        .length_of_delta = UZ_MATRIX_SIZE(delta_1),
        .length_of_error = UZ_MATRIX_SIZE(e_1),
        .length_of_gradients = UZ_MATRIX_SIZE(g_1),
        .length_of_temporarybackprop = UZ_MATRIX_SIZE(T1),
        .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_1),
        .m = m1,
        .v = v1,
        .weights = w_1,
        .bias = b_1,
        .output = y_1,
        .sumout = s_1,
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
      .number_of_temporaryrows = NUMBER_OF_NEURONS_IN_SECOND_LAYER,
      .number_of_temporarycolumns = NUMBER_OF_OUTPUTS,
      .length_of_weights = UZ_MATRIX_SIZE(w_2),
      .length_of_bias = UZ_MATRIX_SIZE(b_2),
      .length_of_output = UZ_MATRIX_SIZE(y_2),
      .length_of_sumout = UZ_MATRIX_SIZE(s_2),
      .length_of_delta = UZ_MATRIX_SIZE(delta_2),
      .length_of_gradients = UZ_MATRIX_SIZE(g_2),
      .length_of_error = UZ_MATRIX_SIZE(e_2),
      .length_of_temporarybackprop = UZ_MATRIX_SIZE(T2),
      .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_2),
      .m = m2,
      .v = v2,
      .weights = w_2,
      .bias = b_2,
      .output = y_2,
      .sumout = s_2,
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
   .length_of_delta = UZ_MATRIX_SIZE(delta_3),
   .length_of_gradients = UZ_MATRIX_SIZE(g_3),
   .length_of_error = UZ_MATRIX_SIZE(e_3),
   .length_of_temporarybackprop = UZ_MATRIX_SIZE(T3),
   .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_3),
    .m = m3,
    .v = v3,
   .weights = w_3,
   .bias = b_3,
   .output = y_3,
   .sumout = s_3,
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


void test_uz_nn_train_minibatch_function(void)
{
    //init some instances for mb train function
    uz_nn_t* test = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER,true);
    struct uz_matrix_t refmatrix={0};
    uz_matrix_t* refout=uz_matrix_init(&refmatrix, reference_mat,UZ_MATRIX_SIZE(reference_mat),MINI_BATCH_SIZE,NUMBER_OF_OUTPUTS);
    struct uz_matrix_t input_matrix={0};
    uz_matrix_t* input=uz_matrix_init(&input_matrix, x_mat,UZ_MATRIX_SIZE(x_mat),MINI_BATCH_SIZE,NUMBER_OF_INPUTS);
    float X_data[NUMBER_OF_INPUTS] = {0.0f};
    struct uz_matrix_t input_vec= {0};
    uz_matrix_t *X = uz_matrix_init(&input_vec, X_data, UZ_MATRIX_SIZE(X_data), 1, UZ_MATRIX_SIZE(X_data));
    struct uz_matrix_t refvec={0};
    uz_matrix_t* ref=uz_matrix_init(&refvec,reference_output,UZ_MATRIX_SIZE(reference_output),1,UZ_MATRIX_SIZE(reference_output));
    // set all gradients zero before training
    uz_nn_set_gradients_zero(test);
    float mse[NUMBER_OF_EPOCHS] = {0};
    float lernrate = 0.001f;
    uz_nn_train_minibatch(test, mse, input, refout, X, ref, lernrate, MINI_BATCH_SIZE, NUMBER_OF_EPOCHS);
    // check parameter weights and bias to other test
     for(size_t i = 0;i< (int)(sizeof(mse) / sizeof(float));i++) {
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, mse_mb_train[i], 0.5f* mse[i]);
    }
}

 void test_uz_nn_matlab_mini_batch(void)
  {
      uz_nn_t* test = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER,true);
      struct uz_matrix_t refmatrix={0};
      uz_matrix_t* refout=uz_matrix_init(&refmatrix, reference_mat,UZ_MATRIX_SIZE(reference_mat),MINI_BATCH_SIZE,NUMBER_OF_OUTPUTS);
      struct uz_matrix_t input_matrix={0};
      uz_matrix_t* input=uz_matrix_init(&input_matrix, x_mat,UZ_MATRIX_SIZE(x_mat),MINI_BATCH_SIZE,NUMBER_OF_INPUTS);
      float X_data[NUMBER_OF_INPUTS] = {0.0f};
      struct uz_matrix_t input_vec= {0};
      uz_matrix_t *X = uz_matrix_init(&input_vec, X_data, UZ_MATRIX_SIZE(X_data), 1, UZ_MATRIX_SIZE(X_data));
      struct uz_matrix_t refvec={0};
      uz_matrix_t* ref=uz_matrix_init(&refvec,reference_output,UZ_MATRIX_SIZE(reference_output),1,UZ_MATRIX_SIZE(reference_output));
      // set all gradients zero before training
      uz_nn_set_gradients_zero(test);
      for (size_t i = 0; i < NUMBER_OF_EPOCHS; i++)
      {
      uint32_t mb_size = uz_matrix_get_number_of_rows(input);
      for(uint32_t j=0; j<mb_size;j++){
        uz_matrix_get_row_vector_zero_based(input,X,j);
        uz_nn_ff(test,X);
        uz_matrix_t* output=uz_nn_get_output_data(test);
        uz_matrix_get_row_vector_zero_based(refout,ref,j);
        msetest[j] = uz_nn_mse(output,ref);
        msederv[j] = uz_nn_mse_derv(output,ref);
        float *msed = &msederv[j];
        uz_nn_backward_pass_mini_batch(test,msed,X);        
        }
        float lernrate = 0.001f;
        uz_nn_gradient_descent_mini_batch(test,lernrate,mb_size);
        uz_matrix_t* output=uz_nn_get_output_data(test);
        msebatch[i] = uz_nn_mse(output,ref); 
        //float result=
        uz_matrix_get_element_zero_based(output,0,0);
       // printf("output nach minbatch  %d ist = %.8f \n",(int)i, (double)result);
       // printf("mse nach minibatch %d ist = %.8f \n",(int)i, (double)msebatch[i]);
        uz_nn_set_gradients_zero(test);
        }
}


void test_uz_nn_matlab(void)
  {
      uz_nn_t* test = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER,true);
      struct uz_matrix_t refmatrix={0};
      uz_matrix_t* refout=uz_matrix_init(&refmatrix, reference_output,UZ_MATRIX_SIZE(reference_output),1,UZ_MATRIX_SIZE(reference_output));
      struct uz_matrix_t x_matrix={0};
      uz_matrix_t* input=uz_matrix_init(&x_matrix, x,UZ_MATRIX_SIZE(x),1,NUMBER_OF_INPUTS);
      //clock_t start = clock();
       for (size_t i = 0; i < NUMBER_OF_EPOCHS; i++)
       {
       uz_nn_ff(test,input);
       uz_matrix_t* output=uz_nn_get_output_data(test);
       // MSE Berechnen für Trainingsdatenpaar
       msetest[i] = uz_nn_mse(output,refout);
       msederv[i] = uz_nn_mse_derv(output,refout);
       float *msed = &msederv[i];
       //float result=
       uz_matrix_get_element_zero_based(output,0,0);
     //  printf("output von step %d ist = %.8f \n",(int)i, (double)result);
     //  printf("mse von output step %d ist = %.8f \n",(int)i, (double)msetest[i]);
       uz_nn_backward_pass(test,msed,input);
      //  uz_nn_gradient_descent(test,lernrate);
       }
      //  uz_nn_mat_export(test);
      // clock_t end = clock();
      // float seconds = (float)(end - start) / CLOCKS_PER_SEC;
     //  printf("Zeit des Tests = %.6f \n", (double)seconds);
 }
 void test_uz_nn_matlab_mini_batch_adam(void)
  {
      uz_nn_t* test = uz_nn_init(config, NUMBER_OF_HIDDEN_LAYER,true);
      struct uz_matrix_t refmatrix={0};
      uz_matrix_t* refout=uz_matrix_init(&refmatrix, reference_mat,UZ_MATRIX_SIZE(reference_mat),MINI_BATCH_SIZE,NUMBER_OF_OUTPUTS);
      struct uz_matrix_t input_matrix={0};
      uz_matrix_t* input=uz_matrix_init(&input_matrix, x_mat,UZ_MATRIX_SIZE(x_mat),MINI_BATCH_SIZE,NUMBER_OF_INPUTS);
      float X_data[NUMBER_OF_INPUTS] = {0.0f};
      struct uz_matrix_t input_vec= {0};
      uz_matrix_t *X = uz_matrix_init(&input_vec, X_data, UZ_MATRIX_SIZE(X_data), 1, UZ_MATRIX_SIZE(X_data));
      struct uz_matrix_t refvec={0};
      uz_matrix_t* ref=uz_matrix_init(&refvec,reference_output,UZ_MATRIX_SIZE(reference_output),1,UZ_MATRIX_SIZE(reference_output));
      // set all gradients zero before training
      //adam testing
      float lernrate = 0.01f;
      adam_optimizer_t *adam = uz_adam_init(lernrate/(float)MINI_BATCH_SIZE);
      uz_nn_set_gradients_zero(test);
      for (size_t i = 0; i < NUMBER_OF_EPOCHS; i++)
      {
      uint32_t mb_size = uz_matrix_get_number_of_rows(input);
      for(uint32_t j=0; j<mb_size;j++){
        uz_matrix_get_row_vector_zero_based(input,X,j);
        uz_nn_ff(test,X);
        uz_matrix_t* output=uz_nn_get_output_data(test);
        uz_matrix_get_row_vector_zero_based(refout,ref,j);
        msetest[j] = uz_nn_mse(output,ref);
        msederv[j] = uz_nn_mse_derv(output,ref);
        float *msed = &msederv[j];
        uz_nn_backward_pass_mini_batch(test,msed,X);        
        // float result=uz_matrix_get_element_zero_based(output,0,0);
        // printf("output von minibatch member  %d ist = %.8f \n",(int)j, (double)result);
        // printf("mse von output minibatch member %d ist = %.8f \n",(int)j, (double)msetest[j]);
        }
        adam_optimizer_step(adam,test);
        uz_nn_set_gradients_zero(test);
        uz_matrix_t* output=uz_nn_get_output_data(test);
        msebatch[i] = uz_nn_mse(output,ref); 
        //float result=uz_matrix_get_element_zero_based(output,0,0);
       // printf("output nach minbatch  %d ist = %.8f \n",(int)i, (double)result);
       // printf("mse nach minibatch %d ist = %.8f \n",(int)i, (double)msebatch[i]);
        }
}


#endif // TEST
