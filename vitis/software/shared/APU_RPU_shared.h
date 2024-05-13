//APU_RPU_shared.h
#pragma once
// OCM Bank Adresses
// See UG1085 v2.4 table 18-1 OCM Mapping Summary (https://docs.amd.com/r/en-US/ug1085-zynq-ultrascale-trm)

#define MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU 	0xFFFD0000 // bank 1 is for r5->a53 user data
#define MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU 	0xFFFE0000 // bank 2 is for a53->r5 user data
#define MEM_SHARED_START_OCM_BANK_3_JAVASCOPE 	0xFFFF0000 // bank 3 is for r5->a53 javascope
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

struct APU_to_RPU_user_data_t
{
	// create variables that you want to share from A53 to R5
};

struct RPU_to_APU_user_data_t
{
	// create variables that you want to share from R5 to A53
};
