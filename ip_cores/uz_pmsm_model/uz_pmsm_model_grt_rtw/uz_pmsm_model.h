/*
 * uz_pmsm_model.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "uz_pmsm_model".
 *
 * Model version              : 7.69
 * Simulink Coder version : 23.2 (R2023b) 01-Aug-2023
 * C source code generated on : Fri Feb  2 15:22:22 2024
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ASIC/FPGA->ASIC/FPGA
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_uz_pmsm_model_h_
#define RTW_HEADER_uz_pmsm_model_h_
#ifndef uz_pmsm_model_COMMON_INCLUDES_
#define uz_pmsm_model_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* uz_pmsm_model_COMMON_INCLUDES_ */

#include "uz_pmsm_model_types.h"
#include "rt_nonfinite.h"
#include "rtGetNaN.h"
#include <float.h>
#include <string.h>
#include <stddef.h>
#include "zero_crossing_types.h"

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

/* Block signals (default storage) */
typedef struct {
  real_T RateTransition6;              /* '<Root>/Rate Transition6' */
  real_T RateTransition2;              /* '<Root>/Rate Transition2' */
  real_T RateTransition1;              /* '<Root>/Rate Transition1' */
  real_T RateTransition;               /* '<Root>/Rate Transition' */
  real_T RateTransition17;             /* '<Root>/Rate Transition17' */
  real32_T u_J;                        /* '<S4>/Rate Transition16' */
  real32_T mu;                         /* '<S4>/Rate Transition15' */
  real32_T M_R0;                       /* '<S4>/Rate Transition10' */
  real32_T R_1;                        /* '<S4>/Rate Transition12' */
  real32_T polepair;                   /* '<S4>/Rate Transition13' */
  real32_T u_L_d;                      /* '<S4>/Rate Transition9' */
  real32_T u_L_q;                      /* '<S4>/Rate Transition11' */
  real32_T psi_pm;                     /* '<S4>/Rate Transition14' */
  real32_T i_d;                        /* '<Root>/Rate Transition5' */
  real32_T i_q;                        /* '<Root>/Rate Transition4' */
  real32_T RateTransition3;            /* '<Root>/Rate Transition3' */
  real32_T RateTransition7;            /* '<Root>/Rate Transition7' */
  real32_T ad1;                        /* '<S3>/Rate Transition16' */
  real32_T ad2;                        /* '<S3>/Rate Transition15' */
  real32_T ad3;                        /* '<S3>/Rate Transition10' */
  real32_T ad4;                        /* '<S3>/Rate Transition9' */
  real32_T ad5;                        /* '<S3>/Rate Transition11' */
  real32_T ad6;                        /* '<S3>/Rate Transition12' */
  real32_T aq1;                        /* '<S3>/Rate Transition13' */
  real32_T aq2;                        /* '<S3>/Rate Transition14' */
  real32_T aq3;                        /* '<S3>/Rate Transition1' */
  real32_T aq4;                        /* '<S3>/Rate Transition2' */
  real32_T aq5;                        /* '<S3>/Rate Transition3' */
  real32_T aq6;                        /* '<S3>/Rate Transition4' */
  real32_T u_Fid1_Giq1;                /* '<S3>/Rate Transition5' */
  real32_T u_Fid2_Giq2;                /* '<S3>/Rate Transition6' */
  real32_T ad4ad5;                     /* '<S3>/Rate Transition7' */
  real32_T ad1ad2;                     /* '<S3>/Rate Transition8' */
  real32_T aq4aq5;                     /* '<S3>/Rate Transition17' */
  real32_T aq1aq2;                     /* '<S3>/Rate Transition18' */
  real32_T aq4_aq5;                    /* '<S3>/Rate Transition19' */
  real32_T aq1_aq2;                    /* '<S3>/Rate Transition20' */
  real32_T ad4_ad5;                    /* '<S3>/Rate Transition21' */
  real32_T ad1_ad2;                    /* '<S3>/Rate Transition22' */
  real32_T aq3_aq6;                    /* '<S3>/Rate Transition23' */
  boolean_T RateTransition8;           /* '<Root>/Rate Transition8' */
  boolean_T RateTransition9;           /* '<Root>/Rate Transition9' */
} B_uz_pmsm_model_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S95>/Integrator' */
  real_T Delay1_DSTATE;                /* '<S1>/Delay1' */
  real_T Delay2_DSTATE;                /* '<S1>/Delay2' */
  real_T Integrator_DSTATE_e;          /* '<S47>/Integrator' */
  real_T Integrator_DSTATE_c;          /* '<S206>/Integrator' */
  real_T Delay1_DSTATE_a;              /* '<S2>/Delay1' */
  real_T Delay2_DSTATE_l;              /* '<S2>/Delay2' */
  real_T Integrator_DSTATE_j;          /* '<S158>/Integrator' */
  real_T RateTransition2_Buffer0;      /* '<Root>/Rate Transition2' */
  real_T RateTransition1_Buffer0;      /* '<Root>/Rate Transition1' */
  real_T RateTransition1_Buffer;       /* '<S1>/Rate Transition1' */
  real_T RateTransition11_Buffer;      /* '<S1>/Rate Transition11' */
  real_T RateTransition5_Buffer;       /* '<S1>/Rate Transition5' */
  real_T RateTransition7_Buffer;       /* '<S1>/Rate Transition7' */
  real_T RateTransition4_Buffer;       /* '<S1>/Rate Transition4' */
  real_T RateTransition6_Buffer;       /* '<S1>/Rate Transition6' */
  real_T RateTransition1_Buffer_l;     /* '<S2>/Rate Transition1' */
  real_T RateTransition11_Buffer_f;    /* '<S2>/Rate Transition11' */
  real_T RateTransition12_Buffer;      /* '<S122>/Rate Transition12' */
  real_T RateTransition2_Buffer;       /* '<S2>/Rate Transition2' */
  real_T RateTransition1_Buffer_j;     /* '<S122>/Rate Transition1' */
  real32_T Delay1_DSTATE_j;            /* '<S227>/Delay1' */
  real32_T Delay1_DSTATE_e;            /* '<S228>/Delay1' */
  real32_T Delay1_DSTATE_n;            /* '<S226>/Delay1' */
  real32_T Delay_DSTATE;               /* '<S223>/Delay' */
  real32_T RateTransition5_Buffer0;    /* '<S3>/Rate Transition5' */
  real32_T RateTransition6_Buffer0;    /* '<S3>/Rate Transition6' */
  real32_T RateTransition19_Buffer0;   /* '<S3>/Rate Transition19' */
  real32_T RateTransition20_Buffer0;   /* '<S3>/Rate Transition20' */
  real32_T RateTransition21_Buffer0;   /* '<S3>/Rate Transition21' */
  real32_T RateTransition22_Buffer0;   /* '<S3>/Rate Transition22' */
  real32_T RateTransition3_Buffer[23]; /* '<S1>/Rate Transition3' */
  real32_T RateTransition2_Buffer_f;   /* '<S1>/Rate Transition2' */
} DW_uz_pmsm_model_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Delay1_Reset_ZCE;         /* '<S227>/Delay1' */
  ZCSigState Delay1_Reset_ZCE_f;       /* '<S228>/Delay1' */
  ZCSigState Delay1_Reset_ZCE_i;       /* '<S226>/Delay1' */
} PrevZCX_uz_pmsm_model_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Gain2;                  /* '<Root>/Gain2' */
  const real_T Abs;                    /* '<S3>/Abs' */
  const real_T Abs1;                   /* '<S3>/Abs1' */
  const real_T Abs2;                   /* '<S3>/Abs2' */
  const real_T Abs3;                   /* '<S3>/Abs3' */
  const real_T Abs4;                   /* '<S3>/Abs4' */
  const real_T Abs5;                   /* '<S3>/Abs5' */
  const real_T Add;                    /* '<S3>/Add' */
  const real_T Product;                /* '<S3>/Product' */
  const real_T Product2;               /* '<S3>/Product2' */
  const real_T Product3;               /* '<S3>/Product3' */
  const real_T Product1;               /* '<S3>/Product1' */
  const real_T Gain;                   /* '<S123>/Gain' */
  const real_T Gain1;                  /* '<S123>/Gain1' */
  const real_T Gain_l;                 /* '<S124>/Gain' */
  const real_T Gain1_o;                /* '<S124>/Gain1' */
  const real_T Ldq_Karte;              /* '<S121>/Ldq Lookup Table' */
  const real_T Ldq_Karte_l;            /* '<S121>/Lqd Lookup Table1' */
  const real32_T DataTypeConversion1;  /* '<S3>/Data Type Conversion1' */
  const real32_T DataTypeConversion10; /* '<S3>/Data Type Conversion10' */
  const real32_T DataTypeConversion11; /* '<S3>/Data Type Conversion11' */
  const real32_T DataTypeConversion12; /* '<S3>/Data Type Conversion12' */
  const real32_T DataTypeConversion13; /* '<S3>/Data Type Conversion13' */
  const real32_T DataTypeConversion14; /* '<S3>/Data Type Conversion14' */
  const real32_T DataTypeConversion17; /* '<S3>/Data Type Conversion17' */
  const real32_T DataTypeConversion18; /* '<S3>/Data Type Conversion18' */
  const real32_T DataTypeConversion2;  /* '<S3>/Data Type Conversion2' */
  const real32_T DataTypeConversion3;  /* '<S3>/Data Type Conversion3' */
  const real32_T DataTypeConversion4;  /* '<S3>/Data Type Conversion4' */
  const real32_T DataTypeConversion5;  /* '<S3>/Data Type Conversion5' */
  const real32_T DataTypeConversion6;  /* '<S3>/Data Type Conversion6' */
  const real32_T DataTypeConversion7;  /* '<S3>/Data Type Conversion7' */
  const real32_T DataTypeConversion8;  /* '<S3>/Data Type Conversion8' */
  const real32_T DataTypeConversion9;  /* '<S3>/Data Type Conversion9' */
  const real32_T DataTypeConversion10_h;/* '<S4>/Data Type Conversion10' */
  const real32_T DataTypeConversion11_j;/* '<S4>/Data Type Conversion11' */
  const real32_T DataTypeConversion12_h;/* '<S4>/Data Type Conversion12' */
  const real32_T DataTypeConversion13_o;/* '<S4>/Data Type Conversion13' */
  const real32_T DataTypeConversion14_o;/* '<S4>/Data Type Conversion14' */
  const real32_T DataTypeConversion7_h;/* '<S4>/Data Type Conversion7' */
  const real32_T DataTypeConversion8_c;/* '<S4>/Data Type Conversion8' */
  const real32_T DataTypeConversion9_c;/* '<S4>/Data Type Conversion9' */
  const real32_T psi_d_controller;     /* '<S121>/Flux_d Lookup Table' */
  const real32_T psi_d_set;            /* '<S121>/Flux_d Lookup Table1' */
  const real32_T psi_q_controller;     /* '<S121>/Flux_q Lookup Table1' */
  const real32_T psi_q_set;            /* '<S121>/Flux_q Lookup Table2' */
} ConstB_uz_pmsm_model_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: Flux_d)
   * Referenced by:
   *   '<S120>/Flux_d Lookup Table'
   *   '<S120>/Flux_d Lookup Table1'
   */
  real_T pooled21[400];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S120>/Flux_d Lookup Table'
   *   '<S120>/Flux_d Lookup Table1'
   *   '<S120>/Flux_q Lookup Table1'
   *   '<S120>/Flux_q Lookup Table2'
   *   '<S120>/Ldq Lookup Table'
   *   '<S120>/Lqd Lookup Table1'
   */
  real_T pooled22[20];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S120>/Flux_d Lookup Table'
   *   '<S120>/Flux_d Lookup Table1'
   *   '<S120>/Flux_q Lookup Table1'
   *   '<S120>/Flux_q Lookup Table2'
   *   '<S120>/Ldq Lookup Table'
   *   '<S120>/Lqd Lookup Table1'
   */
  real_T pooled23[20];

  /* Pooled Parameter (Expression: Flux_q)
   * Referenced by:
   *   '<S120>/Flux_q Lookup Table1'
   *   '<S120>/Flux_q Lookup Table2'
   */
  real_T pooled24[400];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S120>/Flux_d Lookup Table'
   *   '<S120>/Flux_d Lookup Table1'
   *   '<S120>/Flux_q Lookup Table1'
   *   '<S120>/Flux_q Lookup Table2'
   *   '<S120>/Ldq Lookup Table'
   *   '<S120>/Lqd Lookup Table1'
   *   '<S121>/Flux_d Lookup Table'
   *   '<S121>/Flux_d Lookup Table1'
   *   '<S121>/Flux_q Lookup Table1'
   *   '<S121>/Flux_q Lookup Table2'
   *   '<S121>/Ldq Lookup Table'
   *   '<S121>/Lqd Lookup Table1'
   */
  uint32_T pooled36[2];
} ConstP_uz_pmsm_model_T;

/* Real-time Model Data Structure */
struct tag_RTM_uz_pmsm_model_T {
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
    uint32_T clockTick1;
    uint32_T clockTickH1;
    struct {
      uint8_T TID[2];
    } TaskCounters;

    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block signals (default storage) */
extern B_uz_pmsm_model_T uz_pmsm_model_B;

/* Block states (default storage) */
extern DW_uz_pmsm_model_T uz_pmsm_model_DW;

/* Zero-crossing (trigger) state */
extern PrevZCX_uz_pmsm_model_T uz_pmsm_model_PrevZCX;
extern const ConstB_uz_pmsm_model_T uz_pmsm_model_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_uz_pmsm_model_T uz_pmsm_model_ConstP;

/* Model entry point functions */
extern void uz_pmsm_model_initialize(void);
extern void uz_pmsm_model_step(void);
extern void uz_pmsm_model_terminate(void);

/* Real-time Model object */
extern RT_MODEL_uz_pmsm_model_T *const uz_pmsm_model_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_pmsm_model'
 * '<S1>'   : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD'
 * '<S2>'   : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1'
 * '<S3>'   : 'uz_pmsm_model/fitting_parameters'
 * '<S4>'   : 'uz_pmsm_model/model_parameters1'
 * '<S5>'   : 'uz_pmsm_model/uz_pmsm_model'
 * '<S6>'   : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Entkopplung_flags'
 * '<S7>'   : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Entkopplungen'
 * '<S8>'   : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller'
 * '<S9>'   : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2'
 * '<S10>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Psi_d_q'
 * '<S11>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Reglernachführung'
 * '<S12>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Entkopplungen/Lineare_Entkopplung'
 * '<S13>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Entkopplungen/decoupling_praediktion'
 * '<S14>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Entkopplungen/dynamic_nonlinear_entkopplung1'
 * '<S15>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Entkopplungen/static_nonlinear_entkopplung'
 * '<S16>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Anti-windup'
 * '<S17>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/D Gain'
 * '<S18>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Filter'
 * '<S19>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Filter ICs'
 * '<S20>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/I Gain'
 * '<S21>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Ideal P Gain'
 * '<S22>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Ideal P Gain Fdbk'
 * '<S23>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Integrator'
 * '<S24>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Integrator ICs'
 * '<S25>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/N Copy'
 * '<S26>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/N Gain'
 * '<S27>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/P Copy'
 * '<S28>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Parallel P Gain'
 * '<S29>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Reset Signal'
 * '<S30>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Saturation'
 * '<S31>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Saturation Fdbk'
 * '<S32>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Sum'
 * '<S33>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Sum Fdbk'
 * '<S34>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Tracking Mode'
 * '<S35>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Tracking Mode Sum'
 * '<S36>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Tsamp - Integral'
 * '<S37>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Tsamp - Ngain'
 * '<S38>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/postSat Signal'
 * '<S39>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/preSat Signal'
 * '<S40>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Anti-windup/Passthrough'
 * '<S41>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/D Gain/Disabled'
 * '<S42>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Filter/Disabled'
 * '<S43>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Filter ICs/Disabled'
 * '<S44>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/I Gain/External Parameters'
 * '<S45>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Ideal P Gain/Passthrough'
 * '<S46>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S47>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Integrator/Discrete'
 * '<S48>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Integrator ICs/Internal IC'
 * '<S49>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S50>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/N Gain/Disabled'
 * '<S51>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/P Copy/Disabled'
 * '<S52>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Parallel P Gain/External Parameters'
 * '<S53>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Reset Signal/Disabled'
 * '<S54>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Saturation/Passthrough'
 * '<S55>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Saturation Fdbk/Disabled'
 * '<S56>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Sum/Sum_PI'
 * '<S57>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Sum Fdbk/Disabled'
 * '<S58>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Tracking Mode/Disabled'
 * '<S59>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S60>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S61>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S62>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/postSat Signal/Forward_Path'
 * '<S63>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller/preSat Signal/Forward_Path'
 * '<S64>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Anti-windup'
 * '<S65>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/D Gain'
 * '<S66>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Filter'
 * '<S67>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Filter ICs'
 * '<S68>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/I Gain'
 * '<S69>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Ideal P Gain'
 * '<S70>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Ideal P Gain Fdbk'
 * '<S71>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Integrator'
 * '<S72>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Integrator ICs'
 * '<S73>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/N Copy'
 * '<S74>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/N Gain'
 * '<S75>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/P Copy'
 * '<S76>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Parallel P Gain'
 * '<S77>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Reset Signal'
 * '<S78>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Saturation'
 * '<S79>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Saturation Fdbk'
 * '<S80>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Sum'
 * '<S81>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Sum Fdbk'
 * '<S82>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Tracking Mode'
 * '<S83>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Tracking Mode Sum'
 * '<S84>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Tsamp - Integral'
 * '<S85>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Tsamp - Ngain'
 * '<S86>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/postSat Signal'
 * '<S87>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/preSat Signal'
 * '<S88>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Anti-windup/Passthrough'
 * '<S89>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/D Gain/Disabled'
 * '<S90>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Filter/Disabled'
 * '<S91>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Filter ICs/Disabled'
 * '<S92>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/I Gain/External Parameters'
 * '<S93>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Ideal P Gain/Passthrough'
 * '<S94>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S95>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Integrator/Discrete'
 * '<S96>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Integrator ICs/Internal IC'
 * '<S97>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/N Copy/Disabled wSignal Specification'
 * '<S98>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/N Gain/Disabled'
 * '<S99>'  : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/P Copy/Disabled'
 * '<S100>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Parallel P Gain/External Parameters'
 * '<S101>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Reset Signal/Disabled'
 * '<S102>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Saturation/Passthrough'
 * '<S103>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Saturation Fdbk/Disabled'
 * '<S104>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Sum/Sum_PI'
 * '<S105>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Sum Fdbk/Disabled'
 * '<S106>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Tracking Mode/Disabled'
 * '<S107>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S108>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Tsamp - Integral/TsSignalSpecification'
 * '<S109>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S110>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/postSat Signal/Forward_Path'
 * '<S111>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/PID Controller2/preSat Signal/Forward_Path'
 * '<S112>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Psi_d_q/psid_approx'
 * '<S113>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Psi_d_q/psid_approx1'
 * '<S114>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Psi_d_q/psiq_approx'
 * '<S115>' : 'uz_pmsm_model/Curren t_Controller_With_FluxMaps_OLD/Psi_d_q/psiq_approx1'
 * '<S116>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/Entkopplung_flags'
 * '<S117>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/Entkopplungen'
 * '<S118>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller'
 * '<S119>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2'
 * '<S120>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/Psi_d_q'
 * '<S121>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/Psi_d_q1'
 * '<S122>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/Reglernachführung'
 * '<S123>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/Entkopplungen/Lineare_Entkopplung'
 * '<S124>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/Entkopplungen/decoupling_praediktion'
 * '<S125>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/Entkopplungen/dynamic_nonlinear_entkopplung1'
 * '<S126>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/Entkopplungen/static_nonlinear_entkopplung'
 * '<S127>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Anti-windup'
 * '<S128>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/D Gain'
 * '<S129>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Filter'
 * '<S130>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Filter ICs'
 * '<S131>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/I Gain'
 * '<S132>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Ideal P Gain'
 * '<S133>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Ideal P Gain Fdbk'
 * '<S134>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Integrator'
 * '<S135>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Integrator ICs'
 * '<S136>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/N Copy'
 * '<S137>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/N Gain'
 * '<S138>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/P Copy'
 * '<S139>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Parallel P Gain'
 * '<S140>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Reset Signal'
 * '<S141>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Saturation'
 * '<S142>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Saturation Fdbk'
 * '<S143>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Sum'
 * '<S144>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Sum Fdbk'
 * '<S145>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Tracking Mode'
 * '<S146>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Tracking Mode Sum'
 * '<S147>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Tsamp - Integral'
 * '<S148>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Tsamp - Ngain'
 * '<S149>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/postSat Signal'
 * '<S150>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/preSat Signal'
 * '<S151>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Anti-windup/Passthrough'
 * '<S152>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/D Gain/Disabled'
 * '<S153>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Filter/Disabled'
 * '<S154>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Filter ICs/Disabled'
 * '<S155>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/I Gain/External Parameters'
 * '<S156>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Ideal P Gain/Passthrough'
 * '<S157>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S158>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Integrator/Discrete'
 * '<S159>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Integrator ICs/Internal IC'
 * '<S160>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S161>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/N Gain/Disabled'
 * '<S162>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/P Copy/Disabled'
 * '<S163>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Parallel P Gain/External Parameters'
 * '<S164>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Reset Signal/Disabled'
 * '<S165>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Saturation/Passthrough'
 * '<S166>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Saturation Fdbk/Disabled'
 * '<S167>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Sum/Sum_PI'
 * '<S168>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Sum Fdbk/Disabled'
 * '<S169>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Tracking Mode/Disabled'
 * '<S170>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S171>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S172>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S173>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/postSat Signal/Forward_Path'
 * '<S174>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller/preSat Signal/Forward_Path'
 * '<S175>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Anti-windup'
 * '<S176>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/D Gain'
 * '<S177>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Filter'
 * '<S178>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Filter ICs'
 * '<S179>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/I Gain'
 * '<S180>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Ideal P Gain'
 * '<S181>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Ideal P Gain Fdbk'
 * '<S182>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Integrator'
 * '<S183>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Integrator ICs'
 * '<S184>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/N Copy'
 * '<S185>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/N Gain'
 * '<S186>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/P Copy'
 * '<S187>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Parallel P Gain'
 * '<S188>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Reset Signal'
 * '<S189>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Saturation'
 * '<S190>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Saturation Fdbk'
 * '<S191>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Sum'
 * '<S192>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Sum Fdbk'
 * '<S193>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Tracking Mode'
 * '<S194>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Tracking Mode Sum'
 * '<S195>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Tsamp - Integral'
 * '<S196>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Tsamp - Ngain'
 * '<S197>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/postSat Signal'
 * '<S198>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/preSat Signal'
 * '<S199>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Anti-windup/Passthrough'
 * '<S200>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/D Gain/Disabled'
 * '<S201>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Filter/Disabled'
 * '<S202>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Filter ICs/Disabled'
 * '<S203>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/I Gain/External Parameters'
 * '<S204>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Ideal P Gain/Passthrough'
 * '<S205>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S206>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Integrator/Discrete'
 * '<S207>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Integrator ICs/Internal IC'
 * '<S208>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/N Copy/Disabled wSignal Specification'
 * '<S209>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/N Gain/Disabled'
 * '<S210>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/P Copy/Disabled'
 * '<S211>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Parallel P Gain/External Parameters'
 * '<S212>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Reset Signal/Disabled'
 * '<S213>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Saturation/Passthrough'
 * '<S214>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Saturation Fdbk/Disabled'
 * '<S215>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Sum/Sum_PI'
 * '<S216>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Sum Fdbk/Disabled'
 * '<S217>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Tracking Mode/Disabled'
 * '<S218>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S219>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Tsamp - Integral/TsSignalSpecification'
 * '<S220>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S221>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/postSat Signal/Forward_Path'
 * '<S222>' : 'uz_pmsm_model/Current_Controller_With_FluxMaps_OLD1/PID Controller2/preSat Signal/Forward_Path'
 * '<S223>' : 'uz_pmsm_model/uz_pmsm_model/mechanical_system'
 * '<S224>' : 'uz_pmsm_model/uz_pmsm_model/pmsm'
 * '<S225>' : 'uz_pmsm_model/uz_pmsm_model/torque_calculation'
 * '<S226>' : 'uz_pmsm_model/uz_pmsm_model/mechanical_system/integrator1'
 * '<S227>' : 'uz_pmsm_model/uz_pmsm_model/pmsm/Subsystem'
 * '<S228>' : 'uz_pmsm_model/uz_pmsm_model/pmsm/Subsystem1'
 */
#endif                                 /* RTW_HEADER_uz_pmsm_model_h_ */
