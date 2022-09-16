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

#include "xtest_data_signals.h"
#include "xuz_log_data.h"
#include "xbram.h"

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

XTest_data_signals PL_Data_1;	// instance of test_data_signals IP Core
XUz_log_data PL_Logger_1;		// instance of uz_log_data IP Core
//XBram BRAM_LogData;				// instance of BRAM

int main(void)
{
	XTest_data_signals_Config *PL_Data_Config;
	XUz_log_data_Config *PL_Logger_Config;

	//XBram_Config *BRAM_LogData_Config;
	//call bram
	//BRAM_LogData_Config = XBram_LookupConfig(XPAR_UZ_USER_AXI_BRAM_CTRL_0_DEVICE_ID);
	//XBram_CfgInitialize(&BRAM_LogData, BRAM_LogData_Config, BRAM_LogData_Config->CtrlBaseAddress);

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
            initialization_chain = print_msg;

            //call the test_data_pl signal generation
            PL_Data_Config = XTest_data_signals_LookupConfig(XPAR_UZ_USER_TEST_DATA_SIGNALS_0_DEVICE_ID);
            XTest_data_signals_CfgInitialize(&PL_Data_1, PL_Data_Config);

            //call data logger
            PL_Logger_Config = XUz_log_data_LookupConfig(XPAR_UZ_USER_UZ_LOG_DATA_0_DEVICE_ID);
            XUz_log_data_CfgInitialize(&PL_Logger_1, PL_Logger_Config);

            //call bram
            //BRAM_LogData_Config = XBram_LookupConfig(XPAR_UZ_USER_AXI_BRAM_CTRL_0_DEVICE_ID);
            //XBram_CfgInitialize(&BRAM_LogData, BRAM_LogData_Config, BRAM_LogData_Config->CtrlBaseAddress);

            //control for int-float-apfixed-float-apfixed-float-apfixed
            u32 control_signal_1 = 0b00000000000000000000000001010101;
            u32 control_signal_2 = 0b00000000000000000000000001111110;
            XUz_log_data_Set_control_1(&PL_Logger_1, control_signal_1);
            XUz_log_data_Set_control_2(&PL_Logger_1, control_signal_2);

            //u64 OCM_BASE_ADDRESS = 0x00FFFC0000;
            //int *OCM_BASE_ADDRESS = (int *) 0x00FFFC0000;
            // casten !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            float PL_Data_amp = 2.0f;
            float PL_Data_freq = 5e2f;
            int PL_Data_period = 16;//0.5f;
            u32 *PL_Data_amp_u32 = ((u32*)&PL_Data_amp);
            u32 *PL_Data_freq_u32 = ((u32*)&PL_Data_freq);
            u32 *PL_Data_period_u32 = ((u32*)&PL_Data_period);

            // OCM:
            //XUz_log_data_Set_dlog_1(&PL_Logger_1, OCM_BASE_ADDRESS);

            XTest_data_signals_Set_amplitude(&PL_Data_1, *PL_Data_amp_u32);
            //XTest_data_signal_generation_Set_frequency(&PL_Data_1, 5e2f);
            //XTest_data_signal_generation_Set_dutycycle(&PL_Data_1, 0.5f);
            //XTest_data_signal_generation_Set_increment(&PL_Data_1, 1.0f);
            XTest_data_signals_Set_frequency(&PL_Data_1, *PL_Data_freq_u32);
            XTest_data_signals_Set_period(&PL_Data_1, *PL_Data_period_u32);

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
