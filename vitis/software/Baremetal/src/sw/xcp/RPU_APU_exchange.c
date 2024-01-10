/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Data exchange between RPU and APU
 */

#include <stdint.h>
#include <stddef.h>

#include "RPU_APU_exchange.h"
#include "xil_cache.h"

//#define APU
#define RPU
#if (!defined(APU) && !defined(RPU)) || (defined(APU) && defined(RPU))
	#error "Define either RPU or APU"
#endif

/*
 * Memory exchange via OCM
 * Memory layout:
 * Byte [0..3]: package len
 * Byte [4..(3 + len)]: payload
 * Byte [(4 + len)..(7 + len)]: 0. Indicator for OCM reader, this is end of
 *          messages. (If a package follows it will be overwritten with its
 *          actual length)
 */

/*-------------------------------------------------------------------
 * Types
 *-----------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * Configuration
 *-----------------------------------------------------------------*/
/*
 * OCM bank3 is reserved for javascope: Address: 0xFFFF0000, len 0x10000 (= 65K).
 * Place XCP data behind javascope memory in same bank3. Use the last 32K for this.
 */
#define XCP_OUT_ADDR				0xFFFF8000
#define XCP_OUT_LEN					0x00007000
#define XCP_IN_ADDR 				(XCP_OUT_ADDR + XCP_OUT_LEN)
#define XCP_IN_LEN					0x00001000

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
static volatile size_t addr_out_w = 0;
static volatile size_t addr_out_r = 0;
static volatile size_t addr_in_w = 0;
static volatile size_t addr_in_r = 0;

static volatile uint32_t cnt_msg_out_w = 0;
static volatile uint32_t cnt_msg_out_r = 0;

/*-------------------------------------------------------------------
 * Static functions
 *-----------------------------------------------------------------*/
static void memcpy_volatile(volatile uint8_t *dst, volatile uint8_t *src, int len)
{
	for (int i = 0; i < len; i++) {
		dst[i] = src[i];
	}
}

/*-------------------------------------------------------------------
 * Global functions
 *-----------------------------------------------------------------*/
void rpu_apu_exchange_init(void)
{
	// The CPU which reads the OCM area initializes it
#ifdef RPU
    *(uint32_t *)XCP_IN_ADDR = 0;
#endif
#ifdef APU
    *(uint32_t *)XCP_OUT_ADDR = 0;
#endif
}

void rpu_apu_exchange_cache_flush_before_read(void)
{
	// TODO: The memory length that is flushed can be shortened to 2 or 3 messages
	// -> Then also make sure only 2 or 3 message are in the buffer at a time
#ifdef RPU
	Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_LEN);
#endif
#ifdef APU
	Xil_DCacheFlushRange(XCP_OUT_ADDR, XCP_OUT_LEN);
#endif
}

void rpu_apu_exchange_cache_flush_after_write(void)
{
	// TODO: The memory length that is flushed can be shortened to 2 or 3 messages
	// -> Then also make sure only 2 or 3 message are in the buffer at a time
#ifdef RPU
	Xil_DCacheFlushRange(XCP_OUT_ADDR, XCP_OUT_LEN);
#endif
#ifdef APU
	Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_LEN);
#endif
}

void rpu_apu_exchange_prepare(rapu_exchange_t rapu)
{
	// TODO: Use #ifdef APU/RPU instead of switch
	switch (rapu) {
	case rapu_exchange_write_apu:
		addr_in_w = XCP_IN_ADDR;
		break;
	case rapu_exchange_write_rpu:
		addr_out_w = XCP_OUT_ADDR;
		break;
	case rapu_exchange_read_apu:
		addr_out_r = XCP_OUT_ADDR;
		break;
	case rapu_exchange_read_rpu:
		addr_in_r = XCP_IN_ADDR;
		break;
	}
}

void rpu_apu_exchange_writeOCM(rapu_exchange_t rapu, uint8_t len, uint8_t *data)
{
	// TODO: Use #ifdef APU/RPU instead of if/else
	volatile uint8_t *dst_p;
	if (rapu == rapu_exchange_write_apu) {
		dst_p = (volatile uint8_t *)(addr_in_w);
	} else if (rapu == rapu_exchange_write_rpu) {
		dst_p = (volatile uint8_t *)(addr_out_w);
	}

	// Write package len
    *(uint32_t *)dst_p = len;
    dst_p += 4;

    // Write payload
    memcpy_volatile(dst_p, data, len);
    dst_p += len;

    // Set next len to 0
    *(uint32_t *)dst_p = 0;

	// TODO: Use #ifdef APU/RPU instead of if/else
    // Write current OCM write address for the next call/entry
	if (rapu == rapu_exchange_write_apu) {
		addr_in_w = (size_t)dst_p;
	} else if (rapu == rapu_exchange_write_rpu) {
		addr_out_w = (size_t)dst_p;
	}

    // Todo remove debug variable
    cnt_msg_out_w++;
}

int rpu_apu_exchange_readOCM(rapu_exchange_t rapu, uint8_t *len, uint8_t **data_p)
{
	// TODO: Use #ifdef APU/RPU instead of if/else
	volatile uint8_t *src_p;
	if (rapu == rapu_exchange_read_apu) {
		src_p = (volatile uint8_t *)(addr_out_r);
	} else if (rapu == rapu_exchange_read_rpu) {
		src_p = (volatile uint8_t *)(addr_in_r);
	}

	// Read len
	*len = *(uint32_t *)src_p;
	// Immediately 'delete' current message by setting its len to 0
	*(uint32_t *)src_p = 0;
	src_p += 4;

	// Is a package ready to read?
	if (*len == 0) {
		addr_out_r = XCP_OUT_ADDR;
		return 0;
	}

	// Set data_p to start of message
	*data_p = (uint8_t *)src_p;
	src_p += *len;

	// TODO: Use #ifdef APU/RPU instead of if/else
    // Write current OCM write address for the next call/entry
	if (rapu == rapu_exchange_read_apu) {
		addr_out_r = (size_t)src_p;
	} else if (rapu == rapu_exchange_read_rpu) {
		addr_in_r = (size_t)src_p;
	}

    // Todo remove debug variable
	cnt_msg_out_r++;

	return 1;
}
