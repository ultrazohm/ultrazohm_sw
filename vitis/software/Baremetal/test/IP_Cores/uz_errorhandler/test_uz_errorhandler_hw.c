#ifdef TEST

#include "unity.h"

#include "uz_errorhandler_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_errorhandler_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_errorhandler_hw_write_to_ERROR(void)
{
    int a=-10;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+ERROR_uint32_Data_uz_axi_errorHandler,a);
    uz_errorhandler_hw_write_ERROR(TEST_BASE_ADDRESS,a);
}

void test_uz_errorhandler_hw_write_to_MASK(void)
{
    int b=100;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+MASK_uint32_Data_uz_axi_errorHandler,b);
    uz_errorhandler_hw_write_MASK(TEST_BASE_ADDRESS,b);
}

void test_uz_errorhandler_hw_read_from_ERROR(void)
{
    int c=101230;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+ERROR_uint32_Data_uz_axi_errorHandler,c);
    int c_readback=uz_errorhandler_hw_read_ERROR(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c,c_readback);
}

void test_uz_errorhandler_hw_read_from_MASK(void)
{
    int c=101230;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+MASK_uint32_Data_uz_axi_errorHandler,c);
    int c_readback=uz_errorhandler_hw_read_MASK(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c,c_readback);
}

void test_uz_errorhandler_hw_read_ERROR_with_zero_base_address(void)
{
    int c=123;
    // Ignores how often the read function is called and returns (c)
    uz_axi_read_int32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_errorhandler_hw_read_ERROR(0));
}

void test_uz_errorhandler_hw_read_MASK_with_zero_base_address(void)
{
    int c=123;
    // Ignores how often the read function is called and returns (c)
    uz_axi_read_int32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_errorhandler_hw_read_MASK(0));
}

void test_uz_errorhandler_hw_write_to_ERROR_with_zero_base_address(void)
{
    int b=10;
    uz_axi_write_int32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_errorhandler_hw_write_ERROR(0,b));
}

void test_uz_errorhandler_hw_write_to_MASK_with_zero_base_address(void)
{
    int a=-10;
    uz_axi_write_int32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_errorhandler_hw_write_MASK(0,a));
}

#endif // TEST
