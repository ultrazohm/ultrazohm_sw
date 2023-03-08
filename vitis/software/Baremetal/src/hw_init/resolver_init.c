/******************************************************************************
* Copyright 2022 Michael Hoerner
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/
#include "../IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "../include/resolver_init.h"

#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

#define CRYSTAL_FREQUENCY 8192000U
#define IP_CLK_FREQ 100000000U

static struct uz_resolverIP_config_t d4_1_config = {
    .base_address = XPAR_RESOLVER_INTERFACE_V_0_BASEADDR,
    .ip_clk_frequency_Hz = IP_CLK_FREQ,
    .resolution = 16,
    .freq_clockin = CRYSTAL_FREQUENCY,
    .zero_position_mechanical = 0.0f,
    .pole_pairs_machine = 5.0f,
    .pole_pairs_resolver = 3.0f,
};

uz_resolverIP_t* init_resolver_d4_1(void) {
	return uz_resolverIP_init(d4_1_config);
}
