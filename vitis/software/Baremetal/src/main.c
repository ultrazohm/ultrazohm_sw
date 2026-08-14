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

// Initialize the global variables
DS_Data Global_Data = {
    .rasv = {
/* Project Wizard BEGIN: rasv_initializer */
        .pwm_2L_0_halfBridgeDutyCycle_1 = 0.0f,
        .pwm_2L_0_halfBridgeDutyCycle_2 = 0.0f,
        .pwm_2L_0_halfBridgeDutyCycle_3 = 0.0f,
        .pwm_2L_1_halfBridgeDutyCycle_1 = 0.0f,
        .pwm_2L_1_halfBridgeDutyCycle_2 = 0.0f,
        .pwm_2L_1_halfBridgeDutyCycle_3 = 0.0f,
        .pwm_2L_2_halfBridgeDutyCycle_1 = 0.0f,
        .pwm_2L_2_halfBridgeDutyCycle_2 = 0.0f,
        .pwm_2L_2_halfBridgeDutyCycle_3 = 0.0f,
        .pwm_2L_3_halfBridgeDutyCycle_1 = 0.0f,
        .pwm_2L_3_halfBridgeDutyCycle_2 = 0.0f,
        .pwm_2L_3_halfBridgeDutyCycle_3 = 0.0f,
        .pwm_3L_0_halfBridgeDutyCycle_1 = 0.0f,
        .pwm_3L_0_halfBridgeDutyCycle_2 = 0.0f,
        .pwm_3L_0_halfBridgeDutyCycle_3 = 0.0f,
/* Project Wizard END: rasv_initializer */
    },
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE / (UZ_PWM_FREQUENCY * Interrupt_ISR_freq_factor)};

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
            initialization_chain = init_ip_cores;
            break;
        case init_ip_cores:
            /* Project Wizard BEGIN: init_ip_cores */
			Global_Data.objects.project_wizard_deadtime_2l_0 = initialize_project_wizard_deadtime_2l_0();
			uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.project_wizard_deadtime_2l_0, true);
			Global_Data.objects.project_wizard_pwm_2l_0 = initialize_project_wizard_pwm_2l_0();
			Global_Data.objects.project_wizard_deadtime_2l_1 = initialize_project_wizard_deadtime_2l_1();
			uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.project_wizard_deadtime_2l_1, true);
			Global_Data.objects.project_wizard_pwm_2l_1 = initialize_project_wizard_pwm_2l_1();
			Global_Data.objects.project_wizard_deadtime_2l_2 = initialize_project_wizard_deadtime_2l_2();
			uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.project_wizard_deadtime_2l_2, true);
			Global_Data.objects.project_wizard_pwm_2l_2 = initialize_project_wizard_pwm_2l_2();
			Global_Data.objects.project_wizard_deadtime_2l_3 = initialize_project_wizard_deadtime_2l_3();
			uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.project_wizard_deadtime_2l_3, true);
			Global_Data.objects.project_wizard_pwm_2l_3 = initialize_project_wizard_pwm_2l_3();
			initialize_project_wizard_pwm_3l(&Global_Data);
			Global_Data.objects.three_phase_sine = uz_wavegen_three_phase_init();
			Global_Data.objects.temperature_card_d3 = initialize_temperature_card_d3();
			uz_TempCard_IF_Reset(Global_Data.objects.temperature_card_d3);
			uz_TempCard_IF_Start(Global_Data.objects.temperature_card_d3);
			Global_Data.objects.temperature_card_d4 = initialize_temperature_card_d4();
			uz_TempCard_IF_Reset(Global_Data.objects.temperature_card_d4);
			uz_TempCard_IF_Start(Global_Data.objects.temperature_card_d4);
/* Project Wizard END: init_ip_cores */
            initialization_chain = print_msg;
            break;
        case print_msg:
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
            uz_printf("RPU: Build Date of main.c: %s at %s,\r\n", __DATE__, __TIME__);
            uz_print_bitstream_timestamp();
            uz_print_control_frequency(Global_Data.av.pwm_frequency_hz, Global_Data.av.isr_samplerate_s);
            initialization_chain = init_interrupts;
            break;
        case init_interrupts:
            uz_axigpio_enable_datamover();
            Initialize_ISR();
            Global_Data.objects.mux_axi = initialize_uz_mux_axi(); // Initialize the Interrupt-Mux - last line of code before infinite loop
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
