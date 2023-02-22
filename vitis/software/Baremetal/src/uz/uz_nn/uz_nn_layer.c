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
    uz_matrix_t *sumout;// wird benötigt für backprop
    uz_matrix_t *derivate_gradients;// wird benötigt für backprop
    uz_matrix_t *delta;// wird benötigt für backprop
    uz_matrix_t *error;//Speichern des zwischenwert für den Fehler
    uz_matrix_t *gradients;
    struct uz_matrix_t weight_matrix;
    struct uz_matrix_t bias_matrix;
    struct uz_matrix_t output_matrix;
    struct uz_matrix_t sumout_matrix;
    struct uz_matrix_t derivate_gradients_matrix;
    struct uz_matrix_t delta_matrix;
    struct uz_matrix_t error_matrix;
    struct uz_matrix_t gradients_matrix;
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
    uz_assert_not_NULL(layer_config.sumout);
    uz_assert_not_NULL(layer_config.derivate_gradients);
    uz_assert_not_NULL(layer_config.delta);
    uz_assert_not_NULL(layer_config.error);
    uz_assert_not_NULL(layer_config.gradients);
    uz_assert((layer_config.number_of_neurons * layer_config.number_of_inputs) == layer_config.length_of_weights);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_output);
    uz_assert((layer_config.length_of_sumout * layer_config.length_of_sumout) == layer_config.length_of_derivate_gradients);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_delta);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_error);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_sumout);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_bias);
    uz_assert(layer_config.length_of_weights+layer_config.length_of_bias == layer_config.length_of_gradients);
    uz_nn_layer_t *self = uz_nn_layer_allocation();
    self->number_of_neurons = layer_config.number_of_neurons;
    self->weights = uz_matrix_init(&self->weight_matrix, layer_config.weights, layer_config.length_of_weights, layer_config.number_of_inputs, layer_config.number_of_neurons);
    self->bias = uz_matrix_init(&self->bias_matrix, layer_config.bias, layer_config.length_of_bias, 1, layer_config.number_of_neurons);
    self->output = uz_matrix_init(&self->output_matrix, layer_config.output, layer_config.length_of_output, 1, layer_config.number_of_neurons);
    self->sumout = uz_matrix_init(&self->sumout_matrix, layer_config.sumout, layer_config.length_of_sumout, 1, layer_config.number_of_neurons);
    self->derivate_gradients = uz_matrix_init(&self->derivate_gradients_matrix, layer_config.derivate_gradients, layer_config.length_of_derivate_gradients, layer_config.length_of_sumout, layer_config.length_of_sumout);
    self->delta = uz_matrix_init(&self->delta_matrix, layer_config.delta, layer_config.length_of_delta,layer_config.number_of_neurons,1);
    self->error = uz_matrix_init(&self->error_matrix,layer_config.error, layer_config.length_of_error,layer_config.number_of_neurons,1);
    self->gradients = uz_matrix_init(&self->gradients_matrix,layer_config.gradients, layer_config.length_of_gradients,layer_config.length_of_gradients,1);
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
    uz_matrix_copy(self->output,self->sumout);// speichere Wert für Summenausgang
    uz_matrix_apply_function_to_each_element(self->output, self->activation_function);
}

void uz_nn_layer_back(uz_nn_layer_t *const self, uz_matrix_t *const locgradprev, uz_matrix_t *const weightprev, uz_matrix_t *cache)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_matrix_set_columnvector_as_diagonal(self->derivate_gradients,self->sumout);
    uz_matrix_apply_function_to_diagonal(self->derivate_gradients,self->activation_function_derivative);
    uz_matrix_multiply(self->derivate_gradients,weightprev,cache); //matrix zum zwischenspeichern
    // float cache1 = uz_matrix_get_element_zero_based(cache,0,0);
    // float cache2 = uz_matrix_get_element_zero_based(cache,1,0);
    // float cache3 = uz_matrix_get_element_zero_based(cache,0,1);
    // float cache4 = uz_matrix_get_element_zero_based(cache,1,1);
    // funktioniert bis hierhin, cache hat die richtigen Werte
    // mit copybefehl kein assert, die Frage ist warum, die Dimension ist laut debugger gleich
    // uz_matrix_copy würde auch in assert gehen wenn dimension ungleich
    // für layer 2 funktioniert es nur mit copy für layer 1 failt es logischerweise, da die Dimension anders ist
    //uz_matrix_copy(cache,self->gradientslocal);
    uz_matrix_multiply(cache,locgradprev,self->delta);
}

void uz_nn_layer_back_last_layer(uz_nn_layer_t *const self,float const *const reference)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // loop to calculate error in the last layer
    for(size_t i=0;i<self->output->length_of_data;i++){

        self->error->data[i]=reference[i]-self->output->data[i];

    }
    uz_matrix_set_columnvector_as_diagonal(self->derivate_gradients,self->sumout);
    uz_matrix_apply_function_to_diagonal(self->derivate_gradients,self->activation_function_derivative);
    uz_matrix_multiply(self->derivate_gradients,self->error,self->delta);
    uz_matrix_multiply_by_scalar(self->delta,-1.0f); //-1 Am Ausgang
}

void uz_nn_layer_calc_gradients(uz_nn_layer_t *const self, uz_matrix_t *const outputprev, uz_matrix_t *const biasprev)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    float zw1[2] = {0};
    //zuerst gradienten bezogen auf Gewichte bilden
    struct uz_matrix_t zw1_matrix={0};
    uz_matrix_t *zwischenmatrix1=uz_matrix_init(&zw1_matrix, zw1,2,2,1);
    uz_matrix_transpose(outputprev);
    uz_matrix_multiply(outputprev,self->delta,zwischenmatrix1);
    //matrizen zusammenbasteln und in self->gradients speichern, delta = gradient für bias in diesem Beispiel
    uz_matrix_columnvec_concatenate_horizontal(zwischenmatrix1,self->delta,self->gradients);    
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

uz_matrix_t *uz_nn_layer_get_derivate_data(uz_nn_layer_t const*const self)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (self->derivate_gradients);
}

uz_matrix_t *uz_nn_layer_get_delta_data(uz_nn_layer_t const*const self)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (self->delta);
}

uz_matrix_t *uz_nn_layer_get_gradient_data(uz_nn_layer_t const*const self)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (self->gradients);
}
#endif
