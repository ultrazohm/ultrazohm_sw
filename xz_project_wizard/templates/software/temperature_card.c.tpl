/* xz Project Wizard generated content for {{ slot }} */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_temperaturecard_config_t config_temperature_card_{{ slot_lower }} = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = {{ ip_clk_frequency_hz }}U,
    .Sample_Freq_Hz = {{ sample_frequency_hz }}U,
    .Config_Global_A = 0U,
    .Config_Mux_A = 0U,
    .Config_Global_B = 0U,
    .Config_Mux_B = 0U,
    .Config_Global_C = 0U,
    .Config_Mux_C = 0U,
    .Configdata_A = {
{{ configdata_a }}
    },
    .Configdata_B = {0U},
    .Configdata_C = {0U},
};

uz_temperaturecard_t* initialize_temperature_card_{{ slot_lower }}(void)
{
    return uz_temperaturecard_init(config_temperature_card_{{ slot_lower }});
}
