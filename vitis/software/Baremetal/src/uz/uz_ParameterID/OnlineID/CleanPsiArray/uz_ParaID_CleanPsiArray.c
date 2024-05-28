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
#include "uz_ParaID_CleanPsiArray.h"
#include "../../../uz_HAL.h"

struct uz_ParaID_CleanPsiArray_t {
	bool is_ready;
	ExtY_CleanPsiArray_t output;
	ExtU_CleanPsiArray_t input;
	DW_CleanPsiArray_t rtDW; /* Observable states */
	RT_MODEL_CleanPsiArray_t modelData;
	RT_MODEL_CleanPsiArray_t *PtrToModelData;
};

static uint32_t instances_counter_ParaID_CleanPsiArray = 0;
static uz_ParaID_CleanPsiArray_t instances_ParaID_CleanPsiArray[UZ_PARAMETERID_MAX_INSTANCES] = { 0 };

static uz_ParaID_CleanPsiArray_t* uz_ParaID_CleanPsiArray_allocation(void);

static uz_ParaID_CleanPsiArray_t* uz_ParaID_CleanPsiArray_allocation(void) {
	uz_assert(instances_counter_ParaID_CleanPsiArray < UZ_PARAMETERID_MAX_INSTANCES);
	uz_ParaID_CleanPsiArray_t* self = &instances_ParaID_CleanPsiArray[instances_counter_ParaID_CleanPsiArray];
	uz_assert_false(self->is_ready);
	instances_counter_ParaID_CleanPsiArray++;
	self->is_ready = true;
	return (self);
}
uz_ParaID_CleanPsiArray_t* uz_CleanPsiArray_init(void) {
	uz_ParaID_CleanPsiArray_t* self = uz_ParaID_CleanPsiArray_allocation();
	self->PtrToModelData = &self->modelData;
	self->PtrToModelData->dwork = &self->rtDW;
	self->PtrToModelData->inputs = &self->input;
	self->PtrToModelData->outputs = &self->output;
	CleanPsiArray_initialize(self->PtrToModelData);
	return (self);
}

void uz_CleanPsiArray_step(uz_ParaID_CleanPsiArray_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	CleanPsiArray_step(self->PtrToModelData);
}

void uz_CleanPsiArray_set_OnlineID_output(uz_ParaID_CleanPsiArray_t* self, uz_ParaID_OnlineID_output_t* OnlineID_output) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.OnlineID_output = *OnlineID_output;
}

void uz_CleanPsiArray_set_eta_c(uz_ParaID_CleanPsiArray_t* self, float eta_c) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.eta_c = eta_c;
}

float* uz_CleanPsiArray_get_psi_array_out(uz_ParaID_CleanPsiArray_t* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->output.psi_array_out);
}

bool uz_CleanPsiArray_get_array_cleaned_flag(uz_ParaID_CleanPsiArray_t* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->output.array_cleaned_flag);
}

float uz_CleanPsiArray_get_n_flux_points(uz_ParaID_CleanPsiArray_t* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->output.n_flux_points);
}
#endif
