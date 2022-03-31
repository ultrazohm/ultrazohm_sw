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
#if UZ_PARAMETERID_MAX_INSTANCES > 0U
#include "uz_PID_ControlState.h"

static uint32_t instances_counter_PID_ControlState = 0;

static uz_PID_ControlState_t instances_PID_ControlState[UZ_PARAMETERID_MAX_INSTANCES] = { 0 };

static uz_PID_ControlState_t* uz_PID_ControlState_allocation(void);

static uz_PID_ControlState_t* uz_PID_ControlState_allocation(void) {
	uz_assert(instances_counter_PID_ControlState < UZ_PARAMETERID_MAX_INSTANCES);
	uz_PID_ControlState_t* self = &instances_PID_ControlState[instances_counter_PID_ControlState];
	instances_counter_PID_ControlState++;
	return (self);
}

uz_PID_ControlState_t* uz_ControlState_init(void) {
	uz_PID_ControlState_t* self = uz_PID_ControlState_allocation();
	self->PtrToModelData = &self->modelData;
	self->PtrToModelData->dwork = &self->rtDW;
	self->PtrToModelData->inputs = &self->input;
	self->PtrToModelData->outputs = &self->output;
	ControlState_initialize(self->PtrToModelData);
	return (self);
}

void uz_ControlState_step(uz_PID_ControlState_t *self) {
	uz_assert_not_NULL(self);
	ControlState_step(self->PtrToModelData);
}
#endif