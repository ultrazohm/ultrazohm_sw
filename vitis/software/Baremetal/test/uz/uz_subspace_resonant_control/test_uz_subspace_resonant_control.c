#ifdef TEST

#include "unity.h"

#include "uz_subspace_resonant_control.h"
#include "uz_resonant_controller.h"
#include "Resonant_Controller.h"
#include "uz_HAL.h"
#include "uz_Transformation.h"


struct uz_subspace_resonant_control_config config = {0}; 


void setUp(void)
{
    config.sampling_time = 0.0001f;
    config.gain_1 = 160.0f;
    config.gain_2 = 160.0f;
    config.harmonic_order = 2.0f;
    config.lower_limit = -2.0f;
    config.upper_limit = 2.0f;
    config.antiwindup_gain = 1.0f; 
}

void tearDown(void)
{
}

void test_uz_subspace_resonant_control_init_and_step(void)
{
    // Test init
    uz_subspace_resonant_control* obj = uz_subspace_resonant_control_init(config);
    uz_assert_not_NULL(obj);

    // Test step dq
    uz_3ph_dq_t ref = {
        .d = 3.0f,
        .q = 3.0f
    };
    uz_3ph_dq_t actual = {
        .d = 2.0f,
        .q = 2.0f
    };
    float omega_el = 10.0f;
    uz_3ph_dq_t out = uz_subspace_resonant_control_step_dq(obj, ref, actual, omega_el);
    TEST_ASSERT_FLOAT_WITHIN(0.01f - 1e-06f, 0.01f + 1e-06f, out.d);
    TEST_ASSERT_FLOAT_WITHIN(0.01f - 1e-06f, 0.01f + 1e-06f, out.q);

    // Reset
    uz_subspace_resonant_control_reset(obj);

    // Test step alpha beta
    uz_3ph_alphabeta_t ref_ab = {
        .alpha = 3.0f,
        .beta = 3.0f
    };
    uz_3ph_alphabeta_t actual_ab = {
        .alpha = 2.0f,
        .beta = 2.0f
    };
    uz_3ph_alphabeta_t out_ab = uz_subspace_resonant_control_step_alphabeta(obj, ref_ab, actual_ab, omega_el);
    TEST_ASSERT_FLOAT_WITHIN(0.01f - 1e-06f, 0.01f + 1e-06f, out_ab.alpha);
    TEST_ASSERT_FLOAT_WITHIN(0.01f - 1e-06f, 0.01f + 1e-06f, out_ab.beta);

    uz_subspace_resonant_control_set_gains(obj, 111.0f, 222.0f);
    struct uz_subspace_resonant_control_config config_out = uz_subspace_resonant_control_get_config(obj);
    TEST_ASSERT_EQUAL_FLOAT(config_out.gain_1, 111.0f);
    TEST_ASSERT_EQUAL_FLOAT(config_out.gain_2, 222.0f);
}


#endif // TEST
