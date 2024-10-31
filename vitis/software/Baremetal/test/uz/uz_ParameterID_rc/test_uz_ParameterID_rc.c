#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"

#include "../uz_ParameterID_rc/uz_ParameterID_rc.h"

struct uz_parameterID_rc_config_t test_config = {0};

void setUp(void)
{
     test_config.id_start_Amps = -1.0f; 
     test_config.id_stop_Amps = -5.0f;
     test_config.iq_start_Amps = 1.0f;
     test_config.iq_stop_Amps = 5.0f;
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

void test_uz_parameterID_rs_init_equal(void){
    uz_parameterID_rc_t* rc_instance3 = uz_parameterID_rc_init(test_config);
    struct uz_parameterID_rc_config_t get_internal_config = uz_parameterID_rc_get_config(rc_instance3);

 // test_config.id_start_Amps=5.0f;
    TEST_ASSERT_EQUAL_FLOAT(test_config.id_start_Amps, get_internal_config.id_start_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.id_stop_Amps, get_internal_config.id_stop_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.iq_start_Amps, get_internal_config.iq_start_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.iq_stop_Amps, get_internal_config.iq_stop_Amps);
}


void test_uz_parameterID_rc_test_initial_outputs(void){
    uz_parameterID_rc_t* rc_instance4 = uz_parameterID_rc_init(test_config);
    struct uz_parameterID_rc_ref_val_t test_output;
    test_output = uz_parameterID_rc_generate_idq_ref(rc_instance4);
    TEST_ASSERT_EQUAL_FLOAT(test_config.id_start_Amps, test_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.iq_start_Amps, test_output.iq_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_start_rpm, test_output.n_ref_rpm);
}


#endif // TEST
