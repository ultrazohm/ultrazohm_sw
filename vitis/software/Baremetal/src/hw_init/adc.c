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

uint16_t TestVar = 0;
uint32_t Max11ConfigSPI =0;
uint32_t Max11ConfigBiPo =0;
uint32_t Max11ConfigUniPo =0;
uint32_t Max11ConfigAdcSelFORCEINIT =0;
uint32_t Max11ConfigStatus =0;
uint32_t Max11ConfigErrorCounter =0;
uint32_t FORCEINIT;

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
    data->aa.A3.me.ADC_array[0] = ((float)adc_data.data[16]) / (1 << Q12) * data->aa.A3.cf.ADC_A1;
    data->aa.A3.me.ADC_array[1] = ((float)adc_data.data[17]) / (1 << Q12) * data->aa.A3.cf.ADC_A2;
    data->aa.A3.me.ADC_array[2] = ((float)adc_data.data[18]) / (1 << Q12) * data->aa.A3.cf.ADC_A3;
    data->aa.A3.me.ADC_array[3] = ((float)adc_data.data[19]) / (1 << Q12) * data->aa.A3.cf.ADC_A4;
    data->aa.A3.me.ADC_array[4] = ((float)adc_data.data[20]) / (1 << Q12) * data->aa.A3.cf.ADC_B5;
    data->aa.A3.me.ADC_array[5] = ((float)adc_data.data[21]) / (1 << Q12) * data->aa.A3.cf.ADC_B6;
    data->aa.A3.me.ADC_array[6] = ((float)adc_data.data[22]) / (1 << Q12) * data->aa.A3.cf.ADC_B7;
    data->aa.A3.me.ADC_array[7] = ((float)adc_data.data[23]) / (1 << Q12) * data->aa.A3.cf.ADC_B8;
//	TestVar = (adc_data.data[16]);
//    data->aa.A3.me.ADC_array[1] = ((float)adc_data.data[17]);
//    data->aa.A3.me.ADC_array[2] = ((float)adc_data.data[18]);
//    data->aa.A3.me.ADC_array[3] = ((float)adc_data.data[19]);
//    data->aa.A3.me.ADC_array[4] = ((float)adc_data.data[20]);
//    data->aa.A3.me.ADC_array[5] = ((float)adc_data.data[21]);
//    data->aa.A3.me.ADC_array[6] = ((float)adc_data.data[22]);
//    data->aa.A3.me.ADC_array[7] = ((float)adc_data.data[23]);
};

void ADC_readCardA3_MAX11(DS_Data *data, uz_array_int16_t adc_data)
{
    data->aa.A3_Max11_ADC2.me.ADC_array[0] = ((float)adc_data.data[24]) / (1 << Q12) * data->aa.A3_Max11_ADC2.cf.ADC_A1;
    data->aa.A3_Max11_ADC2.me.ADC_array[1] = ((float)adc_data.data[25]) / (1 << Q12) * data->aa.A3_Max11_ADC2.cf.ADC_A2;
    data->aa.A3_Max11_ADC2.me.ADC_array[2] = ((float)adc_data.data[26]) / (1 << Q12) * data->aa.A3_Max11_ADC2.cf.ADC_A3;
    data->aa.A3_Max11_ADC2.me.ADC_array[3] = ((float)adc_data.data[27]) / (1 << Q12) * data->aa.A3_Max11_ADC2.cf.ADC_A4;
    data->aa.A3_Max11_ADC2.me.ADC_array[4] = ((float)adc_data.data[28]) / (1 << Q12) * data->aa.A3_Max11_ADC2.cf.ADC_B5;
    data->aa.A3_Max11_ADC2.me.ADC_array[5] = ((float)adc_data.data[29]) / (1 << Q12) * data->aa.A3_Max11_ADC2.cf.ADC_B6;
    data->aa.A3_Max11_ADC2.me.ADC_array[6] = ((float)adc_data.data[30]) / (1 << Q12) * data->aa.A3_Max11_ADC2.cf.ADC_B7;
    data->aa.A3_Max11_ADC2.me.ADC_array[7] = ((float)adc_data.data[31]) / (1 << Q12) * data->aa.A3_Max11_ADC2.cf.ADC_B8;

    data->aa.A3_Max11_ADC3.me.ADC_array[0] = ((float)adc_data.data[32]) / (1 << Q12) * data->aa.A3_Max11_ADC3.cf.ADC_A1;
    data->aa.A3_Max11_ADC3.me.ADC_array[1] = ((float)adc_data.data[33]) / (1 << Q12) * data->aa.A3_Max11_ADC3.cf.ADC_A2;
    data->aa.A3_Max11_ADC3.me.ADC_array[2] = ((float)adc_data.data[34]) / (1 << Q12) * data->aa.A3_Max11_ADC3.cf.ADC_A3;
    data->aa.A3_Max11_ADC3.me.ADC_array[3] = ((float)adc_data.data[35]) / (1 << Q12) * data->aa.A3_Max11_ADC3.cf.ADC_A4;
    data->aa.A3_Max11_ADC3.me.ADC_array[4] = ((float)adc_data.data[36]) / (1 << Q12) * data->aa.A3_Max11_ADC3.cf.ADC_B5;
    data->aa.A3_Max11_ADC3.me.ADC_array[5] = ((float)adc_data.data[37]) / (1 << Q12) * data->aa.A3_Max11_ADC3.cf.ADC_B6;
    data->aa.A3_Max11_ADC3.me.ADC_array[6] = ((float)adc_data.data[38]) / (1 << Q12) * data->aa.A3_Max11_ADC3.cf.ADC_B7;
    data->aa.A3_Max11_ADC3.me.ADC_array[7] = ((float)adc_data.data[39]) / (1 << Q12) * data->aa.A3_Max11_ADC3.cf.ADC_B8;
};



void ADC_readCardALL(DS_Data *data)
{
    uz_array_int16_t adc_data = uz_dataMover_update_buffer_and_get_data();
    ADC_readCardA1(data, adc_data);
    ADC_readCardA2(data, adc_data);
    ADC_readCardA3(data, adc_data);
    ADC_readCardA3_MAX11(data, adc_data);


    Max11ConfigSPI = uz_adcMax11331_hw_read_spi_cfgr(XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_A3_ADC_MAX11331_BASEADDR);
    Max11ConfigBiPo = uz_adcMax11331_hw_read_EchoBipolar(XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_A3_ADC_MAX11331_BASEADDR);
    Max11ConfigUniPo = uz_adcMax11331_hw_read_EchoUnipolar(XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_A3_ADC_MAX11331_BASEADDR);
    Max11ConfigAdcSelFORCEINIT = uz_adcMax11331_hw_read_master_channel(XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_A3_ADC_MAX11331_BASEADDR);
    Max11ConfigStatus = uz_adcMax11331_hw_read_Status(XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_A3_ADC_MAX11331_BASEADDR);
    Max11ConfigErrorCounter = uz_adcMax11331_hw_read_ErrorCounter(XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_A3_ADC_MAX11331_BASEADDR);
    uz_adcMax11331_hw_write_master_channel(XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_A3_ADC_MAX11331_BASEADDR,FORCEINIT);

}
