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
/*
//IP-Cores for 6 Phase FSC-MPC
static struct uz_vsd_and_park_transformation_6phase_config_t config_vsd_and_park_transformation={
   .base_address= XPAR_UZ_USER_VSD_AND_PARK_TRANSFO_0_BASEADDR,
   .ip_clk_frequency_Hz=100000000,
   .theta_offset = 0.14608003f
};
uz_vsd_and_park_transformation_6phase_t* instance_vsd_and_park_transformation;


static struct uz_delay_compensation_fcs_mpc_6phase_config_t config_delay_compensation_fcs_mpc_6phase_pmsm={
    .base_address= XPAR_UZ_USER_DELAY_COMPENSATION_F_0_BASEADDR,
    .ip_clk_frequency_Hz=100000000,
    .psiPM = 0.0048f,
    .Lq =0.000147f,//[H]
    .Ld = 0.000147f,//[H]
    .Rs = 0.125f,//[Ohm]
    .SampleTime = 0.00001f,
    .pole_pairs = 5.0f,//needs to be asked
    .Lx = 0.00005566f,//maybe this value needs to be half of the size
    .Ly = 0.0000554f,//maybe this value needs to be half of the size
    .use_AXI =0
};
uz_delay_compensation_fcs_mpc_6phase_t* instance_delay_compensation_fcs_mpc_6phase_pmsm;


static struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_config_t config_phase_voltages_per_switching_state_fcs_mpc_6phase={
    .base_address= XPAR_UZ_USER_PHASE_VOLTAGES_PER_S_0_BASEADDR,
    .ip_clk_frequency_Hz=100000000,
    .theta_el_offset=0.14608003f,//needs to be asked
    .u_dc_link_voltage=36.0f,//needs to be asked
    .use_AXI=0
};
uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* instance_phase_voltages_per_switching_state_fcs_mpc_6phase;


static struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_config_t config_prediction_and_cost_function_fcs_mpc_6phase_pmsm={
    .base_address = XPAR_UZ_USER_PREDICTION_AND_COST_0_BASEADDR,
    .ip_clk_frequency_Hz = 100000000,
    .psiPM = 0.0048f,//measurement needed
    .Lq = 0.000147f,//[H]
    .Ld = 0.000147f,//[H]
    .Rs = 0.125f,//[Ohm]
    .SampleTime = 0.00001f,
    .pole_pairs = 5.0f,//needs to be asked
    .Lx = 0.00005566f,//maybe this value needs to be half of the size
    .Ly = 0.0000554f,//maybe this value needs to be half of the size
    .id_ref = 0.0f,//needs to be asked
    .iq_ref = 0.0f,//needs to be asked
    .ix_ref = 0.0f,//needs to be asked
    .iy_ref = 0.0f,//needs to be asked
    .use_AXI = 0
};
uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* instance_prediction_and_cost_function_fcs_mpc_6phase_pmsm;


static struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_config_t config_min_cost_function_and_vopt_fcs_mpc_6phase_pmsm={
    .base_address= XPAR_UZ_USER_MIN_COST_FUNCTION_AN_0_BASEADDR,
    .ip_clk_frequency_Hz=100000000,
    .use_AXI =0
};
uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* instance_min_cost_function_and_vopt_fcs_mpc_6phase_pmsm;
*/


// IP-Cores for 6 Phase FCS-MPC parallel 8
static struct uz_vsd_8_config_t config_vsd_8={
   .base_address= XPAR_UZ_USER_PARALLEL_8_VSD_AND_P_0_BASEADDR,
   .ip_clk_frequency_Hz=100000000,
   .theta_offset = 0.14608003f
};
uz_vsd_8_t* test_instance_vsd_8;

static struct uz_prediction_and_cost_function_8_config_t config_prediction_and_cost_function_8={
    .base_address = XPAR_UZ_USER_PARALLEL_8_PREDICTIO_0_BASEADDR,
    .ip_clk_frequency_Hz = 100000000,
    .psiPM = 0.0048f,//measurement needed
    .Lq = 0.000147f,//[H]
    .Ld = 0.000147f,//[H]
    .Rs = 0.125f,//[Ohm]
    .SampleTime = 0.00001f,
    .pole_pairs = 5.0f,//needs to be asked
    .Lx = 0.00005566f,//maybe this value needs to be half of the size
    .Ly = 0.0000554f,//maybe this value needs to be half of the size
    .id_ref = 0.0f,//needs to be asked
    .iq_ref = 0.0f,//needs to be asked
    .ix_ref = 0.0f,//needs to be asked
    .iy_ref = 0.0f,//needs to be asked
};
uz_prediction_and_cost_function_8_t* test_instance_prediction_and_cost_function_8;

static struct uz_delay_compensation_8_config_t config_delay_compensation_8={
    .base_address= XPAR_UZ_USER_PARALLEL_8_DELAY_COM_0_BASEADDR,
    .ip_clk_frequency_Hz=100000000,
    .psiPM = 0.0048f,
    .Lq =0.000147f,//[H]
    .Ld = 0.000147f,//[H]
    .Rs = 0.125f,//[Ohm]
    .SampleTime = 0.00001f,
    .pole_pairs = 5.0f,//needs to be asked
    .Lx = 0.00005566f,//maybe this value needs to be half of the size
    .Ly = 0.0000554f,//maybe this value needs to be half of the size
};
uz_delay_compensation_8_t* test_instance_delay_compensation_8;

static struct uz_phase_voltages_8_config_t config_phase_voltages_8={
    .base_address= XPAR_UZ_USER_PARALLEL_8_PHASE_VOL_0_BASEADDR,
    .ip_clk_frequency_Hz=100000000,
    .theta_el_offset=0.14608003f,//needs to be asked
    .u_dc_link_voltage=36.0f,//needs to be asked
};

static struct uz_min_cost_function_8_config_t config_min_cost_function_8={
    .base_address= XPAR_UZ_USER_PARALLEL_8_MIN_COST_0_BASEADDR,
    .ip_clk_frequency_Hz=100000000,
};
uz_min_cost_function_8_t* test_instance_min_cost_function_8;

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
/*
            // Includes IP-Cores driver for 6 Phase FSC-MPC
            instance_vsd_and_park_transformation = uz_vsd_and_park_transformation_6phase_init(config_vsd_and_park_transformation);
            instance_delay_compensation_fcs_mpc_6phase_pmsm = uz_delay_compensation_fcs_mpc_6phase_init(config_delay_compensation_fcs_mpc_6phase_pmsm);
            instance_phase_voltages_per_switching_state_fcs_mpc_6phase = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_init(config_phase_voltages_per_switching_state_fcs_mpc_6phase);
            instance_prediction_and_cost_function_fcs_mpc_6phase_pmsm = uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_init(config_prediction_and_cost_function_fcs_mpc_6phase_pmsm);
            instance_min_cost_function_and_vopt_fcs_mpc_6phase_pmsm = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_init(config_min_cost_function_and_vopt_fcs_mpc_6phase_pmsm);
*/
            // Init IP-Cores 6 Phase FCS-MPC parallel 8
            test_instance_vsd_8 = uz_vsd_8_init(config_vsd_8);
            test_instance_prediction_and_cost_function_8=uz_prediction_and_cost_function_8_init(config_prediction_and_cost_function_8);
            test_instance_delay_compensation_8 = uz_delay_compensation_8_init(config_delay_compensation_8);
            uz_phase_voltages_8_init(config_phase_voltages_8);
            test_instance_min_cost_function_8= uz_min_cost_function_8_init(config_min_cost_function_8);

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
