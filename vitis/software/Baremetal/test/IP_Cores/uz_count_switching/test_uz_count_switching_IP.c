#ifdef TEST

#include "unity.h"

#include "uz_count_switching_IP.h"

#include "test_assert_with_exception.h"

#include "mock_uz_count_switching_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}

void test_count_switching_IP_(void)
{
        struct uz_count_switching_IP_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    uz_count_switching_IP_t *instance = uz_count_switching_IP_init(config);


    uint32_t a = 1000;
    uz_count_switching_hw_read_count_sum_ExpectAndReturn(TEST_BASE_ADDRESS, a);
    uint32_t b = uz_count_switching_IP_get_count_sum(instance);
    TEST_ASSERT_EQUAL_UINT32(a, b);

    uint32_t a0 = 100;
    uint32_t a1 = 101;
    uint32_t a2 = 102;
    uint32_t a3 = 103;
    uint32_t a4 = 104;
    uint32_t a5 = 105;
    uint32_t a6 = 106;
    uint32_t a7 = 107;
    uint32_t a8 = 108;

    uz_count_switching_hw_read_count_0_ExpectAndReturn(TEST_BASE_ADDRESS, a0);
    uz_count_switching_hw_read_count_1_ExpectAndReturn(TEST_BASE_ADDRESS, a1);
    uz_count_switching_hw_read_count_2_ExpectAndReturn(TEST_BASE_ADDRESS, a2);
    uz_count_switching_hw_read_count_3_ExpectAndReturn(TEST_BASE_ADDRESS, a3);
    uz_count_switching_hw_read_count_4_ExpectAndReturn(TEST_BASE_ADDRESS, a4);
    uz_count_switching_hw_read_count_5_ExpectAndReturn(TEST_BASE_ADDRESS, a5);
    uz_count_switching_hw_read_count_6_ExpectAndReturn(TEST_BASE_ADDRESS, a6);
    uz_count_switching_hw_read_count_7_ExpectAndReturn(TEST_BASE_ADDRESS, a7);
    uz_count_switching_hw_read_count_8_ExpectAndReturn(TEST_BASE_ADDRESS, a8);

    b = uz_count_switching_IP_get_count(instance, 0);
    TEST_ASSERT_EQUAL_UINT32(a0, b);

    b = uz_count_switching_IP_get_count(instance, 1);
    TEST_ASSERT_EQUAL_UINT32(a1, b);

    b = uz_count_switching_IP_get_count(instance, 2);
    TEST_ASSERT_EQUAL_UINT32(a2, b);

    b = uz_count_switching_IP_get_count(instance, 3);
    TEST_ASSERT_EQUAL_UINT32(a3, b);

    b = uz_count_switching_IP_get_count(instance, 4);
    TEST_ASSERT_EQUAL_UINT32(a4, b);

    b = uz_count_switching_IP_get_count(instance, 5);
    TEST_ASSERT_EQUAL_UINT32(a5, b);

    b = uz_count_switching_IP_get_count(instance, 6);
    TEST_ASSERT_EQUAL_UINT32(a6, b);

    b = uz_count_switching_IP_get_count(instance, 7);
    TEST_ASSERT_EQUAL_UINT32(a7, b);

    b = uz_count_switching_IP_get_count(instance, 8);
    TEST_ASSERT_EQUAL_UINT32(a8, b);


    uz_count_switching_hw_reset_Expect(TEST_BASE_ADDRESS, true);

    uz_count_switching_IP_set_reset(instance, true);

    

}

#endif // TEST
