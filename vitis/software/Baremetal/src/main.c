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

// ***************** PMSM 2 ***************** //
// 1.362164
struct uz_pmsm_control_configuration_t config = {
    .current_conversion_factors = {
        .a = 12.2889f,
        .b = 11.8330f,
        .c = 11.7894f},
    .current_offsets = {.a = 0.0164f, .b = 0.0161f, .c = 0.0184f},
    .v_dc_in_V_conversion_factor = 12.0f,
    .v_dc_in_V_offset = 0.0f,
    .i_dc_in_V_conversion_factor = 12.5f,
    .i_dc_in_V_offset = 0.0f,
    .theta_el_offset = 1.362164f,
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = false,
    .speed_controller_max_torque = 0.5f,
    .speed_controller_kp = 0.1f,
    .speed_controller_ki = 0.0f,
    .current_controller_d_kp = 3.77f,
    .current_controller_d_ki = 1810.0f,
    .current_controller_q_kp = 4.73f,
    .current_controller_q_ki = 1810.0f,
    .setpoint_lower_bound_i_d_in_A = -5.0f,
    .setpoint_upper_bound_i_d_in_A = 0.5f,
    .setpoint_lower_bound_i_q_in_A = -5.0f,
    .setpoint_upper_bound_i_q_in_A = 5.0f,
    .setpoint_upper_bound_speed_in_rpm = 500.0f,
    .setpoint_lower_bound_speed_in_rpm = -500.0f,
    .error_upper_bound_speed_in_rpm = 3500.0f,
    .error_lower_bound_speed_in_rpm = -3500.0f,
    .disturbance_input_lower_bound_in_Nm = 0.0f, // disable disturbance input for now
    .disturbance_input_upper_bound_in_Nm = 0.0f,
    .decoupling_method = linear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = 0.0f,
    .motor_type = IPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f},
};

// Configuration of PMSM 2 (Brose PMSM)
struct uz_PMSM_t config_PMSM_heidrive = {
    .R_ph_Ohm = 0.543f,
    .Ld_Henry = 0.00113f,
    .Lq_Henry = 0.00142f,
    .Psi_PM_Vs = 0.0169f,
    .polePairs = 3.0f,
    .J_kg_m_squared = 0.000108f,
    .I_max_Ampere = 10.8f};

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
            Global_Data.objects.pwm_d1_brose = initialize_pwm_2l_on_D1_pin_0_to_5();
            Global_Data.objects.pwm_d2_heidrive = initialize_pwm_2l_on_D1_pin_6_to_11();
            Global_Data.objects.pwm_d1_pin_12_to_17 = initialize_pwm_2l_on_D1_pin_12_to_17();
            Global_Data.objects.pwm_d1_pin_18_to_23 = initialize_pwm_2l_on_D1_pin_18_to_23();
            Global_Data.objects.mux_axi = initialize_uz_mux_axi();
            Global_Data.objects.inverter_d1_brose = initialize_uz_inverter_adapter_on_D1();
            Global_Data.objects.inverter_d2_heidrive = initialize_uz_inverter_adapter_on_D2();
            Global_Data.objects.resolver_d4 = initialize_resolver_d4();
            Global_Data.objects.resolver_pl_d4 = initialize_resolver_pl_d4();
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            Global_Data.objects.encoder_D5_1 = initialize_incremental_encoder_ipcore_on_D5_1(UZ_D5_1_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_1_MOTOR_POLE_PAIR_NUMBER);
            Global_Data.objects.encoder_D5_2 = initialize_incremental_encoder_ipcore_on_D5_2(UZ_D5_2_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_2_MOTOR_POLE_PAIR_NUMBER);
            Global_Data.objects.encoder_D5_3 = initialize_incremental_encoder_ipcore_on_D5_3(UZ_D5_3_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_3_MOTOR_POLE_PAIR_NUMBER);
            initialization_chain = init_control;
            break;
        case init_control:
            Global_Data.objects.heidrive_controller = uz_pmsm_control_init(config, config_PMSM_heidrive);
            Global_Data.heidrive_actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.heidrive_controller);
            Global_Data.heidrive_reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.heidrive_controller);
            Global_Data.heidrive_measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.heidrive_controller);
            JavaScope_initialize(&Global_Data);

            // speed_setpoint_filter_heidrive_config
            // Global_Data.objects.speed_setpoint_filter_heidrive=uz_signals_IIR_Filter_init(speed_setpoint_filter_heidrive_config);
            // Global_Data.objects.tracking_error_filter_heidrive=uz_signals_IIR_Filter_init(tracking_error_filter_heidrive_config);
            nn_init();
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
