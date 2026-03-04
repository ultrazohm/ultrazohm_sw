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


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ PMSM model in FPGA ~~~~~~~~~
uz_pmsm_model9ph_dq_t *pmsm=NULL;
struct uz_pmsm_model9ph_dq_config_t pmsm_config = {   // example config values
  .base_address=XPAR_UZ_PMSM_MODEL_9PH_DQ_0_BASEADDR,
  .ip_core_frequency_Hz = 100000000U,
  .polepairs = 3.0f,
  .r_1 = 31.3f,
  .inductance.d = 0.46f,
  .inductance.q = 0.46f,
  .inductance.x1 = 0.08f,
  .inductance.y1 = 0.08f,
  .inductance.x2 = 0.08f,
  .inductance.y2 = 0.08f,
  .inductance.x3 = 0.08f,
  .inductance.y3 = 0.08f,
  .inductance.zero = 0.08f,
  .psi_pm = 0.072f,
  .friction_coefficient = 0.001f,
  .coulomb_friction_constant = 0.001f,
  .inertia = 0.001f,
  .simulate_mechanical_system = false,	// Determine if mechanical system is simulated or speed is an input
  .switch_pspl = false};				// true (--> use inputs from PS), false (--> use inputs from PL)
// HeDrive: Psi_PM = 0.067 Vs


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ DQ Trafo for PMSM model in FPGA ~~~~~~~~~
uz_pmsm9ph_transformation_t *cil_dq_trafo = NULL;
struct uz_pmsm9ph_config_t cil_dq_trafo_config = {
  .base_address = XPAR_UZ_NINEPHASE_VSD_TRANSFORMATION_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Inverter model in FPGA ~~~~~~~~~~
uz_inverter_3ph_t *cil_inv1 = NULL;
uz_inverter_3ph_t *cil_inv2 = NULL;
uz_inverter_3ph_t *cil_inv3 = NULL;
struct uz_inverter_3ph_config_t cil_inv1_config = {
    .base_address = XPAR_UZ_INVERTER_3PH_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .switch_pspl_abc = false,
    .switch_pspl_gate = false,
    .udc = 800.0f};
struct uz_inverter_3ph_config_t cil_inv2_config = {
    .base_address = XPAR_UZ_INVERTER_3PH_1_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .switch_pspl_abc = false,
    .switch_pspl_gate = false,
    .udc = 800.0f};
struct uz_inverter_3ph_config_t cil_inv3_config = {
    .base_address = XPAR_UZ_INVERTER_3PH_1_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .switch_pspl_abc = false,
    .switch_pspl_gate = false,
    .udc = 800.0f};



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
            xcp_interface_init();

            // --- init Simulink model ---
            init_control_functions();
            // ---------------------------

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
            Global_Data.objects.resolver_left = initialize_resolver_left();
            Global_Data.objects.resolver_right = initialize_resolver_right();

            /* init UZ_D_Temperature card */
            Global_Data.objects.temperature_card_d4 = initialize_temperature_card_d4();
            uz_TempCard_IF_Reset(Global_Data.objects.temperature_card_d4);
            uz_TempCard_IF_Start(Global_Data.objects.temperature_card_d4);

            // CIL model inits
            pmsm = uz_pmsm_model9ph_dq_init(pmsm_config);
            cil_dq_trafo = uz_pmsm9ph_transformation_init(cil_dq_trafo_config);
            cil_inv1 = uz_inverter_3ph_init(cil_inv1_config);
            cil_inv2 = uz_inverter_3ph_init(cil_inv2_config);
            cil_inv3 = uz_inverter_3ph_init(cil_inv3_config);
            // end of CIL model inits

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
			
			/* --- Start of Task Scheduler --- */
			if(Control_FLAG_1ms)
			{
				Control_FLAG_1ms = 0;
				Control_Task_1ms();
			}

			if(Control_FLAG_10ms)
			{
				Control_FLAG_10ms = 0;
				Control_Task_10ms();
			}

			if(Control_FLAG_100ms)
			{
				Control_FLAG_100ms = 0;
				Control_Task_100ms();
			}

			Control_Task_Idle();
			/* --- End of Task Scheduler --- */
			
            break;
        default:
            break;
        }

    }
    return (status);
}
