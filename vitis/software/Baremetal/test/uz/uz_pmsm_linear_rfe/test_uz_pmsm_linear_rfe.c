#ifdef TEST

#include "unity.h"

#include "uz_pmsm_linear_rfe.h"
#include "../uz_integrator/uz_integrator.h"
#include "../uz_Transformation/uz_Transformation.h"
#include <stdbool.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_pmsm_linear_rfe_ones(void)
{
    float R = 1.0f;
    float L_d = 1.0f;
    float L_q = 1.0f;
    float rfe_d= 1.0f;
    float rfe_q= 1.0f;
     float psi_pm = 0.001f;
    float ts = 1.0f / 10000.0f;
    float omega_el = 0;
    uz_pmsm_linear_rfe_t *pmsm = uz_pmsm_linear_rfe_init(R, psi_pm, L_d, L_q, rfe_d, rfe_q, ts);
    uz_3ph_dq_t v = {
        .d = 1.0f,
        .q = -1.0f};
    uz_3ph_dq_t current = {0};
    for (size_t i = 0; i < 1000000; i++)
    {
        current = uz_pmsm_linear_rfe_step(pmsm, v, omega_el);
    }
    // at standstill, R=1 und v_dq= 1 & -1, the currents must be 1 & -1 in steady state
    TEST_ASSERT_FLOAT_WITHIN(1e-3, 1.0f, current.d);
    TEST_ASSERT_FLOAT_WITHIN(1e-3, -1.0f, current.q);
}

#endif // TEST
