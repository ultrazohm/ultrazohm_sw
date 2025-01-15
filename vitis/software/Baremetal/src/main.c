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
#include "uz/uz_fixedpoint/uz_fixedpoint.h"

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

struct uz_IIR_Filter_config config_IIR_invTemp = { .selection = LowPass_first_order,
   		.cutoff_frequency_Hz = 0.5f, .sample_frequency_Hz = UZ_PWM_FREQUENCY};

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

    struct uz_fixedpoint_definition_t current_limit_SI = {
    		.is_signed = true,
    		.integer_bits = 12,
    		.fractional_bits = 15
    };

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
            Global_Data.av.i_max_cur_lim_ip_SI = 20.0f;
            Global_Data.av.polepairs = 5.0f;
            Global_Data.av.offset_el_incre = 945U;
            Global_Data.av.lambda_dq = 10.0f;
            Global_Data.av.lambda_xy = 10.0f;
            Global_Data.av.solver_tolerance = 1e-6f;
            Global_Data.av.max_iter = 20.0f; //no effect with quadprog implementation
            Global_Data.rasv.current_ctrl_select = PI_FOC;
            Global_Data.rasv.a53_ctrl_off_on = false;
            Global_Data.av.angle_lead_factor_FOC = 1.5f;
            Global_Data.av.angle_lead_factor_MPC = 2.5f;
            Global_Data.av.kalman_R = 1.0f;
            Global_Data.av.kalman_Q1 = 100.0f;
            Global_Data.av.kalman_Q2 = 1.0f;
            Global_Data.av.phiPM_h[0] = 4.6f;//-0.1349143; //psi pm initialized in FOC_init.c
            Global_Data.av.phiPM_h[1] = 2.9f;//-1.7723498;
            Global_Data.av.Rs = 0.27;
            Global_Data.av.Ld = 1.7e-3;
            Global_Data.av.Lq = 3.8e-3;
            Global_Data.av.Lx = 2.7e-3;
            Global_Data.av.Ly = 2.7e-3;
            Global_Data.av.psi_pm = 0.19;
            Global_Data.objects.foc_current_dq = init_FOC_CurrentControl();
            Global_Data.objects.foc_current_xy = init_FOC_xy_control();
            Global_Data.objects.resonant_dq2 = init_resonant_control_dq_2();
            Global_Data.objects.resonant_xy2 = init_resonant_control_xy_2();
            Global_Data.objects.resonant_xy6 = init_resonant_control_xy_6();
            Global_Data.objects.speed_ref_filt = speed_ref_filt_init();
            Global_Data.objects.setpoint = setpoint_init();
            Global_Data.objects.speed_control = speed_control_init();
            Global_Data.objects.invTemp1_filter = uz_signals_IIR_Filter_init(config_IIR_invTemp);
            Global_Data.objects.invTemp2_filter = uz_signals_IIR_Filter_init(config_IIR_invTemp);
            Global_Data.objects.sysmon = init_sysmon();
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
            Global_Data.objects.tempMeasurement1 = init_InverterTempMeasurement1();
            Global_Data.objects.tempMeasurement2 = init_InverterTempMeasurement2();
            Global_Data.objects.resolver_d5_1 = init_resolver_at_d5_1();
            Global_Data.objects.resolver_pl_interface = initialize_resolver_pl_interface();
            Global_Data.objects.temperature_card_d4 = initialize_temperature_card_d4();
            uz_TempCard_IF_Reset(Global_Data.objects.temperature_card_d4);
            uz_TempCard_IF_Start(Global_Data.objects.temperature_card_d4);
            Global_Data.objects.inv_fault_in = init_inverter_fault_axi_gpio();
            Global_Data.objects.encoder_D3 = initialize_incremental_encoder_ipcore_on_D3(UZ_D3_INCREMENTAL_ENCODER_RESOLUTION, UZ_D3_MOTOR_POLE_PAIR_NUMBER);
            uz_incrementalEncoder_set_electrical_Offset(Global_Data.objects.encoder_D3, Global_Data.av.offset_el_incre);
            // current limit detection ip
            uz_fixedpoint_axi_write(XPAR_UZ_USER_UZ_CUR_LIM_0_BASEADDR + 0x100, Global_Data.av.i_max_cur_lim_ip_SI, current_limit_SI);

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

        	// read temperature values from inverters
        	Global_Data.av.tempPWMoutputs1 = uz_PWM_duty_freq_detection_get_outputs(Global_Data.objects.tempMeasurement1);
        	Global_Data.av.tempPWMoutputs2 = uz_PWM_duty_freq_detection_get_outputs(Global_Data.objects.tempMeasurement2);
        	Global_Data.av.temperature_inv_1 = uz_signals_IIR_Filter_sample(Global_Data.objects.invTemp1_filter, Global_Data.av.tempPWMoutputs1.TempDegreesCelsius);
        	Global_Data.av.temperature_inv_2 = uz_signals_IIR_Filter_sample(Global_Data.objects.invTemp2_filter, Global_Data.av.tempPWMoutputs2.TempDegreesCelsius);
        	// read temperature values from winding
        	uz_TempCard_IF_MeasureTemps_cyclic(Global_Data.objects.temperature_card_d4);
            Global_Data.av.channel_A_data = uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_d4, 'A');
            Global_Data.av.average_winding_temp = uz_TempCard_IF_average_temperature_for_valid(Global_Data.av.channel_A_data, 3U, 13U);
//            // reset the error reset flag, to re-arm the error reset button
//            uz_axi_write_bool(XPAR_UZ_CUR_LIM_0_BASEADDR + 0x104, false);
            // read zynq temperature from sysmon
            Global_Data.av.zynq_temp = uz_sysmon_ps_read_temperature_degree_celsius(Global_Data.objects.sysmon);

            break;
        default:
            break;
        }
    }
    return (status);
}
