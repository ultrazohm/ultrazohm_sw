/******************************************************************************
* Copyright 2023 Robert Zipprich
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

#include "uz_LinearRegressionCore_hw.h"

//Basics
void enable_Channel_hw(uint32_t base_address, uint32_t Channel_nr){		// enables Linear Regression on specified Channel
	uz_assert_not_zero(base_address);
	uint32_t Regdata = 0;
	Regdata = uz_axi_read_int32(base_address + Channel_Select_Register);
	uz_axi_write_int32(base_address + Channel_Select_Register, (Regdata | Channel_nr));
}

void disable_Channel_hw(uint32_t base_address, uint32_t Channel_nr){	// disables Linear Regression on specified Channel
	uz_assert_not_zero(base_address);
	uint32_t Regdata = 0;
	Regdata = uz_axi_read_int32(base_address + Channel_Select_Register);
	uz_axi_write_int32(base_address + Channel_Select_Register, (Regdata & ~Channel_nr));
}

void write_Channel_hw(uint32_t base_address,uint32_t Channels){			// write all channels
	uz_assert_not_zero(base_address);
	uz_axi_write_int32(base_address + Channel_Select_Register, Channels);
}

uint32_t read_Channel_hw(uint32_t base_address){						// read all channels
	uz_assert_not_zero(base_address + Channel_Select_Register);
	uint32_t Regdata = 0;
	Regdata = uz_axi_read_int32(base_address + Channel_Select_Register);
	return Regdata;
}

uint32_t	check_Channel_hw(uint32_t base_address){					// disables Linear Regression on specified Channel
	uz_assert_not_zero(base_address + Channel_Select_Register);
	uint32_t Regdata = 0;
	Regdata = uz_axi_read_int32(base_address + Channel_Select_Register);
	return Regdata;
}
