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
#include "../uz_wavegen/uz_wavegen.h"
#include "../../include/pwm.h"

#if UZ_PARAMETERID_ACTIVE > 0U

void uz_ParameterID_init(uz_ParameterID_t* self) {
	uz_assert(self->is_ready == false);
	uz_PID_ControlState_init(self->ControlState);
	uz_PID_ElectricalID_init(self->ElectricalID);
	uz_PID_FluxMapID_init(self->FluxMapID);
	self->is_ready = true;
}

uz_PID_GlobalConfig_t PID_GlobalConfig;

uz_ParameterID_Data_t uz_ParameterID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t Data) {

	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);

	//Update Control-State inputs, which are not depended on other states
	self->ControlState->input.GlobalConfig_in = Data.PID_GlobalConfig;

	//Control-State will always be stepped
	uz_PID_ControlState_step(self->ControlState);

	//Update Data-Struct with Control-State outputs
	Data.PID_ControlFlags = self->ControlState->output.ControlFlags;

	//ElectricalID
	if (self->ControlState->output.GlobalConfig_out.ElectricalID == true && self->ControlState->output.GlobalConfig_out.Reset == false && self->ControlState->output.ControlFlags.transNr == 1U) {
		//Update State-Inputs
		self->ElectricalID->input.ActualValues = Data.PID_ActualValues;
		self->ElectricalID->input.ElectricalIDConfig = Data.PID_ElectricalID_Config;
		self->ElectricalID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
		self->ElectricalID->input.ControlFlags = self->ControlState->output.ControlFlags;

		//Step the function
		uz_PID_ElectricalID_step(self->ElectricalID);

		//Update Control-State-inputs
		self->ControlState->input.ElectricalID_FOC_output = self->ElectricalID->output.ElectricalID_FOC_output;
		self->ControlState->input.ElectricalID_output = self->ElectricalID->output.ElectricalID_output;
		self->ControlState->input.enteredElectricalID = self->ElectricalID->output.enteredElectricalID;
		self->ControlState->input.finishedElectricalID = self->ElectricalID->output.finishedElectricalID;

		//Update Data struct with new output values
		Data.PID_Controller_Parameters = self->ElectricalID->output.ElectricalID_FOC_output;
		Data.PID_ElectricalID_Output = self->ElectricalID->output.ElectricalID_output;
		Data.PID_GlobalConfig.thetaOffset = self->ElectricalID->output.ElectricalID_output.thetaOffset;


	} else if (self->ControlState->output.GlobalConfig_out.ElectricalID == false && self->ElectricalID->output.enteredElectricalID == true) {
		self->ElectricalID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
		uz_PID_ElectricalID_step(self->ElectricalID);
	} else if (self->ControlState->output.GlobalConfig_out.Reset == true) {
		self->ElectricalID->input.GlobalConfig_out.Reset = true;
		uz_PID_ElectricalID_step(self->ElectricalID);
	}

	//FluxMapID
	if (self->ControlState->output.GlobalConfig_out.FluxMapID == true && self->ControlState->output.GlobalConfig_out.Reset == false && self->ControlState->output.ControlFlags.transNr == 4U) {
		//Update State-Inputs
		self->FluxMapID->input.ActualValues = Data.PID_ActualValues;
		self->FluxMapID->input.FluxMapIDConfig = Data.PID_FluxMapID_Config;
		self->FluxMapID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
		self->FluxMapID->input.ControlFlags = self->ControlState->output.ControlFlags;

		//Step the function
		uz_PID_FluxMapID_step(self->FluxMapID);

		//Update Control-State-inputs
		self->ControlState->input.enteredFluxMapID = self->FluxMapID->output.enteredFluxMapID;
		self->ControlState->input.finishedFluxMapID = self->FluxMapID->output.finishedFluxMapID;

		//Update Data struct with new output values
		Data.PID_Controller_Parameters = self->FluxMapID->output.FluxMapID_FOC_output;
		Data.PID_FluxMapID_Output = self->FluxMapID->output.FluxMapID_output;
	} else if (self->ControlState->output.GlobalConfig_out.FluxMapID == false && self->FluxMapID->output.enteredFluxMapID == true) {
		self->FluxMapID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
		uz_PID_FluxMapID_step(self->FluxMapID);
	} else if (self->ControlState->output.GlobalConfig_out.Reset == true) {
		self->FluxMapID->input.GlobalConfig_out.Reset = true;
		uz_PID_FluxMapID_step(self->FluxMapID);
	}

	// reset ACCEPT
	if (self->ControlState->output.GlobalConfig_out.ACCEPT == true) {
		self->ControlState->output.GlobalConfig_out.ACCEPT = false;
		Data.PID_GlobalConfig.ACCEPT = false;
	}

	// reset RESET-button
	if (Data.PID_GlobalConfig.Reset == true) {
		self->ControlState->output.GlobalConfig_out.ACCEPT = false;
		Data.PID_GlobalConfig.Reset = false;
	}
	return (Data);

}

//struct uz_DutyCycle_t uz_ParameterID_Controller(uz_ParameterID_Data_t Data, uz_FOC* FOC_instance, uz_PI_Controller* Speed_instance) {
struct uz_dq_t uz_ParameterID_Controller(uz_ParameterID_Data_t Data, uz_FOC* FOC_instance, uz_PI_Controller* Speed_instance) {
	struct uz_DutyCycle_t output_DutyCycle = { 0 };
	uz_dq_t v_dq_Volts = { 0 };
	uz_dq_t i_SpeedControl_reference_Ampere = { 0 };

	if (Data.PID_Controller_Parameters.enableFOC_speed == true) {
		//Change, if desired, the speed controller here
		bool ext_clamping = uz_FOC_get_ext_clamping(FOC_instance);
		i_SpeedControl_reference_Ampere = uz_SpeedControl_sample(Speed_instance, Data.PID_ActualValues.omega_el, Data.PID_Controller_Parameters.n_ref_FOC, Data.PID_ActualValues.V_DC,
		                Data.PID_Controller_Parameters.i_dq_ref.d, Data.PID_GlobalConfig.PMSM_config, ext_clamping);
		//Create sine excitation for J-Identification
		if (Data.PID_Controller_Parameters.VibOn_out == true) {
			float sine_excitation = uz_wavegen_sine(Data.PID_Controller_Parameters.VibAmp_out, Data.PID_Controller_Parameters.VibFreq_out);
			i_SpeedControl_reference_Ampere.q += sine_excitation;
		} else {
			i_SpeedControl_reference_Ampere.q += Data.PID_Controller_Parameters.PRBS_out;
		}
	} else if (Data.PID_Controller_Parameters.enableFOC_current || Data.PID_Controller_Parameters.enableFOC_speed == true) {
		//Change, if desired, the current controller here
		if (Data.PID_Controller_Parameters.enableFOC_current == true) {
			//If CurrentControl is active, use input reference currents
			v_dq_Volts = uz_FOC_sample(FOC_instance, Data.PID_Controller_Parameters.i_dq_ref, Data.PID_ActualValues.i_dq, Data.PID_ActualValues.V_DC, Data.PID_ActualValues.omega_el);
		} else if (Data.PID_Controller_Parameters.enableFOC_speed == true) {
			//If SpeedControl is active, use reference currents from SpeedControl
			v_dq_Volts = uz_FOC_sample(FOC_instance, i_SpeedControl_reference_Ampere, Data.PID_ActualValues.i_dq, Data.PID_ActualValues.V_DC, Data.PID_ActualValues.omega_el);
		}
		uz_UVW_t V_UVW_Volts = uz_dq_inverse_transformation(v_dq_Volts, Data.PID_ActualValues.theta_el);
		output_DutyCycle = uz_FOC_generate_DutyCycles(V_UVW_Volts, Data.PID_ActualValues.V_DC);
	} else if (Data.PID_Controller_Parameters.resetIntegrator == true) {
		uz_FOC_reset(FOC_instance);
		uz_SpeedControl_reset(Speed_instance);
		output_DutyCycle.DutyCycle_U = 0.0f;
		output_DutyCycle.DutyCycle_V = 0.0f;
		output_DutyCycle.DutyCycle_W = 0.0f;
	}
	if (Data.PID_GlobalConfig.ElectricalID == true) {
		if (Data.PID_Controller_Parameters.activeState == 144U) {
			uz_FOC_set_decoupling_method(FOC_instance, no_decoupling);
		} else if (Data.PID_Controller_Parameters.activeState == 170U) {
			uz_FOC_set_PMSM_parameters(FOC_instance, Data.PID_ElectricalID_Output.PMSM_parameters);
			uz_PI_Controller_set_Ki(Speed_instance, Data.PID_Controller_Parameters.Ki_n_out);
			uz_PI_Controller_set_Kp(Speed_instance, Data.PID_Controller_Parameters.Kp_n_out);
			uz_FOC_set_decoupling_method(FOC_instance, linear_decoupling);
		} else if (Data.PID_Controller_Parameters.activeState >= 110 && Data.PID_Controller_Parameters.activeState <= 143) {
			PWM_SS_SetTriState(Data.PID_ElectricalID_Output.enable_TriState[0], Data.PID_ElectricalID_Output.enable_TriState[1], Data.PID_ElectricalID_Output.enable_TriState[2]);
			output_DutyCycle.DutyCycle_U = Data.PID_ElectricalID_Output.PWM_Switch_0;
			output_DutyCycle.DutyCycle_V = Data.PID_ElectricalID_Output.PWM_Switch_2;
			output_DutyCycle.DutyCycle_W = Data.PID_ElectricalID_Output.PWM_Switch_4;
		}
		uz_FOC_set_Kp_id(FOC_instance, Data.PID_Controller_Parameters.Kp_id_out);
		uz_FOC_set_Kp_iq(FOC_instance, Data.PID_Controller_Parameters.Kp_iq_out);
		uz_FOC_set_Ki_id(FOC_instance, Data.PID_Controller_Parameters.Ki_id_out);
		uz_FOC_set_Ki_iq(FOC_instance, Data.PID_Controller_Parameters.Ki_iq_out);
		uz_PI_Controller_set_Ki(Speed_instance, Data.PID_Controller_Parameters.Ki_n_out);
		uz_PI_Controller_set_Kp(Speed_instance, Data.PID_Controller_Parameters.Kp_n_out);
	}



	//return (output_DutyCycle);
	return (v_dq_Volts);
}

uz_ParameterID_Data_t uz_ParameterID_initialize_data_structs(void) {
	uz_ParameterID_Data_t output = { 0 };

	//Initialize Global-Config
	output.PID_GlobalConfig.ACCEPT = false;
	output.PID_GlobalConfig.Reset = false;
	output.PID_GlobalConfig.ElectricalID = false;
	output.PID_GlobalConfig.FluxMapID = false;
	output.PID_GlobalConfig.FrictionID = false;
	output.PID_GlobalConfig.TwoMassID = false;
	output.PID_GlobalConfig.OnlineID = false;
	output.PID_GlobalConfig.VibAmp = 0.0f;
	output.PID_GlobalConfig.VibFreq = 0U;
	output.PID_GlobalConfig.VibOn = false;
	output.PID_GlobalConfig.thetaOffset = 0.0f;
	output.PID_GlobalConfig.sampleTimeISR = 50.0e-06f;

	//Initialize motor-related parameters inside Global-Config
	//Motor Buehler 1.25.058.201
	output.PID_GlobalConfig.Ki_id = 158.8f;
	output.PID_GlobalConfig.Ki_iq = 158.8f;
	output.PID_GlobalConfig.Ki_n = 0.8f;
	output.PID_GlobalConfig.Kp_id = 0.54f;
	output.PID_GlobalConfig.Kp_iq = 0.54f;
	output.PID_GlobalConfig.Kp_n = 0.08f;
	output.PID_GlobalConfig.PMSM_config.Ld_Henry = 2.90e-04f;
	output.PID_GlobalConfig.PMSM_config.Lq_Henry = 3.00e-04f;
	output.PID_GlobalConfig.PMSM_config.R_ph_Ohm = 0.085f;
	output.PID_GlobalConfig.PMSM_config.Psi_PM_Vs = 0.0075f;
	output.PID_GlobalConfig.PMSM_config.polePairs = 4.0f;
	output.PID_GlobalConfig.ratCurrent = 8.0f;
	output.PID_GlobalConfig.ratSpeed = 3000.0f;

	//Initialize ElectricalID-Config
	output.PID_ElectricalID_Config.dutyCyc = 0.0f;
	output.PID_ElectricalID_Config.goertzlAmp = 0.0f;
	output.PID_ElectricalID_Config.identLq = false;
	output.PID_ElectricalID_Config.min_n_ratio = 0.0f;
	output.PID_ElectricalID_Config.n_ref_measurement = 0.0f;

	//Initialize FluxMapID-Config
	output.PID_FluxMapID_Config.AMMsampleTime = 0.0f;
	output.PID_FluxMapID_Config.IDstart = 0.0f;
	output.PID_FluxMapID_Config.IDstepsize = 0.0f;
	output.PID_FluxMapID_Config.IDstop = 0.0f;
	output.PID_FluxMapID_Config.IQstart = 0.0f;
	output.PID_FluxMapID_Config.IQstepsize = 0.0f;
	output.PID_FluxMapID_Config.IQstop = 0.0f;
	output.PID_FluxMapID_Config.R_s_ref = 0.0f;
	output.PID_FluxMapID_Config.Temp_ref = 0.0f;
	output.PID_FluxMapID_Config.identR = false;
	output.PID_FluxMapID_Config.identRAmp = 0.0f;
	output.PID_FluxMapID_Config.start_FM_ID = false;

	return (output);
}

#endif
