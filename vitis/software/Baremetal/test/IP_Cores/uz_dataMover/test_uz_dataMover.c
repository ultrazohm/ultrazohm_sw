#ifdef TEST

#include "unity.h"

#include "uz_dataMover.h"
#include "uz_array.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_DataMover_pointer_address_to_BTCM(void)
{
    uz_array_int16_t test=uz_dataMover_get_data_by_pointer();
    TEST_ASSERT_EQUAL_PTR (0x00020000U, test.data); // just tests that the hard-coded pointer to the BTCM start address is returned
}



#endif // TEST
