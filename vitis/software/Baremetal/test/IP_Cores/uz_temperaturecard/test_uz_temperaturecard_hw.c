#ifdef TEST

#include "unity.h"
#include "uz_temperaturecard_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_TempCard_IF_hw_Reset_base_address_zero(void)
{
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_Reset(0U));
    
}

void test_uz_TempCard_IF_hw_Reset_success(void)
{
    uint32_t Test_Regdata1 = 42U & ~(0x02U);
    uint32_t Test_Regdata2 = 42U | 0x02U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + TempCard_IF_Controlreg, Test_Regdata1);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + TempCard_IF_Controlreg, Test_Regdata2);
    uz_axi_read_uint32_IgnoreAndReturn(Test_Regdata1);
    uz_axi_read_uint32_IgnoreAndReturn(Test_Regdata2);

    uz_TempCard_IF_hw_Reset(TEST_BASE_ADDRESS);    
    
}

void test_uz_TempCard_IF_hw_Start_base_address_zero(void)
{
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_Start(0U));
    
}

void test_uz_TempCard_IF_hw_Start_success(void)
{
    uint32_t Test_Regdata = 42U | 0x01U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + TempCard_IF_Controlreg, Test_Regdata);
    uz_axi_read_uint32_IgnoreAndReturn(Test_Regdata);
    
    uz_TempCard_IF_hw_Start(TEST_BASE_ADDRESS);    
    
}

void test_uz_TempCard_IF_hw_Stop_base_address_zero(void)
{
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_Stop(0U));
    
}

void test_uz_TempCard_IF_hw_Stop_success(void)
{
    uint32_t Test_Regdata = 42U & ~(0x01U);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + TempCard_IF_Controlreg, Test_Regdata);
    uz_axi_read_uint32_IgnoreAndReturn(Test_Regdata);
    
    uz_TempCard_IF_hw_Stop(TEST_BASE_ADDRESS);    
    
}

void test_uz_TempCard_IF_hw_writeReg_base_address_zero(void)
{
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_writeReg(0U, 0U));
    
}

#endif // TEST
