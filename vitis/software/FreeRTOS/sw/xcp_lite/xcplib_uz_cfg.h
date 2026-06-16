/*******************************************************************************
 * xcplib_uz_cfg.h
 *
 * UltraZohm (A53 / FreeRTOS / lwIP) XCPlite configuration override.
 *
 * Included at the END of the vendored xcplib_cfg.h via:
 *   -DXCPLIB_CFG_OVERRIDE="xcplib_uz_cfg.h"
 *
 * VERIFY BEFORE FIRST BUILD: the macro name XCPLIB_CFG_OVERRIDE must match
 * what the vendored XCPlite version actually reads in its xcplib_cfg.h.
 * Search the vendored xcplib_cfg.h for:
 *   #ifdef XCPLIB_CFG_OVERRIDE
 *   #include XCPLIB_CFG_OVERRIDE
 * If the upstream uses a different name, update the compiler flag in
 * VENDOR.md and vitis_generate_UltraZohm_workspace.tcl to match.
 *
 * Reference: see vendored xcplib_rtos_cfg.h — this file follows the same
 * pattern but is tuned to the UltraZohm hardware.
 *
 * MIT-licensed XCPlite v2.1.1: https://github.com/vectorgrp/XCPlite
 * UltraZohm integration: Copyright 2024 Eyke Liegmann, Apache-2.0
 ******************************************************************************/

#ifndef XCPLIB_UZ_CFG_H
#define XCPLIB_UZ_CFG_H

/*---------------------------------------------------------------------------
 * FreeRTOS + lwIP task configuration
 * OPTION_FREERTOS_STACK_BYTES: stack per XCP rx/tx task.
 * OPTION_FREERTOS_PRIORITY: must be <= lwIP THREAD_PRIO_DEFAULT (2).
 *--------------------------------------------------------------------------*/
#undef  OPTION_FREERTOS_STACK_BYTES
#define OPTION_FREERTOS_STACK_BYTES (2048U * 4U)   /* 8 KB */
#undef  OPTION_FREERTOS_PRIORITY
#define OPTION_FREERTOS_PRIORITY    2U              /* == lwIP default priority */

/* lwIP socket backend for FreeRTOS. */
#ifndef OPTION_FREERTOS_LWIP
#define OPTION_FREERTOS_LWIP
#endif

/*---------------------------------------------------------------------------
 * Logging -- no stderr on bare-metal/FreeRTOS.
 *--------------------------------------------------------------------------*/
#undef OPTION_ENABLE_DBG_STDERR

/* Keep OPTION_ENABLE_DBG_PRINTS active during bring-up.
 * #undef before production to remove all debug output. */
/* #undef OPTION_ENABLE_DBG_PRINTS */

/*---------------------------------------------------------------------------
 * Clock -- 1 us resolution, arbitrary epoch.
 * ApplXcpGetClock64() in xcp_server_uz.c uses XTime_GetTime() (~100 MHz)
 * divided by COUNTS_PER_USECOND.
 *--------------------------------------------------------------------------*/
#undef  OPTION_CLOCK_TICKS_1NS
#define OPTION_CLOCK_TICKS_1US
#undef  OPTION_CLOCK_EPOCH_PTP
#define OPTION_CLOCK_EPOCH_ARB

/*---------------------------------------------------------------------------
 * Transport -- UDP only.
 * MTU 1504 => max UDP payload 1472 bytes (standard Ethernet).
 *--------------------------------------------------------------------------*/
#undef OPTION_ENABLE_TCP
#undef OPTION_MTU
#define OPTION_MTU 1504
#undef OPTION_SERVER_FORCEFULL_TERMINATION

/*---------------------------------------------------------------------------
 * DAQ -- reduced footprint for embedded SRAM.
 * 6 bytes per signal in maximum fragmentation.
 * OPTION_DAQ_EVENT_COUNT must be even.
 *--------------------------------------------------------------------------*/
#undef  OPTION_DAQ_MEM_SIZE
#define OPTION_DAQ_MEM_SIZE     (64U * 6U)
#undef  OPTION_DAQ_EVENT_COUNT
#define OPTION_DAQ_EVENT_COUNT  8U

/*---------------------------------------------------------------------------
 * Transport queue -- queue32 (mutex-based).
 * The 64-bit lockless variants need 64-bit atomics; queue32 is safe on
 * FreeRTOS where GCC atomic support is BSP-dependent.
 * Compile queue32.c; exclude queue64f.c and queue64v.c from the build.
 *--------------------------------------------------------------------------*/
#undef OPTION_QUEUE_64_VAR_SIZE
#undef OPTION_QUEUE_64_FIX_SIZE
#define OPTION_QUEUE_32

/*---------------------------------------------------------------------------
 * Calibration -- Phase 4.
 * The UZ uses the OCM double-buffer in xcp_cal_image_a53.c rather than
 * the upstream segment manager. These values keep the protocol layer from
 * asserting on segment config. Disable (undef OPTION_CAL_SEGMENTS) until
 * Phase 4 bring-up.
 *--------------------------------------------------------------------------*/
#undef OPTION_CAL_SEGMENT_COUNT
#define OPTION_CAL_SEGMENT_COUNT 2
#undef OPTION_CAL_MEM_SIZE
#define OPTION_CAL_MEM_SIZE (1024U * 2U)
#define OPTION_CAL_SEGMENTS_ABS
#undef OPTION_ENABLE_PERSISTENCE

/*---------------------------------------------------------------------------
 * A2L / ELF -- no filesystem; generate A2L offline via bintool on the PC.
 *--------------------------------------------------------------------------*/
#undef OPTION_ENABLE_A2L_GENERATOR
#undef OPTION_ENABLE_A2L_UPLOAD
#undef OPTION_ENABLE_ELF_UPLOAD

#endif /* XCPLIB_UZ_CFG_H */
