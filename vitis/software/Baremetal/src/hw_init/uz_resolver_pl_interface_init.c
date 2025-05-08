#include "../include/uz_resolver_pl_interface_init.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

struct uz_resolver_pl_interface_config_t resolver_pl_config_d4_0 = {
               .base_address = XPAR_UZ_RESOLVER_PL_INTERFACE_0_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000,
               .machine_polepairs = 4,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
               .theta_m_offset_rad = -0.3964f
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d4_0 = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};

uz_resolver_pl_interface_t* initialize_resolver_pl_d4_0(void){
       return (uz_resolver_pl_interface_init(resolver_pl_config_d4_0, resolver_pl_outputs_d4_0));
}

struct uz_resolver_pl_interface_config_t resolver_pl_config_d4_1 = {
               .base_address = XPAR_UZ_RESOLVER_PL_INTERFACE_1_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000,
               .machine_polepairs = 4,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
               .theta_m_offset_rad = -0.3964f
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d4_1 = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};

uz_resolver_pl_interface_t* initialize_resolver_pl_d4_1(void){
       return (uz_resolver_pl_interface_init(resolver_pl_config_d4_1, resolver_pl_outputs_d4_1));
}
