#include "../include/resolver.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

struct uz_resolverIP_config_t resolver_config_left={
        .base_address=XPAR_UZ_USER_RESOLVER_D4_RESOLVER_INTERFACE_V_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000U,
        .resolution = 16,
        .freq_clockin = 8192000,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical = 0.3959959f, //0.3923f <- was the rough estimate
        .mode_after_init = POSITION_VELOCITY_MODE,
     };

struct uz_resolverIP_config_t resolver_config_right={
        .base_address=XPAR_UZ_USER_RESOLVER_D4_RESOLVER_INTERFACE_V_2_BASEADDR,
        .ip_clk_frequency_Hz=100000000U,
        .resolution = 16,
        .freq_clockin = 8192000,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical =  0.4008981f, //0.3964f <- was the rough estimate
        .mode_after_init = POSITION_VELOCITY_MODE,
     };


struct uz_resolver_pl_interface_config_t resolver_pl_config_left = {
               .base_address = XPAR_UZ_RESOLVER_PL_INTERFACE_0_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000U,
               .machine_polepairs = 4,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
               .theta_m_offset_rad = -0.3959959f
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_left = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};

struct uz_resolver_pl_interface_config_t resolver_pl_config_right = {
               .base_address = XPAR_UZ_RESOLVER_PL_INTERFACE_2_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000U,
               .machine_polepairs = 4,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
               .theta_m_offset_rad = -0.4008981f
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_right = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};


uz_resolverIP_t* initialize_resolver_left(void) {
	return (uz_resolverIP_init(resolver_config_left));
}

uz_resolverIP_t* initialize_resolver_right(void) {
	return (uz_resolverIP_init(resolver_config_right));
}

uz_resolver_pl_interface_t* initialize_resolver_pl_interface_left(void) {
	return (uz_resolver_pl_interface_init(resolver_pl_config_left,
			resolver_pl_outputs_left));
}

uz_resolver_pl_interface_t* initialize_resolver_pl_interface_right(void) {
	return (uz_resolver_pl_interface_init(resolver_pl_config_right,
			resolver_pl_outputs_right));
}
