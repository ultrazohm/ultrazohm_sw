
#ifdef TEST

#include "unity.h"
#include "mock_uz_AXI.h"
#include "test_assert_with_exception.h"
#include "uz_JL_pmsmModel_hwAdresse.h"
#include "uz_JL_pmsmModel_hw.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address
#define IP_FRQ 1000000000U;

void setUp(void)
{
}

void tearDown(void)
{
}


void test_uz_JL_pmsmModel_hw_write_R1(void)
{
    float mot_R1=1.0f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+r1_Data_uz_JL_pmsmModel,mot_R1);
    uz_JL_pmsmModel_hw_write_R1(TEST_BASE_ADDRESS, mot_R1);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_R1_without_baseaddress(void)
{
    float mot_R1=1.0f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_R1(0u,mot_R1));
}

void test_uz_JL_pmsmModel_hw_write_psi_pm(void)
{
    float psi_pm=3.2f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+psi_pm_Data_uz_JL_pmsmModel,psi_pm);
    uz_JL_pmsmModel_hw_write_psi_pm(TEST_BASE_ADDRESS, psi_pm);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_psi_pm_without_baseaddress(void)
{
    float psi_pm=3.2f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_psi_pm(0u, psi_pm));
}

void test_uz_JL_pmsmModel_hw_write_L_d(void)
{
    float L_d=3.2f;
    float rec_L_d = 1/(L_d);
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Ld_Data_uz_JL_pmsmModel,L_d);
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+rec_mot_Ld_Data_uz_JL_pmsmModel,rec_L_d);
    uz_JL_pmsmModel_hw_write_L_d(TEST_BASE_ADDRESS, L_d);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_L_d_without_baseaddress(void)
{
    float L_d=3.2f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_L_d(0u, L_d));
}

void test_uz_JL_pmsmModel_hw_write_L_q(void)
{
    float L_q=3.2f;
    float rec_L_q = 1/(L_q);
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Lq_Data_uz_JL_pmsmModel,L_q);
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+rec_mot_Lq_Data_uz_JL_pmsmModel,rec_L_q);
    uz_JL_pmsmModel_hw_write_L_q(TEST_BASE_ADDRESS, L_q);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_L_q_without_baseaddress(void)
{
    float L_q=3.2f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_L_q(0u, L_q));
}

void test_uz_JL_pmsmModel_hw_write_mot_p(void)
{
    float mot_p=3.2f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+polpaare_Data_uz_JL_pmsmModel,mot_p);
    uz_JL_pmsmModel_hw_write_mot_p(TEST_BASE_ADDRESS, mot_p);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_mot_p_without_baseaddress(void)
{
    float mot_p=3.2f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_mot_p(0u, mot_p));
}

void test_uz_JL_pmsmModel_hw_write_mot_J(void)
{
    float mot_J=3.2f;
    float rec_J = 1/mot_J;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+mot_J_Data_uz_JL_pmsmModel,rec_J);
    uz_JL_pmsmModel_hw_write_mot_J(TEST_BASE_ADDRESS, mot_J);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_mot_J_without_baseaddress(void)
{
    float mot_J=3.2f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_mot_J(0u, mot_J));
}

// void test_uz_JL_pmsmModel_hw_write_n_N(void)
// {
//     float n_N=3.2f;
//     uz_axi_write_float_Expect(TEST_BASE_ADDRESS+PMSM_config_mot_n_N_Data_uz_JL_pmsmModel,n_N);
//     uz_JL_pmsmModel_hw_write_n_N(TEST_BASE_ADDRESS, n_N);
// }

// void test_uz_JL_pmsmModel_hw_fail_assert_write_n_N_without_baseaddress(void)
// {
//     float n_N=3.2f;
//     uz_axi_write_float_Ignore();
//     TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_n_N(0u, n_N));
// }

// void test_uz_JL_pmsmModel_hw_write_M_N(void)
// {
//     float M_N=3.2f;
//     uz_axi_write_float_Expect(TEST_BASE_ADDRESS+PMSM_config_mot_M_N_Data_uz_JL_pmsmModel,M_N);
//     uz_JL_pmsmModel_hw_write_M_N(TEST_BASE_ADDRESS, M_N);
// }

// void test_uz_JL_pmsmModel_hw_fail_assert_write_M_N_without_baseaddress(void)
// {
//     float M_N=3.2f;
//     uz_axi_write_float_Ignore();
//     TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_M_N(0u, M_N));
// }

// void test_uz_JL_pmsmModel_hw_write_I_max(void)
// {
//     float I_max=3.2f;
//     uz_axi_write_float_Expect(TEST_BASE_ADDRESS+PMSM_config_mot_I_max_Data_uz_JL_pmsmModel,I_max);
//     uz_JL_pmsmModel_hw_write_I_max(TEST_BASE_ADDRESS, I_max);
// }

// void test_uz_JL_pmsmModel_hw_fail_assert_write_I_max_without_baseaddress(void)
// {
//     float I_max=3.2f;
//     uz_axi_write_float_Ignore();
//     TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_I_max(0u, I_max));
// }

void test_uz_JL_pmsmModel_hw_write_Last_J(void)
{
    float Last_J=3.2f;
    float rec_J = 1/Last_J;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Last_J_Data_uz_JL_pmsmModel,rec_J);
    uz_JL_pmsmModel_hw_write_Last_J(TEST_BASE_ADDRESS, Last_J);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_Last_J_without_baseaddress(void)
{
    float Last_J=3.2f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_Last_J(0u, Last_J));
}

void test_uz_JL_pmsmModel_hw_write_Last_M(void)
{
    float Last_M=3.2f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Last_M_Data_uz_JL_pmsmModel,Last_M);
    uz_JL_pmsmModel_hw_write_Last_M(TEST_BASE_ADDRESS, Last_M);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_Last_M_without_baseaddress(void)
{
    float Last_M=3.2f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_Last_M(0u, Last_M));
}

void test_uz_JL_pmsmModel_hw_write_bremse(void)
{
    bool bremse=true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+Bremse_Data_uz_JL_pmsmModel,bremse);
    uz_JL_pmsmModel_hw_write_bremse(TEST_BASE_ADDRESS, bremse);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_bremse_without_baseaddress(void)
{
    bool bremse=true;
    uz_axi_write_bool_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_bremse(0u, bremse));
}

void test_uz_JL_pmsmModel_hw_write_Coulomb_Reibung(void)
{
    float Coulomb_Reibung=0.01f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Coulomb_Reibung_Data_uz_JL_pmsmModel, Coulomb_Reibung);
    uz_JL_pmsmModel_hw_write_Coulomb_Reibung(TEST_BASE_ADDRESS, Coulomb_Reibung);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_Coulomb_Reibung_without_baseaddress(void)
{
    float Coulomb_Reibung=0.01f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_Coulomb_Reibung(0u, Coulomb_Reibung));
}

void test_uz_JL_pmsmModel_hw_write_Reibungskoeffizient(void)
{
    float reibungskoeffizient=0.001f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Reibungskoeffizient_Data_uz_JL_pmsmModel,reibungskoeffizient);
    uz_JL_pmsmModel_hw_write_Reibungskoeffizient(TEST_BASE_ADDRESS, reibungskoeffizient);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_Reibungkoeffizient_without_baseaddress(void)
{
    float reibungskoeffizient=0.001f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_Reibungskoeffizient(0u, reibungskoeffizient));
}

void test_uz_JL_pmsmModel_hw_write_switchUabc_dq(void)
{
    bool switchUabc_dq=true;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+switchUabc_dq_Data_uz_JL_pmsmModel,switchUabc_dq);
    uz_JL_pmsmModel_hw_write_switchUabc_dq(TEST_BASE_ADDRESS, switchUabc_dq);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_switchUabc_dq_without_baseaddress(void)
{
    bool switchUabc_dq=true;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_switchUabc_dq(0u, switchUabc_dq));
}

void test_uz_JL_pmsmModel_hw_write_Udq(void)
{
    float Udq[2]= {1.2f, 3.5f};
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Ud_Data_uz_JL_pmsmModel,Udq[0]);
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Uq_Data_uz_JL_pmsmModel,Udq[1]);
    uz_JL_pmsmModel_hw_write_Udq(TEST_BASE_ADDRESS, Udq);
}

void test_uz_JL_pmsmModel_hw_fail_assert_write_Udq_without_baseaddress(void)
{
    float Udq[2]= {1.2f, 3.5f};
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_pmsmModel_hw_write_Udq(0u, Udq));
}

void test_uz_JL_pmsmModel_hw_read_omega_mech(void)
{
    float omega_mech_expect=4.2f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS+omega_mech_Data_uz_JL_pmsmModel,omega_mech_expect);
    float omega_mech_read=uz_JL_pmsmModel_hw_read_omega_mech(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(omega_mech_expect,omega_mech_read);
}

void test_uz_JL_pmsmModel_hw_read_phi_mech(void)
{
    float phi_mech_expect=4.2f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS+phi_mech_Data_uz_JL_pmsmModel,phi_mech_expect);
    float phi_mech_read=uz_JL_pmsmModel_hw_read_phi_mech(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(phi_mech_expect,phi_mech_read);
}

void test_uz_JL_pmsmModel_hw_read_torque(void)
{
    float torque_expect=4.2f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS+pmsm_M_Mot_Data_uz_JL_pmsmModel,torque_expect);
    float torque_read=uz_JL_pmsmModel_hw_read_torque(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(torque_expect,torque_read);
}

void test_uz_JL_pmsmModel_hw_read_I_a(void)
{
    float I_u_expect=4.2f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS+pmsm_Iu_Data_uz_JL_pmsmModel,I_u_expect);
    float I_u_read=uz_JL_pmsmModel_hw_read_I_a(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(I_u_expect,I_u_read);
}

void test_uz_JL_pmsmModel_hw_read_I_b(void)
{
    float I_v_expect=4.2f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS+pmsm_Iv_Data_uz_JL_pmsmModel,I_v_expect);
    float I_v_read=uz_JL_pmsmModel_hw_read_I_b(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(I_v_expect,I_v_read);
}

void test_uz_JL_pmsmModel_hw_read_I_c(void)
{
    float I_w_expect=4.2f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS+pmsm_Iw_Data_uz_JL_pmsmModel,I_w_expect);
    float I_w_read=uz_JL_pmsmModel_hw_read_I_c(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(I_w_expect,I_w_read);
}

// void test_uz_JL_pmsmModel_hw_trigger_input_strobe(void){
//     uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+Udq_Strobe_uz_JL_pmsmModel,true);
//     uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+Udq_Strobe_uz_JL_pmsmModel,false);
//     uz_JL_pmsmModel_hw_trigger_input_strobe(TEST_BASE_ADDRESS);
// }

void test_uz_JL_pmsmModel_hw_trigger_output_strobe(void){
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+pmsm_out_Strobe_uz_JL_pmsmModel,true);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+pmsm_out_Strobe_uz_JL_pmsmModel,false);
    uz_JL_pmsmModel_hw_trigger_output_strobe(TEST_BASE_ADDRESS);
}

#endif // TEST
