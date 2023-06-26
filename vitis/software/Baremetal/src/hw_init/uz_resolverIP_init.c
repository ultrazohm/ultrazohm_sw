	/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Felix Kaiser, Thomas Effenberger, Eyke Liegmann
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

#include <stdint.h>
#include <math.h>
#include "../include/uz_resolverIP_init.h"
#include "../IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "xparameters.h"
#include "../IP_Cores/uz_resolverIP/uz_resolverIP_hw.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_math_constants.h"
#include "../IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"

#define CRYSTAL_FREQUENCY 8192000U

static struct uz_resolverIP_config_t resolver_D5_config={
		.base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_RESOLVER_INTERFACE_V_0_BASEADDR,
   	    .ip_clk_frequency_Hz=100000000U,
		.resolution = 16,
		.freq_clockin = CRYSTAL_FREQUENCY,
		.zero_position_mechanical = 0.42f,
		.pole_pairs_machine = 5.0f,
		.pole_pairs_resolver = 2.0f
};

uz_resolverIP_t* initialize_resolverIP_on_D5(void){
	return (uz_resolverIP_init(resolver_D5_config));
}

void update_position_of_resolverIP(DS_Data* const data){
	data->av.theta_mech = uz_resolverIP_readMechanicalPosition(data->objects.resolver_IP);
	data->av.theta_elec = (data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)) - 2 * UZ_PIf * floor(data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)  / (2* UZ_PIf));
}

void update_speed_of_resolverIP(DS_Data* const data){
	data->av.mechanicalRotorSpeed = uz_resolverIP_readMechanicalVelocity(data->objects.resolver_IP) * 60.f; //in rpm
}

struct uz_resolverIP_position_velocity_t update_position_and_speed_of_resolverIP(DS_Data* const data){
	uz_resolverIP_readMechanicalPositionAndVelocity(data->objects.resolver_IP);
//	data->av.mechanicalRotorSpeed = data->av.mechanicalRotorSpeed * 60.F; //rpm
//	data->av.theta_elec = (data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)) - 2 * UZ_PIf * floor(data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)  / (2* UZ_PIf));
}
//
//// For DEBUGGING only
//void readRegister_of_resolverIP(DS_Data* const data){
//	uint32_t val = uz_resolverIP_readRegister(data->objects.resolver_IP,CONTROL_REG_ADR);
//	uz_printf("%d \n",val);
//	uint32_t val1 = uz_resolverIP_readRegister(data->objects.resolver_IP,POS_REG_1_ADR);
//	uz_printf("%d \n",val1);
//}

static struct uz_resolver_pl_interface_config_t pl_config = {
		.base_address = XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_PL_INTER_0_BASEADDR,
		.ip_clk_frequency_Hz = 100000000U,
		.position_intmax = 65535,
		.bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
		.machine_polepairs = 5,
		.resolver_polepairs = 2,
		.theta_m_offset_rad = -0.42f
};

static struct uz_resolver_pl_interface_outputs_t pl_outputs = {
		.revolution_counter = 0,
		.position_mech_2pi = 0.0f,
		.position_el_2pi = 0.0f,
		.omega_mech_rad_s = 0.0f,
		.n_mech_rpm = 0.0f
};

uz_resolver_pl_interface_t* initialize_resolver_pl_interface(void) {
	return(uz_resolver_pl_interface_init(pl_config, pl_outputs));
}
