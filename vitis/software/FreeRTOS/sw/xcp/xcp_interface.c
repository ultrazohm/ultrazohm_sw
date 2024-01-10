/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between UltraZohm project and XCP Basic Driver
 */

#include <stdint.h>

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

/*-------------------------------------------------------------------
 * Local functions
 *-----------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * Global functions
 *-----------------------------------------------------------------*/
void xcp_events_10kHz(void)
{
	rpu_apu_exchange_reset(rapu_exchange_write_rpu);

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

typedef struct {
	struct {
		uint8_t saw_90B[90];
		uint32_t ticks_run;
		uint8_t saw;
	} meas;
	struct {
		uint8_t enable;
	} stim;
} xcp_data_t;
static xcp_data_t xcp_data = {0};

void xcp_stim(void)
{
	rpu_apu_exchange_reset(rapu_exchange_read_rpu);

	while (1) {
		uint8_t *data;
		uint8_t len;
		if (! rpu_apu_exchange_readOCM(rapu_exchange_read_rpu, &len, &data)) {
			// Could not read a message from OCM
			break;
		}

		XcpCommand((uint32_t *)(data + XCP_HEADER_LEN));
	}
}

void dummy_task(void)
{
//	static int div_cnt = 0;
//	if (div_cnt++ < 100) {
//		return;
//	}
//	div_cnt = 0;

	static int init_once = 1;
	if (init_once) {
		init_once = 0;
		for (int i = 0; i < sizeof(xcp_data.meas.saw_90B); i++) {
			xcp_data.meas.saw_90B[i] = i;
		}
	}

	if (xcp_data.stim.enable) {
		xcp_data.meas.saw += 1;
		for (int i = 0; i < sizeof(xcp_data.meas.saw_90B); i++) {
			xcp_data.meas.saw_90B[i] += 1;
		}
	}

	xcp_events_10kHz();
	xcp_stim();
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

    rpu_apu_exchange_writeOCM(rapu_exchange_write_rpu, len + 4, msg_with_header_p);

    // TODO necessary?
    XcpSendCallBack();
}

MTABYTEPTR ApplXcpGetPointer( vuint8 addr_ext, vuint32 addr )
{
    // Address extension is not used.
    // --> addr already holds the requested memory address
    return (MTABYTEPTR)((uint64_t)addr);
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
