#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "uz_axiTestIP2.h"
struct uz_axiTestIP2 {
	const uint32_t base_address;
	bool is_ready;
	int32_t A;
	int32_t B;
	int32_t C;
};
