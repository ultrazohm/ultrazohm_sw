#ifndef UZ_AXI_H
#define UZ_AXI_H
#include "uz_HAL.h"
#ifndef TEST

/**
 * @brief Writes a float value to the specified register by AXI.
 * 
 * @param Addr Absolute address of the register (base address+offset).
 * @param Value
 */
static inline void uz_axi_write_float(uintptr_t Addr, float Value) {
	volatile float *LocalAddr = (volatile float *) Addr;
	*LocalAddr = Value;
}

/**
 * @brief Reads a float value from the specified register by AXI.
 * 
 * @param Addr Absolute address of the register (base address+offset).
 * @return float 
 */
static inline float uz_axi_read_float(uintptr_t Addr) {
	return *(volatile float *) Addr;
}

/**
 * @brief Write a 32-bit unsigned int variable to the specified register by AXI.
 * 
 * @param Addr Absolute address of the register (base address+offset).
 * @param Value 
 */
static inline void uz_axi_write_uint32(uintptr_t Addr, uint32_t Value) {
	volatile uint32_t *LocalAddr = (volatile uint32_t *) Addr;
	*LocalAddr = Value;
}

/**
 * @brief Reads a 32-bit unsigned int variable from the specified register by AXI.
 * 
 * @param Addr Absolute address of the register (base address+offset).
 * @return uint32_t 
 */
static inline uint32_t uz_axi_read_uint32(uintptr_t Addr) {
	return *(volatile uint32_t *) Addr;
}

/**
 * @brief Writes a 32-bit signed int variable to the specified register by AXI.
 * 
 * @param Addr Absolute address of the register (base address+offset).
 * @param Value 
 */
static inline void uz_axi_write_int32(uintptr_t Addr, int32_t Value) {
	volatile int32_t *LocalAddr = (volatile int32_t *) Addr;
	*LocalAddr = Value;
}

/**
 * @brief Reads a 32-bit signed int variable from the specified register by AXI.
 * 
 * @param Addr Absolute address of the register (base address+offset).
 * @return int32_t 
 */
static inline int32_t uz_axi_read_int32(uintptr_t Addr) {
	return *(volatile int32_t *) Addr;
}

/**
 * @brief Writes a boolean to the specified register by AXI.
 *        True is written as a 32-bit unsigned int variable with value 0x00000001.
 *        False is written as a 32-bit unsigned int variable with value 0x00000000.
 * 
 * @param Addr Absolute address of the register (base address+offset).
 * @param enable true/false.
 */
static inline void uz_axi_write_bool(uintptr_t Addr, _Bool enable) {
	if (enable == true) {
		uz_axi_write_uint32(Addr, (uint32_t) 0x00000001U);
	}
	if (enable == false) {
		uz_axi_write_uint32(Addr, (uint32_t) 0x00000000U);
	}
}
/**
 * @brief Reads a boolean from the specified register by AXI.
 *        If the value is read as a 32-bit unsigned value.
 *        False is 0x00000000, true is 0x00000001.
 *        If any bit except the LSB is one an assertion triggers.
 * 
 * @param Addr Absolute address of the register (base address+offset).
 * @return _Bool 
 */
static inline _Bool uz_axi_read_bool(uintptr_t Addr) {
	uint32_t tmp = uz_axi_read_uint32(Addr);
	uz_assert( (tmp ==0x00000000U) || (tmp==0x00000001U) );
	bool return_value = false;
	if (tmp == 0x00000001U) {
		return_value = true;
	}
	return (return_value);
}

#endif
#ifdef TEST

// Function declaration of axi read/write functions for which Cmock can generate mock interfaces
// since functions that are static inline do not work
void uz_axi_write_float(uintptr_t Addr, float Value);
float uz_axi_read_float(uintptr_t Addr);
void uz_axi_write_uint32(uintptr_t Addr, uint32_t Value);
uint32_t uz_axi_read_uint32(uintptr_t Addr);
void uz_axi_write_int32(uintptr_t Addr, int32_t Value);
int32_t uz_axi_read_int32(uintptr_t Addr);
void uz_axi_write_bool(uintptr_t Addr, _Bool enable);
_Bool uz_axi_read_bool(uintptr_t Addr);
#endif

/**
 * @brief Converts a signed fixed point value that is stored as a signed 32-bit integer value to a float.
 *        This function should only be used directly after reading the int32_t variable from AXI!
 * 
 * @param data Fixed point value stored as a signed 32-bit integer that is read from AXI.
 * @param number_of_fractional_bits Number of fractional bits of the data, 31-number_of_fractional_bits is the number of integer bits.
 * @return float 
 */
static inline float uz_convert_sfixed_to_float(int32_t data, int number_of_fractional_bits) {
	uz_assert(number_of_fractional_bits>=0);
	return (ldexpf((float) data, -number_of_fractional_bits));
}

/**
 * @brief Converts a float to a 32-bit signed fixed point value.
 *        This function should only be used directly before writing the int32_t variable from AXI!
 * 
 * @param data 
 * @param number_of_fractional_bits Number of fractional bits of the data, 31-number_of_fractional_bits is the number of integer bits.
 * @return int32_t 
 */
static inline int32_t uz_convert_float_to_sfixed(float data, int number_of_fractional_bits) {
	uz_assert(number_of_fractional_bits>=0);
	return ((int32_t) ldexpf(data, number_of_fractional_bits));
}

#endif
