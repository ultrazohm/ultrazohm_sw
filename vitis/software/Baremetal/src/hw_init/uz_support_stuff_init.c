#include "../include/uz_support_stuff_init.h"
#include "xparameters.h"



struct uz_6ph_spacevector_decoder_config_t config_spacevector_decoder_1 = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_6PH_SV_DECODE_IP_0_BASEADDR,
    .ip_clk_frequency_Hz = 100000000,
};

uz_6ph_spacevector_decoder_t* init_uz_6ph_spacevector_decoder_1(void){
	return uz_6ph_spacevector_decoder_init(config_spacevector_decoder_1);
}





struct uz_count_switching_IP_config_t config_switching_counter_1_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_COUNT_IP_0_BASEADDR, /**< Base address of the IP-Core */
    .ip_clk_frequency_Hz = 100000000,
};

uz_count_switching_IP_t* init_uz_count_switching_IP_1(void){
	uz_count_switching_IP_t* uz_count_switching_IP_init(config_switching_counter_1_config);
}
