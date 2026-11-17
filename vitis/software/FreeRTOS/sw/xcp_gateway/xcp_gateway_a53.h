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
/* UDP port the gateway listens on (CANape / xcp_poll.py connect here; printed
 * by print_xcp_app_header() in sw/ethernet.c). */
#ifndef XCP_GATEWAY_UDP_PORT
#define XCP_GATEWAY_UDP_PORT 5556
#endif
/* Master supervision. UDP has no connection: when CANape crashes or the
 * cable is pulled during a measurement, the R5 keeps sampling and the A53
 * keeps sending to a dead endpoint until the next power cycle. The gateway
 * therefore closes the session itself (it injects an XCP DISCONNECT for the
 * R5 engine, which stops DAQ, and forgets the master endpoint) when
 *  a) XCP_GATEWAY_SEND_FAIL_LIMIT datagrams in a row could not be sent even
 *     after the bounded retries (link down, no route) - always active, or
 *  b) DAQ data is flowing but the master has sent nothing for
 *     XCP_GATEWAY_MASTER_TIMEOUT_MS - OFF by default (0): the XCP standard
 *     does not oblige a master to send anything during a pure DAQ
 *     measurement, and xcp_poll.py --stress stays silent for the whole run.
 *     Enable it only for a master known to poll (e.g. CANape with cyclic
 *     GET_DAQ_CLOCK / status polling) and set it well above that period.
 * A later CONNECT from any endpoint starts a normal new session. Counted in
 * xcp_gw_master_lost (mirrored to the XCP master like the other counters). */
#ifndef XCP_GATEWAY_MASTER_TIMEOUT_MS
#define XCP_GATEWAY_MASTER_TIMEOUT_MS 0
#endif
#ifndef XCP_GATEWAY_SEND_FAIL_LIMIT
#define XCP_GATEWAY_SEND_FAIL_LIMIT 20
#endif
/* A53 time profile: time in the IPI hook (chain copy, queue copies), in the
 * tx task and in lwip_sendto, plus an idle probe task at the idle priority,
 * measured with the A53 system counter and mirrored with the gateway counters
 * (ocm_xcp_fifo.h) for xcp_poll.py --stress. Costs a few counter reads per
 * IPI and per datagram; the probe only uses CPU time nothing else wants.
 * 0 = off (the profile slots read 0). */
#ifndef XCP_GW_PROFILE
#define XCP_GW_PROFILE 1
#endif
/* Create the UDP socket, queues and rx/tx tasks. Call once the IP is up. */
int  xcp_gateway_a53_init(uint32_t thread_stack, uint32_t thread_prio);
/* Call from APU_IPI_ISR under the gateway mode (ISR context: OCM + queues). */
void xcp_gateway_a53_on_ipi(BaseType_t *pxHigherPriorityTaskWoken);
#ifdef __cplusplus
}
#endif
#endif /* XCP_GATEWAY_A53_H_ */
