/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TwoMassID.h
 *
 * Code generated for Simulink model 'TwoMassID'.
 *
 * Model version                  : 2.371
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Dec 22 12:41:11 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (9), Warnings (3), Error (0)
 */
#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U
#include "../../uz_PMSM_config/uz_PMSM_config.h"
#include "../../uz_Transformation/uz_Transformation.h"

#ifndef RTW_HEADER_TwoMassID_h_
#define RTW_HEADER_TwoMassID_h_
#include "../rtwtypes.h"
#include <stddef.h>
#include <math.h>
#include <string.h>
#ifndef TwoMassID_COMMON_INCLUDES_
#define TwoMassID_COMMON_INCLUDES_
#include "../rtwtypes.h"
#endif                                 /* TwoMassID_COMMON_INCLUDES_ */

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

#define TwoMassID_M                    (rtTwoMassID_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_TwoMassID_t RT_MODEL_TwoMassID_t;

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_TwoMassIDConfig_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_TwoMassIDConfig_t_

/**
 * @brief configuration struct for TwoMassID specific settings
 * 
 */
typedef struct {
  real32_T ScaleTorquePRBS; /**< current amplitude of PRBS excitation */
  real32_T n_ref_measurement; /** reference speed for identification */
  uint16_T f_max; /**< maximum evaluation frequency */
  uint16_T f_min; /**< minimum evaluation frequency */
  uint8_T UseLbMq; /**< flag to use Levenberg Marquardt Algorithm */
  real32_T d_TMS_start; /**< inital damping value for LM-algorithm */
} uz_PID_TwoMassIDConfig_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_ActualValues_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_ActualValues_t_

typedef struct {
  uz_3ph_abc_t V_abc;
  uz_3ph_abc_t I_abc;
  uz_3ph_dq_t i_dq;
  uz_3ph_dq_t v_dq;
  real32_T omega_m;
  real32_T omega_el;
  real32_T theta_m;
  real32_T theta_el;
  real32_T V_DC;
} uz_PID_ActualValues_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_GlobalConfig_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_GlobalConfig_t_

typedef struct {
  uz_PMSM_t PMSM_config;
  boolean_T enableParameterID;
  boolean_T Reset;
  real32_T Kp_id;
  real32_T Kp_iq;
  real32_T Kp_n;
  real32_T Ki_id;
  real32_T Ki_iq;
  real32_T Ki_n;
  boolean_T ElectricalID;
  boolean_T FrictionID;
  boolean_T TwoMassID;
  boolean_T FluxMapID;
  boolean_T OnlineID;
  boolean_T ACCEPT;
  real32_T sampleTimeISR;
  real32_T ratCurrent;
  real32_T ratSpeed;
  uz_3ph_dq_t i_dq_ref;
  real32_T n_ref;
} uz_PID_GlobalConfig_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_ControlFlags_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_ControlFlags_t_

typedef struct {
  boolean_T startFrictionID;
  boolean_T startElectricalID;
  boolean_T startTwoMassID;
  boolean_T startFluxMapID;
  uint16_T transNr;
  boolean_T enableOnlineID;
  boolean_T finished_all_Offline_states;
} uz_PID_ControlFlags_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_Controller_Parameters_output_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_Controller_Parameters_output_t_

typedef struct {
  uz_3ph_dq_t i_dq_ref;
  uint16_T activeState;
  real32_T n_ref_FOC;
  boolean_T enableFOC_speed;
  boolean_T enableFOC_current;
  boolean_T resetIntegrator;
  real32_T Kp_id_out;
  real32_T Kp_iq_out;
  real32_T Kp_n_out;
  real32_T Ki_id_out;
  real32_T Ki_iq_out;
  real32_T Ki_n_out;
} uz_PID_Controller_Parameters_output_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_TwoMassID_output_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_TwoMassID_output_t_

/**
 * @brief output struct of TwoMassID
 * 
 */
typedef struct {
  real32_T PRBS_out; /**< output of excitation signal. Has to added on top of the speedcontrol q_reference_current */
  real32_T c_est_out; /**< identified TMS stiffness in Nm/rad */
  real32_T d_est_out; /**< identified TMS damping in Nms/rad */
  real32_T LoadInertia; /**< identified inertia of the load in kgm² */
  real32_T TrainInertia; /**< identified inertia of the total system in kgm² */
  real32_T rotorInertia; /**< identified inertia of the motor in kgm² */
} uz_PID_TwoMassID_output_t;

#endif

#ifndef struct_tag_ZpaURosCCuIauE184fQrdB
#define struct_tag_ZpaURosCCuIauE184fQrdB

struct tag_ZpaURosCCuIauE184fQrdB
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  real32_T pPeriodogramMatrix[2046];
  real32_T pW[1024];
  real32_T pWindowData[2046];
  real32_T pWindowPower;
  real32_T pNumAvgsCounter;
  real32_T pNewPeriodogramIdx;
  real32_T ReferenceLoad;
  real32_T pReferenceLoad;
  real32_T pFreq[1024];
  real32_T pFrameCounter;
  real32_T pFrameDelay;
};

#endif                                 /* struct_tag_ZpaURosCCuIauE184fQrdB */

#ifndef typedef_dsp_simulink_SpectrumEstimato_t
#define typedef_dsp_simulink_SpectrumEstimato_t

typedef struct tag_ZpaURosCCuIauE184fQrdB dsp_simulink_SpectrumEstimato_t;

#endif                             /* typedef_dsp_simulink_SpectrumEstimato_t */

/* Custom Type definition for Chart: '<Root>/TwoMassID' */
#ifndef struct_tag_MVWU0C6TwghbPF0nrErUCF
#define struct_tag_MVWU0C6TwghbPF0nrErUCF

struct tag_MVWU0C6TwghbPF0nrErUCF
{
  int32_T S0_isInitialized;
  uint8_T W0_shiftReg[11];
  uint8_T P0_Polynomial[12];
  uint8_T P1_IniState[11];
  uint8_T P2_Mask[11];
};

#endif                                 /* struct_tag_MVWU0C6TwghbPF0nrErUCF */

#ifndef typedef_comm_PNSequence_0_TwoMassID_t
#define typedef_comm_PNSequence_0_TwoMassID_t

typedef struct tag_MVWU0C6TwghbPF0nrErUCF comm_PNSequence_0_TwoMassID_t;

#endif                               /* typedef_comm_PNSequence_0_TwoMassID_t */

/* Block signals and states (default storage) for system '<S1>/TwoMassID.Welch' */
typedef struct {
  dsp_simulink_SpectrumEstimato_t obj; /* '<S3>/Spectrum Estimator' */
  creal32_T X[2046];
  creal32_T wwc[2045];
  creal32_T ytmp[1023];
  creal32_T fv[2048];
  creal32_T reconVar1[1023];
  creal32_T reconVar2[1023];
  creal32_T fcv[2048];
  creal32_T fv_m[2048];
  creal32_T y;
  real32_T SpectrumEstimator_o1[1024]; /* '<S3>/Spectrum Estimator' */
  real32_T SpectrumEstimator_o2[1024]; /* '<S3>/Spectrum Estimator' */
  real32_T x[2046];
  real32_T x_c[2046];
  real32_T xout[2046];
  real32_T hcostab[1024];
  real32_T hsintab[1024];
  real32_T hcostabinv[1024];
  real32_T hsintabinv[1024];
  real32_T y_k;
  real32_T varargin_2;
  real32_T X_re;
  real32_T X_im;
  real32_T nt_im;
  real32_T b_re;
  int32_T i;
  int32_T b_xj;
  int32_T i_c;
  int32_T rt;
  int32_T b_k;
  int32_T y_b;
  int32_T xidx;
  int16_T wrapIndex[1023];
} DW_TwoMassIDWelch_TwoMassID_t;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_TwoMassIDWelch_TwoMassID_t TwoMassIDWelch_l;/* '<S1>/TwoMassID.Welch' */
  real_T dv[2047];
  real_T dv1[4];
  real32_T prbs_array[2048];           /* '<Root>/TwoMassID' */
  real32_T iq_array[1024];             /* '<Root>/TwoMassID' */
  real32_T omega_array[1024];          /* '<Root>/TwoMassID' */
  real32_T measArray2[2048];           /* '<Root>/TwoMassID' */
  real32_T J[4096];                    /* '<Root>/TwoMassID' */
  real32_T Ustep[103];
  real32_T LbMq[5];
  real32_T H[4];
  real32_T fv[4];
  real32_T x;
  real32_T lambda;
  real32_T ee;
  real32_T ee_lm;
  real32_T c_est;
  real32_T Tilgerwert;
  real32_T Tilgerfrequenz;
  real32_T Resonanzwert;
  real32_T Resonanzfrequenz;
  real32_T JT;
  real32_T JL;
  real32_T d_est;
  real32_T fehler0;
  real32_T fehlerc;
  real32_T fehlerd;
  real32_T d2;
  real32_T c_est_start_idx_0;
  real32_T c_est_start_idx_1;
  real32_T Jac_idx_0;
  real32_T Jac_idx_1;
  real32_T ar;
  real32_T ai;
  real32_T br;
  real32_T brm;
  real32_T bim;
  real32_T d_est_tmp;
  real32_T c_est_start_idx_1_tmp;
  real32_T fehlerc_tmp;
  real32_T c_est_start_idx_0_tmp;
  real32_T c_est_start_idx_0_tmp_tmp;
  real32_T c_est_start_idx_1_tmp_m;
  real32_T br_tmp;
  real32_T ee_lm_tmp_tmp;
  real32_T c_est_start_idx_1_tmp_tmp;
  real32_T f;
  real32_T f1;
  real32_T r;
  real32_T t;
  real32_T b_x;
  real32_T a;
  int32_T i;
  int32_T i_c;
  int32_T b;
  int32_T c_k;
  int32_T f_k;
  int32_T i_k;
  int32_T c_k_tmp;
  int32_T k;
  uint32_T counter;                    /* '<Root>/TwoMassID' */
  uint32_T mean_count;                 /* '<Root>/TwoMassID' */
  uint32_T nextstate;                  /* '<Root>/TwoMassID' */
  uint32_T prbs_count;                 /* '<Root>/TwoMassID' */
  uint32_T one_sec_transition_counter; /* '<Root>/TwoMassID' */
  uint32_T qY;
  uint32_T qY_c;
  uint16_T index_min;
  uint16_T index_max;
  uint8_T is_active_c17_TwoMassID;     /* '<Root>/TwoMassID' */
  uint8_T is_c17_TwoMassID;            /* '<Root>/TwoMassID' */
  uint8_T is_TwoMassID;                /* '<Root>/TwoMassID' */
  uint8_T updateJac;
} DW_TwoMassID_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uz_PID_TwoMassIDConfig_t TwoMassIDConfig;/* '<Root>/TwoMassIDConfig' */
  uz_PID_ActualValues_t ActualValues;  /* '<Root>/ActualValues' */
  uz_PID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig' */
  uz_PID_ControlFlags_t ControlFlags;  /* '<Root>/ControlFlags' */
} ExtU_TwoMassID_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T finishedTwoMassID;         /* '<Root>/finishedTwoMassID' */
  boolean_T enteredTwoMassID;          /* '<Root>/enteredTwoMassID' */
  uz_PID_Controller_Parameters_output_t TwoMassID_FOC_output;/* '<Root>/TwoMassID_FOC_output' */
  uz_PID_TwoMassID_output_t TwoMassID_output;/* '<Root>/TwoMassID_output' */
} ExtY_TwoMassID_t;

/* Real-time Model Data Structure */
struct tag_RTM_TwoMassID_t {
  ExtU_TwoMassID_t *inputs;
  ExtY_TwoMassID_t *outputs;
  DW_TwoMassID_t *dwork;
};

/* Model entry point functions */
extern void TwoMassID_initialize(RT_MODEL_TwoMassID_t *const rtTwoMassID_M);
extern void TwoMassID_step(RT_MODEL_TwoMassID_t *const rtTwoMassID_M);

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
 * hilite_system('uz_ParameterID/TwoMassID')    - opens subsystem uz_ParameterID/TwoMassID
 * hilite_system('uz_ParameterID/TwoMassID/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID'
 * '<S1>'   : 'uz_ParameterID/TwoMassID'
 * '<S2>'   : 'uz_ParameterID/TwoMassID/TwoMassID.Welch'
 * '<S3>'   : 'uz_ParameterID/TwoMassID/TwoMassID.Welch/Spectrum Estimator1'
 */

/*-
 * Requirements for '<Root>': TwoMassID
 */
#endif                                 /* RTW_HEADER_TwoMassID_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
