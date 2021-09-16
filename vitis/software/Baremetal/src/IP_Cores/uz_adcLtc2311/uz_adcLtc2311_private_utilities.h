#pragma once
#include <stdint.h>

int32_t uz_adcLtc2311_cr_wait_for_value_acknowledgement(uint32_t base_address, uint32_t max_attempts);