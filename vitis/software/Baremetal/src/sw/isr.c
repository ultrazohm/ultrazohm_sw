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
#include "../IP_Cores/uz_DutyCycleMeas/uz_DutyCycleMeas_hw.h"
#include "../IP_Cores/uz_inverter_status/uz_inverter_status_hw.h"

#include "../IP_Cores/uz_DutyCycleMeas/uz_DutyCycleMeas_hwAddresses.h"
#include "../IP_Cores/uz_inverter_status/uz_inverter_status_hwAddresses.h"

//#include "control.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

typedef struct {
	struct {
		real32_T U_DC;                       /* '<Root>/U_DC [V]' */
		real32_T I_phA[6];                   /* '<Root>/I_ph [A]' */
		real32_T I_dq_RefA[2];               /* '<Root>/I_dq_Ref [A]' */
		real32_T phi_elrad;                  /* '<Root>/phi_el [rad]' */
		real32_T FOC_Mode;                   /* '<Root>/FOC_Mode' */
		real32_T FOC_Enable;                 /* '<Root>/FOC_Enable' */
		real32_T w_el_Ref_IfStarter;         /* '<Root>/w_el_Ref_IfStarter' */
		real32_T IfStarter_Active;           /* '<Root>/IfStarter_Active' */
	} fcf_in;
	struct {
		real32_T DutyCycles01[6];            /* '<Root>/DutyCycles [0..1]' */
		real32_T I_dq_ActA[4];               /* '<Root>/I_dq_Act [A]' */
		real32_T ModInd[2];                  /* '<Root>/ModInd' */
		real32_T w_elrads;                   /* '<Root>/w_el [rad//s]' */
		real_T FOC_Error;                    /* '<Root>/FOC_Error' */
	} fcf_out;
} ctrl_data_t;


ctrl_data_t ctrl_data;

float DutyCycleMeas_Value;
uint32_t PWMin_HighTicks;
uint32_t PWMin_PeriodTicks;
uint32_t DutyCycleIPcoreTimestamp;
//float PWM_DutyCycle[3];
float PWM_DutyCycle_0;
float PWM_DutyCycle_1;
float PWM_DutyCycle_2;
uint32_t inverter_status_RDY;
uint32_t inverter_status_FLT;
uint8_t inverter_GateDriverEnable;


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

    // read position from resolver IP Core
    Global_Data.av.theta_elec = uz_resolverIP_readElectricalPosition(Global_Data.objects.resolver_left);

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state

    	// write measurement data to control model interface struct
//    	ctrl_data.fcf_in.


    	// write inputs to fast control function of simulink model
    	FOC_FCF_MPtr->inputs->U_DC = 123;
    	FOC_FCF_MPtr->inputs->FOC_Enable = 1;

    	FOC_FCF_step(FOC_FCF_MPtr);

    	ctrl_data.fcf_out.DutyCycles01[0] = FOC_FCF_MPtr->outputs->DutyCycles01[0];
    	ctrl_data.fcf_out.DutyCycles01[1] = FOC_FCF_MPtr->outputs->DutyCycles01[1];
    	ctrl_data.fcf_out.DutyCycles01[2] = FOC_FCF_MPtr->outputs->DutyCycles01[2];
    	ctrl_data.fcf_out.DutyCycles01[3] = FOC_FCF_MPtr->outputs->DutyCycles01[3];
    	ctrl_data.fcf_out.DutyCycles01[4] = FOC_FCF_MPtr->outputs->DutyCycles01[4];
    	ctrl_data.fcf_out.DutyCycles01[5] = FOC_FCF_MPtr->outputs->DutyCycles01[5];


    	Global_Data.rasv.halfBridge1DutyCycle = ctrl_data.fcf_out.DutyCycles01[0];
    	Global_Data.rasv.halfBridge2DutyCycle = ctrl_data.fcf_out.DutyCycles01[1];
		Global_Data.rasv.halfBridge3DutyCycle = ctrl_data.fcf_out.DutyCycles01[2];
//    	Global_Data.rasv.halfBridge1DutyCycle = PWM_DutyCycle_0;//[0];
//    	Global_Data.rasv.halfBridge2DutyCycle = PWM_DutyCycle_1;//[1];
//		Global_Data.rasv.halfBridge3DutyCycle = PWM_DutyCycle_2;//[2];
    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

//    PWMin_HighTicks = (uint32_t*) (XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_UZ_DUTYCYCLEMEAS_IP_0_BASEADDR + AXI_hightime_Data_uz_dutycyclemeas_ip);
//    PWMin_PeriodTicks = (uint32_t*) (XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_UZ_DUTYCYCLEMEAS_IP_0_BASEADDR + AXI_period_Data_uz_dutycyclemeas_ip);
    PWMin_HighTicks   = uz_DutyCycleMeas_hw_get_PWMhightimeTicks(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_0_BASEADDR);
    PWMin_PeriodTicks = uz_DutyCycleMeas_hw_get_PWMperiodTicks(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_0_BASEADDR);

    DutyCycleMeas_Value = uz_DutyCycleMeas_hw_get_DutyCycle(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_0_BASEADDR);
    DutyCycleIPcoreTimestamp = (uint32_t*) (XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_0_BASEADDR + IPCore_Timestamp_uz_dutycyclemeas_ip);

    inverter_status_FLT = uz_inverter_status_hw_get_FLT(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_GATES_UZ_INVERTER_STATUS_IP_0_BASEADDR);
    inverter_status_RDY = uz_inverter_status_hw_get_RDY(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_GATES_UZ_INVERTER_STATUS_IP_0_BASEADDR);
    uz_inverter_status_hw_set_GateDriverEnable(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_GATES_UZ_INVERTER_STATUS_IP_0_BASEADDR, inverter_GateDriverEnable, 0);

	xcp_irq();
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
