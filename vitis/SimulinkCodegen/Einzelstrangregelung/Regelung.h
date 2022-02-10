/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Regelung.h
 *
 * Code generated for Simulink model 'Regelung'.
 *
 * Model version                  : 2.26
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Sep 20 14:43:03 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_Regelung_h_
#define RTW_HEADER_Regelung_h_
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef Regelung_COMMON_INCLUDES_
#define Regelung_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Regelung_COMMON_INCLUDES_ */

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

#define Regelung_M                     (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T Delay_DSTATE_k[20];         /* '<S52>/Delay' */
  real32_T Delay_DSTATE_l[120];        /* '<S53>/Delay' */
  real32_T Delay_DSTATE_f[20];         /* '<S54>/Delay' */
  real32_T Delay_DSTATE_b[20];         /* '<S55>/Delay' */
  real32_T Diff_i[2];                  /* '<S22>/Diff' */
  real32_T I_re;                       /* '<S3>/Merge' */
  real32_T I_im;                       /* '<S3>/Merge1' */
  real32_T Merge5;                     /* '<S7>/Merge5' */
  real32_T Merge4;                     /* '<S7>/Merge4' */
  real32_T Merge3;                     /* '<S7>/Merge3' */
  real32_T Delay_DSTATE;               /* '<S2>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S2>/Discrete-Time Integrator' */
  real32_T Accumulator_DSTATE;         /* '<S52>/Accumulator' */
  real32_T Accumulator_DSTATE_k;       /* '<S53>/Accumulator' */
  real32_T Accumulator_DSTATE_g;       /* '<S54>/Accumulator' */
  real32_T Accumulator_DSTATE_f;       /* '<S55>/Accumulator' */
  real32_T Delay_DSTATE_p;             /* '<S11>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_a;/* '<S11>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_j;             /* '<S6>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_d;/* '<S10>/Discrete-Time Integrator' */
  real32_T UD_1_DSTATE;                /* '<S42>/UD' */
  real32_T UD_2_DSTATE;                /* '<S42>/UD' */
  real32_T Delay1_DSTATE;              /* '<S47>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_o;/* '<S47>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_a;             /* '<S47>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S47>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_k;            /* '<S45>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_f;/* '<S45>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_ja;            /* '<S45>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_n;/* '<S45>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_e;            /* '<S46>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_e;/* '<S46>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_c;             /* '<S46>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_l;/* '<S46>/Discrete-Time Integrator1' */
  real32_T UD_1_DSTATE_i;              /* '<S32>/UD' */
  real32_T UD_2_DSTATE_a;              /* '<S32>/UD' */
  real32_T Delay1_DSTATE_a;            /* '<S37>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_i;/* '<S37>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_g;             /* '<S37>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_h;/* '<S37>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_k3;           /* '<S35>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S35>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_i;             /* '<S35>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_e;/* '<S35>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_n;            /* '<S36>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTAT_a3;/* '<S36>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_gj;            /* '<S36>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_i;/* '<S36>/Discrete-Time Integrator1' */
  real32_T UD_1_DSTATE_c;              /* '<S22>/UD' */
  real32_T UD_2_DSTATE_at;             /* '<S22>/UD' */
  real32_T Delay1_DSTATE_d;            /* '<S27>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTAT_oq;/* '<S27>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_m;             /* '<S27>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTA_i0;/* '<S27>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_b;            /* '<S25>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_n;/* '<S25>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_al;            /* '<S25>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_k;/* '<S25>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_i;            /* '<S26>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_l;/* '<S26>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_d;             /* '<S26>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTA_iy;/* '<S26>/Discrete-Time Integrator1' */
  real32_T U_FA;
  real32_T a;
  real32_T b;
  real32_T Gain;                       /* '<S2>/Gain' */
  real32_T Gain4_i;                    /* '<S26>/Gain4' */
  real32_T Product4_k;                 /* '<S26>/Product4' */
  real32_T U_re_c;                     /* '<S27>/Sum5' */
  real32_T Gain2_n;                    /* '<S27>/Gain2' */
  real32_T U_im_g;                     /* '<S27>/Sum6' */
  real32_T re_lim_d;                   /* '<S27>/MATLAB Function' */
  real32_T im_lim_c;                   /* '<S27>/MATLAB Function' */
  real32_T Product3_fd;                /* '<S27>/Product3' */
  real32_T Switch2;                    /* '<S12>/Switch2' */
  real32_T Gain1;                      /* '<S10>/Gain1' */
  real32_T Gain1_cp;                   /* '<S25>/Gain1' */
  real32_T y;                          /* '<S10>/Sum' */
  real32_T Gain2_i;                    /* '<S25>/Gain2' */
  real32_T im_lim_b;                   /* '<S25>/MATLAB Function' */
  real32_T Product3_b;                 /* '<S25>/Product3' */
  int_T idxDelay;
  int8_T switch_case_power_ActiveSubsyst;/* '<S1>/switch_case_power' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S3>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_f; /* '<S7>/Switch Case' */
  int8_T SwitchCase1_ActiveSubsystem;  /* '<S7>/Switch Case1' */
  int8_T SwitchCase2_ActiveSubsystem;  /* '<S7>/Switch Case2' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Act_Iu;                     /* '<Root>/Act_Iu' */
  real32_T Act_Iv;                     /* '<Root>/Act_Iv' */
  real32_T Act_Iw;                     /* '<Root>/Act_Iw' */
  real32_T Act_theta_u_el;             /* '<Root>/Act_theta_u_el' */
  real32_T Act_w_el;                   /* '<Root>/Act_w_el' */
  real32_T Act_U_ZK;                   /* '<Root>/Act_U_ZK' */
  real32_T Act_n;                      /* '<Root>/Act_n' */
  real32_T Ref_n;                      /* '<Root>/Ref_n' */
  real32_T Ref_I_re_ext;               /* '<Root>/Ref_I_re_ext' */
  real32_T Ref_I_im_ext;               /* '<Root>/Ref_I_im_ext' */
  uint8_T fl_power;                    /* '<Root>/fl_power' */
  uint8_T fl_control_type;             /* '<Root>/fl_control_type' */
  uint8_T fl_integrator_reset;         /* '<Root>/fl_integrator_reset' */
  uint8_T fl_field_weakening;          /* '<Root>/fl_field_weakening' */
  uint8_T fl_voltage_limitation;       /* '<Root>/fl_voltage_limitation' */
  uint8_T fl_decoupling;               /* '<Root>/fl_decoupling' */
  uint8_T fl_angle_prediction;         /* '<Root>/fl_angle_prediction' */
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
                                        *   '<S27>/Gain1'
                                        *   '<S27>/Gain2'
                                        *   '<S37>/Gain1'
                                        *   '<S37>/Gain2'
                                        *   '<S47>/Gain1'
                                        *   '<S47>/Gain2'
                                        */
  real32_T K2;                         /* Variable: K2
                                        * Referenced by:
                                        *   '<S25>/Gain4'
                                        *   '<S35>/Gain4'
                                        *   '<S45>/Gain4'
                                        */
  real32_T K3;                         /* Variable: K3
                                        * Referenced by:
                                        *   '<S26>/Gain4'
                                        *   '<S36>/Gain4'
                                        *   '<S46>/Gain4'
                                        */
  real32_T Kis_n;                      /* Variable: Kis_n
                                        * Referenced by: '<S10>/Gain1'
                                        */
  real32_T Kp;                         /* Variable: Kp
                                        * Referenced by:
                                        *   '<S27>/Gain6'
                                        *   '<S37>/Gain6'
                                        *   '<S47>/Gain6'
                                        */
  real32_T Kp_n;                       /* Variable: Kp_n
                                        * Referenced by: '<S10>/Gain'
                                        */
  real32_T L;                          /* Variable: L
                                        * Referenced by:
                                        *   '<S6>/Function_Feldschwaeche'
                                        *   '<S6>/function_Eckdrehzahl'
                                        */
  real32_T Offset_V;                   /* Variable: Offset_V
                                        * Referenced by: '<S16>/Constant'
                                        */
  real32_T Offset_W;                   /* Variable: Offset_W
                                        * Referenced by: '<S17>/Constant'
                                        */
  real32_T Psi_PM;                     /* Variable: Psi_PM
                                        * Referenced by:
                                        *   '<S6>/Function_Feldschwaeche'
                                        *   '<S6>/function_Eckdrehzahl'
                                        */
  real32_T R;                          /* Variable: R
                                        * Referenced by: '<S6>/function_Eckdrehzahl'
                                        */
  real32_T T_R;                        /* Variable: T_R
                                        * Referenced by:
                                        *   '<S2>/Gain'
                                        *   '<S7>/Constant'
                                        *   '<S10>/Gain1'
                                        *   '<S11>/Gain'
                                        *   '<S25>/Gain1'
                                        *   '<S25>/Gain2'
                                        *   '<S26>/Gain1'
                                        *   '<S26>/Gain2'
                                        *   '<S27>/Gain1'
                                        *   '<S27>/Gain2'
                                        *   '<S35>/Gain1'
                                        *   '<S35>/Gain2'
                                        *   '<S36>/Gain1'
                                        *   '<S36>/Gain2'
                                        *   '<S37>/Gain1'
                                        *   '<S37>/Gain2'
                                        *   '<S45>/Gain1'
                                        *   '<S45>/Gain2'
                                        *   '<S46>/Gain1'
                                        *   '<S46>/Gain2'
                                        *   '<S47>/Gain1'
                                        *   '<S47>/Gain2'
                                        */
  real32_T T_VF_n;                     /* Variable: T_VF_n
                                        * Referenced by: '<S11>/Gain'
                                        */
  real32_T i_max_peak;                 /* Variable: i_max_peak
                                        * Referenced by:
                                        *   '<S4>/Constant'
                                        *   '<S4>/Constant4'
                                        *   '<S4>/Constant6'
                                        */
  real32_T i_max_rms;                  /* Variable: i_max_rms
                                        * Referenced by:
                                        *   '<S4>/Constant1'
                                        *   '<S4>/Constant5'
                                        *   '<S4>/Constant7'
                                        */
  real32_T i_ref_max;                  /* Variable: i_ref_max
                                        * Referenced by:
                                        *   '<S6>/function_Eckdrehzahl'
                                        *   '<S6>/Constant'
                                        *   '<S8>/Constant'
                                        */
  real32_T max_current_samplenumber;   /* Variable: max_current_samplenumber
                                        * Referenced by:
                                        *   '<S52>/Gain'
                                        *   '<S54>/Gain'
                                        *   '<S55>/Gain'
                                        */
  real32_T max_speed_samplenumber;     /* Variable: max_speed_samplenumber
                                        * Referenced by: '<S53>/Gain'
                                        */
  real32_T n_max;                      /* Variable: n_max
                                        * Referenced by: '<S4>/Constant3'
                                        */
  real32_T n_max_peak;                 /* Variable: n_max_peak
                                        * Referenced by: '<S4>/Constant2'
                                        */
  real32_T n_ref_max;                  /* Variable: n_ref_max
                                        * Referenced by: '<S6>/function_Eckdrehzahl'
                                        */
  real32_T p;                          /* Variable: p
                                        * Referenced by: '<S6>/function_Eckdrehzahl'
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

/* Model entry point functions */
extern void Regelung_initialize(RT_MODEL *const rtM);
extern void Regelung_step(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Propagation' : Unused code path elimination
 * Block '<S13>/Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S21>/Scope2' : Unused code path elimination
 * Block '<S25>/Scope' : Unused code path elimination
 * Block '<S26>/Scope' : Unused code path elimination
 * Block '<S27>/Scope' : Unused code path elimination
 * Block '<S31>/Scope2' : Unused code path elimination
 * Block '<S35>/Scope' : Unused code path elimination
 * Block '<S36>/Scope' : Unused code path elimination
 * Block '<S37>/Scope' : Unused code path elimination
 * Block '<S41>/Scope2' : Unused code path elimination
 * Block '<S45>/Scope' : Unused code path elimination
 * Block '<S46>/Scope' : Unused code path elimination
 * Block '<S47>/Scope' : Unused code path elimination
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
 * hilite_system('uz_codegen_Einzelstrang/Regelung-Einzelstrang')    - opens subsystem uz_codegen_Einzelstrang/Regelung-Einzelstrang
 * hilite_system('uz_codegen_Einzelstrang/Regelung-Einzelstrang/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen_Einzelstrang'
 * '<S1>'   : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang'
 * '<S2>'   : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/PT1'
 * '<S3>'   : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung'
 * '<S4>'   : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Sicherheitsabschaltung'
 * '<S5>'   : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/aus'
 * '<S6>'   : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Drehzahlregler'
 * '<S7>'   : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung'
 * '<S8>'   : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromvorgabe_extern'
 * '<S9>'   : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Drehzahlregler/Function_Feldschwaeche'
 * '<S10>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Drehzahlregler/PI_for_Limiter'
 * '<S11>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Drehzahlregler/PT1_V_n'
 * '<S12>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Drehzahlregler/Saturation Dynamic'
 * '<S13>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Drehzahlregler/Saturation Dynamic1'
 * '<S14>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Drehzahlregler/function_Eckdrehzahl'
 * '<S15>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang U'
 * '<S16>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang V'
 * '<S17>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang W'
 * '<S18>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Switch Case Action Subsystem'
 * '<S19>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Switch Case Action Subsystem1'
 * '<S20>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Switch Case Action Subsystem2'
 * '<S21>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang U/Einzelstrangstromregler'
 * '<S22>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang U/Einzelstrangstromregler/Difference'
 * '<S23>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang U/Einzelstrangstromregler/MATLAB Function'
 * '<S24>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang U/Einzelstrangstromregler/Referenzstromerzeugung'
 * '<S25>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang U/Einzelstrangstromregler/resonater-I-Regler'
 * '<S26>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang U/Einzelstrangstromregler/resonater-I-Regler1'
 * '<S27>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang U/Einzelstrangstromregler/resonater-PI-Regler'
 * '<S28>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang U/Einzelstrangstromregler/resonater-I-Regler/MATLAB Function'
 * '<S29>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang U/Einzelstrangstromregler/resonater-I-Regler1/MATLAB Function'
 * '<S30>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang U/Einzelstrangstromregler/resonater-PI-Regler/MATLAB Function'
 * '<S31>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang V/Einzelstrangstromregler'
 * '<S32>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang V/Einzelstrangstromregler/Difference'
 * '<S33>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang V/Einzelstrangstromregler/MATLAB Function'
 * '<S34>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang V/Einzelstrangstromregler/Referenzstromerzeugung'
 * '<S35>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang V/Einzelstrangstromregler/resonater-I-Regler'
 * '<S36>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang V/Einzelstrangstromregler/resonater-I-Regler1'
 * '<S37>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang V/Einzelstrangstromregler/resonater-PI-Regler'
 * '<S38>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang V/Einzelstrangstromregler/resonater-I-Regler/MATLAB Function'
 * '<S39>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang V/Einzelstrangstromregler/resonater-I-Regler1/MATLAB Function'
 * '<S40>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang V/Einzelstrangstromregler/resonater-PI-Regler/MATLAB Function'
 * '<S41>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang W/Einzelstrangstromregler'
 * '<S42>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang W/Einzelstrangstromregler/Difference'
 * '<S43>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang W/Einzelstrangstromregler/MATLAB Function'
 * '<S44>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang W/Einzelstrangstromregler/Referenzstromerzeugung'
 * '<S45>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang W/Einzelstrangstromregler/resonater-I-Regler'
 * '<S46>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang W/Einzelstrangstromregler/resonater-I-Regler1'
 * '<S47>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang W/Einzelstrangstromregler/resonater-PI-Regler'
 * '<S48>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang W/Einzelstrangstromregler/resonater-I-Regler/MATLAB Function'
 * '<S49>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang W/Einzelstrangstromregler/resonater-I-Regler1/MATLAB Function'
 * '<S50>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromregelung/Strang W/Einzelstrangstromregler/resonater-PI-Regler/MATLAB Function'
 * '<S51>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Regelung/Stromvorgabe_extern/Function_I_limit'
 * '<S52>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Sicherheitsabschaltung/moving mean'
 * '<S53>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Sicherheitsabschaltung/moving mean1'
 * '<S54>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Sicherheitsabschaltung/moving mean2'
 * '<S55>'  : 'uz_codegen_Einzelstrang/Regelung-Einzelstrang/Sicherheitsabschaltung/moving mean3'
 */

/*-
 * Requirements for '<Root>': Regelung
 */
#endif                                 /* RTW_HEADER_Regelung_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
