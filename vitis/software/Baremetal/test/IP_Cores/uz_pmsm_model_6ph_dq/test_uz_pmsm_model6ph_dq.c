#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_pmsm_model6ph_dq.h"
#include "mock_uz_pmsm_model6ph_dq_hw.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_pmsm_model6ph_dq_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_core_frequency_Hz = IP_FRQ,
    .simulate_mechanical_system = true,
    .switch_pspl = true,
    .r_1 = 2.1f,
    .inductance.d = 0.00005f,
    .inductance.q = 0.00005f,
    .inductance.x1 = 0.0001f,
    .inductance.y1 = 0.0002f,
    .inductance.x2 = 0.0003f,
    .inductance.y2 = 0.0004f,
    .inductance.x3 = 0.0005f,
    .inductance.y3 = 0.0006f,
    .inductance.zero = 0.0007f,
    .psi_pm = 0.05f,
    .polepairs = 2.0f,
    .inertia = 0.001f,
    .coulomb_friction_constant = 0.01f,
    .friction_coefficient = 0.001f};

uz_9ph_dq_t ninephase_struct_expect = {
    .d = 1.0f,
    .q = 2.0f,
    .x1 = 3.0f,
    .y1 = 4.0f,
    .x2 = 5.0f,
    .y2 = 6.0f,
    .x3 = 7.0f,
    .y3 = 8.0f,
    .zero = 9.0f};

void setUp(void)
{
}

void tearDown(void)
{
}

uz_pmsm_model6ph_dq_t *successful_init(struct uz_pmsm_model6ph_dq_config_t configuration);
uz_pmsm_model6ph_dq_t *successful_init(struct uz_pmsm_model6ph_dq_config_t configuration)
{
    // This function is called by tests who require an successful initialized instance
    uz_pmsm_model6ph_hw_write_polepairs_Expect(BASE_ADDRESS, configuration.polepairs);
    uz_pmsm_model6ph_hw_write_r_1_Expect(BASE_ADDRESS, configuration.r_1);
    uz_pmsm_model6ph_hw_write_psi_pm_Expect(BASE_ADDRESS, configuration.psi_pm);
    uz_pmsm_model6ph_hw_write_L_d_Expect(BASE_ADDRESS, configuration.inductance.d);
    uz_pmsm_model6ph_hw_write_L_q_Expect(BASE_ADDRESS, configuration.inductance.q);
    uz_pmsm_model6ph_hw_write_L_x1_Expect(BASE_ADDRESS, configuration.inductance.x1);
    uz_pmsm_model6ph_hw_write_L_y1_Expect(BASE_ADDRESS, configuration.inductance.y1);
    uz_pmsm_model6ph_hw_write_L_x2_Expect(BASE_ADDRESS, configuration.inductance.x2);
    uz_pmsm_model6ph_hw_write_L_y2_Expect(BASE_ADDRESS, configuration.inductance.y2);
    uz_pmsm_model6ph_hw_write_L_x3_Expect(BASE_ADDRESS, configuration.inductance.x3);
    uz_pmsm_model6ph_hw_write_L_y3_Expect(BASE_ADDRESS, configuration.inductance.y3);
    uz_pmsm_model6ph_hw_write_L_zero_Expect(BASE_ADDRESS, configuration.inductance.zero);
    if (configuration.simulate_mechanical_system)
    {
        uz_pmsm_model6ph_hw_write_friction_coefficient_Expect(BASE_ADDRESS, configuration.friction_coefficient);
        uz_pmsm_model6ph_hw_write_coulomb_friction_constant_Expect(BASE_ADDRESS, configuration.coulomb_friction_constant);
        uz_pmsm_model6ph_hw_write_inertia_Expect(BASE_ADDRESS, configuration.inertia);
    }
    else
    {
        // if mechanical part is not simulated, expect the hw write functions to be called with the default values
        uz_pmsm_model6ph_hw_write_friction_coefficient_Expect(BASE_ADDRESS, 1.0f);
        uz_pmsm_model6ph_hw_write_coulomb_friction_constant_Expect(BASE_ADDRESS, 0.0f);
        uz_pmsm_model6ph_hw_write_inertia_Expect(BASE_ADDRESS, 1.0f);
    }
    uz_pmsm_model6ph_hw_write_simulate_mechanical_Expect(BASE_ADDRESS, configuration.simulate_mechanical_system);
    uz_pmsm_model6ph_hw_write_switch_pspl_Expect(BASE_ADDRESS, configuration.switch_pspl);
    uz_pmsm_model6ph_dq_t *instance = uz_pmsm_model6ph_dq_init(configuration);
    return (instance);
}

void test_uz_pmsm_model_9ph_successful_init(void)
{
    uz_pmsm_model6ph_dq_t *test_instance = successful_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

// Testing uz_pmsm_model6ph_dq_reset and uz_pmsm_model6ph_dq_set_use_axi_input
void test_uz_pmsm_model6ph_dq_reset(void){
    uz_pmsm_model6ph_dq_t *test_instance = successful_init(config);

    // pspl: true -> voltages will be set to zero

    uz_pmsm_model6ph_hw_write_omega_mech_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_inputs_general
    uz_pmsm_model6ph_hw_write_load_torque_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_inputs_general

    uz_pmsm_model6ph_hw_write_u_d_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_voltage
    uz_pmsm_model6ph_hw_write_u_q_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_voltage
    uz_pmsm_model6ph_hw_write_u_x1_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_voltage
    uz_pmsm_model6ph_hw_write_u_y1_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_voltage
    uz_pmsm_model6ph_hw_write_u_x2_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_voltage
    uz_pmsm_model6ph_hw_write_u_y2_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_voltage
    uz_pmsm_model6ph_hw_write_u_x3_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_voltage
    uz_pmsm_model6ph_hw_write_u_y3_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_voltage
    uz_pmsm_model6ph_hw_write_u_zero_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_voltage
    uz_pmsm_model6ph_trigger_voltage_input_strobe_hw_Expect(BASE_ADDRESS); // from uz_pmsm_model6ph_dq_set_voltage
    
    uz_pmsm_model6ph_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_pmsm_model6ph_hw_write_reset_Expect(BASE_ADDRESS, true);
    uz_pmsm_model6ph_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_pmsm_model6ph_dq_reset(test_instance);

    // set pspl false
    uz_pmsm_model6ph_hw_write_switch_pspl_Expect(BASE_ADDRESS, false);
    uz_pmsm_model6ph_dq_set_use_axi_input(test_instance,false);

    // pspl: false -> voltages will not be set to zero

    uz_pmsm_model6ph_hw_write_omega_mech_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_inputs_general
    uz_pmsm_model6ph_hw_write_load_torque_Expect(BASE_ADDRESS, 0.0f); // from uz_pmsm_model6ph_dq_set_inputs_general

    uz_pmsm_model6ph_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_pmsm_model6ph_hw_write_reset_Expect(BASE_ADDRESS, true);
    uz_pmsm_model6ph_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_pmsm_model6ph_dq_reset(test_instance);

    // set pspl true
    uz_pmsm_model6ph_hw_write_switch_pspl_Expect(BASE_ADDRESS, true);
    uz_pmsm_model6ph_dq_set_use_axi_input(test_instance,true);
}

// Testing uz_pmsm_model6ph_dq_set_inputs_general and uz_pmsm_model6ph_dq_set_voltage
void test_set_inputs(void){
    uz_pmsm_model6ph_dq_t *test_instance = successful_init(config);

    // Test uz_pmsm_model6ph_dq_set_inputs_general
    float omega_expect = 4.4f;
    float torque_expect = 5.5f;
    uz_pmsm_model6ph_hw_write_omega_mech_Expect(BASE_ADDRESS, omega_expect);
    uz_pmsm_model6ph_hw_write_load_torque_Expect(BASE_ADDRESS, torque_expect);
    uz_pmsm_model6ph_dq_set_inputs_general(test_instance,omega_expect,torque_expect);

    // Test uz_pmsm_model6ph_dq_set_voltage
    uz_pmsm_model6ph_hw_write_u_d_Expect(BASE_ADDRESS, ninephase_struct_expect.d); 
    uz_pmsm_model6ph_hw_write_u_q_Expect(BASE_ADDRESS, ninephase_struct_expect.q); 
    uz_pmsm_model6ph_hw_write_u_x1_Expect(BASE_ADDRESS, ninephase_struct_expect.x1);
    uz_pmsm_model6ph_hw_write_u_y1_Expect(BASE_ADDRESS, ninephase_struct_expect.y1);
    uz_pmsm_model6ph_hw_write_u_x2_Expect(BASE_ADDRESS, ninephase_struct_expect.x2);
    uz_pmsm_model6ph_hw_write_u_y2_Expect(BASE_ADDRESS, ninephase_struct_expect.y2);
    uz_pmsm_model6ph_hw_write_u_x3_Expect(BASE_ADDRESS, ninephase_struct_expect.x3);
    uz_pmsm_model6ph_hw_write_u_y3_Expect(BASE_ADDRESS, ninephase_struct_expect.y3);
    uz_pmsm_model6ph_hw_write_u_zero_Expect(BASE_ADDRESS, ninephase_struct_expect.zero);
    uz_pmsm_model6ph_trigger_voltage_input_strobe_hw_Expect(BASE_ADDRESS);
    uz_pmsm_model6ph_dq_set_voltage(test_instance,ninephase_struct_expect);
}

// Testing uz_pmsm_model6ph_dq_get_outputs_general, uz_pmsm_model6ph_dq_get_output_currents and uz_pmsm_model6ph_dq_get_input_voltages
void test_get_outputs(void){
    uz_pmsm_model6ph_dq_t *test_instance = successful_init(config);

    // Test uz_pmsm_model6ph_dq_get_outputs_general
    struct uz_pmsm_model6ph_dq_outputs_general_t outputs_expect = {
        .torque = 7.7f,
        .omega_mech = 8.8f,
        .theta_el = 9.9f};
    uz_pmsm_model6ph_hw_read_torque_ExpectAndReturn(BASE_ADDRESS,outputs_expect.torque);
    uz_pmsm_model6ph_hw_read_omega_mech_ExpectAndReturn(BASE_ADDRESS,outputs_expect.omega_mech);
    uz_pmsm_model6ph_hw_read_theta_el_ExpectAndReturn(BASE_ADDRESS,outputs_expect.theta_el);
    struct uz_pmsm_model6ph_dq_outputs_general_t out = uz_pmsm_model6ph_dq_get_outputs_general(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(out.torque,outputs_expect.torque);
    TEST_ASSERT_EQUAL_FLOAT(out.omega_mech,outputs_expect.omega_mech);
    TEST_ASSERT_EQUAL_FLOAT(out.theta_el,outputs_expect.theta_el);

    // Test uz_pmsm_model6ph_dq_get_output_currents
    uz_pmsm_model6ph_trigger_current_output_strobe_hw_Expect(BASE_ADDRESS);
    uz_pmsm_model6ph_hw_read_i_d_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.d);
    uz_pmsm_model6ph_hw_read_i_q_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.q);
    uz_pmsm_model6ph_hw_read_i_x1_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.x1);
    uz_pmsm_model6ph_hw_read_i_y1_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.y1);
    uz_pmsm_model6ph_hw_read_i_x2_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.x2);
    uz_pmsm_model6ph_hw_read_i_y2_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.y2);
    uz_pmsm_model6ph_hw_read_i_x3_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.x3);
    uz_pmsm_model6ph_hw_read_i_y3_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.y3);
    uz_pmsm_model6ph_hw_read_i_zero_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.zero);
    uz_9ph_dq_t out_ninephase = uz_pmsm_model6ph_dq_get_output_currents(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.d,ninephase_struct_expect.d);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.q,ninephase_struct_expect.q);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.x1,ninephase_struct_expect.x1);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.y1,ninephase_struct_expect.y1);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.x2,ninephase_struct_expect.x2);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.y2,ninephase_struct_expect.y2);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.x3,ninephase_struct_expect.x3);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.y3,ninephase_struct_expect.y3);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.zero,ninephase_struct_expect.zero);

    // Test uz_pmsm_model6ph_dq_get_input_voltages
    uz_pmsm_model6ph_trigger_voltage_output_strobe_hw_Expect(BASE_ADDRESS);
    uz_pmsm_model6ph_hw_read_u_d_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.d);
    uz_pmsm_model6ph_hw_read_u_q_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.q);
    uz_pmsm_model6ph_hw_read_u_x1_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.x1);
    uz_pmsm_model6ph_hw_read_u_y1_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.y1);
    uz_pmsm_model6ph_hw_read_u_x2_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.x2);
    uz_pmsm_model6ph_hw_read_u_y2_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.y2);
    uz_pmsm_model6ph_hw_read_u_x3_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.x3);
    uz_pmsm_model6ph_hw_read_u_y3_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.y3);
    uz_pmsm_model6ph_hw_read_u_zero_ExpectAndReturn(BASE_ADDRESS,ninephase_struct_expect.zero);
    out_ninephase = uz_pmsm_model6ph_dq_get_input_voltages(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.d,ninephase_struct_expect.d);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.q,ninephase_struct_expect.q);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.x1,ninephase_struct_expect.x1);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.y1,ninephase_struct_expect.y1);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.x2,ninephase_struct_expect.x2);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.y2,ninephase_struct_expect.y2);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.x3,ninephase_struct_expect.x3);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.y3,ninephase_struct_expect.y3);
    TEST_ASSERT_EQUAL_FLOAT(out_ninephase.zero,ninephase_struct_expect.zero);
}


#endif // TEST
