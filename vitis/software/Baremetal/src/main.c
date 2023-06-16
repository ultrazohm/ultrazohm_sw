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


////////////////////////////////////
////////////User Setting////////////
////////////////////////////////////
const bool openhw_pspl = false; //false: FOC in PL (IP-cores), true: FOC in PS (uz_CurrentControl)
const float openhw_udc = 100.0f; //dont change unless SPWM IP-core can also be changed from PS
///////////////////////////////////////////
////////////////////CIL////////////////////
///////////////////////////////////////////
// includes
#include "IP_Cores/uz_pmsm_model_6ph_dq/uz_pmsm_model6ph_dq.h"
#include "IP_Cores/uz_pmsm6ph_transformation/uz_pmsm6ph_transformation.h"
#include "IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "uz/uz_PMSM_config/uz_PMSM_config.h"

// PMSM
const  uz_PMSM_t config_PMSM = {
	.I_max_Ampere = 255.0f,
	.J_kg_m_squared = 0.01f,
	.Ld_Henry = 0.003f,
	.Lq_Henry = 0.003f,
	.Psi_PM_Vs = 0.0075f,
	.R_ph_Ohm = 0.3f,
	.polePairs = 4.0f
};
uz_pmsm_model6ph_dq_t *pmsm = NULL;
struct uz_pmsm_model6ph_dq_config_t cil_pmsm_comfig = {
    .base_address = XPAR_UZ_USER_CIL_UZ_PMSM_MODEL_6PH_DQ_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .polepairs = config_PMSM.polePairs,
    .r_1 = config_PMSM.R_ph_Ohm,
    .inductance.d = config_PMSM.Ld_Henry,
    .inductance.q = config_PMSM.Lq_Henry,
    .inductance.x = 2.00e-03f,
    .inductance.y = 4.00e-03f,
    .inductance.z1 = 5.00e-03f,
    .inductance.z2 = 6.00e-03f,
    .psi_pm = config_PMSM.Psi_PM_Vs,
    .friction_coefficient = 0.001f,
    .coulomb_friction_constant = 0.001f,
    .inertia = config_PMSM.J_kg_m_squared,
    .simulate_mechanical_system = false,
    .switch_pspl = openhw_pspl};

// Transformation
uz_pmsm6ph_transformation_t *transformation = NULL;
struct uz_pmsm6ph_config_t cil_transformation_config = {
  .base_address = XPAR_UZ_USER_CIL_UZ_SIXPHASE_VSD_TRAN_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f};

// Inverter
uz_inverter_3ph_t *inverter1 = NULL;
uz_inverter_3ph_t *inverter2 = NULL;
struct uz_inverter_3ph_config_t cil_inverter1_config = {
    .base_address = XPAR_UZ_USER_CIL_UZ_INVERTER_3PH_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .switch_pspl_abc = false,
    .switch_pspl_gate = false,
    .udc = openhw_udc};
struct uz_inverter_3ph_config_t cil_inverter2_config = {
    .base_address = XPAR_UZ_USER_CIL_UZ_INVERTER_3PH_1_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .switch_pspl_abc = false,
    .switch_pspl_gate = false,
    .udc = openhw_udc};
//////////////////////////////////////////////
////////////////////FOC PS////////////////////
//////////////////////////////////////////////
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_piController/uz_piController.h"
struct uz_PI_Controller_config PI_config = {
  .Kp = 100.0f,
  .Ki = 10.0f,
  .samplingTime_sec = 1.0f/UZ_PWM_FREQUENCY,
  .upper_limit = 20.0f,
  .lower_limit = -100.0f};
uz_CurrentControl_t* cc_instance = NULL;

//////////////////////////////////////////////
////////////////////FOC PL////////////////////
//////////////////////////////////////////////
#include "IP_Cores/uz_FOC/xuz_foc.h"
XUz_foc FOC_ip_instance;
uint32_t* int_KI = (uint32_t*)&PI_config.Ki;
uint32_t* int_KP = (uint32_t*)&PI_config.Kp;
uint32_t* int_limit = (uint32_t*)&PI_config.upper_limit;
uint32_t* int_ts = (uint32_t*)&PI_config.samplingTime_sec;

#include "IP_Cores/uz_SPWM/xuz_spwm_3ph.h"
XUz_spwm_3ph ip_SPWM_0;
XUz_spwm_3ph ip_SPWM_1;
uint32_t* int_udc = (uint32_t*)&openhw_udc;

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
            uz_SystemTime_init();
            JavaScope_initalize(&Global_Data);
            initialization_chain = init_ip_cores;
            break;
        case init_ip_cores:
            uz_adcLtc2311_ip_core_init();
            Global_Data.objects.deadtime_interlock_d1_pin_0_to_5 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_0_to_5();
            Global_Data.objects.deadtime_interlock_d1_pin_6_to_11 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_6_to_11();
//            Global_Data.objects.deadtime_interlock_d1_pin_12_to_17 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_12_to_17();
//            Global_Data.objects.deadtime_interlock_d1_pin_18_to_23 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_18_to_23();
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, true);
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, true);
//            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_12_to_17, true);
//            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_18_to_23, true);
            Global_Data.objects.pwm_d1_pin_0_to_5 = initialize_pwm_2l_on_D1_pin_0_to_5();
            Global_Data.objects.pwm_d1_pin_6_to_11 = initialize_pwm_2l_on_D1_pin_6_to_11();
//            Global_Data.objects.pwm_d1_pin_12_to_17 = initialize_pwm_2l_on_D1_pin_12_to_17();
//            Global_Data.objects.pwm_d1_pin_18_to_23 = initialize_pwm_2l_on_D1_pin_18_to_23();
            Global_Data.objects.mux_axi = initialize_uz_mux_axi();
            PWM_3L_Initialize(&Global_Data); // three-level modulator
//          initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);

            //CIL
            pmsm = uz_pmsm_model6ph_dq_init(cil_pmsm_comfig);
			transformation = uz_pmsm6ph_transformation_init(cil_transformation_config);
			inverter1 = uz_inverter_3ph_init(cil_inverter1_config);
			inverter2 = uz_inverter_3ph_init(cil_inverter2_config);
			//FOX UZ
			if(openhw_pspl){
				PI_config.samplingTime_sec = 0.0001f;
			}
			struct uz_CurrentControl_config cc_config = {
				.config_PMSM = config_PMSM,
				.config_id = PI_config,
				.config_iq = PI_config,
				.decoupling_select = no_decoupling,
				.max_modulation_index = 1.0f
			};
			cc_instance = uz_CurrentControl_init(cc_config);
			//FOC controller FPGA
			XUz_foc_Initialize(&FOC_ip_instance, XPAR_UZ_USER_TRANSFORMATION_AND_CONTROL_UZ_FOC_0_DEVICE_ID);
			XUz_foc_Set_axi_id_KI(&FOC_ip_instance, *int_KI);
			XUz_foc_Set_axi_id_KP(&FOC_ip_instance, *int_KP);
			XUz_foc_Set_axi_limit(&FOC_ip_instance, *int_limit);
			XUz_foc_Set_axi_sampletime(&FOC_ip_instance, *int_ts);
			XUz_foc_Set_axi_iq_KI(&FOC_ip_instance, *int_KI);
			XUz_foc_Set_axi_iq_KP(&FOC_ip_instance, *int_KP);
			//SPWM FPGA
			XUz_spwm_3ph_Initialize(&ip_SPWM_0, XPAR_UZ_USER_TRANSFORMATION_AND_CONTROL_UZ_SPWM_3PH_0_DEVICE_ID);
			XUz_spwm_3ph_Initialize(&ip_SPWM_1, XPAR_UZ_USER_TRANSFORMATION_AND_CONTROL_UZ_SPWM_3PH_1_DEVICE_ID);
			XUz_spwm_3ph_Set_u_dc(&ip_SPWM_0, *int_udc);
			XUz_spwm_3ph_Set_u_dc(&ip_SPWM_1, *int_udc);
			//end

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
