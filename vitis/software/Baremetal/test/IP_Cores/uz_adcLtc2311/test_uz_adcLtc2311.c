#ifdef TEST

#include "unity.h"
#include "uz_adcLtc2311.h"
#include "uz_adcLtc2311_private_utilities.h"
#include "test_assert_with_exception.h"
#include "mock_uz_adcLtc2311_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_HAL.h"

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

static struct uz_adcLtc2311_config_t config = {
        .base_address=TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .conversion_factor=1,
        .samples=1,
        .cpol=1,
        .try_infinite=true,
};

void setUp(void)
{
}

void tearDown(void)
{
}

uz_adcLtc2311_t* successfull_init(struct uz_adcLtc2311_config_t configuration);
uz_adcLtc2311_t* successfull_init(struct uz_adcLtc2311_config_t configuration) 
{
    uz_adcLtc2311_t* instance = uz_adcLtc2311_init(configuration);
    return instance;
}

void test_uz_adcLtc2311_successfull_init_(void)
{
    uz_adcLtc2311_t* test_instance = successfull_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}
void test_uz_adcLtc2311_init_fail_assert_zero_base_address(void)
{
    struct uz_adcLtc2311_config_t test_config = {
        .base_address=TEST_BASE_ADDRESS
    };
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_init(test_config));
}

void test_uz_adcLtc2311_init_fail_assert_zero_clock_frequency(void)
{
    struct uz_adcLtc2311_config_t test_config = {
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_init(test_config));
}

// test configure function

void test_uz_adcLtc2311_configure_self_not_null(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_configure(NULL));
}

/**
 * @brief Setup instance for conversion factor testing and expect the function calls
 * until acknowledgement
 * 
 */

void prepare_instance_operation_param_update(
    uz_adcLtc2311_t* instance, 
    uint32_t cr_return_value, 
    uint32_t cr_write_value)
{
    uint32_t master_select = UZ_ADCLTC2311_MASTER1;
    uint32_t channel_select = UZ_ADCLTC2311_CH2;
    int32_t conversion_factor = 10;
    int32_t offset = 20;
    uint32_t samples = 5;

    uz_adcLtc2311_set_master_select(instance, master_select);
    uz_adcLtc2311_set_channel_select(instance, channel_select);
    uz_adcLtc2311_set_conversion_factor(instance, conversion_factor);
    uz_adcLtc2311_set_offset(instance, offset);
    uz_adcLtc2311_set_samples(instance, samples);

    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, cr_return_value);
    uz_adcLtc2311_hw_write_master_channel_Expect(TEST_BASE_ADDRESS, master_select);
    uz_adcLtc2311_hw_write_channel_Expect(TEST_BASE_ADDRESS,channel_select);
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, conversion_factor);
    uz_adcLtc2311_hw_write_cr_Expect(TEST_BASE_ADDRESS, cr_write_value);
}

/**
 * @brief Setup instance for operation parameter update success
 * -> return acknowledgement
 * 
 * @param instance 
 * @param cr_return_value State of the CR register before the acknowledgement
 */
void prepare_instance_operation_param_update_hw_success(uz_adcLtc2311_t* instance, uint32_t cr_value)
{
    // max_attempts = 0 -> try infinitely
    uz_adcLtc2311_set_max_attempts(instance, 0);
    // cr return value now signals the acknowledgement of the update request
    uint32_t cr_return_value = cr_value & ~(UZ_ADCLTC2311_CR_CONV_VALUE_VALID);
    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, cr_return_value);
}

/**
 * @brief Setup instance for operation parameter update failure
 * -> return no acknowledgement
 * 
 */
void prepare_instance_operation_param_update_hw_failure(
    uz_adcLtc2311_t* instance,
    uint32_t cr_value,
    uint32_t max_attempts)
{
    uz_adcLtc2311_set_max_attempts(instance, max_attempts);
    // cr return value does not signal the acknowledgement of the update request
    uint32_t cr_return_value = cr_value  | UZ_ADCLTC2311_CR_CONV_VALUE_VALID;

    // expect the software to call the read function max_attempts times
    for(uint32_t i = 0; i <= max_attempts; i++)
    {
        uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, cr_return_value);
    }
}

/**
 * @brief Test successful conversion factor update
 * 
 */
void test_uz_adcLtc2311_update_conversion_factor(void)
{
    
    uint32_t cr_return_value = 0x0;
    uint32_t cr_write_value = cr_return_value;
    int32_t function_return_value = UZ_FAILURE;
    // setup the expected values
    // see the function implementation for more details
    cr_write_value &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_write_value |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_0;
    
    uz_adcLtc2311_t* instance = successfull_init(config);

    // prepare instance for test cases
    prepare_instance_operation_param_update(instance, cr_return_value, cr_write_value);
    prepare_instance_operation_param_update_hw_success(instance, cr_write_value);

    function_return_value = uz_adcLtc2311_update_conversion_factor(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_SUCCESS);
}


/**
 * @brief Test hardware failure in case of conversion factor update
 * 
 */
void test_uz_adcLtc2311_update_conversion_factor_hw_failure(void)
{
    uint32_t max_attempts = 5;
    uint32_t cr_return_value = 0x0;
    uint32_t cr_write_value = cr_return_value;
    int32_t function_return_value = UZ_FAILURE;
    // setup the expected values
    // see the function implementation for more details
    cr_write_value &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_write_value |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_0;
    
    uz_adcLtc2311_t* instance = successfull_init(config);

    // prepare instance for test cases
    prepare_instance_operation_param_update(instance, cr_return_value, cr_write_value);
    prepare_instance_operation_param_update_hw_failure(instance, cr_write_value, max_attempts);

    function_return_value = uz_adcLtc2311_update_conversion_factor(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_FAILURE);
}

#endif // TEST
