#include "../include/endat_encoder.h"

struct uz_endat_interface_config_t endat_d5_1_config = {
		.base_address = XPAR_UZ_USER_UZ_ENDAT_INTERFACE_0_BASEADDR,
		.ip_clk_frequency_Hz = 100000000U,
		.machine_polepairs = 2U,
		.endat_clk_frequency_Hz = 2500000U,
		.position_mech_offset_si_single_turn = 0.0f,
		.endat_encoder_bit_width_single_turn = 25U,
		.endat_encoder_bit_width_multi_turn = 12U,
		.endat_encoder_number_of_CRC_bits = 5U, // is always 5 with endat
		.kp_pll = 628.3185f,
		.ki_pll = 98696.0f,
		.sampling_interval_seconds = 0.0001f
};

//struct uz_endat_interface_config_t endat_d5_3_config = {
//		.base_address = XPAR_UZ_USER_UZ_ENDAT_INTERFACE_1_BASEADDR,
//		.ip_clk_frequency_Hz = 100000000U,
//		.machine_polepairs = 2U,
//		.endat_clk_frequency_Hz = 2500000U,
//		.position_mech_offset_si_single_turn = 0.0f,
//		.endat_encoder_bit_width_single_turn = 25U,
//		.endat_encoder_bit_width_multi_turn = 0U,
//		.endat_encoder_number_of_CRC_bits = 5U,
//		.kp_pll = 628.3185f,
//		.ki_pll = 98696.0f,
//		.sampling_interval_seconds = 0.0001f
//};

uz_endat_interface_t* endat_encoder_init_endat_d5_1() {

	return(uz_endat_interface_init(endat_d5_1_config));
}

//uz_endat_interface_t* endat_encoder_init_endat_d5_3() {
//
//	return(uz_endat_interface_init(endat_d5_3_config));
//}
