#ifndef XCPLIB_R5_CFG_H
#define XCPLIB_R5_CFG_H
/* UltraZohm R5 (bare-metal) XCPlite config: Option Z - engine on the control
 * core. Applied at the END of xcplib_cfg.h (UZ patch there), i.e. after the
 * upstream defaults, exactly like upstream's own xcplib_rtos_cfg.h override.
 * Engine base: upstream XCPlite V2.3.4 (github vectorgrp/XCPlite, 2026-11-11). */
#undef  OPTION_ENABLE_TCP      /* no sockets on R5; transport is the OCM FIFO  */
#undef  OPTION_ENABLE_UDP
#undef  OPTION_ENABLE_DBG_STDERR
/* Logging: fixed level 1 = errors only. The default runtime level 3 printed
 * the CONNECT / "DAQ processing stop" info lines through the blocking UART
 * printf inside the main-loop sweep (milliseconds of sweep gap per line),
 * and the level-4 "DAQ queue overrun" trace sits in the ISR DAQ path, armed
 * as soon as anyone raised gXcpLogLevel. Errors stay: rare and worth it. */
#undef  OPTION_DEFAULT_DBG_LEVEL
#undef  OPTION_MAX_DBG_LEVEL
#define OPTION_FIXED_DBG_LEVEL 1
/* DAQ clock: uz_SystemTime's 64-bit AXI timer at 100 MHz, 10 ns per tick
 * (clockGet in platform_baremetal.c, which checks the rate against the BSP).
 * The engine reports it as UNIT_1NS with 10 ticks per unit (A2L
 * TIMESTAMP_SUPPORTED 0x0A UNIT_1NS). The 32-bit DTO timestamp wraps every
 * 42.9 s. Was OPTION_CLOCK_TICKS_1US, truncated to whole microseconds. */
#undef  OPTION_CLOCK_TICKS_1NS
#undef  OPTION_CLOCK_TICKS_1US
#undef  CLOCK_TICKS_PER_S
#define CLOCK_TICKS_PER_S 100000000UL
#undef  OPTION_CLOCK_EPOCH_PTP
#define OPTION_CLOCK_EPOCH_ARB
#undef  OPTION_QUEUE_64_VAR_SIZE
#undef  OPTION_QUEUE_64_FIX_SIZE
#define OPTION_QUEUE_32
#undef  OPTION_CAL_SEGMENTS         /* direct addressing: DOWNLOAD writes straight to R5 memory */
/* Memory access gate on the MTA path (UZ patch in xcplite.c XcpReadMta /
 * XcpWriteMta, not in upstream V2.3.4): SET_MTA only validates the start
 * address, then UPLOAD/DOWNLOAD/BUILD_CHECKSUM auto-increment the MTA without
 * limit. With this option every access re-checks pointer + size through
 * ApplXcpCheckMemory -> xcp_r5_check_memory (xcptl_ocm.c), so a chained
 * upload cannot walk from R5 DDR into A53 memory or PL space (data abort). */
#define XCP_ENABLE_MTA_RANGE_CHECK
/* Write gate (UZ patch in xcplite.c XcpWriteMta, not in upstream V2.3.4):
 * the range check above treats reads and writes alike, and everything the
 * R5 can read includes its own code (.text is in DDR), the exception
 * vectors (ATCM) and the OCM exchange. Every DOWNLOAD / SHORT_DOWNLOAD is
 * therefore passed through xcp_r5_check_write() (xcptl_ocm.c) as well:
 * only initialised and zero-initialised data (.data/.sdata/.sbss/.bss) is
 * writable, and nothing at all in a measurement-only build
 * (XCP_R5_READ_ONLY, xcp_r5.h). */
#include <stdint.h>
extern uint8_t xcp_r5_check_write(uint32_t addr, uint8_t size);
#define XCP_MTA_WRITE_CHECK(addr, size) xcp_r5_check_write((addr), (size))
/* Largest BUILD_CHECKSUM block (UZ patch in xcplite.c calcChecksum): the
 * checksum loop runs inside the main-loop sweep, ~50 ns per byte with the
 * range check -> 64 KB caps one command at ~3 ms; bigger -> ERR_OUT_OF_RANGE. */
#define XCP_CHECKSUM_MAX_SIZE (64u * 1024u)
/* No event-relative (DYN, ext 2..15) addressing (UZ patch in xcp_cfg.h): the
 * R5 samples DAQ with the plain XcpEvent(), which never executes the commands
 * the engine would park for an XcpEventExt() context. SET_MTA/SHORT_UPLOAD/
 * DOWNLOAD/WRITE_DAQ with such an extension now get OUT_OF_RANGE /
 * ACCESS_DENIED instead of silence (and a stuck cmd_pending -> BUSY). The A2L
 * only ever uses ext 0. */
#define OPTION_DISABLE_DYN_ADDRESSING
#undef  OPTION_ENABLE_PERSISTENCE
#undef  OPTION_ENABLE_A2L_GENERATOR
#undef  OPTION_ENABLE_A2L_UPLOAD
#undef  OPTION_SECTION_REGISTRATION /* events are created at run time by xcp_r5_init (XcpCreateEvent) */
/* Run-time event list (upstream default since V2.2, stated explicitly: xcp_r5_init
 * creates DAQ_R5 and the daq_* time slices with XcpCreateEvent). 32 event slots
 * keeps the DAQ table layout of the V2.1.0 engine (upstream default is 16). */
#ifndef OPTION_DAQ_EVENT_LIST
#define OPTION_DAQ_EVENT_LIST
#endif
#undef  OPTION_DAQ_EVENT_COUNT
#define OPTION_DAQ_EVENT_COUNT 32
#undef  OPTION_DAQ_MEM_SIZE
/* DAQ table memory (R5 .bss/DDR): 12 B per DAQ list + 8 B per ODT + 6 B per
 * measured signal. Sized for the five rasters DAQ_R5/1ms/10ms/100ms/1s
 * (~1000 signals total); a too-small value shows up as MEMORY_OVERFLOW when
 * CANape allocates the DAQ lists. */
#define OPTION_DAQ_MEM_SIZE (1024 * 6)
/* Message and segment sizes. Every DTO is one record of the OCM DAQ ring
 * (at most OCM_XCP_DAQ_MAX_LEN, shared/ocm_xcp_ring.h; checked in
 * xcptl_ocm.c); the A53 gateway packs them into datagrams of up to 1472
 * bytes = 1500-byte MTU - 20 (IPv4) - 8 (UDP), the largest datagram without
 * IP fragmentation (XCP_GW_BATCH_BUF_SIZE, xcp_gateway_a53.c). The segment
 * size is no longer used on the R5 (no queue32); it stays at the datagram
 * size for the engine's own checks. Upstream derives the same 1472 from
 * OPTION_MTU 1500; here it is set directly (xcptl_cfg.h honours the
 * predefine, UZ patch). Was 1400 until 2026-11-27.
 * DTO 1024 (upstream default): every ODT is one DAQ message, and each costs a
 * fixed ~0.6-0.8 us in ISR_Control (queue acquire/push, measured 2026-11-17
 * with queue32),
 * so a bigger DTO means fewer ODTs for the same data. An ODT now carries up
 * to 1024 - 4 (ODT/DAQ header) - 4 (timestamp, first ODT) = 1016 bytes.
 * Commands stay at MAX_CTO 248 (largest record of the OCM RSP ring).
 * CONNECT advertises MAX_CTO/MAX_DTO = 248/1024 (matches gen_a2l.py and
 * CANape/UZ_XCP/uz.A2L). Was 248/252 until 2026-11-17: the OCM records had an
 * 8-bit length. */
#undef  OPTION_MTU
#define XCPTL_MAX_SEGMENT_SIZE 1472
#define XCPTL_MAX_DTO_SIZE 1024
/* Largest single ODT entry the engine accepts and advertises
 * (GET_DAQ_RESOLUTION_INFO MAX_ODT_ENTRY_SIZE_DAQ; uz.A2L says 0xF0 too).
 * Kept at 240 from the 248-byte DTO era, where an ODT carried at most 240
 * bytes and a 248-byte entry (CANape merges the contiguous members of a
 * structure up to this maximum) failed WRITE_DAQ with DAQ_CONFIG. An ODT now
 * holds several such entries. The XCP protocol caps an entry at 255 (WRITE_DAQ
 * size is one byte); 240 is a multiple of 4 (copy granularity). */
#define XCP_MAX_ODT_ENTRY_SIZE 240
/* Engine asserts: upstream XCPlite consistency checks, some of them in the
 * DAQ code that runs in ISR_Control (queue segment and message checks,
 * ODT entry checks under XCP_ENABLE_TEST_CHECKS). The Vitis Debug build does
 * not define NDEBUG, so they are active, and a failing check calls abort()
 * and stops the R5. 1 (default): keep them (upstream behaviour).
 * 0: build the engine sources without them (NDEBUG from here on, plus a
 * second include of assert.h for files that included it before this
 * header), for example to measure what they cost in the ISR. */
#ifndef XCP_R5_ENGINE_ASSERTS
#define XCP_R5_ENGINE_ASSERTS 1
#endif
#if !XCP_R5_ENGINE_ASSERTS
#ifndef NDEBUG
#define NDEBUG
#endif
#include <assert.h>
#endif
#endif
