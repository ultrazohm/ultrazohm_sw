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

#define SDW_OFFSET_AVG_WINDOW_LENGTH 10000U // Fensterlänge zum ermitteln des DC Offsets
#define SDW_SINC3_OSR 225U // Dezimierungsfaktor (OSR) des SINC³-Filters, Basis für start_time_us Berechnung
// Idq Ref und ISt werte loggen, filter f�r p und i teil separat, Sinc filter Signalfolge loggen

/* Initilalisieurng der IP Cores (s. Treiber). Jede Filterinstanz hat eine eigene, unabhaengige Config. */
struct uz_JL_SigmaDelta_Interface_config_t filter_config[SDW_FILTER_ENDMARKER] = {
	[SDW_FILTER_0] = {
		.base_address = XPAR_UZ_USER_UZ_JL_SIGMADELTA_INT_0_BASEADDR,
		.ip_clk_frequency_Hz = 100000000.0f,
		.dezimation = SDW_SINC3_OSR,	// Dezimierungsfaktor für ZK-Spannungsmessung
		.clk_ratio = 10, 		// Taktrate des Sigma-Delta-Modulators (5 Mhz untere Grenze AMC1204)
		.switch_edge = 0,	    //0 = every falling edge, 1 = every second even falling edge, 2 = every second odd falling edge; anpassbar für verschiedene Sigma-Delta-Wandler
		.switch_cont_disc = true,	// TODO: neues Inport-Signal aus IP-Core-Regenerierung, Bedeutung/gewünschter Wert noch nicht validiert
		.filt_input_delay = 3,	// Verzögerung des Abtastzeitpunkts, um Gruppenlaufzeit zu kompensieren, in 10 ns Schritten; 9 f�r 5 Mhz, 3 f�r 10 Mhz
		.clk_dutycycle = 0.8,  // Clock Dutycycle, anpassbar zur kompensation von Signalverzerrung durch LWL; 5MHz 0,65, 10Mhz 0,8 -> nur 10% Schritte,
		.start_time_us = 13.25f,//(50e-6f - (1.0f / (10000000.0f / SDW_SINC3_OSR)) * 1.5f),
		.delay_data_valid = 0,
		.sinc_sample_periods = 4,	// TODO: bislang nur fest vorgegeben, Wert nicht experimentell validiert
		.use_clk_ext = false,	// TODO: neues Inport-Signal aus IP-Core-Regenerierung, Bedeutung/gewünschter Wert noch nicht validiert
	},
	[SDW_FILTER_1] = {
		// TODO: eigenstaendige Config fuer den zweiten Filter (z.B. andere Dezimation/Sinc-Sample-Periods
		// fuer eine staerkere/schwaechere Filterung). base_address = 0 bis die zweite HW-Instanz existiert;
		// SigmaDeltaWandler_init() initialisiert diese Instanz erst, wenn SDW_SECOND_FILTER_HW_AVAILABLE == 1 ist.
		.base_address = XPAR_UZ_USER_UZ_JL_SIGMADELTA_INT_1_BASEADDR,	// TODO: XPAR_UZ_USER_UZ_JL_SIGMADELTA_INT_1_BASEADDR nach HW-Erweiterung eintragen
		.ip_clk_frequency_Hz = 100000000.0f,
		.dezimation = 500,
		.clk_ratio = 10,
		.switch_edge = 0,
		.switch_cont_disc = false,
		.filt_input_delay = 3,
		.clk_dutycycle = 0.8,
		.start_time_us = 13.25f,
		.delay_data_valid = 0,
		.sinc_sample_periods = 3,
		.use_clk_ext = true,
	},
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

/* Struct zum Kalibrieren der Kanäle. Hier für vier Strommessungen und eine Spannungsmeessung, je Filterinstanz. */
static struct SigmaDeltaWandler_calibration_t calibration[SDW_FILTER_ENDMARKER][SDW_CH_ENDMARKER] = {
	[SDW_FILTER_0] = {
		[SDW_CH_PH1] = {.k_manual =  70.0f, .offset_manual = -0.00037f},//68.91812
		[SDW_CH_PH2] = {.k_manual =  70.0f, .offset_manual = -0.00028f},//71.22505
		[SDW_CH_PH3] = {.k_manual =  70.0f, .offset_manual = -0.0005f},
	//	[SDW_CH_PH4] = {.k_manual = 1.0f, .offset_manual = 0.0f}, // TODO: Platzhalter, reale Kalibrierwerte noch zu bestimmen
	//	[SDW_CH_U]   = {.k_manual = 1.0f, .offset_manual = 0.0f}, // TODO: Platzhalter, reale Kalibrierwerte noch zu bestimmen
	},
	// SDW_FILTER_1: Kalibrierwerte noch offen (TODO), solange die zweite HW-Instanz nicht existiert.
};

static bool is_initialized[SDW_FILTER_ENDMARKER] = {false};

// Gleitender Fenster-Mittelwert des rohen (unkalibrierten) Werts je Filterinstanz und Kanal, zur
// Bestimmung von offset_counts (siehe SigmaDeltaWandler_get_raw_average).
static uz_movingAverageFilter_t *raw_average_filter[SDW_FILTER_ENDMARKER][SDW_CH_ENDMARKER];
static float raw_average_buffer[SDW_FILTER_ENDMARKER][SDW_CH_ENDMARKER][SDW_OFFSET_AVG_WINDOW_LENGTH];
static float raw_average[SDW_FILTER_ENDMARKER][SDW_CH_ENDMARKER] = {0};

uz_JL_SigmaDelta_Interface_t *SigmaDeltaWandler_init(enum SigmaDeltaWandler_filter_instance filter)
{
	uz_assert(filter < SDW_FILTER_ENDMARKER);

#if !SDW_SECOND_FILTER_HW_AVAILABLE
	if (filter == SDW_FILTER_1) {
		// Zweite HW-Instanz existiert noch nicht (siehe SDW_SECOND_FILTER_HW_AVAILABLE) - keine Initialisierung.
		return NULL;
	}
#endif

	/* Initialisierung des IP Cores*/
	uz_JL_SigmaDelta_Interface_t *filter_instance = uz_JL_SigmaDelta_Interface_init(filter_config[filter]);

	/* Initialisierung des gleitenden Fenster-Mittelwerts für jeden Kanal */
	struct uz_movingAverageFilter_config avg_config = {.filterLength = SDW_OFFSET_AVG_WINDOW_LENGTH};
	for (uint32_t ch = 0U; ch < SDW_CH_ENDMARKER; ch++) {
		uz_array_float_t buffer = {.length = SDW_OFFSET_AVG_WINDOW_LENGTH, .data = raw_average_buffer[filter][ch]};
		raw_average_filter[filter][ch] = uz_movingAverageFilter_init(avg_config, buffer);
	}

	// DC-Gain (OSR^3) je Kanal: PH1..PH4 nutzen dezimation_I, U nutzt dezimation_U.
	float osr = (float)filter_config[filter].dezimation;
	float osr_cubed = osr * osr * osr;


	/* Initialisierung der Kalibrierwerte */
	for (uint32_t ch = 0U; ch < SDW_CH_ENDMARKER; ch++) {
		/* Skalieren der manuellen Kalibrierwerte auf die OSR*/
		calibration[filter][ch].k_per_count = calibration[filter][ch].k_manual / osr_cubed;
		calibration[filter][ch].offset_counts = (int32_t)roundf(calibration[filter][ch].offset_manual * osr_cubed);
	}

	is_initialized[filter] = true;

	return filter_instance;
}

/* Funktion zum Verarbeiten der Filterrohwerte */
static float SigmaDeltaWandler_process_channel(enum SigmaDeltaWandler_filter_instance filter, int32_t raw_fpga_value, enum SigmaDeltaWandler_channel channel)
{
	uz_assert(is_initialized[filter]);
	uz_assert(channel < SDW_CH_ENDMARKER);

	int32_t centered_val = raw_fpga_value - calibration[filter][channel].offset_counts;
	float output = (float)centered_val * calibration[filter][channel].k_per_count;

	raw_average[filter][channel] = uz_movingAverageFilter_sample(raw_average_filter[filter][channel], output);
	return output;
}

float *SigmaDeltaWandler_get_raw_average(enum SigmaDeltaWandler_filter_instance filter, enum SigmaDeltaWandler_channel channel)
{
	uz_assert(filter < SDW_FILTER_ENDMARKER);
	uz_assert(channel < SDW_CH_ENDMARKER);
	return &raw_average[filter][channel];
}

/* Funktion, um die Verarbeitung von allen Phasenströmen aufzurufen*/
void SigmaDeltaWandler_process(enum SigmaDeltaWandler_filter_instance filter, struct uz_JL_SigmaDelta_Interface_output_t raw, struct uz_JL_SigmaDelta_Interface_output_t_float *result)
{
	uz_assert_not_NULL(result);


	result->data_PH1 = SigmaDeltaWandler_process_channel(filter, raw.data_PH1, SDW_CH_PH1);
	result->data_PH2 = SigmaDeltaWandler_process_channel(filter, raw.data_PH2, SDW_CH_PH2);
	result->data_PH3 = SigmaDeltaWandler_process_channel(filter, raw.data_PH3, SDW_CH_PH3);
//	result->data_PH4 = SigmaDeltaWandler_process_channel(filter, raw.data_PH4, SDW_CH_PH4);
//	result->data_U   = SigmaDeltaWandler_process_channel(filter, raw.data_U,   SDW_CH_U);
}
