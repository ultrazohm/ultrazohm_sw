// "Copyright [year] <Copyright Owner>"
#ifdef TEST  // NOLINT
#include <stdint.h>

#include "unity.h"  // NOLINT

#include "uz_EnDat.h"
#include "test_assert_with_exception.h"  // NOLINT
#include "mock_uz_EnDat_hw.h"  // Mock the _hw functions to isolate testing


#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U


void setUp(void) {
}

void tearDown(void) {
}

void test_uz_EnDat_fail_assert_if_base_address_is_zero(void) {
    struct uz_EnDat_config_t config = {
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ
    };
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_init(config));
}

void test_uz_EnDat_fail_assert_if_ip_frequency_is_zero(void) {
    struct uz_EnDat_config_t config = {
        .base_address = TEST_BASE_ADDRESS
    };
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_init(config));
}


void test_uz_EnDat_fail_assert_if_write_control_and_divider_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_write_control_and_divider(NULL, 0, 0));
}


void test_uz_EnDat_fail_assert_if_write_factor_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_write_factor(NULL, 0, 0));
}



void test_uz_EnDat_fail_assert_if_read_statusword_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_read_statusword(NULL));
}




void test_uz_EnDat_fail_assert_if_read_pos_tx_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_read_pos(NULL, 0));
}

void test_uz_EnDat_fail_assert_if_read_crc_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_read_crc(NULL));
}

void test_uz_EnDat_fail_assert_if_set_default_values_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_set_default_values(NULL));
}




#endif  // TEST
