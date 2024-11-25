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
#include "include/init_beckhoff_on_d2.h"
#include "include/init_buehler_on_d2.h"
#include "include/init_heidrive_on_d2.h"

#include "include/init_brose_on_d1.h"
#include "include/init_ebm_on_d1.h"
#include "include/init_hoerner_on_d1.h"

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
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}}};

enum init_chain
{
    init_assertions = 0,
    init_gpios,
    init_software,
    init_ip_cores,
    init_control,
    print_msg,
    init_interrupts,
    infinite_loop
};
enum init_chain initialization_chain = init_assertions;

struct uz_IIR_Filter_config reverse_filter_config = {
    .selection = LowPass_first_order,
    .cutoff_frequency_Hz = 1700.0f,
    .sample_frequency_Hz = 10000.0f};

int main(void)
{
    int status = UZ_SUCCESS;

    struct uz_IIR_Filter_config tracking_error_filter_prime_mover_config = {
        .selection = LowPass_first_order,
        .cutoff_frequency_Hz = 0.3f,
        .sample_frequency_Hz = 10000.0f,
    };
    Global_Data.profile.wait_for_n_ref = true;
    Global_Data.profile.speed_setpoint_reached = false;
    Global_Data.profile.start_angle_found = false;
    Global_Data.profile.change_speed = false;
    Global_Data.profile.setpoint_index = 0U;
    Global_Data.profile.n_ref_setpoint_index = 0U;
    // Global_Data.use_cil=true;

    while (1)
    {
        switch (initialization_chain)
        {
        case init_assertions:
            uz_assert_configuration(); // This has to be the first line of code in main.c
            initialization_chain = init_gpios;
            break;
        case init_gpios:
            Initialize_AXI_GPIO();               // This has to be the second line of code in main.c since the assertion callback uses the AXI_GPIO to disable the system
            uz_frontplane_button_and_led_init(); // This has to be the third line of code since the assertion callback uses the LEDs to indicate an error
            initialization_chain = init_software;
            break;
        case init_software:
            uz_SystemTime_init();
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
            Global_Data.objects.pwm_d1 = initialize_pwm_2l_on_D1_pin_0_to_5();
            Global_Data.objects.pwm_d2 = initialize_pwm_2l_on_D1_pin_6_to_11();
            Global_Data.objects.pwm_d1_pin_12_to_17 = initialize_pwm_2l_on_D1_pin_12_to_17();
            Global_Data.objects.pwm_d1_pin_18_to_23 = initialize_pwm_2l_on_D1_pin_18_to_23();
            Global_Data.objects.mux_axi = initialize_uz_mux_axi();
            Global_Data.objects.inverter_d1 = initialize_uz_inverter_adapter_on_D1();
            Global_Data.objects.inverter_d2 = initialize_uz_inverter_adapter_on_D2();
            Global_Data.objects.resolver_d4 = initialize_resolver_d4();
            Global_Data.objects.resolver_pl_d4 = initialize_resolver_pl_d4();
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            Global_Data.objects.encoder_D5_1 = initialize_incremental_encoder_ipcore_on_D5_1(UZ_D5_1_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_1_MOTOR_POLE_PAIR_NUMBER);
            Global_Data.objects.encoder_D5_2 = initialize_incremental_encoder_ipcore_on_D5_2(UZ_D5_2_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_2_MOTOR_POLE_PAIR_NUMBER);
            Global_Data.objects.encoder_D5_3 = initialize_incremental_encoder_ipcore_on_D5_3(UZ_D5_3_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_3_MOTOR_POLE_PAIR_NUMBER);
            // uz_IIR_Filter_t *uz_signals_IIR_Filter_init(struct uz_IIR_Filter_config config)
            Global_Data.objects.phase_a_lowpass = uz_signals_IIR_Filter_init(reverse_filter_config);
            Global_Data.objects.phase_b_lowpass = uz_signals_IIR_Filter_init(reverse_filter_config);
            Global_Data.objects.phase_c_lowpass = uz_signals_IIR_Filter_init(reverse_filter_config);
            Global_Data.objects.d2_phase_a_lowpass = uz_signals_IIR_Filter_init(reverse_filter_config);
            Global_Data.objects.d2_phase_b_lowpass = uz_signals_IIR_Filter_init(reverse_filter_config);
            Global_Data.objects.d2_phase_c_lowpass = uz_signals_IIR_Filter_init(reverse_filter_config);
            initialization_chain = init_control;
            break;
        case init_control:

#if D1_MACHINE == HOERNER
            init_hoerner_on_d1();
#elif D1_MACHINE == EBM
            init_ebm_on_d1();
#elif D1_MACHINE == BROSE
            init_brose_on_d1();
#endif

#if D2_MACHINE == BUEHLER
            init_buehler_on_d2();
#elif D2_MACHINE == HEIDRIVE_D2
            init_heidrive_on_d2();
#elif D2_MACHINE == BECKHOFF
            init_beckhoff_on_d2();
#endif

            if (D1_IS_PRIME_MOVER)
            {
                Global_Data.dut_theta_offset = uz_pmsm_control_get_pointer_to_theta_offset(Global_Data.objects.d2_controller);
            }
            else
            {
                Global_Data.dut_theta_offset = uz_pmsm_control_get_pointer_to_theta_offset(Global_Data.objects.d1_controller);
            }
            Global_Data.objects.tracking_error_filter_prime_mover = uz_signals_IIR_Filter_init(tracking_error_filter_prime_mover_config);
            initialization_chain = print_msg;
            break;
        case print_msg:
            struct uz_pmsmModel_config_t pmsm_IPCore_config = {
                .base_address = XPAR_UZ_USER_UZ_PMSM_MODEL_0_BASEADDR,
                .ip_core_frequency_Hz = 100000000,
                .simulate_mechanical_system = false,
                .r_1 = Global_Data.dut.pmsm_data->R_ph_Ohm,
                .L_d = Global_Data.dut.pmsm_data->Ld_Henry,
                .L_q = Global_Data.dut.pmsm_data->Lq_Henry,
                .psi_pm = Global_Data.dut.pmsm_data->Psi_PM_Vs,
                .polepairs = Global_Data.dut.pmsm_data->polePairs,
                .inertia = 1.48e-05f,
                .coulomb_friction_constant = 0.01f,
                .friction_coefficient = 0.001f};
            Global_Data.cil.pmsm_cil = uz_pmsmModel_init(pmsm_IPCore_config);
            uz_pmsmModel_reset(Global_Data.cil.pmsm_cil);
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
            uz_printf("RPU Build Date: %s at %s,\r\n", __DATE__, __TIME__);
            JavaScope_initialize(&Global_Data);
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
