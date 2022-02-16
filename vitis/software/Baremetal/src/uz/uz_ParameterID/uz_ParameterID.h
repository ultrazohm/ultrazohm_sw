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
#ifndef UZ_PARAMETERID_H
#define UZ_PARAMETERID_H

#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U

#include "../../globalData.h"
#include <math.h>
#include "../uz_HAL.h"
#include <stdbool.h>
#include "../uz_FOC/uz_FOC.h"
#include "../uz_SpeedControl/uz_speedcontrol.h"
#include "ControlState/uz_PID_ControlState.h"
#include "ElectricalID/uz_PID_ElectricalID.h"
#include "FluxMapID/uz_PID_FluxMapID.h"
#include "FrictionID/uz_PID_FrictionID.h"
#include "OnlineID/uz_PID_OnlineID.h"
#include "TwoMassID/uz_PID_TwoMassID.h"

/**
 * @brief Object definition for uz_ParameterID_t
 * 
 */
typedef struct uz_ParameterID_t uz_ParameterID_t;

/*! enum for selection of control algorithm if all OfflineID states are finished */
enum uz_PID_Control_selection {
	No_Control = 0, Current_Control, Speed_Control
};

/**
 * @brief Data struct to share inputs and outputs to the encapsuled uz_ParameterID_t object
 * 
 */
typedef struct uz_ParameterID_Data_t { 
	uz_PID_ActualValues_t ActualValues; /**<Input: measured values needed for the ParameterID */ 
	uz_PID_ControlFlags_t* ControlFlags; /**<Output: current values of the ControlFlags struct */
	uz_PID_GlobalConfig_t GlobalConfig; /**<Input: Global configuration struct for general settings of the ParameterID */
	uz_PID_ElectricalIDConfig_t ElectricalID_Config; /**<Input: Configuration struct for ElectricalID */
	uz_PID_TwoMassIDConfig_t TwoMassID_Config; /**<Input: Configuration struct for TwoMassID */
	uz_PID_FrictionIDConfig_t FrictionID_Config; /**<Input: Configuration struct for FrictionID */
	uz_PID_FluxMapIDConfig_t FluxMapID_Config; /**< Input:Configuration struct for FluxMapID */
	uz_PID_OnlineIDConfig_t OnlineID_Config; /**<Input: Configuration struct for  OnlineID */
	uz_PID_AutoRefCurrentsConfig_t AutoRefCurrents_Config; /**<Input: Configuration struct for AutoReference current generator */
	uz_PID_ElectricalID_output_t *ElectricalID_Output; /**<Output: Pointer to output struct of ElectricalID */
	uz_PID_TwoMassID_output_t *TwoMassID_Output; /**<Output: Pointer to output struct of TwoMassID */ 
	uz_PID_FrictionID_output_t *FrictionID_Output; /**<Output: Pointer to output struct of FrictionID */
	uz_PID_FluxMapID_output_t *FluxMapID_Output; /**<Output: Pointer to output struct of FluxMapID */
	uz_PID_OnlineID_output_t* OnlineID_Output; /**<Output: Pointer to output struct of OnlineID */
	uz_PID_Controller_Parameters_output_t Controller_Parameters;/**<Output: output struct for control algorithm (i_dq_ref / n_ref etc.) */
	uz_dq_t AutoRefCurrents_Output; /**<Output: output struct for reference currents of the AutoReference current generator*/
	uz_PID_FluxMapsData_t* FluxMap_Data; /**<Storage for calculated OnlineID FluxMaps*/
	bool calculate_flux_maps; /**<status bool to signal, that the OnlineID FluxMaps should be calculated */
	int FluxMap_counter; /**<counter to transmit FluxMaps 1by1 to the uz_GUI */
	float Psi_D_pointer; /**<current value of the FluxMap array corresponding to the value of the FluxMap_counter*/
	float Psi_Q_pointer; /**<current value of the FluxMap array corresponding to the value of the FluxMap_counter*/
	float FluxMap_MeasuringPoints; /**<amount of unique measuring points for the FluxMaps */
	enum uz_PID_Control_selection PID_Control_Selection;/**< PID_Control_Selection \n
													0 = No_Control \n
													1 = Current_Control \n
													2 = Speed_Control*/ 
} uz_ParameterID_Data_t;

/**
 * @brief Initializes the uz_ParameterID_t object and its sub-objects
 * 
 * @return uz_ParameterID_t* pointer to object
 */
uz_ParameterID_t* uz_ParameterID_init(void);

/**
 * @brief steps the ParameterID once and updates the output values of the ID-states
 * 
 * @param self pointer to uz_ParameterID_t object
 * @param Data pointer to uz_ParameterID_Data_t struct
 */
void uz_ParameterID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);

/**
 * @brief Generates a DutyCycle corresponding to the commands from the uz_ParameterID_step function. To calculate the reference voltages of the uz_ParameterID_Controller function into DutyCycles for the inverter, the function uz_FOC_generate_DutyCycles is used. 
 * This is meant as an example function, to ease the initial setup of the ParameterID. This function is however not essential to the ParamterID itself and can be replaced at will.
 * 
 * @param Data pointer to uz_ParameterID_Data_t struct
 * @param v_dq_Volts reference voltage from control algorithm
 * @param PWM_Module pointer to uz_PWM_SS_2L_t object
 * @return struct uz_DutyCycle_t DutyCycles for the inverter
 */
struct uz_DutyCycle_t uz_ParameterID_generate_DutyCycle(uz_ParameterID_Data_t* Data, uz_dq_t v_dq_Volts, uz_PWM_SS_2L_t* PWM_Module);

/**
 * @brief Exemplary control algorithm (FOC) for the use of the ParamterID.  
 * This is meant as an example function, to ease the initial setup of the ParameterID. This function is however not essential to the ParamterID itself and can be replaced at will.
 * 
 * @param Data pointer to uz_ParameterID_Data_t struct
 * @param FOC_instance pointer to uz_FOC object
 * @param Speed_instance pointer to uz_PI_Controller object
 * @return struct uz_dq_t reference voltages of controller
 */
struct uz_dq_t uz_ParameterID_Controller(uz_ParameterID_Data_t* Data, uz_FOC* FOC_instance, uz_PI_Controller* Speed_instance);

/**
 * @brief Initializes the uz_ParameterID_Data_t used to communicate with the encapsuled ParamterID. This must be called after 
 * 
 * @param Data pointer to uz_ParameterID_Data_t struct
 * @param ParameterID pointer to uz_ParameterID_t object
 */
void uz_ParameterID_initialize_data_structs(uz_ParameterID_Data_t *Data, uz_ParameterID_t *ParameterID);

/**
 * @brief This function is cleaning the array storing the measurement values, which always consits of a d-q-current combination a winding temperature and a speed value such as a d-q-flux combination
The function is searching for measuring pairs which are closer than "eta_c" to their neighbors. In this case it is averaging these similar pairs to avoid measuring values containing the same information. 
 * 
 * @param self pointer to uz_ParameterID_t object
 * @param Data pointer to uz_ParameterID_Data_t struct
 */
void uz_ParameterID_CleanPsiArray(uz_ParameterID_t *self, uz_ParameterID_Data_t* Data);

/**
 * @brief This function is calculating the regular flux maps out of the irregular scatter data array. The outputs is written onto the member FluxMap_Data of the uz_ParameterID_Data_t struct.
 * 
 * @param self pointer to uz_ParameterID_t object
 * @param Data pointer to uz_ParameterID_Data_t struct
 */
void uz_ParameterID_CalcFluxMaps(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);

//only for testing, delete for merge
void uz_ParameterID_correct_LP1_filter(uz_ParameterID_Data_t* Data, float RC);



#endif // UZ_PARAMETERID_H

#endif
