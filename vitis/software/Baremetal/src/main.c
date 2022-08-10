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
	.av.U_ZK = 36.0f,
	.av.theta_offset =  -0.14608003,
	.av.I_d_ref = 0,
	.av.I_q_ref = 0,
};


//fault detection:
uz_vsd_opf_fd_v7 uz_FD_v7;

uz_resonant_controller r_c_2H_x;
uz_resonant_controller r_c_2H_y;

//single Index FD:
uz_singleindex_faultdetection singleindex_FD;

struct uz_movAverageFilter_config movAvF_config;
uz_movAverageFilter_t* movAvFilter;

uz_movAverageFilter_t* movAvFilter_R1;
uz_movAverageFilter_t* movAvFilter_R2;
uz_movAverageFilter_t* movAvFilter_R3;
uz_movAverageFilter_t* movAvFilter_R4;
uz_movAverageFilter_t* movAvFilter_R5;
uz_movAverageFilter_t* movAvFilter_R6;


uz_filter_t* r_c_iir_2H_x;
uz_filter_t* r_c_iir_2H_y;

float r_c_filterParameterA[3] = {	1,
									-2*cos(0.0f*0.0001f),
									1};

float r_c_filterParameterB[3] = {	0.1f * (2.0f*M_PI*1000.0f)*(2.0f*M_PI*1000.0f)* 0.00004f*0.0001f*cos(2.0f*0.0f*0.0001f),
		0.1f * (2.0f*M_PI*1000.0f)*(2.0f*M_PI*1000.0f)* 0.00004f*0.0001f* -cos(0.0f*0.0001f),
									0.1f * (2.0f*M_PI*1000.0f)*(2.0f*M_PI*1000.0f)* 0.00004*0.0001f*0.0f};

float ar_circularBufferInput_2H_x[3]={0};
float ar_circularBufferInput_2H_y[3]={0};
float ar_circularBufferOutput_2H_x[3]={0};
float ar_circularBufferOutput_2H_y[3]={0};

struct uz_filter_config filter_config_rc_2H_x = {
	.filterLength = 3,
	.filterParameterA = r_c_filterParameterA,
	.filterParameterB = r_c_filterParameterB,
	.circularBufferInput = ar_circularBufferInput_2H_x,
	.circularBufferOutput = ar_circularBufferOutput_2H_x
};

struct uz_filter_config filter_config_rc_2H_y = {
	.filterLength = 3,
	.filterParameterA = r_c_filterParameterA,
	.filterParameterB = r_c_filterParameterB,
	.circularBufferInput = ar_circularBufferInput_2H_y,
	.circularBufferOutput = ar_circularBufferOutput_2H_y
};


#define FILTER_LENGTH 11

uz_filter_t* filter_a1;
uz_filter_t* filter_b1;
uz_filter_t* filter_c1;
uz_filter_t* filter_a2;
uz_filter_t* filter_b2;
uz_filter_t* filter_c2;

float ar_filterParameterA[FILTER_LENGTH] = {   1,
		  -8.795170347593165516286717320326715707779,
		  34.87498281940548139345992240123450756073 ,
		 -82.095896845589493295847205445170402526855,
		 127.042943858755734254373237490653991699219,
		-135.035542883992434326501097530126571655273,
		  99.835079040061941668682266026735305786133,
		 -50.691818433648244024425366660580039024353,
		  16.916722791727497821057113469578325748444,
		  -3.350305445143596738688529512728564441204,
		   0.299005477912280381858067812572699040174};

float ar_filterParameterB[FILTER_LENGTH] = {0.000000000031148454939792163363898700541,
		0.00000000031148454939792164656368407655    ,
		0.000000001401680472290647254440213490781   ,
		0.000000003737814592775059345173902642084   ,
		0.000000006541175537356353440464023347133   ,
		0.000000007849410644827625452045808101403   ,
		0.00000000654117553735635426764463590016    ,
		0.000000003737814592775059345173902642084   ,
		0.000000001401680472290647461235366629038   ,
		0.00000000031148454939792164656368407655    ,
		0.000000000031148454939792163363898700541 };


float ar_circularBufferInput_a1[FILTER_LENGTH] = {0};
float ar_circularBufferOutput_a1[FILTER_LENGTH] = {0};
float ar_circularBufferInput_b1[FILTER_LENGTH] = {0};
float ar_circularBufferOutput_b1[FILTER_LENGTH] = {0};
float ar_circularBufferInput_c1[FILTER_LENGTH] = {0};
float ar_circularBufferOutput_c1[FILTER_LENGTH] = {0};
float ar_circularBufferInput_a2[FILTER_LENGTH] = {0};
float ar_circularBufferOutput_a2[FILTER_LENGTH] = {0};
float ar_circularBufferInput_b2[FILTER_LENGTH] = {0};
float ar_circularBufferOutput_b2[FILTER_LENGTH] = {0};
float ar_circularBufferInput_c2[FILTER_LENGTH] = {0};
float ar_circularBufferOutput_c2[FILTER_LENGTH] = {0};

struct uz_filter_config filter_config_a1 = {
	.filterLength = FILTER_LENGTH,
	.filterParameterA = ar_filterParameterA,
	.filterParameterB = ar_filterParameterB,
	.circularBufferInput = ar_circularBufferInput_a1,
	.circularBufferOutput = ar_circularBufferOutput_a1
};

struct uz_filter_config filter_config_b1 = {
	.filterLength = FILTER_LENGTH,
	.filterParameterA = ar_filterParameterA,
	.filterParameterB = ar_filterParameterB,
	.circularBufferInput = ar_circularBufferInput_b1,
	.circularBufferOutput = ar_circularBufferOutput_b1
};

struct uz_filter_config filter_config_c1 = {
	.filterLength = FILTER_LENGTH,
	.filterParameterA = ar_filterParameterA,
	.filterParameterB = ar_filterParameterB,
	.circularBufferInput = ar_circularBufferInput_c1,
	.circularBufferOutput = ar_circularBufferOutput_c1
};

struct uz_filter_config filter_config_a2 = {
	.filterLength = FILTER_LENGTH,
	.filterParameterA = ar_filterParameterA,
	.filterParameterB = ar_filterParameterB,
	.circularBufferInput = ar_circularBufferInput_a2,
	.circularBufferOutput = ar_circularBufferOutput_a2
};

struct uz_filter_config filter_config_b2 = {
	.filterLength = FILTER_LENGTH,
	.filterParameterA = ar_filterParameterA,
	.filterParameterB = ar_filterParameterB,
	.circularBufferInput = ar_circularBufferInput_b2,
	.circularBufferOutput = ar_circularBufferOutput_b2
};

struct uz_filter_config filter_config_c2 = {
	.filterLength = FILTER_LENGTH,
	.filterParameterA = ar_filterParameterA,
	.filterParameterB = ar_filterParameterB,
	.circularBufferInput = ar_circularBufferInput_c2,
	.circularBufferOutput = ar_circularBufferOutput_c2
};


//parameter for FOC






struct uz_FOC* FOC_dq;

const struct uz_PMSM_t config_PMSM = {
   .Ld_Henry = 0.0001f,			//Richtige Parameter f�r den Motor einf�gen
   .Lq_Henry = 0.0002f,
   .Psi_PM_Vs = 0.008f,
   .R_ph_Ohm = 0.0f,
   .polePairs = 5.0f,
   .J_kg_m_squared = 0.0f,
   .I_max_Ampere = 10.0f
};


const struct uz_PI_Controller_config config_id = {
	.Kp = 0.2f,//1.1f,										//nach Betragsoptimum:  Kp = Tn/(2*Ks*T_sw) mit Tn = L/R, T_sw = 1/f_sw (10kHz), Ks = 1/R
	.Ki = 1/0.0008f *0.1,															 // Ki = 1/Tn
	.samplingTime_sec = 0.0001f,
	.upper_limit = 10.0f,
	.lower_limit = -10.0f
};


const struct uz_PI_Controller_config config_iq = {
	.Kp = 0.2f, //1.1f,
	.Ki = 1/0.0008f *0.1,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 10.0f,
	.lower_limit = -10.0f
};

struct uz_FOC_config config_FOC = {
   .decoupling_select = no_decoupling,
   .config_PMSM = config_PMSM,
   .config_id = config_id,
   .config_iq = config_iq
};


const struct uz_PI_Controller_config config_idn = {
	.Kp = 0.05f,//1.1f,
	.Ki = 1/0.0008f * 0.005f,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 10.0f,
	.lower_limit = -10.0f
};

const struct uz_PI_Controller_config config_iqn = {
	.Kp = 0.05f,//1.1f,
	.Ki = 1/0.0008f * 0.005f,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 10.0f,
	.lower_limit = -10.0f
};

struct uz_PI_Controller* PI_d_n;
struct uz_PI_Controller* PI_q_n;





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


const struct uz_PI_Controller_config config_ix = {
	.Kp = 0.05f , //* 4.0f, //1.1f,
	.Ki = 1/0.0008f *0.005f,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 15.0f,
	.lower_limit = -15.0f
};

const struct uz_PI_Controller_config config_iy = {
	.Kp = 0.05f, //* 4.0f,//1.1f,
	.Ki = 1/0.0008f *0.005f,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 15.0f,
	.lower_limit = -15.0f
};

struct uz_PI_Controller* PI_x_s;
struct uz_PI_Controller* PI_x_n;
struct uz_PI_Controller* PI_y_s;
struct uz_PI_Controller* PI_y_n;

const struct uz_PI_Controller_config config_iz1 = {
	.Kp = 0.05*0.1f , //* 4.0f, //1.1f,
	.Ki = 1/0.0008f *0.001f,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 15.0f,
	.lower_limit = -15.0f
};

const struct uz_PI_Controller_config config_iz2 = {
	.Kp = 0.05*0.1f , //* 4.0f,//1.1f,
	.Ki = 1/0.0008f *0.001f,
	.samplingTime_sec = 0.0001f,
	.upper_limit = 15.0f,
	.lower_limit = -15.0f
};

struct uz_PI_Controller* PI_z1_s;
struct uz_PI_Controller* PI_z1_n;
struct uz_PI_Controller* PI_z2_s;
struct uz_PI_Controller* PI_z2_n;



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
            movAvFilter = uz_movAverageFilter_init(movAvF_config);

            movAvFilter_R1 =  uz_movAverageFilter_init(movAvF_config);
            movAvFilter_R2 =  uz_movAverageFilter_init(movAvF_config);
            movAvFilter_R3 =  uz_movAverageFilter_init(movAvF_config);
            movAvFilter_R4 =  uz_movAverageFilter_init(movAvF_config);
            movAvFilter_R5 =  uz_movAverageFilter_init(movAvF_config);
            movAvFilter_R6 =  uz_movAverageFilter_init(movAvF_config);


            filter_a1 = uz_filter_init(filter_config_a1);
            filter_b1 = uz_filter_init(filter_config_b1);
            filter_c1 = uz_filter_init(filter_config_c1);
            filter_a2 = uz_filter_init(filter_config_a2);
            filter_b2 = uz_filter_init(filter_config_b2);
            filter_c2 = uz_filter_init(filter_config_c2);

            // Resonant-Controller in c (IIR-Filter)
            r_c_iir_2H_x = uz_filter_init(filter_config_rc_2H_x);
			r_c_iir_2H_y = uz_filter_init(filter_config_rc_2H_y);

			// Matlab Resonant Controller
            uz_resonant_controller_init(&r_c_2H_x);
            uz_resonant_controller_init(&r_c_2H_y);

            initialization_chain = init_FOC;
            break;
        case init_FOC:

        	FOC_dq = uz_FOC_init(config_FOC);

        	PI_d_n = uz_PI_Controller_init(config_idn);
			PI_q_n = uz_PI_Controller_init(config_iqn);

        	Global_Data.av.kp_d = config_FOC.config_id.Kp;
        	Global_Data.av.ki_d = config_FOC.config_id.Ki;
        	Global_Data.av.kp_q = config_FOC.config_iq.Kp;
        	Global_Data.av.ki_q = config_FOC.config_iq.Ki;


        	PI_x_s = uz_PI_Controller_init(config_ix);
        	PI_x_n = uz_PI_Controller_init(config_ix);
        	PI_y_s = uz_PI_Controller_init(config_iy);
        	PI_y_n = uz_PI_Controller_init(config_iy);


        	PI_z1_s = uz_PI_Controller_init(config_iz1);
        	PI_z1_n = uz_PI_Controller_init(config_iz1);
        	PI_z2_s = uz_PI_Controller_init(config_iz2);
        	PI_z2_n = uz_PI_Controller_init(config_iz2);


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
