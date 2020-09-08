/******************************************************************************
 *
 * adc.h
 *
 * Copyright (C) 2020 UltraZohm Community, All rights reserved.
 *
 *  Created on: 08.09.2020
 *      Author: Eyke Liegmann (EL)
 *
******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "../main.h"


int Initialize_ADC_CONVERSION(void);						// Init for the ADC-conversion IP-Block
int Initialize_TRANS_123_DQ_CONVERSION(DS_Data* data);		// Init Park-transformation 123 to dq

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

#endif /* ADC_H_ */
