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
#include "../uz/uz_FOC/uz_FOC.h"
// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;
extern uz_codegen codegenInstance;

#define CURRENT_CONV_FACTOR 80.0f/3.0f
#define PN 1.0f
#define theta_offset 1.1f
#define dc_link 15.0f
#define VOLTAGE_CONV_FACTOR 12.5f
#define MAX_CURRENT_ASSERTION 20.0f
#define MAX_SPEED_ASSERTION 1500.0f
#define voltage_offsetL13 8.6f
#define voltage_offsetL2 8.8f

uz_3ph_abc_t three_phase_output = {0};
bool is_three_phase_active = false;
struct uz_DutyCycle_t duty_cycles={0};

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();

extern uz_pmsmModel_t *pmsm;
extern uz_FOC* FOC_instance;
uz_3ph_dq_t reference_currents_Amp = {0};
uz_3ph_dq_t measured_currents_dq_Amp = {0};
uz_3ph_dq_t FOC_output_Volts = {0};
uz_3ph_abc_t measured_currents_uvw_Amp = {0};
uz_3ph_abc_t calc_voltage_uvw = {0};
uz_3ph_dq_t output_dq = {0};
float omega_el_rad_per_sec = 0.0f;
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
float theta_el_rad = 0.0f;
float rpm_ref = 0.0f;
float torque_ref = 0.0f;
int option = 0;

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
	update_speed_and_position_of_encoder_on_D5(&Global_Data);

	codegenInstance.input.omega = (2.0f * M_PI *rpm_ref / 60.0f) * PN ;
	codegenInstance.input.torque = torque_ref;
    uz_codegen_step(&codegenInstance);

	measured_currents_uvw_Amp.a = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A1-2.5f);
	measured_currents_uvw_Amp.b = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A2-2.5f);
	measured_currents_uvw_Amp.c = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A3-2.5f);

	Global_Data.av.U_L1 = VOLTAGE_CONV_FACTOR * Global_Data.aa.A2.me.ADC_B5 - voltage_offsetL13;
	Global_Data.av.U_L2 = VOLTAGE_CONV_FACTOR * Global_Data.aa.A2.me.ADC_B6 - voltage_offsetL2;
	Global_Data.av.U_L3 = VOLTAGE_CONV_FACTOR * Global_Data.aa.A2.me.ADC_B7 - voltage_offsetL13;

	Global_Data.av.U_ZK = VOLTAGE_CONV_FACTOR * Global_Data.aa.A2.me.ADC_A4;

	Global_Data.av.mechanicalTorqueObserved = Global_Data.aa.A1.me.ADC_A1 * (-2.0f);

	if ((fabs(measured_currents_uvw_Amp.a) > MAX_CURRENT_ASSERTION) || (fabs(measured_currents_uvw_Amp.b) > MAX_CURRENT_ASSERTION) || (fabs(measured_currents_uvw_Amp.c) > MAX_CURRENT_ASSERTION) || (fabs(Global_Data.av.mechanicalRotorSpeed_filtered) > MAX_SPEED_ASSERTION)) {
		uz_assert(0);
		/*Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
		ultrazohm_state_machine_set_stop(true);*/
	}

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
    	//get data



		// options: 1=mtpa_tb, 2=me_tb, 3=mtpa_ip, 4=me_ip, 5=mtpa_tb_current
		switch (option){
			case (1):
    	    		reference_currents_Amp.d = codegenInstance.output.MTPA_id;
    	    		reference_currents_Amp.q = codegenInstance.output.MTPA_iq;
    	    		//reading out the phase currents and encoder data
    	    		/*measured_currents_uvw_Amp.a = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A2-2.5f);
    	    		measured_currents_uvw_Amp.b = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A4-2.5f);
    	    		measured_currents_uvw_Amp.c = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A3-2.5f);*/

    				theta_el_rad = (Global_Data.av.theta_elec - theta_offset) * PN;
    				omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed_filtered * (2.0f*M_PI/60.0f) * PN;
    				// conversion from uvw- to dq-system (currents)
    				measured_currents_dq_Amp = uz_transformation_3ph_abc_to_dq(measured_currents_uvw_Amp, theta_el_rad);
    				// executing the FOC
    	        	FOC_output_Volts = uz_FOC_sample(FOC_instance, reference_currents_Amp, measured_currents_dq_Amp, dc_link, omega_el_rad_per_sec);
    	        	// conversion from dq- to uvw-system (voltages)
    	        	calc_voltage_uvw = uz_transformation_3ph_dq_to_abc(FOC_output_Volts, theta_el_rad);
    	        	// calculates and sets duty cycles
    	        	duty_cycles=	   uz_FOC_generate_DutyCycles(calc_voltage_uvw, dc_link);
    				Global_Data.rasv.halfBridge1DutyCycle = duty_cycles.DutyCycle_U;
    				Global_Data.rasv.halfBridge2DutyCycle = duty_cycles.DutyCycle_V;
    				Global_Data.rasv.halfBridge3DutyCycle = duty_cycles.DutyCycle_W;
    	    		break;
			case (2):
    	    		reference_currents_Amp.d = codegenInstance.output.ME_id;
    	    		reference_currents_Amp.q = codegenInstance.output.ME_iq;
    	    		//reading out the phase currents and encoder data
    	    		/*measured_currents_uvw_Amp.a = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A2-2.5f);
    	    		measured_currents_uvw_Amp.b = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A4-2.5f);
    	    		measured_currents_uvw_Amp.c = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A3-2.5f);*/
    				update_speed_and_position_of_encoder_on_D5(&Global_Data);
    				theta_el_rad = (Global_Data.av.theta_elec - theta_offset) * PN;
    				omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed_filtered * (2.0f*M_PI/60.0f) * PN;
    				// conversion from uvw- to dq-system (currents)
    				measured_currents_dq_Amp = uz_transformation_3ph_abc_to_dq(measured_currents_uvw_Amp, theta_el_rad);
    				// executing the FOC
    	        	FOC_output_Volts = uz_FOC_sample(FOC_instance, reference_currents_Amp, measured_currents_dq_Amp, dc_link, omega_el_rad_per_sec);
    	        	// conversion from dq- to uvw-system (voltages)
    	        	calc_voltage_uvw = uz_transformation_3ph_dq_to_abc(FOC_output_Volts, theta_el_rad);
    	        	// calculates and sets duty cycles
    	        	duty_cycles=	   uz_FOC_generate_DutyCycles(calc_voltage_uvw, dc_link);
    				Global_Data.rasv.halfBridge1DutyCycle = duty_cycles.DutyCycle_U;
    				Global_Data.rasv.halfBridge2DutyCycle = duty_cycles.DutyCycle_V;
    				Global_Data.rasv.halfBridge3DutyCycle = duty_cycles.DutyCycle_W;
    	    		break;
			case (3):
					//starts pmsm model, reads outputs, sets rpm_ref
					uz_pmsmModel_trigger_input_strobe(pmsm);
					uz_pmsmModel_trigger_output_strobe(pmsm);
					pmsm_outputs=uz_pmsmModel_get_outputs(pmsm);
					pmsm_inputs.omega_mech_1_s = 2 * M_PI * rpm_ref / 60.0f;
					// reads reference currents from LUT
    	    		reference_currents_Amp.d = codegenInstance.output.MTPA_id;
    	    		reference_currents_Amp.q = codegenInstance.output.MTPA_iq;
    	    		// reads output currents & omega from pmsm model
    	    		measured_currents_dq_Amp.d = pmsm_outputs.i_d_A;
					measured_currents_dq_Amp.q = pmsm_outputs.i_q_A;
					omega_el_rad_per_sec = pmsm_outputs.omega_mech_1_s * PN;
    				// executing the FOC
					FOC_output_Volts = uz_FOC_sample(FOC_instance, reference_currents_Amp, measured_currents_dq_Amp, 24.0f, omega_el_rad_per_sec);
					// feeds output voltages back to input
					pmsm_inputs.v_q_V=FOC_output_Volts.q;
					pmsm_inputs.v_d_V=FOC_output_Volts.d;
					// sets inputs
					uz_pmsmModel_set_inputs(pmsm, pmsm_inputs);
    	    		break;
			case (4):
					//starts pmsm model, reads outputs, sets rpm_ref
					uz_pmsmModel_trigger_input_strobe(pmsm);
					uz_pmsmModel_trigger_output_strobe(pmsm);
					pmsm_outputs=uz_pmsmModel_get_outputs(pmsm);
					pmsm_inputs.omega_mech_1_s = 2 * M_PI * rpm_ref / 60.0f;
					// reads reference currents from LUT
    	    		reference_currents_Amp.d = codegenInstance.output.ME_id;
    	    		reference_currents_Amp.q = codegenInstance.output.ME_iq;
    	    		// reads output currents & omega from pmsm model
					measured_currents_dq_Amp.d = pmsm_outputs.i_d_A;
					measured_currents_dq_Amp.q = pmsm_outputs.i_q_A;
					omega_el_rad_per_sec = pmsm_outputs.omega_mech_1_s * PN;
    				// executing the FOC
					FOC_output_Volts = uz_FOC_sample(FOC_instance, reference_currents_Amp, measured_currents_dq_Amp, 24.0f, omega_el_rad_per_sec);
					// feeds output voltages back to input
					pmsm_inputs.v_q_V=FOC_output_Volts.q;
					pmsm_inputs.v_d_V=FOC_output_Volts.d;
					// sets inputs
					uz_pmsmModel_set_inputs(pmsm, pmsm_inputs);
    	    		break;
			case (5):
					//reading out the phase currents and encoder data
					/*measured_currents_uvw_Amp.a = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A2-2.5f);
					measured_currents_uvw_Amp.b = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A4-2.5f);
					measured_currents_uvw_Amp.c = CURRENT_CONV_FACTOR * (Global_Data.aa.A2.me.ADC_A3-2.5f);*/
					update_speed_and_position_of_encoder_on_D5(&Global_Data);
					theta_el_rad = (Global_Data.av.theta_elec - theta_offset) * PN;
					omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed_filtered * (2.0f*M_PI/60.0f) * PN;
					// conversion from uvw- to dq-system (currents)
					measured_currents_dq_Amp = uz_transformation_3ph_abc_to_dq(measured_currents_uvw_Amp, theta_el_rad);
					// executing the FOC
					FOC_output_Volts = uz_FOC_sample(FOC_instance, reference_currents_Amp, measured_currents_dq_Amp, dc_link, omega_el_rad_per_sec);
					// conversion from dq- to uvw-system (voltages)
					calc_voltage_uvw = uz_transformation_3ph_dq_to_abc(FOC_output_Volts, theta_el_rad);
					// calculates and sets duty cycles
					duty_cycles=	   uz_FOC_generate_DutyCycles(calc_voltage_uvw, dc_link);
					Global_Data.rasv.halfBridge1DutyCycle = duty_cycles.DutyCycle_U;
					Global_Data.rasv.halfBridge2DutyCycle = duty_cycles.DutyCycle_V;
					Global_Data.rasv.halfBridge3DutyCycle = duty_cycles.DutyCycle_W;
					break;
			default:
					Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
					Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
					Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		}



	} else { //if (current_state!=control_state || !is_three_phase_active) {
		 Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		 Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		 Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
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
