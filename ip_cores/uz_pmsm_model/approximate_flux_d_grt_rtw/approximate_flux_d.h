/*
 * approximate_flux_d.h
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

#ifndef RTW_HEADER_approximate_flux_d_h_
#define RTW_HEADER_approximate_flux_d_h_
#ifndef approximate_flux_d_COMMON_INCLUDES_
#define approximate_flux_d_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* approximate_flux_d_COMMON_INCLUDES_ */

#include "approximate_flux_d_types.h"
#include <float.h>
#include <string.h>
#include <stddef.h>
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T id_regler;                  /* '<Root>/id' */
  real32_T iq_regler;                  /* '<Root>/iq' */
  real32_T iq_regler_o[23];            /* '<Root>/fitting_parameters' */
} ExtU_approximate_flux_d_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T psid_approx;                /* '<Root>/psid_approx' */
} ExtY_approximate_flux_d_T;

/* Real-time Model Data Structure */
struct tag_RTM_approximate_flux_d_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* External inputs (root inport signals with default storage) */
extern ExtU_approximate_flux_d_T approximate_flux_d_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_approximate_flux_d_T approximate_flux_d_Y;

/* Model entry point functions */
extern void approximate_flux_d_initialize(void);
extern void approximate_flux_d_step(void);
extern void approximate_flux_d_terminate(void);

/* Real-time Model object */
extern RT_MODEL_approximate_flux_d_T *const approximate_flux_d_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/#embedded-Coder/approximate_flux_d')    - opens subsystem uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/#embedded-Coder/approximate_flux_d
 * hilite_system('uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/#embedded-Coder/approximate_flux_d/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/#embedded-Coder'
 * '<S1>'   : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/#embedded-Coder/approximate_flux_d'
 */
#endif                                 /* RTW_HEADER_approximate_flux_d_h_ */
