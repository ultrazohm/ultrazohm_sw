#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "uz_switching_states_6Phase_8_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_switching_states_6Phase_8_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_switching_states_6Phase_8_get_Index_in(void){
     int32_t expected_return_value = 3;
     uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+min_Index_AXI_Data_parallel_8_sim_switching_states,expected_return_value);
     int32_t actual_return_value = uz_switching_states_6Phase_8_get_min_Index_(TEST_BASE_ADDRESS);
     TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

#endif // TEST
