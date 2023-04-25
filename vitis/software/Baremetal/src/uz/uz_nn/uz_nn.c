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

uz_nn_t *uz_nn_init(struct uz_nn_layer_config config[UZ_NN_MAX_LAYER], uint32_t number_of_layer)
{
    uz_assert(number_of_layer < UZ_NN_MAX_LAYER);
    uz_assert(number_of_layer > 1U);
    uz_nn_t *self = uz_nn_allocation();
    self->number_of_layer = number_of_layer;
    self->number_of_inputs = config[0U].number_of_inputs;
    self->number_of_outputs = config[number_of_layer - 1U].length_of_output;
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

// void uz_nn_calc_gradients_matrix(uz_nn_t *self,uz_matrix_t *const reference, uz_matrix_t *const input)
// {
//     uz_assert_not_NULL(self);
//     uz_assert(self->is_ready);
//     // lokale Gradienten zurückrechnen vom letzten layer
//     uz_nn_layer_back_last_layer_matrix(self->layer[self->number_of_layer - 1U], reference);
//     for (uint32_t i = self->number_of_layer - 1U; i > 0; i--)
//     {
//         uz_nn_layer_back(self->layer[i-1],uz_nn_get_delta_data(self,i+1),uz_nn_get_weight_matrix(self,i+1));
//     }
//     //Gradient output + alle hidden layer
//     for (uint32_t i = self->number_of_layer - 1U; i > 1; i--)
//     {
//             uz_nn_layer_calc_gradients(self->layer[i],uz_nn_get_output_from_each_layer(self,i));
//     }
//     //Gradient erster layer
//     uz_nn_layer_calc_gradients(self->layer[0],input);
// }

void uz_nn_gradient_descent(uz_nn_t *self, float const learnrate)
{
uz_assert_not_NULL(self);
uz_assert(self->is_ready);
// Loop through layers

    for (uint32_t i = 0; i < (self->number_of_layer); i++)
    {
        uz_nn_update_layer_param(self->layer[i], learnrate);
    }
}


float uz_nn_mse(uz_matrix_t *const output, uz_matrix_t *const expectedoutput)
{
    uz_assert(expectedoutput->length_of_data == output->length_of_data);
    float y = 0.0f;
    // summiere alle Fehler auf
    for (uint32_t i = 0; i < output->length_of_data; i++)
    {
        y+=(output->data[i] - expectedoutput->data[i]) * (output->data[i] - expectedoutput->data[i]);
    }
    // Wer als float ausgeben zum Debuggen 1/n * Summe = MSE
    y = (1.0f/((float)output->length_of_data)) * y;
    
    return y;
}

void uz_nn_backward_pass(uz_nn_t *self,float *const error, uz_matrix_t *const input)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // lokale Gradienten zurückrechnen vom letzten layer
    uz_nn_backward_last_layer(self->layer[self->number_of_layer - 1U], error);
    for (uint32_t i = self->number_of_layer - 1U; i > 0; i--)
    {
        uz_nn_layer_back(self->layer[i-1],uz_nn_get_delta_data(self,i+1),uz_nn_get_weight_matrix(self,i+1));
    }
         //Berechne alle Gradienten

    //  uz_nn_layer_calc_gradients(self->layer[2],uz_nn_get_output_from_each_layer(self,2));

    //  uz_nn_layer_calc_gradients(self->layer[1],uz_nn_get_output_from_each_layer(self,1));

    //  uz_nn_layer_calc_gradients(self->layer[0],input);


    //Gradient output + alle hidden layer
    // for (uint32_t i = self->number_of_layer - 1U; i> 0; --i)
    // {
    //         uz_nn_layer_calc_gradients(self->layer[i],uz_nn_get_output_from_each_layer(self,i));
    // }
    uz_nn_layer_calc_gradients(self->layer[2],uz_nn_get_output_from_each_layer(self,2));
    uz_nn_layer_calc_gradients(self->layer[1],uz_nn_get_output_from_each_layer(self,1));
    //Gradient erster layer
    uz_nn_layer_calc_gradients(self->layer[0],input);
}


void uz_nn_calc_gradients(uz_nn_t *self,float *const reference, uz_matrix_t *const input)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // lokale Gradienten zurückrechnen vom letzten layer
    uz_nn_layer_back_last_layer(self->layer[self->number_of_layer - 1U], reference);
    for (uint32_t i = self->number_of_layer - 1U; i > 0; i--)
    {
        uz_nn_layer_back(self->layer[i-1],uz_nn_get_delta_data(self,i+1),uz_nn_get_weight_matrix(self,i+1));
    }
         //Berechne alle Gradienten

    //  uz_nn_layer_calc_gradients(self->layer[2],uz_nn_get_output_from_each_layer(self,2));

    //  uz_nn_layer_calc_gradients(self->layer[1],uz_nn_get_output_from_each_layer(self,1));

    //  uz_nn_layer_calc_gradients(self->layer[0],input);


    //Gradient output + alle hidden layer
    for (uint32_t i = self->number_of_layer - 1U; i> 0; --i)
    {
            uz_nn_layer_calc_gradients(self->layer[i],uz_nn_get_output_from_each_layer(self,i));
    }
    //Gradient erster layer
    uz_nn_layer_calc_gradients(self->layer[0],input);
}

void uz_nn_update(uz_nn_t *self,float const THETA, float const BIAS,float const Lernrate)
{
    const float *gradient1 = &THETA;
    const float *gradient2 = &BIAS;
    const float *lernratelayer0 = &Lernrate;
    uz_nn_layer_update(self->layer[0],gradient1,gradient2,lernratelayer0);
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

void uz_nn_schroeder_export(uz_nn_t *self)
{
    // Zeige Gewichte nach dem Trainingsschritt an
    uz_matrix_t* weightshelper = uz_nn_get_weight_matrix(self,1);
    uz_matrix_t* biasoutput = uz_nn_get_bias_matrix(self,1);
    float x11 = 0.0f;
    float x12 = 0.0f;
    float b11 = 0.0f;
    float b12 = 0.0f;
    x11 = uz_matrix_get_element_zero_based(weightshelper,0,0);
    x12 = uz_matrix_get_element_zero_based(weightshelper,0,1);
    b11 = uz_matrix_get_element_zero_based(biasoutput,0,0);
    b12 = uz_matrix_get_element_zero_based(biasoutput,0,1);
    printf("Neuer Wert für THETA 1.1 ist %.2f \n", x11);
    printf("Neuer Wert für BIAS 1.1 ist %.2f \n", b11);
// Daten in .csv datei überschreiben
FILE* file1 = fopen("test/uz/uz_nn/schroeder_weights/layer1_weights.csv", "w");
if (file1 != NULL)
{
    fprintf(file1, "%.2ff,%.2ff", x11, x12);
}

FILE* file2 = fopen("test/uz/uz_nn/schroeder_weights/layer1_bias.csv", "w");
if (file2 != NULL)
{
    fprintf(file2, "%.2ff,%.2ff", b11, b12);
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

uz_matrix_t *uz_nn_get_derivate_data(uz_nn_t const *const self, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_nn_layer_get_derivate_data(self->layer[layer - 1]);
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
