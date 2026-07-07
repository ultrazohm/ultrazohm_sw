/* Project Wizard generated content for {{ slot }} */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"
#include <stdbool.h>
#include <stdint.h>

static struct uz_adcMax11331_config_t config_adc_max11331_{{ slot_lower }} = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = {{ ip_clk_frequency_Hz }},
    .master_select = {{ master_select }},
    .trigger_mode = {{ trigger_mode }},
    .adc_delay_offset = {{ adc_delay_offset }},
    .clk_div = {{ clk_div }},
    .cpha = {{ cpha }},
    .cpol = {{ cpol }},
    .error_code = {{ error_code }},
    .channel_config = {
        .conversion_factor = {{ conversion_factor }},
        .conversion_factor_definition = {
            .is_signed = {{ conversion_factor_is_signed }},
            .integer_bits = {{ conversion_factor_integer_bits }},
            .fractional_bits = {{ conversion_factor_fractional_bits }}},
        .offset = {{ offset }},
    }};

uz_adcMax11331_t* initialize_adc_max11331_{{ slot_lower }}(void)
{
    return uz_adcMax11331_init(config_adc_max11331_{{ slot_lower }});
}

float convert_adc_max11331_{{ slot_lower }}_raw_to_physical_value(int16_t raw_value)
{
    return ((float)((int16_t)(raw_value << 4))) / (float)(1 << 15) * config_adc_max11331_{{ slot_lower }}.channel_config.conversion_factor;
}
