/*
 * Copyright (c) 2022 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between UltraZohm project and XCP Basic Driver
 */

#ifndef XCP_INTERFACE_H_
#define XCP_INTERFACE_H_

void wait_for_xcp_master(void *p);
extern void timer_irq_callback_10kHz(void);

#endif /* XCP_INTERFACE_H_ */
