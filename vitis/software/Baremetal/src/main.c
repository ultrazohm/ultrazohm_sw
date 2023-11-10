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

// defines for nn

float epoch_global = 0.0f;

float finished = 5.0f;
float evaluation_run = 0.0f;
float global_loss = 0.0f;
float global_reward_metric = 0.0f;
float penalty_grenze=340.0f;
bool limit_was_hit=false;

#include "uz/uz_dqn/uz_dqn.h"
#include "uz/uz_dqn/uz_environment_bitflip.h"
#include "uz/uz_environment_pt1/uz_environment_pt1.h"

#define EXPERIENCE_BUFFER_LENGTH 150000U
#define MINIBATCHSIZE 8U
#define NUMBER_OF_EPOCHS 500U
#define TARGET_UPDATE_FREQUENCY 20U
// nn
#define NUMBER_OF_INPUTS 5U
#define NUMBER_OF_OUTPUTS 5U
#define NUMBER_OF_HIDDEN_LAYER 2U
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 256U
#define NUMBEROFTESTSTEPS 50U

float discountfact = 0.9f;
float lernrate = 0.0002f;

float epsilon_start = 0.99f;
float epsilon_min = 0.0000000001f;
float epsilon_decay = 0.000001f;

// adam
float m1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0.0f};
float m2[NUMBER_OF_OUTPUTS + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0.0f};
float v1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0.0f};
float v2[NUMBER_OF_OUTPUTS + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0.0f};

// debug stuff
float Q_Target[NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS] = {0.0f};
float Q_Critic[NUMBER_OF_EPOCHS * NUMBER_OF_OUTPUTS] = {0.0f};

// dqn
float X_dat[NUMBER_OF_INPUTS] = {0.0f};
float X1_dat[NUMBER_OF_INPUTS] = {0.0f};

// target
float ts_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float ts_2[NUMBER_OF_OUTPUTS] = {0};

float tx[NUMBER_OF_INPUTS] = {0};
float tw_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float tb_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float ty_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float tw_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};
float tb_2[NUMBER_OF_OUTPUTS] = {0};
float ty_2[NUMBER_OF_OUTPUTS] = {0};

float copy_ts_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float copy_ts_2[NUMBER_OF_OUTPUTS] = {0};

float copy_tx[NUMBER_OF_INPUTS] = {0};
float copy_tw_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float copy_tb_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float copy_ty_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float copy_tw_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};
float copy_tb_2[NUMBER_OF_OUTPUTS] = {0};
float copy_ty_2[NUMBER_OF_OUTPUTS] = {0};
// critic
float cs_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float cs_2[NUMBER_OF_OUTPUTS] = {0};

// deltas
float delta_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float delta_2[NUMBER_OF_OUTPUTS] = {0};

// cache gradients, Gräße entspricht delta des aktuellen layers * größe des Outputs des vorherigen layers
float cacheg_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0};
float cacheg_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};

// Gradienten
float g_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_INPUTS] = {0};
float g_2[NUMBER_OF_OUTPUTS + NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};

float cx[NUMBER_OF_INPUTS] = {0};
float creference_output[NUMBER_OF_OUTPUTS] = {0};

float cw_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0.0f};
float cb_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0.0f};
float cy_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0.0f};

float cw_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0.0f};
float cb_2[NUMBER_OF_OUTPUTS] = {0.0f};
float cy_2[NUMBER_OF_OUTPUTS] = {0.0f};

// error
float e_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0.0f};
float e_2[NUMBER_OF_OUTPUTS] = {0.0f};

// Temporary buffer storage

float T1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};
float T2[4] = {0};

// stuff for buffer
float reward[EXPERIENCE_BUFFER_LENGTH] = {0.0f};
uint32_t action[EXPERIENCE_BUFFER_LENGTH] = {0};
float observation[NUMBER_OF_INPUTS * EXPERIENCE_BUFFER_LENGTH] = {0.0f};
float observation1[NUMBER_OF_INPUTS * EXPERIENCE_BUFFER_LENGTH] = {0.0f};
float vecobs[NUMBER_OF_INPUTS] = {0.0f};
float vecobs1[NUMBER_OF_INPUTS] = {0.0f};

// config random
bool update_lock=false;
float update_lock_float=0.0f;

struct uz_nn_layer_config config_copy[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(tw_1),
        .length_of_bias = UZ_MATRIX_SIZE(tb_1),
        .length_of_output = UZ_MATRIX_SIZE(ty_1),
        .length_of_sumout = UZ_MATRIX_SIZE(ts_1),
        .weights = copy_tw_1,
        .bias = copy_tb_1,
        .output = copy_ty_1,
        .sumout = copy_ts_1},
    [1] = {.activation_function = activation_linear,
    		.number_of_neurons = NUMBER_OF_OUTPUTS,
			.number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
			.length_of_weights = UZ_MATRIX_SIZE(tw_2),
			.length_of_bias = UZ_MATRIX_SIZE(tb_2),
			.length_of_output = UZ_MATRIX_SIZE(ty_2),
			.length_of_sumout = UZ_MATRIX_SIZE(ts_2),
			.weights = copy_tw_2,
			.bias = copy_tb_2,
			.output = copy_ty_2,
			.sumout = copy_ts_2}};
// config critic

// config target
struct uz_nn_layer_config config_target[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(tw_1),
        .length_of_bias = UZ_MATRIX_SIZE(tb_1),
        .length_of_output = UZ_MATRIX_SIZE(ty_1),
        .length_of_sumout = UZ_MATRIX_SIZE(ts_1),
        .weights = tw_1,
        .bias = tb_1,
        .output = ty_1,
        .sumout = ts_1},
    [1] = {.activation_function = activation_linear, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .length_of_weights = UZ_MATRIX_SIZE(tw_2), .length_of_bias = UZ_MATRIX_SIZE(tb_2), .length_of_output = UZ_MATRIX_SIZE(ty_2), .length_of_sumout = UZ_MATRIX_SIZE(ts_2), .weights = tw_2, .bias = tb_2, .output = ty_2, .sumout = ts_2}};
// config critic
struct uz_nn_layer_config config_critic[NUMBER_OF_HIDDEN_LAYER] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .number_of_cachegradrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_cachegradcolumns = NUMBER_OF_INPUTS,
        .number_of_temporaryrows = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_temporarycolumns = NUMBER_OF_OUTPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(cw_1),
        .length_of_bias = UZ_MATRIX_SIZE(cb_1),
        .length_of_output = UZ_MATRIX_SIZE(cy_1),
        .length_of_sumout = UZ_MATRIX_SIZE(cs_1),
        .length_of_delta = UZ_MATRIX_SIZE(delta_1),
        .length_of_error = UZ_MATRIX_SIZE(e_1),
        .length_of_gradients = UZ_MATRIX_SIZE(g_1),
        .length_of_temporarybackprop = UZ_MATRIX_SIZE(T1),
        .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_1),
        .m = m1,
        .v = v1,
        .weights = cw_1,
        .bias = cb_1,
        .output = cy_1,
        .sumout = cs_1,
        .delta = delta_1,
        .temporarybackprop = T1,
        .gradients = g_1,
        .cachegradients = cacheg_1,
        .error = e_1},
    [1] = {.activation_function = activation_linear, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .number_of_cachegradrows = NUMBER_OF_OUTPUTS, .number_of_cachegradcolumns = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .number_of_temporaryrows = 2, .number_of_temporarycolumns = 2, .length_of_weights = UZ_MATRIX_SIZE(cw_2), .length_of_bias = UZ_MATRIX_SIZE(cb_2), .length_of_output = UZ_MATRIX_SIZE(cy_2), .length_of_sumout = UZ_MATRIX_SIZE(cs_2), .length_of_delta = UZ_MATRIX_SIZE(delta_2), .length_of_gradients = UZ_MATRIX_SIZE(g_2), .length_of_error = UZ_MATRIX_SIZE(e_2), .length_of_temporarybackprop = UZ_MATRIX_SIZE(T2), .length_of_cachegradients = UZ_MATRIX_SIZE(cacheg_2), .m = m2, .v = v2, .weights = cw_2, .bias = cb_2, .output = cy_2, .sumout = cs_2, .delta = delta_2, .temporarybackprop = T2, .gradients = g_2, .cachegradients = cacheg_2, .error = e_2}};

// config buffer
struct uz_dqn_experience_replay_config configbuffer = {
    .length_of_buffer = EXPERIENCE_BUFFER_LENGTH,
    .columns_of_observations = NUMBER_OF_INPUTS,
    .reward = reward,
    .observations = observation,
    .observations1 = observation1,
    .obsvec = vecobs,
    .obsvec1 = vecobs1,
    .actions = action};
// buffer

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
        .halfBridge12DutyCycle = 0.0f},
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}},
    .mrp = {.incrementalEncoder_speed_timeout_in_ms = 10}};

uz_environment_pt1_t *pt1;
uint32_t action_k = 0;

float targsmoothfact = 0.05f;
float error[NUMBER_OF_OUTPUTS] = {0.0f};

bool first_episode = true;
uz_dqn_t *testdqn2;
float cum_loss;
float number_of_updates_per_episode=2000; // 200 Hz für 10s sind 2000 samples und damit 2000 updates
float old_number_of_updates;
extern float number_of_updates;

extern enum dqn_chain chain;

enum init_chain
{
    init_assertions = 0,
    init_gpios,
    init_software,
    init_ip_cores,
    init_foc_control_nn,
    print_msg,
    init_interrupts,
    infinite_loop
};
enum init_chain initialization_chain = init_assertions;

// config heidrive pmsm

struct uz_PMSM_t config_heidrive = {
    .R_ph_Ohm = 0.543f,
    .Ld_Henry = 0.00113f,
    .Lq_Henry = 0.00142f,
    .Psi_PM_Vs = 0.0169f,
    .polePairs = 3.0f,
    .J_kg_m_squared = 0.0000148f,
    .I_max_Ampere = 5.0f};
static void dqn_step(void);
int dividingfactordqn = UZ_PWM_FREQUENCY / DQN__CONTROL_FREQUENCY;
float dqn_mutex_float = 0.0f;
float input_nn[5] = {-0.47f, -0.88f, -2.9f, 0.375f, -3.2f};
extern float position_abs;
static uint32_t updates=0;
int main(void)
{
    int status = UZ_SUCCESS;

    // Position Controller linear axis
    struct uz_PI_Controller_config config_angle = {
        .Kp = 0.5f,
        .Ki = 0.0f,
        .samplingTime_sec = 0.00005f,
        .upper_limit = 1500.0f,
        .lower_limit = -1500.0f};

    struct uz_PI_Controller_config config_position = {
        .Kp = 3.0f,
        .Ki = 0.0f,
        .samplingTime_sec = 0.00005f,
        .upper_limit = 1500.0f,
        .lower_limit = -1500.0f};
    // Configuration of Speed Control

    struct uz_SpeedControl_config SC_config = {
        .config_controller.Kp = 0.0207f,
        .config_controller.Ki = 0.207f,
        .config_controller.samplingTime_sec = 0.00005f,
        .config_controller.upper_limit = 1.5f,
        .config_controller.lower_limit = -1.5f,
    };

    // Configuration of Set Point
    struct uz_SetPoint_config SP_config = {
        .config_PMSM = config_heidrive,
        .control_type = FOC,
        .motor_type = IPMSM,
        .is_field_weakening_enabled = false,
        .id_ref_Ampere = 0.0f,
        .relative_torque_tolerance = 0.1f};

    // Configuration of Current Control

    struct uz_PI_Controller_config config_id = {
        .Kp = 5.65f,
        .Ki = 2715.0f,
        .samplingTime_sec = 0.00005f,
        .upper_limit = 40.0f,
        .lower_limit = -40.0f};

    struct uz_PI_Controller_config config_iq = {
        .Kp = 7.11f,
        .Ki = 2715.0f,
        .samplingTime_sec = 0.00005f,
        .upper_limit = 40.0f,
        .lower_limit = -40.0f};

    struct uz_CurrentControl_config CC_config = {
        .decoupling_select = linear_decoupling,
        .config_PMSM = config_heidrive,
        .config_id = config_id,
        .config_iq = config_iq,
        .max_modulation_index = 1.0f / sqrtf(3.0f)};

    struct uz_matrix_t x_matrix = {0};
    struct uz_IIR_Filter_config config1 = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 200.0f, .sample_frequency_Hz = 20000.0f};
    struct uz_IIR_Filter_config config2 = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 100.0f, .sample_frequency_Hz = 20000.0f};
    struct uz_IIR_Filter_config config3 = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 100.0f, .sample_frequency_Hz = 20000.0f};
    struct uz_IIR_Filter_config config4 = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 5.0f, .sample_frequency_Hz = 20000.0f};
    struct uz_IIR_Filter_config config5 = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 1/5.0f, .sample_frequency_Hz = 20000.0f};


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
            uz_SystemTime_init();
            JavaScope_initialize(&Global_Data);
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
            Global_Data.objects.inverter_d1 = initialize_uz_inverter_adapter_on_D1();
            initialization_chain = init_foc_control_nn;
            break;
        case init_foc_control_nn:
            Global_Data.objects.SP_instance = uz_SetPoint_init(SP_config);
            Global_Data.objects.CC_instance = uz_CurrentControl_init(CC_config);
            Global_Data.objects.Speed_instance = uz_SpeedControl_init(SC_config);
            Global_Data.objects.LPF1_instance_angle = uz_signals_IIR_Filter_init(config1);
            Global_Data.objects.LPF1_instance_position = uz_signals_IIR_Filter_init(config1);
            Global_Data.objects.LPF1_instance_2 = uz_signals_IIR_Filter_init(config2);
            Global_Data.objects.LPF1_instance_3 = uz_signals_IIR_Filter_init(config3);
            Global_Data.objects.LPF1_instance_4 = uz_signals_IIR_Filter_init(config4);
            Global_Data.objects.LPF1_position= uz_signals_IIR_Filter_init(config5);
            Global_Data.objects.LPF1_angle = uz_signals_IIR_Filter_init(config5);

            Global_Data.objects.PI_instance = uz_PI_Controller_init(config_position);
            Global_Data.objects.pi_angle = uz_PI_Controller_init(config_angle);

            testdqn2 = uz_dqn_init(X_dat, X1_dat, lernrate, discountfact, config_critic, config_target, 21U, NUMBER_OF_HIDDEN_LAYER, configbuffer, EXPERIENCE_BUFFER_LENGTH, MINIBATCHSIZE, TARGET_UPDATE_FREQUENCY, targsmoothfact, epsilon_start, epsilon_min, epsilon_decay, periodic, error,config_copy);

            Global_Data.objects.input_instance = uz_matrix_init(&x_matrix, input_nn, UZ_MATRIX_SIZE(input_nn), 1, NUMBER_OF_INPUTS);
            Global_Data.mv.V_dc_volts = 48.0f;
            // tune current control after init
            // uz_CurrentControl_tune_magnitude_optimum(Global_Data.objects.CC_instance,0.00005f);
            initialization_chain = print_msg;
            break;
        case print_msg:
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
            uz_printf("RPU Build Date: %s at %s,\r\n", __DATE__, __TIME__);

            initialization_chain = init_interrupts;
            break;
        case init_interrupts:
            uz_axigpio_enable_datamover();
            Initialize_ISR(); // Initialize the Interrupts and enable them - last line of code before infinite loop
            initialization_chain = infinite_loop;
            break;
        case infinite_loop:
            ultrazohm_state_machine_step();
            platform_state_t current_state=ultrazohm_state_machine_get_state();
            if(current_state==control_state){
        	switch (chain) {
    			case dqn_active:
    				//cum_loss = uz_dqn_update(testdqn2);
    				old_number_of_updates=number_of_updates;
                    if ( (!(uz_SystemTime_GetInterruptCounter() % dividingfactordqn)) && (current_state==control_state) )
                    {
                        dqn_mutex_float = 0.0f;
                        dqn_step();
                        dqn_mutex_float = 1.0f;
                    }
    				break;
    			case limit_violation:

    				break;
    			case return_to_zero_position:
    				if(number_of_updates< (old_number_of_updates+number_of_updates_per_episode) ){
    					cum_loss = uz_dqn_update(testdqn2);
    				}
    				break;
    			case wait_at_zero_position:
    				update_lock=true;
    				update_lock_float=1.0f;

    		//		if(updates<200){
    			//		updates++;
    				if(number_of_updates< (old_number_of_updates+number_of_updates_per_episode) ){
    					cum_loss = uz_dqn_update(testdqn2);
    				}
    				//}
    				update_lock=false;
    				update_lock_float=0.0f;
                    action_k = 2;
      				first_episode=true;
    				break;
    			case get_to_start_postion:
    				if(number_of_updates< (old_number_of_updates+number_of_updates_per_episode) ){
    					cum_loss = uz_dqn_update(testdqn2);
    				}
    				break;
    			default:
    				break;
        	}
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
    // sample observation of the environment at k=0
    uz_dqn_sample_observation_k_0(testdqn2, Global_Data.objects.input_instance);
    action_k = uz_dqn_determine_action(testdqn2);
}

void Reset_global_Data(DS_Data *data)
{
    data->obs.dqn_angle_raw = 0.0f;
    data->obs.dqn_chart_position_derv_raw = 0.0f;
    data->obs.dqn_angle_derv_raw = 0.0f;
    data->obs.dqn_chart_position = 0.0f;
    data->obs.dqn_angle_derv = 0.0f;
    data->obs.dqn_angle = 0.0f;
    data->obs.dqn_chart_position_derv = 0.0f;
    data->obs.dqn_sin_angle = 0.0f;
    data->obs.dqn_cos_angle = 0.0f;
}


