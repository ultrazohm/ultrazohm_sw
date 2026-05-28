/* Project Wizard generated content for {{ slot }} */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"
#include <stdbool.h>
#include <stdint.h>

static struct uz_adcLtc2311_config_t config_adc_ltc2311_{{ slot_lower }} = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = {{ ip_clk_frequency_Hz }},
    .channel_config = {
        .conversion_factor = {{ conversion_factor }},
        .conversion_factor_definition = {
            .is_signed = {{ conversion_factor_is_signed }},
            .integer_bits = {{ conversion_factor_integer_bits }},
            .fractional_bits = {{ conversion_factor_fractional_bits }}},
        .offset = {{ offset }},
    },
    .spi_master_config = {
        .samples = {{ samples }},
        .sample_time = {{ sample_time }},
        .trigger_mode = {{ trigger_mode }}},
    .cpol = {{ cpol }},
    .cpha = {{ cpha }},
    .napping_spi_masters = {{ napping_spi_masters }},
    .sleeping_spi_masters = {{ sleeping_spi_masters }},
    .master_select = {{ master_select }},
    .channel_select = {{ channel_select }},
    .pre_delay = {{ pre_delay }},
    .post_delay = {{ post_delay }},
    .clk_div = {{ clk_div }},
    .max_attempts = {{ max_attempts }}};

uz_adcLtc2311_t* initialize_adc_ltc2311_{{ slot_lower }}(void)
{
    return uz_adcLtc2311_init(config_adc_ltc2311_{{ slot_lower }});
}
