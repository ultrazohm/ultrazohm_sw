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
    float poly_coefficients[5] = {1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    float derivate_poly_coefficients[3] = {1.0f, 2.0f, 3.0f};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .use_separate_coefficients = true,
    };
    TEST_ASSERT_FAIL_ASSERT(uz_newton_raphson_derivate(config.poly_coefficients, config.derivate_poly_coefficients));
}

void test_uz_newton_raphson_derivate_4th(void) {
    float poly_coefficients[5] = {1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    float derivate_poly_coefficients[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
    };
    float expected_coefficients[4] = {1.0f, 0.0f, 0.0f, 4.0f};
    uz_newton_raphson_derivate(config.poly_coefficients, config.derivate_poly_coefficients);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_coefficients, config.derivate_poly_coefficients.data, UZ_ARRAY_SIZE(expected_coefficients));
}

void test_uz_newton_raphson_derivate_8th(void) {
    float poly_coefficients[9] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    float derivate_poly_coefficients[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
    };
    float expected_coefficients[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    uz_newton_raphson_derivate(config.poly_coefficients, config.derivate_poly_coefficients);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_coefficients, config.derivate_poly_coefficients.data, UZ_ARRAY_SIZE(expected_coefficients));
}

void test_uz_newton_raphson_derivate_8th_negative_polys(void) {
    float poly_coefficients[9] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f};
    float derivate_poly_coefficients[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float coefficients[5] = {5.0f, 1.0f, 2.5f, 2.5f, 3.33f};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
    };
    float expected_coefficients[8] = {-1.0f, 2.0f, -3.0f, -4.0f, -5.0f, 6.0f, 7.0f, -8.0f};
    uz_newton_raphson_derivate(config.poly_coefficients, config.derivate_poly_coefficients);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_coefficients, config.derivate_poly_coefficients.data, UZ_ARRAY_SIZE(expected_coefficients));
}

void test_uz_newton_raphson_derivate_8th_random_polys(void) {
    float poly_coefficients[9] = {-1.235f, -0.0005f, 66.0f, -89.99f, -1.5f, -0.01f, 1.34f, 1.56f, -1.65f};
    float derivate_poly_coefficients[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float coefficients[5] = {5.0f, 1.0f, 2.5f, 2.5f, 3.33f};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
    };
    float expected_coefficients[8] = {-0.0005f, 132.0f, -269.97f, -6.0f, -0.05f, 8.04f, 10.92f, -13.2f};
    uz_newton_raphson_derivate(config.poly_coefficients, config.derivate_poly_coefficients);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_coefficients, config.derivate_poly_coefficients.data, UZ_ARRAY_SIZE(expected_coefficients));
}

void test_uz_newton_raphson_assert_max_length_poly(void) {
    //Max allowed polynom length = 20th order ->array has max 21 values
    float poly_coefficients[22] = {0};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
    };
    TEST_ASSERT_FAIL_ASSERT(uz_newton_raphson(config));
}

void test_uz_newton_raphson_assert_length_poly_derivate(void) {
    //Length of the derivate array must be 1 smaller than poly-array, otherwise assertion
    float poly_coefficients[9] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f};
    float derivate_poly_coefficients[7] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float coefficients[9] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .use_separate_coefficients = true,
    };
    TEST_ASSERT_FAIL_ASSERT(uz_newton_raphson(config));
}

void test_uz_newton_raphson_assert_length_poly_coefficients(void) {
    //Length of the coefficients-array must be same length as the poly-array, otherwise assertion
    float poly_coefficients[9] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f};
    float derivate_poly_coefficients[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float coefficients[8] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .use_separate_coefficients = true,
    };
    TEST_ASSERT_FAIL_ASSERT(uz_newton_raphson(config));
}

void test_uz_newton_raphson_assert_length_poly_coefficients_pass(void) {
    //Length of the coefficients-array must be same length as the poly-array, otherwise assertion
    float poly_coefficients[9] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f};
    float derivate_poly_coefficients[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float coefficients[8] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .use_separate_coefficients = false,
    };
    //Since the separate coefficients array is not used, the assertion should not trigger
    TEST_ASSERT_PASS_ASSERT(uz_newton_raphson(config));
}

void test_uz_newton_raphson_4th_order_result_no_separate_coefficients(void) {
    float poly_coefficients[5] = {-1.417233563e+04f, 1.64965986e+03f, 0.0f, 0.0f, 1.0f};
    float derivate_poly_coefficients[4] = {2.0f, 1.0f, 0.0f, 4.0f};
    float coefficients[5] = {-1.417233563e+04f, 1.64965986e+03f, 0.0f, 0.0f, 1.0f};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .use_separate_coefficients = false,
        .initial_value = 8.59106f,
        .iterations = 5U,
    };
    uz_newton_raphson_derivate(config.poly_coefficients, config.derivate_poly_coefficients);
    float output = uz_newton_raphson(config);
    TEST_ASSERT_EQUAL_FLOAT(7.073508f, output);
}

void test_uz_newton_raphson_4th_order_result_separate_coefficients(void) {
    float poly_coefficients[5] = {1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    float derivate_poly_coefficients[4] = {1.0f, 1.0f, 0.0f, 4.0f};
    float coefficients[5] = {-1.417233563e+04f, 1.64965986e+03f, 0.0f, 0.0f, 1.0f};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .use_separate_coefficients = true,
        .initial_value = 8.59106f,
        .iterations = 5U,
    };
    float output = uz_newton_raphson(config);
    TEST_ASSERT_EQUAL_FLOAT(7.073508f, output);
}

void test_uz_newton_raphson_10th_order_result_separate_coefficients(void) {
    float poly_coefficients[11] = {1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f};
    float derivate_poly_coefficients[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,};
    float coefficients[11] = {-48.0f, 0.0f, 32.0f, 1.0f, -24.0f, 0.0f, 8.0f, 0.0f, -1.0f, 5.0f, 1.0f};
    struct uz_newton_raphson_config config = {
        .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
        .poly_coefficients.data = &poly_coefficients[0],
        .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
        .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
        .coefficients.length = UZ_ARRAY_SIZE(coefficients),
        .coefficients.data = &coefficients[0],
        .use_separate_coefficients = true,
        .initial_value = 5.0f,
        .iterations = 15U,
    };
    uz_newton_raphson_derivate(config.poly_coefficients, config.derivate_poly_coefficients);
    float output = uz_newton_raphson(config);
    TEST_ASSERT_EQUAL_FLOAT(1.4142135f, output);//Solution is sqrt(2)
}
#endif // TEST
