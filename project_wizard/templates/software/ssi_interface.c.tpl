/* Project Wizard generated content for {{ slot }} channel {{ channel }} */
#include "xparameters.h"

static struct uz_ssi_interface_config_t ssi_encoder_{{ slot_lower }}_{{ channel }}_config = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = {{ ip_clk_frequency_Hz }},
    .machine_polepairs = {{ machine_polepairs }},
    .ssi_clk_frequency_Hz = {{ ssi_clk_frequency_Hz }},
    .position_encoding = {{ position_encoding }},
    .position_mech_offset_si_single_turn = {{ position_mech_offset_si_single_turn }},
    .ssi_encoder_bit_width_single_turn = {{ ssi_encoder_bit_width_single_turn }},
    .ssi_encoder_bit_width_multi_turn = {{ ssi_encoder_bit_width_multi_turn }},
    .ssi_encoder_number_of_status_bits = {{ ssi_encoder_number_of_status_bits }},
    .sampling_interval_seconds = {{ sampling_interval_seconds }},
    .kp_pll = {{ kp_pll }},
    .ki_pll = {{ ki_pll }},
    .sampling_delay_clk_ticks = {{ sampling_delay_clk_ticks }}
};

uz_ssi_interface_t* initialize_ssi_encoder_{{ slot_lower }}_{{ channel }}(void)
{
    return uz_ssi_interface_init(ssi_encoder_{{ slot_lower }}_{{ channel }}_config);
}
