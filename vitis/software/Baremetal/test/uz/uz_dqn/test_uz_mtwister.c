#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include <stdlib.h>
#include "uz_mtwister.h"
#include "uz_nn_layer.h"
#include "uz_matrix.h"
#include "uz_nn_activation_functions.h"
#define NUMBER_OF_INPUTS 3U
#define NUMBER_OF_NEURONS_IN_LAYER 4U


float x[NUMBER_OF_INPUTS] = {1.0f, 2.0f, 3.0f};
float w[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_LAYER] = {0.5377f, 1.8339f, -2.2588f, 0.8622f,
                                                          0.3188f, -1.3077f, -0.4336f, 0.3426f,
                                                          3.5784f, 2.7694f, -1.3499f, 3.0349f};
float b[NUMBER_OF_NEURONS_IN_LAYER] = {1.0f, -2.0f, 3.0f, -4.0f};
float out[NUMBER_OF_NEURONS_IN_LAYER] = {0};
float e[NUMBER_OF_NEURONS_IN_LAYER]={0};
float T[NUMBER_OF_NEURONS_IN_LAYER] = {0};
float s[NUMBER_OF_NEURONS_IN_LAYER] = {0};
float delta[NUMBER_OF_NEURONS_IN_LAYER] = {0};
float cacheg[NUMBER_OF_NEURONS_IN_LAYER * NUMBER_OF_INPUTS] = {0};
float g[NUMBER_OF_NEURONS_IN_LAYER + NUMBER_OF_NEURONS_IN_LAYER * NUMBER_OF_INPUTS] = {0};

struct uz_mtwister_config cfg = {
  .seed = 1,
  .distribution = uniform_distribution
};

void setUp(void)
{
}

void tearDown(void)
{
}

void uz_twister_init(void){
    init_mtwister(cfg);  
 }

void test_uz_twister_init_layer(void){
    uz_mtwister_t* twister = init_mtwister(cfg); 
    twister->mean = 10.0f;
    twister->std = 1.0f;
    struct uz_nn_layer_config config = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .number_of_cachegradrows = NUMBER_OF_INPUTS,
        .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_LAYER,
        .number_of_temporaryrows = 2,
        .number_of_temporarycolumns = 2,
        .length_of_weights = UZ_MATRIX_SIZE(w),
        .length_of_bias = UZ_MATRIX_SIZE(b),
        .length_of_output = UZ_MATRIX_SIZE(out),
        .length_of_sumout = UZ_MATRIX_SIZE(s),
        .length_of_delta = UZ_MATRIX_SIZE(delta),
        .length_of_error = UZ_MATRIX_SIZE(e),
        .length_of_gradients = UZ_MATRIX_SIZE(g),
        .length_of_temporarybackprop = UZ_MATRIX_SIZE(T),
        .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg),
        .weights = w,
        .bias = b,
        .output = out,
        .sumout = s,
        .delta = delta,
        .temporarybackprop = T,
        .gradients = g,
        .cachegradients = cacheg,
        .error = e
};
    uz_nn_layer_t *layer = uz_nn_layer_init_trainable(config);
    uz_nn_layer_param_init(layer,twister,config);
   // float btest[NUMBER_OF_NEURONS_IN_LAYER] = {1.0f, -2.0f, 3.0f, -4.0f};
   // float wtest[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_LAYER] = {0.5377f, 1.8339f, -2.2588f, 0.8622f,
     //                                                     0.3188f, -1.3077f, -0.4336f, 0.3426f,
     //                                                     3.5784f, 2.7694f, -1.3499f, 3.0349f};
    // TEST_ASSERT_EQUAL_FLOAT_ARRAY(btest,b,UZ_MATRIX_SIZE(b));
    // TEST_ASSERT_EQUAL_FLOAT_ARRAY(wtest,w,UZ_MATRIX_SIZE(w));
}

void test_uz_box_mueller_rand(void)
{
  // use mtwister, calculate double between 0 and 1 and scale it to Randmax
  //double randmax = 500; seedRand(0) 
  MTRand r = seedRand(1);
  float mean = 50.0f;
  float std = 0.5f;
  uint32_t length = 10;
  float array[10] = {0.0f};
  for(uint32_t i=0; i<length; i++) {
    // uint kann nicht in der Funktion gecastet werden, sonst kann man nichts mehr skalieren, es kommt nur 0 und 1 raus
    float rand = uz_random_box_mueller(&r, mean, std);
    //printf("%f\n", (double)rand);
    array[i]= rand;
  }
export_histogram(array,length);
// check with matlab plot histogram and x,y
}

void test_uint_32_t_array(void){
  MTRand r = seedRand(1);
  float min_val = 1;
  float max_val = 3;
  uint32_t size = 5;
  uint32_t array[5] = {10,10,10,10,10};
  genRand_uint32_t_array(array,&r,size, min_val, max_val);
  uint32_t expectedarray [5] = {2,2,2,2,2};
  TEST_ASSERT_UINT32_ARRAY_WITHIN (1, expectedarray, array,UZ_MATRIX_SIZE(array));
}
#endif // TEST