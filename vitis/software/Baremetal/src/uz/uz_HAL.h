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
/**
 * @brief Asserts that the condition is true. If false, the assertion callback executes (program is stopped).
 * 
 */
#define uz_assert Xil_AssertNonvoid
/**
 * @brief Prints to stdout, i.e., Vitis terminal
 * 
 */
#define uz_printf xil_printf
/**
 * @brief Processor does nothing for defined seconds
 * 
 */
#define uz_sleep_seconds sleep
/**
 * @brief Processor does nothing for defined microseconds
 * 
 */
#define uz_sleep_useconds usleep
/**
 * @brief Return this define to indicate success in a function and check return value.
 * 
 */
#define UZ_SUCCESS XST_SUCCESS
/**
 * @brief Return this define to indicate failure in a function and check return value.
 * 
 */
#define UZ_FAILURE XST_FAILURE

#endif
#ifdef TEST
#include <stdio.h>
#include <unistd.h>
#include "CException.h"
#define uz_assert(condition) if (!(condition)) Throw(0)
#define uz_printf printf
#define uz_sleep_seconds sleep
#define uz_sleep_useconds usleep
#define UZ_SUCCESS 0U
#define UZ_FAILURE 1U
#endif

/**
 * @brief Asserts that the argument is not a NULL pointer.
 * 
 */
#define uz_assert_not_NULL(Expression) \
{                              \
    uz_assert((Expression)!=NULL);        \
}

/**
 * @brief Asserts that the argument is not zero (!=0).
 * 
 */
#define uz_assert_not_zero(Expression) \
{                              \
    uz_assert((Expression)!=0);        \
}

/**
 * @brief Asserts that the argument is false.
 * 
 */
#define uz_assert_false(Expression) \
{                              \
    uz_assert ((Expression)==false);        \
}

#define uz_assert_true(Expression) \
{                              \
    uz_assert( (Expression) ==true);        \
}
#include "uz_AXI.h" // this include will be deleted but is required since some functions already use the AXI HAL - include has to be done after the assert definitions to prevent compiler warnings!
#endif // Endif of guard

