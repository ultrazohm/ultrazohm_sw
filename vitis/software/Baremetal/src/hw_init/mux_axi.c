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
#include "../include/mux_axi.h"

#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_mux_axi_config_t uz_mux_axi_config = {
        .base_address= XPAR_INTERRUPT_MUX_AXI_IP_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
		.mux=INTERRUPT_ISR_SOURCE_USER_CHOICE,
        .n_th_interrupt=INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE
};

uz_mux_axi_t* initialize_uz_mux_axi(void) {

	return (uz_mux_axi_init(uz_mux_axi_config));

}

