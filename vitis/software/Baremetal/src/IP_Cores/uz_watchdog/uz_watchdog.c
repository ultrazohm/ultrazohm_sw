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
#include "../../uz/uz_global_configuration.h"
#if UZ_WDTTB_MAX_INSTANCES > 0
#include "xwdttb.h"
#include "../../uz/uz_HAL.h"

#define WDTTB_SECURITY_MARGIN_US 1.0f // Security Margin in micro seconds. Tested, only one is needed (adds 100 to the wdt counter, with the AXI frec at 100MHz)

#define WIN_WDT_SBC_COUNT 0xFF /**< Selected byte count */
#define WIN_WDT_BSS_COUNT 1U    /**< Byte segment selected */
#define WIN_WDT_SBC_COUNT_SHIFTED 0x0000FF00

struct uz_watchdog_ip_t
{
    bool is_ready;
    XWdtTb xilinxWdtIP;
    uint32_t reset_counter_start_value;
    struct uz_watchdog_ip_config_t watchdog_config;
};

static size_t instance_counter = 0U;
static uz_watchdog_ip_t instances[UZ_WDTTB_MAX_INSTANCES] = {0};

static uz_watchdog_ip_t *uz_watchdog_allocation()
{
    uz_assert(instance_counter < UZ_WDTTB_MAX_INSTANCES);
    uz_watchdog_ip_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

static int uz_watchdog_write_init_values_to_registers(XWdtTb *watchdog_instance_ptr, uint32_t window_counter_value, uint16_t watchdog_device_id);

static uint32_t uz_watchdog_calculate_counter_from_time(uint32_t ip_clk_frequency_Hz, float reset_timer_in_us);

uz_watchdog_ip_t *uz_watchdog_ip_init(struct uz_watchdog_ip_config_t watchdog_config)
{
    uz_assert(watchdog_config.reset_timer_in_us > 1.0f); // Minimum reset timer
    uz_assert_not_zero_uint32(watchdog_config.ip_clk_frequency_Hz);

    uz_watchdog_ip_t *self = uz_watchdog_allocation();
    self->watchdog_config = watchdog_config;
    self->reset_counter_start_value = uz_watchdog_calculate_counter_from_time(watchdog_config.ip_clk_frequency_Hz, watchdog_config.reset_timer_in_us);

    uz_watchdog_write_init_values_to_registers(&(self->xilinxWdtIP), self->reset_counter_start_value, self->watchdog_config.device_id); // XPFW_WDT_EXPIRE_TIME for WDT PS
    uz_assert(&(self->xilinxWdtIP) != NULL);
    uz_assert(self->xilinxWdtIP.IsReady == XIL_COMPONENT_IS_READY);
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
    uz_assert(0); // Fire assertion since watchdog interrupt occurred --> Watchdog was not padded within the specified time frame
}

static int uz_watchdog_write_init_values_to_registers(XWdtTb *watchdog_instance_ptr, uint32_t window_counter_value, uint16_t watchdog_device_id)
{
    XWdtTb_Config *Config = XWdtTb_LookupConfig(watchdog_device_id); // WDTTB_DEVICE_ID by default
    uz_assert_not_NULL(Config);

    int32_t Status = XWdtTb_CfgInitialize(watchdog_instance_ptr, Config, Config->BaseAddr);
    uz_assert(!Status);

    /*Enable Window Watchdog Feature in WWDT */
    if (!watchdog_instance_ptr->Config.IsPl)
    {
        const uint32_t watchdog_window_mode = 1U; // writing 1 to XWdtTb_ConfigureWDTMode enables window mode, see xwdttb.h
        XWdtTb_ConfigureWDTMode(watchdog_instance_ptr, watchdog_window_mode);
    }

    Status = XWdtTb_SelfTest(watchdog_instance_ptr);
    uz_assert(!Status);

    /* Set register space to writable */
    XWdtTb_SetRegSpaceAccessMode(watchdog_instance_ptr, 1U);

    /* Configure first window = 0 (NOT USED THE CLOSED WINDOW) and second window */
    XWdtTb_SetWindowCount(watchdog_instance_ptr, 0U, window_counter_value);

    /* Set interrupt position */
    XWdtTb_SetByteCount(watchdog_instance_ptr, WIN_WDT_SBC_COUNT);
    XWdtTb_SetByteSegment(watchdog_instance_ptr, WIN_WDT_BSS_COUNT);

    /* Disable Secondary Sequence Timer (SST) */
    XWdtTb_DisableSst(watchdog_instance_ptr);

    /* Disable Program Sequence Monitor (PSM) */
    XWdtTb_DisablePsm(watchdog_instance_ptr);

    /* Disable Fail Counter */
    XWdtTb_DisableFailCounter(watchdog_instance_ptr);

    return XST_SUCCESS;
}

static uint32_t uz_watchdog_calculate_counter_from_time(uint32_t ip_clk_frequency_Hz, float reset_timer_in_us)
{
    uz_assert_not_zero_uint32(ip_clk_frequency_Hz);
    uz_assert(reset_timer_in_us > 0.0f); // no negative time allowed
    reset_timer_in_us += WDTTB_SECURITY_MARGIN_US;
    reset_timer_in_us = roundf(reset_timer_in_us);                                             // Round since casting will turncate
    uint32_t counter_value = ((uint32_t)reset_timer_in_us) * (ip_clk_frequency_Hz / 1000000U); // Scaling ip_clk_frequency to MHz for easy calculation
    counter_value += WIN_WDT_SBC_COUNT_SHIFTED;                                                // Adds shifted offset for interrupt time
    return counter_value;
}

#endif