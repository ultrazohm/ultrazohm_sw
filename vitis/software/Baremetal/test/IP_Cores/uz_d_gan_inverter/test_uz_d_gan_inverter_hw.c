#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_d_gan_inverter_hwAddresses.h"
#include "uz_d_gan_inverter_hw.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}


    void test_uz_d_gan_inverter_get_PWMFreqTicks_H1(void)
    {
        uint32_t PWMFreqTicks_H1 = 11000;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_1_period_Data_UZ_D_GaN_Inverter,PWMFreqTicks_H1);
        uint32_t PWMFreqTicks_H1_readback = uz_d_gan_inverter_get_PWMFreqTicks_H1(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMFreqTicks_H1,PWMFreqTicks_H1_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMFreqTicks_H1_with_zero_base_address(void)
    {
        uint32_t PWMFreqTicks_H1 = 11000;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMFreqTicks_H1);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMFreqTicks_H1(0))
    }

    void test_uz_d_gan_inverter_get_PWMhightimeTicks_H1(void)
    {
        uint32_t PWMhightimeTicks_H1 = 715;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_1_hightime_Data_UZ_D_GaN_Inverter,PWMhightimeTicks_H1);
        uint32_t PWMhightimeTicks_H1_readback = uz_d_gan_inverter_get_PWMhightimeTicks_H1(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMhightimeTicks_H1,PWMhightimeTicks_H1_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMhightimeTicks_H1_with_zero_base_address(void)
    {
        uint32_t PWMhightimeTicks_H1 = 715;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMhightimeTicks_H1);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMhightimeTicks_H1(0))
    }

    void test_uz_d_gan_inverter_get_PWMlowtimeTicks_H1(void)
    {
        uint32_t PWMlowtimeTicks_H1 = 10284;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_1_lowtime_Data_UZ_D_GaN_Inverter,PWMlowtimeTicks_H1);
        uint32_t PWMlowtimeTicks_H1_readback = uz_d_gan_inverter_get_PWMlowtimeTicks_H1(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMlowtimeTicks_H1,PWMlowtimeTicks_H1_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMlowtimeTicks_H1_with_zero_base_address(void)
    {
        uint32_t PWMlowtimeTicks_H1 = 10284;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMlowtimeTicks_H1);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMlowtimeTicks_H1(0));
    }

    void test_uz_d_gan_inverter_get_PWMdutyCycPerCent_H1(void)
    {
        uint32_t axi_read_tempAsDutyCyc = 109051904; //value in Q24 format
        float tempAsDutyCyc_returnedFloat = 6.5;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_1_dutycyc_Data_UZ_D_GaN_Inverter, axi_read_tempAsDutyCyc);
        float tempAsDutyCyc_returnedFloat_readback = uz_d_gan_inverter_get_PWMdutyCycPerCent_H1(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_FLOAT(tempAsDutyCyc_returnedFloat,tempAsDutyCyc_returnedFloat_readback); 
    }

    void test_uz_d_gan_inverter_get_PWMFreqTicks_L1(void)
    {
        uint32_t PWMFreqTicks_L1 = 11000;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_2_period_Data_UZ_D_GaN_Inverter,PWMFreqTicks_L1);
        uint32_t PWMFreqTicks_L1_readback = uz_d_gan_inverter_get_PWMFreqTicks_L1(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMFreqTicks_L1,PWMFreqTicks_L1_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMFreqTicks_L1_with_zero_base_address(void)
    {
        uint32_t PWMFreqTicks_L1 = 11000;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMFreqTicks_L1);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMFreqTicks_L1(0))
    }

    void test_uz_d_gan_inverter_get_PWMhightimeTicks_L1(void)
    {
        uint32_t PWMhightimeTicks_L1 = 715;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_2_hightime_Data_UZ_D_GaN_Inverter,PWMhightimeTicks_L1);
        uint32_t PWMhightimeTicks_L1_readback = uz_d_gan_inverter_get_PWMhightimeTicks_L1(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMhightimeTicks_L1,PWMhightimeTicks_L1_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMhightimeTicks_L1_with_zero_base_address(void)
    {
        uint32_t PWMhightimeTicks_L1 = 715;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMhightimeTicks_L1);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMhightimeTicks_L1(0))
    }

    void test_uz_d_gan_inverter_get_PWMlowtimeTicks_L1(void)
    {
        uint32_t PWMlowtimeTicks_L1 = 10285;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_2_lowtime_Data_UZ_D_GaN_Inverter,PWMlowtimeTicks_L1);
        uint32_t PWMlowtimeTicks_L1_readback = uz_d_gan_inverter_get_PWMlowtimeTicks_L1(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMlowtimeTicks_L1,PWMlowtimeTicks_L1_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMlowtimeTicks_L1_with_zero_base_address(void)
    {
        uint32_t PWMlowtimeTicks_L1 = 10285;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMlowtimeTicks_L1);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMlowtimeTicks_L1(0));
    }

    void test_uz_d_gan_inverter_get_PWMdutyCycPerCent_L1(void)
    {
        uint32_t axi_read_tempAsDutyCyc = 109051904; //value in Q24 format
        float tempAsDutyCyc_returnedFloat = 6.5;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_2_dutycyc_Data_UZ_D_GaN_Inverter, axi_read_tempAsDutyCyc);
        float tempAsDutyCyc_returnedFloat_readback = uz_d_gan_inverter_get_PWMdutyCycPerCent_L1(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_FLOAT(tempAsDutyCyc_returnedFloat,tempAsDutyCyc_returnedFloat_readback); 
    }

       void test_uz_d_gan_inverter_get_PWMFreqTicks_H2(void)
    {
        uint32_t PWMFreqTicks_H2 = 11000;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_3_period_Data_UZ_D_GaN_Inverter,PWMFreqTicks_H2);
        uint32_t PWMFreqTicks_H2_readback = uz_d_gan_inverter_get_PWMFreqTicks_H2(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMFreqTicks_H2,PWMFreqTicks_H2_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMFreqTicks_H2_with_zero_base_address(void)
    {
        uint32_t PWMFreqTicks_H2 = 11000;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMFreqTicks_H2);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMFreqTicks_H2(0))
    }

    void test_uz_d_gan_inverter_get_PWMhightimeTicks_H2(void)
    {
        uint32_t PWMhightimeTicks_H2 = 715;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_3_hightime_Data_UZ_D_GaN_Inverter,PWMhightimeTicks_H2);
        uint32_t PWMhightimeTicks_H2_readback = uz_d_gan_inverter_get_PWMhightimeTicks_H2(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMhightimeTicks_H2,PWMhightimeTicks_H2_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMhightimeTicks_H2_with_zero_base_address(void)
    {
        uint32_t PWMhightimeTicks_H2 = 715;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMhightimeTicks_H2);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMhightimeTicks_H2(0))
    }

    void test_uz_d_gan_inverter_get_PWMlowtimeTicks_H2(void)
    {
        uint32_t PWMlowtimeTicks_H2 = 10285;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_3_lowtime_Data_UZ_D_GaN_Inverter,PWMlowtimeTicks_H2);
        uint32_t PWMlowtimeTicks_H2_readback = uz_d_gan_inverter_get_PWMlowtimeTicks_H2(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMlowtimeTicks_H2,PWMlowtimeTicks_H2_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMlowtimeTicks_H2_with_zero_base_address(void)
    {
        uint32_t PWMlowtimeTicks_H2 = 10285;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMlowtimeTicks_H2);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMlowtimeTicks_H2(0));
    }

    void test_uz_d_gan_inverter_get_PWMdutyCycPerCent_H2(void)
    {
        uint32_t axi_read_tempAsDutyCyc = 109051904; //value in Q24 format
        float tempAsDutyCyc_returnedFloat = 6.5;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_3_dutycyc_Data_UZ_D_GaN_Inverter, axi_read_tempAsDutyCyc);
        float tempAsDutyCyc_returnedFloat_readback = uz_d_gan_inverter_get_PWMdutyCycPerCent_H2(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_FLOAT(tempAsDutyCyc_returnedFloat,tempAsDutyCyc_returnedFloat_readback); 
    }

       void test_uz_d_gan_inverter_get_PWMFreqTicks_L2(void)
    {
        uint32_t PWMFreqTicks_L2 = 11000;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_4_period_Data_UZ_D_GaN_Inverter,PWMFreqTicks_L2);
        uint32_t PWMFreqTicks_L2_readback = uz_d_gan_inverter_get_PWMFreqTicks_L2(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMFreqTicks_L2,PWMFreqTicks_L2_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMFreqTicks_L2_with_zero_base_address(void)
    {
        uint32_t PWMFreqTicks_L2 = 11000;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMFreqTicks_L2);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMFreqTicks_L2(0))
    }

    void test_uz_d_gan_inverter_get_PWMhightimeTicks_L2(void)
    {
        uint32_t PWMhightimeTicks_L2 = 715;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_4_hightime_Data_UZ_D_GaN_Inverter,PWMhightimeTicks_L2);
        uint32_t PWMhightimeTicks_L2_readback = uz_d_gan_inverter_get_PWMhightimeTicks_L2(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMhightimeTicks_L2,PWMhightimeTicks_L2_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMhightimeTicks_L2_with_zero_base_address(void)
    {
        uint32_t PWMhightimeTicks_L2 = 715;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMhightimeTicks_L2);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMhightimeTicks_L2(0))
    }

    void test_uz_d_gan_inverter_get_PWMlowtimeTicks_L2(void)
    {
        uint32_t PWMlowtimeTicks_L2 = 10285;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_4_lowtime_Data_UZ_D_GaN_Inverter,PWMlowtimeTicks_L2);
        uint32_t PWMlowtimeTicks_L2_readback = uz_d_gan_inverter_get_PWMlowtimeTicks_L2(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMlowtimeTicks_L2,PWMlowtimeTicks_L2_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMlowtimeTicks_L2_with_zero_base_address(void)
    {
        uint32_t PWMlowtimeTicks_L2 = 10285;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMlowtimeTicks_L2);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMlowtimeTicks_L2(0));
    }

    void test_uz_d_gan_inverter_get_PWMdutyCycPerCent_L2(void)
    {
        uint32_t axi_read_tempAsDutyCyc = 109051904; //value in Q24 format
        float tempAsDutyCyc_returnedFloat = 6.5;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_4_dutycyc_Data_UZ_D_GaN_Inverter, axi_read_tempAsDutyCyc);
        float tempAsDutyCyc_returnedFloat_readback = uz_d_gan_inverter_get_PWMdutyCycPerCent_L2(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_FLOAT(tempAsDutyCyc_returnedFloat,tempAsDutyCyc_returnedFloat_readback); 
    }

       void test_uz_d_gan_inverter_get_PWMFreqTicks_H3(void)
    {
        uint32_t PWMFreqTicks_H3 = 11000;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_5_period_Data_UZ_D_GaN_Inverter,PWMFreqTicks_H3);
        uint32_t PWMFreqTicks_H3_readback = uz_d_gan_inverter_get_PWMFreqTicks_H3(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMFreqTicks_H3,PWMFreqTicks_H3_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMFreqTicks_H3_with_zero_base_address(void)
    {
        uint32_t PWMFreqTicks_H3 = 11000;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMFreqTicks_H3);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMFreqTicks_H3(0))
    }

    void test_uz_d_gan_inverter_get_PWMhightimeTicks_H3(void)
    {
        uint32_t PWMhightimeTicks_H3 = 715;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_5_hightime_Data_UZ_D_GaN_Inverter,PWMhightimeTicks_H3);
        uint32_t PWMhightimeTicks_H3_readback = uz_d_gan_inverter_get_PWMhightimeTicks_H3(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMhightimeTicks_H3,PWMhightimeTicks_H3_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMhightimeTicks_H3_with_zero_base_address(void)
    {
        uint32_t PWMhightimeTicks_H3 = 715;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMhightimeTicks_H3);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMhightimeTicks_H3(0))
    }

    void test_uz_d_gan_inverter_get_PWMlowtimeTicks_H3(void)
    {
        uint32_t PWMlowtimeTicks_H3 = 10285;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_5_lowtime_Data_UZ_D_GaN_Inverter,PWMlowtimeTicks_H3);
        uint32_t PWMlowtimeTicks_H3_readback = uz_d_gan_inverter_get_PWMlowtimeTicks_H3(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMlowtimeTicks_H3,PWMlowtimeTicks_H3_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMlowtimeTicks_H3_with_zero_base_address(void)
    {
        uint32_t PWMlowtimeTicks_H3 = 10285;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMlowtimeTicks_H3);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMlowtimeTicks_H3(0));
    }

    void test_uz_d_gan_inverter_get_PWMdutyCycPerCent_H3(void)
    {
        uint32_t axi_read_tempAsDutyCyc = 109051904; //value in Q24 format
        float tempAsDutyCyc_returnedFloat = 6.5;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_5_dutycyc_Data_UZ_D_GaN_Inverter, axi_read_tempAsDutyCyc);
        float tempAsDutyCyc_returnedFloat_readback = uz_d_gan_inverter_get_PWMdutyCycPerCent_H3(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_FLOAT(tempAsDutyCyc_returnedFloat,tempAsDutyCyc_returnedFloat_readback); 
    }

       void test_uz_d_gan_inverter_get_PWMFreqTicks_L3(void)
    {
        uint32_t PWMFreqTicks_L3 = 11000;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_6_period_Data_UZ_D_GaN_Inverter,PWMFreqTicks_L3);
        uint32_t PWMFreqTicks_L3_readback = uz_d_gan_inverter_get_PWMFreqTicks_L3(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMFreqTicks_L3,PWMFreqTicks_L3_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMFreqTicks_L3_with_zero_base_address(void)
    {
        uint32_t PWMFreqTicks_L3 = 11000;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMFreqTicks_L3);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMFreqTicks_L3(0))
    }

    void test_uz_d_gan_inverter_get_PWMhightimeTicks_L3(void)
    {
        uint32_t PWMhightimeTicks_L3 = 715;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_6_hightime_Data_UZ_D_GaN_Inverter,PWMhightimeTicks_L3);
        uint32_t PWMhightimeTicks_L3_readback = uz_d_gan_inverter_get_PWMhightimeTicks_L3(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMhightimeTicks_L3,PWMhightimeTicks_L3_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMhightimeTicks_L3_with_zero_base_address(void)
    {
        uint32_t PWMhightimeTicks_L3 = 715;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMhightimeTicks_L3);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMhightimeTicks_L3(0))
    }

    void test_uz_d_gan_inverter_get_PWMlowtimeTicks_L3(void)
    {
        uint32_t PWMlowtimeTicks_L3 = 10285;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_6_lowtime_Data_UZ_D_GaN_Inverter,PWMlowtimeTicks_L3);
        uint32_t PWMlowtimeTicks_L3_readback = uz_d_gan_inverter_get_PWMlowtimeTicks_L3(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMlowtimeTicks_L3,PWMlowtimeTicks_L3_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMlowtimeTicks_L3_with_zero_base_address(void)
    {
        uint32_t PWMlowtimeTicks_L3 = 10285;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMlowtimeTicks_L3);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMlowtimeTicks_L3(0));
    }

    void test_uz_d_gan_inverter_get_PWMdutyCycPerCent_L3(void)
    {
        uint32_t axi_read_tempAsDutyCyc = 109051904; //value in Q24 format
        float tempAsDutyCyc_returnedFloat = 6.5;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_6_dutycyc_Data_UZ_D_GaN_Inverter, axi_read_tempAsDutyCyc);
        float tempAsDutyCyc_returnedFloat_readback = uz_d_gan_inverter_get_PWMdutyCycPerCent_L3(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_FLOAT(tempAsDutyCyc_returnedFloat,tempAsDutyCyc_returnedFloat_readback); 
    } 

    void test_uz_d_gan_inverter_hw_get_OC(void)
    {
        uint32_t axi_read_OC = 63;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_GaN_OC_Data_UZ_D_GaN_Inverter,axi_read_OC);
        uint32_t axi_read_OC_readback = uz_d_gan_inverter_get_OC_GaN(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(axi_read_OC,axi_read_OC_readback);
    }

    void test_uz_D_gan_inverter_hw_get_OC_with_zero_base_address(void)
    {
        uint32_t axi_read_OC = 63;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(axi_read_OC);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_OC_GaN(0));
    }

    void test_uz_d_gan_inverter_hw_get_FAULT(void)
    {
        uint32_t axi_read_FAULT = 63;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_GaN_FAULT_Data_UZ_D_GaN_Inverter,axi_read_FAULT);
        uint32_t axi_read_FAULT_readback = uz_d_gan_inverter_get_FAULT_GaN(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(axi_read_FAULT,axi_read_FAULT_readback);
    }

    void test_uz_D_gan_inverter_hw_get_FAULT_with_zero_base_address(void)
    {
        uint32_t axi_read_FAULT = 63;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(axi_read_FAULT);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_FAULT_GaN(0));
    }

    void test_uz_d_gan_inverter_hw_get_I_DIAG(void)
    {
        uint32_t axi_read_I_DIAG = 15;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_I_DIAG_Data_UZ_D_GaN_Inverter,axi_read_I_DIAG);
        uint32_t axi_read_I_DIAG_readback = uz_d_gan_inverter_get_I_DIAG(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(axi_read_I_DIAG,axi_read_I_DIAG_readback);
    }

    void test_uz_D_gan_inverter_hw_get_I_DIAG_with_zero_base_address(void)
    {
        uint32_t axi_read_I_DIAG = 15;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(axi_read_I_DIAG);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_I_DIAG(0));
    }            
    
    void test_uz_d_gan_inverter_hw_set_PWM_EN(void)
    {
        uint32_t PWM_on_off = true;
        uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + AXI_PWM_Enable_Data_UZ_D_GaN_Inverter, PWM_on_off);
        uz_d_gan_inverter_hw_set_PWM_EN(TEST_BASE_ADDRESS, PWM_on_off);
    }

    void test_uz_d_gan_inverter_hw_set_PWM_EN_with_zero_base_address(void)
    {
        uint32_t PWM_on_off = true;
        // Tell the test that we do not care how often this function is called
        uz_axi_write_uint32_Ignore();
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_hw_set_PWM_EN(0,PWM_on_off))
    }
#endif // TEST
