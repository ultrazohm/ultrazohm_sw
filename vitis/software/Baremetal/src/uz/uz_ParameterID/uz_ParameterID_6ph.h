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

#include "../../globalData.h"
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
uz_6ph_dq_t uz_ParameterID_6ph_Controller(uz_ParameterID_Data_t* Data);

/**
 * @brief Generates a DutyCycle corresponding to the commands from the uz_ParameterID_6ph_step function. To calculate the reference voltages of the uz_ParameterID_6ph_Controller function into DutyCycles for the inverter, the SPWM is used. 
 * 
 * @param Data pointer to uz_ParameterID_Data_t struct
 * @param v_dq_Volts reference voltage from control algorithm
 * @return struct uz_DutyCycle_t DutyCycles for the inverter
 */
struct uz_DutyCycle_2x3ph_t uz_ParameterID_6ph_generate_DutyCycle(uz_ParameterID_Data_t* Data, uz_6ph_dq_t v_dq_Volts);


void uz_ParameterID_6ph_update_transmit_values(uz_ParameterID_Data_t* Data, float *activeState, float *FluxMapCounter, float *ArrayCounter);
void uz_ParameterID_6ph_calculate_PsiPMs(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t *Data, float *meas_array);
bool uz_ParameterID_6ph_transmit_FluxMap_to_Console(uz_ParameterID_Data_t* Data, int js_cnt_slowData);
void uz_ParameterID_6ph_initialize_encoder_offset_estimation(uz_ParameterID_Data_t *Data, float* raw_rotor_angle, float* u_q_ref);

// Temp
void print_paraID(uz_ParameterID_Data_t *Data);

#endif // UZ_PARAMETERID_6PH_H
