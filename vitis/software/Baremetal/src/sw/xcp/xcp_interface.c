/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between UltraZohm project and XCP Basic Driver
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "xcp_config.h"
#include "XCP_Basic/XcpBasic.h"

#include "RPU_APU_exchange.h"
#include "../../include/isr.h"                     /* Interrupt_ISR_freq_factor, UZ_PWM_FREQUENCY */
#include "../../uz/uz_SystemTime/uz_SystemTime.h"  /* uz_SystemTime_GetUptimeInUs */

/*-------------------------------------------------------------------
 * Types
 *-----------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * Configuration
 *-----------------------------------------------------------------*/
/* xcp_irq() is called from ISR_Control, whose rate is the PWM frequency times
 * the trigger factor (e.g. Interrupt_2L_max_min fires twice per PWM period).
 * The XCP event dividers are derived from this so the named events (1MS,
 * 10MS, ...) stay correct when the PWM frequency or the trigger choice
 * changes; they used to be hardcoded for a 10 kHz base.
 * Note: the ISR rate must be an integer multiple of 1 kHz, otherwise the
 * named events drift. */
#define XCP_ISR_FREQ_HZ		((uint32_t)((UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor)))
#define XCP_CYCLES_PER_MS	(XCP_ISR_FREQ_HZ / 1000u)

/* CTO frames (RES/ERR/EV/SERV, PID >= 0xFC) are delivered through the OCM
 * mailbox (see RPU_APU_exchange_impl.c): they persist until the A53
 * acknowledges them, so a delayed A53 IPI can never lose a command response
 * (a lost response = master request timeout = dead XCP session). While the
 * mailbox is occupied, further CTOs wait in this small pending FIFO --
 * request/response is serialized by the master, so more than one entry is
 * only ever used by unsolicited EV/SERV packets. */
#define XCP_CTO_PENDING_DEPTH	4

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
static uint32_t xcp_timestamp;

volatile uint32_t data_first_addr_read_OCM = 0;

static struct {
	uint8_t len;
	uint8_t data[RPU_APU_EXCHANGE_CTO_SLOT_LEN];
} xcp_cto_pending[XCP_CTO_PENDING_DEPTH];
static uint8_t xcp_cto_pending_head = 0;	// next entry to hand to the mailbox
static uint8_t xcp_cto_pending_count = 0;

// Debug counters (inspect via debugger)
volatile uint32_t xcp_cto_pending_dropped = 0;	// pending FIFO full -> CTO lost
volatile uint32_t xcp_cto_sent = 0;				// CTOs handed to the mailbox
volatile uint32_t xcp_in_generations = 0;		// command batches processed

/* Last XCP_IN command-batch generation processed. Each generation is
 * executed exactly once, no matter how many cycles the A53 keeps offering
 * it (rewrite-until-acked; see RPU_APU_exchange_impl.c). */
static uint32_t xcp_in_seq_done = 0;

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

static void xcp_interface_events(void)
{
	/* TODO: Possible optimization: Make sure only 2 or 3 messages are written
	 * to the OCM at a time to reduce IRQ run time in R5 and A53.
	 *  This could be achieved by adding a counter of packages sent in a cycle.
	 *  If this counter reaches 2 an additional xcp events activation is
	 *  delayed to the next cycle.
	 *  This will add jitter to the slower tasks.
	 */

    /* One timestamp per ISR cycle; all events of this cycle share it.
     * Unit matches kXcpDaqTimestampUnit (DAQ_TIMESTAMP_UNIT_1US). */
    xcp_timestamp = (uint32_t)uz_SystemTime_GetUptimeInUs();

    XcpEvent(XCP_EVENT_FAST);

    /* Named events derived from the actual ISR rate. Initial counter values
     * stagger the slower events so they do not all fire in the same cycle
     * (bounds the per-cycle OCM load). */
    static uint32_t cnt_div_1ms = 0;
    cnt_div_1ms++;
    if (cnt_div_1ms >= (1u * XCP_CYCLES_PER_MS)) {
        cnt_div_1ms = 0;

        XcpEvent(XCP_EVENT_1MS);
    }

    static uint32_t cnt_div_10ms = 1;
    cnt_div_10ms++;
    if (cnt_div_10ms >= (10u * XCP_CYCLES_PER_MS)) {
        cnt_div_10ms = 0;
        XcpEvent(XCP_EVENT_10MS);
    }

    static uint32_t cnt_div_100ms = 2;
    cnt_div_100ms++;
    if (cnt_div_100ms >= (100u * XCP_CYCLES_PER_MS)) {
        cnt_div_100ms = 0;
        XcpEvent(XCP_EVENT_100MS);
    }

    static uint32_t cnt_div_1s = 3;
    cnt_div_1s++;
    if (cnt_div_1s >= (1000u * XCP_CYCLES_PER_MS)) {
        cnt_div_1s = 0;
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

/* Hand the oldest pending CTO to the OCM mailbox once the A53 has
 * acknowledged the previous one. Must run between prepare_write() and
 * cache_flush_after_write() (mailbox writes are covered by the seqlock). */
static void xcp_interface_pump_cto(void)
{
	if (xcp_cto_pending_count == 0) {
		return;
	}
	if (! rpu_apu_exchange_cto_mailbox_free()) {
		return;		// previous response not consumed yet; retry next cycle
	}
	if (rpu_apu_exchange_write_cto(xcp_cto_pending[xcp_cto_pending_head].len,
			xcp_cto_pending[xcp_cto_pending_head].data)) {
		xcp_cto_sent++;
	}
	xcp_cto_pending_head = (uint8_t)((xcp_cto_pending_head + 1) % XCP_CTO_PENDING_DEPTH);
	xcp_cto_pending_count--;
}

void xcp_irq(void)
{
	rpu_apu_exchange_prepare_write();
    xcp_interface_events();

	rpu_apu_exchange_cache_invalidate_before_read();

	// Commands: process a batch only when its generation is new. The A53
	// publishes the generation after the chain bytes, so a new value here
	// implies a complete chain; an unchanged value means either nothing new
	// or a batch already executed (never run a generation twice).
	uint32_t in_seq = rpu_apu_exchange_in_seq_read();
	if (in_seq != xcp_in_seq_done) {
		rpu_apu_exchange_prepare_read();
		xcp_interface_stim();
		xcp_in_seq_done = in_seq;
		xcp_in_generations++;
	}
	rpu_apu_exchange_write_in_consumed(xcp_in_seq_done);

	// After stim: a command processed this cycle has queued its response.
	// The ack word was refreshed by cache_invalidate_before_read() above.
	xcp_interface_pump_cto();

	rpu_apu_exchange_cache_flush_after_write();
}

void ApplXcpSend( vuint8 len, const BYTEPTR msg )
{
    uint8_t *msg_with_header_p = (uint8_t *)msg - XCP_HEADER_LEN;
    static uint16_t xcp_package_counter = 0;
    uint8_t framed_len = (uint8_t)(len + XCP_HEADER_LEN);

    msg_with_header_p[0] = (uint8_t) (len >> 0);
    msg_with_header_p[1] = (uint8_t) (len >> 8);
    msg_with_header_p[2] = (uint8_t) (xcp_package_counter >> 0);
    msg_with_header_p[3] = (uint8_t) (xcp_package_counter >> 8);
    xcp_package_counter++;

    /* CTO packets (PID >= 0xFC) take the guaranteed-delivery mailbox path;
     * DAQ DTOs stream through the per-cycle message chain (loss = gap in the
     * measurement, acceptable and counted). */
    if ((len > 0) && (msg[0] >= 0xFC)
        && (framed_len <= RPU_APU_EXCHANGE_CTO_SLOT_LEN)) {
        if (xcp_cto_pending_count < XCP_CTO_PENDING_DEPTH) {
            uint8_t slot = (uint8_t)((xcp_cto_pending_head + xcp_cto_pending_count)
                                     % XCP_CTO_PENDING_DEPTH);
            xcp_cto_pending[slot].len = framed_len;
            memcpy(xcp_cto_pending[slot].data, msg_with_header_p, framed_len);
            xcp_cto_pending_count++;
        } else {
            xcp_cto_pending_dropped++;
        }
    } else {
        rpu_apu_exchange_writeOCM(framed_len, msg_with_header_p);
    }

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
