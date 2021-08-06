#ifdef TEST

#include "unity.h"

#include "max11331_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)

#define baseaddress 0x05
void setUp(void)
{
}

void tearDown(void)
{
}

void test_max11331_hw_write_to_adc_selector(void)
{
    uz_axi_write_uint32_Expect(baseaddress+MAX11331_ADC_SELECTOR_OFFSET,5U);
    uz_max11_write_adc_selector(baseaddress,5U);
}

void test_max11331_hw_write_clk_divider(void){
    SCLK_freq_t clock_divider=f_50MHz;
    uz_axi_write_uint32_Expect(baseaddress+MAX11331_CLK_DIVISION_OFFSET,clock_divider);
    uz_max11_write_clk_divider(baseaddress,clock_divider);
}

#endif // TEST
