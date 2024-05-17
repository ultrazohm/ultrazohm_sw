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
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "IP_Cores/uz_pu_conversion/uz_pu_conversion_hwAddresses.h"
#include "IP_Cores/uz_park_transform/uz_park_transform_hwAddresses.h"

extern const float max_phase_current_;
extern const float V_DC_Volts;

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
	init_CurrentControl,
	init_nn,
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


                        //Global_Data.objects.foc_current = uz_FOC_init(config); See CC later
                        //init fpga current limit
                        Global_Data.av.i_max_fpga = max_phase_current_;
                        Global_Data.av.i_max =max_phase_current_/base_val.IB; // it goes into the cost function, pu.

                        //init lambda factors sw values for mpc
                        Global_Data.av.lambda_d = 1.0f;
                        Global_Data.av.lambda_q = 1.0f;
                        Global_Data.av.lambda_x = 1.0f;
                        Global_Data.av.lambda_y = 1.0f;
                        Global_Data.av.lambda_u = 0.000f;



            initialization_chain = init_CurrentControl;
            break;

        case init_CurrentControl:
      	Global_Data.objects.CC_dq_instance = init_dq_FOC();
       	Global_Data.objects.CC_xy_instance = init_xy_FOC();
        	initialization_chain = init_nn;
        	break;

        case init_nn:
#if NN_15_INPUT_1_64==1
        	nn_15_input_1_64_init();
#endif
#if NN_17_INPUT_1_64==1
        	nn_17_input_1_64_init();
#endif
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
			uz_fixedpoint_axi_write(XPAR_PU_CONVERSION_UZ_DEBUG_IP_0_BASEADDR + 0x120, 5.4843f, theta_el_debug_meas);


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
		   uz_axi_write_uint32(XPAR_UZ_PARK_TRANSFORM_IP_0_BASEADDR + offset_angle_el_AXI_Data_uz_park_transform_ip, uz_convert_float_to_sfixed(-5.4843f, 14)); //offset angle is corrected here

		   // ctrl_state_machine IP init
		   uz_axi_write_uint32(XPAR_MPC_CTRL_STAT_IP_0_BASEADDR + 0x100, 64U); //state machine shall perform 64 iterations for the 64 switch positions

		   // mpc_voltages IP init
		   uz_axi_write_uint32(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x100, 1U); //0=index via AXI 1=index via PL
		   uz_axi_write_uint32(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x11C, 0U); //0=v_dc via AXI 1=v_dc via PL measured
		   uz_axi_write_uint32(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x118, uz_convert_float_to_sfixed(V_DC_Volts/base_val.VB, 15)); // ?? 50.0f at the beginning

		   // pu_omega_m IP init
		   float pu_omega_m_conversion = 1.0f/base_val.omegaB;
		   uz_axi_write_uint32(XPAR_MPC_PU_OMEGA_M_0_BASEADDR + 0x17C, uz_convert_float_to_unsigned_fixed(pu_omega_m_conversion, 18)); //omega_m_rad_per_s

		   // delay_comp IP init
		   pre_calc_val_fixedpoint.Rs_over_ZB = uz_fixedpoint_convert_to_signed_fixed(pre_calc_val.Rs_over_ZB, del_fp);
		   pre_calc_val_fixedpoint.Ts_times_ZB_over_Ld = uz_fixedpoint_convert_to_signed_fixed(pre_calc_val.Ts_times_ZB_over_Ld, del_fp);

		   uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x118, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x11C, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x120, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x124, pre_calc_val.Ts_times_ZB_over_Lx, delay_comp_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x128, pre_calc_val.Ts_times_ZB_over_Ly, delay_comp_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x12C, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x130, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x138, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
		   uz_axi_write_uint32(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x13C, (uint32_t)(dengine.polePairs));

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
		   // cost_optim IP init
		   uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x110, Global_Data.av.i_max, i_max_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x114, Global_Data.av.lambda_d, cost_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x118, Global_Data.av.lambda_q, cost_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x11C, Global_Data.av.lambda_x, cost_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x120, Global_Data.av.lambda_y, cost_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x124, Global_Data.av.lambda_u, cost_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x100, 0.0f/base_val.IB, i_setpoint_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x104, 0.0f/base_val.IB, i_setpoint_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x108, 0.0f/base_val.IB, i_setpoint_fp_def);
		   uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x10C, 0.0f/base_val.IB, i_setpoint_fp_def);


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
