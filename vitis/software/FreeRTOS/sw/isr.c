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

#include <math.h>

#define IPI_HEADER			0x1E0000 /* 1E - Target Module ID */
#define IPI_R5toA53_MSG_LEN		8U
#define IPI_A53toR5_MSG_LEN		3U

extern ARM_to_Oszi_Data_shared_struct OsziData;
extern Oszi_to_ARM_Data_shared_struct ControlData;

extern A53_Data Global_Data_A53;

// Oszi Data Queue parameters
QueueHandle_t OsziData_queue;
int OSZI_QUEUE_FULL = 0;
const int OSZI_QUEUE_SIZE_ELEMENTS = 1000; 		// could be optimized, empirical minimum is ~400, otherwise data might be lost
const int OSZI_QUEUE_RECEIVE_TICKS_WAIT = 100;  // 1 tick = 100ms, wait (almost) indefinitely

Xint16  i_LifeCheck_Transfer_ipc, cnt_javascope=0;

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
	u32 IpiBuf[IPI_R5toA53_MSG_LEN] = {0U};
	u32 RespBuf[IPI_A53toR5_MSG_LEN] = {0,0,XST_SUCCESS};
	u32 RegVal;
	BaseType_t xHigherPriorityTaskWoken;

	// Check if the IPI is from the expected source i-> here we expect from R5_0
	RegVal = XIpiPsu_GetInterruptStatus(&INTCInst_IPI);
	if((RegVal & (u32)XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK) == 0U) {//Check if received source is equal to expected source (R5_0)
		xil_printf("APU: Received IPI from invalid source, ISR:%x\r\n", RegVal);
		Global_Data_A53.ew.wrongInterruptByIPI = XTRUE;
	} else {
		//SW: Now read the IPI payload buffer from the source - if necessary -> but we don't need it!
		RegVal = (u32)XIpiPsu_ReadMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK, IpiBuf, IPI_R5toA53_MSG_LEN, XIPIPSU_BUF_TYPE_MSG);

		RespBuf[0] = (u32)ControlData.id;
		RespBuf[1] = (u32)ControlData.value;
		RespBuf[2] = (u32)ControlData.digInputs;

		//SW: Write message for acknowledge of the interrupt to RPU
		status = XIpiPsu_WriteMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK, RespBuf, IPI_A53toR5_MSG_LEN, XIPIPSU_BUF_TYPE_RESP);

		// Valid IPI. Clear the appropriate bit in the respective ISR
		XIpiPsu_ClearInterruptStatus(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

		i_LifeCheck_Transfer_ipc++;
		if(i_LifeCheck_Transfer_ipc > 25000){
			i_LifeCheck_Transfer_ipc =0;
		}
	}

		// IpiBuf contains float values from R5, use memcpy to avoid unwanted cast to other type
		memcpy(&OsziData.val[0], &IpiBuf[0], sizeof(float));
		memcpy(&OsziData.val[1], &IpiBuf[1], sizeof(float));
		memcpy(&OsziData.val[2], &IpiBuf[2], sizeof(float));
		memcpy(&OsziData.val[3], &IpiBuf[3], sizeof(float));
		memcpy(&OsziData.val[4], &IpiBuf[4], sizeof(float));

		// these variables are sent every time, but only evaluated every 5th time
		OsziData.slowDataContent 		= IpiBuf[5];
		OsziData.slowDataID 			= (Xuint16)IpiBuf[6];
		OsziData.status_BareToRTOS 		= IpiBuf[7];


		// append OsziData to queue
		if ( errQUEUE_FULL == xQueueSendToBackFromISR(OsziData_queue, &OsziData, &xHigherPriorityTaskWoken)  )
		{
			// count how many packages are lost due to a full queue
			// if JavaScope is not connected, this keep counting up
			OSZI_QUEUE_FULL++;
		}

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

	/* Initialize RPU GIC and Connect IPI interrupt*/
	Status = Apu_GicInit(&INTCipc, XPAR_XIPIPSU_0_INT_ID,(Xil_ExceptionHandler)Transfer_ipc_Intr_Handler, &INTCInst_IPI);
	//toDO: check "XPAR_XIPIPSU_0_INT_ID" or "XPAR_XTTCPS_0_INTR"
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

	// create queue with queue_elements elements of of type ARM_to_Oszi_Data_shared_struct
	OsziData_queue = xQueueCreate( OSZI_QUEUE_SIZE_ELEMENTS, sizeof(ARM_to_Oszi_Data_shared_struct) );
		if (OsziData_queue == NULL){
			xil_printf("APU: Error: Queue creation failed\r\n");
			return XST_FAILURE;
		}

	//xil_printf("APU: Queue successfully created\r\n");

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

	XIpiPsu_InterruptEnable(IntcInst_IPI_Ptr, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

	xil_printf("APU: APU_IpiInit: Done\r\n");
	return XST_SUCCESS;
}
