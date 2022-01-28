#ifdef TEST

#include "unity.h"

#include "uz_mlp_three_layer_hw.h"
#include <stdbool.h>
#include <stdint.h>
#include "test_assert_with_exception.h"
#include "mock_uz_fixedpoint.h"
#include "uz_array.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_mlp_three_layer_addr.h"
#include "uz_struct_helper.h"

#define BASE_ADDRESS 0x0F0000000U // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_mlp_three_layer_hw_write_enable_nn(void)
{
    bool enable_signal = true;
    uz_axi_write_bool_Expect(BASE_ADDRESS + enable_nn_Data_uz_mlp_three_layer, enable_signal);
    uz_mlp_three_layer_hw_write_enable_nn(BASE_ADDRESS, enable_signal);
}

void test_uz_mlp_three_layer_hw_write_bias_data(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};
    float bias_data = 123.131f;
    uz_fixedpoint_axi_write_Expect(BASE_ADDRESS + axi_bias_Data_uz_mlp_three_layer, bias_data, def);
    uz_mlp_three_layer_hw_write_bias_data(BASE_ADDRESS, bias_data);
}

void test_uz_mlp_three_layer_hw_write_weight_data(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};
    float weight_data = 123.131f;
    uz_fixedpoint_axi_write_Expect(BASE_ADDRESS + axi_weight_Data_uz_mlp_three_layer, weight_data, def);
    uz_mlp_three_layer_hw_write_weight_data(BASE_ADDRESS, weight_data);
}

void test_uz_mlp_three_layer_hw_write_weight_address(void)
{
    uint32_t weight_address = 10U;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + axi_weight_addr_Data_uz_mlp_three_layer, weight_address);
    uz_mlp_three_layer_hw_write_weight_address(BASE_ADDRESS, weight_address);
}

void test_uz_mlp_three_layer_hw_write_bias_address(void)
{
    uint32_t bias_address = 10U;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + axi_bias_addr_Data_uz_mlp_three_layer, bias_address);
    uz_mlp_three_layer_hw_write_bias_address(BASE_ADDRESS, bias_address);
}

void test_uz_mlp_three_layer_hw_write_enable_bias(void)
{
    bool write_bias = true;
    uz_axi_write_bool_Expect(BASE_ADDRESS + axi_wrEnBias_Data_uz_mlp_three_layer, write_bias);
    uz_mlp_three_layer_hw_write_enable_bias(BASE_ADDRESS, write_bias);
}

void test_uz_mlp_three_layer_hw_write_enable_weight(void)
{
    bool write_weight = true;
    uz_axi_write_bool_Expect(BASE_ADDRESS + axi_wrEnWeights_Data_uz_mlp_three_layer, write_weight);
    uz_mlp_three_layer_hw_write_enable_weights(BASE_ADDRESS, write_weight);
}

void test_uz_mlp_three_layer_hw_write_layerNr(void)
{
    uint32_t layer_nr = 10U;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + axi_layerNr_Data_uz_mlp_three_layer, layer_nr);
    uz_mlp_three_layer_hw_write_layerNr(BASE_ADDRESS, layer_nr);
}

void test_uz_mlp_three_layer_hw_write_use_axi_input(void)
{
    bool use_axi_input = true;
    uz_axi_write_bool_Expect(BASE_ADDRESS + use_axi_input_Data_uz_mlp_three_layer, use_axi_input);
    uz_mlp_three_layer_hw_write_use_axi_input(BASE_ADDRESS, use_axi_input);
}

void test_uz_mlp_three_layer_hw_read_valid_output(void)
{
    bool expected_return = true;
    uz_axi_read_bool_ExpectAndReturn(BASE_ADDRESS + axi_valid_output_Data_uz_mlp_three_layer, expected_return);
    bool actual_return = uz_mlp_three_layer_hw_read_valid_output(BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expected_return, actual_return);
}

void test_uz_mlp_three_layer_hw_write_number_of_inputs(void)
{
    uint32_t number_of_inputs = 2U;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + axi_number_of_inputs_Data_uz_mlp_three_layer, number_of_inputs);
    uz_mlp_three_layer_hw_write_number_of_inputs(BASE_ADDRESS, number_of_inputs);
}

void test_uz_mlp_three_layer_hw_write_number_of_inputs_fail_input_too_low(void)
{
    uint32_t number_of_inputs = 1U;
    TEST_ASSERT_FAIL_ASSERT(uz_mlp_three_layer_hw_write_number_of_inputs(BASE_ADDRESS, number_of_inputs));
}

void test_uz_mlp_three_layer_hw_write_number_of_inputs_fail_input_too_high(void)
{
    uint32_t number_of_inputs = 17U;
    TEST_ASSERT_FAIL_ASSERT(uz_mlp_three_layer_hw_write_number_of_inputs(BASE_ADDRESS, number_of_inputs));
}

void test_uz_mlp_three_layer_hw_number_of_outputs(void)
{
    uint32_t number_of_outputs = 2U;
    // Number of outputs has to be written as (number_of_outputs/2-1)
    uz_axi_write_uint32_Expect(BASE_ADDRESS + axi_output_number_configuration_Data_uz_mlp_three_layer, ((number_of_outputs / 2) - 1));
    uz_mlp_three_layer_hw_write_number_of_outputs(BASE_ADDRESS, number_of_outputs);
}

void test_uz_mlp_three_layer_hw_number_of_outputs_fail_wrong_output_number(void)
{
    uint32_t number_of_outputs = 3U;
    TEST_ASSERT_FAIL_ASSERT(uz_mlp_three_layer_hw_write_number_of_outputs(BASE_ADDRESS, number_of_outputs));
}

void test_uz_mlp_three_layer_hw_write_input(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};

    float data[4] = {1, 2, 3, 4};
    uz_array_float_t input_data = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]};
    // The input are up to 16 values, each register for the values has to add +0x4
    uz_fixedpoint_axi_write_Expect(BASE_ADDRESS + axi_x_input_Data_uz_mlp_three_layer, data[0], def);
    uz_fixedpoint_axi_write_Expect(BASE_ADDRESS + axi_x_input_Data_uz_mlp_three_layer + 0x4U, data[1], def);
    uz_fixedpoint_axi_write_Expect(BASE_ADDRESS + axi_x_input_Data_uz_mlp_three_layer + 0x8U, data[2], def);
    uz_fixedpoint_axi_write_Expect(BASE_ADDRESS + axi_x_input_Data_uz_mlp_three_layer + 0xCU, data[3], def);

    // Set strobe to true, should be reset by the IP-Core - not sure!
    uz_axi_write_bool_Expect(BASE_ADDRESS + axi_x_input_Strobe_uz_mlp_three_layer, true);
    uz_mlp_three_layer_hw_write_input(BASE_ADDRESS, input_data);
}

void test_uz_mlp_three_layer_hw_write_input_fail_only_one_input(void)
{
    float data[1] = {1};
    uz_array_float_t input_data = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]};
    TEST_ASSERT_FAIL_ASSERT(uz_mlp_three_layer_hw_write_input(BASE_ADDRESS, input_data));
}

void test_uz_mlp_three_layer_hw_write_input_fail_too_many_inputs(void)
{
    float data[17] = {0};
    uz_array_float_t input_data = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]};
    TEST_ASSERT_FAIL_ASSERT(uz_mlp_three_layer_hw_write_input(BASE_ADDRESS, input_data));
}

void test_uz_mlp_three_layer_read_output_two(void)
{
    float expected_output[2] = {1.1f, 1.3f};
    float data[2] = {0};
    uz_array_float_t output_data = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]};

    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};

    // First trigger the strobe register, then read the data
    uz_axi_write_bool_Expect(BASE_ADDRESS + axi_nn_output_Strobe_uz_mlp_three_layer, true);
    // There are 8 output registers:
    // Output 1: 0x1A0 (axi_nn_output_Data_uz_mlp_three_layer)
    // Output 2: 0x1A4
    // Output 3: 0x1A8
    // Output 4: 0x1AC
    // Output 5: 0x1B0
    // Output 6: 0x1B4
    // Output 7: 0x1B8
    // Output 8: 0x1BC
    // If only two outputs are read, output 1 and output 4 are expected to be read
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + axi_nn_output_Data_uz_mlp_three_layer, def, expected_output[0]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + 0x1B0, def, expected_output[1]);

    uz_mlp_three_layer_hw_read_output(BASE_ADDRESS, output_data);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_output, data, UZ_ARRAY_SIZE(expected_output));
}

void test_uz_mlp_three_layer_read_output_four(void)
{
    float expected_output[4] = {1.1f, 1.3f, 2.3f, 13.2f};
    float data[4] = {0};
    uz_array_float_t output_data = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]};

    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};

    // First trigger the strobe register, then read the data
    uz_axi_write_bool_Expect(BASE_ADDRESS + axi_nn_output_Strobe_uz_mlp_three_layer, true);
    // There are 8 output registers:
    // Output 1: 0x1A0 (axi_nn_output_Data_uz_mlp_three_layer)
    // Output 2: 0x1A4
    // Output 3: 0x1A8
    // Output 4: 0x1AC
    // Output 5: 0x1B0
    // Output 6: 0x1B4
    // Output 7: 0x1B8
    // Output 8: 0x1BC
    const uint32_t output_1_register_address = axi_nn_output_Data_uz_mlp_three_layer;
    const uint32_t output_2_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U;
    const uint32_t output_3_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U;
    const uint32_t output_4_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U;
    const uint32_t output_5_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U;
    const uint32_t output_6_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U;
    const uint32_t output_7_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U;
    const uint32_t output_8_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U;
    // If four outputs are read, output 1,2,4, and 5 expected to be read
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_1_register_address, def, expected_output[0]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_2_register_address, def, expected_output[1]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_5_register_address, def, expected_output[2]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_6_register_address, def, expected_output[3]);

    uz_mlp_three_layer_hw_read_output(BASE_ADDRESS, output_data);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_output, data, UZ_ARRAY_SIZE(expected_output));
}

void test_uz_mlp_three_layer_read_output_six(void)
{
    float expected_output[6] = {1.1f, 1.3f, 2.3f, 13.2f, 12312.1233f, 3.2f};
    float data[6] = {0};
    uz_array_float_t output_data = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]};

    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};

    // First trigger the strobe register, then read the data
    uz_axi_write_bool_Expect(BASE_ADDRESS + axi_nn_output_Strobe_uz_mlp_three_layer, true);
    // There are 8 output registers:
    // Output 1: 0x1A0 (axi_nn_output_Data_uz_mlp_three_layer)
    // Output 2: 0x1A4
    // Output 3: 0x1A8
    // Output 4: 0x1AC
    // Output 5: 0x1B0
    // Output 6: 0x1B4
    // Output 7: 0x1B8
    // Output 8: 0x1BC
    const uint32_t output_1_register_address = axi_nn_output_Data_uz_mlp_three_layer;
    const uint32_t output_2_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U;
    const uint32_t output_3_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U;
    const uint32_t output_4_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U;
    const uint32_t output_5_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U;
    const uint32_t output_6_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U;
    const uint32_t output_7_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U;
    const uint32_t output_8_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U;
    // If four outputs are read, output 1,2,3,4,5, and 6 expected to be read
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_1_register_address, def, expected_output[0]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_2_register_address, def, expected_output[1]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_3_register_address, def, expected_output[2]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_5_register_address, def, expected_output[3]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_6_register_address, def, expected_output[4]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_7_register_address, def, expected_output[5]);

    uz_mlp_three_layer_hw_read_output(BASE_ADDRESS, output_data);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_output, data, UZ_ARRAY_SIZE(expected_output));
}

void test_uz_mlp_three_layer_read_output_eight(void)
{
    float expected_output[8] = {1.1f, 1.3f, 2.3f, 13.2f, 12312.1233f, 3.2f, 71.1f, 123.1f};
    float data[8] = {0};
    uz_array_float_t output_data = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]};

    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};

    // First trigger the strobe register, then read the data
    uz_axi_write_bool_Expect(BASE_ADDRESS + axi_nn_output_Strobe_uz_mlp_three_layer, true);
    // There are 8 output registers:
    // Output 1: 0x1A0 (axi_nn_output_Data_uz_mlp_three_layer)
    // Output 2: 0x1A4
    // Output 3: 0x1A8
    // Output 4: 0x1AC
    // Output 5: 0x1B0
    // Output 6: 0x1B4
    // Output 7: 0x1B8
    // Output 8: 0x1BC
    const uint32_t output_1_register_address = axi_nn_output_Data_uz_mlp_three_layer;
    const uint32_t output_2_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U;
    const uint32_t output_3_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U;
    const uint32_t output_4_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U;
    const uint32_t output_5_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U;
    const uint32_t output_6_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U;
    const uint32_t output_7_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U;
    const uint32_t output_8_register_address = axi_nn_output_Data_uz_mlp_three_layer + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U + 0x4U;
    // If only two outputs are read, output 1 and output 4 are expected to be read
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_1_register_address, def, expected_output[0]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_2_register_address, def, expected_output[1]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_3_register_address, def, expected_output[2]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_4_register_address, def, expected_output[3]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_5_register_address, def, expected_output[4]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_6_register_address, def, expected_output[5]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_7_register_address, def, expected_output[6]);
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS + output_8_register_address, def, expected_output[7]);

    uz_mlp_three_layer_hw_read_output(BASE_ADDRESS, output_data);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_output, data, UZ_ARRAY_SIZE(expected_output));
}

#endif // TEST
