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

extern const struct uz_PMSM_t Beckhoff_AM8141;

struct uz_movingAverageFilter_config config_MovAvg = {
   .filterLength = 300U
};
float data [300] = {0};
uz_array_float_t circularBuffer = {
   .length = UZ_ARRAY_SIZE(data),
   .data = &data[0]
};
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
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY_ISR,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY_ISR) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
    	   .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
		   .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}
    }
};

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

struct uz_IIR_Filter_config config = { .selection = LowPass_first_order,
		.cutoff_frequency_Hz = 0.5f, .sample_frequency_Hz = UZ_PWM_FREQUENCY_ISR };


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
			Global_Data.av.polepairs_left = Beckhoff_AM8141.polePairs;
			Global_Data.av.polepairs_right = Beckhoff_AM8141.polePairs;
			Global_Data.objects.current_ctrl_left = current_ctrl_left_init();
			Global_Data.objects.setpoint_ctrl_right = setpoint_ctrl_right_init();
			Global_Data.objects.speed_ctrl_right = speed_ctrl_right_init();
			Global_Data.objects.iir_filter_ref_speed = uz_signals_IIR_Filter_init(config);
			Global_Data.objects.movAvgFilt = uz_movingAverageFilter_init(config_MovAvg, circularBuffer);
			Global_Data.av.lambda_d = 1.0f;
			Global_Data.av.lambda_q = 1.0f;
			Global_Data.av.lambda_u_left = 0.0f; //0.000091f;
			Global_Data.av.lambda_u_e5_left = Global_Data.av.lambda_u_left * 1.0e5f;
			Global_Data.av.i_max_mpc = 1.2f;
			Global_Data.rasv.current_ctrl_select = PI_FOC;
            // parameters for automated trade-off curve measurements
            Global_Data.rasv.lambda_u_start = 0.0f;//0.000091;//0.00006;
            Global_Data.rasv.lambda_u_stop = 0.0004;
            Global_Data.rasv.lambda_u_step = 0.00001; // precision acc. to fixed-point data-type:
            Global_Data.rasv.lambda_u_now = Global_Data.rasv.lambda_u_start;
            Global_Data.rasv.cnt_lambda_u_end = (uint32_t)(ceilf((Global_Data.rasv.lambda_u_stop - Global_Data.rasv.lambda_u_start) / Global_Data.rasv.lambda_u_step))+1U;
            Global_Data.rasv.f_cnt_lambda_u_end = (float)Global_Data.rasv.cnt_lambda_u_end;
            Global_Data.rasv.cnt_lambda_u = 1U;
            Global_Data.rasv.f_cnt_lambda_u = 1.0f;
            Global_Data.av.pause_time_sec = 3.0f;

            Global_Data.rasv.lambda_u_LUT[0] = 0.0f;
            for(uint32_t i=1;i<=41;i++) {
            	Global_Data.rasv.lambda_u_LUT[i] = 9e-6*expf(0.1125*(float)i);
            };

            //deadtime comp parameters
            Global_Data.rasv.Ts_minus_Td_over_Ts = 0.94; //0.94 is valid for 150ns deadtime 0.8 is valid for 500ns deadtime
            Global_Data.rasv.Td_over_Ts = 1.0f-Global_Data.rasv.Ts_minus_Td_over_Ts;
            Global_Data.rasv.deadtime_comp_onoff = false;
			initialization_chain = init_ip_cores;
            break;
        case init_ip_cores:
            uz_adcLtc2311_ip_core_init();
            Global_Data.objects.deadtime_interlock_PWM_0 = uz_interlockDeadtime2L_staticAllocator_PWM_0();
            Global_Data.objects.deadtime_interlock_PWM_1 = uz_interlockDeadtime2L_staticAllocator_PWM_1();
            Global_Data.objects.deadtime_interlock_PWM_2 = uz_interlockDeadtime2L_staticAllocator_PWM_2();
            Global_Data.objects.deadtime_interlock_PWM_3 = uz_interlockDeadtime2L_staticAllocator_PWM_3();
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_PWM_0, true);
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_PWM_1, true);
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_PWM_2, true);
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_PWM_3, true);
            Global_Data.objects.pwm_0 = initialize_pwm_0_2l();
            Global_Data.objects.pwm_1 = initialize_pwm_1_2l();
            Global_Data.objects.pwm_2 = initialize_pwm_2_2l();
            Global_Data.objects.pwm_3 = initialize_pwm_3_2l();
            uz_axigpio_reset_pwm_counter(); //reset pwm counter of all instances in order to force synchronous start of all PWM modules
            Global_Data.objects.mux_axi_0 = initialize_uz_mux_axi_0();
            Global_Data.objects.mux_axi_1 = initialize_uz_mux_axi_1();
            Global_Data.objects.resolver_d5_1 = initialize_resolver_D5_1();
            Global_Data.objects.resolver_d5_2 = initialize_resolver_D5_2();
            Global_Data.objects.resolver_pl_interface_d5_1 = initialize_resolver_pl_interface_D5_1();
            Global_Data.objects.resolver_pl_interface_d5_2 = initialize_resolver_pl_interface_D5_2();
            Global_Data.objects.uz_d_inverter_d1 = initialize_inverter_D1();
            Global_Data.objects.uz_d_inverter_d2 = initialize_inverter_D2();
			//MPC init
			//uz_debug_ip
			fcs_mpc_real_or_debug_inputs(true); //false=debug, true=real
			//uz_pu_conversion_ip
			fcs_mpc_init_pu_conversion_ip();
			//uz_park_transform_ip
			fcs_mpc_init_park_transform();
			//uz_mpc_State_machine
			fcs_mpc_init_state_machine(8U); //state machine shall perform 8 iterations for the 8 switch positions
			//uz_pu_voltages
			fcs_mpc_init_pu_voltages(1U, 0U, 48.0f,
					Global_Data.rasv.Ts_minus_Td_over_Ts,
					Global_Data.rasv.Td_over_Ts,
					Global_Data.rasv.deadtime_comp_onoff); //0=index via AXI 1=index via PL | //0=v_dc via AXI 1=v_dc via PL measured
			//uz_pu_omega_m_conversion
			fcs_mpc_init_omega_m_pu_conversion();
			//delay_comp
			fcs_mpc_init_delay_comp();
			//prediction model
			fcs_mpc_init_prediction_model();
			//cost function
			fcs_mpc_init_cost_function();

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
            // update status of both inverters
            uz_inverter_adapter_update_states(Global_Data.objects.uz_d_inverter_d1);
            uz_inverter_adapter_update_states(Global_Data.objects.uz_d_inverter_d1);
            // assign status to Global_Data
            Global_Data.av.inverter_d1_status = uz_inverter_adapter_get_outputs(Global_Data.objects.uz_d_inverter_d1);
            Global_Data.av.inverter_d2_status = uz_inverter_adapter_get_outputs(Global_Data.objects.uz_d_inverter_d2);
            // calculate mean temperature values over all measured temperatures of each inverter
            Global_Data.av.mean_temp_inv_d1 = (Global_Data.av.inverter_d1_status.ChipTempDegreesCelsius_H1+Global_Data.av.inverter_d1_status.ChipTempDegreesCelsius_L1+Global_Data.av.inverter_d1_status.ChipTempDegreesCelsius_H2+Global_Data.av.inverter_d1_status.ChipTempDegreesCelsius_L2+Global_Data.av.inverter_d1_status.ChipTempDegreesCelsius_H3+Global_Data.av.inverter_d1_status.ChipTempDegreesCelsius_L3) * 0.1667;
            Global_Data.av.mean_temp_inv_d2 = (Global_Data.av.inverter_d2_status.ChipTempDegreesCelsius_H1+Global_Data.av.inverter_d2_status.ChipTempDegreesCelsius_L1+Global_Data.av.inverter_d2_status.ChipTempDegreesCelsius_H2+Global_Data.av.inverter_d2_status.ChipTempDegreesCelsius_L2+Global_Data.av.inverter_d2_status.ChipTempDegreesCelsius_H3+Global_Data.av.inverter_d1_status.ChipTempDegreesCelsius_L3) * 0.1667;

            break;
        default:
            break;
        }
    }
    return (status);
}
