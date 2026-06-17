/******************************************************************************
 * xcp_gateway_a53.h
 * Option Z — A53 UDP<->OCM gateway for the R5 XCPlite engine.
 * Select with LOGGING_PATH_XCP_R5_GATEWAY in vitis/software/FreeRTOS/defines.h
 * (and XCP_ENGINE_R5_ENABLE on the R5/Baremetal side).
 * Copyright 2024 Eyke Liegmann, Apache-2.0
 ******************************************************************************/
#ifndef XCP_GATEWAY_A53_H_
#define XCP_GATEWAY_A53_H_
#include "FreeRTOS.h"
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
/* Create the UDP socket, queues and rx/tx tasks. Call once the IP is up. */
int  xcp_gateway_a53_init(uint32_t thread_stack, uint32_t thread_prio);
/* Call from APU_IPI_ISR under the gateway mode (ISR context: OCM + queues). */
void xcp_gateway_a53_on_ipi(BaseType_t *pxHigherPriorityTaskWoken);
#ifdef __cplusplus
}
#endif
#endif /* XCP_GATEWAY_A53_H_ */
