/******************************************************************************
* Copyright 2021 Eyke Liegmann, Sebastian Wendel
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

#ifndef ENCODER_H_
#define ENCODER_H_

#include "../uz/controlToolbox/control_toolbox.h"
#include "../globalData.h"

//Defines for averaging the speed from the encoder
#define SPEED_BUF_SIZE  					2 //3== erster CCS-Versuch
#define SPEED_BUF_SIZE_INVERS 				1/SPEED_BUF_SIZE

void initialize_incremental_encoder_ipcore_on_D5(float incrementalEncoderResolution, float motorPolePairNumber, uint32_t Mech_Offset, uint32_t Elec_Offset, float speed_timeout);  // Init Encoder
void update_speed_and_position_of_encoder_on_D5(DS_Data *const data);	// update speed and position in global data struct

#endif /* ENCODER_H_ */
