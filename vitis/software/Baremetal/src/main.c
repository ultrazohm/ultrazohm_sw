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
        .halfBridge12DutyCycle = 0.0f,
        .ctrl_state = ctrl_state_none,
        .Soll_Drehzahl = 0.0f,
        .Soll_id = 0.0f,
        .Soll_iq = 0.0f,
        .Soll_Square_DutyCycle = 0.5f,
        .Soll_Square_Frequency_Hz = 25.0f,
        .Soll_DPT_Current_A = 0.0f,
        .Soll_DPT_MaxCurrent_A = 10.0f,
        .Soll_DPT_ChargeTimeout_ms = 100.0f,
        .Soll_DPT_Deadtime_us = 5.0f,
        .Soll_DPT_Pulse2_us = 5.0f},
    .objects.platform_state_old = running_state,
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
	.av.theta_el_offset = 0.0f,
    .av.isr_samplerate_s = INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE / (UZ_PWM_FREQUENCY * Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}}};

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


struct uz_axi_gpio_config_t input_config={
            .base_address=XPAR_UZ_USER_AXI_GPIO_1_BASEADDR,
            .device_id=XPAR_UZ_USER_AXI_GPIO_1_DEVICE_ID,
            .number_of_pins=19,
            .direction_of_pins=UZ_AXI_GPIO_DIRECTION_ALL_INPUT
};

struct uz_axi_gpio_config_t gpio_out_config={
            .base_address=XPAR_UZ_USER_AXI_GPIO_0_BASEADDR,
            .device_id=XPAR_UZ_USER_AXI_GPIO_0_DEVICE_ID,
            .number_of_pins=19,
            .direction_of_pins=UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT
};

uz_JL_SigmaDelta_Interface_t *Sinc3_Filter = NULL;

uz_axi_gpio_t* input_gpio=NULL;
uz_axi_gpio_t* output_gpio=NULL;
uz_codegen regelung;


int main(void)
{
	regelung.input.Bus_ZM_In_a.Fehlermeldung = false;
		regelung.input.Bus_ZM_In_a.Soll_Drehzahl = 0;
		regelung.input.Bus_ZM_In_a.Soll_Regelungsart = Drehzahl;
		regelung.input.Bus_ZM_In_a.Soll_Status = Ready;
		regelung.input.Bus_ZM_In_a.Soll_id = 0;
		regelung.input.Bus_ZM_In_a.Soll_iq = 0;
		regelung.input.Bus_ZM_In_a.Start_Traj = false;
		regelung.input.Bus_PMSM_Out_j.pmsm_Omega_mech = 0;
		regelung.input.Bus_PMSM_Out_j.pmsm_Iuvw[0] = 0;
		regelung.input.Bus_PMSM_Out_j.pmsm_Iuvw[1] = 0;
		regelung.input.Bus_PMSM_Out_j.pmsm_Iuvw[2] = 0;
		regelung.input.Bus_PMSM_Out_j.pmsm_m_mot = 0;
		regelung.input.Bus_PMSM_Out_j.pmsm_phi_mech = 0;
		regelung.output.Bus_Ctrl_Out_i.Dutycycle[0] = 0.0;
		regelung.output.Bus_Ctrl_Out_i.Dutycycle[1] = 0.0;
		regelung.output.Bus_Ctrl_Out_i.Dutycycle[2] = 0.0;
		regelung.output.Bus_Ctrl_Out_i.ctrl_Ualpha = 0;
		regelung.output.Bus_Ctrl_Out_i.ctrl_Ubeta = 0;
		regelung.output.Bus_Ctrl_Out_i.act_pwm = false;
		regelung.output.Bus_Ctrl_Out_i.board_en = false;
		regelung.output.Bus_Ctrl_Out_i.pwr_en = false;
		regelung.output.Bus_Ctrl_Out_i.reset = false;
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
            uz_codegen_init(&regelung);
            initialization_chain = init_ip_cores;
            break;
        case init_ip_cores:
            uz_adcLtc2311_ip_core_init();
            Global_Data.objects.deadtime_interlock_d1_pin_0_to_5 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_0_to_5();
            Global_Data.objects.deadtime_interlock_d1_pin_6_to_11 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_6_to_11();
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, true);
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, true);
            Global_Data.objects.pwm_d1_pin_0_to_5 = initialize_pwm_2l_on_D1_pin_0_to_5();
            Global_Data.objects.pwm_d1_pin_6_to_11 = initialize_pwm_2l_on_D1_pin_6_to_11();
            Global_Data.objects.resolver = initialize_resolver();
			Global_Data.objects.resolver_pl_interface = initialize_resolver_pl_interface();
            input_gpio= uz_axi_gpio_init(input_config);
            output_gpio = uz_axi_gpio_init(gpio_out_config);
			Sinc3_Filter = SigmaDeltaWandler_init();
            initialization_chain = print_msg;
            break;
        case print_msg:
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
            uz_printf("RPU: Build Date of main.c: %s at %s,\r\n", __DATE__, __TIME__);
            uz_print_bitstream_timestamp();
            initialization_chain = init_interrupts;
            break;
        case init_interrupts:
            uz_axigpio_enable_datamover();
            Initialize_ISR();
            uz_dpt_init(); // uses the GIC instance initialized in Initialize_ISR(), must be called after it
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
