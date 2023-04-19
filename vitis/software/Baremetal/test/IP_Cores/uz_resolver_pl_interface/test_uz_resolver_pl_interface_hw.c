#ifdef TEST
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_resolver_pl_interface_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address
#include "unity.h"

#include "uz_resolver_pl_interface_hw.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_resolver_pl_interface_hw_write_resolver_polepairs(void)
{
    int32_t polepairs = 3;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS + resolver_polepairs_AXI_Data_uz_resolver_pl_interface, polepairs);
    uz_resolver_pl_interface_hw_write_resolver_polepairs(TEST_BASE_ADDRESS, polepairs);
}

void test_uz_resolver_pl_interface_hw_write_resolver_polepairs_with_zero_base_address(void)
{
    int32_t polepairs = 3;
    uz_axi_write_int32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_write_resolver_polepairs(0, polepairs));
}

void test_uz_resolver_pl_interface_hw_write_cnt_reset(void)
{
    bool reset = true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + cnt_reset_AXI_Data_uz_resolver_pl_interface, reset);
    uz_resolver_pl_interface_hw_write_cnt_reset(TEST_BASE_ADDRESS, reset);
}

void test_uz_resolver_pl_interface_hw_write_cnt_reset_with_zero_base_address(void)
{
    bool reset = true;
    uz_axi_write_bool_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_write_cnt_reset(0, reset));
}

void test_uz_resolver_pl_interface_hw_write_position_intmax(void)
{
    int32_t intmax = 65535;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS + position_intmax_AXI_Data_uz_resolver_pl_interface, intmax);
    uz_resolver_pl_interface_hw_write_position_intmax(TEST_BASE_ADDRESS, intmax);
}

void test_uz_resolver_pl_interface_hw_write_position_intmax_with_zero_base_address(void)
{
    int32_t intmax = 65535;
    uz_axi_write_int32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_write_position_intmax(0, intmax));
}

void test_uz_resolver_pl_interface_hw_write_machine_polepairs(void)
{
    int32_t polepairs = 5;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS + machine_polepairs_AXI_Data_uz_resolver_pl_interface, polepairs);
    uz_resolver_pl_interface_hw_write_machine_polepairs(TEST_BASE_ADDRESS, polepairs);
}

void test_uz_resolver_pl_interface_hw_write_machine_polepairs_with_zero_base_address(void)
{
    int32_t polepairs = 5;
    uz_axi_write_int32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_write_machine_polepairs(0, polepairs));
}

void test_uz_resolver_pl_interface_hw_write_bitToRPS_factor_for_16bit(void)
{
    float bitToRPS_factor = 0.003814697f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS + bitToRPS_Factor_AXI_Data_uz_resolver_pl_interface, bitToRPS_factor);
    uz_resolver_pl_interface_hw_write_bitToRPS_factor(TEST_BASE_ADDRESS, bitToRPS_factor);
}

void test_uz_resolver_pl_interface_hw_write_bitToRPS_factor_with_zero_base_address(void)
{
    float bitToRPS_factor = 0.003814697f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_write_bitToRPS_factor(0, bitToRPS_factor));
}

void test_uz_resolver_pl_interface_hw_write_theta_m_offset_rad(void)
{
    float theta_m_offset_rad = -0.42f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS + theta_m_offset_rad_AXI_Data_uz_resolver_pl_interface, theta_m_offset_rad);
    uz_resolver_pl_interface_hw_write_theta_m_offset_rad(TEST_BASE_ADDRESS, theta_m_offset_rad);
}

void test_uz_resolver_pl_interface_hw_write_theta_m_offset_rad_with_zero_base_address(void)
{
    float theta_m_offset_rad = -0.42f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_write_theta_m_offset_rad(0, theta_m_offset_rad));
}

void test_uz_resolver_pl_interface_hw_write_theta_m_offset_rad_with_positive_theta_offset(void)
{
    float theta_m_offset_rad = 0.42f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_write_theta_m_offset_rad(TEST_BASE_ADDRESS, theta_m_offset_rad));
}

void test_uz_resolver_pl_interface_hw_write_theta_m_offset_rad_with_out_of_bound_theta_offset(void)
{
    float theta_m_offset_rad = -7.42f;
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_write_theta_m_offset_rad(TEST_BASE_ADDRESS, theta_m_offset_rad));
}

void test_uz_resolver_pl_interface_hw_read_revolution_cnt(void)
{
    int32_t cnt_value = -2;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS + cnt_AXI_Data_uz_resolver_pl_interface, -2);
    int32_t cnt_value_return = uz_resolver_pl_interface_hw_read_revolution_cnt(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(cnt_value,cnt_value_return);
}

void test_uz_resolver_pl_interface_hw_read_revolution_cnt_with_zero_base_address(void)
{
    int32_t cnt_value = -2;
    uz_axi_read_int32_IgnoreAndReturn(cnt_value);
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_read_revolution_cnt(0));
}

void test_uz_resolver_pl_interface_hw_read_pos_mech_2pi(void)
{
    float pos = 3.42f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + position_mech_2pi_AXI_Data_uz_resolver_pl_interface, 3.42f);
    float pos_value_return = uz_resolver_pl_interface_hw_read_pos_mech_2pi(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(pos,pos_value_return);
}

void test_uz_resolver_pl_interface_hw_read_pos_mech_2pi_with_zero_base_address(void)
{
    float pos = 3.42f;
    uz_axi_read_float_IgnoreAndReturn(pos);
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_read_pos_mech_2pi(0));
}

void test_uz_resolver_pl_interface_hw_read_pos_el_2pi(void)
{
    float pos = 3.42f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + position_el_2pi_AXI_Data_uz_resolver_pl_interface, 3.42f);
    float pos_value_return = uz_resolver_pl_interface_hw_read_pos_el_2pi(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(pos,pos_value_return);
}

void test_uz_resolver_pl_interface_hw_read_pos_el_2pi_with_zero_base_address(void)
{
    float pos = 3.42f;
    uz_axi_read_float_IgnoreAndReturn(pos);
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_read_pos_el_2pi(0));
}

void test_uz_resolver_pl_interface_hw_read_omega_mech_rad_s(void)
{
    float omega_m = 104.72f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + omega_mech_rad_s_AXI_Data_uz_resolver_pl_interface, 104.72f);
    float omega_m_value_return = uz_resolver_pl_interface_hw_read_omega_mech_rad_s(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(omega_m,omega_m_value_return);
}

void test_uz_resolver_pl_interface_hw_read_omega_mech_rad_s_with_zero_base_address(void)
{
    float omega_m = 104.72f;
    uz_axi_read_float_IgnoreAndReturn(omega_m);
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_read_omega_mech_rad_s(0));
}

void test_uz_resolver_pl_interface_hw_read_n_mech_rpm(void)
{
    float n_mech_rpm = 1000.0f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + n_mech_rpm_AXI_Data_uz_resolver_pl_interface, 1000.0f);
    float n_mech_rpm_value_return = uz_resolver_pl_interface_hw_read_n_mech_rpm(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(n_mech_rpm,n_mech_rpm_value_return);
}

void test_uz_resolver_pl_interface_hw_read_n_mech_rpm_with_zero_base_address(void)
{
    float n_mech_rpm = 1000.0f;
    uz_axi_read_float_IgnoreAndReturn(n_mech_rpm);
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_hw_read_n_mech_rpm(0));
}
#endif // TEST
