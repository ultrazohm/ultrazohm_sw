#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_incrementalEncoder_hw.h"
#include "uz_incrementalEncoder.h"

#define TEST_BASE_ADDRESS 0x0000FU

void setUp(void)
{
}

void tearDown(void)
{
}

struct uz_incrementalEncoder_config testconfig={
    .base_address=TEST_BASE_ADDRESS,
    .ip_core_frequency_Hz=50000000U,
    .increments_per_turn_mech=5000u,
    .OmegaPerOverSample_in_rpm=500.0f,
    .drive_pole_pair=4U
};

void test_uz_incrementalEncoder_init(void)
{

    // Make sure the correct config values are written to the IP-Core
    // PI2_Inc_AXI is 0.0013 in the Simulink model [(2*pi/(IncPerTurn*QuadratureFactor))*PolePair ]
    float expected_pi2_inc=0.0012566447257996; // (2*pi/(IncPerTurn*QuadratureFactor))*PolePair from Simulink model
    uz_incrementalEncoder_hw_set_pi2_inc_Expect(TEST_BASE_ADDRESS,expected_pi2_inc);
    // (T_50MHz*IncPerTurn)/(2*pi) in Simulink
    float expected_timer_fpga=1.5915604308248e-5;
    uz_incrementalEncoder_hw_set_timer_fpga_ms_Expect(TEST_BASE_ADDRESS, expected_timer_fpga);

    uint32_t expected_inc_per_turn_mech=5000*4; // random encoder value, *4 due to quadrature factor
    uz_incrementalEncoder_hw_set_increments_per_turn_mechanical_Expect(TEST_BASE_ADDRESS,expected_inc_per_turn_mech);

    uint32_t expected_inc_per_turn_elek=testconfig.increments_per_turn_mech*4 / testconfig.drive_pole_pair; // *4 due to quadrature factor
    uz_incrementalEncoder_hw_set_increments_per_turn_electric_Expect(TEST_BASE_ADDRESS,expected_inc_per_turn_elek);

    float expected_omegaPerOverSampl=52.35986328125; // from Simulink
    uz_incrementalEncoder_hw_set_omegaPerOverSampl_Expect(TEST_BASE_ADDRESS,expected_omegaPerOverSampl);

    uz_incrementalEncoder_t* test_instance=uz_incrementalEncoder_init(testconfig);


}

#endif // TEST
