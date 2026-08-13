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
		.setpoint_trajectories_enabled = true,
		.im_frequency_reference_Hz = MOTOR_Default_u_f_frequency_Hz,
		.im_i_d_reference_A = MOTOR_Default_i_d_reference_A,
		.im_i_q_reference_A = MOTOR_Default_i_q_reference_A,
		.im_speed_reference_rpm = 0.0f,
		.im_enable_foc = false,
		.im_enable_speed_control = false,
		.im_enable_kalman_filter = false,
		.im_enable_resonant_control = false,
/* Project Wizard BEGIN: rasv_initializer */
        .pwm_2L_0_halfBridgeDutyCycle_1 = 0.0f,
        .pwm_2L_0_halfBridgeDutyCycle_2 = 0.0f,
        .pwm_2L_0_halfBridgeDutyCycle_3 = 0.0f,
        .pwm_2L_1_halfBridgeDutyCycle_1 = 0.0f,
        .pwm_2L_1_halfBridgeDutyCycle_2 = 0.0f,
        .pwm_2L_1_halfBridgeDutyCycle_3 = 0.0f,
        .pwm_3L_0_halfBridgeDutyCycle_1 = 0.0f,
        .pwm_3L_0_halfBridgeDutyCycle_2 = 0.0f,
        .pwm_3L_0_halfBridgeDutyCycle_3 = 0.0f,
/* Project Wizard END: rasv_initializer */
    },
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE / (UZ_PWM_FREQUENCY * Interrupt_ISR_freq_factor)};

enum init_chain
{
    init_assertions = 0,
    wait_for_apu_handshake,
    init_gpios,
    init_software,
    init_ip_cores,
    print_msg,
    init_interrupts,
    infinite_loop
};
enum init_chain initialization_chain = init_assertions;
#include "APU_RPU_shared.h"
#include "xil_cache.h"
#include "xparameters.h"

static const struct uz_PWM_duty_freq_detection_config_t inverter_temperature_pwm_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_UZ_PWMDUTYFREQDETECT_0_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
};

static void initialize_setpoint_trajectories(void)
{
	const float initial_values[SETPOINT_TRAJECTORY_COUNT] = {
		Global_Data.rasv.im_i_d_reference_A,
		Global_Data.rasv.im_i_q_reference_A,
		Global_Data.rasv.im_frequency_reference_Hz,
		Global_Data.rasv.im_speed_reference_rpm,
	};
	for (uint32_t trajectory = 0U; trajectory < SETPOINT_TRAJECTORY_COUNT; trajectory++) {
		struct uz_Trajectory_config config = {
			.selection_interpolation = Linear,
			.selection_XAxis = Seconds,
			.StopStyle = ForceToZero,
			.RepeatStyle = Repeat_Times,
			.Number_Sample_Points = 2U,
			.Repeats = 1U,
			.Stepwidth_ISR = Global_Data.av.isr_samplerate_s,
		};
		for (uint32_t sample = 0U; sample < MAX_TRAJECTORY_SAMPLES; sample++) {
			config.Sample_Amplitude_Y[sample] = 0.0f;
			config.Sample_Duration_X[sample] = 1.0f;
		}
		/* The trajectory supplies a normalized remaining-distance factor.
		 * The ISR stops it at zero before uz_Trajectory's return segment. */
		config.Sample_Amplitude_Y[0] = 1.0f;
		Global_Data.objects.setpoint_trajectories[trajectory] = (setpoint_trajectory_state_t){
			.instance = uz_Trajectory_init(config),
			.start = initial_values[trajectory],
			.target = initial_values[trajectory],
			.active_target = initial_values[trajectory],
		};
	}
}

uint32_t apu_version_final = 0;
uint32_t rpu_version_final = 0;

int main(void)
{
    int status = UZ_SUCCESS;
    while (1)
    {
        switch (initialization_chain)
        {
        case init_assertions:
            uz_rpu_assert_configuration();
            initialization_chain = wait_for_apu_handshake;
            break;
        case wait_for_apu_handshake:
            write_rpu_version(0U);
            do
            {
                apu_version_final = read_apu_version();
            } while (!(apu_version_final == 257U));
            write_rpu_version(UZ_HARDWARE_VERSION);
            do
            {
                apu_version_final = read_apu_version();
            } while ((apu_version_final == 257U));
            write_rpu_version(apu_version_final);
            initialization_chain = init_gpios;
            break;
        case init_gpios:
        	uz_sleep_seconds(5);
            Initialize_AXI_GPIO();
            uz_assert((apu_version_final > 0U) && (apu_version_final <= UZ_HARDWARE_VERSION_MAX));
            uz_frontpanel_button_and_led_init(apu_version_final);
            ultrazohm_state_machine_init(apu_version_final);
            initialization_chain = init_software;
            break;
        case init_software:
            uz_SystemTime_init();
            JavaScope_initialize(&Global_Data);
			IM_testbench_init(&Global_Data);
			initialize_setpoint_trajectories();
            initialization_chain = init_ip_cores;
            break;
        case init_ip_cores:
            /* Project Wizard BEGIN: init_ip_cores */
			Global_Data.objects.project_wizard_deadtime_2l_0 = initialize_project_wizard_deadtime_2l_0();
			uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.project_wizard_deadtime_2l_0, true);
			Global_Data.objects.project_wizard_pwm_2l_0 = initialize_project_wizard_pwm_2l_0();
			Global_Data.objects.project_wizard_deadtime_2l_1 = initialize_project_wizard_deadtime_2l_1();
			uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.project_wizard_deadtime_2l_1, true);
			Global_Data.objects.project_wizard_pwm_2l_1 = initialize_project_wizard_pwm_2l_1();
			initialize_project_wizard_pwm_3l(&Global_Data);
			Global_Data.objects.adc_ltc2311_a1 = initialize_adc_ltc2311_a1();
			Global_Data.objects.adc_ltc2311_a2 = initialize_adc_ltc2311_a2();
			Global_Data.objects.axi_gpio_d1 = initialize_axi_gpio_d1();
			Global_Data.objects.inverter_adapter_d2 = initialize_inverter_adapter_d2();
			Global_Data.objects.incremental_encoder_d5_1 = initialize_incremental_encoder_d5_1();
			Global_Data.objects.incremental_encoder_d5_2 = initialize_incremental_encoder_d5_2();
			Global_Data.objects.incremental_encoder_d5_3 = initialize_incremental_encoder_d5_3();
			Global_Data.objects.inverter_temperature_pwm = uz_PWM_duty_freq_detection_init(inverter_temperature_pwm_config);
/* Project Wizard END: init_ip_cores */
            initialization_chain = print_msg;
            break;
        case print_msg:
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
            uz_printf("RPU: Build Date of main.c: %s at %s,\r\n", __DATE__, __TIME__);
            uz_print_bitstream_timestamp();
            uz_print_control_frequency(Global_Data.av.pwm_frequency_hz, Global_Data.av.isr_samplerate_s);
            initialization_chain = init_interrupts;
            break;
        case init_interrupts:
            uz_axigpio_enable_datamover();
            Initialize_ISR();
            Global_Data.objects.mux_axi = initialize_uz_mux_axi(); // Initialize the Interrupt-Mux - last line of code before infinite loop
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
