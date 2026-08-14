#include "../include/d5_adapter_init.h"

/* Project Wizard BEGIN: D5 definitions */
/* Project Wizard generated content for D5 channel 1 */
#include "xparameters.h"

static struct uz_endat_interface_config_t endat_encoder_d5_1_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_ENDAT_INTERFACE_D5_CHANNEL_1_BASEADDR,
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

uz_endat_interface_t* initialize_endat_encoder_d5_1(void)
{
    return uz_endat_interface_init(endat_encoder_d5_1_config);
}
/* Project Wizard END: D5 definitions */
