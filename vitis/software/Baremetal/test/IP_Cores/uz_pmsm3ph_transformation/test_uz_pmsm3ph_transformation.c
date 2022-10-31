#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_pmsm3ph_transformation.h"

#include "mock_uz_pmsm3ph_transformation_hw.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_pmsm3ph_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_core_frequency_Hz = IP_FRQ};

void setUp(void)
{
}

void tearDown(void)
{
}

uz_pmsm3ph_transformation_t *successful_init(struct uz_pmsm3ph_config_t configuration);
uz_pmsm3ph_transformation_t *successful_init(struct uz_pmsm3ph_config_t configuration){
    uz_pmsm3ph_transformation_t *instance = uz_pmsm3ph_transformation_init(configuration);
    return (instance);
}

void test_uz_pmsm3ph_transformation_successful_init(void){
    uz_pmsm3ph_transformation_t *test_instance = successful_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_pmsm3ph_transformation_normal_usage(void){
    uz_pmsm3ph_transformation_t *test_instance = successful_init(config);
    uz_3ph_abc_t value_expect = {
        .a = 1.0f,
        .b = 2.0f,
        .c = 3.0f,};
    float theta_expect = 4.9f;

    uz_pmsm3ph_transformation_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    uz_pmsm3ph_transformation_hw_read_currents_ExpectAndReturn(BASE_ADDRESS,value_expect);
    uz_3ph_abc_t value_out = uz_pmsm3ph_transformation_get_currents(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.a,value_out.a);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.b,value_out.b);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.c,value_out.c);

    uz_pmsm3ph_transformation_hw_read_theta_el_ExpectAndReturn(BASE_ADDRESS,theta_expect);
    float theta_out = uz_pmsm3ph_transformation_get_theta_el(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(theta_expect,theta_out);
}

#endif // TEST
