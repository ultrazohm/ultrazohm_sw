/******************************************************************************
Jonathan Link 2026
******************************************************************************/

#include "../include/uz_dpt.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "xttcps.h"
#include "xscugic.h"
#include "xparameters.h"

// TTC0 (Zaehler 0 des ersten PS Triple Timer Counter Moduls) - im Rest der
// Firmware unbenutzt (nur TTC9 wird vom BSP als Sleep-Timer verwendet).
#define UZ_DPT_TTC_DEVICE_ID XPAR_XTTCPS_0_DEVICE_ID
#define UZ_DPT_TTC_INTR_ID   XPAR_XTTCPS_0_INTR
#define UZ_DPT_TTC_CLK_HZ    ((float)XPAR_XTTCPS_0_CLOCK_HZ) // 100 MHz -> 10 ns/Count

// bereits in isr.c initialisiert (Rpu_GicInit) - hier wird nur ein zweiter
// Interrupt an denselben GIC angehaengt.
extern XScuGic GIC_instance;

static XTtcPs dpt_timer;
static volatile uz_dpt_state_t dpt_state = dpt_idle;
static uz_PWM_SS_2L_t *dpt_pwm = NULL;
static uz_dpt_config_t dpt_config;
static uint64_t dpt_charge_start_us = 0U;

static void uz_dpt_start_ttc_interval(float duration_us);
static void uz_dpt_set_outputs(bool hb1_active);
static void uz_dpt_ttc_isr(void *CallBackRef);

void uz_dpt_init(void)
{
	XTtcPs_Config *config = XTtcPs_LookupConfig(UZ_DPT_TTC_DEVICE_ID);
	uz_assert_not_NULL(config);

	// Falls TTC0 noch laeuft (z.B. Rest eines vorherigen Debug-Runs ohne vollen
	// PS-Reset ueber JTAG): XTtcPs_CfgInitialize() verweigert sonst die
	// Initialisierung eines bereits gestarteten Zaehlers mit XST_DEVICE_IS_STARTED.
	Xil_Out32(config->BaseAddress + XTTCPS_CNT_CNTRL_OFFSET, XTTCPS_CNT_CNTRL_DIS_MASK);

	s32 status = XTtcPs_CfgInitialize(&dpt_timer, config, config->BaseAddress);
	uz_assert(status == XST_SUCCESS);

	// Reiner Intervall-Interrupt-Timer, kein Wellenform-Ausgang, kein Vorteiler
	// (voller 100 MHz IP-Takt -> 10 ns pro Zaehlerschritt).
	XTtcPs_SetOptions(&dpt_timer, XTTCPS_OPTION_INTERVAL_MODE | XTTCPS_OPTION_WAVE_DISABLE);
	XTtcPs_SetPrescaler(&dpt_timer, XTTCPS_CLK_CNTRL_PS_DISABLE);

	XScuGic_SetPriorityTriggerType(&GIC_instance, UZ_DPT_TTC_INTR_ID, 0x0, 0b11);
	status = XScuGic_Connect(&GIC_instance, UZ_DPT_TTC_INTR_ID, (Xil_ExceptionHandler)uz_dpt_ttc_isr, (void *)&dpt_timer);
	uz_assert(status == XST_SUCCESS);
	XScuGic_Enable(&GIC_instance, UZ_DPT_TTC_INTR_ID);

	dpt_state = dpt_idle;
}

// HB1 = Pruefling, HB2/HB3 sind fuer die gesamte Testdauer tristate.
//
// Um den DPT stattdessen auf HB2 oder HB3 anzuwenden, muss NUR die Position
// von "!hb1_active" in den drei Tristate-Parametern (Reihenfolge: HB1, HB2, HB3)
// verschoben werden, z.B. fuer HB3: uz_PWM_SS_2L_set_tristate(dpt_pwm, true, true, !hb1_active);
// Zusaetzlich muessen dann noch angepasst werden:
//  - uz_dpt_arm(): die 1.0f in uz_PWM_SS_2L_set_duty_cycle() an dieselbe Position verschieben
//  - isr.c (case DPT): uz_dpt_update_charging() muss mit dem zur gewaehlten
//    Halbbruecke passenden Sinc3-Kanal aufgerufen werden (data_PH1<->HB1,
//    data_PH2<->HB2, data_PH3<->HB3)
static void uz_dpt_set_outputs(bool hb1_active)
{
	uz_PWM_SS_2L_set_tristate(dpt_pwm, !hb1_active, true, true);
}

void uz_dpt_arm(uz_PWM_SS_2L_t *dut_pwm, uz_dpt_config_t config)
{
	uz_assert_not_NULL(dut_pwm);
	uz_assert(config.target_current_A < config.max_current_A);

	// Falls (erneut) scharf geschaltet wird, waehrend TTC0 noch eine Trennzeit-/
	// Puls-2-Sequenz eines vorherigen Laufs bearbeitet: sauber stoppen, bevor
	// Puls 1 des neuen Laufs beginnt.
	XTtcPs_Stop(&dpt_timer);
	XTtcPs_DisableInterrupts(&dpt_timer, XTTCPS_IXR_ALL_MASK);

	dpt_pwm = dut_pwm;
	dpt_config = config;

	// Duty bleibt fuer den gesamten Test bei 1.0 - geschaltet wird ausschliesslich
	// ueber Tristate_HB1 (siehe uz_dpt_set_outputs / Header-Kommentar in uz_dpt.h).
	// Reihenfolge der Parameter: HB1, HB2, HB3 - fuer einen DPT auf HB2/HB3 die 1.0f
	// an die entsprechende Position verschieben (siehe Kommentar in uz_dpt_set_outputs).
	uz_PWM_SS_2L_set_duty_cycle(dpt_pwm, 1.0f, 0.0f, 0.0f);
	uz_dpt_set_outputs(true); // Puls 1 beginnt sofort

	dpt_charge_start_us = uz_SystemTime_GetUptimeInUs();
	dpt_state = dpt_charging;
}

void uz_dpt_update_charging(float measured_current_A)
{
	if (dpt_state != dpt_charging) {
		return;
	}

	if (measured_current_A >= dpt_config.max_current_A) {
		// Ueberstrom: sofort abschalten, Test als Fault beenden
		uz_dpt_set_outputs(false);
		dpt_state = dpt_fault;
		return;
	}

	uint64_t elapsed_us = uz_SystemTime_GetUptimeInUs() - dpt_charge_start_us;
	if (elapsed_us >= (uint64_t)(dpt_config.charge_timeout_ms * 1000.0f)) {
		// Zielstrom nicht rechtzeitig erreicht (z.B. Sensor-/Verdrahtungsfehler)
		uz_dpt_set_outputs(false);
		dpt_state = dpt_fault;
		return;
	}

	if (measured_current_A >= dpt_config.target_current_A) {
		// Ende Puls 1 (Schaltereignis 1) - Uebergabe der feinen Sequenz an TTC0
		uz_dpt_set_outputs(false);
		dpt_state = dpt_deadtime;
		uz_dpt_start_ttc_interval(dpt_config.deadtime_us);
	}
}

void uz_dpt_abort(void)
{
	XTtcPs_Stop(&dpt_timer);
	XTtcPs_DisableInterrupts(&dpt_timer, XTTCPS_IXR_ALL_MASK);
	if (dpt_pwm != NULL) {
		uz_PWM_SS_2L_set_tristate(dpt_pwm, true, true, true);
	}
	dpt_state = dpt_idle;
}

uz_dpt_state_t uz_dpt_get_state(void)
{
	return dpt_state;
}

static void uz_dpt_start_ttc_interval(float duration_us)
{
	XInterval interval_counts = (XInterval)(duration_us * UZ_DPT_TTC_CLK_HZ * 1e-6f);

	XTtcPs_Stop(&dpt_timer);
	XTtcPs_ResetCounterValue(&dpt_timer);
	XTtcPs_SetInterval(&dpt_timer, interval_counts);
	XTtcPs_ClearInterruptStatus(&dpt_timer, XTTCPS_IXR_ALL_MASK);
	XTtcPs_EnableInterrupts(&dpt_timer, XTTCPS_IXR_INTERVAL_MASK);
	XTtcPs_Start(&dpt_timer);
}

// Laeuft im TTC0-Interrupt-Kontext - fuehrt die zeitkritische Trennzeit/Puls-2
// Sequenz komplett unabhaengig vom 10 kHz Control-ISR aus.
static void uz_dpt_ttc_isr(void *CallBackRef)
{
	XTtcPs *timer = (XTtcPs *)CallBackRef;
	uint32_t status_event = XTtcPs_GetInterruptStatus(timer);
	XTtcPs_ClearInterruptStatus(timer, status_event);

	if ((status_event & XTTCPS_IXR_INTERVAL_MASK) == 0U) {
		return;
	}

	switch (dpt_state) {
	case dpt_deadtime:
		// Trennzeit abgelaufen -> Puls 2 (Schaltereignis 2, Einschalten) starten
		uz_dpt_set_outputs(true);
		dpt_state = dpt_pulse2;
		uz_dpt_start_ttc_interval(dpt_config.pulse2_width_us);
		break;

	case dpt_pulse2:
		// Puls 2 beendet - Test abgeschlossen
		uz_dpt_set_outputs(false);
		XTtcPs_Stop(timer);
		XTtcPs_DisableInterrupts(timer, XTTCPS_IXR_ALL_MASK);
		dpt_state = dpt_done;
		break;

	default:
		// unerwarteter Interrupt (z.B. nach uz_dpt_abort) - Timer anhalten
		XTtcPs_Stop(timer);
		XTtcPs_DisableInterrupts(timer, XTTCPS_IXR_ALL_MASK);
		break;
	}
}
