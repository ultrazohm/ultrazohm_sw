#include "uz_rlcc.h"

#include "../uz_global_configuration.h"
#if UZ_RLCC_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_rlcc.h"

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_CurrentControl/uz_space_vector_limitation.h"
#include "../IP_Cores/uz_mlp_three_layer/uz_mlp_three_layer.h"
#include "../uz_nn/uz_nn_activation_functions.h"

#define MAX_NUMBER_OF_OBSERVATIONS 9U

struct uz_rlcc_t
{
    bool is_ready;
    struct uz_rlcc_config_t config;
    struct uz_matrix_t input_matrix;
    uz_matrix_t *nn_input_matrix;
    uz_matrix_t *nn_output_matrix;
    uz_nn_t *software_nn;
    bool clamping;
    uz_3ph_dq_t i_dq_integrated_error_A;
    uz_3ph_dq_t i_dq_error_A;
    uz_3ph_dq_t v_dq_k_minus_one_V;
    uz_3ph_dq_t v_dq_out_before_limitation;
    uz_3ph_dq_t v_dq_out_limited;
    float observation[MAX_NUMBER_OF_OBSERVATIONS];
    uz_mlp_three_layer_ip_t* mlp_ip_core;
    float ipcore_out_array[2];
    uz_matrix_t *ipcore_out_pointer;
    struct uz_matrix_t ipcore_out_matrix_t;
};

static uint32_t instance_counter = 0U;
static uz_rlcc_t instances[UZ_RLCC_MAX_INSTANCES] = {0};

static uz_rlcc_t *uz_rlcc_allocation(void);

static uz_rlcc_t *uz_rlcc_allocation(void)
{
    uz_assert(instance_counter < UZ_RLCC_MAX_INSTANCES);
    uz_rlcc_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_rlcc_t *uz_rlcc_init(struct uz_rlcc_config_t config, struct uz_nn_layer_config neural_network_config[], uint32_t number_of_layer, float* input_data, uint32_t length_of_input_data)
{
    uz_rlcc_t *self = uz_rlcc_allocation();
    uz_assert(config.number_of_observations <= MAX_NUMBER_OF_OBSERVATIONS);
    uz_assert(neural_network_config->number_of_inputs == length_of_input_data);
    self->nn_input_matrix = uz_matrix_init(&self->input_matrix, input_data, length_of_input_data, 1U, neural_network_config->number_of_inputs);
    self->software_nn = uz_nn_init(neural_network_config, number_of_layer);
    self->nn_output_matrix = uz_nn_get_output_data(self->software_nn);
    self->clamping=false;
    self->i_dq_integrated_error_A.d=0.0f;
    self->i_dq_error_A.d=0.0f;
    self->v_dq_k_minus_one_V.d=0.0f;
    self->v_dq_out_before_limitation.d=0.0f;
    self->v_dq_out_limited.d=0.0f;
    self->i_dq_integrated_error_A.q = 0.0f;
    self->i_dq_error_A.q = 0.0f;
    self->v_dq_k_minus_one_V.q = 0.0f;
    self->v_dq_out_before_limitation.q = 0.0f;
    self->v_dq_out_limited.q = 0.0f;
    self->config = config;

    if(self->config.use_ip_core){
        uz_assert_not_zero_uint32(self->config.base_address);
        struct uz_mlp_three_layer_ip_config_t mlp_ip_config = {
            .base_address = self->config.base_address,
            .use_axi_input = true,
            .software_network = self->software_nn};
        self->mlp_ip_core = uz_mlp_three_layer_ip_init(mlp_ip_config);
        self->ipcore_out_pointer = uz_matrix_init(&self->ipcore_out_matrix_t, self->ipcore_out_array, UZ_MATRIX_SIZE(self->ipcore_out_array), 1U, UZ_MATRIX_SIZE(self->ipcore_out_array));
    }

    return (self);
}

void uz_rlcc_reset(uz_rlcc_t *self)
{
    uz_assert(self->is_ready);
    self->i_dq_integrated_error_A.d = 0.0f;
    self->i_dq_error_A.d = 0.0f;
    self->v_dq_k_minus_one_V.d = 0.0f;
    self->v_dq_out_before_limitation.d = 0.0f;
    self->v_dq_out_limited.d = 0.0f;
    self->i_dq_integrated_error_A.q = 0.0f;
    self->i_dq_error_A.q = 0.0f;
    self->v_dq_k_minus_one_V.q = 0.0f;
    self->v_dq_out_before_limitation.q = 0.0f;
    self->v_dq_out_limited.q = 0.0f;
    self->i_dq_integrated_error_A.d = 0.0f;
    self->i_dq_integrated_error_A.q = 0.0f;
    self->clamping = false;
}

uz_3ph_dq_t uz_rlcc_sample(uz_rlcc_t *self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    if (self->clamping == false)
    {
        self->i_dq_integrated_error_A.d = (self->i_dq_integrated_error_A.d + (self->i_dq_error_A.d * self->config.ts_in_second)); // use Forward-Euler with error of previous timestep for integration
        self->i_dq_integrated_error_A.q = (self->i_dq_integrated_error_A.q + (self->i_dq_error_A.q * self->config.ts_in_second));
    }
    else
    {
        self->i_dq_integrated_error_A.d += 0.0f;
        self->i_dq_integrated_error_A.q += 0.0f;
    }
    self->i_dq_error_A.d = (i_reference_Ampere.d - i_actual_Ampere.d) * self->config.current_scaling_1_by_norminal;
    self->i_dq_error_A.q = (i_reference_Ampere.q - i_actual_Ampere.q) * self->config.current_scaling_1_by_norminal;

    switch (self->config.number_of_observations)
    {
    case 7:
        self->observation[0] = self->i_dq_error_A.d;
        self->observation[1] = self->v_dq_k_minus_one_V.d * self->config.voltage_scaling;
        self->observation[2] = self->i_dq_error_A.q;
        self->observation[3] = self->v_dq_k_minus_one_V.q * self->config.voltage_scaling;
        self->observation[4] = i_reference_Ampere.d * self->config.current_scaling_1_by_norminal;
        self->observation[5] = i_reference_Ampere.q * self->config.current_scaling_1_by_norminal;
        self->observation[6] = omega_el_rad_per_sec * self->config.speed_scaling_1_by_norminal_omega_el;
        for (uint32_t i = 0; i < self->config.number_of_observations; i++)
        {
            uz_matrix_set_element_zero_based(self->nn_input_matrix, self->observation[i], 0U, i);
        }
        break;
    case 9:
        self->observation[0] = self->i_dq_error_A.d;
        self->observation[1] = self->i_dq_integrated_error_A.d / self->config.ts_in_second;
        self->observation[2] = self->i_dq_error_A.q;
        self->observation[3] = self->i_dq_integrated_error_A.q / self->config.ts_in_second;
        self->observation[4] = i_reference_Ampere.d * self->config.current_scaling_1_by_norminal;
        self->observation[5] = i_reference_Ampere.q * self->config.current_scaling_1_by_norminal;
        self->observation[6] = omega_el_rad_per_sec * self->config.speed_scaling_1_by_norminal_omega_el; // Global_Data.av.mechanicalRotorSpeed_filtered_hoerner * speed_weight_hoerner;
        self->observation[7] = self->v_dq_k_minus_one_V.d * self->config.voltage_scaling;
        self->observation[8] = self->v_dq_k_minus_one_V.q * self->config.voltage_scaling;
        for (uint32_t i = 0; i < self->config.number_of_observations; i++)
        {
            uz_matrix_set_element_zero_based(self->nn_input_matrix, self->observation[i], 0U, i);
        }
        break;
    default:
        uz_assert(0); // Number of observations not implemented, thus assertion triggered to stop everything
        break;
    }

    if(self->config.use_ip_core){
        uz_mlp_three_layer_ff_blocking(self->mlp_ip_core, self->nn_input_matrix, self->ipcore_out_pointer);
        // IP-Core only calculates with linear, tanh has to be added manually
        self->v_dq_out_before_limitation.d = (uz_nn_activation_function_tanh(self->ipcore_out_array[0])) * self->config.voltage_output_scaling;
        self->v_dq_out_before_limitation.q = (uz_nn_activation_function_tanh(self->ipcore_out_array[1])) * self->config.voltage_output_scaling;
    }else{
        uz_nn_ff(self->software_nn, self->nn_input_matrix);
        self->nn_output_matrix = uz_nn_get_output_data(self->software_nn);
        uz_matrix_multiply_by_scalar(self->nn_output_matrix, self->config.voltage_output_scaling); // scaling layer of nn
        self->v_dq_out_before_limitation.d = uz_matrix_get_element_zero_based(self->nn_output_matrix, 0U, 0U);
        self->v_dq_out_before_limitation.q = uz_matrix_get_element_zero_based(self->nn_output_matrix, 0U, 1U);
    }

    self->v_dq_out_limited = uz_CurrentControl_SpaceVector_Limitation(self->v_dq_out_before_limitation, V_dc_volts, self->config.max_modulation_index, omega_el_rad_per_sec, i_reference_Ampere, &self->clamping);
    self->v_dq_k_minus_one_V = self->v_dq_out_limited;
    return self->v_dq_out_limited;
}

#endif