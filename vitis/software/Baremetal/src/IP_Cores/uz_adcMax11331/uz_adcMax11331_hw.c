#include "uz_adcMax11331_hw.h"
#include "uz_adcMax11331_hwAdresses.h"
#include "../../uz/uz_AXI.h"

void uz_adcMax11331_hw_write_spi_cfgr(uint32_t base_address, uint32_t value)
{
	uz_assert_not_zero(base_address);
	//_write_clk_divider to generate SPI clock
	//The SPI clk  is generated internally by logic of a clock divider. Based on 100MHz IP Core clock, a clock divider of 1 gives 50Mhz, 2 gives 25Mhz, 3 gives 16,6MHz and so on...
	//The SPI clk is given by IP-Core clk frequency ( (2^(clock divider))
	uz_axi_write_uint32(base_address+ADC_MAX11331_CLK_DIVISION,value);
}

void uz_adcMax11331_hw_write_master_channel(uint32_t base_address, uint32_t value)
{
	uz_assert_not_zero(base_address);
	uz_axi_write_uint32(base_address + ADC_MAX11331_ADCSELECTOR_FORCEINIT, value);
}

// read functions

uint32_t uz_adcMax11331_hw_read_spi_cfgr(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_MAX11331_CLK_DIVISION));
}

uint32_t uz_adcMax11331_hw_read_master_channel(uint32_t base_address)
{
	uz_assert_not_zero(base_address);
	return (uz_axi_read_uint32(base_address + ADC_MAX11331_ADCSELECTOR_FORCEINIT));
}

