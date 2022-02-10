
#include "../../uz/uz_global_configuration.h"
#if UZ_MLP_THREE_LAYER_IP_MAX_INSTANCES > 0U
#include "uz_mlp_three_layer.h"
#include "uz_mlp_three_layer_hw.h"
#include <stdbool.h>
#include "../../uz/uz_HAL.h"

struct uz_mlp_three_layer_ip_t
{
    bool is_ready;
    uint32_t base_address;
};

static size_t instance_counter = 0U;
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

uz_mlp_three_layer_ip_t *UZ_MLP_THREE_LAYER_IP_init(struct uz_mlp_three_layer_ip_config_t config)
{
    uz_mlp_three_layer_ip_t *self = UZ_MLP_THREE_LAYER_IP_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    self->base_address = config.base_address;

    return (self);
}

void uz_mlp_three_layer_write_bias(uz_mlp_three_layer_ip_t *self, uint32_t parallel_pcu, uz_matrix_t *bias, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Outer loop over number_of_parallel_pcu
    // Middle loop over data with columns:number_of_columns/number_of_parallel_pcu
    // Inner loop over data with rows:number_of_rows
    size_t columns = uz_matrix_get_number_of_columns(bias);
    size_t columns_per_pcu = columns / parallel_pcu;
    uz_mlp_three_layer_hw_write_layerNr(self->base_address, layer);
    for (size_t pcu = 0U; pcu < parallel_pcu; pcu++)
    {
        for (size_t i = 0U; i < columns_per_pcu; i++)
        {
            uz_mlp_three_layer_hw_write_enable_bias(self->base_address, 0U); // Write zero to disable write enable for all BRAM
            float bias_value = uz_matrix_get_element_zero_based(bias, 0U, i + (pcu * columns_per_pcu));
            uz_mlp_three_layer_hw_write_bias_data(self->base_address, bias_value);
            uz_mlp_three_layer_hw_write_bias_address(self->base_address, i);
            uz_mlp_three_layer_hw_write_enable_bias(self->base_address, (pcu + 1U)); // PCU is one based
        }
    }
}

void uz_mlp_three_layer_write_weights(uz_mlp_three_layer_ip_t *self, uint32_t parallel_pcu, uz_matrix_t *weights, uint32_t layer)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    size_t columns = uz_matrix_get_number_of_columns(weights);
    size_t rows = uz_matrix_get_number_of_rows(weights);
    size_t columns_per_pcu = columns / parallel_pcu;
    uz_mlp_three_layer_hw_write_layerNr(self->base_address, layer);
    size_t address = 0U;
    for (size_t pcu = 0U; pcu < parallel_pcu; pcu++)
    {
        for (size_t k = 0U; k < columns_per_pcu; k++)
        {
            for (size_t i = 0U; i < rows; i++)
            {
                uz_mlp_three_layer_hw_write_enable_weights(self->base_address, 0U); // Write zero to disable write enable for all BRAM
                size_t row = i;
                size_t column = k + (pcu * columns_per_pcu);
                float weight_value = uz_matrix_get_element_zero_based(weights, row, column);
                uz_mlp_three_layer_hw_write_weight_data(self->base_address, weight_value);
                address++;
                uz_mlp_three_layer_hw_write_weight_address(self->base_address, address);
                uz_mlp_three_layer_hw_write_enable_weights(self->base_address, (pcu + 1U)); // PCU is one based
            }
        }
    }
}

#endif