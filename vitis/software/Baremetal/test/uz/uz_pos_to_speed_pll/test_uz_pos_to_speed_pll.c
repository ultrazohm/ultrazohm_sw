#ifdef TEST

#include "unity.h"

#include "uz_pos_to_speed_pll.h"
#include "uz_codegen_pos_to_speed_pll_ert_rtw/uz_codegen_pos_to_speed_pll.h"
#include "test_assert_with_exception.h"

#define FLOAT_TOLERANCE 1e-3f

struct uz_pos_to_speed_pll_config_t config = {
    .machine_polepairs = 2.0f,
    .kp_pll = 628.3185f,
    .ki_pll = 98696.0f,
    .sampling_time_in_seconds = 0.0001f
};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_pos_to_speed_pll_initialize(void)
{
    uz_pos_to_speed_pll_init(config);
}

void test_uz_pos_to_speed_pll_set_config_assertions(void)
{
    uz_pos_to_speed_pll_t* test_instance = uz_pos_to_speed_pll_init(config);

    config.machine_polepairs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_pos_to_speed_pll_set_config(test_instance, config));
    config.machine_polepairs = 2.0f;
    config.kp_pll = -42.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_pos_to_speed_pll_set_config(test_instance, config));
    config.kp_pll = 628.3185f;
    config.ki_pll = -42.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_pos_to_speed_pll_set_config(test_instance, config));
    config.ki_pll = 98696.0f;
    config.sampling_time_in_seconds = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_pos_to_speed_pll_set_config(test_instance, config));
    config.sampling_time_in_seconds = 0.0001f;
}

void test_uz_pos_to_speed_pll_get_functions_argument_null(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_pos_to_speed_pll_get_omega_mech_si(NULL));
    TEST_ASSERT_FAIL_ASSERT(uz_pos_to_speed_pll_get_omega_el_si(NULL));
}

void test_uz_pos_to_speed_pll_step_test(void)
{
    uz_pos_to_speed_pll_t* test_instance = uz_pos_to_speed_pll_init(config);

    float position_mech_SI_input = 0.0f;
    float output_omega_mech = 0.0f;
    float output_omega_el = 0.0f;
    // step 1
    uz_pos_to_speed_pll_step(test_instance, position_mech_SI_input);
    output_omega_mech = uz_pos_to_speed_pll_get_omega_mech_si(test_instance);
    output_omega_el = uz_pos_to_speed_pll_get_omega_el_si(test_instance);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 0.0f, output_omega_mech);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 0.0f, output_omega_el);
    // step 2
    position_mech_SI_input = 3.142e-2f;
    uz_pos_to_speed_pll_step(test_instance, position_mech_SI_input);
    output_omega_mech = uz_pos_to_speed_pll_get_omega_mech_si(test_instance);
    output_omega_el = uz_pos_to_speed_pll_get_omega_el_si(test_instance);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 0.0f, output_omega_mech);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 0.0f, output_omega_el);
    // step 3
    position_mech_SI_input = 6.283e-2f;
    uz_pos_to_speed_pll_step(test_instance, position_mech_SI_input);
    output_omega_mech = uz_pos_to_speed_pll_get_omega_mech_si(test_instance);
    output_omega_el = uz_pos_to_speed_pll_get_omega_el_si(test_instance);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 3.1e-1f, output_omega_mech);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 6.2e-1f, output_omega_el);

    // step 4
    position_mech_SI_input = 9.425e-2f;
    uz_pos_to_speed_pll_step(test_instance, position_mech_SI_input);
    output_omega_mech = uz_pos_to_speed_pll_get_omega_mech_si(test_instance);
    output_omega_el = uz_pos_to_speed_pll_get_omega_el_si(test_instance);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 9.103e-1f, output_omega_mech);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 1.821f, output_omega_el);    

    // step 5
    position_mech_SI_input = 1.257e-1f;
    uz_pos_to_speed_pll_step(test_instance, position_mech_SI_input);
    output_omega_mech = uz_pos_to_speed_pll_get_omega_mech_si(test_instance);
    output_omega_el = uz_pos_to_speed_pll_get_omega_el_si(test_instance);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 1.782f, output_omega_mech);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 3.564f, output_omega_el);     
}
#endif // TEST