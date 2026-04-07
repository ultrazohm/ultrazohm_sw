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
#ifndef UZ_PARAID_CLEANPSIARRAY_H
#define UZ_PARAID_CLEANPSIARRAY_H

#include "CleanPsiArray_codegen.h"

/**
 * @brief object definition for uz_ParaID_CleanPsiArray_t
 * 
 */
typedef struct uz_ParaID_CleanPsiArray_t uz_ParaID_CleanPsiArray_t;

/**
 * @brief Initializes the uz_ParaID_CleanPsiArray_t object
 * 
 * @return uz_ParaID_CleanPsiArray_t* pointer to object
 */
uz_ParaID_CleanPsiArray_t* uz_CleanPsiArray_init(void);

/**
 * @brief steps the CleanPsiArray state once
 * 
 * @param self pointer to object
 */
void uz_CleanPsiArray_step(uz_ParaID_CleanPsiArray_t *self);

/**
 * @brief Sets the OnlineID output for the CleanPsiArray
 * 
 * @param self pointer to the uz_ParaID_CleanPsiArray_t object
 * @param OnlineID_output pointer to the output struct of the OnlineID
 */
void uz_CleanPsiArray_set_OnlineID_output(uz_ParaID_CleanPsiArray_t* self, uz_ParaID_OnlineID_output_t* OnlineID_output);

/**
 * @brief Sets the eta_c of the CleanPsiArray. The function is searching for measuring pairs which are closer than "eta_c" to their neighbors. 
 * In this case it is averaging this similar pairs to avoid measuring values containing the same information. 
 * 
 * @param self pointer to the uz_ParaID_CleanPsiArray_t object
 * @param eta_c factor to determine the averaging threshold for close measuring points
 */
void uz_CleanPsiArray_set_eta_c(uz_ParaID_CleanPsiArray_t* self, float eta_c);

/**
 * @brief Gets the cleaned psi array
 * 
 * @param self pointer to the uz_ParaID_CleanPsiArray_t object
 * @return float* returns pointer to the first array element
 */
float* uz_CleanPsiArray_get_psi_array_out(uz_ParaID_CleanPsiArray_t* self);

/**
 * @brief Gets the array cleaned flag. Signals, when the entire array has been cleaned
 * 
 * @param self pointer to the uz_ParaID_CleanPsiArray_t object
 * @return true array has been cleaned
 * @return false array hasn't been cleaned
 */
bool uz_CleanPsiArray_get_array_cleaned_flag(uz_ParaID_CleanPsiArray_t* self);

/**
 * @brief Gets the amount of measuring points from the cleaned array
 * 
 * @param self pointer to the uz_ParaID_CleanPsiArray_t object
 * @return float amount of measuring points
 */
float uz_CleanPsiArray_get_n_flux_points(uz_ParaID_CleanPsiArray_t* self);
#endif
