#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include "../uz_dqn/uz_mtwister.h"
#include "uz_sum.h"
#include "uz_codegen0_ert_rtw/uz_codegen0.h"
#include <time.h>
#include <stdlib.h>

#define NUMBER_OF_INPUTS 4
#define NUMBER_OF_OUTPUTS 3
#define NUMBER_OF_HIDDEN_LAYER 3
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 50
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 20
#define NUMBER_OF_EPOCHS 2000
#define MINI_BATCH_SIZE 150

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
float x_mat[NUMBER_OF_INPUTS * MINI_BATCH_SIZE] = {
#include "iris_weights_mse/xn_iris.csv"
};
float reference_mat[NUMBER_OF_OUTPUTS * MINI_BATCH_SIZE]= {
#include "iris_weights_mse/tn_iris.csv"
};

// Sollausgabe (1 Ausgabewert) aus Matlab
float reference_output[NUMBER_OF_OUTPUTS]= {
#include "iris_weights_mse/t_iris_in.csv"
};
// 13 Trainingsvektordaten aus Matlab(1-13)
float x[NUMBER_OF_INPUTS] = {
#include "iris_weights_mse/x_iris_in.csv"
};
float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "iris_weights_mse/layer1_weights_iris.csv"
};
float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "iris_weights_mse/layer1_bias_iris.csv"
		};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};


float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "iris_weights_mse/layer2_weights_iris.csv"
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "iris_weights_mse/layer2_bias_iris.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};


float w_3[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {
#include "iris_weights_mse/layer3_weights_iris.csv"
};
float b_3[NUMBER_OF_OUTPUTS] = {
#include "iris_weights_mse/layer3_bias_iris.csv"
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

float msetest = {0.0f};
float msederv [MINI_BATCH_SIZE] = {0.0f};
float mse_mb_train [NUMBER_OF_EPOCHS] = {0.0f};

float mse[NUMBER_OF_EPOCHS] = {
#include  "iris_weights_mse/mse_mean_iris_2000episodes.csv"
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


 void test_uz_nn_fit_iris_full_batch(void)
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
      float error[NUMBER_OF_OUTPUTS] = {0.0f};
      for (size_t i = 0; i < NUMBER_OF_EPOCHS; i++)
      {
      uint32_t mb_size = uz_matrix_get_number_of_rows(input);
      for(uint32_t j=0; j<mb_size;j++){
        uz_matrix_get_row_vector_zero_based(input,X,j);
        uz_nn_ff(test,X);
        uz_matrix_t* output=uz_nn_get_output_data(test);
        uz_matrix_get_row_vector_zero_based(refout,ref,j);
        msetest += uz_nn_mse(output,ref);
        uz_nn_mse_derv_mult(output,ref,error);
        uz_nn_backward_pass_mini_batch(test,error,X);        
        }
        float lernrate = 0.001f;
        uz_nn_gradient_descent_mini_batch(test,lernrate,mb_size);
        mse_mb_train[i] = msetest/(float)mb_size;
        uz_nn_set_gradients_zero(test);
        msetest = 0.0f;
        }
        // check gemittelten Fehler nach dem training mit matlab
        for(size_t i = 0;i< (int)(sizeof(mse) / sizeof(float));i++) {
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, mse[i],mse_mb_train[i]);
        }
}




#endif // TEST
