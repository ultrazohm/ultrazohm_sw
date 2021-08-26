//APU_RPU_shared.h

#pragma once

// OCM starts at 				0xFFFF0000
// DDR free region starting at 	0x7FFF0000

#define MEM_SHARED_START 	0xFFFF0000
#define JS_CHANNELS 		20

// update by hand when changing JS_CHANNELS
#define JAVASCOPE_DATA_SIZE_2POW  	128
#define JAVASCOPE_DATA_SIZE  		92 //= sizeof(JAVASCOPE_DATA_STRUCT);


struct javascope_data_t
{
	uint32_t    status;
	uint32_t    slowDataContent;
	uint32_t    slowDataID;
	float       scope_ch[JS_CHANNELS];
};

// Rounding up to next power of 2
//uint32_t next_pow2(uint32_t x) { 	return x == 1 ? 1 : 1<<(32-__builtin_clz(x-1)); }


