#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include <stdint.h>
#define TEST_BASE_ADDRESS 0x000BADBAD
#define TEST_IP_CORE_FRQ 100000000U
#include "uz_fcs_mpc_3phase_spmsm.h"
#include "mock_uz_fcs_mpc_3phase_spmsm_hw.h"

static struct uz_fcs_mpc_3phase_spmsm_config_t config={
   .base_address= TEST_BASE_ADDRESS,
   .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
   .u_dc_link = 1.5f,
   .SampleTime=100.8f,
   .Rs=0.4f,
   .Ld=0.00003f,
   .Lq=0.00005f,
   .psiPM=0.007f,
   .pole_pairs=4.0f
};

void setUp(void)
{
    config.base_address= TEST_BASE_ADDRESS;
    config.ip_clk_frequency_Hz=TEST_IP_CORE_FRQ;
    config.u_dc_link = 1.5f;
    config.SampleTime=100.8f;
    config.Rs=0.4f;
    config.Ld=0.00003f;
    config.Lq=0.00005f;
    config.psiPM=0.007f;
    config.pole_pairs=4.0f;
}

void tearDown(void)
{
}

void test_uz_fcs_mpc_3phase_spmsm_init_test(void)
{
   uz_fcs_mpc_3phase_spmsm_hw_set_u_dc_link_Expect(config.base_address, config.u_dc_link);
   uz_fcs_mpc_3phase_spmsm_hw_set_SampleTime_Expect(config.base_address, config.SampleTime);
   uz_fcs_mpc_3phase_spmsm_hw_set_Rs_Expect(config.base_address, config.Rs);
   uz_fcs_mpc_3phase_spmsm_hw_set_reciprocal_Ls_Expect(config.base_address, config.Ld, config.Lq);
   uz_fcs_mpc_3phase_spmsm_hw_set_psiPM_Expect(config.base_address, config.psiPM);
   uz_fcs_mpc_3phase_spmsm_hw_set_pole_pairs_Expect(config.base_address, config.pole_pairs);
   uz_fcs_mpc_3phase_spmsm_init(config);
}

#endif // TEST
