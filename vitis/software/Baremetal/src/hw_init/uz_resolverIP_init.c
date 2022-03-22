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

// Declares pointer to instance on file scope. DO NOT DO THIS! Just done here to be compatible to the rest of the legacy code in this file!
static uz_resolverIP_t* resolverIP_D5;

#define CRYSTAL_FREQUENCY 8192000U

void initialize_resolverIP(void){
	 struct uz_resolverIP_config_t resolver_D5_config={
   	        .base_address=XPAR_RESOLVER_INTERFACE_V_0_BASEADDR,
   	        .ip_clk_frequency_Hz=100000000U,
			.resolution = 16,
			.freq_clockin = CRYSTAL_FREQUENCY
   	    };

	 resolverIP_D5 = uz_resolverIP_init(resolver_D5_config);
	 uz_resolverIP_setDataModePosition(resolverIP_D5);
	 uz_resolverIP_setZeroPosition(resolverIP_D5,0.F);
	 uz_resolverIP_setPolePairs(resolverIP_D5,1.F);
}

void update_position_of_resolverIP(DS_Data* const data){
	data->av.theta_mech = uz_resolverIP_readMechanicalPosition(resolverIP_D5);
	data->av.theta_elec = (data->av.theta_mech * uz_resolverIP_getPolePairs(resolverIP_D5)) - 2 * floor(data->av.theta_mech * uz_resolverIP_getPolePairs(resolverIP_D5)  / 2);
}

void update_speed_of_resolverIP(DS_Data* const data){
	data->av.mechanicalRotorSpeed = uz_resolverIP_readMechanicalVelocity(resolverIP_D5) * 60.f; //in rpm
}

void update_position_and_speed_of_resolverIP(DS_Data* const data){
	float *position = &data->av.theta_mech;
	float *velocity = &data->av.mechanicalRotorSpeed;
	uz_resolverIP_readMechanicalPositionAndVelocity(resolverIP_D5,position,velocity);
	data->av.mechanicalRotorSpeed = data->av.mechanicalRotorSpeed * 60.F; //rpm
	data->av.theta_elec = (data->av.theta_mech * uz_resolverIP_getPolePairs(resolverIP_D5)) - 2 * floor(data->av.theta_mech * uz_resolverIP_getPolePairs(resolverIP_D5)  / 2);
}

// For DEBUGGING only
void readRegister_of_resolverIP(DS_Data* const data){
	uint32_t val = uz_resolverIP_readRegister(resolverIP_D5,CONTROL_REG_ADR);
	uz_printf("%d \n",val);
	uint32_t val1 = uz_resolverIP_readRegister(resolverIP_D5,POS_REG_1_ADR);
	uz_printf("%d \n",val1);
}
