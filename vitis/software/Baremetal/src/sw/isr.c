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
#include "../include/pwm_3L_driver.h"
#include "../include/adc.h"
#include "../include/encoder.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../IP_Cores/uz_mlp_three_layer/uz_mlp_three_layer.h"
#include "../uz/uz_pmsm_control/uz_pmsm_control.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

float theta_el_offset_hoerner = 1.63f; // 5.85f
struct uz_DutyCycle_t duty_cycle_hoerner = {0};

// =============== Declares for PMSM 2 =============== //

// FOC Instances and Configs
extern struct uz_PMSM_t config_PMSM_beckhoff;
float theta_el_offset_2 = 1.4f;

uint64_t old_uptime = 0U;
float id_setpoints[22] = {
#include "id_setpoints.csv"
};

float iq_setpoints[22] = {
#include "iq_setpoints.csv"
};

float speed_setpoints[8] = {-100, -200, -300, -500, -600, -700, -900, -1000};

extern float PMSM_rated_current_hoerner;
extern bool select_misalignment;

extern uz_3ph_dq_t i_dq_ref_java_Amps_hoerner;

uint32_t Fehlerfall = 0U;

// DDPG Stuff
extern bool select_DDPG;
extern bool select_FOC;
float observation_ip[9U] = {0};
#define NUMBER_OF_INPUTS_7N 7U
#define NUMBER_OF_INPUTS_9N 9U
uz_matrix_t *matrix_output;
uz_3ph_dq_t i_dq_integrated_error_Amps_hoerner = {0};
uz_3ph_dq_t i_dq_error_Amps_hoerner = {0};
float ts = 1.0f / UZ_PWM_FREQUENCY;
float speed_weight_hoerner = 1.0f / 1500.0f;
uz_3ph_dq_t v_dq_non_limited_Volts_hoerner = {0};
uz_3ph_dq_t v_dq_limited_Volts_hoerner = {0};
uz_3ph_dq_t v_dq_limited_Volts_old_old_hoerner = {0};
float U_max_hoerner = 48.0f / 1.732050808f;
float Voltage_Scaling_hoerner = 1.0f / (48.0f / 1.732050808f);
bool ext_clamping_hoerner = false;
float max_modulation_index_hoerner = 1.0f / 1.732050808f;
float theta_el_old_hoerner = 0.0f;

#define PROFILE_SETPOINT_DURATION_IN_ISR_TICKS 5000U // 11290U

// 3 layer MLP
#if ((NN_9_INPUT_3_64) || (NN_7_INPUT_3_64))
extern float mlp_ip_output[2U];
extern uz_matrix_t *p_output_data;
extern uz_mlp_three_layer_ip_t *mlp_ip_instance;
#endif

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
static void check_inverter_errors(void);
static void ddpg(void);
void automatic_profile(void);
void all_measurements(void);

struct uz_pmsm_measurement_values d1_measurements = {0};
struct uz_pmsm_measurement_values d2_measurements = {0};
const int machine_on_d1 = D1_MACHINE; //EBM, Brose, Hoerner
const int machine_on_d2 = D2_MACHINE; // HEIDRIVE, BUEHLER, BECKHOFF

bool enable_d1_controller = false;
bool enable_d2_controller = false;
float d1_reference_speed_in_rpm = 0.0f;
float d2_reference_speed_in_rpm = 0.0f;
uz_3ph_dq_t d1_reference_currents_in_A = {0.0f};
uz_3ph_dq_t d2_reference_currents_in_A = {0.0f};
bool manual_dutycycle_d2 = false;
bool manual_dutycycle_d1 = false;
bool reference_source_javascope = true;

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    all_measurements();
    check_inverter_errors();
    Global_Data.av.Resolver_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4);
    automatic_profile();

    if (reference_source_javascope)
    {
        Global_Data.prime_mover_reference_speed_in_rpm = Global_Data.javascope.prime_mover_reference_speed_in_rpm;
        Global_Data.dut_reference_currents_in_A.d = Global_Data.javascope.dut_reference_currents_in_A.d;
        Global_Data.dut_reference_currents_in_A.q = Global_Data.javascope.dut_reference_currents_in_A.q;
    }
    else
    {
        Global_Data.prime_mover_reference_speed_in_rpm = Global_Data.profile.prime_mover_reference_speed_in_rpm;
        Global_Data.dut_reference_currents_in_A.d = Global_Data.profile.dut_reference_currents_in_A.d;
        Global_Data.dut_reference_currents_in_A.q = Global_Data.profile.dut_reference_currents_in_A.q;
    }

    if (select_misalignment == true)
    {
        // theta_el_rad_hoerner += 5.0f * (M_PI / 180.0f);
    }

    platform_state_t current_state = ultrazohm_state_machine_get_state();
    if (current_state == running_state || current_state == control_state)
    {
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
    }
    else
    {
        uz_pmsm_controller_acknowledge_and_reset_error(Global_Data.objects.d1_controller, d1_measurements);
        uz_pmsm_controller_acknowledge_and_reset_error(Global_Data.objects.d2_controller, d2_measurements);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1, true, true, true);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d2, true, true, true);
    }
//
    if (current_state == control_state)
    {
        enable_d1_controller = true;
        enable_d2_controller = true;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1, false, false, false);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d2, false, false, false);
    }
    else
    {
        enable_d1_controller = false;
        enable_d2_controller = false;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1, true, true, true);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d2, true, true, true);
    }
    uz_pmsm_controller_enable(Global_Data.objects.d1_controller, enable_d1_controller);
    uz_pmsm_controller_enable(Global_Data.objects.d2_controller, enable_d2_controller);

    if (D1_IS_PRIME_MOVER)
    {
        d1_reference_currents_in_A.d = 0.0f;
        d1_reference_currents_in_A.q = 0.0f;
        d1_reference_speed_in_rpm = Global_Data.prime_mover_reference_speed_in_rpm;
        d2_reference_currents_in_A.d = Global_Data.dut_reference_currents_in_A.d;
        d2_reference_currents_in_A.q = Global_Data.dut_reference_currents_in_A.q;
        d2_reference_speed_in_rpm = 0.0f;
    }
    else
    {
        d1_reference_currents_in_A.d = Global_Data.dut_reference_currents_in_A.d;
        d1_reference_currents_in_A.q = Global_Data.dut_reference_currents_in_A.q;
        d1_reference_speed_in_rpm = 0.0f;
        d2_reference_currents_in_A.d = 0.0f;
        d2_reference_currents_in_A.q = 0.0f;
        d2_reference_speed_in_rpm = Global_Data.prime_mover_reference_speed_in_rpm;
    }

    struct uz_DutyCycle_t duty_d1 = uz_pmsm_controller_sample(Global_Data.objects.d1_controller, d1_measurements, d1_reference_speed_in_rpm, d1_reference_currents_in_A, 0.0f);
    struct uz_DutyCycle_t duty_d2 = uz_pmsm_controller_sample(Global_Data.objects.d2_controller, d2_measurements, d2_reference_speed_in_rpm, d2_reference_currents_in_A, 0.0f);

    if (!manual_dutycycle_d2)
    {
        Global_Data.rasv.halfBridge4DutyCycle = duty_d2.DutyCycle_A;
        Global_Data.rasv.halfBridge5DutyCycle = duty_d2.DutyCycle_B;
        Global_Data.rasv.halfBridge6DutyCycle = duty_d2.DutyCycle_C;
    }
    if (!manual_dutycycle_d1)
    {
        Global_Data.rasv.halfBridge1DutyCycle = duty_d1.DutyCycle_A;
        Global_Data.rasv.halfBridge2DutyCycle = duty_d1.DutyCycle_B;
        Global_Data.rasv.halfBridge3DutyCycle = duty_d1.DutyCycle_C;
    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d2, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    JavaScope_update(&Global_Data);

    // Reset DDPG
    // ext_clamping_hoerner = false;
    // i_dq_integrated_error_Amps_hoerner.d = 0.0f;
    // i_dq_integrated_error_Amps_hoerner.q = 0.0f;

    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

void all_measurements(void)
{
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5_1(&Global_Data);
    update_speed_and_position_of_encoder_on_D5_2(&Global_Data);
    update_speed_and_position_of_encoder_on_D5_3(&Global_Data);

    Global_Data.av.mechanicalRotorSpeed_filtered_prime_mover = uz_signals_IIR_Filter_sample(Global_Data.objects.tracking_error_filter_prime_mover, Global_Data.prime_mover.actual_data->speed_in_rpm);

    d2_measurements.i_dc_from_adc_ampere_per_volt = Global_Data.aa.A2.me.ADC_B5;
    d2_measurements.v_dc_from_adc_volt_per_volt = 48.0f / 12.0f;
    d2_measurements.phase_currents_from_adc_ampere_per_volt.a = Global_Data.aa.A2.me.ADC_A4;
    d2_measurements.phase_currents_from_adc_ampere_per_volt.b = Global_Data.aa.A2.me.ADC_A3;
    d2_measurements.phase_currents_from_adc_ampere_per_volt.c = Global_Data.aa.A2.me.ADC_A2;

    switch (machine_on_d2)
    {
    case BECKHOFF:
        d2_measurements.omega_mech_rad_per_sec = Global_Data.av.Resolver_outputs.omega_mech_rad_s;
        d2_measurements.theta_mech = Global_Data.av.Resolver_outputs.position_el_2pi;
        break;
    case BUEHLER:
        d2_measurements.omega_mech_rad_per_sec = Global_Data.av.d5_3_omega_mech_rad_per_sec;
        d2_measurements.theta_mech = Global_Data.av.d5_3_theta_el;
        break;
    case HEIDRIVE:
        d2_measurements.omega_mech_rad_per_sec = Global_Data.av.d5_2_omega_mech_rad_per_sec;
        d2_measurements.theta_mech = Global_Data.av.d5_2_theta_el;
        break;
    default:
        uz_assert(0);
        break;
    }

    d1_measurements.i_dc_from_adc_ampere_per_volt = Global_Data.aa.A1.me.ADC_B5;
    d1_measurements.v_dc_from_adc_volt_per_volt = 48.0f / 12.0f;
    d1_measurements.phase_currents_from_adc_ampere_per_volt.a = Global_Data.aa.A1.me.ADC_A4;
    d1_measurements.phase_currents_from_adc_ampere_per_volt.b = Global_Data.aa.A1.me.ADC_A3;
    d1_measurements.phase_currents_from_adc_ampere_per_volt.c = Global_Data.aa.A1.me.ADC_A2;
    d1_measurements.omega_mech_rad_per_sec = Global_Data.av.d5_1_omega_mech_rad_per_sec;
    d1_measurements.theta_mech = Global_Data.av.d5_1_theta_el;



    Global_Data.M_meas_Nm = Global_Data.aa.A3.me.ADC_A4 * 2.0f; // - 0.02f;
}

void automatic_profile(void)
{
    if ((Global_Data.javascope.select_automatic_idiq))
    {
        Global_Data.profile.prime_mover_reference_speed_in_rpm = speed_setpoints[Global_Data.profile.n_ref_setpoint_index];
        Global_Data.profile.speed_tracking_error = fabsf(Global_Data.profile.prime_mover_reference_speed_in_rpm - Global_Data.av.mechanicalRotorSpeed_filtered_prime_mover);

        if (Global_Data.profile.speed_tracking_error < 1.0f && Global_Data.profile.wait_for_n_ref)
        {
            Global_Data.profile.speed_setpoint_reached = true;
            Global_Data.profile.wait_for_n_ref = false;
        }

        bool theta_dut_zero_crossing = (Global_Data.profile.theta_mech_dut_old - Global_Data.dut.measurement_values->theta_mech);
        if (((theta_dut_zero_crossing > UZ_PIf) || (Global_Data.prime_mover.actual_data->speed_in_rpm < 10.0f)) && (!Global_Data.profile.start_angle_found) && (Global_Data.profile.speed_setpoint_reached))
        {
            Global_Data.profile.start_angle_found = true;
            Global_Data.javascope.start_marker = 1.0f;
            Global_Data.profile.speed_setpoint_reached = false;
        }
        if (Global_Data.profile.start_angle_found)
        {
            Global_Data.profile.dut_reference_currents_in_A.d = id_setpoints[Global_Data.profile.setpoint_index];
            Global_Data.profile.dut_reference_currents_in_A.q = iq_setpoints[Global_Data.profile.setpoint_index] * PMSM_rated_current_hoerner;

            // step throught the array
            uint64_t current_uptime = uz_SystemTime_GetInterruptCounter();
            if ((current_uptime > (old_uptime + PROFILE_SETPOINT_DURATION_IN_ISR_TICKS) && (!Global_Data.profile.change_speed)))
            {
                old_uptime = current_uptime;

                if (Global_Data.profile.setpoint_index < 21)
                {
                    Global_Data.profile.setpoint_index++;
                }
                else
                {
                    Global_Data.profile.setpoint_index = 0U;
                    Global_Data.profile.change_speed = true;
                }
            }
            if (Global_Data.profile.change_speed)
            {
                if (current_uptime > (old_uptime + PROFILE_SETPOINT_DURATION_IN_ISR_TICKS))
                {
                    Global_Data.javascope.start_marker = 0.0f;
                    Global_Data.profile.start_angle_found = false;
                    Global_Data.profile.wait_for_n_ref = true;
                    Global_Data.profile.change_speed = false;
                    if (Global_Data.profile.n_ref_setpoint_index < 7U)
                    {
                        Global_Data.profile.n_ref_setpoint_index++;
                    }
                    else
                    {
                        // stop
                        Global_Data.javascope.select_automatic_idiq = false;
                        Global_Data.profile.n_ref_setpoint_index = 0U;
                    }
                    Global_Data.profile.prime_mover_reference_speed_in_rpm = speed_setpoints[Global_Data.profile.n_ref_setpoint_index];
                }
            }
        }
    }
    Global_Data.profile.theta_mech_dut_old = Global_Data.dut.measurement_values->theta_mech;
}

void check_inverter_errors(void)
{
    // Inverter 1 safety
    // Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    // Overtemperature for H1
    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);
    Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 1U;
    }
    // Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L1)
    {
        // ultrazohm_state_machine_set_error(true);
        Fehlerfall = 2U;
    }
    // Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 3U;
    }
    // Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 4U;
    }
    // Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H3)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 5U;
    }
    // Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L3)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 6U;
    }
    // Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    // Binding of the signals to the driver is slightly unintuitive
    // Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d1.OC_L1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 7U;
    }
    // Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d1.OC_H1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 8U;
    }
    // Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d1.OC_L2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 9U;
    }
    // Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d1.OC_H2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 10U;
    }

    // Inverter 2 safety
    // Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    // Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 11U;
    }
    // Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L1)
    {
        // ultrazohm_state_machine_set_error(true);
        Fehlerfall = 12U;
    }
    // Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 13U;
    }
    // Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 14U;
    }
    // Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H3)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 15U;
    }
    // Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L3)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 16U;
    }
    // Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    // Binding of the signals to the driver is slightly unintuitive
    // Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d2.OC_L1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 17U;
    }
    // Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d2.OC_H1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 18U;
    }
    // Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d2.OC_L2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 19U;
    }
    // Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d2.OC_H2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 20U;
    }
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
    Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable uz_mux_axi for triggering the ADCs and the ISR
    //    uz_mux_axi_hw_enable_IP_core(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR);
    //    uz_mux_axi_hw_set_mux(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
    //    uz_mux_axi_hw_set_n_th_interrupt(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
    // uz_mux_axi_enable(Global_Data.objects.mux_axi);

    return Status;
}

void ddpg()
{

    //        if (ext_clamping_hoerner == false)
    //        {
    //            i_dq_integrated_error_Amps_hoerner.d = (i_dq_integrated_error_Amps_hoerner.d + (i_dq_error_Amps_hoerner.d * ts)); // use Forward-Euler with error of previous timestep for integration
    //            i_dq_integrated_error_Amps_hoerner.q = (i_dq_integrated_error_Amps_hoerner.q + (i_dq_error_Amps_hoerner.q * ts));
    //        }
    //        else
    //        {
    //            i_dq_integrated_error_Amps_hoerner.d += 0.0f;
    //            i_dq_integrated_error_Amps_hoerner.q += 0.0f;
    //        }
    //        i_dq_error_Amps_hoerner.d = (i_dq_ref_Amps_hoerner.d - i_dq_Amps_hoerner.d) / PMSM_rated_current_hoerner;
    //        i_dq_error_Amps_hoerner.q = (i_dq_ref_Amps_hoerner.q - i_dq_Amps_hoerner.q) / PMSM_rated_current_hoerner;
    //
    // #if ((NN_9_INPUT_1_64) || (NN_9_INPUT_3_64)) == 1
    //
    //        observation_ip[0] = i_dq_error_Amps_hoerner.d;
    //        observation_ip[1] = i_dq_integrated_error_Amps_hoerner.d * UZ_PWM_FREQUENCY;
    //        observation_ip[2] = i_dq_error_Amps_hoerner.q;
    //        observation_ip[3] = i_dq_integrated_error_Amps_hoerner.q * UZ_PWM_FREQUENCY;
    //        observation_ip[4] = i_dq_Amps_hoerner.d / PMSM_rated_current_hoerner;
    //        observation_ip[5] = i_dq_Amps_hoerner.q / PMSM_rated_current_hoerner;
    //        observation_ip[6] = -1.0f * n_ref_rpm_beckhoff * speed_weight_hoerner; // Global_Data.av.mechanicalRotorSpeed_filtered_hoerner * speed_weight_hoerner;
    //        observation_ip[7] = v_dq_limited_Volts_old_old_hoerner.d * Voltage_Scaling_hoerner;
    //        observation_ip[8] = v_dq_limited_Volts_old_old_hoerner.q * Voltage_Scaling_hoerner;
    //        for (uint32_t i = 0; i < NUMBER_OF_INPUTS_9N; i++)
    //        {
    //            uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input, observation_ip[i], 0U, i);
    //        }
    // #elif NN_7_INPUT_1_64 == 1
    //        observation_ip[0] = i_dq_error_Amps_hoerner.d;
    //        observation_ip[1] = v_dq_limited_Volts_old_old_hoerner.d * Voltage_Scaling_hoerner;
    //        observation_ip[2] = i_dq_error_Amps_hoerner.q;
    //        observation_ip[3] = v_dq_limited_Volts_old_old_hoerner.q * Voltage_Scaling_hoerner;
    //        observation_ip[4] = i_dq_Amps_hoerner.d / PMSM_rated_current_hoerner;
    //        observation_ip[5] = i_dq_Amps_hoerner.q / PMSM_rated_current_hoerner;
    //        observation_ip[6] = Global_Data.av.mechanicalRotorSpeed_filtered_hoerner * speed_weight_hoerner;
    //        for (uint32_t i = 0; i < NUMBER_OF_INPUTS_7N; i++)
    //        {
    //            uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input, observation_ip[i], 0U, i);
    //        }
    // #endif
    //
    // #if NN_9_INPUT_3_64 == 1
    //        uz_mlp_three_layer_ff_blocking(mlp_ip_instance, Global_Data.objects.matrix_input, p_output_data);
    //        // IP-Core only calculates with linear, tanh has to be added manually
    //        v_dq_non_limited_Volts_hoerner.d = (uz_nn_activation_function_tanh(mlp_ip_output[0])) * U_max_hoerner;
    //        v_dq_non_limited_Volts_hoerner.q = (uz_nn_activation_function_tanh(mlp_ip_output[1])) * U_max_hoerner;
    // #else
    //        uz_nn_ff(Global_Data.objects.nn_layer, Global_Data.objects.matrix_input);
    //        matrix_output = uz_nn_get_output_data(Global_Data.objects.nn_layer);
    //        uz_matrix_multiply_by_scalar(matrix_output, U_max_hoerner); // scaling layer of nn
    //        v_dq_non_limited_Volts_hoerner.d = uz_matrix_get_element_zero_based(matrix_output, 0U, 0U);
    //        v_dq_non_limited_Volts_hoerner.q = uz_matrix_get_element_zero_based(matrix_output, 0U, 1U);
    // #endif
    //        v_dq_limited_Volts_hoerner = uz_CurrentControl_SpaceVector_Limitation(v_dq_non_limited_Volts_hoerner, v_DC_Volts_hoerner, max_modulation_index_hoerner, omega_el_rad_per_sec_hoerner, i_dq_ref_Amps_hoerner, &ext_clamping_hoerner);
    //        // Introduce delay
    //        v_dq_limited_Volts_old_old_hoerner = v_dq_limited_Volts_hoerner;
    //        duty_cycle_hoerner = uz_Space_Vector_Modulation(v_dq_limited_Volts_hoerner, v_DC_Volts_hoerner, theta_el_rad_hoerner_advanced);
    //    }
    //
    //    {
    //        Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    //        Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    //        Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    //    }
    //    Global_Data.rasv.halfBridge1DutyCycle = duty_cycle_hoerner.DutyCycle_A;
    //    Global_Data.rasv.halfBridge2DutyCycle = duty_cycle_hoerner.DutyCycle_B;
    //    Global_Data.rasv.halfBridge3DutyCycle = duty_cycle_hoerner.DutyCycle_C;
}

//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_GicInit() - This function initializes RPU GIC and connects
// 					interrupts with the associated handlers
// @IntcInstPtr		Pointer to the GIC instance
// @IntId			Interrupt ID to be connected and enabled
// @Handler			Associated handler for the Interrupt ID
// @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
//----------------------------------------------------
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId)
{
    XScuGic_Config *IntcConfig;
    int status;

    // Interrupt controller initialization
    IntcConfig = XScuGic_LookupConfig(DeviceId);
    status = XScuGic_CfgInitialize(IntcInstPtr, IntcConfig, IntcConfig->CpuBaseAddress);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, IntcInstPtr);

    /* Enable interrupts in the processor */
    Xil_ExceptionEnable(); // Enable interrupts in the ARM

    // setting interrupt trigger sensitivity
    // b01	Active HIGH level sensitive
    // b11 	Rising edge sensitive
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(IntcInstPtr, Interrupt_ISR_ID, 0x0, 0b11); // rising-edge
    // XScuGic_SetPriorityTriggerType(&INTCInst, Interrupt_ISR_ID, 0x0, 0b01); // active-high - default case

    // Make the connection between the IntId of the interrupt source and the
    // associated handler that is to run when the interrupt is recognized.
    status = XScuGic_Connect(IntcInstPtr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             (void *)IntcInstPtr);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Enable GPIO and timer interrupts in the controller
    XScuGic_Enable(IntcInstPtr, Interrupt_ISR_ID);
    XScuGic_Enable(IntcInstPtr, INTC_IPC_Shared_INTERRUPT_ID);

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
    XIpiPsu_Config *IntcConfig_IPI;
    int status;

    // Interrupt controller configuration
    IntcConfig_IPI = XIpiPsu_LookupConfig(DeviceId);
    if (IntcConfig_IPI == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&INTCInst_IPI, IntcConfig_IPI, IntcConfig_IPI->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: RPU_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static void ReadAllADC()
{
    ADC_readCardALL(&Global_Data);
};
