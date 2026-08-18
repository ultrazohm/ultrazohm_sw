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
    uz_temperaturecard_t* temperature_card = uz_temperaturecard_init(config_temperature_card_{{ slot_lower }});
    uint32_t readback = uz_TempCard_IF_hw_readReadbackReg(config_temperature_card_{{ slot_lower }}.base_address);
    uint32_t internal_error = uz_TempCard_IF_hw_readErrorReg(config_temperature_card_{{ slot_lower }}.base_address);
    if (readback == IP_CORE_READBACK_VALUE) {
        uz_printf("RPU: {{ slot }} temperature card AXI readback OK: 0x%x, internal error: 0x%x", readback, internal_error);
    } else {
        uz_printf("RPU: {{ slot }} temperature card AXI readback FAILED: expected 0x%x, got 0x%x, internal error: 0x%x", IP_CORE_READBACK_VALUE, readback, internal_error);
    }
    return temperature_card;
}
