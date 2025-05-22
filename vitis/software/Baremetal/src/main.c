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
	.av.i_dq_ref = {.d = 0.0f, .q = 0.0f, .zero = 0.0f},
	.av.d_a_ref = 0.0f,
	.av.d_b_ref = 0.0f,
	.av.d_c_ref = 0.0f,
	.av.n_ref_rpm = 0.0f,
	.av.theta_offset = 2.33f,
    .av.select_speed_control = false,
	.av.trajectoryON = 0,
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
    	   .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
		   .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}
    }
};


//const struct uz_PMSM_t config_PMSM = {
 //  .Ld_Henry = 0.001626f,
 //  .Lq_Henry = 0.001626f,
  // .Psi_PM_Vs = 0.07f,
 //  .R_ph_Ohm = 7.3f,
  // .polePairs = 1.0f,
   //.J_kg_m_squared = ,
//   .I_max_Ampere = 1.72f
// };

const struct uz_PMSM_t config_PMSM = {
  .Ld_Henry =  0.00113f,
   .Lq_Henry = 0.00142f,
  .Psi_PM_Vs = 0.0169f,
  .R_ph_Ohm = 0.543f,
  .polePairs = 3.0f,
   //.J_kg_m_squared = ,
  .I_max_Ampere = 5.0f
 };

//const struct uz_PI_Controller_config config_id = {
   //.Kp = 1.0f,
  // .Ki = 120.0f,
  // .samplingTime_sec = 0.00005f
//};

const struct uz_PI_Controller_config config_id = {
   .Kp = 1.1f,
   .Ki = 120.0f,
   .samplingTime_sec = 0.00005f
};

//const struct uz_PI_Controller_config config_iq = {
  // .Kp = 1.0f,
//  .Ki = 120.0f,
//  .samplingTime_sec = 0.00005f
//};


const struct uz_PI_Controller_config config_iq = {
   .Kp =1.42f,
   .Ki = 95.0f,
   .samplingTime_sec = 0.00005f
};

const struct uz_CurrentControl_config config_current_control = {
   .decoupling_select = linear_decoupling,
   .Kp_adjustment_flag = false,
   .config_PMSM = config_PMSM,
   .config_id = config_id,
   .config_iq = config_iq,
   .max_modulation_index = 0.5f //1.0f / sqrtf(3.0f)
};

//struct uz_SpeedControl_config config_speed = {
//   .config_controller.Kp = 0.006f,
//   .config_controller.Ki = 0.1f,
//   .config_controller.samplingTime_sec = 0.00005f,
//   .config_controller.upper_limit = 3.0f,
//   .config_controller.lower_limit = -3.0f
//};

struct uz_SpeedControl_config config_speed = {
   .config_controller.Kp = 0.01f,
   .config_controller.Ki = 0.1f,
   .config_controller.samplingTime_sec = 0.00005f,
   .config_controller.upper_limit = 5.0f,
   .config_controller.lower_limit = -5.0f
};

struct uz_pmsmModel_config_t model_pmsm_config={
    .base_address=XPAR_UZ_USER_UZ_PMSM_MODEL_0_BASEADDR,
    .ip_core_frequency_Hz=100000000,
    .simulate_mechanical_system = true,
    .r_1 = config_PMSM.R_ph_Ohm,
    .L_d = config_PMSM.Ld_Henry,
    .L_q = config_PMSM.Lq_Henry,
    .psi_pm = config_PMSM.Psi_PM_Vs,
    .polepairs = config_PMSM.polePairs,
    .inertia = 3.24e-05f,
    .coulomb_friction_constant = 0.01f,
    .friction_coefficient = 0.001f
};

struct uz_Trajectory_config Traj_config = {
    .selection_interpolation = Zero_Order_Hold,
    .selection_XAxis = MilliSeconds,
    .StopStyle = HoldLast,
    .RepeatStyle = Repeat_Times,
    .Number_Sample_Points = MAX_TRAJECTORY_SAMPLES,
    //.Sample_Amplitude_Y = {500.0f, 700.0f, 800.0f, 950.0f, 750.0f, 500.0f},
    //.Sample_Duration_X = {5000.0f, 5000.0f, 5000.0f, 5000.0f, 5000.0f, 5000.0f},
	   .Sample_Amplitude_Y = {1000.0f, 1500.0f},
	    .Sample_Duration_X = {5000.0f, 5000.0f},
    .Repeats = 1,
    .Stepwidth_ISR = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor)
  };
struct uz_Flussschaetzer_config Flussschaetzer_config={};


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
            uz_SystemTime_init();
            JavaScope_initialize(&Global_Data);

            Global_Data.objects.current_control = uz_CurrentControl_init(config_current_control);
            Global_Data.objects.speed_control = uz_SpeedControl_init(config_speed);
            Global_Data.objects.Flussschaetzer = uz_Flussschaetzer_init(Flussschaetzer_config) ;
            Global_Data.objects.pmsmModel = uz_pmsmModel_init(model_pmsm_config);;
            Global_Data.objects.TraceGen_1 = uz_Trajectory_init(Traj_config);

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
            Global_Data.objects.encoder_D5 = initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);
            Global_Data.objects.inverter_d1 = initialize_uz_inverter_adapter_on_D1();
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
