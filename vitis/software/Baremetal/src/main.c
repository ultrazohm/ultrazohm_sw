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
        .ctrl_state = ctrl_state_none,
        .Soll_Drehzahl = 0.0f,
        .Soll_id = 0.0f,
        .Soll_iq = 0.0f},
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

struct uz_JL_flt_dis_config_t flt_dis_config = {
            .base_address = XPAR_UZ_JL_FLT_IP_0_BASEADDR,
            .ip_core_frequency_Hz = 100000000U,
            .use_flt_dis = true,
};

uz_codegen regelung;

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
            uz_codegen_init(&regelung);
            uz_codegen0_initialize(regelung.PtrToModelData); 
            initialization_chain = init_ip_cores;
            break;
        case init_ip_cores:
            uz_adcLtc2311_ip_core_init();
            Global_Data.objects.deadtime_interlock_d1_pin_0_to_5 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_0_to_5();
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, false);
            Global_Data.objects.pwm_d1_pin_0_to_5 = initialize_pwm_2l_on_D1_pin_0_to_5();
            Global_Data.objects.resolver = initialize_resolver();
			Global_Data.objects.resolver_pl_interface = initialize_resolver_pl_interface();
            Global_Data.objects.input_gpio = uz_axi_gpio_init(input_config);
            Global_Data.objects.output_gpio = uz_axi_gpio_init(gpio_out_config);
			Global_Data.objects.Sinc3_Filter_P = SigmaDeltaWandler_init(SDW_FILTER_P);
			Global_Data.objects.Sinc3_Filter_I = SigmaDeltaWandler_init(SDW_FILTER_I); // liefert NULL, solange SDW_SECOND_FILTER_HW_AVAILABLE == 0
			Global_Data.objects.Sinc3_Filter_OCP = SigmaDeltaWandler_init(SDW_FILTER_OCP); // NULL, bis XPAR_...INT_2 / base_address gesetzt ist
			Global_Data.objects.flt_dis = uz_JL_flt_dis_init(flt_dis_config);
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
