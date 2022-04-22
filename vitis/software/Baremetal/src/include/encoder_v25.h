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

#include "../control/toolbox.h"
#include "../main.h"

void initialize_incremental_encoder_ipcore_v25_on_D5(float incrementalEncoderResolution, float motorPolePairNumber,float speed_timeout);
void update_speed_and_position_of_encoder_on_D5_ip_v25(DS_Data *const data);	// update speed and position in global data struct

#endif /* ENCODER_V25_H_ */
