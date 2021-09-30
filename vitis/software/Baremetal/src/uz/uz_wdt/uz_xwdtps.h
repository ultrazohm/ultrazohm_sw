/*****************************************************************************/
/**
*
* @file uz_xwdtps.h
*
* This file contains a design example using the System Watchdog Timer Device
* (WdtPs) driver and hardware device using interrupt mode. This example test
* assumes that the RESET OUTPUT OF WDT IS NOT CONNECTED to the processor and
* the IRQ output is connected to an interrupt controller attached to the
* processor.
*
* It also contains a XWdtPs_ResetRestart to restart the WDT and enabling Reset Output.
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

#ifndef XWDTPS_INTR_H		/* prevent circular inclusions */
#define XWDTPS_INTR_H		/* by using protection macros */

/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xwdtps.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"


#define ENABLE_WDT_INT


/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are only defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#ifdef XPAR_PS7_WDT_0_DEVICE_ID
#define WDT_IRPT_INTR		XPS_WDT_INT_ID
#endif

#ifdef XPAR_PSU_CSU_WDT_DEVICE_ID
	#define WDT_IRPT_INTR		XPS_CSU_WDT_INT_ID
#else
	#ifdef XPAR_PSU_WDT_0_DEVICE_ID
		#define WDT_IRPT_INTR		XPS_LPD_SWDT_INT_ID
	#else
		#ifdef XPAR_PSU_WDT_1_DEVICE_ID
			#define WDT_IRPT_INTR		XPS_FPD_SWDT_INT_ID
		#endif
	#endif
#endif

#define WDT_DEVICE_ID		XPAR_XWDTPS_0_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID


/*
 * WDT Default expire time in milliseconds.
 *
 * If defined with 0U it will expire with the smallest time value
 * (about 350 useconds).
 */
#define XPFW_WDT_EXPIRE_TIME (0U)

#define XPFW_WDT_CRV_SHIFT 12U
#define XPFW_WDT_PRESCALER 8U

#define XPFW_WDT_CLK_PER_MSEC ((XPAR_PSU_WDT_0_WDT_CLK_FREQ_HZ) / (XPFW_WDT_PRESCALER * 1000U))
#define XPFW_WDT_COUNTER_VAL ((XPFW_WDT_EXPIRE_TIME) * (XPFW_WDT_CLK_PER_MSEC))



/**************************** Type Definitions *******************************/
#define HANDLER_CALLED  0xFFFFFFFF

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

u32 WdtPsIntrPolled(u32 ExpiredTimeDelta) ;

void XWdtPs_ResetRestart() ;

int WdtPsInit(u32 Timeout);

int WdtPsIntrExample(XScuGic *IntcInstancePtr);

void WdtIntrHandler(void *CallBackRef);

int WdtSetupIntrSystem(XScuGic *IntcInstancePtr);

void WdtDisableIntrSystem(XScuGic *IntcInstancePtr);

/************************** Variable Definitions *****************************/

XWdtPs WdtInstance;		/* Instance of WatchDog Timer */
XScuGic IntcInstance;		/* Instance of the Interrupt Controller */

volatile u32 HandlerCalled;	/* flag is set when timeout interrupt occurs */

#endif /* end of protection macro */
