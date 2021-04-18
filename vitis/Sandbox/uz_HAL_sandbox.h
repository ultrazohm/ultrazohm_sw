#ifndef UZ_HAL_H
#define UZ_HAL_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

// The uz_assert macro abstracts the assert method of the platform
// For UltraZohm, use xil_assert.h with Xil_AssertVoid(Expression)
#define uz_assert assert
// Common to assert some pointer is not Null
// Map to platform specific assert macro
#define uz_assert_not_NULL(Expression) \
{                              \
    uz_assert(Expression!=NULL);        \
}

#define uz_printf printf
#define UZ_SUCCESS 0
#define UZ_FAILURE 1

static inline void uz_axi_write_float(uintptr_t Addr, float Value){
  uz_printf("uz_writeFloatToAxi called");
}

static inline float uz_axi_read_float(uintptr_t Addr)
{
      uz_printf("uz_readFloatFromAxi called");
    return (0);
}

static inline void uz_axi_write_uint32(uintptr_t Addr, uint32_t Value){
      uz_printf("uz_writeUnsingedInt32ToAxi called");
}

static inline uint32_t uz_axi_read_uint32(uintptr_t Addr)
{
      uz_printf("uz_readUnsingedInt32FromAxi called");
    return (0);
}

static inline void uz_axi_write_int32(uintptr_t Addr, int32_t Value){
      uz_printf("uz_writeInt32ToAxi called");
}

static inline int32_t uz_axi_read_int32(uintptr_t Addr)
{
      uz_printf("uz_readInt32FromAxi called");
    return (0);
}

static inline void uz_axi_write_bool(uintptr_t Addr, _Bool enable){

      uz_printf("uz_writeBoolToAxi called");
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

