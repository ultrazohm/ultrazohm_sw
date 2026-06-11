/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Data exchange between RPU and APU
 *
 * Single shared implementation for both processors (R5 Baremetal and A53
 * FreeRTOS): the OCM layout below is the protocol between the two cores.
 * Each application compiles this file through a thin stub
 * (.../sw/xcp/RPU_APU_exchange.c) that #includes it; the per-side behaviour
 * is selected by the ARMR5 compiler define. When the regions change, rebuild
 * BOTH applications.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "xil_cache.h"

// A processor specific define like "ARMR5" is only available on R5.
#ifdef ARMR5
	#define RPU
#else
	#define APU
#endif

#if (!defined(APU) && !defined(RPU)) || (defined(APU) && defined(RPU))
	#error "Define either RPU or APU"
#endif

/*
 * Memory exchange via OCM
 * Memory layout:
 * Byte [0..3]: package len
 * Byte [4..(3 + len)]: payload
 * Byte [(4 + len)..(7 + len)]: 0. Indicator for OCM reader, this is end of
 *          messages. (If a package follows it will be overwritten with its
 *          actual length)
 */

/*-------------------------------------------------------------------
 * Configuration
 *-----------------------------------------------------------------*/
/*
 * OCM bank3 is reserved for javascope: Address: 0xFFFF0000, len 0x10000 (= 65K).
 * Place XCP data behind the javascope memory in the same bank3; the upper
 * region is otherwise unused by both processors.
 *
 * XCP_OUT (R5 -> A53: DAQ data + command responses): 7680 bytes, roughly 100
 * DTO frames per exchange cycle (was 512 bytes ~= 6 frames, which capped the
 * DAQ throughput). The end address 0xFFFFFE00 is deliberately below the
 * 32-bit wrap: 0xFFFFE000 + 0x2000 would overflow size_t on the R5.
 *
 * XCP_IN (A53 -> R5: commands): commands trickle in one request at a time,
 * 256 bytes is plenty.
 */
#define XCP_OUT_ADDR				0xFFFFE000
#define XCP_OUT_LEN					7680
#define XCP_IN_ADDR 				0xFFFFC000
#define XCP_IN_LEN					256

/*
 * RPU write side only: the last bytes of XCP_OUT are reserved for CTO frames
 * (XCP PID >= 0xFC: RES/ERR/EV/SERV). A DAQ burst that fills the region must
 * never squeeze out a command response -- the master times out on a lost
 * response, while a dropped DAQ frame is only a gap in the measurement.
 * No reserve on the APU write side (XCP_IN): there the payload starts with a
 * command code (0xC0..0xFF), not a response PID, and commands must never be
 * starved.
 */
#ifdef RPU
	#define XCP_WRITE_CTO_RESERVE	256
#else
	#define XCP_WRITE_CTO_RESERVE	0
#endif

/* Offset of the XCP PID inside a framed message: [0..1] len, [2..3] ctr,
 * [4] = XCP packet id. */
#define XCP_FRAME_PID_OFFSET		4
#define XCP_FRAME_PID_CTO_MIN		0xFC

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
static volatile size_t addr_w = 0;
static volatile size_t addr_w_start = 0;	// begin of the current write region
static volatile size_t addr_w_end = 0;		// exclusive end of the write region
static volatile size_t addr_r = 0;
static volatile size_t addr_r_end = 0;		// exclusive end of the read region

// Statistics / debug counters (inspect via debugger)
static volatile uint32_t cnt_msg_ocm_w = 0;
static volatile uint32_t cnt_msg_ocm_r = 0;
volatile uint32_t cnt_msg_ocm_w_dropped = 0;	// write region full -> message dropped
volatile uint32_t cnt_msg_ocm_r_overrun = 0;	// read chain corrupt or past region end

/*-------------------------------------------------------------------
 * Global functions
 *-----------------------------------------------------------------*/
void rpu_apu_exchange_init(void)
{
	// The CPU which reads the OCM area initializes it
#ifdef RPU
    *(uint32_t *)XCP_IN_ADDR = 0;
	Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_LEN);
#endif
#ifdef APU
    *(uint32_t *)XCP_OUT_ADDR = 0;
	Xil_DCacheFlushRange(XCP_OUT_ADDR, XCP_OUT_LEN);
#endif
}

void rpu_apu_exchange_cache_invalidate_before_read(void)
{
#ifdef RPU
	// XCP_IN is small: flush it in one go. (The R5 never dirties these
	// lines, so flush = clean + invalidate behaves as an invalidate.)
	Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_LEN);
#endif
#ifdef APU
	// Intentionally empty: XCP_OUT is several KB and this runs in the IPI
	// ISR at the control rate. readOCM() invalidates lazily, covering only
	// the lines that actually hold messages.
#endif
}

void rpu_apu_exchange_cache_flush_after_write(void)
{
	// Flush only the bytes actually written this cycle: region start up to
	// and including the 4-byte end-of-messages terminator. (Flushing the
	// whole region every cycle would burn ISR time for nothing.)
	Xil_DCacheFlushRange(addr_w_start, (addr_w + 4u) - addr_w_start);
}

void rpu_apu_exchange_prepare_read(void)
{
#ifdef RPU
	addr_r = XCP_IN_ADDR;
	addr_r_end = XCP_IN_ADDR + XCP_IN_LEN;
#endif
#ifdef APU
	addr_r = XCP_OUT_ADDR;
	addr_r_end = XCP_OUT_ADDR + XCP_OUT_LEN;
#endif
}

void rpu_apu_exchange_prepare_write(void)
{
#ifdef RPU
	addr_w = XCP_OUT_ADDR;
	addr_w_start = XCP_OUT_ADDR;
	addr_w_end = XCP_OUT_ADDR + XCP_OUT_LEN;
#endif
#ifdef APU
	addr_w = XCP_IN_ADDR;
	addr_w_start = XCP_IN_ADDR;
	addr_w_end = XCP_IN_ADDR + XCP_IN_LEN;
#endif
    *(uint32_t *)addr_w = 0;
}

int rpu_apu_exchange_writeOCM(uint8_t len, uint8_t *data)
{
	uint8_t *dst_p = (uint8_t *)(addr_w);
	size_t limit = addr_w_end;

	// DAQ (DTO) frames must leave the CTO reserve untouched; CTO frames
	// (command responses etc.) may use it. Frames too short to carry a PID
	// are treated as DAQ. Reserve is 0 on the APU side (see define above).
	if ((len <= XCP_FRAME_PID_OFFSET)
	    || (data[XCP_FRAME_PID_OFFSET] < XCP_FRAME_PID_CTO_MIN)) {
		limit -= XCP_WRITE_CTO_RESERVE;
	}

	// Bounds check: a message needs 4 (len) + len (payload) + 4 (terminating
	// 0). Without this, writing more messages than the region holds silently
	// overruns the OCM area.
	if (((size_t)dst_p + 4u + (size_t)len + 4u) > limit) {
		cnt_msg_ocm_w_dropped++;
		return 0;	// no space; caller drops or retries next cycle
	}

	// Write package len
    *(uint32_t *)dst_p = len;
    dst_p += 4;

    // Write payload
    memcpy(dst_p, data, len);
    dst_p += len;

    // Set next len to 0
    *(uint32_t *)dst_p = 0;

    // Write current OCM write address for the next call/entry
	addr_w = (size_t)dst_p;

    cnt_msg_ocm_w++;
    return 1;
}

int rpu_apu_exchange_readOCM(uint8_t *len, uint8_t **data_p)
{
	uint8_t *src_p = (uint8_t *)(addr_r);
	uint32_t msg_len;

	// The 4-byte length field itself must lie inside the region.
	if (((size_t)src_p + 4u) > addr_r_end) {
		cnt_msg_ocm_r_overrun++;
		return 0;
	}

#ifdef APU
	// Lazy invalidate (cf. cache_invalidate_before_read): the A53 never
	// writes XCP_OUT, so these lines are never dirty and invalidating only
	// the message actually being read is safe and cheap.
	Xil_DCacheInvalidateRange((size_t)src_p, 4u);
#endif

	msg_len = *(uint32_t *)src_p;

	// End of the message chain
	if (msg_len == 0u) {
		return 0;
	}

	// Stop on a corrupt length or a message reaching past the region end.
	// Without this a garbage length lets the reader walk arbitrary memory
	// (in ISR context on the A53).
	if ((msg_len > 0xFFu) || (((size_t)src_p + 4u + msg_len) > addr_r_end)) {
		cnt_msg_ocm_r_overrun++;
		return 0;
	}

#ifdef APU
	Xil_DCacheInvalidateRange((size_t)src_p + 4u, msg_len);
#endif

	*len = (uint8_t)msg_len;
	src_p += 4;

	// Set data_p to start of message
	*data_p = (uint8_t *)src_p;
	src_p += msg_len;

    // Write current OCM read address for the next call/entry
	addr_r = (size_t)src_p;

	cnt_msg_ocm_r++;

	return 1;
}
