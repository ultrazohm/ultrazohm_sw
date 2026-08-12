/******************************************************************************
Jonathan Link 2026

Softwaremodul zum Auswerten mehrere sigma-Delta-Wandlers und Sinc³ Filtes auf dem FPGA.
Modul ist angepasst für SH-Strommessplatine

- Initialisierung des IP Cores
- Kalibirierung der Kanäle
- Skalierung, Offset und Aufbereitung der Rohdaten aus dem Filter

******************************************************************************/

#include "../include/SigmaDeltaWandler.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_JL_SigmaDelta_Interface/uz_JL_SigmaDelta_Interface.h"
#include "../uz/uz_movingAverageFilter/uz_movingAverageFilter.h"
#include "../uz/uz_array/uz_array.h"
#include "xparameters.h"
#include <stdbool.h>
#include <math.h>

#define SDW_OFFSET_AVG_WINDOW_LENGTH 2000U // Fensterlänge zum ermitteln des DC Offsets 


/* Initilalisieurng des IP Cores (s. Treiber)*/
struct uz_JL_SigmaDelta_Interface_config_t Sinc3_Filter_config = {
		.base_address = XPAR_UZ_USER_UZ_JL_SIGMADELTA_INT_0_BASEADDR,
		.ip_clk_frequency_Hz = 100000000.0f,
		.dezimation = 500,	// Dezimierungsfaktor für ZK-Spannungsmessung
		.clk_ratio = 10, 		// Taktrate des Sigma-Delta-Modulators (5 Mhz untere Grenze AMC1204)
		.switch_edge = 0,	    //0 = every falling edge, 1 = every second even falling edge, 2 = every second odd falling edge; anpassbar für verschiedene Sigma-Delta-Wandler
		.filt_input_delay = 3,	// Verzögerung des Abtastzeitpunkts, um Gruppenlaufzeit zu kompensieren, in 10 ns Schritten; 9 f�r 5 Mhz, 3 f�r 10 Mhz
		.dsw_clk_en = true,		// Aktivieren der Clock des DSW
		.clk_dutycycle = 0.75,  // Clock Dutycycle, anpassbar zur kompensation von Signalverzerrung durch LWL; 5MHz 0,65, 10Mhz 0,75,
};

/**
 * @brief Kalibrierung eines Kanals, OSR-unabhaengig: Wert = (raw/OSR^3 - offset_manual) * k_manual
 * (k_manual ist je nach Kanal A oder V pro normierter Einheit)
 *
 * Der DC-Gain des Sinc3-Filters ist OSR^3 (siehe SigmaDeltaWandler_process_channel). 
 *
 * k_manual/offset_manual: manuell einzutragende Kalibrierwerte
 * k_per_count/offset_counts: NICHT von Hand setzen - werden in SigmaDeltaWandler_init aus
 * k_manual/offset_manual und der aktuellen OSR berechnet (k_per_count = k_manual / OSR^3,
 * offset_counts = offset_manual * OSR^3).
 */
struct SigmaDeltaWandler_calibration_t {
	float k_manual;
	float offset_manual;
	float k_per_count;
	int32_t offset_counts;
};

/* Struct zum Kalibrieren der Kanäle. Hier für vier Strommessungen und eine Spannungsmeessung*/
static struct SigmaDeltaWandler_calibration_t calibration[SDW_CH_ENDMARKER] = {
	[SDW_CH_PH1] = {.k_manual = 67.29f, .offset_manual = -0.00043f},
	[SDW_CH_PH2] = {.k_manual = 66.8f, .offset_manual = -0.000348f},
	[SDW_CH_PH3] = {.k_manual = 68.21f, .offset_manual = -0.00055f},
	[SDW_CH_PH4] = {.k_manual = 1.0f, .offset_manual = 0.0f},
	[SDW_CH_U]   = {.k_manual = 1.0f, .offset_manual = 0.0f},
};

static bool is_initialized = false;

// Gleitender Fenster-Mittelwert des rohen (unkalibrierten) Werts je Kanal, zur
// Bestimmung von offset_counts (siehe SigmaDeltaWandler_get_raw_average).
static uz_movingAverageFilter_t *raw_average_filter[SDW_CH_ENDMARKER];
static float raw_average_buffer[SDW_CH_ENDMARKER][SDW_OFFSET_AVG_WINDOW_LENGTH];
static float raw_average[SDW_CH_ENDMARKER] = {0};

uz_JL_SigmaDelta_Interface_t *SigmaDeltaWandler_init(void)
{
	/* Initialisierung des IP Cores*/
	uz_JL_SigmaDelta_Interface_t *Sinc3_Filter = uz_JL_SigmaDelta_Interface_init(Sinc3_Filter_config);

	/* Initialisierung des gleitenden Fenster-Mittelwerts für jeden Kanal */
	struct uz_movingAverageFilter_config avg_config = {.filterLength = SDW_OFFSET_AVG_WINDOW_LENGTH};
	for (uint32_t ch = 0U; ch < SDW_CH_ENDMARKER; ch++) {
		uz_array_float_t buffer = {.length = SDW_OFFSET_AVG_WINDOW_LENGTH, .data = raw_average_buffer[ch]};
		raw_average_filter[ch] = uz_movingAverageFilter_init(avg_config, buffer);
	}

	// DC-Gain (OSR^3) je Kanal: PH1..PH4 nutzen dezimation_I, U nutzt dezimation_U.
	float osr = (float)Sinc3_Filter_config.dezimation;
	float osr_cubed = osr * osr * osr;


	/* Initialisierung der Kalibrierwerte */
	for (uint32_t ch = 0U; ch < SDW_CH_ENDMARKER; ch++) {
		/* Skalieren der manuellen Kalibrierwerte auf die OSR*/
		calibration[ch].k_per_count = calibration[ch].k_manual / osr_cubed;
		calibration[ch].offset_counts = (int32_t)roundf(calibration[ch].offset_manual * osr_cubed);
	}

	is_initialized = true;

	return Sinc3_Filter;
}

/* Funktion zum Verarbeiten der Filterrohwerte */
static float SigmaDeltaWandler_process_channel(int32_t raw_fpga_value, enum SigmaDeltaWandler_channel channel)
{
	uz_assert(is_initialized);
	uz_assert(channel < SDW_CH_ENDMARKER);

	int32_t centered_val = raw_fpga_value - calibration[channel].offset_counts;
	float output = (float)centered_val * calibration[channel].k_per_count;

	raw_average[channel] = uz_movingAverageFilter_sample(raw_average_filter[channel], output);
	return output;
}

float *SigmaDeltaWandler_get_raw_average(enum SigmaDeltaWandler_channel channel)
{
	uz_assert(channel < SDW_CH_ENDMARKER);
	return &raw_average[channel];
}

/* Funktion, um die Verarbeitung von allen Phasenströmen aufzurufen*/
void SigmaDeltaWandler_process(struct uz_JL_SigmaDelta_Interface_output_t raw, struct uz_JL_SigmaDelta_Interface_output_t_float *result)
{
	uz_assert_not_NULL(result);

	result->data_U   = SigmaDeltaWandler_process_channel(raw.data_U,   SDW_CH_U);
	result->data_PH1 = SigmaDeltaWandler_process_channel(raw.data_PH1, SDW_CH_PH1);
	result->data_PH2 = SigmaDeltaWandler_process_channel(raw.data_PH2, SDW_CH_PH2);
	result->data_PH3 = SigmaDeltaWandler_process_channel(raw.data_PH3, SDW_CH_PH3);
	result->data_PH4 = SigmaDeltaWandler_process_channel(raw.data_PH4, SDW_CH_PH4);
}
