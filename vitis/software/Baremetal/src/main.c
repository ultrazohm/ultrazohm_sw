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

extern pre_calc_val_t pre_calc_val;
extern const base_val_t base_val;
extern uz_PMSM_6ph_t dengine;

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
            Global_Data.av.theta_mech_offset_rad = 6.1205; //4.420
            Global_Data.av.polepairs = 5.0f;
            Global_Data.objects.foc_current = uz_FOC_init(config);

            //init lambda factors sw values for mpc
            Global_Data.av.lambda_d = 1.0f;
            Global_Data.av.lambda_q = 1.0f;
            Global_Data.av.lambda_x = 1.0f;
            Global_Data.av.lambda_y = 1.0f;
            Global_Data.av.lambda_u = 0.000f;

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
            reconfig_ADC();

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
            uz_axi_write_uint32(XPAR_MPC_CTRL_STAT_IP_0_BASEADDR + 0x100, 64U); //state machine shall perform 64 iterations for the 64 switch positions

            // mpc_voltages IP init
            uz_axi_write_uint32(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x100, 1U); //0=index via AXI 1=index via PL

            // pu_omega_m IP init
            float pu_omega_m_conversion = 1.0f/base_val.omegaB;
            uz_axi_write_uint32(XPAR_MPC_PU_OMEGA_M_0_BASEADDR + 0x17C, uz_convert_float_to_unsigned_fixed(pu_omega_m_conversion, 18)); //omega_m_rad_per_s

            // delay_comp IP init
            uz_axi_write_int32(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x118, uz_convert_float_to_sfixed(pre_calc_val.Rs_over_ZB, 15));
            uz_axi_write_int32(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x11C, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Ld, 15));
            uz_axi_write_int32(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x120, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Lq, 15));
            uz_axi_write_int32(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x124, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Lx, 15));
            uz_axi_write_int32(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x128, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Ly, 15));
            uz_axi_write_int32(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x12C, uz_convert_float_to_sfixed(pre_calc_val.Ld_over_LB, 15));
            uz_axi_write_int32(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x130, uz_convert_float_to_sfixed(pre_calc_val.Lq_over_LB, 15));
            uz_axi_write_int32(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x138, uz_convert_float_to_sfixed(pre_calc_val.psi_pm_over_psiB, 15));
            uz_axi_write_uint32(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x13C, dengine.polePairs);

            // prediction IP init
            uz_axi_write_int32(XPAR_MPC_PREDICTION_0_BASEADDR + 0x118, uz_convert_float_to_sfixed(pre_calc_val.Rs_over_ZB, 15));
            uz_axi_write_int32(XPAR_MPC_PREDICTION_0_BASEADDR + 0x11C, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Ld, 15));
            uz_axi_write_int32(XPAR_MPC_PREDICTION_0_BASEADDR + 0x120, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Lq, 15));
            uz_axi_write_int32(XPAR_MPC_PREDICTION_0_BASEADDR + 0x124, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Lx, 15));
            uz_axi_write_int32(XPAR_MPC_PREDICTION_0_BASEADDR + 0x128, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Ly, 15));
            uz_axi_write_int32(XPAR_MPC_PREDICTION_0_BASEADDR + 0x12C, uz_convert_float_to_sfixed(pre_calc_val.Ld_over_LB, 15));
            uz_axi_write_int32(XPAR_MPC_PREDICTION_0_BASEADDR + 0x130, uz_convert_float_to_sfixed(pre_calc_val.Lq_over_LB, 15));
            uz_axi_write_int32(XPAR_MPC_PREDICTION_0_BASEADDR + 0x138, uz_convert_float_to_sfixed(pre_calc_val.psi_pm_over_psiB, 15));
            uz_axi_write_uint32(XPAR_MPC_PREDICTION_0_BASEADDR + 0x13C, dengine.polePairs);

            // cost_optim IP init
            uz_axi_write_int32(XPAR_MPC_COST_OPT_0_BASEADDR + 0x110, uz_convert_float_to_sfixed(0.36f, 15)); //current limit in p.u.
            uz_axi_write_int32(XPAR_MPC_COST_OPT_0_BASEADDR + 0x114, uz_convert_float_to_sfixed(Global_Data.av.lambda_d, 17));
            uz_axi_write_int32(XPAR_MPC_COST_OPT_0_BASEADDR + 0x118, uz_convert_float_to_sfixed(Global_Data.av.lambda_q, 17));
            uz_axi_write_int32(XPAR_MPC_COST_OPT_0_BASEADDR + 0x11C, uz_convert_float_to_sfixed(Global_Data.av.lambda_x, 17));
            uz_axi_write_int32(XPAR_MPC_COST_OPT_0_BASEADDR + 0x120, uz_convert_float_to_sfixed(Global_Data.av.lambda_y, 17));
            uz_axi_write_int32(XPAR_MPC_COST_OPT_0_BASEADDR + 0x124, uz_convert_float_to_sfixed(Global_Data.av.lambda_u, 17));
            uz_axi_write_int32(XPAR_MPC_COST_OPT_0_BASEADDR + 0x100, uz_convert_float_to_sfixed(0.0f/base_val.IB, 11));
            uz_axi_write_int32(XPAR_MPC_COST_OPT_0_BASEADDR + 0x104, uz_convert_float_to_sfixed(0.0f/base_val.IB, 11));
            uz_axi_write_int32(XPAR_MPC_COST_OPT_0_BASEADDR + 0x108, uz_convert_float_to_sfixed(0.0f/base_val.IB, 11));
            uz_axi_write_int32(XPAR_MPC_COST_OPT_0_BASEADDR + 0x10C, uz_convert_float_to_sfixed(0.0f/base_val.IB, 11));

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
