#include "uz_dac_interface_hw.h"
#include "uz_dac_spi_interface_addr.h"
#include "../../uz/uz_AXI.h"
#include <limits.h>
#include <string.h>

static int32_t saturate_to_int16(int32_t input);


void uz_dac_interface_hw_write_trigger(uint32_t base_address, bool trigger)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + trigger_write_Data_uz_dac_spi_interface, trigger);
}

void uz_dac_interface_hw_write_dac1(uint32_t base_address, int32_t dac_value)
{
    uz_assert_not_zero_uint32(base_address);
    dac_value=saturate_to_int16(dac_value);
    uz_axi_write_int32(base_address + dac_data_1_Data_uz_dac_spi_interface, dac_value);
}

void uz_dac_interface_hw_write_dac2(uint32_t base_address, int32_t dac_value)
{
    uz_assert_not_zero_uint32(base_address);
    dac_value=saturate_to_int16(dac_value);
    uz_axi_write_int32(base_address + dac_data_2_Data_uz_dac_spi_interface, dac_value);
}

void uz_dac_interface_hw_write_dac3(uint32_t base_address, int32_t dac_value)
{
    uz_assert_not_zero_uint32(base_address);
    dac_value=saturate_to_int16(dac_value);
    uz_axi_write_int32(base_address + dac_data_3_Data_uz_dac_spi_interface, dac_value);
}

void uz_dac_interface_hw_write_dac4(uint32_t base_address, int32_t dac_value)
{
    uz_assert_not_zero_uint32(base_address);
    dac_value=saturate_to_int16(dac_value);
    uz_axi_write_int32(base_address + dac_data_4_Data_uz_dac_spi_interface, dac_value);
}

void uz_dac_interface_hw_write_dac5(uint32_t base_address, int32_t dac_value)
{
    uz_assert_not_zero_uint32(base_address);
    dac_value=saturate_to_int16(dac_value);
    uz_axi_write_int32(base_address + dac_data_5_Data_uz_dac_spi_interface, dac_value);
}


void uz_dac_interface_hw_write_dac6(uint32_t base_address, int32_t dac_value)
{
    uz_assert_not_zero_uint32(base_address);
    dac_value=saturate_to_int16(dac_value);
    uz_axi_write_int32(base_address + dac_data_6_Data_uz_dac_spi_interface, dac_value);
}

void uz_dac_interface_hw_write_dac7(uint32_t base_address, int32_t dac_value)
{
    uz_assert_not_zero_uint32(base_address);
    dac_value=saturate_to_int16(dac_value);
    uz_axi_write_int32(base_address + dac_data_7_Data_uz_dac_spi_interface, dac_value);
}

void uz_dac_interface_hw_write_dac8(uint32_t base_address, int32_t dac_value)
{
    uz_assert_not_zero_uint32(base_address);
    dac_value=saturate_to_int16(dac_value);
    uz_axi_write_int32(base_address + dac_data_8_Data_uz_dac_spi_interface, dac_value);
}

static int32_t saturate_to_int16(int32_t input)
{
    int32_t output=input;
    if (input > UINT16_MAX)
    {
        output = UINT16_MAX;
    }
    if (input < 0)
    {
        output = 0;
    }
    return output;
}