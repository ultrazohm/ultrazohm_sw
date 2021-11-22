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

void test_uz_incrementalEncoder_hw_set_pi2_inc(void)
{
    float expected=0.0012566447257996f; // (2*pi/(IncPerTurn*QuadratureFactor))*PolePair from Simulink model
    uz_axi_write_uint32_Expect(BASE_ADDRESS+PI2_Inc_AXI4_Data_IncreEncoder_V24_ip, uz_convert_float_to_unsigned_fixed(expected,24) ); // Data type is ufix24_En24
    TEST_ASSERT_EQUAL_HEX32(0x00525BU,uz_convert_float_to_unsigned_fixed(expected,24) ); // 0x00525B is taken with a "display" from simulink using "hex (Stored Integer)" numeric display format 
    uz_incrementalEncoder_hw_set_pi2_inc(BASE_ADDRESS,expected);
    
}

void test_uz_incrementalEncoder_hw_set_timer_fpga_ms(void)
{
    float expected=1.5915604308248e-5f; // (T_50MHz*IncPerTurn)/(2*pi) from Simulink model
    uz_axi_write_uint32_Expect(BASE_ADDRESS+Timer_FPGA_ms_AXI4_Data_IncreEncoder_V24_ip, uz_convert_float_to_unsigned_fixed(expected,32) ); // Data type is ufix32_En32
    TEST_ASSERT_EQUAL_HEX32(0x00010B05U,uz_convert_float_to_unsigned_fixed(expected,32) ); // 0x00010B05 is taken with a "display" from simulink using "hex (Stored Integer)" numeric display format 
    uz_incrementalEncoder_hw_set_timer_fpga_ms(BASE_ADDRESS, expected );
}

void test_uz_incrementalEncoder_hw_set_incPerTurn_mech(void){
     uint32_t expected=312U;
     uz_axi_write_uint32_Expect(BASE_ADDRESS+IncPerTurn_mech_AXI4_Data_IncreEncoder_V24_ip,expected);
     uz_incrementalEncoder_hw_set_increments_per_turn_mechanical(BASE_ADDRESS,expected);
}

void test_uz_incrementalEncoder_hw_set_incPerTurn_elec(void){
    uint32_t expected=34531U;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+IncPerTurn_elek_AXI4_Data_IncreEncoder_V24_ip,expected);
    uz_incrementalEncoder_hw_set_increments_per_turn_electric(BASE_ADDRESS,expected);
}

void test_uz_incrementalEncoder_hw_set_omegaPerOverSampl(void){
    float expected=52.35986328125f; // from Simulink model
    uz_axi_write_int32_Expect(BASE_ADDRESS+OmegaPerOverSampl_AXI4_Data_IncreEncoder_V24_ip,uz_convert_float_to_sfixed(expected,11)); // datatype sfix24_en11
    TEST_ASSERT_EQUAL_HEX32(0x01A2E1U, uz_convert_float_to_sfixed(expected,11));
    uz_incrementalEncoder_hw_set_omegaPerOverSample(BASE_ADDRESS,expected);
}

void test_uz_incrementalEncoder_hw_get_omega(void){
    float expected_return_value=52.3f;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS+omega_AXI4_Data_IncreEncoder_V24_ip,uz_convert_float_to_sfixed(expected_return_value,11)); // datatype sfix24_en11
    float actual_return_value=uz_incrementalEncoder_hw_get_omega(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_incrementalEncoder_hw_get_direction(void){
    float expected_return_value=-1.0f;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS+direction_AXI4_Data_IncreEncoder_V24_ip,uz_convert_float_to_sfixed(expected_return_value,11)); // data type is sfix24_en11
    float actual_return_value=uz_incrementalEncoder_hw_get_direction(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_incrementalEncoder_hw_get_theta_electric(void){
    float expected_return_value=3.1f;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS+theta_el_AXI4_Data_IncreEncoder_V24_ip, uz_convert_float_to_sfixed(expected_return_value,20) );
    float actual_return_value=uz_incrementalEncoder_hw_get_theta_electric(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_incrementalEncoder_hw_get_position(void){
    uint32_t expected_return_value=11U;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS+position_AXI4_Data_IncreEncoder_V24_ip,expected_return_value);
    uint32_t actual_return_value=uz_incrementalEncoder_hw_get_position(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expected_return_value,actual_return_value);
}

void test_uz_incrementalEncoder_hw_get_counterPerPeriod(void){
    uint32_t expected_return_value=55U;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS+countPerPeriod_AXI4_Data_IncreEncoder_V24_ip,expected_return_value);
    uint32_t actual_return_value=uz_incrementalEncoder_hw_get_counterPerPeriod(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expected_return_value,actual_return_value);
}



#endif // TEST
