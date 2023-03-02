/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Dennnis Hufnagel 
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
#include "uz_ParameterID.h"
#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_MAX_INSTANCES > 0U

#include <math.h>
#include "../uz_HAL.h"
#include <stdbool.h>

typedef struct uz_ParameterID_t {
	bool is_ready;
	uz_ParaID_ControlState_t* ControlState;
	uz_ParaID_ElectricalID_t *ElectricalID;
	uz_ParaID_TwoMassID_t* TwoMassID;
	uz_ParaID_FrictionID_t* FrictionID;
	uz_ParaID_FluxMapID_t* FluxMapID;
	uz_ParaID_OnlineID_t* OnlineID;

} uz_ParameterID_t;
static uint32_t instances_counter_ParameterID = 0;
static uz_ParameterID_t instances_ParameterID[UZ_PARAMETERID_MAX_INSTANCES] = { 0 };

static void uz_ParaID_ControlState_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_ElectricalID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_FrictionID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_TwoMassID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_FluxMapID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_OnlineID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_AutoRefCurrents_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_FOC_output_set_zero(uz_ParameterID_Data_t* Data);
static void uz_ParameterID_initialize_data_structs(uz_ParameterID_t *self, uz_ParameterID_Data_t *Data);

static uz_ParameterID_t* uz_ParameterID_allocation(void);

static uz_ParameterID_t* uz_ParameterID_allocation(void) {
	uz_assert(instances_counter_ParameterID < UZ_PARAMETERID_MAX_INSTANCES);
	uz_ParameterID_t* self = &instances_ParameterID[instances_counter_ParameterID];
	uz_assert(self->is_ready == false);
	instances_counter_ParameterID++;
	self->is_ready = true;
	return (self);
}

uz_ParameterID_t* uz_ParameterID_init(uz_ParameterID_Data_t *Data) {
	uz_assert_not_NULL(Data);
	uz_ParameterID_t* self = uz_ParameterID_allocation();
	self->ControlState = uz_ControlState_init();
	self->ElectricalID = uz_ElectricalID_init();
	self->TwoMassID = uz_TwoMassID_init();
	self->FrictionID = uz_FrictionID_init();
	self->FluxMapID = uz_FluxMapID_init();
	self->OnlineID = uz_OnlineID_init();
	uz_ParameterID_initialize_data_structs(self, Data);
	return (self);
}

void uz_ParameterID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	uz_assert(self->is_ready);
	uz_ParaID_ControlState_step(self, Data);

	//All Offline states
	if (uz_ControlState_get_ControlFlags(self->ControlState)->finished_all_Offline_states == false) {
	//if (self->ControlState->output.ControlFlags.finished_all_Offline_states == false) {

		//ElectricalID
		if (uz_ControlState_get_ControlFlags(self->ControlState)->transNr == 1U || uz_ControlState_get_GlobalConfig(self->ControlState)->Reset == true) {
			uz_ParaID_ElectricalID_step(self, Data);
		} else if (uz_ControlState_get_GlobalConfig(self->ControlState)->ElectricalID == false && uz_ElectricalID_get_enteredElectricalID(self->ElectricalID) == true) {
			uz_ParaID_ElectricalID_step(self, Data);
		}

		//TwoMassID
		if (uz_ControlState_get_ControlFlags(self->ControlState)->transNr == 2U || uz_ControlState_get_GlobalConfig(self->ControlState)->Reset == true) {
			uz_ParaID_TwoMassID_step(self, Data);
		} else if (uz_ControlState_get_GlobalConfig(self->ControlState)->TwoMassID == false && uz_TwoMassID_get_enteredTwoMassID(self->TwoMassID) == true) {
			uz_ParaID_TwoMassID_step(self, Data);
		}

		//FrictionID
		if (uz_ControlState_get_ControlFlags(self->ControlState)->transNr == 3U || uz_ControlState_get_GlobalConfig(self->ControlState)->Reset == true) {
			uz_ParaID_FrictionID_step(self, Data);
			if (Data->Array_counter < 256 && (Data->Array_counter == Data->Array_Control_counter)) {
				Data->Array_counter += 1;
			} else if (Data->Array_counter == 256){
				Data->Array_counter = 0;
			}
		} else if (uz_ControlState_get_GlobalConfig(self->ControlState)->FrictionID == false && uz_FrictionID_get_enteredFrictionID(self->FrictionID) == true) {
			uz_ParaID_FrictionID_step(self, Data);
		}

		//FluxMapID
		if (uz_ControlState_get_ControlFlags(self->ControlState)->transNr == 4U || uz_ControlState_get_GlobalConfig(self->ControlState)->Reset == true) {
			uz_ParaID_FluxMapID_step(self, Data);
		} else if (uz_ControlState_get_GlobalConfig(self->ControlState)->FluxMapID == false && uz_FluxMapID_get_enteredFluxMapID(self->FluxMapID) == true) {
			uz_ParaID_FluxMapID_step(self, Data);
		}
	}
	//OnlineID
	if (uz_ControlState_get_ControlFlags(self->ControlState)->enableOnlineID == true || uz_ControlState_get_GlobalConfig(self->ControlState)->Reset == true || Data->OnlineID_Config.OnlineID_Reset == true) {
		uz_ParaID_OnlineID_step(self, Data);
		if (Data->AutoRefCurrents_Config.enableCRS == true || uz_ControlState_get_GlobalConfig(self->ControlState)->Reset == true || Data->OnlineID_Config.OnlineID_Reset == true) {
			uz_ParaID_AutoRefCurrents_step(self, Data);
		}
		if (Data->FluxMap_counter < 400 && (Data->FluxMap_counter == Data->FluxMap_Control_counter)) {
			Data->FluxMap_counter += 1;
		} else if (Data->FluxMap_counter == 400){
			Data->FluxMap_counter = 0;
		}
	} else {
		Data->OnlineID_Output->IdControlFlag = false;
	}
	switch (uz_ControlState_get_ControlFlags(self->ControlState)->transNr) {

	case 1U:
		Data->Controller_Parameters = *uz_ElectricalID_get_FOC_output(self->ElectricalID);
		break;

	case 2U:
		Data->Controller_Parameters = *uz_TwoMassID_get_FOC_output(self->TwoMassID);
		break;

	case 3U:
		Data->Controller_Parameters = *uz_FrictionID_get_FOC_output(self->FrictionID);
		break;

	case 4U:
		Data->Controller_Parameters = *uz_FluxMapID_get_FOC_output(self->FluxMapID);
		break;

	default:
		uz_ParaID_FOC_output_set_zero(Data);
		break;
	}


	//RESET
	if (Data->GlobalConfig.Reset == true) {

		//reset the Reset-button
		uz_ControlState_get_GlobalConfig(self->ControlState)->Reset = false;
		Data->GlobalConfig.Reset = false;
		Data->AutoRefCurrents_Config.Reset = false;
		uz_OnlineID_set_AutoRefCurrents_Config(self->OnlineID, Data->AutoRefCurrents_Config);
	}
	if (Data->OnlineID_Config.OnlineID_Reset) {
		Data->OnlineID_Config.OnlineID_Reset = false;
		Data->AutoRefCurrents_Config.Reset = false;
	}

	// reset ACCEPT
	if (uz_ControlState_get_GlobalConfig(self->ControlState)->ACCEPT == true) {
		uz_ControlState_get_GlobalConfig(self->ControlState)->ACCEPT = false;
		Data->GlobalConfig.ACCEPT = false;
	}
}

struct uz_DutyCycle_t uz_ParameterID_generate_DutyCycle(uz_ParameterID_Data_t* Data, uz_3ph_dq_t v_dq_Volts, uz_PWM_SS_2L_t* PWM_Module) {
	uz_assert_not_NULL(Data);
	uz_assert_not_NULL(PWM_Module);
	struct uz_DutyCycle_t output_DutyCycle = { 0 };
	if (Data->Controller_Parameters.activeState >= 110 && Data->Controller_Parameters.activeState <= 143) {
		uz_PWM_SS_2L_set_tristate(PWM_Module, Data->ElectricalID_Output->enable_TriState[0], Data->ElectricalID_Output->enable_TriState[1], Data->ElectricalID_Output->enable_TriState[2]);
		output_DutyCycle.DutyCycle_U = Data->ElectricalID_Output->PWM_Switch_0;
		output_DutyCycle.DutyCycle_V = Data->ElectricalID_Output->PWM_Switch_2;
		output_DutyCycle.DutyCycle_W = Data->ElectricalID_Output->PWM_Switch_4;
	} else if ((Data->Controller_Parameters.enableFOC_current == true || Data->Controller_Parameters.enableFOC_speed == true)
	                || (Data->ControlFlags->finished_all_Offline_states == true && (Data->ParaID_Control_Selection == Current_Control || Data->ParaID_Control_Selection == Speed_Control))) {
		
		//Generate DutyCylce
	} else {
		output_DutyCycle.DutyCycle_U = 0.0f;
		output_DutyCycle.DutyCycle_V = 0.0f;
		output_DutyCycle.DutyCycle_W = 0.0f;
	}
	if (Data->Controller_Parameters.resetIntegrator == true) {
		output_DutyCycle.DutyCycle_U = 0.0f;
		output_DutyCycle.DutyCycle_V = 0.0f;
		output_DutyCycle.DutyCycle_W = 0.0f;
	}
	return (output_DutyCycle);
}
uz_3ph_dq_t uz_ParameterID_Controller(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance, uz_SpeedControl_t* Speed_instance, uz_SetPoint_t* SP_instance) {
	uz_assert_not_NULL(Data);
	uz_assert_not_NULL(CC_instance);
	uz_assert_not_NULL(Speed_instance);
	uz_assert_not_NULL(SP_instance);
	uz_3ph_dq_t v_dq_Volts = { 0 };
	uz_3ph_dq_t i_SpeedControl_reference_Ampere = { 0 };
	float SpeedControl_reference_torque = 0.0f;

	if (Data->Controller_Parameters.enableFOC_speed == true) {
		//Change, if desired, the speed controller here
		uz_SpeedControl_set_ext_clamping(Speed_instance, uz_CurrentControl_get_ext_clamping(CC_instance));
		SpeedControl_reference_torque = uz_SpeedControl_sample(Speed_instance, Data->ActualValues.omega_m, Data->Controller_Parameters.n_ref_FOC);
		i_SpeedControl_reference_Ampere = uz_SetPoint_sample(SP_instance, Data->ActualValues.omega_m, SpeedControl_reference_torque, Data->ActualValues.V_DC, Data->ActualValues.i_dq);
		i_SpeedControl_reference_Ampere.q += Data->TwoMassID_Output->PRBS_out;
	}

	if (Data->Controller_Parameters.enableFOC_torque == true) {
		i_SpeedControl_reference_Ampere = uz_SetPoint_sample(SP_instance, Data->ActualValues.omega_m, Data->Controller_Parameters.M_ref_FOC, Data->ActualValues.V_DC, Data->ActualValues.i_dq);
	}
	if (Data->Controller_Parameters.enableFOC_current || Data->Controller_Parameters.enableFOC_speed || Data->Controller_Parameters.enableFOC_torque) {
		//Change, if desired, the current controller here
		if (Data->Controller_Parameters.enableFOC_current) {
			//If CurrentControl is active, use input reference currents
			v_dq_Volts = uz_CurrentControl_sample(CC_instance, Data->Controller_Parameters.i_dq_ref, Data->ActualValues.i_dq, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
		} else if (Data->Controller_Parameters.enableFOC_torque || Data->Controller_Parameters.enableFOC_speed) {
			//If SetPoint or SpeedControl & SetPoint is active, use Setpoint currents
			v_dq_Volts = uz_CurrentControl_sample(CC_instance, i_SpeedControl_reference_Ampere, Data->ActualValues.i_dq, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
		}
	}
	if (Data->Controller_Parameters.resetIntegrator == true) {
			uz_CurrentControl_reset(CC_instance);
			uz_SpeedControl_reset(Speed_instance);
	}
	if (Data->ControlFlags->transNr > 0U && Data->ControlFlags->transNr <= 4U) {
		if (Data->Controller_Parameters.activeState == 144U) {
			uz_CurrentControl_set_decoupling_method(CC_instance, no_decoupling);
		} else if (Data->Controller_Parameters.activeState == 170U) {
			uz_CurrentControl_set_decoupling_method(CC_instance, linear_decoupling);
		}
		uz_CurrentControl_set_Kp_id(CC_instance, Data->Controller_Parameters.Kp_id_out);
		uz_CurrentControl_set_Kp_iq(CC_instance, Data->Controller_Parameters.Kp_iq_out);
		uz_CurrentControl_set_Ki_id(CC_instance, Data->Controller_Parameters.Ki_id_out);
		uz_CurrentControl_set_Ki_iq(CC_instance, Data->Controller_Parameters.Ki_iq_out);
		uz_SpeedControl_set_Ki(Speed_instance, Data->Controller_Parameters.Ki_n_out);
		uz_SpeedControl_set_Kp(Speed_instance, Data->Controller_Parameters.Kp_n_out);
	}
	
	//This is the setup for the Controller for Online-ID-states
	if (Data->ControlFlags->finished_all_Offline_states == true) {
		uz_3ph_dq_t Online_current_ref = {0};
		
		if (Data->ParaID_Control_Selection == Current_Control || Data->ParaID_Control_Selection == Speed_Control || Data->ParaID_Control_Selection == Torque_Control) {
			if (Data->ParaID_Control_Selection == Speed_Control) {
				uz_SpeedControl_set_ext_clamping(Speed_instance, uz_CurrentControl_get_ext_clamping(CC_instance));
				SpeedControl_reference_torque = uz_SpeedControl_sample(Speed_instance, Data->ActualValues.omega_el, Data->GlobalConfig.n_ref);
				Online_current_ref = uz_SetPoint_sample(SP_instance, Data->ActualValues.omega_m, SpeedControl_reference_torque, Data->ActualValues.V_DC, Data->ActualValues.i_dq);			
			}
			else if (Data->ParaID_Control_Selection == Torque_Control) {
				Online_current_ref = uz_SetPoint_sample(SP_instance, Data->ActualValues.omega_m, Data->GlobalConfig.M_ref, Data->ActualValues.V_DC, Data->ActualValues.i_dq);
			} else {
				Online_current_ref = Data->GlobalConfig.i_dq_ref;
			}
		}
		if (Data->OnlineID_Output->IdControlFlag == true) {
			if (Data->AutoRefCurrents_Config.enableCRS == true && Data->ParaID_Control_Selection == Current_Control) {//Overwrite dq-ref-currents when AutoRefCurrents is active
				Online_current_ref.d = Data->OnlineID_Output->id_out + Data->AutoRefCurrents_Output.i_dq_ref.d;
				Online_current_ref.q = Data->AutoRefCurrents_Output.i_dq_ref.q;
			} else {
				Online_current_ref.d = Data->GlobalConfig.i_dq_ref.d + Data->OnlineID_Output->id_out;
			}
		} else {
			if (Data->AutoRefCurrents_Config.enableCRS == true && Data->ParaID_Control_Selection == Current_Control) {
				Online_current_ref.d = Data->AutoRefCurrents_Output.i_dq_ref.d;
				Online_current_ref.q = Data->AutoRefCurrents_Output.i_dq_ref.q;
			}
		}
		v_dq_Volts = uz_CurrentControl_sample(CC_instance, Online_current_ref, Data->ActualValues.i_dq, Data->ActualValues.V_DC, Data->ActualValues.omega_el);		
		} else {
			v_dq_Volts.d = 0.0f;
			v_dq_Volts.q = 0.0f;
			v_dq_Volts.zero = 0.0f;
		}
	return (v_dq_Volts);
}

void uz_ParameterID_CleanPsiArray(uz_ParameterID_t *self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	uz_assert(self->is_ready);
	uz_OnlineID_CleanPsiArray(self->OnlineID, Data);
}

void uz_ParameterID_CalcFluxMaps(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	uz_assert(self->is_ready);
	uz_OnlineID_CalcFluxMaps(self->OnlineID, Data);
}


static void uz_ParaID_ElectricalID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Update State-Inputs
	uz_ElectricalID_set_ActualValues(self->ElectricalID, Data->ActualValues);
	uz_ElectricalID_set_Config(self->ElectricalID, Data->ElectricalID_Config);
	uz_ElectricalID_set_GlobalConfig(self->ElectricalID, *uz_ControlState_get_GlobalConfig(self->ControlState));
	uz_ElectricalID_set_ControlFlags(self->ElectricalID, uz_ControlState_get_ControlFlags(self->ControlState));

	//Step the function
	uz_ElectricalID_step(self->ElectricalID);

	//Update Control-State-inputs
	uz_ControlState_set_ElectricalID_FOC_output(self->ControlState, *uz_ElectricalID_get_FOC_output(self->ElectricalID));
	uz_ControlState_set_ElectricalID_output(self->ControlState, uz_ElectricalID_get_output(self->ElectricalID));
	uz_ControlState_set_enteredElectricalID(self->ControlState, uz_ElectricalID_get_enteredElectricalID(self->ElectricalID));
	uz_ControlState_set_finishedElectricalID(self->ControlState, uz_ElectricalID_get_finishedElectricalID(self->ElectricalID));
}

static void uz_ParaID_ControlState_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Update Control-State inputs, which are not depended on other states
	uz_ControlState_set_GlobalConfig(self->ControlState, Data->GlobalConfig);

	//Control-State will always be stepped
	uz_ControlState_step(self->ControlState);
}

static void uz_ParaID_FrictionID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Update State-Inputs
	uz_FrictionID_set_ActualValues(self->FrictionID, Data->ActualValues);
	uz_FrictionID_set_Config(self->FrictionID, Data->FrictionID_Config);
	uz_FrictionID_set_GlobalConfig(self->FrictionID, *uz_ControlState_get_GlobalConfig(self->ControlState));
	uz_FrictionID_set_ControlFlags(self->FrictionID, uz_ControlState_get_ControlFlags(self->ControlState));

	//Step the function
	uz_FrictionID_step(self->FrictionID);

	//Update Control-State-inputs
	uz_ControlState_set_enteredFrictionID(self->ControlState, uz_FrictionID_get_enteredFrictionID(self->FrictionID));
	uz_ControlState_set_finishedFrictionID(self->ControlState, uz_FrictionID_get_finishedFrictionID(self->FrictionID));
}

static void uz_ParaID_TwoMassID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Update State-Inputs
	uz_TwoMassID_set_ActualValues(self->TwoMassID, Data->ActualValues);
	uz_TwoMassID_set_Config(self->TwoMassID, Data->TwoMassID_Config);
	uz_TwoMassID_set_GlobalConfig(self->TwoMassID, *uz_ControlState_get_GlobalConfig(self->ControlState));
	uz_TwoMassID_set_ControlFlags(self->TwoMassID, uz_ControlState_get_ControlFlags(self->ControlState));

	//Step the function
	uz_TwoMassID_step(self->TwoMassID);

	//Update Control-State-inputs
	uz_ControlState_set_enteredTwoMassID(self->ControlState, uz_TwoMassID_get_enteredTwoMassID(self->TwoMassID));
	uz_ControlState_set_finishedTwoMassID(self->ControlState, uz_TwoMassID_get_finishedTwoMassID(self->TwoMassID));
}

static void uz_ParaID_FluxMapID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Update State-Inputs
	uz_FluxMapID_set_ActualValues(self->FluxMapID, Data->ActualValues);
	uz_FluxMapID_set_Config(self->FluxMapID, Data->FluxMapID_Config);
	uz_FluxMapID_set_GlobalConfig(self->FluxMapID, *uz_ControlState_get_GlobalConfig(self->ControlState));
	uz_FluxMapID_set_ControlFlags(self->FluxMapID, uz_ControlState_get_ControlFlags(self->ControlState));

	//Step the function
	uz_FluxMapID_step(self->FluxMapID);

	//Update Control-State-inputs
	uz_ControlState_set_enteredFluxMapID(self->ControlState, uz_FluxMapID_get_enteredFluxMapID(self->FluxMapID));
	uz_ControlState_set_finishedFluxMapID(self->ControlState, uz_FluxMapID_get_finishedFluxMapID(self->FluxMapID));
}

static void uz_ParaID_OnlineID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Update State-Inputs
	uz_OnlineID_set_ActualValues(self->OnlineID, Data->ActualValues);
	uz_OnlineID_set_ControlFlags(self->OnlineID, uz_ControlState_get_ControlFlags(self->ControlState));
	uz_OnlineID_set_GlobalConfig(self->OnlineID, *uz_ControlState_get_GlobalConfig(self->ControlState));
	uz_OnlineID_set_Config(self->OnlineID, Data->OnlineID_Config);

	//Step the function
	uz_OnlineID_step(self->OnlineID);

	//Update Data struct with new output values
	
	Data->Controller_Parameters.activeState = uz_OnlineID_get_output(self->OnlineID)->activeState;
	uz_ControlState_set_enteredOnlineID(self->ControlState, uz_OnlineID_get_enteredOnlineID(self->OnlineID));
}

static void uz_ParaID_AutoRefCurrents_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	uz_OnlineID_set_AutoRefCurrents_ControlFlags(self->OnlineID, uz_ControlState_get_ControlFlags(self->ControlState));
	uz_OnlineID_set_AutoRefCurrents_GlobalConfig(self->OnlineID, *uz_ControlState_get_GlobalConfig(self->ControlState));
	uz_OnlineID_AutoRefCurrents_step(self->OnlineID, Data);
}

static void uz_ParaID_FOC_output_set_zero(uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(Data);
	Data->Controller_Parameters.Ki_id_out = 0.0f;
	Data->Controller_Parameters.Ki_iq_out = 0.0f;
	Data->Controller_Parameters.Ki_n_out = 0.0f;
	Data->Controller_Parameters.Kp_id_out = 0.0f;
	Data->Controller_Parameters.Kp_iq_out = 0.0f;
	Data->Controller_Parameters.Kp_n_out = 0.0f;
	Data->Controller_Parameters.enableFOC_current = false;
	Data->Controller_Parameters.enableFOC_speed = false;
	Data->Controller_Parameters.i_dq_ref.d = 0.0f;
	Data->Controller_Parameters.i_dq_ref.q = 0.0f;
	Data->Controller_Parameters.i_dq_ref.zero = 0.0f;
	Data->Controller_Parameters.n_ref_FOC = 0.0f;
	Data->Controller_Parameters.resetIntegrator = false;
}

float uz_ParameterID_correct_LP1_filter(uz_ParameterID_Data_t* Data, float RC) {
	uz_assert_not_NULL(Data);
	float factor = sqrtf(1.0f + powf((Data->ActualValues.omega_el * RC), 2.0f));
	Data->ActualValues.V_abc.a = Data->ActualValues.V_abc.a * factor;
	Data->ActualValues.V_abc.b = Data->ActualValues.V_abc.b * factor;
	Data->ActualValues.V_abc.c = Data->ActualValues.V_abc.c * factor;
	float theta_el_corr =Data->ActualValues.theta_el - atanf(Data->ActualValues.omega_el * RC);
	return(theta_el_corr);
}

void uz_ParameterID_update_transmit_values(uz_ParameterID_Data_t* Data, float *activeState, float *FluxMapCounter, float *ArrayCounter){
	uz_assert_not_NULL(Data);
	uz_assert_not_NULL(activeState);
	uz_assert_not_NULL(FluxMapCounter);
	uz_assert_not_NULL(ArrayCounter);
	*activeState = (float) Data->Controller_Parameters.activeState;
	*FluxMapCounter = (float) Data->FluxMap_counter;
	*ArrayCounter = (float) Data->Array_counter;
    Data->Psi_D_pointer = Data->FluxMap_Data->psid_grid[Data->FluxMap_counter];
	Data->Psi_Q_pointer =  Data->FluxMap_Data->psiq_grid[Data->FluxMap_counter];
	Data->MeasArraySpeed_pointer = Data->FrictionID_Output->measArraySpeed[Data->Array_counter];
	Data->MeasArrayTorque_pointer = Data->FrictionID_Output->measArrayTorque[Data->Array_counter];

}

static void uz_ParameterID_initialize_data_structs(uz_ParameterID_t *self, uz_ParameterID_Data_t *Data) {
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
	Data->ElectricalID_Output = uz_ElectricalID_get_output(self->ElectricalID);
	Data->FrictionID_Output = uz_FrictionID_get_output(self->FrictionID);
	Data->FluxMapID_Output = uz_FluxMapID_get_output(self->FluxMapID);
	Data->TwoMassID_Output = uz_TwoMassID_get_output(self->TwoMassID);
	Data->OnlineID_Output = uz_OnlineID_get_output(self->OnlineID);
	Data->ControlFlags = uz_ControlState_get_ControlFlags(self->ControlState);
	Data->FluxMap_Data = uz_OnlineID_get_InterpMeshGrid_FluxMapData(self->OnlineID);

	Data->calculate_flux_maps = false;
	Data->FluxMap_counter = 0.0f;
	Data->Psi_D_pointer = 0.0f;
	Data->Psi_Q_pointer = 0.0f;
	Data->ParaID_Control_Selection = No_Control;
}

#endif
