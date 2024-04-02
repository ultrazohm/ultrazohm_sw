#ifdef TEST

#include "unity.h"
#include "uz_flux_prediction.h"
#include "../../../src/uz/uz_flux_prediction/flux_prediction_ert_rtw/flux_prediction.h"
#include "../uz_global_configuration.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "test_assert_with_exception.h"

uz_PMSM_t config = {0};
uz_3ph_dq_t i_actual_Ampere = {0};
uz_3ph_dq_t flux = {0};
uz_3ph_dq_t u_k0 = {0};
uz_3ph_dq_t u_k1 = {0};
float omega_el = 0.0f;
float ts_regler = 0.0f;

void setUp(void)
{
    config.R_ph_Ohm = 0.3f;
    i_actual_Ampere.d = -3.0f;
    i_actual_Ampere.q = 3.0f;
    flux.d = 0.02;
    flux.q = 0.015;
    u_k0.d = 5.0f;
    u_k0.q = 1.0f;
    u_k1.d = 4.0f;
    u_k1.q = 4.0f;
    omega_el = 500.0f;
    ts_regler = 5e-5;
}


void test_uz_flux_prediction_step(void)
{
    uz_flux_prediction_t* test_instance = uz_flux_prediction_init(config,  ts_regler, omega_el);
    uz_3ph_dq_t flux_prediction_output = uz_flux_prediction_step(test_instance, i_actual_Ampere, u_k0, u_k1, flux);
    TEST_ASSERT_FLOAT_WITHIN(1e-04f,0.0146f,flux_prediction_output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-05f,0.02018f,flux_prediction_output.d);
}

#endif // TEST
