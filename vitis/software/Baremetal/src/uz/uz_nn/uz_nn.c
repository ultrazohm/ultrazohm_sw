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
#if UZ_NN_MAX_INSTANCES > 0U
#include <stdio.h>
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_nn.h"
#include "../uz_matrix/uz_matrix.h"

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

static uint32_t instance_counter = 0U;
static uz_nn_t instances[UZ_NN_MAX_INSTANCES] = {0};

static uz_nn_t *uz_nn_allocation(void);

static uz_nn_t *uz_nn_allocation(void)
{
    uz_assert(instance_counter < UZ_NN_MAX_INSTANCES);
    uz_nn_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_nn_t *uz_nn_init(struct uz_nn_layer_config config[UZ_NN_MAX_LAYER], uint32_t number_of_layer, bool is_trainable)
{
    uz_assert(number_of_layer < UZ_NN_MAX_LAYER);
    uz_assert(number_of_layer > 1U);
    uz_nn_t *self = uz_nn_allocation();
    self->is_trainable = is_trainable;
    self->number_of_layer = number_of_layer;
    self->number_of_inputs = config[0U].number_of_inputs;
    self->number_of_outputs = config[number_of_layer - 1U].length_of_output;
    if (self->is_trainable == true)
    {
        for (uint32_t i = 0U; i < number_of_layer; i++)
        {
            self->layer[i] = uz_nn_layer_init_trainable(config[i]);
        }
    }
    else
    {
        for (uint32_t i = 0U; i < number_of_layer; i++)
        {
            self->layer[i] = uz_nn_layer_init(config[i]);
        }
    }
    return (self);
}

uz_nn_t *uz_nn_init_with_rand(struct uz_nn_layer_config config[UZ_NN_MAX_LAYER], uint32_t number_of_layer, uz_mtwister_t *twister, bool is_trainable)
{
    uz_assert(number_of_layer < UZ_NN_MAX_LAYER);
    uz_assert(number_of_layer > 1U);
    uz_nn_t *self = uz_nn_allocation();
    self->is_trainable = is_trainable;
    self->number_of_layer = number_of_layer;
    self->number_of_inputs = config[0U].number_of_inputs;
    self->number_of_outputs = config[number_of_layer - 1U].length_of_output;
    self->initialize = true;
    if (self->is_trainable == true || self->initialize == true)
    {
        for (uint32_t i = 0U; i < number_of_layer; i++)
        {
            self->layer[i] = uz_nn_layer_init_trainable(config[i]);
            uz_nn_layer_param_init(self->layer[i], twister, config[i]);
        }
    }
    return (self);
}

void uz_nn_copy(uz_nn_t *source, uz_nn_t *destination)
{
    uz_assert_not_NULL(source);
    uz_assert_not_NULL(destination);
    // durch die layer loopen
    for (size_t i = 0; i < source->number_of_layer; i++)
    {
        uz_nn_layer_copy(source->layer[i], destination->layer[i]);
    }
}

void uz_nn_copy_smoothing(uz_nn_t *source, uz_nn_t *destination, float *targetsmoothfact)
{
    uz_assert_not_NULL(source);
    uz_assert_not_NULL(destination);
    // durch die layer loopen
    for (size_t i = 0; i < source->number_of_layer; i++)
    {
        uz_nn_layer_copy_smooth(source->layer[i], destination->layer[i], targetsmoothfact);
    }
}

void uz_nn_target_update(uz_nn_t *critic, uz_nn_t *target, enum target_update method, float *targetsmoothfact)
{
    uz_assert_not_NULL(critic);
    uz_assert_not_NULL(target);
    switch (method)
    {
    case smoothing:
        uz_assert_not_NULL(targetsmoothfact);
        uz_nn_copy_smoothing(critic, target, targetsmoothfact);
        break;
    case periodic:
        uz_nn_copy(critic,target);
        break;
    case periodic_smoothing:
        uz_assert_not_NULL(targetsmoothfact);
        uz_nn_copy_smoothing(critic, target, targetsmoothfact);
        break;
    default:
        uz_assert(0);
        break;
    }
}

void uz_nn_train_minibatch(uz_nn_t *self, float *mse, uz_matrix_t const *const input, uz_matrix_t const *const refout, uz_matrix_t const *const rowvec, uz_matrix_t const *const ref, float const learnrate, uint32_t minibatchsize, uint32_t numberofepochs)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->is_trainable);
    for (uint32_t i = 0; i < numberofepochs; i++)
    {
        for (uint32_t j = 0; j < minibatchsize; j++)
        {
            uz_matrix_get_row_vector_zero_based(input, rowvec, j);
            uz_nn_ff(self, rowvec);
            uz_matrix_t *output = uz_nn_get_output_data(self);
            uz_matrix_get_row_vector_zero_based(refout, ref, j);
            float msederv = uz_nn_mse_derv(output, ref);
            uz_nn_backward_pass_mini_batch(self, &msederv, rowvec);
        }
        uz_nn_gradient_descent_mini_batch(self, learnrate, minibatchsize);
        uz_matrix_t *output = uz_nn_get_output_data(self);
        mse[i] = uz_nn_mse(output, ref);
        uz_nn_set_gradients_zero(self);
    }
}

void uz_nn_ff(uz_nn_t *self, uz_matrix_t const *const input)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert_not_NULL(input);
    uz_nn_layer_ff(self->layer[0], input);
    for (uint32_t i = 0; i < (self->number_of_layer - 1U); i++)
    {
        uz_nn_layer_ff(self->layer[i + 1U], uz_nn_layer_get_output_data(self->layer[i]));
    }
}

void uz_nn_gradient_descent(uz_nn_t *self, float const learnrate)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->is_trainable);
    for (uint32_t i = 0; i < (self->number_of_layer); i++)
    {
        uz_nn_update_layer_param(self->layer[i], learnrate);
    }
}

void uz_nn_gradient_descent_mini_batch(uz_nn_t *self, float const learnrate, uint32_t minibatchsize)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->is_trainable);
    for (uint32_t i = 0; i < (self->number_of_layer); i++)
    {
        uz_nn_update_layer_param_mini_batch(self->layer[i], learnrate, minibatchsize);
    }
}

float uz_nn_mse_derv(uz_matrix_t const *const output, uz_matrix_t const *const expectedoutput)
{
    uz_assert(expectedoutput->length_of_data == output->length_of_data);
    float z = 0.0f;
    for (uint32_t i = 0; i < output->length_of_data; i++)
    {
        z += (expectedoutput->data[i] - output->data[i]);
    }
    z = -1.0f * z;
    return z;
}

float uz_nn_mse(uz_matrix_t *const output, uz_matrix_t const *const expectedoutput)
{
    uz_assert(expectedoutput->length_of_data == output->length_of_data);
    float y = 0.0f;
    for (uint32_t i = 0; i < output->length_of_data; i++)
    {
        y += (expectedoutput->data[i] - output->data[i]) * (expectedoutput->data[i] - output->data[i]);
    }
    y = (0.5f / ((float)output->length_of_data)) * y;

    return y;
}

void uz_nn_backward_pass(uz_nn_t *self, const float *const error, uz_matrix_t *const input)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->is_trainable);
    uz_nn_backward_last_layer(self->layer[self->number_of_layer - 1U], *error);
    for (uint32_t i = self->number_of_layer - 1U; i > 0; i--)
    {
        uz_nn_layer_back(self->layer[i - 1], uz_nn_get_delta_data(self, i + 1), uz_nn_get_weight_matrix(self, i + 1));
    }
    for (uint32_t i = self->number_of_layer - 1U; i > 0; --i)
    {
        uz_nn_layer_calc_gradients(self->layer[i], uz_nn_get_output_from_each_layer(self, i));
    }
    uz_nn_layer_calc_gradients(self->layer[0], input);
}

void uz_nn_backward_pass_mini_batch(uz_nn_t *self, const float *const error, uz_matrix_t const *const input)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->is_trainable);
    uz_nn_backward_last_layer(self->layer[self->number_of_layer - 1U], *error);
    for (uint32_t i = self->number_of_layer - 1U; i > 0; i--)
    {
        uz_nn_layer_back(self->layer[i - 1], uz_nn_get_delta_data(self, i + 1), uz_nn_get_weight_matrix(self, i + 1));
    }
    for (uint32_t i = self->number_of_layer - 1U; i > 0; --i)
    {
        uz_nn_layer_calc_gradients_mini_batch(self->layer[i], uz_nn_get_output_from_each_layer(self, i));
    }
    uz_nn_layer_calc_gradients_mini_batch(self->layer[0], input);
}

void uz_nn_mat_export(uz_nn_t *self)
{
    char *fname = "test/uz/uz_nn/matlab_weights/c_layer1_weights.csv";
    uz_nn_layer_matw_export(self->layer[0], fname);
    char *fname1 = "test/uz/uz_nn/matlab_weights/c_layer2_weights.csv";
    uz_nn_layer_matw_export(self->layer[1], fname1);
    char *fname2 = "test/uz/uz_nn/matlab_weights/c_layer3_weights.csv";
    uz_nn_layer_matw_export(self->layer[2], fname2);
    char *fname3 = "test/uz/uz_nn/matlab_weights/c_layer1_bias.csv";
    uz_nn_layer_matb_export(self->layer[0], fname3);
    char *fname4 = "test/uz/uz_nn/matlab_weights/c_layer2_bias.csv";
    uz_nn_layer_matb_export(self->layer[1], fname4);
    char *fname5 = "test/uz/uz_nn/matlab_weights/c_layer3_bias.csv";
    uz_nn_layer_matb_export(self->layer[2], fname5);
}

void uz_nn_trained_export(uz_nn_t *self)
{
    char *fname = "test/uz/uz_nn/loss_test/trained_layer1_weights.csv";
    uz_nn_layer_matw_export(self->layer[0], fname);
    char *fname1 = "test/uz/uz_nn/loss_test/trained_layer2_weights.csv";
    uz_nn_layer_matw_export(self->layer[1], fname1);
    char *fname3 = "test/uz/uz_nn/loss_test/trained_layer1_bias.csv";
    uz_nn_layer_matb_export(self->layer[0], fname3);
    char *fname4 = "test/uz/uz_nn/loss_test/trained_layer2_bias.csv";
    uz_nn_layer_matb_export(self->layer[1], fname4);
}
void uz_nn_set_gradients_zero(uz_nn_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->is_trainable);
    for (uint32_t i = 0; i < (self->number_of_layer); i++)
    {
        uz_nn_set_gradient_in_layer_zero(self->layer[i]);
    }
}

void uz_nn_set_gradient_matrix(uz_nn_t *self, uz_matrix_t *const gradientmatrix, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->is_trainable);
    uz_nn_set_gradient_in_layer(self->layer[layer - 1], gradientmatrix);
}

void uz_nn_schroeder_export(uz_nn_t *self)
{
    uz_matrix_t *weightshelper = uz_nn_get_weight_matrix(self, 1);
    uz_matrix_t *biasoutput = uz_nn_get_bias_matrix(self, 1);
    float x11 = 0.0f;
    float x12 = 0.0f;
    float b11 = 0.0f;
    float b12 = 0.0f;
    x11 = uz_matrix_get_element_zero_based(weightshelper, 0, 0);
    x12 = uz_matrix_get_element_zero_based(weightshelper, 0, 1);
    b11 = uz_matrix_get_element_zero_based(biasoutput, 0, 0);
    b12 = uz_matrix_get_element_zero_based(biasoutput, 0, 1);
    printf("Neuer Wert für THETA 1.1 ist %.2f \n", (double)x11);
    printf("Neuer Wert für BIAS 1.1 ist %.2f \n", (double)b11);
    // Daten in .csv datei überschreiben
    FILE *file1 = fopen("test/uz/uz_nn/schroeder_weights/layer1_weights.csv", "w");
    if (file1 != NULL)
    {
        fprintf(file1, "%.2ff,%.2ff", (double)x11, (double)x12);
    }

    FILE *file2 = fopen("test/uz/uz_nn/schroeder_weights/layer1_bias.csv", "w");
    if (file2 != NULL)
    {
        fprintf(file2, "%.2ff,%.2ff", (double)b11, (double)b12);
    }
}

uz_matrix_t *uz_nn_get_output_data(uz_nn_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_output_data(self->layer[(self->number_of_layer - 1U)]);
}

uz_matrix_t *uz_nn_get_output_from_each_layer(uz_nn_t const *const self, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_output_data(self->layer[layer - 1]);
}

uz_matrix_t *uz_nn_get_bias_matrix(uz_nn_t const *const self, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_bias_matrix(self->layer[layer - 1]);
}

uz_matrix_t *uz_nn_get_weight_matrix(uz_nn_t const *const self, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_weight_matrix(self->layer[layer - 1]);
}

uz_matrix_t *uz_nn_get_delta_data(uz_nn_t const *const self, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_delta_data(self->layer[layer - 1]);
}

uz_matrix_t *uz_nn_get_sumout_data(uz_nn_t const *const self, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_sumout_data(self->layer[layer - 1]);
}

uz_matrix_t *uz_nn_get_gradient_data(uz_nn_t const *const self, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_gradient_data(self->layer[layer - 1]);
}

uz_matrix_t *uz_nn_get_cachegradient_data(uz_nn_t const *const self, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_cachegradient_data(self->layer[layer - 1]);
}

uint32_t uz_nn_get_number_of_layer(uz_nn_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->number_of_layer;
}

uint32_t uz_nn_get_number_of_inputs(uz_nn_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->number_of_inputs;
}

uint32_t uz_nn_get_number_of_outputs(uz_nn_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->number_of_outputs;
}

void adam_optimizer_step(adam_optimizer_t* optimizer, uz_nn_t* network) {
optimizer->traincounter++;
for (int i = 0; i < network->number_of_layer; i++) {
        adam_layer_step(optimizer, network->layer[i]);
}
}

#endif
