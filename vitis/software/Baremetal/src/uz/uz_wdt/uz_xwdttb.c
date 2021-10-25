/******************************************************************************
* Copyright (C) 2016 - 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xwdttb_winwdt_intr_example.c
*
* This file contains a design example using the TimeBase Watchdog Timer Device
* (WdtTb) driver and hardware device using interrupt mode (for the WDT
* interrupt).
*
* @note
*
* This example assumes that the reset output of the WdtTb device is not
* connected to the reset of the processor. This example will not return
* if the interrupts are not working.
*
* MODIFICATION HISTORY:
*
* <pre>
* Ver   Who  Date     Changes
* ----- ---- -------- ---------------------------------------------------------
* 4.0   sha  02/04/16 First release
* 5.0	sne  03/26/20 Updated example to support versal platform.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "uz_xwdttb.h"

#include "../uz_HAL.h"

#ifdef ENABLE_WDTTB_INT


_Bool Wdttb_IsReady = false;

XScuGic_Config *TempConfig;


///*****************************************************************************/
///**
//* Main function to call the WdtTb interrupt example.
//*
//*
//* @return
//*		- XST_SUCCESS if successful
//*		- XST_FAILURE, otherwise.
//*
//* @note		None.
//*
//******************************************************************************/
//#ifndef TESTAPP_GEN
//int main(void)
//{
//	int Status;
//
//	/*
//	 * Call the WdtTb interrupt example, specify the parameters generated in
//	 * xparameters.h
//	 */
//	Status = WinWdtIntrExample(&IntcInstance,
//				&WdtTbInstance,
//				WDTTB_DEVICE_ID,
//				WDTTB_IRPT_INTR);
//	if (Status != XST_SUCCESS) {
//		xil_printf("Window WDT interrupt example failed.\n\r");
//		return XST_FAILURE;
//	}
//
//	xil_printf("Successfully ran Window WDT interrupt example.\n\r");
//	return XST_SUCCESS;
//}
//#endif


/*****************************************************************************/
/**
*
* This function initializes and tests the functioning of the System WatchDog Timer driver and
* sets the inital value to the counter. If the value of Timeout param is 0U it is set to the
* SMALLEST VALUE (about 350 useconds).
*
* @param	Timeout - Watchdog timeout in ms.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
int WdtTbInit(u32 Timeout) {
	int Status;
	XWdtTb_Config *Config;

	/*
	 * Initialize the WDTTB driver so that it's ready to use look up
	 * configuration in the config table, then initialize it.
	 */
	Config = XWdtTb_LookupConfig(WDTTB_DEVICE_ID);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	/*
	 * Initialize the watchdog timer and timebase driver so that
	 * it is ready to use.
	 */
	Status = XWdtTb_CfgInitialize(&WdtTbInstance, Config,
					  Config->BaseAddr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	if(!WdtTbInstance.Config.IsPl) {
		/*Enable Window Watchdog Feature in WWDT */
		XWdtTb_ConfigureWDTMode(&WdtTbInstance, XWT_WWDT);
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly
	 */
	Status = XWdtTb_SelfTest(&WdtTbInstance);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(&WdtTbInstance, 1);

	/* Configure first window = 0 (NOT USED THE CLOSED WINDOW) and second window */
	XWdtTb_SetWindowCount(&WdtTbInstance, 0, Timeout);

	/* Set interrupt position */
	XWdtTb_SetByteCount(&WdtTbInstance, WIN_WDT_SBC_COUNT);
	XWdtTb_SetByteSegment(&WdtTbInstance, WIN_WDT_BSS_COUNT);

	/* Disable Secondary Sequence Timer (SST) */
	XWdtTb_DisableSst(&WdtTbInstance);

	/* Disable Program Sequence Monitor (PSM) */
	XWdtTb_DisablePsm(&WdtTbInstance);

	/* Disable Fail Counter */
	XWdtTb_DisableFailCounter(&WdtTbInstance);

	Wdttb_IsReady = true;

	return XST_SUCCESS;
}

/**
*
* This function RESTARTs the System WatchDog Timer to the initial value to the counter.
* Generates a good event if executed inside the Second Window, or OPEN Window.
*
*
* @note		None.
*
******************************************************************************/
void WdtTb_Restart() {

	/* Stop the timer, disabling the WDTTB, writing 0 in bit WEN */
	XWdtTb_Stop(&WdtTbInstance);

	/*
	 * Start the watchdog timer as a normal application would
	 */
	XWdtTb_Start(&WdtTbInstance);
	WdtExpired = FALSE;

	/* After enabled, write enabled auto clears, so we have to write a 1 to Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(&WdtTbInstance, 1);
}


/*****************************************************************************/
/**
*
* This function tests the functioning of the Window Watchdog Timer in the
* interrupt mode.
*
* This function waits for interrupt programmed point in second window. If the
* interrupt has occurred, interrupt handler sets a flag and restarts the timer.
* This function then clears the interrupt, flag and waits for second interrupt
* to occur and continue waiting for second interrupt as mentioned above.
*
* This function assumes that the reset output of the Window Watchdog Timer
* is not connected to the reset of the processor. The function allows the
* Window Watchdog Timer to timeout such that a reset will occur if it is
* connected.
*
* @param	IntcInstancePtr is a pointer to the instance of the INTC
*		driver.
* @param	WdtTbInstancePtr is a pointer to the instance of WdtTb driver.
* @param	WdtTbDeviceId is the Device ID of the WdtTb Device and is
*		typically XPAR_<WDTTB_instance>_DEVICE_ID value from
*		xparameters.h.
* @param	WdtTbIntrId is the Interrupt Id of the WatchDog and is
*		typically XPAR_<INTC_instance>_<WDTTB_instance>_WDT_
*		INTERRUPT_VEC_ID value from xparameters.h.
*
* @return
*		- XST_SUCCESS if interrupt example run successfully.
*		- XST_FAILURE, if reset has occurred.
*
* @note		None.
*
******************************************************************************/
int WinWdtIntrExample(INTC *IntcInstancePtr,
			XWdtTb *WdtTbInstancePtr)
{
	int Status;

//	Status = WdtTbInit(0);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}



#ifndef TESTAPP_GEN
	XScuGic_Config *IntcConfig;

	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	if (NULL == IntcConfig) {
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(&IntcInstance, IntcConfig,
					IntcConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

#endif /* TESTAPP_GEN */

	/*
	 * Connect the WdtTb to the interrupt subsystem so that interrupts
	 * can occur
	 */
	Status = WdtTbSetupIntrSystem(IntcConfig, &IntcInstance);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	WdtTb_Restart();


	/*
	 * Wait for the first occurrence of interrupt programmed point.
	 */
	while (WdtExpired != TRUE);


	/* Clear interrupt point */
	XWdtTb_IntrClear(WdtTbInstancePtr);
	WdtExpired = FALSE;

	/* Wait for the second occurrence of interrupt programmed point */
	while (WdtExpired != TRUE);

	/* Clear interrupt point */
	XWdtTb_IntrClear(WdtTbInstancePtr);
	WdtExpired = FALSE;

	/* Check for last event */
	if (XWdtTb_GetLastEvent(WdtTbInstancePtr) != XWDTTB_NO_BAD_EVENT) {
		/* Disable and disconnect the interrupt system */
		WdtTbDisableIntrSystem(IntcInstancePtr);

		/* Stop the timer */
		XWdtTb_Stop(WdtTbInstancePtr);
		return XST_FAILURE;
	}

	/* Disable and disconnect the interrupt system */
	WdtTbDisableIntrSystem(IntcInstancePtr);

	/* Stop the timer */
	XWdtTb_Stop(WdtTbInstancePtr);

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function setups the interrupt system such that WDT interrupt can occur
* for the WdtTb. This function is application specific since the actual
* system may or may not have an interrupt controller. The WdtTb device could be
* directly connected to a processor without an interrupt controller. The
* user should modify this function to fit the application.
*
* @param	IntcInstancePtr is a pointer to the instance of the Intc
*		driver.
* @param	WdtTbInstancePtr is a pointer to the instance of WdtTb driver.
* @param	WdtTbIntrId is the Interrupt Id of the WDT interrupt and is
*		typically
*		XPAR_<INTC_instance>_<WDTTB_instance>_WDT_INTERRUPT_VEC_ID
*		value from xparameters.h.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE, otherwise.
*
* @note		None.
*
******************************************************************************/
//static int WdtTbSetupIntrSystem(INTC *IntcInstancePtr)
static int WdtTbSetupIntrSystem(XScuGic_Config *IntcConfig, INTC *IntcInstancePtr)
{
	int Status;
	u8 Priority, Trigger;

#ifdef XPAR_INTC_0_DEVICE_ID

#ifndef TESTAPP_GEN
	/*
	 * Initialize the interrupt controller driver so that
	 * it's ready to use. Specify the device ID that is generated in
	 * xparameters.h
	 */
	Status = XIntc_Initialize(IntcInstancePtr, INTC_DEVICE_ID);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* TESTAPP_GEN */

	/*
	 * Connect a device driver handler that will be called when the WDT
	 * interrupt for the device occurs, the device driver handler performs
	 * the specific interrupt processing for the device
	 */
	Status = XIntc_Connect(IntcInstancePtr, WdtTbIntrId,
			(XInterruptHandler)WdtTbIntrHandler,
			(void *)WdtTbInstancePtr);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

#ifndef TESTAPP_GEN
	/*
	 * Start the interrupt controller such that interrupts are enabled for
	 * all devices that cause interrupts
	 */
	Status = XIntc_Start(IntcInstancePtr, XIN_REAL_MODE);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* TESTAPP_GEN */

	/* Enable the WDT interrupt of the WdtTb Device */
	XIntc_Enable(IntcInstancePtr, WDTTB_IRPT_INTR);
#else

//	XScuGic_SetPriorityTriggerType(IntcInstancePtr, WDTTB_IRPT_INTR,
//					0xA0, 0x3);

	TempConfig = IntcConfig;


	IntcInstance.Config = IntcInstancePtr->Config;
	IntcInstance.IsReady = IntcInstancePtr->IsReady;
	IntcInstance.UnhandledInterrupts = IntcInstancePtr->UnhandledInterrupts;

	XScuGic_GetPriorityTriggerType(IntcInstancePtr, WDTTB_IRPT_INTR,
		                                            &Priority, &Trigger);

	Priority = 0x0;
	Trigger = 3;
	XScuGic_SetPriorityTriggerType(IntcInstancePtr, WDTTB_IRPT_INTR,
			Priority, Trigger);

	XScuGic_GetPriorityTriggerType(IntcInstancePtr, WDTTB_IRPT_INTR,
													&Priority, &Trigger);
	xil_printf("WdtTbSetupIntrSystem: Wd Prio is %d, level is %d\r\n",Priority, Trigger);

	/*
	 * Connect the interrupt handler that will be called when an
	 * interrupt occurs for the device.
	 */
	Status = XScuGic_Connect(IntcInstancePtr, WDTTB_IRPT_INTR,
				(Xil_ExceptionHandler)WdtTbIntrHandler,
				&WdtTbInstance);
	if (Status != XST_SUCCESS) {
		return Status;
	}

	/* Enable the interrupt for the Timer device */
	XScuGic_Enable(IntcInstancePtr, WDTTB_IRPT_INTR);
#endif /* XPAR_INTC_0_DEVICE_ID */

#ifndef TESTAPP_GEN
	/* Initialize the exception table */
	Xil_ExceptionInit();

	/*
	 * Register the interrupt controller handler with the exception table
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler)INTC_HANDLER,
			IntcInstancePtr);

	/* Enable non-critical exceptions */
	Xil_ExceptionEnable();

#endif /* TESTAPP_GEN */

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function is the Interrupt handler for the WDT Interrupt of the
* WdtTb device. It is called when reached to the interrupt programmed point
* and is called from an interrupt context.
*
* @param	CallBackRef is a pointer to the callback reference.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void WdtTbIntrHandler(void *CallBackRef)
{
	XWdtTb *WdtTbInstancePtr = (XWdtTb *)CallBackRef;

	u32 reg;
	reg = XScuGic_ReadReg(TempConfig->CpuBaseAddress, XSCUGIC_RUN_PRIOR_OFFSET);
	xil_printf("WdtIntrHandler: Running priority in WDT handler is %d\r\n",reg >> 3);

	/*
	 * WDT timed out and interrupt occurred, let main test loop know.
	 */
	/* Set the flag indicating that the WDT has expired */
	WdtExpired = TRUE;

	/*
	 * Code for handling the SYSTEM HANG goes here.
	 */
//  Xil_Assert(__FILE__, __LINE__);
//	OR
	/* Restart the watchdog timer as a normal application would */
//	XWdtTb_RestartWdt(WdtTbInstancePtr);
}

/*****************************************************************************/
/**
*
* This function disables the interrupts that occur for the WdtTb.
*
* @param	IntcInstancePtr is the pointer to the instance of INTC driver.
* @param	WdtTbIntrId is the WDT Interrupt Id and is typically
*		XPAR_<INTC_instance>_<WDTTB_instance>_WDT_INTERRUPT_VEC_ID
*		value from xparameters.h.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void WdtTbDisableIntrSystem(INTC *IntcInstancePtr)
{

	/* Disconnect and disable the interrupt for the WdtTb */
#ifdef XPAR_INTC_0_DEVICE_ID
	XIntc_Disconnect(IntcInstancePtr, WDTTB_IRPT_INTR);
#else
	/* Disconnect the interrupt */
	XScuGic_Disable(IntcInstancePtr, WDTTB_IRPT_INTR);
	XScuGic_Disconnect(IntcInstancePtr, WDTTB_IRPT_INTR);

#endif
}

#else /* ENABLE_WDTTB_INT */

void WdtTb_Restart() {}

int WdtTbInit(u32 Timeout){}

int WinWdtIntrExample(INTC *IntcInstancePtr,
			XWdtTb *WdtTbInstancePtr) {}

static void WdtTbIntrHandler(void *CallBackRef);
//static int WdtTbSetupIntrSystem(INTC *IntcInstancePtr){}
static int WdtTbSetupIntrSystem(XScuGic_Config *IntcConfig, INTC *IntcInstancePtr){}

static void WdtTbDisableIntrSystem(INTC *IntcInstancePtr){}

#endif /* ENABLE_WDT_INT */
