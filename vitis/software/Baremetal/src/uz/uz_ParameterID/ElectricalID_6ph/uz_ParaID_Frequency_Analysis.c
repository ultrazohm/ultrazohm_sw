/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Valentin Hoppe
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

#include "uz_ParaID_Frequency_Analysis.h"
#include "FFTRecordedVoltage/FFTRecordedVoltage.h"
#include "../../uz_HAL.h"
#include <string.h>


uint16_t uz_find_array_max_value_index(float array[], uint16_t elements){
    float high_value = 0.0f;
    uint16_t index = 65535;
    for(uint16_t i=0;i<elements;i++)
    {
        if(high_value < array[i])
        {
            high_value = array[i];
            index = i;
        }
    }
    return index;
}

uint16_t uz_find_real_index_in_range(float full_array[], uint16_t ideal_index, const uint16_t range, uint16_t fft_elements)
{
    const uint16_t elements_sliced = 2U*range+1U;
    float temp_array [elements_sliced];
    uint16_t real_index = 65535U;
    // check that sliced array boundaries are larger than 0 and smaller than the maximum size
    uz_assert(ideal_index-range>=0);
    uz_assert(ideal_index+range+1U<=fft_elements);
    // slice array
    for(uint16_t i=0;i<elements_sliced;i++)
    {
        temp_array[i] = full_array[i+ideal_index-range];
    }
    // correct index to match index of full array
    real_index = uz_find_array_max_value_index(temp_array, elements_sliced);
    return (real_index + ideal_index - range);
}

void uz_find_fft_peak_indices(uint16_t order[], const uint16_t n_order, float fft_amplitudes[], const uint16_t fft_elements, uint16_t indices_real[])
{
    // inits
    uint16_t indices_ideal[n_order];    // ideal indices, multiplied fundamental index with order
    const uint16_t range = 15U;         // find index of fundamental
    indices_real[0] = uz_find_array_max_value_index(fft_amplitudes, fft_elements);
    // determine ideal indices of higher orders
    // multiply index of fundamental with all given orders
    // use function to determine real indices in the given range
    for(uint16_t i=1;i<n_order;i++)
    {
        indices_ideal[i] = indices_real[0] * order[i];
        indices_real[i] = uz_find_real_index_in_range(fft_amplitudes, indices_ideal[i], range, fft_elements);
    }   
}

float uz_wrap_to_2pi(float angle)
{
    if(angle < 2.0f*UZ_PIf && angle >= 0.0f)
        return angle;
    else if(angle >= 2.0f*UZ_PIf)
        return uz_wrap_to_2pi(angle-2.0f*UZ_PIf);
    else if(angle < 0.0f)
        return uz_wrap_to_2pi(angle+2.0f*UZ_PIf);
    else
        return 0.0f;
}

void uz_calculate_psi_pms(float psi_pm[][3], uint16_t indices_real[], const uint16_t n_order, float fft_frequencies[], float fft_amplitudes[], float fft_angles[])
{
    // find out psi pm frequencies
    for(uint16_t i=0;i<n_order;i++)
    {
        psi_pm[i][0] = fft_frequencies[indices_real[i]];
    }
    // find out psi pm amplitudes and calculate psi pm
    for(uint16_t i=0;i<n_order;i++)
    {
        psi_pm[i][1] = fft_amplitudes[indices_real[i]]/(psi_pm[i][0]*UZ_PIf*2.0f);
    }
    // find out psi pm angles and norm to angle of fundamental and 2pi
    for(uint16_t i=0;i<n_order;i++)
    {
        psi_pm[i][2] = fft_angles[indices_real[i]];
        psi_pm[i][2] = uz_wrap_to_2pi(psi_pm[i][2] - psi_pm[0][2]);
    }
}


uz_ParaID_ElectricalID_fft_in_t uz_calculate_psi_pms_ElectricalID(float induced_voltage[10000], float ISR_sampletime)
{
    // data inits
    float frequencies[5001];
    float amplitudes[5001];
    float angles[5001];
    const uint16_t n_order = 5U;
    uint16_t order[] = {1U, 3U, 5U, 7U, 9U};    // orders to determine (5 in total)
    uint16_t indices_real[n_order];             // array to save indices of psi_psm orders
    float psi_pms[n_order][3];                  // array holding psi pms
    uz_ParaID_ElectricalID_fft_in_t output;     // output struct for ParaID
    // calculate FFT
    FFTRecordedVoltage(induced_voltage, ISR_sampletime, frequencies, amplitudes, angles);
    // find fft peaks for psi_pm orders
    uz_find_fft_peak_indices(order, n_order, amplitudes, 5001U,indices_real);
    // calculate psi_pms
    uz_calculate_psi_pms(psi_pms, indices_real, n_order, frequencies, amplitudes, angles);
    // write to output struct
    memcpy(output.psi_pm_amplitude, &psi_pms[0][1], sizeof(float)*n_order);
    memcpy(output.psi_pm_angle, &psi_pms[0][2], sizeof(float)*n_order);
    output.finished_flag = true;
    return output;
}