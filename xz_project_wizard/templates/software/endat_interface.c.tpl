/* xz Project Wizard generated content for {{ slot }} channel {{ channel }} */
#include "xparameters.h"

static struct uz_endat_interface_config_t endat_encoder_{{ slot_lower }}_{{ channel }}_config = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = 100000000U,
    .machine_polepairs = 2U,
    .endat_clk_frequency_Hz = 2500000U,
    .position_mech_offset_si_single_turn = -1.0f,
    .endat_encoder_bit_width_single_turn = 25U,
    .endat_encoder_bit_width_multi_turn = 12U,
    .kp_pll = 628.3185f,
    .ki_pll = 98696.0f,
    .sampling_interval_seconds = 0.0001f,
    .delay_sampling_in_clk_ticks = 0U
};

uz_endat_interface_t* initialize_endat_encoder_{{ slot_lower }}_{{ channel }}(void)
{
    return uz_endat_interface_init(endat_encoder_{{ slot_lower }}_{{ channel }}_config);
}
