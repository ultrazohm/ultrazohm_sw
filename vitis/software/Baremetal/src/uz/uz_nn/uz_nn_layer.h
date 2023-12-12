#ifndef UZ_NN_LAYER_H
#define UZ_NN_LAYER_H
#include "../uz_matrix/uz_matrix.h"
#include "../uz_prng/uz_prng.h"
#include "uz_nn_activation_functions.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Object definition for a layer of a neural network
 *
 */
typedef struct uz_nn_layer_t uz_nn_layer_t;
typedef struct adam_optimizer_t adam_optimizer_t;

struct adam_optimizer_t
{
    float beta1;
    float beta2;
    float epsilon;
    float learnrate;
    uint32_t traincounter;
    bool is_ready;
};

/**
 * @brief Enum for passing the type of the activation function to the init function of the layer
 *
 */
enum activation_function
{
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
struct uz_nn_layer_config
{
    enum activation_function activation_function; /**< Activation function of all neurons in this layer */
    uint32_t number_of_neurons;                   /**< Number of neurons in the layer */
    uint32_t number_of_inputs;                    /**< Number of inputs to the layer. Is either the number of inputs to the network or the number of neurons of the previouse layer */
    uint32_t number_of_temporarycolumns;          /**< Number of temporarycolumns to the layer. Is the number of neurons in the actual layer */
    uint32_t number_of_temporaryrows;             /**< Number of temporaryrows to the layer. Is the number of neurons in the next layer,for the output layer it is not used  */
    uint32_t number_of_cachegradcolumns;          /**< Number of cachegradcolumns to the layer. Is either the number of inputs to the network or the number of neurons of the previouse layer */
    uint32_t number_of_cachegradrows;             /**< Number of inputs to the layer. Is the number of neurons in the actual layer */
    uint32_t length_of_weights;                   /**< Number of weights in the layer, has to be calculated by UZ_MATRIX_SIZE(weights) */
    uint32_t length_of_bias;                      /**< Number of bias in the layer, has to be calculated by UZ_MATRIX_SIZE(bias) */
    uint32_t length_of_output;                    /**< Number of outputs in the layer, has to be calculated by UZ_MATRIX_SIZE(output) and is equal to the number of weights */
    uint32_t length_of_sumout;                    /**< Number of sumouts in the layer, has to be calculated by UZ_MATRIX_SIZE(sumout) and is equal to the number of weights or number of outputs */
    uint32_t length_of_delta;                     /**< Number of delta in the layer, has to be calculated by UZ_MATRIX_SIZE(delta) and is equal to the number of bias*/
    uint32_t length_of_error;                     /**< Number of error in the layer, has to be calculated by UZ_MATRIX_SIZE(error) and is equal to the number of neurons in the layer  */
    uint32_t length_of_temporarybackprop;         /**< Number of temporarybackprop in the layer, has to be calculated by UZ_MATRIX_SIZE(temporarybackprop) and is equal to the number of neurons in the layer */
    uint32_t length_of_gradients;                 /**< Number of gradients in the layer, has to be calculated by UZ_MATRIX_SIZE(gradients) and is equal to the number of weights + number of bias */
    uint32_t length_of_cachegradients;            /**< Number of cachegradients in the layer, has to be calculated by UZ_MATRIX_SIZE(cachegradients) and is equal to the number of weights or number of outputs */
    float *const m;                               /** Pointer to an array that holds the biased first moment estimate for Adam */
    float *const v;                               /** Pointer to an array that holds the biased second raw moment estimate for Adam */
    float *const weights;                         /** Pointer to an array that holds the weights */
    float *const bias;                            /** Pointer to an array that holds the bias */
    float *const output;                          /** Pointer to an array that holds the output / where the output is written to */
    float *const sumout;                          /** Pointer to an array that holds the sumout, before activation function is appllied*/
    float *const delta;                           /** Pointer to an array that stores the delta values*/
    float *const temporarybackprop;               /** Pointer to an array that stores temporary values for the backward pass*/
    float *const error;                           /** Pointer to an array that stores the error values from the layer*/
    float *const gradients;                       /** Pointer to an array that stores the gradient values*/
    float *const cachegradients;                  /** Pointer to an array that stores the cache values for the gradient*/
};
/**
 * @brief Initializes a layer of a neural network.
 *
 * @param layer_config Configuration struct
 * @return uz_nn_layer_t*
 */
uz_nn_layer_t *uz_nn_layer_init(struct uz_nn_layer_config layer_config);
uz_nn_layer_t *uz_nn_layer_init_trainable(struct uz_nn_layer_config layer_config);
void uz_nn_layer_init_He_uniform(uz_matrix_t *parameter, uz_prng_t *prng, float mean, float std);
void uz_nn_layer_init_Glorot_uniform(uz_matrix_t *parameter, uz_prng_t *prng, float mean, float std);

void uz_nn_layer_param_init(uz_nn_layer_t *const layer, uz_prng_t *prng, struct uz_nn_layer_config layer_config);
/**
 * @brief Calculates one forward pass of a network layer with the given input value (column vector)
 *
 * @param self
 * @param input Column vector of inputs (rows==1 !)
 */
void uz_nn_layer_ff(uz_nn_layer_t *const self, uz_matrix_t const *const input);
void uz_nn_layer_copy(uz_nn_layer_t *const sourcelayer, uz_nn_layer_t *const destinationlayer);
void uz_nn_layer_copy_smooth(uz_nn_layer_t *const sourcelayer, uz_nn_layer_t *const destinationlayer, float smoothfact);
void uz_nn_update_layer_param_no_bias(uz_nn_layer_t *const self, float lernrate);
/**
 * @brief Calculates one backward pass of a the output layer with the given error value
 *
 * @param self
 * @param error Float value of the error, calculated outside the function
 */
void uz_nn_backward_last_layer(uz_nn_layer_t *const self, float *error);
/**
 * @brief Calculates one backward pass of a network layer with the given input value (column vector)
 *
 * @param self
 * @param locgradprev uz_matrix_t instance, delta from i+1 layer
 * @param weightprev uz_matrix_t instance, weights from i+1 layer
 */

void uz_nn_layer_back(uz_nn_layer_t *const self, uz_matrix_t *const locgradprev, uz_matrix_t *const weightprev);
/**
 * @brief Calculates the gradients for one layer
 *
 * @param self
 * @param outputprev uz_matrix_t instance, output from i+1 layer
 */

void uz_nn_layer_calc_gradients(uz_nn_layer_t *const self, uz_matrix_t *const outputprev);

/**
 * @brief Calculates the gradients for one layer, for mini batch training, gradients are accumulated
 *
 * @param self
 * @param outputprev uz_matrix_t instance, output from i+1 layer
 */
void uz_nn_layer_calc_gradients_mini_batch(uz_nn_layer_t *const self, uz_matrix_t *const outputprev);
void uz_nn_layer_update(uz_nn_layer_t *const self, float *theta, float *bias, float *lernrate);
/**
 * @brief Update the layer parameter with gradient descent
 *
 * @param self
 * @param lernrate float, that determines the step size of the update
 */
void uz_nn_update_layer_param(uz_nn_layer_t *const self, float lernrate);
/**
 * @brief Update the layer parameter with gradient descent
 *
 * @param self
 * @param lernrate float, that determines the step size of the update
 * @param minibatchsize float, that determines the mini batch size of the training parameter
 */
void uz_nn_update_layer_param_mini_batch(uz_nn_layer_t *const self, float lernrate, uint32_t minibatchsize);



/**
 * @brief Set gradient in layer to a uz_matrix_t instance with the same dimension
 *
 * @param self
 * @param gradientmatrix uz_matrix_t, that should be written into the gradient in the layer
 */
void uz_nn_set_gradient_in_layer(uz_nn_layer_t *const self, uz_matrix_t const *const gradientmatrix);
/**
 * @brief Set gradient in layer to zero
 *
 * @param self
 */
void uz_nn_set_gradient_in_layer_zero(uz_nn_layer_t *const self);
/**
 * @brief Returns a pointer to the output data of the layer.
 *        Intended to be used by the following layer as input data.
 *
 * @param self
 * @return uz_matrix*
 */
uz_matrix_t *uz_nn_layer_get_output_data(uz_nn_layer_t const *const self);
/**
 * @brief Returns a pointer to the sumout data of the layer.
 *
 * @param self
 * @return uz_matrix*
 */
uz_matrix_t *uz_nn_layer_get_sumout_data(uz_nn_layer_t const *const self);
/**
 * @brief Returns a pointer to the bias data of the layer.
 *
 * @param self
 * @return uz_matrix*
 */
uz_matrix_t *uz_nn_layer_get_bias_matrix(uz_nn_layer_t const *const self);
/**
 * @brief Returns a pointer to the weight data of the layer.
 *
 * @param self
 * @return uz_matrix*
 */
uz_matrix_t *uz_nn_layer_get_weight_matrix(uz_nn_layer_t const *const self);
/**
 * @brief Returns a pointer to the delta data of the layer.
 *
 * @param self
 * @return uz_matrix*
 */
uz_matrix_t *uz_nn_layer_get_delta_data(uz_nn_layer_t const *const self);
/**
 * @brief Returns a pointer to the gradient data of the layer.
 *
 * @param self
 * @return uz_matrix*
 */
uz_matrix_t *uz_nn_layer_get_gradient_data(uz_nn_layer_t const *const self);
/**
 * @brief Returns a pointer to the cachegradient data of the layer.
 *
 * @param self
 * @return uz_matrix*
 */
uz_matrix_t *uz_nn_layer_get_cachegradient_data(uz_nn_layer_t const *const self);
adam_optimizer_t *uz_adam_init(float learnrate);
void adam_layer_step(adam_optimizer_t *optimizer, uz_nn_layer_t *layer);
#endif // UZ_NN_LAYER_H
