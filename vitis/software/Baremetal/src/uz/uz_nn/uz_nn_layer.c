#include "../uz_global_configuration.h"
#if UZ_NN_LAYER_MAX_INSTANCES > 0U
#include "uz_nn_layer.h"
#include "../uz_HAL.h"
#include <stdbool.h>
#include "uz_nn_activation_functions.h"
struct uz_nn_layer_t
{
    size_t number_of_neurons;
    uz_matrix_t *weights;
    uz_matrix_t *bias;
    uz_matrix_t *output;
    float (*activation_function)(float);
    float (*activation_function_derivative)(float);
    bool is_ready;
};


static size_t instance_counter = 0U;
static uz_nn_layer_t instances[UZ_NN_LAYER_MAX_INSTANCES] = { 0 };

static uz_nn_layer_t* uz_nn_layer_allocation(void);

static uz_nn_layer_t* uz_nn_layer_allocation(void){
    uz_assert(instance_counter < UZ_NN_LAYER_MAX_INSTANCES);
    uz_nn_layer_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_nn_layer_t *uz_nn_layer_init(size_t number_of_neurons, size_t number_of_inputs,
                              float *const weights, size_t length_of_weights,
                              float *const bias, size_t length_of_bias,
                              float *const output, size_t length_of_output,
                              enum activation_function activation)
{
    uz_assert_not_NULL(weights);
    uz_assert_not_NULL(bias);
    uz_assert_not_NULL(output);
    uz_assert(number_of_neurons * number_of_inputs == length_of_weights);
    uz_assert(number_of_neurons == length_of_output);
    uz_assert(number_of_neurons == length_of_bias);
    uz_nn_layer_t *self=uz_nn_layer_allocation();
    self->number_of_neurons = number_of_neurons;
    self->weights = uz_matrix_init(weights, length_of_weights, number_of_inputs, number_of_neurons);
    self->bias = uz_matrix_init(bias, length_of_bias, 1, number_of_neurons);
    self->output = uz_matrix_init(output, length_of_output, 1, number_of_neurons);

    switch (activation)
    {
    case linear:
        self->activation_function = &uz_nn_activation_function_linear;
        self->activation_function_derivative = &uz_nn_activation_function_linear_derivative;
        break;
    case ReLU:
        self->activation_function = &uz_nn_activation_function_relu;
        self->activation_function_derivative = &uz_nn_activation_function_relu_derivative;
        break;
    default:
        break;
    }
    return (self);
}

void uz_nn_layer_ff(uz_nn_layer_t *const self, uz_matrix_t const *const input)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(input);
    uz_assert(self->is_ready);
    uz_assert(uz_matrix_get_number_of_rows(input)==1);
    uz_matrix_set_zero(self->output);
    uz_matrix_multiply(input, self->weights, self->output);
    uz_matrix_add(self->bias, self->output);
    for (size_t i = 0; i < self->number_of_neurons; i++)
    {
        float out = uz_matrix_get_element_zero_based(self->output, 0, i);
        float s = self->activation_function(out);
        uz_matrix_set_element_zero_based(self->output, s, 0, i);
    }
}

uz_matrix_t *uz_nn_layer_get_output_data(uz_nn_layer_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->output);
}

#endif
