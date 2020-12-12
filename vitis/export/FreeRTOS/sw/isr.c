/******************************************************************************
*
* isr.c
*
* Copyright (C) 2018 Institute ELSYS, TH Nürnberg, All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
*
******************************************************************************/

//#include <stdio.h>
#include "xparameters.h"
#include "netif/xadapter.h"
//#include "xil_printf.h"
//#include "xipipsu.c"

#if LWIP_DHCP==1
#include "lwip/dhcp.h"
#endif

#include "../include/isr.h"
#include "../defines.h"

//#include "../main.h"
#include <math.h>

#define IPI_HEADER			0x1E0000 /* 1E - Target Module ID */
#define IPI_R5toA53_MSG_LEN		8U //27U
#define IPI_A53toR5_MSG_LEN		3U

extern ARM_to_Oszi_Data_shared_struct OsziData; //Data from A9_0 to A9_1 (from BareMetal to FreeRTOS) in order to provide data for the GUI (Ethernet-Plot)
extern Oszi_to_ARM_Data_shared_struct ControlData; //Data from A9_1 to A9_0 (from FreeRTOS to BareMetal) in order to receive control data from the GUI
//Oszi_to_ARM_Data_shared_struct ControlDataShadow;
extern A53_Data Global_Data_A53;
extern XGpio Gpio_OUT;											/* GPIO Device driver instance for the real GPIOs */

Xint16  i_LifeCheck_Transfer_ipc, NextPacketArrived=0,cnt_javascope=0,Test_javascope=0;

SemaphoreHandle_t xSemaphore_IPC = NULL;
//Initialize the Interrupt structure
XScuGic INTCipc;	//Interrupt for IPC
XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!
XScuGic_Config *IntcConfig;

u32 RegVal;

/**
 * Apu_IpiHandler() - Interrupt handler for IPI
 *
 * @IpiInstPtr		Pointer to the IPI instance
 */
// Standard isr interrupt from BareMetal -> frequency depends on the Software-interrupt from BareMetal
void Transfer_ipc_Intr_Handler(void *data)
{
	int status;
	//static BaseType_t xHigherPriorityTaskWoken;

	u32 IpiBuf[IPI_R5toA53_MSG_LEN] = {0U};
	//u32 RespBuf[3] = {IPI_HEADER, XST_SUCCESS};
	u32 RespBuf[IPI_A53toR5_MSG_LEN] = {0,0,XST_SUCCESS};

	// Check if the IPI is from the expected source i-> here we expect from R5_0
	RegVal = XIpiPsu_GetInterruptStatus(&INTCInst_IPI); //OLD: RegVal = Xil_In32(0xFF310010U);
	if((RegVal & (u32)XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK) == 0U) {//Check if received source is equal to expected source (R5_0)
		xil_printf("APU: Received IPI from invalid source, ISR:%x\r\n", RegVal);
		Global_Data_A53.ew.wrongInterruptByIPI = XTRUE;
	} else {
		//SW: Now read the IPI payload buffer from the source - if necessary -> but we don't need it!
		RegVal = (u32)XIpiPsu_ReadMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK, IpiBuf, IPI_R5toA53_MSG_LEN, XIPIPSU_BUF_TYPE_MSG);
		//if(status != (u32)XST_SUCCESS) {
		//	xil_printf("APU: IPI payload buffer read failed\r\n");
		//}

		RespBuf[0] = (u32)ControlData.id;
		RespBuf[1] = (u32)ControlData.value;
		RespBuf[2] = (u32)ControlData.digInputs;

		//SW: Write message for acknowledge of the interrupt to RPU
		status = XIpiPsu_WriteMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK, RespBuf, IPI_A53toR5_MSG_LEN, XIPIPSU_BUF_TYPE_RESP);

		// Valid IPI. Clear the appropriate bit in the respective ISR
		XIpiPsu_ClearInterruptStatus(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK) //Xil_Out32(0xFF310010U, (RegVal & (u32)XPAR_XIPIPS_TARGET_PSU_PMU_0_CH1_MASK));

		i_LifeCheck_Transfer_ipc++;
		if(i_LifeCheck_Transfer_ipc > 25000){
			i_LifeCheck_Transfer_ipc =0;
		}
	}


	if (cnt_javascope < 5)
	{
		OsziData.val[cnt_javascope] 	= (Xfloat32)IpiBuf[0];
		OsziData.val[5+cnt_javascope] 	= (Xfloat32)IpiBuf[1];
		OsziData.val[10+cnt_javascope] 	= (Xfloat32)IpiBuf[2];
		OsziData.val[15+cnt_javascope] 	= (Xfloat32)IpiBuf[3];
	}

	cnt_javascope++;

	if (cnt_javascope >= 5)
	{

		OsziData.slowDataContent = IpiBuf[4];
		OsziData.slowDataID = (Xuint16)IpiBuf[5];
		OsziData.status_BareToRTOS = IpiBuf[6];
		OsziData.schiebereg_ausgaenge = (Xuint16)IpiBuf[7];

//	xHigherPriorityTaskWoken = pdFALSE;
    // Unblock the task by releasing the semaphore.
//    xSemaphoreGiveFromISR( xSemaphore_IPC, &xHigherPriorityTaskWoken );
//	OsziData.SampledDataReadDone = 1;	// notify BareMetal that new data was read
//	OsziData.SampledDataWriteDone = 0;	// Reset the WriteDone-flag

	//Allow the Ethernet connection to transfer the next TCP packet, because the new valid data are available!
	NextPacketArrived =1;
	// EL: NextPacketArrived synchronizes this ISR with the ethernet task
	// probably better add a fifo queue here: https://www.freertos.org/Embedded-RTOS-Queues.html


	cnt_javascope = 0;
	}

	//IPCCtoMFlagAcknowledge(IPC_FLAG3);
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
/*
	// Attempt to create a semaphore.
	xSemaphore_IPC = xSemaphoreCreateBinary();

    if(xSemaphore_IPC == NULL ){
        // There was insufficient FreeRTOS heap available for the semaphore to be created successfully.
    }else{
        // The semaphore can now be used. Its handle is stored in the
        //xSemahore variable.  Calling xSemaphoreTake() on the semaphore here
        //will fail until the semaphore has first been given.
    }
    xSemaphoreGive(xSemaphore_IPC);
 */
/*
	//Initialize the shared RAM with zeros
	ControlData.digInputs =0;
	ControlData.id =0;
	ControlData.value =0;
*/
	// Initialize interrupt controller
	//Status = Initialize_Interrupts(INTERRUPT_ID_SCUG);
	//if(Status != XST_SUCCESS) return XST_FAILURE;

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
//SW: The following section is out-sourced to the main(), because otherwise the Ethernet didn't work anymore!
/*
	XScuGic_Config *IntcConfig;
	u32 Status = XST_FAILURE;

	// Interrupt controller configuration
	IntcConfig = XScuGic_LookupConfig(XPAR_SCUGIC_0_DEVICE_ID);
		if(IntcConfig == NULL) {
			xil_printf("APU: Error: GIC Config failed\r\n");
			return XST_FAILURE;
		}

	// Interrupt controller initialization
	Status = XScuGic_CfgInitialize(IntcInstPtr, IntcConfig, IntcConfig->CpuBaseAddress);
		if(Status != XST_SUCCESS) {
			xil_printf("APU: Error: GIC initialization failed\r\n");
			return XST_FAILURE;
		}
*/
	// Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,IntcInstPtr);
	Xil_ExceptionEnable();										//Enable interrupts in the ARM

	// Make the connection between the IntId of the interrupt source and the
	// associated handler that is to run when the interrupt is recognized.
	(void)XScuGic_Connect(IntcInstPtr, IntId, Handler, PeriphInstPtr);

	XScuGic_Enable(IntcInstPtr, IntId);

	// Enable interrupts in the processor
	//Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
/*
	// Enable interrupts in the processor
	//Xil_ExceptionEnable();	//Enable interrupts in the ARM
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
*/
	//xil_printf("APU: Apu_GicInit: Done\r\n");
	return XST_SUCCESS;
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


		/* Enable IPI from PMU to RPU_0 */
	//	Xil_Out32(0xFF310018U, 0xF0000U);
		//Explanation: 0xFF310018U = XPAR_PSU_IPI_1_BASE_ADDRESS + XIPIPSU_IER_OFFSET
		//Explanation: 0xF0000U =  XPAR_PSU_IPI_3_BIT_MASK +XPAR_PSU_IPI_4_BIT_MASK + XPAR_PSU_IPI_5_BIT_MASK + XPAR_PSU_IPI_6_BIT_MASK
		//Explanation: 0xF0000U =  0x00010000U + 0x00020000U + 0x00040000U + 0x00080000U = Enable all IPI to the PMU
//		XIpiPsu_InterruptEnable(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK);
		XIpiPsu_InterruptEnable(IntcInst_IPI_Ptr, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);
//		XIpiPsu_InterruptEnable(IntcInst_IPI_Ptr, 0x00000301U);
//		Status = XPfw_IpiTrigger(IPI_PMU_0_IER_RPU_0_MASK);
//		XPAR_XIPIPS_TARGET_PSU_PMU_0_CH0_MASK

	// Enable GPIO interrupts interrupt
	//XGpio_InterruptEnable(GpioInstancePtr, 1);
	//XGpio_InterruptGlobalEnable(GpioInstancePtr);

	// Enable GPIO and timer interrupts in the controller
//	XScuGic_Enable(&INTCInst_IPI, INTC_IPC_Shared_INTERRUPT_ID);

	xil_printf("APU: APU_IpiInit: Done\r\n");
	return XST_SUCCESS;
}
