#ifdef TEST

#include "unity.h"
#include "uz_axi_myTestIP.h"
#include "mock_uz_axi_myTestIP_hw.h"
#include "test_assert_with_exception.h"

#define TEST_BASE_ADDRESS 0x000F0000

uz_axi_myTestIP* successful_init(void);
uz_axi_myTestIP* successful_init(void) {
	struct uz_axi_myTestIP_config_t config = {
		.base_address = TEST_BASE_ADDRESS,
		.ip_clk_frequency_Hz = 100000000U};
	uz_axi_myTestIP* instance = uz_axi_myTestIP_init(config);
	return(instance);
}

void test_uz_axi_myTestIP_init_successful(void) {
	successful_init();
}

void test_uz_axi_myTestIP_multiply_assert_NULL(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_axi_myTestIP_multiply(NULL, 5, 10));
}

void test_uz_axi_myTestIP_multiply(void) {
	uz_axi_myTestIP* instance = successful_init();
	uz_axi_myTestIP_hw_write_A_Expect(TEST_BASE_ADDRESS, 5);
	uz_axi_myTestIP_hw_write_B_Expect(TEST_BASE_ADDRESS, 10);
	uz_axi_myTestIP_hw_read_result_ExpectAndReturn(TEST_BASE_ADDRESS, 50);
	int32_t result = uz_axi_myTestIP_multiply(instance, 5, 10);
	TEST_ASSERT_EQUAL_INT32(50, result);
}

#endif // TEST
