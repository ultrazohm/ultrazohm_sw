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
#if UZ_PARAMETERID_ACTIVE > 0U
#include "uz_PID_TwoMassID.h"

static size_t instances_counter_PID_TwoMassID = 0;

static uz_PID_TwoMassID_t instances_PID_TwoMassID[UZ_PARAMETERID_ACTIVE] = { 0 };

static uz_PID_TwoMassID_t* uz_PID_TwoMassID_allocation(void);

static uz_PID_TwoMassID_t* uz_PID_TwoMassID_allocation(void) {
	uz_assert(instances_counter_PID_TwoMassID < UZ_PARAMETERID_ACTIVE);
	uz_PID_TwoMassID_t* self = &instances_PID_TwoMassID[instances_counter_PID_TwoMassID];
	instances_counter_PID_TwoMassID++;
	return (self);
}
uz_PID_TwoMassID_t* uz_PID_TwoMassID_init(void) {
	uz_PID_TwoMassID_t* self = uz_PID_TwoMassID_allocation();
	self->PtrToModelData = &self->modelData;
	self->PtrToModelData->dwork = &self->rtDW;
	self->PtrToModelData->inputs = &self->input;
	self->PtrToModelData->outputs = &self->output;
	TwoMassID_initialize(self->PtrToModelData);
	return (self);
}

void uz_PID_TwoMassID_step(uz_PID_TwoMassID_t *self) {
	TwoMassID_step(self->PtrToModelData);
}

#endif
