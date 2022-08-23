#ifdef TEST

#include "unity.h"

#include "uz_delay_compensation_fcs_mpc_6phase_pmsm.h"
#include "test_assert_with_exception.h"
#include "mock_uz_delay_compensation_fcs_mpc_6phase_pmsm_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "../../uz/uz_Transformation/uz_Transformation.h"

static struct uz_delay_compensation_fcs_mpc_6phase_config_t config={
    .base_address= TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
    .psiPM = 1.3f,
    .Ld = 2.3f,
    .Rs = 2.2f,
    .SampleTime = 0.01f,
    .pole_pairs = 4.0f,
    .Lx = 1.1f,
    .Ly = 0.3f,
    .use_AXI =1   
};

static struct uz_delay_compensation_fcs_mpc_6phase_AXI_values_t AXI_values={
    .last_applied_optimal_voltage_ud = 6.3f, 
    .last_applied_optimal_voltage_uq = 5.3f,
    .last_applied_optimal_voltage_ux = 4.3f,
    .last_applied_optimal_voltage_uy = 3.3f,
    .id_measured = 1.2f,
    .iq_measured = 2.2f,
    .ix_measured = 3.2f,
    .iy_measured = 4.2f,
    .omega_m_measured = 1.1f
};



void setUp(void)
{
   config.base_address = TEST_BASE_ADDRESS;
   config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;
   config.psiPM = 1.3f;
   config.Ld = 2.3f;
   config.Rs = 2.2f;
   config.SampleTime = 0.01f;
   config.pole_pairs = 4.0f;
   config.Lx = 1.1f;
   config.Ly = 0.3f;
   config.use_AXI = 1;

   AXI_values.last_applied_optimal_voltage_ud = 6.3f;
   AXI_values.last_applied_optimal_voltage_uq = 5.3f;
   AXI_values.last_applied_optimal_voltage_ux = 4.3f;
   AXI_values.last_applied_optimal_voltage_uy = 3.3f;
   AXI_values.id_measured = 1.2f;
   AXI_values.iq_measured = 2.2f;
   AXI_values.ix_measured = 3.2f;
   AXI_values.iy_measured = 4.2f;
   AXI_values.omega_m_measured = 1.1f;
   
}

void tearDown(void)
{
}

void test_uz_delay_compensation_fcs_mpc_6phase_init_test(void)
{
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Lq_Expect(config.base_address, config.Lq);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Ld_Expect(config.base_address, config.Ld);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Rs_Expect(config.base_address, config.Rs);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_use_AXI_Expect(config.base_address, config.use_AXI);
    uz_delay_compensation_fcs_mpc_6phase_init(config);
}

void test_uz_delay_compensation_fcs_mpc_6phase_set_AXI_values_test(void)
{
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Lq_Expect(config.base_address, config.Lq);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Ld_Expect(config.base_address, config.Ld);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Rs_Expect(config.base_address, config.Rs);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_use_AXI_Expect(config.base_address, config.use_AXI);
    
    uz_delay_compensation_fcs_mpc_6phase_t* test_instance = uz_delay_compensation_fcs_mpc_6phase_init(config);

    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_ud_Expect(config.base_address, AXI_values.last_applied_optimal_voltage_ud);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_uq_Expect(config.base_address, AXI_values.last_applied_optimal_voltage_uq);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_ux_Expect(config.base_address, AXI_values.last_applied_optimal_voltage_ux);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_uy_Expect(config.base_address, AXI_values.last_applied_optimal_voltage_uy);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_id_measured_Expect(config.base_address, AXI_values.id_measured);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_iq_measured_Expect(config.base_address, AXI_values.iq_measured);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_ix_measured_Expect(config.base_address, AXI_values.ix_measured);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_iy_measured_Expect(config.base_address, AXI_values.iy_measured);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_omega_m_measured_Expect(config.base_address, AXI_values.omega_m_measured);

    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_AXI_values(test_instance, AXI_values );
}

void test_uz_delay_compensation_fcs_mpc_6phase_pmsm_read_idk1_iqK1_ixk1_iyk1_test(void)
{
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_psiPM_Expect(config.base_address, config.psiPM);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Lq_Expect(config.base_address, config.Lq);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Ld_Expect(config.base_address, config.Ld);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Rs_Expect(config.base_address, config.Rs);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Ld_Expect(config.base_address, config.SampleTime, config.Ld);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Lq_Expect(config.base_address, config.SampleTime, config.Lq);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Lx_Expect(config.base_address, config.SampleTime, config.Lx);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Ly_Expect(config.base_address, config.SampleTime, config.Ly);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_use_AXI_Expect(config.base_address, config.use_AXI);
    
    uz_delay_compensation_fcs_mpc_6phase_t* test_instance = uz_delay_compensation_fcs_mpc_6phase_init(config);

    float idk1_expected = 2.2f;
    uz_delay_compensation_fcs_mpc_6phase_pmsm_get_id_k_1_ExpectAndReturn(config.base_address, idk1_expected);

    float iqk1_expectet = 3.3f;
    uz_delay_compensation_fcs_mpc_6phase_pmsm_get_iq_k_1_ExpectAndReturn(config.base_address, iqk1_expectet);

    float ixk1_expected = 1.3f;
    uz_delay_compensation_fcs_mpc_6phase_pmsm_get_ix_k_1_ExpectAndReturn(config.base_address, ixk1_expected);

    float iyk1_expected = 0.6f;
    uz_delay_compensation_fcs_mpc_6phase_pmsm_get_iy_k_1_ExpectAndReturn(config.base_address, iyk1_expected);

    struct uz_6ph_idk1_iqk1_ixk1_iyk1_t currents = uz_delay_compensation_fcs_mpc_6phase_pmsm_read_idk1_iqK1_ixk1_iyk1(test_instance);

   TEST_ASSERT_EQUAL_FLOAT(currents.id_k_1, idk1_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.iq_k_1, iqk1_expectet);
   TEST_ASSERT_EQUAL_FLOAT(currents.ix_k_1, ixk1_expected);
   TEST_ASSERT_EQUAL_FLOAT(currents.iy_k_1, iyk1_expected);
}

void test_uz_delay_compensation_fcs_mpc_6phase_pmsm_read_idk1_iqK1_ixk1_iyk1_pointer(void)
{
    uz_delay_compensation_fcs_mpc_6phase_t* testpointer = NULL;
    TEST_ASSERT_FAIL_ASSERT(uz_delay_compensation_fcs_mpc_6phase_pmsm_read_idk1_iqK1_ixk1_iyk1(testpointer));
}

#endif // TEST
