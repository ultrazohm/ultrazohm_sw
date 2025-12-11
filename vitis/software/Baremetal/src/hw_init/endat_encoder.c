#include "../include/endat_encoder.h"


struct uz_endat_interface_config_t endat_d5_3_config = {
		.base_address = XPAR_UZ_USER_UZ_ENDAT_INTERFACE_0_BASEADDR,
		.ip_clk_frequency_Hz = 100000000U,
		.position_encoding = binary,
		.machine_polepairs = 21U,
		.endat_clk_frequency_Hz = 2000000U,
		.position_mech_offset_si_single_turn = 0.0f,
		.endat_encoder_bit_width_single_turn = 23U,
		.endat_encoder_bit_width_multi_turn = 0U,
		.endat_encoder_number_of_CRC_bits = 0U,
		.kp_pll = 628.3185f,
		.ki_pll = 98696.0f,
		.sampling_interval_seconds = 0.000025f
};
/*
struct uz_endat_interface_outputs_t endat_d5_1_outputs = {0};

uz_endat_interface_t* endat_encoder_init_endat_d5_1() {

	return(uz_endat_interface_init(endat_d5_1_config, endat_d5_1_outputs));
}
*/

struct uz_endat_interface_outputs_t endat_d5_3_outputs = {0};

uz_endat_interface_t* endat_encoder_init_endat_d5_3() {

	return(uz_endat_interface_init(endat_d5_3_config, endat_d5_3_outputs));
}
