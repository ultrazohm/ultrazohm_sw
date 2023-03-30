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
// controller
uz_CurrentControl_t* CC_instance_1 = NULL;
uz_CurrentControl_t* CC_instance_2 = NULL;
uz_CurrentControl_t* CC_instance_3 = NULL;
uz_SpeedControl_t* Speed_instace = NULL;
uz_SetPoint_t* sp_instance = NULL;
uz_resonantController_t* res_instance_1 = NULL;
uz_resonantController_t* res_instance_2 = NULL;
//ParameterID end

// controller configs
const float isr_ts = 0.0001f;
const float tau_sum = 2*isr_ts;
struct uz_SpeedControl_config speed_config = {
		.config_controller.type = parallel,
		.config_controller.Kp = 1.0f,
		.config_controller.Ki = 1.0f,
		.config_controller.samplingTime_sec = 0.0001f,
		.config_controller.upper_limit = 10.0f,
		.config_controller.lower_limit = -10.0f};
struct uz_SetPoint_config sp_config = {
		.id_ref_Ampere = 0.0f,
		.is_field_weakening_enabled = false,
		.motor_type = SMPMSM,
		.control_type = FOC};
//end
// setpoint filters for ParaID
#include "uz/uz_signals/uz_signals.h"
struct uz_IIR_Filter_config config = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 1.0f, .sample_frequency_Hz = 10000.0f};
uz_IIR_Filter_t* filter_1 = NULL;
uz_IIR_Filter_t* filter_2 = NULL;
uz_IIR_Filter_t* filter_3 = NULL;
uz_IIR_Filter_t* filter_4 = NULL;
uz_IIR_Filter_t* filter_5 = NULL;
uz_IIR_Filter_t* filter_6 = NULL;
// Psi calc, remove maybe
#include "uz/uz_ParameterID/ElectricalID_6ph/uz_ParaID_Frequency_Analysis.h"
float meas_array[10000];
uz_ParaID_ElectricalID_fft_in_t uncorrected;
uz_ParaID_ElectricalID_fft_in_t corrected;
void print_paraID(uz_ParaID_ElectricalID_fft_in_t uncorrected, uz_ParaID_ElectricalID_fft_in_t corrected, uz_ParaID_ElectricalID_output_t mess);

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
			struct uz_PI_Controller_config PI_config = {
				.Ki = 1500.0f,//ParaID_Data.GlobalConfig.PMSM_config.R_ph_Ohm/(tau_sum),
				.Kp = 10.0f,//ParaID_Data.GlobalConfig.PMSM_config.Ld_Henry/(tau_sum),
				.samplingTime_sec = isr_ts,
				.lower_limit = -20.0f,
				.upper_limit = 20.0f};
			struct uz_PI_Controller_config PI_config_xy = {
				.Ki = 500.0f,//ParaID_Data.GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum),
				.Kp = 15.0f,//ParaID_Data.GlobalConfig.PMSM_config.Ld_Henry/2.0f/(2.0f*tau_sum),
				.samplingTime_sec = isr_ts,
				.lower_limit = -20.0f,
				.upper_limit = 20.0f};
			struct uz_PI_Controller_config PI_config_zero = {
				.Ki = 100.0f,//500.0f,//ParaID_Data.GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum),
				.Kp = 15.0f,//15.0f,//ParaID_Data.GlobalConfig.PMSM_config.Ld_Henry/2.0f/(2.0f*tau_sum),
				.samplingTime_sec = isr_ts,
				.lower_limit = -20.0f,
				.upper_limit = 20.0f};
			struct uz_CurrentControl_config cc_config_1 = {
				.decoupling_select = linear_decoupling,
				.config_id = PI_config,
				.config_iq = PI_config,
				.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config};
			struct uz_CurrentControl_config cc_config_2 = {
				.decoupling_select = no_decoupling,
				.config_id = PI_config_xy,
				.config_iq = PI_config_xy,
				.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config};
			struct uz_CurrentControl_config cc_config_3 = {
				.decoupling_select = no_decoupling,
				.config_id = PI_config_zero,
				.config_iq = PI_config_zero,
				.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config};
			struct uz_resonantController_config resonant_config = {
				.sampling_time = ParaID_Data.GlobalConfig.sampleTimeISR,
				.gain = 1000.0f,//PI_config.Ki,
				.harmonic_order = 6.0f,
				.fundamental_frequency = 1.0f,
				.lower_limit = -5.0f,
				.upper_limit = 5.0f,
				.antiwindup_gain = 100.0f,
				.in_reference_value = 0.0f,
				.in_measured_value = 0.0f};
			// init controllers
			sp_config.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config;
			Speed_instace = uz_SpeedControl_init(speed_config);
			sp_instance = uz_SetPoint_init(sp_config);
			CC_instance_1 = uz_CurrentControl_init(cc_config_1);
			CC_instance_2 = uz_CurrentControl_init(cc_config_2);
			CC_instance_3 = uz_CurrentControl_init(cc_config_3);
			res_instance_1 = uz_resonantController_init(resonant_config);
			res_instance_2 = uz_resonantController_init(resonant_config);
			// init filters
			filter_1 = uz_signals_IIR_Filter_init(config);
			filter_2 = uz_signals_IIR_Filter_init(config);
			filter_3 = uz_signals_IIR_Filter_init(config);
			filter_4 = uz_signals_IIR_Filter_init(config);
			filter_5 = uz_signals_IIR_Filter_init(config);
			filter_6 = uz_signals_IIR_Filter_init(config);
			// rest of inits from UZ
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
            //uz_ParameterID_6ph_transmit_FluxMap_to_Console(&ParaID_Data, &(Global_Data.av.logging), Global_Data.av.js_cnt_slowData);
			uz_ParameterID_6ph_calculate_PsiPMs(ParameterID, &ParaID_Data, meas_array);
            break;
        default:
            break;
        }
    }
    return (status);
}





void print_paraID(uz_ParaID_ElectricalID_fft_in_t uncorrected, uz_ParaID_ElectricalID_fft_in_t corrected, uz_ParaID_ElectricalID_output_t mess)
{
	printf("Rd:%f\n",mess.resistances_6ph.d);
	printf("Rq:%f\n",mess.resistances_6ph.q);
	printf("Rx:%f\n",mess.resistances_6ph.x);
	printf("Ry:%f\n",mess.resistances_6ph.y);
	printf("Rz1:%f\n",mess.resistances_6ph.z1);
	printf("Rz2:%f\n",mess.resistances_6ph.z2);

	printf("Ld:%f\n",mess.inductances_6ph.d*1000.0f);
	printf("Lq:%f\n",mess.inductances_6ph.q*1000.0f);
	printf("Lx:%f\n",mess.inductances_6ph.x*1000.0f);
	printf("Ly:%f\n",mess.inductances_6ph.y*1000.0f);
	printf("Lz1:%f\n",mess.inductances_6ph.z1*1000.0f);
	printf("Lz2:%f\n",mess.inductances_6ph.z2*1000.0f);

	printf("Psi_f1:%f\n",corrected.psi_pm_frequency[0]);
	printf("Psi_f2:%f\n",corrected.psi_pm_frequency[1]);
	printf("Psi_f3:%f\n",corrected.psi_pm_frequency[2]);
	printf("Psi_f4:%f\n",corrected.psi_pm_frequency[3]);
	printf("Psi_f5:%f\n",corrected.psi_pm_frequency[4]);

	printf("Psi_m1:%f\n",corrected.psi_pm_amplitude[0]*1000.0f);
	printf("Psi_m2:%f\n",corrected.psi_pm_amplitude[1]*1000.0f);
	printf("Psi_m3:%f\n",corrected.psi_pm_amplitude[2]*1000.0f);
	printf("Psi_m4:%f\n",corrected.psi_pm_amplitude[3]*1000.0f);
	printf("Psi_m5:%f\n",corrected.psi_pm_amplitude[4]*1000.0f);

	printf("Psi_a1:%f\n",corrected.psi_pm_angle[0]);
	printf("Psi_a2:%f\n",corrected.psi_pm_angle[1]);
	printf("Psi_a3:%f\n",corrected.psi_pm_angle[2]);
	printf("Psi_a4:%f\n",corrected.psi_pm_angle[3]);
	printf("Psi_a5:%f\n",corrected.psi_pm_angle[4]);

	printf("theta:%f\n", mess.thetaOffset);
}

