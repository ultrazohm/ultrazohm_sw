#include "../include/ssi_encoder.h"

struct uz_ssi_interface_config_t ssi_0_config = {
	.base_address = XPAR_UZ_USER_UZ_SSI_INTERFACE_0_BASEADDR,
	.ip_clk_frequency_Hz = 100000000U,
	.position_encoding = binary,
	.machine_polepairs = 2U,
	.ssi_clk_frequency_Hz = 2000000U,
	.position_mech_offset_si_single_turn = 0.0f,
	.ssi_encoder_bit_width_single_turn = 19U,
	.ssi_encoder_bit_width_multi_turn = 0U,
	.ssi_encoder_number_of_status_bits = 0U,
	.kp_pll = 628.3185f,
	.ki_pll = 98696.0f,
	.sampling_interval_seconds = 0.0001f
};

struct uz_ssi_interface_config_t ssi_1_config = {
	.base_address = XPAR_UZ_USER_UZ_SSI_INTERFACE_1_BASEADDR,
	.ip_clk_frequency_Hz = 100000000U,
	.position_encoding = binary,
	.machine_polepairs = 1U,
	.ssi_clk_frequency_Hz = 300000U,
	.position_mech_offset_si_single_turn = 0.0f,
	.ssi_encoder_bit_width_single_turn = 12U,
	.ssi_encoder_bit_width_multi_turn = 12U,
	.ssi_encoder_number_of_status_bits = 0U,
	.kp_pll = 628.3185f,
	.ki_pll = 98696.0f,
	.sampling_interval_seconds = 0.0001f
};

struct uz_ssi_interface_outputs_t ssi_0_outputs = {0};
struct uz_ssi_interface_outputs_t ssi_1_outputs = {0};

uz_ssi_interface_t* ssi_encoder_init_ssi0() {

	return(uz_ssi_interface_init(ssi_0_config, ssi_0_outputs));
}

uz_ssi_interface_t* ssi_encoder_init_ssi1() {

	return(uz_ssi_interface_init(ssi_1_config, ssi_1_outputs));
}
