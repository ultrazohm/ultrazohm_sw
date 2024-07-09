#include "uz_sine_generator_16bit_hw.h"
#include "uz_sine_generator_16bit_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"
#include "../../uz/uz_HAL.h"

void uz_sine_generator_16bit_hw_write_amplitude_1(uint32_t base_address, float amplitude)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 28U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + amplitude_1_Data_uz_sine_generator_16bit, amplitude, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_amplitude_2(uint32_t base_address, float amplitude)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 28U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + amplitude_2_Data_uz_sine_generator_16bit, amplitude, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_amplitude_3(uint32_t base_address, float amplitude)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 28U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + amplitude_3_Data_uz_sine_generator_16bit, amplitude, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_amplitude_4(uint32_t base_address, float amplitude)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 28U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + amplitude_4_Data_uz_sine_generator_16bit, amplitude, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_amplitude_5(uint32_t base_address, float amplitude)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 28U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + amplitude_5_Data_uz_sine_generator_16bit, amplitude, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_amplitude_6(uint32_t base_address, float amplitude)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 28U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + amplitude_6_Data_uz_sine_generator_16bit, amplitude, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_amplitude_7(uint32_t base_address, float amplitude)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 28U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + amplitude_7_Data_uz_sine_generator_16bit, amplitude, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_amplitude_8(uint32_t base_address, float amplitude)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 28U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + amplitude_8_Data_uz_sine_generator_16bit, amplitude, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_phase_1(uint32_t base_address, float phase)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 12U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + phase_shift_1_Data_uz_sine_generator_16bit, phase, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_phase_2(uint32_t base_address, float phase)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 12U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + phase_shift_2_Data_uz_sine_generator_16bit, phase, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_phase_3(uint32_t base_address, float phase)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 12U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + phase_shift_3_Data_uz_sine_generator_16bit, phase, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_phase_4(uint32_t base_address, float phase)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 12U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + phase_shift_4_Data_uz_sine_generator_16bit, phase, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_phase_5(uint32_t base_address, float phase)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 12U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + phase_shift_5_Data_uz_sine_generator_16bit, phase, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_phase_6(uint32_t base_address, float phase)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 12U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + phase_shift_6_Data_uz_sine_generator_16bit, phase, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_phase_7(uint32_t base_address, float phase)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 12U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + phase_shift_7_Data_uz_sine_generator_16bit, phase, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_phase_8(uint32_t base_address, float phase)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 12U,
        .integer_bits = 4U};
    uz_fixedpoint_axi_write(base_address + phase_shift_8_Data_uz_sine_generator_16bit, phase, fixedpoint_definition);
}

void uz_sine_generator_16bit_hw_write_frequency_1(uint32_t base_address, float frequency)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(frequency>0.0f);
    uint32_t frq = (uint32_t)frequency;
    uz_axi_write_uint32(base_address + frequency_1_Data_uz_sine_generator_16bit,frq);
}

void uz_sine_generator_16bit_hw_write_frequency_2(uint32_t base_address, float frequency)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(frequency > 0.0f);
    uint32_t frq = (uint32_t)frequency;
    uz_axi_write_uint32(base_address + frequency_2_Data_uz_sine_generator_16bit, frq);
}

void uz_sine_generator_16bit_hw_write_frequency_3(uint32_t base_address, float frequency)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(frequency > 0.0f);
    uint32_t frq = (uint32_t)frequency;
    uz_axi_write_uint32(base_address + frequency_3_Data_uz_sine_generator_16bit, frq);
}

void uz_sine_generator_16bit_hw_write_frequency_4(uint32_t base_address, float frequency)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(frequency > 0.0f);
    uint32_t frq = (uint32_t)frequency;
    uz_axi_write_uint32(base_address + frequency_4_Data_uz_sine_generator_16bit, frq);
}

void uz_sine_generator_16bit_hw_write_frequency_5(uint32_t base_address, float frequency)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(frequency > 0.0f);
    uint32_t frq = (uint32_t)frequency;
    uz_axi_write_uint32(base_address + frequency_5_Data_uz_sine_generator_16bit, frq);
}

void uz_sine_generator_16bit_hw_write_frequency_6(uint32_t base_address, float frequency)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(frequency > 0.0f);
    uint32_t frq = (uint32_t)frequency;
    uz_axi_write_uint32(base_address + frequency_6_Data_uz_sine_generator_16bit, frq);
}

void uz_sine_generator_16bit_hw_write_frequency_7(uint32_t base_address, float frequency)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(frequency > 0.0f);
    uint32_t frq = (uint32_t)frequency;
    uz_axi_write_uint32(base_address + frequency_7_Data_uz_sine_generator_16bit, frq);
}

void uz_sine_generator_16bit_hw_write_frequency_8(uint32_t base_address, float frequency)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(frequency > 0.0f);
    uint32_t frq = (uint32_t)frequency;
    uz_axi_write_uint32(base_address + frequency_8_Data_uz_sine_generator_16bit, frq);
}

void uz_sine_generator_16bit_hw_write_reset(uint32_t base_address, bool reset)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + reset_sine_Data_uz_sine_generator_16bit, reset);
}

void uz_sine_generator_16bit_hw_write_enable(uint32_t base_address, bool enable)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + enable_sine_Data_uz_sine_generator_16bit, enable);
}