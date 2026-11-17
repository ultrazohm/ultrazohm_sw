/******************************************************************************
 * xcp_r5.h
 *
 * Public interface for the Option Z XCPlite engine on the R5 (control core).
 * Enable with XCP_ENGINE_R5_ENABLE in vitis/software/Baremetal/src/defines.h
 * (and select LOGGING_PATH_XCP_R5_GATEWAY on the A53).
 *
 *   xcp_r5_init()       : call once during init, after uz_SystemTime_init().
 *   xcp_r5_event()      : call from ISR_Control to sample DAQ at the control
 *                         rate. This is the ONLY XCP call in the ISR; its cost
 *                         is the DAQ sample copy (~sub-us idle, ~5 us/KB).
 *                         It also serves the derived time slices (see below).
 *   xcp_r5_background() : call from the MAIN LOOP every iteration. Runs one
 *                         paced exchange sweep (commands + DAQ drain -> OCM,
 *                         every XCP_R5_SWEEP_PERIOD_US) and returns 1 when the
 *                         caller must trigger the IPI to the A53 gateway.
 *   xcp_r5_poll()       : one unpaced sweep (used by xcp_r5_background; direct
 *                         use only for special cases).
 *
 * DAQ rasters (event channel numbers as declared in CANape/UZ_XCP/uz.A2L):
 *   0 DAQ_R5     control-ISR rate (UZ_PWM_FREQUENCY x trigger factor)
 *   1 daq_1ms    2 daq_10ms    3 daq_100ms    4 daq_1s
 * The slices are counted down from the ISR rate in xcp_r5_event(); channel
 * numbers follow the creation order in xcp_r5_init() and must match the A2L.
 *
 * Copyright 2024 Eyke Liegmann, Apache-2.0
 ******************************************************************************/
#ifndef XCP_R5_H_
#define XCP_R5_H_

/* Measurement-only build. 0 (default): the master may calibrate, i.e. write
 * R5 variables with DOWNLOAD / SHORT_DOWNLOAD, but only inside the data
 * sections (.data/.sdata/.sbss/.bss) - code, constants, exception vectors,
 * stacks, heap and the OCM exchange are write-protected in any case.
 * 1: every write is refused with ERR_WRITE_PROTECTED; measuring is
 * unaffected. Set it here or with -DXCP_R5_READ_ONLY=1.
 * Refused writes are counted in xcp_r5_write_denied. */
#ifndef XCP_R5_READ_ONLY
#define XCP_R5_READ_ONLY 0
#endif

/* Exchange profile (diagnostics). 1 (default): the R5 times every exchange
 * sweep and every xcp_r5_event() call with its CPU cycle counter and keeps
 * the sums in xcp_r5_prof below, readable by the XCP master
 * (tools/xcp_test/xcp_poll.py --stress prints them). Cost: a few cycle
 * counter reads per exchange and per control cycle. 0: compiled out. */
#ifndef XCP_R5_PROFILE
#define XCP_R5_PROFILE 1
#endif

#include <stdint.h>

/* Layout of xcp_r5_prof, version 1, 136 bytes, little endian. *_cyc are R5
 * CPU cycles (cpu_hz per second), *_ns come from uz_SystemTime. Wall time
 * includes the control ISRs that interrupted the main loop; isr_ns_* is that
 * ISR time, so wall - isr = CPU time of the phase. All values count from the
 * last reset: write 1 to `reset`, the next exchange clears everything. */
typedef struct {
    uint32_t version;       /*   0  1                                          */
    uint32_t cpu_hz;        /*   4  R5 clock                                   */
    uint32_t reset;         /*   8  write 1 to clear                           */
    uint32_t exchanges;     /*  12  exchange sweeps counted                    */
    uint32_t keeps;         /*  16  ... that kept the unacknowledged chain     */
    uint32_t event_calls;   /*  20  xcp_r5_event() calls = control cycles      */
    uint32_t event_cyc_max; /*  24  longest xcp_r5_event()                     */
    uint32_t copy_cyc_max;  /*  28  longest copy phase, wall                   */
    uint32_t flush_cyc_max; /*  32  longest flush phase, wall                  */
    uint32_t total_cyc_max; /*  36  longest exchange, wall                     */
    uint64_t elapsed_cyc;   /*  40  wall time covered (exchange start to start) */
    uint64_t chain_bytes;   /*  48  bytes written into the XCP_OUT chain       */
    uint64_t cyc_refresh;   /*  56  XCP_IN cache refresh                       */
    uint64_t cyc_commands;  /*  64  open the cycle, commands, response mailbox */
    uint64_t cyc_copy;      /*  72  DAQ queue -> XCP_OUT chain (tx_pump)       */
    uint64_t cyc_flush;     /*  80  chain + header cache flush, publish        */
    uint64_t cyc_total;     /*  88  whole exchange                             */
    uint64_t isr_ns_copy;   /*  96  control-ISR time inside the copy phases    */
    uint64_t isr_ns_flush;  /* 104  control-ISR time inside the flush phases   */
    uint64_t isr_ns_total;  /* 112  control-ISR time inside whole exchanges    */
    uint64_t isr_ns_all;    /* 120  all control-ISR time                       */
    uint64_t event_cyc;     /* 128  cycles in xcp_r5_event(), the XCP part of the ISR */
} xcp_r5_prof_t;

#ifdef __cplusplus
extern "C" {
#endif

int  xcp_r5_init(const char *name, const char *epk);
void xcp_r5_event(void);
int  xcp_r5_background(void);
void xcp_r5_poll(void);

#if XCP_R5_PROFILE
extern volatile xcp_r5_prof_t xcp_r5_prof;
#endif

#ifdef __cplusplus
}
#endif

#endif /* XCP_R5_H_ */
