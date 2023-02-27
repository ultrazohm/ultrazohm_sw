#ifdef TEST

#include "unity.h"

#include "uz_complex.h"
#include "../../uz_HAL.h"

void setUp(void)
{
}

void tearDown(void)
{
}

uz_complex_cartesian_t test_arg1 = 
{
    .real = 4.0f,
    .imag = -3.0f
};
uz_complex_cartesian_t test_arg2 = 
{
    .real = -1.0f,
    .imag = 2.0f
};

uz_complex_polar_t test_exp = 
{
    .abs = 3.0f,
    .angle = -8.0f
};

void test_uz_complex_multiplication(void)
{
    uz_complex_cartesian_t result = uz_complex_multiplication(test_arg1, test_arg2);
    TEST_ASSERT_EQUAL_FLOAT(2.0f,result.real);
    TEST_ASSERT_EQUAL_FLOAT(11.0f,result.imag);
}

void test_uz_complex_addition(void)
{
    uz_complex_cartesian_t result = uz_complex_addition(test_arg1, test_arg2);
    TEST_ASSERT_EQUAL_FLOAT(3.0f,result.real);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f,result.imag);
}

void test_uz_complex_subtraction(void)
{
    uz_complex_cartesian_t result = uz_complex_subtraction(test_arg1, test_arg2);
    TEST_ASSERT_EQUAL_FLOAT(5.0f,result.real);
    TEST_ASSERT_EQUAL_FLOAT(-5.0f,result.imag);
}

void test_uz_complex_division(void)
{
    uz_complex_cartesian_t result = uz_complex_division(test_arg1, test_arg2);
    TEST_ASSERT_EQUAL_FLOAT(-2.0f,result.real);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f,result.imag);
}

void test_uz_complex_cartesian_to_polar(void)
{
    uz_complex_polar_t result = uz_complex_cartesian_to_polar(test_arg1);
    TEST_ASSERT_EQUAL_FLOAT(5.0f,result.abs);
    TEST_ASSERT_EQUAL_FLOAT(-0.6435f,result.angle);
}

void test_uz_complex_polar_to_cartesian(void)
{
    uz_complex_cartesian_t result = uz_complex_polar_to_cartesian(test_exp);
    TEST_ASSERT_EQUAL_FLOAT(-0.436500f,result.real);
    TEST_ASSERT_EQUAL_FLOAT(-2.968075f,result.imag);
}

#endif // TEST
