#ifndef UZ_NN_LAYER_H
#define UZ_NN_LAYER_H
#include "../uz_matrix/uz_matrix.h"
#include "uz_nn_activation_functions.h"
#include <stdint.h>
#include <stdint.h>


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
    activation_ReLU,
    activation_linear,
    activation_sigmoid,
    activation_sigmoid2,
    activation_tanh
};

/**
 * @brief Configuration struct for a layer of uz_nn
 * 
 */
struct uz_nn_layer_config{
    enum activation_function activation_function; /**< Activation function of all neurons in this layer */
    uint32_t number_of_neurons; /**< Number of neurons in the layer */
    uint32_t number_of_inputs; /**< Number of inputs to the layer. Is either the number of inputs to the network or the number of neurons of the previouse layer */
    uint32_t length_of_weights; /**< Number of weights in the layer, has to be calculated by UZ_MATRIX_SIZE(weights) */
    uint32_t length_of_bias; /**< Number of bias in the layer, has to be calculated by UZ_MATRIX_SIZE(bias) */
    uint32_t length_of_output;/**< Number of outputs in the layer, has to be calculated by UZ_MATRIX_SIZE(output) and is equal to the number of weights */
    uint32_t length_of_sumout; 
    uint32_t length_of_derivate_gradients; 
    uint32_t length_of_gradientslocal; 
    float *const weights; /** Pointer to an array that holds the weights */
    float *const bias; /** Pointer to an array that holds the bias */
    float *const output; /** Pointer to an array that holds the output / where the output is written to */
    float *const sumout;
    float *const derivate_gradients;
    float *const gradientslocal;
};

/**
 * @brief Initializes a layer of a neural network.
 * 
 * @param layer_config Configuration struct
 * @return uz_nn_layer_t* 
 */
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
void uz_nn_layer_back(uz_nn_layer_t *const self);

uz_matrix_t* uz_nn_layer_get_output_data(uz_nn_layer_t const*const self);
uz_matrix_t *uz_nn_layer_get_sumout_data(uz_nn_layer_t const *const self);
uz_matrix_t* uz_nn_layer_get_bias_matrix(uz_nn_layer_t const*const self);
uz_matrix_t* uz_nn_layer_get_weight_matrix(uz_nn_layer_t const*const self);
uz_matrix_t* uz_nn_layer_get_derivate_data(uz_nn_layer_t const*const self);
uz_matrix_t *uz_nn_layer_get_derivate_activationfunc(uz_nn_layer_t const *const self);
uz_matrix_t *uz_nn_layer_get_localgradients(uz_nn_layer_t const *const self);
#endif // UZ_NN_LAYER_H
