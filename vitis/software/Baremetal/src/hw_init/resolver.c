#include "../include/resolver.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

struct uz_resolverIP_config_t resolver_config_d5_1={
        .base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_RESOLVER_INTERFACE_V_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000U,
        .resolution = 16,
        .freq_clockin = 8192000,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical = 0.3912f,
//		.zero_position_mechanical = 0.6560f,
        .mode_after_init = POSITION_VELOCITY_MODE,
     };

struct uz_resolverIP_config_t resolver_config_d5_2={
        .base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_RESOLVER_INTERFACE_V_1_BASEADDR,
        .ip_clk_frequency_Hz=100000000U,
        .resolution = 16,
        .freq_clockin = 8192000,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical =  0.3994f,
        .mode_after_init = POSITION_VELOCITY_MODE,
     };


struct uz_resolver_pl_interface_config_t resolver_pl_config_d5_1 = {
               .base_address = XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_PL_INTER_0_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000U,
               .machine_polepairs = 4,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
			   .theta_m_offset_rad = -0.3912f // A B C
//			   .theta_m_offset_rad = -0.6560f // B A C + SIN/COS twisted
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d5_1 = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};

struct uz_resolver_pl_interface_config_t resolver_pl_config_d5_2 = {
		.base_address = XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_PL_INTER_1_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000U,
               .machine_polepairs = 4,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
               .theta_m_offset_rad = -0.3994f
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d5_2 = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};


uz_resolverIP_t* initialize_resolver_D5_1(void) {
	return (uz_resolverIP_init(resolver_config_d5_1));
}

uz_resolverIP_t* initialize_resolver_D5_2(void) {
	return (uz_resolverIP_init(resolver_config_d5_2));
}

uz_resolver_pl_interface_t* initialize_resolver_pl_interface_D5_1(void) {
	return (uz_resolver_pl_interface_init(resolver_pl_config_d5_1,
			resolver_pl_outputs_d5_1));
}

uz_resolver_pl_interface_t* initialize_resolver_pl_interface_D5_2(void) {
	return (uz_resolver_pl_interface_init(resolver_pl_config_d5_2,
			resolver_pl_outputs_d5_2));
}
