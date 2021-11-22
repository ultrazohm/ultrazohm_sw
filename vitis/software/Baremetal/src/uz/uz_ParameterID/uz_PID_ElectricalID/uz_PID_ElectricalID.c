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
#include "../../uz_global_configuration.h"
#include "uz_PID_ElectricalID.h"
#if UZ_PID_ELECTRICALID_ACTIVE > 0U
#include "../../uz_HAL.h"

void uz_ElectricalID_init(uz_PID_ElectricalID *self) {
	uz_assert(self->is_ready == false);
	uz_assert(UZ_PID_CONTROLSTATE_ACTIVE > 0U);
	self->PtrToModelData = &self->modelData;
	self->PtrToModelData->dwork = &self->rtDW;
	self->PtrToModelData->inputs = &self->input;
	self->PtrToModelData->outputs = &self->output;
}

void uz_ElectricalID_step(uz_PID_ElectricalID *self) {
	uz_assert(self->is_ready);
	ElectricalID_step(self->PtrToModelData);
}

#endif
