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



/**< Number of clock cycles for
 *  second window
*/

// VALUES FOR TESTING, ENOUGHT TIME FOR HANDLER PRINTS (54*2^10, more than 500 micro secs)
#define WIN_WDT_SW_COUNT	0x0000FC00	/**< 63*2^10 INITIAL VALUE*/
#define WIN_WDT_SBC_COUNT	0xD8		/**< Selected byte count */
#define WIN_WDT_BSS_COUNT	1		/**< Byte segment selected */


// REAL AND ADJUNTED VALUES, Handler left with 50 micro seconds aprox, 5*2^10 clock ticks exactly *a little over 5000 that the 50 us requieres
//#define WIN_WDT_SW_COUNT	0x00003800	/**< 14*2^10 INITIAL VALUE */
//#define WIN_WDT_SBC_COUNT	0x14		/**< Selected byte count */
//#define WIN_WDT_BSS_COUNT	1		/**< Byte segment selected */




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

int WdtTbInit(u32 Timeout);

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

