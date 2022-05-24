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

#ifndef ENCODER_V25_H_
#define ENCODER_V25_H_

#include "../uz/controlToolbox/control_toolbox.h"
#include "../main.h"

void initialize_incremental_encoder_ipcore_v25_on_D5_1(float incrementalEncoderResolution, float motorPolePairNumber,float speed_timeout);
void update_speed_and_position_of_encoder_on_D5_1_ip_v25(DS_Data *const data);	// update speed and position in global data struct
void update_position_of_encoder_on_D5_2_ip_v25(DS_Data* const data);
void initialize_incremental_encoder_ipcore_v25_on_D5_2(float incrementalEncoderResolution, float motorPolePairNumber, float speed_timeout);
void initialize_incremental_encoder_ipcore_v25_on_D5_3(float incrementalEncoderResolution, float motorPolePairNumber, float speed_timeout);
void update_angle_of_encoder_on_D5_3_ip_v25(DS_Data* const data);
#endif /* ENCODER_V25_H_ */
