/******************************************************************************
* Copyright 2021 Sebastian Wendel, Eyke Liegmann
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

#include "xparameters.h"
#include "netif/xadapter.h"

#if LWIP_DHCP==1
#include "lwip/dhcp.h"
#endif

#include "../include/isr.h"
#include "../defines.h"
#include "APU_RPU_shared.h"


#define IPI_HEADER			0x1E0000 /* 1E - Target Module ID */

Oszi_to_ARM_Data_shared_struct ControlData;

extern A53_Data Global_Data_A53;
extern int js_connection_established;

// Javascope Queue parameters
QueueHandle_t js_queue;
int js_queue_full = 0;

u32 js_mem_address[JS_NUM_BUFFERS] = {0xFFFF0000, 0xFFFF8000};

int i_LifeCheck_Transfer_ipc;

//Initialize the Interrupt structure
XScuGic INTCipc;	//Interrupt for IPC
XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!
XScuGic_Config *IntcConfig;

/**
 * Apu_IpiHandler() - Interrupt handler for IPI
 *
 * @IpiInstPtr		Pointer to the IPI instance
 */
// Standard isr interrupt from BareMetal -> frequency depends on the Software-interrupt from BareMetal
void Transfer_ipc_Intr_Handler(void *data)
{
	int status;
	u32 RespBuf[IPI_A53toR5_MSG_LEN] = {0,0,XST_SUCCESS};
	u32 msgBuf[IPI_A53toR5_MSG_LEN] = {JSCMD_WRITE, 0, 0};
	BaseType_t xHigherPriorityTaskWoken;

	// if javascope connection is established
	if(js_connection_established!=0)
	{
		// Define javascope next buffer to send its address to RPU
		u8 next_js_buff_index = js_buff_index + 1;
		if(next_js_buff_index == JS_NUM_BUFFERS){
			next_js_buff_index = 0;
		}

		// Write message for acknowledge of the interrupt to RPU and command it to write new data
		msgBuf[1] = js_mem_address[next_js_buff_index];
		Send_Command_to_RPU(msgBuf, IPI_A53toR5_MSG_LEN);
	}

	RespBuf[0] = (u32)ControlData.id;
	RespBuf[1] = (u32)ControlData.value;
	RespBuf[2] = (u32)ControlData.digInputs;

	// Write message for acknowledge of the interrupt to RPU
	status = XIpiPsu_WriteMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK, RespBuf, IPI_A53toR5_MSG_LEN, XIPIPSU_BUF_TYPE_RESP);

	// Valid IPI. Clear the appropriate bit in the respective ISR
	XIpiPsu_ClearInterruptStatus(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

	i_LifeCheck_Transfer_ipc++;

	if(i_LifeCheck_Transfer_ipc > 25000){
		i_LifeCheck_Transfer_ipc = 0;
	}
	rxIpi = 1;
	// force context switch after ISR finishes -> switching to ethernet task
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE THE INTERRUPT HAndler (from main)
//----------------------------------------------------
int Initialize_InterruptHandler(){

	int Status = XST_SUCCESS;

	// Interrupt controller configuration
	IntcConfig = XScuGic_LookupConfig(XPAR_SCUGIC_0_DEVICE_ID);
		if(IntcConfig == NULL) {
			xil_printf("APU: Error: GIC Config failed\r\n");
			return XST_FAILURE;
		}

	// Interrupt controller initialization
	Status = XScuGic_CfgInitialize(&INTCipc, IntcConfig, IntcConfig->CpuBaseAddress);
		if(Status != XST_SUCCESS) {
			xil_printf("APU: Error: GIC initialization failed\r\n");
			return XST_FAILURE;
		}

	return Status;
}


//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR(){

	int Status = 0;

	// Initialize RPU GIC and Connect IPI interrupt
	Status = Apu_GicInit(&INTCipc, XPAR_XIPIPSU_0_INT_ID,(Xil_ExceptionHandler)Transfer_ipc_Intr_Handler, &INTCInst_IPI);
	if(Status != XST_SUCCESS) {
		xil_printf("APU: Error: GIC initialization failed\r\n");
		return XST_FAILURE;
	}

	// Initialize interrupt controller for the IPI -> Initialize RPU IPI
	Status = Apu_IpiInit(&INTCInst_IPI, INTERRUPT_ID_IPI);
	if(Status != XST_SUCCESS) {
		xil_printf("APU: Error: IPI initialization failed\r\n");
		return XST_FAILURE;
	}


	return Status;
}

//==============================================================================================================================================================
/**
 * Apu_GicInit() - This function initializes APU GIC and connects
 * 					interrupts with the associated handlers
 * @IntcInstPtr		Pointer to the GIC instance
 * @IntId			Interrupt ID to be connected and enabled
 * @Handler			Associated handler for the Interrupt ID
 * @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
 */
u32 Apu_GicInit(XScuGic *IntcInstPtr, u32 IntId, Xil_ExceptionHandler Handler, void *PeriphInstPtr)
{
	u32 Status = XST_SUCCESS;

	// Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,IntcInstPtr);
	Xil_ExceptionEnable();										//Enable interrupts in the ARM

	// Make the connection between the IntId of the interrupt source and the
	// associated handler that is to run when the interrupt is recognized.
	Status = XScuGic_Connect(IntcInstPtr, IntId, Handler, PeriphInstPtr);

	XScuGic_Enable(IntcInstPtr, IntId);

	//xil_printf("APU: Apu_GicInit: Done\r\n");
	return Status;
}


//==============================================================================================================================================================
/**
 * Apu_IpiInit() - This function initializes APU IPI and enables IPI interrupts
 *
 * @IpiInstPtr		Pointer to the IPI instance
 */
u32 Apu_IpiInit(XIpiPsu *IntcInst_IPI_Ptr,u16 DeviceId)
{
	XIpiPsu_Config *IntcConfig_IPI;
	int status;

	// Interrupt controller configuration
	IntcConfig_IPI = XIpiPsu_LookupConfig(DeviceId);
		if (IntcConfig_IPI == NULL) {
			xil_printf("APU: Error: Ipi Init failed\r\n");
			return XST_FAILURE;
		}

	// Interrupt controller initialization
	status = XIpiPsu_CfgInitialize(IntcInst_IPI_Ptr, IntcConfig_IPI, IntcConfig_IPI->BaseAddress);
		if (status != XST_SUCCESS) {
			xil_printf("APU: Error: IPI Config failed\r\n");
			return XST_FAILURE;
		}

	// Enable reception of IPIs from R5
	XIpiPsu_InterruptEnable(IntcInst_IPI_Ptr, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

	xil_printf("APU: APU_IpiInit: Done\r\n");
	return XST_SUCCESS;
}


void Send_Command_to_RPU(u32 *msgBuf, u8 msgLength){
	u32 status;

	// Write message with command and parameters
	status = XIpiPsu_WriteMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK, msgBuf, msgLength, XIPIPSU_BUF_TYPE_MSG);
	if(status != (u32)XST_SUCCESS) {
		xil_printf("APU: IPI Write Message failed\r\n");
	}
	// Trigger interrupt
	status = XIpiPsu_TriggerIpi(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);
	if(status != (u32)XST_SUCCESS) {
		xil_printf("APU: IPI Trigger failed\r\n");
	}
}
