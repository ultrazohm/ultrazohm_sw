#ifndef UZ_XWDTTB_H
#define UZ_XWDTTB_H

/*****************************************************************************/
/**
*
* @file uz_xwdttb.h
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

#include "xparameters.h"
#include "xwdttb.h"
#include "xil_exception.h"


#define ENABLE_WDTTB_INT

#ifdef XPAR_INTC_0_DEVICE_ID
#include "xintc.h"
#include <stdio.h>
#else
#include "xscugic.h"
#include "xil_printf.h"
#endif

/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are only defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#ifndef TESTAPP_GEN
#define WDTTB_DEVICE_ID         XPAR_WDTTB_0_DEVICE_ID
#endif

#ifdef XPAR_INTC_0_DEVICE_ID
 #define INTC_DEVICE_ID         XPAR_INTC_0_DEVICE_ID
 #define WDTTB_IRPT_INTR         XPAR_INTC_0_WDTTB_0_VEC_ID
#else
 #define INTC_DEVICE_ID         XPAR_SCUGIC_SINGLE_DEVICE_ID
 #ifdef versal
  #define WDTTB_IRPT_INTR       XPAR_XWWDT_0_INTR
 #else
  #define WDTTB_IRPT_INTR       XPAR_FABRIC_WDTTB_0_VEC_ID
 #endif
#endif /* XPAR_INTC_0_DEVICE_ID */


// ORIGINAL VALUES FOR THE EXAMPLE
//#define WIN_WDT_SW_COUNT	0xF00000	/**< Number of clock cycles for
//						  *  second window */
//#define WIN_WDT_SBC_COUNT	16		/**< Selected byte count */
//#define WIN_WDT_BSS_COUNT	2		/**< Byte segment selected */



/* How to set the second Window Size and the Interruption Point.
 * ------------------------------------------------------------
 * WIN_WDT_SW_COUNT		Second Window Size (Initial counter value)
 * WIN_WDT_BSS_COUNT	Byte selected of the counter. Possible values: 0,1,2,3
 * WIN_WDT_SBC_COUNT	Value to the selected byte. When selected byte of the counter equals this value and the rest of bits are 0, the INT is activated.
 *
 * Wit the nexte values we have:
 * 9*2^10 = 10.000 clock ticks => 100 microsec to launch the Interruption
 * 54*2^10 = more than 500 micro secs to execute the handler function (and restart the WD timer inside the Second Win if we wan to resume normal execution)
 *
 * Giving a total Secon Window Size of 63*2^10
 * */
#define WIN_WDT_SW_COUNT	0x0000FC00	/**< 63*2^10 INITIAL COUNTER VALUE*/
#define WIN_WDT_SBC_COUNT	0xD8		/**< Selected byte count */
#define WIN_WDT_BSS_COUNT	1		/**< Byte segment selected */



/**************************** Type Definitions *******************************/
#define HANDLER_CALLED  0xFFFFFFFF

//#ifdef XPAR_INTC_0_DEVICE_ID
//
//#define INTC			XIntc
//#define INTC_HANDLER		XIntc_InterruptHandler
//#else
//#define INTC			XScuGic
//#define INTC_HANDLER		XScuGic_InterruptHandler
//#endif /* XPAR_INTC_0_DEVICE_ID */

/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/


void WdtTb_Start() ;

void WdtTb_Restart() ;

int WdtTbInit(u32 CounterValue);

int WinWdtIntrExample(XScuGic *IntcInstancePtr);

void WdtTbIntrHandler(void *CallBackRef);
//static int WdtTbSetupIntrSystem(INTC *IntcInstancePtr);
int WdtTbSetupIntrSystem(XScuGic_Config *IntcConfig, XScuGic *IntcInstancePtr);
void WdtTbDisableIntrSystem(XScuGic *IntcInstancePtr);

/************************** Variable Definitions *****************************/

#ifndef TESTAPP_GEN
XWdtTb WdtTbInstance;	/* Instance of Time Base WatchDog Timer */
XScuGic IntcInstance;	/* Instance of the Interrupt Controller */
#endif

//volatile int WdtExpired;
volatile u32 HandlerCalled;	/* flag is set when timeout interrupt occurs */

#endif // UZ_XWDTTB_H
