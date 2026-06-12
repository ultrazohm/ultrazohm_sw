/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between XCP data from OCM and Ethernet
 */

#ifndef OCM_ETH_ADAPTER_H_
#define OCM_ETH_ADAPTER_H_

void ocm_eth_adapter_task(void *p);
/* Runs in IPI ISR context. Returns nonzero if a higher-priority task was
 * woken and the caller should portYIELD_FROM_ISR at the end of the ISR. */
int ocm_eth_adapter_irq(void);
/* Nonzero while an XCP master is connected (used by the GEM RX watchdog). */
int ocm_eth_adapter_is_connected(void);

#endif /* OCM_ETH_ADAPTER_H_ */
