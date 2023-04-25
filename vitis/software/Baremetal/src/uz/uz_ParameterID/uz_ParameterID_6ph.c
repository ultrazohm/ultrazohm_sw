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

extern uint16_t scope_selected_subsystem;

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
static void uz_ParameterID_6ph_initialize_data_structs(uz_ParameterID_6ph_t *self, uz_ParameterID_Data_t *Data);
static void uz_ParameterID_reset_controllers(uz_ParameterID_Data_t* Data);

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
		uz_encoder_offset_estimation_reset_states(Data->encoder_offset_estimation);
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

struct uz_DutyCycle_2x3ph_t uz_ParameterID_6ph_generate_DutyCycle(uz_ParameterID_Data_t* Data, uz_6ph_dq_t v_dq_Volts) {
	uz_assert_not_NULL(Data);
	uz_6ph_abc_t V_abc_Volts = {0};
	struct uz_DutyCycle_2x3ph_t output_DutyCycle = { 0 };
	
	// during step responses use directly the given DutyCycles
    if (Data->Controller_Parameters.activeState >= 110 && Data->Controller_Parameters.activeState <= 148) {
		output_DutyCycle.system1.DutyCycle_A = Data->ElectricalID_Output->PWM_Switch_0;
		output_DutyCycle.system1.DutyCycle_B = Data->ElectricalID_Output->PWM_Switch_2;
		output_DutyCycle.system1.DutyCycle_C = Data->ElectricalID_Output->PWM_Switch_4;
		output_DutyCycle.system2.DutyCycle_A = Data->ElectricalID_Output->PWM_Switch_a2;
		output_DutyCycle.system2.DutyCycle_B = Data->ElectricalID_Output->PWM_Switch_b2;
		output_DutyCycle.system2.DutyCycle_C = Data->ElectricalID_Output->PWM_Switch_c2;
	
	// during zero fluxmap everything changes
	} else if(Data->FluxmapID_extended_controller_Output->selected_subsystem == 3){
		V_abc_Volts.a1 = 3.0f/2.0f*v_dq_Volts.z1;
		V_abc_Volts.c1 = -V_abc_Volts.a1;
		V_abc_Volts.a2 = 3.0f/2.0f*v_dq_Volts.z2;
		V_abc_Volts.c2 = -V_abc_Volts.a2;
		output_DutyCycle = uz_FOC_generate_DutyCycles_6ph(V_abc_Volts, Data->ActualValues.V_DC); 
	
	// during normal operation give out calculated dutycycles from setpoints
	} else if ((Data->FluxmapID_extended_controller_Output->selected_subsystem == 1) || (Data->FluxmapID_extended_controller_Output->selected_subsystem == 2) || (Data->Controller_Parameters.enableFOC_current == true || Data->Controller_Parameters.enableFOC_speed == true)
	                || (Data->ControlFlags->finished_all_Offline_states == true && (Data->ParaID_Control_Selection == Current_Control || Data->ParaID_Control_Selection == Speed_Control))) {
		V_abc_Volts = uz_transformation_asym30deg_6ph_dq_to_abc(v_dq_Volts, Data->ActualValues.theta_el);
		output_DutyCycle = uz_FOC_generate_DutyCycles_6ph(V_abc_Volts, Data->ActualValues.V_DC); 
	
	// anything else, set zero
	} else {
		output_DutyCycle.system1.DutyCycle_A = 0.0f;
		output_DutyCycle.system1.DutyCycle_B = 0.0f;
		output_DutyCycle.system1.DutyCycle_C = 0.0f;
		output_DutyCycle.system2.DutyCycle_A = 0.0f;
		output_DutyCycle.system2.DutyCycle_B = 0.0f;
		output_DutyCycle.system2.DutyCycle_C = 0.0f;
	}

	// if integrators are reset, also set zero
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

uz_6ph_dq_t uz_ParameterID_6ph_Controller(uz_ParameterID_Data_t* Data) {
	uz_6ph_dq_t out = {0};
	uz_3ph_dq_t v_dq_Volts = {0};
	uz_assert_not_NULL(Data);
	uz_assert_not_NULL(Data->cc_instance_1);
	uz_assert_not_NULL(Data->cc_instance_2);
	uz_assert_not_NULL(Data->resonant_instance_1);
	uz_assert_not_NULL(Data->resonant_instance_2);
	uz_assert_not_NULL(Data->speed_instance);
	uz_assert_not_NULL(Data->setpoint_instance);
	uz_3ph_dq_t i_SpeedControl_reference_Ampere = { 0 };
	float SpeedControl_reference_torque = 0.0f;

	// Speed control active
	if (Data->Controller_Parameters.enableFOC_speed == true) {
		//Change, if desired, the speed controller here
		uz_SpeedControl_set_ext_clamping(Data->speed_instance, uz_CurrentControl_get_ext_clamping(Data->cc_instance_1));
		SpeedControl_reference_torque = uz_SpeedControl_sample(Data->speed_instance, Data->ActualValues.omega_m, Data->Controller_Parameters.n_ref_FOC);
		i_SpeedControl_reference_Ampere = uz_SetPoint_sample(Data->setpoint_instance, Data->ActualValues.omega_m, SpeedControl_reference_torque, Data->ActualValues.V_DC, Data->ActualValues.i_dq);
		i_SpeedControl_reference_Ampere.q += Data->TwoMassID_Output->PRBS_out;
	}

	// Torque control active
	if (Data->Controller_Parameters.enableFOC_torque == true) {
		i_SpeedControl_reference_Ampere = uz_SetPoint_sample(Data->setpoint_instance, Data->ActualValues.omega_m, Data->Controller_Parameters.M_ref_FOC, Data->ActualValues.V_DC, Data->ActualValues.i_dq);
	}

	// any control active
	if (Data->Controller_Parameters.enableFOC_current || Data->Controller_Parameters.enableFOC_speed || Data->Controller_Parameters.enableFOC_torque) {
		//Change, if desired, the current controller here
		if (Data->Controller_Parameters.enableFOC_current) {
			//If CurrentControl is active, use input reference currents
			v_dq_Volts = uz_CurrentControl_sample(Data->cc_instance_1, Data->Controller_Parameters.i_dq_ref, Data->ActualValues.i_dq, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
		} else if (Data->Controller_Parameters.enableFOC_torque || Data->Controller_Parameters.enableFOC_speed) {
			//If SetPoint or SpeedControl & SetPoint is active, use Setpoint currents
			v_dq_Volts = uz_CurrentControl_sample(Data->cc_instance_1, i_SpeedControl_reference_Ampere, Data->ActualValues.i_dq, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
		}
		out.d = v_dq_Volts.d;
		out.q = v_dq_Volts.q;
	}

	// reset all integrators and controllers
	if (Data->Controller_Parameters.resetIntegrator == true) {
		uz_ParameterID_reset_controllers(Data);
	}

	// configure fundamental controllers
	if (Data->ControlFlags->transNr > 0U && Data->ControlFlags->transNr <= 4U) {
		if (Data->Controller_Parameters.activeState == 148U) {
			uz_CurrentControl_set_decoupling_method(Data->cc_instance_1, no_decoupling);
		} else if (Data->Controller_Parameters.activeState == 170U) {
			uz_CurrentControl_set_decoupling_method(Data->cc_instance_1, linear_decoupling);
		}
		uz_CurrentControl_set_Kp_id(Data->cc_instance_1, Data->Controller_Parameters.Kp_id_out);
		uz_CurrentControl_set_Kp_iq(Data->cc_instance_1, Data->Controller_Parameters.Kp_iq_out);
		uz_CurrentControl_set_Ki_id(Data->cc_instance_1, Data->Controller_Parameters.Ki_id_out);
		uz_CurrentControl_set_Ki_iq(Data->cc_instance_1, Data->Controller_Parameters.Ki_iq_out);
		uz_SpeedControl_set_Ki(Data->speed_instance, Data->Controller_Parameters.Ki_n_out);
		uz_SpeedControl_set_Kp(Data->speed_instance, Data->Controller_Parameters.Kp_n_out);
	}
	return (out);
}

static void uz_ParameterID_reset_controllers(uz_ParameterID_Data_t* Data){
	uz_CurrentControl_reset(Data->cc_instance_1);
	uz_CurrentControl_reset(Data->cc_instance_2);
	uz_resonantController_reset(Data->resonant_instance_1);
	uz_resonantController_reset(Data->resonant_instance_2);
	uz_SpeedControl_reset(Data->speed_instance);
}

static void uz_ParaID_6ph_ElectricalID_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Data);
	//Step the function
	uz_ElectricalID_6ph_step(self->ElectricalID, Data->ElectricalID_Config, Data->ActualValues, Data->GlobalConfig, *Data->ControlFlags, Data->ElectricalID_FFT);
	
	// extended encoder offset estimation
	if(Data->Controller_Parameters.activeState==165U){
		uz_encoder_offset_estimation_reset_states(Data->encoder_offset_estimation);
		uz_encoder_offset_estimation_set_min_omega_el(Data->encoder_offset_estimation, 0.25f*Data->GlobalConfig.ratSpeed/60.0f*2.0f*UZ_PIf*Data->GlobalConfig.PMSM_config.polePairs);
		uz_encoder_offset_estimation_set_setpoint_current(Data->encoder_offset_estimation, Data->ElectricalID_Config.goertzlTorque);
	}
	if(Data->Controller_Parameters.activeState==166U){
		Data->Controller_Parameters.i_dq_ref = uz_encoder_offset_estimation_step(Data->encoder_offset_estimation);
		Data->finished_extended_offset_estimation = uz_encoder_offset_estimation_get_finished(Data->encoder_offset_estimation);
	}

	//Update Control-State-inputs
	uz_ControlState_set_ElectricalID_FOC_output(self->ControlState, *uz_get_ElectricalID_6ph_FOCoutput(self->ElectricalID));
	uz_ControlState_set_ElectricalID_output(self->ControlState, uz_get_ElectricalID_6ph_output(self->ElectricalID));
	uz_ControlState_set_enteredElectricalID(self->ControlState, uz_get_ElectricalID_6ph_entered(self->ElectricalID));
	uz_ControlState_set_finishedElectricalID(self->ControlState, uz_get_ElectricalID_6ph_finished(self->ElectricalID));
	Data->finished_voltage_measurement = uz_get_ElectricalID_6ph_finished_voltage_measurement(self->ElectricalID);
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
	//Data->FluxMapID_Config.selected_subsystem = scope_selected_subsystem;
	Data->FluxMapID_Config.lower_meas_temp = 40.0f;
	Data->FluxMapID_Config.upper_meas_temp = 45.0f;


	//Step the function
	uz_FluxMapID_6ph_step(self->FluxMapID, Data->FluxMapID_Config, Data->ActualValues, Data->GlobalConfig, *Data->ControlFlags, Data->feedback_printed);

	//Update Control-State-inputs
	uz_ControlState_set_enteredFluxMapID(self->ControlState, uz_get_FluxMapID_6ph_entered(self->FluxMapID));
	uz_ControlState_set_finishedFluxMapID(self->ControlState, uz_get_FluxMapID_6ph_finished(self->FluxMapID));
}

void uz_ParameterID_6ph_update_transmit_values(uz_ParameterID_Data_t* Data, float *activeState, float *FluxMapCounter, float *ArrayCounter)
{
	uz_ParameterID_update_transmit_values(Data, activeState, FluxMapCounter, ArrayCounter);
}

void uz_ParameterID_6ph_calculate_PsiPMs(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t *Data, float *meas_array){
	uz_assert_not_NULL(self);
	if(Data->finished_voltage_measurement && Data->Controller_Parameters.activeState==156U)
        {
			uz_get_ElectricalID_6ph_fft_out(self->ElectricalID, meas_array);
        	uz_ParaID_ElectricalID_fft_in_t uncorrected = uz_calculate_psi_pms_ElectricalID(meas_array, Data->GlobalConfig.sampleTimeISR);
        	Data->ElectricalID_FFT = uz_correct_psi_pms_ElectricalID(uncorrected, Data->GlobalConfig, PARAMETERID6PH_ELECTRICAL_N_ORDER);
        	//print_paraID(uncorrected, Data->ElectricalID_FFT, Data->ElectricalID_Output);
        }
	else{
		Data->ElectricalID_FFT.finished_flag = false;
	}
}

bool uz_ParameterID_6ph_transmit_FluxMap_to_Console(uz_ParameterID_Data_t* Data, int js_cnt_slowData){
	bool feedback_printed = false;
	bool logging_flag = uz_FluxMapID_6ph_transmit_calculated_values(Data->FluxmapID_extended_controller_Output, &feedback_printed, Data->Controller_Parameters.activeState, js_cnt_slowData);
	Data->feedback_printed = feedback_printed;
	return (logging_flag);
}

void uz_ParameterID_6ph_initialize_encoder_offset_estimation(uz_ParameterID_Data_t *Data, float* raw_rotor_angle){
	struct uz_encoder_offset_estimation_config offset_estimation_config = {
		.ptr_measured_rotor_angle = raw_rotor_angle,
		.ptr_offset_angle = &Data->ElectricalID_Output->thetaOffset,
		.ptr_actual_omega_el = &Data->ActualValues.omega_el,
		.ptr_actual_u_q_V = &Data->ActualValues.v_dq.q,
		.setpoint_current = 1.0f,
		.min_omega_el = 1.0f};
	Data->encoder_offset_estimation = uz_encoder_offset_estimation_init(offset_estimation_config);
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
	Data->ElectricalID_Config.goertzlTorque = 0.0f;
	Data->ElectricalID_Config.identLq = false;
	Data->ElectricalID_Config.min_n_ratio = 0.015f;
	Data->ElectricalID_Config.n_ref_measurement = 0.0f;
	Data->ElectricalID_Config.extended_psi = false;
	Data->ElectricalID_Config.extended_offset = false;
	Data->ElectricalID_Config.manual_offset = -1.0f;

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
	Data->FluxmapID_extended_controller_Output = uz_get_FluxMapID_6ph_extended_controller_output(self->FluxMapID);
	Data->TwoMassID_Output = uz_TwoMassID_get_output(self->TwoMassID);
	Data->OnlineID_Output = uz_OnlineID_get_output(self->OnlineID);
	Data->ControlFlags = uz_ControlState_get_ControlFlags(self->ControlState);
	Data->FluxMap_Data = uz_OnlineID_get_InterpMeshGrid_FluxMapData(self->OnlineID);

	Data->calculate_flux_maps = false;
	Data->FluxMap_counter = 0.0f;
	Data->Psi_D_pointer = 0.0f;
	Data->Psi_Q_pointer = 0.0f;
	Data->ParaID_Control_Selection = No_Control;

	//initialize flags
	Data->ElectricalID_FFT.finished_flag = false;
	Data->finished_extended_offset_estimation = false;

	// controller instances
	Data->setpoint_instance = NULL;
	Data->speed_instance = NULL;
	Data->cc_instance_1 = NULL;
	Data->cc_instance_2 = NULL;
	Data->resonant_instance_1 = NULL;
	Data->resonant_instance_2 = NULL;
	Data->encoder_offset_estimation = NULL;
}

#endif
