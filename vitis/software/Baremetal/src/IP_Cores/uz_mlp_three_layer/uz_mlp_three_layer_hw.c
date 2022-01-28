#include "uz_mlp_three_layer_hw.h"
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"
#include <math.h>

#define MAX_VALUE_10_BIT 1024U
#define MAX_VALUE_8_BIT 256U

// Since the outputs are
static const uint32_t output_offset_addresses[8] = {
    axi_nn_output_Data_uz_mlp_three_layer + (0U * 0x4U),
    axi_nn_output_Data_uz_mlp_three_layer + (1U * 0x4U),
    axi_nn_output_Data_uz_mlp_three_layer + (2U * 0x4U),
    axi_nn_output_Data_uz_mlp_three_layer + (3U * 0x4U),
    axi_nn_output_Data_uz_mlp_three_layer + (4U * 0x4U),
    axi_nn_output_Data_uz_mlp_three_layer + (5U * 0x4U),
    axi_nn_output_Data_uz_mlp_three_layer + (6U * 0x4U),
    axi_nn_output_Data_uz_mlp_three_layer + (7U * 0x4U)};

void uz_mlp_three_layer_hw_write_enable_nn(uint32_t base_address, bool trigger_conversion)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + enable_nn_Data_uz_mlp_three_layer, trigger_conversion);
}

void uz_mlp_three_layer_hw_write_bias_data(uint32_t base_address, float value)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};
    uz_fixedpoint_axi_write(base_address + axi_bias_Data_uz_mlp_three_layer, value, fixedpoint_definition);
}

void uz_mlp_three_layer_hw_write_weight_data(uint32_t base_address, float value)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};
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

void uz_mlp_three_layer_hw_write_enable_bias(uint32_t base_address, bool write_enable_bias)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + axi_wrEnBias_Data_uz_mlp_three_layer, write_enable_bias);
}

void uz_mlp_three_layer_hw_write_enable_weights(uint32_t base_address, bool write_enable_weights)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + axi_wrEnWeights_Data_uz_mlp_three_layer, write_enable_weights);
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
    uz_assert(number_of_inputs > 1);
    uz_assert(number_of_inputs < 17);
    uz_axi_write_uint32(base_address + axi_number_of_inputs_Data_uz_mlp_three_layer, number_of_inputs);
}

void uz_mlp_three_layer_hw_write_number_of_outputs(uint32_t base_address, uint32_t number_of_outputs)
{
    uz_assert_not_zero_uint32(base_address);
    bool correct_outputs = (number_of_outputs == 2) || (number_of_outputs == 4) || (number_of_outputs == 6) || (number_of_outputs == 8);
    uz_assert(correct_outputs);
    uz_axi_write_uint32(base_address + axi_output_number_configuration_Data_uz_mlp_three_layer, ((number_of_outputs / 2U) - 1U));
}

void uz_mlp_three_layer_hw_write_input(uint32_t base_address, uz_array_float_t input_data)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(input_data.length > 1U);
    uz_assert(input_data.length < 17U);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};
    for (uint32_t i = 0; i < input_data.length; i++)
    {
        uint32_t offset_address = axi_x_input_Data_uz_mlp_three_layer + (0x4U * i);
        uz_fixedpoint_axi_write((base_address + offset_address), input_data.data[i], fixedpoint_definition);
    }
    uz_axi_write_bool(base_address + axi_x_input_Strobe_uz_mlp_three_layer, true);
}

void uz_mlp_three_layer_hw_read_output(uint32_t base_address, uz_array_float_t output_data)
{
    uz_assert_not_zero_uint32(base_address);
    bool correct_outputs = (output_data.length == 2) || (output_data.length == 4) || (output_data.length == 6) || (output_data.length == 8);
    uz_assert(correct_outputs);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};
    uz_axi_write_bool(base_address + axi_nn_output_Strobe_uz_mlp_three_layer, true);
    // First, the first half of the output data is read and set to the output
    for (uint32_t i = 0; i < (output_data.length / 2U); i++)
    {
        uint32_t offset_address = axi_nn_output_Data_uz_mlp_three_layer + (0x4U * i);
        output_data.data[i] = uz_fixedpoint_axi_read(base_address + offset_address, fixedpoint_definition);
    }
    // Second, the later half is read, which starts at output 5 (index 4) of the output vector, therefore an offset of 0x4*4 is added
    for (uint32_t i = 0; i < (output_data.length / 2U); i++)
    {
        uint32_t offset_address = axi_nn_output_Data_uz_mlp_three_layer + (0x4U * i)+ 0x10U;
        output_data.data[(output_data.length / 2U)+i] = uz_fixedpoint_axi_read(base_address + offset_address, fixedpoint_definition);
    }
}
