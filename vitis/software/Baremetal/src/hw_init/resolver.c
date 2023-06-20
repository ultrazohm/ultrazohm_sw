#include "../include/resolver.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

#define CRYSTAL_FREQUENCY 8192000U
#define IP_CLK_FREQ 100000000U

static struct uz_resolverIP_config_t resolver_config={
        .base_address=XPAR_RESOLVER_INTERFACE_V1_0_BASEADDR,
        .ip_clk_frequency_Hz=IP_CLK_FREQ,
        .resolution = 16,
        .freq_clockin = CRYSTAL_FREQUENCY,
        .zero_position_mechanical = 0.0f,
        .pole_pairs_machine = UZ_D5_MOTOR_POLE_PAIR_NUMBER,
        .pole_pairs_resolver = 2
     };

uz_resolverIP_t* init_resolver_at_d5_1(void) {
	return(uz_resolverIP_init(resolver_config));
}
