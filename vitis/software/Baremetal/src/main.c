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

// Includes from own files
#include "main.h"
#include "Codegen/uz_codegen.h"


extern const struct uz_PMSM_t Siemens_1FK7043;

uz_codegen codegenInstance;

#define ENDAT_D4_SPEED_PLL_KP 628.3185f
#define ENDAT_D4_SPEED_PLL_KI 98696.0f
#define ENCODER_OFFSET_ESTIMATION_SETPOINT_CURRENT_A 4.0f
#define ENCODER_OFFSET_ESTIMATION_MIN_OMEGA_EL_RAD_PER_SEC 400.0f

static void initialize_encoder_offset_estimation_resolver_d3();
static void initialize_encoder_offset_estimation_endat_d4();

// Initialize the global variables
DS_Data Global_Data = {
    .rasv = {
        .halfBridge1DutyCycle = 0.0f,
        .halfBridge2DutyCycle = 0.0f,
        .halfBridge3DutyCycle = 0.0f,
        .halfBridge4DutyCycle = 0.0f,
        .halfBridge5DutyCycle = 0.0f,
        .halfBridge6DutyCycle = 0.0f,
        .halfBridge7DutyCycle = 0.0f,
        .halfBridge8DutyCycle = 0.0f,
        .halfBridge9DutyCycle = 0.0f,
        .halfBridge10DutyCycle = 0.0f,
        .halfBridge11DutyCycle = 0.0f,
        .halfBridge12DutyCycle = 0.0f},
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY)/2.0f,//* (Interrupt_ISR_freq_factor)
    .aa = {.A1 = {.cf.ADC_A1 = 1.0f, .cf.ADC_A2 = 1.0f, .cf.ADC_A3 = 1.0f, .cf.ADC_A4 = 1.0f, .cf.ADC_B5 = 1.0f, .cf.ADC_B6 = 1.0f, .cf.ADC_B7 = 1.0f, .cf.ADC_B8 = 1.0f}, .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}}};

enum init_chain
{
    init_assertions = 0,
    wait_for_apu_handshake,
    init_gpios,
    init_software,
    init_ip_cores,
    print_msg,
    init_interrupts,
    infinite_loop
};
enum init_chain initialization_chain = init_assertions;
#include "APU_RPU_shared.h"
#include "xil_cache.h"

uint32_t apu_version_final = 0;
uint32_t rpu_version_final = 0;

int main(void)
{
    int status = UZ_SUCCESS;
    while (1)
    {
        switch (initialization_chain)
        {
        case init_assertions:
            uz_rpu_assert_configuration();
            initialization_chain = wait_for_apu_handshake;
            break;
        case wait_for_apu_handshake:
            write_rpu_version(0U);
            do
            {
                apu_version_final = read_apu_version();
            } while (!(apu_version_final == 257U));
            write_rpu_version(UZ_HARDWARE_VERSION);
            do
            {
                apu_version_final = read_apu_version();
            } while ((apu_version_final == 257U));
            write_rpu_version(apu_version_final);
            initialization_chain = init_gpios;
            break;
        case init_gpios:
        	uz_sleep_seconds(5);
            Initialize_AXI_GPIO();
            uz_assert((apu_version_final > 0U) && (apu_version_final <= UZ_HARDWARE_VERSION_MAX));
            uz_frontpanel_button_and_led_init(apu_version_final);
            ultrazohm_state_machine_init(apu_version_final);
            initialization_chain = init_software;
            break;
        case init_software:
            uz_SystemTime_init();
            JavaScope_initialize(&Global_Data);

            //Initialize codegen
            uz_codegen_init(&codegenInstance);

            Global_Data.av.polepairs_left = Siemens_1FK7043.polePairs;
            Global_Data.av.polepairs_right = Siemens_1FK7043.polePairs;
            struct uz_pos_to_speed_pll_config_t endat_speed_pll_d4_1_config = {
                .machine_polepairs = Global_Data.av.polepairs_right,
                .kp_pll = ENDAT_D4_SPEED_PLL_KP,
                .ki_pll = ENDAT_D4_SPEED_PLL_KI,
                .sampling_time_in_seconds = 1.0f/UZ_PWM_FREQUENCY};
            Global_Data.objects.endat_speed_pll_d4_1 = uz_pos_to_speed_pll_init(endat_speed_pll_d4_1_config);
            initialize_encoder_offset_estimation_resolver_d3();
            initialize_encoder_offset_estimation_endat_d4();
            Global_Data.objects.current_ctrl_left = current_ctrl_left_init();
            Global_Data.objects.current_ctrl_right = current_ctrl_right_init();
            Global_Data.objects.setpoint_ctrl_left = setpoint_ctrl_left_init();
            Global_Data.objects.setpoint_ctrl_right = setpoint_ctrl_right_init();
            Global_Data.objects.speed_ctrl_left = speed_ctrl_left_init();
            Global_Data.objects.speed_ctrl_right = speed_ctrl_right_init();
			Global_Data.objects.iir_filter_ref_speed_left = speed_filt_left_init();
			Global_Data.objects.iir_filter_ref_speed_right = speed_filt_right_init();
			Global_Data.objects.iir_filter_torque = torque_filt_init();
            initialization_chain = init_ip_cores;
            break;
        case init_ip_cores:
            uz_adcLtc2311_ip_core_init();
            Global_Data.objects.deadtime_interlock_d1_pin_0_to_5 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_0_to_5();
            Global_Data.objects.deadtime_interlock_d1_pin_6_to_11 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_6_to_11();
            Global_Data.objects.deadtime_interlock_d1_pin_12_to_17 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_12_to_17();
            Global_Data.objects.deadtime_interlock_d1_pin_18_to_23 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_18_to_23();
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, true);
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, true);
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_12_to_17, true);
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_18_to_23, true);
            Global_Data.objects.pwm_d1_pin_0_to_5 = initialize_pwm_2l_on_D1_pin_0_to_5();
            Global_Data.objects.pwm_d1_pin_6_to_11 = initialize_pwm_2l_on_D1_pin_6_to_11();
            Global_Data.objects.pwm_d1_pin_12_to_17 = initialize_pwm_2l_on_D1_pin_12_to_17();
            Global_Data.objects.pwm_d1_pin_18_to_23 = initialize_pwm_2l_on_D1_pin_18_to_23();
            Global_Data.objects.mux_axi = initialize_uz_mux_axi();
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            Global_Data.objects.encoder_D5 = initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);
            //Global_Data.rasv.resolver_offset = -4.363502f; // estimated with offset estimation module
            Global_Data.rasv.resolver_offset = -0.1642f; // tuned by ourselves
            //Global_Data.rasv.d4_to_d3_offset_mech = 0.59f; // estimated heuristically
            Global_Data.rasv.d4_to_d3_offset_mech = 0.0523f; // tuned by ourselves
            Global_Data.objects.resolver_d3_1 = initialize_resolver_D3_1();
            Global_Data.objects.resolver_pl_interface_d3_1 = initialize_resolver_pl_interface_D3_1();
            uz_resolver_pl_interface_set_theta_m_offset_rad(Global_Data.objects.resolver_pl_interface_d3_1, Global_Data.rasv.resolver_offset);
            Global_Data.objects.endat_encoder_d4_1 = endat_encoder_init_endat_d4_1();
            uz_endat_interface_set_mode_command(Global_Data.objects.endat_encoder_d4_1, uz_endat_interface_send_position);
            uz_endat_interface_enable_ip(Global_Data.objects.endat_encoder_d4_1, true);
            initialization_chain = print_msg;
            break;
        case print_msg:
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
            uz_printf("RPU Build Date: %s at %s,\r\n", __DATE__, __TIME__);

            initialization_chain = init_interrupts;
            break;
        case init_interrupts:
            uz_axigpio_enable_datamover();
            Initialize_ISR(); // Initialize the Interrupts and enable them - last line of code before infinite loop
            initialization_chain = infinite_loop;
            break;
        case infinite_loop:
            ultrazohm_state_machine_step();
            break;
        default:
            break;
        }
    }
    return (status);
}

static void initialize_encoder_offset_estimation_resolver_d3()
{
    struct uz_encoder_offset_estimation_config config = {
        .ptr_measured_rotor_angle = &Global_Data.av.position_el_2pi_d3_1,
        .ptr_offset_angle = &Global_Data.rasv.resolver_offset,
        .ptr_actual_omega_el = &Global_Data.av.omega_el_left,
        .ptr_actual_u_q_V = &Global_Data.av.v_q_left,
        .setpoint_current = ENCODER_OFFSET_ESTIMATION_SETPOINT_CURRENT_A,
        .min_omega_el = ENCODER_OFFSET_ESTIMATION_MIN_OMEGA_EL_RAD_PER_SEC};

    Global_Data.objects.encoder_offset_estimation_resolver_d3 = uz_encoder_offset_estimation_init(config);
}

static void initialize_encoder_offset_estimation_endat_d4()
{
    struct uz_encoder_offset_estimation_config config = {
        .ptr_measured_rotor_angle = &Global_Data.av.endat_machine.theta_elec,
        .ptr_offset_angle = &Global_Data.rasv.endat_offset,
        .ptr_actual_omega_el = &Global_Data.av.endat_software_pll_machine.electricalRotorSpeed,
        .ptr_actual_u_q_V = &Global_Data.av.v_q_right,
        .setpoint_current = ENCODER_OFFSET_ESTIMATION_SETPOINT_CURRENT_A,
        .min_omega_el = ENCODER_OFFSET_ESTIMATION_MIN_OMEGA_EL_RAD_PER_SEC};

    Global_Data.objects.encoder_offset_estimation_endat_d4 = uz_encoder_offset_estimation_init(config);
}
