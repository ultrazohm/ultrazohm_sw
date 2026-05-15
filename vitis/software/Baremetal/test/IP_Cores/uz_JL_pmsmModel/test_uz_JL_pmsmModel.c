
#ifdef TEST

#include "unity.h"
#include "uz_JL_pmsmModel.h"
#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_JL_pmsmModel_hw.h"
#include "../../../src/IP_Cores/uz_JL_pmsmModel/uz_JL_pmsmModel_hwAdresse.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}

struct uz_JL_pmsmModel_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_core_frequency_Hz = IP_FRQ,
    .r_1 = 2.1f,
    .L_d = 0.00005f,
    .L_q = 0.00005f,
    .psi_pm = 0.05f,
    .mot_p = 2.0f,
    .mot_J = 0.001f,
    };

uz_JL_pmsmModel_t *successful_init(struct uz_JL_pmsmModel_config_t configuration);

uz_JL_pmsmModel_t *successful_init(struct uz_JL_pmsmModel_config_t configuration)
{
    // This function is called by tests who require an successful initialized instance
    uz_JL_pmsmModel_hw_write_R1_Expect(BASE_ADDRESS, configuration.r_1);
    uz_JL_pmsmModel_hw_write_L_d_Expect(BASE_ADDRESS, configuration.L_d);
    uz_JL_pmsmModel_hw_write_L_q_Expect(BASE_ADDRESS, configuration.L_q);
    uz_JL_pmsmModel_hw_write_psi_pm_Expect(BASE_ADDRESS, configuration.psi_pm);
    uz_JL_pmsmModel_hw_write_mot_p_Expect(BASE_ADDRESS, configuration.mot_p);
    uz_JL_pmsmModel_hw_write_mot_J_Expect(BASE_ADDRESS, configuration.mot_J);
    // uz_JL_pmsmModel_hw_write_M_N_Expect(BASE_ADDRESS, configuration.M_N);
    // uz_JL_pmsmModel_hw_write_n_N_Expect(BASE_ADDRESS, configuration.n_N);
    // uz_JL_pmsmModel_hw_write_I_max_Expect(BASE_ADDRESS, configuration.i_max);
    uz_JL_pmsmModel_t *instance = uz_JL_pmsmModel_init(configuration);
    return (instance);
}

void test_uz_JL_pmsmModel_successful_init(void)
{
    uz_JL_pmsmModel_t *test_instance = successful_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_JL_pmsmModel_reset_model(void)
{
    uz_JL_pmsmModel_t *test_instance = successful_init(config);

    // write zeros to the model
    uz_JL_pmsmModel_hw_write_bremse_Expect(BASE_ADDRESS,false);
    uz_JL_pmsmModel_hw_write_Last_J_Expect(BASE_ADDRESS,0.0f);
    uz_JL_pmsmModel_hw_write_Last_M_Expect(BASE_ADDRESS,0.0f);
    uz_JL_pmsmModel_hw_write_switchUabc_dq_Expect(BASE_ADDRESS,false);
    float Udq[2] = {0.0f, 0.0f};
    uz_JL_pmsmModel_hw_write_Udq_Expect(BASE_ADDRESS,Udq);
    // uz_JL_pmsmModel_hw_trigger_input_strobe_Expect(BASE_ADDRESS);
    // force rising edge on inputs strobe
    uz_JL_pmsmModel_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_JL_pmsmModel_hw_write_reset_Expect(BASE_ADDRESS, true);
    uz_JL_pmsmModel_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_JL_pmsmModel_reset(test_instance);
}

void test_uz_JL_pmsmModel_normal_usage(void)
{
    // Note that for the driver and tests it does not make a difference if simulate_mechanical_system is true or false, only the hardware changes!
    uz_JL_pmsmModel_t *test_instance = successful_init(config);

    // trigger the strobe to sample new values into AXI shadow registers
    // Furthermore, pass input values from shadow register to inputs by calling strobe 
    // uz_JL_pmsmModel_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    // uz_JL_pmsmModel_trigger_output_strobe(test_instance);
    // uz_JL_pmsmModel_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    // uz_JL_pmsmModel_trigger_output_strobe(test_instance);
    
    float i_u_expect = 6.4f;
    float i_v_expect = 1.1f;
    float i_w_expect = 1.1f;
    float torque_expect = 4.1f;
    float omega_mech_expect = 131.1f;
    float phi_mech_expect = 0.55f;

    // After strobe register was high, current values can be read from AXI
    uz_JL_pmsmModel_hw_read_I_a_ExpectAndReturn(BASE_ADDRESS, i_u_expect);
    uz_JL_pmsmModel_hw_read_I_b_ExpectAndReturn(BASE_ADDRESS, i_v_expect);
    uz_JL_pmsmModel_hw_read_I_c_ExpectAndReturn(BASE_ADDRESS, i_w_expect);
    uz_JL_pmsmModel_hw_read_torque_ExpectAndReturn(BASE_ADDRESS, torque_expect);
    uz_JL_pmsmModel_hw_read_omega_mech_ExpectAndReturn(BASE_ADDRESS,omega_mech_expect);
    uz_JL_pmsmModel_hw_read_phi_mech_ExpectAndReturn(BASE_ADDRESS,phi_mech_expect);
    

    struct uz_JL_pmsmModel_outputs_t out = uz_JL_pmsmModel_get_outputs(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(i_u_expect, out.i_a_A);
    TEST_ASSERT_EQUAL_FLOAT(i_v_expect, out.i_b_A);
    TEST_ASSERT_EQUAL_FLOAT(i_w_expect, out.i_c_A);
    TEST_ASSERT_EQUAL_FLOAT(torque_expect, out.torque_Nm);
    TEST_ASSERT_EQUAL_FLOAT(omega_mech_expect,out.omega_mech_1_s);
    TEST_ASSERT_EQUAL_FLOAT(phi_mech_expect,out.phi_mech_rad);

    // Based on the new values, something can be calculated, e.g., a controller
    struct uz_JL_pmsmModel_inputs_t inputs = {
        .bremse = true,
        .Last_J = 0.252f,
        .Last_M = 0.5f,
    };
    // Write new input values to the shadow registers by AXI
    uz_JL_pmsmModel_hw_write_bremse_Expect(BASE_ADDRESS, inputs.bremse);
    uz_JL_pmsmModel_hw_write_Last_J_Expect(BASE_ADDRESS, inputs.Last_J);
    uz_JL_pmsmModel_hw_write_Last_M_Expect(BASE_ADDRESS, inputs.Last_M);
    uz_JL_pmsmModel_hw_write_switchUabc_dq_Expect(BASE_ADDRESS,false);
    float Udq[2] = {0.0f, 0.0f};
    uz_JL_pmsmModel_hw_write_Udq_Expect(BASE_ADDRESS,Udq);
    uz_JL_pmsmModel_set_inputs(test_instance, inputs);
}
#endif // TEST
