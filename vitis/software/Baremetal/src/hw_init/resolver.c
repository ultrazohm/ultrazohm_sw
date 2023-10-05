#include "../include/resolver.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"


#define CRYSTAL_FREQUENCY 8192000U
#define IP_CLK_FREQ 100000000U
struct uz_resolverIP_config_t resolver_config={
        .base_address=XPAR_UZ_SYSTEM_RESOLVER_INTERFACE_V_0_BASEADDR,
        .ip_clk_frequency_Hz=IP_CLK_FREQ,
        .resolution = 16,
        .freq_clockin = CRYSTAL_FREQUENCY,
        .pole_pairs_machine = 11.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical = 0.3964f,
        .mode_after_init = POSITION_VELOCITY_MODE,
     };


uz_resolverIP_t* init_resolver_d4(void){
	return uz_resolverIP_init(resolver_config);
}

struct uz_resolver_pl_interface_config_t resolver_pl_config_d4 = {
               .base_address = XPAR_UZ_SYSTEM_UZ_RESOLVER_PL_INTER_0_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000,
               .machine_polepairs = 11,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
               .theta_m_offset_rad = -0.3964f
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d4 = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};

uz_resolver_pl_interface_t* initialize_resolver_pl_d4(void){
       return uz_resolver_pl_interface_init(resolver_pl_config_d4, resolver_pl_outputs_d4);
}
