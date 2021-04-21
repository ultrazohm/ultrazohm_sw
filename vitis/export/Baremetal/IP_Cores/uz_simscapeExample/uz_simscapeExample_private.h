#pragma once
#include "uz_simscapeExample.h"

struct uz_simscapeExample {
	const uint32_t base_address;
	bool is_ready;
	float Vin;
	float IR;
	float Iout;
	float Vdiode;
	float amp;
	float freq_Hz;
	float sine;
};
