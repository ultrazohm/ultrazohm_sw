#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"

#include "../uz_global_configuration.h"
#include "../uz_parameterid_rc/uz_parameterid_rc.h"

struct uz_parameterid_rc_config_t test_config = {0};

void setUp(void)
{
    test_config.id_ref = 1.0f;
    test_config.iq_ref = 1.0f;
}

void tearDown(void)
{
}

void test_uz_parameterid_rs_init_pointer_not_null(void)
{
    uz_parameterid_rc_t* test_instance = uz_parameterid_rc_init(test_config);
    TEST_ASSERT_NOT_NULL(test_instance);
}


#endif // TEST
