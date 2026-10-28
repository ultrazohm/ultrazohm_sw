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
#define SDW_SINC3_OSR 100U // Dezimierungsfaktor (OSR) des SINC³-Filters, Basis für start_time_us Berechnung
// data valid reset �berpr�fen
/* Initilalisieurng der IP Cores (s. Treiber). Jede Filterinstanz hat eine eigene, unabhaengige Config. */
struct uz_JL_SigmaDelta_Interface_config_t filter_config[SDW_FILTER_ENDMARKER] = {
	[SDW_FILTER_P] = {
		.base_address = XPAR_UZ_USER_SIGMADELTA_P_BASEADDR,
		.ip_clk_frequency_Hz = 100000000.0f,
		.dezimation = 100,	// Dezimierungsfaktor für ZK-Spannungsmessung
		.clk_ratio = 10, 		// Taktrate des Sigma-Delta-Modulators (5 Mhz untere Grenze AMC1204)
		.switch_edge = 0,	    //0 = every falling edge, 1 = every second even falling edge, 2 = every second odd falling edge; anpassbar für verschiedene Sigma-Delta-Wandler
		.switch_cont_disc = true,	// TODO: neues Inport-Signal aus IP-Core-Regenerierung, Bedeutung/gewünschter Wert noch nicht validiert
		.filt_input_delay = 3,	// Verzögerung des Abtastzeitpunkts, um Gruppenlaufzeit zu kompensieren, in 10 ns Schritten; 9 f�r 5 Mhz, 3 f�r 10 Mhz
		.clk_dutycycle = 0.8,  // Clock Dutycycle, anpassbar zur kompensation von , durch LWL; 5MHz 0,65, 10Mhz 0,8 -> nur 10% Schritte,
		.start_time_us = 32.0f,//(50e-6f - (1.0f / (10000000.0f / SDW_SINC3_OSR)) * 1.5f),
		.delay_data_valid = 0,
		.sinc_sample_periods = 4,	// TODO: bislang nur fest vorgegeben, Wert nicht experimentell validiert
		.use_clk_ext = false,	// TODO: neues Inport-Signal aus IP-Core-Regenerierung, Bedeutung/gewünschter Wert noch nicht validiert
		.sel_pwm_trigger = false,
		.en_ocp = false,	// OCP-Schutz laeuft auf SDW_FILTER_OCP; hier konfiguriert aber deaktiviert
		.en_udc = false,
		.en_ph4 = false,
	},
	[SDW_FILTER_I] = {
		// TODO: eigenstaendige Config fuer den zweiten Filter (z.B. andere Dezimation/Sinc-Sample-Periods
		// fuer eine staerkere/schwaechere Filterung). base_address = 0 bis die zweite HW-Instanz existiert;
		// SigmaDeltaWandler_init() initialisiert diese Instanz erst, wenn SDW_SECOND_FILTER_HW_AVAILABLE == 1 ist.
		.base_address = XPAR_UZ_USER_SIGMADELTA_I_BASEADDR,	// TODO: XPAR_UZ_USER_UZ_JL_SIGMADELTA_INT_1_BASEADDR nach HW-Erweiterung eintragen
		.ip_clk_frequency_Hz = 100000000.0f,
		.dezimation = 2000,
		.clk_ratio = 10,
		.switch_edge = 0,
		.switch_cont_disc = false,
		.filt_input_delay = 3,
		.clk_dutycycle = 0.8,
		.start_time_us = 0.0f,
		.delay_data_valid = 0,
		.sinc_sample_periods = 2,
		.use_clk_ext = true,
		.sel_pwm_trigger = true,
		.en_ocp = false,	// OCP-Schutz laeuft auf SDW_FILTER_OCP; hier konfiguriert aber deaktiviert
		.en_udc = false,
		.en_ph4 = false,
	},
	[SDW_FILTER_OCP] = {
		// Dritte Filterinstanz fuer den FPGA-Ueberstromschutz (OCP). Existiert im FPGA-Design,
		// ist aber noch nicht in der SW verfuegbar: solange base_address == 0 liefert
		// SigmaDeltaWandler_init() NULL (Gate), die Instanz wird also noch nicht initialisiert.
		.base_address = XPAR_UZ_USER_SIGMADELTA_OCP_BASEADDR,	// TODO: XPAR_UZ_USER_UZ_JL_SIGMADELTA_INT_2_BASEADDR nach HW-Export eintragen
		.ip_clk_frequency_Hz = 100000000.0f,
		.dezimation = 8,	// TODO: reale Parameter der OCP-Instanz (Platzhalter analog SDW_FILTER_P)
		.clk_ratio = 10,
		.switch_edge = 0,
		.switch_cont_disc = false,
		.filt_input_delay = 3,
		.clk_dutycycle = 0.8,
		.start_time_us = 32.0f,
		.delay_data_valid = 0,
		.sinc_sample_periods = 4,
		.use_clk_ext = true,
		.sel_pwm_trigger = false,
		.en_ocp = true,	// Ueberstromschutz fuer diese Instanz aktiv (i_ph_max/min werden in init berechnet)
		.en_udc = false,
		.en_ph4 = false,
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
 * k_manual/offset_manual und derosr_160_iosr_1000 aktuellen OSR berechnet (k_per_count = k_manual / OSR^3,
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
	[SDW_FILTER_P] = {
		[SDW_CH_PH1] = {.k_manual =  70.0f, .offset_manual = -0.00037f},//68.91812
		[SDW_CH_PH2] = {.k_manual =  70.0f, .offset_manual = -0.00028f},//71.22505
		[SDW_CH_PH3] = {.k_manual =  70.0f, .offset_manual = -0.0005f},
	//	[SDW_CH_PH4] = {.k_manual = 1.0f, .offset_manual = 0.0f}, // TODO: Platzhalter, reale Kalibrierwerte noch zu bestimmen
	//	[SDW_CH_U]   = {.k_manual = 1.0f, .offset_manual = 0.0f}, // TODO: Platzhalter, reale Kalibrierwerte noch zu bestimmen
	},
	[SDW_FILTER_I] = {
		[SDW_CH_PH1] = {.k_manual =  70.0f, .offset_manual = -0.00037f},//68.91812
		[SDW_CH_PH2] = {.k_manual =  70.0f, .offset_manual = -0.00028f},//71.22505
		[SDW_CH_PH3] = {.k_manual =  70.0f, .offset_manual = -0.0005f},
	// SDW_FILTER_1: Kalibrierwerte noch offen (TODO), solange die zweite HW-Instanz nicht existiert.
	},
	[SDW_FILTER_OCP] = {
		// k_manual wie P/I (70), damit die counts-Umrechnung der OCP-Grenzen einen gueltigen
		// Divisor hat. offset_manual fuer OCP irrelevant (offset-freie, symmetrische Schwelle).
		[SDW_CH_PH1] = {.k_manual =  70.0f, .offset_manual = 0.0f},	// TODO: reale Kalibrierung
		[SDW_CH_PH2] = {.k_manual =  70.0f, .offset_manual = 0.0f},
		[SDW_CH_PH3] = {.k_manual =  70.0f, .offset_manual = 0.0f},
	},
};

static bool is_initialized[SDW_FILTER_ENDMARKER] = {false};

// Gleitender Fenster-Mittelwert des rohen (unkalibrierten) Werts je Filterinstanz und Kanal, zur
// Bestimmung von offset_counts (siehe SigmaDeltaWandler_get_raw_average). Filter und Puffer werden
// nur bei aktiviertem Feature (SDW_RAW_AVERAGE_ENABLED) allokiert; raw_average[][] bleibt immer
// definiert, damit SigmaDeltaWandler_get_raw_average unabhaengig davon kompiliert.
#if SDW_RAW_AVERAGE_ENABLED
static uz_movingAverageFilter_t *raw_average_filter[SDW_FILTER_ENDMARKER][SDW_CH_ENDMARKER];
static float raw_average_buffer[SDW_FILTER_ENDMARKER][SDW_CH_ENDMARKER][SDW_OFFSET_AVG_WINDOW_LENGTH];
#endif
static float raw_average[SDW_FILTER_ENDMARKER][SDW_CH_ENDMARKER] = {0};

uz_JL_SigmaDelta_Interface_t *SigmaDeltaWandler_init(enum SigmaDeltaWandler_filter_instance filter)
{
	uz_assert(filter < SDW_FILTER_ENDMARKER);

	// Instanz (noch) nicht in HW verfuegbar (keine Basisadresse exportiert) -> ueberspringen.
	// Dadurch kann main.c SigmaDeltaWandler_init auch fuer SDW_FILTER_OCP gefahrlos aufrufen,
	// solange XPAR_...INT_2 / base_address noch nicht gesetzt ist (Pointer bleibt NULL).
	if (filter_config[filter].base_address == 0U) {
		return NULL;
	}

	// DC-Gain (OSR^3) je Kanal: PH1..PH4 nutzen dezimation_I, U nutzt dezimation_U.
	// Wird fuer die OCP-Grenzen UND die Kalibrierung gebraucht, daher vor dem IP-Core-init.
	float osr = (float)filter_config[filter].dezimation;
	float osr_cubed = osr * osr * osr;

	// OCP-Stromgrenzen aus den globalen A-Vorgaben in Rohwert-counts umrechnen und in die
	// Config schreiben, bevor der IP-Core initialisiert wird (write_config_to_pl schreibt sie
	// dann mit). counts = I_A * OSR^3 / k_manual (offset-frei); PH1..PH3 haben identisches k_manual.
	if (filter_config[filter].en_ocp) {
		float k = calibration[filter][SDW_CH_PH1].k_manual;
		uz_assert_not_zero(k);
		filter_config[filter].i_ph_max = (int32_t)roundf(SDW_OCP_I_MAX_A * osr_cubed / k);
		filter_config[filter].i_ph_min = (int32_t)roundf(SDW_OCP_I_MIN_A * osr_cubed / k);
	}

	/* Initialisierung des IP Cores*/
	uz_JL_SigmaDelta_Interface_t *filter_instance = uz_JL_SigmaDelta_Interface_init(filter_config[filter]);

#if SDW_RAW_AVERAGE_ENABLED
	/* Initialisierung des gleitenden Fenster-Mittelwerts für jeden Kanal */
	struct uz_movingAverageFilter_config avg_config = {.filterLength = SDW_OFFSET_AVG_WINDOW_LENGTH};
	for (uint32_t ch = 0U; ch < SDW_CH_ENDMARKER; ch++) {
		uz_array_float_t buffer = {.length = SDW_OFFSET_AVG_WINDOW_LENGTH, .data = raw_average_buffer[filter][ch]};
		raw_average_filter[filter][ch] = uz_movingAverageFilter_init(avg_config, buffer);
	}
#endif

	/* Initialisierung der Kalibrierwerte */
	for (uint32_t ch = 0U; ch < SDW_CH_ENDMARKER; ch++) {
		/* Skalieren der manuellen Kalibrierwerte auf die OSR*/
		calibration[filter][ch].k_per_count = calibration[filter][ch].k_manual / osr_cubed;
		calibration[filter][ch].offset_counts = (int32_t)roundf(calibration[filter][ch].offset_manual * osr_cubed);
	}

	is_initialized[filter] = true;

	return filter_instance;
}

/* ISR-Pfad: Strobe + Registerreads + Kalibrierung in einem Aufruf. */
void SigmaDeltaWandler_read_and_process(uz_JL_SigmaDelta_Interface_t *instance, enum SigmaDeltaWandler_filter_instance filter, struct uz_JL_SigmaDelta_Interface_output_t_float *result)
{
	uz_assert(is_initialized[filter]);
	uz_assert_not_NULL(result);

	struct uz_JL_SigmaDelta_Interface_output_t raw = uz_JL_SigmaDelta_Interface_get_outputs(instance);
	const struct SigmaDeltaWandler_calibration_t *cal = calibration[filter];

	result->data_PH1_A = (float)(raw.data_PH1 - cal[SDW_CH_PH1].offset_counts) * cal[SDW_CH_PH1].k_per_count;
	result->data_PH2_A = (float)(raw.data_PH2 - cal[SDW_CH_PH2].offset_counts) * cal[SDW_CH_PH2].k_per_count;
	result->data_PH3_A = (float)(raw.data_PH3 - cal[SDW_CH_PH3].offset_counts) * cal[SDW_CH_PH3].k_per_count;
	result->data_PH4_A = (float)(raw.data_PH4 - cal[SDW_CH_PH4].offset_counts) * cal[SDW_CH_PH4].k_per_count;
	result->data_U_V   = (float)(raw.data_U   - cal[SDW_CH_U].offset_counts)   * cal[SDW_CH_U].k_per_count;

	// Gleitender Fenster-Mittelwert des rohen (unkalibrierten) FPGA-Werts je Kanal, nur bei
	// aktiviertem SDW_RAW_AVERAGE_ENABLED, um offset_counts zu bestimmen (bei 0A/0V einschwingen
	// lassen, siehe SigmaDeltaWandler_get_raw_average). Statt (float)raw.data_PHx kann auch der
	// kalibrierte result->data_PHx gemittelt werden.
#if SDW_RAW_AVERAGE_ENABLED
	raw_average[filter][SDW_CH_PH1] = uz_movingAverageFilter_sample(raw_average_filter[filter][SDW_CH_PH1], (float)raw.data_PH1);
	raw_average[filter][SDW_CH_PH2] = uz_movingAverageFilter_sample(raw_average_filter[filter][SDW_CH_PH2], (float)raw.data_PH2);
	raw_average[filter][SDW_CH_PH3] = uz_movingAverageFilter_sample(raw_average_filter[filter][SDW_CH_PH3], (float)raw.data_PH3);
	raw_average[filter][SDW_CH_PH4] = uz_movingAverageFilter_sample(raw_average_filter[filter][SDW_CH_PH4], (float)raw.data_PH4);
	raw_average[filter][SDW_CH_U]   = uz_movingAverageFilter_sample(raw_average_filter[filter][SDW_CH_U],   (float)raw.data_U);
#endif
}

/* Zugriff auf den eingeschwungenen Rohwert-Mittelwert je Kanal (siehe raw_average). Wird nur
 * aktualisiert, wenn SDW_RAW_AVERAGE_ENABLED gesetzt ist; sonst bleibt der Wert 0. */
float *SigmaDeltaWandler_get_raw_average(enum SigmaDeltaWandler_filter_instance filter, enum SigmaDeltaWandler_channel channel)
{
	uz_assert(filter < SDW_FILTER_ENDMARKER);
	uz_assert(channel < SDW_CH_ENDMARKER);
	return &raw_average[filter][channel];
}
