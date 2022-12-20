#ifdef TEST

#include "unity.h"

#include "uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM.h"
#include "test_assert_with_exception.h"
#include "mock_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "../../uz/uz_Transformation/uz_Transformation.h"

static struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_config_t config={
    .base_address= TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
    .use_AXI =1   
};

static struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_AXI_values_t AXI_values={
    .J_in_AXI = 35.3f,
    .Index_in_AXI = 23, 
    .d_phase_voltage_per_switchimng_state_AXI = 22.4f,
    .q_phase_voltage_per_switchimng_state_AXI = 33.2f,
    .x_phase_voltage_per_switchimng_state_AXI = 56.0f,
    .y_phase_voltage_per_switchimng_state_AXI = 43.7f,
    .valid_in_AXI = 1
};

void setUp(void)
{
    config.base_address = TEST_BASE_ADDRESS;
    config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;
    config.use_AXI = 1;

    AXI_values.J_in_AXI = 35.3f;
    AXI_values.Index_in_AXI = 23; 
    AXI_values.d_phase_voltage_per_switchimng_state_AXI = 22.4f;
    AXI_values.q_phase_voltage_per_switchimng_state_AXI = 33.2f;
    AXI_values.x_phase_voltage_per_switchimng_state_AXI = 56.0f;
    AXI_values.y_phase_voltage_per_switchimng_state_AXI = 43.7f;
    AXI_values.valid_in_AXI = 1;
}

void tearDown(void)
{
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_init_test(void)
{
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI_Expect(config.base_address, config.use_AXI);

    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_init(config);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_set_AXI_values_test(void)
{
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI_Expect(config.base_address, config.use_AXI);
    
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* test_instance = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_init(config);

    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_J_in_AXI_Expect(config.base_address, AXI_values.J_in_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_Index_in_AXI_Expect(config.base_address, AXI_values.Index_in_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_d_phase_voltage_per_switchimng_state_AXI_Expect(config.base_address, AXI_values.d_phase_voltage_per_switchimng_state_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_q_phase_voltage_per_switchimng_state_AXI_Expect(config.base_address, AXI_values.q_phase_voltage_per_switchimng_state_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_x_phase_voltage_per_switchimng_state_AXI_Expect(config.base_address, AXI_values.x_phase_voltage_per_switchimng_state_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_y_phase_voltage_per_switchimng_state_AXI_Expect(config.base_address, AXI_values.y_phase_voltage_per_switchimng_state_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_valid_in_AXI_Expect(config.base_address, AXI_values.valid_in_AXI);

    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_set_AXI_values(test_instance, AXI_values);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_last_applied_optimal_voltage_d_q_x_y_test(void)
{
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI_Expect(config.base_address, config.use_AXI);
    
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* test_instance = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_init(config);



    float ud_expected = 2.2f;
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_ud_AXI_ExpectAndReturn(config.base_address, ud_expected);

    float uq_expectet = 3.3f;
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_uq_AXI_ExpectAndReturn(config.base_address, uq_expectet);

    float ux_expected = 1.3f;
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_ux_AXI_ExpectAndReturn(config.base_address, ux_expected);

    float uy_expected = 0.6f;
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_uy_AXI_ExpectAndReturn(config.base_address, uy_expected);

    struct uz_6ph_optimal_dvoltage_qvoltage_xvoltage_yvoltage_t voltage = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_last_applied_optimal_voltage_d_q_x_y(test_instance);

   TEST_ASSERT_EQUAL_FLOAT(voltage.d, ud_expected);
   TEST_ASSERT_EQUAL_FLOAT(voltage.q, uq_expectet);
   TEST_ASSERT_EQUAL_FLOAT(voltage.x, ux_expected);
   TEST_ASSERT_EQUAL_FLOAT(voltage.y, uy_expected);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_last_applied_optimal_voltage_d_q_x_y_pointer(void)
{
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* testpointer = NULL;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_last_applied_optimal_voltage_d_q_x_y(testpointer));
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_done_complete_AXI_test(void)
{
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI_Expect(config.base_address, config.use_AXI);
    
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* test_instance = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_init(config);

    _Bool done_complete_expected = 0;
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_done_complete_AXI_ExpectAndReturn(config.base_address, done_complete_expected);

    _Bool done_complete = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_done_complete_AXI(test_instance);

   TEST_ASSERT_EQUAL_FLOAT(done_complete, done_complete_expected);
  }

  void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_done_complete_AXI_pointer(void)
{
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* testpointer = NULL;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_done_complete_AXI(testpointer));
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_Index_out_test(void)
{
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI_Expect(config.base_address, config.use_AXI);
    
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* test_instance = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_init(config);

    int32_t Index_out_expected = 34;
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_Index_out_AXI_ExpectAndReturn(config.base_address, Index_out_expected);

    int32_t Index_out = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_Index_out(test_instance);

   TEST_ASSERT_EQUAL_FLOAT(Index_out, Index_out_expected);
  }

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_Index_out_test_pointer(void)
{
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* testpointer = NULL;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_Index_out(testpointer));
}

#endif // TEST
