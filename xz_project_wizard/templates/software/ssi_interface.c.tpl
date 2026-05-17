/* xz Project Wizard generated content for {{ slot }} channel {{ channel }} */
#include "xparameters.h"

static struct uz_ssi_interface_config_t ssi_encoder_{{ slot_lower }}_{{ channel }}_config = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = 100000000U,
    .ssi_clk_frequency_Hz = 2500000U,
    .ssi_encoder_bit_width_single_turn = 19U,
    .ssi_encoder_bit_width_multi_turn = 12U,
    .ssi_encoder_number_of_status_bits = 2U,
    .position_encoding = uz_ssi_interface_gray_code,
    .machine_polepairs = 4U,
    .sampling_delay_clk_ticks = 40U,
    .sampling_interval_seconds = 0.0001f,
    .kp_pll = 628.0f,
    .ki_pll = 98696.0f,
    .position_mech_offset_si_single_turn = -1.276f
};

uz_ssi_interface_t* initialize_ssi_encoder_{{ slot_lower }}_{{ channel }}(void)
{
    return uz_ssi_interface_init(ssi_encoder_{{ slot_lower }}_{{ channel }}_config);
}
