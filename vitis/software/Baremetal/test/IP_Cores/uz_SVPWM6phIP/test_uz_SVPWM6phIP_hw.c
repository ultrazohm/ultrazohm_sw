#ifdef TEST

#include "unity.h"

#include "uz_SVPWM6phIP_hw.h"
#include <stdbool.h>
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_SVPWM6phIP_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00AA0000F // random hex value that represents a fictional base address


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_SVPWM6phIP_hw_SetExternalCounterSource(void)
{
    bool CntExtSrc_on_off = true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + count_src_ext_AXI_Data_SVPWM_6ph_ip, CntExtSrc_on_off);
    uz_SVPWM6phIP_hw_SetExternalCounterSource(TEST_BASE_ADDRESS, CntExtSrc_on_off);
}

void test_uz_SVPWM6phIP_hw_SetExternalCounterSource_with_zero_base_address(void)
{
    bool CntExtSrc_on_off = true;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_SetExternalCounterSource(0, CntExtSrc_on_off));
}



void test_uz_SVPWM6phIP_hw_Set_T_and_SV(void)
{
    float T1 = 0.25f;
    float T2 = 0.05f;
    float T3 = 0.3f;
    float T4 = 0.15f;
    float T5 = 0.25f;
    uint32_t SV1 = 1U;
    uint32_t SV2 = 2U;
    uint32_t SV3 = 3U;
    uint32_t SV4 = 4U;
    uint32_t SV5 = 5U;
    int32_t T1_norm = uz_convert_float_to_sfixed(T1,16);
    int32_t T2_norm = uz_convert_float_to_sfixed(T2,16);
    int32_t T3_norm = uz_convert_float_to_sfixed(T3,16);
    int32_t T4_norm = uz_convert_float_to_sfixed(T4,16);
    int32_t T5_norm = uz_convert_float_to_sfixed(T5,16);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + in_T1_AXI_Data_SVPWM_6ph_ip, (uint32_t)T1_norm);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + in_T2_AXI_Data_SVPWM_6ph_ip, (uint32_t)T2_norm);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + in_T3_AXI_Data_SVPWM_6ph_ip, (uint32_t)T3_norm);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + in_T4_AXI_Data_SVPWM_6ph_ip, (uint32_t)T4_norm);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + in_T5_AXI_Data_SVPWM_6ph_ip, (uint32_t)T5_norm);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + in_SV1_AXI_Data_SVPWM_6ph_ip, SV1);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + in_SV2_AXI_Data_SVPWM_6ph_ip, SV2);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + in_SV3_AXI_Data_SVPWM_6ph_ip, SV3);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + in_SV4_AXI_Data_SVPWM_6ph_ip, SV4);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + in_SV5_AXI_Data_SVPWM_6ph_ip, SV5);
    uz_SVPWM6phIP_hw_Set_T_and_SV(TEST_BASE_ADDRESS,T1,T2,T3,T4,T5,SV1,SV2,SV3,SV4,SV5);
}

void test_uz_SVPWM6phIP_hw_Set_T_and_SV_with_invalid_negative_value(void)
{
        float T1 = -0.25f;
    float T2 = -0.05f;
    float T3 = -0.3f;
    float T4 = -0.15f;
    float T5 = -0.25f;
    uint32_t SV1 = 1U;
    uint32_t SV2 = 2U;
    uint32_t SV3 = 3U;
    uint32_t SV4 = 4U;
    uint32_t SV5 = 5U;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_Set_T_and_SV(TEST_BASE_ADDRESS,T1,T2,T3,T4,T5,SV1,SV2,SV3,SV4,SV5));
}

void test_uz_SVPWM6phIP_hw_Set_T_and_SV_with_invalid_negative_T_value(void)
{
        float T1 = -0.25f;
    float T2 = -0.05f;
    float T3 = -0.3f;
    float T4 = -0.15f;
    float T5 = -0.25f;
    uint32_t SV1 = 1U;
    uint32_t SV2 = 2U;
    uint32_t SV3 = 3U;
    uint32_t SV4 = 4U;
    uint32_t SV5 = 5U;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_Set_T_and_SV(TEST_BASE_ADDRESS,T1,T2,T3,T4,T5,SV1,SV2,SV3,SV4,SV5));
}

void test_uz_SVPWM6phIP_hw_Set_T_and_SV_with_invalid_positive_T_value(void)
{
    float T1 = 2.25f;
    float T2 = 10.05f;
    float T3 = 1.3f;
    float T4 = 2.15f;
    float T5 = 1.25f;
    uint32_t SV1 = 1U;
    uint32_t SV2 = 2U;
    uint32_t SV3 = 3U;
    uint32_t SV4 = 4U;
    uint32_t SV5 = 5U;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_Set_T_and_SV(TEST_BASE_ADDRESS,T1,T2,T3,T4,T5,SV1,SV2,SV3,SV4,SV5));
}

void test_uz_SVPWM6phIP_hw_Set_T_and_SV_with_invalid_SV_value(void)
{
        float T1 = 0.25f;
    float T2 = 0.05f;
    float T3 = 0.3f;
    float T4 = 0.15f;
    float T5 = 0.25f;
    uint32_t SV1 = 123U;
    uint32_t SV2 = 233U;
    uint32_t SV3 = 3122U;
    uint32_t SV4 = 4223U;
    uint32_t SV5 = 5442U;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_Set_T_and_SV(TEST_BASE_ADDRESS,T1,T2,T3,T4,T5,SV1,SV2,SV3,SV4,SV5));
}

void test_uz_SVPWM6phIP_hw_Set_T_and_SV_with_zero_base_address(void)
{
        float T1 = -0.25f;
    float T2 = -0.05f;
    float T3 = -0.3f;
    float T4 = -0.15f;
    float T5 = -0.25f;
    uint32_t SV1 = 1U;
    uint32_t SV2 = 2U;
    uint32_t SV3 = 3U;
    uint32_t SV4 = 4U;
    uint32_t SV5 = 5U;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_Set_T_and_SV(0,T1,T2,T3,T4,T5,SV1,SV2,SV3,SV4,SV5));
}

void test_uz_SVPWM6phIP_hw_SetStatus_on(void)
{
    bool PWM_en = true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + PWM_en_AXI_Data_SVPWM_6ph_ip, PWM_en);
    uz_SVPWM6phIP_hw_SetStatus(TEST_BASE_ADDRESS, PWM_en);
}

void test_uz_SVPWM6phIP_hw_SetStatus_with_zero_base_address(void)
{
    bool PWM_en = false;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_SetStatus(0U, PWM_en));
}

void test_uz_SVPWM6phIP_hw_SetMode(void)
{
    uint32_t PWM_mode = 0U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + Mode_AXI_Data_SVPWM_6ph_ip, PWM_mode);
    uz_SVPWM6phIP_hw_SetMode(TEST_BASE_ADDRESS,PWM_mode);
    }

void test_uz_SVPWM6phIP_hw_SetMode_with_invalid_negative_mode(void)
{
    uint32_t PWM_mode = 212314U; // random big number that is out of range
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_SetMode(TEST_BASE_ADDRESS,PWM_mode));
}

void test_uz_SVPWM6phIP_hw_SetMode_with_invalid_positive_mode(void)
{
    uint32_t PWM_mode = 42U;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_SetMode(TEST_BASE_ADDRESS,PWM_mode));
}

void test_uz_SVPWM6phIP_hw_SetMode_with_zero_base_address(void)
{
    uint32_t PWM_mode = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_SetMode(0U,PWM_mode));
}

void test_uz_SVPWM6phIP_hw_SetCarrierFrequency(void)
{
    uint32_t ip_clk_frequency_Hz = 100000000U;
    float PWM_freq_Hz = 100e3f;
    uint32_t PWM_Scal_f_carrier_expected_Q26 = 134217; // equals Q26 value-1 of 100e3/(100e6*0.5)
    float PWM_Scal_T_carrier_expected = 500.0f;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + Scal_f_carrier_AXI_Data_SVPWM_6ph_ip, PWM_Scal_f_carrier_expected_Q26);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + Scal_T_carrier_AXI_Data_SVPWM_6ph_ip, (uint32_t)PWM_Scal_T_carrier_expected);
    uz_SVPWM6phIP_hw_SetCarrierFrequency(TEST_BASE_ADDRESS, ip_clk_frequency_Hz, PWM_freq_Hz);
}

void test_uz_SVPWM6phIP_hw_SetCarrierFrequency_with_zero_base_address(void)
{
    uint32_t ip_clk_frequency_Hz = 100000000U;
    float PWM_freq_Hz = 100e3f;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_SetCarrierFrequency(0U,ip_clk_frequency_Hz,PWM_freq_Hz));
}

void test_uz_SVPWM6phIP_hw_set_min_T_on(void)
{
    float min_T_on_percent = 0.01001f;
    uint32_t min_T_on_percent_Q12_expected = 41; //41 equals Q12 value of 0.01001
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + PWM_min_SV_time_AXI_Data_SVPWM_6ph_ip, min_T_on_percent_Q12_expected);
    uz_SVPWM6phIP_hw_SetMinimumTon(TEST_BASE_ADDRESS, min_T_on_percent);
}

void test_uz_SVPWM6phIP_hw_set_min_T_on_negative(void)
{
    float min_T_on_percent = -0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_SetMinimumTon(TEST_BASE_ADDRESS, min_T_on_percent));
}

void test_uz_SVPWM6phIP_hw_set_min_T_on_with_zero_base_address(void)
{
    float min_T_on_percent = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_SetMinimumTon(0U,min_T_on_percent));
}

void test_uz_SVPWM6phIP_hw_set_Tristate_all_halfBridges(void)
{
    bool TriState_HB1 = true;
    bool TriState_HB2 = true;
    bool TriState_HB3 = true;
    bool TriState_HB4 = true;
    bool TriState_HB5 = true;
    bool TriState_HB6 = true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + TriState_HB1_AXI_Data_SVPWM_6ph_ip, TriState_HB1);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + TriState_HB2_AXI_Data_SVPWM_6ph_ip, TriState_HB2);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + TriState_HB3_AXI_Data_SVPWM_6ph_ip, TriState_HB3);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + TriState_HB4_AXI1_Data_SVPWM_6ph_ip, TriState_HB4);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + TriState_HB5_AXI1_Data_SVPWM_6ph_ip, TriState_HB5);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + TriState_HB6_AXI1_Data_SVPWM_6ph_ip, TriState_HB6);
    uz_SVPWM6phIP_hw_SetTristate(TEST_BASE_ADDRESS, 1U, TriState_HB1);
    uz_SVPWM6phIP_hw_SetTristate(TEST_BASE_ADDRESS, 2U, TriState_HB2);
    uz_SVPWM6phIP_hw_SetTristate(TEST_BASE_ADDRESS, 3U, TriState_HB3);
    uz_SVPWM6phIP_hw_SetTristate(TEST_BASE_ADDRESS, 4U, TriState_HB4);
    uz_SVPWM6phIP_hw_SetTristate(TEST_BASE_ADDRESS, 5U, TriState_HB5);
    uz_SVPWM6phIP_hw_SetTristate(TEST_BASE_ADDRESS, 6U, TriState_HB6);
}

void test_uz_SVPWM6phIP_hw_SetTristate_with_invalid_halfBridgeNumber(void)
{
    bool TriState = true;
    uint32_t halfBridgeNumber = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_SetTristate(TEST_BASE_ADDRESS,halfBridgeNumber,TriState));
}

void test_uz_SVPWM6phIP_hw_SetTristate_with_zero_base_address(void)
{
    bool TriState = true;
    // Tell the test that we do not care how often this function is called
    uz_axi_write_bool_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_SetTristate(0U,0U,TriState));
}


void test_uz_SVPWM6phIP_hw_SetTriggerSource_assert(void)
{
    uint32_t trigger_source = 3U; //only 0->2 are defined as trigger source inputs
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_hw_SetTriggerSource(TEST_BASE_ADDRESS, trigger_source));    
}

void test_uz_SVPWM6phIP_hw_SetTriggerSource(void)
{
    uint32_t trigger_source = 0U; //MIN
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + PWM_trigger_source_AXI_Data_SVPWM_6ph_ip, trigger_source);   
    uz_SVPWM6phIP_hw_SetTriggerSource(TEST_BASE_ADDRESS, trigger_source);
    trigger_source = 1U; //MAX
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + PWM_trigger_source_AXI_Data_SVPWM_6ph_ip, trigger_source);   
    uz_SVPWM6phIP_hw_SetTriggerSource(TEST_BASE_ADDRESS, trigger_source);
    trigger_source = 2U; //Either
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + PWM_trigger_source_AXI_Data_SVPWM_6ph_ip, trigger_source);   
    uz_SVPWM6phIP_hw_SetTriggerSource(TEST_BASE_ADDRESS, trigger_source);
}




#endif // TEST
