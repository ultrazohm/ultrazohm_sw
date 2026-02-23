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
#include "xcp/xcp_interface.h"
#include "../IP_Cores/uz_inverter_status/uz_inverter_status_hw.h"
#include "../IP_Cores/uz_inverter_status/uz_inverter_status_hwAddresses.h"
#include "../IP_Cores/uz_pmsm_model_9ph_dq/uz_pmsm_model9ph_dq.h"


// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

uint8_t Control_timer_1ms;
uint8_t Control_timer_10ms;
uint8_t Control_timer_100ms;

uint32_t inverter_status_RDY[3] = {0};
uint32_t inverter_status_FLT[3] = {0};

// ~~~~~~~~~~~
extern uz_pmsm_model9ph_dq_t *pmsm;                               // pointer to PMSM object
struct uz_pmsm_model9ph_dq_outputs_general_t out_general = {0};   // stores general outputs
uz_9ph_dq_t in_voltages = {                                       // stores input voltages (set random voltages for testing)
              .d = 1.0f,
              .q = 2.0f,
              .x1 = 3.0f,
              .y1 = 4.0f,
              .x2 = 5.0f,
              .y2 = 6.0f,
              .x3 = 7.0f,
              .y3 = 8.0f,
              .zero = 9.0f};
uz_9ph_dq_t out_currents = {0};                                   // stores output currents
float omega_mech = 10.0f;                                         // fixed speed can be set from Expressions with this variable
int pmsm_model_reset = 0;                                         // use reset variable to reset integrators from Expressions
// ~~~~~~~~~~~

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

    /* get inverter status */
    inverter_status_FLT[0] = uz_inverter_status_hw_get_FLT(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_GATES_UZ_INVERTER_STATUS_IP_0_BASEADDR);
    inverter_status_RDY[0] = uz_inverter_status_hw_get_RDY(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_GATES_UZ_INVERTER_STATUS_IP_0_BASEADDR);

    ctrl_data.bus_BSW_FCF.Gate_Driver_Status_FLT = (inverter_status_FLT[2] << 12) | (inverter_status_FLT[1] << 6) | inverter_status_FLT[0];
    ctrl_data.bus_BSW_FCF.Gate_Driver_Status_RDY = (inverter_status_RDY[2] << 12) | (inverter_status_RDY[1] << 6) | inverter_status_RDY[0];

    // read position from resolver IP Core
    ctrl_data.bus_BSW_FCF.phi = uz_resolverIP_readElectricalPosition(Global_Data.objects.resolver_left);

    // get intermediate circuit voltage measurement value
    ctrl_data.bus_BSW_FCF.ADC_U_DC = Global_Data.aa.A1.me.ADC_A4*13.97; // µInverter

    // get phase currents measurement values
    ctrl_data.bus_BSW_FCF.ADC_I_ph[0] = (Global_Data.aa.A1.me.ADC_A1-2.5)*40; // CASR25-NP (µInverter) --> offset = 2.5 V, sensitivity = 40 A/V
    ctrl_data.bus_BSW_FCF.ADC_I_ph[1] = (Global_Data.aa.A1.me.ADC_A2-2.5)*40; // CASR25-NP (µInverter) --> offset = 2.5 V, sensitivity = 40 A/V
    ctrl_data.bus_BSW_FCF.ADC_I_ph[2] = (Global_Data.aa.A1.me.ADC_A3-2.5)*40; // CASR25-NP (µInverter) --> offset = 2.5 V, sensitivity = 40 A/V
//    ctrl_data.fcf_in.I_phA[3] =
//    ctrl_data.fcf_in.I_phA[4] =
//    ctrl_data.fcf_in.I_phA[5] =
//    ctrl_data.fcf_in.I_phA[6] =
//    ctrl_data.fcf_in.I_phA[7] =
//    ctrl_data.fcf_in.I_phA[8] =


    // get values from Slow Control Function
//    ctrl_data.fcf_in.I_dq_RefA[0] = ctrl_data.scf_out.I_dq_RefA[0];
//	ctrl_data.fcf_in.I_dq_RefA[1] = ctrl_data.scf_out.I_dq_RefA[1];

	// get values from Stateflow Function
//	ctrl_data.fcf_in.FOC_Mode   = ctrl_data.smf_out.FOC_Mode;
//	ctrl_data.fcf_in.FOC_Enable = ctrl_data.smf_out.FOC_Enable_PWM;

	// write inputs to fast control function of simulink model
//	FOC_FCF_MPtr->inputs->U_DC         = ctrl_data.fcf_in.U_DC;
//	FOC_FCF_MPtr->inputs->I_phA[0]     = ctrl_data.fcf_in.I_phA[0];
//	FOC_FCF_MPtr->inputs->I_phA[1]     = ctrl_data.fcf_in.I_phA[1];
//	FOC_FCF_MPtr->inputs->I_phA[2]     = ctrl_data.fcf_in.I_phA[2];
//	FOC_FCF_MPtr->inputs->I_phA[3]     = ctrl_data.fcf_in.I_phA[3];
//	FOC_FCF_MPtr->inputs->I_phA[4]     = ctrl_data.fcf_in.I_phA[4];
//	FOC_FCF_MPtr->inputs->I_phA[5]     = ctrl_data.fcf_in.I_phA[5];
//	FOC_FCF_MPtr->inputs->I_phA[6]     = ctrl_data.fcf_in.I_phA[6];
//	FOC_FCF_MPtr->inputs->I_phA[7]     = ctrl_data.fcf_in.I_phA[7];
//	FOC_FCF_MPtr->inputs->I_phA[8]     = ctrl_data.fcf_in.I_phA[8];
//	FOC_FCF_MPtr->inputs->I_dq_RefA[0] = ctrl_data.fcf_in.I_dq_RefA[0];
//	FOC_FCF_MPtr->inputs->I_dq_RefA[1] = ctrl_data.fcf_in.I_dq_RefA[1];
//	FOC_FCF_MPtr->inputs->phi_elrad    = ctrl_data.fcf_in.phi_elrad;
//	FOC_FCF_MPtr->inputs->FOC_Mode     = ctrl_data.fcf_in.FOC_Mode;
//	FOC_FCF_MPtr->inputs->FOC_Enable_PWM   = ctrl_data.fcf_in.FOC_Enable;
	FOC_FCF_MPtr->inputs->bus_BSW_FCF = ctrl_data.bus_BSW_FCF;
	FOC_FCF_MPtr->inputs->bus_SCF     = ctrl_data.bus_SCF;
	FOC_FCF_MPtr->inputs->bus_SMF     = ctrl_data.bus_SMF;

	FOC_FCF_step(FOC_FCF_MPtr);

	// write simulink outputs to control data exchange structure
	ctrl_data.bus_FCF = FOC_FCF_MPtr->outputs->bus_FCF;

	Global_Data.rasv.halfBridge1DutyCycle = ctrl_data.bus_FCF.DutyCycles[0];
	Global_Data.rasv.halfBridge2DutyCycle = ctrl_data.bus_FCF.DutyCycles[1];
	Global_Data.rasv.halfBridge3DutyCycle = ctrl_data.bus_FCF.DutyCycles[2];
	Global_Data.rasv.halfBridge4DutyCycle = ctrl_data.bus_FCF.DutyCycles[3];
	Global_Data.rasv.halfBridge5DutyCycle = ctrl_data.bus_FCF.DutyCycles[4];
	Global_Data.rasv.halfBridge6DutyCycle = ctrl_data.bus_FCF.DutyCycles[5];
	Global_Data.rasv.halfBridge7DutyCycle = ctrl_data.bus_FCF.DutyCycles[6];
	Global_Data.rasv.halfBridge8DutyCycle = ctrl_data.bus_FCF.DutyCycles[7];
	Global_Data.rasv.halfBridge9DutyCycle = ctrl_data.bus_FCF.DutyCycles[8];

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state

    }

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);


	/* ~~~ Gate Driver Enable Control ~~~ */
	if(ctrl_data.bus_FCF.FOC_Enable_PWM)
		uz_inverter_status_hw_set_GateDriverEnable(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_GATES_UZ_INVERTER_STATUS_IP_0_BASEADDR, 1, 0);
	else
		uz_inverter_status_hw_set_GateDriverEnable(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_GATES_UZ_INVERTER_STATUS_IP_0_BASEADDR, 0, 0);


    /* ~~~~~~~~~~~~~~ MOTOR MODEL ~~~~~~~~~~~~~~~~~~~~~ */
    if(pmsm_model_reset)
      uz_pmsm_model9ph_dq_reset(pmsm);                              // use reset variable to reset integrators from Expressions

    uz_pmsm_model9ph_dq_set_inputs_general(pmsm,omega_mech,0.0f);   // set fixed speed, because load simulation is disabled by pmsm_config.simulate_mechanical_system
    //uz_pmsm_model9ph_dq_set_voltage(pmsm,in_voltages);              // set input voltage
    in_voltages = uz_pmsm_model9ph_dq_get_input_voltages(pmsm);		// read input voltages to PMSM model set by dq-trafo FPGA model
    out_general = uz_pmsm_model9ph_dq_get_outputs_general(pmsm);    // read out resulting general outputs
    out_currents = uz_pmsm_model9ph_dq_get_output_currents(pmsm);   // read out actual currents
    /* ~~~~~~~~~~~~~~ End of MOTOR MODEL ~~~~~~~~~~~~~~ */


	xcp_irq();
    JavaScope_update(&Global_Data);

    // @ToDo: increment timer in a fixed timed task by system trigger (e.g. general purpose interrupt) instead of calling in ISR_Control() function that is related to PWM frequency. --> can lead to wrong timing if PWM frequency is not an integer divisor of 1ms
    if(++Control_timer_1ms >= (0.001f * UZ_PWM_FREQUENCY))
    {
    	Control_timer_1ms = 0;
    	Control_FLAG_1ms = 1;

    	if(++Control_timer_10ms >= 10)
    	{
    		Control_timer_10ms = 0;
    		Control_FLAG_10ms = 1;

    		if(++Control_timer_100ms >= 10)
    		{
    			Control_timer_100ms = 0;
    			Control_FLAG_100ms = 1;
    		}
    	}
    }


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
