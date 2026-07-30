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

#ifndef INCLUDE_SIGMADELTAWANDLER_H_
#define INCLUDE_SIGMADELTAWANDLER_H_

#include <stdint.h>
#include "../IP_Cores/uz_JL_SDDemod/uz_JL_SDDemod.h"

// Kanaele des SD-Demodulators (Auswahl der Kalibrierwerte/OSR)
enum SigmaDeltaWandler_channel {
	SDW_CH_PH1 = 0,
	SDW_CH_PH2,
	SDW_CH_PH3,
	SDW_CH_PH4,
	SDW_CH_U,
	SDW_CH_ENDMARKER
};

/**
 * @brief Initialisiert den SD-Demod-IP-Core (SD_Filter_config).
 * Muss in main.c (init_ip_cores) vor dem ersten Aufruf von
 * SigmaDeltaWandler_process ausgefuehrt werden.
 * @return uz_JL_SDDemod_t* Initialisierte SD_Filter-Instanz (siehe SD_Filter in main.c).
 */
uz_JL_SDDemod_t *SigmaDeltaWandler_init(void);

/**
 * @brief Wandelt die rohen Sinc3-Ausgangswerte des SD-Demod-IP-Cores (Spannung + 4
 * Phasenstroeme) in die kalibrierten physikalischen Werte (V, A) um. Der AMC1204-
 * Bitstream wird vom Sinc3-Filter bipolar (-1/+1) verarbeitet, der Rohwert ist bei
 * 0A/0V bereits um 0 zentriert. Kein LEM-Wandler mehr vorhanden (neuer ADC), daher
 * kein bekannter theoretischer Vollausschlag - die Umrechnung erfolgt je Kanal ueber
 * eine im Code hinterlegte lineare Kalibrierung (k, Offset), siehe SigmaDeltaWandler.c.
 *
 * @param raw Unbeschnittene Rohwerte aus den Sinc3-Ausgangsregistern (uz_JL_SDDemod_get_outputs).
 * @param result Ausgabe: kalibrierte Werte (data_U in Volt, data_PH1..PH4 in Ampere).
 */
void SigmaDeltaWandler_process(struct uz_JL_SDDemod_output_t raw, struct uz_JL_SDDemod_output_t_float *result);

/**
 * @brief Liefert einen Pointer auf den gleitenden Fenster-Mittelwert (uz_movingAverageFilter,
 * siehe SDW_OFFSET_AVG_WINDOW_LENGTH) des rohen (unkalibrierten) Kanalwerts. Dient zur
 * Bestimmung von offset_counts: bei 0A/0V ueber die Einschwingzeit beobachten und den
 * eingeschwungenen Wert als offset_counts uebernehmen. Der Pointer ist bereits vor
 * SigmaDeltaWandler_init gueltig (zeigt auf ein statisches Array), der Wert wird aber erst
 * ab dem ersten SigmaDeltaWandler_process-Aufruf aktualisiert.
 * @param channel Kanal (SDW_CH_PH1 .. SDW_CH_PH4, SDW_CH_U).
 * @return float* Pointer auf den aktuellen gemittelten Rohwert des Kanals.
 */
float *SigmaDeltaWandler_get_raw_average(enum SigmaDeltaWandler_channel channel);

#endif /* INCLUDE_SIGMADELTAWANDLER_H_ */
