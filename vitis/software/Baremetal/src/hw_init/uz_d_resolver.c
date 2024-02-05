#include "xparameters.h"
#include  "../include/uz_d_resolver.h"


struct uz_resolverIP_config_t resolver_config_0={
        .base_address=XPAR_UZ_USER_RESOLVER_INTERFACE_V_0_BASEADDR,
        .ip_clk_frequency_Hz=IP_CLK_FREQ,
        .resolution = 16,
        .freq_clockin = CRYSTAL_FREQUENCY,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical = 0.0f,
        .mode_after_init = POSITION_VELOCITY_MODE,
     };

struct uz_resolverIP_config_t resolver_config_1={
        .base_address=XPAR_UZ_USER_RESOLVER_INTERFACE_V_1_BASEADDR,
        .ip_clk_frequency_Hz=IP_CLK_FREQ,
        .resolution = 16,
        .freq_clockin = CRYSTAL_FREQUENCY,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical = 0.0f,
        .mode_after_init = POSITION_VELOCITY_MODE,
     };

struct uz_resolverIP_config_t resolver_config_2={
        .base_address=XPAR_UZ_USER_RESOLVER_INTERFACE_V_2_BASEADDR,
        .ip_clk_frequency_Hz=IP_CLK_FREQ,
        .resolution = 16,
        .freq_clockin = CRYSTAL_FREQUENCY,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical = 0.0f,
        .mode_after_init = POSITION_VELOCITY_MODE,
     };


struct uz_resolver_pl_interface_config_t resolver_pl_config_d4_0 = {
               .base_address = XPAR_UZ_USER_UZ_RESOLVER_PL_INTER_0_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000,
               .machine_polepairs = 4,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
               .theta_m_offset_rad = 0.0f
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d4_0 = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};

struct uz_resolver_pl_interface_config_t resolver_pl_config_d4_1 = {
               .base_address = XPAR_UZ_USER_UZ_RESOLVER_PL_INTER_1_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000,
               .machine_polepairs = 4,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
               .theta_m_offset_rad = 0.0f
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d4_1 = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};

struct uz_resolver_pl_interface_config_t resolver_pl_config_d4_2 = {
               .base_address = XPAR_UZ_USER_UZ_RESOLVER_PL_INTER_2_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000,
               .machine_polepairs = 4,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
               .theta_m_offset_rad = 0.0f
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d4_2 = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};


uz_resolverIP_t* init_uz_d_resolverIP_d4_0() {
	return uz_resolverIP_init(resolver_config_0);
}

uz_resolverIP_t* init_uz_d_resolverIP_d4_1() {
	return uz_resolverIP_init(resolver_config_1);
}

uz_resolverIP_t* init_uz_d_resolverIP_d4_2() {
	return uz_resolverIP_init(resolver_config_2);
}


uz_resolver_pl_interface_t* init_uz_d_resolver_pl_interf_d4_0() {
	return  uz_resolver_pl_interface_init(resolver_pl_config_d4_0, resolver_pl_outputs_d4_0);
}

uz_resolver_pl_interface_t* init_uz_d_resolver_pl_interf_d4_1() {
	return  uz_resolver_pl_interface_init(resolver_pl_config_d4_1, resolver_pl_outputs_d4_1);
}

uz_resolver_pl_interface_t* init_uz_d_resolver_pl_interf_d4_2() {
	return  uz_resolver_pl_interface_init(resolver_pl_config_d4_2, resolver_pl_outputs_d4_2);
}
