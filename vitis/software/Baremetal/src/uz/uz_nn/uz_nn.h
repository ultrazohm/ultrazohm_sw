#ifndef UZ_NN_H
#define UZ_NN_H
#include "uz_nn_layer.h"

/**
 * @brief Arbitrarily defined maximum number of layers for the module. Affect all instances of the module.
 * 
 */
#define UZ_NN_MAX_LAYER 10U

/**
 * @brief Object definition for one neural network
 * 
 */
typedef struct uz_nn_t uz_nn_t;


/**
 * @brief Initialization of a neural network object. 
 * 
 * @param config Array of length(number_of_layer) 
 * @param number_of_layer Number of layers including hidden layer and output layer (but not input layer)
 * @return uz_nn_t* 
 */
uz_nn_t* uz_nn_init(struct uz_nn_layer_config config[UZ_NN_MAX_LAYER], uint32_t number_of_layer);

/**
 * @brief Calculates one forward pass of the neural network.
 * 
 * @param self Pointer to neural network instance
 * @param input Input matrix of dimension 1 x Inputs
 */
void uz_nn_ff(uz_nn_t* self, uz_matrix_t const*const input);

/**
 * @brief Returns a matrix of dimension 1xOutputs of the last fordward pass.
 * 
 * @param self 
 * @return uz_matrix_t* 
 */
float uz_nn_calc_output_error(float output,float reference_output);
/**
 * @brief Returns ...
 * 
 * @param output Output of nn
 * @param reference_output expected output 
 * @return float of error 
 */
void uz_nn_backprop(uz_nn_t *self);

uz_matrix_t *uz_nn_get_output_data(uz_nn_t const *const self);

uz_matrix_t* uz_nn_get_sumout_data(uz_nn_t const *const self);
uz_matrix_t* uz_nn_get_bias_matrix(uz_nn_t const*const self, uint32_t layer);
uz_matrix_t* uz_nn_get_weight_matrix(uz_nn_t const*const self, uint32_t layer);
uint32_t uz_nn_get_number_of_layer(uz_nn_t const*const self);
uint32_t uz_nn_get_number_of_inputs(uz_nn_t const*const self);
uint32_t uz_nn_get_number_of_outputs(uz_nn_t const*const self);

#endif // UZ_NN_H
