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
    	   //.A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
    		.A2 = {.cf.ADC_A1 = 150.875f, .cf.ADC_A2 = 33.8780*2, .cf.ADC_A3 = 33.8780*2, .cf.ADC_A4 = 33.8780*2, .cf.ADC_B5 = 150.875, .cf.ADC_B6 = 33.8780*2, .cf.ADC_B7 = 33.8780*2, .cf.ADC_B8 = 33.8780*2}, //@ 2*18mOhm shunts in parallel

    		.A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}
    },
	.av.U_ZK = 48.0f,
	.av.theta_offset =  1.05, //-0.14608003 + 0.623,
	.av.I_d_ref = 0,
	.av.I_q_ref = 0,
};


//fault detection:
uz_vsd_opf_fd_v7 uz_FD_v7;


uz_resonantController_t* rc_2H_x;
uz_resonantController_t* rc_2H_y;
uz_resonantController_t* rc_6H_x;
uz_resonantController_t* rc_6H_y;
uz_resonantController_t* rc_2H_d;
uz_resonantController_t* rc_2H_q;
uz_resonantController_t* rc_8H_d;
uz_resonantController_t* rc_8H_q;
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
		.gain = 52.5f,
		.harmonic_order = 2.0f,
		.fundamental_frequency = 10.0f,
		.lower_limit = -4.0f,
		.upper_limit = 4.0f,
		.antiwindup_gain = 10.0f,
		.in_reference_value = 0.0f,
		.in_measured_value = 0.0f,
		.reset = 0.0f
};





//single Index FD:
uz_singleindex_faultdetection singleindex_FD;

struct uz_movingAverageFilter_config movAvF_config;
uz_movingAverageFilter_t* movAvFilter;

uz_movingAverageFilter_t* movAvFilter_R1;
uz_movingAverageFilter_t* movAvFilter_R2;
uz_movingAverageFilter_t* movAvFilter_R3;
uz_movingAverageFilter_t* movAvFilter_R4;
uz_movingAverageFilter_t* movAvFilter_R5;
uz_movingAverageFilter_t* movAvFilter_R6;

uz_movingAverageFilter_t* movAvFilter_temp1;
uz_movingAverageFilter_t* movAvFilter_temp2;
uz_movingAverageFilter_t* movAvFilter_temp3;
uz_movingAverageFilter_t* movAvFilter_temp4;
uz_movingAverageFilter_t* movAvFilter_temp5;


//parameter for FOC

struct uz_FOC* FOC_dq;

const struct uz_PMSM_t config_PMSM = {
   .Ld_Henry = 0.0001473f,			//Richtige Parameter f�r den Motor einf�gen
   .Lq_Henry = 0.0001484f,
   .Psi_PM_Vs = 0.0048f,
   .R_ph_Ohm = 0.1278f,
   .polePairs = 5.0f,
   .J_kg_m_squared = 0.0f,
   .I_max_Ampere = 25.0f
};


const struct uz_PI_Controller_config config_id = {
	.Kp = 0.37, //0.37, //0.5, //0.6, //0.75, //1.125f, //0.2f,//1.1f,										//nach Betragsoptimum:  Kp = Tn/(2*Ks*T_sw) mit Tn = L/R, T_sw = 1/f_sw (10kHz), Ks = 1/R
	.Ki = 880, //770, //1/0.0008f *0.1,															 // Ki = 1/Tn *Kp ( * Kp da wir eine Parallelform haben)
	.samplingTime_sec = 0.0001f,
	.upper_limit = 15.0f,
	.lower_limit = -15.0f
};

const struct uz_PI_Controller_config config_iq = {
	.Kp = 0.37, //0.37, //0.5, //0.6, //0.75, //1.125f, //0.2f, //1.1f,
	.Ki = 880, //770, //1/0.0008f *0.1,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 15.0f,
	.lower_limit = -15.0f
};

struct uz_FOC_config config_FOC = {
   .decoupling_select = linear_decoupling, // no_decoupling, linear_decoupling
   .config_PMSM = config_PMSM,
   .config_id = config_id,
   .config_iq = config_iq
};


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
	.Kp = 0.18f , //* 4.0f, //1.1f,
	.Ki = 880, //880, //1/0.0008f *0.005f,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 15.0f,
	.lower_limit = -15.0f
};

const struct uz_PI_Controller_config config_iy = {
	.Kp = 0.14, //0.18f, //* 4.0f,//1.1f,
	.Ki = 880, //880, //1/0.0008f *0.005f,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 15.0f,
	.lower_limit = -15.0f
};

const struct uz_PI_Controller_config config_iz1z2 = {
	.Kp = 0.14, //0.18f , //* 4.0f,//1.1f,
	.Ki = 0,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 15.0f,
	.lower_limit = -15.0f
};





struct uz_d_gan_inverter_t* gan_inverter_D3;
struct uz_d_gan_inverter_t* gan_inverter_D4;

struct uz_d_gan_inverter_config_t config_gan_inverter_D3 = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_UZ_D_GAN_INVERTER_1_UZ_D_GAN_INVERTER_0_BASEADDR,
    .ip_clk_frequency_Hz = 100000
};

struct uz_d_gan_inverter_config_t config_gan_inverter_D4 = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_UZ_D_GAN_INVERTER_UZ_D_GAN_INVERTER_0_BASEADDR,
    .ip_clk_frequency_Hz = 100000
};






enum init_chain
{
    init_assertions = 0,
    init_gpios,
    init_software,
	init_FD,
	init_FOC,
    init_ip_cores,
    print_msg,
    init_interrupts,
    infinite_loop
};
enum init_chain initialization_chain = init_assertions;

int main(void)
{

	movAvF_config.filterLength = 150;


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
            initialization_chain = init_FD;
            break;
        case init_FD:


            uz_vsd_opf_fd_v7_init(&uz_FD_v7);

            uz_singleindex_faultdetection_init(&singleindex_FD);
            movAvFilter = uz_movingAverageFilter_init(movAvF_config);

            movAvFilter_R1 =  uz_movingAverageFilter_init(movAvF_config);
            movAvFilter_R2 =  uz_movingAverageFilter_init(movAvF_config);
            movAvFilter_R3 =  uz_movingAverageFilter_init(movAvF_config);
            movAvFilter_R4 =  uz_movingAverageFilter_init(movAvF_config);
            movAvFilter_R5 =  uz_movingAverageFilter_init(movAvF_config);
            movAvFilter_R6 =  uz_movingAverageFilter_init(movAvF_config);

            movAvFilter_temp1 =  uz_movingAverageFilter_init(movAvF_config);
            movAvFilter_temp2 =  uz_movingAverageFilter_init(movAvF_config);
            movAvFilter_temp3 =  uz_movingAverageFilter_init(movAvF_config);
            movAvFilter_temp4 =  uz_movingAverageFilter_init(movAvF_config);
            movAvFilter_temp5 =  uz_movingAverageFilter_init(movAvF_config);

            // all configs for the resonant controllers

            struct uz_resonantController_config config_R_dq2H = config_R;
            config_R_dq2H.harmonic_order = 2.0f;
            config_R_dq2H.gain = 125.0f;
            config_R_dq2H.upper_limit = 8.0f;
            config_R_dq2H.lower_limit = -8.0f;
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
            rc_8H_d = uz_resonantController_init(config_R_dq8H);
            rc_8H_q = uz_resonantController_init(config_R_dq8H);
            rc_12H_d = uz_resonantController_init(config_R_dq12H);
            rc_12H_q = uz_resonantController_init(config_R_dq12H);
            rc_1H_z1 = uz_resonantController_init(config_R_z1z2_1H);
            rc_1H_z2 = uz_resonantController_init(config_R_z1z2_1H);
            rc_3H_z1 = uz_resonantController_init(config_R_z1z2_3H);
            rc_3H_z2 = uz_resonantController_init(config_R_z1z2_3H);
            rc_9H_z1 = uz_resonantController_init(config_R_z1z2_9H);
            rc_9H_z2 = uz_resonantController_init(config_R_z1z2_9H);

/*
			// Matlab Resonant Controller
            uz_resonantController_init(&rc_2H_x);
            uz_resonantController_init(&rc_2H_y);
            uz_resonantController_init(&rc_6H_x);
            uz_resonantController_init(&rc_6H_y);
            uz_resonantController_init(&rc_2H_d);
            uz_resonantController_init(&rc_2H_q);
            uz_resonantController_init(&rc_8H_d);
            uz_resonantController_init(&rc_8H_q);
            uz_resonantController_init(&rc_12H_d);
            uz_resonantController_init(&rc_12H_q);

            uz_resonantController_init(&rc_1H_z1);
            uz_resonantController_init(&rc_1H_z2);
            uz_resonantController_init(&rc_3H_z1);
            uz_resonantController_init(&rc_3H_z2);
            uz_resonantController_init(&rc_9H_z1);
            uz_resonantController_init(&rc_9H_z2);
*/

            initialization_chain = init_FOC;
            break;
        case init_FOC:

        	FOC_dq = uz_FOC_init(config_FOC);

        	Global_Data.av.kp_d = config_FOC.config_id.Kp;
        	Global_Data.av.ki_d = config_FOC.config_id.Ki;
        	Global_Data.av.kp_q = config_FOC.config_iq.Kp;
        	Global_Data.av.ki_q = config_FOC.config_iq.Ki;

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
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);



            gan_inverter_D3 = uz_d_gan_inverter_init(config_gan_inverter_D3, Global_Data.objects.gan_inverter_outputs_D3);
            gan_inverter_D4 = uz_d_gan_inverter_init(config_gan_inverter_D4, Global_Data.objects.gan_inverter_outputs_D4);




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
