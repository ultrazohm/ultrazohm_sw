/******************************************************************************
 * xcp_r5.h
 *
 * Public interface for the Option Z XCPlite engine on the R5 (control core).
 * Enable with XCP_ENGINE_R5_ENABLE in vitis/software/Baremetal/src/defines.h
 * (and select LOGGING_PATH_XCP_R5_GATEWAY on the A53).
 *
 *   xcp_r5_init()  : call once during init, after uz_SystemTime_init().
 *   xcp_r5_event() : call from ISR_Control to sample DAQ at the control rate.
 *   xcp_r5_poll()  : call from ISR_Control (after event) to process commands
 *                    and drain the DAQ queue into the OCM FIFO; then trigger
 *                    the IPI to the A53 gateway.
 *
 * Copyright 2024 Eyke Liegmann, Apache-2.0
 ******************************************************************************/
#ifndef XCP_R5_H_
#define XCP_R5_H_

#ifdef __cplusplus
extern "C" {
#endif

int  xcp_r5_init(const char *name, const char *epk);
void xcp_r5_event(void);
void xcp_r5_poll(void);

#ifdef __cplusplus
}
#endif

#endif /* XCP_R5_H_ */
