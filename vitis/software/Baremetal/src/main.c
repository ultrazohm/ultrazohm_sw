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

#define DQN_FREQUENCY 400
// defines for nn
#define NUMBER_OF_INPUTS 5
#define NUMBER_OF_OUTPUTS 3
#define NUMBER_OF_HIDDEN_LAYER 3
#define NUMBER_OF_NEURONS_IN_FIRST_LAYER 128
#define NUMBER_OF_NEURONS_IN_SECOND_LAYER 128

float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "uz/uz_nn/full_example_weights/layer1_weights.csv"
};
float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {
#include "uz/uz_nn/full_example_weights/layer1_bias.csv"
};
float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] = {0};

float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "uz/uz_nn/full_example_weights/layer2_weights.csv"
};
float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {
#include "uz/uz_nn/full_example_weights/layer2_bias.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] = {0};

float w_3[NUMBER_OF_NEURONS_IN_SECOND_LAYER * NUMBER_OF_OUTPUTS] = {
#include "uz/uz_nn/full_example_weights/layer3_weights.csv"
};
float b_3[NUMBER_OF_OUTPUTS] = {
#include "uz/uz_nn/full_example_weights/layer3_bias.csv"
};
float y_3[NUMBER_OF_OUTPUTS] = {0};

// Initialize the global variables
DS_Data Global_Data = {
    .rasv = {
        .halfBridge1DutyCycle = 0.0f,
        .halfBridge2DutyCycle = 0.0f,
        .halfBridge3DutyCycle = 0.0f},
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}},
    .mrp = {.incrementalEncoder_speed_timeout_in_ms = 10}};
uz_FOC *FOC_instance;
uz_SpeedControl_t *Speed_instance;
uz_IIR_Filter_t *LPF1_instance_position;
uz_IIR_Filter_t *LPF1_instance_angle;
uz_IIR_Filter_t *LPF1_instance_2;
uz_PI_Controller *PI_instance;
uz_nn_t *uz_nn_instance;
uz_matrix_t *input_instance;
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

static void dqn_step(void);
static int dividingfactordqn=UZ_PWM_FREQUENCY/DQN_FREQUENCY;
bool dqn_mutex=false;
float dqn_mutex_float =0.0f;
float input_nn[5] = {-0.47f, -0.88f, -2.9f, 0.375f, -3.2f};
int main(void)
{
    int status = UZ_SUCCESS;
    struct uz_PMSM_t config_heidrive = {

        .R_ph_Ohm = 0.543f,

        .Ld_Henry = 0.00113f,

        .Lq_Henry = 0.00142f,

        .Psi_PM_Vs = 0.0169f,

        .polePairs = 3.0f,

        .J_kg_m_squared = 0.0000148f,

        .I_max_Ampere = 10.8f

    };

    struct uz_PI_Controller_config config_id = {

        .Kp = 3.0f,

        .Ki = 600.0f,

        .samplingTime_sec = 0.00005f,

        .upper_limit = 40.0f,

        .lower_limit = -40.0f

    };

    struct uz_PI_Controller_config config_iq = {

        .Kp = 3.5f,

        .Ki = 600.0f,

        .samplingTime_sec = 0.00005f,

        .upper_limit = 40.0f,

        .lower_limit = -40.0f

    };
    struct uz_PI_Controller_config config_position = {

        .Kp = 2.0f,

        .Ki = 0.0f,

        .samplingTime_sec = 0.00005f,

        .upper_limit = 500.0f,

        .lower_limit = -500.0f

    };

    struct uz_FOC_config config_FOC = {

        .decoupling_select = linear_decoupling,

        .config_PMSM = config_heidrive,

        .config_id = config_id,

        .config_iq = config_iq

    };

    struct uz_SpeedControl_config config_speed = {

        .config_controller.Kp = 0.01f,

        .config_controller.Ki = 7.0f,

        .config_controller.samplingTime_sec = 0.00005f,

        .config_controller.upper_limit = 15.0f,

        .config_controller.lower_limit = -15.0f,

        .config_PMSM.R_ph_Ohm = 0.543f,

        .config_PMSM.Ld_Henry = 0.00113f,

        .config_PMSM.Lq_Henry = 0.00142f,

        .config_PMSM.Psi_PM_Vs = 0.0169f,

        .config_PMSM.polePairs = 3.0f,

        .config_PMSM.J_kg_m_squared = 0.0000148f,

        .config_PMSM.I_max_Ampere = 10.8f,

        .is_field_weakening_active = false

    };
    struct uz_nn_layer_config config_nn[NUMBER_OF_HIDDEN_LAYER] = {
        [0] = {
            .activation_function = activation_ReLU,
            .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
            .number_of_inputs = NUMBER_OF_INPUTS,
            .length_of_weights = UZ_MATRIX_SIZE(w_1),
            .length_of_bias = UZ_MATRIX_SIZE(b_1),
            .length_of_output = UZ_MATRIX_SIZE(y_1),
            .weights = w_1,
            .bias = b_1,
            .output = y_1},
        [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_FIRST_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
        [2] = {.activation_function = activation_linear, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3}};

    struct uz_matrix_t x_matrix = {0};
    struct uz_IIR_Filter_config config1 = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 200.0f, .sample_frequency_Hz = 20000.0f};
    struct uz_IIR_Filter_config config2 = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 10.0f, .sample_frequency_Hz = 20000.0f};
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
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            initialize_incremental_encoder_ipcore_v25_on_D5_1(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER, Global_Data.mrp.incrementalEncoder_speed_timeout_in_ms);
            initialize_incremental_encoder_ipcore_v25_on_D5_2(UZ_D5_POSINCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER, Global_Data.mrp.incrementalEncoder_speed_timeout_in_ms);
            initialize_incremental_encoder_ipcore_v25_on_D5_3(UZ_D5_ANGINCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER, Global_Data.mrp.incrementalEncoder_speed_timeout_in_ms);
            initialization_chain = print_msg;
            initialization_chain = init_foc;
            break;
        case init_foc:
            FOC_instance = uz_FOC_init(config_FOC);
            Speed_instance = uz_SpeedControl_init(config_speed);
            LPF1_instance_angle = uz_signals_IIR_Filter_init(config1);
            LPF1_instance_position = uz_signals_IIR_Filter_init(config1);
            LPF1_instance_2 = uz_signals_IIR_Filter_init(config2);
            PI_instance = uz_PI_Controller_init(config_position);
            uz_nn_instance = uz_nn_init(config_nn, NUMBER_OF_HIDDEN_LAYER);
            input_instance = uz_matrix_init(&x_matrix, input_nn, UZ_MATRIX_SIZE(input_nn), 1, 5);
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

            if( !(uz_SystemTime_GetInterruptCounter() % dividingfactordqn) ){
                dqn_mutex=false;
                dqn_mutex_float=0.0f;
                dqn_step();
                dqn_mutex=true;
                dqn_mutex_float=1.0f;
            }

            break;
        default:
            break;
        }
    }
    return (status);
}


static void dqn_step(void)
{
	input_nn[0]=Global_Data.obs.dqn_sin_angle;
	input_nn[1]=Global_Data.obs.dqn_cos_angle;
	input_nn[2]=Global_Data.obs.dqn_chart_position_derv;
	input_nn[3]=Global_Data.obs.dqn_chart_position;
	input_nn[4]=Global_Data.obs.dqn_angle_derv;
    uz_nn_ff(uz_nn_instance, input_instance);
}
