/******************************************************************************
* Copyright 2021 Robert Zipprich
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

#include "uz_TempCard_IF.h"
#include "uz_TempCard_IF_private.h"
#include "uz_TempCard_IF_staticAllocator.h"
#include "xparameters.h"

#ifdef XPAR_TEMPERATURE_CARD_INTERFACE_TEMPERATURE_CARD_INT_0_BASEADDR

static uz_TempCard_IF uz_TempCard_IF_instance={
	.base_address=XPAR_TEMPERATURE_CARD_INTERFACE_TEMPERATURE_CARD_INT_0_BASEADDR,
	.ip_clk_frequency_Hz=100000000U
};

uz_TempCard_IF_handle uz_TempCard_IF_instance_one(void){
    return (uz_TempCard_IF_init(&uz_TempCard_IF_instance));
}

#endif