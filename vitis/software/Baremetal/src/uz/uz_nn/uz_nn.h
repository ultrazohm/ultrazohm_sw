#ifndef UZ_NN_H
#define UZ_NN_H

#define UZ_NN_MAX_LAYER 10U
#include "uz_nn_layer.h"

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
uz_nn_t* uz_nn_init(struct uz_nn_layer_config config[UZ_NN_MAX_LAYER], size_t number_of_layer);

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
uz_matrix_t *uz_nn_get_output_data(uz_nn_t const *const self);


#endif // UZ_NN_H
