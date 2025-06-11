#include "../include/uz_resolverIP_init.h"

#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

#define CRYSTAL_FREQUENCY 8192000U
#define IP_CLK_FREQ 100000000U

struct uz_resolverIP_config_t resolverIP_config_0 = {
        .base_address=XPAR_UZ_USER_UZ_RESOLVER_RESOLVER_INTERFACE_V_0_BASEADDR,
        .ip_clk_frequency_Hz=IP_CLK_FREQ,
        .resolution = 16,
        .freq_clockin = CRYSTAL_FREQUENCY,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical = 0.3964f,
        .mode_after_init = CONFIG_MODE,
     };

uz_resolverIP_t* initialize_resolverIP_0(void){
       return (uz_resolverIP_init(resolverIP_config_0));
}

struct uz_resolverIP_config_t resolverIP_config_1 = {
        .base_address=XPAR_UZ_USER_UZ_RESOLVER_RESOLVER_INTERFACE_V_1_BASEADDR,
        .ip_clk_frequency_Hz=IP_CLK_FREQ,
        .resolution = 16,
        .freq_clockin = CRYSTAL_FREQUENCY,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical = 0.3964f,
        .mode_after_init = CONFIG_MODE,
     };

uz_resolverIP_t* initialize_resolverIP_1(void){
       return (uz_resolverIP_init(resolverIP_config_1));
}
