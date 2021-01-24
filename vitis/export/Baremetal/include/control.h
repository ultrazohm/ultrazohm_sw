/******************************************************************************
* Copyright 2021 Sebastian Wendel
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

#ifndef SRC_INCLUDE_CONTROL_H_
#define SRC_INCLUDE_CONTROL_H_

//#include "../main.h"

int Initialize_FPGAController(DS_Data* data);			// Init FPGA Control algorithm
int Initialize_ARMController(DS_Data* data);			// Init ARM Control algorithm
int Configure_FOC_Control(DS_Data* data);				// Configure the system for FOC control
int Configure_MPC_Control(DS_Data* data);				// Configure the system for MPC control
int Configure_DTC_Control(DS_Data* data);				// Configure the system for DTC control
int Configure_HalfBridge_Control(DS_Data* data);		// Configure the system for HalfBridge control
int Initialize_MotorRelatedParameters(DS_Data* data);	// Init the mrp structure

#endif /* SRC_INCLUDE_CONTROL_H_ */
