/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Valentin Hoppe
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/
#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U
#include "uz_ParaID_ElectricalID_6ph.h"
#include "ElectricalID_6ph_codegen.h"

#include <stdbool.h>
#include "../../uz_HAL.h"

struct uz_ParaID_ElectricalID_6ph_t {
    bool is_ready;
    ExtY_ElectricalID_6ph_codegen_t output;
    ExtU_ElectricalID_6ph_codegen_t input;
    DW_ElectricalID_6ph_codegen_t rtDW;
    RT_MODEL_ElectricalID_6ph_cod_t modelData;
    RT_MODEL_ElectricalID_6ph_cod_t *PtrToModelData;
};

static uint32_t instance_counter = 0U;
static uz_ParaID_ElectricalID_6ph_t instances[UZ_PARAMETERID_6PH_MAX_INSTANCES] = { 0 };

static uz_ParaID_ElectricalID_6ph_t* uz_ElectricalID_6ph_allocation(void);

static uz_ParaID_ElectricalID_6ph_t* uz_ElectricalID_6ph_allocation(void){
    uz_assert(instance_counter < UZ_PARAMETERID_6PH_MAX_INSTANCES);
    uz_ParaID_ElectricalID_6ph_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_ParaID_ElectricalID_6ph_t* uz_ElectricalID_6ph_init(void) {
    uz_ParaID_ElectricalID_6ph_t* self = uz_ElectricalID_6ph_allocation();
    self->PtrToModelData=&self->modelData;
    self->PtrToModelData->dwork=&self->rtDW;
    self->PtrToModelData->inputs=&self->input;
    self->PtrToModelData->outputs=&self->output;
    ElectricalID_6ph_codegen_initialize(self->PtrToModelData);
    return (self);
}

void uz_ElectricalID_6ph_step(uz_ParaID_ElectricalID_6ph_t* self){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    ElectricalID_6ph_codegen_step(self->PtrToModelData);
}

void uz_ElectricalID_6ph_set_Config(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_ElectricalIDConfig_t Config) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ElectricalIDConfig = Config;
}

void uz_ElectricalID_6ph_set_ActualValues(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_ActualValues_t ActualValues) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ActualValues = ActualValues;
}

void uz_ElectricalID_6ph_set_GlobalConfig(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_GlobalConfig_t GlobalConfig) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.GlobalConfig_out = GlobalConfig;
}

void uz_ElectricalID_6ph_set_ControlFlags(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_ControlFlags_t* ControlFlags) {
	uz_assert_not_NULL(self);
    uz_assert_not_NULL(ControlFlags);
	uz_assert(self->is_ready);
	self->input.ControlFlags = *ControlFlags;
}

void uz_ElectricalID_6ph_set_FFT_in(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_ElectricalID_fft_in_t fft_in) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.ElectricalID_fft_in = fft_in;
}

void uz_ElectricalID_6ph_set_Offset_Estimation(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_ElectricalID_offset_estimation_t offset_est_in) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->input.extended_offset_estimation = offset_est_in;
}

bool uz_ElectricalID_6ph_get_entered(uz_ParaID_ElectricalID_6ph_t* self)
{
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    return self->output.enteredElectricalID;
}

bool uz_ElectricalID_6ph_get_finished(uz_ParaID_ElectricalID_6ph_t* self)
{
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    return self->output.finishedElectricalID;
}

bool uz_ElectricalID_6ph_get_finished_voltage_measurement(uz_ParaID_ElectricalID_6ph_t* self)
{
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    return self->output.finished_voltage_measurement;
}

uz_ParaID_Controller_Parameters_output_t* uz_ElectricalID_6ph_get_FOCoutput(uz_ParaID_ElectricalID_6ph_t* self)
{
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.ElectricalID_FOC_output);
}

uz_ParaID_ElectricalID_output_t* uz_ElectricalID_6ph_get_output(uz_ParaID_ElectricalID_6ph_t* self)
{
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.ElectricalID_output);
}

float* uz_ElectricalID_6ph_get_fft_out(uz_ParaID_ElectricalID_6ph_t* self)
{
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
   return(&self->output.voltage_meas_array[0]);
}
#endif
