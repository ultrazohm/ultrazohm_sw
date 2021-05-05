#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "staticAllocator.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_staticAllocator_NeedToImplement(void)
{
    //TEST_IGNORE_MESSAGE("Need to Implement staticAllocator");
    allocator* ptr=allocator_init(10);
    allocator* ptr2=allocator_init(100);
    TEST_ASSERT_FAIL_ASSERT(allocator* ptr3=allocator_init(-100));
    TEST_ASSERT_EQUAL(10,allocator_get_base_addres(ptr));
    TEST_ASSERT_EQUAL(100,allocator_get_base_addres(ptr2));
}

#endif // TEST
