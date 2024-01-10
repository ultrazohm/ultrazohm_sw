#ifdef TEST

#include "unity.h"

#include "uz_parameterid_rs.h"

struct uz_parameterid_rs_config_t config = {0};

void setUp(void)
{
    config.omega_start = 1.0f;
    config.omega_end = 100.0f;
    config.omega_increment = 10.0f;
}

void tearDown(void)
{
}

void test_uz_parameterid_rs_init_pointer_not_null(void)
{
    uz_parameterid_rs_t *test_instance = uz_parameterid_rs_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_parameterid_rs_init_equal(void)
{
    uz_parameterid_rs_t *test_instance = uz_parameterid_rs_init(config);
    struct uz_parameterid_rs_config_t actual_configuration = uz_parameterid_rs_get_current_config(test_instance);
    float actual_omega_start =actual_configuration.omega_start;
   TEST_ASSERT_EQUAL_FLOAT(config.omega_start, actual_omega_start);
}

#endif // TEST
