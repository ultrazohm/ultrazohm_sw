/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between UltraZohm project and XCP Basic Driver
 */

#include <stdint.h>
#include <stddef.h>

#include "xcp_config.h"
#include "XCP_Basic/XcpBasic.h"

#include "RPU_APU_exchange.h"

/*-------------------------------------------------------------------
 * Types
 *-----------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * Configuration
 *-----------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
static uint32_t xcp_timestamp;

volatile uint32_t data_first_addr_read_OCM = 0;

/*-------------------------------------------------------------------
 * Static functions
 *-----------------------------------------------------------------*/
static void xcp_interface_stim(void)
{
	while (1) {
		uint8_t *data;
		uint8_t len;
		if (! rpu_apu_exchange_readOCM(&len, &data)) {
			// Could not read a message from OCM
			break;
		}

		XcpCommand((uint32_t *)(data + XCP_HEADER_LEN));
	}
}

static void xcp_interface_events_10kHz(void)
{
	/* TODO: Possible optimization: Make sure only 2 or 3 messages are written
	 * to the OCM at a time to reduce IRQ run time in R5 and A53.
	 *  This could be achieved by adding a counter of packages sent in a cycle.
	 *  If this counter reaches 2 an additional xcp events activation is
	 *  delayed to the next cycle.
	 *  This will add jitter to the slower tasks.
	 */

    xcp_timestamp += 1; // = uz_SystemTime_GetUptimeInUs();

    XcpEvent(XCP_EVENT_FAST);

    static uint32_t cnt_div_10 = 0;
    cnt_div_10++;
    if (cnt_div_10 >= 10) {
        cnt_div_10 = 0;

        XcpEvent(XCP_EVENT_1MS);
    }

    static uint32_t cnt_div_100 = 1;
    cnt_div_100++;
    if (cnt_div_100 >= 100) {
        cnt_div_100 = 0;
        XcpEvent(XCP_EVENT_10MS);
    }

    static uint32_t cnt_div_1000 = 2;
    cnt_div_1000++;
    if (cnt_div_1000 >= 1000) {
        cnt_div_1000 = 0;
        XcpEvent(XCP_EVENT_100MS);
    }

    static uint32_t cnt_div_10000 = 3;
    cnt_div_10000++;
    if (cnt_div_10000 >= 10000) {
        cnt_div_10000 = 0;
        XcpEvent(XCP_EVENT_1S);
    }
}

/*-------------------------------------------------------------------
 * Global functions
 *-----------------------------------------------------------------*/
void xcp_interface_init(void)
{
	XcpInit();
	rpu_apu_exchange_init();
}

void xcp_irq(void)
{
	rpu_apu_exchange_prepare_write();
    xcp_interface_events_10kHz();

	rpu_apu_exchange_cache_invalidate_before_read();
	rpu_apu_exchange_prepare_read();
    xcp_interface_stim();
	rpu_apu_exchange_cache_flush_after_write();
}

void ApplXcpSend( vuint8 len, const BYTEPTR msg )
{
    uint8_t *msg_with_header_p = (uint8_t *)msg - XCP_HEADER_LEN;
    static uint16_t xcp_package_counter = 0;

    msg_with_header_p[0] = (uint8_t) (len >> 0);
    msg_with_header_p[1] = (uint8_t) (len >> 8);
    msg_with_header_p[2] = (uint8_t) (xcp_package_counter >> 0);
    msg_with_header_p[3] = (uint8_t) (xcp_package_counter >> 8);
    xcp_package_counter++;

    rpu_apu_exchange_writeOCM(len + 4, msg_with_header_p);

    // TODO necessary?
    XcpSendCallBack();
}

MTABYTEPTR ApplXcpGetPointer( vuint8 addr_ext, vuint32 addr )
{
    // Address extension is not used.
    // --> addr already holds the requested memory address
    return (MTABYTEPTR)((size_t)addr);
}

void ApplXcpInterruptDisable( void )
{
    // Do not disable IRQs. Synchronization is ensured by using OS tasks
    //Xil_ExceptionDisable();
}

void ApplXcpInterruptEnable( void )
{
    //Xil_ExceptionEnable();
}

vuint8 ApplXcpSendStall( void )
{
    return (vuint8) 0;
}

XcpDaqTimestampType ApplXcpGetTimestamp(void)
{
	return xcp_timestamp;
}
