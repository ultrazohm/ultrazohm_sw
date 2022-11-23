/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 4.5
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Nov 21 10:43:21 2022
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
  real32_T theta_e;                    /* '<S23>/Sum1' */
  real32_T im_lim_k;                   /* '<S34>/MATLAB Function' */
  real32_T theta_ep;                   /* '<S23>/Sum' */
  real32_T re_lim_b;                   /* '<S34>/MATLAB Function' */
  real32_T im_lim_d;                   /* '<S31>/MATLAB Function' */
  real32_T re_lim_g;                   /* '<S31>/MATLAB Function' */
  real32_T im_lim_mv;                  /* '<S32>/MATLAB Function' */
  real32_T re_lim_l4;                  /* '<S32>/MATLAB Function' */
  real32_T im_lim_lb;                  /* '<S33>/MATLAB Function' */
  real32_T re_lim_i;                   /* '<S33>/MATLAB Function' */
  real32_T Delay1_m;                   /* '<S35>/Delay1' */
  real32_T Strom_kompensiert_l;        /* '<S30>/Strom_kompensiert' */
  real32_T im_lim_o4;                  /* '<S35>/MATLAB Function' */
  real32_T re_lim_gw;                  /* '<S35>/MATLAB Function' */
  real32_T Product3_a;                 /* '<S35>/Product3' */
  real32_T Gain1_h;                    /* '<S32>/Gain1' */
  real32_T U_re_o;                     /* '<S32>/Sum5' */
  real32_T Gain2_nl;                   /* '<S32>/Gain2' */
  real32_T U_im_i;                     /* '<S32>/Sum6' */
  real32_T Sum_pr;                     /* '<S32>/Sum' */
  real32_T Gain1_g;                    /* '<S33>/Gain1' */
  real32_T U_re_h;                     /* '<S33>/Sum5' */
  real32_T Gain2_d;                    /* '<S33>/Gain2' */
  real32_T U_im_pl;                    /* '<S33>/Sum6' */
  real32_T Sum_j;                      /* '<S33>/Sum' */
  real32_T Gain1_i;                    /* '<S31>/Gain1' */
  real32_T Gain2_io;                   /* '<S31>/Gain2' */
  real32_T Sum_i;                      /* '<S31>/Sum' */
  real32_T Gain1_n;                    /* '<S34>/Gain1' */
  real32_T Gain2_e;                    /* '<S34>/Gain2' */
  real32_T U_im_pt;                    /* '<S34>/Sum6' */
  real32_T Sum_o;                      /* '<S34>/Sum' */
  real32_T U_re_b;                     /* '<S35>/Sum5' */
  real32_T Gain2_m;                    /* '<S35>/Gain2' */
  real32_T U_im_f;                     /* '<S35>/Sum6' */
  real32_T DiscreteTimeIntegrator;
  real32_T DiscreteTimeIntegrator1;
  real32_T DiscreteTimeIntegrator_o;
  real32_T DiscreteTimeIntegrator1_f;
  real32_T DiscreteTimeIntegrator_j;
  real32_T DiscreteTimeIntegrator1_e;
  real32_T DiscreteTimeIntegrator1_h;
  uint32_T bpIdx;
  int16_T SignCorrected_h;             /* '<S74>/SignCorrected' */
  int16_T SignCorrected_cw;            /* '<S117>/SignCorrected' */
  int16_T SignCorrected_o;             /* '<S119>/SignCorrected' */
  uint16_T CastU16En16_jv;             /* '<S74>/CastU16En16' */
  uint16_T rtb_CastU16En16_jv_m;
  uint16_T rtb_CastU16En16_jv_tmp;
  uint16_T rtb_CastU16En16_jv_tmp_tmp;
  boolean_T LTEp25_my;                 /* '<S74>/LTEp25' */
  boolean_T GTEp75_cz;                 /* '<S74>/GTEp75' */
  boolean_T GTEp75_o;                  /* '<S87>/GTEp75' */
} DW_Strangstromregler_asymetrisc;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_MATLABFunction_m sf_MATLABFunction_e;/* '<S212>/MATLAB Function' */
  DW_Strangstromregler_asymetrisc Strangstromregler_asymetrisch1;
                                    /* '<S10>/Strangstromregler_asymetrisch1' */
  DW_Strangstromregler_asymetrisc Strangstromregler_asymetrisch_h;
                                     /* '<S10>/Strangstromregler_asymetrisch' */
  uint64_T frac;
  real32_T Delay_DSTATE_k[20];         /* '<S316>/Delay' */
  real32_T Delay_DSTATE_ki[120];       /* '<S317>/Delay' */
  real32_T Delay_DSTATE_kl[20];        /* '<S318>/Delay' */
  real32_T Delay_DSTATE_b[20];         /* '<S319>/Delay' */
  real32_T I_im;                       /* '<S4>/Merge4' */
  real32_T Merge1;                     /* '<S8>/Merge1' */
  real32_T I_re;                       /* '<S4>/Merge3' */
  real32_T Merge;                      /* '<S8>/Merge' */
  real32_T Merge5;                     /* '<S10>/Merge5' */
  real32_T Merge4;                     /* '<S10>/Merge4' */
  real32_T Merge3;                     /* '<S10>/Merge3' */
  real32_T Delay_DSTATE;               /* '<S3>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S3>/Discrete-Time Integrator' */
  real32_T Accumulator_DSTATE;         /* '<S316>/Accumulator' */
  real32_T Accumulator_DSTATE_d;       /* '<S317>/Accumulator' */
  real32_T Accumulator_DSTATE_f;       /* '<S318>/Accumulator' */
  real32_T Accumulator_DSTATE_n;       /* '<S319>/Accumulator' */
  real32_T Delay_DSTATE_n;             /* '<S14>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_n;/* '<S14>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_h;             /* '<S7>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_f;/* '<S13>/Discrete-Time Integrator' */
  real32_T Delay1_DSTATE;              /* '<S214>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_o;/* '<S214>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_l;             /* '<S214>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S214>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_o;            /* '<S215>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_m;/* '<S215>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_nv;            /* '<S215>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_f;/* '<S215>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_d;            /* '<S213>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTAT_om;/* '<S213>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_j;             /* '<S213>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_a;/* '<S213>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_g;            /* '<S216>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_c;/* '<S216>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_a;             /* '<S216>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_o;/* '<S216>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_oi;           /* '<S217>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S217>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_nm;            /* '<S217>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTA_os;/* '<S217>/Discrete-Time Integrator1' */
  real32_T a;
  real32_T b;
  real32_T c;
  real32_T Gain;                       /* '<S3>/Gain' */
  real32_T Add;                        /* '<S4>/Add' */
  real32_T theta_b;                    /* '<S25>/Sum1' */
  real32_T Switch2;                    /* '<S15>/Switch2' */
  real32_T Gain1;                      /* '<S13>/Gain1' */
  real32_T theta_m;                    /* '<S25>/Sum' */
  real32_T y;                          /* '<S13>/Sum' */
  real32_T re_lim;                     /* '<S215>/MATLAB Function' */
  real32_T Delay1;                     /* '<S217>/Delay1' */
  real32_T Strom_kompensiert;          /* '<S212>/Strom_kompensiert' */
  real32_T im_lim_f;                   /* '<S217>/MATLAB Function' */
  real32_T re_lim_e;                   /* '<S217>/MATLAB Function' */
  real32_T Product3;                   /* '<S217>/Product3' */
  real32_T Gain1_k;                    /* '<S214>/Gain1' */
  real32_T U_re;                       /* '<S214>/Sum5' */
  real32_T U_im;                       /* '<S214>/Sum6' */
  real32_T Sum_cz;                     /* '<S214>/Sum' */
  real32_T Gain1_e;                    /* '<S215>/Gain1' */
  real32_T U_re_c;                     /* '<S215>/Sum5' */
  real32_T Gain2_n;                    /* '<S215>/Gain2' */
  real32_T U_im_k;                     /* '<S215>/Sum6' */
  real32_T Sum_a;                      /* '<S215>/Sum' */
  real32_T Gain1_d;                    /* '<S213>/Gain1' */
  real32_T Gain2_c;                    /* '<S213>/Gain2' */
  real32_T Sum_pq;                     /* '<S213>/Sum' */
  real32_T Gain1_m;                    /* '<S216>/Gain1' */
  real32_T Gain2_h;                    /* '<S216>/Gain2' */
  real32_T U_im_p;                     /* '<S216>/Sum6' */
  real32_T Sum_cr;                     /* '<S216>/Sum' */
  real32_T U_re_d;                     /* '<S217>/Sum5' */
  real32_T Gain2_i;                    /* '<S217>/Gain2' */
  real32_T U_im_c;                     /* '<S217>/Sum6' */
  real32_T DiscreteTimeIntegrator;
  real32_T y_i;
  real32_T DiscreteTimeIntegrator_o;
  real32_T DiscreteTimeIntegrator1;
  real32_T DiscreteTimeIntegrator_k;
  real32_T DiscreteTimeIntegrator1_e;
  real32_T U_re_m;
  real32_T U_im_cl;
  real32_T DiscreteTimeIntegrator_a;
  real32_T DiscreteTimeIntegrator1_a;
  real32_T DiscreteTimeIntegrator1_g;
  int_T idxDelay;
  uint32_T bpIdx;
  int16_T SignCorrected_a;             /* '<S315>/SignCorrected' */
  int16_T SignCorrected_c;             /* '<S299>/SignCorrected' */
  int16_T SignCorrected_d;             /* '<S301>/SignCorrected' */
  uint16_T CastU16En16_h;              /* '<S315>/CastU16En16' */
  uint16_T rtb_CastU16En16_h_k;
  uint16_T rtb_CastU16En16_h_tmp_tmp;
  int8_T switch_case_power_ActiveSubsyst;/* '<S2>/switch_case_power' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S4>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_o; /* '<S10>/Switch Case' */
  int8_T SwitchCase1_ActiveSubsystem;  /* '<S10>/Switch Case1' */
  int8_T SwitchCase2_ActiveSubsystem;  /* '<S10>/Switch Case2' */
  int8_T rtPrevAction;
  int8_T rtAction;
  uint8_T error_speed_limit;
  boolean_T LTEp50_j;                  /* '<S315>/LTEp50' */
  boolean_T GTEp75;                    /* '<S256>/GTEp75' */
  boolean_T GTEp75_b;                  /* '<S269>/GTEp75' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const real32_T Gain;                 /* '<S10>/Gain' */
} ConstB;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: YData)
   * Referenced by:
   *   '<S308>/Look-Up Table'
   *   '<S310>/Look-Up Table'
   *   '<S312>/Look-Up Table'
   *   '<S314>/Look-Up Table'
   *   '<S43>/Look-Up Table'
   *   '<S45>/Look-Up Table'
   *   '<S47>/Look-Up Table'
   *   '<S49>/Look-Up Table'
   *   '<S51>/Look-Up Table'
   *   '<S53>/Look-Up Table'
   *   '<S60>/Look-Up Table'
   *   '<S62>/Look-Up Table'
   *   '<S64>/Look-Up Table'
   *   '<S66>/Look-Up Table'
   *   '<S73>/Look-Up Table'
   *   '<S75>/Look-Up Table'
   *   '<S77>/Look-Up Table'
   *   '<S79>/Look-Up Table'
   *   '<S86>/Look-Up Table'
   *   '<S88>/Look-Up Table'
   *   '<S90>/Look-Up Table'
   *   '<S92>/Look-Up Table'
   *   '<S99>/Look-Up Table'
   *   '<S101>/Look-Up Table'
   *   '<S103>/Look-Up Table'
   *   '<S105>/Look-Up Table'
   *   '<S112>/Look-Up Table'
   *   '<S114>/Look-Up Table'
   *   '<S116>/Look-Up Table'
   *   '<S118>/Look-Up Table'
   *   '<S134>/Look-Up Table'
   *   '<S136>/Look-Up Table'
   *   '<S138>/Look-Up Table'
   *   '<S140>/Look-Up Table'
   *   '<S142>/Look-Up Table'
   *   '<S144>/Look-Up Table'
   *   '<S151>/Look-Up Table'
   *   '<S153>/Look-Up Table'
   *   '<S155>/Look-Up Table'
   *   '<S157>/Look-Up Table'
   *   '<S164>/Look-Up Table'
   *   '<S166>/Look-Up Table'
   *   '<S168>/Look-Up Table'
   *   '<S170>/Look-Up Table'
   *   '<S177>/Look-Up Table'
   *   '<S179>/Look-Up Table'
   *   '<S181>/Look-Up Table'
   *   '<S183>/Look-Up Table'
   *   '<S190>/Look-Up Table'
   *   '<S192>/Look-Up Table'
   *   '<S194>/Look-Up Table'
   *   '<S196>/Look-Up Table'
   *   '<S203>/Look-Up Table'
   *   '<S205>/Look-Up Table'
   *   '<S207>/Look-Up Table'
   *   '<S209>/Look-Up Table'
   *   '<S225>/Look-Up Table'
   *   '<S227>/Look-Up Table'
   *   '<S229>/Look-Up Table'
   *   '<S231>/Look-Up Table'
   *   '<S233>/Look-Up Table'
   *   '<S235>/Look-Up Table'
   *   '<S242>/Look-Up Table'
   *   '<S244>/Look-Up Table'
   *   '<S246>/Look-Up Table'
   *   '<S248>/Look-Up Table'
   *   '<S255>/Look-Up Table'
   *   '<S257>/Look-Up Table'
   *   '<S259>/Look-Up Table'
   *   '<S261>/Look-Up Table'
   *   '<S268>/Look-Up Table'
   *   '<S270>/Look-Up Table'
   *   '<S272>/Look-Up Table'
   *   '<S274>/Look-Up Table'
   *   '<S281>/Look-Up Table'
   *   '<S283>/Look-Up Table'
   *   '<S285>/Look-Up Table'
   *   '<S287>/Look-Up Table'
   *   '<S294>/Look-Up Table'
   *   '<S296>/Look-Up Table'
   *   '<S298>/Look-Up Table'
   *   '<S300>/Look-Up Table'
   */
  int16_T pooled21[16385];
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
                                        *   '<S32>/Gain1'
                                        *   '<S32>/Gain2'
                                        *   '<S123>/Gain1'
                                        *   '<S123>/Gain2'
                                        *   '<S214>/Gain1'
                                        *   '<S214>/Gain2'
                                        */
  real32_T K2;                         /* Variable: K2
                                        * Referenced by:
                                        *   '<S33>/Gain1'
                                        *   '<S33>/Gain2'
                                        *   '<S124>/Gain1'
                                        *   '<S124>/Gain2'
                                        *   '<S215>/Gain1'
                                        *   '<S215>/Gain2'
                                        */
  real32_T K3;                         /* Variable: K3
                                        * Referenced by:
                                        *   '<S31>/Gain4'
                                        *   '<S122>/Gain4'
                                        *   '<S213>/Gain4'
                                        */
  real32_T K4;                         /* Variable: K4
                                        * Referenced by:
                                        *   '<S34>/Gain1'
                                        *   '<S34>/Gain2'
                                        *   '<S125>/Gain1'
                                        *   '<S125>/Gain2'
                                        *   '<S216>/Gain1'
                                        *   '<S216>/Gain2'
                                        */
  real32_T K6;                         /* Variable: K6
                                        * Referenced by:
                                        *   '<S35>/Gain1'
                                        *   '<S35>/Gain2'
                                        *   '<S126>/Gain1'
                                        *   '<S126>/Gain2'
                                        *   '<S217>/Gain1'
                                        *   '<S217>/Gain2'
                                        */
  real32_T Kp;                         /* Variable: Kp
                                        * Referenced by:
                                        *   '<S32>/Gain6'
                                        *   '<S33>/Gain6'
                                        *   '<S34>/Gain6'
                                        *   '<S35>/Gain6'
                                        *   '<S123>/Gain6'
                                        *   '<S124>/Gain6'
                                        *   '<S125>/Gain6'
                                        *   '<S126>/Gain6'
                                        *   '<S214>/Gain6'
                                        *   '<S215>/Gain6'
                                        *   '<S216>/Gain6'
                                        *   '<S217>/Gain6'
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
 * Block '<S35>/Scope' : Unused code path elimination
 * Block '<S122>/Scope' : Unused code path elimination
 * Block '<S123>/Scope' : Unused code path elimination
 * Block '<S124>/Scope' : Unused code path elimination
 * Block '<S125>/Scope' : Unused code path elimination
 * Block '<S126>/Scope' : Unused code path elimination
 * Block '<S213>/Scope' : Unused code path elimination
 * Block '<S214>/Scope' : Unused code path elimination
 * Block '<S215>/Scope' : Unused code path elimination
 * Block '<S216>/Scope' : Unused code path elimination
 * Block '<S217>/Scope' : Unused code path elimination
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
 * '<S36>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup'
 * '<S37>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup1'
 * '<S38>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup2'
 * '<S39>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S40>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup'
 * '<S41>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup1'
 * '<S42>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup2'
 * '<S43>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine'
 * '<S44>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S45>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine'
 * '<S46>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S47>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine'
 * '<S48>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine/Handle Quarter Symmetry Cosine'
 * '<S49>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine'
 * '<S50>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S51>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine'
 * '<S52>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S53>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine'
 * '<S54>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine/Handle Quarter Symmetry Sine'
 * '<S55>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Cosine Lookup'
 * '<S56>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Cosine Lookup1'
 * '<S57>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/MATLAB Function'
 * '<S58>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Sine Lookup'
 * '<S59>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Sine Lookup1'
 * '<S60>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Cosine Lookup/Cosine'
 * '<S61>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S62>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Cosine Lookup1/Cosine'
 * '<S63>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S64>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Sine Lookup/Sine'
 * '<S65>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S66>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Sine Lookup1/Sine'
 * '<S67>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-I-Regler/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S68>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup'
 * '<S69>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup1'
 * '<S70>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/MATLAB Function'
 * '<S71>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup'
 * '<S72>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup1'
 * '<S73>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup/Cosine'
 * '<S74>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S75>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup1/Cosine'
 * '<S76>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S77>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup/Sine'
 * '<S78>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S79>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup1/Sine'
 * '<S80>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S81>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup'
 * '<S82>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup1'
 * '<S83>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/MATLAB Function'
 * '<S84>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup'
 * '<S85>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup1'
 * '<S86>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup/Cosine'
 * '<S87>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S88>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup1/Cosine'
 * '<S89>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S90>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup/Sine'
 * '<S91>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S92>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup1/Sine'
 * '<S93>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S94>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup'
 * '<S95>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup1'
 * '<S96>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/MATLAB Function'
 * '<S97>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup'
 * '<S98>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup1'
 * '<S99>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup/Cosine'
 * '<S100>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S101>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup1/Cosine'
 * '<S102>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S103>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup/Sine'
 * '<S104>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S105>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup1/Sine'
 * '<S106>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S107>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup'
 * '<S108>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup1'
 * '<S109>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/MATLAB Function'
 * '<S110>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup'
 * '<S111>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup1'
 * '<S112>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup/Cosine'
 * '<S113>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S114>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup1/Cosine'
 * '<S115>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S116>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup/Sine'
 * '<S117>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S118>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup1/Sine'
 * '<S119>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S120>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/MATLAB Function'
 * '<S121>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch'
 * '<S122>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler'
 * '<S123>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler'
 * '<S124>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1'
 * '<S125>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2'
 * '<S126>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3'
 * '<S127>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup'
 * '<S128>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup1'
 * '<S129>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup2'
 * '<S130>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S131>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup'
 * '<S132>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup1'
 * '<S133>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup2'
 * '<S134>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine'
 * '<S135>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S136>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine'
 * '<S137>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S138>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine'
 * '<S139>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine/Handle Quarter Symmetry Cosine'
 * '<S140>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine'
 * '<S141>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S142>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine'
 * '<S143>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S144>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine'
 * '<S145>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine/Handle Quarter Symmetry Sine'
 * '<S146>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Cosine Lookup'
 * '<S147>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Cosine Lookup1'
 * '<S148>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/MATLAB Function'
 * '<S149>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Sine Lookup'
 * '<S150>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Sine Lookup1'
 * '<S151>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Cosine Lookup/Cosine'
 * '<S152>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S153>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Cosine Lookup1/Cosine'
 * '<S154>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S155>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Sine Lookup/Sine'
 * '<S156>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S157>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Sine Lookup1/Sine'
 * '<S158>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-I-Regler/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S159>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup'
 * '<S160>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup1'
 * '<S161>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/MATLAB Function'
 * '<S162>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup'
 * '<S163>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup1'
 * '<S164>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup/Cosine'
 * '<S165>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S166>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup1/Cosine'
 * '<S167>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S168>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup/Sine'
 * '<S169>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S170>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup1/Sine'
 * '<S171>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S172>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup'
 * '<S173>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup1'
 * '<S174>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/MATLAB Function'
 * '<S175>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup'
 * '<S176>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup1'
 * '<S177>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup/Cosine'
 * '<S178>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S179>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup1/Cosine'
 * '<S180>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S181>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup/Sine'
 * '<S182>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S183>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup1/Sine'
 * '<S184>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S185>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup'
 * '<S186>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup1'
 * '<S187>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/MATLAB Function'
 * '<S188>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup'
 * '<S189>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup1'
 * '<S190>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup/Cosine'
 * '<S191>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S192>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup1/Cosine'
 * '<S193>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S194>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup/Sine'
 * '<S195>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S196>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup1/Sine'
 * '<S197>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S198>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup'
 * '<S199>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup1'
 * '<S200>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/MATLAB Function'
 * '<S201>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup'
 * '<S202>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup1'
 * '<S203>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup/Cosine'
 * '<S204>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S205>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup1/Cosine'
 * '<S206>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S207>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup/Sine'
 * '<S208>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S209>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup1/Sine'
 * '<S210>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S211>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/MATLAB Function'
 * '<S212>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch'
 * '<S213>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler'
 * '<S214>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler'
 * '<S215>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1'
 * '<S216>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2'
 * '<S217>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3'
 * '<S218>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup'
 * '<S219>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup1'
 * '<S220>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup2'
 * '<S221>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S222>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup'
 * '<S223>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup1'
 * '<S224>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup2'
 * '<S225>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine'
 * '<S226>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S227>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine'
 * '<S228>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S229>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine'
 * '<S230>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Cosine Lookup2/Cosine/Handle Quarter Symmetry Cosine'
 * '<S231>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine'
 * '<S232>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S233>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine'
 * '<S234>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S235>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine'
 * '<S236>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/Sine Lookup2/Sine/Handle Quarter Symmetry Sine'
 * '<S237>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Cosine Lookup'
 * '<S238>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Cosine Lookup1'
 * '<S239>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/MATLAB Function'
 * '<S240>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Sine Lookup'
 * '<S241>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Sine Lookup1'
 * '<S242>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Cosine Lookup/Cosine'
 * '<S243>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S244>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Cosine Lookup1/Cosine'
 * '<S245>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S246>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Sine Lookup/Sine'
 * '<S247>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S248>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Sine Lookup1/Sine'
 * '<S249>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-I-Regler/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S250>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup'
 * '<S251>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup1'
 * '<S252>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/MATLAB Function'
 * '<S253>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup'
 * '<S254>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup1'
 * '<S255>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup/Cosine'
 * '<S256>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S257>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup1/Cosine'
 * '<S258>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S259>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup/Sine'
 * '<S260>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S261>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup1/Sine'
 * '<S262>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S263>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup'
 * '<S264>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup1'
 * '<S265>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/MATLAB Function'
 * '<S266>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup'
 * '<S267>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup1'
 * '<S268>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup/Cosine'
 * '<S269>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S270>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup1/Cosine'
 * '<S271>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S272>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup/Sine'
 * '<S273>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S274>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup1/Sine'
 * '<S275>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S276>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup'
 * '<S277>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup1'
 * '<S278>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/MATLAB Function'
 * '<S279>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup'
 * '<S280>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup1'
 * '<S281>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup/Cosine'
 * '<S282>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S283>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup1/Cosine'
 * '<S284>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S285>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup/Sine'
 * '<S286>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S287>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup1/Sine'
 * '<S288>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S289>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup'
 * '<S290>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup1'
 * '<S291>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/MATLAB Function'
 * '<S292>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup'
 * '<S293>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup1'
 * '<S294>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup/Cosine'
 * '<S295>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S296>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup1/Cosine'
 * '<S297>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Cosine Lookup1/Cosine/Handle Quarter Symmetry Cosine'
 * '<S298>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup/Sine'
 * '<S299>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S300>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup1/Sine'
 * '<S301>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S302>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation'
 * '<S303>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Switch Case Action Subsystem'
 * '<S304>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup'
 * '<S305>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup1'
 * '<S306>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup2'
 * '<S307>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup3'
 * '<S308>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup/Sine'
 * '<S309>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S310>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup1/Sine'
 * '<S311>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup1/Sine/Handle Quarter Symmetry Sine'
 * '<S312>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup2/Sine'
 * '<S313>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup2/Sine/Handle Quarter Symmetry Sine'
 * '<S314>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup3/Sine'
 * '<S315>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/Sine Lookup3/Sine/Handle Quarter Symmetry Sine'
 * '<S316>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean'
 * '<S317>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean1'
 * '<S318>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean2'
 * '<S319>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean3'
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
