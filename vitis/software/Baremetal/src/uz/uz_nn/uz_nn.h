#ifndef UZ_NN_H
#define UZ_NN_H
#include "uz_nn_layer.h"

/**
 * @brief Arbitrarily defined maximum number of layers for the module. Affect all instances of the module.
 *
 */
#define UZ_NN_MAX_LAYER 10U
enum target_update
{
    smoothing,
    periodic,
    periodic_smoothing
};

struct uz_nn_t
{
    bool is_ready;
    bool is_trainable;
    bool initialize;
    uint32_t number_of_layer;
    uint32_t number_of_inputs;
    uint32_t number_of_outputs;
    uz_nn_layer_t *layer[UZ_NN_MAX_LAYER];
};
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
uz_nn_t *uz_nn_init(struct uz_nn_layer_config config[UZ_NN_MAX_LAYER], uint32_t number_of_layer, bool is_trainable);
uz_nn_t *uz_nn_init_with_rand(struct uz_nn_layer_config config[UZ_NN_MAX_LAYER], uint32_t number_of_layer, uz_mtwister_t *twister, bool is_trainable);
/**
 * @brief Calculates one forward pass of the neural network.
 *
 * @param self Pointer to neural network instance
 * @param input Input matrix of dimension 1 x Inputs
 */
void uz_nn_copy(uz_nn_t *source, uz_nn_t *destination);
void uz_nn_copy_smoothing(uz_nn_t *source, uz_nn_t *destination, float *targetsmoothfact);
void uz_nn_target_update(uz_nn_t *critic, uz_nn_t *target, enum target_update method, float *targetsmoothfact);

void uz_nn_ff(uz_nn_t *self, uz_matrix_t const *const input);

/**
 * @brief Calculates one backward pass of the neural network.
 *
 * @param self Pointer to neural network instance
 * @param error Float value of the error, calculated outside the function
 * @param input Input matrix of dimension 1 x Inputs
 */

void uz_nn_backward_pass(uz_nn_t *self, const float *const error, uz_matrix_t *const input);
/**
 * @brief Calculates one backward pass of the neural network, for minibatch training.
 *
 * @param self Pointer to neural network instance
 * @param error Float value of the error, calculated outside the function
 * @param input Input matrix of dimension 1 x Inputs
 */

void uz_nn_backward_pass_mini_batch(uz_nn_t *self, const float *const error, uz_matrix_t const *const input);
/**
 * @brief Update whole neural network with gradient descent
 *
 * @param self
 * @param learnrate float, that determines the step size of the update
 */
void uz_nn_gradient_descent(uz_nn_t *self, float const learnrate);
void uz_nn_gradient_descent_no_bias(uz_nn_t *self, float const learnrate);
/**
 * @brief Update whole neural network with gradient descent
 *
 * @param self
 * @param learnrate float, that determines the step size of the update
 * @param minibatchsize size of the minibatch for the training
 */
void uz_nn_gradient_descent_mini_batch(uz_nn_t *self, float const learnrate, uint32_t minibatchsize);
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
/**
 * @brief Exports trained parameters to matlab, hardcoded for NN with two hidden layers.
 *
 * @param self
 */
void uz_nn_mat_export(uz_nn_t *self);
/**
 * @brief Calculates the mse for the expected and actual value
 *
 * @param output uz_matrix_t with the actual values
 * @param expectedoutput uz_matrix_t with the expected values
 * @return float
 */
float uz_nn_mse(uz_matrix_t *const output, uz_matrix_t const *const expectedoutput);
/**
 * @brief Calculates the derivate of the mse function for the expected and actual value
 *
 * @param output uz_matrix_t with the actual values
 * @param expectedoutput uz_matrix_t with the expected values
 * @return float
 */
float uz_nn_mse_derv(uz_matrix_t const *const output, uz_matrix_t const *const expectedoutput);
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
 * @param layer uint32_t value for layer, zero based
 * @return uz_matrix_t*
 */
uz_matrix_t *uz_nn_get_output_from_each_layer(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns a matrix with the sumout data of a specific layer
 *
 * @param self
 * @param layer uint32_t value for layer, zero based
 * @return uz_matrix_t*
 */
uz_matrix_t *uz_nn_get_sumout_data(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns a matrix with the bias data of a specific layer
 *
 * @param self
 * @param layer uint32_t value for layer, zero based
 * @return uz_matrix_t*
 */
uz_matrix_t *uz_nn_get_bias_matrix(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns a matrix with the weight data of a specific layer
 *
 * @param self
 * @param layer uint32_t value for layer, zero based
 * @return uz_matrix_t*
 */
uz_matrix_t *uz_nn_get_weight_matrix(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns a matrix with the delta data of a specific layer
 *
 * @param self
 * @param layer uint32_t value for layer, zero based
 * @return uz_matrix_t*
 */
uz_matrix_t *uz_nn_get_delta_data(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns a matrix with the gradient data of a specific layer
 *
 * @param self
 * @param layer uint32_t value for layer, zero based
 * @return uz_matrix_t*
 */
uz_matrix_t *uz_nn_get_gradient_data(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns a matrix with the cachegradient data of a specific layer
 *
 * @param self
 * @param layer uint32_t value for layer, zero based
 * @return uz_matrix_t*
 */
uz_matrix_t *uz_nn_get_cachegradient_data(uz_nn_t const *const self, uint32_t layer);
/**
 * @brief Returns number of layer from a nn
 *
 * @param self
 * @return uint32_t
 */
uint32_t uz_nn_get_number_of_layer(uz_nn_t const *const self);
/**
 * @brief Returns number of inputs from a nn
 *
 * @param self
 * @return uint32_t
 */
uint32_t uz_nn_get_number_of_inputs(uz_nn_t const *const self);
/**
 * @brief Returns number of outputs from a nn
 *
 * @param self
 * @return uint32_t
 */
uint32_t uz_nn_get_number_of_outputs(uz_nn_t const *const self);

/**
 * @brief Trains a neural network with a defined minibatch size for a determined number of epochs.
 *
 * @param self Pointer to neural network instance
 * @param mse Pointer to a float array for the MSE of the last trainingsvector, for debug/testing reasons
 * @param input Input matrix of dimension Minibatchsize x Inputs
 * @param refout Output matrix of dimension Minibatchsize x Outputs, target values for outputs
 * @param rowvec Input vector of dimension 1 x Inputs
 * @param ref Output vector of dimension 1 x Outputs, target values for output
 * @param learnrate Lernrate for updating NN
 * @param minibatchsize Minibatchsize of trainingsdata set
 * @param numberofepochs Number of epochs to train the network
 */

void uz_nn_train_minibatch(uz_nn_t *self, float *mse, uz_matrix_t const *const input, uz_matrix_t const *const refout, uz_matrix_t const *const rowvec, uz_matrix_t const *const ref, float const learnrate, uint32_t minibatchsize, uint32_t numberofepochs);
void adam_optimizer_step(adam_optimizer_t *optimizer, uz_nn_t *network);
void uz_nn_mse_derv_mult(uz_matrix_t const *const output, uz_matrix_t const *const expectedoutput, float *error);
#endif // UZ_NN_H
