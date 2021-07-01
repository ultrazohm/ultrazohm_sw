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
	.SamplingTime_sec=0.00001,
	.polePairs=4,
	.FOC_Select = 1U,
	.Reset = false,
};

void test_uz_FOC_update_PI_ID_Controller_variables_Null(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_update_PI_ID_Controller_variables(NULL,config,values));
}

void test_uz_FOC_update_PI_ID_Controller_values_Null(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	uz_FOC_PI_Controller_variables* variables = uz_FOC_PI_ID_Controller_variables_init(config, values);
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_update_PI_ID_Controller_variables(variables,config,NULL));
}

void test_uz_FOC_update_PI_IQ_Controller_variables_Null(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_update_PI_IQ_Controller_variables(NULL,config,values));
}

void test_uz_FOC_update_PI_IQ_Controller_values_Null(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	uz_FOC_PI_Controller_variables* variables = uz_FOC_PI_IQ_Controller_variables_init(config, values);
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_update_PI_IQ_Controller_variables(variables,config,NULL));
}

void test_uz_FOC_update_PI_N_Controller_variables_Null(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_update_PI_N_Controller_variables(NULL,config,values));
}

void test_uz_FOC_update_PI_N_Controller_values_Null(void){
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	uz_FOC_PI_Controller_variables* variables = uz_FOC_PI_N_Controller_variables_init(config, values);
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_update_PI_N_Controller_variables(variables,config,NULL));
}
void test_uz_FOC_Dead_Zone_min_greater_than_max(void){
config.d_y_max=-10.0f;
config.d_y_min=10.0f;
TEST_ASSERT_FAIL_ASSERT(uz_FOC_Dead_Zone(2.0f,config));
config.d_y_max=10.0f;
config.d_y_min=-10.0f;
}

void test_uz_FOC_Dead_Zone_input_greather_than_deadzone(void){
TEST_ASSERT_EQUAL_FLOAT(10.0f,uz_FOC_Dead_Zone(20.0f,config));
}

void test_uz_FOC_Dead_Zone_input_smaller_than_deadzone(void){
TEST_ASSERT_EQUAL_FLOAT(-10.0f,uz_FOC_Dead_Zone(-20.0f,config));
}

void test_uz_FOC_Dead_Zone_input_inside_deadzone(void){
TEST_ASSERT_EQUAL_FLOAT(0.0f,uz_FOC_Dead_Zone(3.0f,config));
}

void test_FOC_get_sign_of_value_input_positive(void){
TEST_ASSERT_EQUAL_FLOAT(1,uz_FOC_get_sign_of_value(20.0f));
}

void test_FOC_get_sign_of_value_input_negative(void){
TEST_ASSERT_EQUAL_FLOAT(-1,uz_FOC_get_sign_of_value(-20.0f));
}

void test_FOC_get_sign_of_value_input_zero(void){
TEST_ASSERT_EQUAL_FLOAT(0,uz_FOC_get_sign_of_value(0.0f));
}

void test_uz_FOC_Clamping_Circuit_activate_clamping_false(void){
 TEST_ASSERT_EQUAL_FLOAT(false,uz_FOC_Clamping_Circuit(-0.03f,-0.05f,config));   
}

void test_uz_FOC_Clamping_Circuit_activate_clamping_true(void){
 TEST_ASSERT_EQUAL_FLOAT(true,uz_FOC_Clamping_Circuit(-30.0f,-25.0f,config));   
}

void test_uz_FOC_PI_Controller_id_ControllerVariables_Null(void){
	TEST_ASSERT_FAIL_ASSERT(uz_FOC_PI_Controller(NULL,config,false));
}

void test_uz_FOC_PI_Controller_id_output(void){
	config.Kp_id = 6.75f;
	config.Kp_iq = 6.75f;
	config.Kp_n = 0.00864;
	config.Ki_id = 2000.0f;
	config.Ki_iq = 2000.0f;
	config.Ki_n = 0.0864f;
	config.id_ref_Ampere = 1.0f;
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	uz_FOC_PI_Controller_variables* variables = uz_FOC_PI_ID_Controller_variables_init(config, values);
	//Compare values with Simulink Simulation
	float values_id[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_output[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f};
	for(int i=0;i<11;i++){
		values->i_d_Ampere = values_id[i];
		variables = uz_FOC_update_PI_ID_Controller_variables(variables, config, values);
		TEST_ASSERT_EQUAL_FLOAT(values_output[i],roundf(uz_FOC_PI_Controller(variables,config,false)*100)/100);
	}
}

void test_uz_FOC_PI_Controller_iq_output(void){
	config.iq_ref_Ampere = 1.0f;
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	uz_FOC_PI_Controller_variables* variables = uz_FOC_PI_IQ_Controller_variables_init(config, values);
	//Compare values with Simulink Simulation
	float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_output[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f};
	for(int i=0;i<11;i++){
		values->i_q_Ampere = values_iq[i];
		variables = uz_FOC_update_PI_IQ_Controller_variables(variables, config, values);
		TEST_ASSERT_EQUAL_FLOAT(values_output[i],roundf(uz_FOC_PI_Controller(variables,config,false)*100)/100);
	}
}

void test_uz_FOC_PI_Controller_n_output(void){
	config.n_ref_rpm = 1000.0f;
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	uz_FOC_PI_Controller_variables* variables = uz_FOC_PI_N_Controller_variables_init(config, values);
	//Compare values with Simulink Simulation
	float values_omega[36]={0.0f, 0.0f, 0.0167f, 0.063f, 0.153f, 0.296f, 0.498f, 0.756f, 1.06f, 1.4f, 1.76f, 2.12f, 2.46f, 2.77f, 
	3.04f, 3.27f, 3.45f, 3.6f, 3.71f, 3.8f, 3.87f, 3.94f, 4.0f, 4.07f, 4.15f, 4.23f, 4.31f, 4.39f, 4.46f, 4.53f, 4.59f,
	4.64f, 4.67f, 4.7f, 4.72f, 4.73f};
	float values_output[36]={3.62f, 3.62f, 3.62f, 3.62f, 3.62f, 3.62f, 3.62f, 3.61f, 3.61f, 3.61f, 3.61f, 3.60f, 3.60f, 3.60f, 3.60f, 3.59f,
	3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 
	3.59f, 3.59f, 3.59f};
	bool ext_clamping[36]={false, true, true, true, true, false, false, false, false, false, false, false, false, false, false, false
	, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
	, false, false};
	for(int i=0;i<36;i++){
		values->omega_el_rad_per_sec = values_omega[i];
		variables = uz_FOC_update_PI_N_Controller_variables(variables, config, values);
		TEST_ASSERT_EQUAL_FLOAT(values_output[i],roundf(uz_FOC_PI_Controller(variables,config,ext_clamping[i])*100)/100);
	}
}

#endif // TEST

void test_uz_FOC_PI_Controller_id_output_Reset(void){
	config.id_ref_Ampere = 1.0f;
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	uz_FOC_PI_Controller_variables* variables = uz_FOC_PI_ID_Controller_variables_init(config, values);
	//Compare values with Simulink Simulation
	float values_id[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_output[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f};
	for(int i=0;i<11;i++){
		values->i_d_Ampere = values_id[i];
		variables = uz_FOC_update_PI_ID_Controller_variables(variables, config, values);
		TEST_ASSERT_EQUAL_FLOAT(values_output[i],roundf(uz_FOC_PI_Controller(variables,config,false)*100)/100);
	}
	config.Reset = true;
	values->i_d_Ampere = 0.956f;
	variables = uz_FOC_update_PI_ID_Controller_variables(variables, config, values);
	TEST_ASSERT_EQUAL_FLOAT(0.0f,roundf(uz_FOC_PI_Controller(variables,config,false)*100)/100);
	config.Reset = false;
	values->i_d_Ampere = 0.953f;
	variables = uz_FOC_update_PI_ID_Controller_variables(variables, config, values);
	TEST_ASSERT_EQUAL_FLOAT(0.32f,roundf(uz_FOC_PI_Controller(variables,config,false)*100)/100);
}

void test_uz_FOC_PI_Controller_iq_output_Reset(void){
	config.iq_ref_Ampere = 1.0f;
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	uz_FOC_PI_Controller_variables* variables = uz_FOC_PI_IQ_Controller_variables_init(config, values);
	//Compare values with Simulink Simulation
	float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_output[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f};
	for(int i=0;i<11;i++){
		values->i_q_Ampere = values_iq[i];
		variables = uz_FOC_update_PI_IQ_Controller_variables(variables, config, values);
		TEST_ASSERT_EQUAL_FLOAT(values_output[i],roundf(uz_FOC_PI_Controller(variables,config,false)*100)/100);
	}
	config.Reset = true;
	values->i_q_Ampere = 0.956f;
	variables = uz_FOC_update_PI_IQ_Controller_variables(variables, config, values);
	TEST_ASSERT_EQUAL_FLOAT(0.0f,roundf(uz_FOC_PI_Controller(variables,config,false)*100)/100);
	config.Reset = false;
	values->i_q_Ampere = 0.953f;
	variables = uz_FOC_update_PI_IQ_Controller_variables(variables, config, values);
	TEST_ASSERT_EQUAL_FLOAT(0.32f,roundf(uz_FOC_PI_Controller(variables,config,false)*100)/100);
}

void test_uz_FOC_PI_Controller_n_output_Reset(void){
	config.n_ref_rpm = 1000.0f;
	uz_FOC_ActualValues* values = uz_FOC_ActualValues_init();
	uz_FOC_PI_Controller_variables* variables = uz_FOC_PI_N_Controller_variables_init(config, values);
	//Compare values with Simulink Simulation
	float values_omega[36]={0.0f, 0.0f, 0.0167f, 0.063f, 0.153f, 0.296f, 0.498f, 0.756f, 1.06f, 1.4f, 1.76f, 2.12f, 2.46f, 2.77f, 
	3.04f, 3.27f, 3.45f, 3.6f, 3.71f, 3.8f, 3.87f, 3.94f, 4.0f, 4.07f, 4.15f, 4.23f, 4.31f, 4.39f, 4.46f, 4.53f, 4.59f,
	4.64f, 4.67f, 4.7f, 4.72f, 4.73f};
	float values_output[36]={3.62f, 3.62f, 3.62f, 3.62f, 3.62f, 3.62f, 3.62f, 3.61f, 3.61f, 3.61f, 3.61f, 3.60f, 3.60f, 3.60f, 3.60f, 3.59f,
	3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 3.59f, 
	3.59f, 3.59f, 3.59f};
	bool ext_clamping[36]={false, true, true, true, true, false, false, false, false, false, false, false, false, false, false, false
	, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
	, false, false};
	for(int i=0;i<36;i++){
		values->omega_el_rad_per_sec = values_omega[i];
		variables = uz_FOC_update_PI_N_Controller_variables(variables, config, values);
		TEST_ASSERT_EQUAL_FLOAT(values_output[i],roundf(uz_FOC_PI_Controller(variables,config,ext_clamping[i])*100)/100);
	}
	config.Reset = true;
	values->omega_el_rad_per_sec = 4.73f;
	variables = uz_FOC_update_PI_N_Controller_variables(variables, config, values);
	TEST_ASSERT_EQUAL_FLOAT(0.0f,roundf(uz_FOC_PI_Controller(variables,config,false)*100)/100);
	config.Reset = false;
	values->omega_el_rad_per_sec = 4.74f;
	variables = uz_FOC_update_PI_N_Controller_variables(variables, config, values);
	TEST_ASSERT_EQUAL_FLOAT(3.58f,roundf(uz_FOC_PI_Controller(variables,config,false)*100)/100);

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