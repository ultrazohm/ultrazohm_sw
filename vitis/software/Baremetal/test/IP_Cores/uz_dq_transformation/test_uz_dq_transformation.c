#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include <stdint.h>
#define TEST_BASE_ADDRESS 0x000BADBAD
#define TEST_IP_CORE_FRQ 100000000U
#include "uz_dq_transformation.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_dq_transformation_test_init(void)
{
   uz_dq_transformation_t* test_instance = uz_dq_transformation_init();
}

#endif // TEST
