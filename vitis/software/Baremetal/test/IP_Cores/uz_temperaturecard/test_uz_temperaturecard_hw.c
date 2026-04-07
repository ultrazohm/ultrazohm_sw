#ifdef TEST

#include "unity.h"
#include "uz_temperaturecard_hw.h"
#include "uz_temperaturecard.h"
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

void test_uz_TempCard_IF_hw_writeReg_success(void)
{
    uint32_t Test_Regdata = 42U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS, Test_Regdata);
    uz_TempCard_IF_hw_writeReg(TEST_BASE_ADDRESS, Test_Regdata);
    
}

void test_uz_TempCard_IF_hw_readReg_base_address_zero(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_readReg(0U));
}

void test_uz_TempCard_IF_hw_readReg_success(void)
{
    uint32_t test_ret_val = 0xF0F0F0F0U;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS, test_ret_val);
    TEST_ASSERT_EQUAL_UINT32(test_ret_val, uz_TempCard_IF_hw_readReg(TEST_BASE_ADDRESS));
}

void test_uz_TempCard_IF_hw_write_channel_group_A_configdata_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_write_channel_group_A_configdata(0U,0U));
}

void test_uz_TempCard_IF_hw_write_channel_group_B_configdata_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_write_channel_group_B_configdata(0U,0U));
}

void test_uz_TempCard_IF_hw_write_channel_group_C_configdata_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_write_channel_group_C_configdata(0U,0U));
}
void test_uz_TempCard_IF_hw_write_channel_group_A_configdata(void)
{
    
    uint32_t configdata[20] = {0U};

    for (uint32_t i=0;i<20;i++) {
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+ TempCard_IF_Config_A_0 + (i*CHANNEL_ADDRESS_INCREMENT), configdata[i]);
    }
    uz_TempCard_IF_hw_write_channel_group_A_configdata(TEST_BASE_ADDRESS, configdata);

    
}

void test_uz_TempCard_IF_hw_write_channel_group_B_configdata(void)
{
    
    uint32_t configdata[20] = {0U};

    for (uint32_t i=0;i<20;i++) {
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+ TempCard_IF_Config_B_0 + (i*CHANNEL_ADDRESS_INCREMENT), configdata[i]);
    }
    uz_TempCard_IF_hw_write_channel_group_B_configdata(TEST_BASE_ADDRESS, configdata);

    
}

void test_uz_TempCard_IF_hw_write_channel_group_C_configdata(void)
{
    
    uint32_t configdata[20] = {0U};

    for (uint32_t i=0;i<20;i++) {
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+ TempCard_IF_Config_C_0 + (i*CHANNEL_ADDRESS_INCREMENT), configdata[i]);
    }
    uz_TempCard_IF_hw_write_channel_group_C_configdata(TEST_BASE_ADDRESS, configdata);

    
}

void test_uz_TempCard_IF_hw_read_raw_value_channel_group_A_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_read_raw_value_channel_group_A(0U,0U));
}

void test_uz_TempCard_IF_hw_read_raw_value_channel_group_B_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_read_raw_value_channel_group_B(0U,0U));
}

void test_uz_TempCard_IF_hw_read_raw_value_channel_group_C_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_read_raw_value_channel_group_C(0U,0U));
}

void test_uz_TempCard_IF_hw_read_raw_value_channel_group_A(void)
{
    uint32_t test_result_raw = 0xF0F0F0F0U;
    uint32_t test_ch_number = 19U;

    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + TempCard_IF_Result_A_0 + (test_ch_number*CHANNEL_ADDRESS_INCREMENT), test_result_raw);

    TEST_ASSERT_EQUAL_UINT32(test_result_raw,uz_TempCard_IF_hw_read_raw_value_channel_group_A(TEST_BASE_ADDRESS, test_ch_number));
}

void test_uz_TempCard_IF_hw_read_raw_value_channel_group_B(void)
{
    uint32_t test_result_raw = 0xF0F0F0F0U;
    uint32_t test_ch_number = 13U;

    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + TempCard_IF_Result_B_0 + (test_ch_number*CHANNEL_ADDRESS_INCREMENT), test_result_raw);

    TEST_ASSERT_EQUAL_UINT32(test_result_raw,uz_TempCard_IF_hw_read_raw_value_channel_group_B(TEST_BASE_ADDRESS, test_ch_number));
}

void test_uz_TempCard_IF_hw_read_raw_value_channel_group_C(void)
{
    uint32_t test_result_raw = 0xF0F0F0F0U;
    uint32_t test_ch_number = 9U;

    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + TempCard_IF_Result_C_0 + (test_ch_number*CHANNEL_ADDRESS_INCREMENT), test_result_raw);

    TEST_ASSERT_EQUAL_UINT32(test_result_raw,uz_TempCard_IF_hw_read_raw_value_channel_group_C(TEST_BASE_ADDRESS, test_ch_number));
}

void test_uz_TempCard_IF_hw_writeCounterReg_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_writeCounterReg(0U,0U));
}

void test_uz_TempCard_IF_hw_writeCounterReg(void)
{
    uint32_t test_counter_val = 42U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+TempCard_IF_Counterreg, test_counter_val);

    uz_TempCard_IF_hw_writeCounterReg(TEST_BASE_ADDRESS, test_counter_val);
}

void test_uz_TempCard_IF_hw_readCounterReg_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_readCounterReg(0U));
}

void test_uz_TempCard_IF_hw_readCounterReg(void)
{
    uint32_t test_read_val = 4711U;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+TempCard_IF_Counterreg, test_read_val);
    TEST_ASSERT_EQUAL_UINT32(test_read_val, uz_TempCard_IF_hw_readCounterReg(TEST_BASE_ADDRESS));

}

void test_uz_TempCard_IF_hw_writeGlobalConfigReg_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_writeGlobalConfigReg(0U,0U));
}

void test_uz_TempCard_IF_hw_writeGlobalConfigReg(void)
{
    uint32_t reg_data = 42U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+TempCard_IF_GlobalConfig, reg_data);
    uz_TempCard_IF_hw_writeGlobalConfigReg(TEST_BASE_ADDRESS,reg_data);
    
}


void test_uz_TempCard_IF_hw_writeMuxConfigReg_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_writeMuxConfigReg(0U,0U));
}

void test_uz_TempCard_IF_hw_writeMuxConfigReg(void)
{
    uint32_t reg_data = 42U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+TempCard_IF_MuxConfig, reg_data);
    uz_TempCard_IF_hw_writeMuxConfigReg(TEST_BASE_ADDRESS,reg_data);
    
}

void test_uz_TempCard_IF_hw_readMuxConfigReg_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_readMuxConfigReg(0U));
}


void test_uz_TempCard_IF_hw_readGlobalConfigReg_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_TempCard_IF_hw_readGlobalConfigReg(0U));
}

#endif // TEST
