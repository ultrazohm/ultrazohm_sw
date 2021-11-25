#ifdef TEST
// #includes

#include "unity.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "test_assert_with_exception.h"
#include "uz_adcLtc2311_hwAdresses.h"
#include "uz_adcLtc2311_hw.h"

#include "uz_struct_helper.h"
#include "mock_uz_fixedpoint.h"

// #defines

#define TEST_BASE_ADDRESS 0x00000000F
#define TEST_RETURN       0x0

void setUp(void)
{
}

void tearDown(void)
{
}

// write function tests
void test_adcLtc2311_hw_write_cr(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + ADC_LTC2311_CR, value);
    uz_adcLtc2311_hw_write_cr(TEST_BASE_ADDRESS, value);
}

void test_adcLtc2311_hw_write_spi_cr(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + ADC_LTC2311_SPI_CR, value);
    uz_adcLtc2311_hw_write_spi_cr(TEST_BASE_ADDRESS, value);
}

void test_adcLtc2311_hw_write_spi_cfgr(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + ADC_LTC2311_SPI_CFGR, value);
    uz_adcLtc2311_hw_write_spi_cfgr(TEST_BASE_ADDRESS, value);
}

void test_adcLtc2311_hw_write_master_channel(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + ADC_LTC2311_MASTER_CHANNEL, value);
    uz_adcLtc2311_hw_write_master_channel(TEST_BASE_ADDRESS, value);
}

void test_adcLtc2311_hw_write_channel(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + ADC_LTC2311_CHANNEL, value);
    uz_adcLtc2311_hw_write_channel(TEST_BASE_ADDRESS, value);
}

void test_adcLtc2311_hw_write_value(void)
{
    uint32_t value = 0U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + ADC_LTC2311_VALUE, value);
    uz_adcLtc2311_hw_write_value(TEST_BASE_ADDRESS, value);
}

void test_adcLtc2311_hw_write_value_signed(void)
{
    int32_t value = 0;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS + ADC_LTC2311_VALUE, value);
    uz_adcLtc2311_hw_write_value_signed(TEST_BASE_ADDRESS, value);
}

void test_adcLtc2311_hw_write_adc_available(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + ADC_LTC2311_ADC_AVAILABLE, value);
    uz_adcLtc2311_hw_write_adc_available(TEST_BASE_ADDRESS, value);
}

// zero base address tests
void test_adcLtc2311_hw_write_cr_zero_base_address(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_write_cr(0, value));
}

void test_adcLtc2311_hw_write_spi_cr_zero_base_address(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_write_spi_cr(0, value));
}

void test_adcLtc2311_hw_write_spi_cfgr_zero_base_address(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_write_spi_cfgr(0, value));
}

void test_adcLtc2311_hw_write_master_channel_zero_base_address(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_write_master_channel(0, value));
}

void test_adcLtc2311_hw_write_channel_zero_base_address(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_write_channel(0, value));
}

void test_adcLtc2311_hw_write_value_zero_base_address(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_write_value(0, value));
}

void test_adcLtc2311_hw_write_value_signed_zero_base_address(void)
{
    int32_t value = TEST_RETURN;
    uz_axi_write_int32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_write_value_signed(0, value));
}

void test_adcLtc2311_hw_write_adc_available_zero_base_address(void)
{
    uint32_t value = TEST_RETURN;
    uz_axi_write_uint32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_write_adc_available(0, value));
}

// read functions

void test_adcLtc2311_hw_read_cr(void)
{
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + ADC_LTC2311_CR, TEST_RETURN);
    uz_adcLtc2311_hw_read_cr(TEST_BASE_ADDRESS);
}

void test_adcLtc2311_hw_read_spi_cr(void)
{
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + ADC_LTC2311_SPI_CR, TEST_RETURN);
    uz_adcLtc2311_hw_read_spi_cr(TEST_BASE_ADDRESS);
}

void test_adcLtc2311_hw_read_spi_cfgr(void)
{
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + ADC_LTC2311_SPI_CFGR, TEST_RETURN);
    uz_adcLtc2311_hw_read_spi_cfgr(TEST_BASE_ADDRESS);
}

void test_adcLtc2311_hw_read_master_channel(void)
{
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + ADC_LTC2311_MASTER_CHANNEL, TEST_RETURN);
    uz_adcLtc2311_hw_read_master_channel(TEST_BASE_ADDRESS);
}

void test_adcLtc2311_hw_read_channel(void)
{
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + ADC_LTC2311_CHANNEL, TEST_RETURN);
    uz_adcLtc2311_hw_read_channel(TEST_BASE_ADDRESS);
}

void test_adcLtc2311_hw_read_master_finish(void)
{
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + ADC_LTC2311_MASTER_FINISH, TEST_RETURN);
    uz_adcLtc2311_hw_read_master_finish(TEST_BASE_ADDRESS);
}

void test_adcLtc2311_hw_read_master_si_finish(void)
{
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + ADC_LTC2311_MASTER_SI_FINISH, TEST_RETURN);
    uz_adcLtc2311_hw_read_master_si_finish(TEST_BASE_ADDRESS);
}

void test_adcLtc2311_hw_read_master_busy(void)
{
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + ADC_LTC2311_MASTER_BUSY, TEST_RETURN);
    uz_adcLtc2311_hw_read_master_busy(TEST_BASE_ADDRESS);
}

void test_adcLtc2311_hw_read_value(void)
{
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + ADC_LTC2311_VALUE, TEST_RETURN);
    uz_adcLtc2311_hw_read_value(TEST_BASE_ADDRESS);
}

void test_adcLtc2311_hw_read_adc_available(void)
{
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + ADC_LTC2311_ADC_AVAILABLE, TEST_RETURN);
    uz_adcLtc2311_hw_read_adc_available(TEST_BASE_ADDRESS);
}

// zero base address tests


void test_adcLtc2311_hw_read_cr_zero_base_address(void)
{
    uz_axi_read_uint32_IgnoreAndReturn(TEST_RETURN);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_read_cr(0));
}

void test_adcLtc2311_hw_read_spi_cr_zero_base_address(void)
{
    uz_axi_read_uint32_IgnoreAndReturn(TEST_RETURN);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_read_spi_cr(0));
}

void test_adcLtc2311_hw_read_spi_cfgr_zero_base_address(void)
{
    uz_axi_read_uint32_IgnoreAndReturn(TEST_RETURN);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_read_spi_cfgr(0));
}

void test_adcLtc2311_hw_read_master_channel_zero_base_address(void)
{
    uz_axi_read_uint32_IgnoreAndReturn(TEST_RETURN);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_read_master_channel(0));
}

void test_adcLtc2311_hw_read_channel_zero_base_address(void)
{
    uz_axi_read_uint32_IgnoreAndReturn(TEST_RETURN);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_read_channel(0));
}

void test_adcLtc2311_hw_read_master_finish_zero_base_address(void)
{
    uz_axi_read_uint32_IgnoreAndReturn(TEST_RETURN);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_read_master_finish(0));
}

void test_adcLtc2311_hw_read_master_si_finish_zero_base_address(void)
{
    uz_axi_read_uint32_IgnoreAndReturn(TEST_RETURN);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_read_master_si_finish(0));
}

void test_adcLtc2311_hw_read_master_busy_zero_base_address(void)
{
    uz_axi_read_uint32_IgnoreAndReturn(TEST_RETURN);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_read_master_busy(0));
}

void test_adcLtc2311_hw_read_value_zero_base_address(void)
{
    uz_axi_read_uint32_IgnoreAndReturn(TEST_RETURN);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_read_value(0));
}

void test_adcLtc2311_hw_read_adc_available_zero_base_address(void)
{
    uz_axi_read_uint32_IgnoreAndReturn(TEST_RETURN);
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_hw_read_adc_available(0));
}

void test_adcLtc2311_hw_write_value_fixedpoint(void){
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .is_signed=true,
        .integer_bits=10,
        .fractional_bits=10
    };

    float conversion_factor=1.3f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+ADC_LTC2311_VALUE,conversion_factor,fixedpoint_definition);
    uz_adcLtc2311_hw_write_value_fixedpoint(TEST_BASE_ADDRESS, conversion_factor, fixedpoint_definition);
}

#endif // TEST
