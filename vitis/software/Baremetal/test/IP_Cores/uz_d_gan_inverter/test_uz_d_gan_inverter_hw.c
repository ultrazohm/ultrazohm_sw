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

    void uz_d_gan_inverter_hw_write_PWM_on_off(uint32_t base_address, uint32_t PWM_on_off){
        uz_axi_write_uint32(base_address+AXI_PWM_Enable_Data_UZ_D_GaN_Inverter, PWM_on_off);
    }

    void test_uz_d_gan_inverter_hw_set_PWM_EN(void)
    {
        uint32_t PWM_on_off = true;
        uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+AXI_PWM_Enable_Data_UZ_D_GaN_Inverter, PWM_on_off);
        uz_d_gan_inverter_hw_write_PWM_on_off(TEST_BASE_ADDRESS, PWM_on_off);
    }

#endif // TEST
