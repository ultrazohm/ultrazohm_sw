/******************************************************************************
 * xcp_r5.h
 *
 * Public interface for the Option Z XCPlite engine on the R5 (control core).
 * Enable with XCP_ENGINE_R5_ENABLE in vitis/software/Baremetal/src/defines.h
 * (and select LOGGING_PATH_XCP_R5_GATEWAY on the A53).
 *
 *   xcp_r5_init()       : call once during init, after uz_SystemTime_init()
 *                         and before the control ISR is enabled.
 *   xcp_r5_event()      : call from ISR_Control to sample DAQ at the control
 *                         rate. The engine writes the DTOs straight into the
 *                         DAQ ring in OCM; the call then publishes them (one
 *                         cache clean, ~1.3 us/KB) and sends the IPI when
 *                         enough data waits. It also serves the derived time
 *                         slices (see below).
 *   xcp_r5_background() : call from the MAIN LOOP every iteration. Executes
 *                         new commands from the CMD ring; their responses go
 *                         out at once (RSP ring + IPI).
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

/* Transport profile (diagnostics). 1 (default): xcp_r5_event() and the
 * command execution are timed with the CPU cycle counter; the sums in
 * xcp_r5_prof below are readable by the XCP master
 * (tools/xcp_test/xcp_poll.py --stress prints them). Cost: a few cycle
 * counter reads per control cycle. 0: compiled out. */
#ifndef XCP_R5_PROFILE
#define XCP_R5_PROFILE 1
#endif

#include <stdint.h>

/* Layout of xcp_r5_prof, version 3 (OCM rings), 88 bytes, little endian.
 * *_cyc are R5 CPU cycles (cpu_hz per second), isr_ns_all comes from
 * uz_SystemTime. All values count from the last reset: write 1 to `reset`,
 * the next control cycle clears everything. */
typedef struct {
    uint32_t version;         /*  0  3                                          */
    uint32_t cpu_hz;          /*  4  R5 clock                                   */
    uint32_t reset;           /*  8  write 1 to clear                           */
    uint32_t event_calls;     /* 12  xcp_r5_event() calls = control cycles      */
    uint32_t event_cyc_max;   /* 16  longest xcp_r5_event()                     */
    uint32_t publish_cyc_max; /* 20  longest publish of one cycle's DTOs        */
    uint32_t ipis;            /* 24  IPIs from the control ISR                  */
    uint32_t commands;        /* 28  commands executed                          */
    uint64_t elapsed_cyc;     /* 32  wall time covered                          */
    uint64_t event_cyc;       /* 40  cycles in xcp_r5_event(), the XCP part of the ISR */
    uint64_t sample_cyc;      /* 48  of it: XcpEvent, DTOs into the ring        */
    uint64_t publish_cyc;     /* 56  of it: cache clean + write position        */
    uint64_t daq_bytes;       /* 64  bytes published into the DAQ ring          */
    uint64_t isr_ns_all;      /* 72  all control-ISR time                       */
    uint64_t cmd_cyc;         /* 80  main loop: command execution, wall         */
} xcp_r5_prof_t;

#ifdef __cplusplus
extern "C" {
#endif

int  xcp_r5_init(const char *name, const char *epk);
void xcp_r5_event(void);
void xcp_r5_background(void);

#if XCP_R5_PROFILE
extern volatile xcp_r5_prof_t xcp_r5_prof;
#endif

#ifdef __cplusplus
}
#endif

#endif /* XCP_R5_H_ */
