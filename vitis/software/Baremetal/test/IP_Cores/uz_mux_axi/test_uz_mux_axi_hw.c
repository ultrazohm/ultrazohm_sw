#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_mux_axi_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x000BADBAD // random hex value that represents a fictional base address
#include "uz_mux_axi_hw.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_mux_axi_hw_enable_IP_core_with_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_mux_axi_hw_enable_IP_core(0));
}

void test_uz_mux_axi_hw_set_mux_with_zero_base_address(void)
{
    uint32_t test_mux = 0;
    TEST_ASSERT_FAIL_ASSERT(uz_mux_axi_hw_set_mux(0,test_mux));
}

void test_uz_mux_axi_hw_set_mux_with_mux_too_high(void)
{
    uint32_t test_mux = 42;
    TEST_ASSERT_FAIL_ASSERT(uz_mux_axi_hw_set_mux(TEST_BASE_ADDRESS,test_mux));
}

void test_uz_mux_axi_hw_set_nth_interrupt_with_zero_base_address(void)
{
    uint32_t test_n_th_interrupt = 1;
    TEST_ASSERT_FAIL_ASSERT(uz_mux_axi_hw_set_n_th_interrupt(0,test_n_th_interrupt));
}

void test_uz_mux_axi_hw_set_nth_interrupt_with_zero_n_th_interrupt(void)
{
    uint32_t test_n_th_interrupt = 0;
    TEST_ASSERT_FAIL_ASSERT(uz_mux_axi_hw_set_n_th_interrupt(TEST_BASE_ADDRESS,test_n_th_interrupt));
}

void test_uz_mux_axi_hw_set_mux(void)
{
    uint32_t test_mux = 1;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + select_AXI_Data_mux_axi_ip,test_mux);
    uz_mux_axi_hw_set_mux(TEST_BASE_ADDRESS,test_mux);
}

void test_uz_mux_axi_hw_set_n_th_interrupt(void)
{
    uint32_t test_n_th_interrupt = 5;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + select_n_th_adc_interrupt_Data_mux_axi_ip,test_n_th_interrupt);
    uz_mux_axi_hw_set_n_th_interrupt(TEST_BASE_ADDRESS,test_n_th_interrupt);
}
#endif // TEST
