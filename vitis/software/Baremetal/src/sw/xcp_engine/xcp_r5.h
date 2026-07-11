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
 *   xcp_r5_background() : call from the MAIN LOOP every iteration. Runs one
 *                         paced exchange sweep (commands + DAQ drain -> OCM,
 *                         every XCP_R5_SWEEP_PERIOD_US) and returns 1 when the
 *                         caller must trigger the IPI to the A53 gateway.
 *   xcp_r5_poll()       : one unpaced sweep (used by xcp_r5_background; direct
 *                         use only for special cases).
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
int  xcp_r5_background(void);
void xcp_r5_poll(void);

#ifdef __cplusplus
}
#endif

#endif /* XCP_R5_H_ */
