/*****************************************************************************/
/**
*
* @file uz_xwdttb.c
*
* This file contains the functions to initialize the TimeBase Watchdog Timer Device
* (WdtTb) driver and hardware device and a design example using the using interrupt
* mode (for the WDT interrupt).
*
* @note
*
* This library has been developed based in the Xilinx driver examples.
*
* MODIFICATION HISTORY:
*
* <pre>
* Ver   Who  Date     Changes
* ----- ---- -------- ---------------------------------------------------------
* 1.0   David Ken  03/11/21 First release
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "uz_xwdttb.h"

#include "../../uz/uz_HAL.h"

#ifdef ENABLE_WDTTB_INT


/************************** Variable Definitions *****************************/

#ifndef TESTAPP_GEN
XWdtTb WdtTbInstance;	/* Instance of Time Base WatchDog Timer */
XScuGic IntcInstance;	/* Instance of the Interrupt Controller */
#endif

//volatile int WdtExpired;
volatile u32 HandlerCalled;	/* flag is set when timeout interrupt occurs */

_Bool Wdttb_IsReady = false;

XScuGic_Config *TempConfig;


/*****************************************************************************/
/**
*
* This function initializes and tests the functioning of the System WatchDog Timer driver and
* sets the inital value to the counter. This is the total size for The Second Window (Open).
* The closed Window is not used (0 value for its counter).
* The rest of the optional functions: FC, SST and SIGNATURE are disabled.
*
*
* @param	CounterValue - Initial value for the counter in number of tics.
* 					Watchdog timeout is therefore CounterValue * Tcycle,
* 					and Tcycle = 10 ns with a 100MH processor.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
int WdtTbInit(u32 CounterValue) {
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
	XWdtTb_SetWindowCount(&WdtTbInstance, 0, CounterValue);

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
* This function STARTs the System WatchDog Timer to the initial value to the counter.
* Generates a good event if executed inside the Second Window, or OPEN Window.
*
* The WDT Start is accomplished by enabling the IP Core writing WEN bit =1.
* The And granting write access to the IP Registers.
*
* It also protects the WEN bit. It is not possible to Stop() the device.
*
* @note		None.
*
******************************************************************************/
void WdtTb_Start() {

	uz_assert(Wdttb_IsReady);

//	/* Stop the timer, disabling the WDTTB, writing 0 in bit WEN */
//	XWdtTb_Stop(&WdtTbInstance);


	/* Write a 1 to Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(&WdtTbInstance, 1);

	/*
	 * Set the AEN bit (to enable protection against accidental clearing)
	 * and to avoid disable (WEN = 0) ==>> XWdtTb_Stop() NOT POSSIBLE
	 * BUT when Second Window times out, and bad even occurs and RESET is produced ANYWAY (and IP CORE STOPS RUNNING)
	 */
	 XWdtTb_AlwaysEnable(&WdtTbInstance);

	 XWdtTb_EnableExtraProtection(&WdtTbInstance);

	/*
	 * Start the watchdog timer as a normal application would (WEN bit = 1)
	 */
	XWdtTb_Start(&WdtTbInstance);
//	WdtExpired = FALSE;

	/* After enabled, write enabled auto clears, so we have to write a 1 to Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(&WdtTbInstance, 1);
}


/**
*
* This function Restart the AXI IP watch dog timer: kick forward .
*
* @note		None.
*
******************************************************************************/
void WdtTb_Restart() {
	uz_assert(Wdttb_IsReady);
	XWdtTb_RestartWdt(&WdtTbInstance);
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
int WinWdtIntrExample(XScuGic *IntcInstancePtr)
{
	int Status;

	uz_assert(Wdttb_IsReady);

//	Status = WdtTbInit(0);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}



//#ifndef TESTAPP_GEN
//	XScuGic_Config *IntcConfig;
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
//	Status = XScuGic_CfgInitialize(&IntcInstance, IntcConfig,
//					IntcConfig->CpuBaseAddress);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}
//
//#endif /* TESTAPP_GEN */
//
//	/*
//	 * Connect the WdtTb to the interrupt subsystem so that interrupts
//	 * can occur
//	 */
//	Status = WdtTbSetupIntrSystem(IntcConfig, &IntcInstance);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}


//	WdtTb_Start();

	XWdtTb_Start(&WdtTbInstance);
	//	WdtExpired = FALSE;

	/* After enabled, write enabled auto clears, so we have to write a 1 to Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(&WdtTbInstance, 1);

	HandlerCalled = 0;

	/*
	 * Wait for the first occurrence of interrupt programmed point.
	 */
//	while (WdtExpired != TRUE);
	while ((HandlerCalled == 0)) ;


	/* Clear interrupt point */
	XWdtTb_IntrClear(&WdtTbInstance);
//	WdtExpired = FALSE;
	HandlerCalled = 0;

	/* Wait for the second occurrence of interrupt programmed point */
//	while (WdtExpired != TRUE);
	while ((HandlerCalled == 0)) ;

	/* Clear interrupt point */
	XWdtTb_IntrClear(&WdtTbInstance);
//	WdtExpired = FALSE;
	HandlerCalled = 0;

	/* Check for last event */
	if (XWdtTb_GetLastEvent(&WdtTbInstance) != XWDTTB_NO_BAD_EVENT) {
		/* Disable and disconnect the interrupt system */
		WdtTbDisableIntrSystem(IntcInstancePtr);

		/* Stop the timer */
		XWdtTb_Stop(&WdtTbInstance);
		return XST_FAILURE;
	}

//	/* Disable and disconnect the interrupt system */
//	WdtTbDisableIntrSystem(IntcInstancePtr);
//
	/* Stop the timer */
//	XWdtTb_Stop(&WdtTbInstance);

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
* @param	IntcConfig is a pointer to the instance of the XGIC
*		Configutarion.
* @param	IntcInstancePtr is a pointer to the instance of the Intc
*		driver.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE, otherwise.
*
* @note		None.
*
******************************************************************************/
//static int WdtTbSetupIntrSystem(INTC *IntcInstancePtr)
int WdtTbSetupIntrSystem(XScuGic_Config *IntcConfig, XScuGic *IntcInstancePtr)
{
	int Status;
	u8 Priority, Trigger;

	uz_assert(Wdttb_IsReady);

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
	//	DEBUG INFO
	//	xil_printf("WdtTbSetupIntrSystem: Wd Prio is %d, level is %d\r\n",Priority, Trigger);

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
			(Xil_ExceptionHandler)XScuGic_InterruptHandler, // (Xil_ExceptionHandler)INTC_HANDLER,
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
* The handler of the timing violation. The default behavior is to resume the execution,
* by restarting the WDT. The execution time of this function is also limited, as is has
* to restart the WDT inside the second window, otherwise a Reset from the IP core is
* activated, and the IP stops running
*
* @param	CallBackRef is a pointer to the callback reference.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void WdtTbIntrHandler(void *CallBackRef)
{

	uz_assert(Wdttb_IsReady);

	XWdtTb *WdtTbInstancePtr = (XWdtTb *)CallBackRef;

	//	DEBUG INFO
	// u32 reg;
	// reg = XScuGic_ReadReg(TempConfig->CpuBaseAddress, XSCUGIC_RUN_PRIOR_OFFSET);
//	xil_printf("WdtTbIntrHandler AND RESTART AND CLEAR: Running priority in WDT handler is %d\r\n",reg >> 3);

	/*
	 * Restart the watchdog timer as a normal application would.
	 * The WDT Retart is to continue the execution
	 * */
	XWdtTb_RestartWdt(WdtTbInstancePtr);

	/* Clear interrupt point. To allow a new INT to be triggered again (see documentation)*/
	XWdtTb_IntrClear(&WdtTbInstance);


	/* Increment the number of failures handled or received invocations.*/
	HandlerCalled++;

	/* Check for last event: After Restart inside the second Window it should be always a GOOD_EVENT.
	 * If it is not, Disable and Stop().
	 * */
	if (XWdtTb_GetLastEvent(&WdtTbInstance) != XWDTTB_NO_BAD_EVENT) {
		/* Disable and disconnect the interrupt system */
		WdtTbDisableIntrSystem(&IntcInstance);

		/* Stop the timer */
		XWdtTb_Stop(&WdtTbInstance);

	}
//	OR / AND TO STOP PS EXECUTION!!
//  Xil_Assert(__FILE__, __LINE__);


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
void WdtTbDisableIntrSystem(XScuGic *IntcInstancePtr)
{

	uz_assert(Wdttb_IsReady);

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

void WdtTb_Start() {}

void WdtTb_Restart() {}

int WdtTbInit(u32 CounterValue){}

int WinWdtIntrExample(INTC *IntcInstancePtr) {}

void WdtTbIntrHandler(void *CallBackRef);
//static int WdtTbSetupIntrSystem(INTC *IntcInstancePtr){}
int WdtTbSetupIntrSystem(XScuGic_Config *IntcConfig, XScuGic *IntcInstancePtr){}

void WdtTbDisableIntrSystem(XScuGic *IntcInstancePtr){}

#endif /* ENABLE_WDT_INT */
