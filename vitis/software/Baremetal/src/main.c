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
#include "uz/uz_encoder_offset_estimation/uz_encoder_offset_estimation.h"
#include "uz/uz_ParameterID/uz_ParameterID.h"

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

// Declare Pointer for FOC of PMSM 1
uz_SpeedControl_t* SC_instance_1;
uz_SetPoint_t* SP_instance_1;
uz_CurrentControl_t* CC_instance_1;
uz_encoder_offset_estimation_t* encoder_offset_obj_1;
uz_wavegen_chirp* chirp_instance_1;

//ParameterID Code
uz_ParameterID_t* ParameterID = NULL;
uz_ParameterID_Data_t ParaID_Data = { 0 };
// Declare Pointer for FOC of PMSM 2
uz_SpeedControl_t* SC_instance;
uz_SetPoint_t* SP_instance;
uz_CurrentControl_t* CC_instance_dq;
uz_encoder_offset_estimation_t* encoder_offset_obj_2;
uz_subspace_resonant_control* RC_instance_6th_2;
uz_IIR_Filter_t* LP_instance_ud_ind_2;
uz_IIR_Filter_t* LP_instance_uq_ind_2;

// Configuration of PMSM 1 (Hoerner PMSM)
struct uz_PMSM_t config_PMSM_1 = {
   .R_ph_Ohm = 0.249f,
   .Ld_Henry = 0.00044f,
   .Lq_Henry = 0.00245f,
   .Psi_PM_Vs = 0.0194f,
   .polePairs = 4.0f,
   .J_kg_m_squared = 0.000084f,
   .I_max_Ampere = 10.0f
};//these parameters are only needed if linear decoupling is selected

// Configuration of PMSM 2 (Brose PMSM)
struct uz_PMSM_t config_PMSM_2 = {
   .R_ph_Ohm = 0.01664f,
   .Ld_Henry = 0.00003f,
   .Lq_Henry = 0.00005f,
   .Psi_PM_Vs = 0.007f,
   .polePairs = 5.0f,
   .J_kg_m_squared = 0.00001773f,
   .I_max_Ampere = 20.0f
};//these parameters are only needed if linear decoupling is selected

enum init_chain
{
    init_assertions = 0,
    init_gpios,
    init_software,
    init_ip_cores,
	init_control,
    print_msg,
    init_interrupts,
    infinite_loop
};
enum init_chain initialization_chain = init_assertions;

int main(void)
{
    int status = UZ_SUCCESS;
    ParameterID = uz_ParameterID_init(&ParaID_Data);
    // ============== Configs for PMSM 1 (Pruefling) ============== //
    // -------------- Configuration of Speed Control -------------- //
    struct uz_SpeedControl_config SC_config_1 = {
       .config_controller.Kp = 0.01f, //0.001f
       .config_controller.Ki = 1.0f,  //0.05f
       .config_controller.samplingTime_sec = 0.0001f,
       .config_controller.upper_limit = 2.0f,
       .config_controller.lower_limit = -2.0f,
    };
    // ---------------- Configuration of Set Point ---------------- //
    struct uz_SetPoint_config SP_config_1 = {
       .config_PMSM = config_PMSM_1,
       .control_type = FOC,
       .motor_type = IPMSM,
       .is_field_weakening_enabled = false,
       .id_ref_Ampere = 0.0f,
 	   .relative_torque_tolerance = 0.1f
     };
    // ------------- Configuration of Current Control ------------- //
    struct uz_PI_Controller_config config_id_1 = {
       .Kp = 1.47f, // nach BO
       .Ki = 830.0f, //nach BO
       .samplingTime_sec = 0.0001f,
 	   .upper_limit = 15.0f,
  	   .lower_limit = -15.0f
    };
    struct uz_PI_Controller_config config_iq_1 = {
       .Kp = 8.17f, // nach BO
       .Ki = 830.0f, // nach BO
       .samplingTime_sec = 0.0001f,
  	   .upper_limit = 10.0f,
	   .lower_limit = -10.0f
    };
    struct uz_CurrentControl_config CC_config_1 = {
       .decoupling_select = linear_decoupling,
       .config_PMSM = config_PMSM_1,
       .config_id = config_id_1,
       .config_iq = config_iq_1,
       .max_modulation_index = 1.0f / sqrtf(3.0f)
    };
    // ---------------- Encoder offset estimation ----------------- //
    struct uz_encoder_offset_estimation_config encoder_offset_cfg_1 = { 	// config struct
      .ptr_measured_rotor_angle = &Global_Data.av.theta_elec_1,             // pointer to the measured electric rotor angle (raw, not offset corrected)
      .ptr_offset_angle = &Global_Data.av.theta_offset_1,                   // pointer to global variable holding the offset angle
      .ptr_actual_omega_el = &Global_Data.av.omega_el_1,                    // pointer to actual electric rotor angular speed
      .ptr_actual_u_q_V = &Global_Data.av.U_q_1,                              // pointer to q-setpoint voltage
      .min_omega_el = 300.0f,                                               // target electric rotor angular speed (USE OWN)
      .setpoint_current = 3.0f 												// current setpoint to reach speed (USE OWN)
    };
    // ---------------- Chirp excitation ----------------- //
    // Configuration Wavegen Chirp
    struct uz_wavegen_chirp_config config_chirp_1 = {
      .amplitude = 1.0f,
      .start_frequency_Hz = 1.0f,
      .end_frequency_Hz = 4000.0f,
      .duration_sec = 2.0f,
      .initial_delay_sec = 1.0f,
      .offset = 0.0f
    };

    // ------------------- Filter u-ind ------------------- //
    struct uz_IIR_Filter_config LP_config_ud_ind_2 = {
        	.selection = LowPass_first_order,
			.cutoff_frequency_Hz =  2.0f,
    		.sample_frequency_Hz = 10000.0f,

    };

    struct uz_IIR_Filter_config LP_config_uq_ind_2 = {
        	.selection = LowPass_first_order,
			.cutoff_frequency_Hz = 2.0f,
    		.sample_frequency_Hz = 10000.0f,

    };



    //--------- Configs for PMSM 2 (Last) ---------//
    // Configuration of Speed Control
    struct uz_SpeedControl_config SC_config = {
       .config_controller.Kp = ParaID_Data.GlobalConfig.Kp_n,
       .config_controller.Ki = ParaID_Data.GlobalConfig.Ki_n,
       .config_controller.samplingTime_sec = 0.0001f,
       .config_controller.upper_limit = 10.0f,
       .config_controller.lower_limit = -10.0f,
    };
    // Configuration of Set Point
    struct uz_SetPoint_config SP_config = {
       .config_PMSM = ParaID_Data.GlobalConfig.PMSM_config,
       .control_type = FOC,
       .motor_type = IPMSM,
       .is_field_weakening_enabled = false,
       .id_ref_Ampere = 0.0f,
       .relative_torque_tolerance = 0.1f
     };
     // Configuration of Current Control
     struct uz_PI_Controller_config config_id_2 = {
        .Kp = ParaID_Data.GlobalConfig.Kp_id, // nach BO, 0.3 nach Nina, 1.51f nach Bandbreite
        .Ki = ParaID_Data.GlobalConfig.Ki_id, //nach BO, 230.0f nach Nina , 836.4f nach Bandbreite
        .samplingTime_sec = 0.0001f,
        .upper_limit = 15.0f,
        .lower_limit = -15.0f
      };
      struct uz_PI_Controller_config config_iq_2 = {
        .Kp = ParaID_Data.GlobalConfig.Kp_iq, // nach BO, 0.5f nach Nina
        .Ki = ParaID_Data.GlobalConfig.Ki_iq, // nach BO, 230.0f nach Nina
        .samplingTime_sec = 0.0001f,
        .upper_limit = 15.0f,
	    .lower_limit = -15.0f
      };
      struct uz_CurrentControl_config CC_config_dq = {
        .decoupling_select = linear_decoupling,
        .config_PMSM = ParaID_Data.GlobalConfig.PMSM_config,
        .config_id = config_id_2,
        .config_iq = config_iq_2,
        .max_modulation_index = 1.0f / sqrtf(3.0f)
      };
      // Encoder offset estimation
      struct uz_encoder_offset_estimation_config encoder_offset_cfg_2 = {  	 // config struct
        .ptr_measured_rotor_angle = &Global_Data.av.theta_elec_2,            // pointer to the measured electric rotor angle (raw, not offset corrected)
        .ptr_offset_angle = &Global_Data.av.theta_offset_2,                  // pointer to global variable holding the offset angle
        .ptr_actual_omega_el = &Global_Data.av.omega_el_2,                   // pointer to actual electric rotor angular speed
        .ptr_actual_u_q_V = &Global_Data.av.U_q_2,                             // pointer to q-setpoint voltage
        .min_omega_el = 300.0f,                                              // target electric rotor angular speed (USE OWN)
        .setpoint_current = 3.0f 											 // current setpoint to reach speed (USE OWN)
      };

    // Initialization Chain
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
            initialize_incremental_encoder_ipcore_on_D5_1(UZ_D5_1_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_1_MOTOR_POLE_PAIR_NUMBER);
            initialize_incremental_encoder_ipcore_on_D5_2(UZ_D5_2_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_2_MOTOR_POLE_PAIR_NUMBER);
            initialize_incremental_encoder_ipcore_on_D5_3(UZ_D5_3_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_3_MOTOR_POLE_PAIR_NUMBER);
            Global_Data.objects.inverter_d1 = initialize_uz_inverter_adapter_on_D1();
            Global_Data.objects.inverter_d2 = initialize_uz_inverter_adapter_on_D2();
            initialization_chain = init_control;
            break;
        case init_control:
            SC_instance_1 = uz_SpeedControl_init(SC_config_1);
            SP_instance_1 = uz_SetPoint_init(SP_config_1);
            CC_instance_1 = uz_CurrentControl_init(CC_config_1);
            SC_instance = uz_SpeedControl_init(SC_config);
            SP_instance = uz_SetPoint_init(SP_config);
            CC_instance_dq = uz_CurrentControl_init(CC_config_dq);
           	chirp_instance_1 = uz_wavegen_chirp_init(config_chirp_1);
           	encoder_offset_obj_1 = uz_encoder_offset_estimation_init(encoder_offset_cfg_1);
           	encoder_offset_obj_2 = uz_encoder_offset_estimation_init(encoder_offset_cfg_2);
           	LP_instance_ud_ind_2 = uz_signals_IIR_Filter_init(LP_config_ud_ind_2);
           	LP_instance_uq_ind_2 = uz_signals_IIR_Filter_init(LP_config_uq_ind_2);
           	Global_Data.av.theta_offset_1 = 0.904f;
           	Global_Data.av.theta_offset_2 = 1.4f;
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
