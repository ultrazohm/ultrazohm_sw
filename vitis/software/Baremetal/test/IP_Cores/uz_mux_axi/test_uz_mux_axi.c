#ifdef TEST
#include "test_assert_with_exception.h"
#include "uz_mux_axi.h"
#include "mock_uz_mux_axi_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x00BADBAD
#define TEST_IP_CORE_FRQ 100000000U
#include "unity.h"

#include "uz_mux_axi.h"

    struct uz_mux_axi_config_t config = {
        .base_address=TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .mux=1,
        .n_th_interrupt=1
    };

    


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_mux_axi_set_n_th_interrupt(void)
{  
    uz_mux_axi_hw_set_n_th_interrupt_Expect(TEST_BASE_ADDRESS, config.n_th_interrupt);
    uz_mux_axi_t *instance = uz_mux_axi_init(config);
    uz_mux_axi_set_n_th_interrupt(instance, config.n_th_interrupt);
}

void test_uz_mux_axi_set_mux(void)
{    
    uz_mux_axi_hw_set_mux_Expect(TEST_BASE_ADDRESS, config.mux);
    uz_mux_axi_t *instance = uz_mux_axi_init(config);
    uz_mux_axi_set_mux(instance, config.mux);
}

void test_uz_mux_axi_init_with_zero_base_address(void)
{
    config.base_address=0;
    TEST_ASSERT_FAIL_ASSERT(uz_mux_axi_init(config));
}

void test_uz_mux_axi_init_with_zero_ip_clk(void)
{
    config.ip_clk_frequency_Hz=0;
    TEST_ASSERT_FAIL_ASSERT(uz_mux_axi_init(config));
}

#endif // TEST
