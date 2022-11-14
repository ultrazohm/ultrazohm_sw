#ifdef TEST

#include "unity.h"

#include "uz_min_cost_function_8.h"
#include "test_assert_with_exception.h"
#include "mock_uz_min_cost_function_8_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "../../uz/uz_Transformation/uz_Transformation.h"

static struct uz_min_cost_function_8_config_t config={
    .base_address= TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ, 
};
void setUp(void)
{
    config.base_address = TEST_BASE_ADDRESS;
    config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;
}

void tearDown(void)
{
}

void test_uz_min_cost_function_8_init_test(void)
{
    uz_min_cost_function_8_init(config);
}

/*
void test_uz_min_cost_function_8_read_Index_out_test(void)
{
   
    uz_min_cost_function_8_t* test_instance = uz_min_cost_function_8_init(config);

    int32_t Index_out_expected = 34;
    uz_min_cost_function_8_hw_get_Index_out_AXI_ExpectAndReturn(config.base_address, Index_out_expected);

    int32_t Index_out = uz_min_cost_function_8_read_Index_out(test_instance);

   TEST_ASSERT_EQUAL_FLOAT(Index_out, Index_out_expected);
  }

void test_uz_min_cost_function_8_read_Index_out_test_pointer(void)
{
    uz_min_cost_function_8_t* testpointer = NULL;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_8_read_Index_out(testpointer));
}

void test_uz_min_cost_function_8_get_J_AXI_test(void)
{
   
    uz_min_cost_function_8_t* test_instance = uz_min_cost_function_8_init(config);

    float J_AXI_expected = 2.2f;
    uz_min_cost_function_8_hw_get_J_out_AXI_ExpectAndReturn(config.base_address, J_AXI_expected);

    float J_AXI = uz_min_cost_function_8_get_J_out_AXI(test_instance);

   TEST_ASSERT_EQUAL_FLOAT(J_AXI, J_AXI_expected);
}

void test_uz_min_cost_function_8_get_J_AXI_test_pointer(void)
{
    uz_min_cost_function_8_t* testpointer = NULL;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_8_get_J_out_AXI(testpointer));
}
*/
#endif // TEST
