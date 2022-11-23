/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID_6ph_codegen.h
 *
 * Code generated for Simulink model 'ElectricalID_6ph_codegen'.
 *
 * Model version                  : 2.690
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Nov 23 13:28:13 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "../uz_ParameterID_data.h"

#ifndef RTW_HEADER_ElectricalID_6ph_codegen_h_
#define RTW_HEADER_ElectricalID_6ph_codegen_h_
#include "../rtwtypes.h"
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef ElectricalID_6ph_codegen_COMMON_INCLUDES_
#define ElectricalID_6ph_codegen_COMMON_INCLUDES_
#include "../rtwtypes.h"
#endif                           /* ElectricalID_6ph_codegen_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetRootDWork
#define rtmGetRootDWork(rtm)           ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
#define rtmSetRootDWork(rtm, val)      ((rtm)->dwork = (val))
#endif

#ifndef rtmGetU
#define rtmGetU(rtm)                   ((rtm)->inputs)
#endif

#ifndef rtmSetU
#define rtmSetU(rtm, val)              ((rtm)->inputs = (val))
#endif

#ifndef rtmGetY
#define rtmGetY(rtm)                   ((rtm)->outputs)
#endif

#ifndef rtmSetY
#define rtmSetY(rtm, val)              ((rtm)->outputs = (val))
#endif

#define ElectricalID_6ph_codegen_M     (rtElectricalID_6ph_codegen_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_ElectricalID_6ph_code_t RT_MODEL_ElectricalID_6ph_cod_t;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  uz_6ph_abc_t ActualVabc;             /* '<Root>/ElectricalID_6ph_codegen' */
  uz_6ph_alphabeta_t current;          /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T H[4];                       /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T omega_register[5];          /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T d[2048];                    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T i_est[2048];                /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T J[4096];                    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T Vstep[205];                 /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T measArray1[1024];           /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T inv_VSD[36];                /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T VSD[36];                    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T fv[2048];
  real32_T fv1[2048];
  real32_T fv2[6];
  real32_T fv3[6];
  real32_T fv4[4];
  real32_T fv5[2];
  real32_T abc_vector[6];
  real32_T e;                          /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T lambda;                     /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T V0;                         /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T R_corr;                     /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T bandwidthCurrentControl;    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T dampingFactor;              /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T psiOverJ;                   /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T Kp_iq_loc;                  /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T omega_sum;                  /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T ia_sum;                     /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T DutyCycle;                  /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T ref_amplitude;              /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T R_est;
  real32_T L_est;
  real32_T R_est_m;
  real32_T L_est_c;
  int32_T i;
  uint32_T counter;                    /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T wait_count;                 /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T one_sec_transition_counter; /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T sineCounter;                /* '<Root>/ElectricalID_6ph_codegen' */
  uint16_T n_iters;                    /* '<Root>/ElectricalID_6ph_codegen' */
  uint16_T z;                          /* '<Root>/ElectricalID_6ph_codegen' */
  uint8_T is_active_c3_ElectricalID_6ph_c;/* '<Root>/ElectricalID_6ph_codegen' */
  uint8_T is_c3_ElectricalID_6ph_codegen;/* '<Root>/ElectricalID_6ph_codegen' */
  uint8_T is_ElectricalID;             /* '<Root>/ElectricalID_6ph_codegen' */
  boolean_T updateJ;                   /* '<Root>/ElectricalID_6ph_codegen' */
  boolean_T om_con;                    /* '<Root>/ElectricalID_6ph_codegen' */
  boolean_T ia_valid;                  /* '<Root>/ElectricalID_6ph_codegen' */
  boolean_T DC_manual;                 /* '<Root>/ElectricalID_6ph_codegen' */
} DW_ElectricalID_6ph_codegen_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uz_ParaID_ElectricalIDConfig_t ElectricalIDConfig;/* '<Root>/ElectricalIDConfig' */
  uz_ParaID_ActualValues_t ActualValues;/* '<Root>/ActualValues' */
  uz_ParaID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig' */
  uz_ParaID_ControlFlags_t ControlFlags;/* '<Root>/ControlFlags' */
} ExtU_ElectricalID_6ph_codegen_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T enteredElectricalID;       /* '<Root>/enteredElectricalID' */
  boolean_T finishedElectricalID;      /* '<Root>/finishedElectricalID' */
  uz_ParaID_Controller_Parameters_output_t ElectricalID_FOC_output;/* '<Root>/ElectricalID_FOC_output' */
  uz_ParaID_ElectricalID_output_t ElectricalID_output;/* '<Root>/ElectricalID_output' */
} ExtY_ElectricalID_6ph_codegen_t;

/* Real-time Model Data Structure */
struct tag_RTM_ElectricalID_6ph_code_t {
  ExtU_ElectricalID_6ph_codegen_t *inputs;
  ExtY_ElectricalID_6ph_codegen_t *outputs;
  DW_ElectricalID_6ph_codegen_t *dwork;
};

/* Model entry point functions */
extern void ElectricalID_6ph_codegen_initialize(RT_MODEL_ElectricalID_6ph_cod_t *
  const rtElectricalID_6ph_codegen_M);
extern void ElectricalID_6ph_codegen_step(RT_MODEL_ElectricalID_6ph_cod_t *const
  rtElectricalID_6ph_codegen_M);

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
 * hilite_system('uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen')    - opens subsystem uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen
 * hilite_system('uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID6ph/ElectricalID6ph'
 * '<S1>'   : 'uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen'
 */

/*-
 * Requirements for '<Root>': ElectricalID_6ph_codegen
 */
#endif                              /* RTW_HEADER_ElectricalID_6ph_codegen_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
