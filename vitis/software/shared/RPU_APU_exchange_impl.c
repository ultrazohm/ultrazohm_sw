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
#include "RPU_APU_exchange.h"

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
 *
 * The R5 rewrites XCP_OUT from scratch every control-ISR cycle (20 kHz) and
 * the A53 reads it from its IPI ISR -- there is no flow control between the
 * two. Whenever the A53 is late (interrupt latency under network load), the
 * R5 overwrites the region mid-read. Two mechanisms make that safe:
 *
 * 1. A seqlock on XCP_OUT: the R5 increments cycle_seq to an ODD value
 *    (flushed) before touching the region and to an EVEN value (flushed
 *    last, after the payload flush) when the cycle's content is complete.
 *    The A53 samples the sequence before and after reading; a mismatch or an
 *    odd value means the read raced the writer and everything read this IPI
 *    is discarded. Torn frames can therefore never reach the network.
 *    Discarded/overwritten DAQ frames are acceptable (a gap in the
 *    measurement) and are counted.
 *
 * 2. A CTO mailbox with an acknowledge: command responses (RES/ERR/EV/SERV)
 *    must NEVER be lost -- a lost response kills the XCP session (master
 *    request timeout). The response is parked in a dedicated slot with its
 *    own sequence number and stays there, surviving any number of cycle
 *    rewrites, until the A53 acknowledges the sequence number through the
 *    XCP_IN header. Delivery is exactly-once: the A53 forwards a mailbox
 *    frame only when its sequence changes.
 *
 * 3. A generation handshake on XCP_IN (commands, A53 -> R5): the A53 keeps
 *    the current command batch IN PLACE and rewrites it every IPI cycle,
 *    publishing a generation number (in_seq) AFTER the chain bytes. The R5
 *    processes a generation exactly once (in_seq != last processed) and
 *    acknowledges it through in_consumed_seq in the XCP_OUT header; only
 *    then does the A53 build the next batch. A command can therefore never
 *    be lost to a missed cycle (the failure observed as CANape
 *    "Timeout: Keine Response" with clean wire data, T8 pcap analysis)
 *    nor executed twice (generation dedup on the R5).
 *
 * XCP_OUT layout (R5 writes, A53 reads):
 *   +0                   u32 cycle_seq   seqlock (odd = write in progress)
 *   +4                   u32 cto_seq     mailbox sequence, 0 = never used
 *   +8                   u32 cto_len     framed length of the mailbox message
 *   +12                  u8  cto_frame[XCP_CTO_SLOT_LEN]
 *   +12+SLOT             u32 in_consumed_seq  last XCP_IN generation processed
 *   +XCP_OUT_HDR_LEN     message chain (see below)
 *
 * XCP_IN layout (A53 writes, R5 reads):
 *   +0                   u32 cto_ack_seq last mailbox sequence consumed
 *   +4                   u32 in_seq      command-batch generation, 0 = none;
 *                                        published AFTER the chain bytes
 *   +XCP_IN_HDR_LEN      message chain
 *
 * Message chain format (unchanged):
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

/* Header sizes in front of the message chains: one A53 cache line (64 B)
 * each, so header words and chain bytes never share a cache line. That
 * separation is what makes the publish-after-payload flush order real: the
 * chain lines can be flushed completely before the line carrying the
 * sequence/generation word goes out. (XCP_OUT: seqlock word + CTO mailbox +
 * in_consumed ack in line 0. XCP_IN: cto_ack + in_seq in line 0.) */
#define XCP_OUT_HDR_LEN				64
#define XCP_IN_HDR_LEN				64

/* Mailbox frame slot: a framed CTO message is 4 (transport header) +
 * kXcpMaxCTO (32) = 36 bytes; the slot must also fit in the header line. */
#define XCP_CTO_SLOT_LEN			RPU_APU_EXCHANGE_CTO_SLOT_LEN
#if (12 + XCP_CTO_SLOT_LEN) > 64
#error "CTO mailbox must fit into the 64-byte XCP_OUT header line"
#endif

#define XCP_OUT_CHAIN_ADDR			(XCP_OUT_ADDR + XCP_OUT_HDR_LEN)
#define XCP_IN_CHAIN_ADDR			(XCP_IN_ADDR + XCP_IN_HDR_LEN)

#define XCP_OUT_CYCLE_SEQ_P			((volatile uint32_t *)(XCP_OUT_ADDR + 0u))
#define XCP_OUT_CTO_SEQ_P			((volatile uint32_t *)(XCP_OUT_ADDR + 4u))
#define XCP_OUT_CTO_LEN_P			((volatile uint32_t *)(XCP_OUT_ADDR + 8u))
#define XCP_OUT_CTO_FRAME_P			((volatile uint8_t *)(XCP_OUT_ADDR + 12u))
#define XCP_OUT_IN_CONSUMED_P		((volatile uint32_t *)(XCP_OUT_ADDR + 12u + XCP_CTO_SLOT_LEN))
#define XCP_IN_CTO_ACK_P			((volatile uint32_t *)(XCP_IN_ADDR + 0u))
#define XCP_IN_SEQ_P				((volatile uint32_t *)(XCP_IN_ADDR + 4u))

#if (12 + XCP_CTO_SLOT_LEN + 4) > 64
#error "XCP_OUT header fields must fit into the 64-byte header line"
#endif
#if (XCP_IN_LEN - XCP_IN_HDR_LEN) != RPU_APU_EXCHANGE_IN_CHAIN_LEN
#error "RPU_APU_EXCHANGE_IN_CHAIN_LEN out of sync with the XCP_IN layout"
#endif

/*
 * RPU write side only: the last bytes of XCP_OUT are reserved for CTO frames
 * (XCP PID >= 0xFC: RES/ERR/EV/SERV). A DAQ burst that fills the region must
 * never squeeze out a command response -- the master times out on a lost
 * response, while a dropped DAQ frame is only a gap in the measurement.
 * (With the CTO mailbox, responses normally bypass the chain entirely; the
 * reserve stays as a second line of defense for oversized CTOs.)
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
static volatile size_t addr_w_start = 0;	// begin of the flushed write range
static volatile size_t addr_w_end = 0;		// exclusive end of the write region
static volatile size_t addr_r = 0;
static volatile size_t addr_r_end = 0;		// exclusive end of the read region

#ifdef RPU
/* Writer-side shadows of the OCM sequence words (the R5 owns them and never
 * needs to read them back). */
static uint32_t cycle_seq_shadow = 0;
static uint32_t cto_seq_shadow = 0;
#endif

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
	*XCP_IN_CTO_ACK_P = 0;
	*XCP_IN_SEQ_P = 0;
	*(uint32_t *)XCP_IN_CHAIN_ADDR = 0;
	Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_LEN);
#endif
#ifdef APU
	*XCP_OUT_CYCLE_SEQ_P = 0;
	*XCP_OUT_CTO_SEQ_P = 0;
	*XCP_OUT_CTO_LEN_P = 0;
	*XCP_OUT_IN_CONSUMED_P = 0;
	*(uint32_t *)XCP_OUT_CHAIN_ADDR = 0;
	Xil_DCacheFlushRange(XCP_OUT_ADDR, XCP_OUT_LEN);
#endif
}

void rpu_apu_exchange_cache_invalidate_before_read(void)
{
#ifdef RPU
	// XCP_IN is small: flush it in one go. (The R5 never dirties these
	// lines, so flush = clean + invalidate behaves as an invalidate.)
	// Covers the cto_ack word read by rpu_apu_exchange_cto_mailbox_free().
	Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_LEN);
#endif
#ifdef APU
	// Intentionally empty: XCP_OUT is several KB and this runs in the IPI
	// ISR at the control rate. readOCM() invalidates lazily, covering only
	// the lines that actually hold messages; the header line is invalidated
	// by rpu_apu_exchange_out_seq_read().
#endif
}

void rpu_apu_exchange_cache_flush_after_write(void)
{
#ifdef RPU
	// Publish order matters: payload first, sequence word last. A reader
	// that sees the new (even) cycle_seq must also see the chain content it
	// describes; flushing the header before the chain would break that.
	Xil_DCacheFlushRange(addr_w_start, (addr_w + 4u) - addr_w_start);
	cycle_seq_shadow++;		// even: cycle content is complete
	*XCP_OUT_CYCLE_SEQ_P = cycle_seq_shadow;
	Xil_DCacheFlushRange(XCP_OUT_ADDR, XCP_OUT_HDR_LEN);
#endif
#ifdef APU
	// Publish order matters here too: chain bytes first, header (with the
	// in_seq generation word) last. The R5 accepting a new generation must
	// imply the chain content it describes is complete in the OCM.
	Xil_DCacheFlushRange(addr_w_start, (addr_w + 4u) - addr_w_start);
	Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_HDR_LEN);
#endif
}

void rpu_apu_exchange_prepare_read(void)
{
#ifdef RPU
	addr_r = XCP_IN_CHAIN_ADDR;
	addr_r_end = XCP_IN_ADDR + XCP_IN_LEN;
#endif
#ifdef APU
	addr_r = XCP_OUT_CHAIN_ADDR;
	addr_r_end = XCP_OUT_ADDR + XCP_OUT_LEN;
#endif
}

void rpu_apu_exchange_prepare_write(void)
{
#ifdef RPU
	// Seqlock write-begin: publish an ODD sequence before touching the
	// region, so a concurrently reading A53 knows the content is in flux.
	// (Only the first header line needs to reach the OCM here.)
	cycle_seq_shadow++;
	*XCP_OUT_CYCLE_SEQ_P = cycle_seq_shadow;
	Xil_DCacheFlushRange(XCP_OUT_ADDR, 4u);

	addr_w = XCP_OUT_CHAIN_ADDR;
	addr_w_start = XCP_OUT_CHAIN_ADDR;	// header is flushed separately (last)
	addr_w_end = XCP_OUT_ADDR + XCP_OUT_LEN;
#endif
#ifdef APU
	addr_w = XCP_IN_CHAIN_ADDR;
	addr_w_start = XCP_IN_CHAIN_ADDR;	// header is flushed separately (last)
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

/*-------------------------------------------------------------------
 * Seqlock accessors (APU read side)
 *-----------------------------------------------------------------*/
#ifdef APU
uint32_t rpu_apu_exchange_out_seq_read(void)
{
	// Invalidating the header start refreshes the whole 64-byte header line
	// (cycle_seq, cto_seq, cto_len and the mailbox frame slot).
	Xil_DCacheInvalidateRange(XCP_OUT_ADDR, 4u);
	return *XCP_OUT_CYCLE_SEQ_P;
}

int rpu_apu_exchange_out_seq_unchanged(uint32_t seq_begin)
{
	Xil_DCacheInvalidateRange(XCP_OUT_ADDR, 4u);
	return (*XCP_OUT_CYCLE_SEQ_P == seq_begin);
}

/* Copy the mailbox frame out of the header. Returns 1 if the slot holds a
 * plausible frame (nonzero seq, valid length), 0 otherwise. Must be called
 * between out_seq_read() and out_seq_unchanged(); the copy is only
 * trustworthy if the surrounding seqlock check passes. */
int rpu_apu_exchange_read_cto(uint8_t *len, uint8_t *dst, uint32_t *seq)
{
	uint32_t s = *XCP_OUT_CTO_SEQ_P;
	uint32_t l = *XCP_OUT_CTO_LEN_P;

	if ((s == 0u) || (l == 0u) || (l > XCP_CTO_SLOT_LEN)) {
		return 0;
	}
	memcpy(dst, (const void *)XCP_OUT_CTO_FRAME_P, l);
	*len = (uint8_t)l;
	*seq = s;
	return 1;
}

/* Publish the last consumed mailbox sequence. Written into the XCP_IN header
 * during the write phase; reaches the OCM with cache_flush_after_write(). */
void rpu_apu_exchange_write_cto_ack(uint32_t seq)
{
	*XCP_IN_CTO_ACK_P = seq;
}

/* Publish the command-batch generation. Written during the write phase; the
 * split flush in cache_flush_after_write() guarantees the chain bytes reach
 * the OCM before this word does (publish-after-payload). */
void rpu_apu_exchange_publish_in_seq(uint32_t seq)
{
	*XCP_IN_SEQ_P = seq;
}

/* Last XCP_IN generation the R5 has processed. Lives in the XCP_OUT header:
 * only valid between out_seq_read() and a passing out_seq_unchanged(). */
uint32_t rpu_apu_exchange_read_in_consumed(void)
{
	return *XCP_OUT_IN_CONSUMED_P;
}
#endif /* APU */

/*-------------------------------------------------------------------
 * CTO mailbox (RPU write side)
 *-----------------------------------------------------------------*/
#ifdef RPU
/* The mailbox is free once the A53 has acknowledged the last sequence.
 * Relies on cache_invalidate_before_read() having refreshed XCP_IN this
 * cycle. */
int rpu_apu_exchange_cto_mailbox_free(void)
{
	return (*XCP_IN_CTO_ACK_P == cto_seq_shadow);
}

/* Park one framed CTO message in the mailbox. Call only while the seqlock
 * is held (between prepare_write() and cache_flush_after_write()) and only
 * when the mailbox is free. The content persists across cycle rewrites until
 * acknowledged, so a response can never be lost to an overwritten cycle. */
int rpu_apu_exchange_write_cto(uint8_t len, const uint8_t *data)
{
	if ((len == 0u) || (len > XCP_CTO_SLOT_LEN)) {
		return 0;
	}
	memcpy((void *)XCP_OUT_CTO_FRAME_P, data, len);
	*XCP_OUT_CTO_LEN_P = len;
	cto_seq_shadow++;
	if (cto_seq_shadow == 0u) {
		cto_seq_shadow = 1u;	// 0 is reserved for "never used"
	}
	*XCP_OUT_CTO_SEQ_P = cto_seq_shadow;
	// Published by the header flush in cache_flush_after_write(), together
	// with the even cycle_seq -- the A53 only trusts it under the seqlock.
	return 1;
}

/* Current command-batch generation published by the A53. Relies on
 * cache_invalidate_before_read() having refreshed XCP_IN this cycle. The
 * A53 publishes the generation only after the chain bytes are in the OCM,
 * so a new value here implies a complete, readable command chain. */
uint32_t rpu_apu_exchange_in_seq_read(void)
{
	return *XCP_IN_SEQ_P;
}

/* Acknowledge a processed command-batch generation. Lands in the XCP_OUT
 * header, published by the header flush in cache_flush_after_write(). */
void rpu_apu_exchange_write_in_consumed(uint32_t seq)
{
	*XCP_OUT_IN_CONSUMED_P = seq;
}
#endif /* RPU */
