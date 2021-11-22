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
#include "uz_ParameterID.h"

typedef struct uz_ParameterID_t {
	bool is_ready;
	uz_PID_ElectricalID_t *ElectricalID;
	uz_PID_ControlState_t *ControlState;
} uz_ParameterID_t;

void uz_ParameterID_init(uz_ParameterID_t *self) {
	uz_assert(self->is_ready == false);
}
