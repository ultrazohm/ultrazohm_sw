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
#include "uz_ParaID_FluxMapID.h"
#include "../../uz_HAL.h"

struct uz_ParaID_FluxMapID_t{
	bool is_ready;
	ExtY_FluxMapID_t output;
	ExtU_FluxMapID_t input;
	DW_FluxMapID_t rtDW; /* Observable states */
	RT_MODEL_FluxMapID_t modelData;
	RT_MODEL_FluxMapID_t *PtrToModelData;
};

static uint32_t instances_counter_ParaID_FluxMapID = 0;
static uz_ParaID_FluxMapID_t instances_ParaID_FluxMapID[UZ_PARAMETERID_MAX_INSTANCES] = { 0 };

static uz_ParaID_FluxMapID_t* uz_ParaID_FluxMapID_allocation(void);

static uz_ParaID_FluxMapID_t* uz_ParaID_FluxMapID_allocation(void) {
	uz_assert(instances_counter_ParaID_FluxMapID < UZ_PARAMETERID_MAX_INSTANCES);
	uz_ParaID_FluxMapID_t* self = &instances_ParaID_FluxMapID[instances_counter_ParaID_FluxMapID];
	uz_assert_false(self->is_ready);
	instances_counter_ParaID_FluxMapID++;
	self->is_ready = true;
	return (self);
}
uz_ParaID_FluxMapID_t* uz_FluxMapID_init(void) {
	uz_ParaID_FluxMapID_t* self = uz_ParaID_FluxMapID_allocation();
	self->PtrToModelData = &self->modelData;
	self->PtrToModelData->dwork = &self->rtDW;
	self->PtrToModelData->inputs = &self->input;
	self->PtrToModelData->outputs = &self->output;
	FluxMapID_initialize(self->PtrToModelData);
	return (self);
}

void uz_FluxMapID_step(uz_ParaID_FluxMapID_t *self) {
	uz_assert_not_NULL(self);
	FluxMapID_step(self->PtrToModelData);
}

void uz_FluxMapID_set_Config(uz_ParaID_FluxMapID_t *self, uz_ParaID_FluxMapIDConfig_t Config) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.FluxMapIDConfig = Config;
}

void uz_FluxMapID_set_ActualValues(uz_ParaID_FluxMapID_t *self, uz_ParaID_ActualValues_t ActualValues) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ActualValues = ActualValues;
}

void uz_FluxMapID_set_GlobalConfig(uz_ParaID_FluxMapID_t *self, uz_ParaID_GlobalConfig_t GlobalConfig) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.GlobalConfig_out = GlobalConfig;
}

void uz_FluxMapID_set_ControlFlags(uz_ParaID_FluxMapID_t *self, uz_ParaID_ControlFlags_t ControlFlags) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ControlFlags = ControlFlags;
}

bool uz_FluxMapID_get_enteredFluxMapID(uz_ParaID_FluxMapID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->output.enteredFluxMapID);
}
bool uz_FluxMapID_get_finishedFluxMapID(uz_ParaID_FluxMapID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->output.finishedFluxMapID);
}

uz_ParaID_Controller_Parameters_output_t* uz_FluxMapID_get_FOC_output(uz_ParaID_FluxMapID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.FluxMapID_FOC_output);
}

uz_ParaID_FluxMapID_output_t* uz_FluxMapID_get_output(uz_ParaID_FluxMapID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.FluxMapID_output);
}
#endif
