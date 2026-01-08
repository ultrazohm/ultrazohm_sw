//APU_RPU_shared.h

#pragma once

// OCM Bank 3 starts at         0xFFFF0000
// See UG1085 page 533 (https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf#G20.375357)

#define MEM_SHARED_START 	0xFFFF0000
#define JS_CHANNELS 		20

// update by hand when changing JS_CHANNELS
// Bank 3 of OCM has 64 KB, thus a maximum of 16K float values can be stored
#define JAVASCOPE_DATA_SIZE_2POW  	128


struct javascope_data_t
{
	uint32_t    status;
	float	    slowDataContent;
	uint32_t    slowDataID;
	float       scope_ch[JS_CHANNELS];
};

struct APU_to_RPU_t
{
	uint32_t id;
	float value;
};

// Unidirectional data transfer A53 (APU) -> R5 (RPU)
struct data_A53_2_R5_t
{
	float Data1;
	float Data2;
	float Data3;
};

// Unidirectional data transfer R5 (RPU) -> A53 (APU)
struct data_R5_2_A53_t
{
	float Data1;
	float Data2;
	float Data3;
};
