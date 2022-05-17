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
static int32_t convert_voltage_to_int(float input, float conversion_factor);

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
    for (uint32_t i = 0U; i < 8; i++)
    {
        uz_assert(config.conversion_factor[i] > 0.0f);                    // Make sure conversion factor is set for all channels
        config.conversion_factor[i] = 1.0f / config.conversion_factor[i]; // Inverse conversion factor at initialization to prevent later division
    }
    uz_dac_interface_t *self = uz_dac_interface_allocation();
    self->config = config;

    return (self);
}

void uz_dac_interface_set_ouput_values(uz_dac_interface_t *self, uz_array_float_t *output_values)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(output_values);

    uz_dac_interface_hw_write_dac1(self->config.base_address, convert_voltage_to_int(output_values->data[0], self->config.conversion_factor[0]));
    uz_dac_interface_hw_write_dac2(self->config.base_address, convert_voltage_to_int(output_values->data[1], self->config.conversion_factor[1]));
    uz_dac_interface_hw_write_dac3(self->config.base_address, convert_voltage_to_int(output_values->data[2], self->config.conversion_factor[2]));
    uz_dac_interface_hw_write_dac4(self->config.base_address, convert_voltage_to_int(output_values->data[3], self->config.conversion_factor[3]));
    uz_dac_interface_hw_write_dac5(self->config.base_address, convert_voltage_to_int(output_values->data[4], self->config.conversion_factor[4]));
    uz_dac_interface_hw_write_dac6(self->config.base_address, convert_voltage_to_int(output_values->data[5], self->config.conversion_factor[5]));
    uz_dac_interface_hw_write_dac7(self->config.base_address, convert_voltage_to_int(output_values->data[6], self->config.conversion_factor[6]));
    uz_dac_interface_hw_write_dac8(self->config.base_address, convert_voltage_to_int(output_values->data[7], self->config.conversion_factor[7]));
    uz_dac_interface_hw_write_trigger(self->config.base_address, true);
    uz_dac_interface_hw_write_trigger(self->config.base_address, false);
}

void uz_dac_interface_set_ouput_values_unsafe(uz_dac_interface_t *self, uz_array_float_t *output_values)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(output_values);

    int32_t out[8] = {0};
    uz_array_int32_t out_array={
        .length=8U,
        .data=&out[0]
    };
    for (uint32_t i = 0; i < 8; i++)
    {
        out[i] = convert_voltage_to_int(output_values->data[i], self->config.conversion_factor[i]);
    }
    uz_dac_interface_hw_write_all(self->config.base_address, &out_array);
    uz_dac_interface_hw_write_trigger(self->config.base_address, true);
    uz_dac_interface_hw_write_trigger(self->config.base_address, false);
}

static int32_t convert_voltage_to_int(float input, float conversion_factor)
{
    int32_t voltage_set_point = (int32_t)(((input * 0.4f * conversion_factor) * 32768) + 32768); // 1/2.5f=0.4f to prevent division at runtime
    return voltage_set_point;
}

#endif