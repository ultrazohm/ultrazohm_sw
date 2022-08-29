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

#include "../include/isr.h"
#include "../defines.h"
#include "../main.h"
#include "../include/ipc_ARM.h"
#include <math.h>
#include <xtmrctr.h>
#include "../include/javascope.h"
#include "../include/pwm_3L_driver.h"
#include "../include/adc.h"
#include "../include/encoder.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"
#include "../uz/uz_global_configuration.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

// Variables for PMSM IP-Core
extern uz_pmsmModel_t *pmsm;

struct uz_pmsmModel_inputs_t pmsm_inputs={
  .omega_mech_1_s=0.0f,
  .v_d_V=0.0f,
  .v_q_V=0.0f,
  .load_torque=0.0f
};
struct uz_pmsmModel_outputs_t pmsm_outputs={
  .i_d_A=0.0f,
  .i_q_A=0.0f,
  .torque_Nm=0.0f,
  .omega_mech_1_s=0.0f
};


// Variables for NN
extern uz_matrix_t* input;
uz_matrix_t* output;
extern uz_nn_t *layer;
extern uz_matrix_t input_matrix;

struct uz_3ph_dq_t ddpg_output_V = {0};
struct uz_3ph_abc_t ddpg_output_abc_V = {0};

// Variables for left motor
extern uz_FOC* FOC_instance_left;

struct uz_3ph_dq_t i_actual_A = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_abc_t i_actual_A_abc = {0};
struct uz_3ph_dq_t i_reference_A = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t i_error_A = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t i_integrated_error_A = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t FOC_output_Volts = {0};
struct uz_3ph_abc_t FOC_output_abc_Volts = {0};
struct uz_DutyCycle_t dutycyle = {0};

float omega_el_rad_per_sec = 0.0f;
float V_dc_volts = 24.0f;
float theta_offset = 0.2f; // zum Bestimmen eine Phase bestromen, dadurch Ausrichtung d-Achse auf bestromte, theta_elec muss 0 oder 2pi sein mit offset
float adc_scaling = (20.0f/2.084f)/3.0f;
float poles = 3.0f;

// Variables for right motor
extern uz_FOC* FOC_instance_right;
extern uz_SpeedControl_t* Speed_control_instance;

struct uz_3ph_dq_t i_actual_A_right = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_abc_t i_actual_A_abc_right = {0};
struct uz_3ph_dq_t i_reference_A_right = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t i_error_A_right = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t i_integrated_error_A_right = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t FOC_output_Volts_right = {0};
struct uz_3ph_abc_t FOC_output_abc_Volts_right = {0};
struct uz_DutyCycle_t dutycyle_right = {0};

float n_ref_rpm = 0.0f;
float omega_el_ref_rad_per_sec_right = 0.0f;
float omega_m_rad_per_sec_right = 0.0f;
float omega_el_rad_per_sec_right = 0.0f;
float theta_offset_right = 0.2f;
float adc_scaling_right = (20.0f/2.084f)/3.0f;
float poles_right = 3.0f;

// Choose control type for left motor
enum control
{
	foc_ip,
	foc_echt,
	ddpg_ip,
	ddpg_echt,
	none
};

enum control control_type_motor_left=none;

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    // right motor
    Global_Data.av.theta_elec = fmodf(Global_Data.av.theta_elec*poles_right,2*M_PI)-theta_offset_right; // *poles da bei PMSM config nur 1 Pol angegeben
    i_actual_A_abc_right.a = (Global_Data.aa.A1.me.ADC_A2-2.5f)*adc_scaling_right; // zeigt 2.5 bei 0 an
    i_actual_A_abc_right.b = (Global_Data.aa.A1.me.ADC_A3-2.5f)*adc_scaling_right;
    i_actual_A_abc_right.c = (Global_Data.aa.A1.me.ADC_A4-2.5f)*adc_scaling_right;
    i_actual_A_right = uz_transformation_3ph_abc_to_dq(i_actual_A_abc_right, Global_Data.av.theta_elec);
    omega_m_rad_per_sec_right = Global_Data.av.mechanicalRotorSpeed*2.0f*M_PI/60.0f;
    omega_el_rad_per_sec_right = omega_m_rad_per_sec_right*poles_right;

    // left motor
    if ((control_type_motor_left == foc_echt) || (control_type_motor_left ==ddpg_echt)) {
    Global_Data.av.theta_elec = fmodf(Global_Data.av.theta_elec*poles,2*M_PI)-theta_offset; // *poles da bei PMSM config nur 1 Pol angegeben
    i_actual_A_abc.a = (Global_Data.aa.A1.me.ADC_A2-2.5f)*adc_scaling; // zeigt 2.5 bei 0 an
    i_actual_A_abc.b = (Global_Data.aa.A1.me.ADC_A3-2.5f)*adc_scaling;
    i_actual_A_abc.c = (Global_Data.aa.A1.me.ADC_A4-2.5f)*adc_scaling;
    i_actual_A = uz_transformation_3ph_abc_to_dq(i_actual_A_abc, Global_Data.av.theta_elec);
    omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed*poles*2.0f*M_PI/60.0f;
    }

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
    	// right motor
    	n_ref_rpm = omega_el_ref_rad_per_sec_right*60.0f/(2.0f*M_PI);
    	i_reference_A_right = uz_SpeedControl_sample(Speed_control_instance, omega_m_rad_per_sec_right, n_ref_rpm, V_dc_volts, i_reference_A_right.d);
		FOC_output_Volts_right = uz_FOC_sample(FOC_instance_right, i_reference_A_right, i_actual_A_right, V_dc_volts, omega_el_rad_per_sec_right);
		FOC_output_abc_Volts_right = uz_transformation_3ph_dq_to_abc(FOC_output_Volts_right, Global_Data.av.theta_elec);
		dutycyle_right = uz_FOC_generate_DutyCycles(FOC_output_abc_Volts_right, V_dc_volts);
    	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, dutycyle_right.DutyCycle_U, dutycyle_right.DutyCycle_V, dutycyle_right.DutyCycle_W);

    	// left motor
    	switch (control_type_motor_left) {
    		case foc_ip:
    	        uz_pmsmModel_trigger_input_strobe(pmsm);
    	        uz_pmsmModel_trigger_output_strobe(pmsm);
    	        pmsm_outputs=uz_pmsmModel_get_outputs(pmsm);
    	        i_actual_A.d = pmsm_outputs.i_d_A;
    	        i_actual_A.q = pmsm_outputs.i_q_A;
    	        FOC_output_Volts = uz_FOC_sample(FOC_instance_left, i_reference_A, i_actual_A, V_dc_volts, omega_el_rad_per_sec);
    	        pmsm_inputs.v_q_V=FOC_output_Volts.q;
    	        pmsm_inputs.v_d_V=FOC_output_Volts.d;
    	        pmsm_inputs.omega_mech_1_s = omega_el_rad_per_sec/poles;
    	        uz_pmsmModel_set_inputs(pmsm, pmsm_inputs);
    			break;
    		case foc_echt:
    			FOC_output_Volts = uz_FOC_sample(FOC_instance_left, i_reference_A, i_actual_A, V_dc_volts, omega_el_rad_per_sec);
    			FOC_output_abc_Volts = uz_transformation_3ph_dq_to_abc(FOC_output_Volts, Global_Data.av.theta_elec);
    			dutycyle = uz_FOC_generate_DutyCycles(FOC_output_abc_Volts, V_dc_volts);
    	    	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, dutycyle.DutyCycle_U, dutycyle.DutyCycle_V, dutycyle.DutyCycle_W);
    			break;
    		case ddpg_ip:
    	        uz_pmsmModel_trigger_input_strobe(pmsm);
    	        uz_pmsmModel_trigger_output_strobe(pmsm);
    	        pmsm_outputs=uz_pmsmModel_get_outputs(pmsm);
    	        i_actual_A.d = pmsm_outputs.i_d_A;
    	        i_actual_A.q = pmsm_outputs.i_q_A;
    	        i_integrated_error_A.d += i_error_A.d * (1/UZ_PWM_FREQUENCY); // use Forward-Euler with error of previous timestep for integration
    	        i_integrated_error_A.q += i_error_A.q * (1/UZ_PWM_FREQUENCY);
    	        i_error_A.d = i_reference_A.d - i_actual_A.d;
    	        i_error_A.q = i_reference_A.q - i_actual_A.q;
    	        float observation_ip[NUMBER_OF_INPUTS] = {i_error_A.d,100*i_integrated_error_A.d,i_error_A.q,100*i_integrated_error_A.q,i_actual_A.d,i_actual_A.q,omega_el_rad_per_sec/500.0f};
    	        for (uint32_t i = 0; i < NUMBER_OF_INPUTS; i++)
    	        {
    	        	uz_matrix_set_element_zero_based(input,observation_ip[i],0,i);
    	        }
    	        uz_nn_ff(layer,input);
    	        output=uz_nn_get_output_data(layer);
    	        uz_matrix_multiply_by_scalar(output,48.0f); // scaling layer of nn
    	        pmsm_inputs.v_d_V = uz_matrix_get_element_zero_based(output,0,0);
    	        pmsm_inputs.v_q_V = uz_matrix_get_element_zero_based(output,0,1);
    	        pmsm_inputs.omega_mech_1_s = omega_el_rad_per_sec/poles;
    	        uz_pmsmModel_set_inputs(pmsm, pmsm_inputs);
    			break;
    		case ddpg_echt:
    	        i_integrated_error_A.d += i_error_A.d * (1/UZ_PWM_FREQUENCY); // use Forward-Euler with error of previous timestep for integration
    	        i_integrated_error_A.q += i_error_A.q * (1/UZ_PWM_FREQUENCY);
    	        i_error_A.d = i_reference_A.d - i_actual_A.d;
    	        i_error_A.q = i_reference_A.q - i_actual_A.q;
    	        float observation_echt[NUMBER_OF_INPUTS] = {i_error_A.d,100*i_integrated_error_A.d,i_error_A.q,100*i_integrated_error_A.q,i_actual_A.d,i_actual_A.q,omega_el_rad_per_sec/500.0f};
    	        for (uint32_t i = 0; i < NUMBER_OF_INPUTS; i++)
    	        {
    	        	uz_matrix_set_element_zero_based(input,observation_echt[i],0,i);
    	        }
    	        uz_nn_ff(layer,input);
    	        output=uz_nn_get_output_data(layer);
    	        uz_matrix_multiply_by_scalar(output,48.0f); // scaling layer of nn
    	        ddpg_output_V.d = uz_matrix_get_element_zero_based(output,0,0);
    	        ddpg_output_V.q = uz_matrix_get_element_zero_based(output,0,1);
    	        ddpg_output_abc_V = uz_transformation_3ph_dq_to_abc(ddpg_output_V, Global_Data.av.theta_elec);
    			dutycyle = uz_FOC_generate_DutyCycles(ddpg_output_abc_V, V_dc_volts);
    	    	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, dutycyle.DutyCycle_U, dutycyle.DutyCycle_V, dutycyle.DutyCycle_W);
    			break;
    		case none:
    			// Motor 1 auf was setzen?
    			break;
    		default: abort();
    	}
    }
    else{
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
    }
    // Set duty cycles for three-level modulator
//    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
//                        Global_Data.rasv.halfBridge2DutyCycle,
//                        Global_Data.rasv.halfBridge3DutyCycle);
    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

//==============================================================================================================================================================

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR()
{

    int Status = 0;

    // Initialize interrupt controller for the IPI -> Initialize RPU IPI
    Status = Rpu_IpiInit(INTERRUPT_ID_IPI);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI initialization failed\r\n");
        return XST_FAILURE;
    }

    // Initialize interrupt controller for the GIC
    Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG, &Timer_Interrupt);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable uz_mux_axi for triggering the ADCs and the ISR
//    uz_mux_axi_hw_enable_IP_core(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR);
//    uz_mux_axi_hw_set_mux(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
//    uz_mux_axi_hw_set_n_th_interrupt(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
    //uz_mux_axi_enable(Global_Data.objects.mux_axi);

    return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE AXI-TIMER FOR ISRs
// - "TIMER_LOAD_VALUE" sets the counter-end-value in order to set the ISR-frequency f_c
// - "Con_TIMER_DEVICE_ID" uses the Device-ID of the used timer in Vivado
// - "Timer_Interrupt" is the used timer structure instance
// - "XTC_INT_MODE_OPTION" activates the Interrupt function
// - "XTC_AUTO_RELOAD_OPTION" activates an automatic reload of the timer
// - By default, the counter counts up
//----------------------------------------------------
int Initialize_Timer()
{

    int Status;

    // SETUP THE TIMER 1 for Interrupts
    Status = XTmrCtr_Initialize(&Timer_Interrupt, XPAR_UZ_SYSTEM_INTERRUPT_TRIGGER_F_CC_DEVICE_ID);
    if (Status != XST_SUCCESS)
        return XST_FAILURE;
    // XTmrCtr_SetHandler(&Timer_Interrupt, ISR_Control, &Timer_Interrupt);
    XTmrCtr_SetOptions(&Timer_Interrupt, 0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
    XTmrCtr_SetResetValue(&Timer_Interrupt, 0, TIMER_LOAD_VALUE);
    XTmrCtr_Reset(&Timer_Interrupt, 0);
    XTmrCtr_Start(&Timer_Interrupt, 0);

    return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_GicInit() - This function initializes RPU GIC and connects
// 					interrupts with the associated handlers
// @IntcInstPtr		Pointer to the GIC instance
// @IntId			Interrupt ID to be connected and enabled
// @Handler			Associated handler for the Interrupt ID
// @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
//----------------------------------------------------
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId, XTmrCtr *Timer_Interrupt_InstancePtr)
{
    XScuGic_Config *IntcConfig;
    int status;

    // Interrupt controller initialization
    IntcConfig = XScuGic_LookupConfig(DeviceId);
    status = XScuGic_CfgInitialize(IntcInstPtr, IntcConfig, IntcConfig->CpuBaseAddress);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, IntcInstPtr);

    /* Enable interrupts in the processor */
    Xil_ExceptionEnable(); // Enable interrupts in the ARM

    // setting interrupt trigger sensitivity
    // b01	Active HIGH level sensitive
    // b11 	Rising edge sensitive
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(IntcInstPtr, Interrupt_ISR_ID, 0x0, 0b11); // rising-edge
    // XScuGic_SetPriorityTriggerType(&INTCInst, Interrupt_ISR_ID, 0x0, 0b01); // active-high - default case

    // Make the connection between the IntId of the interrupt source and the
    // associated handler that is to run when the interrupt is recognized.
    status = XScuGic_Connect(IntcInstPtr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             (void *)IntcInstPtr);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Enable GPIO and timer interrupts in the controller
    XScuGic_Enable(IntcInstPtr, Interrupt_ISR_ID);
    XScuGic_Enable(IntcInstPtr, INTC_IPC_Shared_INTERRUPT_ID);

    xil_printf("RPU: Rpu_GicInit: Done\r\n");
    return XST_SUCCESS;
}

//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_IpiInit() - This function initializes RPU IPI and enables IPI interrupts
//
// @IpiInstPtr		Pointer to the IPI instance
//----------------------------------------------------
u32 Rpu_IpiInit(u16 DeviceId)
{
    XIpiPsu_Config *IntcConfig_IPI;
    int status;

    // Interrupt controller configuration
    IntcConfig_IPI = XIpiPsu_LookupConfig(DeviceId);
    if (IntcConfig_IPI == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&INTCInst_IPI, IntcConfig_IPI, IntcConfig_IPI->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: RPU_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static void ReadAllADC()
{
    ADC_readCardALL(&Global_Data);
};
