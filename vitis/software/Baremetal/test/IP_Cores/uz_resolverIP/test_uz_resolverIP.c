#ifdef TEST

#include "test_assert_with_exception.h"
#include "uz_resolverIP.h"
#include "mock_uz_resolverIP_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>


#define TEST_BASE_ADDRESS 0x43C00000
#define TEST_IP_CORE_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}

  void test_uz_resolverIP_test_A_times_B_equals_C(void)
  {
      struct uz_resolverIP_config_t config={
          .base_address= TEST_BASE_ADDRESS,
          .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
      };
      uz_resolverIP_t *instance = uz_resolverIP_init(config);
      int32_t a = -10;
      int32_t b = 200;
     uz_resolverIP_hw_write_A_Expect(TEST_BASE_ADDRESS, a);
     uz_resolverIP_hw_write_B_Expect(TEST_BASE_ADDRESS, b);
     uz_resolverIP_hw_read_C_ExpectAndReturn(TEST_BASE_ADDRESS, a * b);
     int32_t c = uz_resolverIP_multiply(instance, a, b);
     TEST_ASSERT_EQUAL_INT32(a * b, c);
 }

 void test_uz_resolverIP_fail_assert_if_base_address_is_zero(void)
{
    struct uz_resolverIP_config_t config={
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_init(config) );

}

void test_uz_resolverIP_fail_assert_if_ip_frequency_is_zero(void)
{
    struct uz_resolverIP_config_t config={
        .base_address=TEST_BASE_ADDRESS
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_init(config) );
}

#endif // TEST
