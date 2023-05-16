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
#include <stdio.h>
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
    uz_matrix_t *temporarybackprop;
    uz_matrix_t *gradients;
    uz_matrix_t *cachegradients;
    struct uz_matrix_t weight_matrix;
    struct uz_matrix_t bias_matrix;
    struct uz_matrix_t output_matrix;
    struct uz_matrix_t sumout_matrix;
    struct uz_matrix_t derivate_gradients_matrix;
    struct uz_matrix_t delta_matrix;
    struct uz_matrix_t error_matrix;
    struct uz_matrix_t temporarybackprop_matrix;
    struct uz_matrix_t gradients_matrix;
    struct uz_matrix_t cachegradients_matrix;
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
    uz_assert_not_NULL(layer_config.temporarybackprop);
    uz_assert_not_NULL(layer_config.gradients);
    uz_assert_not_NULL(layer_config.cachegradients);
    uz_assert((layer_config.number_of_neurons * layer_config.number_of_inputs) == layer_config.length_of_weights);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_output);
    uz_assert((layer_config.length_of_sumout * layer_config.length_of_sumout) == layer_config.length_of_derivate_gradients);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_delta);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_error);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_sumout);
    uz_assert(layer_config.number_of_neurons == layer_config.length_of_bias);
    uz_assert(layer_config.length_of_weights+layer_config.length_of_bias == layer_config.length_of_gradients);
    uz_assert(layer_config.number_of_cachegradrows * layer_config.number_of_cachegradcolumns == layer_config.length_of_cachegradients);
    uz_nn_layer_t *self = uz_nn_layer_allocation();
    self->number_of_neurons = layer_config.number_of_neurons;
    self->weights = uz_matrix_init(&self->weight_matrix, layer_config.weights, layer_config.length_of_weights, layer_config.number_of_inputs, layer_config.number_of_neurons);
    self->bias = uz_matrix_init(&self->bias_matrix, layer_config.bias, layer_config.length_of_bias, 1, layer_config.number_of_neurons);
    self->output = uz_matrix_init(&self->output_matrix, layer_config.output, layer_config.length_of_output, 1, layer_config.number_of_neurons);
    self->sumout = uz_matrix_init(&self->sumout_matrix, layer_config.sumout, layer_config.length_of_sumout, 1, layer_config.number_of_neurons);
    self->derivate_gradients = uz_matrix_init(&self->derivate_gradients_matrix, layer_config.derivate_gradients, layer_config.length_of_derivate_gradients, layer_config.length_of_sumout, layer_config.length_of_sumout);
    self->delta = uz_matrix_init(&self->delta_matrix, layer_config.delta, layer_config.length_of_delta,layer_config.number_of_neurons,1);
    self->error = uz_matrix_init(&self->error_matrix,layer_config.error, layer_config.length_of_error,layer_config.number_of_neurons,1);
    self->temporarybackprop = uz_matrix_init(&self->temporarybackprop_matrix,layer_config.temporarybackprop, layer_config.length_of_temporarybackprop,layer_config.number_of_temporaryrows,layer_config.number_of_temporarycolumns);
    self->gradients = uz_matrix_init(&self->gradients_matrix,layer_config.gradients, layer_config.length_of_gradients,layer_config.length_of_gradients,1);
    self->cachegradients = uz_matrix_init(&self->cachegradients_matrix,layer_config.cachegradients, layer_config.length_of_cachegradients,layer_config.number_of_cachegradrows,layer_config.number_of_cachegradcolumns);
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

void uz_nn_layer_back(uz_nn_layer_t *const self, uz_matrix_t *const locgradprev, uz_matrix_t *const weightprev)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_matrix_set_columnvector_as_diagonal(self->derivate_gradients,self->sumout);
    uz_matrix_apply_function_to_diagonal(self->derivate_gradients,self->activation_function_derivative);
    uz_matrix_multiply(self->derivate_gradients,weightprev,self->temporarybackprop);
    uz_matrix_multiply(self->temporarybackprop,locgradprev,self->delta);
}

// void uz_nn_layer_back_last_layer_matrix(uz_nn_layer_t *const self,uz_matrix_t *const reference)
// {
//     uz_assert_not_NULL(self);
//     uz_assert(self->is_ready);
//     // loop to calculate error in the last layer
//     for(size_t i=0;i<self->output->length_of_data;i++){

//         self->error->data[i]=reference[i]-self->output->data[i];

//     }
//     uz_matrix_set_columnvector_as_diagonal(self->derivate_gradients,self->sumout);
//     uz_matrix_apply_function_to_diagonal(self->derivate_gradients,self->activation_function_derivative);
//     uz_matrix_multiply(self->derivate_gradients,self->error,self->delta);
//     uz_matrix_multiply_by_scalar(self->delta,-1.0f); //-1 Am Ausgang
// }

void uz_nn_backward_last_layer(uz_nn_layer_t *const self,float *error)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->error->data = error;
    uz_matrix_set_columnvector_as_diagonal(self->derivate_gradients,self->sumout);
    uz_matrix_apply_function_to_diagonal(self->derivate_gradients,self->activation_function_derivative);
    uz_matrix_multiply(self->derivate_gradients,self->error,self->delta);
    uz_matrix_multiply_by_scalar(self->delta,-1.0f); //-1 Am Ausgang, 20.04. Test weil mse nicht funktioniert
}

// void uz_nn_layer_back_last_layer(uz_nn_layer_t *const self,float *reference)
// {
//     uz_assert_not_NULL(self);
//     uz_assert(self->is_ready);
//     // loop to calculate error in the last layer
//     for(size_t i=0;i<self->output->length_of_data;i++){

//         self->error->data[i]=reference[i]-self->output->data[i];

//     }
//     uz_matrix_set_columnvector_as_diagonal(self->derivate_gradients,self->sumout);
//     uz_matrix_apply_function_to_diagonal(self->derivate_gradients,self->activation_function_derivative);
//     uz_matrix_multiply(self->derivate_gradients,self->error,self->delta);
//     uz_matrix_multiply_by_scalar(self->delta,-1.0f); //-1 Am Ausgang
// }

void uz_nn_layer_calc_gradients(uz_nn_layer_t *const self, uz_matrix_t *const outputprev)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_matrix_multiply(self->delta,outputprev,self->cachegradients);
    uz_matrix_reshape_and_concatenate(self->cachegradients,self->delta,self->gradients);
    // if else statement macht probleme => switch case
     // check for the dimension of outputprev and delta, if necessary transpose outputprev
    //layer 2
    // if (outputprev->rows==self->delta->columns && outputprev->columns==self->delta->rows)
    // {
    // uz_matrix_multiply(self->delta,outputprev,self->cachegradients);
    // uz_matrix_transpose(self->cachegradients); 
    // }
    // /* diese Zeile ist nur damit am Schluss der Gradient gleich ist wie im Example, an sich ist es ja nicht nötig, da der Mittelwert
    // über alle Gradienten gebildet wird */
    // }
    // //layer 1
    // else if(outputprev->rows==1 && outputprev->columns == 1)
    // {
    //     uz_matrix_multiply(self->delta,outputprev,self->cachegradients);
    // }
    // // layer 3
    // else if (self->delta->columns==1 && self->delta->rows==1)
    // {
    // /* in der uz_matrix_multiply funktion ist es nicht möglich einen float mit einem Zeilenvektor zu multiplizieren,
    // ist durch uz_assert festgelegt 
    // 20.03.23: Problem behoben, indem in der Config self->cachegradients als Zeilenvektor angelegt wurde,
    // somit gibt es auch kein Problem mehr in der Loop in schroeder_example und es muss nur eine instanz initialisiert werden,
    // damit die 13 Trainingspaare berechnet werden können*/
    // uz_matrix_transpose(outputprev);
    // uz_matrix_multiply(self->delta,outputprev,self->cachegradients);
    // }

    //matrizen zusammenstellen und in self->gradients speichern, delta = gradient für bias in diesem Beispiel
    
}
void uz_nn_layer_calc_gradients_last_layer(uz_nn_layer_t *const self, uz_matrix_t *const outputprev)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_matrix_multiply(self->delta,outputprev,self->cachegradients);
    uz_matrix_reshape_and_concatenate(self->cachegradients,self->delta,self->gradients);
}

void uz_nn_update_layer_param(uz_nn_layer_t *const self, float lernrate)
{
uint32_t bias_index = self->bias->length_of_data;
uint32_t weight_index = self->weights->length_of_data;
//erst weights (loop von 0-649)
for(size_t i=0;i< weight_index;i++)
{
self->weights->data[i] = self->weights->data[i] + ( lernrate * (-1.0f * self->gradients->data[i]));
}
//dann bias (loop von 650-700 z.B.)
for(size_t i=weight_index;i<(weight_index+bias_index);i++)
{
self->bias->data[i-weight_index] = self->bias->data[i-weight_index] + ( lernrate * (-1.0f * self->gradients->data[i]));
}
// sinnvoller wäre es verschiedene Speicher anzulegen, dann kann man nicht durcheinander kommen!
}

void uz_nn_layer_matw_export(uz_nn_layer_t *const self, char *fname)
{
    FILE *f = fopen(fname, "w");
    for (uint32_t i = 0; i< self->weights->length_of_data; i++)
    {
    fprintf(f, "%.6f,", self->weights->data[i]); 
    } 
  fclose(f);
}

void uz_nn_layer_matb_export(uz_nn_layer_t *const self, char *fname)
{
    FILE *f = fopen(fname, "w");
    for (uint32_t i = 0; i< self->bias->length_of_data; i++)
    {
    fprintf(f, "%.6f,", self->bias->data[i]); 
    } 
  fclose(f);
}
void uz_nn_layer_update(uz_nn_layer_t *const self,float *theta, float *bias,float *lernrate)
{
    self->weights->data[0] = self->weights->data[0] - *lernrate * *theta;
    self->bias->data[0] = self->bias->data[0] - *lernrate * *bias;
}

void uz_nn_set_gradient_in_layer(uz_nn_layer_t *const self, uz_matrix_t const *const gradientmatrix)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->gradients->length_of_data == gradientmatrix->length_of_data); //assert wenn matrix nicht gleiche länge haben
    for(uint32_t i=0U;i<self->gradients->length_of_data;i++){
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

uz_matrix_t *uz_nn_layer_get_cachegradient_data(uz_nn_layer_t const*const self)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (self->cachegradients);
}

uz_matrix_t *uz_nn_layer_get_gradient_data(uz_nn_layer_t const*const self)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (self->gradients);
}
#endif
