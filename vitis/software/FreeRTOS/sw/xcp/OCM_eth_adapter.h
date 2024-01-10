/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between XCP data from OCM and Ethernet
 */

#ifndef OCM_ETH_ADAPTER_H_
#define OCM_ETH_ADAPTER_H_

void xcp_device(void *p);
void read_rxQueue_write_OCM(void);
void read_OCM_write_txQueue(void);

#endif /* OCM_ETH_ADAPTER_H_ */
