/******************************************************************************
* Copyright 2021 Eyke Liegmann
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

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <math.h>

#include "xparameters.h"
#include "xil_types.h"
#include "xil_io.h"

#include "../globalData.h"
#include "../IP_Cores/ADC_Module_LVDS_v2_ip_addr.h"

typedef union _ADCread_union_ {
	struct{
		int16_t ADC1;
		int16_t ADC2;
		int16_t ADC3;
		int16_t ADC4;
		};
	u64 ADC_Block_64bit;
} ADCread_union;


void ADC_readCardA1(DS_Data* data);
void ADC_readCardA2(DS_Data* data);
void ADC_readCardA3(DS_Data* data);

void ADC_readCardALL(DS_Data* data);

void ADC_WriteConversionFactor(int ADC_ConversionFactor);	// Init for the ADC-conversion IP-Block

//==============================================================================================================================================================
// AXI2TCM Registers
#define R5_0_BTCM_SPLIT_REG	0x20000

// ADC Card Slot A1
#define ADC_A1_ChA1_REG		(R5_0_BTCM_SPLIT_REG + 0x00)
#define ADC_A1_ChA2_REG		(R5_0_BTCM_SPLIT_REG + 0x02)
#define ADC_A1_ChA3_REG		(R5_0_BTCM_SPLIT_REG + 0x04)
#define ADC_A1_ChA4_REG		(R5_0_BTCM_SPLIT_REG + 0x06)

#define ADC_A1_ChB5_REG		(R5_0_BTCM_SPLIT_REG + 0x08)
#define ADC_A1_ChB6_REG		(R5_0_BTCM_SPLIT_REG + 0x0A)
#define ADC_A1_ChB7_REG		(R5_0_BTCM_SPLIT_REG + 0x0C)
#define ADC_A1_ChB8_REG		(R5_0_BTCM_SPLIT_REG + 0x0E)

// ADC Card Slot
#define ADC_A2_ChA1_REG		(R5_0_BTCM_SPLIT_REG + 0x10)
#define ADC_A2_ChA2_REG		(R5_0_BTCM_SPLIT_REG + 0x12)
#define ADC_A2_ChA3_REG		(R5_0_BTCM_SPLIT_REG + 0x14)
#define ADC_A2_ChA4_REG		(R5_0_BTCM_SPLIT_REG + 0x16)

#define ADC_A2_ChB5_REG		(R5_0_BTCM_SPLIT_REG + 0x18)
#define ADC_A2_ChB6_REG		(R5_0_BTCM_SPLIT_REG + 0x1A)
#define ADC_A2_ChB7_REG		(R5_0_BTCM_SPLIT_REG + 0x1C)
#define ADC_A2_ChB8_REG		(R5_0_BTCM_SPLIT_REG + 0x1E)

// ADC Card Slot 
#define ADC_A3_ChA1_REG		(R5_0_BTCM_SPLIT_REG + 0x20)
#define ADC_A3_ChA2_REG		(R5_0_BTCM_SPLIT_REG + 0x22)
#define ADC_A3_ChA3_REG		(R5_0_BTCM_SPLIT_REG + 0x24)
#define ADC_A3_ChA4_REG		(R5_0_BTCM_SPLIT_REG + 0x26)

#define ADC_A3_ChB5_REG		(R5_0_BTCM_SPLIT_REG + 0x28)
#define ADC_A3_ChB6_REG		(R5_0_BTCM_SPLIT_REG + 0x2A)
#define ADC_A3_ChB7_REG		(R5_0_BTCM_SPLIT_REG + 0x2C)
#define ADC_A3_ChB8_REG		(R5_0_BTCM_SPLIT_REG + 0x2E)

#define ADC_ChA1	0
#define ADC_ChA2	1
#define ADC_ChA3	2
#define ADC_ChA4	3
#define ADC_ChB5	4
#define ADC_ChB6	5
#define ADC_ChB7	6
#define ADC_ChB8	7

#endif /* ADC_H_ */
