#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_pmsmModel.h"
#include "mock_uz_pmsmModel_hw.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_pmsmModel_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_core_frequency_Hz = IP_FRQ,
    .simulate_mechanical_system = true,
    .r_1 = 2.1f,
    .L_d = 0.00005f,
    .L_q = 0.00005f,
    .psi_pm = 0.05f,
    .polepairs = 2.0f,
    .inertia = 0.001f,
    .coulomb_friction_constant = 0.01f,
    .friction_coefficient = 0.001f};

void setUp(void)
{
}

void tearDown(void)
{
}

uz_pmsmModel_t *successful_init(struct uz_pmsmModel_config_t configuration);
uz_pmsmModel_t *successful_init(struct uz_pmsmModel_config_t configuration)
{
    // This function is called by tests who require an successful initialized instance
    uz_pmsmModel_hw_write_polepairs_Expect(BASE_ADDRESS, configuration.polepairs);
    uz_pmsmModel_hw_write_r_1_Expect(BASE_ADDRESS, configuration.r_1);
    uz_pmsmModel_hw_write_psi_pm_Expect(BASE_ADDRESS, configuration.psi_pm);
    uz_pmsmModel_hw_write_L_d_Expect(BASE_ADDRESS, configuration.L_d);
    uz_pmsmModel_hw_write_L_q_Expect(BASE_ADDRESS, configuration.L_q);
    if (configuration.simulate_mechanical_system)
    {
        uz_pmsmModel_hw_write_friction_coefficient_Expect(BASE_ADDRESS, configuration.friction_coefficient);
        uz_pmsmModel_hw_write_coulomb_friction_constant_Expect(BASE_ADDRESS, configuration.coulomb_friction_constant);
        uz_pmsmModel_hw_write_inertia_Expect(BASE_ADDRESS, configuration.inertia);
    }
    else
    {
        // if mechanical part is not simulated, expect the hw write functions to be called with the default values
        uz_pmsmModel_hw_write_friction_coefficient_Expect(BASE_ADDRESS, 1.0f);
        uz_pmsmModel_hw_write_coulomb_friction_constant_Expect(BASE_ADDRESS, 0.0f);
        uz_pmsmModel_hw_write_inertia_Expect(BASE_ADDRESS, 1.0f);
    }
    uz_pmsmModel_hw_write_simulate_mechanical_Expect(BASE_ADDRESS, configuration.simulate_mechanical_system);
    uz_pmsmModel_t *instance = uz_pmsmModel_init(configuration);
    return (instance);
}

void test_uz_pmsmModel_successful_init(void)
{
    uz_pmsmModel_t *test_instance = successful_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_pmsmModel_reset_model(void)
{
    uz_pmsmModel_t *test_instance = successful_init(config);

    uz_pmsmModel_hw_write_u_d_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsmModel_hw_write_u_q_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsmModel_hw_write_load_torque_Expect(BASE_ADDRESS,0.0f);
    uz_pmsmModel_hw_write_omega_mech_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsmModel_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_pmsmModel_hw_write_reset_Expect(BASE_ADDRESS, true);
    uz_pmsmModel_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_pmsmModel_reset(test_instance);
}

void test_uz_pmsmModel_struct_api_usage_without_mechanical(void)
{
    // Note that for the driver and tests it does not make a difference if simulate_mechanical_system is true or false, only the hardware changes!
    config.simulate_mechanical_system = false;
    uz_pmsmModel_t *test_instance = successful_init(config);

    struct uz_pmsmModel_inputs_t inputs = {
        .u_d_V = 100.1f,
        .u_q_V = -300.0f,
        .omega_mech_1_s = 312.123f,
        .load_torque=0.0f};

    uz_pmsmModel_hw_write_u_d_Expect(BASE_ADDRESS, inputs.u_d_V);
    uz_pmsmModel_hw_write_u_q_Expect(BASE_ADDRESS, inputs.u_q_V);
    uz_pmsmModel_hw_write_load_torque_Expect(BASE_ADDRESS,inputs.load_torque);
    uz_pmsmModel_hw_write_omega_mech_Expect(BASE_ADDRESS, inputs.omega_mech_1_s);
    uz_pmsmModel_set_inputs(test_instance, inputs);

    float i_d_expect = 6.4f;
    float i_q_expect = 1.1f;
    float torque_expect = 4.1f;
    float omega_mech_expect=131.1f;
    uz_pmsmModel_hw_read_i_d_ExpectAndReturn(BASE_ADDRESS, i_d_expect);
    uz_pmsmModel_hw_read_i_q_ExpectAndReturn(BASE_ADDRESS, i_q_expect);
    uz_pmsmModel_hw_read_torque_ExpectAndReturn(BASE_ADDRESS, torque_expect);
    uz_pmsmModel_hw_read_omega_mech_ExpectAndReturn(BASE_ADDRESS,omega_mech_expect);

    struct uz_pmsmModel_outputs_t out = uz_pmsmModel_get_outputs(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(i_d_expect, out.i_d_A);
    TEST_ASSERT_EQUAL_FLOAT(i_q_expect, out.i_q_A);
    TEST_ASSERT_EQUAL_FLOAT(torque_expect, out.torque_Nm);
    TEST_ASSERT_EQUAL_FLOAT(omega_mech_expect,out.omega_mech_1_s);
}

#endif // TEST
