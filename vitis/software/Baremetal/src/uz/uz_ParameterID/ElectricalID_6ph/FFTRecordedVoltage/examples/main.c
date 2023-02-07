/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 07-Feb-2023 13:28:43
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "FFTRecordedVoltage.h"
#include "FFTRecordedVoltage_terminate.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void argInit_1x10000_real32_T(float result[10000]);

static float argInit_real32_T(void);

static void main_FFTRecordedVoltage(void);

/* Function Definitions */
/*
 * Arguments    : float result[10000]
 * Return Type  : void
 */
static void argInit_1x10000_real32_T(float result[10000])
{
  int idx1;
  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 10000; idx1++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx1] = argInit_real32_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : float
 */
static float argInit_real32_T(void)
{
  return 0.0F;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_FFTRecordedVoltage(void)
{
  static float fv[10000];
  float amplitudes[5001];
  float angles[5001];
  float frequencies[5001];
  /* Initialize function 'FFTRecordedVoltage' input arguments. */
  /* Initialize function input argument 'data'. */
  /* Call the entry-point 'FFTRecordedVoltage'. */
  argInit_1x10000_real32_T(fv);
  FFTRecordedVoltage(fv, argInit_real32_T(), frequencies, amplitudes, angles);
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_FFTRecordedVoltage();
  /* Terminate the application.
You do not need to do this more than one time. */
  FFTRecordedVoltage_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
