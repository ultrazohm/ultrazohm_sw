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
#undef  OPTION_CLOCK_TICKS_1NS
#define OPTION_CLOCK_TICKS_1US
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
/* OCM FIFO transport bound: a FIFO record is u8-length capped (<= 255 bytes
 * including the 4-byte TL header), and the A53 gateway frame cap is 256.
 * Segment 252 = exactly one max message (4 + 248). Upstream derives the
 * segment from OPTION_MTU rounded down to a multiple of 8, and 256 would not
 * fit a record, so the segment size is set directly (xcptl_cfg.h honours the
 * predefine, UZ patch). DTO 248 so CONNECT advertises MAX_CTO/MAX_DTO =
 * 248/248 (matches gen_a2l.py and CANape/UZ_XCP/uz.A2L). */
#undef  OPTION_MTU
#define XCPTL_MAX_SEGMENT_SIZE 252
#define XCPTL_MAX_DTO_SIZE 248
/* Largest single ODT entry the engine accepts and advertises
 * (GET_DAQ_RESOLUTION_INFO MAX_ODT_ENTRY_SIZE_DAQ; uz.A2L says 0xF0 too).
 * Upstream's default 248 equals the whole DTO, but an ODT carries at most
 * DTO - 4 (ODT/DAQ header) - 4 (timestamp in the first ODT) = 240 bytes, so a
 * 248-byte entry - what CANape builds when it merges the contiguous members
 * of a structure up to the advertised maximum - can never fit an ODT and
 * WRITE_DAQ fails with DAQ_CONFIG. 240 is a multiple of 4 (copy granularity). */
#define XCP_MAX_ODT_ENTRY_SIZE 240
#endif
