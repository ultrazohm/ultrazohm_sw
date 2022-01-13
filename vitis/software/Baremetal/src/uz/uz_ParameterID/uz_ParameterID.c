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

typedef struct uz_ParameterID_t {
	bool is_ready;
	uz_PID_ControlState_t* ControlState;
	uz_PID_ElectricalID_t *ElectricalID;
	uz_PID_TwoMassID_t* TwoMassID;
	uz_PID_FrictionID_t* FrictionID;
	uz_PID_FluxMapID_t* FluxMapID;
	uz_PID_OnlineID_t* OnlineID;

} uz_ParameterID_t;
static size_t instances_counter_ParameterID = 0;
static uz_ParameterID_t instances_ParameterID[UZ_PARAMETERID_ACTIVE] = { 0 };

static void uz_PID_ControlState_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_PID_ElectricalID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_PID_FrictionID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_PID_TwoMassID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_PID_FluxMapID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_PID_OnlineID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);

static uz_ParameterID_t* uz_ParameterID_allocation(void);

static uz_ParameterID_t* uz_ParameterID_allocation(void) {
	uz_assert(instances_counter_ParameterID < UZ_PARAMETERID_ACTIVE);
	uz_ParameterID_t* self = &instances_ParameterID[instances_counter_ParameterID];
	uz_assert(self->is_ready == false);
	instances_counter_ParameterID++;
	self->is_ready = true;
	return (self);
}

uz_ParameterID_t* uz_ParameterID_init(void) {
	uz_ParameterID_t* self = uz_ParameterID_allocation();
	self->ControlState = uz_ControlState_init();
	self->ElectricalID = uz_ElectricalID_init();
	self->TwoMassID = uz_TwoMassID_init();
	self->FrictionID = uz_FrictionID_init();
	self->FluxMapID = uz_FluxMapID_init();
	self->OnlineID = uz_OnlineID_init();
	return (self);
}

void uz_ParameterID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	uz_PID_ControlState_step(self, Data);

	//All Offline states
	if (self->ControlState->output.ControlFlags.finished_all_Offline_states == false) {

		//ElectricalID
		if (self->ControlState->output.GlobalConfig_out.ElectricalID == true && self->ControlState->output.GlobalConfig_out.Reset == false
		                && self->ControlState->output.ControlFlags.transNr == 1U) {
			uz_PID_ElectricalID_step(self, Data);
		} else if (self->ControlState->output.GlobalConfig_out.ElectricalID == false && self->ElectricalID->output.enteredElectricalID == true) {
			uz_PID_ElectricalID_step(self, Data);
		}

		//TwoMassID
		if (self->ControlState->output.GlobalConfig_out.TwoMassID == true && self->ControlState->output.GlobalConfig_out.Reset == false
		                && self->ControlState->output.ControlFlags.transNr == 2U) {
			uz_PID_TwoMassID_step(self, Data);
		} else if (self->ControlState->output.GlobalConfig_out.TwoMassID == false && self->TwoMassID->output.enteredTwoMassID == true) {
			uz_PID_TwoMassID_step(self, Data);
		}

		//FrictionID
		if (self->ControlState->output.GlobalConfig_out.FrictionID == true && self->ControlState->output.GlobalConfig_out.Reset == false
		                && self->ControlState->output.ControlFlags.transNr == 3U) {
			uz_PID_FrictionID_step(self, Data);
		} else if (self->ControlState->output.GlobalConfig_out.FrictionID == false && self->FrictionID->output.enteredFrictionID == true) {
			uz_PID_FrictionID_step(self, Data);
		}

		//FluxMapID
		if (self->ControlState->output.GlobalConfig_out.FluxMapID == true && self->ControlState->output.GlobalConfig_out.Reset == false
		                && self->ControlState->output.ControlFlags.transNr == 4U) {
			uz_PID_FluxMapID_step(self, Data);
		} else if (self->ControlState->output.GlobalConfig_out.FluxMapID == false && self->FluxMapID->output.enteredFluxMapID == true) {
			uz_PID_FluxMapID_step(self, Data);
		}
	}
	//OnlineID
	if (self->ControlState->output.ControlFlags.enableOnlineID == true || self->ControlState->output.GlobalConfig_out.Reset == true || Data->PID_OnlineID_Config.OnlineID_Reset == true) {
		uz_PID_OnlineID_step(self, Data);
	}

	//RESET
	if (Data->PID_GlobalConfig.Reset == true) {
		uz_PID_ControlState_step(self, Data);
		uz_PID_ElectricalID_step(self, Data);
		uz_PID_TwoMassID_step(self, Data);
		uz_PID_FrictionID_step(self, Data);
		uz_PID_FluxMapID_step(self, Data);
		uz_PID_OnlineID_step(self, Data);

		//reset the Reset-button
		self->ControlState->output.GlobalConfig_out.Reset = false;
		Data->PID_GlobalConfig.Reset = false;
	}

	// reset ACCEPT
	if (self->ControlState->output.GlobalConfig_out.ACCEPT == true) {
		self->ControlState->output.GlobalConfig_out.ACCEPT = false;
		Data->PID_GlobalConfig.ACCEPT = false;
	}
}

//struct uz_DutyCycle_t uz_ParameterID_Controller(uz_ParameterID_Data_t* Data, uz_FOC* FOC_instance, uz_PI_Controller* Speed_instance) {
struct uz_dq_t uz_ParameterID_Controller(uz_ParameterID_Data_t* Data, uz_FOC* FOC_instance, uz_PI_Controller* Speed_instance, ControlReference ControlRef) {
		struct uz_DutyCycle_t output_DutyCycle = { 0 };
		uz_dq_t v_dq_Volts = { 0 };
		uz_dq_t i_SpeedControl_reference_Ampere = { 0 };
	bool ext_clamping = false;

		if (Data->PID_Controller_Parameters.enableFOC_speed == true) {
			//Change, if desired, the speed controller here
		ext_clamping = uz_FOC_get_ext_clamping(FOC_instance);
			i_SpeedControl_reference_Ampere = uz_SpeedControl_sample(Speed_instance, Data->PID_ActualValues.omega_el, Data->PID_Controller_Parameters.n_ref_FOC,
			                Data->PID_ActualValues.V_DC, Data->PID_Controller_Parameters.i_dq_ref.d, Data->PID_GlobalConfig.PMSM_config, ext_clamping);
			//Create sine excitation for J-Identification
			if (Data->PID_Controller_Parameters.VibOn_out == true) {
				float sine_excitation = uz_wavegen_sine(Data->PID_Controller_Parameters.VibAmp_out, Data->PID_Controller_Parameters.VibFreq_out);
				i_SpeedControl_reference_Ampere.q += sine_excitation;
			} else {
				i_SpeedControl_reference_Ampere.q += Data->PID_Controller_Parameters.PRBS_out;
			}
	}
	if (Data->PID_Controller_Parameters.enableFOC_current == true || Data->PID_Controller_Parameters.enableFOC_speed == true) {
			//Change, if desired, the current controller here
			if (Data->PID_Controller_Parameters.enableFOC_current == true) {
				//If CurrentControl is active, use input reference currents
				v_dq_Volts = uz_FOC_sample(FOC_instance, Data->PID_Controller_Parameters.i_dq_ref, Data->PID_ActualValues.i_dq, Data->PID_ActualValues.V_DC,
				                Data->PID_ActualValues.omega_el);
			} else if (Data->PID_Controller_Parameters.enableFOC_speed == true) {
				//If SpeedControl is active, use reference currents from SpeedControl
				v_dq_Volts = uz_FOC_sample(FOC_instance, i_SpeedControl_reference_Ampere, Data->PID_ActualValues.i_dq, Data->PID_ActualValues.V_DC, Data->PID_ActualValues.omega_el);
			}
			uz_UVW_t V_UVW_Volts = uz_dq_inverse_transformation(v_dq_Volts, Data->PID_ActualValues.theta_el);
			output_DutyCycle = uz_FOC_generate_DutyCycles(V_UVW_Volts, Data->PID_ActualValues.V_DC);
	}
	if (Data->PID_Controller_Parameters.resetIntegrator == true) {
			uz_FOC_reset(FOC_instance);
			uz_SpeedControl_reset(Speed_instance);
			output_DutyCycle.DutyCycle_U = 0.0f;
			output_DutyCycle.DutyCycle_V = 0.0f;
			output_DutyCycle.DutyCycle_W = 0.0f;
		}
	if (Data->PID_GlobalConfig.ElectricalID == true) {
		if (Data->PID_Controller_Parameters.activeState == 144U) {
			uz_FOC_set_decoupling_method(FOC_instance, no_decoupling);
		} else if (Data->PID_Controller_Parameters.activeState == 170U) {
			uz_FOC_set_PMSM_parameters(FOC_instance, Data->PID_ElectricalID_Output->PMSM_parameters);
			uz_FOC_set_decoupling_method(FOC_instance, linear_decoupling);
			} else if (Data->PID_Controller_Parameters.activeState >= 110 && Data->PID_Controller_Parameters.activeState <= 143) {
			PWM_SS_SetTriState(Data->PID_ElectricalID_Output->enable_TriState[0], Data->PID_ElectricalID_Output->enable_TriState[1], Data->PID_ElectricalID_Output->enable_TriState[2]);
			output_DutyCycle.DutyCycle_U = Data->PID_ElectricalID_Output->PWM_Switch_0;
			output_DutyCycle.DutyCycle_V = Data->PID_ElectricalID_Output->PWM_Switch_2;
			output_DutyCycle.DutyCycle_W = Data->PID_ElectricalID_Output->PWM_Switch_4;
			}
//		uz_FOC_set_Kp_id(FOC_instance, Data->PID_Controller_Parameters.Kp_id_out);
//		uz_FOC_set_Kp_iq(FOC_instance, Data->PID_Controller_Parameters.Kp_iq_out);
//		uz_FOC_set_Ki_id(FOC_instance, Data->PID_Controller_Parameters.Ki_id_out);
//		uz_FOC_set_Ki_iq(FOC_instance, Data->PID_Controller_Parameters.Ki_iq_out);
//		uz_PI_Controller_set_Ki(Speed_instance, Data->PID_Controller_Parameters.Ki_n_out);
//		uz_PI_Controller_set_Kp(Speed_instance, Data->PID_Controller_Parameters.Kp_n_out);
		}
	if (Data->PID_GlobalConfig.TwoMassID == true) {
		uz_PI_Controller_set_Ki(Speed_instance, Data->PID_Controller_Parameters.Ki_n_out);
		uz_PI_Controller_set_Kp(Speed_instance, Data->PID_Controller_Parameters.Kp_n_out);
	}

	if (Data->PID_ControlFlags->finished_all_Offline_states == true) {
		uz_dq_t Online_current_ref = Data->PID_GlobalConfig.i_dq_ref;
		if (Data->PID_OnlineID_Output->IdControlFlag == true) {
			Online_current_ref.d = Data->PID_GlobalConfig.i_dq_ref.d + Data->PID_OnlineID_Output->id_out;
		} else {
			Online_current_ref.d = Data->PID_GlobalConfig.i_dq_ref.d;
		}
		if (ControlRef == CurrentControl) {
			v_dq_Volts = uz_FOC_sample(FOC_instance, Online_current_ref, Data->PID_ActualValues.i_dq, Data->PID_ActualValues.V_DC, Data->PID_ActualValues.omega_el);
		} else if (ControlRef == SpeedControl) {
			ext_clamping = uz_FOC_get_ext_clamping(FOC_instance);
			i_SpeedControl_reference_Ampere = uz_SpeedControl_sample(Speed_instance, Data->PID_ActualValues.omega_el, Data->PID_GlobalConfig.n_ref, Data->PID_ActualValues.V_DC,
			                Online_current_ref.d,
			                Data->PID_GlobalConfig.PMSM_config, ext_clamping);
			v_dq_Volts = uz_FOC_sample(FOC_instance, i_SpeedControl_reference_Ampere, Data->PID_ActualValues.i_dq, Data->PID_ActualValues.V_DC, Data->PID_ActualValues.omega_el);
		} else {
			v_dq_Volts.d = 0.0f;
			v_dq_Volts.q = 0.0f;
			v_dq_Volts.zero = 0.0f;
		}
	}
		//return (output_DutyCycle);
		return (v_dq_Volts);
	}

void uz_ParameterID_CleanPsiArray(uz_ParameterID_t *self, uz_ParameterID_Data_t* Data) {
	self->OnlineID->CleanPsiArray->input.OnlineID_output = self->OnlineID->output.OnlineID_output;
	self->OnlineID->CleanPsiArray->input.eta_c = 0.05f * Data->PID_GlobalConfig.ratCurrent;
	uz_OnlineID_CleanPsiArray(self->OnlineID);
	memcpy(self->OnlineID->input.cleaned_psi_array, self->OnlineID->CleanPsiArray->output.psi_array_out, sizeof(self->OnlineID->input.cleaned_psi_array));
	Data->PID_OnlineID_Config.array_cleaned = self->OnlineID->CleanPsiArray->output.array_cleaned_flag;
}

void uz_ParameterID_CalcFluxMaps(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	memcpy(self->OnlineID->InterpMeshGrid->input.psi_array_in, self->OnlineID->CleanPsiArray->output.psi_array_out, sizeof(self->OnlineID->CleanPsiArray->output.psi_array_out));
	self->OnlineID->InterpMeshGrid->input.i_rat = Data->PID_GlobalConfig.ratCurrent;
	self->OnlineID->InterpMeshGrid->input.OnlineID_input = self->OnlineID->output.OnlineID_output;
	uz_OnlineID_CalcFluxMaps(self->OnlineID);
}


static void uz_PID_ElectricalID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	//Update State-Inputs
	self->ElectricalID->input.ActualValues = Data->PID_ActualValues;
	self->ElectricalID->input.ElectricalIDConfig = Data->PID_ElectricalID_Config;
	self->ElectricalID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
	self->ElectricalID->input.ControlFlags = self->ControlState->output.ControlFlags;

	//Step the function
	uz_ElectricalID_step(self->ElectricalID);

	//Update Control-State-inputs
	self->ControlState->input.ElectricalID_FOC_output = self->ElectricalID->output.ElectricalID_FOC_output;
	self->ControlState->input.ElectricalID_output = self->ElectricalID->output.ElectricalID_output;
	self->ControlState->input.enteredElectricalID = self->ElectricalID->output.enteredElectricalID;
	self->ControlState->input.finishedElectricalID = self->ElectricalID->output.finishedElectricalID;

	//Update Data struct with new output values
	Data->PID_Controller_Parameters = self->ElectricalID->output.ElectricalID_FOC_output;
	Data->PID_GlobalConfig.thetaOffset = self->ElectricalID->output.ElectricalID_output.thetaOffset;
}

static void uz_PID_ControlState_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	//Update Control-State inputs, which are not depended on other states
	self->ControlState->input.GlobalConfig_in = Data->PID_GlobalConfig;

	//Control-State will always be stepped
	uz_ControlState_step(self->ControlState);
}

static void uz_PID_FrictionID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	//Update State-Inputs
	self->FrictionID->input.ActualValues = Data->PID_ActualValues;
	self->FrictionID->input.FrictionConfigID = Data->PID_FrictionID_Config;
	self->FrictionID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
	self->FrictionID->input.ControlFlags = self->ControlState->output.ControlFlags;

	//Step the function
	uz_FrictionID_step(self->FrictionID);

	//Update Control-State-inputs
	self->ControlState->input.enteredFrictionID = self->FrictionID->output.enteredFrictionID;
	self->ControlState->input.finishedFrictionID = self->FrictionID->output.finishedFrictionID;
	//Update Data struct with new output values
	Data->PID_Controller_Parameters = self->FrictionID->output.FrictionID_FOC_output;
}

static void uz_PID_TwoMassID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	//Update State-Inputs
	self->TwoMassID->input.ActualValues = Data->PID_ActualValues;
	self->TwoMassID->input.TwoMassIDConfig = Data->PID_TwoMassID_Config;
	self->TwoMassID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
	self->TwoMassID->input.ControlFlags = self->ControlState->output.ControlFlags;

	//Step the function
	uz_TwoMassID_step(self->TwoMassID);

	//Update Control-State-inputs
	self->ControlState->input.enteredTwoMassID = self->TwoMassID->output.enteredTwoMassID;
	self->ControlState->input.finishedTwoMassID = self->TwoMassID->output.finishedTwoMassID;

	//Update Data struct with new output values
	Data->PID_Controller_Parameters = self->TwoMassID->output.TwoMassID_FOC_output;
}

static void uz_PID_FluxMapID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	//Update State-Inputs
	self->FluxMapID->input.ActualValues = Data->PID_ActualValues;
	self->FluxMapID->input.FluxMapIDConfig = Data->PID_FluxMapID_Config;
	self->FluxMapID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
	self->FluxMapID->input.ControlFlags = self->ControlState->output.ControlFlags;

	//Step the function
	uz_FluxMapID_step(self->FluxMapID);

	//Update Control-State-inputs
	self->ControlState->input.enteredFluxMapID = self->FluxMapID->output.enteredFluxMapID;
	self->ControlState->input.finishedFluxMapID = self->FluxMapID->output.finishedFluxMapID;

	//Update Data struct with new output values
	Data->PID_Controller_Parameters = self->FluxMapID->output.FluxMapID_FOC_output;
}

static void uz_PID_OnlineID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	//Update State-Inputs
	self->OnlineID->input.ActualValues = Data->PID_ActualValues;
	self->OnlineID->input.ControlFlags = self->ControlState->output.ControlFlags;
	self->OnlineID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
	self->OnlineID->input.OnlineIDConfig = Data->PID_OnlineID_Config;

	//Step the function
	uz_OnlineID_step(self->OnlineID);

	//Update Data struct with new output values
	Data->PID_Controller_Parameters.activeState = self->OnlineID->output.OnlineID_output.activeState;
}


void uz_ParameterID_initialize_data_structs(uz_ParameterID_Data_t *Data, uz_ParameterID_t *ParameterID) {

	//Initialize Global-Config
	Data->PID_GlobalConfig.ACCEPT = false;
	Data->PID_GlobalConfig.Reset = false;
	Data->PID_GlobalConfig.enableParameterID = false;
	Data->PID_GlobalConfig.ElectricalID = false;
	Data->PID_GlobalConfig.FluxMapID = false;
	Data->PID_GlobalConfig.FrictionID = false;
	Data->PID_GlobalConfig.TwoMassID = false;
	Data->PID_GlobalConfig.OnlineID = false;
	Data->PID_GlobalConfig.VibAmp = 0.0f;
	Data->PID_GlobalConfig.VibFreq = 0U;
	Data->PID_GlobalConfig.VibOn = false;
	Data->PID_GlobalConfig.thetaOffset = 0.0f;
	Data->PID_GlobalConfig.sampleTimeISR = 50.0e-06f;

	//Initialize motor-related parameters inside Global-Config
	//Motor Buehler 1.25.058.201
	Data->PID_GlobalConfig.Ki_id = 158.8f;
	Data->PID_GlobalConfig.Ki_iq = 158.8f;
	Data->PID_GlobalConfig.Ki_n = 0.8f;
	Data->PID_GlobalConfig.Kp_id = 0.54f;
	Data->PID_GlobalConfig.Kp_iq = 0.54f;
	Data->PID_GlobalConfig.Kp_n = 0.08f;
	Data->PID_GlobalConfig.PMSM_config.Ld_Henry = 2.90e-04f;
	Data->PID_GlobalConfig.PMSM_config.Lq_Henry = 3.00e-04f;
	Data->PID_GlobalConfig.PMSM_config.R_ph_Ohm = 0.085f;
	Data->PID_GlobalConfig.PMSM_config.Psi_PM_Vs = 0.0075f;
	Data->PID_GlobalConfig.PMSM_config.polePairs = 4.0f;
	Data->PID_GlobalConfig.PMSM_config.J_kg_m_squared = 3.24e-05f;
	Data->PID_GlobalConfig.PMSM_config.I_max_Ampere = 15.0f;
	Data->PID_GlobalConfig.ratCurrent = 8.0f;
	Data->PID_GlobalConfig.ratSpeed = 3000.0f;

	//Initialize ElectricalID-Config
	Data->PID_ElectricalID_Config.dutyCyc = 0.0f;
	Data->PID_ElectricalID_Config.goertzlAmp = 0.0f;
	Data->PID_ElectricalID_Config.identLq = false;
	Data->PID_ElectricalID_Config.min_n_ratio = 0.0f;
	Data->PID_ElectricalID_Config.n_ref_measurement = 0.0f;

	//Initialize FluxMapID-Config
	Data->PID_FluxMapID_Config.AMMsampleTime = 2.0f;
	Data->PID_FluxMapID_Config.IDstart = 0.0f;
	Data->PID_FluxMapID_Config.IDstepsize = 0.0f;
	Data->PID_FluxMapID_Config.IDstop = 0.0f;
	Data->PID_FluxMapID_Config.IQstart = 0.0f;
	Data->PID_FluxMapID_Config.IQstepsize = 0.0f;
	Data->PID_FluxMapID_Config.IQstop = 0.0f;
	Data->PID_FluxMapID_Config.R_s_ref = 0.0f;
	Data->PID_FluxMapID_Config.Temp_ref = 0.0f;
	Data->PID_FluxMapID_Config.identR = false;
	Data->PID_FluxMapID_Config.identRAmp = 0.0f;
	Data->PID_FluxMapID_Config.start_FM_ID = false;

	//Initialize FrictionID-Config
	Data->PID_FrictionID_Config.BrkCount = 0.0f;
	Data->PID_FrictionID_Config.N_Brk = 0.0f;
	Data->PID_FrictionID_Config.N_Visco = 0.0f;
	Data->PID_FrictionID_Config.StepScale = 0.0f;
	Data->PID_FrictionID_Config.eta = 0.0f;
	Data->PID_FrictionID_Config.maxCurrent = 10.0f;
	Data->PID_FrictionID_Config.n_eva_max = 0.0f;

	//Inintialize OnlineID-Config
	Data->PID_OnlineID_Config.AverageTransParams = false;
	Data->PID_OnlineID_Config.OnlineID_Reset = false;
	Data->PID_OnlineID_Config.Rs_time = 0.0f;
	Data->PID_OnlineID_Config.Temp_ref = 0.0f;
	Data->PID_OnlineID_Config.allowPsiCalcOutside = false;
	Data->PID_OnlineID_Config.dev_curr = 0.05f;
	Data->PID_OnlineID_Config.dev_omega = 0.05f;
	Data->PID_OnlineID_Config.identRAmp = 2.0f;
	Data->PID_OnlineID_Config.max_n_ratio = 0.0f;
	Data->PID_OnlineID_Config.min_n_ratio = 0.0f;
	Data->PID_OnlineID_Config.nom_factor = 0.0f;
	Data->PID_OnlineID_Config.array_cleaned = false;

	//Inintialize Output data structs
	Data->PID_ElectricalID_Output = &ParameterID->ElectricalID->output.ElectricalID_output;
	Data->PID_FrictionID_Output = &ParameterID->FrictionID->output.FrictionID_output;
	Data->PID_FluxMapID_Output = &ParameterID->FluxMapID->output.FluxMapID_output;
	Data->PID_TwoMassID_Output = &ParameterID->TwoMassID->output.TwoMassID_output;
	Data->PID_OnlineID_Output = &ParameterID->OnlineID->output.OnlineID_output;
	Data->PID_ControlFlags = &ParameterID->ControlState->output.ControlFlags;
	Data->FluxMap_Data = &ParameterID->OnlineID->InterpMeshGrid->output.FluxMapData;


}
#endif
