/* Project Wizard generated content for {{ slot }} channel {{ channel }} */
#include "xparameters.h"

static struct uz_endat_interface_config_t endat_encoder_{{ slot_lower }}_{{ channel }}_config = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = {{ ip_clk_frequency_Hz }},
    .machine_polepairs = {{ machine_polepairs }},
    .endat_clk_frequency_Hz = {{ endat_clk_frequency_Hz }},
    .position_mech_offset_si_single_turn = {{ position_mech_offset_si_single_turn }},
    .endat_encoder_bit_width_single_turn = {{ endat_encoder_bit_width_single_turn }},
    .endat_encoder_bit_width_multi_turn = {{ endat_encoder_bit_width_multi_turn }},
    .kp_pll = {{ kp_pll }},
    .ki_pll = {{ ki_pll }},
    .sampling_interval_seconds = {{ sampling_interval_seconds }},
    .delay_sampling_in_clk_ticks = {{ delay_sampling_in_clk_ticks }}
};

uz_endat_interface_t* initialize_endat_encoder_{{ slot_lower }}_{{ channel }}(void)
{
    return uz_endat_interface_init(endat_encoder_{{ slot_lower }}_{{ channel }}_config);
}
