#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"

#include "../uz_ParameterID_rc/uz_ParameterID_rc.h"

struct uz_parameterID_rc_config_t test_config = {0};

void setUp(void)
{
     test_config.abs_id_max_Amps = 4.0f; 
     test_config.abs_iq_max_Amps = 4.0f;
     test_config.id_steps = 4U;
     test_config.iq_steps = 4U;
     test_config.n_start_rpm = 500.0f;
     test_config.n_stop_rpm = 1000.0f;
     test_config.n_steps = 1U;
     test_config.check_temp = true; 
}

void tearDown(void)
{
}

void test_uz_parameterID_rc_init_pointer_not_null(void)
{
    uz_parameterID_rc_t* rc_instance1 = uz_parameterID_rc_init(test_config);
    TEST_ASSERT_NOT_NULL(rc_instance1);
}

// used to test assertions for different id/iq conditions
void test_uz_parameterID_rc_assert_config(void){
    uz_parameterID_rc_t* rc_instance2 = uz_parameterID_rc_init(test_config);
}

void test_uz_parameterID_rc_init_equal(void){
    uz_parameterID_rc_t* rc_instance3 = uz_parameterID_rc_init(test_config);
    struct uz_parameterID_rc_config_t get_internal_config = uz_parameterID_rc_get_config(rc_instance3);

 // test_config.id_start_Amps=5.0f;
    TEST_ASSERT_EQUAL_FLOAT(test_config.abs_id_max_Amps, get_internal_config.abs_id_max_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.abs_iq_max_Amps, get_internal_config.abs_iq_max_Amps);
}

void test_uz_parameterID_rc_test_temp_check(void){
    uz_parameterID_rc_t* rc_instance4 = uz_parameterID_rc_init(test_config);
    struct uz_parameterID_rc_ref_val_t test_output;
    float temp_degrees = 50.0f; 
    for (size_t i = 0; i < 1000; i++)
    {
        test_output = uz_parameterID_rc_generate_idq_ref(rc_instance4, temp_degrees);
    }
    temp_degrees = 40.0f;
    for (size_t i = 0; i < 1000000; i++)
    {
        test_output = uz_parameterID_rc_generate_idq_ref(rc_instance4, temp_degrees);
    }
    



}

#endif // TEST
