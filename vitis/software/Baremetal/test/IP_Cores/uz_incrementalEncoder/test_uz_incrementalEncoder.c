#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_incrementalEncoder_hw.h"
#include "uz_incrementalEncoder.h"
#include <math.h>
#include "uz_math_constants.h"
#define TEST_BASE_ADDRESS 0x0000FU

struct uz_incrementalEncoder_config testconfig={
    .base_address=TEST_BASE_ADDRESS,
    .ip_core_frequency_Hz=100000000U,
    .line_number_per_turn_mech=5000u,
    .OmegaPerOverSample_in_rpm=500.0f,
    .drive_pole_pair=4U
};

void setUp(void)
{
    testconfig.base_address=TEST_BASE_ADDRESS;
    testconfig.ip_core_frequency_Hz=100000000U;
    testconfig.line_number_per_turn_mech=5000u;
    testconfig.OmegaPerOverSample_in_rpm=500.0f;
    testconfig.drive_pole_pair=4U;
    testconfig.Speed_Timeout_ms = 100U;
    testconfig.Encoder_elec_Offset = 0U;
    testconfig.Encoder_mech_Offset = 0U;
    testconfig.counting_direction = uz_incrementalEncoder_counting_clock_wise;
}

void tearDown(void)
{
}


uz_incrementalEncoder_t* successful_init(){
    uz_incrementalEncoder_hw_reset_ip_core_Expect(testconfig.base_address);
    uz_incrementalEncoder_hw_set_Position_Offset_Expect(testconfig.base_address, testconfig.Encoder_mech_Offset);
    uz_incrementalEncoder_hw_set_theta_el_Offset_Expect(testconfig.base_address, testconfig.Encoder_elec_Offset);

    uint32_t speed_timeout = (testconfig.Speed_Timeout_ms * testconfig.ip_core_frequency_Hz) / 1000U;
    uz_incrementalEncoder_hw_set_speed_timeout_value_Expect(testconfig.base_address, speed_timeout);
    uz_incrementalEncoder_hw_set_cw_ccw_direction_Expect(testconfig.base_address, testconfig.counting_direction);
    // Make sure the correct config values are written to the IP-Core
    // PI2_Inc_AXI is 0.0013 in the Simulink model [(2*pi/(IncPerTurn*QuadratureFactor))*PolePair ]
    float expected_pi2_inc=0.0012566447257996f; // (2*pi/(IncPerTurn*QuadratureFactor))*PolePair from Simulink model
    uz_incrementalEncoder_hw_set_pi2_inc_Expect(TEST_BASE_ADDRESS,expected_pi2_inc);
    // (T_100MHz*IncPerTurn)/(2*pi) in Simulink
    float expected_timer_fpga=7.957748e-6f; 
    uz_incrementalEncoder_hw_set_timer_fpga_ms_Expect(TEST_BASE_ADDRESS, expected_timer_fpga);

    uint32_t expected_inc_per_turn_mech=5000U*4U; // random encoder value, *4 due to quadrature factor
    uz_incrementalEncoder_hw_set_increments_per_turn_mechanical_Expect(TEST_BASE_ADDRESS,expected_inc_per_turn_mech);

    uint32_t expected_inc_per_turn_elec=testconfig.line_number_per_turn_mech*4 / testconfig.drive_pole_pair; // *4 due to quadrature factor
    uz_incrementalEncoder_hw_set_increments_per_turn_electric_Expect(TEST_BASE_ADDRESS,expected_inc_per_turn_elec);

    float expected_omegaPerOverSampl=52.35986328125f; // from Simulink
    uz_incrementalEncoder_hw_set_omegaPerOverSample_Expect(TEST_BASE_ADDRESS,expected_omegaPerOverSampl);

    uz_incrementalEncoder_t* test_instance=uz_incrementalEncoder_init(testconfig);
    return test_instance;
}

void test_uz_incrementalEncoder_init(void)
{
    successful_init();
}

void test_uz_incrementalEncoder_init_assert_base_address_zero(void) {
    testconfig.base_address = 0x0U;
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_init(testconfig));
}

void test_uz_incrementalEncoder_init_assert_frequency_wrong(void) {
    testconfig.ip_core_frequency_Hz = 50U;
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_init(testconfig));
}

void test_uz_incrementalEncoder_init_assert_line_number_not_zero(void) {
    testconfig.line_number_per_turn_mech = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_init(testconfig));
}

void test_uz_incrementalEncoder_init_assert_line_number_UINT16(void) {
    testconfig.line_number_per_turn_mech = UINT16_MAX + 1U;
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_init(testconfig));
}

void test_uz_incrementalEncoder_init_assert_mech_Offset_UINT16(void) {
    testconfig.Encoder_mech_Offset = UINT16_MAX + 1U;
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_init(testconfig));
}

void test_uz_incrementalEncoder_init_assert_mech_Offset_line_number(void) {
    testconfig.Encoder_mech_Offset = testconfig.line_number_per_turn_mech + 1U;
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_init(testconfig));
}

void test_uz_incrementalEncoder_init_assert_elec_Offset_UINT16(void) {
    testconfig.Encoder_elec_Offset = UINT16_MAX + 1U;
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_init(testconfig));
}

void test_uz_incrementalEncoder_init_assert_elec_Offset_line_number(void) {
    testconfig.Encoder_elec_Offset = testconfig.line_number_per_turn_mech + 1U;
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_init(testconfig));
}

void test_uz_incrementalEncoder_get_omega(void){
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_get_omega_mech(NULL));
    uz_incrementalEncoder_t* test_instance= successful_init();
    float expected=321.1f;
    uz_incrementalEncoder_hw_get_omega_ExpectAndReturn(TEST_BASE_ADDRESS,expected);
    float omega=uz_incrementalEncoder_get_omega_mech(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(expected,omega);
}

void test_uz_incrementalEncoder_get_omega_mech_MA_N4(void){
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_get_omega_mech_MA_N4(NULL));
    uz_incrementalEncoder_t* test_instance= successful_init();
    float expected=321.1f;
    uz_incrementalEncoder_hw_get_omega_MA_N4_ExpectAndReturn(TEST_BASE_ADDRESS,expected);
    float omega=uz_incrementalEncoder_get_omega_mech_MA_N4(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(expected,omega);
}

void test_uz_incrementalEncoder_get_theta_el(void){
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_get_theta_el(NULL));
    uz_incrementalEncoder_t* test_instance= successful_init();
    float expected=0.13f;
    uz_incrementalEncoder_hw_get_theta_electric_ExpectAndReturn(TEST_BASE_ADDRESS,expected);
    float theta_el=uz_incrementalEncoder_get_theta_el(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(expected,theta_el);
}

void test_uz_incrementalEncoder_get_position(void){
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_get_position(NULL));
    uz_incrementalEncoder_t* test_instance= successful_init();
    uint32_t expected=3421U;
    uz_incrementalEncoder_hw_get_position_ExpectAndReturn(TEST_BASE_ADDRESS,expected);
    uint32_t position=uz_incrementalEncoder_get_position(test_instance);
    TEST_ASSERT_EQUAL_UINT32(expected,position);
}

void test_uz_incrementalEncoder_get_position_wOffset(void){
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_get_position_wOffset(NULL));
    uz_incrementalEncoder_t* test_instance= successful_init();
    uint32_t expected=3421U;
    uz_incrementalEncoder_hw_get_position_wOffset_ExpectAndReturn(TEST_BASE_ADDRESS,expected);
    uint32_t position=uz_incrementalEncoder_get_position_wOffset(test_instance);
    TEST_ASSERT_EQUAL_UINT32(expected,position);
}

void test_uz_incrementalEncoder_set_electrical_Offset(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_set_electrical_Offset(NULL, 10U));
    testconfig.Encoder_elec_Offset = 20U;
    uz_incrementalEncoder_t* test_instance= successful_init();    
    uint32_t new_offset = 50U;
    uint32_t new_offset_expected = new_offset * 4; //Because of quadrature factor
    uz_incrementalEncoder_hw_set_theta_el_Offset_Expect(TEST_BASE_ADDRESS, new_offset_expected);
    uz_incrementalEncoder_set_electrical_Offset(test_instance, new_offset);
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_set_electrical_Offset(test_instance, UINT16_MAX+1U));
    //Should assert, since offset is larger than line number
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_set_electrical_Offset(test_instance, testconfig.line_number_per_turn_mech + 10U));
}

void test_uz_incrementalEncoder_set_mechanical_Offset(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_set_mechanical_Offset(NULL, 10U));
    testconfig.Encoder_mech_Offset = 20U;
    uz_incrementalEncoder_t* test_instance= successful_init();
    uint32_t new_offset = 50U;
    uint32_t new_offset_expected = new_offset * 4; //Because of quadrature factor
    uz_incrementalEncoder_hw_set_Position_Offset_Expect(TEST_BASE_ADDRESS, new_offset_expected);
    uz_incrementalEncoder_set_mechanical_Offset(test_instance, new_offset);
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_set_mechanical_Offset(test_instance, UINT16_MAX+1U));
    //Should assert, since offset is larger than line number
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_set_mechanical_Offset(test_instance, testconfig.line_number_per_turn_mech + 10U));
}

void test_uz_incrementalEncoder_non_integer_pole_pair(void){
    // This test makes sure that if increments per turn is not an integer multiple of pole pair, increments_per_turn is set to a default and calling get_theta_el generates an assertion
    testconfig.drive_pole_pair=9U;
    uz_incrementalEncoder_hw_reset_ip_core_Expect(testconfig.base_address);
    uz_incrementalEncoder_hw_set_Position_Offset_Expect(testconfig.base_address, testconfig.Encoder_mech_Offset);
    uz_incrementalEncoder_hw_set_theta_el_Offset_Expect(testconfig.base_address, testconfig.Encoder_elec_Offset);
    
    uint32_t speed_timeout = (testconfig.Speed_Timeout_ms * testconfig.ip_core_frequency_Hz) / 1000U;
    uz_incrementalEncoder_hw_set_speed_timeout_value_Expect(testconfig.base_address, speed_timeout);
    uz_incrementalEncoder_hw_set_cw_ccw_direction_Expect(testconfig.base_address, testconfig.counting_direction);
    
    float expected_pi2_inc= (2.0f*UZ_PIf)/( (float)testconfig.line_number_per_turn_mech*4.0f)* (float)testconfig.drive_pole_pair; // (2*pi/(IncPerTurn*QuadratureFactor))*PolePair from Simulink model
    uz_incrementalEncoder_hw_set_pi2_inc_Expect(TEST_BASE_ADDRESS,expected_pi2_inc);
    // (T_50MHz*IncPerTurn)/(2*pi) in Simulink
    float expected_timer_fpga=7.957748e-06f; 
    uz_incrementalEncoder_hw_set_timer_fpga_ms_Expect(TEST_BASE_ADDRESS, expected_timer_fpga);

    uint32_t expected_inc_per_turn_mech=5000U*4U; // random encoder value, *4 due to quadrature factor
    uz_incrementalEncoder_hw_set_increments_per_turn_mechanical_Expect(TEST_BASE_ADDRESS,expected_inc_per_turn_mech);

    uint32_t expected_inc_per_turn_elec=testconfig.line_number_per_turn_mech*4; // *4 due to quadrature factor but pole pair = 1 if theta_el can not be used
    uz_incrementalEncoder_hw_set_increments_per_turn_electric_Expect(TEST_BASE_ADDRESS,expected_inc_per_turn_elec);

    float expected_omegaPerOverSampl=52.35986328125f; // from Simulink
    uz_incrementalEncoder_hw_set_omegaPerOverSample_Expect(TEST_BASE_ADDRESS,expected_omegaPerOverSampl);

    uz_incrementalEncoder_t* test_instance=uz_incrementalEncoder_init(testconfig);
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_get_theta_el(test_instance));
}

#endif // TEST
