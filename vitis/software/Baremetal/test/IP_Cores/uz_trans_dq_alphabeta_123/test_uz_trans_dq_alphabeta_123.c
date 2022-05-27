#ifdef TEST

#include "unity.h"

#include "uz_trans_dq_alphabeta_123.h"

#include "test_assert_with_exception.h"
#include "mock_uz_trans_dq_alphabeta_123_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "../../uz/uz_Transformation/uz_Transformation.h"

static struct uz_dq_alphabeta_123_IPcore_config_t config={
   .base_address= TEST_BASE_ADDRESS,
   .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
   .theta_offset = -1.5f,
   .id_ref = 2.5f,
   .iq_ref = 3.5f
};

void setUp(void)
{
   config.base_address = TEST_BASE_ADDRESS;
   config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;
   config.theta_offset = -1.5f;
   config.id_ref = 2.5f;
   config.iq_ref = 3.5;
}

void tearDown(void)
{
}

void test_uz_trans_dq_alphabeta_123_init_test(void)
{
   uz_trans_dq_alphabeta_123_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_trans_dq_alphabeta_123_hw_set_idref_Expect(config.base_address, config.id_ref);
   uz_trans_dq_alphabeta_123_hw_set_iqref_Expect(config.base_address, config.iq_ref);
   uz_dq_alphabeta_123_IPcore_init(config);
}

void test_uz_trans_dq_alphabeta_123_read_i_uvw(void)
{
   uz_trans_dq_alphabeta_123_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_trans_dq_alphabeta_123_hw_set_idref_Expect(config.base_address, config.id_ref);
   uz_trans_dq_alphabeta_123_hw_set_iqref_Expect(config.base_address, config.iq_ref);
   uz_dq_alphabeta_123_IPcore_t* test_instance = uz_dq_alphabeta_123_IPcore_init(config);

   float iu_expected = -2.25f; 
   uz_trans_dq_alphabeta_123_hw_get_i1_ExpectAndReturn(config.base_address, iu_expected);

   float iv_expected = 12.125f; 
   uz_trans_dq_alphabeta_123_hw_get_i2_ExpectAndReturn(config.base_address, iv_expected);

   float iw_expected = 13.125f; 
   uz_trans_dq_alphabeta_123_hw_get_i3_ExpectAndReturn(config.base_address, iw_expected);

   struct uz_3ph_abc_t currents = uz_dq_alphabeta_123_IPcore_get_i_abc(test_instance);
   
   TEST_ASSERT_EQUAL_FLOAT(currents.a, iu_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.b, iv_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.c, iw_expected);
}

void test_uz_trans_dq_alphabeta_123_read_i_uvw_pointer(void)
{
   uz_dq_alphabeta_123_IPcore_t* testpointer = NULL;
   TEST_ASSERT_FAIL_ASSERT(uz_dq_alphabeta_123_IPcore_get_i_abc(testpointer));
}


void test_uz_trans_dq_alphabeta_123_read_i_alphabeta(void)
{
   uz_trans_dq_alphabeta_123_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_trans_dq_alphabeta_123_hw_set_idref_Expect(config.base_address, config.id_ref);
   uz_trans_dq_alphabeta_123_hw_set_iqref_Expect(config.base_address, config.iq_ref);
   uz_dq_alphabeta_123_IPcore_t* test_instance = uz_dq_alphabeta_123_IPcore_init(config);

   float ialpha_expected = -3.124f; 
   uz_trans_dq_alphabeta_123_hw_get_ialpha_ExpectAndReturn(config.base_address, ialpha_expected);

   float ibeta_expected = 6.125f; 
   uz_trans_dq_alphabeta_123_hw_get_ibeta_ExpectAndReturn(config.base_address, ibeta_expected);

   struct uz_3ph_alphabeta_t currents = uz_dq_alphabeta_123_IPcore_get_ialpha_ibeta(test_instance);
   
   TEST_ASSERT_EQUAL_FLOAT(currents.alpha, ialpha_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.beta, ibeta_expected);
}

void test_uz_trans_dq_alphabeta_123_read_i_alphabeta_pointer(void)
{
   uz_dq_alphabeta_123_IPcore_t* testpointer = NULL;
   TEST_ASSERT_FAIL_ASSERT(uz_dq_alphabeta_123_IPcore_get_ialpha_ibeta(testpointer));
}


#endif // TEST






