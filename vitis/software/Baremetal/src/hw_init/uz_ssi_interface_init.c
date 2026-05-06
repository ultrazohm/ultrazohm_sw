#include "../include/uz_ssi_interface_init.h"

struct uz_ssi_interface_config_t ssi_d5_1_config = {
	.base_address = XPAR_UZ_USER_UZ_SSI_INTERFACE_0_BASEADDR,
	.ip_clk_frequency_Hz = 100000000U,
	.position_encoding = uz_ssi_interface_binary,
	.machine_polepairs = 2U,
	.ssi_clk_frequency_Hz = 1000000U,
	.position_mech_offset_si_single_turn = 0.0f,
	.ssi_encoder_bit_width_single_turn = 19U,
	.ssi_encoder_bit_width_multi_turn = 0U,
	.ssi_encoder_number_of_status_bits = 0U,
	.sampling_delay_clk_ticks = 0U,
	.kp_pll = 628.3185f,
	.ki_pll = 98696.0f,
	.sampling_interval_seconds = 0.0001f
};

struct uz_ssi_interface_config_t ssi_d5_2_config = {
	.base_address = XPAR_UZ_USER_UZ_SSI_INTERFACE_1_BASEADDR,
	.ip_clk_frequency_Hz = 100000000U,
	.position_encoding = uz_ssi_interface_gray_code,
	.machine_polepairs = 2U,
	.ssi_clk_frequency_Hz = 1000000U,
	.position_mech_offset_si_single_turn = 0.0f,
	.ssi_encoder_bit_width_single_turn = 12U,
	.ssi_encoder_bit_width_multi_turn = 12U,
	.ssi_encoder_number_of_status_bits = 0U,
	.sampling_delay_clk_ticks = 0U,
	.kp_pll = 628.3185f,
	.ki_pll = 98696.0f,
	.sampling_interval_seconds = 0.0001f
};

struct uz_ssi_interface_config_t ssi_d5_3_config = {
	.base_address = XPAR_UZ_USER_UZ_SSI_INTERFACE_2_BASEADDR,
	.ip_clk_frequency_Hz = 100000000U,
	.position_encoding = uz_ssi_interface_gray_code,
	.machine_polepairs = 2U,
	.ssi_clk_frequency_Hz = 1000000U,
	.position_mech_offset_si_single_turn = 0.0f,
	.ssi_encoder_bit_width_single_turn = 14U,
	.ssi_encoder_bit_width_multi_turn = 0U,
	.ssi_encoder_number_of_status_bits = 0U,
	.sampling_delay_clk_ticks = 0U,
	.kp_pll = 628.3185f,
	.ki_pll = 98696.0f,
	.sampling_interval_seconds = 0.0001f
};

uz_ssi_interface_t* ssi_encoder_init_d5_1() {

	return(uz_ssi_interface_init(ssi_d5_1_config));
}

uz_ssi_interface_t* ssi_encoder_init_d5_2() {

	return(uz_ssi_interface_init(ssi_d5_2_config));
}

uz_ssi_interface_t* ssi_encoder_init_d5_3() {

	return(uz_ssi_interface_init(ssi_d5_3_config));
}
