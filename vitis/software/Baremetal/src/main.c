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
#include "IP_Cores/uz_dac_interface/uz_dac_interface.h"
#include "IP_Cores/uz_pmsm_model_6ph_dq/uz_pmsm_model6ph_dq.h"
#include "IP_Cores/uz_pmsm6ph_transformation/uz_pmsm6ph_transformation.h"
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

struct uz_dac_interface_config_t dac_config={
    .base_address=XPAR_UZ_USER_UZ_DAC_SPI_INTERFACE_0_BASEADDR, // Depends on xparameters.h!
    .ip_clk_frequency_Hz=100000000,
    .gain={2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f}
};


//upper code for inverter


uz_pmsm_model6ph_dq_t *pmsm=NULL;

struct uz_pmsm_model6ph_dq_config_t pmsm_config={
              .base_address=XPAR_UZ_USER_UZ_PMSM_MODEL_6PH_DQ_0_BASEADDR,
              .ip_core_frequency_Hz=100000000,
              .simulate_mechanical_system = false,
              .r_1 = 0.19f,
			  .inductance.d = 0.002f,
			  .inductance.q = 0.0064f,
			  .inductance.x = 0.003f,
			  .inductance.y = 0.003f,
			  .inductance.z1 = 0.003f,
			  .inductance.z2 = 0.003f,
              .psi_pm = 0.19f,
              .polepairs = 5.0f,
              .inertia = 0.001,
              .coulomb_friction_constant = 0.001f,
              .friction_coefficient = 0.001f,
			  .switch_pspl = false};



//upper code for inverter
#include "IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"

struct uz_inverter_3ph_config_t inverter_1_config = {
		.base_address= XPAR_UZ_USER_UZ_INVERTER_3PH_0_BASEADDR,
		.ip_core_frequency_Hz= 100000000,
		.switch_pspl_abc=false,
		.switch_pspl_gate=false,
		.udc=560.0f
};

struct uz_inverter_3ph_config_t inverter_2_config = {
		.base_address= XPAR_UZ_USER_UZ_INVERTER_3PH_1_BASEADDR,
		.ip_core_frequency_Hz= 100000000,
		.switch_pspl_abc=false,
		.switch_pspl_gate=false,
		.udc=560.0f
};

struct uz_pmsm6ph_config_t pmsm_6ph_transformation_config={
		.base_address=XPAR_UZ_USER_UZ_SIXPHASE_VSD_TRAN_0_BASEADDR,
		.ip_core_frequency_Hz=100000000
};

struct uz_inverter_3ph_t *inverter_1=NULL;
struct uz_inverter_3ph_t *inverter_2=NULL;

uz_pmsm6ph_transformation_t* transformation_6ph=NULL;

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

extern pre_calc_val_t pre_calc_val;
extern uz_PMSM_6ph_t dengine;

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
            Global_Data.objects.dac_instance = uz_dac_interface_init(dac_config);
            Global_Data.objects.mux_axi = initialize_uz_mux_axi();
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);



            //debug for pu ip core (set pu conversion values for channels)
//            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x100, 65536); //65536 = 0.25f = 1/4*2^18 (Q18) values for dac adapter board
//            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x104, 65536); //65536 = 0.25f = 1/4*2^18 (Q18)
//            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x108, 65536); //65536 = 0.25f = 1/4*2^18 (Q18)
//            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x10C, 65536); //65536 = 0.25f = 1/4*2^18 (Q18)
//            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x110, 65536); //65536 = 0.25f = 1/4*2^18 (Q18)
//            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x114, 65536); //65536 = 0.25f = 1/4*2^18 (Q18)
            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x100, 26215); //26215 = 0.10000095f = 1/9.999905*2^18 (Q18) values for IB
            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x104, 26215);
            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x108, 26215);
            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x10C, 26215);
            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x110, 26215);
            uz_axi_write_uint32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR + 0x114, 26215);


            //debug for 6ph-VSD voltages ip-core
            uz_axi_write_uint32(XPAR_UZ_USER_UZ_6_PH_VOLTAGES_IP_0_BASEADDR + 0x100, 1); //0=index via AXI 1=index via PL

            //debug for delay_comp ip-core
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR + 0x118, uz_convert_float_to_sfixed(pre_calc_val.Rs_over_ZB, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR + 0x11C, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Ld, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR + 0x120, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Lq, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR + 0x124, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Lx, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR + 0x128, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Ly, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR + 0x12C, uz_convert_float_to_sfixed(pre_calc_val.Ld_over_LB, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR + 0x130, uz_convert_float_to_sfixed(pre_calc_val.Lq_over_LB, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR + 0x138, uz_convert_float_to_sfixed(pre_calc_val.psi_pm_over_psiB, 15));
            uz_axi_write_uint32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR + 0x12C, dengine.polePairs);

            //debug for prediction ip-core
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_PREDICT_IP_0_BASEADDR + 0x118, uz_convert_float_to_sfixed(pre_calc_val.Rs_over_ZB, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_PREDICT_IP_0_BASEADDR + 0x11C, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Ld, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_PREDICT_IP_0_BASEADDR + 0x120, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Lq, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_PREDICT_IP_0_BASEADDR + 0x124, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Lx, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_PREDICT_IP_0_BASEADDR + 0x128, uz_convert_float_to_sfixed(pre_calc_val.Ts_times_ZB_over_Ly, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_PREDICT_IP_0_BASEADDR + 0x12C, uz_convert_float_to_sfixed(pre_calc_val.Ld_over_LB, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_PREDICT_IP_0_BASEADDR + 0x130, uz_convert_float_to_sfixed(pre_calc_val.Lq_over_LB, 15));
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_PREDICT_IP_0_BASEADDR + 0x138, uz_convert_float_to_sfixed(pre_calc_val.psi_pm_over_psiB, 15));
            uz_axi_write_uint32(XPAR_UZ_USER_UZ_6PH_PREDICT_IP_0_BASEADDR + 0x13C, dengine.polePairs);

            //debug for cost ip-core
            uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_COST_IP_0_BASEADDR + 0x110, uz_convert_float_to_sfixed(2.5f, 15));

            //debug for 6ph PMSM ip core
            //loop code for PMSM
			pmsm = uz_pmsm_model6ph_dq_init(pmsm_config);
			uz_pmsm_model6ph_dq_reset(pmsm);
			inverter_1 = uz_inverter_3ph_init(inverter_1_config);
			inverter_2 = uz_inverter_3ph_init(inverter_2_config);
			transformation_6ph=uz_pmsm6ph_transformation_init(pmsm_6ph_transformation_config);
			//end

            initialization_chain = print_msg;
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
