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
#include "uz_ParameterID_6ph.h"
#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U
#include <math.h>
#include "../uz_HAL.h"
#include <stdbool.h>

typedef struct uz_ParameterID_6ph_t {
	bool is_ready;
	uz_ParaID_ControlState_t* ControlState;
	uz_ParaID_ElectricalID_6ph_t* ElectricalID;
	uz_ParaID_TwoMassID_t* TwoMassID;
	uz_ParaID_FrictionID_t* FrictionID;
	uz_ParaID_FluxMapID_t* FluxMapID;
	uz_ParaID_OnlineID_t* OnlineID;
} uz_ParameterID_6ph_t;

static uint32_t instances_counter_ParameterID_6ph = 0;
static uz_ParameterID_6ph_t instances_ParameterID_6ph[UZ_PARAMETERID_6PH_MAX_INSTANCES] = { 0 };

static void uz_ParaID_6ph_ControlState_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_6ph_ElectricalID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_6ph_FrictionID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_6ph_TwoMassID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParameterID_6ph_initialize_data_structs(uz_ParameterID_6ph_t *self, uz_ParameterID_Data_t *Data);

static uz_ParameterID_6ph_t* uz_ParameterID_6ph_allocation(void);

static uz_ParameterID_6ph_t* uz_ParameterID_6ph_allocation(void) {
	uz_assert(instances_counter_ParameterID_6ph < UZ_PARAMETERID_6PH_MAX_INSTANCES);
	uz_ParameterID_6ph_t* self = &instances_ParameterID_6ph[instances_counter_ParameterID_6ph];
	uz_assert(self->is_ready == false);
	instances_counter_ParameterID_6ph++;
	self->is_ready = true;
	return (self);
}

uz_ParameterID_6ph_t* uz_ParameterID_6ph_init(uz_ParameterID_Data_t *Data) {
	uz_assert_not_NULL(Data);
	uz_ParameterID_6ph_t* self = uz_ParameterID_6ph_allocation();
	self->ControlState = uz_ControlState_init();
	self->ElectricalID = uz_ElectricalID_6ph_init();
	self->TwoMassID = uz_TwoMassID_init();
	self->FrictionID = uz_FrictionID_init();
	uz_ParameterID_6ph_initialize_data_structs(self, Data);
	return (self);
}

void uz_ParameterID_6ph_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	uz_assert(self->is_ready);
	uz_ParaID_6ph_ControlState_step(self, Data);

	//All Offline states
	if (self->ControlState->output.ControlFlags.finished_all_Offline_states == false) {

		//ElectricalID
		if (self->ControlState->output.ControlFlags.transNr == 1U || self->ControlState->output.GlobalConfig_out.Reset == true) {
			uz_ParaID_6ph_ElectricalID_step(self, Data);
		} else if (self->ControlState->output.GlobalConfig_out.ElectricalID == false && self->ControlState->input.enteredElectricalID == true) {
			uz_ParaID_6ph_ElectricalID_step(self, Data);
		}

		//TwoMassID
		if (self->ControlState->output.ControlFlags.transNr == 2U || self->ControlState->output.GlobalConfig_out.Reset == true) {
			uz_ParaID_6ph_TwoMassID_step(self, Data);
		} else if (self->ControlState->output.GlobalConfig_out.TwoMassID == false && self->TwoMassID->output.enteredTwoMassID == true) {
			uz_ParaID_6ph_TwoMassID_step(self, Data);
		}

		//FrictionID
		if (self->ControlState->output.ControlFlags.transNr == 3U || self->ControlState->output.GlobalConfig_out.Reset == true) {
			uz_ParaID_6ph_FrictionID_step(self, Data);
			if (Data->Array_counter < 256 && (Data->Array_counter == Data->Array_Control_counter)) {
				Data->Array_counter += 1;
			} else if (Data->Array_counter == 256){
				Data->Array_counter = 0;
			}
		} else if (self->ControlState->output.GlobalConfig_out.FrictionID == false && self->FrictionID->output.enteredFrictionID == true) {
			uz_ParaID_6ph_FrictionID_step(self, Data);
		}

	}

	//FOC output
	switch (self->ControlState->output.ControlFlags.transNr) {
	case 1U:
		Data->Controller_Parameters = uz_get_ElectricalID_6ph_FOCoutput(self->ElectricalID);
		break;
	case 2U:
		Data->Controller_Parameters = self->TwoMassID->output.TwoMassID_FOC_output;
		break;
	case 3U:
		Data->Controller_Parameters = self->FrictionID->output.FrictionID_FOC_output;
		break;
	default:
		break;
	}


	//RESET
	if (Data->GlobalConfig.Reset == true) {

		//reset the Reset-button
		self->ControlState->output.GlobalConfig_out.Reset = false;
		Data->GlobalConfig.Reset = false;
		self->OnlineID->AutoRefCurrents->input.AutoRefCurrentsConfig.Reset = false;
		Data->AutoRefCurrents_Config.Reset = false;
	}
	if (Data->OnlineID_Config.OnlineID_Reset) {
		Data->OnlineID_Config.OnlineID_Reset = false;
		Data->AutoRefCurrents_Config.Reset = false;
	}

	// reset ACCEPT
	if (self->ControlState->output.GlobalConfig_out.ACCEPT == true) {
		self->ControlState->output.GlobalConfig_out.ACCEPT = false;
		Data->GlobalConfig.ACCEPT = false;
	}
}

static void uz_ParaID_6ph_ElectricalID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Step the function
	uz_ElectricalID_6ph_step(self->ElectricalID,Data->ElectricalID_Config,Data->ActualValues,Data->GlobalConfig,*Data->ControlFlags);

	//Update Control-State-inputs
	self->ControlState->input.ElectricalID_FOC_output = uz_get_ElectricalID_6ph_FOCoutput(self->ElectricalID);
	self->ControlState->input.ElectricalID_output = uz_get_ElectricalID_6ph_output(self->ElectricalID);
	self->ControlState->input.enteredElectricalID = uz_get_ElectricalID_6ph_entered(self->ElectricalID);
	self->ControlState->input.finishedElectricalID = uz_get_ElectricalID_6ph_finished(self->ElectricalID);
}

static void uz_ParaID_6ph_ControlState_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Update Control-State inputs, which are not depended on other states
	self->ControlState->input.GlobalConfig_in = Data->GlobalConfig;

	//Control-State will always be stepped
	uz_ControlState_step(self->ControlState);
}

static void uz_ParaID_6ph_FrictionID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Update State-Inputs
	self->FrictionID->input.ActualValues = Data->ActualValues;
	self->FrictionID->input.FrictionConfigID = Data->FrictionID_Config;
	self->FrictionID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
	self->FrictionID->input.ControlFlags = self->ControlState->output.ControlFlags;

	//Step the function
	uz_FrictionID_step(self->FrictionID);

	//Update Control-State-inputs
	self->ControlState->input.enteredFrictionID = self->FrictionID->output.enteredFrictionID;
	self->ControlState->input.finishedFrictionID = self->FrictionID->output.finishedFrictionID;
}

static void uz_ParaID_6ph_TwoMassID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Update State-Inputs
	self->TwoMassID->input.ActualValues = Data->ActualValues;
	self->TwoMassID->input.TwoMassIDConfig = Data->TwoMassID_Config;
	self->TwoMassID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
	self->TwoMassID->input.ControlFlags = self->ControlState->output.ControlFlags;

	//Step the function
	uz_TwoMassID_step(self->TwoMassID);

	//Update Control-State-inputs
	self->ControlState->input.enteredTwoMassID = self->TwoMassID->output.enteredTwoMassID;
	self->ControlState->input.finishedTwoMassID = self->TwoMassID->output.finishedTwoMassID;
}


static void uz_ParameterID_6ph_initialize_data_structs(uz_ParameterID_6ph_t *self, uz_ParameterID_Data_t *Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Initialize Global-Config
	Data->GlobalConfig.ACCEPT = false;
	Data->GlobalConfig.Reset = false;
	Data->GlobalConfig.enableParameterID = false;
	Data->GlobalConfig.ElectricalID = false;
	Data->GlobalConfig.FluxMapID = false;
	Data->GlobalConfig.FrictionID = false;
	Data->GlobalConfig.TwoMassID = false;
	Data->GlobalConfig.OnlineID = false;
	Data->GlobalConfig.sampleTimeISR = 50.0e-06f;

	//Initialize motor-related parameters inside Global-Config
	Data->GlobalConfig.Ki_id = 158.8f;
	Data->GlobalConfig.Ki_iq = 158.8f;
	Data->GlobalConfig.Ki_n = 0.8f;
	Data->GlobalConfig.Kp_id = 0.25;
	Data->GlobalConfig.Kp_iq = 0.25f;
	Data->GlobalConfig.Kp_n = 0.04f;
	Data->GlobalConfig.PMSM_config.Ld_Henry = 2.90e-04f;
	Data->GlobalConfig.PMSM_config.Lq_Henry = 3.00e-04f;
	Data->GlobalConfig.PMSM_config.R_ph_Ohm = 0.105f;
	Data->GlobalConfig.PMSM_config.Psi_PM_Vs = 0.0075f;
	Data->GlobalConfig.PMSM_config.polePairs = 4.0f;
	Data->GlobalConfig.PMSM_config.J_kg_m_squared = 3.24e-05f;
	Data->GlobalConfig.PMSM_config.I_max_Ampere = 15.0f;
	Data->GlobalConfig.ratCurrent = 8.0f;
	Data->GlobalConfig.ratTorque = 0.29f;
	Data->GlobalConfig.ratSpeed = 3000.0f;

	//Initialize ElectricalID-Config
	Data->ElectricalID_Config.goertzlFreq = 0.0f;
	Data->ElectricalID_Config.dutyCyc = 0.0f;
	Data->ElectricalID_Config.goertzlTorque= 0.0f;
	Data->ElectricalID_Config.identLq = false;
	Data->ElectricalID_Config.min_n_ratio = 0.015f;
	Data->ElectricalID_Config.n_ref_measurement = 0.0f;

	//Initialize FluxMapID-Config
	Data->FluxMapID_Config.AMMsampleTime = 2.0f;
	Data->FluxMapID_Config.IDstart = 0.0f;
	Data->FluxMapID_Config.IDstepsize = 0.0f;
	Data->FluxMapID_Config.IDstop = 0.0f;
	Data->FluxMapID_Config.IQstart = 0.0f;
	Data->FluxMapID_Config.IQstepsize = 0.0f;
	Data->FluxMapID_Config.IQstop = 0.0f;
	Data->FluxMapID_Config.R_s_ref = 0.0f;
	Data->FluxMapID_Config.Temp_ref = 0.0f;
	Data->FluxMapID_Config.identR = false;
	Data->FluxMapID_Config.identRAmp = 0.0f;
	Data->FluxMapID_Config.start_FM_ID = false;

	//Initialize FrictionID-Config
	Data->FrictionID_Config.BrkCount = 0.0f;
	Data->FrictionID_Config.N_Brk = 0.0f;
	Data->FrictionID_Config.N_Visco = 0.0f;
	Data->FrictionID_Config.StepScale = 0.0f;
	Data->FrictionID_Config.eta = 0.0f;
	Data->FrictionID_Config.maxCurrent = 10.0f;
	Data->FrictionID_Config.n_eva_max = 0.0f;

	//Initialize OnlineID-Config
	Data->OnlineID_Config.AverageTransParams = true;
	Data->OnlineID_Config.OnlineID_Reset = false;
	Data->OnlineID_Config.Rs_time = 0.0f;
	Data->OnlineID_Config.Temp_ref = 0.0f;
	Data->OnlineID_Config.allowPsiCalcOutside = false;
	Data->OnlineID_Config.dev_curr = 0.05f;
	Data->OnlineID_Config.dev_omega = 0.05f;
	Data->OnlineID_Config.identRAmp = 2.0f;
	Data->OnlineID_Config.max_n_ratio = 0.0f;
	Data->OnlineID_Config.min_n_ratio = 0.0f;
	Data->OnlineID_Config.nom_factor = 0.0f;
	Data->OnlineID_Config.array_cleaned = false;

	//Initialize Output data structs
	Data->ElectricalID_Output = uz_get_ElectricalID_6ph_output(self->ElectricalID);
	Data->FrictionID_Output = &self->FrictionID->output.FrictionID_output;
	//Data->FluxMapID_Output = &self->FluxMapID->output.FluxMapID_output;
	Data->TwoMassID_Output = &self->TwoMassID->output.TwoMassID_output;
	//Data->OnlineID_Output = &self->OnlineID->output.OnlineID_output;
	Data->ControlFlags = &self->ControlState->output.ControlFlags;
	//Data->FluxMap_Data = &self->OnlineID->InterpMeshGrid->output.FluxMapData;

	Data->calculate_flux_maps = false;
	Data->FluxMap_counter = 0.0f;
	Data->Psi_D_pointer = 0.0f;
	Data->Psi_Q_pointer = 0.0f;
	Data->ParaID_Control_Selection = No_Control;
}

#endif
