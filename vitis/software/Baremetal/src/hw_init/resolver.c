#include "../include/resolver.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

struct uz_resolverIP_config_t resolver_config_D5_1 = {
		.base_address = XPAR_UZ_USER_RESOLVER_D5_1_RESOLVER_INTERFACE_V_0_BASEADDR,
		.freq_clockin = 8192000,
		.ip_clk_frequency_Hz = 100000000,
		.pole_pairs_machine = 4.0f,
		.pole_pairs_resolver = 1.0f,
		.resolution = 16,
		.zero_position_mechanical = 0.3923f
};

struct uz_resolverIP_config_t resolver_config_D5_2 = {
		.base_address = XPAR_UZ_USER_RESOLVER_D5_2_RESOLVER_INTERFACE_V_0_BASEADDR,
		.freq_clockin = 8192000,
		.ip_clk_frequency_Hz = 100000000,
		.pole_pairs_machine = 4.0f,
		.pole_pairs_resolver = 1.0f,
		.resolution = 16,
		.zero_position_mechanical = 0.3964f
};


uz_resolverIP_t* initialize_resolver_D5_1(void){
	return (uz_resolverIP_init(resolver_config_D5_1));
}

uz_resolverIP_t* initialize_resolver_D5_2(void){
	return (uz_resolverIP_init(resolver_config_D5_2));
}

