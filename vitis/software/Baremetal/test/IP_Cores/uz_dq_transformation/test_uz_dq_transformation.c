#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include <stdint.h>
#define TEST_BASE_ADDRESS 0x000BADBAD
#define TEST_IP_CORE_FRQ 100000000U
#include "uz_dq_transformation.h"
#include "mock_uz_dq_transformation_hw.h"
#include "uz_Transformation.h" 

static struct uz_dq_transformation_config_t config={
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

void test_uz_dq_transformation_init_test(void)
{
   uz_dqTransformation_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_dq_transformation_t* test_instance = uz_dq_transformation_init(config);
}


void test_uz_dq_transformation_read_idq(void)
{
   uz_dqTransformation_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_dq_transformation_t* test_instance = uz_dq_transformation_init(config);

   float id_expected = -2.25f; 
   uz_dqTransformation_hw_get_id_ExpectAndReturn(config.base_address, id_expected);

   float iq_expected = 12.125f; 
   uz_dqTransformation_hw_get_iq_ExpectAndReturn(config.base_address, iq_expected);

   struct uz_dq_t currents = uz_dqTransformation_get_id_iq(test_instance);
   
   TEST_ASSERT_EQUAL_FLOAT(currents.d, id_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.q, iq_expected);
}

#endif // TEST
