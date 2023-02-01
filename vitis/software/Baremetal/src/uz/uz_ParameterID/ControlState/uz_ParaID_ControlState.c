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
#include "uz_ParaID_ControlState.h"
#include "../../uz_HAL.h"

typedef struct uz_ParaID_ControlState_t{
	bool is_ready;
	ExtY_ControlState_t output;
	ExtU_ControlState_t input;
	DW_ControlState_t rtDW; /* Observable states */
	RT_MODEL_ControlState_t modelData;
	RT_MODEL_ControlState_t *PtrToModelData;
};

static uint32_t instances_counter_ParaID_ControlState = 0;
static uz_ParaID_ControlState_t instances_ParaID_ControlState[UZ_PARAMETERID_MAX_INSTANCES] = { 0 };

static uz_ParaID_ControlState_t* uz_ParaID_ControlState_allocation(void);

static uz_ParaID_ControlState_t* uz_ParaID_ControlState_allocation(void) {
	uz_assert(instances_counter_ParaID_ControlState < UZ_PARAMETERID_MAX_INSTANCES);
	uz_ParaID_ControlState_t* self = &instances_ParaID_ControlState[instances_counter_ParaID_ControlState];
	uz_assert_false(self->is_ready);
	instances_counter_ParaID_ControlState++;
	self->is_ready = true;
	return (self);
}

uz_ParaID_ControlState_t* uz_ControlState_init(void) {
	uz_ParaID_ControlState_t* self = uz_ParaID_ControlState_allocation();
	self->PtrToModelData = &self->modelData;
	self->PtrToModelData->dwork = &self->rtDW;
	self->PtrToModelData->inputs = &self->input;
	self->PtrToModelData->outputs = &self->output;
	ControlState_initialize(self->PtrToModelData);
	return (self);
}

void uz_ControlState_step(uz_ParaID_ControlState_t *self) {
	uz_assert_not_NULL(self);
	ControlState_step(self->PtrToModelData);
}

void uz_ControlState_set_finishedFrictionID(uz_ParaID_ControlState_t *self, bool is_finished) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.finishedFrictionID = is_finished;
}

void uz_ControlState_set_finishedElectricalID(uz_ParaID_ControlState_t *self, bool is_finished) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.finishedElectricalID = is_finished;
}

void uz_ControlState_set_finishedTwoMassID(uz_ParaID_ControlState_t *self, bool is_finished) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.finishedTwoMassID = is_finished;
}

void uz_ControlState_set_finishedFluxMapID(uz_ParaID_ControlState_t *self, bool is_finished) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.finishedFluxMapID = is_finished;
}

void uz_ControlState_set_enteredFrictionID(uz_ParaID_ControlState_t *self, bool did_enter) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.enteredFrictionID = did_enter;
}
void uz_ControlState_set_enteredFluxMapID(uz_ParaID_ControlState_t *self, bool did_enter) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.enteredFluxMapID = did_enter;
}

void uz_ControlState_set_enteredTwoMassID(uz_ParaID_ControlState_t *self, bool did_enter) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.enteredTwoMassID = did_enter;
}

void uz_ControlState_set_enteredElectricalID(uz_ParaID_ControlState_t *self, bool did_enter) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.enteredElectricalID = did_enter;
}

void uz_ControlState_set_enteredOnlineID(uz_ParaID_ControlState_t *self, bool did_enter) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.enteredOnlineID = did_enter;
}
void uz_ControlState_set_ElectricalID_output(uz_ParaID_ControlState_t *self, uz_ParaID_ElectricalID_output_t ElectricalID_output) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ElectricalID_output = ElectricalID_output;
}

void uz_ControlState_set_GlobalConfig(uz_ParaID_ControlState_t *self, uz_ParaID_GlobalConfig_t GlobalConfig) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);	
	self->input.GlobalConfig_in = GlobalConfig;
}

void uz_ControlState_set_ElectricalID_FOC_output(uz_ParaID_ControlState_t *self, uz_ParaID_Controller_Parameters_output_t ElectricalID_FOC_output) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ElectricalID_FOC_output = ElectricalID_FOC_output;
}

uz_ParaID_GlobalConfig_t* uz_ControlState_get_GlobalConfig(uz_ParaID_ControlState_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.GlobalConfig_out);
}
uz_ParaID_ControlFlags_t* uz_ControlState_get_ControlFlags(uz_ParaID_ControlState_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.ControlFlags);
 }
#endif
