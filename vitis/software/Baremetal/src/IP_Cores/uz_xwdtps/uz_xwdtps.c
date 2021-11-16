/*****************************************************************************/
/**
*
* @file uz_xwdtps.c
*
* This file contains a design example using the System Watchdog Timer Device
* (WdtPs) driver and hardware device using interrupt mode. This test
* assumes that the RESET OUTPUT OF WDT IS NOT CONNECTED to the processor and
* the IRQ output is connected to an interrupt controller attached to the
* processor.
*
* It also contains a XWdtPs_ResetRestart to restart the WDT and enabling Reset Output.
*
* Based on @file xwdtps_intr_example.c. Copyright (C) 2010 - 2021 Xilinx, Inc.  All rights reserved. SPDX-License-Identifier: MIT
*
*
* @note
*
* <pre>
*
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ------ -------- ---------------------------------------------
* 1.00a ecm/jz 01/15/10 First release
* 3.1	sg	   08/20/18 Updated interrupt example to fix interrupt ID
* 						conflict issue
* 4		DKen	09/30/2021 Detached Init function with TimeOut timer in ms.
* 						Added a Restart function to use the RESET OUTPUT.
*
* </pre>
*
******************************************************************************/


#include "uz_xwdtps.h"

#include "../../uz/uz_HAL.h"

#ifdef ENABLE_WDT_INT


_Bool Wdt_IsReady = false;

XScuGic_Config *TempConfig;

/*****************************************************************************/
/**
* Main function to call the Wdt interrupt example.
*
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
//int main(void)
//{
//	int Status;
//
//	xil_printf("WDT Interrupt Example Test\r\n");
//
//	/*
//	 * Call the interrupt example, specify the parameters generated in
//	 * xparameters.h
//	 */
//	Status = WdtPsIntrExample(&IntcInstance,
//				WDT_DEVICE_ID, WDT_IRPT_INTR);
//	if (Status != XST_SUCCESS) {
//		xil_printf("WDT Interrupt Example Test Failed\r\n");
//		return XST_FAILURE;
//	}
//
//	xil_printf("Successfully ran WDT Interrupt Example Test\r\n");
//	return XST_SUCCESS;
//}


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
int WdtPsInit(u32 Timeout) //&WdtInstance, WDT_DEVICE_ID,
{
	int Status;
//	u32 Timebase = 0;
//	u32 ExpiredTimeDelta = 0;
	u32 EffectiveAddress;	/* This can be the virtual address */
	XWdtPs_Config *ConfigPtr;

	u32 CounterValue;

	/*
	 * Initialize the Wdt driver.
	 */
	ConfigPtr = XWdtPs_LookupConfig(WDT_DEVICE_ID);

	/*
	 * This is where the virtual address would be used, this example
	 * uses physical address.
	 */
	EffectiveAddress = ConfigPtr->BaseAddress;

	Status = XWdtPs_CfgInitialize(&WdtInstance, ConfigPtr, EffectiveAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XWdtPs_SelfTest(&WdtInstance);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Set the initial Divider ratio at the SMALLEST VALUE .
	 */
	XWdtPs_SetControlValue(&WdtInstance, (u8) XWDTPS_CLK_PRESCALE,
			(u8) XWDTPS_CCR_PSCALE_0008);

	if (Timeout == 0U) {

		/*
		 * Set the initial counter restart to the SMALLEST VALUE (0).
		 */
		XWdtPs_SetControlValue(&WdtInstance, (u8) XWDTPS_COUNTER_RESET, (u8) 0);

	} else {

		/* Set the Watchdog counter reset value */

		/* Watchdog counter reset value for Expire time of 100Sec,
		 * i.e., XPFW_WDT_EXPIRE_TIME
		 */
		CounterValue = ((Timeout) * (XPFW_WDT_CLK_PER_MSEC)) >> XPFW_WDT_CRV_SHIFT;

		/* Set the Watchdog counter reset value */
		XWdtPs_SetControlValue(&WdtInstance, XWDTPS_COUNTER_RESET,
				CounterValue);
	}

	Wdt_IsReady = true;

	return XST_SUCCESS;
}


u32 WdtPsIntrPolled(u32 ExpiredTimeDelta) {

//	xil_printf("WdtPsIntrPolled: start");

	uz_assert(Wdt_IsReady);

	/*
	 * Disable the RESET output.
	 */
	XWdtPs_DisableOutput(&WdtInstance, XWDTPS_RESET_SIGNAL);
	/*
	 * Disable the IRQ output.
	 */
	XWdtPs_DisableOutput(&WdtInstance, (u8) XWDTPS_IRQ_SIGNAL);

	/*
	 * Start the Wdt device.
	 */
	XWdtPs_Start(&WdtInstance);
	/*
	 * Restart the timer.
	 */
	XWdtPs_RestartWdt(&WdtInstance);
	/*
	 * Determine how long it takes for the Watchdog Timer to expire
	 * for later processing.
	 * If the reset output of the device is connected to the processor,
	 * the following code will cause a reset.
	 */
	while (1) {
		if (!(XWdtPs_IsWdtExpired(&WdtInstance))) {
			ExpiredTimeDelta++;
		} else {
			break;
		}
	}

	xil_printf("WdtPsIntrPolled with ExpiredTimeDelta: %u", ExpiredTimeDelta);
	/*
	 * Stop the timer to set up the device in interrupt mode.
	 */
	XWdtPs_Stop(&WdtInstance);
	return ExpiredTimeDelta;
}

/*****************************************************************************/
/**
*
* This function resets the System WatchDog Timer to the inital value to the counter.
* And Enables the IRQ OutPut of the System WatchDog Driver to be
* handled by the PMU processor
*
*
* @note		None.
*
******************************************************************************/
void XWdtPs_Restart()
{
	uz_assert(Wdt_IsReady);

//	XWdtPs_DisableOutput(&WdtInstance, XWDTPS_RESET_SIGNAL);
	XWdtPs_DisableOutput(&WdtInstance, (u8) XWDTPS_IRQ_SIGNAL);
	XWdtPs_Stop(&WdtInstance);
	/* Start the Watchdog timer */
	XWdtPs_Start(&WdtInstance);
	XWdtPs_RestartWdt(&WdtInstance);
	/* Enable reset output */
//	XWdtPs_EnableOutput(&WdtInstance, XWDTPS_RESET_SIGNAL);
	XWdtPs_EnableOutput(&WdtInstance, (u8) XWDTPS_IRQ_SIGNAL);
}

/*****************************************************************************/
/**
*
* This function tests the functioning of the System WatchDog Timer driver in the
* Interrupt mode.
*
* After one expiration of the timeout interval, an interrupt is generated and
* the WDT state bit is set to one in the status register.
*
* This function assumes that the reset output of the Wdt device is not
* connected to the reset of the processor, otherwise, the timer will cause the
* processor to reset when it expires.
*
* @param	IntcInstancePtr is a pointer to the instance of the XScuGic
*		driver. It has to be already Initialized.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
int WdtPsIntrExample(XScuGic_Config *IntcConfig, XScuGic *IntcInstancePtr)
//	Status = WdtPsIntrExample(&IntcInstance, WDT_DEVICE_ID, WDT_IRPT_INTR);
{
	int Status;
	u32 Timebase = 0;
	u32 ExpiredTimeDelta = 0;

	xil_printf("WdtPsIntrExample: start\r\n");

	/*
	 * Initialize the Wdt driver and Perform a self-test to ensure that the hardware was built correctly.
	 * Set the initial counter restart to the smallest value (0).
	 */
	if (!Wdt_IsReady) {
		Status = WdtPsInit(0U);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}
	}

	uz_assert(Wdt_IsReady);

//	xil_printf("WdtPsIntrExample: uz_assert");

	/*
	 * Without INT, establish the expiration time by polling the driver.
	 */
	ExpiredTimeDelta = WdtPsIntrPolled(ExpiredTimeDelta);

//	xil_printf("WdtPsIntrExample: WdtPsIntrPolled with ExpiredTimeDelta: %u", ExpiredTimeDelta);


	/*
	 * Connect to the interrupt subsystem so that interrupts can occur and Enable the IRQ output.
	 */
	Status = WdtSetupIntrSystem(IntcConfig, IntcInstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Start the Wdt device.
	 */
	HandlerCalled = 0;
	XWdtPs_Start(&WdtInstance);
	XWdtPs_RestartWdt(&WdtInstance);

	/*
	 * Verify that the Watchdog Timer does  timeout when not restarted
	 * all the time, wait more than the amount of time it took for it
	 * to expire in the previous test.
	 */
	while (1) {
		/*
		 * If the handler is called, the test passed
		 */
		if ((HandlerCalled != 0)) {
			break;
		}

		/*
		 * If more time has gone past than it took for it to expire
		 * when not restarted in the previous test, then stop since the
		 * handler was never called failing the test.
		 */

		Timebase++;
		if (Timebase > ExpiredTimeDelta + ExpiredTimeDelta) {
			/*
			 * Disable and disconnect the interrupt system.
			 */

			WdtDisableIntrSystem(IntcInstancePtr);
			return XST_FAILURE;
		}

		/*
		 * If the Watchdog Timer expired and handler was not called,
		 * then the test failed.
		 */
		if ((XWdtPs_IsWdtExpired(&WdtInstance)) &&
		    (HandlerCalled == 0)) {
			/*
			 * Disable and disconnect the interrupt system.
			 */
				WdtDisableIntrSystem(IntcInstancePtr);
			return XST_FAILURE;
		}
	}

	/*
	 * Restart the device to allow the next test to run normally.
	 */
	XWdtPs_RestartWdt(&WdtInstance);

	HandlerCalled = 0;

	/*
	 * Verify that the Watchdog Timer does not timeout when restarted
	 * all the time, wait more than the amount of time it took for it
	 * to expire in the previous test.
	 */
	while (1) {
		/*
		 * Reset the WDT each pass through the loop
		 */
		XWdtPs_RestartWdt(&WdtInstance);

		/*
		 * If more time has gone past than it took for it to expire
		 * when not restarted in the previous test, then stop as the
		 * restarting worked.
		 */
		Timebase++;
		if (Timebase > ExpiredTimeDelta + ExpiredTimeDelta) {
			break;
		}

		/*
		 * If the Watchdog Timer expired and/or handler called, then the
		 * test failed.
		 */
		if ((XWdtPs_IsWdtExpired(&WdtInstance)) ||
		    (HandlerCalled != 0)) {
			/*
			 * Disable and disconnect the interrupt system.
			 */
			WdtDisableIntrSystem(IntcInstancePtr);
			return XST_FAILURE;
		}
	}

	/*
	 * Disable and disconnect the interrupt system.
	 */
	WdtDisableIntrSystem(IntcInstancePtr);

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function sets up the interrupt system such that interrupts can occur
* for the device. This function is application specific since the actual
* system may or may not have an interrupt controller. The device could be
* directly connected to a processor without an interrupt controller. The
* user should modify this function to fit the application.
*
* @param	IntcInstancePtr is a pointer to the instance of ScuGic driver ALREADY INITIALIZED
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
int WdtSetupIntrSystem(XScuGic_Config *IntcConfig, XScuGic *IntcInstancePtr)
{
	int Status;
//	XScuGic_Config *IntcConfig;
	u8 Priority, Trigger;

	uz_assert(Wdt_IsReady);

	Xil_ExceptionInit();
//
//	/*
//	 * Initialize the interrupt controller driver so that it is ready to
//	 * use.
//	 */
//	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
//	if (NULL == IntcConfig) {
//		return XST_FAILURE;
//	}

	TempConfig = IntcConfig;
//
//	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
//					IntcConfig->CpuBaseAddress);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}

	XScuGic_GetPriorityTriggerType(IntcInstancePtr, WDT_IRPT_INTR,
	                                            &Priority, &Trigger);

	Priority = 0x0;
	Trigger = 3;
	XScuGic_SetPriorityTriggerType(IntcInstancePtr, WDT_IRPT_INTR,
			Priority, Trigger);

	XScuGic_GetPriorityTriggerType(IntcInstancePtr, WDT_IRPT_INTR,
		                                            &Priority, &Trigger);
	xil_printf("WdtSetupIntrSystem: Wd Prio is %d, level is %d\r\n",Priority, Trigger);

//	/*
//	 * Connect the interrupt controller interrupt handler to the hardware
//	 * interrupt handling logic in the processor.
//	 */
//	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
//				(Xil_ExceptionHandler)XScuGic_InterruptHandler,
//				IntcInstancePtr);

	/*
	 * Connect the device driver handler that will be called when an
	 * interrupt for the device occurs, the handler defined above performs
	 * the specific interrupt processing for the device.
	 */
	Status = XScuGic_Connect(IntcInstancePtr, WDT_IRPT_INTR,
				(Xil_ExceptionHandler)WdtIntrHandler,
				(void *)&WdtInstance);
	if (Status != XST_SUCCESS) {
		return Status;
	}

	/*
	 * Enable the interrupt for the device.
	 */
	XScuGic_Enable(IntcInstancePtr, WDT_IRPT_INTR);

	/*
	 * Enable interrupts in the Processor.
	 */
	Xil_ExceptionEnable();

	/*
	 * Enable the IRQ output.
	 */
	XWdtPs_EnableOutput(&WdtInstance, (u8) XWDTPS_IRQ_SIGNAL);

	xil_printf("RPU: WdtSetupIntrSystem: Done\r\n");

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function is the Interrupt handler for the WDT Interrupt of the
* Wdt device. It is called on the expiration of the timer counter in
* interrupt context.
*
* @param	CallBackRef is a pointer to the callback function.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void WdtIntrHandler(void *CallBackRef)
{
	u32 reg;
	reg = XScuGic_ReadReg(TempConfig->CpuBaseAddress, XSCUGIC_RUN_PRIOR_OFFSET);
	xil_printf("WdtIntrHandler: Running priority in WDT handler is %d\r\n",reg >> 3);

	/*
	 * WDT timed out and interrupt occurred, let main test loop know.
	 */
	HandlerCalled = HANDLER_CALLED;

	/*
	 * Code for handling the SYSTEM HANG goes here.
	 */
	//  Xil_Assert(__FILE__, __LINE__);
	//  OR
	//	XWdtPs_RestartWdt(&WdtInstance);
}

/*****************************************************************************/
/**
*
* This function disables the interrupts that occur for the device.
*
* @param	IntcInstancePtr is the pointer to the instance of XScuGic
*		driver ALREADY INITIALIZED.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void WdtDisableIntrSystem(XScuGic *IntcInstancePtr)
{

	uz_assert(Wdt_IsReady);

	/*
	 * Disconnect and disable the interrupt for the Wdt.
	 */
	XScuGic_Disconnect(IntcInstancePtr, WDT_IRPT_INTR);

}
#else /* ENABLE_WDT_INT */

u32 WdtPsIntrPolled(u32 ExpiredTimeDelta) { }

void XWdtPs_Restart() {}

int WdtPsInit(XWdtPs * WdtInstancePtr, u16 WdtDeviceId, u32 Timeout){ }

int WdtPsIntrExample(XScuGic_Config *IntcConfig, XScuGic *IntcInstancePtr){ }

void WdtIntrHandler(void *CallBackRef){ }

int WdtSetupIntrSystem(XScuGic_Config *IntcConfig, XScuGic *IntcInstancePtr){ }

void WdtDisableIntrSystem(XScuGic *IntcInstancePtr){ }

#endif /* ENABLE_WDT_INT */
