/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 4.4
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Fri Nov 11 16:27:55 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (9), Warning (1), Errors (2)
 */

#ifndef RTW_HEADER_uz_codegen0_h_
#define RTW_HEADER_uz_codegen0_h_
#ifndef uz_codegen0_COMMON_INCLUDES_
#define uz_codegen0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* uz_codegen0_COMMON_INCLUDES_ */

#include <stddef.h>
#include <string.h>

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

#define uz_codegen0_M                  (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<S30>/MATLAB Function' */
typedef struct {
  creal32_T U_sym_komp_hilf[3];
  creal32_T U_sym_komp_hilf_m;
  creal32_T a;
  real32_T br;
  int32_T i;
} DW_MATLABFunction_m;

/* Block signals and states (default storage) for system '<S10>/Strangstromregler_asymetrisch' */
typedef struct {
  DW_MATLABFunction_m sf_MATLABFunction_i;/* '<S30>/MATLAB Function' */
  real32_T U_re;                       /* '<S31>/Discrete-Time Integrator' */
  real32_T U_im;                       /* '<S31>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE;              /* '<S32>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S32>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE;               /* '<S32>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S32>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_m;            /* '<S33>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_d;/* '<S33>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_a;             /* '<S33>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_m;/* '<S33>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_l;            /* '<S31>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_m;/* '<S31>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_b;             /* '<S31>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_l;/* '<S31>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_g;            /* '<S34>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_i;/* '<S34>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_bz;            /* '<S34>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_k;/* '<S34>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_i;            /* '<S35>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTAT_if;/* '<S35>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_h;             /* '<S35>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_a;/* '<S35>/Discrete-Time Integrator1' */
  real32_T Product4_i;                 /* '<S35>/Product4' */
  real32_T Delay1_c;                   /* '<S34>/Delay1' */
  real32_T Product5_h;                 /* '<S35>/Product5' */
  real32_T im_lim_k;                   /* '<S34>/MATLAB Function' */
  real32_T im_lim_d;                   /* '<S31>/MATLAB Function' */
  real32_T re_lim_g;                   /* '<S31>/MATLAB Function' */
  real32_T im_lim_m;                   /* '<S32>/MATLAB Function' */
  real32_T re_lim_l4;                  /* '<S32>/MATLAB Function' */
  real32_T im_lim_lb;                  /* '<S33>/MATLAB Function' */
  real32_T re_lim_i;                   /* '<S33>/MATLAB Function' */
  real32_T Strom_kompensiert_l;        /* '<S30>/Strom_kompensiert' */
  real32_T Cos2_k;                     /* '<S30>/Cos2' */
  real32_T Gain1_p4;                   /* '<S30>/Gain1' */
  real32_T Product_am;                 /* '<S35>/Product' */
  real32_T re_lim_gw;                  /* '<S35>/MATLAB Function' */
  real32_T Gain1_h;                    /* '<S32>/Gain1' */
  real32_T U_re_o;                     /* '<S32>/Sum5' */
  real32_T Gain2_nl;                   /* '<S32>/Gain2' */
  real32_T U_im_i;                     /* '<S32>/Sum6' */
  real32_T Gain1_g;                    /* '<S33>/Gain1' */
  real32_T U_re_h;                     /* '<S33>/Sum5' */
  real32_T Gain2_d;                    /* '<S33>/Gain2' */
  real32_T U_im_pl;                    /* '<S33>/Sum6' */
  real32_T Product3_o;                 /* '<S33>/Product3' */
  real32_T Product2_b3;                /* '<S33>/Product2' */
  real32_T Gain1_i;                    /* '<S31>/Gain1' */
  real32_T Gain2_io;                   /* '<S31>/Gain2' */
  real32_T Product3_a;                 /* '<S31>/Product3' */
  real32_T Product2_p;                 /* '<S31>/Product2' */
  real32_T Gain1_n;                    /* '<S34>/Gain1' */
  real32_T U_re_j;                     /* '<S34>/Sum5' */
  real32_T Gain2_e;                    /* '<S34>/Gain2' */
  real32_T U_im_pt;                    /* '<S34>/Sum6' */
  real32_T Product3_lj;                /* '<S34>/Product3' */
  real32_T Product2_c;                 /* '<S34>/Product2' */
  real32_T Gain1_a;                    /* '<S35>/Gain1' */
  real32_T U_re_b;                     /* '<S35>/Sum5' */
  real32_T DiscreteTimeIntegrator;
  real32_T DiscreteTimeIntegrator1;
  real32_T DiscreteTimeIntegrator_o;
  real32_T DiscreteTimeIntegrator1_f;
  real32_T DiscreteTimeIntegrator_j;
  real32_T DiscreteTimeIntegrator1_e;
  real32_T DiscreteTimeIntegrator_h;
  real32_T DiscreteTimeIntegrator1_h;
  boolean_T Betrieb_n;                 /* '<S23>/MATLAB Function' */
} DW_Strangstromregler_asymetrisc;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_MATLABFunction_m sf_MATLABFunction_e;/* '<S56>/MATLAB Function' */
  DW_Strangstromregler_asymetrisc Strangstromregler_asymetrisch1;
                                    /* '<S10>/Strangstromregler_asymetrisch1' */
  DW_Strangstromregler_asymetrisc Strangstromregler_asymetrisch_h;
                                     /* '<S10>/Strangstromregler_asymetrisch' */
  real32_T Delay_DSTATE_k[20];         /* '<S70>/Delay' */
  real32_T Delay_DSTATE_ki[120];       /* '<S71>/Delay' */
  real32_T Delay_DSTATE_kl[20];        /* '<S72>/Delay' */
  real32_T Delay_DSTATE_b[20];         /* '<S73>/Delay' */
  real32_T I_im;                       /* '<S4>/Merge4' */
  real32_T Merge1;                     /* '<S8>/Merge1' */
  real32_T I_re;                       /* '<S4>/Merge3' */
  real32_T Merge;                      /* '<S8>/Merge' */
  real32_T Merge5;                     /* '<S10>/Merge5' */
  real32_T Merge4;                     /* '<S10>/Merge4' */
  real32_T Merge3;                     /* '<S10>/Merge3' */
  real32_T Delay_DSTATE;               /* '<S3>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S3>/Discrete-Time Integrator' */
  real32_T Accumulator_DSTATE;         /* '<S70>/Accumulator' */
  real32_T Accumulator_DSTATE_d;       /* '<S71>/Accumulator' */
  real32_T Accumulator_DSTATE_f;       /* '<S72>/Accumulator' */
  real32_T Accumulator_DSTATE_n;       /* '<S73>/Accumulator' */
  real32_T Delay_DSTATE_n;             /* '<S14>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_n;/* '<S14>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_h;             /* '<S7>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_f;/* '<S13>/Discrete-Time Integrator' */
  real32_T Delay1_DSTATE;              /* '<S58>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_o;/* '<S58>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_l;             /* '<S58>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S58>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_o;            /* '<S59>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_m;/* '<S59>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_nv;            /* '<S59>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_f;/* '<S59>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_d;            /* '<S57>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTAT_om;/* '<S57>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_j;             /* '<S57>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_a;/* '<S57>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_g;            /* '<S60>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_c;/* '<S60>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_a;             /* '<S60>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_o;/* '<S60>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_oi;           /* '<S61>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S61>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_nm;            /* '<S61>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTA_os;/* '<S61>/Discrete-Time Integrator1' */
  real32_T a;
  real32_T b;
  real32_T c;
  real32_T Gain;                       /* '<S3>/Gain' */
  real32_T Product5_ju;                /* '<S61>/Product5' */
  real32_T im_lim;                     /* '<S59>/MATLAB Function' */
  real32_T re_lim;                     /* '<S59>/MATLAB Function' */
  real32_T Switch2;                    /* '<S15>/Switch2' */
  real32_T Strom_kompensiert;          /* '<S56>/Strom_kompensiert' */
  real32_T Cos2;                       /* '<S56>/Cos2' */
  real32_T Gain1_p;                    /* '<S56>/Gain1' */
  real32_T Gain1;                      /* '<S13>/Gain1' */
  real32_T y;                          /* '<S13>/Sum' */
  real32_T Product_d;                  /* '<S61>/Product' */
  real32_T re_lim_e;                   /* '<S61>/MATLAB Function' */
  real32_T Gain1_k;                    /* '<S58>/Gain1' */
  real32_T U_re;                       /* '<S58>/Sum5' */
  real32_T U_im;                       /* '<S58>/Sum6' */
  real32_T Gain1_e;                    /* '<S59>/Gain1' */
  real32_T U_re_c;                     /* '<S59>/Sum5' */
  real32_T Gain2_n;                    /* '<S59>/Gain2' */
  real32_T U_im_k;                     /* '<S59>/Sum6' */
  real32_T Product3_m;                 /* '<S59>/Product3' */
  real32_T Product2_i;                 /* '<S59>/Product2' */
  real32_T Gain1_d;                    /* '<S57>/Gain1' */
  real32_T Gain2_c;                    /* '<S57>/Gain2' */
  real32_T Product3_h;                 /* '<S57>/Product3' */
  real32_T Product2_o;                 /* '<S57>/Product2' */
  real32_T Gain1_m;                    /* '<S60>/Gain1' */
  real32_T U_re_n;                     /* '<S60>/Sum5' */
  real32_T Gain2_h;                    /* '<S60>/Gain2' */
  real32_T U_im_p;                     /* '<S60>/Sum6' */
  real32_T Product3_l;                 /* '<S60>/Product3' */
  real32_T Product2_l;                 /* '<S60>/Product2' */
  real32_T Gain1_j;                    /* '<S61>/Gain1' */
  real32_T U_re_d;                     /* '<S61>/Sum5' */
  real32_T DiscreteTimeIntegrator;
  real32_T y_i;
  real32_T DiscreteTimeIntegrator_o;
  real32_T DiscreteTimeIntegrator1;
  real32_T DiscreteTimeIntegrator_k;
  real32_T DiscreteTimeIntegrator1_e;
  real32_T U_re_m;
  real32_T U_im_c;
  real32_T DiscreteTimeIntegrator_a;
  real32_T DiscreteTimeIntegrator1_a;
  real32_T DiscreteTimeIntegrator_n;
  real32_T DiscreteTimeIntegrator1_g;
  real32_T c_k;
  int_T idxDelay;
  int8_T switch_case_power_ActiveSubsyst;/* '<S2>/switch_case_power' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S4>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_o; /* '<S10>/Switch Case' */
  int8_T SwitchCase1_ActiveSubsystem;  /* '<S10>/Switch Case1' */
  int8_T SwitchCase2_ActiveSubsystem;  /* '<S10>/Switch Case2' */
  int8_T rtPrevAction;
  int8_T rtAction;
  uint8_T error_speed_limit;
  boolean_T Betrieb;                   /* '<S25>/MATLAB Function' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const real32_T Gain;                 /* '<S10>/Gain' */
} ConstB;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Act_U_ZK;                   /* '<Root>/Act_U_ZK' */
  real32_T Act_Iu;                     /* '<Root>/Act_Iu' */
  real32_T Act_Iv;                     /* '<Root>/Act_Iv' */
  real32_T Act_Iw;                     /* '<Root>/Act_Iw' */
  real32_T Act_theta_u_el;             /* '<Root>/Act_theta_u_el' */
  real32_T Act_w_el;                   /* '<Root>/Act_w_el' */
  real32_T Act_n;                      /* '<Root>/Act_n' */
  real32_T Ref_I_re_ext_mit;           /* '<Root>/Ref_I_re_ext_mit' */
  real32_T Ref_I_im_ext_mit;           /* '<Root>/Ref_I_im_ext_mit' */
  real32_T Ref_n;                      /* '<Root>/Ref_n' */
  uint8_T fl_power;                    /* '<Root>/fl_power' */
  uint8_T fl_control_type;             /* '<Root>/fl_control_type' */
  uint8_T fl_integrator_reset;         /* '<Root>/fl_integrator_reset' */
  uint8_T fl_field_weakening;          /* '<Root>/fl_field_weakening' */
  uint8_T fl_voltage_limitation;       /* '<Root>/fl_voltage_limitation' */
  uint8_T fl_decoupling;               /* '<Root>/fl_decoupling' */
  uint8_T fl_angle_prediction;         /* '<Root>/fl_angle_prediction' */
  uint8_T fl_enable_compensation_current;
                                   /* '<Root>/fl_enable_compensation_current' */
  uint8_T fl_enable_compensation_cogging_;
                            /* '<Root>/fl_enable_compensation_cogging_torque' */
  uint8_T fl_compensat_CT_current;     /* '<Root>/fl_compensat_CT_current' */
  real32_T amplitude_a;                /* '<Root>/amplitude_a' */
  real32_T ordnung_a;                  /* '<Root>/ordnung_a' */
  real32_T phase_a;                    /* '<Root>/phase_a' */
  real32_T amplitude_b;                /* '<Root>/amplitude_b' */
  real32_T ordnung_b;                  /* '<Root>/ordnung_b' */
  real32_T phase_b;                    /* '<Root>/phase_b' */
  real32_T amplitude_c;                /* '<Root>/amplitude_c' */
  real32_T ordnung_c;                  /* '<Root>/ordnung_c' */
  real32_T phase_c;                    /* '<Root>/phase_c' */
  real32_T amplitude_d;                /* '<Root>/amplitude_d' */
  real32_T ordnung_d;                  /* '<Root>/ordnung_d' */
  real32_T phase_d;                    /* '<Root>/phase_d' */
  creal32_T Psi_PM_U;                  /* '<Root>/Psi_PM_U' */
  creal32_T Psi_PM_V;                  /* '<Root>/Psi_PM_V' */
  creal32_T Psi_PM_W;                  /* '<Root>/Psi_PM_W' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T a_U;                        /* '<Root>/a_U' */
  real32_T a_V;                        /* '<Root>/a_V' */
  real32_T a_W;                        /* '<Root>/a_W' */
  real32_T I_re_Ref;                   /* '<Root>/I_re_Ref' */
  real32_T I_im_Ref;                   /* '<Root>/I_im_Ref' */
  uint8_T error_speed_limit;           /* '<Root>/error_speed_limit' */
  boolean_T fault_peak_current_u;      /* '<Root>/fault_peak_current_u' */
  boolean_T fault_rms_current_u;       /* '<Root>/fault_rms_current_u' */
  boolean_T fault_peak_speed;          /* '<Root>/fault_peak_speed' */
  boolean_T fault_max_speed;           /* '<Root>/fault_max_speed' */
  boolean_T fault_rms_current_v;       /* '<Root>/fault_rms_current_v' */
  boolean_T fault_rms_current_w;       /* '<Root>/fault_rms_current_w' */
  boolean_T fault_peak_current_v;      /* '<Root>/fault_peak_current_v' */
  boolean_T fault_peak_current_w;      /* '<Root>/fault_peak_current_w' */
  real32_T Iu_ref;                     /* '<Root>/Iu_ref' */
  real32_T Iv_ref;                     /* '<Root>/Iv_ref' */
  real32_T Iw_ref;                     /* '<Root>/Iw_ref' */
} ExtY;

/* Parameters (default storage) */
struct P_ {
  real32_T K1;                         /* Variable: K1
                                        * Referenced by:
                                        *   '<S32>/Gain1'
                                        *   '<S32>/Gain2'
                                        *   '<S45>/Gain1'
                                        *   '<S45>/Gain2'
                                        *   '<S58>/Gain1'
                                        *   '<S58>/Gain2'
                                        */
  real32_T K2;                         /* Variable: K2
                                        * Referenced by:
                                        *   '<S33>/Gain1'
                                        *   '<S33>/Gain2'
                                        *   '<S46>/Gain1'
                                        *   '<S46>/Gain2'
                                        *   '<S59>/Gain1'
                                        *   '<S59>/Gain2'
                                        */
  real32_T K3;                         /* Variable: K3
                                        * Referenced by:
                                        *   '<S31>/Gain4'
                                        *   '<S44>/Gain4'
                                        *   '<S57>/Gain4'
                                        */
  real32_T K4;                         /* Variable: K4
                                        * Referenced by:
                                        *   '<S34>/Gain1'
                                        *   '<S34>/Gain2'
                                        *   '<S47>/Gain1'
                                        *   '<S47>/Gain2'
                                        *   '<S60>/Gain1'
                                        *   '<S60>/Gain2'
                                        */
  real32_T K6;                         /* Variable: K6
                                        * Referenced by:
                                        *   '<S35>/Gain1'
                                        *   '<S35>/Gain2'
                                        *   '<S48>/Gain1'
                                        *   '<S48>/Gain2'
                                        *   '<S61>/Gain1'
                                        *   '<S61>/Gain2'
                                        */
  real32_T Kp;                         /* Variable: Kp
                                        * Referenced by:
                                        *   '<S32>/Gain6'
                                        *   '<S33>/Gain6'
                                        *   '<S34>/Gain6'
                                        *   '<S35>/Gain6'
                                        *   '<S45>/Gain6'
                                        *   '<S46>/Gain6'
                                        *   '<S47>/Gain6'
                                        *   '<S48>/Gain6'
                                        *   '<S58>/Gain6'
                                        *   '<S59>/Gain6'
                                        *   '<S60>/Gain6'
                                        *   '<S61>/Gain6'
                                        */
  real32_T i_max_peak;                 /* Variable: i_max_peak
                                        * Referenced by:
                                        *   '<S5>/Constant'
                                        *   '<S5>/Constant4'
                                        *   '<S5>/Constant6'
                                        */
  real32_T i_max_rms;                  /* Variable: i_max_rms
                                        * Referenced by:
                                        *   '<S5>/Constant1'
                                        *   '<S5>/Constant5'
                                        *   '<S5>/Constant7'
                                        */
  real32_T i_ref_max;                  /* Variable: i_ref_max
                                        * Referenced by:
                                        *   '<S7>/function_Eckdrehzahl'
                                        *   '<S7>/Constant'
                                        *   '<S9>/Constant'
                                        */
  real32_T n_max;                      /* Variable: n_max
                                        * Referenced by: '<S5>/Constant3'
                                        */
  real32_T n_max_peak;                 /* Variable: n_max_peak
                                        * Referenced by: '<S5>/Constant2'
                                        */
  real32_T n_ref_max;                  /* Variable: n_ref_max
                                        * Referenced by: '<S7>/function_Eckdrehzahl'
                                        */
};

/* Parameters (default storage) */
typedef struct P_ P;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

/* Block parameters (default storage) */
extern P rtP;
extern const ConstB rtConstB;          /* constant block i/o */

/* Model entry point functions */
extern void uz_codegen0_initialize(RT_MODEL *const rtM);
extern void uz_codegen0_step(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S15>/Data Type Duplicate' : Unused code path elimination
 * Block '<S15>/Data Type Propagation' : Unused code path elimination
 * Block '<S16>/Data Type Duplicate' : Unused code path elimination
 * Block '<S16>/Data Type Propagation' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S31>/Scope' : Unused code path elimination
 * Block '<S32>/Scope' : Unused code path elimination
 * Block '<S33>/Scope' : Unused code path elimination
 * Block '<S34>/Scope' : Unused code path elimination
 * Block '<S35>/Scope' : Unused code path elimination
 * Block '<S44>/Scope' : Unused code path elimination
 * Block '<S45>/Scope' : Unused code path elimination
 * Block '<S46>/Scope' : Unused code path elimination
 * Block '<S47>/Scope' : Unused code path elimination
 * Block '<S48>/Scope' : Unused code path elimination
 * Block '<S57>/Scope' : Unused code path elimination
 * Block '<S58>/Scope' : Unused code path elimination
 * Block '<S59>/Scope' : Unused code path elimination
 * Block '<S60>/Scope' : Unused code path elimination
 * Block '<S61>/Scope' : Unused code path elimination
 */

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
 * hilite_system('uz_codegen/uz_codegen')    - opens subsystem uz_codegen/uz_codegen
 * hilite_system('uz_codegen/uz_codegen/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen'
 * '<S1>'   : 'uz_codegen/uz_codegen'
 * '<S2>'   : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch'
 * '<S3>'   : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/PT2'
 * '<S4>'   : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch'
 * '<S5>'   : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung'
 * '<S6>'   : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/aus'
 * '<S7>'   : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Drehzahlregler'
 * '<S8>'   : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Rastmomentstrom mit Kompensieren Switch Case'
 * '<S9>'   : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Stromvorgabe_extern'
 * '<S10>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem'
 * '<S11>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation'
 * '<S12>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Drehzahlregler/Function_Feldschwaeche'
 * '<S13>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Drehzahlregler/PI_for_Limiter'
 * '<S14>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Drehzahlregler/PT1_V_n'
 * '<S15>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Drehzahlregler/Saturation Dynamic'
 * '<S16>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Drehzahlregler/Saturation Dynamic1'
 * '<S17>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Drehzahlregler/function_Eckdrehzahl'
 * '<S18>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Rastmomentstrom mit Kompensieren Switch Case/Switch Case Action Subsystem'
 * '<S19>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Rastmomentstrom mit Kompensieren Switch Case/Switch Case Action Subsystem1'
 * '<S20>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Rastmomentstrom mit Kompensieren Switch Case/Switch Case Action Subsystem2'
 * '<S21>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Rastmomentstrom mit Kompensieren Switch Case/Switch Case Action Subsystem3'
 * '<S22>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Stromvorgabe_extern/Function_I_limit'
 * '<S23>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch'
 * '<S24>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1'
 * '<S25>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2'
 * '<S26>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Switch Case Action Subsystem'
 * '<S27>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Switch Case Action Subsystem1'
 * '<S28>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Switch Case Action Subsystem2'
 * '<S29>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/MATLAB Function'
 * '<S30>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch'
 * '<S31>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler'
 * '<S32>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler'
 * '<S33>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1'
 * '<S34>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2'
 * '<S35>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3'
 * '<S36>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S37>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/MATLAB Function'
 * '<S38>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/MATLAB Function'
 * '<S39>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/MATLAB Function'
 * '<S40>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/MATLAB Function'
 * '<S41>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/MATLAB Function'
 * '<S42>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/MATLAB Function'
 * '<S43>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch'
 * '<S44>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler'
 * '<S45>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler'
 * '<S46>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1'
 * '<S47>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2'
 * '<S48>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3'
 * '<S49>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S50>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/MATLAB Function'
 * '<S51>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/MATLAB Function'
 * '<S52>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/MATLAB Function'
 * '<S53>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/MATLAB Function'
 * '<S54>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/MATLAB Function'
 * '<S55>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/MATLAB Function'
 * '<S56>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch'
 * '<S57>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler'
 * '<S58>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler'
 * '<S59>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1'
 * '<S60>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2'
 * '<S61>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3'
 * '<S62>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S63>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/MATLAB Function'
 * '<S64>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/MATLAB Function'
 * '<S65>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/MATLAB Function'
 * '<S66>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/MATLAB Function'
 * '<S67>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/MATLAB Function'
 * '<S68>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation'
 * '<S69>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Switch Case Action Subsystem'
 * '<S70>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean'
 * '<S71>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean1'
 * '<S72>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean2'
 * '<S73>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean3'
 */

/*-
 * Requirements for '<Root>': uz_codegen0
 */
#endif                                 /* RTW_HEADER_uz_codegen0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
