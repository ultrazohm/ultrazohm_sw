/*----------------------------------------------------------------------------
| ocm_xcp_ring.h
|   Option Z: the OCM exchange between the R5 (XCPlite engine) and the A53
|   (UDP gateway), three rings of uz_ocm_ring.h in OCM banks 2 and 3:
|
|     DAQ  R5 control ISR -> A53   XCP DTOs, written by the engine in place
|     RSP  R5 main loop   -> A53   command responses (CRM) and events
|     CMD  A53 rx task    -> R5    command datagrams from the master
|
|   DAQ and RSP records are XCP-on-Ethernet transport layer messages as
|   they go on the wire ([dlc][ctr][packet], header = {len = dlc, aux =
|   ctr}); the A53 packs them into datagrams and stamps the transport
|   counter in transmission order. A CMD record is one received UDP
|   datagram (one or more [dlc][ctr][packet] frames).
|
|   Map (bank 2 + 3 = 0xFFFE0000 .. 0xFFFFFFFF, see APU_RPU_shared.h):
|     0xFFFE0000  DAQ ring data, 112 KB
|     0xFFFFC000  A53 gateway counters (OCM_XCP_GW_DIAG_*), A53 writes
|     0xFFFFC080  DAQ position lines: producer (R5), consumer (A53)
|     0xFFFFC100  RSP position lines: producer (R5), consumer (A53)
|     0xFFFFC180  CMD position lines: producer (A53), consumer (R5)
|     0xFFFFC200  RSP ring data, 4 KB
|     0xFFFFD200  CMD ring data, 4 KB
|     0xFFFFE200  free up to 0xFFFFFEFF (0xFFFFFF00: the engine's EPK address)
|   JavaScope uses 0xFFFF0000 instead; the two logging paths are compiled
|   exclusively (uz_logging_path.h).
|
|   Replaces ocm_xcp_fifo.c/.h (XCP_OUT chain with seqlock, CTO mailbox,
|   command generations and chain acknowledge): every record is written
|   once and read once, so none of those handshakes is needed.
|   UltraZohm.
 ----------------------------------------------------------------------------*/
#ifndef OCM_XCP_RING_H_
#define OCM_XCP_RING_H_

#include <stdint.h>
#include "uz_ocm_ring.h"

#define OCM_XCP_DAQ_DATA_ADDR  0xFFFE0000u
#define OCM_XCP_DAQ_DATA_LEN   0x1C000u   /* 112 KB: ~3 ms at 900 B per 25 us */
#define OCM_XCP_GW_DIAG_BASE   0xFFFFC000u
#define OCM_XCP_DAQ_PROD_ADDR  0xFFFFC080u
#define OCM_XCP_DAQ_CONS_ADDR  0xFFFFC0C0u
#define OCM_XCP_RSP_PROD_ADDR  0xFFFFC100u
#define OCM_XCP_RSP_CONS_ADDR  0xFFFFC140u
#define OCM_XCP_CMD_PROD_ADDR  0xFFFFC180u
#define OCM_XCP_CMD_CONS_ADDR  0xFFFFC1C0u
#define OCM_XCP_RSP_DATA_ADDR  0xFFFFC200u
#define OCM_XCP_RSP_DATA_LEN   0x1000u
#define OCM_XCP_CMD_DATA_ADDR  0xFFFFD200u
#define OCM_XCP_CMD_DATA_LEN   0x1000u

#if (OCM_XCP_DAQ_DATA_ADDR + OCM_XCP_DAQ_DATA_LEN) > OCM_XCP_GW_DIAG_BASE
#error "DAQ ring overlaps the control lines"
#endif
#if (OCM_XCP_CMD_DATA_ADDR + OCM_XCP_CMD_DATA_LEN) > 0xFFFFFF00u
#error "CMD ring reaches the EPK address"
#endif

/* Largest record payloads. A DTO is at most XCPTL_MAX_DTO_SIZE (1024,
 * xcplib_r5_cfg.h), a response XCPTL_MAX_CTO_SIZE (248). A command record
 * is a whole datagram: 1400, the size of the DAQ datagrams the gateway
 * sends (XCP_GW_BATCH_BUF_SIZE), below a 1500-byte MTU. */
#define OCM_XCP_DAQ_MAX_LEN    1024u
#define OCM_XCP_RSP_MAX_LEN    248u
#define OCM_XCP_CMD_MAX_LEN    1400u

/* Describe the three rings (local state of the calling core). */
static inline void ocm_xcp_ring_setup(uz_ocm_ring_t *daq, uz_ocm_ring_t *rsp, uz_ocm_ring_t *cmd) {
    uz_ocm_ring_setup(daq, (void *)(uintptr_t)OCM_XCP_DAQ_DATA_ADDR, OCM_XCP_DAQ_DATA_LEN, OCM_XCP_DAQ_MAX_LEN,
                      (void *)(uintptr_t)OCM_XCP_DAQ_PROD_ADDR, (void *)(uintptr_t)OCM_XCP_DAQ_CONS_ADDR);
    uz_ocm_ring_setup(rsp, (void *)(uintptr_t)OCM_XCP_RSP_DATA_ADDR, OCM_XCP_RSP_DATA_LEN, OCM_XCP_RSP_MAX_LEN,
                      (void *)(uintptr_t)OCM_XCP_RSP_PROD_ADDR, (void *)(uintptr_t)OCM_XCP_RSP_CONS_ADDR);
    uz_ocm_ring_setup(cmd, (void *)(uintptr_t)OCM_XCP_CMD_DATA_ADDR, OCM_XCP_CMD_DATA_LEN, OCM_XCP_CMD_MAX_LEN,
                      (void *)(uintptr_t)OCM_XCP_CMD_PROD_ADDR, (void *)(uintptr_t)OCM_XCP_CMD_CONS_ADDR);
}

/* A53 gateway counters, written by the A53 at every IPI and cleaned with
 * one range operation; the XCP master reads them by absolute address
 * through the R5 engine (OCM is in its allow-list). Fixed addresses,
 * independent of any build: mirrored in CANape/UZ_XCP/uz.A2L (xcp_gw_*),
 * tools/xcp_test/gen_a2l.py and tools/xcp_test/xcp_poll.py - keep in sync.
 * Words 0 and 1 are reserved. */
#define OCM_XCP_GW_DIAG_ADDR  (OCM_XCP_GW_DIAG_BASE + 8u)
#define OCM_XCP_GW_DIAG_COUNT 27u
enum ocm_xcp_gw_diag_slot {
    OCM_XCP_DIAG_GW_RING_BAD = 0,            /* DAQ/RSP ring resyncs, corrupt data  */
    OCM_XCP_DIAG_GW_DAQ_LEVEL_MAX,           /* fullest DAQ ring seen at a drain, B */
    OCM_XCP_DIAG_GW_CMD_DROPPED,             /* command ring full -> datagram lost  */
    OCM_XCP_DIAG_GW_DRAIN_CAPPED,            /* per-IPI drain cap hit (rest later)  */
    OCM_XCP_DIAG_GW_TXQ_DROPPED,             /* DAQ queue full -> segment dropped   */
    OCM_XCP_DIAG_GW_CTOQ_DROPPED,            /* CTO queue full -> frame dropped     */
    OCM_XCP_DIAG_GW_CMD_RECORDS,             /* command datagrams handed to the R5  */
    OCM_XCP_DIAG_GW_DAQ_RECORDS,             /* DTOs taken from the DAQ ring        */
    OCM_XCP_DIAG_GW_TX_MALFORMED_DROP,       /* TL walk failed on TX               */
    OCM_XCP_DIAG_GW_RX_MALFORMED_DROP,       /* TL walk failed on RX               */
    OCM_XCP_DIAG_GW_SENDTO_ERR,              /* transient lwip_sendto failures     */
    OCM_XCP_DIAG_GW_SENDTO_DROP,             /* batch dropped after retries        */
    OCM_XCP_DIAG_GW_IPI_COUNT,               /* IPIs handled (A53 liveness)        */
    OCM_XCP_DIAG_GW_TXQ_LEVEL,               /* DAQ queue fill (gauge, not count)  */
    OCM_XCP_DIAG_GW_MASTER_LOST,             /* sessions closed by the gateway     */
    /* A53 time profile (XCP_GW_PROFILE, xcp_gateway_a53.h; 0 when off):
     * microsecond sums of the A53 system counter that wrap after ~71 min -
     * the master uses differences over a run. Read by
     * tools/xcp_test/xcp_poll.py --stress only, not part of the A2L. */
    OCM_XCP_DIAG_GW_PROF_NOW_US,             /* A53 time base                      */
    OCM_XCP_DIAG_GW_PROF_IDLE_US,            /* CPU time left to the idle probe    */
    OCM_XCP_DIAG_GW_PROF_IPI_US,             /* in the IPI hook                    */
    OCM_XCP_DIAG_GW_PROF_IPI_MAX_US,         /* longest IPI hook, last full second */
    OCM_XCP_DIAG_GW_PROF_CHAIN_US,           /* DAQ ring -> segments copy          */
    OCM_XCP_DIAG_GW_PROF_ENQ_US,             /* segments -> queue (FromISR copies) */
    OCM_XCP_DIAG_GW_PROF_RECORDS,            /* segments queued (count)            */
    OCM_XCP_DIAG_GW_PROF_TX_US,              /* tx task: batching + sendto         */
    OCM_XCP_DIAG_GW_PROF_SENDTO_US,          /* inside lwip_sendto                 */
    OCM_XCP_DIAG_GW_PROF_SENDTO_N,           /* lwip_sendto calls (count)          */
    OCM_XCP_DIAG_GW_PROF_TX_KB,              /* datagram bytes handed to lwIP, KiB */
    OCM_XCP_DIAG_GW_PROF_SENDTO_MAX_US,      /* longest sendto, last full second   */
};

#endif /* OCM_XCP_RING_H_ */
