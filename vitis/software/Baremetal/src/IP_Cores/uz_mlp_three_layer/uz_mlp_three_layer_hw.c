#include "uz_mlp_three_layer_hw.h"
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"
#include <math.h>
#include <string.h>

#define MAX_VALUE_10_BIT 1024U
#define MAX_VALUE_8_BIT 256U
#define MLP_LENGTH_OF_OUTPUT_VECTOR 8U

#define NUMBER_OF_FRACTIONAL_BITS 14
#define NUMBER_OF_INTEGER_BITS 18

void uz_mlp_three_layer_hw_write_enable_nn(uint32_t base_address, bool trigger_conversion)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + axi_enable_nn_Data_uz_mlp_three_layer, trigger_conversion);
}

void uz_mlp_three_layer_hw_write_bias_data(uint32_t base_address, float value)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = NUMBER_OF_FRACTIONAL_BITS,
        .integer_bits = NUMBER_OF_INTEGER_BITS};
    uz_fixedpoint_axi_write(base_address + axi_bias_Data_uz_mlp_three_layer, value, fixedpoint_definition);
}

void uz_mlp_three_layer_hw_write_weight_data(uint32_t base_address, float value)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = NUMBER_OF_FRACTIONAL_BITS,
        .integer_bits = NUMBER_OF_INTEGER_BITS};
    uz_fixedpoint_axi_write(base_address + axi_weight_Data_uz_mlp_three_layer, value, fixedpoint_definition);
}

void uz_mlp_three_layer_hw_write_weight_address(uint32_t base_address, uint32_t weight_address)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(weight_address <= (MAX_VALUE_10_BIT));
    uz_axi_write_uint32(base_address + axi_weight_addr_Data_uz_mlp_three_layer, weight_address);
}

void uz_mlp_three_layer_hw_write_bias_address(uint32_t base_address, uint32_t bias_address)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(bias_address <= (MAX_VALUE_10_BIT));
    uz_axi_write_uint32(base_address + axi_bias_addr_Data_uz_mlp_three_layer, bias_address);
}

void uz_mlp_three_layer_hw_write_enable_bias(uint32_t base_address, uint32_t write_enable_bias_parallel_mac_number)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(write_enable_bias_parallel_mac_number <= MAX_VALUE_10_BIT);
    uz_axi_write_uint32(base_address + axi_wrEnBias_Data_uz_mlp_three_layer, write_enable_bias_parallel_mac_number);
}

void uz_mlp_three_layer_hw_write_enable_weights(uint32_t base_address, uint32_t write_enable_bias_parallel_mac_number)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(write_enable_bias_parallel_mac_number <= MAX_VALUE_10_BIT);
    uz_axi_write_uint32(base_address + axi_wrEnWeights_Data_uz_mlp_three_layer, write_enable_bias_parallel_mac_number);
}

void uz_mlp_three_layer_hw_write_layerNr(uint32_t base_address, uint32_t layerNr)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(layerNr <= MAX_VALUE_8_BIT);
    uz_axi_write_uint32(base_address + axi_layerNr_Data_uz_mlp_three_layer, layerNr);
}

void uz_mlp_three_layer_hw_write_use_axi_input(uint32_t base_address, bool use_axi_input)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + use_axi_input_Data_uz_mlp_three_layer, use_axi_input);
}

bool uz_mlp_three_layer_hw_read_valid_output(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    return uz_axi_read_bool(base_address + axi_valid_output_Data_uz_mlp_three_layer);
}

void uz_mlp_three_layer_hw_write_number_of_inputs(uint32_t base_address, uint32_t number_of_inputs)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(number_of_inputs > 1U);
    uz_assert(number_of_inputs < 17U);
    uz_axi_write_uint32(base_address + axi_number_of_inputs_Data_uz_mlp_three_layer, number_of_inputs);
}

void uz_mlp_three_layer_hw_write_number_of_outputs(uint32_t base_address, uint32_t number_of_outputs)
{
    uz_assert_not_zero_uint32(base_address);
    bool correct_outputs = (number_of_outputs == 2U) || (number_of_outputs == 4U) || (number_of_outputs == 6U) || (number_of_outputs == 8U);
    uz_assert(correct_outputs);
    uz_axi_write_uint32(base_address + axi_output_number_configuration_Data_uz_mlp_three_layer, ((number_of_outputs / 2U) - 1U));
}

void uz_mlp_three_layer_hw_write_input(uint32_t base_address, uz_matrix_t* input_data)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(input_data->length_of_data > 1U);
    uz_assert(input_data->length_of_data < 17U);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = NUMBER_OF_FRACTIONAL_BITS,
        .integer_bits = NUMBER_OF_INTEGER_BITS};
    for (uint32_t i = 0U; i < input_data->length_of_data; i++)
    {
        uint32_t offset_address = axi_x_input_Data_uz_mlp_three_layer + (0x4U * i);
        uz_fixedpoint_axi_write((base_address + offset_address), input_data->data[i], fixedpoint_definition);
    }
    uz_axi_write_bool(base_address + axi_x_input_Strobe_uz_mlp_three_layer, true);
}

void uz_mlp_three_layer_hw_write_input_unsafe(uint32_t base_address, uz_matrix_t* input_data)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(input_data->length_of_data > 1U);
    uz_assert(input_data->length_of_data < 17U);
    int32_t mlp_buffer[16] = {0}; // A maximum of 16 values can be written as inputs to the IP-Core, thus a buffer with max. size is used here to simplify the declaration. Its faster to just always have 16 values than determining this at runtime
    for (uint32_t i = 0U; i < input_data->length_of_data; i++)
    {
        mlp_buffer[i] = (int32_t)(input_data->data[i] * 16384); // 16384 is 2^14 to transform int32_t to float
    }
    // The performance of fixed-length memcpy is multiple microseconds faster than using ginput_data.length*sizeof(int32_t)
    // For simplicity, either 8 or 16 input values are written to the IP-Core
    // The additional input values that are written from the buffer to the IP-Core that are not set to data of input_data is just ignored by the IP-Core
    if (input_data->length_of_data < 9U)
    {
#pragma GCC diagnostic push // http://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast" // base address is uint32_t, axi_x_input is unsigned int, void is 4 or 8 byte depending if the code runs in the test environment or UZ - thus suppress this warning
        memcpy((void *)(base_address + axi_x_input_Data_uz_mlp_three_layer), &mlp_buffer[0], 8U * sizeof(int32_t));
#pragma GCC diagnostic pop
    }
    else
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
        memcpy((void *)(base_address + axi_x_input_Data_uz_mlp_three_layer), &mlp_buffer[0], 16U * sizeof(int32_t));
#pragma GCC diagnostic pop
    }
    uz_axi_write_bool(base_address + axi_x_input_Strobe_uz_mlp_three_layer, true);
}

void uz_mlp_three_layer_hw_read_output(uint32_t base_address, uz_matrix_t* output_data)
{
    uz_assert_not_zero_uint32(base_address);
    bool correct_outputs = (output_data->length_of_data == 2U) || (output_data->length_of_data == 4U) || (output_data->length_of_data == 6U) || (output_data->length_of_data == 8U);
    uz_assert(correct_outputs);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = NUMBER_OF_FRACTIONAL_BITS,
        .integer_bits = NUMBER_OF_INTEGER_BITS};
    uz_axi_write_bool(base_address + axi_nn_output_Strobe_uz_mlp_three_layer, true);
    // First, the first half of the output data is read and set to the output
    for (uint32_t i = 0; i < (output_data->length_of_data / 2U); i++)
    {
        uint32_t offset_address = axi_nn_output_Data_uz_mlp_three_layer + (0x4U * i);
        output_data->data[i] = uz_fixedpoint_axi_read(base_address + offset_address, fixedpoint_definition);
    }
    // Second, the later half is read, which starts at output 5 (index 4) of the output vector, therefore an offset of 0x4*4 is added
    for (uint32_t i = 0; i < (output_data->length_of_data / 2U); i++)
    {
        uint32_t offset_address = axi_nn_output_Data_uz_mlp_three_layer + (0x4U * i) + 0x10U;
        output_data->data[(output_data->length_of_data / 2U) + i] = uz_fixedpoint_axi_read(base_address + offset_address, fixedpoint_definition);
    }
}

void uz_mlp_three_layer_hw_read_output_unsafe(uint32_t base_address, uz_matrix_t* output_data)
{
    uz_assert_not_NULL(output_data);
    uz_assert_not_zero_uint32(base_address);
    bool correct_outputs = (output_data->length_of_data == 2U) || (output_data->length_of_data == 4U) || (output_data->length_of_data == 6U) || (output_data->length_of_data == 8U);
    uz_assert(correct_outputs);
    uz_axi_write_bool(base_address + axi_nn_output_Strobe_uz_mlp_three_layer, true);
    int32_t mlp_buffer[MLP_LENGTH_OF_OUTPUT_VECTOR] = {0};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast" 
    memcpy(&mlp_buffer[0], (void *)(base_address + axi_nn_output_Data_uz_mlp_three_layer), MLP_LENGTH_OF_OUTPUT_VECTOR * sizeof(int32_t));
#pragma GCC diagnostic pop

    // Copy+paste every entry is about 0.1us-0.2us faster than a for loop
    switch (output_data->length_of_data)
    {
    case 2:
        output_data->data[0] = ((float)mlp_buffer[0]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[1] = ((float)mlp_buffer[4]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        break;
    case 4:
        output_data->data[0] = ((float)mlp_buffer[0]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[1] = ((float)mlp_buffer[1]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[2] = ((float)mlp_buffer[4]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[3] = ((float)mlp_buffer[5]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        break;
    case 6:
        output_data->data[0] = ((float)mlp_buffer[0]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[1] = ((float)mlp_buffer[1]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[2] = ((float)mlp_buffer[2]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[3] = ((float)mlp_buffer[4]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[4] = ((float)mlp_buffer[5]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[5] = ((float)mlp_buffer[6]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        break;
    case 8:
        output_data->data[0] = ((float)mlp_buffer[0]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[1] = ((float)mlp_buffer[1]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[2] = ((float)mlp_buffer[2]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[3] = ((float)mlp_buffer[3]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[4] = ((float)mlp_buffer[4]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[5] = ((float)mlp_buffer[5]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[6] = ((float)mlp_buffer[6]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        output_data->data[7] = ((float)mlp_buffer[7]) / (1U << NUMBER_OF_FRACTIONAL_BITS);
        break;
    default:
        break;
    }
}

void uz_mlp_three_layer_hw_disable_pl_trigger(uint32_t base_address, bool disable_pl_trigger){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+disable_pl_trigger_Data_uz_mlp_three_layer,disable_pl_trigger);
}
