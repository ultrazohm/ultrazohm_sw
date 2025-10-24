#include "../include/resolver.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

struct uz_resolverIP_config_t resolver_config_d3_1={
        .base_address=XPAR_UZ_USER_ADAPTER_D3_RESOLVER_INTERFACE_V_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000U,
        .resolution = 16, // actually 14 bit ist selected in hardware, but due to buggy IP stay with 16
        .freq_clockin = 8192000,
        .pole_pairs_machine = 3.0f,
        .pole_pairs_resolver = 3.0f,
        .zero_position_mechanical = 0.0f,
        .mode_after_init = POSITION_VELOCITY_MODE,
     };

struct uz_resolver_pl_interface_config_t resolver_pl_config_d3_1 = {
               .base_address = XPAR_UZ_USER_ADAPTER_D3_UZ_RESOLVER_PL_INTER_0_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT, // actually 14 bit ist selected in hardware, but due to buggy IP stay with 16
               .ip_clk_frequency_Hz = 100000000U,
               .machine_polepairs = 3,
               .position_intmax = 65535,// actually 14 bit ist selected in hardware, but due to buggy IP stay with 16
               .resolver_polepairs = 3,
			   .theta_m_offset_rad = 0.0f
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d3_1 = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};


uz_resolverIP_t* initialize_resolver_D3_1(void) {
	return (uz_resolverIP_init(resolver_config_d3_1));
}

uz_resolver_pl_interface_t* initialize_resolver_pl_interface_D3_1(void) {
	return (uz_resolver_pl_interface_init(resolver_pl_config_d3_1,
			resolver_pl_outputs_d3_1));
}
