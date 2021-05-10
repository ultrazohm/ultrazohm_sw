#pragma once
#include "uz_axiTestIP.h"

struct uz_axiTestIP {
	const uint32_t base_address;
	bool is_ready;
	int32_t A_int32_t;
	int32_t B_int32_t;
	int32_t C_int32_t;
	float A_float;
	float B_float;
	float C_float;
};
