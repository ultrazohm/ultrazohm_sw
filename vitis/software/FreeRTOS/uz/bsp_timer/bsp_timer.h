/*
 * Copyright (c) 2022 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Abstraction layer for timer
 */

#ifndef BSP_TIMER_H_
#define BSP_TIMER_H_

#include <stdint.h>

void bsp_timer_init(void);
void bsp_timer_start(void);
void bsp_timer_stop(void);

uint16_t bsp_timer_timestamp_get(void);
uint32_t bsp_timer_timestamp_get_time_delta_ns(uint16_t time_start,
                                               uint16_t time_end);
void timer_irq_callback__(void);

#endif /* BSP_TIMER_H_ */
