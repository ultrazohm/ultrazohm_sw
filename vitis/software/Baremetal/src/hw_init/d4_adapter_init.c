#include "../include/d4_adapter_init.h"

/* Project Wizard BEGIN: D4 definitions */
/* Project Wizard generated content for D4 channel 1 */
#include "xparameters.h"

static struct uz_ssi_interface_config_t ssi_encoder_d4_1_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D4_ADAPTER_UZ_SSI_INTERFACE_D4_CHANNEL_1_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .machine_polepairs = 4U,
    .ssi_clk_frequency_Hz = 1000000U,
    .position_encoding = uz_ssi_interface_binary,
    .position_mech_offset_si_single_turn = 0.0f,
    .ssi_encoder_bit_width_single_turn = 19U,
    .ssi_encoder_bit_width_multi_turn = 0U,
    .ssi_encoder_number_of_status_bits = 0U,
    .sampling_interval_seconds = 0.0001f,
    .kp_pll = 628.3185f,
    .ki_pll = 98696.0f,
    .sampling_delay_clk_ticks = 0U
};

uz_ssi_interface_t* initialize_ssi_encoder_d4_1(void)
{
    return uz_ssi_interface_init(ssi_encoder_d4_1_config);
}
/* Project Wizard END: D4 definitions */
