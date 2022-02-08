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
#include "xwdttb.h"
#include "../../uz/uz_global_configuration.h"
#include "../../uz/uz_HAL.h"

#if (UZ_WDTTB_MAX_INSTANCES > 0U && UZ_WDTTB_MAX_INSTANCES <= XPAR_XWDTTB_NUM_INSTANCES)

/************************** Constant Definitions *****************************/

#define HANDLER_CALLED  0xFFFFFFFF

struct uz_watchdog_ip_t {
    bool is_ready;
    XWdtTb xilinxWdtIP;
    struct uz_watchdog_ip_config_t watchdog_config;
};

/************************** Variable Definitions *****************************/

static size_t instance_counter = 0U;
static uz_watchdog_ip_t instances[UZ_WDTTB_MAX_INSTANCES] = {0};

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
static int uz_watchdog_XilinxInit(XWdtTb *WdtTbInstancePtr, uint32_t CounterValue, uint16_t WdtTbDeviceId) {
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

static uz_watchdog_ip_t *uz_watchdog_allocation(uint32_t CounterValue, uint16_t WdtTbDeviceId)
{
	uz_assert(instance_counter < UZ_WDTTB_MAX_INSTANCES);
    uz_watchdog_ip_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);

    /*
	 * Call the WDT init to initialize and set timer to the given timeout.
	 * Both
	 */
	int Status = uz_watchdog_XilinxInit(&(self->xilinxWdtIP), CounterValue, WdtTbDeviceId); // XPFW_WDT_EXPIRE_TIME for WDT PS

	if (Status != XST_SUCCESS) {
		//DEBUG
		//xil_printf("WDT initialization failed\r\n");
		return NULL;
	}

	uz_assert(&(self->xilinxWdtIP) != NULL);
    uz_assert(self != NULL);

#ifdef TEST
	XWdtTb_Config conf =
	{
		XPAR_WDTTB_0_DEVICE_ID,
		XPAR_WDTTB_0_BASEADDR,
		XPAR_WDTTB_0_ENABLE_WINDOW_WDT,
		XPAR_WDTTB_0_MAX_COUNT_WIDTH,
		XPAR_WDTTB_0_SST_COUNT_WIDTH,
		XPAR_WDTTB_0_IS_PL
	};

	XWdtTb testWdtTb = {
    .Config = conf,        /**< Hardware Configuration */
    .IsReady = XIL_COMPONENT_IS_READY,          /**< Device is initialized and ready */
   };
   self->xilinxWdtIP = testWdtTb;
#endif
#ifndef TEST
// The real initialization and readyness is done by xilinx driver.
// Not done if we are mocking the driver under TEST.
    uz_assert(self->xilinxWdtIP.IsReady == XIL_COMPONENT_IS_READY);
#endif
    instance_counter++;
    self->is_ready = true;
    return (self);
}

/************************** Public Functions ******************************/

uz_watchdog_ip_t* uz_watchdog_ip_init(struct uz_watchdog_ip_config_t watchdog_config)
{
	uz_assert_not_zero(watchdog_config.CounterValue);
	// uz_assert_not_zero(watchdog_config.WdtTbDeviceId);
	uz_watchdog_ip_t *self = uz_watchdog_allocation(watchdog_config.CounterValue, watchdog_config.WdtTbDeviceId);
	self->watchdog_config=watchdog_config;
    return (self);
}

/*****************************************************************************/

void uz_watchdog_ip_start(uz_watchdog_ip_t *WdtTbInstancePtr) {

	/* Verify arguments. */
	uz_assert(WdtTbInstancePtr != NULL);
	uz_assert(WdtTbInstancePtr->is_ready);
	uz_assert(WdtTbInstancePtr->xilinxWdtIP.IsReady == XIL_COMPONENT_IS_READY);
//	/* Stop the timer, disabling the WDTTB, writing 0 in bit WEN */
//	XWdtTb_Stop(&WdtTbInstancePtr);


	/* Write a 1 to Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(&(WdtTbInstancePtr->xilinxWdtIP), 1);

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
	XWdtTb_Start(&(WdtTbInstancePtr->xilinxWdtIP));
//	WdtExpired = FALSE;

	/* After enabled, write enabled auto clears, so we have to write a 1 to Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(&(WdtTbInstancePtr->xilinxWdtIP), 1);
}

/*****************************************************************************/

void uz_watchdog_ip_restart(uz_watchdog_ip_t *WdtTbInstancePtr) {
	/* Verify arguments. */
	uz_assert(WdtTbInstancePtr != NULL);
	uz_assert(WdtTbInstancePtr->is_ready);
	uz_assert(WdtTbInstancePtr->xilinxWdtIP.IsReady == XIL_COMPONENT_IS_READY);

	XWdtTb_RestartWdt(&(WdtTbInstancePtr->xilinxWdtIP));
}


/*****************************************************************************/

int uz_watchdog_WinIntrExample(uz_watchdog_ip_t *WdtTbInstancePtr)
{
	/*
	 * The Driver has to be properly initialized and the GIC interrupt system ALSO!
	 */
	uz_assert(WdtTbInstancePtr != NULL);
	uz_assert(WdtTbInstancePtr->is_ready);
	uz_assert(WdtTbInstancePtr->xilinxWdtIP.IsReady == XIL_COMPONENT_IS_READY);

	XWdtTb_Start(&(WdtTbInstancePtr->xilinxWdtIP));
	//	WdtExpired = FALSE;

	/* After enabled, write enabled auto clears, so we have to write a 1 to Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(&(WdtTbInstancePtr->xilinxWdtIP), 1);

	HandlerCalled = 0;

	/*
	 * Wait for the first occurrence of interrupt programmed point.
	 */
	while ((HandlerCalled == 0)) ;


	/* Clear interrupt point */
	XWdtTb_IntrClear(&(WdtTbInstancePtr->xilinxWdtIP));
//	WdtExpired = FALSE;
	HandlerCalled = 0;

	/* Wait for the second occurrence of interrupt programmed point */
	while ((HandlerCalled == 0)) ;

	/* Clear interrupt point */
	XWdtTb_IntrClear(&(WdtTbInstancePtr->xilinxWdtIP));
	HandlerCalled = 0;

	/* Check for last event */
	if (XWdtTb_GetLastEvent(&(WdtTbInstancePtr->xilinxWdtIP)) != XWDTTB_NO_BAD_EVENT) {
		/* Disable and disconnect the interrupt system */
//		WdtTbDisableIntrSystem(IntcInstancePtr);

		/* Stop the timer */
		XWdtTb_Stop(&(WdtTbInstancePtr->xilinxWdtIP));
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

	uz_watchdog_ip_t *WdtTbInstancePtr = (uz_watchdog_ip_t *)CallBackRef;

	uz_assert(WdtTbInstancePtr != NULL);
	uz_assert(WdtTbInstancePtr->is_ready);
	uz_assert(WdtTbInstancePtr->xilinxWdtIP.IsReady == XIL_COMPONENT_IS_READY);

	//	DEBUG INFO
	// u32 reg;
	// reg = XScuGic_ReadReg(TempConfig->CpuBaseAddress, XSCUGIC_RUN_PRIOR_OFFSET);
	//	xil_printf("WdtTbIntrHandler AND RESTART AND CLEAR: Running priority in WDT handler is %d\r\n",reg >> 3);

	/*
	 * Restart the watchdog timer as a normal application would.
	 * The WDT Retart is to continue the execution
	 * */
	XWdtTb_RestartWdt(&(WdtTbInstancePtr->xilinxWdtIP));

	/* Clear interrupt point. To allow a new INT to be triggered again (see documentation)*/
	XWdtTb_IntrClear(&(WdtTbInstancePtr->xilinxWdtIP));


	/* Increment the number of failures handled or received invocations.*/
	HandlerCalled++;

	/* Check for last event: After Restart inside the second Window it should be always a GOOD_EVENT.
	 * If it is not, Disable and Stop().
	 * */
	if (XWdtTb_GetLastEvent(&(WdtTbInstancePtr->xilinxWdtIP)) != XWDTTB_NO_BAD_EVENT) {
		/* Disable and disconnect the interrupt system
		 * FROM the isr.c main interrupt manager inside
		 * this Baremetal project with
		 * WdtTbDisableIntrSystem(&IntcInstance);*/

		/* Stop the timer */
		XWdtTb_Stop(&(WdtTbInstancePtr->xilinxWdtIP));

	}
//	OR / AND TO STOP PS EXECUTION!!
//  Xil_Assert(__FILE__, __LINE__);


}


#else /* UZ_WDTTB_MAX_INSTANCES <= 0 */

void uz_watchdog_ip_start(uz_watchdog_ip_t *WdtTbInstancePtr) {}

void uz_watchdog_ip_restart(uz_watchdog_ip_t *WdtTbInstancePtr) {}


int uz_watchdog_WinIntrExample(uz_watchdog_ip_t *WdtTbInstancePtr) {}


uz_watchdog_ip_t* uz_watchdog_ip_init(struct uz_watchdog_ip_config_t watchdog_config) {}


void uz_watchdog_IntrHandler(void *CallBackRef);


#endif /* UZ_WDTTB_MAX_INSTANCES <= 0 */
