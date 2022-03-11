#pragma once
#include <stdint.h>


typedef struct uz_watchdog_ip_t uz_watchdog_ip_t;

enum uz_watchdog_fail_mode{
    watchdog_assertion=0,
    watchdog_debug_mode
};

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
  uint16_t device_id;
  uint32_t ip_clk_frequency_Hz;
  float reset_timer_in_us;
  enum uz_watchdog_fail_mode fail_mode;
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

