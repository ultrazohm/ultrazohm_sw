#include "../include/d5_adapter_init.h"

/* xz Project Wizard BEGIN: D5 definitions */
/* xz Project Wizard generated content for D5 channel 1 */
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
/* xz Project Wizard generated content for D5 channel 2 */
#include "xparameters.h"

static struct uz_ssi_interface_config_t ssi_encoder_d5_2_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_SSI_INTERFACE_D5_CHANNEL_2_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .machine_polepairs = 2U,
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

uz_ssi_interface_t* initialize_ssi_encoder_d5_2(void)
{
    return uz_ssi_interface_init(ssi_encoder_d5_2_config);
}
/* xz Project Wizard generated content for D5 channel 3 */
#include "xparameters.h"

static struct uz_endat_interface_config_t endat_encoder_d5_3_config = {
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

uz_endat_interface_t* initialize_endat_encoder_d5_3(void)
{
    return uz_endat_interface_init(endat_encoder_d5_3_config);
}
/* xz Project Wizard END: D5 definitions */
