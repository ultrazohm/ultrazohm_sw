#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "IncreEncoder_V24_ip_addr.h"
#define BASE_ADDRESS 0x00000000FU // random hex value that represents a fictional base address

#include "uz_incrementalEncoder_hw.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_incrementalEncoder_hw_set_timer_fpga_ms(void)
{
    uint32_t expected=10;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+Timer_FPGA_ms_AXI4_Data_IncreEncoder_V24_ip,expected);
    uz_incrementalEncoder_hw_set_timer_fpga_ms(BASE_ADDRESS,expected);
}

void test_uz_incrementalEncoder_hw_set_pi2_inc(void)
{
    uint32_t expected=1123;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+PI2_Inc_AXI4_Data_IncreEncoder_V24_ip,expected);
    uz_incrementalEncoder_hw_set_pi2_inc(BASE_ADDRESS,expected);
}

void test_uz_incrementalEncoder_hw_set_incPerTurn_mech(void){
     uint32_t expected=312;
     uz_axi_write_uint32_Expect(BASE_ADDRESS+IncPerTurn_mech_AXI4_Data_IncreEncoder_V24_ip,expected);
     uz_incrementalEncoder_hw_set_increments_per_turn_mechanical(BASE_ADDRESS,expected);
}

void test_uz_incrementalEncoder_hw_set_incPerTurn_elec(void){
    uint32_t expected=34531;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+IncPerTurn_elek_AXI4_Data_IncreEncoder_V24_ip,expected);
    uz_incrementalEncoder_hw_set_increments_per_turn_electric(BASE_ADDRESS,expected);
}

void test_uz_incrementalEncoder_hw_set_omegaPerOverSampl(void){
    uint32_t expected=444;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+OmegaPerOverSampl_AXI4_Data_IncreEncoder_V24_ip,expected);
    uz_incrementalEncoder_hw_set_omegaPerOverSampl(BASE_ADDRESS,expected);
}

void test_uz_incrementalEncoder_hw_get_omega(void){
    uint32_t expected_return_value=123;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS+omega_AXI4_Data_IncreEncoder_V24_ip,expected_return_value);
    uint32_t actual_return_value=uz_incrementalEncoder_hw_get_omega(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expected_return_value,actual_return_value);
}

void test_uz_incrementalEncoder_hw_get_direction(void){
    uint32_t expected_return_value=123891239;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS+direction_AXI4_Data_IncreEncoder_V24_ip,expected_return_value);
    uint32_t actual_return_value=uz_incrementalEncoder_hw_get_direction(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expected_return_value,actual_return_value);
}

void test_uz_incrementalEncoder_hw_get_theta_electric(void){
    uint32_t expected_return_value=22;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS+theta_el_AXI4_Data_IncreEncoder_V24_ip,expected_return_value);
    uint32_t actual_return_value=uz_incrementalEncoder_hw_get_theta_electric(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expected_return_value,actual_return_value);
}

void test_uz_incrementalEncoder_hw_get_position(void){
    uint32_t expected_return_value=11;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS+position_AXI4_Data_IncreEncoder_V24_ip,expected_return_value);
    uint32_t actual_return_value=uz_incrementalEncoder_hw_get_position(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expected_return_value,actual_return_value);
}

void test_uz_incrementalEncoder_hw_get_counterPerPeriod(void){
    uint32_t expected_return_value=55;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS+countPerPeriod_AXI4_Data_IncreEncoder_V24_ip,expected_return_value);
    uint32_t actual_return_value=uz_incrementalEncoder_hw_get_counterPerPeriod(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expected_return_value,actual_return_value);
}



#endif // TEST
