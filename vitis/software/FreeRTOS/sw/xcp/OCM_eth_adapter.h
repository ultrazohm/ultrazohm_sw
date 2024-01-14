/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between XCP data from OCM and Ethernet
 */

#ifndef OCM_ETH_ADAPTER_H_
#define OCM_ETH_ADAPTER_H_

void ocm_eth_adapter_task(void *p);
void ocm_eth_adapter_irq(void);

#endif /* OCM_ETH_ADAPTER_H_ */
