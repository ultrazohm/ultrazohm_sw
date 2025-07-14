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
    test_config.n_start_rpm = 100.0f;
    test_config.n_end = 1000.0f;
    test_config.n_steps = 9.0f;
    test_increments.n_increment = (test_config.n_end - test_config.n_start_rpm)/test_config.n_steps;
    test_config.i_pos_Amps = 10.0f;
    test_config.i_neg_Amps = 1.0f; 
    test_config.i_repeats = 5.0f;
    test_config.i_steptime = 2.0f;
    test_config.wait_time = 4.0f;
    test_config.isr_steptime = (1.0f / 10.0e3f) * 1.0f;
    test_output.id_ref_Amps = 0.0f;
    test_output.n_ref_rpm = 0.0f;
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
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_start_rpm, actual_configuration.n_start_rpm);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_end, actual_configuration.n_end);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_steps, actual_configuration.n_steps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.i_pos_Amps, actual_configuration.i_pos_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.i_neg_Amps, actual_configuration.i_neg_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.i_repeats, actual_configuration.i_repeats);  
    struct uz_parameterid_rs_increments_t actual_increments = uz_parameterid_rs_get_current_increments(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(test_increments.n_increment, actual_increments.n_increment);   
}

void test_uz_parameterid_rs_negative_end_speed(void){ 
    test_config.n_end = -200.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_end = 1000.0f;
}

void test_uz_parameterid_rs_negative_start_speed(void){ 
    test_config.n_start_rpm = -200.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_start_rpm = 100.0f;
}

void test_uz_parameterid_rs_negative_steps_speed(void){ 
    test_config.n_steps = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_steps = 9.0f;
}

void test_uz_parameterid_rs_start_higher_end_speed(void){ 
    test_config.n_end = 100.0f;
    test_config.n_start_rpm = 1000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_end = 1000.0f;
    test_config.n_start_rpm = 100.0f;
}

void test_uz_parameterid_rs_negative_steps_current(void){ 
    test_config.n_steps = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_steps = 9.0f;
}

void test_uz_parameterid_rs_i_neg_Amps_null(void){ 
    test_config.i_neg_Amps = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.i_neg_Amps = 1.0f;
    test_config.i_pos_Amps = 10.0f;
}

void test_uz_parameterid_rs_reset_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_reset(NULL));
}

void test_uz_parameterid_rs_generate_outputs_test_isr_counter(void){
    uz_parameterid_rs_t* test_instance2 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output;
    float c = 20000.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, 1.0f, 1.0f);
    }
    float output_isr_counter = uz_parameterid_rs_get_isr_counter(test_instance2);
    TEST_ASSERT_EQUAL_FLOAT(c, output_isr_counter);
    TEST_ASSERT_EQUAL_FLOAT(c, actual_output.isr_stepcounter);
    test_config.i_steptime = 2.0f;
    test_config.wait_time = 4.0f;
}

void test_uz_parameterid_rs_generate_outputs_i_pos_Amps_state(void){
    test_config.i_steptime = 2.0f * test_config.isr_steptime;
    test_config.wait_time = 4.0f * test_config.isr_steptime;
    uz_parameterid_rs_t* test_instance2 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output;
    float c = 6.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, 1.0f, 1.0f);
    }
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual_output.i_sample);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_start_rpm, actual_output.n_sample);
    test_config.i_steptime = 2.0f;
    test_config.wait_time = 4.0f;
}

void test_uz_parameterid_rs_generate_outputs_i_increment_state(void){
    test_config.i_steptime = 2.0f * test_config.isr_steptime;
    test_config.wait_time = 4.0f * test_config.isr_steptime;
    uz_parameterid_rs_t* test_instance2 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output;
    float c = 8.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, 1.0f, 1.0f);
    }
    TEST_ASSERT_EQUAL_FLOAT(11.0f, actual_output.i_sample);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_start_rpm, actual_output.n_sample);
    test_config.i_steptime = 2.0f;
    test_config.wait_time = 4.0f;
}

void test_uz_parameterid_rs_generate_outputs_n_increment_and_wait(void){
    test_config.i_steptime = 2.0f * test_config.isr_steptime;
    test_config.wait_time = 4.0f * test_config.isr_steptime;
    uz_parameterid_rs_t* test_instance2 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output;
    float c = 76.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, 1.0f, 1.0f);
    }
    TEST_ASSERT_EQUAL_FLOAT(400.0f, actual_output.n_sample);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output.i_sample);
    test_config.i_steptime = 2.0f;
    test_config.wait_time = 4.0f;
}

void test_uz_parameterid_rs_generate_outputs_n_increment_and_i_pos_Amps(void){
    test_config.i_steptime = 2.0f * test_config.isr_steptime;
    test_config.wait_time = 4.0f * test_config.isr_steptime;
    uz_parameterid_rs_t* test_instance2 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output;
    int32_t c = 81; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, 1.0f, 1.0f);
    }
    TEST_ASSERT_EQUAL_FLOAT(400.0f, actual_output.n_sample);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual_output.i_sample);
    test_config.i_steptime = 2.0f;
    test_config.wait_time = 4.0f;
}



void test_uz_parameterid_rs_generate_outputs_start_state(void){
    test_config.i_steptime = 2.0f * test_config.isr_steptime;
    test_config.wait_time = 4.0f * test_config.isr_steptime;
    uz_parameterid_rs_t* test_instance2 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output;
    float c = 2.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, 1.0f, 1.0f);
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output.i_sample);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_start_rpm, actual_output.n_sample);
}


void test_uz_parameterid_rs_sample_fail_assert(void){
    uz_parameterid_rs_t* test_instance5 = uz_parameterid_rs_init(test_config);   
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_sample(test_instance5, 1.0f, 1.0f););

}

void test_uz_parameterid_rs_sample(void){
    test_config.wait_time = 2.0f * test_config.isr_steptime;
    test_config.i_steptime = 2.0f;
    test_config.i_repeats = 2.0f;
    enum state test; 
    float ud;
    float id;
    uz_parameterid_rs_t* test_instance5 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output;
    struct uz_parameterid_rs_sample_output test_output;
    float c = 10.0f*80004.0f; 
    for (int i = 0; i<=c; i++){
        test = uz_parameterid_rs_get_current_state(test_instance5);
        switch (test)
        {
        case i_pos_Amps:
            ud = 1.0f+(actual_output.n_sample/100.0f);
            id = 2.0f;  
            break;
         case i_increment:
            ud = 1.0f; 
            id = 1.0f; 
            break;       
        default:
            break;
        }
        actual_output = uz_parameterid_rs_generate_outputs(test_instance5, ud, id);
        test_output = uz_parameterid_rs_get_rs(test_instance5);
    }
    
    TEST_ASSERT_EQUAL_FLOAT(2.0f, test_output.rs_calc[1]);

}




#endif // TEST
