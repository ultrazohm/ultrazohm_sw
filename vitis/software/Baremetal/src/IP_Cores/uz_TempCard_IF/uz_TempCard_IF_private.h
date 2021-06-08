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

#pragma once
#ifndef UZ_TEMPCARD_IF_PRIVATE_H
#define UZ_TEMPCARD_IF_PRIVATE_H

#include "uz_TempCard_IF.h"

//Configurations of one LTC2983
typedef struct {
	float       temperature[CHANNEL_COUNT_OneChannel];
	uint32_t    temperature_raw[CHANNEL_COUNT_OneChannel];
    uint32_t    Configdata[CHANNEL_COUNT_OneChannel];
	uint8_t		Channels_Valid[CHANNEL_COUNT_OneChannel];
}UZ_TempCard_IF_OneChannel;

struct uz_TempCard_IF {
	const uint32_t 				base_address;
	bool 						is_ready;
	uint32_t 					Control_Reg;
	uint32_t 					Counter_Period;
	uint32_t 					Readback;
	UZ_TempCard_IF_OneChannel	Channel_A;
	UZ_TempCard_IF_OneChannel	Channel_B;
	UZ_TempCard_IF_OneChannel	Channel_C;
};

#endif // UZ_TEMPCARD_IF_PRIVATE_H
