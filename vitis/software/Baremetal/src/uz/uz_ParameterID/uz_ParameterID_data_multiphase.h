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

#ifndef UZ_PARAMETERID6PH_DATA_MULTIPHASE_H
#define UZ_PARAMETERID6PH_DATA_MULTIPHASE_H

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "rtwtypes.h"
#include <stdbool.h>

//----------------------------------------//
//----------------------------------------//
//------------GlobalStructs---------------//
//----------------------------------------//
//----------------------------------------//

/**
 * @brief Global configuration struct for general settings of the ParameterID
 *
 */
typedef struct {
  uz_PMSM_t PMSM_config; /**< motor related parameters. Is needed, if ElectricalID should not be executed */
  uz_9ph_dq_t inductance;
  boolean_T enableParameterID; /**< flag to enable the entire ParameterID */
  boolean_T Reset; /**< flag to Reset the entire ParameterID*/
  boolean_T ElectricalID; /**< flag to enable ElectricalID */
  boolean_T FrictionID; /**< flag to enable FrictionID */
  boolean_T TwoMassID; /**< flag to enable TwoMassID */
  boolean_T FluxMapID; /**< flag to enable FluxMapID */
  boolean_T OnlineID; /**< flag to enable OnlineID */
  boolean_T ACCEPT; /**< flag for the ACCEPT button  */
  real32_T sampleTimeISR; /**< sampleTime of the ISR. i.e. sampleTime of the function call uz_ParameterID_step. Very important parameter */
  real32_T ratCurrent; /**< rated current of the motor */
  real32_T ratTorque; /**< rated torque of the motor */
  real32_T ratSpeed; /**< rated speed of the motor */
} uz_ParaID6ph_GlobalConfig_t;

/**
 * @brief struct for the measured values which are needed for the ParameterID
 *
 */
typedef struct {
  uz_6ph_abc_t V_abc; /**< measured three-phase voltages */
  uz_6ph_abc_t I_abc; /**< measured three-phase currents */
  uz_6ph_dq_t i_dq; /**< measured dq voltages */
  uz_6ph_dq_t v_dq; /**< measured dq currents */
  real32_T omega_m; /**< measured mechanical omega */
  real32_T omega_el; /**< measured electrical omega */
  real32_T theta_m; /**< measured mechanical theta */
  real32_T theta_el; /**< measured electrical theta */
  real32_T V_DC; /**< measured DC-link voltage */
} uz_ParaID6ph_ActualValues_t;

//----------------------------------------//
//----------------------------------------//
//------------ElectricalID----------------//
//----------------------------------------//
//----------------------------------------//

/**
 * @brief output struct of ElectricalID
 *
 */
typedef struct {
  real32_T PWM_Switch_a1;
  real32_T PWM_Switch_b1;
  real32_T PWM_Switch_c1;
  real32_T PWM_Switch_a2;
  real32_T PWM_Switch_b2;
  real32_T PWM_Switch_c2;
  boolean_T enable_TriState[3]; /**< array to signal which halfbridge of the inverter should be in tristate mode. true signals, that the halfbridge should be in tristate mode. (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T thetaOffset; /**< determined offset of theta in rad */
  uz_PMSM_t PMSM_parameters; /**< identified motor parameters */
} uz_ParaID_ElectricalID6ph_output_t;

//----------------------------------------//
//----------------------------------------//
//--------ParameterID_Data struct---------//
//----------------------------------------//
//----------------------------------------//

/*! enum for selection of control algorithm if all OfflineID states are finished */
enum uz_ParaID_Control_selection {
	No_Control = 0, Current_Control, Speed_Control
};

/**
 * @brief Data struct to share inputs and outputs to the encapsuled uz_ParameterID_t object
 *
 */
typedef struct uz_ParameterID6ph_Data_t {
	uz_ParaID6ph_ActualValues_t ActualValues; /**<Input: measured values needed for the ParameterID */
	uz_ParaID_ControlFlags_t* ControlFlags; /**<Output: current values of the ControlFlags struct */
	uz_ParaID6ph_GlobalConfig_t GlobalConfig; /**<Input: Global configuration struct for general settings of the ParameterID */
	uz_ParaID_ElectricalIDConfig_t ElectricalID_Config; /**<Input: Configuration struct for ElectricalID */
	uz_ParaID_TwoMassIDConfig_t TwoMassID_Config; /**<Input: Configuration struct for TwoMassID */
	uz_ParaID_FrictionIDConfig_t FrictionID_Config; /**<Input: Configuration struct for FrictionID */
	uz_ParaID_FluxMapIDConfig_t FluxMapID_Config; /**< Input:Configuration struct for FluxMapID */
	uz_ParaID_OnlineIDConfig_t OnlineID_Config; /**<Input: Configuration struct for  OnlineID */
	uz_ParaID_AutoRefCurrentsConfig_t AutoRefCurrents_Config; /**<Input: Configuration struct for AutoReference current generator */
	uz_ParaID_ElectricalID6ph_output_t *ElectricalID_Output; /**<Output: Pointer to output struct of ElectricalID */
	uz_ParaID_TwoMassID_output_t *TwoMassID_Output; /**<Output: Pointer to output struct of TwoMassID */
	uz_ParaID_FrictionID_output_t *FrictionID_Output; /**<Output: Pointer to output struct of FrictionID */
	uz_ParaID_FluxMapID_output_t *FluxMapID_Output; /**<Output: Pointer to output struct of FluxMapID */
	uz_ParaID_OnlineID_output_t* OnlineID_Output; /**<Output: Pointer to output struct of OnlineID */
	uz_ParaID_Controller_Parameters_output_t Controller_Parameters;/**<Output: output struct for control algorithm (i_dq_ref / n_ref etc.) */
	uz_ParaID_AutoRefCurrents_output_t AutoRefCurrents_Output; /**<Output: output struct for reference currents of the AutoReference current generator*/
	uz_ParaID_FluxMapsData_t* FluxMap_Data; /**<Storage for calculated OnlineID FluxMaps*/
	bool calculate_flux_maps; /**<status bool to signal, that the OnlineID FluxMaps should be calculated */
	int FluxMap_counter; /**<counter to transmit FluxMaps 1by1 to the uz_GUI */
	int FluxMap_Control_counter; /**<control counter from the GUI to sync the FluxMaps counter */
	float Psi_D_pointer; /**<current value of the FluxMap array corresponding to the value of the FluxMap_counter*/
	float Psi_Q_pointer; /**<current value of the FluxMap array corresponding to the value of the FluxMap_counter*/
	int Array_counter; /**<counter to transmit meas arrays of FrictionID 1by1 to the uz_GUI */
	int Array_Control_counter; /**<control counter from the GUI to sync the array_counter */
	float MeasArraySpeed_pointer; /**< current value of the MeasSpeedArray corresponding to the value of the array_counter*/
	float MeasArrayTorque_pointer; /**< current value of the MeasTorqueArray corresponding to the value of the array_counter*/
	float FluxMap_MeasuringPoints; /**<amount of unique measuring points for the FluxMaps */
	enum uz_ParaID_Control_selection ParaID_Control_Selection;/**< ParaID_Control_Selection \n
													0 = No_Control \n
													1 = Current_Control \n
													2 = Speed_Control*/
} uz_ParameterID6ph_Data_t;

#endif
