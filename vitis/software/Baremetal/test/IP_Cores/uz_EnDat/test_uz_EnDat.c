#ifdef TEST

#include "unity.h"

#include "uz_EnDat.h"
#include "test_assert_with_exception.h"
#include "mock_uz_EnDat_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_EnDat_fail_assert_if_base_address_is_zero(void)
{
    struct uz_EnDat_config_t config={
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_init(config));
}

void test_uz_EnDat_fail_assert_if_ip_frequency_is_zero(void)
{
    struct uz_EnDat_config_t config={
        .base_address=TEST_BASE_ADDRESS
    };
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_init(config));
}


void test_uz_EnDat_fail_assert_if_write_control_and_divider_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_write_control_and_divider(NULL,0,0));

}


void test_uz_EnDat_fail_assert_if_write_factor_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_write_factor(NULL,0,0));

}



void test_uz_EnDat_fail_assert_if_read_statusword_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_read_statusword(NULL));

}


/*void test_uz_EnDat_write_control_and_divider(void)
{
    int ret;
    struct uz_EnDat_config_t config={
         .base_address= TEST_BASE_ADDRESS,
         .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
     };
    uz_EnDat_t *instance = uz_EnDat_init(config);
    uint8_t divider = 0;
    uint16_t ctrlwrd = 0;

    ret = uz_EnDat_write_control_and_divider(instance, ctrlwrd, divider);
    
    TEST_ASSERT_EQUAL_INT(ret,0);


}*/
 

#endif // TEST
