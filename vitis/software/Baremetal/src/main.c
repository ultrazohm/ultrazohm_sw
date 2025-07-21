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
int Fehler = 0;
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
	.av.select_CurrentControl = false,
    .av.select_Real = false,
	.av.select_CIL = false,
	.av.n_ref_rpm = 0.0f,
	.av.i_d_ref = 0.0f,
	.av.i_q_ref = 0.0f,
	.av.i_X_ref = 0.0f,
	.av.i_Y_ref = 0.0f,
	.av.v_dqxy_limited_volts = {0},
    .av.v_dq_limited_volts = {0},
	.av.v_xy_limited_volts = {0},
	.av.v_dq_non_limited_volts = {0},
	.av.v_xy_non_limited_volts = {0},
	.av.v_dqxy_limited_volts_k_old = {0},
	.av.v_dqxy_non_limited_volts = {0},
	.av.CIL_i_dqxy_meas = {0},
	.av.REAL_i_abc_meas = {0},
	.av.REAL_v_abc_meas = {0},
	.av.REAL_v_abc_ref = {0},
	.av.REAL_i_dqxy_meas = {0},
	.av.REAL_v_dqxy_meas = {0},
	.av.CIL_v_dq_reference = {0},
	.av.CIL_v_xy_reference = {0},
	.av.CIL_v_z1z2_reference = {0},
	.av.REAL_v_dq_reference = {0},
	.av.REAL_v_xy_reference = {0},
	.av.REAL_v_z1z2_reference = {0},
	.av.i_dq_reference = {0},
	.av.i_xy_reference = {0},
	.av.i_z1z2_reference = {0},
	.av.CIL_i_dq_meas= {0},
	.av.CIL_i_xy_meas = {0},
	.av.CIL_i_z1z2_meas = {0},
	.av.REAL_i_dq_meas= {0},
	.av.REAL_i_xy_meas = {0},
	.av.REAL_i_z1z2_meas = {0},
	.av.DutyCycle_output = {0},
   	.av.phaseshiftoption = {0},
	.av.shift_system_1 = {0},
	.av.shift_system_2 = {0},
	.av.phi_rad = {0},
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
    	   .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
		   .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}
    }
};


struct uz_IIR_Filter_config IIR_config = {
		.selection = LowPass_first_order,
		.cutoff_frequency_Hz = 100.0f,
		.sample_frequency_Hz = 10000.0f};

uz_IIR_Filter_t* uz_signals_IIR_Filter_init(IIR_config);


enum init_chain
{
    init_assertions = 0,
    init_gpios,
    init_software,
	init_CurrentControl,
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

            Global_Data.objects.IRR_filter_A1 = uz_signals_IIR_Filter_init(IIR_config);
            Global_Data.objects.IRR_filter_B1 = uz_signals_IIR_Filter_init(IIR_config);
            Global_Data.objects.IRR_filter_C1 = uz_signals_IIR_Filter_init(IIR_config);
            Global_Data.objects.IRR_filter_A2 = uz_signals_IIR_Filter_init(IIR_config);
            Global_Data.objects.IRR_filter_B2 = uz_signals_IIR_Filter_init(IIR_config);
            Global_Data.objects.IRR_filter_C2 = uz_signals_IIR_Filter_init(IIR_config);

            initialization_chain = init_CurrentControl;
            break;

        case init_CurrentControl:
        	Global_Data.objects.CC_dq_instance = init_dq_FOC();
        	Global_Data.objects.CC_xy_instance = init_xy_FOC();
        	initialization_chain = init_ip_cores;
        	break;

        case init_ip_cores:
            uz_adcLtc2311_ip_core_init();
            Global_Data.objects.deadtime_interlock_d1_pin_0_to_5 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_0_to_5();
            Global_Data.objects.deadtime_interlock_d1_pin_6_to_11 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_6_to_11();
            Global_Data.objects.deadtime_interlock_d1_pin_12_to_17 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_12_to_17();
            Global_Data.objects.deadtime_interlock_d1_pin_18_to_23 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_18_to_23();
            Global_Data.objects.inverter_d1 = initialize_uz_inverter_adapter_on_D1();
            Global_Data.objects.inverter_d2 = initialize_uz_inverter_adapter_on_D2();
            Global_Data.objects.CIL_pmsm = init_CIL_6ph_PMSM();
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
