#ifndef UZ_HAL_H
#define UZ_HAL_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "xil_assert.h"
#include "xstatus.h"
#include <math.h>

// The uz_assert macro abstracts the assert method of the platform
// For UltraZohm, use xil_assert.h with Xil_AssertVoid(Expression)
#define uz_assert Xil_AssertNonvoid
// Common to assert some pointer is not Null
// Map to platform specific assert macro
#define uz_assert_not_NULL(Expression) \
{                              \
    uz_assert(Expression!=NULL);        \
}

#define uz_printf xil_printf
#define UZ_SUCCESS XST_SUCCESS
#define UZ_FAILURE XST_FAILURE

static inline void uz_axi_write_float(uintptr_t Addr, float Value){
  volatile float *LocalAddr = (volatile float *)Addr;
  *LocalAddr = Value;
}

static inline float uz_axi_read_float(uintptr_t Addr)
{
    return *(volatile float *) Addr;
}

static inline void uz_axi_write_uint32(uintptr_t Addr, uint32_t Value){
  volatile uint32_t *LocalAddr = (volatile uint32_t *)Addr;
  *LocalAddr = Value;
}

static inline uint32_t uz_axi_read_uint32(uintptr_t Addr)
{
    return *(volatile uint32_t *) Addr;
}

static inline void uz_axi_write_int32(uintptr_t Addr, int32_t Value){
  volatile int32_t *LocalAddr = (volatile int32_t *)Addr;
  *LocalAddr = Value;
}

static inline int32_t uz_axi_read_int32(uintptr_t Addr)
{
    return *(volatile int32_t *) Addr;
}

static inline void uz_axi_write_bool(uintptr_t Addr, _Bool enable){

	if(enable==true){
		uz_axi_write_uint32(Addr, (uint32_t)0x00000001);
	}
	if(enable==false){
		uz_axi_write_uint32(Addr, (uint32_t)0x00000000);
	}
}

static inline float uz_convert_sfixed_to_float(int32_t data, int numberOfFractionalBits){
	uz_assert(numberOfFractionalBits>=0);
	return (ldexpf((float)data, -numberOfFractionalBits));
}

static inline int32_t uz_convert_float_to_sfixed(float data, int numberOfFractionalBits){
	uz_assert(numberOfFractionalBits>=0);
	return ((int32_t)ldexpf(data, numberOfFractionalBits));
}


#endif // Endif of guard

