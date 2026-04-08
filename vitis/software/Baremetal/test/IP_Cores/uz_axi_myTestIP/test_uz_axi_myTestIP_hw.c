#include "unity.h"
#include "uz_axi_myTestIP_hw.h"
#include <stdbool.h>
#include <stdint.h>
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_axi_myTestIP_hwAddresses.h"

#define BASE_ADDRESS 0x0F0000000U // random hex value that represents a fictional base address
#define ZERO_BASE_ADDRESS 0x00000000U


void test_uz_axi_myTestIP_hw_write_A_base_address_zero(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_axi_myTestIP_hw_write_A(ZERO_BASE_ADDRESS, 10));
}

void test_uz_axi_myTestIP_hw_write_B_base_address_zero(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_axi_myTestIP_hw_write_B(ZERO_BASE_ADDRESS, 10));
}

void test_uz_axi_myTestIP_hw_read_result_base_address_zero(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_axi_myTestIP_hw_read_result(ZERO_BASE_ADDRESS));
}

void test_uz_axi_myTestIP_hw_write_A(void) {
	int32_t testvalue = 10;
	uz_axi_write_int32_Expect(BASE_ADDRESS + XUZ_AXI_myTestIP_CONTROL_ADDR_A_DATA, testvalue);
	uz_axi_myTestIP_hw_write_A(BASE_ADDRESS, testvalue);
}

void test_uz_axi_myTestIP_hw_write_B(void) {
	int32_t testvalue = 10;
	uz_axi_write_int32_Expect(BASE_ADDRESS + XUZ_AXI_myTestIP_CONTROL_ADDR_B_DATA, testvalue);
	uz_axi_myTestIP_hw_write_B(BASE_ADDRESS, testvalue);
}

void test_uz_axi_myTestIP_hw_read_result(void) {
	int32_t expected_result = 42;
	uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS + XUZ_AXI_myTestIP_CONTROL_ADDR_RESULT_DATA, expected_result);
	uz_axi_myTestIP_hw_read_result(BASE_ADDRESS);
}
