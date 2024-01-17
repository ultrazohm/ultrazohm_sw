#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_parameterid_rs.h"
#include "mock_uz_SystemTime.h"
#include "../uz_global_configuration.h"


struct uz_parameterid_rs_config_t test_config = {0};
struct uz_parameterid_rs_increments_t test_increments = {0};
struct uz_parameterid_output test_output = {0};

void setUp(void)
{
    test_config.n_start = 100.0f;
    test_config.n_end = 1000.0f;
    test_config.n_steps = 9.0f;
    test_increments.n_increment = (test_config.n_end - test_config.n_start)/test_config.n_steps;
    test_config.i_start = 10.0f;
    test_config.i_diff = 1.0f; 
    test_config.i_steps = 9.0f;
    test_increments.i_increment = (test_config.i_diff - test_config.i_start)/test_config.i_steps;
    test_config.isr_steptime = (1.0f / 10.0e3f) * 1.0f;
    test_output.i_sample = 0.0f;
    test_output.n_sample = 0.0f;
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
    TEST_ASSERT_EQUAL_FLOAT(test_config.i_diff, actual_configuration.i_diff);
    TEST_ASSERT_EQUAL_FLOAT(test_config.i_steps, actual_configuration.i_steps);  
    struct uz_parameterid_rs_increments_t actual_increments = uz_parameterid_rs_get_current_increments(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(test_increments.n_increment, actual_increments.n_increment);   
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

void test_uz_parameterid_rs_i_diff_null(void){ 
    test_config.i_diff = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.i_diff = 1.0f;
    test_config.i_start = 10.0f;
}

void test_uz_parameterid_rs_reset_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_reset(NULL));
}

void test_uz_parameterid_rs_sample_calc_isr_counter_and_elapsed_time(void){
    uz_parameterid_rs_t* test_instance2 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output = {0};
    float c = 20000.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_sample(test_instance2);
    }
    float output_time = uz_parameterid_rs_get_elapsed_time(test_instance2);
    float output_isr_counter = uz_parameterid_rs_get_isr_counter(test_instance2);
    float actual_time = c * test_config.isr_steptime;
    float end_time = uz_parameterid_rs_get_end_time(test_instance2); 
    float actual_endtime = (test_config.i_steps+1.0f) * (test_config.n_steps+1.0f) * 2.0f ; 
    TEST_ASSERT_EQUAL_FLOAT(actual_time, output_time);
    TEST_ASSERT_EQUAL_FLOAT(c, output_isr_counter);
    TEST_ASSERT_EQUAL_FLOAT(c, actual_output.isr_stepcounter);
    TEST_ASSERT_EQUAL_FLOAT(end_time, actual_endtime);
}

void test_uz_parameterid_rs_sample(void){
    uz_parameterid_rs_t* test_instance3 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output = {0};
    float c = 200000.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_sample(test_instance3);
    }

    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual_output.i_sample);
    TEST_ASSERT_EQUAL_FLOAT(200.0f, actual_output.n_sample);
}


void test_uz_parameterid_rs_sample_finished(void){
    uz_parameterid_rs_t* test_instance4 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output = {0};
    float c = ((test_config.i_steps+1.0f) * (test_config.n_steps+1.0f) * 2.0f)/test_config.isr_steptime+1.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_sample(test_instance4);
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output.i_sample);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output.n_sample);
}

#endif // TEST
