/******************************************************************************
 * Copyright 2021 Eyke Liegmann, Tobias Schindler, Sebastian Wendel
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

#include "../include/isr.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_SystemTime/uz_AxiTimer64Bit.h"

#define SDW_DATA_VALID_MAX_POLLS 250U  // Obergrenze Busy-Wait auf Sinc3 Data_valid pro ISR-Zyklus
#define SDW_DATA_VALID_MAX_FAILS 2U    // so viele ISR-Zyklen ohne gueltigen Wert -> Stop (idle_state)

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

static void ReadAllADC();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);

// Global variable structure
extern DS_Data Global_Data;
extern conv_status_signals_t conv_status_signals;
extern uz_codegen regelung;
bool data_valid= 0;

struct SDC_Interface_output_t Sinc3_Filter_P_out = {0};
static bool Sinc3_Filter_I_data_ready = false;
static uint32_t sinc3_P_data_valid_fail_cnt = 0U; // aufeinanderfolgende ISR-Zyklen ohne gueltigen Sinc3-Wert
Bus_ZM_In struct_ZM_In;
float theta_el_unwrapped = 0.0f;

/* Messwerterfassung der Sinc3-Filter: liest Filter_I (sofern genuegend Data_valid-Zyklen
 * vorliegen) und Filter_P (Busy-Wait auf Data_valid) in Global_Data.av ein, pflegt
 * Sinc3_Filter_I_data_ready sowie den Fehlzaehler und stoppt die Zustandsmaschine, wenn ueber
 * mehrere ISR-Zyklen kein gueltiger Sinc3_Filter_P-Wert vorliegt. Gemeinsame Routine fuer
 * running_state und control_state. */
static void sinc3_read_measurements(void)
{
	if (SDC_Interface_get_data_valid_cnt(Global_Data.objects.Sinc3_Filter_I) >= SDW_FILTER2_DATA_VALID_CNT_THRESHOLD)
	{
		SigmaDeltaWandler_read_and_process(Global_Data.objects.Sinc3_Filter_I, SDW_FILTER_I, &Global_Data.av.Sinc3_Filter_I);
		SDC_Interface_reset_data_valid_cnt(Global_Data.objects.Sinc3_Filter_I);
		Sinc3_Filter_I_data_ready = true;
	}
	else
	{
		Sinc3_Filter_I_data_ready = false;
	}

	bool sinc3_P_data_valid = false;
	for (uint32_t data_valid_poll = 0U; data_valid_poll < SDW_DATA_VALID_MAX_POLLS; data_valid_poll++)
	{
		if (SDC_Interface_is_data_valid(Global_Data.objects.Sinc3_Filter_P))
		{
			sinc3_P_data_valid = true;
			break;
		}
	}

	if (sinc3_P_data_valid)
	{
		sinc3_P_data_valid_fail_cnt = 0U;
		SigmaDeltaWandler_read_and_process(Global_Data.objects.Sinc3_Filter_P, SDW_FILTER_P, &Global_Data.av.Sinc3_Filter_P);
	}
	else
	{
		// Budget erschoepft: kein frischer Sinc3-Wert in diesem ISR-Zyklus,
		// Global_Data.av.Sinc3_Filter behaelt den letzten Wert
		sinc3_P_data_valid_fail_cnt++;
		if (sinc3_P_data_valid_fail_cnt >= SDW_DATA_VALID_MAX_FAILS)
		{
			ultrazohm_state_machine_set_stop(true); // zurueck in idle_state
		}
	}
}

/* Liest den FLT_ps-Fehlerstatus der FPGA-Ueberstromerkennung (SDC_OCP) fuer beide Pfade
 * (P- und OCP-Mess-Pfad) und loest bei einem Fehler einen gelatchten error_state aus (PWM aus).
 * Je Instanz NULL-geschuetzt. Ergaenzt - nicht ersetzt - die SW-seitige 18A-Abschaltung. Die
 * FPGA-Latches werden hier NICHT quittiert (reset_fault erfolgt spaeter ueber einen Bedienbefehl). */
static void sinc3_check_ocp_fault(void)
{
	// Kalibrierte OCP-Phasenstroeme einlesen, damit sie im JavaScope beobachtbar sind
	// (reine Visualisierung; die Abschaltentscheidung trifft die FPGA-Ueberstromerkennung).
	if (Global_Data.objects.Sinc3_Filter_OCP != NULL)
	{
		SigmaDeltaWandler_read_and_process(Global_Data.objects.Sinc3_Filter_OCP, SDW_FILTER_OCP, &Global_Data.av.Sinc3_Filter_OCP);
	}

	// Fehlercode beider Ueberstromerkennungs-Cores lesen und per ODER verknuepfen, damit auch ein
	// Ueberstrom im P-Mess-Pfad abschaltet.
	uint32_t flt = (uint32_t)SDC_OCP_FAULT_NONE;
	if (Global_Data.objects.sdc_ocp_P != NULL)
	{
		flt |= (uint32_t)SDC_OCP_get_fault(Global_Data.objects.sdc_ocp_P);
	}
	if (Global_Data.objects.sdc_ocp_OCP != NULL)
	{
		flt |= (uint32_t)SDC_OCP_get_fault(Global_Data.objects.sdc_ocp_OCP);
	}
	conv_status_signals.ocp_fault = flt;
	if (flt != (uint32_t)SDC_OCP_FAULT_NONE)
	{
		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		Global_Data.rasv.ctrl_state = ctrl_state_none;
		io_fault_shutdown_set_FLT_PS(Global_Data.objects.flt_dis, true);
		ultrazohm_state_machine_set_error(true);
	}
}

/* Liest die gelatchten HW-Fehler der Fehlerabschaltung (io_fault_shutdown: FLT_1..4/FLT_PS) und
 * des Regelkreis-Watchdogs (ctrl_loop_watchdog). Liegt einer an, wird ein gelatchter error_state
 * ausgeloest (PWM tristate in isr.c error_state). Die eigentliche IO-Sperre macht bereits die PL;
 * dieser Check zieht nur die SW-Statemachine nach. Quittiert wird NICHT hier, sondern ausschliesslich
 * ueber den Bedienbefehl Error_Reset. Je Instanz NULL-geschuetzt. */
static void check_hw_fault_shutdown(void)
{
	bool fault_active = false;
	if ((Global_Data.objects.flt_dis != NULL)
		&& (io_fault_shutdown_get_fault(Global_Data.objects.flt_dis) != IO_FAULT_SHUTDOWN_FAULT_NONE))
	{
		fault_active = true;
	}
	if ((Global_Data.objects.ctrl_loop_watchdog != NULL)
		&& ctrl_loop_watchdog_get_fault(Global_Data.objects.ctrl_loop_watchdog))
	{
		fault_active = true;
	}
	if (fault_active)
	{
		ultrazohm_state_machine_set_error(true); // -> error_state; Quittierung nur ueber Error_Reset
	}
}

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    //ReadAllADC();            // Nur bei Benutzung von ADC Karten
    uint64_t t0 = uz_AxiTimer64Bit_ReadValue64Bit();

    check_hw_fault_shutdown();	// io_fault_shutdown + Watchdog -> error_state bei gelatchtem Fehler

    /* Read status signal READY of the converter*/
    conv_status_signals.board_ready = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.input_gpio, BOARD_READY_BIT);
    struct_ZM_In.Inv_Ready = conv_status_signals.board_ready;

    /* Read IGBT desaturation fault signal */
   conv_status_signals.igbt_desat = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.input_gpio, IGBT_Desat_BIT);
   struct_ZM_In.IGBT_desat = conv_status_signals.igbt_desat;

	Global_Data.av.resolver_pl_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface);
	theta_el_unwrapped = Global_Data.av.resolver_pl_outputs.position_el_2pi - Global_Data.av.theta_el_offset;
	Global_Data.av.theta_el = uz_signals_wrap(theta_el_unwrapped, 2.0f*UZ_PIf);
	Global_Data.av.mechanicalPosition = Global_Data.av.resolver_pl_outputs.position_mech_2pi;
	Global_Data.av.omega_el = Global_Data.av.resolver_pl_outputs.omega_mech_rad_s*4.0f;
    regelung.input.Bus_PMSM_Out_g.pmsm_theta_mech_rad = Global_Data.av.mechanicalPosition;
    regelung.input.Bus_PMSM_Out_g.pmsm_Omega_mech_rad_s = Global_Data.av.resolver_pl_outputs.omega_mech_rad_s;
    regelung.input.Bus_PMSM_Out_g.pmsm_theta_el_rad = Global_Data.av.theta_el;
    regelung.input.Bus_PMSM_Out_g.pmsm_Omega_el_rad_s = Global_Data.av.omega_el;
    Global_Data.av.CB_omega_grads = Global_Data.av.resolver_pl_outputs.omega_mech_rad_s * (180.0f / UZ_PIf)/struct_Ctrl_Config.Getriebeuebersetzung;

	/* Multiturn-Positionsistwert (in Grad) aus uz_resolver_pos_mt lesen und als
	 * Istwert fuer die Positionsregelung im Codegen bereitstellen. */
	struct resolver_pos_mt_reading_t pos_mt = resolver_pos_mt_read_position(Global_Data.objects.resolver_pos_mt);
	Global_Data.av.mult_pos_grad = (float)pos_mt.multiturn_position_deg;
    Global_Data.av.mult_pos_turns = (float)pos_mt.turns;
	Global_Data.av.mult_pos_valid = pos_mt.valid;
	regelung.input.Bus_PMSM_Out_g.pmsm_mult_pos_grad = Global_Data.av.mult_pos_grad;

	/* Read UZ state for control state machine*/
    platform_state_t current_state=ultrazohm_state_machine_get_state();
    struct_ZM_In.UZ_Platform_State = current_state;
    switch(current_state)
    	{
    		case idle_state:
                if (Global_Data.objects.platform_state_old != idle_state)
                {

                    Global_Data.objects.platform_state_old = idle_state;
                    Global_Data.rasv.ctrl_state = ctrl_state_none;
                    struct_ZM_In.Soll_Drehzahl_Umin = 0;
                    struct_ZM_In.Soll_id_A = 0;
                    struct_ZM_In.Soll_iq_A = 0;
                    struct_ZM_In.Fehlermeldung = false;
                    struct_ZM_In.Modus_Position = Warten;
                    struct_ZM_In.Soll_Winkel_CB_Grad = 0.0f;
                    struct_ZM_In.Soll_Drehzahl_CB_Grads = 0.0f;
                    struct_ZM_In.Soll_Beschleunigung_CB_Grads2 = 0.0f;
                    struct_ZM_In.Soll_Drehzahl_Home_Grads = 0.0f;
                    Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
                    Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
                    Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
                    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, false);
                    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
                }
                regelung.input.Bus_ZM_In_o = struct_ZM_In;
				uz_codegen_step(&regelung);
    			break;
    		case running_state:
                if (Global_Data.objects.platform_state_old != running_state)
                {
                    Global_Data.objects.platform_state_old = running_state;
                	if (Global_Data.objects.sdc_ocp_P != NULL)
                    {
                        SDC_OCP_acknowledge_fault(Global_Data.objects.sdc_ocp_P);     // P-Pfad: DC maskieren -> FLT_Reset -> EN_OCP aus
                    }
                    if (Global_Data.objects.sdc_ocp_OCP != NULL)
                    {
                        SDC_OCP_acknowledge_fault(Global_Data.objects.sdc_ocp_OCP);   // OCP-Pfad: DC maskieren -> FLT_Reset -> EN_OCP aus
                    }
                    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, true);
                    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
                    Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
				    Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
                    Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
                    struct_ZM_In.Strom_gesperrt_rst = false;
                    struct_ZM_In.Soll_Drehzahl_Umin = 0;
    			    struct_ZM_In.Soll_id_A = 0;
    			    struct_ZM_In.Soll_iq_A = 0;
                    struct_ZM_In.Modus_Position = Warten;
                }
                else
                {
                    uint64_t t1 = uz_AxiTimer64Bit_ReadValue64Bit();
                    Global_Data.av.debug_timestamp_s = (float)(t1 - t0) / (UZ_AXI_TIMER_CLOCK_FREQ * 1e-6f);
					sinc3_read_measurements();
					sinc3_check_ocp_fault();	// FPGA-OCP: loest bei Fehler error_state aus (No-op solange OCP-Instanz NULL)

                    regelung.input.Bus_ZM_In_o = struct_ZM_In;
	                uz_codegen_step(&regelung);
                }
    			break;
    		case control_state:
    			if (Global_Data.objects.platform_state_old != control_state)
                    {
                        Global_Data.objects.platform_state_old = control_state;
                        Global_Data.rasv.ctrl_state = ctrl_state_none;
                        // Beide OCP-Instanzen scharfschalten: SDC_OCP_arm stellt die konfigurierten
                        // DC-Enables (EN_Udc/EN_I_dc) wieder her, aktiviert EN_OCP und quittiert den Latch.
                        // board_ready steht hier und der Sinc-Filter ist eingeschwungen -> kein
                        // Einschwing-Transient. (In Error_Reset wurden die Kanaele zuvor maskiert.)
                        if (Global_Data.objects.sdc_ocp_P != NULL)
                        {
                            SDC_OCP_arm(Global_Data.objects.sdc_ocp_P);
                        }
                        if (Global_Data.objects.sdc_ocp_OCP != NULL)
                        {
                            SDC_OCP_arm(Global_Data.objects.sdc_ocp_OCP);
                        }
                    }
                else
                    {
                        sinc3_read_measurements();
                        sinc3_check_ocp_fault();	// FPGA-OCP: loest bei Fehler error_state aus (No-op solange OCP-Instanz NULL)
                        regelung.input.Bus_PMSM_Out_g.pmsm_Iuvw_P_A[0] = Global_Data.av.Sinc3_Filter_P.data_PH1_A;
                        regelung.input.Bus_PMSM_Out_g.pmsm_Iuvw_P_A[1] = Global_Data.av.Sinc3_Filter_P.data_PH2_A;
                        regelung.input.Bus_PMSM_Out_g.pmsm_Iuvw_P_A[2] = Global_Data.av.Sinc3_Filter_P.data_PH3_A;
                        regelung.input.Bus_PMSM_Out_g.pmsm_Iuvw_I_A[0] = Global_Data.av.Sinc3_Filter_I.data_PH1_A;
                        regelung.input.Bus_PMSM_Out_g.pmsm_Iuvw_I_A[1] = Global_Data.av.Sinc3_Filter_I.data_PH2_A;
                        regelung.input.Bus_PMSM_Out_g.pmsm_Iuvw_I_A[2] = Global_Data.av.Sinc3_Filter_I.data_PH3_A;
                        regelung.input.trigger_actI_I_calc = SDW_ACT_I_SEPARATE_CALC_ENABLED && Sinc3_Filter_I_data_ready;

                        switch (Global_Data.rasv.ctrl_state)
                        {
                    
                        case current_control:
                            struct_ZM_In.Soll_iq_A = Global_Data.rasv.Soll_iq;
                            struct_ZM_In.Soll_id_A = Global_Data.rasv.Soll_id;
                            struct_ZM_In.Soll_Drehzahl_Umin = 0;
                            struct_ZM_In.Soll_Regelungsart = Ctrl_Strom;
                            struct_ZM_In.Modus_Position = Pos_Warten;
                            break;

                        case rpm_control:
                            struct_ZM_In.Soll_Drehzahl_Umin = Global_Data.rasv.Soll_Drehzahl;
                            struct_ZM_In.Soll_Regelungsart = Ctrl_Drehzahl;
                            struct_ZM_In.Modus_Position = Pos_Warten;
                            break;
        
                        case position_control:
                            struct_ZM_In.Soll_iq_A = 0;
                            struct_ZM_In.Soll_id_A = 0;
                            struct_ZM_In.Soll_Drehzahl_Umin = 0;
                            struct_ZM_In.Soll_Regelungsart = Ctrl_Position;
                            // Sicherheits-Interlock: ohne gueltige Multiturn-Referenz keine Fahrt freigeben
                            // (Modus Warten -> Positionsregler haelt, es wird keine Trajektorie gestartet)
                            if (Global_Data.av.mult_pos_valid)
                            {
                                struct_ZM_In.Modus_Position = (Modus_Position)Global_Data.rasv.Modus_Position_sel;
                            }
                            else
                            {
                                struct_ZM_In.Modus_Position = Pos_Warten;
                            }
                            struct_ZM_In.Soll_Drehzahl_Home_Grads = 3.0f;
                            struct_ZM_In.Soll_Winkel_CB_Grad = Global_Data.rasv.Soll_Winkel_grad;
                            struct_ZM_In.Soll_Drehzahl_CB_Grads = Global_Data.rasv.Soll_Geschwindigkeit_grads;
                            struct_ZM_In.Soll_Beschleunigung_CB_Grads2 = Global_Data.rasv.Soll_Beschleunigung_grads2;
                            break;

                        case manual_duty_cycle:
                            struct_ZM_In.Soll_iq_A = 0;
                            struct_ZM_In.Soll_id_A = 0;
                            struct_ZM_In.Soll_Drehzahl_Umin = 0;
                            struct_ZM_In.Modus_Position = Pos_Warten;
                            struct_ZM_In.Soll_Regelungsart = Ctrl_Manuell;
                            if(conv_status_signals.board_ready == true)
                            {
                                Global_Data.rasv.halfBridge1DutyCycle = Global_Data.rasv.Soll_HB1_DutyCycle;
                                Global_Data.rasv.halfBridge2DutyCycle = Global_Data.rasv.Soll_HB2_DutyCycle;
                                Global_Data.rasv.halfBridge3DutyCycle = Global_Data.rasv.Soll_HB3_DutyCycle;
                            }
                            break;

                        case ctrl_state_none:
                            struct_ZM_In.Soll_iq_A = 0;
                            struct_ZM_In.Soll_id_A = 0;
                            struct_ZM_In.Soll_Drehzahl_Umin = 0;
                            Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
                            Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
                            Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
                            struct_ZM_In.Modus_Position = Pos_Warten;
                            struct_ZM_In.Soll_Regelungsart = Ctrl_Warten;
                            break;

                        default:
                            struct_ZM_In.Soll_iq_A = 0;
                            struct_ZM_In.Soll_id_A = 0;
                            struct_ZM_In.Soll_Drehzahl_Umin = 0;
                            Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
                            Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
                            Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
                            struct_ZM_In.Modus_Position = Pos_Warten;
                            struct_ZM_In.Soll_Regelungsart = Ctrl_Warten;
                            break;
                        }

                        if ((Global_Data.rasv.ctrl_state != manual_duty_cycle)
                            && (Global_Data.rasv.ctrl_state != ctrl_state_none))
                        {
                            regelung.input.Bus_ZM_In_o = struct_ZM_In;
                            uz_codegen_step(&regelung);
                            if (regelung.output.Bus_Ctrl_Out_a.act_pwm == true && conv_status_signals.board_ready == true)
                            {
                                Global_Data.rasv.halfBridge1DutyCycle = regelung.output.Bus_Ctrl_Out_a.Dutycycle[0];
                                Global_Data.rasv.halfBridge2DutyCycle = regelung.output.Bus_Ctrl_Out_a.Dutycycle[1];
                                Global_Data.rasv.halfBridge3DutyCycle = regelung.output.Bus_Ctrl_Out_a.Dutycycle[2];
                            }
                        }
                    }


    		   break;
    		case error_state:
                if (Global_Data.objects.platform_state_old != error_state)
                {
                    Global_Data.objects.platform_state_old = error_state;
                    struct_ZM_In.Soll_Drehzahl_Umin = 0;
                    struct_ZM_In.Soll_id_A = 0;
                    struct_ZM_In.Soll_iq_A = 0;
                    struct_ZM_In.Fehlermeldung = true;
                    Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
                    Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
                    Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
                    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, false);
                    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
                    regelung.input.Bus_ZM_In_o = struct_ZM_In;
	                uz_codegen_step(&regelung);
                }
                else
                {
                	regelung.input.Bus_ZM_In_o = struct_ZM_In;
					uz_codegen_step(&regelung);
                }
    			break;
    		default:
    			break;
    	}
    
    conv_status_signals.pwr_en = (bool)regelung.output.Bus_Ctrl_Out_a.pwr_en;
    conv_status_signals.board_en =  (bool)regelung.output.Bus_Ctrl_Out_a.board_en;
    conv_status_signals.board_rst =  !(bool)regelung.output.Bus_Ctrl_Out_a.reset;
    // Combine the three status bits into a single read + write instead of three
    // separate read-modify-write AXI transactions (one per bit) to shorten ISR runtime.
    uint32_t output_bitmask_local = uz_axi_gpio_read_bitmask(Global_Data.objects.output_gpio);
    output_bitmask_local = conv_status_signals.pwr_en   ? (output_bitmask_local | (1U << PWR_EN_BIT))   : (output_bitmask_local & ~(1U << PWR_EN_BIT));
    output_bitmask_local = conv_status_signals.board_en  ? (output_bitmask_local | (1U << BOARD_EN_BIT))  : (output_bitmask_local & ~(1U << BOARD_EN_BIT));
    output_bitmask_local = conv_status_signals.board_rst ? (output_bitmask_local | (1U << BOARD_RST_BIT)) : (output_bitmask_local & ~(1U << BOARD_RST_BIT));
    uz_axi_gpio_write_bitmask(Global_Data.objects.output_gpio, output_bitmask_local);

    ctrl_loop_watchdog_trigger(Global_Data.objects.ctrl_loop_watchdog);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, (1.0f-Global_Data.rasv.halfBridge1DutyCycle), (1.0f-Global_Data.rasv.halfBridge2DutyCycle),(1.0f-Global_Data.rasv.halfBridge3DutyCycle));
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    JavaScope_update(&Global_Data);

    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

//==============================================================================================================================================================

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR()
{

    int Status = 0;

    // Initialize interrupt controller for the IPI -> Initialize RPU IPI
    Status = Rpu_IpiInit(INTERRUPT_ID_IPI);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI initialization failed\r\n");
        return XST_FAILURE;
    }

    // Initialize interrupt controller for the GIC
    Status = Rpu_GicInit(&GIC_instance, INTERRUPT_ID_SCUG);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable interrupt on CPU level
    Xil_ExceptionEnable();

    return Status;
}


/**
 * @brief Initialize the R5 GIC and connect/enable the PL-to-PS interrupt used by the RPU.
 *
 * @param[in,out] GIC_instance_ptr Pointer to an XScuGic instance to initialize.
 * @param[in]     DeviceId    GIC device ID (typically XPAR_SCUGIC_0_DEVICE_ID).
 *
 * @return XST_SUCCESS on success. This implementation asserts on failures.
 */
int Rpu_GicInit(XScuGic *GIC_instance_ptr, u16 DeviceId)
{
    XScuGic_Config *GIC_config;
    int status;

    // Disable all interrupts
    Xil_ExceptionDisable();

    GIC_config = XScuGic_LookupConfig(DeviceId);

    uz_assert_not_NULL(GIC_config);

    status = XScuGic_CfgInitialize(GIC_instance_ptr, GIC_config, GIC_config->CpuBaseAddress);
	uz_assert(status == XST_SUCCESS);

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, GIC_instance_ptr);

    // Clear latched active interrupt register - for UZ warm start
    uz_r5_gic_reset_active_pl_interrupts(GIC_instance_ptr);

    // Configure trigger/priority
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(GIC_instance_ptr, Interrupt_ISR_ID, 0x0, 0b11); // Trigger 0b11 = rising-edge, Trigger 0b01 = active-high

    // Connect handler
    status = XScuGic_Connect(GIC_instance_ptr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             NULL);
	uz_assert(status == XST_SUCCESS);

    // Enable only the connected interrupt
    XScuGic_Enable(GIC_instance_ptr, Interrupt_ISR_ID);

    xil_printf("RPU: Rpu_GicInit: Done\r\n");
    return XST_SUCCESS;
}


//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_IpiInit() - This function initializes RPU IPI and enables IPI interrupts
//
// @IpiInstPtr		Pointer to the IPI instance
//----------------------------------------------------
u32 Rpu_IpiInit(u16 DeviceId)
{
    XIpiPsu_Config *IPI_config;
    int status;

    // Interrupt controller configuration
    IPI_config = XIpiPsu_LookupConfig(DeviceId);
    if (IPI_config == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&IPI_instance, IPI_config, IPI_config->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: Rpu_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static void ReadAllADC()
{
    ADC_readCardALL(&Global_Data);
};




static inline bool uz_gic_is_active_id(XScuGic *Gic, u32 IntId)
{
    /* Active status is in Distributor ACTIVE banked registers */
    const u32 reg = XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_ACTIVE_OFFSET, IntId); /* ACTIVE + (IntId/32)*4 */
    const u32 bit = (u32)1U << (IntId % 32U);

    const u32 act = XScuGic_DistReadReg(Gic, reg);
    return ((act & bit) != 0U);
}


/**
 * @brief Clears stuck ACTIVE PL interrupts by writing GICC_EOIR (End Of Interrupt Register)
 * with the active interrupt ID, to enable soft restart without resetting entire system.
 *
 * Equivalent to XSCT: mwr (CpuBaseAddress + 0x10) intid
 *
 * Call during GIC init, before enabling IRQ delivery on the R5.
 *
 */
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic)
{
	// list of all PL Interrupt IDs
	const uint16_t uz_fpga_spi_ids[] = {
	    XPS_FPGA0_INT_ID,  XPS_FPGA1_INT_ID,  XPS_FPGA2_INT_ID,  XPS_FPGA3_INT_ID,
	    XPS_FPGA4_INT_ID,  XPS_FPGA5_INT_ID,  XPS_FPGA6_INT_ID,  XPS_FPGA7_INT_ID,
	    XPS_FPGA8_INT_ID,  XPS_FPGA9_INT_ID,  XPS_FPGA10_INT_ID, XPS_FPGA11_INT_ID,
	    XPS_FPGA12_INT_ID, XPS_FPGA13_INT_ID, XPS_FPGA14_INT_ID, XPS_FPGA15_INT_ID
	};

	uz_assert_not_NULL(Gic);
	uz_assert_not_NULL(Gic->Config);

    // iterate over all PL interrupts
	for (uint32_t i = 0U; i < (uint32_t)(sizeof(uz_fpga_spi_ids)/sizeof(uz_fpga_spi_ids[0])); ++i)
	{
		const uint32_t id = (uint32_t)uz_fpga_spi_ids[i];

		// check if id-interrupt is stuck on active
		if (uz_gic_is_active_id(Gic, id)) {

			/* Writing IntId to EOIR to clear the stuck ACTIVE state */
			XScuGic_CPUWriteReg(Gic, XSCUGIC_EOI_OFFSET, (id & XSCUGIC_EOI_INTID_MASK));
			uz_printf("RPU: GIC Cleared ACTIVE for PL interrupt ID %u\r\n", (unsigned long)id);

		}
    }
}



