#ifndef UZ_AXI_H
#define UZ_AXI_H
#include "uz_HAL.h"
#ifndef TEST

static inline void uz_axi_write_float(uintptr_t Addr, float Value) {
	volatile float *LocalAddr = (volatile float *) Addr;
	*LocalAddr = Value;
}

static inline float uz_axi_read_float(uintptr_t Addr) {
	return *(volatile float *) Addr;
}

static inline void uz_axi_write_uint32(uintptr_t Addr, uint32_t Value) {
	volatile uint32_t *LocalAddr = (volatile uint32_t *) Addr;
	*LocalAddr = Value;
}

static inline uint32_t uz_axi_read_uint32(uintptr_t Addr) {
	return *(volatile uint32_t *) Addr;
}

static inline void uz_axi_write_int32(uintptr_t Addr, int32_t Value) {
	volatile int32_t *LocalAddr = (volatile int32_t *) Addr;
	*LocalAddr = Value;
}

static inline int32_t uz_axi_read_int32(uintptr_t Addr) {
	return *(volatile int32_t *) Addr;
}
#endif
#ifdef TEST

// Function declaration of axi read/write functions for which Cmock can generate mock interfaces (functions that are static inline do not work)
void uz_axi_write_float(uintptr_t Addr, float Value);
float uz_axi_read_float(uintptr_t Addr);
void uz_axi_write_uint32(uintptr_t Addr, uint32_t Value);
uint32_t uz_axi_read_uint32(uintptr_t Addr);
void uz_axi_write_int32(uintptr_t Addr, int32_t Value);
int32_t uz_axi_read_int32(uintptr_t Addr);
#endif

static inline void uz_axi_write_bool(uintptr_t Addr, _Bool enable) {
	if (enable == true) {
		uz_axi_write_uint32(Addr, (uint32_t) 0x00000001);
	}
	if (enable == false) {
		uz_axi_write_uint32(Addr, (uint32_t) 0x00000000);
	}
}

static inline _Bool uz_axi_read_bool(uintptr_t Addr) {
	uint32_t tmp = uz_axi_read_uint32(Addr);
	uz_assert( (tmp ==0x00000000) || (tmp==0x00000001) );
	bool return_value = false;
	if (tmp == 0x00000001) {
		return_value = true;
	}
	return (return_value);
}

static inline float uz_convert_sfixed_to_float(int32_t data, int number_of_fractional_bits) {
	uz_assert(number_of_fractional_bits>=0);
	return (ldexpf((float) data, -number_of_fractional_bits));
}

static inline int32_t uz_convert_float_to_sfixed(float data, int number_of_fractional_bits) {
	uz_assert(number_of_fractional_bits>=0);
	return ((int32_t) ldexpf(data, number_of_fractional_bits));
}

#endif
