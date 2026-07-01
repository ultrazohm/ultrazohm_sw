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
#define ISR_SAMPLE_FREQ_HZ 20000.0f

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
    .av.isr_samplerate_s = INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE / (UZ_PWM_FREQUENCY * Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}}};

const struct uz_IIR_Filter_config config_filter = {
  .selection = LowPass_first_order,
  .cutoff_frequency_Hz = 200.0f,
  .sample_frequency_Hz = ISR_SAMPLE_FREQ_HZ};

struct uz_dq_setpoint_filter_config config = {
  .config_filter_d = config_filter,
  .config_filter_q = config_filter};


struct uz_parameterid_rs_config_t config_rs_meas = {
		.n_start_rpm = 200.0f,
	    .n_end_rpm = 2200.0f,
	    .n_steps = 9.0f,
	    .i_pos_Amps = 50.0f,
	    .i_neg_Amps = -50.0f,
	    .i_repeats = 5.0f, // W
	    .i_steptime = 3.0f,
	    .wait_time = 20.0f,
	    .isr_steptime = (1.0f / ISR_SAMPLE_FREQ_HZ),
		.abs_iq_max_Amps = 50.0f,
		.check_temp = 1U
};


const struct uz_parameterID_rc_config_t rc_meas_config = {
  	.abs_id_max_Amps = 50.0f,
  	.abs_iq_max_Amps = 50.0f,
	.n_start_rpm = 100.0f,
	.n_stop_rpm = 100.0f,
	.id_steps = 5U,
	.iq_steps = 5U,
	.n_steps = 0U,
	.check_temp=1
  };

struct uz_encoder_offset_estimation_config encoder_offset_cfg = {               // config struct
    .ptr_measured_rotor_angle = &Global_Data.av.theta_elec,                     // pointer to the measured electric rotor angle (raw, not offset corrected)
    .ptr_offset_angle = &Global_Data.av.theta_offset,                           // pointer to global variable holding the offset angle
    .ptr_actual_omega_el = &Global_Data.av.omega_el,                            // pointer to actual electric rotor angular speed
    .ptr_actual_u_q_V = &Global_Data.av.U_q,                                    // pointer to q-setpoint voltage
    .min_omega_el = 1300.0f,                                                     // target electric rotor angular speed (USE OWN)
    .setpoint_current = 30.0f};    // current setpoint to reach speed (USE OWN)

struct uz_wavegen_chirp_config config_chirp = {
        .amplitude = 15.0f,
        .start_frequency_Hz = 1.0f,
        .end_frequency_Hz = 7000.0f,
        .duration_sec = 5.0f,
        .initial_delay_sec = 0.0f,
        .offset = 150.0f
};

const struct uz_resonantController_config config_R = {
    .sampling_time = 1/ISR_SAMPLE_FREQ_HZ,
    .gain = 1.0f,
    .harmonic_order = 6.0f,
    .fundamental_frequency = 0.0f,
    .lower_limit = -8.0f,
    .upper_limit = 8.0f,
    .antiwindup_gain = 1.0f,
    .in_reference_value = 0.0f,
    .in_measured_value = 0.0f,
};

static float dead_time_lut_currents_A[41] = {
    -25.0000000f, -23.7500000f, -22.5000000f, -21.2500000f, -20.0000000f, -18.7500000f, -17.5000000f, -16.2500000f, -15.0000000f, -13.7500000f,
    -12.5000000f, -11.2500000f, -10.0000000f, -8.7500000f, -7.5000000f, -6.2500000f, -5.0000000f, -3.7500000f, -2.5000000f, -1.2500000f,
    0.0000000f, 1.2500000f, 2.5000000f, 3.7500000f, 5.0000000f, 6.2500000f, 7.5000000f, 8.7500000f, 10.0000000f, 11.2500000f,
    12.5000000f, 13.7500000f, 15.0000000f, 16.2500000f, 17.5000000f, 18.7500000f, 20.0000000f, 21.2500000f, 22.5000000f, 23.7500000f, 25.0000000f
};

static float dead_time_lut_values[41] = {
    -1.0000000f, -0.9988809f, -0.9974101f, -0.9954759f, -0.9929302f,
    -0.9895774f, -0.9851575f, -0.9793256f, -0.9716230f, -0.9614383f,
    -0.9479550f, -0.9300800f, -0.9063454f, -0.8747726f, -0.8326819f,
    -0.7764207f, -0.7009650f, -0.5993062f, -0.4614183f, -0.2721095f,
    0.0000000f, 0.2721095f, 0.4614183f, 0.5993062f, 0.7009650f,
    0.7764207f, 0.8326819f, 0.8747726f, 0.9063454f, 0.9300800f,
    0.9479550f, 0.9614383f, 0.9716230f, 0.9793256f, 0.9851575f,
    0.9895774f, 0.9929302f, 0.9954759f, 0.9974101f, 0.9988809f, 1.0000000f
};

struct uz_VoltageCompensation_config VoltComp_config = {
	 .dead_time_us = 0.6489075f,
	 .enable_dead_time_compensation = 1U,
	 .enable_on_delay_time_compensation = 0U,
	 .enable_voltage_drop_compensation = 0U,
	 .enable_R_on_compensation = 0U,
	 .switching_frequency_Hz = UZ_PWM_FREQUENCY,
	 .threshold_current = 25.0000000f,
	 .dead_time_compensation_type = UZ_VOLTAGE_COMPENSATION_DEAD_TIME_USE_EXPONENTIAL_FUNCTION,
	 .dead_time_exp_A = 1.0035966f,
	 .dead_time_exp_B = 0.2415270f,
	 .dead_time_exp_C = 0.9612082f,
	 .dead_time_exp_S = 1.1f,
	 .dead_time_lut_currents_A = dead_time_lut_currents_A,
	 .dead_time_lut_values = dead_time_lut_values,
	 .dead_time_lut_size = 41,
	 .R_on_mOhm = 3.5f
};


enum init_chain
{
    init_assertions_and_wait_for_apu_handshake = 0,
    init_gpios,
    init_software,
    init_ip_cores,
    print_msg,
    init_interrupts,
    infinite_loop
};
enum init_chain initialization_chain = init_assertions_and_wait_for_apu_handshake;
#include "APU_RPU_shared.h"
#include "xil_cache.h"

uint32_t apu_version_final = 0;
uint32_t rpu_version_final = 0;

int main(void)
{
    int status = UZ_SUCCESS;
    while (1)
    {
        switch (initialization_chain)
        {
        case init_assertions_and_wait_for_apu_handshake:
            uz_assert_configuration(); 
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

            struct uz_PMSM_t config_PMSM = {
               .Ld_Henry = 0.00001159f,				// 0.000027 fuer seg-rotor
               .Lq_Henry = 0.000016663f,				// 0.000042 fuer seg_rotor
               .Psi_PM_Vs = 0.0041939f,				// Leerlauf 80�C,  0.0071f (SM) oder 0.0073 (SEG) im Strang --> Umrechnung Sternschaltung fuer Umrichter
               .polePairs = 21.0f,
               .J_kg_m_squared = 0.032972f,			// J_motor = 0.00156 kgm2 + J_T40B = 0.0015 + J_Kupplung= 0.005 + J_Last = 0.0249
               .R_ph_Ohm = 0.0071f,					// Gemessen aus Sollspannugn UZ
               .I_max_Ampere = 250.0f
             };//these parameters are only needed if linear decoupling is selected

             struct uz_PI_Controller_config config_id = {
               .Kp = 0.0509f,						// 0.1 seg-rotor, 0.08 SM-PMSM /  Betragsoptimum: 2.8975
               .Ki = 54.7f,					// 173.3 seg-rotor, 87 SM-PMSM / Betragsoptimum: 1775
			   .type = UZ_PI_PARALLEL,
               .samplingTime_sec = 1.0f/ISR_SAMPLE_FREQ_HZ
            };

            struct uz_PI_Controller_config config_iq = {
               .Kp = 0.0578f,						// 0.2 seg-rotor, 0.08 SM-PMSM / Opt: 4.16575
			   .Ki = 54.7f,						// 173.3 seg-rotor, 87 SM-PMSM / Opt: 1775
			   .type = UZ_PI_PARALLEL,
               .samplingTime_sec = 1.0f/ISR_SAMPLE_FREQ_HZ
            };
            struct uz_CurrentControl_config FOC_config = {
               .decoupling_select = linear_decoupling,
               .config_PMSM = config_PMSM,
               .config_id = config_id,
               .config_iq = config_iq,
               .max_modulation_index = 1.0f/sqrt(3.0f)
            };
            Global_Data.objects.FOC_instance = uz_CurrentControl_init(FOC_config);
            struct uz_SetPoint_config SP_config = {
                  .config_PMSM = config_PMSM,
                  .motor_type = IPMSM,
                  .is_field_weakening_enabled = false,
                  .id_ref_Ampere = 0.0f,
                  .relative_torque_tolerance = 0.001f
            };
            Global_Data.objects.current_setpoint_obj = uz_SetPoint_init(SP_config);
            Global_Data.rasv.flg_use_setpoint_calculation = 0.0f;
            Global_Data.objects.dq_setpoint_filter = uz_uz_dq_setpoint_filter_init(config);
            Global_Data.av.theta_offset = -0.0195f;
            Global_Data.objects.pll_0 = pll_0_init();

            Global_Data.objects.encoder_offset_obj = uz_encoder_offset_estimation_init(encoder_offset_cfg);
            Global_Data.objects.rs_meas_instance = uz_parameterid_rs_init(config_rs_meas);
            Global_Data.objects.rc_meas_instance = uz_parameterID_rc_init(rc_meas_config);

            Global_Data.objects.chirp_instance = uz_wavegen_chirp_init(config_chirp);
            Global_Data.objects.R_controller_instance_d = uz_resonantController_init(config_R);
            Global_Data.objects.R_controller_instance_q = uz_resonantController_init(config_R);
            Global_Data.rasv.flg_use_ResonantController = 0.0f;
            Global_Data.rasv.flg_use_voltComp = 0.0f;
            Global_Data.objects.VoltageComp_instance = uz_VoltageCompensation_init(VoltComp_config);

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

            // AXI GPIOs
            Global_Data.objects.mux_axi = initialize_uz_mux_axi();
            struct uz_axi_gpio_config_t config_input = {
                        		.base_address = XPAR_UZ_SYSTEM_UZ_ENABLE_AXI_GPIO_0_BASEADDR ,
                        		.device_id = XPAR_UZ_SYSTEM_UZ_ENABLE_AXI_GPIO_0_DEVICE_ID,
                        		.number_of_pins = 4,
                        		.direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_INPUT
                        };
            struct uz_axi_gpio_config_t config_output = {
                        		.base_address = XPAR_UZ_SYSTEM_UZ_ENABLE_AXI_GPIO_2_BASEADDR ,
                        		.device_id = XPAR_UZ_SYSTEM_UZ_ENABLE_AXI_GPIO_2_DEVICE_ID,
                        		.number_of_pins = 8,
                        		.direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT
                        };
            struct uz_axi_gpio_config_t config_output_LMG = {
                        		.base_address = XPAR_UZ_USER_AXI_GPIO_0_BASEADDR ,
                        		.device_id = XPAR_UZ_USER_AXI_GPIO_0_DEVICE_ID,
                        		.number_of_pins = 6,
                        		.direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT
                        };
            Global_Data.objects.input_gpio = uz_axi_gpio_init(config_input);
            Global_Data.objects.output_gpio = uz_axi_gpio_init(config_output);
            Global_Data.objects.output_gpio_LMG = uz_axi_gpio_init(config_output_LMG);
            uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio_LMG, 1, 1U);

            // Temperature Card
            Global_Data.objects.temperature_card_d3 = initialize_temperature_card_d3();
            uz_TempCard_IF_Reset(Global_Data.objects.temperature_card_d3);
            uz_TempCard_IF_Start(Global_Data.objects.temperature_card_d3);

            // EnDat
            Global_Data.objects.endat_encoder_d5_3 = endat_encoder_init_endat_d5_3();
            uz_endat_interface_enable_ip(Global_Data.objects.endat_encoder_d5_3, true);
            initialization_chain = print_msg;
            break;
        case print_msg:
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
            uz_printf("RPU Build Date of main.c: %s at %s,\r\n", __DATE__, __TIME__);
            uz_print_bitstream_timestamp();
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
