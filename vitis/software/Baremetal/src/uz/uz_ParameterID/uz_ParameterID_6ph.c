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
#include "uz_ParameterID.h"

typedef struct uz_ParameterID_6ph_t {
	bool is_ready;
	uz_ParaID_ControlState_t* ControlState;
	uz_ParaID_ElectricalID_6ph_t* ElectricalID;
	uz_ParaID_TwoMassID_t* TwoMassID;
	uz_ParaID_FrictionID_t* FrictionID;
	uz_ParaID_FluxMapID_6ph_t* FluxMapID;
	uz_ParaID_OnlineID_t* OnlineID;
} uz_ParameterID_6ph_t;

static uint32_t instances_counter_ParameterID_6ph = 0;
static uz_ParameterID_6ph_t instances_ParameterID_6ph[UZ_PARAMETERID_6PH_MAX_INSTANCES] = { 0 };

static void uz_ParaID_6ph_ControlState_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_6ph_ElectricalID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_6ph_FrictionID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_6ph_TwoMassID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_6ph_FluxMapID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);
static void uz_ParaID_6ph_FOC_output_set_zero(uz_ParameterID_Data_t* Data);
static void uz_ParaID_6ph_AutoRefCurrents_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);
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
	self->FluxMapID = uz_FluxMapID_6ph_init();
	self->OnlineID = uz_OnlineID_init();
	uz_ParameterID_6ph_initialize_data_structs(self, Data);
	return (self);
}

void uz_ParameterID_6ph_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	uz_assert(self->is_ready);
	uz_ParaID_6ph_ControlState_step(self, Data);


	if (uz_ControlState_get_ControlFlags(self->ControlState)->finished_all_Offline_states == false) {
	//if (self->ControlState->output.ControlFlags.finished_all_Offline_states == false) {

		//ElectricalID
		if (uz_ControlState_get_ControlFlags(self->ControlState)->transNr == 1U || uz_ControlState_get_GlobalConfig(self->ControlState)->Reset == true) {
			uz_ParaID_6ph_ElectricalID_step(self, Data);
		} else if (uz_ControlState_get_GlobalConfig(self->ControlState)->ElectricalID == false && uz_get_ElectricalID_6ph_entered(self->ElectricalID) == true) {
			uz_ParaID_6ph_ElectricalID_step(self, Data);
		}

		//TwoMassID
		if (uz_ControlState_get_ControlFlags(self->ControlState)->transNr == 2U || uz_ControlState_get_GlobalConfig(self->ControlState)->Reset == true) {
			uz_ParaID_6ph_TwoMassID_step(self, Data);
		} else if (uz_ControlState_get_GlobalConfig(self->ControlState)->TwoMassID == false && uz_TwoMassID_get_enteredTwoMassID(self->TwoMassID) == true) {
			uz_ParaID_6ph_TwoMassID_step(self, Data);
		}

		//FrictionID
		if (uz_ControlState_get_ControlFlags(self->ControlState)->transNr == 3U || uz_ControlState_get_GlobalConfig(self->ControlState)->Reset == true) {
			uz_ParaID_6ph_FrictionID_step(self, Data);
			if (Data->Array_counter < 256 && (Data->Array_counter == Data->Array_Control_counter)) {
				Data->Array_counter += 1;
			} else if (Data->Array_counter == 256){
				Data->Array_counter = 0;
			}
		} else if (uz_ControlState_get_GlobalConfig(self->ControlState)->FrictionID == false && uz_FrictionID_get_enteredFrictionID(self->FrictionID) == true) {
			uz_ParaID_6ph_FrictionID_step(self, Data);
		}

		//FluxMapID
		if (uz_ControlState_get_ControlFlags(self->ControlState)->transNr == 4U || uz_ControlState_get_GlobalConfig(self->ControlState)->Reset == true) {
			uz_ParaID_6ph_FluxMapID_step(self, Data);
		} else if (uz_ControlState_get_GlobalConfig(self->ControlState)->FluxMapID == false && uz_get_FluxMapID_6ph_entered(self->FluxMapID) == true) {
			uz_ParaID_6ph_FluxMapID_step(self, Data);
		}
	}

	//FOC output
	switch (uz_ControlState_get_ControlFlags(self->ControlState)->transNr) {

	case 1U:
		Data->Controller_Parameters = *uz_get_ElectricalID_6ph_FOCoutput(self->ElectricalID);
		break;

	case 2U:
		Data->Controller_Parameters = *uz_TwoMassID_get_FOC_output(self->TwoMassID);
		break;

	case 3U:
		Data->Controller_Parameters = *uz_FrictionID_get_FOC_output(self->FrictionID);
		break;

	case 4U:
		Data->Controller_Parameters = *uz_get_FluxMapID_6ph_FOCoutput(self->FluxMapID);
		break;

	default:
		uz_ParaID_6ph_FOC_output_set_zero(Data);
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

static void uz_ParaID_6ph_FOC_output_set_zero(uz_ParameterID_Data_t* Data) {
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

static void uz_ParaID_6ph_AutoRefCurrents_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	uz_OnlineID_set_AutoRefCurrents_ControlFlags(self->OnlineID, uz_ControlState_get_ControlFlags(self->ControlState));
	uz_OnlineID_set_AutoRefCurrents_GlobalConfig(self->OnlineID, *uz_ControlState_get_GlobalConfig(self->ControlState));
	uz_OnlineID_AutoRefCurrents_step(self->OnlineID, Data);
}

struct uz_DutyCycle_2x3ph_t uz_ParameterID_6ph_generate_DutyCycle(uz_ParameterID_Data_t* Data, uz_6ph_dq_t v_dq_Volts) {
	uz_assert_not_NULL(Data);
	struct uz_DutyCycle_2x3ph_t output_DutyCycle = { 0 };
	uz_3ph_abc_t system1 = {0};
	uz_3ph_abc_t system2 = {0};
	if (Data->Controller_Parameters.activeState >= 110 && Data->Controller_Parameters.activeState <= 151) {
		output_DutyCycle.system1.DutyCycle_A = Data->ElectricalID_Output->PWM_Switch_0;
		output_DutyCycle.system1.DutyCycle_B = Data->ElectricalID_Output->PWM_Switch_2;
		output_DutyCycle.system1.DutyCycle_C = Data->ElectricalID_Output->PWM_Switch_4;
		output_DutyCycle.system2.DutyCycle_A = Data->ElectricalID_Output->PWM_Switch_a2;
		output_DutyCycle.system2.DutyCycle_B = Data->ElectricalID_Output->PWM_Switch_b2;
		output_DutyCycle.system2.DutyCycle_C = Data->ElectricalID_Output->PWM_Switch_c2;
	} else if ((Data->Controller_Parameters.enableFOC_current == true || Data->Controller_Parameters.enableFOC_speed == true)
	                || (Data->ControlFlags->finished_all_Offline_states == true && (Data->ParaID_Control_Selection == Current_Control || Data->ParaID_Control_Selection == Speed_Control))) {
		uz_6ph_abc_t V_abc_Volts = uz_transformation_asym30deg_6ph_dq_to_abc(v_dq_Volts, Data->ActualValues.theta_el);
		system1.a = V_abc_Volts.a1;
		system1.b = V_abc_Volts.b1;
		system1.c = V_abc_Volts.c1;
		system2.a = V_abc_Volts.a2;
		system2.b = V_abc_Volts.b2;
		system2.c = V_abc_Volts.c2;
		output_DutyCycle.system1 = uz_Space_Vector_Modulation(uz_transformation_3ph_abc_to_dq(system1, Data->ActualValues.theta_el), Data->ActualValues.V_DC, Data->ActualValues.theta_el); 
		output_DutyCycle.system2 = uz_Space_Vector_Modulation(uz_transformation_3ph_abc_to_dq(system2, Data->ActualValues.theta_el), Data->ActualValues.V_DC, Data->ActualValues.theta_el); 
	} else {
		output_DutyCycle.system1.DutyCycle_A = 0.0f;
		output_DutyCycle.system1.DutyCycle_B = 0.0f;
		output_DutyCycle.system1.DutyCycle_C = 0.0f;
		output_DutyCycle.system2.DutyCycle_A = 0.0f;
		output_DutyCycle.system2.DutyCycle_B = 0.0f;
		output_DutyCycle.system2.DutyCycle_C = 0.0f;
	}
	if (Data->Controller_Parameters.resetIntegrator == true) {
		output_DutyCycle.system1.DutyCycle_A = 0.0f;
		output_DutyCycle.system1.DutyCycle_B = 0.0f;
		output_DutyCycle.system1.DutyCycle_C = 0.0f;
		output_DutyCycle.system2.DutyCycle_A = 0.0f;
		output_DutyCycle.system2.DutyCycle_B = 0.0f;
		output_DutyCycle.system2.DutyCycle_C = 0.0f;
	}
	return (output_DutyCycle);
}
/*
uz_6ph_dq_t uz_ParameterID_6ph_Controller_FluxMapID(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance_dq1, uz_CurrentControl_t* CC_instance_dq2, uz_resonantController_t* resonant_dq1, uz_resonantController_t* resonant_dq2)
{
	static uz_3ph_dq_t actual_dq1 = {0}; // actual values mapped to appropriate struct 
	static uz_3ph_dq_t actual_dq2 = {0}; // actual values mapped to appropriate struct 
	static uz_3ph_alphabeta_t actual_ab2 = {0}; // actual values mapped to appropriate struct 
	actual_dq1.d = Data->ActualValues.i_dq_6ph.d; // mapping multiphase dq to threephase dq
	actual_dq1.q = Data->ActualValues.i_dq_6ph.q; // mapping multiphase dq to threephase dq
	actual_ab2.alpha = Data->ActualValues.i_dq_6ph.x;
	actual_ab2.beta = Data->ActualValues.i_dq_6ph.y;
	actual_dq2 = uz_transformation_3ph_alphabeta_to_dq(actual_ab2, Data->ActualValues.theta_el*Data->FluxmapID_extended_controller_Output.xy.theta_factor);
	// set configs, flag will be reset after start of FluxMapID
	if(Data->FluxmapID_extended_controller_Output.controllers_running)
	{
		// set configs for PI controllers fundamental
		uz_CurrentControl_set_Kp_id(CC_instance_dq1, Data->FluxmapID_extended_controller_Output.ab.config_PI.config_id.Kp);
		uz_CurrentControl_set_Ki_id(CC_instance_dq1, Data->FluxmapID_extended_controller_Output.ab.config_PI.config_id.Ki);
		uz_CurrentControl_set_Kp_iq(CC_instance_dq1, Data->FluxmapID_extended_controller_Output.ab.config_PI.config_iq.Kp);
		uz_CurrentControl_set_Ki_iq(CC_instance_dq1, Data->FluxmapID_extended_controller_Output.ab.config_PI.config_iq.Ki);
		// set configs for PI controllers 3rd
		uz_CurrentControl_set_Kp_id(CC_instance_dq2, Data->FluxmapID_extended_controller_Output.xy.config_PI.config_id.Kp);
		uz_CurrentControl_set_Ki_id(CC_instance_dq2, Data->FluxmapID_extended_controller_Output.xy.config_PI.config_id.Ki);
		uz_CurrentControl_set_Kp_iq(CC_instance_dq2, Data->FluxmapID_extended_controller_Output.xy.config_PI.config_iq.Kp);
		uz_CurrentControl_set_Ki_iq(CC_instance_dq2, Data->FluxmapID_extended_controller_Output.xy.config_PI.config_iq.Ki);
		// set configs for resonant controllers
		uz_resonantController_set_config(resonant_dq1, Data->FluxmapID_extended_controller_Output.ab.config_Res);
		uz_resonantController_set_config(resonant_dq2, Data->FluxmapID_extended_controller_Output.xy.config_Res);
	}
	// normal operation
	else
	{
		uz_CurrentControl_sample(CC_instance_dq1, Data->FluxmapID_extended_controller_Output.ab.i_dq_PI_ref, actual_ab, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
		uz_CurrentControl_sample(CC_instance_dq2, Data->FluxmapID_extended_controller_Output.xy.i_dq_PI_ref, actual_xy, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
		uz_resonantController_step(resonant_dq1, Data->FluxmapID_extended_controller_Output.ab.i_dq_PI_ref, ,);

	}
}
*/

uz_6ph_dq_t uz_ParameterID_6ph_Controller(uz_ParameterID_Data_t* Data, uz_CurrentControl_t** CC_instance_1, uz_CurrentControl_t** CC_instance_2, uz_SpeedControl_t* Speed_instance, uz_SetPoint_t* SP_instance, uz_resonantController_t** res_instance_1, uz_resonantController_t** res_instance_2) {
	uz_6ph_dq_t out = {0};
	static bool controllers_initialized = false;
	if(Data->FluxmapID_extended_controller_Output->control_active == true)
	{
		if((Data->FluxmapID_extended_controller_Output->selected_subsystem == 0) && !controllers_initialized)
		{
			uz_FluxMapID_6ph_init_controllers(Data->GlobalConfig, &CC_instance_1, &CC_instance_2, &res_instance_1, &res_instance_2);
			controllers_initialized = true;	
		}
		else
		{
			out = uz_FluxMapID_6ph_step_controllers(Data, *CC_instance_1, *CC_instance_2, *res_instance_1, *res_instance_2);
		}
	}
	else
	{
		uz_3ph_dq_t v_dq_Volts =  uz_ParameterID_Controller(Data, CC_instance_1, Speed_instance, SP_instance);
		out.d = v_dq_Volts.d;
		out.q = v_dq_Volts.q;
		out.x = 0.0f;
		out.y = 0.0f;
		out.z1 = 0.0f;
		out.z2 = 0.0f;
		controllers_initialized = false;
	}
	return (out);
}

/*
void uz_ParameterID_CleanPsiArray(uz_ParameterID_6ph_t *self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	uz_assert(self->is_ready);
	uz_OnlineID_CleanPsiArray(self->OnlineID, Data);
}

void uz_ParameterID_CalcFluxMaps(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	uz_assert(self->is_ready);
	uz_OnlineID_CalcFluxMaps(self->OnlineID, Data);
}
*/

static void uz_ParaID_6ph_ElectricalID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Step the function
	uz_ElectricalID_6ph_step(self->ElectricalID, Data->ElectricalID_Config, Data->ActualValues, Data->GlobalConfig, *Data->ControlFlags, Data->ElectricalID_FFT);

	//Update Control-State-inputs
	uz_ControlState_set_ElectricalID_FOC_output(self->ControlState, *uz_get_ElectricalID_6ph_FOCoutput(self->ElectricalID));
	uz_ControlState_set_ElectricalID_output(self->ControlState, uz_get_ElectricalID_6ph_output(self->ElectricalID));
	uz_ControlState_set_enteredElectricalID(self->ControlState, uz_get_ElectricalID_6ph_entered(self->ElectricalID));
	uz_ControlState_set_finishedElectricalID(self->ControlState, uz_get_ElectricalID_6ph_finished(self->ElectricalID));
	Data->finished_voltage_measurement = uz_get_ElectricalID_6ph_finished_voltage_measurement(self->ElectricalID);
}

void uz_ParameterID_6ph_transmit_measured_voltages(uz_ParameterID_6ph_t* self, float *destination){
	uz_assert_not_NULL(self);
	uz_get_ElectricalID_6ph_fft_out(self->ElectricalID, destination);
}

static void uz_ParaID_6ph_ControlState_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Update Control-State inputs, which are not depended on other states
	uz_ControlState_set_GlobalConfig(self->ControlState, Data->GlobalConfig);

	//Control-State will always be stepped
	uz_ControlState_step(self->ControlState);
}

static void uz_ParaID_6ph_FrictionID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
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

static void uz_ParaID_6ph_TwoMassID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
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

static void uz_ParaID_6ph_FluxMapID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Step the function
	uz_FluxMapID_6ph_step(self->FluxMapID, Data->FluxMapID_Config, Data->ActualValues, Data->GlobalConfig, *Data->ControlFlags);

	//Update Control-State-inputs
	uz_ControlState_set_enteredFluxMapID(self->ControlState, uz_get_FluxMapID_6ph_entered(self->FluxMapID));
	uz_ControlState_set_finishedFluxMapID(self->ControlState, uz_get_FluxMapID_6ph_finished(self->FluxMapID));
}

void uz_ParameterID_6ph_update_transmit_values(uz_ParameterID_Data_t* Data, float *activeState, float *FluxMapCounter, float *ArrayCounter)
{
	uz_ParameterID_update_transmit_values(Data, activeState, FluxMapCounter, ArrayCounter);
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
	Data->GlobalConfig.sampleTimeISR = 100.0e-06f;

	//Initialize motor-related parameters inside Global-Config
	Data->GlobalConfig.Ki_id = 70.0f;
	Data->GlobalConfig.Ki_iq = 70.0f;
	Data->GlobalConfig.Ki_n = 0.8f;
	Data->GlobalConfig.Kp_id = 0.09f;
	Data->GlobalConfig.Kp_iq = 0.08f;
	Data->GlobalConfig.Kp_n = 0.04f;
	Data->GlobalConfig.PMSM_config.Ld_Henry = 0.0918e-03f;
	Data->GlobalConfig.PMSM_config.Lq_Henry = 0.0757e-03f;
	Data->GlobalConfig.PMSM_config.R_ph_Ohm = 0.074f;
	Data->GlobalConfig.PMSM_config.Psi_PM_Vs = 0.0048f;
	Data->GlobalConfig.PMSM_config.polePairs = 5.0f;
	Data->GlobalConfig.PMSM_config.J_kg_m_squared = 3.24e-05f;
	Data->GlobalConfig.PMSM_config.I_max_Ampere = 15.0f;
	Data->GlobalConfig.ratCurrent = 8.0f;
	Data->GlobalConfig.ratTorque = 3.0f;
	Data->GlobalConfig.ratSpeed = 1000.0f;
	Data->GlobalConfig.voltage_measurement_C = 0.012e-6f;
	Data->GlobalConfig.voltage_measurement_Rp = 6650.0f;
	Data->GlobalConfig.voltage_measurement_Rs = 2*78700.0f;

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
	Data->FrictionID_Output = uz_FrictionID_get_output(self->FrictionID);
	Data->FluxMapID_Output = uz_get_FluxMapID_6ph_output(self->FluxMapID);
	Data->TwoMassID_Output = uz_TwoMassID_get_output(self->TwoMassID);
	Data->OnlineID_Output = uz_OnlineID_get_output(self->OnlineID);
	Data->ControlFlags = uz_ControlState_get_ControlFlags(self->ControlState);
	Data->FluxMap_Data = uz_OnlineID_get_InterpMeshGrid_FluxMapData(self->OnlineID);

	Data->calculate_flux_maps = false;
	Data->FluxMap_counter = 0.0f;
	Data->Psi_D_pointer = 0.0f;
	Data->Psi_Q_pointer = 0.0f;
	Data->ParaID_Control_Selection = No_Control;

	//initialize fft in
	Data->ElectricalID_FFT.finished_flag = false;
}

#endif
