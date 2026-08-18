/* Project Wizard generated content for {{ slot }} */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "../uz/uz_wavegen/uz_wavegen.h"
#include "../globalData.h"
#include "xparameters.h"
#include <stdint.h>

static struct uz_dac_interface_config_t config_dac8831_{{ slot_lower }} = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = {{ ip_clk_frequency_Hz }},
    .gain = {
        {{ gain_ch0 }},
        {{ gain_ch1 }},
        {{ gain_ch2 }},
        {{ gain_ch3 }},
        {{ gain_ch4 }},
        {{ gain_ch5 }},
        {{ gain_ch6 }},
        {{ gain_ch7 }}}};

static float dac8831_{{ slot_lower }}_outputs[UZ_DAC_INTERFACE_OUTPUT_CHANNELS] = {
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f};

static uz_array_float_t dac8831_{{ slot_lower }}_output_array = {
    .data = &dac8831_{{ slot_lower }}_outputs[0],
    .length = UZ_DAC_INTERFACE_OUTPUT_CHANNELS};

uz_dac_interface_t* initialize_dac8831_{{ slot_lower }}(void)
{
    return uz_dac_interface_init(config_dac8831_{{ slot_lower }});
}

void update_dac8831_{{ slot_lower }}_outputs(struct _DS_Data_* data)
{
{% for assignment in output_assignments %}
{{ assignment }}
{% endfor %}
    uz_dac_interface_set_ouput_values(data->objects.dac8831_{{ slot_lower }}, &dac8831_{{ slot_lower }}_output_array);
}
