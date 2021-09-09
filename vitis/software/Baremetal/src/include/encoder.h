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


#include "xparameters.h"
#include "xil_types.h"
#include "xil_io.h"
#include <math.h>
#include "../uz/controlToolbox/control_toolbox.h"
#include "../IP_Cores/IncreEncoder_V24_ip_addr.h"
#include "../defines.h"
#include "../globalData.h"

//Defines for averaging the speed from the encoder
#define SPEED_BUF_SIZE  					8U //averaging over n values
#define SPEED_FIL_ALPHA						0.05F //defines actuality of filtered size
#define SPEED_FIL_BETA						0.015F //defines actuality of slope of filtered size

// Defines for Calculation
#define QUADRATURE_FACTOR					4.0F
#define OMEGA_2_RPM							60.0F / (2.0F * M_PI)

int Encoder_Incremental_Initialize(DS_Data* data);   // Init Encoder
void Encoder_UpdateSpeedPosition(DS_Data* data);	// update speed and position in global data struct

#define EncoderPI2_Inc_elek_REG               XPAR_INCREENCODER_V24_IP_0_BASEADDR + PI2_Inc_AXI4_Data_IncreEncoder_V24_ip
#define EncoderIncsPerTurn_mech_REG         XPAR_INCREENCODER_V24_IP_0_BASEADDR + IncPerTurn_mech_AXI4_Data_IncreEncoder_V24_ip
#define EncoderIncsPerTurn_elek_REG         XPAR_INCREENCODER_V24_IP_0_BASEADDR + IncPerTurn_elek_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_Time_REG                      XPAR_INCREENCODER_V24_IP_0_BASEADDR + Timer_FPGA_ms_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_rps_REG                       XPAR_INCREENCODER_V24_IP_0_BASEADDR + omega_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_position_REG                  XPAR_INCREENCODER_V24_IP_0_BASEADDR + position_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_theta_e_REG                   XPAR_INCREENCODER_V24_IP_0_BASEADDR + theta_el_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_direction_REG                 XPAR_INCREENCODER_V24_IP_0_BASEADDR + direction_AXI4_Data_IncreEncoder_V24_ip
#define CounterPerPeriodREG                   XPAR_INCREENCODER_V24_IP_0_BASEADDR + countPerPeriod_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_OmegaPerOverSampl_REG        XPAR_INCREENCODER_V24_IP_0_BASEADDR + OmegaPerOverSampl_AXI4_Data_IncreEncoder_V24_ip


#endif /* ENCODER_H_ */
