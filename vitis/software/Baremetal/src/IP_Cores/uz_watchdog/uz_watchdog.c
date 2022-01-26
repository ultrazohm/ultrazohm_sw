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
#include "uz_watchdog.h"

#include "../../uz/uz_global_configuration.h"
#include "../../uz/uz_HAL.h"

#if (UZ_WDTTB_MAX_INSTANCES > 0U && UZ_WDTTB_MAX_INSTANCES <= XPAR_XWDTTB_NUM_INSTANCES)

/************************** Variable Definitions *****************************/

static size_t instance_counter = 0U;
static XWdtTb instances[UZ_WDTTB_MAX_INSTANCES] = {0};

volatile u32 HandlerCalled;	/* flag is set when timeout interrupt occurs */

// Used for testing, to access INT priority, and check preemtion
//XScuGic_Config *TempConfig;

/************************** Function Definitions ******************************/


/************************** Private Functions ******************************/

/**
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
static int uz_watchdog_Init(XWdtTb *WdtTbInstancePtr, uint32_t CounterValue, uint16_t WdtTbDeviceId) {
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

static XWdtTb *uz_watchdog_allocation(uint32_t CounterValue, uint16_t WdtTbDeviceId)
{
    uz_assert(instance_counter < UZ_WDTTB_MAX_INSTANCES);

    /*
	 * Call the WDT init to initialize and set timer to the given timeout.
	 * Both
	 */
	int Status = uz_watchdog_Init(&instances[instance_counter], CounterValue, WdtTbDeviceId); // XPFW_WDT_EXPIRE_TIME for WDT PS

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

/************************** Public Functions ******************************/

XWdtTb *uz_watchdog_init()
{
    XWdtTb *self = uz_watchdog_allocation(WIN_WDT_SW_COUNT, WDTTB_DEVICE_ID);
    return (self);
}

/*****************************************************************************/

XWdtTb *uz_watchdog_init_device(uint32_t CounterValue, uint16_t WdtTbDeviceId)
{
    XWdtTb *self = uz_watchdog_allocation(CounterValue, WdtTbDeviceId);
    return (self);
}

/*****************************************************************************/

void uz_watchdog_Start(XWdtTb *WdtTbInstancePtr) {

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

/*****************************************************************************/

void uz_watchdog_Restart(XWdtTb *WdtTbInstancePtr) {
	/* Verify arguments. */
	uz_assert(WdtTbInstancePtr != NULL);
	uz_assert(WdtTbInstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	XWdtTb_RestartWdt(WdtTbInstancePtr);
}


/*****************************************************************************/

int uz_watchdog_WinIntrExample(XWdtTb *WdtTbInstancePtr)
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

/*****************************************************************************/

void uz_watchdog_IntrHandler(void *CallBackRef)
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
		/* Disable and disconnect the interrupt system
		 * FROM the isr.c main interrupt manager inside
		 * this Baremetal project with
		 * WdtTbDisableIntrSystem(&IntcInstance);*/

		/* Stop the timer */
		XWdtTb_Stop(WdtTbInstancePtr);

	}
//	OR / AND TO STOP PS EXECUTION!!
//  Xil_Assert(__FILE__, __LINE__);


}


#else /* UZ_WDTTB_MAX_INSTANCES <= 0 */

void uz_watchdog_Start(XWdtTb *WdtTbInstancePtr) {}

void uz_watchdog_Restart(XWdtTb *WdtTbInstancePtr) {}


int uz_watchdog_WinIntrExample(XWdtTb *WdtTbInstancePtr) {}


XWdtTb *uz_watchdog_init(){}

XWdtTb *uz_watchdog_init_device(uint32_t CounterValue, uint16_t WdtTbDeviceId) {}

void uz_watchdog_IntrHandler(void *CallBackRef);


#endif /* UZ_WDTTB_MAX_INSTANCES <= 0 */
