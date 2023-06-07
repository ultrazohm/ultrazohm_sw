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
 * @brief Calculates one backward pass of the neural network.
 * 
 * @param self Pointer to neural network instance
 * @param error Float value of the error, calculated outside the function
 * @param input Input matrix of dimension 1 x Inputs
 */

void uz_nn_backward_pass(uz_nn_t *self,const float *const error, uz_matrix_t *const input);
/**
 * @brief Update whole neural network with gradient descent
 * 
 * @param self 
 * @param lernrate float, that determines the step size of the update
 */
void uz_nn_gradient_descent(uz_nn_t *self, float const learnrate);
/**
 * @brief Set gradient in specific layer to a uz_matrix_t instance with the same dimension
 * 
 * @param self 
 * @param gradientmatrix uz_matrix_t, that should be written into the gradient in the layer
  * @param layer layer, which gradients are overwritten
 */
void uz_nn_set_gradient_matrix(uz_nn_t *self, uz_matrix_t *const gradientmatrix, uint32_t layer);
/**
 * @brief Set all gradients in the network to zero.
 * 
 * @param self 
 */
void uz_nn_set_gradients_zero(uz_nn_t *self);
void uz_nn_schroeder_export(uz_nn_t *self);
void uz_nn_mat_export(uz_nn_t *self);
/**
 * @brief Calculates the mse for the expected and actual value
 * 
 * @param output uz_matrix_t with the actual values
 * @param expectedoutput uz_matrix_t with the expected values
 * @return float
 */
float uz_nn_mse(uz_matrix_t *const output, uz_matrix_t *const expectedoutput);
/**
 * @brief Calculates the derivate of the mse function for the expected and actual value
 * 
 * @param output uz_matrix_t with the actual values
 * @param expectedoutput uz_matrix_t with the expected values
 * @return float
 */
float uz_nn_mse_derv(uz_matrix_t *const output, uz_matrix_t *const expectedoutput);
/**
 * @brief Returns a matrix of dimension 1xOutputs of the last fordward pass.
 * 
 * @param self 
 * @return uz_matrix_t* 
 */
uz_matrix_t *uz_nn_get_output_data(uz_nn_t const *const self);
/**
 * @brief Returns a matrix of dimension 1xOutput of a specific layer
 * 
 * @param self 
 * @return uz_matrix_t* 
 */
uz_matrix_t *uz_nn_get_output_from_each_layer(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns a matrix with the sumout data of a specific layer
 * 
 * @param self 
 * @return uz_matrix_t* 
 */
uz_matrix_t *uz_nn_get_sumout_data(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns a matrix with the bias data of a specific layer
 * 
 * @param self 
 * @return uz_matrix_t* 
 */
uz_matrix_t* uz_nn_get_bias_matrix(uz_nn_t const*const self, uint32_t layer);
/**
 * @brief Returns a matrix with the weight data of a specific layer
 * 
 * @param self 
 * @return uz_matrix_t* 
 */
uz_matrix_t* uz_nn_get_weight_matrix(uz_nn_t const*const self, uint32_t layer);
/**
 * @brief Returns a matrix with the delta data of a specific layer
 * 
 * @param self 
 * @return uz_matrix_t* 
 */
uz_matrix_t *uz_nn_get_delta_data(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns a matrix with the gradient data of a specific layer
 * 
 * @param self 
 * @return uz_matrix_t* 
 */
uz_matrix_t* uz_nn_get_gradient_data(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns a matrix with the cachegradient data of a specific layer
 * 
 * @param self 
 * @return uz_matrix_t* 
 */
uz_matrix_t *uz_nn_get_cachegradient_data(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns number of layer from a nn
 * 
 * @param self 
 * @return uint32_t 
 */
uint32_t uz_nn_get_number_of_layer(uz_nn_t const*const self);
/**
 * @brief Returns number of inputs from a nn
 * 
 * @param self 
 * @return uint32_t 
 */
uint32_t uz_nn_get_number_of_inputs(uz_nn_t const*const self);
/**
 * @brief Returns number of outputs from a nn
 * 
 * @param self 
 * @return uint32_t 
 */
uint32_t uz_nn_get_number_of_outputs(uz_nn_t const*const self);


#endif // UZ_NN_H
