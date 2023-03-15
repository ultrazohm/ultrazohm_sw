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

#include "../defines.h"
#include "../globalData.h"
#include "../uz/uz_array/uz_array.h"

void ADC_readCardA1(DS_Data *data, uz_array_int16_t adc_data);
void ADC_readCardA2(DS_Data *data, uz_array_int16_t adc_data);
void ADC_readCardA3(DS_Data *data, uz_array_int16_t adc_data);

void ADC_readCardALL(DS_Data* data);


#endif /* ADC_H_ */
