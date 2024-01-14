/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Data exchange between RPU and APU
 */

#include <stdint.h>
#include <stddef.h>

#include "xil_cache.h"

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
#define XCP_OUT_LEN					512
#define XCP_IN_ADDR 				0xFFFFC000
#define XCP_IN_LEN					512

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
static volatile size_t addr_w = 0;
static volatile size_t addr_r = 0;

// Todo remove debug variable
static volatile uint32_t cnt_msg_ocm_w = 0;
static volatile uint32_t cnt_msg_ocm_r = 0;

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
    Xil_DCacheFlushLine(XCP_IN_ADDR);
#endif
#ifdef APU
    *(uint32_t *)XCP_OUT_ADDR = 0;
    Xil_DCacheFlushLine(XCP_OUT_ADDR);
#endif
}

void rpu_apu_exchange_cache_invalidate_before_read(void)
{
	// TODO: The memory length that is flushed can be shortened to 2 or 3 messages
	// -> Then also make sure only 2 or 3 message are in the buffer at a time
#ifdef RPU
	Xil_DCacheInvalidateRange(XCP_IN_ADDR, XCP_IN_LEN);
#endif
#ifdef APU
	Xil_DCacheInvalidateRange(XCP_OUT_ADDR, XCP_OUT_LEN);
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

void rpu_apu_exchange_prepare_read(void)
{
#ifdef RPU
	addr_r = XCP_IN_ADDR;
#endif
#ifdef APU
	addr_r = XCP_OUT_ADDR;
#endif
}

void rpu_apu_exchange_prepare_write(void)
{
#ifdef RPU
	addr_w = XCP_OUT_ADDR;
#endif
#ifdef APU
	addr_w = XCP_IN_ADDR;
#endif
    *(uint32_t *)addr_w = 0;
}

void rpu_apu_exchange_writeOCM(uint8_t len, uint8_t *data)
{
	volatile uint8_t *dst_p = (volatile uint8_t *)(addr_w);

	// Write package len
    *(uint32_t *)dst_p = len;
    dst_p += 4;

    // Write payload
    memcpy_volatile(dst_p, data, len);
    dst_p += len;

    // Set next len to 0
    *(uint32_t *)dst_p = 0;

    // Write current OCM write address for the next call/entry
	addr_w = (size_t)dst_p;

    cnt_msg_ocm_w++;
}

int rpu_apu_exchange_readOCM(uint8_t *len, uint8_t **data_p)
{
	volatile uint8_t *src_p = (volatile uint8_t *)(addr_r);

	// Read len
	*len = *(uint32_t *)src_p;
	// Immediately 'delete' current message by setting its len to 0
	*(uint32_t *)src_p = 0;
	src_p += 4;

	// Is a package ready to read?
	if (*len == 0) {
		addr_r = XCP_OUT_ADDR;
		return 0;
	}

	// Set data_p to start of message
	*data_p = (uint8_t *)src_p;
	src_p += *len;

    // Write current OCM write address for the next call/entry
	addr_r = (size_t)src_p;

	cnt_msg_ocm_r++;

	return 1;
}
