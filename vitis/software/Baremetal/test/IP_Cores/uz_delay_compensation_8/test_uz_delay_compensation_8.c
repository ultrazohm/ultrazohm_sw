#ifdef TEST

#include "unity.h"

#include "uz_delay_compensation_8.h"
#include "test_assert_with_exception.h"
#include "mock_uz_delay_compensation_8_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "../../uz/uz_Transformation/uz_Transformation.h"

static struct uz_delay_compensation_8_config_t config={
    .base_address= TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
    .psiPM = 1.3f,
    .Lq =0.3f,
    .Ld = 2.3f,
    .Rs = 2.2f,
    .SampleTime = 0.01f,
    .pole_pairs = 4.0f,
    .Lx = 1.1f,
    .Ly = 0.3f,   
};

void setUp(void)
{
   config.base_address = TEST_BASE_ADDRESS;
   config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;
   config.psiPM = 1.3f;
   config.Lq = 0.3f;
   config.Ld = 2.3f;
   config.Rs = 2.2f;
   config.SampleTime = 0.01f;
   config.pole_pairs = 4.0f;
   config.Lx = 1.1f;
   config.Ly = 0.3f;
}

void tearDown(void)
{
}

void test_uz_delay_compensation_8_init_test(void)
{
    uz_delay_compensation_8_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_delay_compensation_8_set_Lq_Expect(config.base_address, config.Lq);
    uz_delay_compensation_8_set_Ld_Expect(config.base_address, config.Ld);
    uz_delay_compensation_8_set_Rs_Expect(config.base_address, config.Rs);
    uz_delay_compensation_8_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_delay_compensation_8_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_delay_compensation_8_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_delay_compensation_8_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_delay_compensation_8_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_delay_compensation_8_init(config);
}

void test_uz_delay_compensation_8_read_idk1_iqK1_ixk1_iyk1_test(void)
{
    uz_delay_compensation_8_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_delay_compensation_8_set_Lq_Expect(config.base_address, config.Lq);
    uz_delay_compensation_8_set_Ld_Expect(config.base_address, config.Ld);
    uz_delay_compensation_8_set_Rs_Expect(config.base_address, config.Rs);
    uz_delay_compensation_8_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_delay_compensation_8_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_delay_compensation_8_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_delay_compensation_8_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_delay_compensation_8_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    
    uz_delay_compensation_8_t* test_instance = uz_delay_compensation_8_init(config);

    float idk1_expected = 2.2f;
    uz_delay_compensation_8_get_id_k_1_ExpectAndReturn(config.base_address, idk1_expected);

    float iqk1_expectet = 3.3f;
    uz_delay_compensation_8_get_iq_k_1_ExpectAndReturn(config.base_address, iqk1_expectet);

    float ixk1_expected = 1.3f;
    uz_delay_compensation_8_get_ix_k_1_ExpectAndReturn(config.base_address, ixk1_expected);

    float iyk1_expected = 0.6f;
    uz_delay_compensation_8_get_iy_k_1_ExpectAndReturn(config.base_address, iyk1_expected);

    struct uz_6ph_idk1_iqk1_ixk1_iyk1_t currents = uz_delay_compensation_8_read_idk1_iqK1_ixk1_iyk1(test_instance);

   TEST_ASSERT_EQUAL_FLOAT(currents.id_k_1, idk1_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.iq_k_1, iqk1_expectet);
   TEST_ASSERT_EQUAL_FLOAT(currents.ix_k_1, ixk1_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.iy_k_1, iyk1_expected);
}

void test_uz_delay_compensation_8_read_idk1_iqK1_ixk1_iyk1_pointer(void)
{
    uz_delay_compensation_8_t* testpointer = NULL;
    TEST_ASSERT_FAIL_ASSERT(uz_delay_compensation_8_read_idk1_iqK1_ixk1_iyk1(testpointer));
}
#endif // TEST
