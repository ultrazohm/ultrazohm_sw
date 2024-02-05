#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"

#include "../uz_global_configuration.h"
#include "../uz_parameterid_rc/uz_parameterid_rc.h"

struct uz_parameterid_rc_config_t test_config = {0};

void setUp(void)
{
    test_config.id_ref = 1.0f;
    test_config.iq_ref = 1.0f;
    test_config.n_ref = 1000.0f;
    test_config.wait_time = 0.5f;
    test_config.isr_steptime = (1.0f / 10.0e3f) * 1.0f;
    test_config.sample_time = 0.5f;
}

void tearDown(void)
{
}

void test_uz_parameterid_rs_init_pointer_not_null(void)
{
    uz_parameterid_rc_t* test_instance = uz_parameterid_rc_init(test_config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_parameterid_rs_init_equal(void){
    uz_parameterid_rc_t* test_instance = uz_parameterid_rc_init(test_config);
    struct uz_parameterid_rc_config_t get_internal_config = uz_parameterid_rc_get_config(test_instance);

    TEST_ASSERT_EQUAL_FLOAT(test_config.id_ref, get_internal_config.id_ref);
    TEST_ASSERT_EQUAL_FLOAT(test_config.iq_ref, get_internal_config.iq_ref);
}

void test_uz_parameterid_rc_generate_outputs_motor(void){
    test_config.wait_time = 4.0f * test_config.isr_steptime;
    uz_parameterid_rc_t* test_instance2 = uz_parameterid_rc_init(test_config);
    struct uz_parameterid_rc_meas_out_t actual_output;
    float c = 500.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rc_generate_outputs(test_instance2, 1.0f, 1.0f, 1.0f, 1.0f, 1000.0f);
    }
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual_output.set_out.id_set);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual_output.set_out.iq_set);
    TEST_ASSERT_EQUAL_FLOAT(-1000.0f, actual_output.set_out.n_set);
    setUp();
}

void test_uz_parameterid_rc_generate_outputs_calc_u_ind(void){
    test_config.wait_time = 4.0f * test_config.isr_steptime;
    test_config.sample_time = 10.0f * test_config.isr_steptime;
    uz_parameterid_rc_t* test_instance2 = uz_parameterid_rc_init(test_config);
    struct uz_parameterid_rc_meas_out_t actual_output;
    float c = 16.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rc_generate_outputs(test_instance2, 1.0f, 1.0f, 1.0f, 1.0f, 1000.0f);
    }

    float r_s = (1.75e-6f * 1000.0f *  1000.0f + 5.733e-4f *  1000.0f + 28.4648)/1000.0f;
    float u_ind_d = 1.0f - r_s * 1.0f;

    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output.set_out.id_set);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output.set_out.iq_set);
    TEST_ASSERT_EQUAL_FLOAT(-1000.0f, actual_output.set_out.n_set);
    setUp();
}

#endif // TEST
