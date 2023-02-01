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
#include "uz_ParaID_ElectricalID.h"
#include "../../uz_HAL.h"

typedef struct uz_ParaID_ElectricalID_t{
	bool is_ready;
	ExtY_ElectricalID_t output;
	ExtU_ElectricalID_t input;
	DW_ElectricalID_t rtDW; /* Observable states */
	RT_MODEL_ElectricalID_t modelData;
	RT_MODEL_ElectricalID_t *PtrToModelData;
};

static uint32_t instances_counter_ParaID_ElectricalID = 0;
static uz_ParaID_ElectricalID_t instances_ParaID_ElectricalID[UZ_PARAMETERID_MAX_INSTANCES] = { 0 };

static uz_ParaID_ElectricalID_t* uz_ParaID_ElectricalID_allocation(void);

static uz_ParaID_ElectricalID_t* uz_ParaID_ElectricalID_allocation(void) {
	uz_assert(instances_counter_ParaID_ElectricalID < UZ_PARAMETERID_MAX_INSTANCES);
	uz_ParaID_ElectricalID_t* self = &instances_ParaID_ElectricalID[instances_counter_ParaID_ElectricalID];
	instances_counter_ParaID_ElectricalID++;
	return (self);
}
uz_ParaID_ElectricalID_t* uz_ElectricalID_init(void) {
	uz_ParaID_ElectricalID_t* self = uz_ParaID_ElectricalID_allocation();
	self->PtrToModelData = &self->modelData;
	self->PtrToModelData->dwork = &self->rtDW;
	self->PtrToModelData->inputs = &self->input;
	self->PtrToModelData->outputs = &self->output;
	ElectricalID_initialize(self->PtrToModelData);
	return (self);
}

void uz_ElectricalID_step(uz_ParaID_ElectricalID_t *self) {
	uz_assert_not_NULL(self);
	ElectricalID_step(self->PtrToModelData);
}

void uz_ElectricalID_set_Config(uz_ParaID_ElectricalID_t *self, uz_ParaID_ElectricalIDConfig_t Config) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ElectricalIDConfig = Config;
}

void uz_ElectricalID_set_ActualValues(uz_ParaID_ElectricalID_t *self, uz_ParaID_ActualValues_t ActualValues) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ActualValues = ActualValues;
}

void uz_ElectricalID_set_GlobalConfig(uz_ParaID_ElectricalID_t *self, uz_ParaID_GlobalConfig_t GlobalConfig) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.GlobalConfig_out = GlobalConfig;
}

void uz_ElectricalID_set_ControlFlags(uz_ParaID_ElectricalID_t *self, uz_ParaID_ControlFlags_t ControlFlags) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ControlFlags = ControlFlags;
}

bool uz_ElectricalID_get_enteredElectricalID(uz_ParaID_ElectricalID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->output.enteredElectricalID);
}

bool uz_ElectricalID_get_finishedElectricalID(uz_ParaID_ElectricalID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->output.finishedElectricalID);
}

uz_ParaID_Controller_Parameters_output_t* uz_ElectricalID_get_FOC_output(uz_ParaID_ElectricalID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.ElectricalID_FOC_output);
}

uz_ParaID_ElectricalID_output_t* uz_ElectricalID_get_output(uz_ParaID_ElectricalID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.ElectricalID_output);
}

#endif
