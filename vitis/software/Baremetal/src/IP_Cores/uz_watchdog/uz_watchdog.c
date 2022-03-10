/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2021 David Ken, Eyke Liegmann, Tobias Schindler
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "uz_watchdog.h"
#include "xwdttb.h"
#include "../../uz/uz_global_configuration.h"
#include "../../uz/uz_HAL.h"

/************************** IP structure definition *****************************/

struct uz_watchdog_ip_t
{
	bool is_ready;
	XWdtTb xilinxWdtIP;
	struct uz_watchdog_ip_config_t watchdog_config;
};

/************************** Variable Definitions *****************************/

static size_t instance_counter = 0U;
static uz_watchdog_ip_t instances[UZ_WDTTB_MAX_INSTANCES] = {0};

// Used for testing, to access INT priority, and check preemtion
// XScuGic_Config *TempConfig;

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
static int uz_watchdog_XilinxInit(XWdtTb *WdtTbInstancePtr, uint32_t CounterValue, uint16_t WdtTbDeviceId)
{
	int Status;
	XWdtTb_Config *Config;

	/*
	 * Initialize the WDTTB driver so that it's ready to use look up
	 * configuration in the config table, then initialize it.
	 */
	Config = XWdtTb_LookupConfig(WdtTbDeviceId); // WDTTB_DEVICE_ID by default
	if (NULL == Config)
	{
		return XST_FAILURE;
	}

	/*
	 * Initialize the watchdog timer and timebase driver so that
	 * it is ready to use.
	 */
	Status = XWdtTb_CfgInitialize(WdtTbInstancePtr, Config,
								  Config->BaseAddr);
	if (Status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}

	if (!WdtTbInstancePtr->Config.IsPl)
	{
		/*Enable Window Watchdog Feature in WWDT */
		XWdtTb_ConfigureWDTMode(WdtTbInstancePtr, XWT_WWDT);
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly
	 */
	Status = XWdtTb_SelfTest(WdtTbInstancePtr);
	if (Status != XST_SUCCESS)
	{
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

static uz_watchdog_ip_t *uz_watchdog_allocation()
{
	uz_assert(instance_counter < UZ_WDTTB_MAX_INSTANCES);
	uz_watchdog_ip_t *self = &instances[instance_counter];
	uz_assert_false(self->is_ready);
	instance_counter++;
	self->is_ready = true;
	return (self);
}

/************************** Public Functions ******************************/

uz_watchdog_ip_t *uz_watchdog_ip_init(struct uz_watchdog_ip_config_t watchdog_config)
{
	uz_assert_not_zero(watchdog_config.CounterValue);
	uz_watchdog_ip_t *self = uz_watchdog_allocation();

	uz_watchdog_XilinxInit(&(self->xilinxWdtIP), watchdog_config.CounterValue, watchdog_config.WdtTbDeviceId); // XPFW_WDT_EXPIRE_TIME for WDT PS

	uz_assert(&(self->xilinxWdtIP) != NULL);
	uz_assert(self->xilinxWdtIP.IsReady == XIL_COMPONENT_IS_READY);
	self->watchdog_config = watchdog_config;
	return (self);
}

void uz_watchdog_ip_start(uz_watchdog_ip_t *self)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);

	/* Write a 1 to Set register space to writable */
	// Start the watchdog timer as a normal application would (WEN bit = 1)
	/* After enabled, write enabled auto clears, so we have to write a 1 to Set register space to writable */
	XWdtTb_SetRegSpaceAccessMode(&(self->xilinxWdtIP), 1U);
	XWdtTb_Start(&(self->xilinxWdtIP));
	XWdtTb_SetRegSpaceAccessMode(&(self->xilinxWdtIP), 1U);
}

void uz_watchdog_ip_restart(uz_watchdog_ip_t *self)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	XWdtTb_RestartWdt(&(self->xilinxWdtIP));
}

void uz_watchdog_IntrHandler(void *CallBackRef)
{
	uz_assert(0); // Fire assertion since watchdog interrupt occured --> Watchdog was not padded within the specified time frame
}
