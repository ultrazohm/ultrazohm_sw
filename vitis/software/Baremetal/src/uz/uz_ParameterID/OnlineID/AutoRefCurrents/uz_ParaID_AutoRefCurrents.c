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
#include "../../../uz_global_configuration.h"
#if UZ_PARAMETERID_MAX_INSTANCES > 0U
#include "uz_ParaID_AutoRefCurrents.h"
#include "../../../uz_HAL.h"

struct uz_ParaID_AutoRefCurrents_t{
	bool is_ready;
	ExtY_AutoRefCurrents_t output;
	ExtU_AutoRefCurrents_t input;
	DW_AutoRefCurrents_t rtDW; /* Observable states */
	RT_MODEL_AutoRefCurrents_t modelData;
	RT_MODEL_AutoRefCurrents_t *PtrToModelData;
};

static uint32_t instances_counter_ParaID_AutoRefCurrents = 0;
static uz_ParaID_AutoRefCurrents_t instances_ParaID_AutoRefCurrents[UZ_PARAMETERID_MAX_INSTANCES] = { 0 };

static uz_ParaID_AutoRefCurrents_t* uz_ParaID_AutoRefCurrents_allocation(void);

static uz_ParaID_AutoRefCurrents_t* uz_ParaID_AutoRefCurrents_allocation(void) {
	uz_assert(instances_counter_ParaID_AutoRefCurrents < UZ_PARAMETERID_MAX_INSTANCES);
	uz_ParaID_AutoRefCurrents_t* self = &instances_ParaID_AutoRefCurrents[instances_counter_ParaID_AutoRefCurrents];
	uz_assert_false(self->is_ready);
	instances_counter_ParaID_AutoRefCurrents++;
	self->is_ready = true;
	return (self);
}
uz_ParaID_AutoRefCurrents_t* uz_AutoRefCurrents_init(void) {
	uz_ParaID_AutoRefCurrents_t* self = uz_ParaID_AutoRefCurrents_allocation();
	self->PtrToModelData = &self->modelData;
	self->PtrToModelData->dwork = &self->rtDW;
	self->PtrToModelData->inputs = &self->input;
	self->PtrToModelData->outputs = &self->output;
	AutoRefCurrents_initialize(self->PtrToModelData);
	return (self);
}

void uz_AutoRefCurrents_step(uz_ParaID_AutoRefCurrents_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	AutoRefCurrents_step(self->PtrToModelData);
}

void uz_AutoRefCurrents_set_Config(uz_ParaID_AutoRefCurrents_t *self, uz_ParaID_AutoRefCurrentsConfig_t Config) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.AutoRefCurrentsConfig = Config;
}

void uz_AutoRefCurrents_set_ActualValues(uz_ParaID_AutoRefCurrents_t *self, uz_ParaID_ActualValues_t ActualValues) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ActualValues = ActualValues;
}

void uz_AutoRefCurrents_set_GlobalConfig(uz_ParaID_AutoRefCurrents_t *self, uz_ParaID_GlobalConfig_t GlobalConfig) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.GlobalConfig_out = GlobalConfig;
}

void uz_AutoRefCurrents_set_ControlFlags(uz_ParaID_AutoRefCurrents_t *self, uz_ParaID_ControlFlags_t* ControlFlags) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ControlFlags = *ControlFlags;
}

uz_ParaID_AutoRefCurrents_output_t* uz_AutoRefCurrents_get_output(uz_ParaID_AutoRefCurrents_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.AutoRefCurrents_state_output);
}
#endif
