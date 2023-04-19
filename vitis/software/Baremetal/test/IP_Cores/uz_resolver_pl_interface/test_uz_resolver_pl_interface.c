#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_resolver_pl_interface.h"
#include "mock_uz_resolver_pl_interface_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_resolver_pl_interface_init(void)
{
    struct uz_resolver_pl_interface_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    uz_resolver_pl_interface_t *instance = uz_resolver_pl_interface_init(config);
    
}

void test_uz_resolver_pl_interface_init_without_base_address_init(void)
{
    struct uz_resolver_pl_interface_config_t config={
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_init(config));
    
}

void test_uz_resolver_pl_interface_init_without_clk_freq_init(void)
{
    struct uz_resolver_pl_interface_config_t config={
        .base_address= TEST_BASE_ADDRESS
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_init(config));
    
}

#endif // TEST
