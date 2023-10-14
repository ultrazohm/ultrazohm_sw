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

#ifndef FREQUENCY_ANALYSIS_H
#define FREQUENCY_ANALYSIS_H

#include "../uz_ParameterID_data.h"
#include "../../uz_math_constants.h"
#include <stdint.h>

#define PARAMETERID6PH_ELECTRICAL_N_ORDER 5U


/**
 * @brief calculates psi_pms from a given fft result of an induced voltage measurement and prepares output for the Electrical ID
 * 
 * @param induced_voltage recorded induced voltage
 * @param ISR_sampletime ISR sample time
 * @return Psi PM result for the selected five orders (frequency, magnitude, angle) and finished flag
 */
uz_ParaID_ElectricalID_fft_in_t uz_calculate_psi_pms_ElectricalID(float induced_voltage[10000], float ISR_sampletime);

/**
 * @brief calculates psi_pms from a given fft result of an induced voltage measurement and prepares output for the Electrical ID
 * 
 * @param psi_pm_uncorrected uncorrected Psi PM results
 * @param global_config ParaID config with details about the filtering
 * @return corrected Psi PM result for magnitude and phase
 */
uz_ParaID_ElectricalID_fft_in_t uz_correct_psi_pms_ElectricalID(uz_ParaID_ElectricalID_fft_in_t psi_pm_uncorrected, uz_ParaID_GlobalConfig_t global_config);

#endif // FREQUENCY_ANALYSIS_H
