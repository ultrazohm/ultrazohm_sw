#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_pmsm_model3ph_dq.h"
#include "uz_PMSM_config.h"
#include "mock_uz_pmsm_model3ph_dq_hw.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_pmsm_model3ph_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_core_frequency_Hz = IP_FRQ,
    .simulate_mechanical_system = true,
    .switch_pspl = true,
    .pmsm.R_ph_Ohm = 2.1f,
    .pmsm.Ld_Henry = 0.00005f,
    .pmsm.Lq_Henry = 0.00005f,
    .pmsm.Psi_PM_Vs = 0.05f,
    .pmsm.polePairs = 2.0f,
    .pmsm.J_kg_m_squared = 0.001f,
    .pmsm.I_max_Ampere = 10.f,
    .coulomb_friction_constant = 0.01f,
    .friction_coefficient = 0.001f};

void setUp(void)
{
}

void tearDown(void)
{
}

uz_pmsm_model3ph_t *successful_init(struct uz_pmsm_model3ph_config_t configuration);
uz_pmsm_model3ph_t *successful_init(struct uz_pmsm_model3ph_config_t configuration)
{
    // This function is called by tests who require an successful initialized instance
    uz_pmsm_model3ph_hw_write_polepairs_Expect(BASE_ADDRESS, configuration.pmsm.polePairs);
    uz_pmsm_model3ph_hw_write_r_1_Expect(BASE_ADDRESS, configuration.pmsm.R_ph_Ohm);
    uz_pmsm_model3ph_hw_write_psi_pm_Expect(BASE_ADDRESS, configuration.pmsm.Psi_PM_Vs);
    uz_pmsm_model3ph_hw_write_L_d_Expect(BASE_ADDRESS, configuration.pmsm.Ld_Henry);
    uz_pmsm_model3ph_hw_write_L_q_Expect(BASE_ADDRESS, configuration.pmsm.Lq_Henry);
    if (configuration.simulate_mechanical_system)
    {
        uz_pmsm_model3ph_hw_write_friction_coefficient_Expect(BASE_ADDRESS, configuration.friction_coefficient);
        uz_pmsm_model3ph_hw_write_coulomb_friction_constant_Expect(BASE_ADDRESS, configuration.coulomb_friction_constant);
        uz_pmsm_model3ph_hw_write_inertia_Expect(BASE_ADDRESS, configuration.pmsm.J_kg_m_squared);
    }
    else
    {
        // if mechanical part is not simulated, expect the hw write functions to be called with the default values
        uz_pmsm_model3ph_hw_write_friction_coefficient_Expect(BASE_ADDRESS, 1.0f);
        uz_pmsm_model3ph_hw_write_coulomb_friction_constant_Expect(BASE_ADDRESS, 0.0f);
        uz_pmsm_model3ph_hw_write_inertia_Expect(BASE_ADDRESS, 1.0f);
    }
    uz_pmsm_model3ph_hw_write_simulate_mechanical_Expect(BASE_ADDRESS, configuration.simulate_mechanical_system);
    uz_pmsm_model3ph_hw_write_switch_pspl_Expect(BASE_ADDRESS, configuration.switch_pspl);
    uz_pmsm_model3ph_t *instance = uz_pmsm_model3ph_init(configuration);
    return (instance);
}

void test_uz_pmsm_model3ph_successful_init(void)
{
    uz_pmsm_model3ph_t *test_instance = successful_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_pmsm_model3ph_reset_model(void)
{
    uz_pmsm_model3ph_t *test_instance = successful_init(config);

    // write zeros to the model
    uz_pmsm_model3ph_hw_write_v_d_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model3ph_hw_write_v_q_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model3ph_hw_write_omega_mech_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model3ph_hw_write_load_torque_Expect(BASE_ADDRESS,0.0f);
    // force rising edge on inputs strobe
    uz_pmsm_model3ph_hw_trigger_input_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model3ph_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_pmsm_model3ph_hw_write_reset_Expect(BASE_ADDRESS, true);
    uz_pmsm_model3ph_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_pmsm_model3ph_reset(test_instance);
}

void test_read_fb_voltage(void)
{
    uz_pmsm_model3ph_t *test_instance = successful_init(config);
    uz_3ph_dq_t dq_expect = {
        .d = 1.0f,
        .q = 2.0f,
        .zero = 0.0f};
    uz_pmsm_model3ph_hw_trigger_fb_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model3ph_hw_read_v_d_ExpectAndReturn(BASE_ADDRESS, dq_expect.d);
    uz_pmsm_model3ph_hw_read_v_q_ExpectAndReturn(BASE_ADDRESS, dq_expect.q);
    uz_3ph_dq_t out = uz_pmsm_model3ph_dq_get_input_voltages(test_instance);

    TEST_ASSERT_EQUAL_FLOAT(dq_expect.d, out.d);
    TEST_ASSERT_EQUAL_FLOAT(dq_expect.q, out.q);
    TEST_ASSERT_EQUAL_FLOAT(dq_expect.zero, out.zero);
}

void test_uz_pmsm_model3ph_normal_usage(void)
{
    // Note that for the driver and tests it does not make a difference if simulate_mechanical_system is true or false, only the hardware changes!
    config.simulate_mechanical_system = false;
    uz_pmsm_model3ph_t *test_instance = successful_init(config);

    // trigger the strobe to sample new values into AXI shadow registers
    // Furthermore, pass input values from shadow register to inputs by calling strobe 
    uz_pmsm_model3ph_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model3ph_trigger_output_strobe(test_instance);
    uz_pmsm_model3ph_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model3ph_trigger_output_strobe(test_instance);
    
    float i_d_expect = 6.4f;
    float i_q_expect = 1.1f;
    float torque_expect = 4.1f;
    float omega_mech_expect=131.1f;
    float theta_el_expect=4.0f;

    // After strobe register was high, current values can be read from AXI
    uz_pmsm_model3ph_hw_read_i_d_ExpectAndReturn(BASE_ADDRESS, i_d_expect);
    uz_pmsm_model3ph_hw_read_i_q_ExpectAndReturn(BASE_ADDRESS, i_q_expect);
    uz_pmsm_model3ph_hw_read_torque_ExpectAndReturn(BASE_ADDRESS, torque_expect);
    uz_pmsm_model3ph_hw_read_omega_mech_ExpectAndReturn(BASE_ADDRESS,omega_mech_expect);
    uz_pmsm_model3ph_hw_read_theta_el_ExpectAndReturn(BASE_ADDRESS,theta_el_expect);

    struct uz_pmsm_model3ph_outputs_t out = uz_pmsm_model3ph_get_outputs(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(i_d_expect, out.currents.d);
    TEST_ASSERT_EQUAL_FLOAT(i_q_expect, out.currents.q);
    TEST_ASSERT_EQUAL_FLOAT(torque_expect, out.torque_Nm);
    TEST_ASSERT_EQUAL_FLOAT(omega_mech_expect, out.omega_mech_1_s);
    TEST_ASSERT_EQUAL_FLOAT(theta_el_expect, out.theta_el);

    // Based on the new values, something can be calculated, e.g., a controller
    struct uz_pmsm_model3ph_inputs_t inputs = {
        .voltages.d = 100.1f,
        .voltages.q = -300.0f,
        .omega_mech_1_s = 312.123f,
        .load_torque=0.0f};
    // Write new input values to the shadow registers by AXI
    uz_pmsm_model3ph_hw_write_v_d_Expect(BASE_ADDRESS, inputs.voltages.d);
    uz_pmsm_model3ph_hw_write_v_q_Expect(BASE_ADDRESS, inputs.voltages.q);
    uz_pmsm_model3ph_hw_write_omega_mech_Expect(BASE_ADDRESS, inputs.omega_mech_1_s);
    uz_pmsm_model3ph_hw_write_load_torque_Expect(BASE_ADDRESS, inputs.load_torque);
    uz_pmsm_model3ph_set_inputs(test_instance, inputs);

}

#endif // TEST
