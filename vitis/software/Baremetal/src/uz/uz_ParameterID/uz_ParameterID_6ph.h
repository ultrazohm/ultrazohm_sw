/******************************************************************************
 * Copyright 2022 Valentin Hoppe
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
#ifndef UZ_PARAMETERID_6PH_H
#define UZ_PARAMETERID_6PH_H

#include "uz_ParameterID_data.h"
#include "../uz_CurrentControl/uz_CurrentControl.h"
#include "../uz_SpeedControl/uz_speedcontrol.h"
#include "../uz_setpoint/uz_setpoint.h"
#include "../uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "ControlState/uz_ParaID_ControlState.h"
#include "ElectricalID_6ph/uz_ParaID_ElectricalID_6ph.h"
#include "ElectricalID_6ph/uz_ParaID_Frequency_Analysis.h"
#include "FluxMapID_6ph/uz_ParaID_FluxMapID_6ph.h"
#include "FrictionID/uz_ParaID_FrictionID.h"
#include "OnlineID/uz_ParaID_OnlineID.h"
#include "TwoMassID/uz_ParaID_TwoMassID.h"
#include "../uz_encoder_offset_estimation/uz_encoder_offset_estimation.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_spwm/uz_spwm.h"
#include "../uz_controller_setpoint_filter/uz_controller_setpoint_filter.h"
#include "../uz_subspace_resonant_control/uz_subspace_resonant_control.h"


/**
 * @brief Object definition for uz_ParameterID_6ph_t
 * 
 */
typedef struct uz_ParameterID_6ph_t uz_ParameterID_6ph_t;

/**
 * @brief Initializes the uz_ParameterID_6ph_t object and its sub-objects
 * 
 * @param Data pointer to uz_ParameterID_6ph_Data_t struct
 * @return uz_ParameterID_6ph_t* pointer to uz_ParameterID_6ph_t object
 */
uz_ParameterID_6ph_t* uz_ParameterID_6ph_init(uz_ParameterID_Data_t *Data);

/**
 * @brief steps the ParameterID_6ph once and updates the output values of the ID-states
 * 
 * @param self pointer to uz_ParameterID_6ph_t object
 * @param Data pointer to uz_ParameterID_6ph_Data_t struct
 */
void uz_ParameterID_6ph_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);

/**
 * @brief Includes multiple control functions of the UZ libraries controllers
 * 
 * @param Data pointer to uz_ParameterID_Data_t struct
 * @return struct uz_6ph_dq_t reference voltages of controller
 */
uz_6ph_dq_t uz_ParameterID_6ph_Controller(uz_ParameterID_Data_t* Data, struct uz_ParameterID_controller objects);

/**
 * @brief Generates a DutyCycle corresponding to the commands from the uz_ParameterID_6ph_step function. To calculate the reference voltages of the uz_ParameterID_6ph_Controller function into DutyCycles for the inverter, the SPWM is used. 
 * 
 * @param Data pointer to uz_ParameterID_Data_t struct
 * @param v_dq_Volts reference voltage from control algorithm
 * @return struct uz_DutyCycle_t DutyCycles for the inverter
 */
struct uz_DutyCycle_2x3ph_t uz_ParameterID_6ph_generate_DutyCycle(uz_ParameterID_Data_t* Data, uz_6ph_dq_t v_dq_Volts);

/**
 * @brief processes the given actual values, mainly by rotating subspaces and saving the rotated variables in extra subspace variables 
 * 
 * @param Data pointer to uz_ParameterID_Data_t struct
 * @param u_a1c1 voltage between phases a1 and c1 used for FluxMapID zero system
 * @param u_a2c2 voltage between phases a2 and c2 used for FluxMapID zero system
 */
void uz_ParameterID_6ph_process_actual_values(uz_ParameterID_Data_t *Data, float u_a1c1, float u_a2c2);

/**
 * @brief initializes three dq-setpoint filter instances and saves them to the Data struct
 * 
 * @param Data pointer to uz_ParameterID_Data_t struct
 * @param config config for the setpoint filters (same will be used for all)
 */
void uz_ParameterID_6ph_initialize_filter(uz_ParameterID_Data_t* Data, const float isr_frequency);

/**
 * @brief initializes the encoder offset estimation and saves the object pointer to the Data struct
 * 
 * @param Data pointer to uz_ParameterID_Data_t struct
 * @param u_q_ref pointer to the q-voltage reference, take from the output of the FOC controller
 */
void uz_ParameterID_6ph_initialize_encoder_offset_estimation(uz_ParameterID_Data_t *Data, float* u_q_ref);

/**
 * @brief updates transmit values/Converts some int-values from the ParameterID to float and helps to sync the array transmission
 * 
 * @param Data pointer to uz_ParameterID_Data_t struct
 * @param activeState pointer to float variable of activeState
 * @param FluxMapCounter pointer to float variable of FluxMapCounter
 * @param ArrayCounter pointer to float variable of ArrayCounter
 */
void uz_ParameterID_6ph_update_transmit_values(uz_ParameterID_Data_t* Data, float *activeState, float FMID_val_milli[4], float *FMID_index_array);

/**
 * @brief calculates PsiPMs from FFT in the main function to not block the isr
 * 
 * @param self pointer to uz_ParameterID_6ph_t object
 * @param Data pointer to uz_ParameterID_Data_t struct
 * @param meas_array pointer to float variable of activeState
 */
void uz_ParameterID_6ph_calculate_PsiPMs(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t *Data);

#endif // UZ_PARAMETERID_6PH_H
