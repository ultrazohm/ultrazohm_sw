/* isr_diag.h - timing diagnostics of ISR_Control, per control cycle.
 *
 * With UZ_ISR_DIAG 1, ISR_Control splits its run time into sections with the
 * R5 cycle counter (2 ns at 500 MHz) and counts up to three CPU events with
 * the performance monitor (PMU) over the ISR. At the end of every ISR the
 * record of that cycle is published in uz_isr_diag.last, so a DAQ list on
 * DAQ_R5 samples the record of the PREVIOUS cycle - the same cycle as
 * timingR5.isr_execution_time_us. uz_isr_diag.entry_main_phase tells what the
 * main loop was doing when the CURRENT cycle's interrupt arrived; it explains
 * a late ISR start (timingR5.isr_period_us, the DAQ time stamp).
 *
 * tools/xcp_test/isr_jitter.py records and evaluates these values.
 *
 * The PMU events are selected by uz_isr_diag.pmu_events (byte i = event of
 * counter i, see xpm_counter.h of the BSP); the master may write it while the
 * application runs, the ISR applies a change at its next start. The counts of
 * that one cycle are then invalid (0xFFFF).
 */
#ifndef ISR_DIAG_H_
#define ISR_DIAG_H_

#include <stdint.h>

/* 1: measure every control cycle. Costs 0.7 to 0.9 us per ISR (bench
 * 2026-11-24, 40 kHz), so the execution time it reports is that much longer
 * than without it. 0: no code at all (default). */
#ifndef UZ_ISR_DIAG
#define UZ_ISR_DIAG 0
#endif

#define UZ_ISR_DIAG_PMU_COUNT 3u

/* Default PMU events: instruction-cache misses (0x01), data-cache misses
 * (0x03), external memory requests (0x43: cache line fills, uncached and
 * device accesses such as the AXI registers in the PL). */
#define UZ_ISR_DIAG_PMU_EVENTS_DEFAULT 0x00430301u

/* What the main loop was doing (uz_isr_diag_main_phase). Since the OCM
 * rings (2026-11-26) the main loop only executes commands; PACING, COPY and
 * FLUSH belonged to the former main-loop exchange and stay reserved so
 * older recordings keep their meaning. */
typedef enum {
    UZ_ISR_DIAG_MAIN_OTHER = 0,       /* state machine, loop, waiting for a command */
    UZ_ISR_DIAG_MAIN_XCP_PACING = 1,  /* (former exchange: header refresh, pacing) */
    UZ_ISR_DIAG_MAIN_XCP_COMMANDS = 2, /* xcp_r5_background(): XcpCommand(), responses */
    UZ_ISR_DIAG_MAIN_XCP_COPY = 3,    /* (former exchange: DAQ queue -> OCM copy) */
    UZ_ISR_DIAG_MAIN_XCP_FLUSH = 4,   /* (former exchange: cache flush of the chain) */
} uz_isr_diag_main_phase_t;

/* One control cycle, in CPU cycles (2 ns) unless noted. Sections that do
 * not fit 16 bits read 0xFFFF. */
typedef struct {
    uint32_t seq;        /* low word of the ISR count (timingR5.interrupt_counter) of this cycle */
    uint16_t tic;        /* ISR_Control entry -> after uz_SystemTime_ISR_Tic() */
    uint16_t adc;        /* ReadAllADC() */
    uint16_t encoder;    /* update_speed_and_position_of_encoder_on_D5() */
    uint16_t pwm;        /* state machine, control algorithm, duty cycles */
    uint16_t xcp;        /* JavaScope_update_lifecheck() + xcp_r5_event() incl. publish (or JavaScope_update()) */
    uint16_t xcp_base;   /* part of xcp: the DAQ_R5 event */
    uint16_t xcp_slices; /* part of xcp: the time-slice events daq_1ms ... daq_1s */
    uint16_t total;      /* ISR_Control entry -> before uz_SystemTime_ISR_Toc() */
    uint16_t pmu[UZ_ISR_DIAG_PMU_COUNT]; /* event counts after Tic .. before Toc (events: pmu_events) */
    uint16_t reserved;
} uz_isr_diag_record_t;

typedef struct {
    uz_isr_diag_record_t last; /* the previous control cycle, complete */
    uint8_t entry_main_phase;  /* main loop when this cycle's interrupt arrived (uz_isr_diag_main_phase_t) */
    uint8_t reserved[3];
    uint32_t pmu_events;       /* WRITABLE: PMU event of counter i in byte i */
} uz_isr_diag_t;

_Static_assert(sizeof(uz_isr_diag_record_t) == 28u, "uz_isr_diag_record_t layout changed (isr_jitter.py)");
_Static_assert(sizeof(uz_isr_diag_t) == 36u, "uz_isr_diag_t layout changed (isr_jitter.py)");

#if UZ_ISR_DIAG
extern volatile uz_isr_diag_t uz_isr_diag;
extern volatile uint8_t uz_isr_diag_main_phase;   /* written by the main loop */
extern volatile uint32_t uz_isr_diag_xcp_base;    /* written by xcp_r5_event() */
extern volatile uint32_t uz_isr_diag_xcp_slices;  /* written by xcp_r5_event() */

/* R5 cycle counter (PMCCNTR). The "memory" clobber keeps the compiler from
 * moving it across the measured code. */
static inline uint32_t uz_isr_diag_cycles(void) {
    uint32_t v;
    __asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(v)::"memory");
    return v;
}

#define UZ_ISR_DIAG_MAIN_PHASE(p) (uz_isr_diag_main_phase = (uint8_t)(p))
#else
#define UZ_ISR_DIAG_MAIN_PHASE(p) ((void)0)
#endif

#endif /* ISR_DIAG_H_ */
