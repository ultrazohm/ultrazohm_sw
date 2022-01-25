#ifdef TEST

#include "unity.h"

#include "uz_mlp_three_layer_hw.h"
#include <stdbool.h>
#include <stdint.h>
#include "mock_uz_fixedpoint.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_mlp_three_layer_addr.h"
#include "uz_struct_helper.h"

#define BASE_ADDRESS 0x00000000FU // random hex value that represents a fictional base address

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
    uz_mlp_three_layer_hw_write_bias_data(BASE_ADDRESS, bias_data, def);
}

void test_uz_mlp_three_layer_hw_write_weight_data(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 14,
        .integer_bits = 18};
    float weight_data = 123.131f;
    uz_fixedpoint_axi_write_Expect(BASE_ADDRESS + axi_weight_Data_uz_mlp_three_layer, weight_data, def);
    uz_mlp_three_layer_hw_write_weight_data(BASE_ADDRESS, weight_data, def);
}

void test_uz_mlp_three_layer_hw_write_weight_address(void)
{
    uint32_t weight_address=10U;
    uz_axi_write_uint32(BASE_ADDRESS + axi_weight_Data_uz_mlp_three_layer, weight_address);
    uz_mlp_three_layer_hw_write_weight_address(BASE_ADDRESS, weight_address);
}









#endif // TEST
