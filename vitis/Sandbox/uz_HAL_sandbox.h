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
#define uz_assertNotNull(Expression) \
{                              \
    uz_assert(Expression!=NULL);        \
}

#define uz_printf printf
#define UZ_SUCCESS 0
#define UZ_FAILURE 1

static inline void uz_writeFloatToAxi(uintptr_t Addr, float Value){
  uz_printf("uz_writeFloatToAxi called");
}

static inline float uz_readFloatFromAxi(uintptr_t Addr)
{
      uz_printf("uz_readFloatFromAxi called");
    return (0);
}

static inline void uz_writeUnsingedInt32ToAxi(uintptr_t Addr, uint32_t Value){
      uz_printf("uz_writeUnsingedInt32ToAxi called");
}

static inline uint32_t uz_readUnsingedInt32FromAxi(uintptr_t Addr)
{
      uz_printf("uz_readUnsingedInt32FromAxi called");
    return (0);
}

static inline void uz_writeInt32ToAxi(uintptr_t Addr, int32_t Value){
      uz_printf("uz_writeInt32ToAxi called");
}

static inline int32_t uz_readInt32FromAxi(uintptr_t Addr)
{
      uz_printf("uz_readInt32FromAxi called");
    return (0);
}

static inline void uz_writeBoolToAxi(uintptr_t Addr, _Bool enable){

      uz_printf("uz_writeBoolToAxi called");
}

static inline float uz_sfixedToFloat(int32_t data, int numberOfFractionalBits){
	uz_assert(numberOfFractionalBits>=0);
	return (ldexpf((float)data, -numberOfFractionalBits));
}

static inline int32_t uz_FloatToSfixed(float data, int numberOfFractionalBits){
	uz_assert(numberOfFractionalBits>=0);
	return ((int32_t)ldexpf(data, numberOfFractionalBits));
}


#endif // Endif of guard

