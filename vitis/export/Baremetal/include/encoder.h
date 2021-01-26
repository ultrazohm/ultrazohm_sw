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

#include "../main.h"
#include "../IP_Cores/IncreEncoder_V24_ip_addr.h"
#include "../defines.h"
#include "../include/control_toolbox.h"

int Encoder_Incremental_Initialize(DS_Data* data);   // Init Encoder
void Encoder_UpdateSpeedPosition(DS_Data* data);	// update speed and position in global data struct

#define EncoderPI2_Inc_elek_REG               XPAR_INCREENCODER_V24_IP_0_BASEADDR + PI2_Inc_AXI4_Data_IncreEncoder_V24_ip
//#define EncoderPI2_Inc_mech_REG             XPAR_INCREENCODER_V24_IP_0_BASEADDR + Inc_PerTurn_mech_2PI_AXI4_Data_IncreEncoder_ip
#define EncoderIncsPerTurn_mech_REG         XPAR_INCREENCODER_V24_IP_0_BASEADDR + IncPerTurn_mech_AXI4_Data_IncreEncoder_V24_ip
#define EncoderIncsPerTurn_elek_REG         XPAR_INCREENCODER_V24_IP_0_BASEADDR + IncPerTurn_elek_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_Time_REG                      XPAR_INCREENCODER_V24_IP_0_BASEADDR + Timer_FPGA_ms_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_rps_REG                       XPAR_INCREENCODER_V24_IP_0_BASEADDR + omega_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_position_REG                  XPAR_INCREENCODER_V24_IP_0_BASEADDR + position_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_theta_e_REG                   XPAR_INCREENCODER_V24_IP_0_BASEADDR + theta_el_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_direction_REG                 XPAR_INCREENCODER_V24_IP_0_BASEADDR + direction_AXI4_Data_IncreEncoder_V24_ip
//#define OverSamplingFactorInverseREG         XPAR_INCREENCODER_V24_IP_0_BASEADDR + OverSamplFactorInv_AXI4_Data_IncreEncoder_ip
//#define OverSamplingFactorREG                 XPAR_INCREENCODER_V24_IP_0_BASEADDR + OverSamplFactor_AXI4_Data_IncreEncoder_ip
#define CounterPerPeriodREG                   XPAR_INCREENCODER_V24_IP_0_BASEADDR + countPerPeriod_AXI4_Data_IncreEncoder_V24_ip
#define Encoder_OmegaPerOverSampl_REG        XPAR_INCREENCODER_V24_IP_0_BASEADDR + OmegaPerOverSampl_AXI4_Data_IncreEncoder_V24_ip


#endif /* ENCODER_H_ */
