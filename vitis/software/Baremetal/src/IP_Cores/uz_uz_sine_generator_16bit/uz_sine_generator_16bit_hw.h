#ifndef UZ_SINE_GENERATOR_16BIT_HW_H
#define UZ_SINE_GENERATOR_16BIT_HW_H

#include "uz_sine_generator_16bit_hw.h"
#include "uz_sine_generator_16bit_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"


void uz_sine_generator_16bit_hw_write_amplitude_1(uint32_t base_address, float amplitude);
void uz_sine_generator_16bit_hw_write_amplitude_2(uint32_t base_address, float amplitude);
void uz_sine_generator_16bit_hw_write_amplitude_3(uint32_t base_address, float amplitude);
void uz_sine_generator_16bit_hw_write_amplitude_4(uint32_t base_address, float amplitude);
void uz_sine_generator_16bit_hw_write_amplitude_5(uint32_t base_address, float amplitude);
void uz_sine_generator_16bit_hw_write_amplitude_6(uint32_t base_address, float amplitude);
void uz_sine_generator_16bit_hw_write_amplitude_7(uint32_t base_address, float amplitude);
void uz_sine_generator_16bit_hw_write_amplitude_8(uint32_t base_address, float amplitude);

void uz_sine_generator_16bit_hw_write_phase_1(uint32_t base_address, float phase);
void uz_sine_generator_16bit_hw_write_phase_2(uint32_t base_address, float phase);
void uz_sine_generator_16bit_hw_write_phase_3(uint32_t base_address, float phase);
void uz_sine_generator_16bit_hw_write_phase_4(uint32_t base_address, float phase);
void uz_sine_generator_16bit_hw_write_phase_5(uint32_t base_address, float phase);
void uz_sine_generator_16bit_hw_write_phase_6(uint32_t base_address, float phase);
void uz_sine_generator_16bit_hw_write_phase_7(uint32_t base_address, float phase);
void uz_sine_generator_16bit_hw_write_phase_8(uint32_t base_address, float phase);

void uz_sine_generator_16bit_hw_write_frequency_1(uint32_t base_address, float frequency);
void uz_sine_generator_16bit_hw_write_frequency_2(uint32_t base_address, float frequency);
void uz_sine_generator_16bit_hw_write_frequency_3(uint32_t base_address, float frequency);
void uz_sine_generator_16bit_hw_write_frequency_4(uint32_t base_address, float frequency);
void uz_sine_generator_16bit_hw_write_frequency_5(uint32_t base_address, float frequency);
void uz_sine_generator_16bit_hw_write_frequency_6(uint32_t base_address, float frequency);
void uz_sine_generator_16bit_hw_write_frequency_7(uint32_t base_address, float frequency);
void uz_sine_generator_16bit_hw_write_frequency_8(uint32_t base_address, float frequency);

void uz_sine_generator_16bit_hw_write_reset(uint32_t base_address, bool reset);
void uz_sine_generator_16bit_hw_write_enable(uint32_t base_address, bool enable);

#endif // UZ_SINE_GENERATOR_16BIT_HW_H
