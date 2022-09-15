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

XGpio output;
int axi_gpio_data = 0xFFFFFFFF;
int axi_gpio_init_ok = 0U;

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
		.halfBridge12DutyCycle = 0.0f
    },
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
    	   .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
		   .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}
    }
};

// Current reference values for POHR
float CurrentOn_Angle_deg = 120.0f;
float CurrentOff_Angle_deg = 175.0f;
float CurrentOn_Reference_A = 5.0f;
float i_ref = 0.0f;		// Actual reference value
float PIon_Angle_Active_deg = 115.0f;
float PIon_Angle_Inactive_deg = 175.0f;
float flg_theta_mech_prediction = 1.0f;	// Predicts theta_mech for one time_step to set reference values
float flg_InductanceDeviation_Compensation = 1.0f;	// Compensation of dL/dt * i
float flg_Inductance_PreControl = 1.0f;

struct uz_IIR_Filter_config iir_config_dc_volts = {
		.selection = LowPass_first_order,
		.cutoff_frequency_Hz = 1.0f,
		.sample_frequency_Hz = SAMPLE_FREQUENCY};

struct uz_IIR_Filter_config iir_config_currents = {
		.selection = LowPass_first_order,
		.cutoff_frequency_Hz = 500.0f,
		.sample_frequency_Hz = SAMPLE_FREQUENCY};

struct uz_IIR_Filter_config iir_config_rpm_ref = {
		.selection = LowPass_first_order,
		.cutoff_frequency_Hz = 10.0f,
		.sample_frequency_Hz = SAMPLE_FREQUENCY};

// Active for both coils in series for rising current edge
// L_min = 2*0.4699 mH;  L_max = 2*1.9957 mH;	R = 2*0.044 Ohm
// Kp = L * 2*Pi*BW
// Ki = R/L
// Kp(L_max,800Hz) =  20.1;	Ki(L_max,800Hz) = 22.05
// Kp(L_min,800Hz) =  4.7240;	Ki(L_max,800Hz) = 93.64
const struct uz_PI_Controller_config config_PI1_on = {
   .Kp = 7.0f,	//Serial: 10.0
   .Ki = 2000.0f,	//Serial: 700
   .samplingTime_sec = 1.0f/SAMPLE_FREQUENCY,
   .upper_limit = 300.0f,
   .lower_limit = -300.0f
};
// Active for both coils in series for falling current edge
const struct uz_PI_Controller_config config_PI1_off = {
   .Kp = 6.0f,		//Serial: 20.0
   .Ki = 800.0f,	//Serial 600
   .samplingTime_sec = 1.0f/SAMPLE_FREQUENCY,
   .upper_limit = 300.0f,
   .lower_limit = -300.0f
};

enum init_chain
{
    init_assertions = 0,
    init_gpios,
    init_software,
    init_ip_cores,
    print_msg,
    init_interrupts,
    infinite_loop
};
enum init_chain initialization_chain = init_assertions;

int main(void)
{
    int status = UZ_SUCCESS;
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
            Initialize_Timer();
            uz_SystemTime_init();
            JavaScope_initalize(&Global_Data);
            Global_Data.objects.iir_u_dc = uz_signals_IIR_Filter_init(iir_config_dc_volts);
            Global_Data.objects.iir_i_a1 = uz_signals_IIR_Filter_init(iir_config_currents);
            Global_Data.objects.iir_i_b1 = uz_signals_IIR_Filter_init(iir_config_currents);
            Global_Data.objects.iir_i_c1 = uz_signals_IIR_Filter_init(iir_config_currents);
            Global_Data.objects.iir_rpm_ref = uz_signals_IIR_Filter_init(iir_config_rpm_ref);
            Global_Data.av.theta_offset = 0.48583f;
            Global_Data.av.polepairs = 1.0f;
            Global_Data.av.flg_rising_edge = 0.0f;
            Global_Data.av.flg_falling_edge = 0.0f;
            Global_Data.av.u_precontrol = 0.0f;
            Global_Data.av.precontrol_counter_on = 3.0f;
            Global_Data.av.precontrol_counter_off = 3.0f;
            Global_Data.objects.PI_cntr1_on = uz_PI_Controller_init(config_PI1_on);
            Global_Data.objects.PI_cntr1_off = uz_PI_Controller_init(config_PI1_off);
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
            Global_Data.objects.resolver_IP = initialize_resolverIP_on_D5();
            axi_gpio_init_ok = XGpio_Initialize(&output, XPAR_UZ_USER_AXI_GPIO_0_DEVICE_ID);
			XGpio_SetDataDirection(&output, 1, 0x00U);
			XGpio_DiscreteWrite(&output, 1, axi_gpio_data);
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            initialization_chain = print_msg;
            break;
        case print_msg:
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
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
