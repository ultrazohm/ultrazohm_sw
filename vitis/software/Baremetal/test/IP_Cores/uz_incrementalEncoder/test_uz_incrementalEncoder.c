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
    .ip_core_frequency_Hz=50000000U,
    .line_number_per_turn_mech=5000u,
    .OmegaPerOverSample_in_rpm=500.0f,
    .drive_pole_pair=4U
};

void setUp(void)
{
    testconfig.base_address=TEST_BASE_ADDRESS;
    testconfig.ip_core_frequency_Hz=50000000U;
    testconfig.line_number_per_turn_mech=5000u;
    testconfig.OmegaPerOverSample_in_rpm=500.0f;
    testconfig.drive_pole_pair=4U;
}

void tearDown(void)
{
}


uz_incrementalEncoder_t* successful_init(){
    // Make sure the correct config values are written to the IP-Core
    // PI2_Inc_AXI is 0.0013 in the Simulink model [(2*pi/(IncPerTurn*QuadratureFactor))*PolePair ]
    float expected_pi2_inc=0.0012566447257996f; // (2*pi/(IncPerTurn*QuadratureFactor))*PolePair from Simulink model
    uz_incrementalEncoder_hw_set_pi2_inc_Expect(TEST_BASE_ADDRESS,expected_pi2_inc);
    // (T_50MHz*IncPerTurn)/(2*pi) in Simulink
    float expected_timer_fpga=1.5915604308248e-5f * 2.0f; // Half of the expected timer due to bug in IP-Core, see issue #145
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

void test_uz_incrementalEncoder_get_omega(void){
    uz_incrementalEncoder_t* test_instance= successful_init();
    float expected=321.1f;
    uz_incrementalEncoder_hw_get_omega_ExpectAndReturn(TEST_BASE_ADDRESS,expected);
    float omega=uz_incrementalEncoder_get_omega_mech(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(expected,omega);
}

void test_uz_incrementalEncoder_get_theta_el(void){
    uz_incrementalEncoder_t* test_instance= successful_init();
    float expected=0.13f;
    uz_incrementalEncoder_hw_get_theta_electric_ExpectAndReturn(TEST_BASE_ADDRESS,expected);
    float theta_el=uz_incrementalEncoder_get_theta_el(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(expected,theta_el);
}

void test_uz_incrementalEncoder_get_position(void){
    uz_incrementalEncoder_t* test_instance= successful_init();
    uint32_t expected=3421U;
    uz_incrementalEncoder_hw_get_position_ExpectAndReturn(TEST_BASE_ADDRESS,expected);
    uint32_t position=uz_incrementalEncoder_get_position(test_instance);
    TEST_ASSERT_EQUAL_UINT32(expected,position);
}

void test_uz_incrementalEncoder_non_integer_pole_pair(void){
    // This test makes sure that if increments per turn is not an integer multiple of pole pair, increments_per_turn is set to a default and calling get_theta_el generates an assertion
    testconfig.drive_pole_pair=9U;
    
    float expected_pi2_inc= (2.0f*UZ_PIf)/( (float)testconfig.line_number_per_turn_mech*4.0f)* (float)testconfig.drive_pole_pair; // (2*pi/(IncPerTurn*QuadratureFactor))*PolePair from Simulink model
    uz_incrementalEncoder_hw_set_pi2_inc_Expect(TEST_BASE_ADDRESS,expected_pi2_inc);
    // (T_50MHz*IncPerTurn)/(2*pi) in Simulink
    float expected_timer_fpga=1.5915604308248e-5f * 2.0f; // Half of the expected timer due to bug in IP-Core, see issue #145
    uz_incrementalEncoder_hw_set_timer_fpga_ms_Expect(TEST_BASE_ADDRESS, expected_timer_fpga);

    uint32_t expected_inc_per_turn_mech=5000U*4U; // random encoder value, *4 due to quadrature factor
    uz_incrementalEncoder_hw_set_increments_per_turn_mechanical_Expect(TEST_BASE_ADDRESS,expected_inc_per_turn_mech);

    uint32_t expected_inc_per_turn_elec=testconfig.line_number_per_turn_mech*4U ; // *4 due to quadrature factor but pole pair = 1 if theta_el can not be used
    uz_incrementalEncoder_hw_set_increments_per_turn_electric_Expect(TEST_BASE_ADDRESS,expected_inc_per_turn_elec);

    float expected_omegaPerOverSampl=52.35986328125f; // from Simulink
    uz_incrementalEncoder_hw_set_omegaPerOverSample_Expect(TEST_BASE_ADDRESS,expected_omegaPerOverSampl);

    uz_incrementalEncoder_t* test_instance=uz_incrementalEncoder_init(testconfig);
    TEST_ASSERT_FAIL_ASSERT(uz_incrementalEncoder_get_theta_el(test_instance));
}

#endif // TEST
