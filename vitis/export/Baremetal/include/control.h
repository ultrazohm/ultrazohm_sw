/******************************************************************************
*
* control.h
*
* Copyright (C) 2019 Institute ELSYS, TH Nürnberg, All rights reserved.
*
*  Created on: 22.10.2019
*      Author: Wendel Sebastian (SW)
*
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
