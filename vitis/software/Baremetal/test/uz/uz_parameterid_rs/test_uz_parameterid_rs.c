#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_parameterid_rs.h"

struct uz_parameterid_rs_config_t test_config = {0};
struct uz_parameterid_rs_increments_t test_increments = {0};
struct uz_parameterid_output test_output = {0};

void setUp(void)
{
    test_config.n_start = 100.0f;
    test_config.n_end = 1000.0f;
    test_config.n_steps = 9.0f;
    test_increments.n_increment = (test_config.n_end - test_config.n_start)/test_config.n_steps;
    test_config.i_start = 1.0f;
    test_config.i_end = 10.0f; 
    test_config.i_steps = 9.0f;
    test_increments.i_increment = (test_config.i_end - test_config.i_start)/test_config.i_steps;
    test_output.i_sample = 10.0f;
    test_output.n_sample = 100.0f;
}

void tearDown(void)
{
}

void test_uz_parameterid_rs_init_pointer_not_null(void)
{
    uz_parameterid_rs_t* test_instance = uz_parameterid_rs_init(test_config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_parameterid_rs_init_equal(void)
{
    uz_parameterid_rs_t* test_instance = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_rs_config_t actual_configuration = uz_parameterid_rs_get_current_config(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_start, actual_configuration.n_start);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_end, actual_configuration.n_end);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_steps, actual_configuration.n_steps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.i_start, actual_configuration.i_start);
    TEST_ASSERT_EQUAL_FLOAT(test_config.i_end, actual_configuration.i_end);
    TEST_ASSERT_EQUAL_FLOAT(test_config.i_steps, actual_configuration.i_steps);  
    struct uz_parameterid_rs_increments_t actual_increments = uz_parameterid_rs_get_current_increments(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(test_increments.n_increment, actual_increments.n_increment); 
    TEST_ASSERT_EQUAL_FLOAT(test_increments.i_increment, actual_increments.i_increment);   
}

void test_uz_parameterid_rs_negative_end_speed(void){ 
    test_config.n_end = -200.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_end = 1000.0f;
}

void test_uz_parameterid_rs_negative_start_speed(void){ 
    test_config.n_start = -200.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_start = 100.0f;
}

void test_uz_parameterid_rs_negative_steps_speed(void){ 
    test_config.n_steps = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_steps = 9.0f;
}

void test_uz_parameterid_rs_start_higher_end_speed(void){ 
    test_config.n_end = 100.0f;
    test_config.n_start = 1000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_end = 1000.0f;
    test_config.n_start = 100.0f;
}

void test_uz_parameterid_rs_negative_steps_current(void){ 
    test_config.n_steps = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_steps = 9.0f;
}

void test_uz_parameterid_rs_start_higher_end_current(void){ 
    test_config.i_end = 10.0f;
    test_config.i_start = 20.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.i_end = 10.0f;
    test_config.i_start = 1.0f;
}

void test_uz_parameterid_rs_reset_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_reset(NULL));
}

void test_uz_parameterid_rs_sample(void){
    uz_parameterid_rs_t* test_instance2 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output = uz_parameterid_rs_sample(test_instance2);
    TEST_ASSERT_EQUAL_FLOAT(test_output.n_sample, actual_output.n_sample);
}

#endif // TEST
