#ifdef TEST
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_resolverIP_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x43C00000 // random hex value that represents a fictional base address


#include "uz_resolverIP_hw.h"

void setUp(void)
{
}

void tearDown(void)
{
    //test123
}



void test_uz_resolverIP_hw_write_to_RESCON(void)
{
    int a=10;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+RESCON_Data_uz_resolverIP,a);
    uz_resolverIP_hw_write_RESCON(TEST_BASE_ADDRESS,a);
}

void test_uz_resolverIP_hw_write_to_RESDAT(void)
{
    int a=10;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+RESDAT_Data_uz_resolverIP,a);
    uz_resolverIP_hw_write_RESDAT(TEST_BASE_ADDRESS,a);
}

void test_uz_resolverIP_hw_write_to_RESADR(void)
{
    int a=10;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+RESADR_Data_uz_resolverIP,a);
    uz_resolverIP_hw_write_RESADR(TEST_BASE_ADDRESS,a);
}

void test_uz_resolverIP_hw_read_from_RESCON(void)
{
    int c=0;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+RESCON_Data_uz_resolverIP,c);
    int c_readback=uz_resolverIP_hw_read_RESCON(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c,c_readback);
}

void test_uz_resolverIP_hw_read_from_RESDAT(void)
{
    int c=0;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+RESDAT_Data_uz_resolverIP,c);
    int c_readback=uz_resolverIP_hw_read_RESDAT(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c,c_readback);
}

void test_uz_resolverIP_hw_read_from_RESADR(void)
{
    int c=0;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+RESADR_Data_uz_resolverIP,c);
    int c_readback=uz_resolverIP_hw_read_RESADR(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c,c_readback);
}

void test_uz_resolverIP_hw_read_from_RESRDA(void)
{
    int c=0;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+RESRDA_Data_uz_resolverIP,c);
    int c_readback=uz_resolverIP_hw_read_RESRDA(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c,c_readback);
}

void test_uz_resolverIP_hw_write_to_RESCON_with_zero_base_address(void)
{
    int a=10;
    uz_axi_write_int32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_hw_write_RESCON(0,a))
}

void test_uz_resolverIP_hw_write_to_RESDAT_with_zero_base_address(void)
{
    int a=10;
    uz_axi_write_int32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_hw_write_RESDAT(0,a))
}

void test_uz_resolverIP_hw_write_to_RESADR_with_zero_base_address(void)
{
    int a=10;
    uz_axi_write_int32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_hw_write_RESADR(0,a))
}

void test_uz_resolverIP_hw_read_RESCON_with_zero_base_address(void)
{
    int c=123;
    uz_axi_read_int32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_hw_read_RESCON(0));
}

void test_uz_resolverIP_hw_read_RESDAT_with_zero_base_address(void)
{
    int c=123;
    uz_axi_read_int32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_hw_read_RESDAT(0));
}

void test_uz_resolverIP_hw_read_RESRDA_with_zero_base_address(void)
{
    int c=123;
    uz_axi_read_int32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_hw_read_RESRDA(0));
}

void test_uz_resolverIP_hw_read_RESADR_with_zero_base_address(void)
{
    int c=123;
    uz_axi_read_int32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_hw_read_RESCON(0));
}

#endif // TEST
