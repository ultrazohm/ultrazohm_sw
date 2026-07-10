/* Project Wizard generated content for {{ slot }} */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "../globalData.h"
#include "xparameters.h"
#include <stdbool.h>

static struct uz_inverter_adapter_config_t config_inverter_adapter_{{ slot_lower }} = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = {{ ip_clk_frequency_Hz }},
    .linear_interpolation_params = {
        .a = {{ linear_interpolation_a }},
        .b = {{ linear_interpolation_b }}}};

static struct uz_inverter_adapter_outputs_t inverter_adapter_{{ slot_lower }}_outputs = {0};

uz_inverter_adapter_t* initialize_inverter_adapter_{{ slot_lower }}(void)
{
    return uz_inverter_adapter_init(config_inverter_adapter_{{ slot_lower }}, inverter_adapter_{{ slot_lower }}_outputs);
}

void update_inverter_adapter_{{ slot_lower }}_outputs(struct _DS_Data_* data)
{
    data->av.inverter_adapter_{{ slot_lower }} = uz_inverter_adapter_get_outputs(data->objects.inverter_adapter_{{ slot_lower }});
}
