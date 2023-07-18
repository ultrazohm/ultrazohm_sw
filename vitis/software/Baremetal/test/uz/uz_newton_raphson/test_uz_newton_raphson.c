#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include <stddef.h>
#include <stdint.h>
#include "uz_array.h"
#include "uz_newton_raphson.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_newton_raphson_derivate_assert_length(void) {
    float coefficients[5] = {1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    float derivate_poly_coefficients[3] = {1.0f, 2.0f, 3.0f};
    struct uz_newton_raphson_config config = {
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
    };
    TEST_ASSERT_FAIL_ASSERT(uz_newton_raphson_derivate(config));
}

void test_uz_newton_raphson_derivate_4th(void) {
    float coefficients[5] = {1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    float derivate_poly_coefficients[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    struct uz_newton_raphson_config config = {
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
    };
    float expected_coefficients[4] = {1.0f, 0.0f, 0.0f, 4.0f};
    uz_newton_raphson_derivate(config);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_coefficients, config.derivate_poly_coefficients.data, UZ_ARRAY_SIZE(expected_coefficients));
}

void test_uz_newton_raphson_derivate_8th(void) {
    float coefficients[9] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    float derivate_poly_coefficients[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    struct uz_newton_raphson_config config = {
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
    };
    float expected_coefficients[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    uz_newton_raphson_derivate(config);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_coefficients, config.derivate_poly_coefficients.data, UZ_ARRAY_SIZE(expected_coefficients));
}

void test_uz_newton_raphson_derivate_8th_negative_polys(void) {
    float coefficients[9] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f};
    float derivate_poly_coefficients[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    struct uz_newton_raphson_config config = {
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
    };
    float expected_coefficients[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    uz_newton_raphson_derivate(config);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_coefficients, config.derivate_poly_coefficients.data, UZ_ARRAY_SIZE(expected_coefficients));
}

void test_uz_newton_raphson_derivate_8th_random_polys(void) {
    float coefficients[9] = {-1.235f, -0.0005f, 66.0f, -89.99f, -1.5f, -0.01f, 1.34f, 1.56f, -1.65f};
    float derivate_poly_coefficients[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    struct uz_newton_raphson_config config = {
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
    };
    float expected_coefficients[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    uz_newton_raphson_derivate(config);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_coefficients, config.derivate_poly_coefficients.data, UZ_ARRAY_SIZE(expected_coefficients));
}

void test_uz_newton_raphson_assert_max_length_poly(void) {
    //Max allowed polynom length = 20th order ->array has max 21 values
    float coefficients[22] = {0};
    struct uz_newton_raphson_config config = {
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
    };
    TEST_ASSERT_FAIL_ASSERT(uz_newton_raphson(config));
}

void test_uz_newton_raphson_assert_length_poly_derivate(void) {
    //Length of the derivate array must be 1 smaller than poly-array, otherwise assertion
    float derivate_poly_coefficients[7] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float coefficients[9] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f};
    struct uz_newton_raphson_config config = {
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
    };
    TEST_ASSERT_FAIL_ASSERT(uz_newton_raphson(config));
}

void test_uz_newton_raphson_assert_length_poly_coefficients(void) {
    //Length of the coefficients-array must be same length as the poly-array, otherwise assertion
    float derivate_poly_coefficients[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float coefficients[8] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f};
    struct uz_newton_raphson_config config = {
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
    };
    TEST_ASSERT_FAIL_ASSERT(uz_newton_raphson(config));
}

void test_uz_newton_raphson_4th_order_result_separate_coefficients(void) {
    // x^4 + 0*x^3 + 0*x^2+1.64965986e+03f*x^1 - -1.417233563e+04f
    float derivate_poly_coefficients[4] = {1.0f, 1.0f, 0.0f, 4.0f};
    float coefficients[5] = {-1.417233563e+04f, 1.64965986e+03f, 0.0f, 0.0f, 1.0f};
    struct uz_newton_raphson_config config = {
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .initial_value = 8.59106f,
        .iterations = 5U,
        .root_absolute_tolerance=0.05f
    };
    float output = uz_newton_raphson(config);
    TEST_ASSERT_EQUAL_FLOAT(7.073508f, output);
}

void test_uz_newton_raphson_10th_order_positive_result(void) {
    //Test result for: x^10 - x^8 + 8x^6 - 24*x^4 + 32*x^2 - 48
    // https://www.wolframalpha.com/input?i=x%5E10+-+x%5E8+%2B+8x%5E6+-+24*x%5E4+%2B+32*x%5E2+-+48
    // Roots are +/- sqrt(2)
    float derivate_poly_coefficients[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,};
    float coefficients[11] = {-48.0f, 0.0f, 32.0f, 0.0f, -24.0f, 0.0f, 8.0f, 0.0f, -1.0f, 0.0f, 1.0f};
    struct uz_newton_raphson_config config = {
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .initial_value = 5.0f,
        .iterations = 15U,
        .root_absolute_tolerance=0.05f
    };
    uz_newton_raphson_derivate(config);
    float output = uz_newton_raphson(config);
    TEST_ASSERT_EQUAL_FLOAT(1.4142135f, output);//Solution is sqrt(2)
}

void test_uz_newton_raphson_10th_order_negative_result(void) {
    //Test result for: x^10 - x^8 + 8x^6 - 24*x^4 + 32*x^2 - 48
    // https://www.wolframalpha.com/input?i=x%5E10+-+x%5E8+%2B+8x%5E6+-+24*x%5E4+%2B+32*x%5E2+-+48
    // Roots are +/- sqrt(2)
    float derivate_poly_coefficients[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,};
    float coefficients[11] = {-48.0f, 0.0f, 32.0f, 0.0f, -24.0f, 0.0f, 8.0f, 0.0f, -1.0f, 0.0f, 1.0f};
    struct uz_newton_raphson_config config = {
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .initial_value = -5.0f,
        .iterations = 15U,
        .root_absolute_tolerance=0.05f
    };
    uz_newton_raphson_derivate(config);
    float output = uz_newton_raphson(config);
    TEST_ASSERT_EQUAL_FLOAT(- 1.4142135f, output);//Solution is sqrt(2)
}
#endif // TEST
