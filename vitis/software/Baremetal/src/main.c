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
#include "uz/uz_FOC/uz_FOC.h"
#include "IP_Cores/uz_pu_conversion/uz_pu_conversion_hwAddresses.h"
#include "IP_Cores/uz_park_transform/uz_park_transform_hwAddresses.h"

const struct uz_PMSM_t config_PMSM = {
		.R_ph_Ohm = 0.27f,
		.Ld_Henry = 0.0017f,
		.Lq_Henry = 0.0038f,
		.Psi_PM_Vs = 0.19f,
		.polePairs = 5.0f,
		.I_max_Ampere = 18.0f
};

const struct uz_PI_Controller_config config_id = {
		.Kp = 10.0f, //4.24f
		.Ki = 1500.0f, //159.0f
		.samplingTime_sec = 0.0001f,
		.type = ideal,
		.upper_limit = 326.0f,
		.lower_limit = -326.0f
};

const struct uz_PI_Controller_config config_iq = {
		.Kp = 10.0f, //9.5f
		.Ki = 1500.0f, //71.0f
		.samplingTime_sec = 0.0001f,
		.type = ideal,
		.upper_limit = 326.0f,
		.lower_limit = -326.0f
};

struct uz_FOC_config config = {
		.config_PMSM = config_PMSM,
		.config_id = config_id,
		.config_iq = config_iq,
		.decoupling_select = no_decoupling
};

struct uz_fixedpoint_definition_t delay_comp_fp_def = {
		.is_signed = true,
		.integer_bits = 3,
		.fractional_bits = 15
};

struct uz_fixedpoint_definition_t cost_fp_def = {
		.is_signed = false,
		.integer_bits = 1,
		.fractional_bits = 17
};

struct uz_fixedpoint_definition_t i_max_fp_def = {
		.is_signed = false,
		.integer_bits = 3,
		.fractional_bits = 15
};

struct uz_fixedpoint_definition_t i_setpoint_fp_def = {
		.is_signed = true,
		.integer_bits = 7,
		.fractional_bits = 11
};

struct uz_fixedpoint_definition_t i_debug_meas = {
		.is_signed = true,
		.integer_bits = 12,
		.fractional_bits = 15
};

struct uz_fixedpoint_definition_t omega_m_debug_meas = {
		.is_signed = true,
		.integer_bits = 13,
		.fractional_bits = 11
};

struct uz_fixedpoint_definition_t theta_el_debug_meas = {
		.is_signed = true,
		.integer_bits = 7,
		.fractional_bits = 20
};

struct uz_fixedpoint_definition_t del_fp = {
		.is_signed = true,
		.integer_bits = 3,
		.fractional_bits = 15
};

struct uz_fixedpoint_definition_t current_limit_SI = {
		.is_signed = true,
		.integer_bits = 12,
		.fractional_bits = 15
};

struct uz_PI_Controller_config MPC_setpoint_config = {
   .type = parallel,
   .Kp = 0.0f,
   .Ki = 4.0f,
   .samplingTime_sec = 0.0001f,
   .upper_limit = 10.0f,
   .lower_limit = -10.0f
};

extern pre_calc_val_t pre_calc_val;
extern const base_val_t base_val;
extern uz_PMSM_6ph_t dengine;

typedef struct pre_calc_val_fixedpoint_t {
	int32_t Rs_over_ZB;
	int32_t Ts_times_ZB_over_Ld;
	int32_t Ts_times_ZB_over_Lq;
	int32_t Ts_times_ZB_over_Lx;
	int32_t Ts_times_ZB_over_Ly;
	int32_t Ld_over_LB;
	int32_t Lq_over_LB;
	int32_t psi_pm_over_psiB;
}pre_calc_val_fixedpoint_t;

pre_calc_val_fixedpoint_t pre_calc_val_fixedpoint={0};

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
            Initialize_Timer();
            uz_SystemTime_init();
            JavaScope_initalize(&Global_Data);
//            Global_Data.av.theta_offset = 1.120014f; //!!! if cnt is reset to zero at init we have to add pi to 1.120014 = 4.261607
//            Global_Data.av.theta_offset = 4.261607f;
            Global_Data.av.theta_mech_offset_rad = 6.25;//6.1205; //4.420
            Global_Data.av.polepairs = 5.0f;
            Global_Data.av.offset_el_incre = 945U;
            Global_Data.objects.foc_current = uz_FOC_init(config);
            //init fpga current limit
            Global_Data.av.i_max_fpga = 1.0f;

            //init lambda factors sw values for mpc
            Global_Data.av.lambda_d = 1.0f;
            Global_Data.av.lambda_q = 1.0f;
            Global_Data.av.lambda_x = 1.0f;
            Global_Data.av.lambda_y = 1.0f;
            Global_Data.av.lambda_u = 0.000f;

            // parameters for automated trade-off curve measurements
            Global_Data.rasv.lambda_u_start = 0.000;
            Global_Data.rasv.lambda_u_stop = 0.02;
            Global_Data.rasv.lambda_u_step = 0.0001;
            Global_Data.rasv.lambda_u_now = Global_Data.rasv.lambda_u_start;
            Global_Data.rasv.cnt_lambda_u_end = (uint32_t)(ceilf((Global_Data.rasv.lambda_u_stop - Global_Data.rasv.lambda_u_start) / Global_Data.rasv.lambda_u_step))+1U;
            Global_Data.rasv.f_cnt_lambda_u_end = (float)Global_Data.rasv.cnt_lambda_u_end;
            Global_Data.rasv.cnt_lambda_u = 1U;
            Global_Data.rasv.f_cnt_lambda_u = 1.0f;
            Global_Data.av.pause_time_sec = 3.0f;

            Global_Data.objects.MPC_setpoint_PI = uz_PI_Controller_init(MPC_setpoint_config);


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
            Global_Data.objects.pl_interface = initialize_resolver_pl_interface();
            Global_Data.objects.tempMeasurement1 = init_tempMeasurement1();
            Global_Data.objects.tempMeasurement2 = init_tempMeasurement2();
            Global_Data.objects.lmg_trigger = init_lmg_trigger();
            Global_Data.objects.encoder_D3 = initialize_incremental_encoder_ipcore_on_D3(UZ_D3_INCREMENTAL_ENCODER_RESOLUTION, UZ_D3_MOTOR_POLE_PAIR_NUMBER);
            uz_incrementalEncoder_set_electrical_Offset(Global_Data.objects.encoder_D3, Global_Data.av.offset_el_incre);
//            reconfig_ADC();
            // current limit detection ip
            uz_fixedpoint_axi_write(XPAR_PU_CONVERSION_UZ_CUR_LIM_0_BASEADDR + 0x100, Global_Data.av.i_max_fpga, current_limit_SI);
            // init debug switch ip
            Global_Data.av.debug_ip_off = true; //NO DEBUG BY INIT
            uz_axi_write_bool(XPAR_PU_CONVERSION_UZ_DEBUG_IP_0_BASEADDR + 0x124, Global_Data.av.debug_ip_off);
            uz_fixedpoint_axi_write(XPAR_PU_CONVERSION_UZ_DEBUG_IP_0_BASEADDR + 0x100, 3.0f, i_debug_meas); // 6-dummy phase currents
            uz_fixedpoint_axi_write(XPAR_PU_CONVERSION_UZ_DEBUG_IP_0_BASEADDR + 0x104, 2.0f, i_debug_meas);
            uz_fixedpoint_axi_write(XPAR_PU_CONVERSION_UZ_DEBUG_IP_0_BASEADDR + 0x108, 1.0f, i_debug_meas);
            uz_fixedpoint_axi_write(XPAR_PU_CONVERSION_UZ_DEBUG_IP_0_BASEADDR + 0x10C, 6.0f, i_debug_meas);
            uz_fixedpoint_axi_write(XPAR_PU_CONVERSION_UZ_DEBUG_IP_0_BASEADDR + 0x110, 5.0f, i_debug_meas);
            uz_fixedpoint_axi_write(XPAR_PU_CONVERSION_UZ_DEBUG_IP_0_BASEADDR + 0x114, 4.0f, i_debug_meas);
            uz_fixedpoint_axi_write(XPAR_PU_CONVERSION_UZ_DEBUG_IP_0_BASEADDR + 0x118, 50.0f, i_debug_meas);
            uz_fixedpoint_axi_write(XPAR_PU_CONVERSION_UZ_DEBUG_IP_0_BASEADDR + 0x11C, 0.0f, omega_m_debug_meas);
            uz_fixedpoint_axi_write(XPAR_PU_CONVERSION_UZ_DEBUG_IP_0_BASEADDR + 0x120, 0.0f, theta_el_debug_meas);


            // init pu-conversion
//          float pu_current_conversion = 0.1f; // 10A = 1 p.u.
            float pu_current_conversion = 1.0f/base_val.IB;
            uz_axi_write_uint32(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in0_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion, 18)); //i_c1
            uz_axi_write_uint32(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in1_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion, 18)); //i_b1
            uz_axi_write_uint32(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in2_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion, 18)); //i_a1
            uz_axi_write_uint32(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in8_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion, 18)); //i_c2
            uz_axi_write_uint32(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in9_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion, 18)); //i_b2
            uz_axi_write_uint32(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in10_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion, 18));//i_a2
//            float pu_voltage_conversion = 0.00666667f;
            float pu_voltage_conversion = 1.0f/base_val.VB;
            uz_axi_write_uint32(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in3_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_voltage_conversion, 18)); //v_dc1
            uz_axi_write_uint32(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in11_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_voltage_conversion, 18)); //v_dc2
            // init VSD IP
            //nothing to init here

            // init park transform IP
            uz_axi_write_uint32(XPAR_UZ_PARK_TRANSFORM_IP_0_BASEADDR + factor_angle_el_AXI_Data_uz_park_transform_ip, uz_convert_float_to_sfixed(1.0f, 14)); //factor multiplied with el. position
            uz_axi_write_uint32(XPAR_UZ_PARK_TRANSFORM_IP_0_BASEADDR + offset_angle_el_AXI_Data_uz_park_transform_ip, uz_convert_float_to_sfixed(0.0f, 14)); //offset angle is already respected in uz_resolver_pl_interface

            // ctrl_state_machine IP init
            uz_axi_write_uint32(XPAR_MPC_CTRL_STAT_IP_0_BASEADDR + 0x100, 8U); //state machine shall perform 8 iterations for the 8 parallel branches of the MPC (=64 switch positions)

            // mpc_voltages IP init
            uz_axi_write_uint32(XPAR_MPC_PAR_PU_VOLTS_VSD_0_BASEADDR + 0x100, 1U); //0=index via AXI 1=index via PL
            uz_axi_write_uint32(XPAR_MPC_PAR_PU_VOLTS_VSD_0_BASEADDR + 0x11C, 0U); //0=v_dc via AXI 1=v_dc via PL measured
            uz_axi_write_uint32(XPAR_MPC_PAR_PU_VOLTS_VSD_0_BASEADDR + 0x118, uz_convert_float_to_sfixed(50.0f/base_val.VB, 15));
            uz_axi_write_uint32(XPAR_MPC_PAR_PU_VOLTS_VSD_0_BASEADDR + 0x108, 8U); // idx_offset_1
            uz_axi_write_uint32(XPAR_MPC_PAR_PU_VOLTS_VSD_0_BASEADDR + 0x10C, 16U); // idx_offset_2
            uz_axi_write_uint32(XPAR_MPC_PAR_PU_VOLTS_VSD_0_BASEADDR + 0x110, 24U); // idx_offset_3
            uz_axi_write_uint32(XPAR_MPC_PAR_PU_VOLTS_VSD_0_BASEADDR + 0x114, 32U); // idx_offset_4
            uz_axi_write_uint32(XPAR_MPC_PAR_PU_VOLTS_VSD_0_BASEADDR + 0x120, 40U); // idx_offset_5
            uz_axi_write_uint32(XPAR_MPC_PAR_PU_VOLTS_VSD_0_BASEADDR + 0x124, 48U); // idx_offset_6
            uz_axi_write_uint32(XPAR_MPC_PAR_PU_VOLTS_VSD_0_BASEADDR + 0x128, 56U); // idx_offset_7

            // pu_omega_m IP init
            float pu_omega_m_conversion = 1.0f/base_val.omegaB;
            uz_axi_write_uint32(XPAR_MPC_PU_OMEGA_M_0_BASEADDR + 0x17C, uz_convert_float_to_unsigned_fixed(pu_omega_m_conversion, 18)); //omega_m_rad_per_s

            // delay_comp IP init
            pre_calc_val_fixedpoint.Rs_over_ZB = uz_fixedpoint_convert_to_signed_fixed(pre_calc_val.Rs_over_ZB, del_fp);
            pre_calc_val_fixedpoint.Ts_times_ZB_over_Ld = uz_fixedpoint_convert_to_signed_fixed(pre_calc_val.Ts_times_ZB_over_Ld, del_fp);

            uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x118, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x11C, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x120, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x124, pre_calc_val.Ts_times_ZB_over_Lx, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x128, pre_calc_val.Ts_times_ZB_over_Ly, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x12C, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x130, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x138, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
            uz_axi_write_uint32(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x13C, (uint32_t)(dengine.polePairs));

            // prediction IP init
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_0_BASEADDR + 0x118, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_0_BASEADDR + 0x11C, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_0_BASEADDR + 0x120, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_0_BASEADDR + 0x124, pre_calc_val.Ts_times_ZB_over_Lx, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_0_BASEADDR + 0x128, pre_calc_val.Ts_times_ZB_over_Ly, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_0_BASEADDR + 0x12C, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_0_BASEADDR + 0x130, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_0_BASEADDR + 0x138, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PREDICTION_0_BASEADDR + 0x13C, (uint32_t)(dengine.polePairs));

            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_1_BASEADDR + 0x118, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_1_BASEADDR + 0x11C, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_1_BASEADDR + 0x120, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_1_BASEADDR + 0x124, pre_calc_val.Ts_times_ZB_over_Lx, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_1_BASEADDR + 0x128, pre_calc_val.Ts_times_ZB_over_Ly, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_1_BASEADDR + 0x12C, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_1_BASEADDR + 0x130, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_1_BASEADDR + 0x138, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PREDICTION_1_BASEADDR + 0x13C, (uint32_t)(dengine.polePairs));

            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_2_BASEADDR + 0x118, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_2_BASEADDR + 0x11C, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_2_BASEADDR + 0x120, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_2_BASEADDR + 0x124, pre_calc_val.Ts_times_ZB_over_Lx, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_2_BASEADDR + 0x128, pre_calc_val.Ts_times_ZB_over_Ly, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_2_BASEADDR + 0x12C, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_2_BASEADDR + 0x130, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_2_BASEADDR + 0x138, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PREDICTION_2_BASEADDR + 0x13C, (uint32_t)(dengine.polePairs));

            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_3_BASEADDR + 0x118, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_3_BASEADDR + 0x11C, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_3_BASEADDR + 0x120, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_3_BASEADDR + 0x124, pre_calc_val.Ts_times_ZB_over_Lx, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_3_BASEADDR + 0x128, pre_calc_val.Ts_times_ZB_over_Ly, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_3_BASEADDR + 0x12C, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_3_BASEADDR + 0x130, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_3_BASEADDR + 0x138, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PREDICTION_3_BASEADDR + 0x13C, (uint32_t)(dengine.polePairs));

            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_4_BASEADDR + 0x118, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_4_BASEADDR + 0x11C, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_4_BASEADDR + 0x120, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_4_BASEADDR + 0x124, pre_calc_val.Ts_times_ZB_over_Lx, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_4_BASEADDR + 0x128, pre_calc_val.Ts_times_ZB_over_Ly, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_4_BASEADDR + 0x12C, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_4_BASEADDR + 0x130, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_4_BASEADDR + 0x138, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PREDICTION_4_BASEADDR + 0x13C, (uint32_t)(dengine.polePairs));

            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_5_BASEADDR + 0x118, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_5_BASEADDR + 0x11C, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_5_BASEADDR + 0x120, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_5_BASEADDR + 0x124, pre_calc_val.Ts_times_ZB_over_Lx, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_5_BASEADDR + 0x128, pre_calc_val.Ts_times_ZB_over_Ly, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_5_BASEADDR + 0x12C, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_5_BASEADDR + 0x130, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_5_BASEADDR + 0x138, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PREDICTION_5_BASEADDR + 0x13C, (uint32_t)(dengine.polePairs));

            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_6_BASEADDR + 0x118, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_6_BASEADDR + 0x11C, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_6_BASEADDR + 0x120, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_6_BASEADDR + 0x124, pre_calc_val.Ts_times_ZB_over_Lx, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_6_BASEADDR + 0x128, pre_calc_val.Ts_times_ZB_over_Ly, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_6_BASEADDR + 0x12C, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_6_BASEADDR + 0x130, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_6_BASEADDR + 0x138, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PREDICTION_6_BASEADDR + 0x13C, (uint32_t)(dengine.polePairs));

            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_7_BASEADDR + 0x118, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_7_BASEADDR + 0x11C, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_7_BASEADDR + 0x120, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_7_BASEADDR + 0x124, pre_calc_val.Ts_times_ZB_over_Lx, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_7_BASEADDR + 0x128, pre_calc_val.Ts_times_ZB_over_Ly, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_7_BASEADDR + 0x12C, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_7_BASEADDR + 0x130, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PREDICTION_7_BASEADDR + 0x138, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PREDICTION_7_BASEADDR + 0x13C, (uint32_t)(dengine.polePairs));
            // cost_optim IP init
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x110, 1.0f, i_max_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x114, Global_Data.av.lambda_d, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x118, Global_Data.av.lambda_q, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x11C, Global_Data.av.lambda_x, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x120, Global_Data.av.lambda_y, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x124, Global_Data.av.lambda_u, cost_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x100, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x104, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x108, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x10C, 0.0f/base_val.IB, i_setpoint_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x128, 0U); // offset_index
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x12C, 8U); // index_limit

            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x110, 1.0f, i_max_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x114, Global_Data.av.lambda_d, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x118, Global_Data.av.lambda_q, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x11C, Global_Data.av.lambda_x, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x120, Global_Data.av.lambda_y, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x124, Global_Data.av.lambda_u, cost_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x100, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x104, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x108, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x10C, 0.0f/base_val.IB, i_setpoint_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x128, 8U); // offset_index
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x12C, 16U); // index_limit

            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x110, 1.0f, i_max_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x114, Global_Data.av.lambda_d, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x118, Global_Data.av.lambda_q, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x11C, Global_Data.av.lambda_x, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x120, Global_Data.av.lambda_y, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x124, Global_Data.av.lambda_u, cost_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x100, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x104, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x108, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x10C, 0.0f/base_val.IB, i_setpoint_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x128, 16U); // offset_index
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x12C, 24U); // index_limit

            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x110, 1.0f, i_max_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x114, Global_Data.av.lambda_d, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x118, Global_Data.av.lambda_q, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x11C, Global_Data.av.lambda_x, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x120, Global_Data.av.lambda_y, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x124, Global_Data.av.lambda_u, cost_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x100, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x104, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x108, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x10C, 0.0f/base_val.IB, i_setpoint_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x128, 24U); // offset_index
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x12C, 32U); // index_limit

            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x110, 1.0f, i_max_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x114, Global_Data.av.lambda_d, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x118, Global_Data.av.lambda_q, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x11C, Global_Data.av.lambda_x, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x120, Global_Data.av.lambda_y, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x124, Global_Data.av.lambda_u, cost_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x100, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x104, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x108, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x10C, 0.0f/base_val.IB, i_setpoint_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x128, 32U); // offset_index
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x12C, 40U); // index_limit

            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x110, 1.0f, i_max_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x114, Global_Data.av.lambda_d, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x118, Global_Data.av.lambda_q, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x11C, Global_Data.av.lambda_x, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x120, Global_Data.av.lambda_y, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x124, Global_Data.av.lambda_u, cost_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x100, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x104, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x108, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x10C, 0.0f/base_val.IB, i_setpoint_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x128, 40U); // offset_index
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x12C, 48U); // index_limit

            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x110, 1.0f, i_max_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x114, Global_Data.av.lambda_d, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x118, Global_Data.av.lambda_q, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x11C, Global_Data.av.lambda_x, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x120, Global_Data.av.lambda_y, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x124, Global_Data.av.lambda_u, cost_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x100, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x104, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x108, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x10C, 0.0f/base_val.IB, i_setpoint_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x128, 48U); // offset_index
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x12C, 56U); // index_limit

            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x110, 1.0f, i_max_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x114, Global_Data.av.lambda_d, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x118, Global_Data.av.lambda_q, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x11C, Global_Data.av.lambda_x, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x120, Global_Data.av.lambda_y, cost_fp_def);
            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x124, Global_Data.av.lambda_u, cost_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x100, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x104, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x108, 0.0f/base_val.IB, i_setpoint_fp_def);
//            uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x10C, 0.0f/base_val.IB, i_setpoint_fp_def);
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x128, 56U); // offset_index
            uz_axi_write_uint32(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x12C, 64U); // index_limit

            // current reference distribution IP
			uz_fixedpoint_axi_write(XPAR_MPC_REF_DISTRIBUTOR_0_BASEADDR + 0x100, 0.0f/base_val.IB, i_setpoint_fp_def);
			uz_fixedpoint_axi_write(XPAR_MPC_REF_DISTRIBUTOR_0_BASEADDR + 0x104, 0.0f/base_val.IB, i_setpoint_fp_def);
			uz_fixedpoint_axi_write(XPAR_MPC_REF_DISTRIBUTOR_0_BASEADDR + 0x108, 0.0f/base_val.IB, i_setpoint_fp_def);
			uz_fixedpoint_axi_write(XPAR_MPC_REF_DISTRIBUTOR_0_BASEADDR + 0x10C, 0.0f/base_val.IB, i_setpoint_fp_def);

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
