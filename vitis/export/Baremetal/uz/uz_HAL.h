#ifndef UZ_HAL_H
#define UZ_HAL_H

#define TARGET_ULTRAZOHM 0
#define TARGET_SANDBOX 1

#if (TARGET_ULTRAZOHM == TARGET_SANDBOX)
#error Set TargetUltraZohm or Target Sandbox to one.
#endif

#if (TARGET_SANDBOX==1)

#include <assert.h>
#include <stdio.h>

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

#define uz_Write32BitToRegister Write32BitDummy
#define uz_Read32BitFromRegister Read32BitDummy

#define UZ_SUCCESS 0
#define UZ_FAILURE 1

#endif

#if (TARGET_ULTRAZOHM==1)

#include "xil_assert.h"
#include "xil_io.h"
#include "xstatus.h"

// The uz_assert macro abstracts the assert method of the platform
// For UltraZohm, use xil_assert.h with Xil_AssertVoid(Expression)
#define uz_assert Xil_AssertVoid
// Common to assert some pointer is not Null
// Map to platform specific assert macro
#define uz_assertNotNull(Expression) \
{                              \
    uz_assert(Expression!=NULL);        \
}

#define uz_printf xil_printf

#define uz_Write32BitToRegister Xil_Out32
#define uz_Read32BitFromRegister Xil_In32

#define UZ_SUCCESS XST_SUCCESS
#define UZ_FAILURE XST_FAILURE

#endif

#endif // Endif of guard
