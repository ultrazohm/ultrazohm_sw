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
#include "uz_ParameterID.h"
#include "../uz_global_configuration.h"

#if UZ_PARAMETERID_ACTIVE > 0U

void uz_ParameterID_init(uz_ParameterID_t* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready == false);
	uz_PID_ControlState_init(self->ControlState);
	uz_PID_ElectricalID_init(self->ElectricalID);
	self->is_ready = true;
}

uz_PID_GlobalConfig_t PID_GlobalConfig;

void uz_ParameterID_step(uz_ParameterID_t* self, uz_PID_GlobalConfig_t GlobalConfig, uz_PID_ActualValues_t ActualValues, uz_PID_ElectricalIDConfig_t ElectricalIDConfig) {

	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	if (GlobalConfig.ElectricalID == true && GlobalConfig.Reset == false) {
		//Update State-Inputs
		self->ElectricalID->input.ActualValues = ActualValues;
		self->ElectricalID->input.ElectricalIDConfig = ElectricalIDConfig;
		self->ElectricalID->input.GlobalConfig_out = GlobalConfig;
		self->ElectricalID->input.ControlFlags = self->ControlState->output.ControlFlags;

		//Step the function
		uz_PID_ElectricalID_step(self->ElectricalID);

		//Update Control-State-inputs
		self->ControlState->input.ElectricalID_FOC_output = self->ElectricalID->output.ElectricalID_FOC_output;
		self->ControlState->input.ElectricalID_output = self->ElectricalID->output.ElectricalID_output;
		self->ControlState->input.enteredElectricalID = self->ElectricalID->output.enteredElectricalID;
		self->ControlState->input.finishedElectricalID = self->ElectricalID->output.finishedElectricalID;
	} else if (GlobalConfig.ElectricalID == false) {
		self->ElectricalID->input.GlobalConfig_out.ElectricalID = false;
		uz_PID_ElectricalID_step(self->ElectricalID);
	} else if (GlobalConfig.Reset == true) {
		self->ElectricalID->input.GlobalConfig_out.Reset = true;
		uz_PID_ElectricalID_step(self->ElectricalID);
	}

	//Update Control-State inputs, which are not depended on other states
	self->ControlState->input.GlobalConfig_in = GlobalConfig;

	//Control-State will always be stepped
	uz_PID_ControlState_step(self->ControlState);
}

uz_ParameterID_Data_t uz_ParameterID_initialize_data_structs(void) {
	uz_ParameterID_Data_t output = { 0 };

	//Initialize Global-Config
	output.PID_GlobalConifg.ACCEPT = false;
	output.PID_GlobalConifg.Reset = false;
	output.PID_GlobalConifg.ElectricalID = false;
	output.PID_GlobalConifg.FluxMapID = false;
	output.PID_GlobalConifg.FrictionID = false;
	output.PID_GlobalConifg.TwoMassID = false;
	output.PID_GlobalConifg.OnlineID = false;
	output.PID_GlobalConifg.Ki_id = 0.0f;
	output.PID_GlobalConifg.Ki_iq = 0.0f;
	output.PID_GlobalConifg.Ki_n = 0.0f;
	output.PID_GlobalConifg.Kp_id = 0.0f;
	output.PID_GlobalConifg.Kp_iq = 0.0f;
	output.PID_GlobalConifg.Kp_n = 0.0f;
	output.PID_GlobalConifg.L_d = 0.0f;
	output.PID_GlobalConifg.L_q = 0.0f;
	output.PID_GlobalConifg.R_ph = 0.0f;
	output.PID_GlobalConifg.psi_pm = 0.0f;
	output.PID_GlobalConifg.polePairs = 0.0f;
	output.PID_GlobalConifg.ratCurrent = 0.0f;
	output.PID_GlobalConifg.ratSpeed = 0.0f;
	output.PID_GlobalConifg.VibAmp = 0.0f;
	output.PID_GlobalConifg.VibFreq = 0U;
	output.PID_GlobalConifg.VibOn = false;
	output.PID_GlobalConifg.controlType = 0.0f;
	output.PID_GlobalConifg.thetaOffset = 0.0f;
	output.PID_GlobalConifg.sampleTimeISR = 0.0f;
	return (output);
}

#endif
