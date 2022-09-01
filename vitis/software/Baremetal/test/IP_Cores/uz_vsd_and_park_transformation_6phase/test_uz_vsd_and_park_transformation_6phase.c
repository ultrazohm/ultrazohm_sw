#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include <stdint.h>
#define TEST_BASE_ADDRESS 0x000BADBAD
#define TEST_IP_CORE_FRQ 100000000U
#include "uz_vsd_and_park_transformation_6phase.h"
#include "mock_uz_vsd_and_park_transformation_6phase_hw.h"
#include "uz_Transformation.h" 

static struct uz_vsd_and_park_transformation_6phase_config_t config={
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

void test_uz_vsd_and_park_transformation_6phase_init(void)
{
   uz_vsd_and_park_transformation_6phase_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_vsd_and_park_transformation_6phase_init(config);
}

void test_uz_vsd_and_park_transformation_6phase_read_idq(void)
{
   uz_vsd_and_park_transformation_6phase_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_vsd_and_park_transformation_6phase_t* test_instance = uz_vsd_and_park_transformation_6phase_init(config);

   float id_expected = -2.25f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_d_ExpectAndReturn(config.base_address, id_expected);

   float iq_expected = 12.125f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_q_ExpectAndReturn(config.base_address, iq_expected);

   uz_3ph_dq_t currents = uz_vsd_and_park_transformation_6phase_get_id_iq(test_instance);
   
   TEST_ASSERT_EQUAL_FLOAT(currents.d, id_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.q, iq_expected);
}

void test_uz_vsd_and_park_transformation_6phase_read_idq_pointer(void)
{
   uz_vsd_and_park_transformation_6phase_t* testpointer = NULL;
   TEST_ASSERT_FAIL_ASSERT(uz_vsd_and_park_transformation_6phase_get_id_iq(testpointer));
}

void test_uz_vsd_and_park_transformation_6phase_get_ialpha_ibeta_ix_iy_i0plus_i0minus(void)
{
   uz_vsd_and_park_transformation_6phase_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_vsd_and_park_transformation_6phase_t* test_instance = uz_vsd_and_park_transformation_6phase_init(config);

   float ialpha_expected = -3.25f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_alpha_ExpectAndReturn(config.base_address, ialpha_expected);

   float ibeta_expected = 2.125f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_beta_ExpectAndReturn(config.base_address, ibeta_expected);

   float ix_expected = 5.125f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_x_ExpectAndReturn(config.base_address, ix_expected);

   float iy_expected = -6.125f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_y_ExpectAndReturn(config.base_address, iy_expected);

   float i0plus_expected = 8.125f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_0_plus_ExpectAndReturn(config.base_address, i0plus_expected);

   float i0minus_expected = -8.125f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_0_minus_ExpectAndReturn(config.base_address, i0minus_expected);



   uz_6ph_alphabeta_t currents = uz_vsd_and_park_transformation_6phase_get_ialpha_ibeta_ix_iy_i0plus_i0minus(test_instance);
   
   TEST_ASSERT_EQUAL_FLOAT(currents.alpha, ialpha_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.beta, ibeta_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.x, ix_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.y, iy_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.z1, i0plus_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.z2, i0minus_expected);
}

void test_uz_vsd_and_park_transformation_6phase_get_ialpha_ibeta_ix_iy_i0plus_i0minus_pointer(void)
{
   uz_vsd_and_park_transformation_6phase_t* testpointer = NULL;
   TEST_ASSERT_FAIL_ASSERT(uz_vsd_and_park_transformation_6phase_get_ialpha_ibeta_ix_iy_i0plus_i0minus(testpointer));
}

void test_uz_vsd_and_park_transformation_6phase_get_ia1_ib1_ic1_ia2_ib2_ic2(void)
{
   uz_vsd_and_park_transformation_6phase_hw_set_thetaOffset_Expect(config.base_address, config.theta_offset);
   uz_vsd_and_park_transformation_6phase_t* test_instance = uz_vsd_and_park_transformation_6phase_init(config);

   float ia1_expected = -4.25f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_a1_ExpectAndReturn(config.base_address, ia1_expected);

   float ib1_expected = 3.125f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_b1_ExpectAndReturn(config.base_address, ib1_expected);

   float ic1_expected = 6.125f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_c1_ExpectAndReturn(config.base_address, ic1_expected);

   float ia2_expected = -7.125f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_a2_ExpectAndReturn(config.base_address, ia2_expected);

   float ib2_expected = 9.125f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_b2_ExpectAndReturn(config.base_address, ib2_expected);

   float ic2_expected = -9.125f; 
   uz_vsd_and_park_transformation_6phase_hw_get_i_c2_ExpectAndReturn(config.base_address, ic2_expected);



   uz_6ph_abc_t currents = uz_vsd_and_park_transformation_6phase_get_ia1_ib1_ic1_ia2_ib2_ic2(test_instance);
   
   TEST_ASSERT_EQUAL_FLOAT(currents.a1, ia1_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.b1, ib1_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.c1, ic1_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.a2, ia2_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.b2, ib2_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.c2, ic2_expected);
}

void test_uz_vsd_and_park_transformation_6phase_get_ia1_ib1_ic1_ia2_ib2_ic2_pointer(void)
{
   uz_vsd_and_park_transformation_6phase_t* testpointer = NULL;
   TEST_ASSERT_FAIL_ASSERT(uz_vsd_and_park_transformation_6phase_get_ia1_ib1_ic1_ia2_ib2_ic2(testpointer));
}


#endif // TEST
