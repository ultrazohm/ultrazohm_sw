/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2021 Tobias Schindler
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "../uz_global_configuration.h"
#if UZ_NN_LAYER_MAX_INSTANCES > 0U
#include "uz_nn_layer.h"
#include "../uz_HAL.h"

struct uz_nn_layer_t
{
    uint32_t number_of_neurons;
    uz_matrix_t *weights;
    uz_matrix_t *bias;
    uz_matrix_t *output;
    uz_matrix_t *sumout;
    uz_matrix_t *delta;
    uz_matrix_t *error;
    uz_matrix_t *temporarybackprop;
    uz_matrix_t *gradients;
    uz_matrix_t *cachegradients;
    struct uz_matrix_t weight_matrix;
    struct uz_matrix_t bias_matrix;
    struct uz_matrix_t output_matrix;
    struct uz_matrix_t sumout_matrix;
    struct uz_matrix_t delta_matrix;
    struct uz_matrix_t error_matrix;
    struct uz_matrix_t temporarybackprop_matrix;
    struct uz_matrix_t gradients_matrix;
    struct uz_matrix_t cachegradients_matrix;
    float *m;
    float *v;
    float (*activation_function)(float);
    float (*activation_function_derivative)(float);
    enum activation_function activation_function_name;
    bool is_ready;
};

static uint32_t instance_counter = 0U;
static uz_nn_layer_t instances[UZ_NN_LAYER_MAX_INSTANCES] = {0};

static uz_nn_layer_t *uz_nn_layer_allocation(void);

static uz_nn_layer_t *uz_nn_layer_allocation(void)
{
    uz_assert(instance_counter < UZ_NN_LAYER_MAX_INSTANCES);
    uz_nn_layer_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

static uint32_t instance_counter_optimizer = 0U;
static adam_optimizer_t instancesoptimizer[UZ_NN_LAYER_MAX_INSTANCES] = {0};

static adam_optimizer_t *uz_nn_optimizer_allocation(void);

static adam_optimizer_t *uz_nn_optimizer_allocation(void)
{
    uz_assert(instance_counter_optimizer < UZ_NN_OPTIMIZER_MAX_INSTANCES);
    adam_optimizer_t *self = &instancesoptimizer[instance_counter_optimizer];
    uz_assert_false(self->is_ready);
    instance_counter_optimizer++;
    self->is_ready = true;
    return (self);
}
adam_optimizer_t *uz_adam_init(float learnrate)
{
    adam_optimizer_t *self = uz_nn_optimizer_allocation();
    uz_adam_reset(self, learnrate);
    return (self);
}

void uz_adam_reset(adam_optimizer_t *self, float learn_rate)
{
    self->beta1 = 0.9f;
    self->beta2 = 0.999f;
    self->epsilon = 1e-8f;
    self->learnrate = learn_rate;
    self->traincounter = 0U;
}

uz_nn_layer_t *uz_nn_layer_init(struct uz_nn_layer_config layer_config)
{
    uz_assert_not_NULL(layer_config.weights);
    uz_assert_not_NULL(layer_config.bias);
    uz_assert_not_NULL(layer_config.output);
    uz_assert((layer_config.number_of_neurons * layer_config.number_of_inputs) == layer_config.length_of_weights);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_output);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_bias);
    uz_nn_layer_t *self = uz_nn_layer_allocation();
    self->number_of_neurons = layer_config.number_of_neurons;
    self->weights = uz_matrix_init(&self->weight_matrix, layer_config.weights, layer_config.length_of_weights, layer_config.number_of_inputs, layer_config.number_of_neurons);
    self->bias = uz_matrix_init(&self->bias_matrix, layer_config.bias, layer_config.length_of_bias, 1, layer_config.number_of_neurons);
    self->output = uz_matrix_init(&self->output_matrix, layer_config.output, layer_config.length_of_output, 1, layer_config.number_of_neurons);
    self->sumout = NULL;
    self->m = NULL;
    self->v = NULL;
    self->delta = NULL;
    self->error = NULL;
    self->temporarybackprop = NULL;
    self->gradients = NULL;
    self->cachegradients = NULL;
    self->activation_function_name = layer_config.activation_function;
    switch (layer_config.activation_function)
    {
    case activation_linear:
        self->activation_function = &uz_nn_activation_function_linear;
        self->activation_function_derivative = &uz_nn_activation_function_linear_derivative;
        break;
    case activation_ReLU:
        self->activation_function = &uz_nn_activation_function_relu;
        self->activation_function_derivative = &uz_nn_activation_function_relu_derivative;
        break;
    case activation_sigmoid:
        self->activation_function = &uz_nn_activation_function_sigmoid_logistic;
        self->activation_function_derivative = &uz_nn_activation_function_sigmoid_logistic_derivative;
        break;
    case activation_sigmoid2:
        self->activation_function = &uz_nn_activation_function_sigmoid2_logistic;
        self->activation_function_derivative = &uz_nn_activation_function_sigmoid2_logistic_derivative;
        break;
    case activation_tanh:
        self->activation_function = &uz_nn_activation_function_tanh;
        self->activation_function_derivative = &uz_nn_activation_function_tanh_derivative;
        break;
    default:
        uz_assert(0);
        break;
    }
    return (self);
}

uz_nn_layer_t *uz_nn_layer_init_trainable(struct uz_nn_layer_config layer_config)
{
    uz_assert_not_NULL(layer_config.weights);
    uz_assert_not_NULL(layer_config.bias);
    uz_assert_not_NULL(layer_config.output);
    uz_assert_not_NULL(layer_config.sumout);
    uz_assert_not_NULL(layer_config.delta);
    uz_assert_not_NULL(layer_config.error);
    uz_assert_not_NULL(layer_config.temporarybackprop);
    uz_assert_not_NULL(layer_config.gradients);
    uz_assert_not_NULL(layer_config.cachegradients);
    uz_assert((layer_config.number_of_neurons * layer_config.number_of_inputs) == layer_config.length_of_weights);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_output);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_delta);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_error);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_sumout);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_bias);
    uz_assert(layer_config.length_of_weights + layer_config.length_of_bias == layer_config.length_of_gradients);
    uz_assert(layer_config.number_of_cachegradrows * layer_config.number_of_cachegradcolumns == layer_config.length_of_cachegradients);
    uz_nn_layer_t *self = uz_nn_layer_allocation();
    self->number_of_neurons = layer_config.number_of_neurons;
    self->weights = uz_matrix_init(&self->weight_matrix, layer_config.weights, layer_config.length_of_weights, layer_config.number_of_inputs, layer_config.number_of_neurons);
    self->bias = uz_matrix_init(&self->bias_matrix, layer_config.bias, layer_config.length_of_bias, 1, layer_config.number_of_neurons);
    self->output = uz_matrix_init(&self->output_matrix, layer_config.output, layer_config.length_of_output, 1, layer_config.number_of_neurons);
    self->sumout = uz_matrix_init(&self->sumout_matrix, layer_config.sumout, layer_config.length_of_sumout, 1, layer_config.number_of_neurons);
    self->delta = uz_matrix_init(&self->delta_matrix, layer_config.delta, layer_config.length_of_delta, layer_config.number_of_neurons, 1);
    self->error = uz_matrix_init(&self->error_matrix, layer_config.error, layer_config.length_of_error, layer_config.number_of_neurons, 1);
    self->temporarybackprop = uz_matrix_init(&self->temporarybackprop_matrix, layer_config.temporarybackprop, layer_config.length_of_temporarybackprop, layer_config.number_of_temporaryrows, layer_config.number_of_temporarycolumns);
    self->gradients = uz_matrix_init(&self->gradients_matrix, layer_config.gradients, layer_config.length_of_gradients, layer_config.length_of_gradients, 1);
    self->cachegradients = uz_matrix_init(&self->cachegradients_matrix, layer_config.cachegradients, layer_config.length_of_cachegradients, layer_config.number_of_cachegradrows, layer_config.number_of_cachegradcolumns);
    self->m = layer_config.m;
    self->v = layer_config.v;
    self->activation_function_name = layer_config.activation_function;

    switch (layer_config.activation_function)
    {
    case activation_linear:
        self->activation_function = &uz_nn_activation_function_linear;
        self->activation_function_derivative = &uz_nn_activation_function_linear_derivative;
        break;
    case activation_ReLU:
        self->activation_function = &uz_nn_activation_function_relu;
        self->activation_function_derivative = &uz_nn_activation_function_relu_derivative;
        break;
    case activation_sigmoid:
        self->activation_function = &uz_nn_activation_function_sigmoid_logistic;
        self->activation_function_derivative = &uz_nn_activation_function_sigmoid_logistic_derivative;
        break;
    case activation_sigmoid2:
        self->activation_function = &uz_nn_activation_function_sigmoid2_logistic;
        self->activation_function_derivative = &uz_nn_activation_function_sigmoid2_logistic_derivative;
        break;
    case activation_tanh:
        self->activation_function = &uz_nn_activation_function_tanh;
        self->activation_function_derivative = &uz_nn_activation_function_tanh_derivative;
        break;
    default:
        uz_assert(0);
        break;
    }
    return (self);
}

void uz_nn_layer_init_Glorot_normal(uz_matrix_t *parameter, uz_prng_t *prng, float mean, float std)
{
    uz_assert_not_NULL(parameter);
    uz_assert_not_NULL(prng);
    for (uint32_t i = 0U; i < parameter->length_of_data; i++)
    {
        parameter->data[i] = uz_prng_get_normal_float(prng, mean, std);
    }
}

void uz_nn_layer_init_He_normal(uz_matrix_t *parameter, uz_prng_t *prng, float mean, float std)
{
    uz_assert_not_NULL(parameter);
    uz_assert_not_NULL(prng);
    for (uint32_t i = 0U; i < parameter->length_of_data; i++)
    {
        parameter->data[i] = uz_prng_get_normal_float(prng, mean, std);
    }
}

void uz_nn_layer_set_zero(uz_nn_layer_t* layer){
    uz_assert_not_NULL(layer);
    uz_matrix_set_zero(layer->bias);
    uz_matrix_set_zero(layer->weights);
}

void uz_nn_layer_param_init(uz_nn_layer_t *const layer, uz_prng_t *prng, uint32_t length_of_output)
{
    uz_assert_not_NULL(layer);
    uz_assert_not_NULL(prng);
    switch ((layer->activation_function_name))
    {
    case (activation_linear || activation_sigmoid || activation_tanh || activation_sigmoid2):
    {
        // float fanavg = (float)(layer->number_of_neurons/uz_matrix_get_number_of_rows(layer->output_matrix));
        float std = sqrtf(2.0f / (float)((layer->number_of_neurons + length_of_output)));
        float mean = 0.0f;
        // uz_nn_layer_init_Glorot(layer->bias,self);
        uz_nn_layer_init_Glorot_normal(layer->weights, prng, mean, std);
        break;
    }
    case activation_ReLU:
    {

        float std = sqrtf(2.0f / (float)((layer->number_of_neurons)));
        float mean = 0.0f;
        // float fanin = (float)(layer->number_of_neurons);
        // uz_nn_layer_init_He(layer->bias,self);
        uz_nn_layer_init_He_normal(layer->weights, prng, mean, std);
        break;
    }
    default:
    {
        break;
    }
    }
}

void uz_nn_layer_copy(uz_nn_layer_t *const sourcelayer, uz_nn_layer_t *const destinationlayer)
{
    uz_assert_not_NULL(sourcelayer);
    uz_assert_not_NULL(destinationlayer);
    uz_matrix_copy(sourcelayer->weights, destinationlayer->weights);
    uz_matrix_copy(sourcelayer->bias, destinationlayer->bias);
}

void uz_nn_layer_copy_smooth(uz_nn_layer_t *const sourcelayer, uz_nn_layer_t *const destinationlayer, float smoothfact)
{
    uz_assert_not_NULL(sourcelayer);
    uz_assert_not_NULL(destinationlayer);
    uz_matrix_update_smooth(sourcelayer->weights, destinationlayer->weights, smoothfact);
    uz_matrix_update_smooth(sourcelayer->bias, destinationlayer->bias, smoothfact);
}

void uz_nn_layer_ff(uz_nn_layer_t *const self, uz_matrix_t const *const input)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(input);
    uz_assert(self->is_ready);
    uz_assert(uz_matrix_get_number_of_rows(input) == 1U);
    uz_matrix_set_zero(self->output);
    uz_matrix_multiply(input, self->weights, self->output);
    uz_matrix_add(self->bias, self->output);
    if(self->sumout != NULL){ // If sumout is not NULL, the network is assumed to be trainable. Bit hacky
        uz_matrix_copy(self->output, self->sumout); // This line should probably be guarded by if(is_trainable such that the nn module behaves unchanged to the current state if it is not trainable.)
    }
    uz_matrix_apply_function_to_each_element(self->output, self->activation_function);
}

void uz_nn_layer_back(uz_nn_layer_t *const self, uz_matrix_t *const locgradprev, uz_matrix_t *const weightprev)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_matrix_apply_function_to_each_element(self->sumout, self->activation_function_derivative);
    uz_matrix_transpose(self->sumout);
    uz_matrix_columnvec_matrix_product(self->sumout, weightprev, self->temporarybackprop);
    uz_matrix_transpose(self->sumout);
    uz_matrix_multiply(self->temporarybackprop, locgradprev, self->delta);
}

void uz_nn_backward_last_layer(uz_nn_layer_t *const self, float *error)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    for (size_t i = 0; i < self->number_of_neurons; i++)
    {
        self->error->data[i] = error[i];
    }
    uz_matrix_apply_function_to_each_element(self->sumout, self->activation_function_derivative);
    uz_matrix_transpose(self->sumout);
    uz_matrix_elementwise_product(self->sumout, self->error, self->delta);
    uz_matrix_transpose(self->sumout);
}

void uz_nn_layer_calc_gradients(uz_nn_layer_t *const self, uz_matrix_t *const outputprev)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_matrix_multiply(self->delta, outputprev, self->cachegradients);
    uz_matrix_reshape_and_concatenate(self->cachegradients, self->delta, self->gradients);
}

void uz_nn_layer_calc_gradients_mini_batch(uz_nn_layer_t *const self, uz_matrix_t *const outputprev)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_matrix_multiply(self->delta, outputprev, self->cachegradients);
    uz_matrix_reshape_and_concatenate_acc(self->cachegradients, self->delta, self->gradients);
}

void uz_nn_update_layer_param(uz_nn_layer_t *const self, float lernrate)
{
    uz_matrix_multiply_by_scalar(self->cachegradients, lernrate);
    uz_matrix_multiply_by_scalar(self->cachegradients, -1.0f);
    uz_matrix_transpose(self->weights);
    uz_matrix_add(self->cachegradients, self->weights);
    uz_matrix_transpose(self->weights);
    uz_matrix_multiply_by_scalar(self->delta, lernrate);
    uz_matrix_multiply_by_scalar(self->delta, -1.0f);
    uz_matrix_transpose(self->delta);
    uz_matrix_add(self->delta, self->bias);
    uz_matrix_transpose(self->delta);
}
void uz_nn_update_layer_param_no_bias(uz_nn_layer_t *const self, float lernrate)
{
    uz_matrix_multiply_by_scalar(self->cachegradients, lernrate);
    uz_matrix_multiply_by_scalar(self->cachegradients, -1.0f);
    uz_matrix_transpose(self->weights);
    uz_matrix_add(self->cachegradients, self->weights);
    uz_matrix_transpose(self->weights);
}

void adam_layer_step(adam_optimizer_t *optimizer, uz_nn_layer_t *layer)
{
    uint32_t bias_index = layer->bias->length_of_data;
    uint32_t weight_index = layer->weights->length_of_data;
    // get number of params from layer
    uint32_t params = bias_index + weight_index;
    for (uint32_t i = 0; i < params; i++)
    {
        layer->m[i] = optimizer->beta1 * layer->m[i] + (1.0f - optimizer->beta1) * (layer->gradients->data[i]);
        layer->v[i] = optimizer->beta2 * layer->v[i] + (1.0f - optimizer->beta2) * (layer->gradients->data[i] * layer->gradients->data[i]);

        // Bias-corrected moving averages
        float m_hat = layer->m[i] / (1.0f - powf(optimizer->beta1, (float)optimizer->traincounter));
        float v_hat = layer->v[i] / (1.0f - powf(optimizer->beta2, (float)optimizer->traincounter));

        // Update weights
        if (i < weight_index)
        {
            layer->weights->data[i] -= optimizer->learnrate * m_hat / (sqrtf(v_hat) + optimizer->epsilon);
        }
        else
        {
            layer->bias->data[i - weight_index] -= optimizer->learnrate * m_hat / (sqrtf(v_hat) + optimizer->epsilon);
        }
    }
}

void adam_layer_reset(uz_nn_layer_t *layer)
{
    uint32_t bias_index = layer->bias->length_of_data;
    uint32_t weight_index = layer->weights->length_of_data;
    // get number of params from layer
    uint32_t params = bias_index + weight_index;
    for (uint32_t i = 0; i < params; i++)
    {
        layer->m[i] = 0.0f;
        layer->v[i] = 0.0f;
    }
}

void uz_nn_update_layer_param_mini_batch(uz_nn_layer_t *const self, float lernrate, uint32_t minibatchsize)
{
    uint32_t bias_index = self->bias->length_of_data;
    uint32_t weight_index = self->weights->length_of_data;
    // erst weights
    for (uint32_t i = 0; i < weight_index; i++)
    {
        self->weights->data[i] = self->weights->data[i] + (lernrate / (float)minibatchsize * (-1.0f * self->gradients->data[i]));
    }
    // dann bias
    for (uint32_t i = weight_index; i < (weight_index + bias_index); i++)
    {
        self->bias->data[i - weight_index] = self->bias->data[i - weight_index] + (lernrate / (float)minibatchsize * (-1.0f * self->gradients->data[i]));
    }
}

void uz_nn_layer_update(uz_nn_layer_t *const self, float *theta, float *bias, float *lernrate)
{
    self->weights->data[0] = self->weights->data[0] - *lernrate * *theta;
    self->bias->data[0] = self->bias->data[0] - *lernrate * *bias;
}

void uz_nn_set_gradient_in_layer(uz_nn_layer_t *const self, uz_matrix_t const *const gradientmatrix)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->gradients->length_of_data == gradientmatrix->length_of_data);
    for (uint32_t i = 0U; i < self->gradients->length_of_data; i++)
    {
        self->gradients->data[i] = gradientmatrix->data[i];
    }
}

void uz_nn_set_gradient_in_layer_zero(uz_nn_layer_t *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_matrix_set_zero(self->gradients);
}

uz_matrix_t *uz_nn_layer_get_output_data(uz_nn_layer_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->output);
}

uz_matrix_t *uz_nn_layer_get_sumout_data(uz_nn_layer_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->sumout);
}

uz_matrix_t *uz_nn_layer_get_bias_matrix(uz_nn_layer_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->bias;
}
uz_matrix_t *uz_nn_layer_get_weight_matrix(uz_nn_layer_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->weights;
}

uz_matrix_t *uz_nn_layer_get_delta_data(uz_nn_layer_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->delta);
}

uz_matrix_t *uz_nn_layer_get_cachegradient_data(uz_nn_layer_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->cachegradients);
}

uz_matrix_t *uz_nn_layer_get_gradient_data(uz_nn_layer_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->gradients);
}

/**
 * @brief Returns a pointer to the activation function of the layer
 *
 * @param self
 * @return float(*)(float)
 */
float (*uz_nn_layer_get_activation_function(uz_nn_layer_t const *const self))(float)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->activation_function);
}
#endif
