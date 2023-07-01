#pragma once
#include "uz_interlockDeadtime2L.h"

struct uz_interlockDeadtime2L {
	const uint32_t base_address;
	const int clock_frequency_MHz;
	bool is_ready;
	float max_deadtime_us;
	float deadtime_us;
	const bool inverse_bottom_switch;
};
