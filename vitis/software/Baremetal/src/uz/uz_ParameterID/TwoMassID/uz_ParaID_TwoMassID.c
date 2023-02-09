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
#include "uz_ParaID_TwoMassID.h"
#include "../../uz_HAL.h"

struct uz_ParaID_TwoMassID_t{
	bool is_ready;
	ExtY_TwoMassID_t output;
	ExtU_TwoMassID_t input;
	DW_TwoMassID_t rtDW; /* Observable states */
	RT_MODEL_TwoMassID_t modelData;
	RT_MODEL_TwoMassID_t *PtrToModelData;
};

static uint32_t instances_counter_ParaID_TwoMassID = 0;
static uz_ParaID_TwoMassID_t instances_ParaID_TwoMassID[UZ_PARAMETERID_MAX_INSTANCES] = { 0 };

static uz_ParaID_TwoMassID_t* uz_ParaID_TwoMassID_allocation(void);

static uz_ParaID_TwoMassID_t* uz_ParaID_TwoMassID_allocation(void) {
	uz_assert(instances_counter_ParaID_TwoMassID < UZ_PARAMETERID_MAX_INSTANCES);
	uz_ParaID_TwoMassID_t* self = &instances_ParaID_TwoMassID[instances_counter_ParaID_TwoMassID];
	uz_assert_false(self->is_ready);
	instances_counter_ParaID_TwoMassID++;
	self->is_ready = true;
	return (self);
}
uz_ParaID_TwoMassID_t* uz_TwoMassID_init(void) {
	uz_ParaID_TwoMassID_t* self = uz_ParaID_TwoMassID_allocation();
	self->PtrToModelData = &self->modelData;
	self->PtrToModelData->dwork = &self->rtDW;
	self->PtrToModelData->inputs = &self->input;
	self->PtrToModelData->outputs = &self->output;
	TwoMassID_initialize(self->PtrToModelData);
	return (self);
}

void uz_TwoMassID_step(uz_ParaID_TwoMassID_t *self) {
	uz_assert_not_NULL(self);
	TwoMassID_step(self->PtrToModelData);
}

void uz_TwoMassID_set_Config(uz_ParaID_TwoMassID_t *self, uz_ParaID_TwoMassIDConfig_t Config) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.TwoMassIDConfig = Config;
}

void uz_TwoMassID_set_ActualValues(uz_ParaID_TwoMassID_t *self, uz_ParaID_ActualValues_t ActualValues) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ActualValues = ActualValues;
}

void uz_TwoMassID_set_GlobalConfig(uz_ParaID_TwoMassID_t *self, uz_ParaID_GlobalConfig_t GlobalConfig) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.GlobalConfig_out = GlobalConfig;
}

void uz_TwoMassID_set_ControlFlags(uz_ParaID_TwoMassID_t *self, uz_ParaID_ControlFlags_t* ControlFlags) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ControlFlags = *ControlFlags;
}

bool uz_TwoMassID_get_enteredTwoMassID(uz_ParaID_TwoMassID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->output.enteredTwoMassID);
}

bool uz_TwoMassID_get_finishedTwoMassID(uz_ParaID_TwoMassID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->output.finishedTwoMassID);
}

uz_ParaID_Controller_Parameters_output_t* uz_TwoMassID_get_FOC_output(uz_ParaID_TwoMassID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.TwoMassID_FOC_output);
}

uz_ParaID_TwoMassID_output_t* uz_TwoMassID_get_output(uz_ParaID_TwoMassID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.TwoMassID_output);
}

#endif
