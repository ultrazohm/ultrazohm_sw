#ifdef TEST

#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_myIP_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

#include "unity.h"

#include "uz_myIP_hw.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void  test_uz_myIP_hw_write_to_A(void)
{
    int32_t a = 10;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+A_int32_Data_uz_axi_testIP,a);
    uz_myIP_hw_write_A(TEST_BASE_ADDRESS,a);
}

void test_uz_myIP_hw_write_to_A_with_zero_base_address(void)
{
    int32_t a=10;
    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_myIP_hw_write_A(0,a))
}

void test_uz_myIP_hw_write_to_B(void)
{
    int32_t b=100;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+B_int32_Data_uz_axi_testIP,b);
    uz_myIP_hw_write_B(TEST_BASE_ADDRESS,b);
}

void test_uz_myIP_hw_write_to_B_with_zero_base_address(void)
{
    int32_t b=2;
    uz_axi_write_int32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_myIP_hw_write_B(0,b))
}

void test_uz_myIP_hw_read_from_C(void)
{
    int32_t c=101230;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+C_int32_Data_uz_axi_testIP,c);
    int c_readback=uz_myIP_hw_read_C(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c,c_readback);
}

void test_uz_myIP_hw_read_C_with_zero_base_address(void)
{
    int32_t c=123;
    // Ignores how often the read function is called and returns (c)
    uz_axi_read_int32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_myIP_hw_read_C(0));
}


//unsigned int

void  test_uz_myIP_hw_write_to_A_uint(void)
{
    uint32_t a = 10;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+A_uint32_Data_uz_axi_testIP,a);
    uz_myIP_hw_write_A_uint(TEST_BASE_ADDRESS,a);
}

void test_uz_myIP_hw_write_to_A_uint_with_zero_base_address(void)
{
    uint32_t a=10;
    // Tell the test that we do not care how often this function is called
    uz_axi_write_uint32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_myIP_hw_write_A_uint(0,a))
}

void test_uz_myIP_hw_write_to_B_uint(void)
{
    uint32_t b=100;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+B_uint32_Data_uz_axi_testIP,b);
    uz_myIP_hw_write_B_uint(TEST_BASE_ADDRESS,b);
}

void test_uz_myIP_hw_write_to_B_uint_with_zero_base_address(void)
{
    uint32_t b=2;
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_myIP_hw_write_B_uint(0,b))
}

void test_uz_myIP_hw_read_from_C_uint(void)
{
    uint32_t c=101230;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+C_uint32_Data_uz_axi_testIP,c);
    uint32_t c_readback=uz_myIP_hw_read_C_uint(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c,c_readback);
}

void test_uz_myIP_hw_read_C_uint_with_zero_base_address(void)
{
    uint32_t c=123;
    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_myIP_hw_read_C_uint(0));
}

#endif // TEST
