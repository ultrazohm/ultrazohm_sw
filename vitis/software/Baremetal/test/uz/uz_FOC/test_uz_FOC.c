#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_FOC.h"
TEST_FILE("uz_piController.c")
TEST_FILE("uz_signals.c")
TEST_FILE("uz_linear_decoupling.c")
TEST_FILE("uz_space_vector_limitation.c")



struct uz_FOC_config config = {0};
struct uz_dq_t i_actual_Ampere = {0};
struct uz_dq_t i_reference_Ampere = {0};
float omega_el_rad_per_sec = 0.0f;
float U_zk_Volts = 0.0f;
void setUp(void)
{
    config.config_id.Kp = 6.75f;
    config.config_id.Ki = 2000.0f;
    config.config_id.samplingTime_sec = 0.00001f;
    config.config_id.upper_limit = 10.0f;
    config.config_id.lower_limit = -10.0f;
    config.config_iq.Kp = 6.75f;
    config.config_iq.Ki = 2000.0f;
    config.config_iq.samplingTime_sec = 0.00001f;
    config.config_iq.upper_limit = 10.0f;
    config.config_iq.lower_limit = -10.0f;
    i_actual_Ampere.d = 0.0f;
    i_actual_Ampere.q = 0.0f;
    i_actual_Ampere.zero = 0.0f;
    omega_el_rad_per_sec = 0.0f;
    U_zk_Volts = 24.0f;
    config.config_lin_decoupling.Ld_Henry = 0.00027f;
    config.config_lin_decoupling.Lq_Henry = 0.00027f;
    config.config_lin_decoupling.Psi_PM_Vs = 0.0082f;
    i_reference_Ampere.d = 1.0f;
    i_reference_Ampere.q = 1.0f;
    i_reference_Ampere.zero = 0.0f;
}

void test_uz_FOC_reset_NULL(void){
    setUp();
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_reset(NULL));
}

void test_uz_FOC_set_Kp_id_NULL(void){
    setUp();
    float Kp_id = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Kp_id(NULL, Kp_id));
}

void test_uz_FOC_set_Kp_id_negative(void){
    setUp();
    float Kp_id = -10.0f;
    uz_FOC* instance = uz_FOC_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Kp_id(instance, Kp_id));
}

void test_uz_FOC_set_Ki_id_negative(void){
    setUp();
    float Ki_id = -10.0f;
    uz_FOC* instance = uz_FOC_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Ki_id(instance, Ki_id));
}

void test_uz_FOC_set_Kp_iq_NULL(void){
    setUp();
    float Kp_iq = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Kp_iq(NULL, Kp_iq));
}

void test_uz_FOC_set_Kp_iq_negative(void){
    setUp();
    float Kp_iq = -10.0f;
    uz_FOC* instance = uz_FOC_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Kp_iq(instance, Kp_iq));
}

void test_uz_FOC_set_Ki_iq_negative(void){
    setUp();
    float Ki_iq = -10.0f;
    uz_FOC* instance = uz_FOC_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Ki_iq(instance, Ki_iq));
}

void test_uz_FOC_sample_output(void){
    setUp();
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config);
    float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.76f, 0.819f, 0.863f, 0.895f, 0.919f, 0.937f};
    float values_id[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.899f, 0.924f, 0.943f};
	float values_omega[11]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f, 0.622f, 1.26f, 2.29f, 3.85f, 6.08f, 9.13f};
    float ud_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.756f, 0.588f, 0.461f};
    float uq_out[11]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f, 1.68f, 1.3f, 1.01f, 0.811f, 0.671f, 0.581}; 
    for(int i=0;i<11;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_reference_Ampere, i_actual_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
}

void test_uz_FOC_sample_output_SVLimitation_active(void){
    setUp();
    U_zk_Volts = 10.0f;
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config);
    float values_iq[11]={0.874f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f};
    float values_id[11]={1.0f, 0.998f, 0.997f, 0.996f, 0.995f, 0.995f, 0.994f, 0.994f, 0.994f, 0.994f, 0.993f};
	float values_omega[11]={673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f};
    float ud_out[11]={-0.159f, -0.146f, -0.138f, -0.131f, -0.126f, -0.123f, -0.12f, -0.118f, -0.116f, -0.115f, -0.114f};
    float uq_out[11]={5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77}; 
    for(int i=0;i<11;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_reference_Ampere, i_actual_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
}

void test_uz_FOC_reset(void){
    setUp();
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config);
    float values_iq[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
    float values_id[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
	float values_omega[5]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f};
    float ud_out[5]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f};
    float uq_out[5]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f}; 
    for(int i=0;i<5;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_reference_Ampere, i_actual_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
    uz_FOC_reset(instance);
    for(int i=0;i<5;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_reference_Ampere, i_actual_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
}

void test_uz_FOC_set_Kp_and_Ki_id(void){
    //Tests, if the new values are properly written into the FOC instance
    setUp();
    struct uz_dq_t output = {0};
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config);
    for(int i=0;i<11;i++){
        output = uz_FOC_sample(instance, i_reference_Ampere, i_actual_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    }    
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.95f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.95f, output.q);
    uz_FOC_set_Kp_id(instance, 0.0f);
    uz_FOC_set_Ki_id(instance, 0.0f);
    uz_FOC_reset(instance);
    for(int i=0;i<5;i++){
        output = uz_FOC_sample(instance, i_reference_Ampere, i_actual_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    }
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 0.0f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.83f, output.q);
}

void test_uz_FOC_set_Kp_and_Ki_iq(void){
    //Tests, if the new values are properly written into the FOC instance
    setUp();
    struct uz_dq_t output = {0};
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config);
    for(int i=0;i<11;i++){
        output = uz_FOC_sample(instance, i_reference_Ampere, i_actual_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    }    
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.95f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.95f, output.q);
    uz_FOC_set_Kp_iq(instance, 0.0f);
    uz_FOC_set_Ki_iq(instance, 0.0f);
    uz_FOC_reset(instance);
    for(int i=0;i<5;i++){
        output = uz_FOC_sample(instance, i_reference_Ampere, i_actual_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    }
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.83f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 0.0f, output.q);
}

void test_uz_FOC_get_ext_clamping_NULL(void){
    setUp();
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_get_ext_clamping(NULL));
}

void test_uz_FOC_get_ext_clamping_output(void){
    setUp();
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config);
    i_actual_Ampere.q = 0.0f;
    i_actual_Ampere.d = 0.0f;
    omega_el_rad_per_sec =  0.0f; 
    uz_FOC_sample(instance, i_reference_Ampere, i_actual_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    TEST_ASSERT_EQUAL_INT(0,uz_FOC_get_ext_clamping(instance));
    U_zk_Volts = 10.0f;
    i_actual_Ampere.q = 0.874f;
    i_actual_Ampere.d = 1.0f;
    omega_el_rad_per_sec =  673.0f; 
    uz_FOC_sample(instance, i_reference_Ampere, i_actual_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    TEST_ASSERT_EQUAL_INT(1,uz_FOC_get_ext_clamping(instance));
}
#endif // TEST