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
#include "../../uz_complex/uz_complex.h"


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
    if((angle < 2.0f*UZ_PIf) && (angle >= 0.0f))
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
    static float frequencies[5001];
    static float amplitudes[5001];
    static float angles[5001];
    uint16_t order[] = {1U, 3U, 5U, 7U, 9U};    // orders to determine (5 in total)
    uint16_t indices_real[PARAMETERID6PH_ELECTRICAL_N_ORDER];             // array to save indices of psi_psm orders
    float psi_pms[PARAMETERID6PH_ELECTRICAL_N_ORDER][3];                  // array holding psi pms
    uz_ParaID_ElectricalID_fft_in_t output;     // output struct for ParaID
    // calculate FFT
    FFTRecordedVoltage(induced_voltage, ISR_sampletime, 100e-6, frequencies, amplitudes, angles);
    // find fft peaks for psi_pm orders
    uz_find_fft_peak_indices(order, PARAMETERID6PH_ELECTRICAL_N_ORDER, amplitudes, 5001U, indices_real);
    // calculate psi_pms
    uz_calculate_psi_pms(psi_pms, indices_real, PARAMETERID6PH_ELECTRICAL_N_ORDER, frequencies, amplitudes, angles);
    // write to output struct
    for(uint16_t i=0U;i<PARAMETERID6PH_ELECTRICAL_N_ORDER;i++)
    {
        output.psi_pm_frequency[i] = psi_pms[i][0];
        output.psi_pm_amplitude[i] = psi_pms[i][1];
        output.psi_pm_angle[i] = psi_pms[i][2];
    }
    output.finished_flag = true;
    return output;
}

uz_ParaID_ElectricalID_fft_in_t uz_correct_psi_pms_ElectricalID(uz_ParaID_ElectricalID_fft_in_t psi_pm_uncorrected, uz_ParaID_GlobalConfig_t global_config, const uint16_t n_order)
{
    uz_ParaID_ElectricalID_fft_in_t psi_pm_corrected = psi_pm_uncorrected;
    uz_complex_cartesian_t Xc[n_order];
    uz_complex_cartesian_t R_parallel;
    uz_complex_cartesian_t R_series;
    uz_complex_cartesian_t Z_parallel[n_order];
    uz_complex_polar_t factor[n_order];
    R_parallel.real = global_config.voltage_measurement_Rp;
    R_parallel.imag = 0.0f;
    R_series.real = global_config.voltage_measurement_Rs;
    R_series.imag = 0.0f;

    for(uint16_t i=0U;i<n_order;i++)
    {   
        Xc[i].real = 0.0f;
        Xc[i].imag = -1.0f/(global_config.voltage_measurement_C*psi_pm_uncorrected.psi_pm_frequency[i]*2.0f*UZ_PIf);                
    }
    for(uint16_t i=0U;i<n_order;i++)
        Z_parallel[i] = uz_complex_division(uz_complex_multiplication(R_parallel,Xc[i]),uz_complex_addition(R_parallel,Xc[i]));
    for(uint16_t i=0U;i<n_order;i++)
        factor[i] = uz_complex_cartesian_to_polar(uz_complex_division(uz_complex_addition(Z_parallel[i],R_series),Z_parallel[i]));
    for(uint16_t i=0U;i<n_order;i++)
    {
        //printf("%f, %f\n", factor[i].abs, factor[i].angle);
        psi_pm_corrected.psi_pm_amplitude[i] = psi_pm_uncorrected.psi_pm_amplitude[i]*factor[i].abs/factor[0].abs;
        psi_pm_corrected.psi_pm_angle[i] = psi_pm_uncorrected.psi_pm_angle[i] + factor[i].angle;
        psi_pm_corrected.psi_pm_angle[i] = uz_wrap_to_2pi(psi_pm_corrected.psi_pm_angle[i] - psi_pm_corrected.psi_pm_angle[0]);
    }
    return psi_pm_corrected;
}