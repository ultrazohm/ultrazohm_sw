#ifdef TEST

#include "unity.h"
#include "uz_adcLtc2311.h"
#include "uz_adcLtc2311_private_utilities.h"
#include "test_assert_with_exception.h"
#include "mock_uz_adcLtc2311_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_struct_helper.h"
#include "mock_uz_fixedpoint.h"

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * Function declarations of utilities only used in this file
 * These functions are not tests on there own
 * Implementation can be found at the bottom of the file
 * The functions set up expects for specific operations. the expect_ functions may
 * be called for different use cases
 * 
 * Example: The uz_adcLtc2311_init(...) function as well as the update_conversion_factor(...) function needs
 * expects for a successfull update of the conversion factor
 * -> the function expect_update_conversion_factor_success(...) is called in both functions
 * The expect_ functions only set up expects they do not have access to the instance
 * HW registers are always given as pointers and they are updated by the expect_ functions
 */

void expect_set_ss_n(uint32_t *spi_cr_content);
void expect_reset_ss_n(uint32_t *spi_cr_content);
void expect_set_sclk(uint32_t *spi_cr_content);
void expect_reset_sclk(uint32_t *spi_cr_content);
void expect_prepare_manual_operation_success(uint32_t *spi_cr_content, uint32_t *cr_content, uint32_t master_select_value);
void expect_disable_manual_mode_success(uint32_t *spi_cr_content);

void expect_operation_param_update_success(uint32_t *cr_content);
void expect_operation_param_update_failure(uint32_t *cr_content, uint32_t max_attempts);
void expect_update_specific_channel(uint32_t *cr_content, uint32_t master, uint32_t channel);
void expect_update_master_only(uint32_t *cr_content, uint32_t master);

void expect_update_conversion_factor_success(uint32_t *cr_content, uint32_t master, uint32_t channel, float value, struct uz_fixedpoint_definition_t fixedpoint_definition);
void expect_update_offset_success(uint32_t *cr_content, uint32_t master, uint32_t channel, int value);
void expect_update_samples_success(uint32_t *cr_content, uint32_t master, uint32_t value);
void expect_update_sample_time_success(uint32_t *cr_content, uint32_t master, uint32_t value);
void expect_update_spi_success(uint32_t *spi_cr_content, uint32_t *spi_cfgr_content, uint32_t pre_delay, uint32_t post_delay, uint32_t clk_div, uint32_t cpol, uint32_t cpha);
void expect_enter_nap_mode_success(uint32_t *spi_cr_content, uint32_t *cr_content, uint32_t *adc_available_content, uint32_t master);
void expect_enter_sleep_mode_success(uint32_t *spi_cr_content, uint32_t *cr_content, uint32_t *adc_available_content, uint32_t master);
void expect_adc_available(uint32_t *adc_available_content, uint32_t mask);
void expect_adc_not_available(uint32_t *adc_available_content, uint32_t mask);
void expect_set_triggered_mode(uint32_t *cr_content);
void expect_set_pl_trigger_mode(uint32_t *cr_content);

// Utilites
uint32_t gen_uint32_all_bits_set(void);
uz_adcLtc2311_t *successfull_init(void);

/************ End of private utility declaration used in this file *************************/

void test_uz_adcLtc2311_successfull_init_(void)
{
    uz_adcLtc2311_t *test_instance = successfull_init();
    TEST_ASSERT_NOT_NULL(test_instance);
}
void test_uz_adcLtc2311_init_fail_assert_zero_base_address(void)
{
    struct uz_adcLtc2311_config_t test_config = {
        .base_address = TEST_BASE_ADDRESS};
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_init(test_config));
}

void test_uz_adcLtc2311_init_fail_assert_zero_clock_frequency(void)
{
    struct uz_adcLtc2311_config_t test_config = {
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ};
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_init(test_config));
}

void test_uz_adcLtc2311_set_samples_msb_set(void)
{
    uz_adcLtc2311_t *instance = successfull_init();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_samples(instance, (1U << 31)));
}

void test_uz_adcLtc2311_set_sample_time_msb_set(void)
{
    uz_adcLtc2311_t *instance = successfull_init();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_sample_time(instance, (1U << 31)));
}

void test_uz_adcLtc2311_set_samples_msb_not_set(void)
{
    uz_adcLtc2311_t *instance = successfull_init();
    uz_adcLtc2311_set_samples(instance, (1U << 30));
}

void test_uz_adcLtc2311_set_sample_time_msb_not_set(void)
{
    uz_adcLtc2311_t *instance = successfull_init();
    uz_adcLtc2311_set_sample_time(instance, (1U << 30));
}

void test_uz_adcLtc2311_set_channel_config_successful(void)
{
    uz_adcLtc2311_t *instance = successfull_init();

    uint32_t master_select = UZ_ADCLTC2311_MASTER1;
    uint32_t channel_select = UZ_ADCLTC2311_CH1 | UZ_ADCLTC2311_CH2 | UZ_ADCLTC2311_CH3; // Set same config to channel 1, 2, and 3
    struct uz_adcLtc2311_channel_config_t channel_config = {
        .conversion_factor = 13.3f,
        .conversion_factor_definition = {
            .is_signed = true,
            .fractional_bits = 5,
            .integer_bits = 10},
        .offset = 10};
    // expect the HW transactions
    uint32_t cr_content = 0x0;
    expect_update_conversion_factor_success(&cr_content, master_select, channel_select, channel_config.conversion_factor, channel_config.conversion_factor_definition);
    expect_update_offset_success(&cr_content, master_select, channel_select, channel_config.offset);

    uz_adcLtc2311_set_channel_config(instance, master_select, channel_select, channel_config);
}

void test_uz_adcLtc2311_set_samples_value_is_zero(void)
{
    uz_adcLtc2311_t *instance = successfull_init();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_samples(instance, 0));
}

/**
 * @brief Test successful conversion factor update
 * 
 */
void test_uz_adcLtc2311_update_conversion_factor(void)
{
    float conversion_factor = 10;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t channel = UZ_ADCLTC2311_CH1;
    uint32_t cr_content = 0x0;
    uint32_t function_return_value = UZ_FAILURE;

    struct uz_fixedpoint_definition_t conversion_factor_fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 6,
        .integer_bits = 10};

    uz_adcLtc2311_t *instance = successfull_init();

    // setup the instance
    uz_adcLtc2311_set_master_select(instance, master);
    uz_adcLtc2311_set_channel_select(instance, channel);
    uz_adcLtc2311_set_conversion_factor(instance, conversion_factor, conversion_factor_fixedpoint_definition);

    // expect the HW transactions
    expect_update_conversion_factor_success(&cr_content, master, channel, conversion_factor, conversion_factor_fixedpoint_definition);

    // call the actual function
    function_return_value = uz_adcLtc2311_update_conversion_factor(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_SUCCESS);
}

/**
 * @brief Test hardware failure in case of conversion factor update
 * 
 */
void test_uz_adcLtc2311_update_conversion_factor_hw_failure(void)
{
    float conversion_factor = 10.0f;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t channel = UZ_ADCLTC2311_CH1;
    uint32_t cr_content = 0x0;
    uint32_t max_attempts = 2U;
    uint32_t function_return_value = UZ_FAILURE;
    struct uz_fixedpoint_definition_t conversion_factor_fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 6,
        .integer_bits = 10};

    uz_adcLtc2311_t *instance = successfull_init();

    // setup the instance
    uz_adcLtc2311_set_master_select(instance, master);
    uz_adcLtc2311_set_channel_select(instance, channel);
    uz_adcLtc2311_set_conversion_factor(instance, conversion_factor, conversion_factor_fixedpoint_definition);
    uz_adcLtc2311_set_max_attempts(instance, max_attempts);

    // expect the HW transactions
    // prepare instance for test cases
    expect_update_specific_channel(&cr_content, master, channel);

    // expect the software to write the conversion factor
    uz_adcLtc2311_hw_write_value_fixedpoint_Ignore(); // the arguments and function call does not matter since this tests the fail case
    cr_content &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_content |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_0;

    // expect update failure
    expect_operation_param_update_failure(&cr_content, max_attempts);

    // call the actual function
    function_return_value = uz_adcLtc2311_update_conversion_factor(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_FAILURE);
}

/**
 * @brief Test successful offset update
 * 
 */
void test_uz_adcLtc2311_update_offset(void)
{
    int32_t offset = 5;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t channel = UZ_ADCLTC2311_CH1;
    uint32_t cr_content = 0x0;
    uint32_t function_return_value = UZ_FAILURE;

    uz_adcLtc2311_t *instance = successfull_init();

    // setup the instance
    uz_adcLtc2311_set_master_select(instance, master);
    uz_adcLtc2311_set_channel_select(instance, channel);
    uz_adcLtc2311_set_offset(instance, offset);

    // expect the HW transactions
    expect_update_offset_success(&cr_content, master, channel, offset);

    // call the actual function
    function_return_value = uz_adcLtc2311_update_offset(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_SUCCESS);
}

/**
 * @brief Test hardware failure in case of offset update
 * 
 */
void test_uz_adcLtc2311_update_offset_hw_failure(void)
{
    int32_t offset = 5;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t channel = UZ_ADCLTC2311_CH1;
    uint32_t cr_content = 0x0;
    uint32_t max_attempts = 2;
    uint32_t function_return_value = UZ_FAILURE;

    uz_adcLtc2311_t *instance = successfull_init();

    // setup the instance
    uz_adcLtc2311_set_master_select(instance, master);
    uz_adcLtc2311_set_channel_select(instance, channel);
    uz_adcLtc2311_set_offset(instance, offset);
    uz_adcLtc2311_set_max_attempts(instance, max_attempts);

    // expect the HW transactions
    // prepare instance for test cases
    expect_update_specific_channel(&cr_content, master, channel);

    // expect the software to write the conversion factor
    uz_adcLtc2311_hw_write_value_signed_Ignore();
    cr_content &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_content |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID;

    // expect update failure
    expect_operation_param_update_failure(&cr_content, max_attempts);

    // call the actual function
    function_return_value = uz_adcLtc2311_update_offset(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_FAILURE);
}

void test_uz_adcLtc2311_update_samples(void)
{
    uint32_t samples = 2147483647;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t cr_content = 0x0;
    uint32_t function_return_value = UZ_FAILURE;

    uz_adcLtc2311_t *instance = successfull_init();

    // setup the instance
    uz_adcLtc2311_set_master_select(instance, master);
    uz_adcLtc2311_set_samples(instance, samples);

    // expect the HW transactions
    expect_update_samples_success(&cr_content, master, samples);

    // call the actual function
    function_return_value = uz_adcLtc2311_update_samples(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_SUCCESS);
}

/**
 * @brief Test hardware failure in case of samples update
 * 
 */
void test_uz_adcLtc2311_update_samples_hw_failure(void)
{
    uint32_t samples = 15U;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t cr_content = 0x0;
    uint32_t max_attempts = 2U;
    uint32_t function_return_value = UZ_FAILURE;

    uz_adcLtc2311_t *instance = successfull_init();

    // setup the instance
    uz_adcLtc2311_set_master_select(instance, master);
    uz_adcLtc2311_set_samples(instance, samples);
    uz_adcLtc2311_set_max_attempts(instance, max_attempts);

    // expect the HW transactions
    // prepare instance for test cases
    expect_update_master_only(&cr_content, master);

    // expect the software to write the number of samples
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, samples);
    cr_content &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_content |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_1;

    // expect successfull update

    expect_operation_param_update_failure(&cr_content, max_attempts);

    // call the actual function
    function_return_value = uz_adcLtc2311_update_samples(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_FAILURE);
}

void test_uz_adcLtc2311_update_sample_time(void)
{
    uint32_t sample_time = 25U;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t cr_content = 0x0;
    uint32_t function_return_value = UZ_FAILURE;

    uz_adcLtc2311_t *instance = successfull_init();

    // setup the instance
    uz_adcLtc2311_set_master_select(instance, master);
    uz_adcLtc2311_set_sample_time(instance, sample_time);

    // expect the HW transactions
    expect_update_sample_time_success(&cr_content, master, sample_time);

    // call the actual function
    function_return_value = uz_adcLtc2311_update_sample_time(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_SUCCESS);
}

/**
 * @brief Test hardware failure in case of sample_time update
 * 
 */
void test_uz_adcLtc2311_update_sample_time_hw_failure(void)
{
    uint32_t sample_time = 25U;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t max_attempts = 10;
    uint32_t cr_content = 0x0;
    uint32_t function_return_value = UZ_FAILURE;

    uz_adcLtc2311_t *instance = successfull_init();

    // setup the instance
    uz_adcLtc2311_set_master_select(instance, master);
    uz_adcLtc2311_set_sample_time(instance, sample_time);
    uz_adcLtc2311_set_max_attempts(instance, max_attempts);

    // expect the HW transactions
    expect_update_master_only(&cr_content, master);

    // expect the software to write the number of samples
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, sample_time);
    cr_content &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_content |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_0;

    // expect successfull update

    expect_operation_param_update_failure(&cr_content, max_attempts);

    // call the actual function
    function_return_value = uz_adcLtc2311_update_sample_time(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_FAILURE);
}

void test_uz_adcLtc2311_set_pre_delay_to_big(void)
{
    uz_adcLtc2311_t *instance = successfull_init();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_pre_delay(instance, (1 << (UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_WIDTH))));
}

void test_uz_adcLtc2311_set_post_delay_to_big(void)
{
    uz_adcLtc2311_t *instance = successfull_init();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_post_delay(instance, (1 << (UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_WIDTH))));
}

void test_uz_adcLtc2311_set_clk_div_to_big(void)
{
    uz_adcLtc2311_t *instance = successfull_init();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_clk_div(instance, (1 << (UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_WIDTH))));
}

void test_uz_adcLtc2311_set_cpha_one(void)
{
    uz_adcLtc2311_t *instance = successfull_init();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_cpha(instance, 1));
}

void test_uz_adcLtc2311_set_cpol_zero(void)
{
    uz_adcLtc2311_t *instance = successfull_init();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_cpol(instance, 0));
}

void test_uz_adcLtc2311_update_spi(void)
{
    uint32_t pre_delay = 10U;
    uint32_t post_delay = 5U;
    uint32_t clk_div = 20U;
    uint32_t cpol = 1U;
    uint32_t cpha = 0U;
    // set another bit for testing purposes
    uint32_t spi_cr_content = UZ_ADCLTC2311_SPI_CR_SS_N;
    uint32_t spi_cfgr_content = 0x0;
    uz_adcLtc2311_t *instance = successfull_init();

    uz_adcLtc2311_set_pre_delay(instance, pre_delay);
    uz_adcLtc2311_set_post_delay(instance, post_delay);
    uz_adcLtc2311_set_clk_div(instance, clk_div);
    uz_adcLtc2311_set_cpha(instance, cpha);
    uz_adcLtc2311_set_cpol(instance, cpol);

    expect_update_spi_success(&spi_cr_content, &spi_cfgr_content, pre_delay, post_delay, clk_div, cpol, cpha);
    uz_adcLtc2311_update_spi(instance);
}

void test_uz_adcLtc2311_software_trigger_success(void)
{
    uint32_t cr_content = 0x0;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uz_adcLtc2311_t *instance = successfull_init();

    // test software trigger with direct channel indication
    uz_adcLtc2311_hw_write_master_channel_Expect(TEST_BASE_ADDRESS, master);
    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, cr_content);
    cr_content |= UZ_ADCLTC2311_CR_TRIGGER;
    uz_adcLtc2311_hw_write_cr_Expect(TEST_BASE_ADDRESS, cr_content);
    // reset bit by HW
    cr_content &= ~UZ_ADCLTC2311_CR_TRIGGER;
    uz_adcLtc2311_software_trigger(instance, master);

    // test software trigger with indirect channel indication
    master = UZ_ADCLTC2311_MASTER10;
    uz_adcLtc2311_set_master_select(instance, master);
    uz_adcLtc2311_hw_write_master_channel_Expect(TEST_BASE_ADDRESS, master);
    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, cr_content);
    cr_content |= UZ_ADCLTC2311_CR_TRIGGER;
    uz_adcLtc2311_hw_write_cr_Expect(TEST_BASE_ADDRESS, cr_content);
    uz_adcLtc2311_software_trigger(instance, 0);
}

// tests for nap mode

void test_uz_adcLtc2311_enter_nap_mode_success(void)
{
    uint32_t return_value = UZ_FAILURE;
    uint32_t cr_content = 0U;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t spi_cr_content = UZ_ADCLTC2311_SPI_CR_CPOL;
    uint32_t adc_available_content = gen_uint32_all_bits_set();

    uz_adcLtc2311_t *instance = successfull_init();
    uz_adcLtc2311_set_master_select(instance, master);
    expect_enter_nap_mode_success(&spi_cr_content, &cr_content, &adc_available_content, master);

    return_value = uz_adcLtc2311_enter_nap_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_napping_masters(instance));

    // try to send another channel to nap mode. This should work and both channels should be in nap mode
    master = UZ_ADCLTC2311_MASTER2;
    uz_adcLtc2311_set_master_select(instance, master);
    expect_enter_nap_mode_success(&spi_cr_content, &cr_content, &adc_available_content, master);
    return_value = uz_adcLtc2311_enter_nap_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(master | UZ_ADCLTC2311_MASTER1, uz_adcLtc2311_get_napping_masters(instance));
}

void test_uz_adcLtc2311_enter_nap_mode_no_master_selected(void)
{
    uint32_t return_value = UZ_SUCCESS;
    uz_adcLtc2311_t *instance = successfull_init();

    uz_adcLtc2311_set_master_select(instance, 0U);
    return_value = uz_adcLtc2311_enter_nap_mode(instance);
    TEST_ASSERT_EQUAL(UZ_FAILURE, return_value);
    TEST_ASSERT_EQUAL(UZ_ADCLTC2311_NS_NO_SELECTION, uz_adcLtc2311_get_error_code(instance));
}

void test_uz_adcLtc2311_enter_nap_mode_master_already_in_nap_mode(void)
{
    uint32_t return_value = UZ_FAILURE;
    uint32_t cr_content = 0U;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t spi_cr_content = UZ_ADCLTC2311_SPI_CR_CPOL;
    uint32_t adc_available_content = gen_uint32_all_bits_set();

    uz_adcLtc2311_t *instance = successfull_init();

    uz_adcLtc2311_set_master_select(instance, master);
    expect_enter_nap_mode_success(&spi_cr_content, &cr_content, &adc_available_content, master);

    return_value = uz_adcLtc2311_enter_nap_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_napping_masters(instance));

    // try to send the same channel again to nap mode. This should fail
    return_value = uz_adcLtc2311_enter_nap_mode(instance);
    TEST_ASSERT_EQUAL(UZ_FAILURE, return_value);
    TEST_ASSERT_EQUAL(UZ_ADCLTC2311_NS_ALREADY_IN_MODE, uz_adcLtc2311_get_error_code(instance));
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_napping_masters(instance));
}

void test_uz_adcLtc2311_leave_nap_mode_success(void)
{
    uint32_t return_value = UZ_FAILURE;
    uint32_t cr_content = 0U;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t spi_cr_content = UZ_ADCLTC2311_SPI_CR_CPOL;
    uint32_t adc_available_content = gen_uint32_all_bits_set();

    uz_adcLtc2311_t *instance = successfull_init();
    uz_adcLtc2311_set_master_select(instance, master);
    expect_enter_nap_mode_success(&spi_cr_content, &cr_content, &adc_available_content, master);

    return_value = uz_adcLtc2311_enter_nap_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_napping_masters(instance));

    // leave nap mode
    expect_prepare_manual_operation_success(&spi_cr_content, &cr_content, master);
    expect_reset_sclk(&spi_cr_content);
    expect_set_sclk(&spi_cr_content);

    expect_adc_available(&adc_available_content, master);
    expect_disable_manual_mode_success(&spi_cr_content);

    return_value = uz_adcLtc2311_leave_nap_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(0, uz_adcLtc2311_get_napping_masters(instance));
}

void test_uz_adcLtc2311_leave_nap_mode_master_not_in_nap_mode(void)
{
    uint32_t return_value = UZ_FAILURE;
    uint32_t master = UZ_ADCLTC2311_MASTER1;

    uz_adcLtc2311_t *instance = successfull_init();
    uz_adcLtc2311_set_master_select(instance, master);

    return_value = uz_adcLtc2311_leave_nap_mode(instance);
    TEST_ASSERT_EQUAL(UZ_FAILURE, return_value);
    TEST_ASSERT_EQUAL(UZ_ADCLTC2311_NS_NOT_IN_MODE, uz_adcLtc2311_get_error_code(instance));
}

void test_uz_adcLtc2311_enter_sleep_mode_success(void)
{
    uint32_t return_value = UZ_FAILURE;
    uint32_t cr_content = 0U;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t spi_cr_content = UZ_ADCLTC2311_SPI_CR_CPOL;
    uint32_t adc_available_content = gen_uint32_all_bits_set();

    uz_adcLtc2311_t *instance = successfull_init();
    uz_adcLtc2311_set_master_select(instance, master);
    expect_enter_sleep_mode_success(&spi_cr_content, &cr_content, &adc_available_content, master);

    return_value = uz_adcLtc2311_enter_sleep_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_sleeping_masters(instance));

    // try to send another channel to sleep mode. This should work and both channels should be in sleep mode
    master = UZ_ADCLTC2311_MASTER2;
    uz_adcLtc2311_set_master_select(instance, master);
    expect_enter_sleep_mode_success(&spi_cr_content, &cr_content, &adc_available_content, master);
    return_value = uz_adcLtc2311_enter_sleep_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(master | UZ_ADCLTC2311_MASTER1, uz_adcLtc2311_get_sleeping_masters(instance));
}

void test_uz_adcLtc2311_enter_sleep_mode_no_master_selected(void)
{
    uint32_t return_value = UZ_SUCCESS;
    uz_adcLtc2311_t *instance = successfull_init();

    uz_adcLtc2311_set_master_select(instance, 0U);
    return_value = uz_adcLtc2311_enter_sleep_mode(instance);
    TEST_ASSERT_EQUAL(UZ_FAILURE, return_value);
    TEST_ASSERT_EQUAL(UZ_ADCLTC2311_NS_NO_SELECTION, uz_adcLtc2311_get_error_code(instance));
}

void test_uz_adcLtc2311_enter_sleep_mode_master_already_in_sleep_mode(void)
{
    uint32_t return_value = UZ_FAILURE;
    uint32_t cr_content = 0;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t spi_cr_content = UZ_ADCLTC2311_SPI_CR_CPOL;
    uint32_t adc_available_content = gen_uint32_all_bits_set();

    uz_adcLtc2311_t *instance = successfull_init();

    uz_adcLtc2311_set_master_select(instance, master);
    expect_enter_sleep_mode_success(&spi_cr_content, &cr_content, &adc_available_content, master);

    return_value = uz_adcLtc2311_enter_sleep_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_sleeping_masters(instance));

    // try to send the same channel again to sleep mode. This should fail
    return_value = uz_adcLtc2311_enter_sleep_mode(instance);
    TEST_ASSERT_EQUAL(UZ_FAILURE, return_value);
    TEST_ASSERT_EQUAL(UZ_ADCLTC2311_NS_ALREADY_IN_MODE, uz_adcLtc2311_get_error_code(instance));
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_sleeping_masters(instance));
}

void test_uz_adcLtc2311_leave_sleep_mode_success(void)
{
    uint32_t return_value = UZ_FAILURE;
    uint32_t cr_content = 0U;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t spi_cr_content = UZ_ADCLTC2311_SPI_CR_CPOL;
    uint32_t adc_available_content = gen_uint32_all_bits_set();

    uz_adcLtc2311_t *instance = successfull_init();
    uz_adcLtc2311_set_master_select(instance, master);
    expect_enter_sleep_mode_success(&spi_cr_content, &cr_content, &adc_available_content, master);

    return_value = uz_adcLtc2311_enter_sleep_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_sleeping_masters(instance));

    // leave nap mode
    expect_prepare_manual_operation_success(&spi_cr_content, &cr_content, master);
    expect_reset_ss_n(&spi_cr_content);
    expect_set_ss_n(&spi_cr_content);

    expect_adc_available(&adc_available_content, master);
    expect_disable_manual_mode_success(&spi_cr_content);

    return_value = uz_adcLtc2311_leave_sleep_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(0, uz_adcLtc2311_get_napping_masters(instance));
}

void test_uz_adcLtc2311_leave_sleep_mode_master_not_in_sleep_mode(void)
{
    uint32_t return_value = UZ_FAILURE;
    uint32_t master = UZ_ADCLTC2311_MASTER1;

    uz_adcLtc2311_t *instance = successfull_init();
    uz_adcLtc2311_set_master_select(instance, master);

    return_value = uz_adcLtc2311_leave_sleep_mode(instance);
    TEST_ASSERT_EQUAL(UZ_FAILURE, return_value);
    TEST_ASSERT_EQUAL(UZ_ADCLTC2311_NS_NOT_IN_MODE, uz_adcLtc2311_get_error_code(instance));
}

void test_uz_adcLtc2311_enter_nap_mode_master_in_sleep(void)
{
    uint32_t return_value = UZ_FAILURE;
    uint32_t cr_content = 0U;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t spi_cr_content = UZ_ADCLTC2311_SPI_CR_CPOL;
    uint32_t adc_available_content = gen_uint32_all_bits_set();

    uz_adcLtc2311_t *instance = successfull_init();
    uz_adcLtc2311_set_master_select(instance, master);
    expect_enter_sleep_mode_success(&spi_cr_content, &cr_content, &adc_available_content, master);

    return_value = uz_adcLtc2311_enter_sleep_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_sleeping_masters(instance));

    // try to send the same master to sleep mode. This should fail
    return_value = uz_adcLtc2311_enter_nap_mode(instance);
    TEST_ASSERT_EQUAL(UZ_FAILURE, return_value);
    TEST_ASSERT_EQUAL(UZ_ADCLTC2311_NS_ALREADY_IN_MODE, uz_adcLtc2311_get_error_code(instance));
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_sleeping_masters(instance));
}

void test_uz_adcLtc2311_enter_sleep_mode_master_in_nap(void)
{
    uint32_t return_value = UZ_FAILURE;
    uint32_t cr_content = 0U;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t spi_cr_content = UZ_ADCLTC2311_SPI_CR_CPOL;
    uint32_t adc_available_content = gen_uint32_all_bits_set();

    uz_adcLtc2311_t *instance = successfull_init();
    uz_adcLtc2311_set_master_select(instance, master);
    expect_enter_nap_mode_success(&spi_cr_content, &cr_content, &adc_available_content, master);

    return_value = uz_adcLtc2311_enter_nap_mode(instance);
    TEST_ASSERT_EQUAL(UZ_SUCCESS, return_value);
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_napping_masters(instance));

    // try to send the same master to nap mode. This should fail
    return_value = uz_adcLtc2311_enter_sleep_mode(instance);
    TEST_ASSERT_EQUAL(UZ_FAILURE, return_value);
    TEST_ASSERT_EQUAL(UZ_ADCLTC2311_NS_ALREADY_IN_MODE, uz_adcLtc2311_get_error_code(instance));
    TEST_ASSERT_EQUAL(master, uz_adcLtc2311_get_napping_masters(instance));
}

/************* Private utilites implementation used in the tests above **********************/

// Utilities

uint32_t gen_uint32_all_bits_set(void)
{
    uint32_t return_value = 0U;
    for (uint32_t i = 0; i < sizeof(return_value); i++)
    {
        return_value |= (1U << i);
    }

    return (return_value);
}

uz_adcLtc2311_t *successfull_init(void)
{
    float conversion_factor = 1.0f;
    uint32_t samples = 1U;
    int32_t offset = 0;
    uint32_t sample_time = 0U;
    uint32_t cpol = 1U;
    uint32_t cpha = 0U;
    uint32_t pre_delay = 0U;
    uint32_t post_delay = 0U;
    uint32_t clk_div = 0U;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t channel = UZ_ADCLTC2311_CH1 | UZ_ADCLTC2311_CH2 | UZ_ADCLTC2311_CH3 | UZ_ADCLTC2311_CH4 | UZ_ADCLTC2311_CH5 | UZ_ADCLTC2311_CH6 | UZ_ADCLTC2311_CH7 | UZ_ADCLTC2311_CH8;

    // Simulated HW register content
    uint32_t cr_content = 0x0;
    uint32_t spi_cr_content = UZ_ADCLTC2311_SPI_CR_CPOL;
    uint32_t spi_cfgr_content = 0U;

    struct uz_adcLtc2311_config_t default_configuration = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
        .channel_config = {
            .conversion_factor = conversion_factor,
            .conversion_factor_definition = {
                .is_signed = true,
                .integer_bits = 10,
                .fractional_bits = 6},
            .offset = offset,
        },
        .spi_master_config = {.samples = samples, .sample_time = sample_time, .trigger_mode=pl_trigger},
        .cpol = cpol,
        .cpha = cpha,
        .napping_spi_masters = 0,
        .sleeping_spi_masters = 0,
        .master_select = master,
        .channel_select = channel,
        .pre_delay = pre_delay,
        .post_delay = post_delay,
        .clk_div = clk_div,};

    expect_set_triggered_mode(&cr_content);
    expect_set_pl_trigger_mode(&cr_content);
    expect_update_conversion_factor_success(&cr_content, master, channel, conversion_factor, default_configuration.channel_config.conversion_factor_definition);
    expect_update_offset_success(&cr_content, master, channel, offset);
    expect_update_samples_success(&cr_content, master, samples);
    expect_update_sample_time_success(&cr_content, master, sample_time);
    expect_update_spi_success(&spi_cr_content, &spi_cfgr_content, pre_delay, post_delay, clk_div, cpol, cpha);
    uz_adcLtc2311_t *instance = uz_adcLtc2311_init(default_configuration);
    return instance;
}

// expect_ functions

/**
 * @brief Sets up the expects for a successfull update of the conversion factor. No actual update is
 * performed.
 * 
 * @param cr_content Pointer to the content of the cr. The variable gets updated. After function 
 *                   execution the variable contains the expected value of cr.
 * @param master 
 * @param channel 
 * @param value 
 */
void expect_update_conversion_factor_success(uint32_t *cr_content, uint32_t master, uint32_t channel, float value, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    // prepare instance for test cases
    expect_update_specific_channel(cr_content, master, channel);

    // expect the software to write the conversion factor
    uz_adcLtc2311_hw_write_value_fixedpoint_Expect(TEST_BASE_ADDRESS, value, fixedpoint_definition);

    *cr_content &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    *cr_content |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_0;

    // expect successfull update

    expect_operation_param_update_success(cr_content);
}

void expect_update_offset_success(uint32_t *cr_content, uint32_t master, uint32_t channel, int value)
{
    // prepare instance for test cases
    expect_update_specific_channel(cr_content, master, channel);

    // expect the software to write the offset
    uz_adcLtc2311_hw_write_value_signed_Expect(TEST_BASE_ADDRESS, value);

    *cr_content &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    *cr_content |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID;

    // expect successfull update

    expect_operation_param_update_success(cr_content);
}

void expect_update_samples_success(uint32_t *cr_content, uint32_t master, uint32_t value)
{
    // prepare instance for test cases
    expect_update_master_only(cr_content, master);

    // expect the software to write the number of samples
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, value);
    *cr_content &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    *cr_content |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_1;

    // expect successfull update

    expect_operation_param_update_success(cr_content);
}

void expect_update_sample_time_success(uint32_t *cr_content, uint32_t master, uint32_t value)
{
    // prepare instance for test cases
    expect_update_master_only(cr_content, master);

    // expect the software to write the sample time
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, value);
    *cr_content &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    *cr_content |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_0;

    // expect successfull update

    expect_operation_param_update_success(cr_content);
}

void expect_update_spi_success(uint32_t *spi_cr_content, uint32_t *spi_cfgr_content, uint32_t pre_delay, uint32_t post_delay, uint32_t clk_div, uint32_t cpol, uint32_t cpha)
{
    // values are concatenated in the SPI configuration register
    *spi_cfgr_content = (clk_div << UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_LSB) |
                        (pre_delay << UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_LSB) |
                        (post_delay << UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_LSB);
    uz_adcLtc2311_hw_write_spi_cfgr_Expect(TEST_BASE_ADDRESS, *spi_cfgr_content);

    uz_adcLtc2311_hw_read_spi_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *spi_cr_content);

    if (cpol == 0U)
        *spi_cr_content &= ~UZ_ADCLTC2311_SPI_CR_CPOL;
    else
        *spi_cr_content |= UZ_ADCLTC2311_SPI_CR_CPOL;

    if (cpha == 0U)
        *spi_cr_content &= ~UZ_ADCLTC2311_SPI_CR_CPHA;
    else
        *spi_cr_content |= UZ_ADCLTC2311_SPI_CR_CPHA;

    uz_adcLtc2311_hw_write_spi_cr_Expect(TEST_BASE_ADDRESS, *spi_cr_content);
}

void expect_update_specific_channel(uint32_t *cr_content, uint32_t master, uint32_t channel)
{
    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *cr_content);
    uz_adcLtc2311_hw_write_master_channel_Expect(TEST_BASE_ADDRESS, master);
    uz_adcLtc2311_hw_write_channel_Expect(TEST_BASE_ADDRESS, channel);
}

void expect_update_master_only(uint32_t *cr_content, uint32_t master)
{
    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *cr_content);
    uz_adcLtc2311_hw_write_master_channel_Expect(TEST_BASE_ADDRESS, master);
}

void expect_operation_param_update_success(uint32_t *cr_content)
{
    uz_adcLtc2311_hw_write_cr_Expect(TEST_BASE_ADDRESS, *cr_content);
    // HW acknowledgement = reset of VALUE_VALID bit
    *cr_content &= ~(UZ_ADCLTC2311_CR_CONV_VALUE_VALID);
    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *cr_content);
}

void expect_operation_param_update_failure(uint32_t *cr_content, uint32_t max_attempts)
{
    uz_adcLtc2311_hw_write_cr_Expect(TEST_BASE_ADDRESS, *cr_content);
    // HW acknowledgement = reset of VALUE_VALID bit -> no ack -> bit stays 1
    *cr_content |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID;

    // expect the software to call the read function max_attempts times
    for (uint32_t i = 0U; i < max_attempts; i++)
    {
        uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *cr_content);
    }
}

void expect_enter_nap_mode_success(uint32_t *spi_cr_content, uint32_t *cr_content, uint32_t *adc_available_content, uint32_t master)
{
    // pulses on ss_n that are expected. This is external HW dependant and will not change
    // even if the IP core is changed. Therefore, the #define is not used in the test
    const uint32_t ltc2311_nap_pulses = 2U;
    expect_prepare_manual_operation_success(spi_cr_content, cr_content, master);

    // expect the HW operation to send LTC2311 to nap mode
    for (uint32_t i = 0U; i < ltc2311_nap_pulses; i++)
    {
        expect_set_ss_n(spi_cr_content);
        expect_reset_ss_n(spi_cr_content);
    }
    expect_set_ss_n(spi_cr_content);

    expect_adc_not_available(adc_available_content, master);
    expect_disable_manual_mode_success(spi_cr_content);
}

void expect_enter_sleep_mode_success(uint32_t *spi_cr_content, uint32_t *cr_content, uint32_t *adc_available_content, uint32_t master)
{
    // pulses on ss_n that are expected. This is external HW dependant and will not change
    // even if the IP core is changed. Therefore, the #define is not used in the test
    const uint32_t ltc2311_sleep_pulses = 4U;
    expect_prepare_manual_operation_success(spi_cr_content, cr_content, master);

    // expect the HW operation to send LTC2311 to sleep mode
    for (uint32_t i = 0; i < ltc2311_sleep_pulses; i++)
    {
        expect_set_ss_n(spi_cr_content);
        expect_reset_ss_n(spi_cr_content);
    }
    expect_set_ss_n(spi_cr_content);

    expect_adc_not_available(adc_available_content, master);
    expect_disable_manual_mode_success(spi_cr_content);
}

void expect_adc_not_available(uint32_t *adc_available_content, uint32_t mask)
{
    uz_adcLtc2311_hw_read_adc_available_ExpectAndReturn(TEST_BASE_ADDRESS, *adc_available_content);
    *adc_available_content &= ~mask;
    uz_adcLtc2311_hw_write_adc_available_Expect(TEST_BASE_ADDRESS, *adc_available_content);
}

void expect_adc_available(uint32_t *adc_available_content, uint32_t mask)
{
    uz_adcLtc2311_hw_read_adc_available_ExpectAndReturn(TEST_BASE_ADDRESS, *adc_available_content);
    *adc_available_content |= mask;
    uz_adcLtc2311_hw_write_adc_available_Expect(TEST_BASE_ADDRESS, *adc_available_content);
}

void expect_set_triggered_mode(uint32_t *cr_content)
{
    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *cr_content);
    *cr_content &= ~UZ_ADCLTC2311_CR_MODE;
    uz_adcLtc2311_hw_write_cr_Expect(TEST_BASE_ADDRESS, *cr_content);
}

void expect_set_pl_trigger_mode(uint32_t *cr_content)
{
    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *cr_content);
    *cr_content &= ~UZ_ADCLTC2311_CR_SW_TRIGGER_MODE;
    uz_adcLtc2311_hw_write_cr_Expect(TEST_BASE_ADDRESS, *cr_content);
}

void expect_set_ss_n(uint32_t *spi_cr_content)
{
    uz_adcLtc2311_hw_read_spi_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *spi_cr_content);
    *spi_cr_content |= UZ_ADCLTC2311_SPI_CR_SS_N;
    uz_adcLtc2311_hw_write_spi_cr_Expect(TEST_BASE_ADDRESS, *spi_cr_content);
}

void expect_reset_ss_n(uint32_t *spi_cr_content)
{
    uz_adcLtc2311_hw_read_spi_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *spi_cr_content);
    *spi_cr_content &= ~UZ_ADCLTC2311_SPI_CR_SS_N;
    uz_adcLtc2311_hw_write_spi_cr_Expect(TEST_BASE_ADDRESS, *spi_cr_content);
}

void expect_set_sclk(uint32_t *spi_cr_content)
{
    uz_adcLtc2311_hw_read_spi_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *spi_cr_content);
    *spi_cr_content |= UZ_ADCLTC2311_SPI_CR_SCLK;
    uz_adcLtc2311_hw_write_spi_cr_Expect(TEST_BASE_ADDRESS, *spi_cr_content);
}

void expect_reset_sclk(uint32_t *spi_cr_content)
{
    uz_adcLtc2311_hw_read_spi_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *spi_cr_content);
    *spi_cr_content &= ~UZ_ADCLTC2311_SPI_CR_SCLK;
    uz_adcLtc2311_hw_write_spi_cr_Expect(TEST_BASE_ADDRESS, *spi_cr_content);
}

/**
 * @brief Expected calls from uz_adcLtc2311_prepare_manual_operation() from private utilities
 * 
 * @param spi_cr_content 
 * @param cr_content 
 * @param master_select_value 
 */
void expect_prepare_manual_operation_success(uint32_t *spi_cr_content, uint32_t *cr_content, uint32_t master_select_value)
{
    expect_set_triggered_mode(cr_content);
    uz_adcLtc2311_hw_write_master_channel_Expect(TEST_BASE_ADDRESS, master_select_value);

    expect_set_ss_n(spi_cr_content);
    expect_set_sclk(spi_cr_content);

    uz_adcLtc2311_hw_read_spi_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *spi_cr_content);
    *spi_cr_content |= UZ_ADCLTC2311_SPI_CR_CONTROL;
    uz_adcLtc2311_hw_write_spi_cr_Expect(TEST_BASE_ADDRESS, *spi_cr_content);

    *spi_cr_content |= UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS;
    uz_adcLtc2311_hw_read_spi_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *spi_cr_content);
}

void expect_disable_manual_mode_success(uint32_t *spi_cr_content)
{
    uz_adcLtc2311_hw_read_spi_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *spi_cr_content);
    *spi_cr_content &= ~UZ_ADCLTC2311_SPI_CR_CONTROL;
    uz_adcLtc2311_hw_write_spi_cr_Expect(TEST_BASE_ADDRESS, *spi_cr_content);

    *spi_cr_content &= ~UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS;
    uz_adcLtc2311_hw_read_spi_cr_ExpectAndReturn(TEST_BASE_ADDRESS, *spi_cr_content);
}

#endif // TEST
