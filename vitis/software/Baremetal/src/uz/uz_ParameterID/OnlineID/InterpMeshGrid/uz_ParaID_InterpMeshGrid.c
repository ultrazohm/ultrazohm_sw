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
#include "uz_ParaID_InterpMeshGrid.h"
#include "../../../uz_HAL.h"

struct uz_ParaID_InterpMeshGrid_t {
	bool is_ready;
	ExtY_InterpMeshGrid_t output;
	ExtU_InterpMeshGrid_t input;
	DW_InterpMeshGrid_t rtDW; /* Observable states */
	RT_MODEL_InterpMeshGrid_t modelData;
	RT_MODEL_InterpMeshGrid_t *PtrToModelData;
};

static uint32_t instances_counter_ParaID_InterpMeshGrid = 0;
static uz_ParaID_InterpMeshGrid_t instances_ParaID_InterpMeshGrid[UZ_PARAMETERID_MAX_INSTANCES] = { 0 };

static uz_ParaID_InterpMeshGrid_t* uz_ParaID_InterpMeshGrid_allocation(void);

static uz_ParaID_InterpMeshGrid_t* uz_ParaID_InterpMeshGrid_allocation(void) {
	uz_assert(instances_counter_ParaID_InterpMeshGrid < UZ_PARAMETERID_MAX_INSTANCES);
	uz_ParaID_InterpMeshGrid_t* self = &instances_ParaID_InterpMeshGrid[instances_counter_ParaID_InterpMeshGrid];
	uz_assert_false(self->is_ready);
	instances_counter_ParaID_InterpMeshGrid++;
	self->is_ready = true;
	return (self);
}
uz_ParaID_InterpMeshGrid_t* uz_InterpMeshGrid_init(void) {
	uz_ParaID_InterpMeshGrid_t* self = uz_ParaID_InterpMeshGrid_allocation();
	self->PtrToModelData = &self->modelData;
	self->PtrToModelData->dwork = &self->rtDW;
	self->PtrToModelData->inputs = &self->input;
	self->PtrToModelData->outputs = &self->output;
	InterpMeshGrid_initialize(self->PtrToModelData);
	return (self);
}

void uz_InterpMeshGrid_step(uz_ParaID_InterpMeshGrid_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	InterpMeshGrid_step(self->PtrToModelData);
}

void uz_InterpMeshGrid_set_psi_array(uz_ParaID_InterpMeshGrid_t *self, float* psi_array_pointer) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	for (uint32_t i = 0U; i < sizeof(self->input.psi_array_in); i++) {
		self->input.psi_array_in[i] = psi_array_pointer[i];
	}
}

void uz_InterpMeshGrid_set_i_rat(uz_ParaID_InterpMeshGrid_t *self, float i_rat) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.i_rat = i_rat;
}

void uz_InterpMeshGrid_set_OnlineID_output(uz_ParaID_InterpMeshGrid_t *self, uz_ParaID_OnlineID_output_t* OnlineID_input) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.OnlineID_input = *OnlineID_input;
}

float* uz_InterpMeshGrid_test(uz_ParaID_InterpMeshGrid_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->input.psi_array_in[0]);
}

uz_ParaID_FluxMapsData_t* uz_InterpMeshGrid_get_FluxMapData(uz_ParaID_InterpMeshGrid_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.FluxMapData);
}
#endif
