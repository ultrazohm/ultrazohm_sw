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
#include "../defines.h"
#include "../main.h"
#include "../include/ipc_ARM.h"
#include <math.h>
#include <xtmrctr.h>
#include "../include/javascope.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "../IP_Cores/uz_dataMover/uz_dataMover.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../include/pwm_init.h"
#include "../include/project_wizard_visualization.h"
#include "../include/project_wizard_io.h"

#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_signals/uz_signals.h"
#include "../include/deskbench_control.h"
#include "../uz/uz_pmsm_control/uz_pmsm_control.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

#define CURRENT_TO_AMPERE 12.5f
#define VOLTAGE_TO_VOLTS 12.0f

/* Project Wizard BEGIN: adc_readout_definitions */
static uz_array_int16_t analog_adc_data;
/* Project Wizard END: adc_readout_definitions */
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);
static void update_adapter_a1(void);
static void update_adapter_a2(void);
static void update_adapter_a3(void);
static void update_adapter_d1(void);
static void update_adapter_d2(void);
static void update_adapter_d3(void);
static void update_adapter_d4(void);
static void update_adapter_d5(void);

void update_temperatures_round_robin(void);
//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
                             /* Project Wizard BEGIN: adc_readout */
    analog_adc_data = uz_dataMover_update_buffer_and_get_data();
    /* Project Wizard END: adc_readout */
    update_adapter_a1();
    update_adapter_a2();
    update_adapter_a3();
    update_adapter_d1();
    update_adapter_d2();
    update_adapter_d3();
    update_adapter_d4();
    update_adapter_d5();
    update_temperatures_round_robin();

    // Current mapping
    Global_Data.m1_phase_voltage.a = VOLTAGE_TO_VOLTS * Global_Data.av.adc_ltc2311_a1_ch3;
    Global_Data.m1_phase_voltage.b = VOLTAGE_TO_VOLTS * Global_Data.av.adc_ltc2311_a1_ch2;
    Global_Data.m1_phase_voltage.c = VOLTAGE_TO_VOLTS * Global_Data.av.adc_ltc2311_a1_ch1;
    Global_Data.m12_dc_voltage = VOLTAGE_TO_VOLTS * Global_Data.av.adc_ltc2311_a1_ch0;

    Global_Data.m1_phase_current.a = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a1_ch7;
    Global_Data.m1_phase_current.b = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a1_ch6;
    Global_Data.m1_phase_current.c = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a1_ch5;
    Global_Data.m2_phase_current.a = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a1_ch4;

    // Global_Data.m2_phase_voltage.a = VOLTAGE_TO_VOLTS * Global_Data.av.adc_ltc2311_a2_ch3;
    // Global_Data.m2_phase_voltage.b = VOLTAGE_TO_VOLTS * Global_Data.av.adc_ltc2311_a2_ch2;
    // Global_Data.m2_phase_voltage.c = VOLTAGE_TO_VOLTS * Global_Data.av.adc_ltc2311_a2_ch1;

    Global_Data.m2_phase_current.b = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a2_ch7;
    Global_Data.m2_phase_current.c = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a2_ch6;
    Global_Data.m1_dc_current = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a2_ch5;
    Global_Data.m2_dc_current = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a2_ch4;

    Global_Data.m3_phase_voltage.a = VOLTAGE_TO_VOLTS * Global_Data.av.adc_ltc2311_a3_ch3;
    Global_Data.m3_phase_voltage.b = VOLTAGE_TO_VOLTS * Global_Data.av.adc_ltc2311_a3_ch2;
    Global_Data.m3_phase_voltage.c = VOLTAGE_TO_VOLTS * Global_Data.av.adc_ltc2311_a3_ch1;
    Global_Data.m34_dc_voltage = VOLTAGE_TO_VOLTS * Global_Data.av.adc_ltc2311_a3_ch0;

    Global_Data.m3_phase_current.a = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a3_ch7;
    Global_Data.m3_phase_current.b = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a3_ch6;
    Global_Data.m3_phase_current.c = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a3_ch5;
    Global_Data.m4_phase_current.a = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a3_ch4;

    Global_Data.m4_phase_current.b = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a2_ch3;
    Global_Data.m4_phase_current.c = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a2_ch2;
    Global_Data.m3_dc_current = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a2_ch1;
    Global_Data.m4_dc_current = CURRENT_TO_AMPERE * Global_Data.av.adc_ltc2311_a2_ch0;

    deskbench_update_measurements(&Global_Data);

    Global_Data.m1_duty_from_javascope.a = Global_Data.av.snd_fld[7];
    Global_Data.m1_duty_from_javascope.b = Global_Data.av.snd_fld[8];
    Global_Data.m1_duty_from_javascope.c = Global_Data.av.snd_fld[9];

    Global_Data.m2_duty_from_javascope.a = Global_Data.av.snd_fld[10];
    Global_Data.m2_duty_from_javascope.b = Global_Data.av.snd_fld[11];
    Global_Data.m2_duty_from_javascope.c = Global_Data.av.snd_fld[12];

    Global_Data.m3_duty_from_javascope.a = Global_Data.av.snd_fld[13];
    Global_Data.m3_duty_from_javascope.b = Global_Data.av.snd_fld[14];
    Global_Data.m3_duty_from_javascope.c = Global_Data.av.snd_fld[15];

    Global_Data.m4_duty_from_javascope.a = Global_Data.av.snd_fld[16];
    Global_Data.m4_duty_from_javascope.b = Global_Data.av.snd_fld[17];
    Global_Data.m4_duty_from_javascope.c = Global_Data.av.snd_fld[18];

    Global_Data.m1_prime_mover_n_ref_rpm = Global_Data.av.snd_fld[1];
    Global_Data.m2_dut_i_dq_ref_A.d = Global_Data.av.snd_fld[2];
    Global_Data.m2_dut_i_dq_ref_A.q = Global_Data.av.snd_fld[3];
    Global_Data.m3_prime_mover_n_ref_rpm = Global_Data.av.snd_fld[4];
    Global_Data.m4_dut_i_dq_ref_A.d = Global_Data.av.snd_fld[5];
    Global_Data.m4_dut_i_dq_ref_A.q = Global_Data.av.snd_fld[6];
    // Start Adding m2, then 3+4 and some enable logic

    uz_pmsm_control_enable_speed_control(Global_Data.objects.m1_prime_mover_control, true);
    uz_pmsm_control_enable_speed_control(Global_Data.objects.m2_dut_control, false);
    uz_pmsm_control_enable_speed_control(Global_Data.objects.m3_prime_mover_control, true);
    uz_pmsm_control_enable_speed_control(Global_Data.objects.m4_dut_control, false);

    platform_state_t current_state = ultrazohm_state_machine_get_state();
    if (current_state == idle_state)
    {
        /* Project Wizard BEGIN: idle_state isr_actions */
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, true, true, true);
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, true, true, true);
        Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_2, true, true, true);
        Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_3, true, true, true);
        Global_Data.d1_inverter_enable = false;
        Global_Data.d2_inverter_enable = false;
        Global_Data.d3_inverter_enable = false;
        Global_Data.d4_inverter_enable = false;

        uz_pmsm_control_enable(Global_Data.objects.m1_prime_mover_control, false);
        uz_pmsm_control_enable(Global_Data.objects.m2_dut_control, false);
        uz_pmsm_control_enable(Global_Data.objects.m3_prime_mover_control, false);
        uz_pmsm_control_enable(Global_Data.objects.m4_dut_control, false);

        uz_pmsm_control_acknowledge_and_reset_error(Global_Data.objects.m1_prime_mover_control, Global_Data.av.m1_measurements);
        uz_pmsm_control_acknowledge_and_reset_error(Global_Data.objects.m2_dut_control, Global_Data.av.m2_measurements);
        uz_pmsm_control_acknowledge_and_reset_error(Global_Data.objects.m3_prime_mover_control, Global_Data.av.m3_measurements);
        uz_pmsm_control_acknowledge_and_reset_error(Global_Data.objects.m4_dut_control, Global_Data.av.m4_measurements);

        /* Project Wizard END: idle_state isr_actions */
    }
    else if (current_state == running_state)
    {
        /* Project Wizard BEGIN: running_state isr_actions */
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, false, false, false);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, false, false, false);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_2, false, false, false);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_3, false, false, false);

        /* Project Wizard END: running_state isr_actions */
    }
    else if (current_state == control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
        switch (Global_Data.control_mode)
        {
        case control_mode_manual:
            Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = Global_Data.m1_duty_from_javascope.a;
            Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = Global_Data.m1_duty_from_javascope.b;
            Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = Global_Data.m1_duty_from_javascope.c;

            Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_1 = Global_Data.m2_duty_from_javascope.a;
            Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_2 = Global_Data.m2_duty_from_javascope.b;
            Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_3 = Global_Data.m2_duty_from_javascope.c;

            Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_1 = Global_Data.m3_duty_from_javascope.a;
            Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_2 = Global_Data.m3_duty_from_javascope.b;
            Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_3 = Global_Data.m3_duty_from_javascope.c;

            Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_1 = Global_Data.m4_duty_from_javascope.a;
            Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_2 = Global_Data.m4_duty_from_javascope.b;
            Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_3 = Global_Data.m4_duty_from_javascope.c;
            break;
        case control_mode_m1_only_foc:
            uz_pmsm_control_enable(Global_Data.objects.m1_prime_mover_control, true);
            uz_pmsm_control_enable(Global_Data.objects.m2_dut_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m3_prime_mover_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m4_dut_control, false);
            break;
        case control_mode_m2_only_foc:
            uz_pmsm_control_enable(Global_Data.objects.m1_prime_mover_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m2_dut_control, true);
            uz_pmsm_control_enable(Global_Data.objects.m3_prime_mover_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m4_dut_control, false);
            break;
        case control_mode_m3_only_foc:
            uz_pmsm_control_enable(Global_Data.objects.m1_prime_mover_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m2_dut_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m3_prime_mover_control, true);
            uz_pmsm_control_enable(Global_Data.objects.m4_dut_control, false);
            break;
        case control_mode_m4_only_foc:
            uz_pmsm_control_enable(Global_Data.objects.m1_prime_mover_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m2_dut_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m3_prime_mover_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m4_dut_control, true);
            break;
        case control_mode_m12_only_foc:
            uz_pmsm_control_enable(Global_Data.objects.m1_prime_mover_control, true);
            uz_pmsm_control_enable(Global_Data.objects.m2_dut_control, true);
            uz_pmsm_control_enable(Global_Data.objects.m3_prime_mover_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m4_dut_control, false);
            break;
        case control_mode_m34_only_foc:
            uz_pmsm_control_enable(Global_Data.objects.m1_prime_mover_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m2_dut_control, false);
            uz_pmsm_control_enable(Global_Data.objects.m3_prime_mover_control, true);
            uz_pmsm_control_enable(Global_Data.objects.m4_dut_control, true);
            break;
        case control_mode_m1234_foc:
            uz_pmsm_control_enable(Global_Data.objects.m1_prime_mover_control, true);
            uz_pmsm_control_enable(Global_Data.objects.m2_dut_control, true);
            uz_pmsm_control_enable(Global_Data.objects.m3_prime_mover_control, true);
            uz_pmsm_control_enable(Global_Data.objects.m4_dut_control, true);
            break;

        default:
            break;
        }
        /* Project Wizard BEGIN: control_state isr_actions */
        /* Project Wizard END: control_state isr_actions */
    }
    else if (current_state == error_state)
    {
        /* Project Wizard BEGIN: error_state isr_actions */
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, true, true, true);
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, true, true, true);
        Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_2, true, true, true);
        Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_3, true, true, true);
        /* Project Wizard END: error_state isr_actions */
    }

    struct uz_DutyCycle_t m1_duty_cycle = uz_pmsm_control_sample_duty(Global_Data.objects.m1_prime_mover_control, Global_Data.av.m1_measurements, Global_Data.m1_prime_mover_n_ref_rpm, Global_Data.m1_prime_mover_i_dq_ref_A, 0.0f);
    struct uz_DutyCycle_t m2_duty_cycle = uz_pmsm_control_sample_duty(Global_Data.objects.m2_dut_control, Global_Data.av.m2_measurements, 0.0f, Global_Data.m2_dut_i_dq_ref_A, 0.0f);
    struct uz_DutyCycle_t m3_duty_cycle = uz_pmsm_control_sample_duty(Global_Data.objects.m3_prime_mover_control, Global_Data.av.m3_measurements, Global_Data.m3_prime_mover_n_ref_rpm, Global_Data.m3_prime_mover_i_dq_ref_A, 0.0f);
    struct uz_DutyCycle_t m4_duty_cycle = uz_pmsm_control_sample_duty(Global_Data.objects.m4_dut_control, Global_Data.av.m4_measurements, 0.0f, Global_Data.m4_dut_i_dq_ref_A, 0.0f);

    if (Global_Data.control_mode != control_mode_manual){

        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = m1_duty_cycle.DutyCycle_A;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = m1_duty_cycle.DutyCycle_B;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = m1_duty_cycle.DutyCycle_C;
        
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_1 = m2_duty_cycle.DutyCycle_A;
    Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_2 = m2_duty_cycle.DutyCycle_B;
    Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_3 = m2_duty_cycle.DutyCycle_C;

    Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_1 = m3_duty_cycle.DutyCycle_A;
    Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_2 = m3_duty_cycle.DutyCycle_B;
    Global_Data.rasv.pwm_2L_2_halfBridgeDutyCycle_3 = m3_duty_cycle.DutyCycle_C;

    Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_1 = m4_duty_cycle.DutyCycle_A;
    Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_2 = m4_duty_cycle.DutyCycle_B;
    Global_Data.rasv.pwm_2L_3_halfBridgeDutyCycle_3 = m4_duty_cycle.DutyCycle_C;
}

    Global_Data.av.m1_safe_operating_region_violation = uz_pmsm_control_get_safe_operating_area_violation(Global_Data.objects.m1_prime_mover_control);
    Global_Data.av.m2_safe_operating_region_violation = uz_pmsm_control_get_safe_operating_area_violation(Global_Data.objects.m2_dut_control);
    Global_Data.av.m3_safe_operating_region_violation = uz_pmsm_control_get_safe_operating_area_violation(Global_Data.objects.m3_prime_mover_control);
    Global_Data.av.m4_safe_operating_region_violation = uz_pmsm_control_get_safe_operating_area_violation(Global_Data.objects.m4_dut_control);
    if (Global_Data.av.m1_safe_operating_region_violation || Global_Data.av.m2_safe_operating_region_violation || Global_Data.av.m3_safe_operating_region_violation || Global_Data.av.m4_safe_operating_region_violation)
    {
        ultrazohm_state_machine_set_error(true);
    }

    /* Project Wizard BEGIN: pwm_runtime */
    project_wizard_update_pwm_outputs(&Global_Data);
    /* Project Wizard END: pwm_runtime */

    project_wizard_visualization_update(&Global_Data);
    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

static void update_adapter_a1(void)
{
    /* Project Wizard BEGIN: A1 isr_control */
    Global_Data.av.adc_ltc2311_a1_ch0 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[0], 0U);
    Global_Data.av.adc_ltc2311_a1_ch1 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[1], 1U);
    Global_Data.av.adc_ltc2311_a1_ch2 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[2], 2U);
    Global_Data.av.adc_ltc2311_a1_ch3 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[3], 3U);
    Global_Data.av.adc_ltc2311_a1_ch4 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[4], 4U);
    Global_Data.av.adc_ltc2311_a1_ch5 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[5], 5U);
    Global_Data.av.adc_ltc2311_a1_ch6 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[6], 6U);
    Global_Data.av.adc_ltc2311_a1_ch7 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[7], 7U);
    /* Project Wizard END: A1 isr_control */
}

static void update_adapter_a2(void)
{
    /* Project Wizard BEGIN: A2 isr_control */
    Global_Data.av.adc_ltc2311_a2_ch0 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[8], 0U);
    Global_Data.av.adc_ltc2311_a2_ch1 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[9], 1U);
    Global_Data.av.adc_ltc2311_a2_ch2 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[10], 2U);
    Global_Data.av.adc_ltc2311_a2_ch3 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[11], 3U);
    Global_Data.av.adc_ltc2311_a2_ch4 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[12], 4U);
    Global_Data.av.adc_ltc2311_a2_ch5 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[13], 5U);
    Global_Data.av.adc_ltc2311_a2_ch6 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[14], 6U);
    Global_Data.av.adc_ltc2311_a2_ch7 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[15], 7U);
    /* Project Wizard END: A2 isr_control */
}

static void update_adapter_a3(void)
{
    /* Project Wizard BEGIN: A3 isr_control */
    Global_Data.av.adc_ltc2311_a3_ch0 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[16], 0U);
    Global_Data.av.adc_ltc2311_a3_ch1 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[17], 1U);
    Global_Data.av.adc_ltc2311_a3_ch2 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[18], 2U);
    Global_Data.av.adc_ltc2311_a3_ch3 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[19], 3U);
    Global_Data.av.adc_ltc2311_a3_ch4 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[20], 4U);
    Global_Data.av.adc_ltc2311_a3_ch5 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[21], 5U);
    Global_Data.av.adc_ltc2311_a3_ch6 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[22], 6U);
    Global_Data.av.adc_ltc2311_a3_ch7 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[23], 7U);
    /* Project Wizard END: A3 isr_control */
}

static void update_adapter_d1(void)
{
    /* Project Wizard BEGIN: D1 isr_control */
    Global_Data.av.io_card_d1_state = uz_axi_gpio_read_bitmask(Global_Data.objects.axi_gpio_d1);
    uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, 3U, Global_Data.d1_inverter_enable);
    uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, 10U, Global_Data.d2_inverter_enable);
    uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, 17U, Global_Data.d3_inverter_enable);
    uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, 24U, Global_Data.d4_inverter_enable);
    /* Project Wizard END: D1 isr_control */
}

static void update_adapter_d2(void)
{
    /* Project Wizard BEGIN: D2 isr_control */
    Global_Data.av.io_card_d2_state = uz_axi_gpio_read_bitmask(Global_Data.objects.axi_gpio_d2);
    /* Project Wizard END: D2 isr_control */
}

static void update_adapter_d3(void)
{
    /* Project Wizard BEGIN: D3 isr_control */
    Global_Data.av.io_card_d3_state = uz_axi_gpio_read_bitmask(Global_Data.objects.axi_gpio_d3);
    /* Project Wizard END: D3 isr_control */
}

static void update_adapter_d4(void)
{
    /* Project Wizard BEGIN: D4 isr_control */
    struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d4_1_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d4_1);
    Global_Data.av.resolver_pl_interface_d4_1_revolution_counter = resolver_pl_interface_d4_1_outputs.revolution_counter;
    Global_Data.av.resolver_pl_interface_d4_1_position_mech_2pi = resolver_pl_interface_d4_1_outputs.position_mech_2pi;
    Global_Data.av.resolver_pl_interface_d4_1_position_el_2pi = resolver_pl_interface_d4_1_outputs.position_el_2pi;
    Global_Data.av.resolver_pl_interface_d4_1_omega_mech_rad_s = resolver_pl_interface_d4_1_outputs.omega_mech_rad_s;
    Global_Data.av.resolver_pl_interface_d4_1_n_mech_rpm = resolver_pl_interface_d4_1_outputs.n_mech_rpm;
    Global_Data.av.resolver_pl_interface_d4_1_omega_el_rad_s = resolver_pl_interface_d4_1_outputs.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_d4_1);
    struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d4_2_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d4_2);
    Global_Data.av.resolver_pl_interface_d4_2_revolution_counter = resolver_pl_interface_d4_2_outputs.revolution_counter;
    Global_Data.av.resolver_pl_interface_d4_2_position_mech_2pi = resolver_pl_interface_d4_2_outputs.position_mech_2pi;
    Global_Data.av.resolver_pl_interface_d4_2_position_el_2pi = resolver_pl_interface_d4_2_outputs.position_el_2pi;
    Global_Data.av.resolver_pl_interface_d4_2_omega_mech_rad_s = resolver_pl_interface_d4_2_outputs.omega_mech_rad_s;
    Global_Data.av.resolver_pl_interface_d4_2_n_mech_rpm = resolver_pl_interface_d4_2_outputs.n_mech_rpm;
    Global_Data.av.resolver_pl_interface_d4_2_omega_el_rad_s = resolver_pl_interface_d4_2_outputs.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_d4_2);
    struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d4_3_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d4_3);
    Global_Data.av.resolver_pl_interface_d4_3_revolution_counter = resolver_pl_interface_d4_3_outputs.revolution_counter;
    Global_Data.av.resolver_pl_interface_d4_3_position_mech_2pi = resolver_pl_interface_d4_3_outputs.position_mech_2pi;
    Global_Data.av.resolver_pl_interface_d4_3_position_el_2pi = resolver_pl_interface_d4_3_outputs.position_el_2pi;
    Global_Data.av.resolver_pl_interface_d4_3_omega_mech_rad_s = resolver_pl_interface_d4_3_outputs.omega_mech_rad_s;
    Global_Data.av.resolver_pl_interface_d4_3_n_mech_rpm = resolver_pl_interface_d4_3_outputs.n_mech_rpm;
    Global_Data.av.resolver_pl_interface_d4_3_omega_el_rad_s = resolver_pl_interface_d4_3_outputs.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_d4_3);
    /* Project Wizard END: D4 isr_control */
}

static void update_adapter_d5(void)
{
    /* Project Wizard BEGIN: D5 isr_control */
    struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d5_1_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d5_1);
    Global_Data.av.resolver_pl_interface_d5_1_revolution_counter = resolver_pl_interface_d5_1_outputs.revolution_counter;
    Global_Data.av.resolver_pl_interface_d5_1_position_mech_2pi = resolver_pl_interface_d5_1_outputs.position_mech_2pi;
    Global_Data.av.resolver_pl_interface_d5_1_position_el_2pi = resolver_pl_interface_d5_1_outputs.position_el_2pi;
    Global_Data.av.resolver_pl_interface_d5_1_omega_mech_rad_s = resolver_pl_interface_d5_1_outputs.omega_mech_rad_s;
    Global_Data.av.resolver_pl_interface_d5_1_n_mech_rpm = resolver_pl_interface_d5_1_outputs.n_mech_rpm;
    Global_Data.av.resolver_pl_interface_d5_1_omega_el_rad_s = resolver_pl_interface_d5_1_outputs.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_d5_1);
    struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d5_2_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d5_2);
    Global_Data.av.resolver_pl_interface_d5_2_revolution_counter = resolver_pl_interface_d5_2_outputs.revolution_counter;
    Global_Data.av.resolver_pl_interface_d5_2_position_mech_2pi = resolver_pl_interface_d5_2_outputs.position_mech_2pi;
    Global_Data.av.resolver_pl_interface_d5_2_position_el_2pi = resolver_pl_interface_d5_2_outputs.position_el_2pi;
    Global_Data.av.resolver_pl_interface_d5_2_omega_mech_rad_s = resolver_pl_interface_d5_2_outputs.omega_mech_rad_s;
    Global_Data.av.resolver_pl_interface_d5_2_n_mech_rpm = resolver_pl_interface_d5_2_outputs.n_mech_rpm;
    Global_Data.av.resolver_pl_interface_d5_2_omega_el_rad_s = resolver_pl_interface_d5_2_outputs.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_d5_2);
    /* Project Wizard END: D5 isr_control */
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
        XPS_FPGA0_INT_ID, XPS_FPGA1_INT_ID, XPS_FPGA2_INT_ID, XPS_FPGA3_INT_ID,
        XPS_FPGA4_INT_ID, XPS_FPGA5_INT_ID, XPS_FPGA6_INT_ID, XPS_FPGA7_INT_ID,
        XPS_FPGA8_INT_ID, XPS_FPGA9_INT_ID, XPS_FPGA10_INT_ID, XPS_FPGA11_INT_ID,
        XPS_FPGA12_INT_ID, XPS_FPGA13_INT_ID, XPS_FPGA14_INT_ID, XPS_FPGA15_INT_ID};

    uz_assert_not_NULL(Gic);
    uz_assert_not_NULL(Gic->Config);

    // iterate over all PL interrupts
    for (uint32_t i = 0U; i < (uint32_t)(sizeof(uz_fpga_spi_ids) / sizeof(uz_fpga_spi_ids[0])); ++i)
    {
        const uint32_t id = (uint32_t)uz_fpga_spi_ids[i];

        // check if id-interrupt is stuck on active
        if (uz_gic_is_active_id(Gic, id))
        {

            /* Writing IntId to EOIR to clear the stuck ACTIVE state */
            XScuGic_CPUWriteReg(Gic, XSCUGIC_EOI_OFFSET, (id & XSCUGIC_EOI_INTID_MASK));
            uz_printf("RPU: GIC Cleared ACTIVE for PL interrupt ID %u\r\n", (unsigned long)id);
        }
    }
}

void update_temperatures_round_robin(void)
{
    static uint32_t temp_counter = 0U;
    linear_interpolation_parameters_t linear_interpolation_params = {
        .a = -289.01f,
        .b = 218.72f};
        
    switch (temp_counter)
    {
    case 0U:
        Global_Data.av.temp_m1_h1 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m1_h1),
                linear_interpolation_params);
        break;

    case 1U:
        Global_Data.av.temp_m1_h2 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m1_h2),
                linear_interpolation_params);
        break;

    case 2U:
        Global_Data.av.temp_m1_h3 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m1_h3),
                linear_interpolation_params);
        break;

    case 3U:
        Global_Data.av.temp_m2_h1 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m2_h1),
                linear_interpolation_params);
        break;

    case 4U:
        Global_Data.av.temp_m2_h2 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m2_h2),
                linear_interpolation_params);
        break;

    case 5U:
        Global_Data.av.temp_m2_h3 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m2_h3),
                linear_interpolation_params);
        break;

    case 6U:
        Global_Data.av.temp_m3_h1 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m3_h1),
                linear_interpolation_params);
        break;

    case 7U:
        Global_Data.av.temp_m3_h2 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m3_h2),
                linear_interpolation_params);
        break;

    case 8U:
        Global_Data.av.temp_m3_h3 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m3_h3),
                linear_interpolation_params);
        break;

    case 9U:
        Global_Data.av.temp_m4_h1 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m4_h1),
                linear_interpolation_params);
        break;

    case 10U:
        Global_Data.av.temp_m4_h2 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m4_h2),
                linear_interpolation_params);
        break;

    case 11U:
        Global_Data.av.temp_m4_h3 =
            uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(
                uz_PWM_duty_freq_detection_get_duty_cycle_normalized(
                    Global_Data.objects.temp_m4_h3),
                linear_interpolation_params);
        break;

    default:
        /* Defensive reset in case temp_counter becomes invalid. */
        temp_counter = 0U;
        return;
    }

    temp_counter++;

    if (temp_counter >= 12U)
    {
        temp_counter = 0U;
    }
}