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
#include "../../uz/uz_global_configuration.h"
#include "uz_xwdttb.h"
#include "../../uz/uz_HAL.h"

#if (UZ_WDTTB_MAX_INSTANCES > 0U && UZ_WDTTB_MAX_INSTANCES <= XPAR_XWDTTB_NUM_INSTANCES)

/************************** Variable Definitions *****************************/

static size_t instance_counter = 0U;
static XWdtTb instances[UZ_WDTTB_MAX_INSTANCES] = {0};


/*****************************************************************************/
/**
*
* This function initializes and tests the functioning of the System WatchDog Timer driver and
* sets the inital value to the counter. This is the total size for The Second Window (Open).
* The closed Window is not used (0 value for its counter).
* The rest of the optional functions: FC, SST and SIGNATURE are disabled.
*
* @param	WdtTbInstancePtr - NOT NULL Pointer to the struct that represents the WDTTB driver.
* @param	CounterValue - Initial value for the counter in number of tics.
* 					Watchdog timeout is therefore CounterValue * Tcycle,
* 					and Tcycle = 10 ns with a 100MH processor.
* @param	WdtTbDeviceId is the Device ID of the WdtTb Device and is
*		typically XPAR_<WDTTB_instance>_DEVICE_ID value from
*		xparameters.h.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
static int WdtTbInit(XWdtTb *WdtTbInstancePtr, u32 CounterValue, u16 WdtTbDeviceId) {
	int Status;
	XWdtTb_Config *Config;

	/*
	 * Initialize the WDTTB driver so that it's ready to use look up
	 * configuration in the config table, then initialize it.
	 */
	Config = XWdtTb_LookupConfig(WdtTbDeviceId); // WDTTB_DEVICE_ID by default
	if (NULL == Config) {
		return XST_FAILURE;
	}

	/*
	 * Initialize the watchdog timer and timebase driver so that
	 * it is ready to use.
	 */
	Status = XWdtTb_CfgInitialize(WdtTbInstancePtr, Config,
					  Config->BaseAddr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	if(!WdtTbInstancePtr->Config.IsPl) {
		/*Enable Window Watchdog Feature in WWDT */
		XWdtTb_ConfigureWDTMode(WdtTbInstancePtr, XWT_WWDT);
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly
	 */
	Status = XWdtTb_SelfTest(WdtTbInstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(WdtTbInstancePtr, 1);

	/* Configure first window = 0 (NOT USED THE CLOSED WINDOW) and second window */
	XWdtTb_SetWindowCount(WdtTbInstancePtr, 0, CounterValue);

	/* Set interrupt position */
	XWdtTb_SetByteCount(WdtTbInstancePtr, WIN_WDT_SBC_COUNT);
	XWdtTb_SetByteSegment(WdtTbInstancePtr, WIN_WDT_BSS_COUNT);

	/* Disable Secondary Sequence Timer (SST) */
	XWdtTb_DisableSst(WdtTbInstancePtr);

	/* Disable Program Sequence Monitor (PSM) */
	XWdtTb_DisablePsm(WdtTbInstancePtr);

	/* Disable Fail Counter */
	XWdtTb_DisableFailCounter(WdtTbInstancePtr);

	return XST_SUCCESS;
}

static XWdtTb *uz_WdtTb_allocation(u32 CounterValue, u16 WdtTbDeviceId)
{
    uz_assert(instance_counter < UZ_WDTTB_MAX_INSTANCES);

    /*
	 * Call the WDT init to initialize and set timer to the given timeout.
	 * Both
	 */
	int Status = WdtTbInit(&instances[instance_counter], CounterValue, WdtTbDeviceId); // XPFW_WDT_EXPIRE_TIME for WDT PS

	if (Status != XST_SUCCESS) {
		//DEBUG
		//xil_printf("WDT initialization failed\r\n");
		return NULL;
	}

    XWdtTb *self = &instances[instance_counter];
    uz_assert(self != NULL);
#ifndef TEST
// The real initialization and readyness is done by xilinx driver.
// Not done if we are mocking the driver under TEST.
    uz_assert(self->IsReady == XIL_COMPONENT_IS_READY);
#endif
    instance_counter++;
    return (self);
}

XWdtTb *uz_WdtTb_init()
{
    XWdtTb *self = uz_WdtTb_allocation(WIN_WDT_SW_COUNT, WDTTB_DEVICE_ID);
    return (self);
}

/**
*
* This function initializes and tests the functioning of the System WatchDog Timer driver and
* sets the inital value to the counter. This is the total size for The Second Window (Open).
* The closed Window is not used (0 value for its counter).
* The rest of the optional functions: FC, SST and SIGNATURE are disabled.
*
* @param	CounterValue - Initial value for the counter in number of tics.
* 					Watchdog timeout is therefore CounterValue * Tcycle,
* 					and Tcycle = 10 ns with a 100MH processor.
* @param	WdtTbDeviceId is the Device ID of the WdtTb Device and is
*		typically XPAR_<WDTTB_instance>_DEVICE_ID value from
*		xparameters.h.
*
* @return	XWdtTb pointer to the initialized WDTTB driver.
*
* @note		None.
*
******************************************************************************/
XWdtTb *uz_WdtTb_init_device(u32 CounterValue, u16 WdtTbDeviceId)
{
    XWdtTb *self = uz_WdtTb_allocation(CounterValue, WdtTbDeviceId);
    return (self);
}

volatile u32 HandlerCalled;	/* flag is set when timeout interrupt occurs */

// Used for testing, to access INT priority, and check preemtion
//XScuGic_Config *TempConfig;


/**
*
* This function STARTs the System WatchDog Timer to the initial value to the counter.
* Generates a good event if executed inside the Second Window, or OPEN Window.
*
* NO: It also protects the WEN bit. It is not possible to Stop() the device.
*
* The WDT Start is accomplished by enabling the IP Core writing WEN bit =1.
* The And granting write access to the IP Registers.
*
* @param	WdtTbInstancePtr - NOT NULL Pointer to the struct that represents
*							the WDTTB driver. Initialized and ready
*
* @note		None.
*
******************************************************************************/
void WdtTb_Start(XWdtTb *WdtTbInstancePtr) {

	/* Verify arguments. */
	uz_assert(WdtTbInstancePtr != NULL);
	uz_assert(WdtTbInstancePtr->IsReady == XIL_COMPONENT_IS_READY);

//	/* Stop the timer, disabling the WDTTB, writing 0 in bit WEN */
//	XWdtTb_Stop(&WdtTbInstancePtr);


	/* Write a 1 to Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(WdtTbInstancePtr, 1);

	// /*
	//  * Set the AEN bit (to enable protection against accidental clearing)
	//  * and to avoid disable (WEN = 0) ==>> XWdtTb_Stop() NOT POSSIBLE
	//  * BUT when Second Window times out, and bad even occurs and RESET is produced ANYWAY (and IP CORE STOPS RUNNING)
	//  */
	//  XWdtTb_AlwaysEnable(WdtTbInstancePtr);

	//  XWdtTb_EnableExtraProtection(WdtTbInstancePtr);

	/*
	 * Start the watchdog timer as a normal application would (WEN bit = 1)
	 */
	XWdtTb_Start(WdtTbInstancePtr);
//	WdtExpired = FALSE;

	/* After enabled, write enabled auto clears, so we have to write a 1 to Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(WdtTbInstancePtr, 1);
}


/**
*
* This function Restart the AXI IP watch dog timer: kick forward.
*
* @param	WdtTbInstancePtr - NOT NULL Pointer to the struct that represents
*							the WDTTB driver. Initialized and ready
*
* @note		None.
*
******************************************************************************/
void WdtTb_Restart(XWdtTb *WdtTbInstancePtr) {
	/* Verify arguments. */
	uz_assert(WdtTbInstancePtr != NULL);
	uz_assert(WdtTbInstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	XWdtTb_RestartWdt(WdtTbInstancePtr);
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
int WinWdtIntrExample(XWdtTb *WdtTbInstancePtr)
{
	/*
	 * The Driver has to be properly initialized and the GIC interrupt system ALSO!
	 */
	uz_assert(WdtTbInstancePtr != NULL);
	uz_assert(WdtTbInstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	XWdtTb_Start(WdtTbInstancePtr);
	//	WdtExpired = FALSE;

	/* After enabled, write enabled auto clears, so we have to write a 1 to Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(WdtTbInstancePtr, 1);

	HandlerCalled = 0;

	/*
	 * Wait for the first occurrence of interrupt programmed point.
	 */
	while ((HandlerCalled == 0)) ;


	/* Clear interrupt point */
	XWdtTb_IntrClear(WdtTbInstancePtr);
//	WdtExpired = FALSE;
	HandlerCalled = 0;

	/* Wait for the second occurrence of interrupt programmed point */
	while ((HandlerCalled == 0)) ;

	/* Clear interrupt point */
	XWdtTb_IntrClear(WdtTbInstancePtr);
	HandlerCalled = 0;

	/* Check for last event */
	if (XWdtTb_GetLastEvent(WdtTbInstancePtr) != XWDTTB_NO_BAD_EVENT) {
		/* Disable and disconnect the interrupt system */
//		WdtTbDisableIntrSystem(IntcInstancePtr);

		/* Stop the timer */
		XWdtTb_Stop(WdtTbInstancePtr);
		return XST_FAILURE;
	}

//	/* Disable and disconnect the interrupt system */
//	WdtTbDisableIntrSystem(IntcInstancePtr);
//
	/* Stop the timer */
//	XWdtTb_Stop(&WdtTbInstance);

	return XST_SUCCESS;
}

///*****************************************************************************/
///**
//*
//* This function setups the interrupt system such that WDT interrupt can occur
//* for the WdtTb. This function is application specific since the actual
//* system may or may not have an interrupt controller. The WdtTb device could be
//* directly connected to a processor without an interrupt controller. The
//* user should modify this function to fit the application.
//*
//* @param	IntcConfig is a pointer to the instance of the XGIC
//*		Configutarion.
//* @param	IntcInstancePtr is a pointer to the instance of the Intc
//*		driver.
//*
//* @return
//*		- XST_SUCCESS if successful.
//*		- XST_FAILURE, otherwise.
//*
//* @note		None.
//*
//******************************************************************************/
//int WdtTbSetupIntrSystem(XScuGic_Config *IntcConfig, XScuGic *IntcInstancePtr)
//{
//	int Status;
//	u8 Priority, Trigger;
//
//	uz_assert(Wdttb_IsReady);
//
////	TempConfig = IntcConfig;
//
//	IntcInstance.Config = IntcInstancePtr->Config;
//	IntcInstance.IsReady = IntcInstancePtr->IsReady;
//	IntcInstance.UnhandledInterrupts = IntcInstancePtr->UnhandledInterrupts;
//
//	XScuGic_GetPriorityTriggerType(IntcInstancePtr, WDTTB_IRPT_INTR,
//		                                            &Priority, &Trigger);
//
//	Priority = 0x0;
//	Trigger = 3;
//	XScuGic_SetPriorityTriggerType(IntcInstancePtr, WDTTB_IRPT_INTR,
//			Priority, Trigger);
//
//	XScuGic_GetPriorityTriggerType(IntcInstancePtr, WDTTB_IRPT_INTR,
//													&Priority, &Trigger);
//	//	DEBUG INFO
//	//	xil_printf("WdtTbSetupIntrSystem: Wd Prio is %d, level is %d\r\n",Priority, Trigger);
//
//	/*
//	 * Connect the interrupt handler that will be called when an
//	 * interrupt occurs for the device.
//	 */
//	Status = XScuGic_Connect(IntcInstancePtr, WDTTB_IRPT_INTR,
//				(Xil_ExceptionHandler)WdtTbIntrHandler,
//				&WdtTbInstance);
//	if (Status != XST_SUCCESS) {
//		return Status;
//	}
//
//	/* Enable the interrupt for the Timer device */
//	XScuGic_Enable(IntcInstancePtr, WDTTB_IRPT_INTR);
//
//	/* Initialize the exception table */
//	Xil_ExceptionInit();
//
//	/*
//	 * Register the interrupt controller handler with the exception table
//	 */
//	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
//			(Xil_ExceptionHandler)XScuGic_InterruptHandler, // (Xil_ExceptionHandler)INTC_HANDLER,
//			IntcInstancePtr);
//
//	/* Enable non-critical exceptions */
//	Xil_ExceptionEnable();
//
//	return XST_SUCCESS;
//}

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

	XWdtTb *WdtTbInstancePtr = (XWdtTb *)CallBackRef;

	uz_assert(WdtTbInstancePtr != NULL);
	uz_assert(WdtTbInstancePtr->IsReady == XIL_COMPONENT_IS_READY);

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
	XWdtTb_IntrClear(WdtTbInstancePtr);


	/* Increment the number of failures handled or received invocations.*/
	HandlerCalled++;

	/* Check for last event: After Restart inside the second Window it should be always a GOOD_EVENT.
	 * If it is not, Disable and Stop().
	 * */
	if (XWdtTb_GetLastEvent(WdtTbInstancePtr) != XWDTTB_NO_BAD_EVENT) {
		/* Disable and disconnect the interrupt system */
//		WdtTbDisableIntrSystem(&IntcInstance);

		/* Stop the timer */
		XWdtTb_Stop(WdtTbInstancePtr);

	}
//	OR / AND TO STOP PS EXECUTION!!
//  Xil_Assert(__FILE__, __LINE__);


}

///*****************************************************************************/
///**
//*
//* This function disables the interrupts that occur for the WdtTb.
//*
//* @param	IntcInstancePtr is the pointer to the instance of INTC driver.
//* @param	WdtTbIntrId is the WDT Interrupt Id and is typically
//*		XPAR_<INTC_instance>_<WDTTB_instance>_WDT_INTERRUPT_VEC_ID
//*		value from xparameters.h.
//*
//* @return	None.
//*
//* @note		None.
//*
//******************************************************************************/
//void WdtTbDisableIntrSystem(XScuGic *IntcInstancePtr)
//{
//	uz_assert(Wdttb_IsReady);
//
//	/* Disconnect and disable the interrupt for the WdtTb */
//
//	XScuGic_Disable(IntcInstancePtr, WDTTB_IRPT_INTR);
//	XScuGic_Disconnect(IntcInstancePtr, WDTTB_IRPT_INTR);
//
//}

#else /* UZ_WDTTB_MAX_INSTANCES <= 0 */

void WdtTb_Start(XWdtTb *WdtTbInstance) {}

void WdtTb_Restart(XWdtTb *WdtTbInstance) {}

//int WdtTbInit(u32 CounterValue){}

int WinWdtIntrExample(XWdtTb *WdtTbInstance) {}

//XWdtTb *getWdtTbInstance(){}

XWdtTb* uz_WdtTb_init(){}

XWdtTb *uz_WdtTb_init_device(u32 CounterValue, u16 WdtTbDeviceId) {}

void WdtTbIntrHandler(void *CallBackRef);
//static int WdtTbSetupIntrSystem(INTC *IntcInstancePtr){}
//int WdtTbSetupIntrSystem(XScuGic_Config *IntcConfig, XScuGic *IntcInstancePtr){}

//void WdtTbDisableIntrSystem(XScuGic *IntcInstancePtr){}

#endif /* ENABLE_WDT_INT */
