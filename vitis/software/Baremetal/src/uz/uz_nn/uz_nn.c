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
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_nn.h"
#include "../uz_matrix/uz_matrix.h"

struct uz_nn_t
{
    bool is_ready;
    uint32_t number_of_layer;
    uint32_t number_of_inputs;
    uint32_t number_of_outputs;
    uint32_t number_of_sumouts;
    uint32_t number_of_derivate_gradients;
    uint32_t number_of_gradientslocal;
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

uz_nn_t *uz_nn_init(struct uz_nn_layer_config config[UZ_NN_MAX_LAYER], uint32_t number_of_layer)
{
    uz_assert(number_of_layer < UZ_NN_MAX_LAYER);
    uz_assert(number_of_layer > 1U);
    uz_nn_t *self = uz_nn_allocation();
    self->number_of_layer = number_of_layer;
    self->number_of_inputs = config[0U].number_of_inputs;
    self->number_of_outputs = config[number_of_layer - 1U].length_of_output;
    self->number_of_sumouts = config[number_of_layer - 1U].length_of_sumout;
    self->number_of_derivate_gradients = config[number_of_layer - 1U].length_of_derivate_gradients;
    self->number_of_gradientslocal = config[number_of_layer - 1U].length_of_gradientslocal;
    for (uint32_t i = 0U; i < number_of_layer; i++)
    {
        self->layer[i] = uz_nn_layer_init(config[i]);
    }
    return (self);
}

void uz_nn_ff(uz_nn_t *self, uz_matrix_t const *const input)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_nn_layer_ff(self->layer[0], input);
    for (uint32_t i = 0; i < (self->number_of_layer - 1U); i++)
    {
        uz_nn_layer_ff(self->layer[i + 1U], uz_nn_layer_get_output_data(self->layer[i]));
    }
}


void uz_nn_backprop(uz_nn_t *self,float const reference_output)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // aus derivate matrix und nn zurückpropagieren und die lokalen gradienten Berechnen
    const float *reference = &reference_output;
    uz_nn_layer_back_last_layer(self->layer[2], reference);
    uz_nn_layer_back(self->layer[1],uz_nn_get_gradient_data(self,2),uz_nn_get_weight_matrix(self,2));
    //uz_nn_layer_back(self->layer[0],uz_nn_get_gradient_data(self,1),uz_nn_get_weight_matrix(self,1));
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

uz_matrix_t *uz_nn_get_derivate_data(uz_nn_t const *const self, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_derivate_data(self->layer[layer - 1]);
}
uz_matrix_t *uz_nn_get_gradient_data(uz_nn_t const *const self, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_gradient_data(self->layer[layer - 1]);
}

uz_matrix_t *uz_nn_get_sumout_data(uz_nn_t const *const self, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_sumout_data(self->layer[layer - 1]);
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

#endif
