#ifdef TEST

#include "unity.h"
#include "uz_HLS_testIP.h"
#include "mock_uz_HLS_testIP_hw.h"
#include "test_assert_with_exception.h"

#define TEST_BASE_ADDRESS 0x000F0000

uz_HLS_testIP* successful_init(void);
uz_HLS_testIP* successful_init(void) {
	struct uz_HLS_testIP_config_t config = {
		.base_address = TEST_BASE_ADDRESS,
		.ip_clk_frequency_Hz = 100000000U};
	uz_HLS_testIP* instance = uz_HLS_testIP_init(config);
	return(instance);
}

void test_uz_HLS_testIP_init_successful(void) {
	successful_init();
}

void test_uz_HLS_testIP_multiply_assert_NULL(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_HLS_testIP_multiply(NULL, 5, 10));
}

void test_uz_HLS_testIP_multiply(void) {
	uz_HLS_testIP* instance = successful_init();
	uz_HLS_testIP_hw_write_A_Expect(TEST_BASE_ADDRESS, 5);
	uz_HLS_testIP_hw_write_B_Expect(TEST_BASE_ADDRESS, 10);
	uz_HLS_testIP_hw_read_result_ExpectAndReturn(TEST_BASE_ADDRESS, 50);
	int32_t result = uz_HLS_testIP_multiply(instance, 5, 10);
	TEST_ASSERT_EQUAL_INT32(50, result);
}

#endif // TEST
