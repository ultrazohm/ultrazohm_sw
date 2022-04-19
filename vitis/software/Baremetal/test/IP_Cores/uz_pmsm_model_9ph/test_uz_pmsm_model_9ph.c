#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_pmsm_model_9ph.h"
#include "mock_uz_pmsm_model_9ph_hw.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_pmsm_model_9ph_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_core_frequency_Hz = IP_FRQ,
    .simulate_mechanical_system = true,
    .switch_pspl = true,
    .control_dq_abc = true,
    .r_1 = 2.1f,
    .L_d = 0.00005f,
    .L_q = 0.00005f,
    .L_o1 = 0.0001f,
    .L_o2 = 0.0002f,
    .L_x1 = 0.0003f,
    .L_y1 = 0.0004f,
    .L_x2 = 0.0005f,
    .L_y2 = 0.0006f,
    .L_zero = 0.0007f,
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

uz_pmsm_model_9ph_t *successful_init(struct uz_pmsm_model_9ph_config_t configuration);
uz_pmsm_model_9ph_t *successful_init(struct uz_pmsm_model_9ph_config_t configuration)
{
    // This function is called by tests who require an successful initialized instance
    uz_pmsm_model_9ph_hw_write_polepairs_Expect(BASE_ADDRESS, configuration.polepairs);
    uz_pmsm_model_9ph_hw_write_r_1_Expect(BASE_ADDRESS, configuration.r_1);
    uz_pmsm_model_9ph_hw_write_psi_pm_Expect(BASE_ADDRESS, configuration.psi_pm);
    uz_pmsm_model_9ph_hw_write_L_d_Expect(BASE_ADDRESS, configuration.L_d);
    uz_pmsm_model_9ph_hw_write_L_q_Expect(BASE_ADDRESS, configuration.L_q);
    uz_pmsm_model_9ph_hw_write_L_o1_Expect(BASE_ADDRESS, configuration.L_o1);
    uz_pmsm_model_9ph_hw_write_L_o2_Expect(BASE_ADDRESS, configuration.L_o2);
    uz_pmsm_model_9ph_hw_write_L_x1_Expect(BASE_ADDRESS, configuration.L_x1);
    uz_pmsm_model_9ph_hw_write_L_y1_Expect(BASE_ADDRESS, configuration.L_y1);
    uz_pmsm_model_9ph_hw_write_L_x2_Expect(BASE_ADDRESS, configuration.L_x2);
    uz_pmsm_model_9ph_hw_write_L_y2_Expect(BASE_ADDRESS, configuration.L_y2);
    uz_pmsm_model_9ph_hw_write_L_zero_Expect(BASE_ADDRESS, configuration.L_zero);
    if (configuration.simulate_mechanical_system)
    {
        uz_pmsm_model_9ph_hw_write_friction_coefficient_Expect(BASE_ADDRESS, configuration.friction_coefficient);
        uz_pmsm_model_9ph_hw_write_coulomb_friction_constant_Expect(BASE_ADDRESS, configuration.coulomb_friction_constant);
        uz_pmsm_model_9ph_hw_write_inertia_Expect(BASE_ADDRESS, configuration.inertia);
    }
    else
    {
        // if mechanical part is not simulated, expect the hw write functions to be called with the default values
        uz_pmsm_model_9ph_hw_write_friction_coefficient_Expect(BASE_ADDRESS, 1.0f);
        uz_pmsm_model_9ph_hw_write_coulomb_friction_constant_Expect(BASE_ADDRESS, 0.0f);
        uz_pmsm_model_9ph_hw_write_inertia_Expect(BASE_ADDRESS, 1.0f);
    }
    uz_pmsm_model_9ph_hw_write_simulate_mechanical_Expect(BASE_ADDRESS, configuration.simulate_mechanical_system);
    uz_pmsm_model_9ph_hw_write_switch_pspl_Expect(BASE_ADDRESS, configuration.switch_pspl);
    uz_pmsm_model_9ph_hw_write_control_dq_abc_Expect(BASE_ADDRESS, configuration.control_dq_abc);
    uz_pmsm_model_9ph_t *instance = uz_pmsm_model_9ph_init(configuration);
    return (instance);
}

void test_uz_pmsm_model_9ph_successful_init(void)
{
    uz_pmsm_model_9ph_t *test_instance = successful_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_pmsm_model_9ph_reset_model(void)
{
    uz_pmsm_model_9ph_t *test_instance = successful_init(config);

    // write zeros to the model
    uz_pmsm_model_9ph_hw_write_omega_mech_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_load_torque_Expect(BASE_ADDRESS, 0.0f);

    uz_pmsm_model_9ph_hw_write_u_d_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_q_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_o1_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_o2_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_x1_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_y1_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_x2_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_y2_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_zero_Expect(BASE_ADDRESS, 0.0f);

    uz_pmsm_model_9ph_hw_write_u_a1_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_b1_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_c1_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_a2_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_b2_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_c2_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_a3_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_b3_Expect(BASE_ADDRESS, 0.0f);
    uz_pmsm_model_9ph_hw_write_u_c3_Expect(BASE_ADDRESS, 0.0f);

    // force rising edge on inputs strobe
    uz_pmsm_model_9ph_hw_trigger_input_general_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model_9ph_hw_trigger_input_voltages_dq_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model_9ph_hw_trigger_input_voltages_abc_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model_9ph_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_pmsm_model_9ph_hw_write_reset_Expect(BASE_ADDRESS, true);
    uz_pmsm_model_9ph_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_pmsm_model_9ph_reset(test_instance);
}

void test_uz_pmsm_model_9ph_normal_usage(void)
{
    // Note that for the driver and tests it does not make a difference if simulate_mechanical_system is true or false, only the hardware changes!
    config.simulate_mechanical_system = false;
    uz_pmsm_model_9ph_t *test_instance = successful_init(config);

    // trigger the strobe to sample new values into AXI shadow registers
    // Furthermore, pass input values from shadow register to inputs by calling strobe 
    uz_pmsm_model_9ph_hw_trigger_output_general_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model_9ph_trigger_output_general_strobe(test_instance);
    uz_pmsm_model_9ph_hw_trigger_output_general_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model_9ph_trigger_output_general_strobe(test_instance);

    uz_pmsm_model_9ph_hw_trigger_output_currents_dq_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model_9ph_trigger_output_currents_dq_strobe(test_instance);
    uz_pmsm_model_9ph_hw_trigger_output_currents_dq_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model_9ph_trigger_output_currents_dq_strobe(test_instance);

    uz_pmsm_model_9ph_hw_trigger_output_currents_abc_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model_9ph_trigger_output_currents_abc_strobe(test_instance);
    uz_pmsm_model_9ph_hw_trigger_output_currents_abc_strobe_Expect(BASE_ADDRESS);
    uz_pmsm_model_9ph_trigger_output_currents_abc_strobe(test_instance);
  
    float i_d_expect = 6.4f;
    float i_q_expect = 1.1f;
    float torque_expect = 4.1f;
    float omega_mech_expect=131.1f;
    float theta_el_expect = 1.9f;

    float i_d_outdq_expect = 2.4f;
    float i_q_outdq_expect = 2.1f;
    float i_o1_expect = 1.2f;
    float i_o2_expect = 1.3f;
    float i_x1_expect = 1.4f;
    float i_y1_expect = 1.5f;
    float i_x2_expect = 1.6f;
    float i_y2_expect = 1.7f;
    float i_zero_expect = 1.8f;

    float i_a1_expect = 5.1f;
    float i_b1_expect = 5.2f;
    float i_c1_expect = 5.3f;
    float i_a2_expect = 5.4f;
    float i_b2_expect = 5.5f;
    float i_c2_expect = 5.6f;
    float i_a3_expect = 5.7f;
    float i_b3_expect = 5.8f;
    float i_c3_expect = 5.9f;
    

    // After strobe register was high, current values can be read from AXI
    uz_pmsm_model_9ph_hw_read_i_d_ExpectAndReturn(BASE_ADDRESS, i_d_expect);
    uz_pmsm_model_9ph_hw_read_i_q_ExpectAndReturn(BASE_ADDRESS, i_q_expect);
    uz_pmsm_model_9ph_hw_read_torque_ExpectAndReturn(BASE_ADDRESS, torque_expect);
    uz_pmsm_model_9ph_hw_read_omega_mech_ExpectAndReturn(BASE_ADDRESS,omega_mech_expect);
    uz_pmsm_model_9ph_hw_read_theta_el_ExpectAndReturn(BASE_ADDRESS,theta_el_expect);

    uz_pmsm_model_9ph_hw_read_i_d_outdq_ExpectAndReturn(BASE_ADDRESS, i_d_outdq_expect);
    uz_pmsm_model_9ph_hw_read_i_q_outdq_ExpectAndReturn(BASE_ADDRESS, i_q_outdq_expect);
    uz_pmsm_model_9ph_hw_read_i_o1_ExpectAndReturn(BASE_ADDRESS, i_o1_expect);
    uz_pmsm_model_9ph_hw_read_i_o2_ExpectAndReturn(BASE_ADDRESS, i_o2_expect);
    uz_pmsm_model_9ph_hw_read_i_x1_ExpectAndReturn(BASE_ADDRESS, i_x1_expect);
    uz_pmsm_model_9ph_hw_read_i_y1_ExpectAndReturn(BASE_ADDRESS, i_y1_expect);
    uz_pmsm_model_9ph_hw_read_i_x2_ExpectAndReturn(BASE_ADDRESS, i_x2_expect);
    uz_pmsm_model_9ph_hw_read_i_y2_ExpectAndReturn(BASE_ADDRESS, i_y2_expect);
    uz_pmsm_model_9ph_hw_read_i_zero_ExpectAndReturn(BASE_ADDRESS, i_zero_expect);

    uz_pmsm_model_9ph_hw_read_i_a1_ExpectAndReturn(BASE_ADDRESS, i_a1_expect);
    uz_pmsm_model_9ph_hw_read_i_b1_ExpectAndReturn(BASE_ADDRESS, i_b1_expect);
    uz_pmsm_model_9ph_hw_read_i_c1_ExpectAndReturn(BASE_ADDRESS, i_c1_expect);
    uz_pmsm_model_9ph_hw_read_i_a2_ExpectAndReturn(BASE_ADDRESS, i_a2_expect);
    uz_pmsm_model_9ph_hw_read_i_b2_ExpectAndReturn(BASE_ADDRESS, i_b2_expect);
    uz_pmsm_model_9ph_hw_read_i_c2_ExpectAndReturn(BASE_ADDRESS, i_c2_expect);
    uz_pmsm_model_9ph_hw_read_i_a3_ExpectAndReturn(BASE_ADDRESS, i_a3_expect);
    uz_pmsm_model_9ph_hw_read_i_b3_ExpectAndReturn(BASE_ADDRESS, i_b3_expect);
    uz_pmsm_model_9ph_hw_read_i_c3_ExpectAndReturn(BASE_ADDRESS, i_c3_expect);
    

    struct uz_pmsm_model_9ph_outputs_general_t out = uz_pmsm_model_9ph_get_outputs_general(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(i_d_expect, out.i_dq.d);
    TEST_ASSERT_EQUAL_FLOAT(i_q_expect, out.i_dq.q);
    TEST_ASSERT_EQUAL_FLOAT(torque_expect, out.torque_Nm);
    TEST_ASSERT_EQUAL_FLOAT(omega_mech_expect,out.omega_mech_1_s);
    TEST_ASSERT_EQUAL_FLOAT(theta_el_expect,out.theta_el);

    struct uz_pmsm_model_9ph_outputs_dq_t out_dq = uz_pmsm_model_9ph_get_outputs_dq(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(i_d_outdq_expect, out_dq.i_dq.d);
    TEST_ASSERT_EQUAL_FLOAT(i_q_outdq_expect, out_dq.i_dq.q);
    TEST_ASSERT_EQUAL_FLOAT(i_o1_expect, out_dq.i_subspaces.z1);
    TEST_ASSERT_EQUAL_FLOAT(i_o2_expect, out_dq.i_subspaces.z2);
    TEST_ASSERT_EQUAL_FLOAT(i_x1_expect, out_dq.i_subspaces.x1);
    TEST_ASSERT_EQUAL_FLOAT(i_y1_expect, out_dq.i_subspaces.y1);
    TEST_ASSERT_EQUAL_FLOAT(i_x2_expect, out_dq.i_subspaces.x2);
    TEST_ASSERT_EQUAL_FLOAT(i_y2_expect, out_dq.i_subspaces.y2);
    TEST_ASSERT_EQUAL_FLOAT(i_zero_expect, out_dq.i_subspaces.z3);

    uz_9ph_abc_t out_abc = uz_pmsm_model_9ph_get_outputs_abc(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(i_a1_expect, out_abc.a1);
    TEST_ASSERT_EQUAL_FLOAT(i_b1_expect, out_abc.b1);
    TEST_ASSERT_EQUAL_FLOAT(i_c1_expect, out_abc.c1);
    TEST_ASSERT_EQUAL_FLOAT(i_a2_expect, out_abc.a2);
    TEST_ASSERT_EQUAL_FLOAT(i_b2_expect, out_abc.b2);
    TEST_ASSERT_EQUAL_FLOAT(i_c2_expect, out_abc.c2);
    TEST_ASSERT_EQUAL_FLOAT(i_a3_expect, out_abc.a3);
    TEST_ASSERT_EQUAL_FLOAT(i_b3_expect, out_abc.b3);
    TEST_ASSERT_EQUAL_FLOAT(i_c3_expect, out_abc.c3);
/*
    // Based on the new values, something can be calculated, e.g., a controller
    struct uz_pmsm_model_9ph_inputs_t inputs = {
        .u_d_V = 100.1f,
        .u_q_V = -300.0f,
        .omega_mech_1_s = 312.123f,
        .load_torque=0.0f,
        .u_o1_V = -3002.0f,
        .u_o2_V = -3003.0f,
        .u_x1_V = -300.4f,
        .u_y1_V = -300.5f,
        .u_x2_V = -300.7f,
        .u_y2_V = -308.0f,
        .u_zero_V = -309.0f};
    // Write new input values to the shadow registers by AXI
    uz_pmsm_model_9ph_hw_write_u_d_Expect(BASE_ADDRESS, inputs.u_d_V);
    uz_pmsm_model_9ph_hw_write_u_q_Expect(BASE_ADDRESS, inputs.u_q_V);
    uz_pmsm_model_9ph_hw_write_omega_mech_Expect(BASE_ADDRESS, inputs.omega_mech_1_s);
    uz_pmsm_model_9ph_hw_write_load_torque_Expect(BASE_ADDRESS,inputs.load_torque);
    uz_pmsm_model_9ph_hw_write_u_o1_Expect(BASE_ADDRESS, inputs.u_o1_V);
    uz_pmsm_model_9ph_hw_write_u_o2_Expect(BASE_ADDRESS, inputs.u_o2_V);
    uz_pmsm_model_9ph_hw_write_u_x1_Expect(BASE_ADDRESS, inputs.u_x1_V);
    uz_pmsm_model_9ph_hw_write_u_y1_Expect(BASE_ADDRESS, inputs.u_y1_V);
    uz_pmsm_model_9ph_hw_write_u_x2_Expect(BASE_ADDRESS, inputs.u_x2_V);
    uz_pmsm_model_9ph_hw_write_u_y2_Expect(BASE_ADDRESS, inputs.u_y2_V);
    uz_pmsm_model_9ph_hw_write_u_zero_Expect(BASE_ADDRESS, inputs.u_zero_V);
    uz_pmsm_model_9ph_set_inputs(test_instance, inputs);
*/
}

#endif // TEST
