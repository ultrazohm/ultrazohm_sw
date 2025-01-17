#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"

#include "../uz_ParameterID_rc/uz_ParameterID_rc.h"

struct uz_parameterID_rc_config_t test_config = {0};

void setUp(void)
{
     test_config.abs_id_max_Amps = 5.0f; 
     test_config.abs_iq_max_Amps = 5.0f;
     test_config.id_steps = 5U;
     test_config.iq_steps = 5U;
     test_config.n_start_rpm = 100.0f;
     test_config.n_stop_rpm = 1100.0f;
     test_config.n_steps = 10U;
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
    TEST_ASSERT_EQUAL_FLOAT(test_config.abs_id_max_Amps , get_internal_config.abs_id_max_Amps );
    TEST_ASSERT_EQUAL_FLOAT(test_config.abs_iq_max_Amps , get_internal_config.abs_iq_max_Amps );
}


void test_uz_parameterID_rc_test_initial_outputs(void){
    uz_parameterID_rc_t* rc_instance4 = uz_parameterID_rc_init(test_config);
    struct uz_parameterID_rc_ref_val_t test_output;
    test_output = uz_parameterID_rc_generate_idq_ref(rc_instance4);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_output.iq_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_start_rpm, test_output.n_ref_rpm);
}


// works when the duration of the state rc_wait is set to 1 isr cycle (self->counter.wait == 1U) 
void test_uz_parameterID_rc_test_generate_outputs(void){
    uz_parameterID_rc_t* rc_instance = uz_parameterID_rc_init(test_config);
    struct uz_parameterID_rc_ref_val_t test_output;
    for (uint32_t i = 0; i < 2; i++)
    {
        test_output = uz_parameterID_rc_generate_idq_ref(rc_instance);
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_output.iq_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(100.0f, test_output.n_ref_rpm);
    
    for (uint32_t j = 0; j < 7; j++)
    {
        test_output = uz_parameterID_rc_generate_idq_ref(rc_instance);
    }
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, test_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.abs_iq_max_Amps , test_output.iq_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_start_rpm, test_output.n_ref_rpm);
        
    for (uint32_t j = 0; j < 6; j++)
    {
        test_output = uz_parameterID_rc_generate_idq_ref(rc_instance);
    }
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, test_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.abs_iq_max_Amps, test_output.iq_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(100.0f, test_output.n_ref_rpm);

    for (uint32_t j = 0; j < 24; j++)
    {
        test_output = uz_parameterID_rc_generate_idq_ref(rc_instance);
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, test_output.iq_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(100.0f, test_output.n_ref_rpm);

        for (uint32_t j = 0; j < 180; j++)
    {
        test_output = uz_parameterID_rc_generate_idq_ref(rc_instance);
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, test_output.iq_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(100.0f, test_output.n_ref_rpm);

    for (uint32_t j = 0; j < 250; j++)
    {
        test_output = uz_parameterID_rc_generate_idq_ref(rc_instance);
    }
    TEST_ASSERT_EQUAL_FLOAT(200.0f, test_output.n_ref_rpm);

    for (uint32_t j = 0; j < 250000; j++)
    {
        test_output = uz_parameterID_rc_generate_idq_ref(rc_instance);
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_output.iq_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_output.n_ref_rpm);
}


#endif // TEST
