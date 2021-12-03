#include "uz_adcLtc2311_hw.h"
#include "uz_adcLtc2311_hwAdresses.h"
#include "../../uz/uz_AXI.h"

void uz_adcLtc2311_hw_write_cr(uint32_t base_address, uint32_t value)
{
	uz_assert_not_zero(base_address);
	uz_axi_write_uint32(base_address + ADC_LTC2311_CR, value);
}

void uz_adcLtc2311_hw_write_spi_cr(uint32_t base_address, uint32_t value)
{
	uz_assert_not_zero(base_address);
	uz_axi_write_uint32(base_address + ADC_LTC2311_SPI_CR, value);
}

void uz_adcLtc2311_hw_write_spi_cfgr(uint32_t base_address, uint32_t value)
{
	uz_assert_not_zero(base_address);
	uz_axi_write_uint32(base_address + ADC_LTC2311_SPI_CFGR, value);
}

void uz_adcLtc2311_hw_write_master_channel(uint32_t base_address, uint32_t value)
{
	uz_assert_not_zero(base_address);
	uz_axi_write_uint32(base_address + ADC_LTC2311_MASTER_CHANNEL, value);
}

void uz_adcLtc2311_hw_write_channel(uint32_t base_address, uint32_t value)
{
	uz_assert_not_zero(base_address);
	uz_axi_write_uint32(base_address + ADC_LTC2311_CHANNEL, value);
}

void uz_adcLtc2311_hw_write_value(uint32_t base_address, uint32_t value)
{
	uz_assert_not_zero(base_address);
	uz_axi_write_uint32(base_address + ADC_LTC2311_VALUE, value);
}

void uz_adcLtc2311_hw_write_value_signed(uint32_t base_address, int32_t value)
{
	uz_assert_not_zero(base_address);
	uz_axi_write_int32(base_address + ADC_LTC2311_VALUE, value);
}

void uz_adcLtc2311_hw_write_adc_available(uint32_t base_address, uint32_t value)
{
	uz_assert_not_zero(base_address);
	uz_axi_write_uint32(base_address + ADC_LTC2311_ADC_AVAILABLE, value);
}

// read functions

uint32_t uz_adcLtc2311_hw_read_cr(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_LTC2311_CR));
}

uint32_t uz_adcLtc2311_hw_read_spi_cr(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_LTC2311_SPI_CR));
}

uint32_t uz_adcLtc2311_hw_read_spi_cfgr(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_LTC2311_SPI_CFGR));
}

uint32_t uz_adcLtc2311_hw_read_master_channel(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_LTC2311_MASTER_CHANNEL));
}

uint32_t uz_adcLtc2311_hw_read_channel(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_LTC2311_CHANNEL));
}

uint32_t uz_adcLtc2311_hw_read_master_finish(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_LTC2311_MASTER_FINISH));
}

uint32_t uz_adcLtc2311_hw_read_master_si_finish(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_LTC2311_MASTER_SI_FINISH));
}

uint32_t uz_adcLtc2311_hw_read_master_busy(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_LTC2311_MASTER_BUSY));
}

uint32_t uz_adcLtc2311_hw_read_value(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_LTC2311_VALUE));
}

uint32_t uz_adcLtc2311_hw_read_adc_available(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_LTC2311_ADC_AVAILABLE));
}

void uz_adcLtc2311_hw_write_value_fixedpoint(uint32_t base_address, float value, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
	uz_assert_not_zero_uint32(base_address);
	uz_fixedpoint_axi_write(base_address + ADC_LTC2311_VALUE, value, fixedpoint_definition);
}
