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
		.dezimation = 125,	// Dezimierungsfaktor für ZK-Spannungsmessung
		.clk_ratio = 10, 		// Taktrate des Sigma-Delta-Modulators (5 Mhz untere Grenze AMC1204), Taktrate = ip_clk_frequency_Hz/clk_ratio
		.switch_edge = 0,	    //0 = every falling edge, 1 = every second even falling edge, 2 = every second odd falling edge; anpassbar für verschiedene Sigma-Delta-Wandler
		.switch_cont_disc = true, // false = kontinuierlich, true = diskontinuierlich; 
		.filt_input_delay = 3,	// Verzögerung des Abtastzeitpunkts, um Gruppenlaufzeit zu kompensieren, in 10 ns Schritten; 9 f�r 5 Mhz, 3 f�r 10 Mhz
		.clk_dutycycle = 0.8,  // Clock Dutycycle, anpassbar zur kompensation von , durch LWL; 5MHz 0,65, 10Mhz 0,8 -> nur 10% Schritte,
		.start_time_us = 31.25f, // ISR Trigger - 1.5*OSR/10MHz+(sinc_sample_periods-3)*OSR/10Mhz 
		.delay_data_valid = 1,
		.sinc_sample_periods = 3,	// Anzahl an Dezimierungsstufen im Filter mit reset. S. Simulinkmodell
		.use_clk_ext = false,	
		.sel_pwm_trigger = false, // false = pwm min; true = pwm max
	},
	[SDW_FILTER_I] = {
		.base_address = XPAR_UZ_USER_SIGMADELTA_I_BASEADDR,	
		.ip_clk_frequency_Hz = 100000000.0f,
		.dezimation = 2000,
		.clk_ratio = 10,
		.switch_edge = 0,
		.switch_cont_disc = false,
		.filt_input_delay = 3,
		.clk_dutycycle = 0.8,
		.start_time_us = 0.0f,
		.delay_data_valid = 0,
		.sinc_sample_periods = 3,
		.use_clk_ext = true,
		.sel_pwm_trigger = false,
	},
	[SDW_FILTER_OCP] = {
		// Dritte Filterinstanz fuer den FPGA-Ueberstromschutz (OCP). Existiert im FPGA-Design,
		.base_address = XPAR_UZ_USER_SIGMADELTA_OCP_BASEADDR,	
		.ip_clk_frequency_Hz = 100000000.0f,
		.dezimation = 8,	
		.clk_ratio = 10,
		.switch_edge = 0,
		.switch_cont_disc = false,
		.filt_input_delay = 3,
		.clk_dutycycle = 0.8,
		.start_time_us = 32.0f,
		.delay_data_valid = 0,
		.sinc_sample_periods = 3,
		.use_clk_ext = true,
		.sel_pwm_trigger = false,
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

	// DC-Gain (OSR^3) je Kanal: PH1..PH4 nutzen dezimation_I, U nutzt dezimation_U.
	// Wird fuer die Kalibrierung gebraucht. Die OCP-Stromgrenzen werden separat in
	// SigmaDeltaWandler_init_ocp (eigener uz_JL_SDC_OCP-Core) berechnet.
	float osr = (float)filter_config[filter].dezimation;
	float osr_cubed = osr * osr * osr;

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

/* HW-Konfiguration der uz_JL_SDC_OCP-Ueberstromerkennungs-Cores, indiziert ueber die Filterinstanz,
 * deren Datenvektor (In1) der jeweilige OCP-Core in der PL vergleicht. base_address == 0 bedeutet:
 * fuer diese Filterinstanz existiert kein OCP-Core (-> SigmaDeltaWandler_init_ocp liefert NULL). */
static const struct {
	uint32_t base_address;
	float    i_max_A;    // obere Strom-Grenze in Ampere
	float    i_min_A;    // untere Strom-Grenze in Ampere
	int32_t  u_dc_max;   // obere ZK-Spannungs-Grenze in counts (TODO: realen Wert festlegen)
	int32_t  u_dc_min;   // untere ZK-Spannungs-Grenze in counts (TODO: realen Wert festlegen)
	bool     en_udc;     // Spannungsueberwachung aktiv
	bool     en_ph4;     // Phase 4 ueberwachen
	bool     en_ocp;     // Ueberstromschutz aktiv
} 

ocp_hw[SDW_FILTER_ENDMARKER] = {
	[SDW_FILTER_P] = {
		.base_address = XPAR_UZ_USER_UZ_JL_SDC_OCP_P_BASEADDR,
		.i_max_A = SDW_OCP_I_MAX_A,
		.i_min_A = SDW_OCP_I_MIN_A,
		.en_udc = false,
		.en_ph4 = false,
		.en_ocp = false,
	},
	[SDW_FILTER_I] = {
		.base_address = 0U,   // keine OCP-Instanz fuer den I-Filter
	},
	[SDW_FILTER_OCP] = {
		.base_address = XPAR_UZ_USER_UZ_JL_SDC_OCP_OCP_BASEADDR,
		.i_max_A = SDW_OCP_I_MAX_A,
		.i_min_A = SDW_OCP_I_MIN_A,
		.en_udc = false,
		.en_ph4 = false,
		.en_ocp = false,
	},
};

uz_JL_SDC_OCP_t *SigmaDeltaWandler_init_ocp(enum SigmaDeltaWandler_filter_instance filter)
{
	uz_assert(filter < SDW_FILTER_ENDMARKER);
	if (ocp_hw[filter].base_address == 0U) {
		return NULL;   // keine OCP-Erkennungs-Instanz fuer diese Filterinstanz
	}

	// Stromgrenzen aus A in Rohwert-counts der zugehoerigen Filterinstanz umrechnen:
	// counts = I_A * OSR^3 / k_manual (offset-frei). OSR/k_manual MUESSEN zur SigmaDelta-Instanz
	// passen, deren Datenvektor (In1) der OCP-Core vergleicht (P: OSR=100, OCP: OSR=8).
	float osr = (float)filter_config[filter].dezimation;
	float osr_cubed = osr * osr * osr;
	float k = calibration[filter][SDW_CH_PH1].k_manual;
	uz_assert_not_zero(k);

	struct uz_JL_SDC_OCP_config_t config = {
		.base_address = ocp_hw[filter].base_address,
		.ip_clk_frequency_Hz = (uint32_t)filter_config[filter].ip_clk_frequency_Hz,
		.i_ph_max = (int32_t)roundf(ocp_hw[filter].i_max_A * osr_cubed / k),
		.i_ph_min = (int32_t)roundf(ocp_hw[filter].i_min_A * osr_cubed / k),
		.u_dc_max = ocp_hw[filter].u_dc_max,
		.u_dc_min = ocp_hw[filter].u_dc_min,
		.en_udc = ocp_hw[filter].en_udc,
		.en_ph4 = ocp_hw[filter].en_ph4,
		.en_ocp = ocp_hw[filter].en_ocp,
	};
	return uz_JL_SDC_OCP_init(config);
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
//	result->data_PH4_A = (float)(raw.data_PH4 - cal[SDW_CH_PH4].offset_counts) * cal[SDW_CH_PH4].k_per_count;
//	result->data_U_V   = (float)(raw.data_U   - cal[SDW_CH_U].offset_counts)   * cal[SDW_CH_U].k_per_count;

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
