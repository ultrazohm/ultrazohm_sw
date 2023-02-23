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
#include "uz_ParaID_OnlineID.h"
#include "../../uz_HAL.h"

struct uz_ParaID_OnlineID_t{
	bool is_ready;
	ExtY_OnlineID_t output;
	ExtU_OnlineID_t input;
	DW_OnlineID_t rtDW; /* Observable states */
	RT_MODEL_OnlineID_t modelData;
	RT_MODEL_OnlineID_t *PtrToModelData;
	uz_ParaID_CleanPsiArray_t* CleanPsiArray;
	uz_ParaID_InterpMeshGrid_t* InterpMeshGrid;
	uz_ParaID_AutoRefCurrents_t* AutoRefCurrents;
};

static uint32_t instances_counter_ParaID_OnlineID = 0;

static uz_ParaID_OnlineID_t instances_ParaID_OnlineID[UZ_PARAMETERID_MAX_INSTANCES] = { 0 };

static uz_ParaID_OnlineID_t* uz_ParaID_OnlineID_allocation(void);

static uz_ParaID_OnlineID_t* uz_ParaID_OnlineID_allocation(void) {
	uz_assert(instances_counter_ParaID_OnlineID < UZ_PARAMETERID_MAX_INSTANCES);
	uz_ParaID_OnlineID_t* self = &instances_ParaID_OnlineID[instances_counter_ParaID_OnlineID];
	uz_assert_false(self->is_ready);
	instances_counter_ParaID_OnlineID++;
	self->is_ready = true;
	return (self);
}
uz_ParaID_OnlineID_t* uz_OnlineID_init(void) {
	uz_ParaID_OnlineID_t* self = uz_ParaID_OnlineID_allocation();
	self->PtrToModelData = &self->modelData;
	self->PtrToModelData->dwork = &self->rtDW;
	self->PtrToModelData->inputs = &self->input;
	self->PtrToModelData->outputs = &self->output;
	self->CleanPsiArray = uz_CleanPsiArray_init();
	self->InterpMeshGrid = uz_InterpMeshGrid_init();
	self->AutoRefCurrents = uz_AutoRefCurrents_init();
	OnlineID_initialize(self->PtrToModelData);
	return (self);
}

void uz_OnlineID_step(uz_ParaID_OnlineID_t *self) {
	uz_assert_not_NULL(self);
	OnlineID_step(self->PtrToModelData);
}

void uz_OnlineID_set_Config(uz_ParaID_OnlineID_t *self, uz_ParaID_OnlineIDConfig_t Config) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.OnlineIDConfig = Config;
}

void uz_OnlineID_set_ActualValues(uz_ParaID_OnlineID_t *self, uz_ParaID_ActualValues_t ActualValues) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ActualValues = ActualValues;
}

void uz_OnlineID_set_GlobalConfig(uz_ParaID_OnlineID_t *self, uz_ParaID_GlobalConfig_t GlobalConfig) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.GlobalConfig_out = GlobalConfig;
}

void uz_OnlineID_set_ControlFlags(uz_ParaID_OnlineID_t *self, uz_ParaID_ControlFlags_t* ControlFlags) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ControlFlags = *ControlFlags;
}

void uz_OnlineID_set_cleaned_psi_array(uz_ParaID_OnlineID_t *self, float* array_pointer) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	for(uint32_t i = 0U; i < (sizeof(self->input.cleaned_psi_array)); i++) {
		self->input.cleaned_psi_array[0] = array_pointer[0];
	}
}

bool uz_OnlineID_get_enteredOnlineID(uz_ParaID_OnlineID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->output.enteredOnlineID);
}

uz_ParaID_OnlineID_output_t* uz_OnlineID_get_output(uz_ParaID_OnlineID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.OnlineID_output);
}

void uz_OnlineID_CleanPsiArray(uz_ParaID_OnlineID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert_not_NULL(Data);
	uz_CleanPsiArray_set_OnlineID_output(self->CleanPsiArray, &self->output.OnlineID_output);
	uz_CleanPsiArray_set_eta_c(self->CleanPsiArray, 0.01f * Data->GlobalConfig.ratCurrent);
	uz_CleanPsiArray_step(self->CleanPsiArray);
	if (Data->OnlineID_Config.OnlineID_Reset == false) {
		float* array_pointer = uz_CleanPsiArray_get_psi_array_out(self->CleanPsiArray);
		for (uint32_t i = 0U; i < sizeof(self->input.cleaned_psi_array); i++) {			
			self->input.cleaned_psi_array[0] = array_pointer[0];
		}
	} else {
		memcpy(self->input.cleaned_psi_array, self->output.OnlineID_output.psi_array, sizeof(self->input.cleaned_psi_array));
	}
	Data->OnlineID_Config.array_cleaned = uz_CleanPsiArray_get_array_cleaned_flag(self->CleanPsiArray);
	Data->FluxMap_MeasuringPoints = uz_CleanPsiArray_get_n_flux_points(self->CleanPsiArray);
}

void uz_OnlineID_CalcFluxMaps(uz_ParaID_OnlineID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	uz_assert(self->is_ready);
	uz_InterpMeshGrid_set_psi_array(self->InterpMeshGrid, uz_CleanPsiArray_get_psi_array_out(self->CleanPsiArray));
	uz_InterpMeshGrid_set_i_rat(self->InterpMeshGrid, Data->GlobalConfig.ratCurrent);
	uz_InterpMeshGrid_set_OnlineID_output(self->InterpMeshGrid, &self->output.OnlineID_output);
	uz_InterpMeshGrid_step(self->InterpMeshGrid);
}

void uz_OnlineID_AutoRefCurrents_step(uz_ParaID_OnlineID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	uz_assert(self->is_ready);

	//Update State-Inputs
	uz_AutoRefCurrents_set_ActualValues(self->AutoRefCurrents, Data->ActualValues);
	uz_AutoRefCurrents_set_Config(self->AutoRefCurrents, Data->AutoRefCurrents_Config);

	//Step the function
	uz_AutoRefCurrents_step(self->AutoRefCurrents);

	//Update Data struct with new output values
	Data->AutoRefCurrents_Output = *uz_AutoRefCurrents_get_output(self->AutoRefCurrents);
}

void uz_OnlineID_set_AutoRefCurrents_Config(uz_ParaID_OnlineID_t *self, uz_ParaID_AutoRefCurrentsConfig_t Config) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_AutoRefCurrents_set_Config(self->AutoRefCurrents, Config);
}

void uz_OnlineID_set_AutoRefCurrents_GlobalConfig(uz_ParaID_OnlineID_t *self, uz_ParaID_GlobalConfig_t GlobalConfig) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_AutoRefCurrents_set_GlobalConfig(self->AutoRefCurrents, GlobalConfig);
}

void uz_OnlineID_set_AutoRefCurrents_ControlFlags(uz_ParaID_OnlineID_t *self, uz_ParaID_ControlFlags_t* ControlFlags) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_AutoRefCurrents_set_ControlFlags(self->AutoRefCurrents, ControlFlags);
}

uz_ParaID_FluxMapsData_t* uz_OnlineID_get_InterpMeshGrid_FluxMapData(uz_ParaID_OnlineID_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(uz_InterpMeshGrid_get_FluxMapData(self->InterpMeshGrid));
}
#endif
