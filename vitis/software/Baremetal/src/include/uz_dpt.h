/******************************************************************************
Jonathan Link 2026

Doppelpulstest (DPT) fuer eine Halbbruecke der PWM_and_SS_control_V4_ip.

Funktionsprinzip:
- Puls 1 (Aufmagnetisierung) wird ueber die normale 10 kHz Control-ISR gefahren
  (Tristate_HB1=false, Duty=1.0), bis der Sinc3-Strommesswert die Zielschwelle
  erreicht (siehe uz_dpt_update_charging).
- Ab dem Ausschalten von Puls 1 uebernimmt ein TTC0-Hardware-Timer (PS Triple
  Timer Counter, eigener Interrupt am selben GIC wie die PWM-ISR) die feine
  Sequenz aus Trennzeit und Puls 2. Der Timer laeuft mit dem vollen 100 MHz
  IP-Takt (10 ns Aufloesung) und ist komplett unabhaengig vom 10 kHz PWM-Takt.
- Ein-/Ausschalten erfolgt ausschliesslich ueber uz_PWM_SS_2L_set_tristate():
  Die Duty Cycle bleibt fuer den gesamten Test bei 1.0, das Tristate-Register
  wirkt laut IP-Core (PWM_and_SS_control_V4_ip_src_VSI_Control_Signal_Switch.vhd)
  direkt am IP-Takt und NICHT traegerfrequenz-synchronisiert wie die Duty Cycle -
  dadurch ist eine Aufloesung im Bereich weniger 100 ns statt 1/PWM_freq_Hz moeglich.

Hinweis Interrupt-Prioritaet: Der TTC0-Interrupt wird mit derselben (hoechsten)
Prioritaet wie die PWM-ISR registriert. Faellt ein TTC-Interrupt zufaellig in
die Ausfuehrungszeit der PWM-ISR, wird er dadurch etwas verzoegert (siehe
JSSD_FLOAT_ISR_ExecTime_us fuer die typische Groessenordnung). Fuer die
meisten DPT-Anwendungen ist das unkritisch, da es die Gesamt-Zeitbasis nicht
verschiebt (der Timer selbst laeuft unbeeinflusst weiter).

Hinweis HB2/HB3: Aktuell ist HB1 als Pruefling fest verdrahtet. Um den DPT
stattdessen auf HB2 oder HB3 anzuwenden, sind ausschliesslich drei Stellen
anzupassen (jeweils nur die Position eines Parameters verschieben, keine
Logikaenderung):
 1. uz_dpt.c, uz_dpt_set_outputs(): Position von "!hb1_active" in den drei
    Tristate-Parametern verschieben.
 2. uz_dpt.c, uz_dpt_arm(): Position der 1.0f in uz_PWM_SS_2L_set_duty_cycle()
    entsprechend mitverschieben.
 3. isr.c, case DPT: uz_dpt_update_charging() auf den passenden Sinc3-Kanal
    umstellen (data_PH1<->HB1, data_PH2<->HB2, data_PH3<->HB3).
******************************************************************************/

#ifndef INCLUDE_UZ_DPT_H_
#define INCLUDE_UZ_DPT_H_

#include <stdbool.h>
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

// Ablaufzustaende des Doppelpulstests
typedef enum _uz_dpt_state_t_ {
	dpt_idle = 0,  // kein Test aktiv, Ausgaenge tristate
	dpt_charging,  // Puls 1: Aufmagnetisierung bis Soll-Strom erreicht
	dpt_deadtime,  // Trennzeit zwischen Puls 1 und Puls 2 (TTC0-gesteuert)
	dpt_pulse2,    // Puls 2: kurzer Einschaltpuls (TTC0-gesteuert)
	dpt_done,      // Test erfolgreich abgeschlossen, Ausgaenge tristate
	dpt_fault      // Abbruch durch Timeout oder Ueberstrom, Ausgaenge tristate
} uz_dpt_state_t;

// Parameter eines DPT-Laufs
typedef struct _uz_dpt_config_t_ {
	float target_current_A;  // Soll-Strom, bei dem Puls 1 endet
	float max_current_A;     // harte Ueberstromschwelle -> sofortiger Abbruch (Fault)
	float charge_timeout_ms; // maximale Dauer von Puls 1 (Sicherheitsabschaltung)
	float deadtime_us;       // Trennzeit zwischen Puls 1 und Puls 2
	float pulse2_width_us;   // Breite von Puls 2
} uz_dpt_config_t;

/**
 * @brief Initialisiert den TTC0-Timer und haengt dessen Interrupt an den GIC.
 * Muss einmalig nach Initialize_ISR() (GIC_instance muss existieren) aufgerufen werden.
 */
void uz_dpt_init(void);

/**
 * @brief Startet einen neuen DPT-Lauf: Tristate/Duty werden gesetzt und Puls 1 beginnt sofort.
 * @param dut_pwm Halbbruecken-Instanz, an der der Pruefling haengt (HB1 = Pruefling, HB2/HB3 werden tristate geschaltet).
 * @param config Testparameter (Zielstrom, Timeout, Trennzeit, Puls-2-Breite, Ueberstromschwelle).
 */
void uz_dpt_arm(uz_PWM_SS_2L_t *dut_pwm, uz_dpt_config_t config);

/**
 * @brief Muss waehrend dpt_charging jeden 10 kHz Control-ISR-Zyklus mit dem aktuellen
 * Strommesswert des Pruefling-Kanals aufgerufen werden. Beendet Puls 1 (Uebergabe an den
 * TTC0-Timer), sobald Zielstrom erreicht ist, oder bricht bei Timeout/Ueberstrom ab.
 */
void uz_dpt_update_charging(float measured_current_A);

/**
 * @brief Bricht einen laufenden Test sofort ab: TTC0 stoppen, alle drei Halbbruecken tristate.
 * Sollte aufgerufen werden, wenn ctrl_state waehrend eines laufenden Tests verlassen wird.
 */
void uz_dpt_abort(void);

uz_dpt_state_t uz_dpt_get_state(void);

#endif /* INCLUDE_UZ_DPT_H_ */
