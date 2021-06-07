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

//Configurations of one LTC2983
struct UZ_TempCard_IF_OneChannel {
	float       temperature[CHANNEL_COUNT];
	long        temperature_raw[CHANNEL_COUNT];
    u_int32_t   Configdata[CHANNEL_COUNT];
};

struct UZ_TempCard_IF_OneChannel {
	float       temperature[CHANNEL_COUNT];
	long        temperature_raw[CHANNEL_COUNT];
    u_int32_t   Configdata[CHANNEL_COUNT];
};