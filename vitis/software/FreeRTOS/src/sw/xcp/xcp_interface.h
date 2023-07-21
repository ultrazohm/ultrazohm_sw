/*
 * Copyright (c) 2022 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between UltraZohm project and XCP Basic Driver
 */

#ifndef XCP_INTERFACE_H_
#define XCP_INTERFACE_H_

void xcp_interface(void *p);

void xcp_event_fast(void);
void xcp_events_1ms(void);

#endif /* XCP_INTERFACE_H_ */
