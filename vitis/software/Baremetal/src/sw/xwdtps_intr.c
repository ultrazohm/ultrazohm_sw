///******************************************************************************
//* Copyright (C) 2010 - 2021 Xilinx, Inc.  All rights reserved.
//* SPDX-License-Identifier: MIT
//******************************************************************************/
//
///*****************************************************************************/
///**
//*
//* @file xwdtps_intr_example.c
//*
//* This file contains a design example using the System Watchdog Timer Device
//* (WdtPs) driver and hardware device using interrupt mode. This test
//* assumes that the RESET OUTPUT OF WDT IS NOT CONNECTED to the processor and
//* the IRQ output is connected to an interrupt controller attached to the
//* processor
//*
//*
//* @note
//*
//* <pre>
//*
//* MODIFICATION HISTORY:
//*
//* Ver   Who    Date     Changes
//* ----- ------ -------- ---------------------------------------------
//* 1.00a ecm/jz 01/15/10 First release
//* 3.1	sg	   08/20/18 Updated interrupt example to fix interrupt ID
//* 						conflict issue
//*
//* </pre>
//*
//******************************************************************************/
//
///***************************** Include Files *********************************/
//
//#include "xparameters.h"
//#include "xwdtps.h"
//#include "xscugic.h"
//#include "xil_exception.h"
//#include "xil_printf.h"
//
///************************** Constant Definitions *****************************/
//
///*
// * The following constants map to the XPAR parameters created in the
// * xparameters.h file. They are only defined here such that a user can easily
// * change all the needed parameters in one place.
// */
//#ifdef XPAR_PS7_WDT_0_DEVICE_ID
//#define WDT_IRPT_INTR		XPS_WDT_INT_ID
//#endif
//
//#ifdef XPAR_PSU_CSU_WDT_DEVICE_ID
//	#define WDT_IRPT_INTR		XPS_CSU_WDT_INT_ID
//#else
//	#ifdef XPAR_PSU_WDT_0_DEVICE_ID
//		#define WDT_IRPT_INTR		XPS_LPD_SWDT_INT_ID
//	#else
//		#ifdef XPAR_PSU_WDT_1_DEVICE_ID
//			#define WDT_IRPT_INTR		XPS_FPD_SWDT_INT_ID
//		#endif
//	#endif
//#endif
//
//#define WDT_DEVICE_ID		XPAR_XWDTPS_0_DEVICE_ID
//#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
//
///* Assign default values for WDT params assuming default config */
//#define WDT_CRV_SHIFT 12U
//#define WDT_PRESCALER 4096U
//#define WDT_CLK_PER_SEC ((XPAR_PSU_WDT_1_WDT_CLK_FREQ_HZ) / (WDT_PRESCALER))
//
///**************************** Type Definitions *******************************/
//#define HANDLER_CALLED  0xFFFFFFFF
//
///***************** Macros (Inline Functions) Definitions *********************/
//
///************************** Function Prototypes ******************************/
//
//u32 WdtPsIntrPolled(u32 ExpiredTimeDelta, XWdtPs* WdtInstancePtr) ;
//
//int WdtPsIntrInit(XWdtPs * WdtInstancePtr, u16 WdtDeviceId, u32 Timeout);
//
//int WdtPsIntrExample(XScuGic *IntcInstancePtr, XWdtPs * WdtInstancePtr,
//		       u16 WdtDeviceId, u16 WdtIntrId);
//
//static void WdtIntrHandler(void *CallBackRef);
//
//static int WdtSetupIntrSystem(XScuGic *IntcInstancePtr,
//				  XWdtPs * WdtInstancePtr, u16 WdtIntrId);
//
//static void WdtDisableIntrSystem(XScuGic *IntcInstancePtr, u16 WdtIntrId);
//
///************************** Variable Definitions *****************************/
//
//XWdtPs WdtInstance;		/* Instance of WatchDog Timer */
//XScuGic IntcInstance;		/* Instance of the Interrupt Controller */
//
//volatile u32 HandlerCalled;	/* flag is set when timeout interrupt occurs */


#include "xwdtps_intr.h"

#ifdef ENABLE_WDT_INT

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
* This function initializes and tests the functioning of the System WatchDog Timer driver in the
* Interrupt mode.
*
* @param	WdtInstancePtr is a pointer to the instance of XWdtPs driver.
* @param	WdtDeviceId is the Device ID of the XWdtPs device.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
int WdtPsIntrInit(u32 Timeout) //&WdtInstance, WDT_DEVICE_ID,
{
	int Status;
//	u32 Timebase = 0;
//	u32 ExpiredTimeDelta = 0;
	u32 EffectiveAddress;	/* This can be the virtual address */
	XWdtPs_Config *ConfigPtr;


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

//	/*
//	 * Perform a self-test to ensure that the hardware was built correctly.
//	 */
//	Status = XWdtPs_SelfTest(&WdtInstance);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}

//	if (Timeout == 0U) {

		/*
		 * Set the initial counter restart to the smallest value (0).
		 */
		XWdtPs_SetControlValue(&WdtInstance, (u8) XWDTPS_COUNTER_RESET, (u8) 0);
		/*
		 * Set the initial Divider ratio at the smallest value.
		 */
		XWdtPs_SetControlValue(&WdtInstance, (u8) XWDTPS_CLK_PRESCALE,
				(u8) XWDTPS_CCR_PSCALE_0008);
//	} else {
//
//		/* Set the Watchdog counter reset value */
//		XWdtPs_SetControlValue(&WdtInstance, XWDTPS_COUNTER_RESET,
//				(Timeout*WDT_CLK_PER_SEC) >> WDT_CRV_SHIFT);
//
//		/* Setting the divider value */
//		XWdtPs_SetControlValue(&WdtInstance, XWDTPS_CLK_PRESCALE,
//				XWDTPS_CCR_PSCALE_4096);
//	}

	return XST_SUCCESS;
}

u32 WdtPsIntrPolled(u32 ExpiredTimeDelta) {

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

/*
	 * Stop the timer to set up the device in interrupt mode.
	 */
void XWdtPs_StopWdt() {
	/*
	 * Start the Wdt device.
	 */
	XWdtPs_Stop(&WdtInstance);

//	/*
//	 * Disable the RESET output.
//	 */
//	XWdtPs_DisableOutput(&WdtInstance, XWDTPS_RESET_SIGNAL);
//	/*
//	 * Disable the IRQ output.
//	 */
//	XWdtPs_DisableOutput(&WdtInstance, (u8) XWDTPS_IRQ_SIGNAL);
}

void XWdtPs_Restart() {
	/*
	 * RE Start the Wdt device.
	 */
	XWdtPs_RestartWdt(&WdtInstance);
}

void XWdtPs_Start_RestartWdt() {
	/*
	 * Start the Wdt device.
	 */
	HandlerCalled = 0;
	XWdtPs_Start(&WdtInstance);
	XWdtPs_RestartWdt(&WdtInstance);
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
*		driver.
* @param	WdtInstancePtr is a pointer to the instance of XWdtPs driver.
* @param	WdtDeviceId is the Device ID of the XWdtPs device.
* @param	WdtIntrId is the Interrupt Id of the XWdtPs device.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
int WdtPsIntrExample(XScuGic *IntcInstancePtr)
//	Status = WdtPsIntrExample(&IntcInstance, WDT_DEVICE_ID, WDT_IRPT_INTR);
{
	int Status;
	u32 Timebase = 0;
	u32 ExpiredTimeDelta = 0;
//	u32 EffectiveAddress;	/* This can be the virtual address */
//	XWdtPs_Config *ConfigPtr;


//	/*
//	 * Initialize the Wdt driver.
//	 */
//	ConfigPtr = XWdtPs_LookupConfig(WdtDeviceId);
//
//	/*
//	 * This is where the virtual address would be used, this example
//	 * uses physical address.
//	 */
//	EffectiveAddress = ConfigPtr->BaseAddress;
//
//	Status = XWdtPs_CfgInitialize(WdtInstancePtr, ConfigPtr,
//				       EffectiveAddress);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}




	/*
	 * Initialize the Wdt driver and Perform a self-test to ensure that the hardware was built correctly.
	 * Set the initial counter restart to the smallest value (0).
	 */
//	Status = WdtPsIntrInit(0U);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}

	/*
	 * Without INT, establish the expiration time by polling the driver.
	 */
	ExpiredTimeDelta = WdtPsIntrPolled(ExpiredTimeDelta);

	xil_printf("WdtPsIntrExample: WdtPsIntrPolled with ExpiredTimeDelta: %u", ExpiredTimeDelta);


	/*
	 * Connect to the interrupt subsystem so that interrupts can occur and Enable the IRQ output.
	 */
	Status = WdtSetupIntrSystem(IntcInstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Start the Wdt device.
	 */
	XWdtPs_Start_RestartWdt();
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
int WdtSetupIntrSystem(XScuGic *IntcInstancePtr)
{
	int Status;
//	XScuGic_Config *IntcConfig;
	u8 Priority, Trigger;

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
//
//	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
//					IntcConfig->CpuBaseAddress);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}

	XScuGic_GetPriorityTriggerType(IntcInstancePtr, WDT_IRPT_INTR,
	                                            &Priority, &Trigger);
	Trigger = 3;
	XScuGic_SetPriorityTriggerType(IntcInstancePtr, WDT_IRPT_INTR,
			0x0, Trigger);

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
	/*
	 * WDT timed out and interrupt occurred, let main test loop know.
	 */
	xil_printf("\r\nHANDLER_CALLED WdtIntrHandler: HANDLER_CALLED HANDLER_CALLED\r\n");

	HandlerCalled = HANDLER_CALLED;

	XWdtPs_RestartWdt(&WdtInstance);
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

	/*
	 * Disconnect and disable the interrupt for the Wdt.
	 */
	XScuGic_Disconnect(IntcInstancePtr, WDT_IRPT_INTR);

}
#else /* ENABLE_WDT_INT */

u32 WdtPsIntrPolled(u32 ExpiredTimeDelta) { }

void XWdtPs_StopWdt() {}

void XWdtPs_Restart() {}

void XWdtPs_Start_RestartWdt() {}

int WdtPsIntrInit(XWdtPs * WdtInstancePtr, u16 WdtDeviceId, u32 Timeout){ }

int WdtPsIntrExample(XScuGic *IntcInstancePtr){ }

void WdtIntrHandler(void *CallBackRef){ }

int WdtSetupIntrSystem(XScuGic *IntcInstancePtr){ }

void WdtDisableIntrSystem(XScuGic *IntcInstancePtr){ }

#endif /* ENABLE_WDT_INT */
