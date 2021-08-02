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

#endif /* ADC_H_ */
