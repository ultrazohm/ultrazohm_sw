#pragma once
#include <stdint.h>

#define WDTTB_SECURITY_MARGIN_US 1 // Security Margin in micro seconds. Tested, only one is needed (adds 100 to the wdt counter, with the AXI frec at 100MHz)

#define WIN_WDT_SBC_COUNT 0xFF /**< Selected byte count */
#define WIN_WDT_BSS_COUNT 1	   /**< Byte segment selected */
// We take as reference the Timer_up_time included in the UZ. (100000000U HZ)
#define WDTTB_AXI_CLOCK_FREQ_HZ		100000000


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
  uint16_t device_id;
};


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
void uz_watchdog_ip_start(uz_watchdog_ip_t *self) ;

/**
* @brief This function Restart the AXI IP watch dog timer: kick forward.
*
* @param	WdtTbInstancePtr - NOT NULL Pointer to the struct that represents
*							the WDTTB driver. Initialized and ready
*/
void uz_watchdog_ip_restart(uz_watchdog_ip_t *self) ;

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

