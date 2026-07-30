/******************************************************************************
* Copyright 2026 Jonathan Link
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

#include "../include/SigmaDeltaWandler.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_JL_SDDemod/uz_JL_SDDemod.h"
#include "../uz/uz_movingAverageFilter/uz_movingAverageFilter.h"
#include "../uz/uz_array/uz_array.h"
#include "xparameters.h"
#include <stdbool.h>

// Fensterlaenge fuer die Offset-Mittelung: 1000 Samples bei 10kHz ISR-Rate = 100ms Fenster.
#define SDW_OFFSET_AVG_WINDOW_LENGTH 2000U

struct uz_JL_SDDemod_config_t SD_Filter_config = {
		.base_address = XPAR_UZ_JL_SDDEMOD_0_BASEADDR,
		.ip_clk_frequency_Hz = 100000000.0f,
		.dezimation_U = 250,
		.dezimation_I = 400,
		.clk_ratio = 20, 		// 5 Mhz untere Grenze AMC1204
		.switch_edge = false,	//false = every falling edge, true = every second falling edge
		.filt_input_delay = 9,	// in 10ns Schritten
		.calib_en = false,
		.dsw_clk_en = true,
		.clk_dutycycle = 0.65,  //0.65 CLk Dutycycle angepasst, damit am ADC bei 50%
};

/**
 * @brief Kalibrierung eines Kanals: Wert = (raw - offset_counts) * k_per_count
 * (k_per_count ist je nach Kanal A/Count oder V/Count)
 */
struct SigmaDeltaWandler_calibration_t {
	float k_per_count;
	int32_t offset_counts;
};

// TODO: Kalibrierwerte je Kanal eintragen (Strom-/Spannungsmessreihe, linearer Fit).
// Noch nicht kalibriert -> k_per_count = 0.0f liefert bewusst 0 statt falscher Werte.
static struct SigmaDeltaWandler_calibration_t calibration[SDW_CH_ENDMARKER] = {
	[SDW_CH_PH1] = {.k_per_count = 1.0f, .offset_counts = -26920},
	[SDW_CH_PH2] = {.k_per_count = 1.0f, .offset_counts = -22750},
	[SDW_CH_PH3] = {.k_per_count = 1.0f, .offset_counts = -34375},
	[SDW_CH_PH4] = {.k_per_count = 1.0f, .offset_counts = 0},
	[SDW_CH_U]   = {.k_per_count = 1.0f, .offset_counts = 0},
};

static bool is_initialized = false;

// Gleitender Fenster-Mittelwert des rohen (unkalibrierten) Werts je Kanal, zur
// Bestimmung von offset_counts (siehe SigmaDeltaWandler_get_raw_average).
static uz_movingAverageFilter_t *raw_average_filter[SDW_CH_ENDMARKER];
static float raw_average_buffer[SDW_CH_ENDMARKER][SDW_OFFSET_AVG_WINDOW_LENGTH];
static float raw_average[SDW_CH_ENDMARKER] = {0};

uz_JL_SDDemod_t *SigmaDeltaWandler_init(void)
{
	uz_JL_SDDemod_t *SD_Filter = uz_JL_SDDemod_init(SD_Filter_config);

	struct uz_movingAverageFilter_config avg_config = {.filterLength = SDW_OFFSET_AVG_WINDOW_LENGTH};
	for (uint32_t ch = 0U; ch < SDW_CH_ENDMARKER; ch++) {
		uz_array_float_t buffer = {.length = SDW_OFFSET_AVG_WINDOW_LENGTH, .data = raw_average_buffer[ch]};
		raw_average_filter[ch] = uz_movingAverageFilter_init(avg_config, buffer);
	}

	is_initialized = true;

	return SD_Filter;
}

// AMC1204-Bitstream wird vom Sinc3-Filter als bipolar (-1/+1, nicht 0/1) verarbeitet.
// Bei 0A/0V (50% Einsen) mitteln sich +1 und -1 zu 0 -> der Rohwert ist bereits um 0
// zentriert, kein geometrischer Mittenoffset (OSR^3/2) noetig. Verbleibender realer
// Offset (Verstaerker-/Kanalfehler) wird ausschliesslich ueber offset_counts kalibriert.
static float SigmaDeltaWandler_process_channel(int32_t raw_fpga_value, enum SigmaDeltaWandler_channel channel)
{
	uz_assert(is_initialized);
	uz_assert(channel < SDW_CH_ENDMARKER);

	raw_average[channel] = uz_movingAverageFilter_sample(raw_average_filter[channel], (float)raw_fpga_value);

	int32_t centered_val = raw_fpga_value - calibration[channel].offset_counts;
	return (float)centered_val * calibration[channel].k_per_count;
}

float *SigmaDeltaWandler_get_raw_average(enum SigmaDeltaWandler_channel channel)
{
	uz_assert(channel < SDW_CH_ENDMARKER);
	return &raw_average[channel];
}

void SigmaDeltaWandler_process(struct uz_JL_SDDemod_output_t raw, struct uz_JL_SDDemod_output_t_float *result)
{
	uz_assert_not_NULL(result);

	result->data_U   = SigmaDeltaWandler_process_channel(raw.data_U,   SDW_CH_U);
	result->data_PH1 = SigmaDeltaWandler_process_channel(raw.data_PH1, SDW_CH_PH1);
	result->data_PH2 = SigmaDeltaWandler_process_channel(raw.data_PH2, SDW_CH_PH2);
	result->data_PH3 = SigmaDeltaWandler_process_channel(raw.data_PH3, SDW_CH_PH3);
	result->data_PH4 = SigmaDeltaWandler_process_channel(raw.data_PH4, SDW_CH_PH4);
}
