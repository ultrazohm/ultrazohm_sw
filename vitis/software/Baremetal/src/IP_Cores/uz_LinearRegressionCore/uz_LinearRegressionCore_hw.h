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

#ifndef UZ_LINEARREGRESSIONCORE_HW
#define UZ_LINEARREGRESSIONCORE_HW

#include <stdint.h>
#include "uz_LinearRegressionCore_hwAddresses.h"
#include "../../uz/uz_AXI.h"

//Basics
void		enable_Channel_hw(uint32_t base_address,uint32_t Channel_nr);		// enables Linear Regression on specified Channel
void		disable_Channel_hw(uint32_t base_address,uint32_t Channel_nr);		// disables Linear Regression on specified Channel
void		write_Channel_hw(uint32_t base_address,uint32_t Channel_nr);		// write all channels
uint32_t	read_Channel_hw(uint32_t base_address);								// read all channels
uint32_t	check_Channel_hw(uint32_t base_address);							// check Channels

#endif // UZ_LINEARREGRESSIONCORE_HW
