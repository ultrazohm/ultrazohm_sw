#pragma once
#include <stdint.h>
#include <stdbool.h>

int32_t uz_adcLtc2311_cr_wait_for_value_acknowledgement(uint32_t base_address, uint32_t max_attempts);
_Bool uz_adcLtc2311_check_32_bit_int_if_msb_not_set(uint32_t value);
_Bool uz_adcLtc2311_check_32_bit_int_if_not_more_sign_bits_set_than_spec(uint32_t value, uint32_t spec);