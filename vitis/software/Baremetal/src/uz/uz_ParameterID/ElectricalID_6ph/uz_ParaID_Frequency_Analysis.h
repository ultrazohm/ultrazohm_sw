/******************************************************************************
 * Copyright 2022 Valentin Hoppe
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#ifndef FREQUENCY_ANALYSIS_H
#define FREQUENCY_ANALYSIS_H

#include "../uz_ParameterID_data.h"
#include "../../uz_math_constants.h"

/**
 * @brief find the index of the highest value in an array of floats
 * 
 * @param array array to search inside
 * @param elements number of elements inside the array
 * @return index of the first occurance of the highest number (as index, meaning first number is 0)
 */
uint16_t uz_find_array_max_value_index(float array[], uint16_t elements);

/**
 * @brief slices a large array to a smaller one and searches the largest number in the smaller range
 * 
 * @param full_array array to search inside
 * @param ideal_index middle value of the given range to search inside
 * @param range half of the range, meaning the sliced array will be "range" values before and "range" values after the middle number
 * @param fft_elements number of elements in the large array
 * @return index of the first occurance of the highest number in the given range, but the index is respective to the full array
 */
uint16_t uz_find_real_index_in_range(float full_array[], uint16_t ideal_index, const uint16_t range, uint16_t fft_elements);

/**
 * @brief finds the indices of the peaks of fft amplitudes
 * 
 * @param order array with all orders to look for, e.g. [1,3,5,7,9] meaning fundamental, 3rd, 5th, ... order
 * @param n_order amount of orders to search including fundamental, for given example 5 
 * @param fft_amplitudes array with the amplitudes of the fft
 * @param fft_elements number of elements in the large array
 * @param indices_real array with the size of "n_order" to save the indices of the peaks
 */
void uz_find_fft_peak_indices(uint16_t order[], const uint16_t n_order, float fft_amplitudes[], const uint16_t fft_elements, uint16_t indices_real[]);

/**
 * @brief wraps an angle to the range from 0-2pi
 * 
 * @param angle angle to wrap
 * @return wrapped angle
 */
float uz_wrap_to_2pi(float angle);

/**
 * @brief calculates psi_pms from a given fft result of an induced voltage measurement
 * 
 * @param psi_pm 2D array containing the frequency, amplitude and angle in the y-dimension and all "n_order" orders in the x-dimension
 * @param indices_real array with the size of "n_order" containing the indices of the peaks/orders of psi_pm
 * @param n_order amount of orders to search including fundamental
 * @param fft_frequencies array with the frequencies of the fft
 * @param fft_amplitudes array with the amplitudes of the fft
 * @param fft_angles array with the angles of the fft
 */
void uz_calculate_psi_pms(float psi_pm[][3], uint16_t indices_real[], const uint16_t n_order, float fft_frequencies[], float fft_amplitudes[], float fft_angles[]);

#endif // FREQUENCY_ANALYSIS_H
