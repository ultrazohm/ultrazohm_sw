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
#include <stdbool.h>
struct uz_nn_layer_t
{
    uint32_t number_of_neurons;
    uz_matrix_t *weights;
    uz_matrix_t *bias;
    uz_matrix_t *output;
    struct uz_matrix_t weight_matrix;
    struct uz_matrix_t bias_matrix;
    struct uz_matrix_t output_matrix;
    float (*activation_function)(float);
    float (*activation_function_derivative)(float);
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

void uz_nn_layer_ff(uz_nn_layer_t *const self, uz_matrix_t const *const input)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(input);
    uz_assert(self->is_ready);
    uz_assert(uz_matrix_get_number_of_rows(input) == 1U);
    uz_matrix_set_zero(self->output);
    uz_matrix_multiply(input, self->weights, self->output);
    uz_matrix_add(self->bias, self->output);
    uz_matrix_apply_function_to_each_element(self->output, self->activation_function);
}

uz_matrix_t *uz_nn_layer_get_output_data(uz_nn_layer_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->output);
}

uz_matrix_t* uz_nn_layer_get_bias_matrix(uz_nn_layer_t const*const self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return self->bias;
}
uz_matrix_t* uz_nn_layer_get_weight_matrix(uz_nn_layer_t const*const self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return self->weights;
}


#endif
