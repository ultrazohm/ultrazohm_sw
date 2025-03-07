
#include "../../uz/uz_global_configuration.h"
#if UZ_MLP_THREE_LAYER_IP_MAX_INSTANCES > 0U
#include "uz_mlp_three_layer.h"
#include "uz_mlp_three_layer_hw.h"
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_array/uz_array.h"

// Number of parallel pcu in each layer is hard-coded into the IP-Core hardware
#define NUMBER_OF_PARALLEL_PCU_LAYER_1 4U
#define NUMBER_OF_PARALLEL_PCU_LAYER_2 8U
#define NUMBER_OF_PARALLEL_PCU_LAYER_3 8U
#define NUMBER_OF_PARALLEL_PCU_LAYER_4 2U


struct uz_mlp_three_layer_ip_t
{
    bool is_ready;
    struct uz_mlp_three_layer_ip_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_mlp_three_layer_ip_t instances[UZ_MLP_THREE_LAYER_IP_MAX_INSTANCES] = {0};

static uz_mlp_three_layer_ip_t *UZ_MLP_THREE_LAYER_IP_allocation(void);

static uz_mlp_three_layer_ip_t *UZ_MLP_THREE_LAYER_IP_allocation(void)
{
    uz_assert(instance_counter < UZ_MLP_THREE_LAYER_IP_MAX_INSTANCES);
    uz_mlp_three_layer_ip_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_mlp_three_layer_ip_t *uz_mlp_three_layer_ip_init(struct uz_mlp_three_layer_ip_config_t config)
{
    uz_mlp_three_layer_ip_t *self = UZ_MLP_THREE_LAYER_IP_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_NULL(config.software_network);
    self->config = config;
    uint32_t number_of_inputs = (uint32_t)uz_nn_get_number_of_inputs(self->config.software_network);
    uint32_t number_of_outputs = (uint32_t)uz_nn_get_number_of_outputs(self->config.software_network);
    uz_mlp_three_layer_hw_write_number_of_inputs(self->config.base_address, number_of_inputs);
    uz_mlp_three_layer_hw_write_number_of_outputs(self->config.base_address, number_of_outputs);
    uz_mlp_three_layer_set_use_axi_input(self, self->config.use_axi_input);
    uz_mlp_three_layer_set_parameters(self);
    return (self);
}

void uz_mlp_three_layer_set_bias(uz_mlp_three_layer_ip_t *self, uint32_t parallel_pcu, uz_matrix_t *bias, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Outer loop over number_of_parallel_pcu
    // Middle loop over data with columns:number_of_columns/number_of_parallel_pcu
    // Inner loop over data with rows:number_of_rows
    uint32_t columns = uz_matrix_get_number_of_columns(bias);
    uint32_t columns_per_pcu = columns / parallel_pcu;
    uz_mlp_three_layer_hw_write_layerNr(self->config.base_address, layer);
    for (uint32_t pcu = 0U; pcu < parallel_pcu; pcu++)
    {
        for (uint32_t i = 0U; i < columns_per_pcu; i++)
        {
            uz_mlp_three_layer_hw_write_enable_bias(self->config.base_address, 0U); // Write zero to disable write enable for all BRAM
            uint32_t abs_value = i + (pcu * columns_per_pcu);
            float bias_value = uz_matrix_get_element_zero_based(bias, 0U, abs_value);
            uz_mlp_three_layer_hw_write_bias_data(self->config.base_address, bias_value);
            uz_mlp_three_layer_hw_write_bias_address(self->config.base_address, (uint32_t)i);
            uint32_t bias_enable_address = (uint32_t)pcu + 1U;
            uz_mlp_three_layer_hw_write_enable_bias(self->config.base_address, bias_enable_address); // PCU is one based
            uz_mlp_three_layer_hw_write_enable_bias(self->config.base_address, 0U);                  // Write zero to disable write enable for all BRAM
        }
    }
}

void uz_mlp_three_layer_set_weights(uz_mlp_three_layer_ip_t *self, uint32_t parallel_pcu, uz_matrix_t *weights, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uint32_t columns = uz_matrix_get_number_of_columns(weights);
    uint32_t rows = uz_matrix_get_number_of_rows(weights);
    uint32_t columns_per_pcu = columns / parallel_pcu;
    uz_mlp_three_layer_hw_write_layerNr(self->config.base_address, layer);
    for (uint32_t pcu = 0U; pcu < parallel_pcu; pcu++)
    {
        uint32_t address = 0U;
        for (uint32_t k = 0U; k < columns_per_pcu; k++)
        {
            for (uint32_t i = 0U; i < rows; i++)
            {
                uz_mlp_three_layer_hw_write_enable_weights(self->config.base_address, 0U); // Write zero to disable write enable for all BRAM
                uint32_t row = i;
                uint32_t column = k + (pcu * columns_per_pcu);
                float weight_value = uz_matrix_get_element_zero_based(weights, row, column);
                uz_mlp_three_layer_hw_write_weight_data(self->config.base_address, weight_value);
                address++;
                uz_mlp_three_layer_hw_write_weight_address(self->config.base_address, address);
                uz_mlp_three_layer_hw_write_enable_weights(self->config.base_address, ((uint32_t)pcu + 1U)); // PCU is one based
                uz_mlp_three_layer_hw_write_enable_bias(self->config.base_address, 0U);                      // Write zero to disable write enable for all BRAM
            }
        }
    }
}

void uz_mlp_three_layer_set_parameters(uz_mlp_three_layer_ip_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_matrix_t *bias_1 = uz_nn_get_bias_matrix(self->config.software_network, 1U);
    uz_matrix_t *weight_1 = uz_nn_get_weight_matrix(self->config.software_network, 1U);

    uz_matrix_t *bias_2 = uz_nn_get_bias_matrix(self->config.software_network, 2U);
    uz_matrix_t *weight_2 = uz_nn_get_weight_matrix(self->config.software_network, 2U);

    uz_matrix_t *bias_3 = uz_nn_get_bias_matrix(self->config.software_network, 3U);
    uz_matrix_t *weight_3 = uz_nn_get_weight_matrix(self->config.software_network, 3U);

    uz_matrix_t *bias_4 = uz_nn_get_bias_matrix(self->config.software_network, 4U);
    uz_matrix_t *weight_4 = uz_nn_get_weight_matrix(self->config.software_network, 4U);

    uz_mlp_three_layer_set_bias(self, NUMBER_OF_PARALLEL_PCU_LAYER_1, bias_1, 1U);
    uz_mlp_three_layer_set_bias(self, NUMBER_OF_PARALLEL_PCU_LAYER_2, bias_2, 2U);
    uz_mlp_three_layer_set_bias(self, NUMBER_OF_PARALLEL_PCU_LAYER_3, bias_3, 3U);
    uz_mlp_three_layer_set_bias(self, NUMBER_OF_PARALLEL_PCU_LAYER_4, bias_4, 4U);

    uz_mlp_three_layer_set_weights(self, NUMBER_OF_PARALLEL_PCU_LAYER_1, weight_1, 1U);
    uz_mlp_three_layer_set_weights(self, NUMBER_OF_PARALLEL_PCU_LAYER_2, weight_2, 2U);
    uz_mlp_three_layer_set_weights(self, NUMBER_OF_PARALLEL_PCU_LAYER_3, weight_3, 3U);
    uz_mlp_three_layer_set_weights(self, NUMBER_OF_PARALLEL_PCU_LAYER_4, weight_4, 4U);
}

void uz_mlp_three_layer_ff_blocking(uz_mlp_three_layer_ip_t *self, uz_matrix_t *input_data, uz_matrix_t *output_data)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(input_data);
    uz_assert_not_NULL(output_data);
    uz_assert(self->is_ready);
    uz_mlp_three_layer_ff_trigger(self, input_data);
    uz_mlp_three_layer_ff_get_result_blocking(self, output_data);
}

void uz_mlp_three_layer_ff_trigger(uz_mlp_three_layer_ip_t *self, uz_matrix_t *input_data)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(input_data);
    uz_assert(self->is_ready);
    uz_mlp_three_layer_hw_write_input(self->config.base_address, input_data);
    uz_mlp_three_layer_hw_write_enable_nn(self->config.base_address, true);
    uz_mlp_three_layer_hw_write_enable_nn(self->config.base_address, false);
}

void uz_mlp_three_layer_ff_get_result_blocking(uz_mlp_three_layer_ip_t *self, uz_matrix_t *output_data)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert_not_NULL(output_data);
    while (!(uz_mlp_three_layer_hw_read_valid_output(self->config.base_address)))
    {
        // do nothing while output is not valid
    }
    uz_mlp_three_layer_hw_read_output(self->config.base_address, output_data);
}

void uz_mlp_three_layer_ff_blocking_unsafe(uz_mlp_three_layer_ip_t *self, uz_matrix_t *input_data, uz_matrix_t *output_data)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(input_data);
    uz_assert_not_NULL(output_data);
    uz_assert(self->is_ready);
    uz_mlp_three_layer_ff_trigger_unsafe(self, input_data);
    uz_mlp_three_layer_ff_get_result_blocking_unsafe(self, output_data);
}

void uz_mlp_three_layer_ff_trigger_unsafe(uz_mlp_three_layer_ip_t *self, uz_matrix_t *input_data)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(input_data);
    uz_assert(self->is_ready);
    uz_mlp_three_layer_hw_write_input_unsafe(self->config.base_address, input_data);
    uz_mlp_three_layer_hw_write_enable_nn(self->config.base_address, true);
    uz_mlp_three_layer_hw_write_enable_nn(self->config.base_address, false);
}

void uz_mlp_three_layer_ff_get_result_blocking_unsafe(uz_mlp_three_layer_ip_t *self, uz_matrix_t *output_data)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert_not_NULL(output_data);
    while (!(uz_mlp_three_layer_hw_read_valid_output(self->config.base_address)))
    {
        // do nothing while output is not valid
    }
    uz_mlp_three_layer_hw_read_output_unsafe(self->config.base_address, output_data);
}


void uz_mlp_three_layer_set_use_axi_input(uz_mlp_three_layer_ip_t *self, bool use_axi_input)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.use_axi_input = use_axi_input;
    uz_mlp_three_layer_hw_write_use_axi_input(self->config.base_address, self->config.use_axi_input);
}

void uz_mlp_three_layer_disable_pl_trigger(uz_mlp_three_layer_ip_t *self, bool disable_pl_trigger){
    uz_assert_not_NULL(self);
    uz_mlp_three_layer_hw_disable_pl_trigger(self->config.base_address,disable_pl_trigger);
}


#endif
