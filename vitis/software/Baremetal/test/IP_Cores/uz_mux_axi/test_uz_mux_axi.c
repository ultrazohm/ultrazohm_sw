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
        .n_th_interrupt=1,
        .delay_adc_trigger_in_us=0.0f
    };

    


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_mux_axi_set_n_th_interrupt(void)
{  
    uz_mux_axi_hw_enable_IP_core_Expect(TEST_BASE_ADDRESS);
    uz_mux_axi_hw_set_mux_Expect(TEST_BASE_ADDRESS,config.mux);
    uz_mux_axi_hw_set_n_th_interrupt_Expect(TEST_BASE_ADDRESS, config.n_th_interrupt);
    uz_mux_axi_hw_set_delay_adc_trigger_in_clk_cycles_Expect(TEST_BASE_ADDRESS, 0U);
    uz_mux_axi_t *instance = uz_mux_axi_init(config);
    uz_mux_axi_hw_set_n_th_interrupt_Expect(TEST_BASE_ADDRESS, config.n_th_interrupt);
    uz_mux_axi_set_n_th_interrupt(instance, config.n_th_interrupt);
}

void test_uz_mux_axi_set_mux(void)
{    
    uz_mux_axi_hw_enable_IP_core_Expect(TEST_BASE_ADDRESS);
    uz_mux_axi_hw_set_mux_Expect(TEST_BASE_ADDRESS, config.mux);
    uz_mux_axi_hw_set_n_th_interrupt_Expect(TEST_BASE_ADDRESS, config.n_th_interrupt);
    uz_mux_axi_hw_set_delay_adc_trigger_in_clk_cycles_Expect(TEST_BASE_ADDRESS, 0U);
    uz_mux_axi_t *instance = uz_mux_axi_init(config);
    uz_mux_axi_hw_set_mux_Expect(TEST_BASE_ADDRESS, config.mux);
    uz_mux_axi_set_mux(instance, config.mux);
}

void test_uz_mux_axi_set_delay_adc_trigger_in_us(void)
{
    config.delay_adc_trigger_in_us = 0.40f;
    uz_mux_axi_hw_enable_IP_core_Expect(TEST_BASE_ADDRESS);
    uz_mux_axi_hw_set_mux_Expect(TEST_BASE_ADDRESS, config.mux);
    uz_mux_axi_hw_set_n_th_interrupt_Expect(TEST_BASE_ADDRESS, config.n_th_interrupt);
    uz_mux_axi_hw_set_delay_adc_trigger_in_clk_cycles_Expect(TEST_BASE_ADDRESS, 40U);
    uz_mux_axi_t *instance = uz_mux_axi_init(config);
    uz_mux_axi_hw_set_delay_adc_trigger_in_clk_cycles_Expect(TEST_BASE_ADDRESS, 40U);
    uz_mux_axi_set_delay_adc_trigger_in_us(instance, config.delay_adc_trigger_in_us);
}

void test_uz_mux_axi_set_delay_adc_trigger_in_us_rounds_up_to_next_clock_cycle(void)
{
    config.delay_adc_trigger_in_us = 0.0f;
    uz_mux_axi_hw_enable_IP_core_Expect(TEST_BASE_ADDRESS);
    uz_mux_axi_hw_set_mux_Expect(TEST_BASE_ADDRESS, config.mux);
    uz_mux_axi_hw_set_n_th_interrupt_Expect(TEST_BASE_ADDRESS, config.n_th_interrupt);
    uz_mux_axi_hw_set_delay_adc_trigger_in_clk_cycles_Expect(TEST_BASE_ADDRESS, 0U);
    uz_mux_axi_t *instance = uz_mux_axi_init(config);
    uz_mux_axi_hw_set_delay_adc_trigger_in_clk_cycles_Expect(TEST_BASE_ADDRESS, 2U);
    uz_mux_axi_set_delay_adc_trigger_in_us(instance, 0.015f);
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

void test_uz_mux_axi_init_with_delay_adc_trigger_in_us_too_high(void)
{
    config.delay_adc_trigger_in_us = ((float) UZ_MUX_AXI_HW_MAX_DELAY_CYCLES + 1.0f) * (1.0e6f / (float) TEST_IP_CORE_FRQ);
    TEST_ASSERT_FAIL_ASSERT(uz_mux_axi_init(config));
}

void test_uz_mux_axi_init_with_negative_delay_adc_trigger_in_us(void)
{
    config.delay_adc_trigger_in_us = -0.1f;
    TEST_ASSERT_FAIL_ASSERT(uz_mux_axi_init(config));
}

void test_uz_mux_axi_init_with_delay_adc_trigger_in_us_not_matching_ip_clock_period_rounds_up(void)
{
    config.delay_adc_trigger_in_us = 0.015f;
    uz_mux_axi_hw_enable_IP_core_Expect(TEST_BASE_ADDRESS);
    uz_mux_axi_hw_set_mux_Expect(TEST_BASE_ADDRESS, config.mux);
    uz_mux_axi_hw_set_n_th_interrupt_Expect(TEST_BASE_ADDRESS, config.n_th_interrupt);
    uz_mux_axi_hw_set_delay_adc_trigger_in_clk_cycles_Expect(TEST_BASE_ADDRESS, 2U);
    uz_mux_axi_t *instance = uz_mux_axi_init(config);
    TEST_ASSERT_NOT_NULL(instance);
}
#endif // TEST
