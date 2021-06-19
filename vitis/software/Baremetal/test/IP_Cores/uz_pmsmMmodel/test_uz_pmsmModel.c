#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_pmsmModel.h"
#include "mock_uz_pmsmModel_hw.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_pmsmModel_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_core_frequency_Hz = IP_FRQ};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_pmsmModel_successful_init(void)
{
    uz_pmsmModel_t *instance = uz_pmsmModel_init(config);
    TEST_ASSERT_NOT_NULL(instance);
}

void test_uz_pmsmModel_get_i_d(void)
{
    uz_pmsmModel_t *test_instance = uz_pmsmModel_init(config);
    float i_d_expect = 1.3f;
    uz_pmsmModel_hw_read_i_d_ExpectAndReturn(BASE_ADDRESS, i_d_expect);
    float i_d_returned = uz_pmsmModel_get_i_d(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(i_d_expect, i_d_returned);
}

void test_uz_pmsmModel_get_i_q(void)
{
    uz_pmsmModel_t *test_instance = uz_pmsmModel_init(config);
    float i_q_expect = 11.312f;
    uz_pmsmModel_hw_read_i_q_ExpectAndReturn(BASE_ADDRESS, i_q_expect);
    float i_q_returned = uz_pmsmModel_get_i_q(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(i_q_expect, i_q_returned);
}

void test_uz_pmsmModel_get_torque(void)
{
    uz_pmsmModel_t *test_instance = uz_pmsmModel_init(config);
    float torque_expect = 23.1f;
    uz_pmsmModel_hw_read_torque_ExpectAndReturn(BASE_ADDRESS, torque_expect);
    float torque_returned = uz_pmsmModel_get_torque(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(torque_expect, torque_returned);
}

void test_uz_pmsmModel_set_u_d(void)
{
    uz_pmsmModel_t *test_instance = uz_pmsmModel_init(config);
    float u_d = 123.1f;
    uz_pmsmModel_hw_write_u_d_Expect(BASE_ADDRESS, u_d);
    uz_pmsmModel_set_u_d(test_instance, u_d);
}

void test_uz_pmsmModel_set_u_q(void)
{
    uz_pmsmModel_t *test_instance = uz_pmsmModel_init(config);
    float u_q = -31.2f;
    uz_pmsmModel_hw_write_u_q_Expect(BASE_ADDRESS, u_q);
    uz_pmsmModel_set_u_q(test_instance, u_q);
}

void test_uz_pmsmModel_set_omega_mech(void)
{
    uz_pmsmModel_t *test_instance = uz_pmsmModel_init(config);
    float omega_mech = -3111.2f;
    uz_pmsmModel_hw_write_omega_mech_Expect(BASE_ADDRESS, omega_mech);
    uz_pmsmModel_set_omega_mech(test_instance, omega_mech);
}

void test_uz_pmsmModel_reset_model(void)
{
    uz_pmsmModel_t *test_instance = uz_pmsmModel_init(config);
    uz_pmsmModel_hw_write_omega_mech_Expect(BASE_ADDRESS,0.0f);
    uz_pmsmModel_hw_write_u_d_Expect(BASE_ADDRESS,0.0f);
    uz_pmsmModel_hw_write_u_q_Expect(BASE_ADDRESS,0.0f);
    uz_pmsmModel_hw_write_reset_Expect(BASE_ADDRESS,false);
    uz_pmsmModel_hw_write_reset_Expect(BASE_ADDRESS,true);
    uz_pmsmModel_hw_write_reset_Expect(BASE_ADDRESS,false);
    uz_pmsmModel_reset(test_instance);
}

#endif // TEST
