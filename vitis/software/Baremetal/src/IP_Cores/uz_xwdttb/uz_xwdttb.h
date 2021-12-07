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

/************************** Enabling Module  *****************************/
// Go to "../../uz/uz_global_configuration.h" and set UZ_WDTTB_MAX_INSTANCES to 0U (0 instances)

/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are only defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define WDTTB_DEVICE_ID         XPAR_WDTTB_0_DEVICE_ID
// Constants for the GIC driver management
#define INTC_DEVICE_ID         XPAR_SCUGIC_SINGLE_DEVICE_ID
#define WDTTB_IRPT_INTR       XPAR_FABRIC_WDTTB_0_VEC_ID

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

// ORIGINAL VALUES FOR THE EXAMPLE
//#define WIN_WDT_SW_COUNT	0xF00000	/**< Number of clock cycles for
//						  *  second window */
//#define WIN_WDT_SBC_COUNT	16		/**< Selected byte count */
//#define WIN_WDT_BSS_COUNT	2		/**< Byte segment selected */



/**************************** Type Definitions *******************************/
#define HANDLER_CALLED  0xFFFFFFFF


/************************** Function Prototypes ******************************/

/**
* @brief This function STARTs the System WatchDog Timer to the initial
*        value to the counter.Generates a good event if executed inside
*        the Second Window, or OPEN Window.
*        The WDT Start is accomplished by enabling the IP Core
*        writing WEN bit =1. And granting write access to the IP
*        Registers.
*
* @param	WdtTbInstancePtr - NOT NULL Pointer to the struct that represents
*							the WDTTB driver. Initialized and ready
*/
void WdtTb_Start(XWdtTb *WdtTbInstancePtr) ;

/**
* @brief This function Restart the AXI IP watch dog timer: kick forward.
*
* @param	WdtTbInstancePtr - NOT NULL Pointer to the struct that represents
*							the WDTTB driver. Initialized and ready
*/
void WdtTb_Restart(XWdtTb *WdtTbInstancePtr) ;

/**
 * @brief Initializes an instance of the WDTTB driver
 *
 * @return XWdtTb pointer to the initialized WDTTB driver.
 */
XWdtTb* uz_WdtTb_init();

/**
* @brief This function initializes and tests the functioning of the System
*        WatchDog Timer driver and sets the inital value to the counter.
*        This is the total size for The Second Window (Open). The closed
*        Window is not used (0 value for its counter). The rest of the
*        optional functions: FC, SST and SIGNATURE are disabled.
*
* @param	CounterValue - Initial value for the counter in number of tics.
* 					Watchdog timeout is therefore CounterValue * Tcycle,
* 					and Tcycle = 10 ns with a 100MH processor.
* @param	WdtTbDeviceId is the Device ID of the WdtTb Device and is
*		typically XPAR_<WDTTB_instance>_DEVICE_ID value from
*		xparameters.h.
*
* @return	XWdtTb pointer to the initialized WDTTB driver.
*/
XWdtTb* uz_WdtTb_init_device(u32 CounterValue, u16 WdtTbDeviceId);

/**
* @brief This function tests the functioning of the Window Watchdog
*        Timer in the interrupt mode.
*
*        This function waits for interrupt programmed point in
*        second window. If the interrupt has occurred, interrupt
*        handler sets a flag and restarts the timer. This function
*        then clears the interrupt, flag and waits for second
*        interrupt to occur and continue waiting for second
*        interrupt as mentioned above.
*
*        This function assumes that the reset output of the Window
*        Watchdog Timer is not connected to the reset of the processor.
*        The function allows the Window Watchdog Timer to timeout such
*        that a reset will occur if it is connected.
*
*        The Driver has to be properly initialized and the GIC interrupt system ALSO!
*
* @param	WdtTbInstancePtr is a pointer to the instance of WdtTb driver.
*
* @return
*		- XST_SUCCESS if interrupt example run successfully.
*		- XST_FAILURE, if reset has occurred.
*/
int WinWdtIntrExample(XWdtTb *WdtTbInstancePtr);

/**
* @brief This function is the Interrupt handler for the WDT Interrupt of the
*        WdtTb device. It is called when reached to the interrupt programmed point
*        and is called from an interrupt context.
*
*        The handler of the timing violation. The default behavior is to resume
*        the execution, by restarting the WDT. The execution time of this
*        function is also limited, as is has to restart the WDT inside the
*        second window, otherwise a Reset from the IP core is activated,
*        and the IP stops running
*
* @param	CallBackRef is a pointer to the callback reference.
*
* @return	None.
*/
void WdtTbIntrHandler(void *CallBackRef);


#endif // UZ_XWDTTB_H
