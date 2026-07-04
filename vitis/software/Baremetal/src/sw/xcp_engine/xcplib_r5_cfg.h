#ifndef XCPLIB_R5_CFG_H
#define XCPLIB_R5_CFG_H
/* UltraZohm R5 (bare-metal) XCPlite config: Option Z — engine on the control core. */
#undef  OPTION_ENABLE_TCP      /* no sockets on R5; transport is the OCM FIFO  */
#undef  OPTION_ENABLE_UDP
#undef  OPTION_ENABLE_DBG_STDERR
#undef  OPTION_CLOCK_TICKS_1NS
#define OPTION_CLOCK_TICKS_1US
#undef  OPTION_CLOCK_EPOCH_PTP
#define OPTION_CLOCK_EPOCH_ARB
#undef  OPTION_QUEUE_64_VAR_SIZE
#undef  OPTION_QUEUE_64_FIX_SIZE
#define OPTION_QUEUE_32
#undef  OPTION_CAL_SEGMENTS         /* direct addressing: DOWNLOAD writes straight to R5 memory */
#undef  OPTION_ENABLE_PERSISTENCE
#undef  OPTION_ENABLE_A2L_GENERATOR
#undef  OPTION_ENABLE_A2L_UPLOAD
#undef  OPTION_ENABLE_ELF_UPLOAD
#undef  OPTION_DAQ_MEM_SIZE
#define OPTION_DAQ_MEM_SIZE (512 * 6)
/* OCM FIFO transport bound: a FIFO record is u8-length capped (<= 255 bytes
 * including the 4-byte TL header), and the A53 gateway frame cap is 256.
 * MTU 284 -> XCPTL_MAX_SEGMENT_SIZE 252 (= max record payload); DTO 248 so
 * CONNECT advertises MAX_CTO/MAX_DTO = 248/248 (matches gen_a2l.py). */
#undef  OPTION_MTU
#define OPTION_MTU 284
#define XCPTL_MAX_DTO_SIZE 248 /* xcptl_cfg.h honours this predefine */
#endif
