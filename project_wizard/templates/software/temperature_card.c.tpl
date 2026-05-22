/* Project Wizard generated content for {{ slot }} */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_temperaturecard_config_t config_temperature_card_{{ slot_lower }} = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = {{ ip_clk_frequency_hz }}U,
    .Sample_Freq_Hz = {{ sample_frequency_hz }}U,
    .Config_Global_A = {{ config_global_a }},
    .Config_Mux_A = {{ config_mux_a }},
    .Config_Global_B = {{ config_global_b }},
    .Config_Mux_B = {{ config_mux_b }},
    .Config_Global_C = {{ config_global_c }},
    .Config_Mux_C = {{ config_mux_c }},
    .Configdata_A = {
{{ configdata_a }}
    },
    .Configdata_B = {
{{ configdata_b }}
    },
    .Configdata_C = {
{{ configdata_c }}
    },
};

uz_temperaturecard_t* initialize_temperature_card_{{ slot_lower }}(void)
{
    return uz_temperaturecard_init(config_temperature_card_{{ slot_lower }});
}
