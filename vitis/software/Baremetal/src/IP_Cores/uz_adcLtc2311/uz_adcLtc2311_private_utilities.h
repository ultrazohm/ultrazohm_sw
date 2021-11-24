#pragma once
#include "uz_adcLtc2311.h"
#include <stdint.h>
#include <stdbool.h>

uint32_t uz_adcLtc2311_cr_wait_for_value_acknowledgement(uint32_t base_address, uint32_t max_attempts);
uint32_t uz_adcLtc2311_spi_cr_wait_for_control_set_acknowledgement(uint32_t base_address, uint32_t max_attempts);
uint32_t uz_adcLtc2311_spi_cr_wait_for_control_reset_acknowledgement(uint32_t base_address, uint32_t max_attempts);
_Bool uz_adcLtc2311_check_32_bit_int_if_msb_not_set(uint32_t value);
_Bool uz_adcLtc2311_check_32_bit_int_if_not_more_sign_bits_set_than_spec(uint32_t value, uint32_t spec);

uint32_t uz_adcLtc2311_prepare_manual_operation(uz_adcLtc2311_t* self);
void uz_adcLtc2311_spi_set_ss_n(uint32_t base_address);
void uz_adcLtc2311_spi_reset_ss_n(uint32_t base_address);
void uz_adcLtc2311_spi_set_sclk(uint32_t base_address);
void uz_adcLtc2311_spi_reset_sclk(uint32_t base_address);

uint32_t uz_adcLtc2311_get_base_address(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_disable_manual_mode(uint32_t base_address, uint32_t max_attempts);
uint32_t uz_adcLtc2311_all_masked_bits_set_in_value(uint32_t value, uint32_t mask);

void uz_adcLtc2311_init_set_parameters(uz_adcLtc2311_t* self);
