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

#define 	CURRENT_2_SI_AMPERE	12.5f
#define		VOLTAGE_2_SI_VOLTS	12.0f

// Initialize the global variables
DS_Data Global_Data = {
    .rasv = {
        .halfBridge1DutyCycle = 0.0f,
        .halfBridge2DutyCycle = 0.0f,
        .halfBridge3DutyCycle = 0.0f,
        .halfBridge4DutyCycle = 0.0f,
        .halfBridge5DutyCycle = 0.0f,
        .halfBridge6DutyCycle = 0.0f,},
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f/0.0242f, .cf.ADC_A2 = 10.0f/0.0242f, .cf.ADC_A3 = 10.0f/0.0242f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A2 = {.cf.ADC_A1 = 10.0f*VOLTAGE_2_SI_VOLTS, .cf.ADC_A2 = 10.0f*CURRENT_2_SI_AMPERE, .cf.ADC_A3 = 10.0f*CURRENT_2_SI_AMPERE, .cf.ADC_A4 = 10.0f*CURRENT_2_SI_AMPERE, .cf.ADC_B5 = 10.0f*CURRENT_2_SI_AMPERE, .cf.ADC_B6 = 10.0f*VOLTAGE_2_SI_VOLTS, .cf.ADC_B7 = 10.0f*VOLTAGE_2_SI_VOLTS, .cf.ADC_B8 = 10.0f*VOLTAGE_2_SI_VOLTS}, .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}}};

enum init_chain
{
    init_assertions_and_wait_for_apu_handshake = 0,
    init_gpios,
    init_software,
    init_ip_cores,
    print_msg,
    init_interrupts,
    infinite_loop
};
enum init_chain initialization_chain = init_assertions_and_wait_for_apu_handshake;
#include "APU_RPU_shared.h"
#include "xil_cache.h"

uint32_t apu_version_final = 0;
uint32_t rpu_version_final = 0;

struct uz_PWM_duty_freq_detection_config_t config = {
 .base_address = XPAR_UZ_USER_UZ_PWMDUTYFREQDETECT_BASEADDR,
 .ip_clk_frequency_Hz = 100000000U,

};

struct uz_axi_gpio_config_t d1_gpi_config={
            .base_address=XPAR_UZ_USER_AXI_GPI_D1_BASEADDR,
            .device_id=XPAR_UZ_USER_AXI_GPI_D1_DEVICE_ID,
            .number_of_pins=3,
            .direction_of_pins=UZ_AXI_GPIO_DIRECTION_ALL_INPUT
};
struct linear_interpolation_parameters_t lin_inter_param= {
 .a = 100.0f,
 .b = -50.0f
};
extern const struct uz_PMSM_t Voestalpine;
int main(void)
{
    int status = UZ_SUCCESS;
    while (1)
    {
        switch (initialization_chain)
        {
        case init_assertions_and_wait_for_apu_handshake:
            uz_assert_configuration(); 
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
            Global_Data.av.VA_polepairs = Voestalpine.polePairs;
            Global_Data.objects.current_ctrl_VA = current_ctrl_VA_init();
            Global_Data.objects.setpoint_ctrl_VA = setpoint_ctrl_VA_init();
            Global_Data.objects.speed_ctrl_VA = speed_ctrl_VA_init();
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
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            Global_Data.objects.encoder_IM = initialize_incremental_encoder_ipcore_on_D5_1(IM_INCREMENTAL_ENCODER_RESOLUTION, IM_POLE_PAIR_NUMBER);
            Global_Data.objects.encoder_VA = initialize_incremental_encoder_ipcore_on_D5_2(VOEST_ALPINE_INCREMENTAL_ENCODER_RESOLUTION, VOEST_ALPINE_POLE_PAIR_NUMBER);
            Global_Data.objects.PWM_Detect_instance = uz_PWM_duty_freq_detection_init(config);
            Global_Data.objects.d1_gpi_ch15_17	= uz_axi_gpio_init(d1_gpi_config);
            Global_Data.objects.inverter_d2 = initialize_uz_inverter_adapter_on_D2();
			Global_Data.objects.iir_filter_ref_speed_VA= speed_filt_VA_init();
            initialization_chain = print_msg;
            break;
        case print_msg:
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
            uz_printf("RPU Build Date of main.c: %s at %s,\r\n", __DATE__, __TIME__);
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
