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

void uz_ParameterID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t Data) {

	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	if (Data.PID_GlobalConifg.ElectricalID == true && Data.PID_GlobalConifg.Reset == false) {
		//Update State-Inputs
		self->ElectricalID->input.ActualValues = Data.PID_ActualValues;
		self->ElectricalID->input.ElectricalIDConfig = Data.PID_ElectricalID_Config;
		self->ElectricalID->input.GlobalConfig_out = Data.PID_GlobalConifg;
		self->ElectricalID->input.ControlFlags = self->ControlState->output.ControlFlags;

		//Step the function
		uz_PID_ElectricalID_step(self->ElectricalID);

		//Update Control-State-inputs
		self->ControlState->input.ElectricalID_FOC_output = self->ElectricalID->output.ElectricalID_FOC_output;
		self->ControlState->input.ElectricalID_output = self->ElectricalID->output.ElectricalID_output;
		self->ControlState->input.enteredElectricalID = self->ElectricalID->output.enteredElectricalID;
		self->ControlState->input.finishedElectricalID = self->ElectricalID->output.finishedElectricalID;

		//Update values for Controller
		Data.PID_Controller_Parameters = self->ElectricalID->output.ElectricalID_FOC_output;

	} else if (Data.PID_GlobalConifg.ElectricalID == false) {
		self->ElectricalID->input.GlobalConfig_out.ElectricalID = false;
		uz_PID_ElectricalID_step(self->ElectricalID);
	} else if (Data.PID_GlobalConifg.Reset == true) {
		self->ElectricalID->input.GlobalConfig_out.Reset = true;
		uz_PID_ElectricalID_step(self->ElectricalID);
	}

	//Update Control-State inputs, which are not depended on other states
	self->ControlState->input.GlobalConfig_in = Data.PID_GlobalConifg;

	//Control-State will always be stepped
	uz_PID_ControlState_step(self->ControlState);
}

struct uz_DutyCycle_t uz_ParameterID_Controller(uz_ParameterID_Data_t Data, uz_FOC* FOC_instance, uz_PI_Controller* Speed_instance) {
	struct uz_DutyCycle_t output_DutyCycle = { 0 };
	uz_dq_t u_dq_Volts = { 0 };
	uz_dq_t i_SpeedControl_reference_Ampere = { 0 };

	if (Data.PID_Controller_Parameters.enableFOC_speed == true) {
		bool ext_clamping = uz_FOC_get_ext_clamping(FOC_instance);
		i_SpeedControl_reference_Ampere = uz_SpeedControl_sample(Speed_instance, Data.PID_ActualValues.omega_el, Data.PID_Controller_Parameters.n_ref_FOC, Data.PID_ActualValues.U_zk,
		                Data.PID_Controller_Parameters.i_dq_ref.d, Data.PID_GlobalConifg.PMSM_config, ext_clamping);
	} else if (Data.PID_Controller_Parameters.enableFOC_current || Data.PID_Controller_Parameters.enableFOC_speed == true) {

		if (Data.PID_Controller_Parameters.enableFOC_current == true) {
			u_dq_Volts = uz_FOC_sample(FOC_instance, Data.PID_Controller_Parameters.i_dq_ref, Data.PID_ActualValues.i_dq, Data.PID_ActualValues.U_zk, Data.PID_ActualValues.omega_el);
		}

		if (Data.PID_Controller_Parameters.enableFOC_current == true) {
			u_dq_Volts = uz_FOC_sample(FOC_instance, i_SpeedControl_reference_Ampere, Data.PID_ActualValues.i_dq, Data.PID_ActualValues.U_zk, Data.PID_ActualValues.omega_el);
		}
		uz_UVW_t U_UVW_Volts = uz_dq_inverse_transformation(u_dq_Volts, Data.PID_ActualValues.theta_el);
		output_DutyCycle = uz_FOC_generate_DutyCycles(U_UVW_Volts, Data.PID_ActualValues.U_zk);
	} else if (Data.PID_Controller_Parameters.resetIntegrator == true) {
		uz_FOC_reset(FOC_instance);
		uz_SpeedControl_reset(Speed_instance);
	}
	uz_FOC_set_Kp_id(FOC_instance, Data.PID_GlobalConifg.Kp_id);
	uz_FOC_set_Kp_iq(FOC_instance, Data.PID_GlobalConifg.Kp_iq);
	uz_FOC_set_Ki_id(FOC_instance, Data.PID_GlobalConifg.Ki_id);
	uz_FOC_set_Ki_iq(FOC_instance, Data.PID_GlobalConifg.Ki_iq);



	return (output_DutyCycle);
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
	output.PID_GlobalConifg.VibAmp = 0.0f;
	output.PID_GlobalConifg.VibFreq = 0U;
	output.PID_GlobalConifg.VibOn = false;
	output.PID_GlobalConifg.controlType = 0.0f;
	output.PID_GlobalConifg.thetaOffset = 0.0f;
	output.PID_GlobalConifg.sampleTimeISR = 50.0e-06f;

	//Initialize motor-related parameters inside Global-Config
	//Motor Buehler 1.25.058.201
	output.PID_GlobalConifg.Ki_id = 158.8f;
	output.PID_GlobalConifg.Ki_iq = 158.8f;
	output.PID_GlobalConifg.Ki_n = 0.8f;
	output.PID_GlobalConifg.Kp_id = 0.54f;
	output.PID_GlobalConifg.Kp_iq = 0.54f;
	output.PID_GlobalConifg.Kp_n = 0.08f;
	output.PID_GlobalConifg.PMSM_config.Ld_Henry = 2.90e-04f;
	output.PID_GlobalConifg.PMSM_config.Lq_Henry = 3.00e-04f;
	output.PID_GlobalConifg.PMSM_config.R_ph_Ohm = 0.085f;
	output.PID_GlobalConifg.PMSM_config.Psi_PM_Vs = 0.0075f;
	output.PID_GlobalConifg.PMSM_config.polePairs = 4.0f;
	output.PID_GlobalConifg.ratCurrent = 8.0f;
	output.PID_GlobalConifg.ratSpeed = 3000.0f;

	//Initialize ElectricalID-Config
	output.PID_ElectricalID_Config.dutyCyc = 0.0f;
	output.PID_ElectricalID_Config.goertzlAmp = 0.0f;
	output.PID_ElectricalID_Config.identLq = false;
	output.PID_ElectricalID_Config.min_n_ratio = 0.0f;
	output.PID_ElectricalID_Config.n_ref_measurement = 0.0f;

	return (output);
}

#endif
