#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_FOC.h"

uz_FOC_config config = {
	.Kp_id = 0.0f,
	.Kp_iq = 0.0f,
	.Kp_n = 0.0f,
	.Ki_id = 0.0f,
	.Ki_iq = 0.0f,
	.Ki_n = 0.0f,
	.iq_ref_Ampere = 0.0f,
	.id_ref_Ampere = 0.0f,
	.n_ref_rpm = 0.0f,
	.d_y_max = 0.0f,
	.d_y_min = 0.0f,
	.SamplingTime_sec=0.00001f,
	.polePairs=4,
	.FOC_Select = 1U,
	.Reset = false,
};

void test_FOC_get_sign_of_value_input_positive(void){
TEST_ASSERT_EQUAL_FLOAT(1,uz_FOC_get_sign_of_value(20.0f));
}

void test_FOC_get_sign_of_value_input_negative(void){
TEST_ASSERT_EQUAL_FLOAT(-1,uz_FOC_get_sign_of_value(-20.0f));
}

void test_FOC_get_sign_of_value_input_zero(void){
TEST_ASSERT_EQUAL_FLOAT(0,uz_FOC_get_sign_of_value(0.0f));
}

void test_uz_FOC_linear_decouppling_values_Null(void){
	float ud_vor;
	float uq_vor;
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_linear_decouppling(NULL, config, &ud_vor, &uq_vor));
}

void test_uz_FOC_linear_decouppling_uq_vor_Null(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	float uq_vor;
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_linear_decouppling(values, config, NULL, &uq_vor));
}

void test_uz_FOC_linear_decouppling_ud_vor_Null(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	float ud_vor;
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_linear_decouppling(values, config, &ud_vor, NULL));
}

void test_uz_FOC_linear_decouppling_Lq_negative(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	config.L_q = -10.0f;
	float ud_vor;
	float uq_vor;
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_linear_decouppling(values, config, &ud_vor, &uq_vor));
    config.L_q = 0.00027f;
}

void test_uz_FOC_linear_decouppling_Ld_negative(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	config.L_d = -10.0f;
	float ud_vor;
	float uq_vor;
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_linear_decouppling(values, config, &ud_vor, &uq_vor));
    config.L_d = 0.00027f;
}

void test_uz_FOC_linear_decouppling_psi_pm_negative(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	config.psi_pm = -10.0f;
	float ud_vor;
	float uq_vor;
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_linear_decouppling(values, config, &ud_vor, &uq_vor));
    config.psi_pm = 0.0082f;
}

void test_uz_FOC_linear_decouppling_output(void){
	//Values for comparision from simulation
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	float ud_vor;
	float uq_vor;
	values->omega_el_rad_per_sec = 714.0f;
	values->i_q_Ampere = 1.0f;
	values->i_d_Ampere = 1.0f;
	uz_FOC_linear_decouppling(values, config, &ud_vor, &uq_vor);
	TEST_ASSERT_EQUAL_FLOAT(-0.19f,roundf(ud_vor*100)/100);
	TEST_ASSERT_EQUAL_FLOAT(6.05f,roundf(uq_vor*100)/100);
}

void test_uz_FOC_SpaceVector_Limitation_reference_NULL(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpaceVector_Limitation(NULL, values));
}

void test_uz_FOC_SpaceVector_Limitation_values_NULL(void){
	uz_FOC_VoltageReference* reference = uz_FOC_VoltageReference_init();
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpaceVector_Limitation(reference, NULL));
}

void test_uz_FOC_SpaceVector_Limitation_Uzk_negativ(void){
 	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
 	uz_FOC_VoltageReference* reference = uz_FOC_VoltageReference_init();
 	values->U_zk_Volts = -10.0f;
 	TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpaceVector_Limitation(reference, values));
 }

void test_uz_FOC_SpaceVector_Limitation_Uzk_zero(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	uz_FOC_VoltageReference* reference = uz_FOC_VoltageReference_init();
	values->U_zk_Volts = 0.0f;
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpaceVector_Limitation(reference, values));
}

#endif // TEST