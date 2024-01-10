/*
 * Copyright (c) 2022 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between UltraZohm project and XCP Basic Driver
 */

#ifndef XCP_INTERFACE_H_
#define XCP_INTERFACE_H_

void xcp_interface_init(void);
void xcp_interface_stim(void);
void xcp_interface_events_10kHz(void);

#endif /* XCP_INTERFACE_H_ */
