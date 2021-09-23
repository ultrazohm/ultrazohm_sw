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
        .cpol=1
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

void test_uz_adcLtc2311_set_samples_msb_set(void)
{
    uz_adcLtc2311_t* instance = successfull_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_samples(instance, (1<<31) ));
}

void test_uz_adcLtc2311_set_sample_time_msb_set(void)
{
    uz_adcLtc2311_t* instance = successfull_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_sample_time(instance, (1<<31) ));
}

void test_uz_adcLtc2311_set_samples_msb_not_set(void)
{
    uz_adcLtc2311_t* instance = successfull_init(config);
    uz_adcLtc2311_set_samples(instance, (1<<30) );
}

void test_uz_adcLtc2311_set_sample_time_msb_not_set(void)
{
    uz_adcLtc2311_t* instance = successfull_init(config);
    uz_adcLtc2311_set_sample_time(instance, (1<<30) );
}

void test_uz_adcLtc2311_set_samples_value_is_zero(void)
{
    uz_adcLtc2311_t* instance = successfull_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_samples(instance, 0));
}

/**
 * @brief Setup instance for operation parameter update testing and expect the function calls
 * until acknowledgement
 * 
 * @param instance 
 * @param cr_return_value Current state of the CR register
 * @param update_channel Determination, if individual ADC channels shall be updated or not
 */
void prepare_instance_operation_param_update(
    uz_adcLtc2311_t* instance, 
    uint32_t cr_return_value,
    _Bool update_channel)
{
    uint32_t master_select = UZ_ADCLTC2311_MASTER1;
    uint32_t channel_select = UZ_ADCLTC2311_CH2;

    uz_adcLtc2311_set_master_select(instance, master_select);

    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, cr_return_value);
    uz_adcLtc2311_hw_write_master_channel_Expect(TEST_BASE_ADDRESS, master_select);
    if (update_channel)
    {
        uz_adcLtc2311_set_channel_select(instance, channel_select);
        uz_adcLtc2311_hw_write_channel_Expect(TEST_BASE_ADDRESS,channel_select);
    }
}

/**
 * @brief Setup instance for operation parameter update success
 * -> return acknowledgement
 * 
 * @param instance 
 * @param cr_write_value Value that is expected wo be written to the CR register
 */
void prepare_instance_operation_param_update_hw_success(uz_adcLtc2311_t* instance, uint32_t cr_write_value)
{
    uz_adcLtc2311_hw_write_cr_Expect(TEST_BASE_ADDRESS, cr_write_value);
    // max_attempts = 0 -> try infinitely
    uz_adcLtc2311_set_max_attempts(instance, 0);
    // cr return value now signals the acknowledgement of the update request
    uint32_t cr_return_value = cr_write_value & ~(UZ_ADCLTC2311_CR_CONV_VALUE_VALID);
    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS, cr_return_value);
}

/**
 * @brief Setup instance for operation parameter update failure
 * -> return no acknowledgement
 * 
 * @param instance 
 * @param cr_write_value Value that is expected wo be written to the CR register
 * @param max_attempts Maximum number of reads from the CR with no acknowledgement before
 * the update is considered to be failed.
 */
void prepare_instance_operation_param_update_hw_failure(
    uz_adcLtc2311_t* instance,
    uint32_t cr_write_value,
    uint32_t max_attempts)
{
    uz_adcLtc2311_hw_write_cr_Expect(TEST_BASE_ADDRESS, cr_write_value);
    uz_adcLtc2311_set_max_attempts(instance, max_attempts);
    // cr return value does not signal the acknowledgement of the update request
    uint32_t cr_return_value = cr_write_value  | UZ_ADCLTC2311_CR_CONV_VALUE_VALID;

    // expect the software to call the read function max_attempts times
    for(uint32_t i = 0; i < max_attempts; i++)
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
    int32_t conversion_factor = 10;
    uint32_t cr_return_value = 0x0;
    uint32_t cr_write_value = cr_return_value;
    int32_t function_return_value = UZ_FAILURE;
    // setup the expected values
    // see the function implementation for more details
    cr_write_value &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_write_value |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_0;
    
    uz_adcLtc2311_t* instance = successfull_init(config);

    // prepare instance for test cases
    prepare_instance_operation_param_update(instance, cr_return_value, true);

    // expect the software to write the conversion factor
    uz_adcLtc2311_set_conversion_factor(instance, conversion_factor);
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, conversion_factor);

    // expect successfull update
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
    int32_t conversion_factor = 10;
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
    prepare_instance_operation_param_update(instance, cr_return_value, true);

    // expect the software to write the conversion factor
    uz_adcLtc2311_set_conversion_factor(instance, conversion_factor);
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, conversion_factor);

    // expect update to fail (no acknowledgement)
    prepare_instance_operation_param_update_hw_failure(instance, cr_write_value, max_attempts);

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
    uint32_t cr_return_value = 0x0;
    uint32_t cr_write_value = cr_return_value;
    int32_t function_return_value = UZ_FAILURE;
    // setup the expected values
    // see the function implementation for more details
    cr_write_value &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_write_value |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID;
    
    uz_adcLtc2311_t* instance = successfull_init(config);

    // prepare instance for test cases
    prepare_instance_operation_param_update(instance, cr_return_value, true);

    // expect the software to write the conversion factor
    uz_adcLtc2311_set_offset(instance, offset);
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, offset);

    // expect successfull update
    prepare_instance_operation_param_update_hw_success(instance, cr_write_value);

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
    uint32_t max_attempts = 1;
    uint32_t cr_return_value = 0x0;
    uint32_t cr_write_value = cr_return_value;
    int32_t function_return_value = UZ_FAILURE;
    // setup the expected values
    // see the function implementation for more details
    cr_write_value &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_write_value |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID;
    
    uz_adcLtc2311_t* instance = successfull_init(config);

    // prepare instance for test cases
    prepare_instance_operation_param_update(instance, cr_return_value, true);

    // expect the software to write the conversion factor
    uz_adcLtc2311_set_offset(instance, offset);
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, offset);

    // expect update to fail (no acknowledgement)
    prepare_instance_operation_param_update_hw_failure(instance, cr_write_value, max_attempts);

    function_return_value = uz_adcLtc2311_update_offset(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_FAILURE);
}

void test_uz_adcLtc2311_update_samples(void)
{
    uint32_t samples = 2147483647;
    uint32_t cr_return_value = 0x0;
    uint32_t cr_write_value = cr_return_value;
    int32_t function_return_value = UZ_FAILURE;
    // setup the expected values
    // see the function implementation for more details
    cr_write_value &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_write_value |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_1;
    
    uz_adcLtc2311_t* instance = successfull_init(config);

    // prepare instance for test cases
    prepare_instance_operation_param_update(instance, cr_return_value, false);

    // expect the software to write the conversion factor
    uz_adcLtc2311_set_samples(instance, samples);
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, samples);

    // expect successfull update
    prepare_instance_operation_param_update_hw_success(instance, cr_write_value);

    function_return_value = uz_adcLtc2311_update_samples(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_SUCCESS);
}


/**
 * @brief Test hardware failure in case of samples update
 * 
 */
void test_uz_adcLtc2311_update_samples_hw_failure(void)
{
    uint32_t samples = 15;
    uint32_t max_attempts = 1;
    uint32_t cr_return_value = 0x0;
    uint32_t cr_write_value = cr_return_value;
    int32_t function_return_value = UZ_FAILURE;
    // setup the expected values
    // see the function implementation for more details
    cr_write_value &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_write_value |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_1;
    
    uz_adcLtc2311_t* instance = successfull_init(config);

    // prepare instance for test cases
    prepare_instance_operation_param_update(instance, cr_return_value, false);

    // expect the software to write the conversion factor
    uz_adcLtc2311_set_samples(instance, samples);
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, samples);

    // expect update to fail (no acknowledgement)
    prepare_instance_operation_param_update_hw_failure(instance, cr_write_value, max_attempts);

    function_return_value = uz_adcLtc2311_update_samples(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_FAILURE);
}

void test_uz_adcLtc2311_update_sample_time(void)
{
    uint32_t sample_time = 25;
    uint32_t cr_return_value = 0x0;
    uint32_t cr_write_value = cr_return_value;
    int32_t function_return_value = UZ_FAILURE;
    // setup the expected values
    // see the function implementation for more details
    cr_write_value &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_write_value |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_0;
    
    uz_adcLtc2311_t* instance = successfull_init(config);

    // prepare instance for test cases
    prepare_instance_operation_param_update(instance, cr_return_value, false);

    // expect the software to write the conversion factor
    uz_adcLtc2311_set_sample_time(instance, sample_time);
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, sample_time);

    // expect successfull update
    prepare_instance_operation_param_update_hw_success(instance, cr_write_value);

    function_return_value = uz_adcLtc2311_update_sample_time(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_SUCCESS);
}


/**
 * @brief Test hardware failure in case of sample_time update
 * 
 */
void test_uz_adcLtc2311_update_sample_time_hw_failure(void)
{
    uint32_t sample_time = 25;
    uint32_t max_attempts = 10;
    uint32_t cr_return_value = 0x0;
    uint32_t cr_write_value = cr_return_value;
    int32_t function_return_value = UZ_FAILURE;
    // setup the expected values
    // see the function implementation for more details
    cr_write_value &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    cr_write_value |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_0;
    
    uz_adcLtc2311_t* instance = successfull_init(config);

    // prepare instance for test cases
    prepare_instance_operation_param_update(instance, cr_return_value, false);

    // expect the software to write the conversion factor
    uz_adcLtc2311_set_sample_time(instance, sample_time);
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, sample_time);

    // expect update to fail (no acknowledgement)
    prepare_instance_operation_param_update_hw_failure(instance, cr_write_value, max_attempts);

    function_return_value = uz_adcLtc2311_update_sample_time(instance);
    TEST_ASSERT_EQUAL(function_return_value, UZ_FAILURE);
}

void test_uz_adcLtc2311_set_pre_delay_to_big(void)
{
    uz_adcLtc2311_t* instance = successfull_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_pre_delay(instance, (1 << (UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_WIDTH))));
}

void test_uz_adcLtc2311_set_post_delay_to_big(void)
{
    uz_adcLtc2311_t* instance = successfull_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_post_delay(instance, (1 << (UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_WIDTH))));
}

void test_uz_adcLtc2311_set_clk_div_to_big(void)
{
    uz_adcLtc2311_t* instance = successfull_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_clk_div(instance, (1 << (UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_WIDTH))));
}

void test_uz_adcLtc2311_set_cpha_one(void)
{
    uz_adcLtc2311_t* instance = successfull_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_cpha(instance, 1));
}

void test_uz_adcLtc2311_set_cpol_zero(void)
{
    uz_adcLtc2311_t* instance = successfull_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_set_cpol(instance, 0));
}

void test_uz_adcLtc2311_update_spi(void)
{
    uint32_t pre_delay = 10;
    uint32_t post_delay = 5;
    uint32_t clk_div = 20;
    // set another bit for testing purposes
    uint32_t spi_cr_content = UZ_ADCLTC2311_SPI_CR_SS_N;
    uz_adcLtc2311_t* instance = successfull_init(config);
    uz_adcLtc2311_set_pre_delay(instance, pre_delay);
    uz_adcLtc2311_set_post_delay(instance, post_delay);
    uz_adcLtc2311_set_clk_div(instance, clk_div);
    uz_adcLtc2311_set_cpha(instance, 0);
    uz_adcLtc2311_set_cpol(instance, 1);

    // values are concatenated in the SPI configuration register
    uint32_t spi_cfgr = (clk_div << UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_LSB) |
                        (pre_delay << UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_LSB) | 
	                    (post_delay << UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_LSB); 
    uz_adcLtc2311_hw_write_spi_cfgr_Expect(TEST_BASE_ADDRESS, spi_cfgr);

    uz_adcLtc2311_hw_read_spi_cr_ExpectAndReturn(TEST_BASE_ADDRESS, spi_cr_content);
    uint32_t spi_cr_write = spi_cr_content | UZ_ADCLTC2311_SPI_CR_CPOL;
    spi_cr_write = spi_cr_write & ~(UZ_ADCLTC2311_SPI_CR_CPHA);
    uz_adcLtc2311_hw_write_spi_cr_Expect(TEST_BASE_ADDRESS, spi_cr_write);
    uz_adcLtc2311_update_spi(instance);
}

#endif // TEST
