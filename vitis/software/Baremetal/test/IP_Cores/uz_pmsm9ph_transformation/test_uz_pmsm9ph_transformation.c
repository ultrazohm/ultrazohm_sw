#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_pmsm9ph_transformation.h"

#include "mock_uz_pmsm9ph_transformation_hw.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_pmsm9ph_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_core_frequency_Hz = IP_FRQ};

void setUp(void)
{
}

void tearDown(void)
{
}

uz_pmsm9ph_transformation_t *successful_init(struct uz_pmsm9ph_config_t configuration);
uz_pmsm9ph_transformation_t *successful_init(struct uz_pmsm9ph_config_t configuration){
    uz_pmsm9ph_transformation_t *instance = uz_pmsm9ph_transformation_init(configuration);
    return (instance);
}

void test_uz_pmsm9ph_transformation_successful_init(void){
    uz_pmsm9ph_transformation_t *test_instance = successful_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_pmsm9ph_transformation_normal_usage(void){
    uz_pmsm9ph_transformation_t *test_instance = successful_init(config);
    uz_9ph_abc_t value_expect = {
        .a1 = 1.0f,
        .b1 = 2.0f,
        .c1 = 3.0f,
        .a2 = 4.0f,
        .b2 = 5.0f,
        .c2 = 6.0f,
        .a3 = 7.0f,
        .b3 = 8.0f,
        .c3 = 9.0f};
    float theta_expect = 4.9f;

    uz_pmsm9ph_transformation_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    uz_pmsm9ph_transformation_hw_read_currents_ExpectAndReturn(BASE_ADDRESS,value_expect);
    uz_9ph_abc_t value_out = uz_pmsm9ph_transformation_get_currents(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.a1,value_out.a1);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.b1,value_out.b1);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.c1,value_out.c1);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.a2,value_out.a2);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.b2,value_out.b2);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.c2,value_out.c2);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.a3,value_out.a3);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.b3,value_out.b3);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.c3,value_out.c3);

    uz_pmsm9ph_transformation_hw_read_theta_el_ExpectAndReturn(BASE_ADDRESS,theta_expect);
    float theta_out = uz_pmsm9ph_transformation_get_theta_el(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(theta_expect,theta_out);
}

#endif // TEST
