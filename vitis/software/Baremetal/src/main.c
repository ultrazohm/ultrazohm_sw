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

//ParameterID Code
#include "uz/uz_ParameterID/uz_ParameterID_6ph.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "uz/uz_math_constants.h"
uz_ParameterID_6ph_t* ParameterID = NULL;
uz_ParameterID_Data_t ParaID_Data = { 0 };
struct uz_SpeedControl_config speed_config = { .config_controller.type =
		parallel, .config_controller.Kp = 1.0f, .config_controller.Ki = 1.0f,
		.config_controller.samplingTime_sec = 0.0001f,
		.config_controller.upper_limit = 10.0f, .config_controller.lower_limit =
				-10.0f };

extern uz_6ph_dq_t controller_out;

struct uz_IIR_Filter_config config_filter = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 1.0f, .sample_frequency_Hz = 10000.0f};
//ParameterID end

float meas_array[10000];

// Temperaturemeasurement
#include "IP_Cores/uz_temperaturecard/uz_temperaturecard.h"
uz_temperaturecard_t* uz_Tempcard = NULL;
struct uz_temperaturecard_config_t t_config = {
    .base_address = XPAR_UZ_USER_TEMP_CARD_INTERFACE_TEMPERATURE_CARD_INT_0_BASEADDR,
    .ip_clk_frequency_Hz = 100000000,
    .Sample_Freq = 100,
    .Configdata_A = {0},
	.Configdata_A[4-1]  = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[6-1]  = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[8-1]  = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[10-1] = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[12-1] = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[14-1] = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[2-1] = 0xE80FA000,//(SENSOR_TYPE__SENSE_RESISTOR) + (SENSE_RESISTOR_VALUE),
	.Configdata_B = {0},
	.Configdata_C = {0}};

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
            Global_Data.av.theta_mech_offset_rad = 6.14;
            Global_Data.av.polepairs = 5.0f;

            // Init ParaID
			ParameterID = uz_ParameterID_6ph_init(&ParaID_Data);
			// Init controller configs


			struct uz_PI_Controller_config PI_config_dq = {
					.Ki = 1000.0f,
					.Kp = 5.0f,
					.samplingTime_sec = ParaID_Data.GlobalConfig.sampleTimeISR,
					.lower_limit = -20.0f,
					.upper_limit = 20.0f };
			struct uz_PI_Controller_config PI_config_xy = {
					.Ki = 500.0f,
					.Kp = 15.0f,
					.samplingTime_sec = ParaID_Data.GlobalConfig.sampleTimeISR,
					.lower_limit = -20.0f,
					.upper_limit = 20.0f };
			struct uz_CurrentControl_config cc_config_1 = {
					.decoupling_select = linear_decoupling,
					.config_id = PI_config_dq,
					.config_iq = PI_config_dq,
					.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config,
					.max_modulation_index = 1/sqrtf(3.0f)};
			struct uz_CurrentControl_config cc_config_2 = {
					.decoupling_select = no_decoupling,
					.config_id = PI_config_xy,
					.config_iq = PI_config_xy,
					.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config,
					.max_modulation_index = 1/sqrtf(3.0f)};
			struct uz_PI_Controller_config PI_config_zero = {
				.Ki = 100.0f,
				.Kp = 15.0f,
				.samplingTime_sec = ParaID_Data.GlobalConfig.sampleTimeISR,
				.lower_limit = -20.0f,
				.upper_limit = 20.0f};
			struct uz_CurrentControl_config cc_config_3 = {
				.decoupling_select = no_decoupling,
				.config_id = PI_config_zero,
				.config_iq = PI_config_zero,
				.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config,
				.max_modulation_index = 1/sqrtf(3.0f)};
			struct uz_resonantController_config resonant_config_dq = {
					.sampling_time = ParaID_Data.GlobalConfig.sampleTimeISR,
					.gain = 1000.0f,
					.harmonic_order = 2.0f,
					.fundamental_frequency = 1.0f,
					.lower_limit = -5.0f,
					.upper_limit = 5.0f,
					.antiwindup_gain = 100.0f,
					.in_reference_value = 0.0f,
					.in_measured_value = 0.0f };
			struct uz_resonantController_config resonant_config_xy = resonant_config_dq;
			resonant_config_xy.harmonic_order = 6.0f;
			resonant_config_xy.gain = 1000.0f;
			struct uz_resonantController_config resonant_config_zero = resonant_config_dq;
			resonant_config_zero.harmonic_order = 6.0f;
			resonant_config_zero.gain = 500.0f;
			struct uz_SetPoint_config sp_config = {
					.id_ref_Ampere = 0.0f,
					.is_field_weakening_enabled = false,
					.motor_type = SMPMSM,
					.control_type = FOC,
					.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config};

			// ParaID inits
			uz_ParameterID_6ph_init_controllers(&ParaID_Data, sp_config, speed_config, cc_config_1, cc_config_2, cc_config_1, resonant_config_dq, resonant_config_xy, resonant_config_zero);
			uz_ParameterID_6ph_init_filter(&ParaID_Data, config_filter);
			uz_ParameterID_6ph_initialize_encoder_offset_estimation(&ParaID_Data, &Global_Data.av.theta_elec_rad, &controller_out.q);
			// ParaID inits end
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
            Global_Data.objects.resolver_d5_1 = init_resolver_at_d5_1();
            Global_Data.objects.tempMeasurement1 = init_tempMeasurement1();
            Global_Data.objects.tempMeasurement2 = init_tempMeasurement2();
            // uz tempcard
            uz_Tempcard = uz_temperaturecard_init(t_config);
			uz_TempCard_IF_Reset(uz_Tempcard);
			uz_TempCard_IF_Start(uz_Tempcard);
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

