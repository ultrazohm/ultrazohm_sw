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


//ParameterID Code
#include "uz/uz_ParameterID/uz_ParameterID_6ph.h"
#include "uz/uz_math_constants.h"
uz_ParameterID_6ph_t* ParameterID = NULL;
uz_ParameterID_Data_t ParaID_Data = { 0 };
//ParameterID end


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
	.av.theta_offset =  0.79,
	.av.I_d_ref = 0,
	.av.I_q_ref = 0,
};


float dataR1 [500] = {0};
uz_array_float_t circularBuffer_R1 = {
   .length = UZ_ARRAY_SIZE(dataR1),
   .data = &dataR1[0]
};
float dataR2 [500] = {0};
uz_array_float_t circularBuffer_R2 = {
   .length = UZ_ARRAY_SIZE(dataR2),
   .data = &dataR2[0]
};
float dataR3 [500] = {0};
uz_array_float_t circularBuffer_R3 = {
   .length = UZ_ARRAY_SIZE(dataR3),
   .data = &dataR3[0]
};
float dataR4 [500] = {0};
uz_array_float_t circularBuffer_R4 = {
   .length = UZ_ARRAY_SIZE(dataR4),
   .data = &dataR4[0]
};
float dataR5 [500] = {0};
uz_array_float_t circularBuffer_R5 = {
   .length = UZ_ARRAY_SIZE(dataR5),
   .data = &dataR5[0]
};
float dataR6 [500] = {0};
uz_array_float_t circularBuffer_R6 = {
   .length = UZ_ARRAY_SIZE(dataR6),
   .data = &dataR6[0]
};





// Gan-Inverter:-----------------------------

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




// Init: --------------------------------------

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
        	ParameterID = uz_ParameterID_6ph_init(&ParaID_Data);
            Initialize_Timer();
            uz_SystemTime_init();
            JavaScope_initalize(&Global_Data);
            initialization_chain = init_FD;
            break;
        case init_FD:
            initialization_chain = init_FOC;
            break;
        case init_FOC:





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
