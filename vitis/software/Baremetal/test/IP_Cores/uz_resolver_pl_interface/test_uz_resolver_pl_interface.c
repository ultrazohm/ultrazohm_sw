#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_resolver_pl_interface.h"
#include "mock_uz_resolver_pl_interface_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_resolver_pl_interface_init(void)
{
    struct uz_resolver_pl_interface_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .resolver_polepairs=3.0f,
        .machine_polepairs=5.0f,
        .bitToRPS_factor=0.003814697f,
        .position_intmax=65535U,
        .theta_m_offset_rad=-0.42f
    };

    struct uz_resolver_pl_interface_outputs_t outputs={
        .revolution_counter=0U,
        .position_mech_2pi=0.0f,
        .position_el_2pi=0.0f,
        .omega_mech_rad_s=0.0f,
        .n_mech_rpm=0.0f
    };
    uz_resolver_pl_interface_hw_write_machine_polepairs_Expect(TEST_BASE_ADDRESS, config.machine_polepairs);
    uz_resolver_pl_interface_hw_write_resolver_polepairs_Expect(TEST_BASE_ADDRESS, config.resolver_polepairs);
    uz_resolver_pl_interface_hw_write_position_intmax_Expect(TEST_BASE_ADDRESS, config.position_intmax);
    uz_resolver_pl_interface_hw_write_bitToRPS_factor_Expect(TEST_BASE_ADDRESS, config.bitToRPS_factor);
    uz_resolver_pl_interface_hw_write_theta_m_offset_rad_Expect(TEST_BASE_ADDRESS, config.theta_m_offset_rad);
    uz_resolver_pl_interface_hw_write_cnt_reset_Expect(TEST_BASE_ADDRESS, true);
    uz_resolver_pl_interface_hw_write_cnt_reset_Expect(TEST_BASE_ADDRESS, false);
    uz_resolver_pl_interface_init(config, outputs);

}

void test_uz_resolver_pl_interface_init_without_base_address_init(void)
{
    struct uz_resolver_pl_interface_config_t config={
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .resolver_polepairs=3.0f,
        .machine_polepairs=5.0f,
        .bitToRPS_factor=0.003814697f,
        .position_intmax=65535U,
        .theta_m_offset_rad=-0.42f
    };
    struct uz_resolver_pl_interface_outputs_t outputs={
        .revolution_counter=0U,
        .position_mech_2pi=0.0f,
        .position_el_2pi=0.0f,
        .omega_mech_rad_s=0.0f,
        .n_mech_rpm=0.0f
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_init(config, outputs));  
}

void test_uz_resolver_pl_interface_init_without_clk_freq_init(void)
{
    struct uz_resolver_pl_interface_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .resolver_polepairs=3.0f,
        .machine_polepairs=5.0f,
        .bitToRPS_factor=0.003814697f,
        .position_intmax=65535U,
        .theta_m_offset_rad=-0.42f
    };

    struct uz_resolver_pl_interface_outputs_t outputs={
        .revolution_counter=0U,
        .position_mech_2pi=0.0f,
        .position_el_2pi=0.0f,
        .omega_mech_rad_s=0.0f,
        .n_mech_rpm=0.0f
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_init(config, outputs)); 
}

void test_uz_resolver_pl_interface_init_without_resolver_polepairs_init(void)
{
    struct uz_resolver_pl_interface_config_t config={
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .machine_polepairs=5.0f,
        .bitToRPS_factor=0.003814697f,
        .position_intmax=65535U,
        .theta_m_offset_rad=-0.42f
    };
    struct uz_resolver_pl_interface_outputs_t outputs={
        .revolution_counter=0U,
        .position_mech_2pi=0.0f,
        .position_el_2pi=0.0f,
        .omega_mech_rad_s=0.0f,
        .n_mech_rpm=0.0f
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_init(config, outputs));  
}

void test_uz_resolver_pl_interface_init_without_machine_polepairs_init(void)
{
    struct uz_resolver_pl_interface_config_t config={
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .resolver_polepairs=3.0f,
        .bitToRPS_factor=0.003814697f,
        .position_intmax=65535U,
        .theta_m_offset_rad=-0.42f
    };
    struct uz_resolver_pl_interface_outputs_t outputs={
        .revolution_counter=0U,
        .position_mech_2pi=0.0f,
        .position_el_2pi=0.0f,
        .omega_mech_rad_s=0.0f,
        .n_mech_rpm=0.0f
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_init(config, outputs));  
}

void test_uz_resolver_pl_interface_init_without_bitToRPS_factor_init(void)
{
    struct uz_resolver_pl_interface_config_t config={
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .resolver_polepairs=3.0f,
        .machine_polepairs=5.0f,
        .position_intmax=65535U,
        .theta_m_offset_rad=-0.42f
    };
    struct uz_resolver_pl_interface_outputs_t outputs={
        .revolution_counter=0U,
        .position_mech_2pi=0.0f,
        .position_el_2pi=0.0f,
        .omega_mech_rad_s=0.0f,
        .n_mech_rpm=0.0f
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_init(config, outputs));  
}

void test_uz_resolver_pl_interface_init_without_position_intmax_init(void)
{
    struct uz_resolver_pl_interface_config_t config={
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .resolver_polepairs=3.0f,
        .machine_polepairs=5.0f,
        .bitToRPS_factor=0.003814697f,
        .theta_m_offset_rad=-0.42f
    };
    struct uz_resolver_pl_interface_outputs_t outputs={
        .revolution_counter=0U,
        .position_mech_2pi=0.0f,
        .position_el_2pi=0.0f,
        .omega_mech_rad_s=0.0f,
        .n_mech_rpm=0.0f
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_init(config, outputs));  
}

void test_uz_resolver_pl_interface_set_config_with_null(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_set_config(NULL));
}

void test_uz_resolver_pl_interface_get_outputs(void)
{
        struct uz_resolver_pl_interface_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .resolver_polepairs=3.0f,
        .machine_polepairs=5.0f,
        .bitToRPS_factor=0.003814697f,
        .position_intmax=65535U,
        .theta_m_offset_rad=-0.42f
    };

    struct uz_resolver_pl_interface_outputs_t outputs={
        .revolution_counter=0U,
        .position_mech_2pi=0.0f,
        .position_el_2pi=0.0f,
        .omega_mech_rad_s=0.0f,
        .n_mech_rpm=0.0f
    };

    uz_resolver_pl_interface_hw_write_machine_polepairs_Expect(TEST_BASE_ADDRESS, config.machine_polepairs);
    uz_resolver_pl_interface_hw_write_resolver_polepairs_Expect(TEST_BASE_ADDRESS, config.resolver_polepairs);
    uz_resolver_pl_interface_hw_write_position_intmax_Expect(TEST_BASE_ADDRESS, config.position_intmax);
    uz_resolver_pl_interface_hw_write_bitToRPS_factor_Expect(TEST_BASE_ADDRESS, config.bitToRPS_factor);
    uz_resolver_pl_interface_hw_write_theta_m_offset_rad_Expect(TEST_BASE_ADDRESS, config.theta_m_offset_rad);
    uz_resolver_pl_interface_hw_write_cnt_reset_Expect(TEST_BASE_ADDRESS, true);
    uz_resolver_pl_interface_hw_write_cnt_reset_Expect(TEST_BASE_ADDRESS, false);
    uz_resolver_pl_interface_t *instance = uz_resolver_pl_interface_init(config, outputs);

    uz_resolver_pl_interface_hw_read_revolution_cnt_ExpectAndReturn(TEST_BASE_ADDRESS, outputs.revolution_counter);
    uz_resolver_pl_interface_hw_read_pos_mech_2pi_ExpectAndReturn(TEST_BASE_ADDRESS, outputs.position_mech_2pi);
    uz_resolver_pl_interface_hw_read_pos_el_2pi_ExpectAndReturn(TEST_BASE_ADDRESS, outputs.position_el_2pi);
    uz_resolver_pl_interface_hw_read_omega_mech_rad_s_ExpectAndReturn(TEST_BASE_ADDRESS, outputs.omega_mech_rad_s);
    uz_resolver_pl_interface_hw_read_n_mech_rpm_ExpectAndReturn(TEST_BASE_ADDRESS, outputs.n_mech_rpm);
    
    uz_resolver_pl_interface_get_outputs(instance);
}

void test_uz_resolver_pl_interface_get_outputs_with_null(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_get_outputs(NULL));
}

void test_uz_resolver_pl_interface_set_theta_m_offset_rad_with_null(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pl_interface_set_theta_m_offset_rad(NULL,-0.42f));
}
#endif // TEST
