/******************************************************************************
* Copyright 2021 Eyke Liegmann, Tobias Schindler, Sebastian Wendel
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

#include "../include/adc.h"
#include "../IP_Cores/uz_dataMover/uz_dataMover.h"
#include "../uz/uz_HAL.h"

void ADC_readCardA1(DS_Data *data, uz_array_int16_t adc_data)
{
    // bitshift operation of -16 digits, because it is an 16-bit ADC, scaling the value to +/- 0.5
    // multiplying it afterwards with the conversion factor, which is the peak-to-peak into value
    // Conversion Factor is defined in main.c InitializeDataStructure
    data->aa.A1.me.ADC_array[0] = ((float)adc_data.data[0]) / (1 << Q16) * data->aa.A1.cf.ADC_A1;
    data->aa.A1.me.ADC_array[1] = ((float)adc_data.data[1]) / (1 << Q16) * data->aa.A1.cf.ADC_A2;
    data->aa.A1.me.ADC_array[2] = ((float)adc_data.data[2]) / (1 << Q16) * data->aa.A1.cf.ADC_A3;
    data->aa.A1.me.ADC_array[3] = ((float)adc_data.data[3]) / (1 << Q16) * data->aa.A1.cf.ADC_A4;
    data->aa.A1.me.ADC_array[4] = ((float)adc_data.data[4]) / (1 << Q16) * data->aa.A1.cf.ADC_B5;
    data->aa.A1.me.ADC_array[5] = ((float)adc_data.data[5]) / (1 << Q16) * data->aa.A1.cf.ADC_B6;
    data->aa.A1.me.ADC_array[6] = ((float)adc_data.data[6]) / (1 << Q16) * data->aa.A1.cf.ADC_B7;
    data->aa.A1.me.ADC_array[7] = ((float)adc_data.data[7]) / (1 << Q16) * data->aa.A1.cf.ADC_B8;
}

void ADC_readCardA2(DS_Data *data, uz_array_int16_t adc_data)
{
    data->aa.A2.me.ADC_array[0] = ((float)adc_data.data[8]) / (1 << Q16) * data->aa.A2.cf.ADC_A1;
    data->aa.A2.me.ADC_array[1] = ((float)adc_data.data[9]) / (1 << Q16) * data->aa.A2.cf.ADC_A2;
    data->aa.A2.me.ADC_array[2] = ((float)adc_data.data[10]) / (1 << Q16) * data->aa.A2.cf.ADC_A3;
    data->aa.A2.me.ADC_array[3] = ((float)adc_data.data[11]) / (1 << Q16) * data->aa.A2.cf.ADC_A4;
    data->aa.A2.me.ADC_array[4] = ((float)adc_data.data[12]) / (1 << Q16) * data->aa.A2.cf.ADC_B5;
    data->aa.A2.me.ADC_array[5] = ((float)adc_data.data[13]) / (1 << Q16) * data->aa.A2.cf.ADC_B6;
    data->aa.A2.me.ADC_array[6] = ((float)adc_data.data[14]) / (1 << Q16) * data->aa.A2.cf.ADC_B7;
    data->aa.A2.me.ADC_array[7] = ((float)adc_data.data[15]) / (1 << Q16) * data->aa.A2.cf.ADC_B8;
}

void ADC_readCardA3(DS_Data *data, uz_array_int16_t adc_data)
{

	if (UZ_MAX11_INPUT_CONFIGURATION == 2U){
		//Max11 reads 12Bits in Fully Diff.-Mode Bipolar (2nd Complement), see p.28 of MAX11 ADC datasheet.
		//Explanation see also: https://bitbucket.org/ultrazohm/uz_a_max11331/issues/2/first-commissioning-of-pcb
		data->aa.A3.me.ADC_array[0] = (float)((int16_t)(adc_data.data[16] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_A1;
		data->aa.A3.me.ADC_array[1] = (float)((int16_t)(adc_data.data[17] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_A2;
		data->aa.A3.me.ADC_array[2] = (float)((int16_t)(adc_data.data[18] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_A3;
		data->aa.A3.me.ADC_array[3] = (float)((int16_t)(adc_data.data[19] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_A4;
		data->aa.A3.me.ADC_array[4] = (float)((int16_t)(adc_data.data[20] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_B5;
		data->aa.A3.me.ADC_array[5] = (float)((int16_t)(adc_data.data[21] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_B6;
		data->aa.A3.me.ADC_array[6] = (float)((int16_t)(adc_data.data[22] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_B7;
		data->aa.A3.me.ADC_array[7] = (float)((int16_t)(adc_data.data[23] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_B8;
		data->aa.A3.me.ADC_array[8] = (float)((int16_t)(adc_data.data[24] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_C9;
		data->aa.A3.me.ADC_array[9] = (float)((int16_t)(adc_data.data[25] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_C10;
		data->aa.A3.me.ADC_array[10] = (float)((int16_t)(adc_data.data[26] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_C11;
		data->aa.A3.me.ADC_array[11] = (float)((int16_t)(adc_data.data[27] << Q4))/ (1 << Q15) *  data->aa.A3.cf.ADC_C12;
		data->aa.A3.me.ADC_array[12] = (float)((int16_t)(adc_data.data[28] << Q4))/ (1 << Q15) *  data->aa.A3.cf.ADC_D13;
		data->aa.A3.me.ADC_array[13] = (float)((int16_t)(adc_data.data[29] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_D14;
		data->aa.A3.me.ADC_array[14] = (float)((int16_t)(adc_data.data[30] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_D15;
		data->aa.A3.me.ADC_array[15] = (float)((int16_t)(adc_data.data[31] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_D16;
		data->aa.A3.me.ADC_array[16] = (float)((int16_t)(adc_data.data[32] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_E17;
		data->aa.A3.me.ADC_array[17] = (float)((int16_t)(adc_data.data[33] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_E18;
		data->aa.A3.me.ADC_array[18] = (float)((int16_t)(adc_data.data[34] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_E19;
		data->aa.A3.me.ADC_array[19] = (float)((int16_t)(adc_data.data[35] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_E20;
		data->aa.A3.me.ADC_array[20] = (float)((int16_t)(adc_data.data[36] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_F21;
		data->aa.A3.me.ADC_array[21] = (float)((int16_t)(adc_data.data[37] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_F22;
		data->aa.A3.me.ADC_array[22] = (float)((int16_t)(adc_data.data[38] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_F23;
		data->aa.A3.me.ADC_array[23] = (float)((int16_t)(adc_data.data[39] << Q4))/ (1 << Q15) * data->aa.A3.cf.ADC_F24;
	}else{
		//MAX11 reads 12 Bits in Single-Ended Unipolar (Binary Coding)
		data->aa.A3.me.ADC_array[0] = ((float)adc_data.data[16]) / (1 << Q12) * data->aa.A3.cf.ADC_A1;
		data->aa.A3.me.ADC_array[1] = ((float)adc_data.data[17]) / (1 << Q12) * data->aa.A3.cf.ADC_A2;
		data->aa.A3.me.ADC_array[2] = ((float)adc_data.data[18]) / (1 << Q12) * data->aa.A3.cf.ADC_A3;
		data->aa.A3.me.ADC_array[3] = ((float)adc_data.data[19]) / (1 << Q12) * data->aa.A3.cf.ADC_A4;
		data->aa.A3.me.ADC_array[4] = ((float)adc_data.data[20]) / (1 << Q12) * data->aa.A3.cf.ADC_B5;
		data->aa.A3.me.ADC_array[5] = ((float)adc_data.data[21]) / (1 << Q12) * data->aa.A3.cf.ADC_B6;
		data->aa.A3.me.ADC_array[6] = ((float)adc_data.data[22]) / (1 << Q12) * data->aa.A3.cf.ADC_B7;
		data->aa.A3.me.ADC_array[7] = ((float)adc_data.data[23]) / (1 << Q12) * data->aa.A3.cf.ADC_B8;
		data->aa.A3.me.ADC_array[8] = ((float)adc_data.data[24]) / (1 << Q12) * data->aa.A3.cf.ADC_C9;
		data->aa.A3.me.ADC_array[9] = ((float)adc_data.data[25]) / (1 << Q12) * data->aa.A3.cf.ADC_C10;
		data->aa.A3.me.ADC_array[10] = ((float)adc_data.data[26]) / (1 << Q12) * data->aa.A3.cf.ADC_C11;
		data->aa.A3.me.ADC_array[11] = ((float)adc_data.data[27]) / (1 << Q12) * data->aa.A3.cf.ADC_C12;
		data->aa.A3.me.ADC_array[12] = ((float)adc_data.data[28]) / (1 << Q12) * data->aa.A3.cf.ADC_D13;
		data->aa.A3.me.ADC_array[13] = ((float)adc_data.data[29]) / (1 << Q12) * data->aa.A3.cf.ADC_D14;
		data->aa.A3.me.ADC_array[14] = ((float)adc_data.data[30]) / (1 << Q12) * data->aa.A3.cf.ADC_D15;
		data->aa.A3.me.ADC_array[15] = ((float)adc_data.data[31]) / (1 << Q12) * data->aa.A3.cf.ADC_D16;
		data->aa.A3.me.ADC_array[16] = 0;//Channel not available in MicroZohm
		data->aa.A3.me.ADC_array[17] = 0;//Channel not available in MicroZohm
		data->aa.A3.me.ADC_array[18] = 0;//Channel not available in MicroZohm
		data->aa.A3.me.ADC_array[19] = 0;//Channel not available in MicroZohm
		data->aa.A3.me.ADC_array[20] = 0;//Channel not available in MicroZohm
		data->aa.A3.me.ADC_array[21] = 0;//Channel not available in MicroZohm
		data->aa.A3.me.ADC_array[22] = 0;//Channel not available in MicroZohm
		data->aa.A3.me.ADC_array[23] = 0;//Channel not available in MicroZohm
	}
};

void ADC_readCardALL(DS_Data *data)
{
    uz_array_int16_t adc_data = uz_dataMover_update_buffer_and_get_data();
    ADC_readCardA1(data, adc_data);
    ADC_readCardA2(data, adc_data);
    ADC_readCardA3(data, adc_data);
}
