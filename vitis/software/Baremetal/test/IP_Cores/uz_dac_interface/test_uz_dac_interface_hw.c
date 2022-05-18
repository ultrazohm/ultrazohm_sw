#ifdef TEST

#include "unity.h"

#include "uz_dac_interface_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h"
#include "uz_dac_spi_interface_addr.h"
#include <stdbool.h>
#include <limits.h>

#define TEST_BASE_ADDRESS 0x0F0F0000F

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_dac_interface_hw_trigger_send_data(void)
{
    bool enable=true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+trigger_write_Data_uz_dac_spi_interface,enable);
    uz_dac_interface_hw_write_trigger(TEST_BASE_ADDRESS,enable);
}

void test_uz_dac_interface_hw_write_dac1(void)
{
    int32_t value=100;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+dac_data_1_Data_uz_dac_spi_interface,value);
    uz_dac_interface_hw_write_dac1(TEST_BASE_ADDRESS,value);
}

void test_uz_dac_interface_hw_write_dac1_overflow(void)
{
    // In hardware, the DAC has 16 bits but the AXI register writes 32-bits.
    // If the function is called with a value greater than MAX(int16), the value should be just limited to MAX(int16)
    // This is done here compared to an assertion triggering since just limiting to the max value prevents bugs from float rounding
    int32_t value=UINT16_MAX+1; 
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+dac_data_1_Data_uz_dac_spi_interface,UINT16_MAX);
    uz_dac_interface_hw_write_dac1(TEST_BASE_ADDRESS,value);
}

void test_uz_dac_interface_hw_write_dac1_underflow(void)
{
    // Same as int16 overflow but with negative values
    int32_t value=0-10; 
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+dac_data_1_Data_uz_dac_spi_interface,0);
    uz_dac_interface_hw_write_dac1(TEST_BASE_ADDRESS,value);
}

void test_uz_dac_interface_hw_write_dac2(void)
{
    int32_t value=100;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+dac_data_2_Data_uz_dac_spi_interface,value);
    uz_dac_interface_hw_write_dac2(TEST_BASE_ADDRESS,value);
}

void test_uz_dac_interface_hw_write_dac3(void)
{
    int32_t value=100;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+dac_data_3_Data_uz_dac_spi_interface,value);
    uz_dac_interface_hw_write_dac3(TEST_BASE_ADDRESS,value);
}

void test_uz_dac_interface_hw_write_dac4(void)
{
    int32_t value=100;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+dac_data_4_Data_uz_dac_spi_interface,value);
    uz_dac_interface_hw_write_dac4(TEST_BASE_ADDRESS,value);
}

void test_uz_dac_interface_hw_write_dac5(void)
{
    int32_t value=100;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+dac_data_5_Data_uz_dac_spi_interface,value);
    uz_dac_interface_hw_write_dac5(TEST_BASE_ADDRESS,value);
}

void test_uz_dac_interface_hw_write_dac6(void)
{
    int32_t value=100;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+dac_data_6_Data_uz_dac_spi_interface,value);
    uz_dac_interface_hw_write_dac6(TEST_BASE_ADDRESS,value);
}

void test_uz_dac_interface_hw_write_dac7(void)
{
    int32_t value=100;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+dac_data_7_Data_uz_dac_spi_interface,value);
    uz_dac_interface_hw_write_dac7(TEST_BASE_ADDRESS,value);
}

void test_uz_dac_interface_hw_write_dac8(void)
{
    int32_t value=100;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+dac_data_8_Data_uz_dac_spi_interface,value);
    uz_dac_interface_hw_write_dac8(TEST_BASE_ADDRESS,value);
}




#endif // TEST
