/*
 * bsp_ringBuffer.h
 *
 *  Created on: 24.06.2019
 *      Author: Jens
 */

#ifndef BSP_RINGBUFFER_H_
#define BSP_RINGBUFFER_H_

#include <stdint.h>

typedef enum rbt_t_ {
	rbt_rx,
	rbt_tx,
	rbt_num // must be last for count!
} rbt_t;

void bsp_ringBuffer_init(void);
uint32_t bsp_ringBuffer_write(rbt_t rbt, uint8_t * data, uint32_t num_bytes);
uint32_t bsp_ringBuffer_get(rbt_t rbt, uint8_t ** data_p);
//uint32_t bsp_ringBuffer_get_write_left(void);
//uint32_t bsp_ringBuffer_get_read_left(void);

#endif /* BSP_RINGBUFFER_H_ */
