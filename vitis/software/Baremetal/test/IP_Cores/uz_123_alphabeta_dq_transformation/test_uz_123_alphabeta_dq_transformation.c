#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include <stdint.h>
#define TEST_BASE_ADDRESS 0x000BADBAD
#define TEST_IP_CORE_FRQ 100000000U
#include "uz_123_alphabeta_dq_transformation.h"
#include "mock_uz_123_alphabeta_dq_transformation_hw.h"
#include "uz_Transformation.h" 

static struct uz_dqIPcore_config_t config={
   .base_address= TEST_BASE_ADDRESS,
   .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
   .theta_offset = -1.5f
};

void setUp(void)
{
   config.base_address = TEST_BASE_ADDRESS;
   config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;
   config.theta_offset = -1.5f;
}

void tearDown(void)
{
}

void test_123_alphabeta_uz_dq_transformation_init_test(void)
{
   uz_123_alphabeta_dqTransformation_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_123_alphabeta_dqIPcore_init(config);
}


void test_123_alphabeta_uz_dq_transformation_read_idq(void)
{
   uz_123_alphabeta_dqTransformation_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_dqIPcore_t* test_instance = uz_123_alphabeta_dqIPcore_init(config);

   float id_expected = -2.25f; 
   uz_123_alphabeta_dqTransformation_hw_get_id_ExpectAndReturn(config.base_address, id_expected);

   float iq_expected = 12.125f; 
   uz_123_alphabeta_dqTransformation_hw_get_iq_ExpectAndReturn(config.base_address, iq_expected);

   uz_3ph_dq_t currents = uz_123_alphabeta_dqIPcore_get_id_iq(test_instance);
   
   TEST_ASSERT_EQUAL_FLOAT(currents.d, id_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.q, iq_expected);
}

void test_uz_123_alphabeta_dq_transformation_read_i_uvw(void)
{
   uz_123_alphabeta_dqTransformation_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_dqIPcore_t* test_instance = uz_123_alphabeta_dqIPcore_init(config);

   float iu_expected = -2.25f; 
   uz_123_alphabeta_dqTransformation_hw_get_i1_ExpectAndReturn(config.base_address, iu_expected);

   float iv_expected = 12.125f; 
   uz_123_alphabeta_dqTransformation_hw_get_i2_ExpectAndReturn(config.base_address, iv_expected);

   float iw_expected = 13.125f; 
   uz_123_alphabeta_dqTransformation_hw_get_i3_ExpectAndReturn(config.base_address, iw_expected);

   struct uz_3ph_abc_t currents = uz_123_alphabeta_dqIPcore_get_i_abc(test_instance);
   
   TEST_ASSERT_EQUAL_FLOAT(currents.a, iu_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.b, iv_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.c, iw_expected);
}

void test_123_alphabeta_uz_dq_transformation_read_i_uvw_pointer(void)
{
   uz_dqIPcore_t* testpointer = NULL;
   TEST_ASSERT_FAIL_ASSERT(uz_123_alphabeta_dqIPcore_get_i_abc(testpointer));
}

void test_uz_123_alphabeta_dq_transformation_read_i_alphabeta(void)
{
   uz_123_alphabeta_dqTransformation_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_dqIPcore_t* test_instance = uz_123_alphabeta_dqIPcore_init(config);

   float ialpha_expected = 42.25f; 
   uz_123_alphabeta_dqTransformation_hw_get_ialpha_ExpectAndReturn(config.base_address, ialpha_expected);

   float ibeta_expected = 13.125f; 
   uz_123_alphabeta_dqTransformation_hw_get_ibeta_ExpectAndReturn(config.base_address, ibeta_expected);

   struct uz_3ph_alphabeta_t currents = uz_123_alphabeta_dqIPcore_get_i_alphabeta(test_instance);
   
   TEST_ASSERT_EQUAL_FLOAT(currents.alpha, ialpha_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.beta, ibeta_expected);

}

void test_123_alphabeta_uz_dq_transformation_read_i_alphabeta_pointer(void)
{
   uz_dqIPcore_t* testpointer = NULL;
   TEST_ASSERT_FAIL_ASSERT(uz_123_alphabeta_dqIPcore_get_i_alphabeta(testpointer));
}


#endif // TEST
