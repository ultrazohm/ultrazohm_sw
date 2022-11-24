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
		.halfBridge12DutyCycle = 0.0f,
		.ref_halfBridge1DutyCycle = 0.0f,
		.ref_halfBridge2DutyCycle = 0.0f,
		.ref_halfBridge3DutyCycle = 0.0f,
		.ref_halfBridge4DutyCycle = 0.0f,
		.ref_halfBridge5DutyCycle = 0.0f,
		.ref_halfBridge6DutyCycle = 0.0f,
		.ref_halfBridge7DutyCycle = 0.0f,
		.ref_halfBridge8DutyCycle = 0.0f,
		.ref_halfBridge9DutyCycle = 0.0f,
		.ref_halfBridge10DutyCycle = 0.0f,
		.ref_halfBridge11DutyCycle = 0.0f,
		.ref_halfBridge12DutyCycle= 0.0f
    },
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
    	   .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
		   .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}
    },
	.av.U_ZK = 48.0f,
	.av.theta_offset =  1.120014f,
	.av.i_d_ref = 0,
	.av.i_q_ref = 0
};




uz_resonantController_t* rc_2H_x;
uz_resonantController_t* rc_2H_y;
uz_resonantController_t* rc_6H_x;
uz_resonantController_t* rc_6H_y;
uz_resonantController_t* rc_2H_d;
uz_resonantController_t* rc_2H_q;
uz_resonantController_t* rc_12H_d;
uz_resonantController_t* rc_12H_q;

uz_resonantController_t* rc_1H_z1;
uz_resonantController_t* rc_1H_z2;
uz_resonantController_t* rc_3H_z1;
uz_resonantController_t* rc_3H_z2;
uz_resonantController_t* rc_9H_z1;
uz_resonantController_t* rc_9H_z2;


const struct uz_resonantController_config config_R = {
		.sampling_time = 0.0001f,
		.gain = 1000.0f,
		.harmonic_order = 2.0f,
		.fundamental_frequency = 10.0f,
		.lower_limit = -40.0f,
		.upper_limit = 40.0f,
		.antiwindup_gain = 10.0f,
		.in_reference_value = 0.0f,
		.in_measured_value = 0.0f,
};


struct uz_movingAverageFilter_config movAvF_config;

uz_movingAverageFilter_t* movAvFilter_R1;
uz_movingAverageFilter_t* movAvFilter_R2;
uz_movingAverageFilter_t* movAvFilter_R3;
uz_movingAverageFilter_t* movAvFilter_R4;
uz_movingAverageFilter_t* movAvFilter_R5;
uz_movingAverageFilter_t* movAvFilter_R6;









struct uz_IIR_Filter_config iir_config_dc_volts = {
		.selection = LowPass_first_order,
		.cutoff_frequency_Hz = 1.0f,
		.sample_frequency_Hz = 10000.0f};

struct uz_IIR_Filter_config iir_config_currents = {
		.selection = LowPass_first_order,
		.cutoff_frequency_Hz = 500.0f,
		.sample_frequency_Hz = 10000.0f};

struct uz_IIR_Filter_config iir_config_rpm_ref = {
		.selection = LowPass_first_order,
		.cutoff_frequency_Hz = 10.0f,
		.sample_frequency_Hz = 10000.0f};

const struct uz_PMSM_t config_PMSM = {
	.R_ph_Ohm = 0.2f,
   .Ld_Henry = 0.0001f,
   .Lq_Henry = 0.0001f,
   .Psi_PM_Vs = 0.008f,
   .polePairs = 5.0f,
   .I_max_Ampere = 10.0f
 };//these parameters are only needed if linear decoupling is selected


const struct uz_PI_Controller_config config_id = {
   .Kp = 6.0f, //4.0f, //6.0f, //2.5f,
   .Ki = 20.0f, //20.0f, //200.0f,
   .samplingTime_sec = 0.0001f,
   .upper_limit = 326.0f,
   .lower_limit = -326.0f
};
const struct uz_PI_Controller_config config_iq = {
   .Kp = 6.0f, //4.0f, //6.0f, //2.5f,
   .Ki = 20.0f, //20.0f, //200.0f,
   .samplingTime_sec = 0.0001f,
   .upper_limit = 326.0f,
   .lower_limit = -326.0f
};
struct uz_FOC_config config_FOC = {
   .decoupling_select = no_decoupling,
   .config_PMSM = config_PMSM,
   .config_id = config_id,
   .config_iq = config_iq
};

struct uz_SpeedControl_config config_speed = {
   .config_controller.Kp = 0.1f,
   .config_controller.Ki = 5.0f,
   .config_controller.samplingTime_sec = 0.0001f,
   .config_controller.upper_limit = 8.0f,
   .config_controller.lower_limit = -8.0f,
   .enable_field_weakening = false
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////

// alphabeta -> dq & reverse
void uz_park_transform(float* output, float* input, float theta_el_rad)
{
    float sin_coefficient = sinf(theta_el_rad);
    float cos_coefficient = cosf(theta_el_rad);
    output[0] = ( cos_coefficient * input[0]) + (sin_coefficient * input[1]);
    output[1] =	(-sin_coefficient * input[0]) + (cos_coefficient * input[1]);
}

void uz_inv_park_transform(float* output, float* input, float theta_el_rad)
{
    float sin_coefficient = sinf(theta_el_rad);
    float cos_coefficient = cosf(theta_el_rad);
    output[0] = (cos_coefficient * input[0]) - (sin_coefficient * input[1]);
    output[1] = (sin_coefficient * input[0]) + (cos_coefficient * input[1]);
}

struct uz_PI_Controller* PI_x_n;
struct uz_PI_Controller* PI_y_n;
struct uz_PI_Controller* PI_z1;
struct uz_PI_Controller* PI_z2;

const struct uz_PI_Controller_config config_ix = {
	.Kp = 5.0f, //0.18f ,
	.Ki = 15, //880, //1/0.0008f *0.005f,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 50.0f,
	.lower_limit = -50.0f
};

const struct uz_PI_Controller_config config_iy = {
	.Kp = 5.0f, //0.14, //0.18f, //* 4.0f,//1.1f,
	.Ki = 15, //880, //1/0.0008f *0.005f,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 50.0f,
	.lower_limit = -50.0f
};

const struct uz_PI_Controller_config config_iz1z2 = {
	.Kp = 2.0f, //0.14, //0.18f , //* 4.0f,//1.1f,
	.Ki = 0,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 50.0f,
	.lower_limit = -50.0f
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

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
            Global_Data.objects.iir_i_a2 = uz_signals_IIR_Filter_init(iir_config_currents);
            Global_Data.objects.iir_i_b2 = uz_signals_IIR_Filter_init(iir_config_currents);
            Global_Data.objects.iir_i_c2 = uz_signals_IIR_Filter_init(iir_config_currents);
            Global_Data.objects.iir_rpm_ref = uz_signals_IIR_Filter_init(iir_config_rpm_ref);
            Global_Data.av.theta_offset = 1.120014f;
            Global_Data.av.polepairs = 5.0f;
            Global_Data.objects.foc_current = uz_FOC_init(config_FOC);
            Global_Data.objects.foc_speed = uz_SpeedControl_init(config_speed);


			movAvFilter_R1 =  uz_movingAverageFilter_init(movAvF_config);
			movAvFilter_R2 =  uz_movingAverageFilter_init(movAvF_config);
			movAvFilter_R3 =  uz_movingAverageFilter_init(movAvF_config);
			movAvFilter_R4 =  uz_movingAverageFilter_init(movAvF_config);
			movAvFilter_R5 =  uz_movingAverageFilter_init(movAvF_config);
			movAvFilter_R6 =  uz_movingAverageFilter_init(movAvF_config);

            struct uz_resonantController_config config_R_dq2H = config_R;
            config_R_dq2H.harmonic_order = 2.0f;
            config_R_dq2H.upper_limit = 50.0f;
            config_R_dq2H.lower_limit = -50.0f;
            struct uz_resonantController_config config_R_dq8H = config_R;
            config_R_dq8H.harmonic_order = 8.0f;
            struct uz_resonantController_config config_R_dq12H = config_R;
            config_R_dq12H.harmonic_order = 12.0f;
            struct uz_resonantController_config config_R_xy2H = config_R;
            config_R_xy2H.harmonic_order = 2.0f;
            struct uz_resonantController_config config_R_xy6H = config_R;
            config_R_xy6H.harmonic_order = 6.0f;
            struct uz_resonantController_config config_R_z1z2_1H = config_R;
            config_R_z1z2_1H.harmonic_order = 1.0f;
            struct uz_resonantController_config config_R_z1z2_3H = config_R;
            config_R_z1z2_3H.harmonic_order = 3.0f;
            struct uz_resonantController_config config_R_z1z2_9H = config_R;
            config_R_z1z2_9H.harmonic_order = 9.0f;

            rc_2H_x = uz_resonantController_init(config_R_xy2H);
            rc_2H_y = uz_resonantController_init(config_R_xy2H);
            rc_6H_x = uz_resonantController_init(config_R_xy6H);
            rc_6H_y = uz_resonantController_init(config_R_xy6H);
            rc_2H_d = uz_resonantController_init(config_R_dq2H);
            rc_2H_q = uz_resonantController_init(config_R_dq2H);
            rc_12H_d = uz_resonantController_init(config_R_dq12H);
            rc_12H_q = uz_resonantController_init(config_R_dq12H);
            rc_1H_z1 = uz_resonantController_init(config_R_z1z2_1H);
            rc_1H_z2 = uz_resonantController_init(config_R_z1z2_1H);
            rc_3H_z1 = uz_resonantController_init(config_R_z1z2_3H);
            rc_3H_z2 = uz_resonantController_init(config_R_z1z2_3H);
            rc_9H_z1 = uz_resonantController_init(config_R_z1z2_9H);
            rc_9H_z2 = uz_resonantController_init(config_R_z1z2_9H);

        	PI_x_n = uz_PI_Controller_init(config_ix);
        	PI_y_n = uz_PI_Controller_init(config_iy);
        	PI_z1 = uz_PI_Controller_init(config_iz1z2);
        	PI_z2 = uz_PI_Controller_init(config_iz1z2);



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
