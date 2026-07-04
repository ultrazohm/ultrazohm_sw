/*----------------------------------------------------------------------------
| ocm_xcp_fifo.c
|   Option Z — OCM FIFO between the R5 (XCPlite engine) and the A53 (gateway).
|   ONE shared implementation; the side is chosen by the ARMR5 define.
|
|   Memory layout of each region (chain of framed messages):
|     [0..3]   message length (u32)
|     [4..]    payload (the XCP-on-Ethernet TL frame: dlc:u16, ctr:u16, packet)
|     [..]     trailing u32 = 0  (end-of-chain marker; overwritten by next msg)
|
|   Adapted from uz_sw_xcp_hedrive_andi RPU_APU_exchange (Jens Wenzl, 2023),
|   hardware-proven incl. the bounds/CTO-reserve fixes from its bottleneck
|   analysis. Renamed to ocm_xcp_fifo_* for this repo. UltraZohm, Apache-2.0.
 ----------------------------------------------------------------------------*/

#include "ocm_xcp_fifo.h"
#include <stddef.h>
#include <string.h>
#include "xil_cache.h"

#ifdef ARMR5
#define OCM_XCP_RPU
#else
#define OCM_XCP_APU
#endif

/* OCM regions (bank 3 upper area — unused by JavaScope, which is off under XCP).
 * XCP_OUT (R5 -> A53): DAQ + command responses. XCP_IN (A53 -> R5): commands. */
#define XCP_OUT_ADDR 0xFFFFE000u
#define XCP_OUT_LEN  7680u
#define XCP_IN_ADDR  0xFFFFC000u
#define XCP_IN_LEN   1024u /* >= several max-size command records (4+252+4 each) */

/* R5 write side reserves the tail of XCP_OUT for CTO frames (XCP PID >= 0xFC:
 * RES/ERR/EV/SERV) so a DAQ burst can never starve a command response.
 * Must hold at least one max-size CRM record: 4 + (4+248) + 4 = 260 bytes. */
#ifdef OCM_XCP_RPU
#define XCP_WRITE_CTO_RESERVE 512u
#else
#define XCP_WRITE_CTO_RESERVE 0u
#endif

#define XCP_FRAME_PID_OFFSET 4u   /* [0..1] len, [2..3] ctr, [4] = XCP PID */
#define XCP_FRAME_PID_CTO_MIN 0xFCu

static volatile size_t addr_w = 0;
static volatile size_t addr_w_start = 0;
static volatile size_t addr_w_end = 0;
static volatile size_t addr_r = 0;
static volatile size_t addr_r_end = 0;

volatile uint32_t ocm_xcp_w_dropped = 0;   /* write region full -> dropped     */
volatile uint32_t ocm_xcp_r_overrun = 0;   /* read chain corrupt / past region */

void ocm_xcp_fifo_init(void) {
    /* The core that READS a region initialises it. */
#ifdef OCM_XCP_RPU
    *(volatile uint32_t *)XCP_IN_ADDR = 0u;
    Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_LEN);
#else
    *(volatile uint32_t *)XCP_OUT_ADDR = 0u;
    Xil_DCacheFlushRange(XCP_OUT_ADDR, XCP_OUT_LEN);
#endif
}

void ocm_xcp_fifo_cache_invalidate_before_read(void) {
#ifdef OCM_XCP_RPU
    Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_LEN);
#endif
    /* APU: lazy per-message invalidate inside ocm_xcp_fifo_read(). */
}

void ocm_xcp_fifo_cache_flush_after_write(void) {
    /* Flush only the bytes written this cycle: start..(addr_w + terminator). */
    Xil_DCacheFlushRange(addr_w_start, (addr_w + 4u) - addr_w_start);
}

/* R5 only: zero the XCP_IN chain head after consuming it, so that a delayed
 * A53 IPI (which normally rewinds XCP_IN) cannot make the R5 re-read and
 * RE-EXECUTE the same commands next cycle. Race with a concurrent A53 write is
 * benign: at worst one command chain is lost and the master retries. */
void ocm_xcp_fifo_consume_read(void) {
#ifdef OCM_XCP_RPU
    *(volatile uint32_t *)XCP_IN_ADDR = 0u;
    Xil_DCacheFlushRange(XCP_IN_ADDR, 4u);
#endif
}

void ocm_xcp_fifo_prepare_read(void) {
#ifdef OCM_XCP_RPU
    addr_r = XCP_IN_ADDR;
    addr_r_end = XCP_IN_ADDR + XCP_IN_LEN;
#else
    addr_r = XCP_OUT_ADDR;
    addr_r_end = XCP_OUT_ADDR + XCP_OUT_LEN;
#endif
}

void ocm_xcp_fifo_prepare_write(void) {
#ifdef OCM_XCP_RPU
    addr_w = XCP_OUT_ADDR;
    addr_w_start = XCP_OUT_ADDR;
    addr_w_end = XCP_OUT_ADDR + XCP_OUT_LEN;
#else
    addr_w = XCP_IN_ADDR;
    addr_w_start = XCP_IN_ADDR;
    addr_w_end = XCP_IN_ADDR + XCP_IN_LEN;
#endif
    *(volatile uint32_t *)addr_w = 0u;
}

int ocm_xcp_fifo_write(uint8_t len, const uint8_t *data) {
    uint8_t *dst_p = (uint8_t *)(addr_w);
    size_t limit = addr_w_end;

    /* DAQ (DTO) frames must leave the CTO reserve free; CTO frames may use it.
     * Frames too short to carry a PID are treated as DAQ. */
    if ((len <= XCP_FRAME_PID_OFFSET) || (data[XCP_FRAME_PID_OFFSET] < XCP_FRAME_PID_CTO_MIN)) {
        limit -= XCP_WRITE_CTO_RESERVE;
    }

    /* Need 4 (len) + len (payload) + 4 (terminator). */
    if (((size_t)dst_p + 4u + (size_t)len + 4u) > limit) {
        ocm_xcp_w_dropped++;
        return 0;
    }

    *(volatile uint32_t *)dst_p = len;
    dst_p += 4;
    memcpy(dst_p, data, len);
    dst_p += len;
    *(volatile uint32_t *)dst_p = 0u; /* new end-of-chain marker */

    addr_w = (size_t)dst_p;
    return 1;
}

int ocm_xcp_fifo_read(uint8_t *len, uint8_t **data_p) {
    uint8_t *src_p = (uint8_t *)(addr_r);
    uint32_t msg_len;

    if (((size_t)src_p + 4u) > addr_r_end) {
        ocm_xcp_r_overrun++;
        return 0;
    }
#ifdef OCM_XCP_APU
    Xil_DCacheInvalidateRange((size_t)src_p, 4u);
#endif
    msg_len = *(volatile uint32_t *)src_p;

    if (msg_len == 0u) {
        return 0; /* end of chain */
    }
    if ((msg_len > 0xFFu) || (((size_t)src_p + 4u + msg_len) > addr_r_end)) {
        ocm_xcp_r_overrun++;
        return 0;
    }
#ifdef OCM_XCP_APU
    Xil_DCacheInvalidateRange((size_t)src_p + 4u, msg_len);
#endif

    *len = (uint8_t)msg_len;
    src_p += 4;
    *data_p = src_p;
    src_p += msg_len;
    addr_r = (size_t)src_p;
    return 1;
}
