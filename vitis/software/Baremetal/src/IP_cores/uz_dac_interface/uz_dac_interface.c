#include "uz_dac_interface.h"

#include "../../uz/uz_global_configuration.h"
#if UZ_DAC_INTERFACE_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_dac_interface.h"
#include "uz_dac_interface_hw.h"

struct uz_dac_interface_t
{
    bool is_ready;
    struct uz_dac_interface_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_dac_interface_t instances[UZ_DAC_INTERFACE_MAX_INSTANCES] = {0};

static uz_dac_interface_t *uz_dac_interface_allocation(void);

static uz_dac_interface_t *uz_dac_interface_allocation(void)
{
    uz_assert(instance_counter < UZ_DAC_INTERFACE_MAX_INSTANCES);
    uz_dac_interface_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_dac_interface_t *uz_dac_interface_init(struct uz_dac_interface_config_t config)
{
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    uz_dac_interface_t *self = uz_dac_interface_allocation();
    self->config = config;

    return (self);
}

void uz_dac_interface_set_ouput_values(uz_dac_interface_t *self, uz_array_int32_t *output_values)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(output_values);

    uz_dac_interface_hw_write_dac1(self->config.base_address, output_values->data[0]);
    uz_dac_interface_hw_write_dac2(self->config.base_address, output_values->data[1]);
    uz_dac_interface_hw_write_dac3(self->config.base_address, output_values->data[2]);
    uz_dac_interface_hw_write_dac4(self->config.base_address, output_values->data[3]);
    uz_dac_interface_hw_write_dac5(self->config.base_address, output_values->data[4]);
    uz_dac_interface_hw_write_dac6(self->config.base_address, output_values->data[5]);
    uz_dac_interface_hw_write_dac7(self->config.base_address, output_values->data[6]);
    uz_dac_interface_hw_write_dac8(self->config.base_address, output_values->data[7]);
    uz_dac_interface_hw_write_trigger(self->config.base_address, true);
    uz_dac_interface_hw_write_trigger(self->config.base_address, false);
}

void uz_dac_interface_set_ouput_values_unsafe(uz_dac_interface_t *self, uz_array_int32_t *output_values)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(output_values);

    uz_mlp_three_layer_hw_write_input_unsafe(self->config.base_address, output_values);
    uz_dac_interface_hw_write_trigger(self->config.base_address, true);
    uz_dac_interface_hw_write_trigger(self->config.base_address, false);
}

#endif