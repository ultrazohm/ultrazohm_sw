#ifndef UZ_NN_LAYER_H
#define UZ_NN_LAYER_H
#include "../uz_matrix/uz_matrix.h"
#include "uz_nn_activation_functions.h"

/**
 * @brief Object definition for a layer of a neural network
 * 
 */
typedef struct uz_nn_layer_t uz_nn_layer_t;


/**
 * @brief Enum for passing the type of the activation function to the init function of the layer
 * 
 */
enum activation_function{
    ReLU,
    linear
};

/**
 * @brief Configuration struct for a layer of uz_nn
 * 
 */
struct uz_nn_layer_config{
    enum activation_function activation_function; /**< Activation function of all neurons in this layer */
    size_t number_of_neurons; /**< Number of neurons in the layer */
    size_t number_of_inputs; /**< Number of inputs to the layer. Is either the number of inputs to the network or the number of neurons of the previouse layer */
    size_t length_of_weights; /**< Number of weights in the layer, has to be calculated by UZ_MATRIX_SIZE(weights) */
    size_t length_of_bias; /**< Number of bias in the layer, has to be calculated by UZ_MATRIX_SIZE(bias) */
    size_t length_of_output; /**< Number of outputs in the layer, has to be calculated by UZ_MATRIX_SIZE(output) and is equal to the number of weights */
    float *const weights; /** Pointer to an array that holds the weights */
    float *const bias; /** Pointer to an array that holds the bias */
    float *const output; /** Pointer to an array that holds the output / where the output is written to */
};

/**
 * @brief Initializes a layer of a neural network.
 *        Length of bias has to be equal to the number of neurons in the layer
 *        Length of output has to be equal to the number of neurons in the layer
 *        Length of weights has to be number_of_neurons*number_of_inputs
 * 
 * @param number_of_neurons 
 * @param number_of_inputs 
 * @param weights Array of the weights
 * @param length_of_weights Length of the weights calculated with ARRAY_SIZE(weights)
 * @param bias Array of the bias
 * @param length_of_bias Length of the bias calculated with ARRAY_SIZE(bias)
 * @param output Array for the output of the layer
 * @param length_of_output Length of the bias calculated with ARRAY_SIZE(output)
 * @param activation Defines the activation function of the layer using an enum type
 * @return uz_nn_layer* Pointer to the layer object
 */

//uz_nn_layer_t *uz_nn_layer_init(size_t number_of_neurons, size_t number_of_inputs,
//                              float *const weights, size_t length_of_weights,
//                              float *const bias, size_t length_of_bias,
//                              float *const output, size_t length_of_output,
//                              enum activation_function activation);

uz_nn_layer_t *uz_nn_layer_init(struct uz_nn_layer_config layer_config);

/**
 * @brief Calculates one forward pass of the network with the given input value (column vector)
 * 
 * @param self 
 * @param input Column vector of inputs (rows==1 !)
 */
void uz_nn_layer_ff(uz_nn_layer_t *const self, uz_matrix_t const*const input);

/**
 * @brief Returns a pointer to the output data of the layer.
 *        Intended to be used by the following layer as input data.
 * 
 * @param self 
 * @return uz_matrix* 
 */
uz_matrix_t* uz_nn_layer_get_output_data(uz_nn_layer_t const*const self);

#endif // UZ_NN_LAYER_H
