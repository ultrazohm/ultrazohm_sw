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

void uz_mlp_three_layer_hw_write_input_unsafe(uint32_t base_address, uz_array_int32_t* input_data)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(input_data->length==8U);
    int32_t buffer[8U] = {0};
    for (uint32_t i = 0U; i < input_data->length; i++)
    {
        buffer[i] = saturate_to_int16(input_data->data[i]);
    }
#pragma GCC diagnostic push // http://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast" // base address is uint32_t, axi_x_input is unsigned int, void is 4 or 8 byte depending if the code runs in the test environment or UZ - thus suppress this warning
        memcpy((void *)(base_address + dac_data_1_Data_uz_dac_spi_interface), &buffer[0], 8U * sizeof(int32_t));
#pragma GCC diagnostic pop
}

static int32_t saturate_to_int16(int32_t input)
{
    int32_t output=input;
    if (input > INT16_MAX)
    {
        output = INT16_MAX;
    }
    if (input < INT16_MIN)
    {
        output = INT16_MIN;
    }
    return output;
}