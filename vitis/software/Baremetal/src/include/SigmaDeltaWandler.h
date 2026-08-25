/******************************************************************************
Jonathan Link 2026
******************************************************************************/

#ifndef INCLUDE_SIGMADELTAWANDLER_H_
#define INCLUDE_SIGMADELTAWANDLER_H_

#include <stdint.h>
#include "../IP_Cores/uz_JL_SigmaDelta_Interface/uz_JL_SigmaDelta_Interface.h"

// Kanaele des SD-Demodulators (Auswahl der Kalibrierwerte/OSR)
enum SigmaDeltaWandler_channel {
	SDW_CH_PH1 = 0,
	SDW_CH_PH2,
	SDW_CH_PH3,
	SDW_CH_PH4,
	SDW_CH_U,
	SDW_CH_ENDMARKER
};

// Filterinstanzen: SDW_FILTER_0 ist der bestehende, physisch vorhandene Sinc3-Filter.
// SDW_FILTER_1 ist ein zweiter, softwareseitig vorbereiteter Filter fuer eine zukuenftige
// getrennte P-/I-Messwertversorgung des Stromreglers (siehe SDW_SECOND_FILTER_HW_AVAILABLE).
enum SigmaDeltaWandler_filter_instance {
	SDW_FILTER_0 = 0,
	SDW_FILTER_1,
	SDW_FILTER_ENDMARKER
};

// TODO: auf 1 setzen, sobald eine zweite Hardware-Instanz des IP-Cores existiert
// (XPAR_UZ_USER_UZ_JL_SIGMADELTA_INT_1_BASEADDR nach Erweiterung des Vivado Block Designs
// und Re-Export der Hardware-Plattform). Bis dahin bleibt SDW_FILTER_1 uninitialisiert.
#define SDW_SECOND_FILTER_HW_AVAILABLE 0

// TODO: tatsaechlichen Wert festlegen, sobald das Verhaeltnis der Abtastraten von
// Sinc3_Filter_2 zur ISR-Rate final feststeht (abhaengig von dessen Dezimation/sinc_sample_periods).
#define SDW_FILTER2_DATA_VALID_CNT_THRESHOLD 1U

// Schaltet die Trennung von P-/I-Anteil in der Regelung (struct_Ctrl_Config.sel_act_I) ein/aus.
// Nur sinnvoll aktivierbar, wenn SDW_SECOND_FILTER_HW_AVAILABLE == 1 (sonst bleibt der I-Zweig auf 0).
#define SDW_ACT_I_SEPARATE_CALC_ENABLED 0U

/**
 * @brief Initialisiert den SD-Demod-IP-Core (filter_config[filter]).
 * Muss in main.c (init_ip_cores) vor dem ersten Aufruf von
 * SigmaDeltaWandler_process fuer diese Filterinstanz ausgefuehrt werden.
 * @param filter Zu initialisierende Filterinstanz (SDW_FILTER_0 oder SDW_FILTER_1).
 * @return uz_JL_SigmaDelta_Interface_t* Initialisierte Filter-Instanz (siehe Sinc3_Filter/Sinc3_Filter_2 in main.c),
 * oder NULL falls filter == SDW_FILTER_1 und die zweite Hardware-Instanz noch nicht verfuegbar ist
 * (SDW_SECOND_FILTER_HW_AVAILABLE == 0).
 */
uz_JL_SigmaDelta_Interface_t *SigmaDeltaWandler_init(enum SigmaDeltaWandler_filter_instance filter);

/**
 * @brief Wandelt die rohen Sinc3-Ausgangswerte des SD-Demod-IP-Cores (Spannung + 4
 * Phasenstroeme) in die kalibrierten physikalischen Werte (V, A) um. Der AMC1204-
 * Bitstream wird vom Sinc3-Filter bipolar (-1/+1) verarbeitet, der Rohwert ist bei
 * 0A/0V bereits um 0 zentriert. Kein LEM-Wandler mehr vorhanden (neuer ADC), daher
 * kein bekannter theoretischer Vollausschlag - die Umrechnung erfolgt je Kanal ueber
 * eine im Code hinterlegte lineare Kalibrierung (k, Offset), siehe SigmaDeltaWandler.c.
 *
 * @param filter Filterinstanz, deren Kalibrierung/OSR fuer die Umrechnung verwendet wird.
 * @param raw Unbeschnittene Rohwerte aus den Sinc3-Ausgangsregistern (uz_JL_SDDemod_get_outputs).
 * @param result Ausgabe: kalibrierte Werte (data_U in Volt, data_PH1..PH4 in Ampere).
 */
void SigmaDeltaWandler_process(enum SigmaDeltaWandler_filter_instance filter, struct uz_JL_SigmaDelta_Interface_output_t raw, struct uz_JL_SigmaDelta_Interface_output_t_float *result);

/**
 * @brief Liefert einen Pointer auf den gleitenden Fenster-Mittelwert (uz_movingAverageFilter,
 * siehe SDW_OFFSET_AVG_WINDOW_LENGTH) des rohen (unkalibrierten) Kanalwerts. Dient zur
 * Bestimmung von offset_counts: bei 0A/0V ueber die Einschwingzeit beobachten und den
 * eingeschwungenen Wert als offset_counts uebernehmen. Der Pointer ist bereits vor
 * SigmaDeltaWandler_init gueltig (zeigt auf ein statisches Array), der Wert wird aber erst
 * ab dem ersten SigmaDeltaWandler_process-Aufruf aktualisiert.
 * @param filter Filterinstanz (SDW_FILTER_0 oder SDW_FILTER_1).
 * @param channel Kanal (SDW_CH_PH1 .. SDW_CH_PH4, SDW_CH_U).
 * @return float* Pointer auf den aktuellen gemittelten Rohwert des Kanals.
 */
float *SigmaDeltaWandler_get_raw_average(enum SigmaDeltaWandler_filter_instance filter, enum SigmaDeltaWandler_channel channel);

#endif /* INCLUDE_SIGMADELTAWANDLER_H_ */
