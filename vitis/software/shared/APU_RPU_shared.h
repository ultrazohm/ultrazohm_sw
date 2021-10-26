//APU_RPU_shared.h

#pragma once

// OCM Bank 3 starts at         0xFFFF0000
// See UG1085 page 533 (https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf#G20.375357)

#define MEM_SHARED_START 	0xFFFF0000
#define JS_CHANNELS 		20

// update by hand when changing JS_CHANNELS
// Bank 3 of OCM has 64 KB, thus a maximum of 2^16/32=2048 float values can be stored
#define JAVASCOPE_DATA_SIZE_2POW  	128


struct javascope_data_t
{
	uint32_t    status;
	uint32_t    slowDataContent;
	uint32_t    slowDataID;
	float       scope_ch[JS_CHANNELS];
};
