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
struct uz_PMSM_t config_PMSM = {
            		.R_ph_Ohm = 0.543f,
            		.Ld_Henry = 1.13e-03f,
					.Lq_Henry = 1.42e-03f,
					.Psi_PM_Vs = 0.0169f,
					.polePairs = 3.0f,
					.J_kg_m_squared = 1.48e-05f,
					.I_max_Ampere = 5.0f,
};
// config structs neural network
// read in weights and bias from .csv
float x[NUMBER_OF_INPUTS] = {0};
static float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
	#include "ac_layer1_weights.csv"
};

static float b_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
	#include "ac_layer1_bias.csv"
};

static float y_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float w_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
	#include "ac_layer_out_weights.csv"
};
static float b_2[NUMBER_OF_OUTPUTS] = {
	#include "ac_layer_out_bias.csv"
};
static float y_2[NUMBER_OF_OUTPUTS] = {0};

// initialize config struct and activation function
struct uz_nn_layer_config config[3] = {
[0] = {
    .activation_function = activation_ReLU,
    .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .number_of_inputs = NUMBER_OF_INPUTS,
    .length_of_weights = UZ_MATRIX_SIZE(w_1),
    .length_of_bias = UZ_MATRIX_SIZE(b_1),
    .length_of_output = UZ_MATRIX_SIZE(y_1),
    .weights = w_1,
    .bias = b_1,
    .output = y_1},
[1] = {
	.activation_function = activation_tanh,
    .number_of_neurons = NUMBER_OF_OUTPUTS,
    .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .length_of_weights = UZ_MATRIX_SIZE(w_2),
    .length_of_bias = UZ_MATRIX_SIZE(b_2),
    .length_of_output = UZ_MATRIX_SIZE(y_2),
    .weights = w_2,
    .bias = b_2,
    .output = y_2}
};

struct uz_matrix_t input_matrix={0};


enum init_chain
{
    init_assertions = 0,
    init_gpios,
    init_software,
	init_nn,
	init_FOC,
	init_PMSM_IP_Core,
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
            initialization_chain = init_nn;
            break;
        case init_nn:
            Global_Data.objects.matrix_input=uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1,NUMBER_OF_INPUTS);
            Global_Data.objects.nn_layer = uz_nn_init(config, 2);
        	initialization_chain = init_FOC;
        	break;
        case init_FOC:;
        	struct uz_PI_Controller_config config_id = {
        			.Kp = 3.767f, // 0.5f
        			.Ki = 1810.0f, //158.8f,
        			.samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_iq = {
        	   		.Kp = 4.733f, //0.5f,
					.Ki = 1810.0f,//158.8f,
        			.samplingTime_sec = 0.0001f,
        	};
        	struct uz_CurrentControl_config CC_config = {
        	   		.decoupling_select = linear_decoupling,
					.config_PMSM = config_PMSM,
					.config_id = config_id,
        			.config_iq = config_iq,
        			.max_modulation_index = 1.0f / sqrtf(3.0f)
        	};
        	struct uz_SetPoint_config SP_config = {
        			.config_PMSM = config_PMSM,
        			.control_type = FOC,
        			.motor_type = IPMSM,
        			.is_field_weakening_enabled = false,
        			.id_ref_Ampere = 0.0f
        	};
        	struct uz_SpeedControl_config SC_config = {
        			.config_controller.Kp = 0.0207f,
					.config_controller.Ki = 0.207f,
					.config_controller.samplingTime_sec = 0.0001f,
					.config_controller.upper_limit = 2.0f,
					.config_controller.lower_limit = -2.0f,
        	};
        	Global_Data.objects.CC_instance = uz_CurrentControl_init(CC_config);
        	Global_Data.objects.SP_instance = uz_SetPoint_init(SP_config);
        	Global_Data.objects.SC_instance = uz_SpeedControl_init(SC_config);
        	initialization_chain = init_PMSM_IP_Core;
        	break;
        case init_PMSM_IP_Core:;
        	struct uz_pmsmModel_config_t pmsm_IPCore_config = {
        			.base_address = XPAR_UZ_USER_UZ_PMSM_MODEL_0_BASEADDR,
					.ip_core_frequency_Hz=100000000,
					.simulate_mechanical_system = true,
					.r_1 = config_PMSM.R_ph_Ohm,
					.L_d = config_PMSM.Ld_Henry,
					.L_q = config_PMSM.Lq_Henry,
					.psi_pm = config_PMSM.Psi_PM_Vs,
					.polepairs = config_PMSM.polePairs,
					.inertia = 1.48e-05f,
					.coulomb_friction_constant = 0.01f,
					.friction_coefficient = 0.001f
        	};
        	Global_Data.objects.pmsm_IP_core = uz_pmsmModel_init(pmsm_IPCore_config);
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
            Global_Data.objects.inverter_d1 = initialize_uz_inverter_adapter_on_D1();
            Global_Data.objects.pwm_d1_pin_0_to_5 = initialize_pwm_2l_on_D1_pin_0_to_5();
            Global_Data.objects.pwm_d1_pin_6_to_11 = initialize_pwm_2l_on_D1_pin_6_to_11();
            Global_Data.objects.pwm_d1_pin_12_to_17 = initialize_pwm_2l_on_D1_pin_12_to_17();
            Global_Data.objects.pwm_d1_pin_18_to_23 = initialize_pwm_2l_on_D1_pin_18_to_23();
            Global_Data.objects.mux_axi = initialize_uz_mux_axi();
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);
            initialization_chain = print_msg;
            break;
	    case print_msg:
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
            uz_printf("RPU Build Date: %s at %s,\r\n",__DATE__, __TIME__);

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
