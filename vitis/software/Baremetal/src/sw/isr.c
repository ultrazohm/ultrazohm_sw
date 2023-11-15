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
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

# define MAX_CURRENT 10.0f
# define CONROL_FREQUENCY 10000
//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();

bool use_CiL = false;
bool use_Motor = false;
bool select_automatic_idiq = false;
bool use_PI = false;
bool use_NN = false;

extern uz_CurrentControl_t* CurrentControl_instance;
struct uz_3ph_dq_t i_dq_reference_Ampere = {0};
struct uz_3ph_dq_t reference_currents_Amp_javascope = {0};
struct uz_3ph_dq_t i_dq_CIL_Ampere = {0};
float reference_n_javascope = 0.0f;
struct uz_3ph_dq_t CurrentControl_output_Volts = {0};
struct uz_3ph_abc_t i_abc_actual_Ampere = {0};
struct uz_3ph_abc_t v_abc_actualVolts = {0};
struct uz_3ph_dq_t i_dq_actual_Ampere = {0};
struct uz_3ph_dq_t v_dq_actual_Volts = {0};
struct uz_3ph_dq_t v_dq_non_limited_Volts = {0};
struct uz_3ph_dq_t v_dq_limited_Volts = {0};
struct uz_DutyCycle_t DutyCycle_output = {0};
float max_modulation_index = 1.0f / 1.732050808f;
bool ext_clamping = false;

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

extern uz_matrix_t* input;
extern uz_nn_t *my_NN;
uz_matrix_t* output;

float offset = 3.31f;
float start_marker=0.0f;
float obs[NUMBER_OF_INPUTS] = {};
float a_d_k_1 = 0;
float a_q_k_1 = 0;
int k = 0;
int idx = 0;

// Reference profile idq
float ref_iq[10] = {
	0, 2, -2, -1, 3, -1, -3, -4, -2, 2
};

float ref_id[10] ={
	0,1,2,3,3,-2,0,-0.5,2, 2
};

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    platform_state_t current_state=ultrazohm_state_machine_get_state();

	if (select_automatic_idiq) {
		start_marker = 1.0f;;
		if ((k%200)==0) {
			if (idx >= (sizeof(ref_id)/sizeof(ref_id[0]))) {
				i_dq_reference_Ampere.d = 0;
				i_dq_reference_Ampere.q = 0;
			} else {
				i_dq_reference_Ampere.d = ref_id[idx];
				i_dq_reference_Ampere.q = ref_iq[idx];
				idx+=1;
			}
		}
		k+=1;
	} else {
		i_dq_reference_Ampere = reference_currents_Amp_javascope;
		k=0;
		idx=0;
	}

	if (use_CiL) {
		uz_pmsmModel_trigger_input_strobe(Global_Data.objects.pmsm_IP_core);
		uz_pmsmModel_trigger_output_strobe(Global_Data.objects.pmsm_IP_core);
		pmsm_outputs=uz_pmsmModel_get_outputs(Global_Data.objects.pmsm_IP_core);
		i_dq_CIL_Ampere.d = pmsm_outputs.i_d_A;
		i_dq_CIL_Ampere.q = pmsm_outputs.i_q_A;
		Global_Data.av.I_d = pmsm_outputs.i_d_A;
		Global_Data.av.I_q = pmsm_outputs.i_q_A;
		Global_Data.av.omega_m = pmsm_outputs.omega_mech_1_s;
		Global_Data.av.mechanicalRotorSpeed = pmsm_outputs.omega_mech_1_s * 30.0f / M_PI;
		Global_Data.av.omega_elec = pmsm_outputs.omega_mech_1_s * 3.0f;

		if (current_state==control_state) {
			if (use_PI) {
				CurrentControl_output_Volts = uz_CurrentControl_sample(CurrentControl_instance, i_dq_reference_Ampere, i_dq_CIL_Ampere, 48.0f, Global_Data.av.omega_elec);
				pmsm_inputs.v_d_V = CurrentControl_output_Volts.d;
				pmsm_inputs.v_q_V = CurrentControl_output_Volts.q;
				pmsm_inputs.omega_mech_1_s = reference_n_javascope / 30.0f * M_PI;
				uz_pmsmModel_set_inputs(Global_Data.objects.pmsm_IP_core, pmsm_inputs);
			}
			if (use_NN) {
				pmsm_inputs.omega_mech_1_s = reference_n_javascope / 30.0f * M_PI;

				obs[0] = i_dq_CIL_Ampere.d/10.8f/sqrt(2);
				obs[1] = i_dq_CIL_Ampere.q/10.8f/sqrt(2);
				obs[2] = Global_Data.av.mechanicalRotorSpeed/4140.0f;
				obs[3] = a_d_k_1;
				obs[4] = a_q_k_1;
				obs[5] = i_dq_reference_Ampere.d/10.8f/sqrt(2);
				obs[6] = i_dq_reference_Ampere.q/10.8f/sqrt(2);

				for (uint32_t i = 0; i < NUMBER_OF_INPUTS; i++) {
					uz_matrix_set_element_zero_based(input,obs[i],0,i);
				}

				uz_nn_ff(my_NN, input);
				output=uz_nn_get_output_data(my_NN);
				a_d_k_1 = uz_matrix_get_element_zero_based(output,0,0);
				a_q_k_1 = uz_matrix_get_element_zero_based(output,0,1);
				uz_matrix_multiply_by_scalar(output,24.0f);

				/*float v_d = uz_matrix_get_element_zero_based(output,0,0);
				float v_q = uz_matrix_get_element_zero_based(output,0,1);

				float eps_elec = Global_Data.av.mechanicalRotorSpeed * M_PI / 30.0f * 3.0f;

				float cumulative_angle +=*/

				pmsm_inputs.v_d_V = uz_matrix_get_element_zero_based(output,0,0);
				pmsm_inputs.v_q_V = uz_matrix_get_element_zero_based(output,0,1);

				uz_pmsmModel_set_inputs(Global_Data.objects.pmsm_IP_core, pmsm_inputs);
				Global_Data.av.U_d = pmsm_inputs.v_d_V;
				Global_Data.av.U_q = pmsm_inputs.v_q_V;
			}
		}
	}
	if (use_Motor) {
    	Global_Data.av.theta_mech = Global_Data.av.theta_mech - offset;
    	Global_Data.av.omega_elec = Global_Data.av.omega_m * 3.0f;
    	Global_Data.av.theta_elec = Global_Data.av.theta_mech * 3.0f;  // changed the encoder function to write the theta onto theta_mech
    	//Global_Data.av.theta_elec_adv = Global_Data.av.theta_elec;
    	Global_Data.av.theta_elec_adv = 1.5f / CONROL_FREQUENCY * Global_Data.av.omega_elec + Global_Data.av.theta_elec;	// angle advance 3/2*T_a*omega
    	Global_Data.av.inverter_outputs_d3 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d3);
    	Global_Data.av.I_a = Global_Data.aa.A1.me.ADC_A4 * 12.5f;
    	Global_Data.av.I_b = Global_Data.aa.A1.me.ADC_A3 * 12.5f;
    	Global_Data.av.I_c = Global_Data.aa.A1.me.ADC_A2 * 12.5f;
    	Global_Data.av.I_DC = Global_Data.aa.A1.me.ADC_B5 * 12.5f;
    	Global_Data.av.U_a = Global_Data.aa.A1.me.ADC_B8 * 12.0f;
    	Global_Data.av.U_b = Global_Data.aa.A1.me.ADC_B7 * 12.0f;
    	Global_Data.av.U_c = Global_Data.aa.A1.me.ADC_B6 * 12.0f;
    	Global_Data.av.U_ZK = Global_Data.aa.A1.me.ADC_A1 * 12.0f;

    	// assign measurements to motor control structs
    	i_abc_actual_Ampere.a = Global_Data.av.I_a;
    	i_abc_actual_Ampere.b = Global_Data.av.I_b;
    	i_abc_actual_Ampere.c = Global_Data.av.I_c;
    	v_abc_actualVolts.a = Global_Data.av.U_a;
    	v_abc_actualVolts.b = Global_Data.av.U_b;
    	v_abc_actualVolts.c = Global_Data.av.U_c;
    	i_dq_actual_Ampere = uz_transformation_3ph_abc_to_dq(i_abc_actual_Ampere, Global_Data.av.theta_elec);
    	v_dq_actual_Volts = uz_transformation_3ph_abc_to_dq(v_abc_actualVolts, Global_Data.av.theta_elec);
    	Global_Data.av.I_d = i_dq_actual_Ampere.d;
    	Global_Data.av.I_q = i_dq_actual_Ampere.q;
    	Global_Data.av.U_d = v_dq_actual_Volts.d;
    	Global_Data.av.U_q = v_dq_actual_Volts.q;

    	// check for current limit
    	if (fabs(Global_Data.av.I_a) > MAX_CURRENT || fabs(Global_Data.av.I_b) > MAX_CURRENT || fabs(Global_Data.av.I_c) > MAX_CURRENT) {
    		ultrazohm_state_machine_set_stop(true);
    	}

    	if (current_state == running_state || current_state == control_state) {
			// enable inverter adapter hardware
			uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, true);
		} else {
			// disable inverter adapter hardware
			uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, false);
		}
    	if (current_state==control_state) {
    		if (use_PI) {
    			CurrentControl_output_Volts = uz_CurrentControl_sample(CurrentControl_instance, i_dq_reference_Ampere, i_dq_actual_Ampere, Global_Data.av.U_ZK, Global_Data.av.omega_elec);
    			DutyCycle_output = uz_Space_Vector_Modulation(CurrentControl_output_Volts, Global_Data.av.U_ZK, Global_Data.av.theta_elec_adv);
    			Global_Data.rasv.halfBridge1DutyCycle = DutyCycle_output.DutyCycle_A;
				Global_Data.rasv.halfBridge2DutyCycle = DutyCycle_output.DutyCycle_B;
				Global_Data.rasv.halfBridge3DutyCycle = DutyCycle_output.DutyCycle_C;
    		} else if (use_NN) {
    			obs[0] = i_dq_actual_Ampere.d/10.8f/sqrt(2);
				obs[1] = i_dq_actual_Ampere.q/10.8f/sqrt(2);
				obs[2] = Global_Data.av.mechanicalRotorSpeed/4140.0f;
				obs[3] = a_d_k_1;
				obs[4] = a_q_k_1;
				obs[5] = i_dq_reference_Ampere.d/10.8f/sqrt(2);
				obs[6] = i_dq_reference_Ampere.q/10.8f/sqrt(2);

				for (uint32_t i = 0; i < NUMBER_OF_INPUTS; i++) {
					uz_matrix_set_element_zero_based(input,obs[i],0,i);
				}
				uz_nn_ff(my_NN, input);
				output=uz_nn_get_output_data(my_NN);
				a_d_k_1 = uz_matrix_get_element_zero_based(output,0,0);
				a_q_k_1 = uz_matrix_get_element_zero_based(output,0,1);
				uz_matrix_multiply_by_scalar(output,24.0f);

				v_dq_non_limited_Volts.d = uz_matrix_get_element_zero_based(output,0,0);
				v_dq_non_limited_Volts.q = uz_matrix_get_element_zero_based(output,0,1);

				v_dq_limited_Volts = uz_CurrentControl_SpaceVector_Limitation(v_dq_non_limited_Volts, Global_Data.av.U_ZK, max_modulation_index, Global_Data.av.omega_elec, i_dq_actual_Ampere, &ext_clamping);
				DutyCycle_output = uz_Space_Vector_Modulation(v_dq_limited_Volts, Global_Data.av.U_ZK, Global_Data.av.theta_elec_adv);
				Global_Data.rasv.halfBridge1DutyCycle = DutyCycle_output.DutyCycle_A;
    	  		Global_Data.rasv.halfBridge2DutyCycle = DutyCycle_output.DutyCycle_B;
    	  		Global_Data.rasv.halfBridge3DutyCycle = DutyCycle_output.DutyCycle_C;
    		} else {
    	    	uz_CurrentControl_reset(CurrentControl_instance);
    	    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    		}
    	}
	}

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Set duty cycles for three-level modulator
    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
                        Global_Data.rasv.halfBridge2DutyCycle,
                        Global_Data.rasv.halfBridge3DutyCycle);
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
    Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG);
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
// Rpu_GicInit() - This function initializes RPU GIC and connects
// 					interrupts with the associated handlers
// @IntcInstPtr		Pointer to the GIC instance
// @IntId			Interrupt ID to be connected and enabled
// @Handler			Associated handler for the Interrupt ID
// @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
//----------------------------------------------------
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId)
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
