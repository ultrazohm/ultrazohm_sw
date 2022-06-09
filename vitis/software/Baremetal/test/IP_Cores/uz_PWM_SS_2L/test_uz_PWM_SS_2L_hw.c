#ifdef TEST

#include "unity.h"

#include "uz_PWM_SS_2L_hw.h"
#include <stdbool.h>
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_PWM_SS_2L_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x000BADBAD // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_PWM_SS_2L_hw_SetExternalCounterSource(void)
{
    bool CntExtSrc_on_off = true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + count_src_ext_AXI_Data_PWM_and_SS_control_V4_ip, CntExtSrc_on_off);
    uz_PWM_SS_2L_hw_SetExternalCounterSource(TEST_BASE_ADDRESS, CntExtSrc_on_off);
}

void test_uz_PWM_SS_2L_hw_SetExternalCounterSource_with_zero_base_address(void)
{
    bool CntExtSrc_on_off = true;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetExternalCounterSource(0, CntExtSrc_on_off));
}

void test_uz_PWM_SS_2L_hw_SetDutyCycle(void)
{
    float dutyCyc_A = 0.3f;
    float dutyCyc_B = 0.5f;
    float dutyCyc_C = 0.7f;
    uint32_t dutyCyc_A_Q12 = 1228U;
    uint32_t dutyCyc_B_Q12 = 2048U;
    uint32_t dutyCyc_C_Q12 = 2867U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + m_u1_norm_AXI_Data_PWM_and_SS_control_V4_ip, dutyCyc_A_Q12);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + m_u2_norm_AXI_Data_PWM_and_SS_control_V4_ip, dutyCyc_B_Q12);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + m_u3_norm_AXI_Data_PWM_and_SS_control_V4_ip, dutyCyc_C_Q12);
    uz_PWM_SS_2L_hw_SetDutyCycle(TEST_BASE_ADDRESS,dutyCyc_A,dutyCyc_B,dutyCyc_C);
}

void test_uz_PWM_SS_2L_hw_SetDutyCycle_with_invalid_negative_dutyCyc(void)
{
    float dutyCyc_A = -0.01f;
    float dutyCyc_B = -1.02f;
    float dutyCyc_C = -1.03f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetDutyCycle(TEST_BASE_ADDRESS,dutyCyc_A,dutyCyc_B,dutyCyc_C));
}

void test_uz_PWM_SS_2L_hw_SetDutyCycle_with_invalid_positive_dutyCyc(void)
{
    float dutyCyc_A = 1.01f;
    float dutyCyc_B = 1.02f;
    float dutyCyc_C = 1.03f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetDutyCycle(TEST_BASE_ADDRESS,dutyCyc_A,dutyCyc_B,dutyCyc_C));
}

void test_uz_PWM_SS_2L_hw_SetDutyCycle_with_zero_base_address(void)
{
    float dutyCyc_A = 0.3f;
    float dutyCyc_B = 0.5f;
    float dutyCyc_C = 0.7f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetDutyCycle(0,dutyCyc_A,dutyCyc_B,dutyCyc_C));
}

void test_uz_PWM_SS_2L_hw_SetStatus_on(void)
{
    bool PWM_en = true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + PWM_en_AXI_Data_PWM_and_SS_control_V4_ip, PWM_en);
    uz_PWM_SS_2L_hw_SetStatus(TEST_BASE_ADDRESS, PWM_en);
}

void test_uz_PWM_SS_2L_hw_SetStatus_with_zero_base_address(void)
{
    bool PWM_en = false;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetStatus(0U, PWM_en));
}

void test_uz_PWM_SS_2L_hw_SetMode(void)
{
    uint32_t PWM_mode = 0U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + Mode_AXI_Data_PWM_and_SS_control_V4_ip, PWM_mode);
    uz_PWM_SS_2L_hw_SetMode(TEST_BASE_ADDRESS,PWM_mode);
    }

void test_uz_PWM_SS_2L_hw_SetMode_with_invalid_negative_mode(void)
{
    uint32_t PWM_mode = 212314U; // random big number that is out of range
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetMode(TEST_BASE_ADDRESS,PWM_mode));
}

void test_uz_PWM_SS_2L_hw_SetMode_with_invalid_positive_mode(void)
{
    uint32_t PWM_mode = 42U;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetMode(TEST_BASE_ADDRESS,PWM_mode));
}

void test_uz_PWM_SS_2L_hw_SetMode_with_zero_base_address(void)
{
    uint32_t PWM_mode = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetMode(0U,PWM_mode));
}

void test_uz_PWM_SS_2L_hw_SetCarrierFrequency(void)
{
    uint32_t ip_clk_frequency_Hz = 100000000U;
    float PWM_freq_Hz = 100e3f;
    uint32_t PWM_Scal_f_carrier_expected_Q26 = 134217; // equals Q26 value-1 of 100e3/(100e6*0.5)
    float PWM_Scal_T_carrier_expected = 500.0f;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + Scal_f_carrier_AXI_Data_PWM_and_SS_control_V4_ip, PWM_Scal_f_carrier_expected_Q26);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + Scal_T_carrier_AXI_Data_PWM_and_SS_control_V4_ip, (uint32_t)PWM_Scal_T_carrier_expected);
    uz_PWM_SS_2L_hw_SetCarrierFrequency(TEST_BASE_ADDRESS, ip_clk_frequency_Hz, PWM_freq_Hz);
}

void test_uz_PWM_SS_2L_hw_SetCarrierFrequency_with_zero_base_address(void)
{
    uint32_t ip_clk_frequency_Hz = 100000000U;
    float PWM_freq_Hz = 100e3f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetCarrierFrequency(0U,ip_clk_frequency_Hz,PWM_freq_Hz));
}

void test_uz_PWM_SS_2L_hw_set_min_pulse_width(void)
{
    float min_pulse_width_percent = 0.01001f;
    uint32_t min_pulse_width_percent_Q12_expected = 41; //41 equals Q12 value of 0.01001
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + PWM_min_pulse_width_AXI_Data_PWM_and_SS_control_V4_ip, min_pulse_width_percent_Q12_expected);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth(TEST_BASE_ADDRESS, min_pulse_width_percent);
}

void test_uz_PWM_SS_2L_hw_set_min_pulse_width_negative(void)
{
    float min_pulse_width_percent = -0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetMinimumPulseWidth(TEST_BASE_ADDRESS, min_pulse_width_percent));
}

void test_uz_PWM_SS_2L_hw_set_min_pulse_width_with_zero_base_address(void)
{
    float min_pulse_width_percent = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetMinimumPulseWidth(0U,min_pulse_width_percent));
}

void test_uz_PWM_SS_2L_hw_set_Tristate_all_halfBridges(void)
{
    bool TriState_HB1 = true;
    bool TriState_HB2 = true;
    bool TriState_HB3 = true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + TriState_HB1_AXI_Data_PWM_and_SS_control_V4_ip, TriState_HB1);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + TriState_HB2_AXI_Data_PWM_and_SS_control_V4_ip, TriState_HB2);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + TriState_HB3_AXI_Data_PWM_and_SS_control_V4_ip, TriState_HB3);
    uz_PWM_SS_2L_hw_SetTristate(TEST_BASE_ADDRESS, 1U, TriState_HB1);
    uz_PWM_SS_2L_hw_SetTristate(TEST_BASE_ADDRESS, 2U, TriState_HB2);
    uz_PWM_SS_2L_hw_SetTristate(TEST_BASE_ADDRESS, 3U, TriState_HB3);
}

void test_uz_PWM_SS_2L_hw_SetTristate_with_invalid_halfBridgeNumber(void)
{
    bool TriState = true;
    uint32_t halfBridgeNumber = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetTristate(TEST_BASE_ADDRESS,halfBridgeNumber,TriState));
}

void test_uz_PWM_SS_2L_hw_SetTristate_with_zero_base_address(void)
{
    bool TriState = true;
    // Tell the test that we do not care how often this function is called
    uz_axi_write_bool_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetTristate(0U,0U,TriState));
}

void test_uz_PWM_SS_2L_hw_SetTriangleShift_with_zero_base_address(void)
{
    float triangle_shift_HB1 = 0.5f;
    float triangle_shift_HB2 = 0.5f;
    float triangle_shift_HB3 = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetTriangleShift(0, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3));
}

void test_uz_PWM_SS_2L_hw_SetTriangleShift_assert_HB1_upper_limit(void)
{
    float triangle_shift_HB1 = 1.5f;
    float triangle_shift_HB2 = 0.5f;
    float triangle_shift_HB3 = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetTriangleShift(TEST_BASE_ADDRESS, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3));
}

void test_uz_PWM_SS_2L_hw_SetTriangleShift_assert_HB1_negative_value(void)
{
    float triangle_shift_HB1 = -1.5f;
    float triangle_shift_HB2 = 0.5f;
    float triangle_shift_HB3 = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetTriangleShift(TEST_BASE_ADDRESS, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3));
}

void test_uz_PWM_SS_2L_hw_SetTriangleShift_assert_HB2_upper_limit(void)
{
    float triangle_shift_HB2 = 1.5f;
    float triangle_shift_HB1 = 0.5f;
    float triangle_shift_HB3 = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetTriangleShift(TEST_BASE_ADDRESS, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3));
}

void test_uz_PWM_SS_2L_hw_SetTriangleShift_assert_HB2_negative_value(void)
{
    float triangle_shift_HB2 = -1.5f;
    float triangle_shift_HB1 = 0.5f;
    float triangle_shift_HB3 = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetTriangleShift(TEST_BASE_ADDRESS, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3));
}

void test_uz_PWM_SS_2L_hw_SetTriangleShift_assert_HB3_upper_limit(void)
{
    float triangle_shift_HB3 = 1.5f;
    float triangle_shift_HB1 = 0.5f;
    float triangle_shift_HB2 = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetTriangleShift(TEST_BASE_ADDRESS, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3));
}

void test_uz_PWM_SS_2L_hw_SetTriangleShift_assert_HB3_negative_value(void)
{
    float triangle_shift_HB3 = -1.5f;
    float triangle_shift_HB1 = 0.5f;
    float triangle_shift_HB2 = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_hw_SetTriangleShift(TEST_BASE_ADDRESS, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3));
}

void test_uz_PWM_SS_2L_hw_SetTriangleShift(void)
{
    float triangle_shift_HB1 = 0.685f;
    float triangle_shift_HB2 = 0.1793f;
    float triangle_shift_HB3 = 0.33458f;
    uint32_t triangle_shift_HB1_Q17 = uz_convert_float_to_unsigned_fixed(triangle_shift_HB1, 17);
    uint32_t triangle_shift_HB2_Q17 = uz_convert_float_to_unsigned_fixed(triangle_shift_HB2, 17);
    uint32_t triangle_shift_HB3_Q17 = uz_convert_float_to_unsigned_fixed(triangle_shift_HB3, 17);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + triangle_shift_HB1_Data_PWM_and_SS_control_V4_ip, triangle_shift_HB1_Q17);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + triangle_shift_HB2_Data_PWM_and_SS_control_V4_ip, triangle_shift_HB2_Q17);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + triangle_shift_HB3_Data_PWM_and_SS_control_V4_ip, triangle_shift_HB3_Q17);
    uz_PWM_SS_2L_hw_SetTriangleShift(TEST_BASE_ADDRESS, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3);
}

#endif // TEST
