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
        .halfBridge3DutyCycle = 0.0f
    },
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
    	   .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
		   .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}
    }
};


//upper code for PMSM
#include "IP_Cores/uz_pmsm_model_9ph/uz_pmsm_model_9ph.h"
#include "uz/uz_piController/uz_piController.h"
#include "xparameters.h"
uz_pmsm_model_9ph_t *pmsm=NULL;
uz_PI_Controller *PI_d_current=NULL;
uz_PI_Controller *PI_q_current=NULL;
uz_PI_Controller *PI_rpm=NULL;
struct uz_pmsm_model_9ph_config_t pmsm_config={
              .base_address=XPAR_UZ_USER_UZ_PMSM_MODEL_9PH_0_BASEADDR,
              .ip_core_frequency_Hz=100000000,
              .simulate_mechanical_system = false,
              .r_1 = 31.3f,
              .L_d = 0.5f,
              .L_q = 0.5f,
              .L_z1 = 0.08f,
              .L_z2 = 0.08f,
              .L_x1 = 0.08f,
              .L_y1 = 0.08f,
              .L_x2 = 0.08f,
              .L_y2 = 0.08f,
              .L_z3 = 0.08f,
              .psi_pm = 0.6f,
              .polepairs = 2.0f,
              .inertia = 0.001,
              .coulomb_friction_constant = 0.001f,
              .friction_coefficient = 0.001f,
			  .control_dq_abc = false,
			  .switch_pspl = false};

struct uz_PI_Controller_config config = {
              .Kp = 1250.0f,
              .Ki = 78250.0f,
              .samplingTime_sec = 0.0001f,
              .upper_limit = 280.0f,
              .lower_limit = -280.0f};
//end

// upper code for PWM
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
struct uz_PWM_SS_2L_config_t pwm_config_1 = {
        .base_address= XPAR_UZ_USER_PWM_AND_SS_CONTROL_V_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = 10e3f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = true,
        .init_dutyCyc_A = 0.0f,
        .init_dutyCyc_B = 0.0f,
        .init_dutyCyc_C = 0.0f
};

struct uz_PWM_SS_2L_config_t pwm_config_2 = {
        .base_address= XPAR_UZ_USER_PWM_AND_SS_CONTROL_V_1_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = 10e3f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = true,
        .init_dutyCyc_A = 0.0f,
        .init_dutyCyc_B = 0.0f,
        .init_dutyCyc_C = 0.0f
};

struct uz_PWM_SS_2L_config_t pwm_config_3 = {
        .base_address= XPAR_UZ_USER_PWM_AND_SS_CONTROL_V_2_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = 10e3f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = true,
        .init_dutyCyc_A = 0.0f,
        .init_dutyCyc_B = 0.0f,
        .init_dutyCyc_C = 0.0f
};

uz_PWM_SS_2L_t *pwm_instance_1=NULL;
uz_PWM_SS_2L_t *pwm_instance_2=NULL;
uz_PWM_SS_2L_t *pwm_instance_3=NULL;

//end

//upper code for inverter
#include "IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"

struct uz_inverter_3ph_config_t inverter_1_config = {
		.base_address= XPAR_UZ_USER_UZ_INVERTER_3PH_0_BASEADDR,
		.ip_core_frequency_Hz= 100000000,
		.switch_pspl_abc=false,
		.switch_pspl_gate=false,
		.udc=560.0f
};

struct uz_inverter_3ph_config_t inverter_2_config = {
		.base_address= XPAR_UZ_USER_UZ_INVERTER_3PH_1_BASEADDR,
		.ip_core_frequency_Hz= 100000000,
		.switch_pspl_abc=false,
		.switch_pspl_gate=false,
		.udc=560.0f
};

struct uz_inverter_3ph_config_t inverter_3_config = {
		.base_address= XPAR_UZ_USER_UZ_INVERTER_3PH_2_BASEADDR,
		.ip_core_frequency_Hz= 100000000,
		.switch_pspl_abc=false,
		.switch_pspl_gate=false,
		.udc=560.0f
};

struct uz_inverter_3ph_t *inverter_1=NULL;
struct uz_inverter_3ph_t *inverter_2=NULL;
struct uz_inverter_3ph_t *inverter_3=NULL;

//end

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
            initialization_chain = init_ip_cores;
            break;
        case init_ip_cores:
            uz_adcLtc2311_ip_core_init();
            Global_Data.objects.deadtime_interlock_d1 = uz_interlockDeadtime2L_staticAllocator_slotD1();
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1, true);
            Global_Data.objects.pwm_d1 = initialize_pwm_2l_on_D1();
            Global_Data.objects.mux_axi = initialize_uz_mux_axi();
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            //loop code for PMSM
            pmsm = uz_pmsm_model_9ph_init(pmsm_config);
            uz_pmsm_model_9ph_reset(pmsm);
            PI_d_current = uz_PI_Controller_init(config);
            PI_q_current = uz_PI_Controller_init(config);
            PI_rpm = uz_PI_Controller_init(config);

            pwm_instance_1 = uz_PWM_SS_2L_init(pwm_config_1);
            pwm_instance_2 = uz_PWM_SS_2L_init(pwm_config_2);
			pwm_instance_3 = uz_PWM_SS_2L_init(pwm_config_3);

			inverter_1 = uz_inverter_3ph_init(inverter_1_config);
			inverter_2 = uz_inverter_3ph_init(inverter_2_config);
			inverter_3 = uz_inverter_3ph_init(inverter_3_config);
            //end
            initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);
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
