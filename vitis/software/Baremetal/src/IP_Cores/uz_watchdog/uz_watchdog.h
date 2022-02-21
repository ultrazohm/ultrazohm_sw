#pragma once
#ifndef UZ_XWDTTB_H
#define UZ_XWDTTB_H

/*****************************************************************************/
/**
*
* @file uz_watchdog.h
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
* 1.0   David Ken  03/11/21 First draft
* 1.0   David Ken  09/02/22 First version
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xparameters.h"
#include <stdint.h>


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


// We take as reference the Timer_up_time included in the UZ. (100000000U HZ)
#define WDTTB_AXI_CLOCK_FREQ_HZ		XPAR_TIMER_UPTIME_64BIT_CLOCK_FREQ_HZ

// Security Margin in micro seconds. Tested, only one is needed (adds 100 to the wdt counter, with the AXI frec at 100MHz)
#define WDTTB_SECURITY_MARGIN_US		1


/* How to set the second Window Size and the Interruption Point.
 * ------------------------------------------------------------
 * WIN_WDT_SW_COUNT		Second Window Size (Initial counter value)
 * WIN_WDT_BSS_COUNT	Byte selected of the counter. Possible values: 0,1,2,3
 * WIN_WDT_SBC_COUNT	Value to the selected byte. When selected byte of the counter equals this value and the rest of bits are 0, the INT is activated.
 *
 * With the next values we have:
 * 0x2710 = 10.000 clock ticks => 100 microsec to launch the Interruption
 * We establish the interruption point in the value of the counter: 0x0000FF00
 * to have enough time execute the handler function (and restart the WD timer inside the Second Win if we wan to resume normal execution)
 *
 * so we add the clocks needed to the int point: 0x0000FF00 + 0x2710 =  0x00012610 Total Second Window Size
 * */
#define WIN_WDT_SW_COUNT	0x00012610	/**< INITIAL COUNTER VALUE*/
#define WIN_WDT_SBC_COUNT	0xFF		/**< Selected byte count */
#define WIN_WDT_BSS_COUNT	1		/**< Byte segment selected */

#define WIN_WDT_SBC_COUNT_SHIFTED	0x0000FF00

// calculate the period in microseconds adding a security margin
#define WDTTB_PERIOD_US    ((1.0f/(UZ_PWM_FREQUENCY * Interrupt_ISR_freq_factor)*1e6f) + WDTTB_SECURITY_MARGIN_US)

// cycles_per_us = WDTTB_AXI_CLOCK_FREQ_HZ * 1e-6   // for 100 MHz->10ns; 10ns * 100 = 1us
// cycles_per_period times cycles_per_us   and  we add the base or shift as it is requested by the specification
#define WDTTB_CYCLES_PER_PERIOD ((((uint32_t) WDTTB_PERIOD_US) * (WDTTB_AXI_CLOCK_FREQ_HZ * 1e-6)) + WIN_WDT_SBC_COUNT_SHIFTED)

// ORIGINAL VALUES FOR THE EXAMPLE
//#define WIN_WDT_SW_COUNT	0xF00000	/**< Number of clock cycles for
//						  *  second window */
//#define WIN_WDT_SBC_COUNT	16		/**< Selected byte count */
//#define WIN_WDT_BSS_COUNT	2		/**< Byte segment selected */


/**************************** Type Definitions *******************************/

typedef struct uz_watchdog_ip_t uz_watchdog_ip_t;


/** @struct uz_watchdog_ip_config_t
 *  @brief This structure is used to initialize the WatchDog Timer IP driver
 *  @var uz_watchdog_ip_config_t::CounterValue
 *  Member 'CounterValue' contains the initial value for the counter in number of tics.
 * 					Watchdog timeout is therefore CounterValue * Tcycle
 *  @var uz_watchdog_ip_config_t::WdtTbDeviceId
 *  Member 'WdtTbDeviceId' contains is the Device ID of the WdtTb Device and is
 *		typically XPAR_<WDTTB_instance>_DEVICE_ID value from
 *		xparameters.h.
 */
struct uz_watchdog_ip_config_t {
  uint32_t CounterValue;
  uint16_t WdtTbDeviceId;
};


/************************** Function Prototypes ******************************/

/**
* @brief This function STARTs the System WatchDog Timer to the initial
*        value to the counter. Generates a good event if executed inside
*        the Second Window, or OPEN Window.
*        The WDT Start is accomplished by enabling the IP Core
*        writing WEN bit =1. And granting write access to the IP
*        Registers.
*
* @param	WdtTbInstancePtr - NOT NULL Pointer to the struct that represents
*							the WDTTB driver. Initialized and ready
*/
void uz_watchdog_ip_start(uz_watchdog_ip_t *WdtTbInstancePtr) ;

/**
* @brief This function Restart the AXI IP watch dog timer: kick forward.
*
* @param	WdtTbInstancePtr - NOT NULL Pointer to the struct that represents
*							the WDTTB driver. Initialized and ready
*/
void uz_watchdog_ip_restart(uz_watchdog_ip_t *WdtTbInstancePtr) ;

/**
* @brief This function initializes the WatchDog Timer IP driver and sets the inital value to the counter.
*        This is the total size for The Second Window (Open). The closed
*        Window is not used (0 value for its counter). The rest of the
*        optional functions: FC, SST and SIGNATURE are disabled.
*
* @param	watchdog_config - Config structure with DeviceID and second window size.
*
* @return	uz_watchdog_ip_t pointer to the initialized WDTTB driver.
*/
uz_watchdog_ip_t* uz_watchdog_ip_init(struct uz_watchdog_ip_config_t watchdog_config);

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
void uz_watchdog_IntrHandler(void *CallBackRef);


#endif // UZ_XWDTTB_H
