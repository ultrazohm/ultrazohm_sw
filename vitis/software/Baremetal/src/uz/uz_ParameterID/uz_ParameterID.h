/******************************************************************************
 * Copyright 2021 Dennis Hufnagel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#ifndef UZ_PARAMETERID_H
#define UZ_PARAMETERID_H

#include <math.h>
#include "../uz_HAL.h"
#include <stdbool.h>
#include "uz_PID_ControlState/uz_PID_ControlState.h"
#include "uz_PID_ElectricalID/uz_PID_ElectricalID.h"

typedef struct uz_ParameterID_t {
	bool is_ready;
	uz_PID_ElectricalID_t* ElectricalID;
	uz_PID_ControlState_t* ControlState;
} uz_ParameterID_t;

void uz_ParameterID_init(uz_ParameterID_t* self);

void uz_ParameterID_step(uz_ParameterID_t* self, uz_PID_GlobalConfig_t GlobalConfig, uz_PID_ActualValues_t ActualValues, uz_PID_ElectricalIDConfig_t ElectricalIDConfig);







#endif // UZ_PARAMETERID_H