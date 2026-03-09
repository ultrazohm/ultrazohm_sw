#include "../include/uz_resolver_pl_IP_init.h"

#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

struct uz_resolver_pl_interface_config_t resolver_pl_IP_config = {
               .base_address = XPAR_UZ_RESOLVER_PL_INTERFACE_0_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000,
               .machine_polepairs = 4,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
               .theta_m_offset_rad = -0.3959959f
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_IP_outputs = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};

uz_resolver_pl_interface_t* init_resolver_pl_IP(void){
       return (uz_resolver_pl_interface_init(resolver_pl_IP_config, resolver_pl_IP_outputs));
}
