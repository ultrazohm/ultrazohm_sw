#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_FOC.h"
TEST_FILE("uz_piController.c")
TEST_FILE("uz_signals.c")


uz_PI_Controller_config config_id = {0};
void setUp_PI_Controller_id(void)
{
    config_id.Kp = 6.75f;
    config_id.Ki = 2000.0f;
    config_id.samplingTime_sec = 0.0001f;
    config_id.upper_limit = 10.0f;
    config_id.lower_limit = -10.0f;
}

uz_PI_Controller_config config_iq = {0};
void setUp_PI_Controller_iq(void)
{
    config_iq.Kp = 6.75f;
    config_iq.Ki = 2000.0f;
    config_iq.samplingTime_sec = 0.0001f;
    config_iq.upper_limit = 10.0f;
    config_iq.lower_limit = -10.0f;
}

uz_PI_Controller_config config_n = {0};
void setUp_PI_Controller_n(void)
{
    config_n.Kp = 0.00864f,
    config_n.Ki = 0.0864f,
    config_n.samplingTime_sec = 0.0001f;
    config_n.upper_limit = 10.0f;
    config_n.lower_limit = -10.0f;
}

uz_FOC_config config_FOC = {
    .iq_ref_Ampere = 1.0f,
    .id_ref_Ampere = 1.0f,
    .n_ref_rpm = 1000.0f,
    .FOC_Select = 1U,
    .polePairs = 4.0f,
    .L_q = 0.00027f,
    .L_d = 0.00027f,
    .psi_pm = 0.0082,
    .Reset = false
};

void test_uz_FOC_init_L_d_negative(void){
    setUp_PI_Controller_n();
    setUp_PI_Controller_id();
    setUp_PI_Controller_iq();
    config_FOC.L_d = -0.1f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
    }

void test_uz_FOC_init_L_d_zero(void){
    config_FOC.L_d = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
    config_FOC.L_d = 0.00027f;
}

void test_uz_FOC_init_L_q_negative(void){
    config_FOC.L_q = -0.1f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_L_q_zero(void){
    config_FOC.L_q = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
    config_FOC.L_q = 0.00027f;
}

void test_uz_FOC_init_psi_pm_negative(void){
    config_FOC.psi_pm = -0.1f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_psi_pm_zero(void){
    config_FOC.psi_pm = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
    config_FOC.psi_pm = 0.0082f;
}

void test_uz_FOC_init_polePairs_negative(void){
    config_FOC.polePairs = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_polePairs_zero(void){
    config_FOC.polePairs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
    config_FOC.polePairs = 4.0f;
}

void test_uz_FOC_init_FOC_select_too_big(void){
    config_FOC.FOC_Select = 20U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_FOC_select_negative(void){
    config_FOC.FOC_Select = -20U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_FOC_select_zero(void){
    config_FOC.FOC_Select = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
    config_FOC.FOC_Select = 1U;
}



void test_uz_FOC_linear_decouppling_FOC_NULL(void){
    uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
    float u_d_vor = 0.0f;
    float u_q_vor = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_linear_decouppling(values, NULL, &u_d_vor, &u_q_vor));
}

void test_uz_FOC_linear_decouppling_values_NULL(void){
    setUp_PI_Controller_id();
    setUp_PI_Controller_iq();
    //setUp_PI_Controller_n();
    uz_FOC* FOC = uz_FOC_init(config_FOC,config_id, config_iq, config_n);
    float u_d_vor = 0.0f;
    float u_q_vor = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_linear_decouppling(NULL, FOC, &u_d_vor, &u_q_vor));
}

// void test_uz_FOC_linear_decouppling_u_d_vor_NULL(void){
//     uz_FOC* FOC = uz_FOC_init(config_FOC,config_id, config_iq, config_n);
//     uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
//     float u_q_vor = 0.0f;
//     TEST_ASSERT_FAIL_ASSERT(uz_FOC_linear_decouppling(values, FOC, NULL, &u_q_vor));
// }

// void test_uz_FOC_linear_decouppling_u_q_vor_NULL(void){
//     uz_FOC* FOC = uz_FOC_init(config_FOC,config_id, config_iq, config_n);
//     uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
//     float u_d_vor = 0.0f;
//     TEST_ASSERT_FAIL_ASSERT(uz_FOC_linear_decouppling(values, FOC, &u_d_vor, NULL));
// }

// void test_uz_FOC_linear_decouppling_output(void){
// 	//Values for comparision from simulation
// 	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
//     uz_FOC* FOC = uz_FOC_init(config_FOC,config_id, config_iq, config_n);
// 	float ud_vor = 0.0f;
// 	float uq_vor = 0.0f;
// 	values->omega_el_rad_per_sec = 714.0f;
// 	values->i_q_Ampere = 1.0f;
// 	values->i_d_Ampere = 1.0f;
// 	uz_FOC_linear_decouppling(values, FOC, &ud_vor, &uq_vor);
// 	TEST_ASSERT_EQUAL_FLOAT(-0.19f,roundf(ud_vor*100)/100);
// 	TEST_ASSERT_EQUAL_FLOAT(6.05f,roundf(uq_vor*100)/100);
// }

void test_uz_FOC_SpaceVector_Limitation_VoltageRef_NULL(void){
    uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpaceVector_Limitation(NULL,values));
}

void test_uz_FOC_SpaceVector_Limitation_Values_NULL(void){
    uz_FOC_VoltageReference* reference = uz_FOC_VoltageReference_init();
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpaceVector_Limitation(reference,NULL));
}

void test_uz_FOC_SpaceVector_Limitation_U_zk_negative(void){
    uz_FOC_VoltageReference* reference = uz_FOC_VoltageReference_init();
    uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
    values->U_zk_Volts = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpaceVector_Limitation(reference,values));
}

void test_uz_FOC_SpaceVector_Limitation_U_zk_zero(void){
    uz_FOC_VoltageReference* reference = uz_FOC_VoltageReference_init();
    uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
    values->U_zk_Volts = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpaceVector_Limitation(reference,values));
}

void test_uz_FOC_SpaceVector_Limitation_output(void){
    //Values for comparision from simulation
    uz_FOC_VoltageReference* reference = uz_FOC_VoltageReference_init();
    uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
    values->U_zk_Volts = 24.0f;
    float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_omega[11]={0.0f, 0.0f, 0.0f, 0.0f, 0.0121f, 0.0402f, 0.0861f, 0.149f, 0.227f, 0.315f, 0.408f};
    float ud_in[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.46f};
    float uq_in[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f};
    float ud_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.46f};
    float uq_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f}; 
    for(int i=0;i<11;i++){
        values->i_q_Ampere = values_iq[i];
        values->omega_el_rad_per_sec = values_omega[i];
        reference->u_d_ref_Volts = ud_in[i];
        reference->u_q_ref_Volts = uq_in[i];
        uz_FOC_SpaceVector_Limitation(reference, values);
		TEST_ASSERT_EQUAL_FLOAT(ud_out[i],roundf(reference->u_d_ref_Volts*100)/100);
	    TEST_ASSERT_EQUAL_FLOAT(uq_out[i],roundf(reference->u_q_ref_Volts*100)/100);
    }
}

void test_uz_FOC_SpaceVector_Limitation_output_transition_to_limit(void){
    //Values for comparision from simulation
    uz_FOC_VoltageReference* reference = uz_FOC_VoltageReference_init();
    uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
    bool output = false;
    values->U_zk_Volts = 12.0f;
    float values_iq[11]={1.7f, 1.7f, 1.7f, 1.7f, 1.7f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_omega[11]={825.67f, 825.69f, 825.72f, 825.735f, 825.75f,825.765f, 825.78f, 825.8f, 825.82f, 825.84f, 825.851f};
    float ud_in[11]={-0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f,-0.436f, -0.436f, -0.436f, -0.436f, -0.436f};
    float uq_in[11]={6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.92f};
    float ud_out[11]={-0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f};
    float uq_out[11]={6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f}; 
    float output_ref[11]={false, false, false, false, false, false, false, false, false, false, true};
    for(int i=0;i<11;i++){
        values->i_q_Ampere = values_iq[i];
        values->omega_el_rad_per_sec = values_omega[i];
        reference->u_d_ref_Volts = ud_in[i];
        reference->u_q_ref_Volts = uq_in[i];
        output = uz_FOC_SpaceVector_Limitation(reference, values);
		TEST_ASSERT_EQUAL_FLOAT(ud_out[i],roundf(reference->u_d_ref_Volts*1000)/1000);
	    TEST_ASSERT_EQUAL_FLOAT(uq_out[i],roundf(reference->u_q_ref_Volts*100)/100);
        TEST_ASSERT_EQUAL_INT(output_ref[i], output);
    }
    //values->U_zk_Volts = 24.0f;
}

void test_uz_FOC_SpaceVector_Limitation_output_limited(void){
    //Values for comparision from simulation
    uz_FOC_VoltageReference* reference = uz_FOC_VoltageReference_init();
    uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
    bool output = false;
    values->U_zk_Volts = 12.0f;
    float values_iq[11]={1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f};
	float values_omega[11]={833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f};
    float ud_in[11]={-0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f,-0.294f, -0.294f, -0.294f, -0.294f, -0.294f};
    float uq_in[11]={11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f};
    float ud_out[11]={-0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f};
    float uq_out[11]={6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f}; 
    float output_ref[11]={true, true, true, true, true, true, true, true, true, true, true};
    for(int i=0;i<11;i++){
        values->i_q_Ampere = values_iq[i];
        values->omega_el_rad_per_sec = values_omega[i];
        reference->u_d_ref_Volts = ud_in[i];
        reference->u_q_ref_Volts = uq_in[i];
        output = uz_FOC_SpaceVector_Limitation(reference, values);
		TEST_ASSERT_EQUAL_FLOAT(ud_out[i],roundf(reference->u_d_ref_Volts*1000)/1000);
	    TEST_ASSERT_EQUAL_FLOAT(uq_out[i],roundf(reference->u_q_ref_Volts*100)/100);
        TEST_ASSERT_EQUAL_INT(output_ref[i], output);
    }
}
#endif // TEST