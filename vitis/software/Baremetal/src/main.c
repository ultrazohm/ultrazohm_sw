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
		.halfBridge12DutyCycle = 0.0f
    },
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
    	   .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
		   .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}
    }
};


// Init structs
const struct uz_PMSM_t config_PMSM = {
	.R_ph_Ohm = 0.140f,

   .Ld_Henry = 0.001f,

   .Lq_Henry = 0.001f,

   .Psi_PM_Vs = 0.0f,

   .polePairs = 2.0f,

   .I_max_Ampere = 10.0f

};

const struct uz_PI_Controller_config config_id = {

   .Kp = 1.0f,

   .Ki = 10.0f,

   .samplingTime_sec = 1/SAMPLE_FREQUENCY,

   .upper_limit = 20.0f,

   .lower_limit = -20.0f

};

const struct uz_PI_Controller_config config_iq = {

   .Kp = 1.0f,

   .Ki = 10.0f,

   .samplingTime_sec = 1/SAMPLE_FREQUENCY,

   .upper_limit = 20.0f,

   .lower_limit = -20.0f

};

struct uz_FOC_config config_FOC = {

   .decoupling_select = no_decoupling,

   .config_PMSM = config_PMSM,

   .config_id = config_id,

   .config_iq = config_iq

};

struct uz_SpeedControl_config config_speed = {

    .config_controller.Kp = 0.01f,

    .config_controller.Ki = 7.0f,

    .config_controller.samplingTime_sec = 1/SAMPLE_FREQUENCY,

    .config_controller.upper_limit = 10.0f,

    .config_controller.lower_limit = -10.0f,

    .config_PMSM.R_ph_Ohm = 0.140f,

    .config_PMSM.Ld_Henry = 0.001f,

    .config_PMSM.Lq_Henry = 0.001f,

    .config_PMSM.Psi_PM_Vs = 0.0f,

    .config_PMSM.polePairs = 2.0f,

    .config_PMSM.J_kg_m_squared = 1.0f,

    .config_PMSM.I_max_Ampere = 10.0f,

    .is_field_weakening_active = false

};

struct uz_IIR_Filter_config iir_config_filt1 = {
		.selection = LowPass_first_order,
		.cutoff_frequency_Hz = 500.0f,
		.sample_frequency_Hz = SAMPLE_FREQUENCY};

enum init_chain
{
    init_assertions = 0,
    init_gpios,
    init_software,
    init_ip_cores,
	init_foc,
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
            // Init Resolver --> Change settings of Resolver in uz_ResolverIp_init.c
            Global_Data.objects.resolver_IP = initialize_resolverIP_on_D4();
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);
            initialization_chain = init_foc;
            break;
        case init_foc:
        	Global_Data.objects.FOC_instance = uz_FOC_init(config_FOC);
            Global_Data.objects.Speed_instance = uz_SpeedControl_init(config_speed);
        	Global_Data.av.theta_offset = 3.1f; // have to be set with duty cycle on first phase
        	Global_Data.av.polepairs = 2.0f;
        	Global_Data.av.flg_speed_control = 0U;	// Set 1U for active speed control, 0U for current control
        	Global_Data.av.i_q_ref = 0.0f;
        	Global_Data.av.i_d_ref = 0.0f;
            Global_Data.objects.iir_u_dc = uz_signals_IIR_Filter_init(iir_config_filt1);
            Global_Data.objects.iir_i_u = uz_signals_IIR_Filter_init(iir_config_filt1);
            Global_Data.objects.iir_i_v = uz_signals_IIR_Filter_init(iir_config_filt1);
            Global_Data.objects.iir_i_w = uz_signals_IIR_Filter_init(iir_config_filt1);
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
