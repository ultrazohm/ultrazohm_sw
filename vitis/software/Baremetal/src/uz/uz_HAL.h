#ifndef UZ_HAL_H
#define UZ_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#ifndef TEST
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_printf.h"
#include "sleep.h"
#define uz_assert Xil_AssertNonvoid
#define uz_printf xil_printf
#define uz_sleep_seconds sleep
#define uz_sleep_useconds usleep
#define UZ_SUCCESS XST_SUCCESS
#define UZ_FAILURE XST_FAILURE

#endif
#ifdef TEST
#include <stdio.h>
#include <assert.h>
#define uz_assert assert
#define uz_printf printf
#define uz_sleep_seconds sleep
#define uz_sleep_useconds usleep
#define UZ_SUCCESS 0U
#define UZ_FAILURE 1U
#endif


#define uz_assert_not_NULL(Expression) \
{                              \
    uz_assert(Expression!=NULL);        \
}

#define uz_assert_not_zero(Expression) \
{                              \
    uz_assert(Expression!=0);        \
}

#define uz_assert_false(Expression) \
{                              \
    uz_assert(Expression==false);        \
}

#define uz_assert_true(Expression) \
{                              \
    uz_assert(Expression==true);        \
}
#include "uz_AXI.h" // this include will be deleted but is required since some functions already use the AXI HAL - include has to be done after the assert definitions to prevent compiler warnings!
#endif // Endif of guard

