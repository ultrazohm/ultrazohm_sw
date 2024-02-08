/*
 * approximate_flux_d.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "approximate_flux_d".
 *
 * Model version              : 7.75
 * Simulink Coder version : 23.2 (R2023b) 01-Aug-2023
 * C source code generated on : Thu Feb  8 10:58:20 2024
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ASIC/FPGA->ASIC/FPGA
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "approximate_flux_d.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>
#include "approximate_flux_d_private.h"
#include "rt_nonfinite.h"

/* External inputs (root inport signals with default storage) */
ExtU_approximate_flux_d_T approximate_flux_d_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_approximate_flux_d_T approximate_flux_d_Y;

/* Real-time model */
static RT_MODEL_approximate_flux_d_T approximate_flux_d_M_;
RT_MODEL_approximate_flux_d_T *const approximate_flux_d_M =
  &approximate_flux_d_M_;

/* Model step function */
void approximate_flux_d_step(void)
{
  real32_T rtb_psidself;

  /* Product: '<S1>/Product1' incorporates:
   *  Inport: '<Root>/fitting_parameters'
   *  Inport: '<Root>/id'
   *  Product: '<S1>/Product'
   *  Sum: '<S1>/Sum'
   *  Trigonometry: '<S1>/Tanh'
   */
  rtb_psidself = (real32_T)tanh((approximate_flux_d_U.id_regler -
    approximate_flux_d_U.iq_regler_o[2]) * approximate_flux_d_U.iq_regler_o[1]) *
    approximate_flux_d_U.iq_regler_o[0];

  /* Outport: '<Root>/psid_approx' incorporates:
   *  Inport: '<Root>/fitting_parameters'
   *  Inport: '<Root>/id'
   *  Inport: '<Root>/iq'
   *  Math: '<S1>/Log'
   *  Math: '<S1>/Log1'
   *  Product: '<S1>/Product10'
   *  Product: '<S1>/Product12'
   *  Product: '<S1>/Product2'
   *  Product: '<S1>/Product3'
   *  Product: '<S1>/Product4'
   *  Product: '<S1>/Product5'
   *  Product: '<S1>/Product6'
   *  Product: '<S1>/Product7'
   *  Product: '<S1>/Product8'
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S1>/Sum2'
   *  Sum: '<S1>/Sum3'
   *  Sum: '<S1>/Sum7'
   *  Trigonometry: '<S1>/Tanh1'
   *  Trigonometry: '<S1>/Tanh2'
   *  Trigonometry: '<S1>/Tanh3'
   *
   * About '<S1>/Log':
   *  Operator: log
   *
   * About '<S1>/Log1':
   *  Operator: log
   */
  approximate_flux_d_Y.psid_approx = rtb_psidself - (rtb_psidself - (real32_T)
    tanh((approximate_flux_d_U.id_regler - approximate_flux_d_U.iq_regler_o[5]) *
         approximate_flux_d_U.iq_regler_o[4]) *
    approximate_flux_d_U.iq_regler_o[3]) * (((real32_T)log((real32_T)cosh
    (approximate_flux_d_U.iq_regler * approximate_flux_d_U.iq_regler_o[7])) *
    approximate_flux_d_U.iq_regler_o[19] + approximate_flux_d_U.iq_regler *
    approximate_flux_d_U.iq_regler * approximate_flux_d_U.iq_regler_o[22]) -
    (real32_T)log((real32_T)cosh(approximate_flux_d_U.iq_regler *
    approximate_flux_d_U.iq_regler_o[10])) * approximate_flux_d_U.iq_regler_o[18])
    * approximate_flux_d_U.iq_regler_o[12];

  /* Matfile logging */
  rt_UpdateTXYLogVars(approximate_flux_d_M->rtwLogInfo,
                      (&approximate_flux_d_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [5.0E-5s, 0.0s] */
    if ((rtmGetTFinal(approximate_flux_d_M)!=-1) &&
        !((rtmGetTFinal(approximate_flux_d_M)-
           approximate_flux_d_M->Timing.taskTime0) >
          approximate_flux_d_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(approximate_flux_d_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++approximate_flux_d_M->Timing.clockTick0)) {
    ++approximate_flux_d_M->Timing.clockTickH0;
  }

  approximate_flux_d_M->Timing.taskTime0 =
    approximate_flux_d_M->Timing.clockTick0 *
    approximate_flux_d_M->Timing.stepSize0 +
    approximate_flux_d_M->Timing.clockTickH0 *
    approximate_flux_d_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void approximate_flux_d_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)approximate_flux_d_M, 0,
                sizeof(RT_MODEL_approximate_flux_d_T));
  rtmSetTFinal(approximate_flux_d_M, 0.05);
  approximate_flux_d_M->Timing.stepSize0 = 5.0E-5;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    approximate_flux_d_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(approximate_flux_d_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(approximate_flux_d_M->rtwLogInfo, (NULL));
    rtliSetLogT(approximate_flux_d_M->rtwLogInfo, "");
    rtliSetLogX(approximate_flux_d_M->rtwLogInfo, "");
    rtliSetLogXFinal(approximate_flux_d_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(approximate_flux_d_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(approximate_flux_d_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(approximate_flux_d_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(approximate_flux_d_M->rtwLogInfo, 1);
    rtliSetLogY(approximate_flux_d_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(approximate_flux_d_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(approximate_flux_d_M->rtwLogInfo, (NULL));
  }

  /* external inputs */
  (void)memset(&approximate_flux_d_U, 0, sizeof(ExtU_approximate_flux_d_T));

  /* external outputs */
  approximate_flux_d_Y.psid_approx = 0.0F;

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(approximate_flux_d_M->rtwLogInfo, 0.0,
    rtmGetTFinal(approximate_flux_d_M), approximate_flux_d_M->Timing.stepSize0,
    (&rtmGetErrorStatus(approximate_flux_d_M)));
}

/* Model terminate function */
void approximate_flux_d_terminate(void)
{
  /* (no terminate code required) */
}
