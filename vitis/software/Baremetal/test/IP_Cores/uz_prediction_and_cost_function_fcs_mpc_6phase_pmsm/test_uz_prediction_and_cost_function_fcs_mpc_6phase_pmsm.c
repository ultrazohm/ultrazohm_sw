#ifdef TEST

#include "unity.h"
#include "uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm.h"
#include "test_assert_with_exception.h"
#include "mock_uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "../../uz/uz_Transformation/uz_Transformation.h"

static struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_config_t config={
    .base_address = TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
    .psiPM = 1.3f,
    .Lq = 0.3f,
    .Ld = 2.3f,
    .Rs = 2.2f,
    .SampleTime = 0.01f,
    .pole_pairs = 4.0f,
    .Lx = 1.1f,
    .Ly = 0.3f,
    .id_ref = 0.0f,
    .iq_ref = 10.0f,
    .ix_ref = 0.1f,
    .iy_ref = 0.3f,
    .use_AXI = 1
}; 

 static struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_AXI_values_t AXI_values={
    .d_voltage_per_switching_state_AXI = 6.3f, 
    .q_voltage_per_switching_state_AXI = 5.3f,
    .x_voltage_per_switching_state_AXI = 4.3f,
    .y_voltage_per_switching_state_AXI = 3.3f,
    .id_k_1_AXI = 1.2f,
    .iq_k_1_AXI = 2.2f,
    .ix_k_1_AXI = 3.2f,
    .iy_k_1_AXI = 4.2f,
    .omega_m_measured_AXI = 1.1f
 };


void setUp(void)
{
    config.base_address = TEST_BASE_ADDRESS;
    config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;
    config.psiPM = 1.3f;
    config.Lq = 0.3f;
    config.Ld = 2.3f;
    config.Rs = 2.2f;
    config.SampleTime = 0.01f;
    config.pole_pairs = 4.0f;
    config.Lx = 1.1f;
    config.Ly = 0.3f;
    config.id_ref = 0.0f;
    config.iq_ref = 10.0f;
    config.ix_ref = 0.1f;
    config.iy_ref = 0.3f;
    config.use_AXI = 1;

    AXI_values.d_voltage_per_switching_state_AXI = 6.3f; 
    AXI_values.q_voltage_per_switching_state_AXI = 5.3f;
    AXI_values.x_voltage_per_switching_state_AXI = 4.3f;
    AXI_values.y_voltage_per_switching_state_AXI = 3.3f;
    AXI_values.id_k_1_AXI = 1.2f;
    AXI_values.iq_k_1_AXI = 2.2f;
    AXI_values.ix_k_1_AXI = 3.2f;
    AXI_values.iy_k_1_AXI = 4.2f;
    AXI_values.omega_m_measured_AXI = 1.1f;
}

void tearDown(void)
{
}

void test_uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_init_test(void)
{
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Lq_Expect(config.base_address, config.Lq);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Ld_Expect(config.base_address, config.Ld);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Rs_Expect(config.base_address, config.Rs);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_id_ref_Expect(config.base_address, config.id_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iq_ref_Expect(config.base_address, config.iq_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_ix_ref_Expect(config.base_address, config.ix_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iy_ref_Expect(config.base_address, config.iy_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_use_AXI_Expect(config.base_address, config.use_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_init(config);
}

void test_uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_set_AXI_values_test(void)
{
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Lq_Expect(config.base_address, config.Lq);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Ld_Expect(config.base_address, config.Ld);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Rs_Expect(config.base_address, config.Rs);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_id_ref_Expect(config.base_address, config.id_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iq_ref_Expect(config.base_address, config.iq_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_ix_ref_Expect(config.base_address, config.ix_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iy_ref_Expect(config.base_address, config.iy_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_use_AXI_Expect(config.base_address, config.use_AXI);
    
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* test_instance = uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_init(config);

    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_id_k_1_AXI_Expect(config.base_address, AXI_values.id_k_1_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iq_k_1_AXI_Expect(config.base_address, AXI_values.iq_k_1_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_ix_k_1_AXI_Expect(config.base_address, AXI_values.ix_k_1_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iy_k_1_AXI_Expect(config.base_address, AXI_values.iy_k_1_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_omega_m_measured_AXI_Expect(config.base_address, AXI_values.omega_m_measured_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_d_voltage_per_switching_state_AXI_Expect(config.base_address, AXI_values.d_voltage_per_switching_state_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_q_voltage_per_switching_state_AXI_Expect(config.base_address, AXI_values.q_voltage_per_switching_state_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_x_voltage_per_switching_state_AXI_Expect(config.base_address, AXI_values.x_voltage_per_switching_state_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_y_voltage_per_switching_state_AXI_Expect(config.base_address, AXI_values.y_voltage_per_switching_state_AXI);

    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_set_AXI_values(test_instance, AXI_values);
}

void test_uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_get_J_AXI_test(void)
{
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Lq_Expect(config.base_address, config.Lq);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Ld_Expect(config.base_address, config.Ld);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Rs_Expect(config.base_address, config.Rs);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_id_ref_Expect(config.base_address, config.id_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iq_ref_Expect(config.base_address, config.iq_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_ix_ref_Expect(config.base_address, config.ix_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iy_ref_Expect(config.base_address, config.iy_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_use_AXI_Expect(config.base_address, config.use_AXI);
    
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* test_instance = uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_init(config);

    float J_AXI_expected = 2.2f;
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_get_J_AXI_ExpectAndReturn(config.base_address, J_AXI_expected);

    float J_AXI = uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_get_J_AXI(test_instance);

   TEST_ASSERT_EQUAL_FLOAT(J_AXI, J_AXI_expected);
}

void test_uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_get_J_AXI_test_pointer(void)
{
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* testpointer = NULL;
    TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_get_J_AXI(testpointer));
}

#endif // TEST
