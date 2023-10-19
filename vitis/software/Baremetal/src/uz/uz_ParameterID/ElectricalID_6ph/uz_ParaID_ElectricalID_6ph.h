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

#ifndef ELECTRICALID_6PH_H
#define ELECTRICALID_6PH_H

#include "../uz_ParameterID_data.h"

/**
 * @brief Object definition for uz_ParaID_ElectricalID_6ph_t
 * 
 */
typedef struct uz_ParaID_ElectricalID_6ph_t uz_ParaID_ElectricalID_6ph_t;

uz_ParaID_ElectricalID_6ph_t* uz_ElectricalID_6ph_init(void);

/**
 * @brief steps the ElectricalID state once
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 */
void uz_ElectricalID_6ph_step(uz_ParaID_ElectricalID_6ph_t* self);

/**
 * @brief Sets the config struct for the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 * @param Config configuration struct for ElectricalID
 */
void uz_ElectricalID_6ph_set_Config(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_ElectricalIDConfig_t Config);

/**
 * @brief Sets the ActualValues struct for the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 * @param ActualValues struct for the measurement values
 */
void uz_ElectricalID_6ph_set_ActualValues(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_ActualValues_t ActualValues);

/**
 * @brief Sets the GlobalConfig struct for the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 * @param GlobalConfig struct for the general settings of the ParameterID
 */
void uz_ElectricalID_6ph_set_GlobalConfig(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_GlobalConfig_t GlobalConfig);

/**
 * @brief Sets the ControlFlags struct for the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 * @param ControlFlags pointer to the struct with the enable signals of the ParameterID
 */
void uz_ElectricalID_6ph_set_ControlFlags(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_ControlFlags_t* ControlFlags);

/**
 * @brief Sets the GlobalConfig struct for the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 * @param fft_in struct for the FFT input
 */
void uz_ElectricalID_6ph_set_FFT_in(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_ElectricalID_fft_in_t fft_in);

/**
 * @brief Sets the GlobalConfig struct for the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 * @param offset_est_in struct for the offset estimation input
 */
void uz_ElectricalID_6ph_set_Offset_Estimation(uz_ParaID_ElectricalID_6ph_t *self, uz_ParaID_ElectricalID_offset_estimation_t offset_est_in);

/**
 * @brief Gets the status of the enteredElectricalID flag
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 * @return true state has been entered
 * @return false state hasn't been entered
 */
bool uz_get_ElectricalID_6ph_entered(uz_ParaID_ElectricalID_6ph_t* self);

/**
 * @brief Gets the status of the finishedElectricalID flag
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 * @return true state has finished
 * @return false state hasn't finished
 */
bool uz_get_ElectricalID_6ph_finished(uz_ParaID_ElectricalID_6ph_t* self);

/**
 * @brief Gets the status of the finished_voltage_measurement flag
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 * @return true measurement has finished
 * @return false measurement hasn't finished
 */
bool uz_get_ElectricalID_6ph_finished_voltage_measurement(uz_ParaID_ElectricalID_6ph_t* self);

/**
 * @brief Gets the pointer to the output controller struct of the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 * @return uz_ParaID_Controller_Parameters_output_t* pointer to the FOC controller parameters struct
 */
uz_ParaID_Controller_Parameters_output_t* uz_get_ElectricalID_6ph_FOCoutput(uz_ParaID_ElectricalID_6ph_t* self);

/**
 * @brief Gets the pointer to the output struct of the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 * @return uz_ParaID_ElectricalID_output_t* pointer to the output struct
 */
uz_ParaID_ElectricalID_output_t* uz_get_ElectricalID_6ph_output(uz_ParaID_ElectricalID_6ph_t* self);

/**
 * @brief copies the logged voltage to the destination for FFT
 * 
 * @param self pointer to uz_ParaID_ElectricalID_6ph_t object
 */
float* uz_get_ElectricalID_6ph_fft_out(uz_ParaID_ElectricalID_6ph_t* self);

#endif // ELECTRICALID_6PH_H
