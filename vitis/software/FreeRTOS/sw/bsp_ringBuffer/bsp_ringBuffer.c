/*
 * bsp_ringBuffer.c
 *
 *  Created on: 24.06.2019
 *      Author: Jens
 */


/*
 * general ring buffer description:
 *
 * Ring buffer will be written from IRQ and read from main while(1){} loop.
 *
 * Synchronisation is ensured by leaving 1 element empty between read and write pointer.
 * Read pointer is only written by ringBuffer_read() and write pointer only by ringBuffer_write().
 *
 * Read pointer marks last read element.
 * Write pointer marks last written element.
 *
 * An element can be read if read_left > 0. Read_left is the distance between p_read to p_write
 * in ascending element count order.
 *    read_left =
 *    	if(p_write >= p_read)
 *    		p_write - p_read;
 *    	else
 *    		len - (p_read - p_write);
 *
 * Elements can be written if write_left > 1 (1 empty element is for IRQ safety..).
 * Write_left is the distance between p_write to p_read in ascending element count order.
 * This is the ring buffer length minus the read_left count.
 *    write_left = len - read_left - 1;
 *
 * Restrictions:
 *  - only read from 1 function without interrupt context
 *  - only write from 1 function (can be an interrupt) - no nested interrupts allowed!
 *
 */

#include "bsp_ringBuffer.h"
#include "xil_printf.h"
#include "xil_exception.h"

//====================================================================
// Configuration
//====================================================================
#define RING_BUFFER_ELEMENT_SIZE 	128
#define RING_BUFFER_NUM_ELEMENTS 	20000
#define RING_BUFFER_MAX_INDEX		(RING_BUFFER_NUM_ELEMENTS - 1)

//====================================================================
// Type definitions
//====================================================================
typedef struct ringBuffer_t_ {
	uint32_t idx_w;
	uint32_t idx_r;
	int fill_level;
	volatile uint32_t max_fill_level;
	uint8_t buf[RING_BUFFER_NUM_ELEMENTS][RING_BUFFER_ELEMENT_SIZE];
} ringBuffer_t;

//====================================================================
// Static variables
//====================================================================
static ringBuffer_t rb[rbt_num] = {0};

//====================================================================
// Global functions
//====================================================================
/*
 * @brief Init the ring buffer r/w pointer.
 */
void bsp_ringBuffer_init(void)
{
	for (int i = 0; i < rbt_num; i++) {
		rb[i].idx_r = 0;
		rb[i].idx_w = 0;
		rb[i].fill_level = 0;
		rb[i].max_fill_level = 0;
	}
}

/*
 * @brief Write an data element to the ring buffer.
 *
 * @param 	data Pointer to the data element.
 * @param	len Number of bytes to write to the ring buffer. Use 0 for RING_BUFFER_ELEMENT_SIZE.
 * @return	1 for success, 0 if write failed due to full ring buffer.
 */
uint32_t bsp_ringBuffer_write(rbt_t rbt, uint8_t * data, uint32_t num_bytes)
{
	ringBuffer_t *rb_p = &rb[rbt];

	if (rb_p->fill_level >= RING_BUFFER_NUM_ELEMENTS) {
		xil_printf("%s(): full\n", __func__);
		return 0;
	}

	rb_p->idx_w++;
	if (rb_p->idx_w >= RING_BUFFER_MAX_INDEX) {
		rb_p->idx_w = 0;
	}

	uint8_t *dst = rb_p->buf[rb_p->idx_w];
	memcpy(dst, data, num_bytes);

	// Increase fill level after the data is actually stored in the buffer
	//Xil_ExceptionDisable();
	rb_p->fill_level++;
	if (rb_p->fill_level > rb_p->max_fill_level)
		rb_p->max_fill_level = rb_p->fill_level;
	//Xil_ExceptionEnable();

	return 1;
}

/*
 * Get pointer to the last element stored in the ring buffer.
 *
 * @param	data_p Pointer that will be set to the address of the current read element.
 * @return	1 for success, 0 if no element is available.
 */
uint32_t bsp_ringBuffer_get(rbt_t rbt, uint8_t ** data_p)
{
	ringBuffer_t *rb_p = &rb[rbt];

	if (rb_p->fill_level <= 0) {
		return 0;
	}

	//Xil_ExceptionDisable();
	rb_p->fill_level--;
	//Xil_ExceptionEnable();

	rb_p->idx_r++;
	if (rb_p->idx_r >= RING_BUFFER_MAX_INDEX) {
		rb_p->idx_r = 0;
	}

	*data_p = rb_p->buf[rb_p->idx_r];

	return 1;
}
