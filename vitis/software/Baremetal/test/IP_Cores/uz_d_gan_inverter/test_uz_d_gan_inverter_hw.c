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
        uint32_t PWMFreqTicks_H1 = 10000;
        uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_Gan_Temp_1_period_Data_UZ_D_GaN_Inverter,PWMFreqTicks_H1);
        uint32_t PWMFreqTicks_H1_readback = uz_d_gan_inverter_get_PWMFreqTicks_H1(TEST_BASE_ADDRESS);
        TEST_ASSERT_EQUAL_INT(PWMFreqTicks_H1,PWMFreqTicks_H1_readback);
    }

    void test_uz_d_gan_inverter_hw_get_PWMFreqTicks_H1_with_zero_base_address(void)
    {
        uint32_t PWMFreqTicks_H1 = 10000;
        // Tell the test that we do not care how often this function is called
        uz_axi_read_uint32_IgnoreAndReturn(PWMFreqTicks_H1);
        // Test passes if an assert fails in the function under test
        TEST_ASSERT_FAIL_ASSERT(uz_d_gan_inverter_get_PWMFreqTicks_H1(0))
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
