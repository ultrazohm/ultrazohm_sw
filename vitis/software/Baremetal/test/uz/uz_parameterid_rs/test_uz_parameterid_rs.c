#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_parameterid_rs.h"
#include "mock_uz_SystemTime.h"
#include "../uz_global_configuration.h"
#include "stdbool.h"


struct uz_parameterid_rs_config_t test_config = {0};
struct uz_parameterid_rs_increments_t test_increments = {0};
struct uz_parameterid_output test_output = {0};
float test_temp_degrees = 25.0f;

void setUp(void)
{
    test_config.n_start_rpm = 100.0f;
    test_config.n_end_rpm = 1000.0f;
    test_config.n_steps = 9.0f;
    test_increments.n_increment = (test_config.n_end_rpm - test_config.n_start_rpm)/test_config.n_steps;
    test_config.i_pos_Amps = 10.0f;
    test_config.i_neg_Amps = -10.0f; 
    test_config.i_repeats = 1.0f;
    test_config.i_steptime = 1.0f;
    test_config.abs_iq_max_Amps = 10.0f;
    test_config.check_temp = false;
    test_config.wait_time = 1.0f;
    test_config.isr_steptime = (1.0f / 10.0e3f) * 1.0f;
    test_output.id_ref_Amps = 0.0f;
    test_output.n_ref_rpm= 0.0f;

}

void tearDown(void)
{
}


void test_uz_parameterid_rs_init_equal(void)
{
    uz_parameterid_rs_t* test_instance = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_rs_config_t actual_configuration = uz_parameterid_rs_get_current_config(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_start_rpm, actual_configuration.n_start_rpm);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_end_rpm, actual_configuration.n_end_rpm);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_steps, actual_configuration.n_steps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.i_pos_Amps, actual_configuration.i_pos_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.i_neg_Amps, actual_configuration.i_neg_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.i_repeats, actual_configuration.i_repeats);  
    struct uz_parameterid_rs_increments_t actual_increments = uz_parameterid_rs_get_current_increments(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(test_increments.n_increment, actual_increments.n_increment);   
}
void test_uz_parameterid_rs_negative_end_speed(void){ 
    test_config.n_end_rpm = -200.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_end_rpm = 1000.0f;
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
    test_config.n_end_rpm = 100.0f;
    test_config.n_start_rpm = 1000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_end_rpm = 1000.0f;
    test_config.n_start_rpm = 100.0f;
}

void test_uz_parameterid_rs_negative_steps_current(void){ 
    test_config.n_steps = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_init(test_config));
    test_config.n_steps = 9.0f;
}
void test_uz_parameterid_rs_reset_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_parameterid_rs_reset(NULL));
}
void test_uz_parameterid_rs_generate_outputs_test_isr_counter(void){
    uz_parameterid_rs_t* test_instance2 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output;
    float c = 20000.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, test_temp_degrees);
    }
    float output_isr_counter = uz_parameterid_rs_get_isr_counter(test_instance2);
    TEST_ASSERT_EQUAL_FLOAT(c, output_isr_counter);
    TEST_ASSERT_EQUAL_FLOAT(c, actual_output.isr_stepcounter);
    test_config.i_steptime = 2.0f;
    test_config.wait_time = 4.0f;
}
void test_uz_parameterid_rs_generate_outputs_i_pos_Amps_state(void){
    uz_parameterid_rs_t* test_instance2 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output;
    float c = 10003.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, test_temp_degrees);
    }
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_start_rpm, actual_output.n_ref_rpm);

    for (int i = 0; i<=10000; i++){
    actual_output = uz_parameterid_rs_generate_outputs(test_instance2, test_temp_degrees);
    }
    TEST_ASSERT_EQUAL_FLOAT(-10.0f, actual_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(test_config.n_start_rpm, actual_output.n_ref_rpm);

    for (int i = 0; i<=10000; i++){
    actual_output = uz_parameterid_rs_generate_outputs(test_instance2, test_temp_degrees);
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(200.0f, actual_output.n_ref_rpm);

}

void test_uz_parameterid_rs_generate_outputs_test_tempcheck(void){
    test_config.check_temp = true;
    uz_parameterid_rs_t* test_instance2 = uz_parameterid_rs_init(test_config);
    struct uz_parameterid_output actual_output;
    float c = 3.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, test_temp_degrees);
    }
    test_temp_degrees = 50.0f; // Set temperature above threshold
    for(int i = 0; i<=10000; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, test_temp_degrees);
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output.id_ref_Amps);    
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output.iq_ref_Amps);    
    test_temp_degrees = 20.0f; // Set temperature below threshold
    for(int i = 0; i<=2; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, test_temp_degrees);
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output.id_ref_Amps);    
    TEST_ASSERT_EQUAL_FLOAT(test_config.abs_iq_max_Amps, actual_output.iq_ref_Amps);   
    test_temp_degrees = 25.0f; // Set temperature below threshold
    for (int i = 0; i<=5000; i++){
        actual_output = uz_parameterid_rs_generate_outputs(test_instance2, test_temp_degrees);
    }
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual_output.id_ref_Amps);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output.iq_ref_Amps);  
}

#endif // TEST
