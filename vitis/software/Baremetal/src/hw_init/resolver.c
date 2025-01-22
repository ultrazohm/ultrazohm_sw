#include "../include/resolver_init.h"
#include "../IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

#define CRYSTAL_FREQUENCY 8192000U
#define IP_CLK_FREQ 100000000U

static struct uz_resolverIP_config_t resolver_config={
        .base_address=XPAR_UZ_USER_RESOLVER_INTERFACE_V_0_BASEADDR,
        .ip_clk_frequency_Hz=IP_CLK_FREQ,
        .resolution = 16,
        .freq_clockin = CRYSTAL_FREQUENCY,
        .zero_position_mechanical = 0.0f,
        .pole_pairs_machine = 5,
        .pole_pairs_resolver = 2
     };

uz_resolverIP_t* init_resolver_at_d5_1(void) {
	return(uz_resolverIP_init(resolver_config));
}


static struct uz_resolver_pl_interface_config_t pl_config = {
		.base_address = XPAR_UZ_USER_UZ_RESOLVER_PL_INTER_0_BASEADDR,
		.ip_clk_frequency_Hz = 100000000U,
		.position_intmax = 65535,
		.bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
		.machine_polepairs = 5,
		.resolver_polepairs = 2,
		.theta_m_offset_rad = -6.25f
};

static struct uz_resolver_pl_interface_outputs_t pl_outputs = {
		.revolution_counter = 0,
		.position_mech_2pi = 0.0f,
		.position_el_2pi = 0.0f,
		.omega_mech_rad_s = 0.0f,
		.n_mech_rpm = 0.0f
};

uz_resolver_pl_interface_t* initialize_resolver_pl_interface(void) {
	return(uz_resolver_pl_interface_init(pl_config, pl_outputs));
}
