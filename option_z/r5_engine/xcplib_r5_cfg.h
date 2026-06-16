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
#endif
