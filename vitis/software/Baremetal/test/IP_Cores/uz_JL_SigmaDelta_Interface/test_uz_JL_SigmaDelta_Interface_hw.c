
#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_JL_SigmaDelta_Interface_hw.h"
#include "uz_JL_SigmaDelta_Interface_hwAddresses.h"
#include <math.h>

#define BASE_ADDRESS 0x0000000FU // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_JL_SigmaDelta_Interface_hw_write_clk_ratio(void)
{
    uint16_t test_val = 100;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + clk_ratio_Data_uz_JL_SigmaDelta_Interface, test_val);
    uz_JL_SigmaDelta_Interface_hw_write_clk_ratio(BASE_ADDRESS, test_val);
}

void test_uz_JL_SigmaDelta_Interface_hw_write_switch_edge(void)
{
    uint8_t test_val = 1;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + switch_edge_Data_uz_JL_SigmaDelta_Interface, test_val);
    uz_JL_SigmaDelta_Interface_hw_write_switch_edge(BASE_ADDRESS, test_val);
}

void test_uz_JL_SigmaDelta_Interface_hw_write_data_delay(void)
{
    uint16_t test_val = 14;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + filt_input_delay_Data_uz_JL_SigmaDelta_Interface, test_val);
    uz_JL_SigmaDelta_Interface_hw_write_data_delay(BASE_ADDRESS, test_val);
}

void test_uz_JL_SigmaDelta_Interface_hw_write_dezimation(void)
{
    uint16_t test_val = 500;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + Dezimation_Data_uz_JL_SigmaDelta_Interface, test_val);
    uz_JL_SigmaDelta_Interface_hw_write_dezimation(BASE_ADDRESS, test_val);
}

void test_uz_JL_SigmaDelta_Interface_hw_write_switch_cont_disc(void)
{
    bool test_val = true;
    uz_axi_write_bool_Expect(BASE_ADDRESS + switch_cont_disc_Data_uz_JL_SigmaDelta_Interface, test_val);
    uz_JL_SigmaDelta_Interface_hw_write_switch_cont_disc(BASE_ADDRESS, test_val);
}

void test_uz_JL_SigmaDelta_Interface_hw_write_clk_dutycycle(void)
{
    float test_val = 0.5f;
    uint32_t expected_raw = (uint32_t)(test_val * (1 << 15));
    uz_axi_write_uint32_Expect(BASE_ADDRESS + clk_dutycycle_Data_uz_JL_SigmaDelta_Interface, expected_raw);
    uz_JL_SigmaDelta_Interface_hw_write_clk_dutycycle(BASE_ADDRESS, test_val);
}

void test_uz_JL_SigmaDelta_Interface_hw_read_data_out_U(void)
{
    int32_t expect_val = 12345;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS + SigmaDelta_Interface_data_out_U, expect_val);
    int32_t val_read = uz_JL_SigmaDelta_Interface_hw_read_data_out_U(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT32(expect_val, val_read);
}

void test_uz_JL_SigmaDelta_Interface_hw_read_data_out_PH1(void)
{
    int32_t expect_val = 23456;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS + SigmaDelta_Interface_data_out_PH1, expect_val);
    int32_t val_read = uz_JL_SigmaDelta_Interface_hw_read_data_out_PH1(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT32(expect_val, val_read);
}

void test_uz_JL_SigmaDelta_Interface_hw_read_data_out_PH2(void)
{
    int32_t expect_val = 34567;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS + SigmaDelta_Interface_data_out_PH2, expect_val);
    int32_t val_read = uz_JL_SigmaDelta_Interface_hw_read_data_out_PH2(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT32(expect_val, val_read);
}

void test_uz_JL_SigmaDelta_Interface_hw_read_data_out_PH3(void)
{
    int32_t expect_val = 45678;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS + SigmaDelta_Interface_data_out_PH3, expect_val);
    int32_t val_read = uz_JL_SigmaDelta_Interface_hw_read_data_out_PH3(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT32(expect_val, val_read);
}

void test_uz_JL_SigmaDelta_Interface_hw_read_data_out_PH4(void)
{
    int32_t expect_val = 56789;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS + SigmaDelta_Interface_data_out_PH4, expect_val);
    int32_t val_read = uz_JL_SigmaDelta_Interface_hw_read_data_out_PH4(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT32(expect_val, val_read);
}

void test_uz_JL_SigmaDelta_Interface_hw_trigger_output_strobe(void)
{
    uz_axi_write_bool_Expect(BASE_ADDRESS + data_out_ps_Strobe_uz_JL_SigmaDelta_Interface, true);
    uz_axi_write_bool_Expect(BASE_ADDRESS + data_out_ps_Strobe_uz_JL_SigmaDelta_Interface, false);
    uz_JL_SigmaDelta_Interface_hw_trigger_output_strobe(BASE_ADDRESS);
}

void test_uz_JL_SigmaDelta_Interface_hw_write_start_time_us(void)
{
    float test_val = 123.456f;
    uint32_t expected_ticks = (uint16_t)roundf(test_val * 100.0f);
    uz_axi_write_uint32_Expect(BASE_ADDRESS + start_time_us_Data_uz_JL_SigmaDelta_Interface, expected_ticks);
    uz_JL_SigmaDelta_Interface_hw_write_start_time_us(BASE_ADDRESS, test_val);
}

void test_uz_JL_SigmaDelta_Interface_hw_write_delay_data_valid(void)
{
    uint8_t test_val = 7;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + delay_data_valid_Data_uz_JL_SigmaDelta_Interface, test_val);
    uz_JL_SigmaDelta_Interface_hw_write_delay_data_valid(BASE_ADDRESS, test_val);
}

void test_uz_JL_SigmaDelta_Interface_hw_read_data_valid(void)
{
    bool expect_val = true;
    uz_axi_read_bool_ExpectAndReturn(BASE_ADDRESS + Data_valid_Data_uz_JL_SigmaDelta_Interface, expect_val);
    bool val_read = uz_JL_SigmaDelta_Interface_hw_read_data_valid(BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expect_val, val_read);
}

void test_uz_JL_SigmaDelta_Interface_hw_write_sinc_sample_periods(void)
{
    uint8_t test_val = 3;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + sinc_sample_periods_Data_uz_JL_SigmaDelta_Interface, test_val);
    uz_JL_SigmaDelta_Interface_hw_write_sinc_sample_periods(BASE_ADDRESS, test_val);
}

void test_uz_JL_SigmaDelta_Interface_hw_write_use_clk_ext(void)
{
    bool test_val = true;
    uz_axi_write_bool_Expect(BASE_ADDRESS + use_clk_ext_Data_uz_JL_SigmaDelta_Interface, test_val);
    uz_JL_SigmaDelta_Interface_hw_write_use_clk_ext(BASE_ADDRESS, test_val);
}

void test_uz_JL_SigmaDelta_Interface_hw_reset_data_valid_cnt(void)
{
    uz_axi_write_bool_Expect(BASE_ADDRESS + rst_data_valid_cnt_Data_uz_JL_SigmaDelta_Interface, true);
    uz_axi_write_bool_Expect(BASE_ADDRESS + rst_data_valid_cnt_Data_uz_JL_SigmaDelta_Interface, false);
    uz_JL_SigmaDelta_Interface_hw_reset_data_valid_cnt(BASE_ADDRESS);
}

void test_uz_JL_SigmaDelta_Interface_hw_read_data_valid_cnt(void)
{
    uint32_t expect_val = 42U;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + data_valid_cnt_Data_uz_JL_SigmaDelta_Interface, expect_val);
    uint8_t val_read = uz_JL_SigmaDelta_Interface_hw_read_data_valid_cnt(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT8((uint8_t)expect_val, val_read);
}

#endif // TEST
