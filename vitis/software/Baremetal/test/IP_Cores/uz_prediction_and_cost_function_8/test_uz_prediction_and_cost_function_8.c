#ifdef TEST

#include "unity.h"
#include "uz_prediction_and_cost_function_8.h"
#include "test_assert_with_exception.h"
#include "mock_uz_prediction_and_cost_function_8_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "../../uz/uz_Transformation/uz_Transformation.h"

static struct uz_prediction_and_cost_function_8_config_t config={
    .base_address = TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
    .psiPM = 1.3f,
    .Lq = 0.3f,
    .Ld = 2.3f,
    .Rs = 2.2f,
    .SampleTime = 0.01f,
    .pole_pairs = 4.0f,
    .Lx = 1.1f,
    .Ly = 0.3f,
    .id_ref = 0.0f,
    .iq_ref = 10.0f,
    .ix_ref = 0.1f,
    .iy_ref = 0.3f
}; 

uz_6ph_idref_iqref_ixref_iyref_t updated_values={
    .id_ref=10.0f,
    .iq_ref=2.2f,
    .ix_ref=1.1f,
    .iy_ref=0.0f
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
    config.id_ref = 0.0f;
    config.iq_ref = 10.0f;
    config.ix_ref = 0.1f;
    config.iy_ref = 0.3f;

    updated_values.id_ref=10.0f;
    updated_values.iq_ref=2.2f;
    updated_values.ix_ref=1.1f;
    updated_values.iy_ref=0.0f;

    
    
   

    
}
//_Bool done_phase_voltages_AXI=0;
//_Bool done_vas_and_park_AXI=1;
//_Bool current_valid_in_AXI=0;


void tearDown(void)
{
}

void test_uz_prediction_and_cost_function_8_init_test(void)
{
    uz_prediction_and_cost_function_8_hw_set_Lq_Expect(config.base_address, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_Ld_Expect(config.base_address, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_prediction_and_cost_function_8_hw_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_prediction_and_cost_function_8_hw_set_Rs_Expect(config.base_address, config.Rs);
    uz_prediction_and_cost_function_8_hw_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_prediction_and_cost_function_8_hw_set_id_ref_Expect(config.base_address, config.id_ref);
    uz_prediction_and_cost_function_8_hw_set_iq_ref_Expect(config.base_address, config.iq_ref);
    uz_prediction_and_cost_function_8_hw_set_ix_ref_Expect(config.base_address, config.ix_ref);
    uz_prediction_and_cost_function_8_hw_set_iy_ref_Expect(config.base_address, config.iy_ref);
    uz_prediction_and_cost_function_8_init(config);
}

void test_uz_prediction_and_cost_function_8_idref_iqref_ixref_iyref_update_test(void)
{
    uz_prediction_and_cost_function_8_hw_set_Lq_Expect(config.base_address, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_Ld_Expect(config.base_address, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_prediction_and_cost_function_8_hw_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_prediction_and_cost_function_8_hw_set_Rs_Expect(config.base_address, config.Rs);
    uz_prediction_and_cost_function_8_hw_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_prediction_and_cost_function_8_hw_set_id_ref_Expect(config.base_address, config.id_ref);
    uz_prediction_and_cost_function_8_hw_set_iq_ref_Expect(config.base_address, config.iq_ref);
    uz_prediction_and_cost_function_8_hw_set_ix_ref_Expect(config.base_address, config.ix_ref);
    uz_prediction_and_cost_function_8_hw_set_iy_ref_Expect(config.base_address, config.iy_ref);
        
    uz_prediction_and_cost_function_8_t* test_instance = uz_prediction_and_cost_function_8_init(config);

   uz_prediction_and_cost_function_8_hw_set_id_ref_Expect(config.base_address, updated_values.id_ref);
   uz_prediction_and_cost_function_8_hw_set_iq_ref_Expect(config.base_address, updated_values.iq_ref);
   uz_prediction_and_cost_function_8_hw_set_ix_ref_Expect(config.base_address, updated_values.ix_ref);
   uz_prediction_and_cost_function_8_hw_set_iy_ref_Expect(config.base_address, updated_values.iy_ref);

   uz_prediction_and_cost_function_8_idref_iqref_ixref_iyref_update(test_instance,updated_values);
   }

   void test_uz_prediction_and_cost_function_8_read_Index(void){

    uz_prediction_and_cost_function_8_hw_set_Lq_Expect(config.base_address, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_Ld_Expect(config.base_address, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_prediction_and_cost_function_8_hw_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_prediction_and_cost_function_8_hw_set_Rs_Expect(config.base_address, config.Rs);
    uz_prediction_and_cost_function_8_hw_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_prediction_and_cost_function_8_hw_set_id_ref_Expect(config.base_address, config.id_ref);
    uz_prediction_and_cost_function_8_hw_set_iq_ref_Expect(config.base_address, config.iq_ref);
    uz_prediction_and_cost_function_8_hw_set_ix_ref_Expect(config.base_address, config.ix_ref);
    uz_prediction_and_cost_function_8_hw_set_iy_ref_Expect(config.base_address, config.iy_ref);
        
    uz_prediction_and_cost_function_8_t* test_instance = uz_prediction_and_cost_function_8_init(config);

    int32_t Index_in_expect = 3;
    uz_prediction_and_cost_function_8_hw_get_Index_ExpectAndReturn(config.base_address, Index_in_expect);
    int32_t Index_in = uz_prediction_and_cost_function_8_read_Index(test_instance);
    TEST_ASSERT_EQUAL_INT(Index_in, Index_in_expect);
}

   void test_uz_prediction_and_cost_function_8_read_done_prediction_and_cost_function(void){

    uz_prediction_and_cost_function_8_hw_set_Lq_Expect(config.base_address, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_Ld_Expect(config.base_address, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_prediction_and_cost_function_8_hw_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_prediction_and_cost_function_8_hw_set_Rs_Expect(config.base_address, config.Rs);
    uz_prediction_and_cost_function_8_hw_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_prediction_and_cost_function_8_hw_set_id_ref_Expect(config.base_address, config.id_ref);
    uz_prediction_and_cost_function_8_hw_set_iq_ref_Expect(config.base_address, config.iq_ref);
    uz_prediction_and_cost_function_8_hw_set_ix_ref_Expect(config.base_address, config.ix_ref);
    uz_prediction_and_cost_function_8_hw_set_iy_ref_Expect(config.base_address, config.iy_ref);
        
    uz_prediction_and_cost_function_8_t* test_instance = uz_prediction_and_cost_function_8_init(config);

    _Bool done_prediction_and_cost_function_expect = 3;
    uz_prediction_and_cost_function_8_hw_get_done_prediction_and_cost_function_ExpectAndReturn(config.base_address, done_prediction_and_cost_function_expect);
    _Bool done_prediction_and_cost_function = uz_prediction_and_cost_function_8_read_done_prediction_and_cost_function(test_instance);
    TEST_ASSERT_EQUAL(done_prediction_and_cost_function_expect, done_prediction_and_cost_function);
}
/*
void test_uz_prediction_and_cost_function_8_set_done_phase_voltages_test(void)
{
    uz_prediction_and_cost_function_8_hw_set_Lq_Expect(config.base_address, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_Ld_Expect(config.base_address, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_prediction_and_cost_function_8_hw_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_prediction_and_cost_function_8_hw_set_Rs_Expect(config.base_address, config.Rs);
    uz_prediction_and_cost_function_8_hw_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_prediction_and_cost_function_8_hw_set_id_ref_Expect(config.base_address, config.id_ref);
    uz_prediction_and_cost_function_8_hw_set_iq_ref_Expect(config.base_address, config.iq_ref);
    uz_prediction_and_cost_function_8_hw_set_ix_ref_Expect(config.base_address, config.ix_ref);
    uz_prediction_and_cost_function_8_hw_set_iy_ref_Expect(config.base_address, config.iy_ref);
        
    uz_prediction_and_cost_function_8_t* test_instance = uz_prediction_and_cost_function_8_init(config);

   uz_prediction_and_cost_function_8_hw_set_done_phase_voltages_Expect(config.base_address, done_phase_voltages_AXI);

   uz_prediction_and_cost_function_8_set_done_phase_voltages_AXI(test_instance, done_phase_voltages_AXI);
   }

void test_uz_prediction_and_cost_function_8_set_done_vsd_and_park_test(void)
{
    uz_prediction_and_cost_function_8_hw_set_Lq_Expect(config.base_address, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_Ld_Expect(config.base_address, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_prediction_and_cost_function_8_hw_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_prediction_and_cost_function_8_hw_set_Rs_Expect(config.base_address, config.Rs);
    uz_prediction_and_cost_function_8_hw_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_prediction_and_cost_function_8_hw_set_id_ref_Expect(config.base_address, config.id_ref);
    uz_prediction_and_cost_function_8_hw_set_iq_ref_Expect(config.base_address, config.iq_ref);
    uz_prediction_and_cost_function_8_hw_set_ix_ref_Expect(config.base_address, config.ix_ref);
    uz_prediction_and_cost_function_8_hw_set_iy_ref_Expect(config.base_address, config.iy_ref);
        
    uz_prediction_and_cost_function_8_t* test_instance = uz_prediction_and_cost_function_8_init(config);

   uz_prediction_and_cost_function_8_hw_set_done_vsd_and_park_Expect(config.base_address, done_vas_and_park_AXI);

   uz_prediction_and_cost_function_8_set_done_vsd_and_park_AXI(test_instance, done_vas_and_park_AXI);
   }

void test_uz_prediction_and_cost_function_8_set_current_valid_in_test(void)
{
    uz_prediction_and_cost_function_8_hw_set_Lq_Expect(config.base_address, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_Ld_Expect(config.base_address, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_prediction_and_cost_function_8_hw_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_prediction_and_cost_function_8_hw_set_Rs_Expect(config.base_address, config.Rs);
    uz_prediction_and_cost_function_8_hw_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_prediction_and_cost_function_8_hw_set_id_ref_Expect(config.base_address, config.id_ref);
    uz_prediction_and_cost_function_8_hw_set_iq_ref_Expect(config.base_address, config.iq_ref);
    uz_prediction_and_cost_function_8_hw_set_ix_ref_Expect(config.base_address, config.ix_ref);
    uz_prediction_and_cost_function_8_hw_set_iy_ref_Expect(config.base_address, config.iy_ref);
        
    uz_prediction_and_cost_function_8_t* test_instance = uz_prediction_and_cost_function_8_init(config);

   uz_prediction_and_cost_function_8_hw_set_current_valid_in_Expect(config.base_address, current_valid_in_AXI);

   uz_prediction_and_cost_function_8_set_current_valid_in_AXI(test_instance, current_valid_in_AXI);
   }
   */
#endif // TEST
