/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 4.6
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Thu Nov 24 11:37:38 2022
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
  uint64_T frac;
  real32_T Delay1_DSTATE;              /* '<S31>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S31>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE;               /* '<S31>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S31>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_m;            /* '<S32>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_d;/* '<S32>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_a;             /* '<S32>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_m;/* '<S32>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_g;            /* '<S33>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_i;/* '<S33>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_b;             /* '<S33>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_k;/* '<S33>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_i;            /* '<S34>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTAT_if;/* '<S34>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_h;             /* '<S34>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_a;/* '<S34>/Discrete-Time Integrator1' */
  real32_T theta_e;                    /* '<S23>/Sum1' */
  real32_T re_lim_b;                   /* '<S33>/MATLAB Function' */
  real32_T Delay1_m;                   /* '<S34>/Delay1' */
  real32_T im_lim_o4;                  /* '<S34>/MATLAB Function' */
  real32_T im_lim_mv;                  /* '<S31>/MATLAB Function' */
  real32_T re_lim_l;                   /* '<S31>/MATLAB Function' */
  real32_T im_lim_l;                   /* '<S32>/MATLAB Function' */
  real32_T re_lim_i;                   /* '<S32>/MATLAB Function' */
  real32_T im_lim_k;                   /* '<S33>/MATLAB Function' */
  real32_T Sum_o;                      /* '<S33>/Sum' */
  real32_T re_lim_g;                   /* '<S34>/MATLAB Function' */
  real32_T Strom_kompensiert_l;        /* '<S30>/Strom_kompensiert' */
  real32_T Sum_j;                      /* '<S32>/Sum' */
  real32_T Add1_l;                     /* '<S23>/Add1' */
  real32_T Sum_d;                      /* '<S34>/Sum' */
  real32_T Gain1_h;                    /* '<S31>/Gain1' */
  real32_T U_re_o;                     /* '<S31>/Sum5' */
  real32_T Gain2_nl;                   /* '<S31>/Gain2' */
  real32_T U_im_i;                     /* '<S31>/Sum6' */
  real32_T Gain1_g;                    /* '<S32>/Gain1' */
  real32_T U_re_h;                     /* '<S32>/Sum5' */
  real32_T Gain2_d;                    /* '<S32>/Gain2' */
  real32_T U_im_pl;                    /* '<S32>/Sum6' */
  real32_T Gain1_n;                    /* '<S33>/Gain1' */
  real32_T U_re_j;                     /* '<S33>/Sum5' */
  real32_T Gain2_e;                    /* '<S33>/Gain2' */
  real32_T U_im_pt;                    /* '<S33>/Sum6' */
  real32_T U_re_b;                     /* '<S34>/Sum5' */
  real32_T Gain2_m;                    /* '<S34>/Gain2' */
  real32_T U_im_f;                     /* '<S34>/Sum6' */
  real32_T DiscreteTimeIntegrator;
  real32_T DiscreteTimeIntegrator1;
  real32_T DiscreteTimeIntegrator_o;
  real32_T DiscreteTimeIntegrator1_f;
  real32_T DiscreteTimeIntegrator_j;
  real32_T DiscreteTimeIntegrator1_e;
  real32_T DiscreteTimeIntegrator1_h;
  uint32_T bpIdx;
  int16_T SignCorrected_h;             /* '<S60>/SignCorrected' */
  int16_T SignCorrected_cw;            /* '<S103>/SignCorrected' */
  int16_T SignCorrected_o;             /* '<S105>/SignCorrected' */
  uint16_T CastU16En16_jv;             /* '<S60>/CastU16En16' */
  uint16_T rtb_CastU16En16_jv_m;
  uint16_T rtb_CastU16En16_jv_tmp;
  uint16_T rtb_CastU16En16_jv_tmp_tmp;
  boolean_T LTEp25_my;                 /* '<S60>/LTEp25' */
  boolean_T GTEp75_cz;                 /* '<S60>/GTEp75' */
  boolean_T GTEp75_o;                  /* '<S73>/GTEp75' */
} DW_Strangstromregler_asymetrisc;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_MATLABFunction_m sf_MATLABFunction_e;/* '<S184>/MATLAB Function' */
  DW_Strangstromregler_asymetrisc Strangstromregler_asymetrisch1;
                                    /* '<S10>/Strangstromregler_asymetrisch1' */
  DW_Strangstromregler_asymetrisc Strangstromregler_asymetrisch_h;
                                     /* '<S10>/Strangstromregler_asymetrisch' */
  uint64_T frac;
  real32_T Delay_DSTATE_k[20];         /* '<S274>/Delay' */
  real32_T Delay_DSTATE_ki[120];       /* '<S275>/Delay' */
  real32_T Delay_DSTATE_kl[20];        /* '<S276>/Delay' */
  real32_T Delay_DSTATE_b[20];         /* '<S277>/Delay' */
  real32_T I_im;                       /* '<S4>/Merge4' */
  real32_T Merge1;                     /* '<S8>/Merge1' */
  real32_T I_re;                       /* '<S4>/Merge3' */
  real32_T Merge;                      /* '<S8>/Merge' */
  real32_T Merge5;                     /* '<S10>/Merge5' */
  real32_T Merge4;                     /* '<S10>/Merge4' */
  real32_T Merge3;                     /* '<S10>/Merge3' */
  real32_T Delay_DSTATE;               /* '<S3>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S3>/Discrete-Time Integrator' */
  real32_T Accumulator_DSTATE;         /* '<S274>/Accumulator' */
  real32_T Accumulator_DSTATE_d;       /* '<S275>/Accumulator' */
  real32_T Accumulator_DSTATE_f;       /* '<S276>/Accumulator' */
  real32_T Accumulator_DSTATE_n;       /* '<S277>/Accumulator' */
  real32_T Delay_DSTATE_n;             /* '<S14>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_n;/* '<S14>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_h;             /* '<S7>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_f;/* '<S13>/Discrete-Time Integrator' */
  real32_T Delay1_DSTATE;              /* '<S185>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_o;/* '<S185>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_l;             /* '<S185>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S185>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_o;            /* '<S186>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_m;/* '<S186>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_nv;            /* '<S186>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_f;/* '<S186>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_g;            /* '<S187>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_c;/* '<S187>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_a;             /* '<S187>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_o;/* '<S187>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_oi;           /* '<S188>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S188>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_nm;            /* '<S188>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTA_os;/* '<S188>/Discrete-Time Integrator1' */
  real32_T a;
  real32_T b;
  real32_T c;
  real32_T Gain;                       /* '<S3>/Gain' */
  real32_T Add;                        /* '<S4>/Add' */
  real32_T theta_b;                    /* '<S25>/Sum1' */
  real32_T Switch2;                    /* '<S15>/Switch2' */
  real32_T Gain1;                      /* '<S13>/Gain1' */
  real32_T Delay1;                     /* '<S188>/Delay1' */
  real32_T y;                          /* '<S13>/Sum' */
  real32_T Sum_cr;                     /* '<S187>/Sum' */
  real32_T re_lim_e;                   /* '<S188>/MATLAB Function' */
  real32_T Strom_kompensiert;          /* '<S184>/Strom_kompensiert' */
  real32_T Sum_a5;                     /* '<S186>/Sum' */
  real32_T Add1;                       /* '<S25>/Add1' */
  real32_T Sum_a;                      /* '<S188>/Sum' */
  real32_T Gain1_k;                    /* '<S185>/Gain1' */
  real32_T U_re;                       /* '<S185>/Sum5' */
  real32_T U_im;                       /* '<S185>/Sum6' */
  real32_T Gain1_e;                    /* '<S186>/Gain1' */
  real32_T U_re_c;                     /* '<S186>/Sum5' */
  real32_T Gain2_n;                    /* '<S186>/Gain2' */
  real32_T U_im_k;                     /* '<S186>/Sum6' */
  real32_T Gain1_m;                    /* '<S187>/Gain1' */
  real32_T U_re_n;                     /* '<S187>/Sum5' */
  real32_T Gain2_h;                    /* '<S187>/Gain2' */
  real32_T U_im_p;                     /* '<S187>/Sum6' */
  real32_T U_re_d;                     /* '<S188>/Sum5' */
  real32_T Gain2_i;                    /* '<S188>/Gain2' */
  real32_T U_im_c;                     /* '<S188>/Sum6' */
  real32_T DiscreteTimeIntegrator;
  real32_T y_i;
  real32_T DiscreteTimeIntegrator_o;
  real32_T DiscreteTimeIntegrator1;
  real32_T DiscreteTimeIntegrator_k;
  real32_T DiscreteTimeIntegrator1_e;
  real32_T DiscreteTimeIntegrator_a;
  real32_T DiscreteTimeIntegrator1_a;
  real32_T DiscreteTimeIntegrator1_g;
  int_T idxDelay;
  uint32_T bpIdx;
  int16_T SignCorrected_a;             /* '<S273>/SignCorrected' */
  int16_T SignCorrected_c;             /* '<S257>/SignCorrected' */
  int16_T SignCorrected_d;             /* '<S259>/SignCorrected' */
  uint16_T CastU16En16_h;              /* '<S273>/CastU16En16' */
  uint16_T rtb_CastU16En16_h_m;
  uint16_T rtb_CastU16En16_h_tmp_tmp;
  int8_T switch_case_power_ActiveSubsyst;/* '<S2>/switch_case_power' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S4>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_o; /* '<S10>/Switch Case' */
  int8_T SwitchCase1_ActiveSubsystem;  /* '<S10>/Switch Case1' */
  int8_T SwitchCase2_ActiveSubsystem;  /* '<S10>/Switch Case2' */
  int8_T rtPrevAction;
  int8_T rtAction;
  uint8_T error_speed_limit;
  boolean_T LTEp50_j;                  /* '<S273>/LTEp50' */
  boolean_T GTEp75;                    /* '<S214>/GTEp75' */
  boolean_T GTEp75_b;                  /* '<S227>/GTEp75' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const real32_T Gain;                 /* '<S10>/Gain' */
} ConstB;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: YData)
   * Referenced by:
   *   '<S266>/Look-Up Table'
   *   '<S268>/Look-Up Table'
   *   '<S270>/Look-Up Table'
   *   '<S272>/Look-Up Table'
   *   '<S42>/Look-Up Table'
   *   '<S44>/Look-Up Table'
   *   '<S46>/Look-Up Table'
   *   '<S48>/Look-Up Table'
   *   '<S50>/Look-Up Table'
   *   '<S52>/Look-Up Table'
   *   '<S59>/Look-Up Table'
   *   '<S61>/Look-Up Table'
   *   '<S63>/Look-Up Table'
   *   '<S65>/Look-Up Table'
   *   '<S72>/Look-Up Table'
   *   '<S74>/Look-Up Table'
   *   '<S76>/Look-Up Table'
   *   '<S78>/Look-Up Table'
   *   '<S85>/Look-Up Table'
   *   '<S87>/Look-Up Table'
   *   '<S89>/Look-Up Table'
   *   '<S91>/Look-Up Table'
   *   '<S98>/Look-Up Table'
   *   '<S100>/Look-Up Table'
   *   '<S102>/Look-Up Table'
   *   '<S104>/Look-Up Table'
   *   '<S119>/Look-Up Table'
   *   '<S121>/Look-Up Table'
   *   '<S123>/Look-Up Table'
   *   '<S125>/Look-Up Table'
   *   '<S127>/Look-Up Table'
   *   '<S129>/Look-Up Table'
   *   '<S136>/Look-Up Table'
   *   '<S138>/Look-Up Table'
   *   '<S140>/Look-Up Table'
   *   '<S142>/Look-Up Table'
   *   '<S149>/Look-Up Table'
   *   '<S151>/Look-Up Table'
   *   '<S153>/Look-Up Table'
   *   '<S155>/Look-Up Table'
   *   '<S162>/Look-Up Table'
   *   '<S164>/Look-Up Table'
   *   '<S166>/Look-Up Table'
   *   '<S168>/Look-Up Table'
   *   '<S175>/Look-Up Table'
   *   '<S177>/Look-Up Table'
   *   '<S179>/Look-Up Table'
   *   '<S181>/Look-Up Table'
   *   '<S196>/Look-Up Table'
   *   '<S198>/Look-Up Table'
   *   '<S200>/Look-Up Table'
   *   '<S202>/Look-Up Table'
   *   '<S204>/Look-Up Table'
   *   '<S206>/Look-Up Table'
   *   '<S213>/Look-Up Table'
   *   '<S215>/Look-Up Table'
   *   '<S217>/Look-Up Table'
   *   '<S219>/Look-Up Table'
   *   '<S226>/Look-Up Table'
   *   '<S228>/Look-Up Table'
   *   '<S230>/Look-Up Table'
   *   '<S232>/Look-Up Table'
   *   '<S239>/Look-Up Table'
   *   '<S241>/Look-Up Table'
   *   '<S243>/Look-Up Table'
   *   '<S245>/Look-Up Table'
   *   '<S252>/Look-Up Table'
   *   '<S254>/Look-Up Table'
   *   '<S256>/Look-Up Table'
   *   '<S258>/Look-Up Table'
   */
  int16_T pooled18[16385];
} ConstP;

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
                                        *   '<S31>/Gain1'
                                        *   '<S31>/Gain2'
                                        *   '<S108>/Gain1'
                                        *   '<S108>/Gain2'
                                        *   '<S185>/Gain1'
                                        *   '<S185>/Gain2'
                                        */
  real32_T K2;                         /* Variable: K2
                                        * Referenced by:
                                        *   '<S32>/Gain1'
                                        *   '<S32>/Gain2'
                                        *   '<S109>/Gain1'
                                        *   '<S109>/Gain2'
                                        *   '<S186>/Gain1'
                                        *   '<S186>/Gain2'
                                        */
  real32_T K4;                         /* Variable: K4
                                        * Referenced by:
                                        *   '<S33>/Gain1'
                                        *   '<S33>/Gain2'
                                        *   '<S110>/Gain1'
                                        *   '<S110>/Gain2'
                                        *   '<S187>/Gain1'
                                        *   '<S187>/Gain2'
                                        */
  real32_T K6;                         /* Variable: K6
                                        * Referenced by:
                                        *   '<S34>/Gain1'
                                        *   '<S34>/Gain2'
                                        *   '<S111>/Gain1'
                                        *   '<S111>/Gain2'
                                        *   '<S188>/Gain1'
                                        *   '<S188>/Gain2'
                                        */
  real32_T Kp;                         /* Variable: Kp
                                        * Referenced by:
                                        *   '<S31>/Gain6'
                                        *   '<S32>/Gain6'
                                        *   '<S33>/Gain6'
                                        *   '<S34>/Gain6'
                                        *   '<S108>/Gain6'
                                        *   '<S109>/Gain6'
                                        *   '<S110>/Gain6'
                                        *   '<S111>/Gain6'
                                        *   '<S185>/Gain6'
                                        *   '<S186>/Gain6'
                                        *   '<S187>/Gain6'
                                        *   '<S188>/Gain6'
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
  real32_T p;                          /* Variable: p
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

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

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
 * Block '<S108>/Scope' : Unused code path elimination
 * Block '<S109>/Scope' : Unused code path elimination
 * Block '<S110>/Scope' : Unused code path elimination
 * Block '<S111>/Scope' : Unused code path elimination
 * Block '<S185>/Scope' : Unused code path elimination
 * Block '<S186>/Scope' : Unused code path elimination
 * Block '<S187>/Scope' : Unused code path elimination
 * Block '<S188>/Scope' : Unused code path elimination
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
 * '<S31>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler'
 * '<S32>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1'
 * '<S33>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2'
 * '<S34>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3'
 * '<S35>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup'
 * '<S36>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup1'
 * '<S37>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup2'
 * '<S38>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S39>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup'
 * '<S40>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup1'
 * '<S41>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup2'
 * '<S42>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine'
 * '<S43>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S44>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine'
 * '<S45>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S46>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine'
 * '<S47>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine/Handle Quarter Symmetry Cosine'
 * '<S48>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine'
 * '<S49>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S50>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine'
 * '<S51>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S52>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine'
 * '<S53>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine/Handle Quarter Symmetry Sine'
 * '<S54>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup'
 * '<S55>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup1'
 * '<S56>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/MATLAB Function'
 * '<S57>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup'
 * '<S58>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup1'
 * '<S59>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup/Cosine'
 * '<S60>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S61>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup1/Cosine'
 * '<S62>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S63>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup/Sine'
 * '<S64>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S65>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup1/Sine'
 * '<S66>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S67>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup'
 * '<S68>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup1'
 * '<S69>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/MATLAB Function'
 * '<S70>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup'
 * '<S71>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup1'
 * '<S72>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup/Cosine'
 * '<S73>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S74>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup1/Cosine'
 * '<S75>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S76>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup/Sine'
 * '<S77>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S78>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup1/Sine'
 * '<S79>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S80>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup'
 * '<S81>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup1'
 * '<S82>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/MATLAB Function'
 * '<S83>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup'
 * '<S84>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup1'
 * '<S85>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup/Cosine'
 * '<S86>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S87>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup1/Cosine'
 * '<S88>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S89>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup/Sine'
 * '<S90>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S91>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup1/Sine'
 * '<S92>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S93>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup'
 * '<S94>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup1'
 * '<S95>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/MATLAB Function'
 * '<S96>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup'
 * '<S97>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup1'
 * '<S98>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup/Cosine'
 * '<S99>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S100>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup1/Cosine'
 * '<S101>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S102>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup/Sine'
 * '<S103>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S104>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup1/Sine'
 * '<S105>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S106>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/MATLAB Function'
 * '<S107>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch'
 * '<S108>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler'
 * '<S109>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1'
 * '<S110>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2'
 * '<S111>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3'
 * '<S112>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup'
 * '<S113>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup1'
 * '<S114>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup2'
 * '<S115>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S116>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup'
 * '<S117>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup1'
 * '<S118>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup2'
 * '<S119>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine'
 * '<S120>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S121>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine'
 * '<S122>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S123>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine'
 * '<S124>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine/Handle Quarter Symmetry Cosine'
 * '<S125>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine'
 * '<S126>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S127>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine'
 * '<S128>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S129>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine'
 * '<S130>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine/Handle Quarter Symmetry Sine'
 * '<S131>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup'
 * '<S132>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup1'
 * '<S133>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/MATLAB Function'
 * '<S134>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup'
 * '<S135>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup1'
 * '<S136>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup/Cosine'
 * '<S137>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S138>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup1/Cosine'
 * '<S139>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S140>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup/Sine'
 * '<S141>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S142>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup1/Sine'
 * '<S143>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S144>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup'
 * '<S145>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup1'
 * '<S146>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/MATLAB Function'
 * '<S147>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup'
 * '<S148>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup1'
 * '<S149>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup/Cosine'
 * '<S150>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S151>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup1/Cosine'
 * '<S152>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S153>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup/Sine'
 * '<S154>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S155>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup1/Sine'
 * '<S156>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S157>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup'
 * '<S158>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup1'
 * '<S159>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/MATLAB Function'
 * '<S160>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup'
 * '<S161>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup1'
 * '<S162>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup/Cosine'
 * '<S163>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S164>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup1/Cosine'
 * '<S165>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S166>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup/Sine'
 * '<S167>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S168>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup1/Sine'
 * '<S169>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S170>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup'
 * '<S171>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup1'
 * '<S172>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/MATLAB Function'
 * '<S173>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup'
 * '<S174>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup1'
 * '<S175>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup/Cosine'
 * '<S176>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S177>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup1/Cosine'
 * '<S178>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S179>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup/Sine'
 * '<S180>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S181>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup1/Sine'
 * '<S182>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S183>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/MATLAB Function'
 * '<S184>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch'
 * '<S185>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler'
 * '<S186>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1'
 * '<S187>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2'
 * '<S188>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3'
 * '<S189>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup'
 * '<S190>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup1'
 * '<S191>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup2'
 * '<S192>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S193>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup'
 * '<S194>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup1'
 * '<S195>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup2'
 * '<S196>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine'
 * '<S197>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S198>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine'
 * '<S199>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S200>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine'
 * '<S201>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine/Handle Quarter Symmetry Cosine'
 * '<S202>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine'
 * '<S203>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S204>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine'
 * '<S205>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S206>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine'
 * '<S207>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine/Handle Quarter Symmetry Sine'
 * '<S208>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup'
 * '<S209>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup1'
 * '<S210>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/MATLAB Function'
 * '<S211>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup'
 * '<S212>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup1'
 * '<S213>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup/Cosine'
 * '<S214>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S215>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup1/Cosine'
 * '<S216>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S217>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup/Sine'
 * '<S218>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S219>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup1/Sine'
 * '<S220>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S221>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup'
 * '<S222>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup1'
 * '<S223>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/MATLAB Function'
 * '<S224>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup'
 * '<S225>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup1'
 * '<S226>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup/Cosine'
 * '<S227>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S228>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup1/Cosine'
 * '<S229>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S230>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup/Sine'
 * '<S231>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S232>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup1/Sine'
 * '<S233>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S234>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup'
 * '<S235>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup1'
 * '<S236>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/MATLAB Function'
 * '<S237>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup'
 * '<S238>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup1'
 * '<S239>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup/Cosine'
 * '<S240>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S241>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup1/Cosine'
 * '<S242>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S243>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup/Sine'
 * '<S244>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S245>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup1/Sine'
 * '<S246>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S247>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup'
 * '<S248>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup1'
 * '<S249>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/MATLAB Function'
 * '<S250>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup'
 * '<S251>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup1'
 * '<S252>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup/Cosine'
 * '<S253>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S254>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup1/Cosine'
 * '<S255>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S256>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup/Sine'
 * '<S257>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S258>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup1/Sine'
 * '<S259>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S260>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation'
 * '<S261>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Switch Case Action Subsystem'
 * '<S262>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup'
 * '<S263>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup1'
 * '<S264>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup2'
 * '<S265>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup3'
 * '<S266>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup/Sine'
 * '<S267>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S268>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup1/Sine'
 * '<S269>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S270>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup2/Sine'
 * '<S271>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup2/Sine/Handle Quarter Symmetry Sine'
 * '<S272>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup3/Sine'
 * '<S273>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup3/Sine/Handle Quarter Symmetry Sine'
 * '<S274>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean'
 * '<S275>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean1'
 * '<S276>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean2'
 * '<S277>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean3'
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
