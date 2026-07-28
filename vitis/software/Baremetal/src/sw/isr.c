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
#include "../include/deskbench_control.h"
#include "../uz/uz_global_configuration.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_pmsm_control/uz_pmsm_control.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

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
    deskbench_update_measurements(&Global_Data);

    platform_state_t current_state = ultrazohm_state_machine_get_state();

    // How to always keep everything in tristate

    switch (current_state)
    {
    case idle_state:
        /* Project Wizard BEGIN: idle_state isr_actions */
        disable_prime_mover(&Global_Data);
        disable_dut(&Global_Data);
        uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, false);
        uz_pmsm_control_enable(Global_Data.objects.dut_control, false);
        uz_pmsm_control_reset(Global_Data.objects.prime_mover_control);
        uz_pmsm_control_reset(Global_Data.objects.dut_control);

        uz_pmsmModel_reset(Global_Data.objects.dut_pmsm_model);
        uz_pmsmModel_reset(Global_Data.objects.prime_mover_pmsm_model);

        uz_pmsm_control_acknowledge_and_reset_error(Global_Data.objects.prime_mover_control, Global_Data.av.prime_mover_measurements);
        uz_pmsm_control_acknowledge_and_reset_error(Global_Data.objects.dut_control, Global_Data.av.dut_measurements);

        Global_Data.dut_manual_duty_cycle = (struct uz_DutyCycle_t){.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f};
        Global_Data.prime_mover_manual_duty_cycle = (struct uz_DutyCycle_t){.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f};
        uz_pmsm_control_set_default_duty_cycle(Global_Data.objects.dut_control, Global_Data.dut_manual_duty_cycle);
        uz_pmsm_control_set_default_duty_cycle(Global_Data.objects.prime_mover_control, Global_Data.prime_mover_manual_duty_cycle);

        /* Project Wizard END: idle_state isr_actions */
        break;

    case running_state:
        switch (Global_Data.control_mode)
        {
        case DUT_ONLY_CURRENT_CONTROL:
            enable_dut(&Global_Data);
            disable_prime_mover(&Global_Data);
            uz_pmsm_control_enable_speed_control(Global_Data.objects.dut_control, false);
            break;
        case DUT_ONLY_CURRENT_CONTROL_CIL:
            disable_dut(&Global_Data);
            disable_prime_mover(&Global_Data);
            uz_pmsmModel_simulate_mechanical_system(Global_Data.objects.dut_pmsm_model, false);
            uz_pmsmModel_reset(Global_Data.objects.dut_pmsm_model);

            break;
        case DUT_ONLY_SPEED_CONTROL:
            uz_pmsm_control_enable_speed_control(Global_Data.objects.dut_control, true);
            uz_pmsm_control_reset(Global_Data.objects.dut_control);
            enable_dut(&Global_Data);
            disable_prime_mover(&Global_Data);
            break;
        case DUT_ONLY_SPEED_CONTROL_CIL:
            uz_pmsm_control_enable_speed_control(Global_Data.objects.dut_control, true);
            uz_pmsm_control_reset(Global_Data.objects.dut_control);
            disable_dut(&Global_Data);
            disable_prime_mover(&Global_Data);
            uz_pmsmModel_simulate_mechanical_system(Global_Data.objects.dut_pmsm_model, true);
            uz_pmsmModel_reset(Global_Data.objects.dut_pmsm_model);
            break;
        case PM_ONLY_CURRENT_CONTROL:
            disable_dut(&Global_Data);
            enable_prime_mover(&Global_Data);
            uz_pmsm_control_enable_speed_control(Global_Data.objects.prime_mover_control, false);
            break;
        case PM_ONLY_CURRENT_CONTROL_CIL:
            disable_dut(&Global_Data);
            disable_prime_mover(&Global_Data);
            uz_pmsmModel_simulate_mechanical_system(Global_Data.objects.prime_mover_pmsm_model, false);
            uz_pmsmModel_reset(Global_Data.objects.prime_mover_pmsm_model);
            break;
        case PM_ONLY_SPEED_CONTROL:
            uz_pmsm_control_enable_speed_control(Global_Data.objects.prime_mover_control, true);
            uz_pmsm_control_reset(Global_Data.objects.prime_mover_control);
            disable_dut(&Global_Data);
            enable_prime_mover(&Global_Data);
            break;
        case PM_ONLY_SPEED_CONTROL_CIL:
            uz_pmsm_control_enable_speed_control(Global_Data.objects.prime_mover_control, true);
            uz_pmsm_control_reset(Global_Data.objects.prime_mover_control);
            disable_dut(&Global_Data);
            disable_prime_mover(&Global_Data);
            uz_pmsmModel_simulate_mechanical_system(Global_Data.objects.prime_mover_pmsm_model, true);
            uz_pmsmModel_reset(Global_Data.objects.prime_mover_pmsm_model);
            break;
        case PM_SPEED_DUT_CURRENT:
            uz_pmsm_control_enable_speed_control(Global_Data.objects.prime_mover_control, true);
            uz_pmsm_control_enable_speed_control(Global_Data.objects.dut_control, false);
            uz_pmsm_control_reset(Global_Data.objects.prime_mover_control);
            uz_pmsm_control_reset(Global_Data.objects.dut_control);
            enable_dut(&Global_Data);
            enable_prime_mover(&Global_Data);
            break;
        case PM_CURRENT_DUT_SPEED:
            uz_pmsm_control_enable_speed_control(Global_Data.objects.prime_mover_control, false);
            uz_pmsm_control_enable_speed_control(Global_Data.objects.dut_control, true);
            uz_pmsm_control_reset(Global_Data.objects.prime_mover_control);
            uz_pmsm_control_reset(Global_Data.objects.dut_control);
            enable_dut(&Global_Data);
            enable_prime_mover(&Global_Data);
            break;
        case PM_SPEED_DUT_CURRENT_CIL:
            uz_pmsm_control_enable_speed_control(Global_Data.objects.prime_mover_control, true);
            uz_pmsm_control_enable_speed_control(Global_Data.objects.dut_control, false);
            uz_pmsm_control_reset(Global_Data.objects.prime_mover_control);
            uz_pmsm_control_reset(Global_Data.objects.dut_control);
            disable_dut(&Global_Data);
            disable_prime_mover(&Global_Data);
            uz_pmsmModel_simulate_mechanical_system(Global_Data.objects.prime_mover_pmsm_model, true);
            uz_pmsmModel_simulate_mechanical_system(Global_Data.objects.dut_pmsm_model, false);
            uz_pmsmModel_reset(Global_Data.objects.prime_mover_pmsm_model);
            uz_pmsmModel_reset(Global_Data.objects.dut_pmsm_model);
            break;
        case PM_CURRENT_DUT_SPEED_CIL:
            uz_pmsm_control_enable_speed_control(Global_Data.objects.prime_mover_control, false);
            uz_pmsm_control_enable_speed_control(Global_Data.objects.dut_control, true);
            uz_pmsm_control_reset(Global_Data.objects.prime_mover_control);
            uz_pmsm_control_reset(Global_Data.objects.dut_control);
            disable_dut(&Global_Data);
            disable_prime_mover(&Global_Data);
            uz_pmsmModel_simulate_mechanical_system(Global_Data.objects.prime_mover_pmsm_model, false);
            uz_pmsmModel_simulate_mechanical_system(Global_Data.objects.dut_pmsm_model, true);
            uz_pmsmModel_reset(Global_Data.objects.prime_mover_pmsm_model);
            uz_pmsmModel_reset(Global_Data.objects.dut_pmsm_model);
            break;
        case PM_ONLY_DUTY_CYCLE:
            uz_pmsm_control_reset(Global_Data.objects.prime_mover_control);
            uz_pmsm_control_reset(Global_Data.objects.dut_control);
            disable_dut(&Global_Data);
            enable_prime_mover(&Global_Data);
            break;
        case DUT_ONLY_DUTY_CYCLE:
            uz_pmsm_control_reset(Global_Data.objects.prime_mover_control);
            uz_pmsm_control_reset(Global_Data.objects.dut_control);
            enable_dut(&Global_Data);
            disable_prime_mover(&Global_Data);
            break;
        default:
            uz_assert(0);
            break;
        }
        break;

    case control_state:
        switch (Global_Data.control_mode)
        {
        case DUT_ONLY_CURRENT_CONTROL:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, true);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, false);
            break;
        case DUT_ONLY_SPEED_CONTROL:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, true);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, false);
            break;
        case DUT_ONLY_CURRENT_CONTROL_CIL:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, true);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, false);
            break;
        case DUT_ONLY_SPEED_CONTROL_CIL:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, true);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, false);
            break;
        case PM_ONLY_CURRENT_CONTROL:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, false);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, true);
            break;
        case PM_ONLY_SPEED_CONTROL:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, false);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, true);
            break;
        case PM_ONLY_CURRENT_CONTROL_CIL:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, false);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, true);
            break;
        case PM_ONLY_SPEED_CONTROL_CIL:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, false);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, true);
            break;
        case PM_SPEED_DUT_CURRENT_CIL:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, true);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, true);
            break;
        case PM_CURRENT_DUT_SPEED_CIL:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, true);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, true);
            break;
        case PM_CURRENT_DUT_SPEED:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, true);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, true);
            break;
        case PM_SPEED_DUT_CURRENT:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, true);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, true);
            break;
        case PM_ONLY_DUTY_CYCLE:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, false);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, false);
            uz_pmsm_control_set_default_duty_cycle(Global_Data.objects.prime_mover_control, Global_Data.prime_mover_manual_duty_cycle);
            break;
        case DUT_ONLY_DUTY_CYCLE:
            uz_pmsm_control_enable(Global_Data.objects.dut_control, false);
            uz_pmsm_control_enable(Global_Data.objects.prime_mover_control, false);
            uz_pmsm_control_set_default_duty_cycle(Global_Data.objects.dut_control, Global_Data.dut_manual_duty_cycle);
            break;
        default:
            uz_assert(0);
            break;
        }
        break;

    case error_state:
        disable_prime_mover(&Global_Data);
        disable_dut(&Global_Data);
        break;

    default:
        break;
    }

    Global_Data.rasv.dut_duty_cycle = uz_pmsm_control_sample_duty(Global_Data.objects.dut_control, Global_Data.av.dut_measurements, Global_Data.rasv.dut_n_ref_rpm, Global_Data.rasv.dut_i_dq_ref_A, 0.0f);
    Global_Data.rasv.prime_mover_duty_cycle = uz_pmsm_control_sample_duty(Global_Data.objects.prime_mover_control, Global_Data.av.prime_mover_measurements, Global_Data.rasv.prime_mover_n_ref_rpm, Global_Data.rasv.prime_mover_i_dq_ref_A, 0.0f);

    Global_Data.av.dut_safe_operating_region_violation = uz_pmsm_control_get_safe_operating_area_violation(Global_Data.objects.dut_control);
    Global_Data.av.prime_mover_safe_operating_region_violation = uz_pmsm_control_get_safe_operating_area_violation(Global_Data.objects.prime_mover_control);

    if (Global_Data.av.dut_safe_operating_region_violation != uz_pmsm_control_no_violation || Global_Data.av.prime_mover_safe_operating_region_violation != uz_pmsm_control_no_violation)
    {
        ultrazohm_state_machine_set_error(true);
    }

    // Set outputs to PMSM IP-Core
    if ((Global_Data.control_mode == DUT_ONLY_CURRENT_CONTROL_CIL) || (Global_Data.control_mode == DUT_ONLY_SPEED_CONTROL_CIL))
    {
        struct uz_pmsmModel_inputs_t dut_model_inputs = {
            .v_d_V = Global_Data.objects.dut_reference_values->v_dq_in_V.d,
            .v_q_V = Global_Data.objects.dut_reference_values->v_dq_in_V.q,
            .omega_mech_1_s = Global_Data.rasv.dut_n_ref_rpm * (2.0f * UZ_PIf / 60.0f),
            .load_torque = 0.0f};
        uz_pmsmModel_set_inputs(Global_Data.objects.dut_pmsm_model, dut_model_inputs);
        uz_pmsmModel_trigger_input_strobe(Global_Data.objects.dut_pmsm_model);
    }

    if ((Global_Data.control_mode == PM_ONLY_CURRENT_CONTROL_CIL) || (Global_Data.control_mode == PM_ONLY_SPEED_CONTROL_CIL))
    {
        struct uz_pmsmModel_inputs_t pm_model_inputs = {
            .v_d_V = Global_Data.objects.prime_mover_reference_values->v_dq_in_V.d,
            .v_q_V = Global_Data.objects.prime_mover_reference_values->v_dq_in_V.q,
            .omega_mech_1_s = Global_Data.rasv.prime_mover_n_ref_rpm * (2.0f * UZ_PIf / 60.0f),
            .load_torque = 0.0f};
        uz_pmsmModel_set_inputs(Global_Data.objects.prime_mover_pmsm_model, pm_model_inputs);
        uz_pmsmModel_trigger_input_strobe(Global_Data.objects.prime_mover_pmsm_model);
    }

    if (Global_Data.control_mode == PM_SPEED_DUT_CURRENT_CIL)
    {
        struct uz_pmsmModel_inputs_t pm_model_inputs = {
            .v_d_V = Global_Data.objects.prime_mover_reference_values->v_dq_in_V.d,
            .v_q_V = Global_Data.objects.prime_mover_reference_values->v_dq_in_V.q,
            .omega_mech_1_s = 0.0f,
            .load_torque = -1.0f * Global_Data.av.dut_torque_Nm};
        uz_pmsmModel_set_inputs(Global_Data.objects.prime_mover_pmsm_model, pm_model_inputs);
        uz_pmsmModel_trigger_input_strobe(Global_Data.objects.prime_mover_pmsm_model);

        struct uz_pmsmModel_inputs_t dut_model_inputs = {
            .v_d_V = Global_Data.objects.dut_reference_values->v_dq_in_V.d,
            .v_q_V = Global_Data.objects.dut_reference_values->v_dq_in_V.q,
            .omega_mech_1_s = -1.0f * Global_Data.objects.prime_mover_actual_data->speed_in_rpm * (2.0f * UZ_PIf / 60.0f), // Global_Data.rasv.dut_n_ref_rpm * (2.0f * UZ_PIf / 60.0f),
            .load_torque = 0.0f};
        uz_pmsmModel_set_inputs(Global_Data.objects.dut_pmsm_model, dut_model_inputs);
        uz_pmsmModel_trigger_input_strobe(Global_Data.objects.dut_pmsm_model);
    }

    if (Global_Data.control_mode == PM_CURRENT_DUT_SPEED_CIL)
    {
        struct uz_pmsmModel_inputs_t pm_model_inputs = {
            .v_d_V = Global_Data.objects.prime_mover_reference_values->v_dq_in_V.d,
            .v_q_V = Global_Data.objects.prime_mover_reference_values->v_dq_in_V.q,
            .omega_mech_1_s = -1.0f * Global_Data.objects.dut_actual_data->speed_in_rpm * (2.0f * UZ_PIf / 60.0f),
            .load_torque = 0.0f};
        uz_pmsmModel_set_inputs(Global_Data.objects.prime_mover_pmsm_model, pm_model_inputs);
        uz_pmsmModel_trigger_input_strobe(Global_Data.objects.prime_mover_pmsm_model);

        struct uz_pmsmModel_inputs_t dut_model_inputs = {
            .v_d_V = Global_Data.objects.dut_reference_values->v_dq_in_V.d,
            .v_q_V = Global_Data.objects.dut_reference_values->v_dq_in_V.q,
            .omega_mech_1_s = 0.0f, // Global_Data.rasv.dut_n_ref_rpm * (2.0f * UZ_PIf / 60.0f),
            .load_torque = -1.0f * Global_Data.av.pm_torque_Nm};
        uz_pmsmModel_set_inputs(Global_Data.objects.dut_pmsm_model, dut_model_inputs);
        uz_pmsmModel_trigger_input_strobe(Global_Data.objects.dut_pmsm_model);
    }
    // If manual mode, use manual duty cycles instead of the control output

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
    update_inverter_adapter_d1_outputs(&Global_Data);
    /* Project Wizard END: D1 isr_control */
}

static void update_adapter_d2(void)
{
    /* Project Wizard BEGIN: D2 isr_control */
    update_inverter_adapter_d2_outputs(&Global_Data);
    /* Project Wizard END: D2 isr_control */
}

static void update_adapter_d3(void)
{
    /* Project Wizard BEGIN: D3 isr_control */
    /* Project Wizard END: D3 isr_control */
}

static void update_adapter_d4(void)
{
    /* Project Wizard BEGIN: D4 isr_control */
    // float d1_theta_m_offset_rad = LIMIT(Global_Data.av.snd_fld[5], -2.0f * UZ_PIf, 0.0f);
    // float d2_theta_m_offset_rad = LIMIT(Global_Data.av.snd_fld[6], -2.0f * UZ_PIf, 0.0f);
    // uz_resolver_pl_interface_set_theta_m_offset_rad(Global_Data.objects.resolver_pl_interface_d4_3, d1_theta_m_offset_rad);
    // uz_resolver_pl_interface_set_theta_m_offset_rad(Global_Data.objects.resolver_pl_interface_d4_1, d2_theta_m_offset_rad);

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
    Global_Data.av.incremental_encoder_d5_1_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_2_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_3_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_3);
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
