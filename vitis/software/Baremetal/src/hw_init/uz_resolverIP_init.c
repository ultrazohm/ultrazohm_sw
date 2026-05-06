#include "../include/resolver.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

#define RESOLVER_D3_1_MACHINE_POLEPAIRS 3.0f

struct uz_resolverIP_config_t resolver_config_d3_1={
        .base_address=XPAR_UZ_USER_ADAPTER_D3_RESOLVER_INTERFACE_V_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000U,
        .resolution = 16, // actually 14 bit ist selected in hardware, but due to buggy IP stay with 16
        .freq_clockin = 8192000,
        .pole_pairs_machine = RESOLVER_D3_1_MACHINE_POLEPAIRS,
        .pole_pairs_resolver = 3.0f,
        .zero_position_mechanical = 0.0f,
        .mode_after_init = POSITION_VELOCITY_MODE,
     };

struct uz_resolver_pl_interface_config_t resolver_pl_config_d3_1 = {
               .base_address = XPAR_UZ_USER_ADAPTER_D3_UZ_RESOLVER_PL_INTER_0_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT, // actually 14 bit ist selected in hardware, but due to buggy IP stay with 16
               .ip_clk_frequency_Hz = 100000000U,
               .machine_polepairs = (int32_t)RESOLVER_D3_1_MACHINE_POLEPAIRS,
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

void update_resolver_D3_1(DS_Data *const data) {
	struct uz_resolver_pl_interface_outputs_t outputs = uz_resolver_pl_interface_get_outputs(data->objects.resolver_pl_interface_d3_1);

	data->av.resolver_pl_outputs_d3_1 = outputs;
	data->av.position_mech_2pi_d3_1 = outputs.position_mech_2pi;
	data->av.position_el_2pi_d3_1 = outputs.position_el_2pi;
	data->av.n_mech_rpm_d3_1 = outputs.n_mech_rpm;
	data->av.omega_mech_left = outputs.omega_mech_rad_s;
	data->av.omega_el_left = outputs.omega_mech_rad_s * RESOLVER_D3_1_MACHINE_POLEPAIRS;
}
