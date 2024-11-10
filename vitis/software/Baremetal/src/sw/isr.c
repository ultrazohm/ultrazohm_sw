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
#include "../uz/uz_array/uz_array.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

struct uz_DutyCycle_t duty_cycle_hoerner = {0};

// =============== Declares for PMSM 2 =============== //

// FOC Instances and Configs
extern struct uz_PMSM_t config_PMSM_beckhoff;
float theta_el_offset_2 = 1.4f;

uint64_t old_uptime = 0U;

#if SETPOINT_PROFILE == SETPOINT_PROFILE_ORIGINAL
float id_setpoints[22] = {
#include "id_setpoints.csv"
};

float iq_setpoints[22] = {
#include "iq_setpoints.csv"
};

#elif SETPOINT_PROFILE == SETPOINT_PROFILE_RS
float id_setpoints[] = {
#include "id_setpoints_rs_ident.csv"
};

float iq_setpoints[] = {
#include "iq_setpoints_rs_ident.csv"
};

#elif SETPOINT_PROFILE == SETPOINT_PROFILE_PARAID
float id_setpoints[] = {
#include "id_setpoints_paraid.csv"
};

float iq_setpoints[] = {
#include "iq_setpoints_paraid.csv"
};
#endif

#if SETPOINT_PROFILE == SETPOINT_PROFILE_ORIGINAL
float speed_setpoints[] = {-0.1f, -0.2f, -0.3f, -0.4f, -0.5f, -0.6f, -0.7f, -0.8f, -0.9f, -1.0f};
#elif SETPOINT_PROFILE == SETPOINT_PROFILE_PARAID
float speed_setpoints[] = {-400};
#elif SETPOINT_PROFILE == SETPOINT_PROFILE_RS
float speed_setpoints[] = {-0.05f,-0.1f, -0.2f, -0.3f, -0.4f, -0.5f, -0.6f, -0.7f, -0.8f, -0.9f, -1.0f};
#endif

extern float PMSM_rated_current_hoerner;
extern bool select_misalignment;

uint32_t Fehlerfall = 0U;

// DDPG Stuff
extern bool select_DDPG;
extern bool select_FOC;
float observation_ip[9U] = {0};
#define NUMBER_OF_INPUTS_7N 7U
#define NUMBER_OF_INPUTS_9N 9U
uz_matrix_t *matrix_output;
float theta_el_old_hoerner = 0.0f;

#define PROFILE_SETPOINT_DURATION_IN_ISR_TICKS 5000U // 11290U

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
static void check_inverter_errors(void);
void automatic_profile(void);
void all_measurements(void);

struct uz_pmsm_measurement_values d1_measurements = {0};
struct uz_pmsm_measurement_values d2_measurements = {0};
const int machine_on_d1 = D1_MACHINE; // EBM, Brose, Hoerner
const int machine_on_d2 = D2_MACHINE; // HEIDRIVE_D2, BUEHLER, BECKHOFF

bool enable_d1_controller = false;
bool enable_d2_controller = false;
float d1_reference_speed_in_rpm = 0.0f;
float d2_reference_speed_in_rpm = 0.0f;
float d1_added_noise = 0.0f;
float d2_added_noise = 0.0f;
uz_3ph_dq_t d1_reference_currents_in_A = {0.0f};
uz_3ph_dq_t d2_reference_currents_in_A = {0.0f};
bool manual_dutycycle_d2 = false;
bool manual_dutycycle_d1 = false;
struct uz_pmsmModel_outputs_t cil_outputs = {0};
struct uz_pmsmModel_outputs_t cil_new_outputs = {0};
struct uz_pmsmModel_inputs_t cil_inputs = {0};
struct uz_3ph_dq_t cil_dq_currents = {0};

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    if (Global_Data.use_cil)
    {
        uz_pmsm_controller_use_cil(Global_Data.objects.d1_controller, true);
        uz_pmsm_controller_use_cil(Global_Data.objects.d2_controller, true);

        uz_pmsmModel_trigger_input_strobe(Global_Data.cil.pmsm_cil);
        uz_pmsmModel_trigger_output_strobe(Global_Data.cil.pmsm_cil);
        cil_new_outputs = uz_pmsmModel_get_outputs(Global_Data.cil.pmsm_cil);
        #if CIL_1_TAU==1
            cil_outputs = cil_new_outputs;
        #endif
        cil_dq_currents.d = cil_outputs.i_d_A;
        cil_dq_currents.q = cil_outputs.i_q_A;
        *Global_Data.dut_theta_offset=0.0f;
        struct uz_3ph_abc_t cil_abc_currents = uz_transformation_3ph_dq_to_abc(cil_dq_currents, *Global_Data.dut_theta_offset);
        Global_Data.av.mechanicalRotorSpeed_filtered_prime_mover = uz_signals_IIR_Filter_sample(Global_Data.objects.tracking_error_filter_prime_mover, Global_Data.prime_mover_reference_speed_in_rpm);

        if (D1_IS_PRIME_MOVER)
        {
            d2_measurements.omega_mech_rad_per_sec = cil_outputs.omega_mech_1_s;
            d2_measurements.phase_currents_from_adc_ampere_per_volt = cil_abc_currents;
            d2_measurements.i_dc_from_adc_ampere_per_volt = 0.0f;
            d2_measurements.theta_mech = 0.0f;
            d2_measurements.v_dc_from_adc_volt_per_volt = 48.0f;
            d1_measurements.v_dc_from_adc_volt_per_volt = 48.0f;
        }
        else
        {
            d1_measurements.omega_mech_rad_per_sec = cil_outputs.omega_mech_1_s;
            d1_measurements.phase_currents_from_adc_ampere_per_volt = cil_abc_currents;
            d1_measurements.i_dc_from_adc_ampere_per_volt = 0.0f;
            d1_measurements.theta_mech = 0.0f;
            d1_measurements.v_dc_from_adc_volt_per_volt = 48.0f;
            d2_measurements.v_dc_from_adc_volt_per_volt = 48.0f;
        }
    }
    else
    {
        uz_pmsm_controller_use_cil(Global_Data.objects.d1_controller, false);
        uz_pmsm_controller_use_cil(Global_Data.objects.d2_controller, false);
        all_measurements();
    }

    check_inverter_errors();
    Global_Data.av.Resolver_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4);
    automatic_profile();

    if(Global_Data.javascope.sweep_theta_el){
        *Global_Data.dut_theta_offset += 1.0f/10000.0f; // Moves the offset slightly in each ISR execution. Slow enought to assume it is still always steady state for evaluation
    }

    if (Global_Data.javascope.setpoints_from_javascope)
    {
        Global_Data.prime_mover_reference_speed_in_rpm = Global_Data.javascope.prime_mover_reference_speed_in_rpm;
        Global_Data.dut_reference_currents_in_A.d = Global_Data.javascope.dut_reference_currents_in_A.d;
        Global_Data.dut_reference_currents_in_A.q = Global_Data.javascope.dut_reference_currents_in_A.q;
        if (D1_IS_PRIME_MOVER)
        {
            if (Global_Data.javascope.disable_speed_control)
            {
                uz_pmsm_controller_enable_speed_control(Global_Data.objects.d1_controller, false);
            }
            else
            {
                uz_pmsm_controller_enable_speed_control(Global_Data.objects.d1_controller, true);
            }
        }
        else
        {
            if (Global_Data.javascope.disable_speed_control)
            {
                uz_pmsm_controller_enable_speed_control(Global_Data.objects.d2_controller, false);
            }
            else
            {
                uz_pmsm_controller_enable_speed_control(Global_Data.objects.d2_controller, true);
            }
        }
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
        if (D1_IS_PRIME_MOVER)
        {
            uz_pmsm_controller_use_rlcc(Global_Data.objects.d2_controller, Global_Data.javascope.use_rl);
        }
        else
        {
            uz_pmsm_controller_use_rlcc(Global_Data.objects.d1_controller, Global_Data.javascope.use_rl);
        }
        uz_pmsm_controller_acknowledge_and_reset_error(Global_Data.objects.d1_controller, d1_measurements);
        uz_pmsm_controller_acknowledge_and_reset_error(Global_Data.objects.d2_controller, d2_measurements);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1, true, true, true);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d2, true, true, true);
        //  uz_pmsmModel_reset(Global_Data.cil.pmsm_cil);
    }
    //
    if (current_state == control_state)
    {
        if (D1_IS_PRIME_MOVER)
        {
            enable_d1_controller = true;
            if (!Global_Data.use_cil)
            {
                uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1, false, false, false);
            }
            if (Global_Data.javascope.enable_dut)
            {
                enable_d2_controller = true;
                if (!Global_Data.use_cil)
                {
                    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d2, false, false, false);
                }
            }
        }
            else
            {
                enable_d2_controller = true;
                if (!Global_Data.use_cil)
                {
                    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d2, false, false, false);
                }
                if (Global_Data.javascope.enable_dut)
                {
                    enable_d1_controller = true;
                    if (!Global_Data.use_cil)
                    {
                        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1, false, false, false);
                    }
                }
            }
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
                if (Global_Data.javascope.disable_speed_control)
                {
                    d1_reference_currents_in_A.d = Global_Data.dut_reference_currents_in_A.d;
                    d1_reference_currents_in_A.q = Global_Data.dut_reference_currents_in_A.q;
                }
                else
                {
                    d1_reference_currents_in_A.d = 0.0f;
                    d1_reference_currents_in_A.q = 0.0f;
                }
                d1_reference_speed_in_rpm = Global_Data.prime_mover_reference_speed_in_rpm;
                d2_reference_currents_in_A.d = Global_Data.dut_reference_currents_in_A.d;
                d2_reference_currents_in_A.q = Global_Data.dut_reference_currents_in_A.q;
                d2_reference_speed_in_rpm = 0.0f;
                // d1_added_noise=0.0f;
                d2_added_noise = 0.0f;
                d1_added_noise = Global_Data.dut.torque_constant * Global_Data.dut_reference_currents_in_A.q;
            }
            else
            {
                d1_reference_currents_in_A.d = Global_Data.dut_reference_currents_in_A.d;
                d1_reference_currents_in_A.q = Global_Data.dut_reference_currents_in_A.q;
                d1_reference_speed_in_rpm = 0.0f;
                if (Global_Data.javascope.disable_speed_control)
                {
                    d2_reference_currents_in_A.d = Global_Data.dut_reference_currents_in_A.d;
                    d2_reference_currents_in_A.q = Global_Data.dut_reference_currents_in_A.q;
                }
                else
                {
                    d2_reference_currents_in_A.d = 0.0f;
                    d2_reference_currents_in_A.q = 0.0f;
                }
                d2_reference_speed_in_rpm = Global_Data.prime_mover_reference_speed_in_rpm;
                d1_added_noise = 0.0f;
                // d2_added_noise = 0.0f;
                d2_added_noise = Global_Data.dut.torque_constant * Global_Data.dut_reference_currents_in_A.q;
            }

            struct uz_DutyCycle_t duty_d1 = uz_pmsm_controller_sample(Global_Data.objects.d1_controller, d1_measurements, d1_reference_speed_in_rpm, d1_reference_currents_in_A, d1_added_noise);
            struct uz_DutyCycle_t duty_d2 = uz_pmsm_controller_sample(Global_Data.objects.d2_controller, d2_measurements, d2_reference_speed_in_rpm, d2_reference_currents_in_A, d2_added_noise);

            if (Global_Data.use_cil && (current_state == control_state))
            {
                cil_inputs.v_d_V = Global_Data.dut.reference_values->v_dq_in_V.d;
                cil_inputs.v_q_V = Global_Data.dut.reference_values->v_dq_in_V.q;
                cil_inputs.omega_mech_1_s = -1.0f*Global_Data.av.mechanicalRotorSpeed_filtered_prime_mover / 60.0f * 2.0f * UZ_PIf;
                cil_inputs.load_torque = 0.0f;
                uz_pmsmModel_set_inputs(Global_Data.cil.pmsm_cil, cil_inputs);
            }

            Global_Data.d1_operating_region_violation = uz_pmsm_controller_get_safe_operating_area_violation(Global_Data.objects.d1_controller);
            Global_Data.d2_operating_region_violation = uz_pmsm_controller_get_safe_operating_area_violation(Global_Data.objects.d2_controller);

            // What to do if operating region is violated? Hard stop? All tristate? Or just control all controllable quantities to 0?
            // Currently, enable is stopped so hardstop it is
            if (Global_Data.d1_operating_region_violation || Global_Data.d2_operating_region_violation)
            {
                ultrazohm_state_machine_set_error(true);
                ultrazohm_state_machine_set_userLED(true);
            }

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
            cil_outputs=cil_new_outputs;
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
            d2_measurements.phase_voltage_from_adc_voltage_per_volt.a = Global_Data.aa.A2.me.ADC_B8;
            d2_measurements.phase_voltage_from_adc_voltage_per_volt.b = Global_Data.aa.A2.me.ADC_B7;
            d2_measurements.phase_voltage_from_adc_voltage_per_volt.c = Global_Data.aa.A2.me.ADC_B6;

            d2_measurements.v_dc_from_adc_volt_per_volt = Global_Data.aa.A2.me.ADC_A1; //48.0f / 12.0f;
            d2_measurements.phase_currents_from_adc_ampere_per_volt.a = Global_Data.aa.A2.me.ADC_A4;
            d2_measurements.phase_currents_from_adc_ampere_per_volt.b = Global_Data.aa.A2.me.ADC_A3;
            d2_measurements.phase_currents_from_adc_ampere_per_volt.c = Global_Data.aa.A2.me.ADC_A2;

            switch (machine_on_d2)
            {
            case BECKHOFF:
                d2_measurements.omega_mech_rad_per_sec = Global_Data.av.Resolver_outputs.omega_mech_rad_s;
                d2_measurements.theta_mech = Global_Data.av.Resolver_outputs.position_mech_2pi;
                break;
            case BUEHLER:
                if (fabsf(Global_Data.av.d5_3_omega_mech_rad_per_sec - d2_measurements.omega_mech_rad_per_sec) < 50.0f)
                {
                    d2_measurements.omega_mech_rad_per_sec = Global_Data.av.d5_3_omega_mech_rad_per_sec;
                }
                // d2_measurements.omega_mech_rad_per_sec = Global_Data.av.d5_3_omega_mech_rad_per_sec;
                d2_measurements.theta_mech = Global_Data.av.d5_3_theta_el;
                break;
            case HEIDRIVE_D2:
                if (fabsf(Global_Data.av.d5_2_omega_mech_rad_per_sec - d2_measurements.omega_mech_rad_per_sec) < 50.0f)
                {
                    d2_measurements.omega_mech_rad_per_sec = Global_Data.av.d5_2_omega_mech_rad_per_sec;
                }
                // d2_measurements.omega_mech_rad_per_sec = Global_Data.av.d5_2_omega_mech_rad_per_sec;
                d2_measurements.theta_mech = Global_Data.av.d5_2_theta_el;
                break;
            default:
                uz_assert(0);
                break;
            }

            d1_measurements.i_dc_from_adc_ampere_per_volt = Global_Data.aa.A1.me.ADC_B5;
            d1_measurements.phase_voltage_from_adc_voltage_per_volt.a = Global_Data.aa.A1.me.ADC_B8;
            d1_measurements.phase_voltage_from_adc_voltage_per_volt.b = Global_Data.aa.A1.me.ADC_B7;
            d1_measurements.phase_voltage_from_adc_voltage_per_volt.c = Global_Data.aa.A1.me.ADC_B6;

            d1_measurements.v_dc_from_adc_volt_per_volt =Global_Data.aa.A1.me.ADC_A1;
            d1_measurements.phase_currents_from_adc_ampere_per_volt.a = Global_Data.aa.A1.me.ADC_A4;
            d1_measurements.phase_currents_from_adc_ampere_per_volt.b = Global_Data.aa.A1.me.ADC_A3;
            d1_measurements.phase_currents_from_adc_ampere_per_volt.c = Global_Data.aa.A1.me.ADC_A2;
            
            if (fabsf(Global_Data.av.d5_1_omega_mech_rad_per_sec - d1_measurements.omega_mech_rad_per_sec) < 50.0f)
            { // only accept new values if the difference between two time steps is below 500
                d1_measurements.omega_mech_rad_per_sec = Global_Data.av.d5_1_omega_mech_rad_per_sec;
            }
            //  d1_measurements.omega_mech_rad_per_sec = Global_Data.av.d5_1_n_rpm_filtered;
            d1_measurements.theta_mech = Global_Data.av.d5_1_theta_el;

            Global_Data.M_meas_Nm = Global_Data.aa.A3.me.ADC_A4 * 2.0f; // - 0.02f;
        }

        float theta_dut_zero_crossing = false;
        bool found_zero_crossing = false;

        void automatic_profile(void)
        {
            if ((Global_Data.javascope.select_automatic_idiq))
            {
                Global_Data.profile.prime_mover_reference_speed_in_rpm = Global_Data.profile.speed_scale_in_rpm * speed_setpoints[Global_Data.profile.n_ref_setpoint_index];
                Global_Data.profile.speed_tracking_error = fabsf(Global_Data.profile.prime_mover_reference_speed_in_rpm - Global_Data.av.mechanicalRotorSpeed_filtered_prime_mover);

                if (Global_Data.profile.speed_tracking_error < 1.0f && Global_Data.profile.wait_for_n_ref)
                {
                    Global_Data.profile.speed_setpoint_reached = true;
                    Global_Data.profile.wait_for_n_ref = false;
                }

                if (Global_Data.use_cil)
                {
                    if (found_zero_crossing == false)
                    {
                        found_zero_crossing = true;
                    }
                }
                else
                {
                    theta_dut_zero_crossing = (Global_Data.profile.theta_mech_dut_old - Global_Data.dut.measurement_values->theta_mech);
                    found_zero_crossing = (theta_dut_zero_crossing > UZ_PIf);
                }

                if ((found_zero_crossing || (Global_Data.prime_mover.actual_data->speed_in_rpm < 10.0f)) && (!Global_Data.profile.start_angle_found) && (Global_Data.profile.speed_setpoint_reached))
                {
                    Global_Data.profile.start_angle_found = true;
                    Global_Data.javascope.start_marker = 1.0f;
                    Global_Data.profile.speed_setpoint_reached = false;
                }
                if (Global_Data.profile.start_angle_found)
                {
                    Global_Data.profile.dut_reference_currents_in_A.d = id_setpoints[Global_Data.profile.setpoint_index] * Global_Data.profile.id_scale_in_A;
                    Global_Data.profile.dut_reference_currents_in_A.q = iq_setpoints[Global_Data.profile.setpoint_index] * Global_Data.profile.iq_scale_in_A; // * PMSM_rated_current_hoerner;

                    // step throught the array
                    uint64_t current_uptime = uz_SystemTime_GetInterruptCounter();
                    if ((current_uptime > (old_uptime + PROFILE_SETPOINT_DURATION_IN_ISR_TICKS) && (!Global_Data.profile.change_speed)))
                    {
                        old_uptime = current_uptime;

                        if (Global_Data.profile.setpoint_index < (UZ_ARRAY_SIZE(id_setpoints) - 1U))
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
                            if (Global_Data.profile.n_ref_setpoint_index < (UZ_ARRAY_SIZE(speed_setpoints) - 1U))
                            {
                                Global_Data.profile.n_ref_setpoint_index++;
                            }
                            else
                            {
                                // stop
                                Global_Data.javascope.select_automatic_idiq = false;
                                Global_Data.profile.n_ref_setpoint_index = 0U;
                                // ultrazohm_state_machine_set_stop(true);
                            }
                            Global_Data.profile.prime_mover_reference_speed_in_rpm = Global_Data.profile.speed_scale_in_rpm * speed_setpoints[Global_Data.profile.n_ref_setpoint_index];
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

        //==============================================================================================================================================================
        //----------------------------------------------------
        // Rpu_GicInit() - This function initializes RPU GIC and connects
        // 					interrupts with the associated handlers
        // @IntcInstPtr		Pointer to the GIC instance
        // @IntId			Interrupt ID to be connected and enabled
        // @Handler			Associated handler for the Interrupt ID
        // @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
        //----------------------------------------------------
        int Rpu_GicInit(XScuGic * IntcInstPtr, u16 DeviceId)
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
