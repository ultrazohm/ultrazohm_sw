#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_endat_interface_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address
#include "uz_endat_interface_hw.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_endat_interface_hw_write_zero_base_address(void)
{
    uint32_t clock_divider = 20U;
    uint32_t encoder_bit_width_single_turn = 25U;
    uint32_t encoder_bit_width_multi_turn = 12U;
    uint32_t encoder_number_of_CRC_bits = 5U;
    float sampling_interval = 0.0001f;
    float kp_pll = 628.0f;
    float ki_pll = 98696.0f;
    uint32_t machine_pole_pairs = 4U;
    int32_t mech_offset_ticks = -42;

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_endat_clock_divider(0U, clock_divider));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_endat_encoder_bit_width_single_turn(0U, encoder_bit_width_single_turn));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_endat_encoder_bit_width_multi_turn(0U, encoder_bit_width_multi_turn));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_endat_encoder_number_of_CRC_bits(0U, encoder_number_of_CRC_bits));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_ip_core_enable(0U, true));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_pll_parameters(0U, sampling_interval, kp_pll, ki_pll));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_machine_pole_pairs(0U, machine_pole_pairs));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_position_mech_offset_ticks_single_turn(0U, mech_offset_ticks));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_read_position_raw_single_turn(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_read_position_raw_multi_turn(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_read_endat_encoder_status(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_read_position_mech_si_single_turn(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_read_position_el_si_single_turn(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_read_speed_mech_si(0U));
}

void test_uz_endat_interface_hw_write_endat_clock_divider_limits(void)
{
    uint32_t clock_divider_too_low = 2U;
    uint32_t clock_divider_too_high = 642U;

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_endat_clock_divider(TEST_BASE_ADDRESS, clock_divider_too_low));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_endat_clock_divider(TEST_BASE_ADDRESS, clock_divider_too_high));
}

void test_uz_endat_interface_hw_write_endat_encoder_bit_width_limits(void)
{
    uint32_t encoder_bit_width_too_low = 0U;
    uint32_t encoder_bit_width_too_high = 33U;

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_endat_encoder_bit_width_single_turn(TEST_BASE_ADDRESS, encoder_bit_width_too_low));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_endat_encoder_bit_width_single_turn(TEST_BASE_ADDRESS, encoder_bit_width_too_high));

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_endat_encoder_bit_width_multi_turn(TEST_BASE_ADDRESS, encoder_bit_width_too_high));
}

void test_uz_endat_interface_hw_write_endat_encoder_bit_width(void)
{
    uint32_t encoder_bit_width_single_turn = 19U;
    uint32_t reciprocal_bit_width_single_turn_unsigned_representation = 256U;

    uint32_t encoder_bit_width_multi_turn = 19U;

    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + endat_encoder_bit_width_single_turn_AXI_Data_uz_endat_interface, encoder_bit_width_single_turn);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + reciprocal_bit_width_single_turn_AXI_Data_uz_endat_interface, reciprocal_bit_width_single_turn_unsigned_representation);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + endat_encoder_bit_width_multi_turn_AXI_Data_uz_endat_interface, encoder_bit_width_multi_turn);
    uz_endat_interface_hw_write_endat_encoder_bit_width_single_turn(TEST_BASE_ADDRESS, encoder_bit_width_single_turn);
    uz_endat_interface_hw_write_endat_encoder_bit_width_multi_turn(TEST_BASE_ADDRESS, encoder_bit_width_multi_turn);
}

void test_uz_endat_interface_hw_write_pll_parameters_limits(void)
{
    float sampling_interval_too_low = 0.0f;
    float sampling_interval_too_high = 0.0156f;
    float kp_pll_too_low = -0.1f;
    float kp_pll_too_high = 8191.0f;
    float ki_pll_too_low = -0.1f;
    float ki_pll_too_high = 262142.0f;

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_pll_parameters(TEST_BASE_ADDRESS, sampling_interval_too_low, 628.0f, 98696.0f));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_pll_parameters(TEST_BASE_ADDRESS, sampling_interval_too_high, 628.0f, 98696.0f));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_pll_parameters(TEST_BASE_ADDRESS, 0.0001f, kp_pll_too_low, 98696.0f));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_pll_parameters(TEST_BASE_ADDRESS, 0.0001f, kp_pll_too_high, 98696.0f));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_pll_parameters(TEST_BASE_ADDRESS, 0.0001f, 628.0f, ki_pll_too_low));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_pll_parameters(TEST_BASE_ADDRESS, 0.0001f, 628.0f, ki_pll_too_high));
}

void test_uz_endat_interface_hw_write_pll_parameters(void)
{
    float sampling_interval = 0.0001f;
    float kp_pll = 628.0f;
    float ki_pll = 98696.0f;

    uint32_t sampling_interval_fp = 1677U;
    uint32_t kp_pll_fp = 20096U;
    uint32_t ki_pll_fp = 98696U;

    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + t_sample_AXI_Data_uz_endat_interface, sampling_interval_fp);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + kp_pll_AXI_Data_uz_endat_interface, kp_pll_fp);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + ki_pll_AXI_Data_uz_endat_interface, ki_pll_fp);
    uz_endat_interface_hw_write_pll_parameters(TEST_BASE_ADDRESS, sampling_interval, kp_pll, ki_pll);
}

void test_uz_endat_interface_hw_write_machine_pole_pair_limits(void)
{
    uint32_t machine_pole_pairs_too_low = 0U;
    uint32_t machine_pole_pairs_too_high = 256U;

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_machine_pole_pairs(TEST_BASE_ADDRESS, machine_pole_pairs_too_low));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_hw_write_machine_pole_pairs(TEST_BASE_ADDRESS, machine_pole_pairs_too_high));
}

void test_uz_endat_interface_hw_read_position_speed_status(void)
{
    uint32_t expected_position_raw_single_turn = 424242U; 
    uint32_t expected_position_si_single_turn_unsigned_representation = 13575769U;
    uint32_t returned_position_raw_single_turn = 0U;
    uint32_t expected_position_el_si_single_turn_unsigend_representation = 13575769U;
    float returned_position_si_single_turn = 0.0f;
    float expected_position_si_single_turn = 0.8091789421f;
    float returned_position_el_si_single_turn = 0.0f;
    float expected_position_el_si_single_turn = 0.8091789421f;
    int32_t expected_speed_mech_si_signed_representation = 6862913;
    float expected_speed_mech_si = 104.7197551f;
    float returned_speed_mech_si = 0.0f;
    int32_t expected_speed_el_si_signed_representation = 1715728;
    float expected_speed_el_si = 418.8790204f;
    float returned_speed_el_si = 0.0f;
    int32_t expected_speed_mech_rpm_signed_representation = 4096000;
    float expected_speed_mech_rpm = 1000.0f;
    float returned_speed_mech_rpm = 0.0f;        
    uint32_t expected_status = 3U;
    uint32_t returned_status = 0U;
    uint32_t expected_position_raw_multi_turn = 42U; 
    uint32_t returned_position_multi_turn = 0U;

    // test single-turn position
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + position_raw_single_turn_AXI_Data_uz_endat_interface, expected_position_raw_single_turn);
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + position_mech_SI_single_turn_AXI_Data_uz_endat_interface, expected_position_si_single_turn_unsigned_representation);
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + position_el_SI_AXI_Data_uz_endat_interface, expected_position_el_si_single_turn_unsigend_representation);
    returned_position_raw_single_turn = uz_endat_interface_hw_read_position_raw_single_turn(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expected_position_raw_single_turn, returned_position_raw_single_turn);
    returned_position_si_single_turn = uz_endat_interface_hw_read_position_mech_si_single_turn(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_position_si_single_turn, returned_position_si_single_turn);
    returned_position_el_si_single_turn = uz_endat_interface_hw_read_position_el_si_single_turn(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_position_el_si_single_turn, returned_position_el_si_single_turn);

    // test multi-turn position
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + position_raw_multi_turn_AXI_Data_uz_endat_interface, expected_position_raw_multi_turn);
    returned_position_multi_turn = uz_endat_interface_hw_read_position_raw_multi_turn(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expected_position_raw_multi_turn, returned_position_multi_turn);

    // test status
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + CRC_raw_AXI_Data_uz_endat_interface, expected_status);
    returned_status = uz_endat_interface_hw_read_endat_encoder_status(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expected_status, returned_status);

    // test speeds
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS + speed_mech_SI_AXI_Data_uz_endat_interface, expected_speed_mech_si_signed_representation);
    returned_speed_mech_si = uz_endat_interface_hw_read_speed_mech_si(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_speed_mech_si, returned_speed_mech_si);

    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS + speed_el_SI_AXI_Data_uz_endat_interface, expected_speed_el_si_signed_representation);
    returned_speed_el_si = uz_endat_interface_hw_read_speed_el_si(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_speed_el_si, returned_speed_el_si);

    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS + speed_mech_rpm_AXI_Data_uz_endat_interface, expected_speed_mech_rpm_signed_representation);
    returned_speed_mech_rpm = uz_endat_interface_hw_read_speed_mech_rpm(TEST_BASE_ADDRESS);   
    TEST_ASSERT_EQUAL_FLOAT(expected_speed_mech_rpm, returned_speed_mech_rpm);
}

#endif // TEST
