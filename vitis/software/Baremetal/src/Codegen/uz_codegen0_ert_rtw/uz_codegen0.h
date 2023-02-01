/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 4.8
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Jan 30 10:51:45 2023
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
  real32_T Delay1_g;                   /* '<S31>/Delay1' */
  real32_T Product4_f;                 /* '<S31>/Product4' */
  real32_T re_lim_i;                   /* '<S32>/MATLAB Function' */
  real32_T Add1_l;                     /* '<S23>/Add1' */
  real32_T theta_e;                    /* '<S23>/Sum' */
  real32_T Product5_h;                 /* '<S31>/Product5' */
  real32_T Product1_a;                 /* '<S31>/Product1' */
  real32_T Merge_h;                    /* '<S36>/Merge' */
  real32_T Merge_h4;                   /* '<S39>/Merge' */
  real32_T Add2_o;                     /* '<S23>/Add2' */
  real32_T re_lim_l;                   /* '<S31>/MATLAB Function' */
  real32_T Add3_j;                     /* '<S23>/Add3' */
  real32_T Product_am;                 /* '<S34>/Product' */
  real32_T Product5_hz;                /* '<S32>/Product5' */
  real32_T Delay1_c;                   /* '<S33>/Delay1' */
  real32_T Merge_hl;                   /* '<S98>/Merge' */
  real32_T Sum_j;                      /* '<S32>/Sum' */
  real32_T Product5_l;                 /* '<S33>/Product5' */
  real32_T Delay1_m;                   /* '<S34>/Delay1' */
  real32_T Product4_ic;                /* '<S33>/Product4' */
  real32_T Sum_o;                      /* '<S33>/Sum' */
  real32_T Product5_hz4;               /* '<S34>/Product5' */
  real32_T Product4_if;                /* '<S34>/Product4' */
  real32_T I_im_mit_e;                 /* '<S30>/MATLAB Function' */
  real32_T I_re_gegen_e;               /* '<S30>/MATLAB Function' */
  real32_T I_im_gegen_g;               /* '<S30>/MATLAB Function' */
  real32_T I_re_null_k;                /* '<S30>/MATLAB Function' */
  real32_T I_im_null_n;                /* '<S30>/MATLAB Function' */
  real32_T Product3_h;                 /* '<S31>/Product3' */
  real32_T U_im_pl;                    /* '<S32>/Sum6' */
  real32_T Gain1_n;                    /* '<S33>/Gain1' */
  real32_T U_re_j;                     /* '<S33>/Sum5' */
  real32_T U_im_pt;                    /* '<S33>/Sum6' */
  real32_T Gain1_a;                    /* '<S34>/Gain1' */
  real32_T U_re_b;                     /* '<S34>/Sum5' */
  real32_T Gain2_m;                    /* '<S34>/Gain2' */
  real32_T DiscreteTimeIntegrator1_f;
  real32_T DiscreteTimeIntegrator_j;
  real32_T DiscreteTimeIntegrator1_e;
  real32_T DiscreteTimeIntegrator_h;
  real32_T DiscreteTimeIntegrator1_h;
  boolean_T Betrieb_n;                 /* '<S23>/MATLAB Function' */
} DW_Strangstromregler_asymetrisc;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_MATLABFunction_m sf_MATLABFunction_e;/* '<S316>/MATLAB Function' */
  DW_Strangstromregler_asymetrisc Strangstromregler_asymetrisch1;
                                    /* '<S10>/Strangstromregler_asymetrisch1' */
  DW_Strangstromregler_asymetrisc Strangstromregler_asymetrisch_h;
                                     /* '<S10>/Strangstromregler_asymetrisch' */
  real32_T Delay_DSTATE_k[20];         /* '<S484>/Delay' */
  real32_T Delay_DSTATE_ki[120];       /* '<S485>/Delay' */
  real32_T Delay_DSTATE_kl[20];        /* '<S486>/Delay' */
  real32_T Delay_DSTATE_b[20];         /* '<S487>/Delay' */
  real32_T I_im;                       /* '<S4>/Merge4' */
  real32_T Merge1;                     /* '<S8>/Merge1' */
  real32_T I_re;                       /* '<S4>/Merge3' */
  real32_T Merge;                      /* '<S8>/Merge' */
  real32_T Merge5;                     /* '<S10>/Merge5' */
  real32_T Merge4;                     /* '<S10>/Merge4' */
  real32_T Merge3;                     /* '<S10>/Merge3' */
  real32_T Delay_DSTATE;               /* '<S3>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S3>/Discrete-Time Integrator' */
  real32_T Accumulator_DSTATE;         /* '<S484>/Accumulator' */
  real32_T Accumulator_DSTATE_d;       /* '<S485>/Accumulator' */
  real32_T Accumulator_DSTATE_f;       /* '<S486>/Accumulator' */
  real32_T Accumulator_DSTATE_n;       /* '<S487>/Accumulator' */
  real32_T Delay_DSTATE_n;             /* '<S14>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_n;/* '<S14>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_h;             /* '<S7>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_f;/* '<S13>/Discrete-Time Integrator' */
  real32_T Delay1_DSTATE;              /* '<S317>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_o;/* '<S317>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_l;             /* '<S317>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S317>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_o;            /* '<S318>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_m;/* '<S318>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_nv;            /* '<S318>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_f;/* '<S318>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_g;            /* '<S319>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_c;/* '<S319>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_a;             /* '<S319>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_o;/* '<S319>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_oi;           /* '<S320>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S320>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_nm;            /* '<S320>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTA_os;/* '<S320>/Discrete-Time Integrator1' */
  real32_T a;
  real32_T b;
  real32_T c;
  real32_T Gain;                       /* '<S3>/Gain' */
  real32_T Add;                        /* '<S4>/Add' */
  real32_T Delay1;                     /* '<S317>/Delay1' */
  real32_T theta_m;                    /* '<S25>/Sum' */
  real32_T Switch2;                    /* '<S15>/Switch2' */
  real32_T Product1_d;                 /* '<S317>/Product1' */
  real32_T Merge_n;                    /* '<S322>/Merge' */
  real32_T Gain1;                      /* '<S13>/Gain1' */
  real32_T Merge_m;                    /* '<S325>/Merge' */
  real32_T y;                          /* '<S13>/Sum' */
  real32_T Add3;                       /* '<S25>/Add3' */
  real32_T Product5_g;                 /* '<S318>/Product5' */
  real32_T Delay1_a;                   /* '<S319>/Delay1' */
  real32_T Product4_i;                 /* '<S318>/Product4' */
  real32_T Sum_a;                      /* '<S318>/Sum' */
  real32_T Product5_g0;                /* '<S319>/Product5' */
  real32_T Delay1_k;                   /* '<S320>/Delay1' */
  real32_T Product4_a;                 /* '<S319>/Product4' */
  real32_T Sum_cr;                     /* '<S319>/Sum' */
  real32_T Product5_j;                 /* '<S320>/Product5' */
  real32_T Product4_ap;                /* '<S320>/Product4' */
  real32_T I_im_mit;                   /* '<S316>/MATLAB Function' */
  real32_T I_re_gegen;                 /* '<S316>/MATLAB Function' */
  real32_T I_im_gegen;                 /* '<S316>/MATLAB Function' */
  real32_T I_re_null;                  /* '<S316>/MATLAB Function' */
  real32_T I_im_null;                  /* '<S316>/MATLAB Function' */
  real32_T U_im_k;                     /* '<S318>/Sum6' */
  real32_T Gain1_m;                    /* '<S319>/Gain1' */
  real32_T U_re_n;                     /* '<S319>/Sum5' */
  real32_T U_im_p;                     /* '<S319>/Sum6' */
  real32_T Gain1_j;                    /* '<S320>/Gain1' */
  real32_T U_re_d;                     /* '<S320>/Sum5' */
  real32_T Gain2_i;                    /* '<S320>/Gain2' */
  real32_T DiscreteTimeIntegrator;
  real32_T y_i;
  real32_T DiscreteTimeIntegrator1_e;
  real32_T DiscreteTimeIntegrator_a;
  real32_T DiscreteTimeIntegrator1_a;
  real32_T DiscreteTimeIntegrator_n;
  real32_T DiscreteTimeIntegrator1_g;
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

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: YData)
   * Referenced by:
   *   '<S467>/Look-Up Table'
   *   '<S472>/Look-Up Table'
   *   '<S477>/Look-Up Table'
   *   '<S482>/Look-Up Table'
   *   '<S45>/Look-Up Table'
   *   '<S50>/Look-Up Table'
   *   '<S55>/Look-Up Table'
   *   '<S60>/Look-Up Table'
   *   '<S65>/Look-Up Table'
   *   '<S70>/Look-Up Table'
   *   '<S80>/Look-Up Table'
   *   '<S85>/Look-Up Table'
   *   '<S90>/Look-Up Table'
   *   '<S95>/Look-Up Table'
   *   '<S105>/Look-Up Table'
   *   '<S110>/Look-Up Table'
   *   '<S115>/Look-Up Table'
   *   '<S120>/Look-Up Table'
   *   '<S130>/Look-Up Table'
   *   '<S135>/Look-Up Table'
   *   '<S140>/Look-Up Table'
   *   '<S145>/Look-Up Table'
   *   '<S155>/Look-Up Table'
   *   '<S160>/Look-Up Table'
   *   '<S165>/Look-Up Table'
   *   '<S170>/Look-Up Table'
   *   '<S188>/Look-Up Table'
   *   '<S193>/Look-Up Table'
   *   '<S198>/Look-Up Table'
   *   '<S203>/Look-Up Table'
   *   '<S208>/Look-Up Table'
   *   '<S213>/Look-Up Table'
   *   '<S223>/Look-Up Table'
   *   '<S228>/Look-Up Table'
   *   '<S233>/Look-Up Table'
   *   '<S238>/Look-Up Table'
   *   '<S248>/Look-Up Table'
   *   '<S253>/Look-Up Table'
   *   '<S258>/Look-Up Table'
   *   '<S263>/Look-Up Table'
   *   '<S273>/Look-Up Table'
   *   '<S278>/Look-Up Table'
   *   '<S283>/Look-Up Table'
   *   '<S288>/Look-Up Table'
   *   '<S298>/Look-Up Table'
   *   '<S303>/Look-Up Table'
   *   '<S308>/Look-Up Table'
   *   '<S313>/Look-Up Table'
   *   '<S331>/Look-Up Table'
   *   '<S336>/Look-Up Table'
   *   '<S341>/Look-Up Table'
   *   '<S346>/Look-Up Table'
   *   '<S351>/Look-Up Table'
   *   '<S356>/Look-Up Table'
   *   '<S366>/Look-Up Table'
   *   '<S371>/Look-Up Table'
   *   '<S376>/Look-Up Table'
   *   '<S381>/Look-Up Table'
   *   '<S391>/Look-Up Table'
   *   '<S396>/Look-Up Table'
   *   '<S401>/Look-Up Table'
   *   '<S406>/Look-Up Table'
   *   '<S416>/Look-Up Table'
   *   '<S421>/Look-Up Table'
   *   '<S426>/Look-Up Table'
   *   '<S431>/Look-Up Table'
   *   '<S441>/Look-Up Table'
   *   '<S446>/Look-Up Table'
   *   '<S451>/Look-Up Table'
   *   '<S456>/Look-Up Table'
   */
  int16_T pooled17[65];
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
  uint8_T fl_lookup_table;             /* '<Root>/fl_lookup_table' */
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
                                        *   '<S174>/Gain1'
                                        *   '<S174>/Gain2'
                                        *   '<S317>/Gain1'
                                        *   '<S317>/Gain2'
                                        */
  real32_T K2;                         /* Variable: K2
                                        * Referenced by:
                                        *   '<S32>/Gain1'
                                        *   '<S32>/Gain2'
                                        *   '<S175>/Gain1'
                                        *   '<S175>/Gain2'
                                        *   '<S318>/Gain1'
                                        *   '<S318>/Gain2'
                                        */
  real32_T K4;                         /* Variable: K4
                                        * Referenced by:
                                        *   '<S33>/Gain1'
                                        *   '<S33>/Gain2'
                                        *   '<S176>/Gain1'
                                        *   '<S176>/Gain2'
                                        *   '<S319>/Gain1'
                                        *   '<S319>/Gain2'
                                        */
  real32_T K6;                         /* Variable: K6
                                        * Referenced by:
                                        *   '<S34>/Gain1'
                                        *   '<S34>/Gain2'
                                        *   '<S177>/Gain1'
                                        *   '<S177>/Gain2'
                                        *   '<S320>/Gain1'
                                        *   '<S320>/Gain2'
                                        */
  real32_T Kp;                         /* Variable: Kp
                                        * Referenced by:
                                        *   '<S31>/Gain6'
                                        *   '<S32>/Gain6'
                                        *   '<S33>/Gain6'
                                        *   '<S34>/Gain6'
                                        *   '<S174>/Gain6'
                                        *   '<S175>/Gain6'
                                        *   '<S176>/Gain6'
                                        *   '<S177>/Gain6'
                                        *   '<S317>/Gain6'
                                        *   '<S318>/Gain6'
                                        *   '<S319>/Gain6'
                                        *   '<S320>/Gain6'
                                        */
  real32_T Offset_U_ideal;             /* Variable: Offset_U_ideal
                                        * Referenced by: '<S10>/Strangstromregler_asymetrisch'
                                        */
  real32_T Offset_V_ideal;             /* Variable: Offset_V_ideal
                                        * Referenced by: '<S10>/Strangstromregler_asymetrisch1'
                                        */
  real32_T Offset_W_ideal;             /* Variable: Offset_W_ideal
                                        * Referenced by:
                                        *   '<S25>/Constant'
                                        *   '<S25>/Constant2'
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
 * Block '<S174>/Scope' : Unused code path elimination
 * Block '<S175>/Scope' : Unused code path elimination
 * Block '<S176>/Scope' : Unused code path elimination
 * Block '<S177>/Scope' : Unused code path elimination
 * Block '<S317>/Scope' : Unused code path elimination
 * Block '<S318>/Scope' : Unused code path elimination
 * Block '<S319>/Scope' : Unused code path elimination
 * Block '<S320>/Scope' : Unused code path elimination
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
 * '<S35>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S36>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case'
 * '<S37>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case1'
 * '<S38>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case2'
 * '<S39>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case'
 * '<S40>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case1'
 * '<S41>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case2'
 * '<S42>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case/Subsystem'
 * '<S43>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table'
 * '<S44>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S45>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S46>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S47>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case1/Subsystem'
 * '<S48>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table'
 * '<S49>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S50>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S51>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S52>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case2/Subsystem'
 * '<S53>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table'
 * '<S54>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table/Cosine Lookup'
 * '<S55>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S56>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S57>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case/Subsystem'
 * '<S58>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table'
 * '<S59>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S60>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S61>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S62>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case1/Subsystem'
 * '<S63>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table'
 * '<S64>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S65>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S66>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S67>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case2/Subsystem'
 * '<S68>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table'
 * '<S69>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table/Sine Lookup'
 * '<S70>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table/Sine Lookup/Sine'
 * '<S71>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S72>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/MATLAB Function'
 * '<S73>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case'
 * '<S74>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case1'
 * '<S75>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case'
 * '<S76>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case1'
 * '<S77>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case/Subsystem'
 * '<S78>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case/cos_lookup_table'
 * '<S79>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S80>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S81>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S82>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case1/Subsystem'
 * '<S83>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case1/cos_lookup_table'
 * '<S84>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S85>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S86>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S87>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case/Subsystem'
 * '<S88>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case/sin_lookup_table'
 * '<S89>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S90>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S91>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S92>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case1/Subsystem'
 * '<S93>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case1/sin_lookup_table'
 * '<S94>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S95>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S96>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S97>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/MATLAB Function'
 * '<S98>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case'
 * '<S99>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case1'
 * '<S100>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case'
 * '<S101>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case1'
 * '<S102>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case/Subsystem'
 * '<S103>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case/cos_lookup_table'
 * '<S104>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S105>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S106>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S107>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case1/Subsystem'
 * '<S108>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table'
 * '<S109>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S110>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S111>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S112>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case/Subsystem'
 * '<S113>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case/sin_lookup_table'
 * '<S114>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S115>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S116>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S117>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case1/Subsystem'
 * '<S118>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table'
 * '<S119>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S120>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S121>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S122>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/MATLAB Function'
 * '<S123>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case'
 * '<S124>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case1'
 * '<S125>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case'
 * '<S126>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case1'
 * '<S127>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case/Subsystem'
 * '<S128>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case/cos_lookup_table'
 * '<S129>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S130>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S131>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S132>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case1/Subsystem'
 * '<S133>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table'
 * '<S134>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S135>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S136>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S137>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case/Subsystem'
 * '<S138>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case/sin_lookup_table'
 * '<S139>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S140>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S141>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S142>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case1/Subsystem'
 * '<S143>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table'
 * '<S144>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S145>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S146>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S147>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/MATLAB Function'
 * '<S148>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case'
 * '<S149>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case1'
 * '<S150>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case'
 * '<S151>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case1'
 * '<S152>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case/Subsystem'
 * '<S153>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case/cos_lookup_table'
 * '<S154>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S155>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S156>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S157>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case1/Subsystem'
 * '<S158>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table'
 * '<S159>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S160>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S161>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S162>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case/Subsystem'
 * '<S163>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case/sin_lookup_table'
 * '<S164>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S165>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S166>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S167>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case1/Subsystem'
 * '<S168>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table'
 * '<S169>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S170>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S171>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S172>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/MATLAB Function'
 * '<S173>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch'
 * '<S174>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler'
 * '<S175>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1'
 * '<S176>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2'
 * '<S177>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3'
 * '<S178>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S179>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case'
 * '<S180>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case1'
 * '<S181>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case2'
 * '<S182>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case'
 * '<S183>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case1'
 * '<S184>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case2'
 * '<S185>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case/Subsystem'
 * '<S186>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table'
 * '<S187>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S188>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S189>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S190>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case1/Subsystem'
 * '<S191>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table'
 * '<S192>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S193>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S194>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S195>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case2/Subsystem'
 * '<S196>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table'
 * '<S197>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table/Cosine Lookup'
 * '<S198>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S199>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S200>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case/Subsystem'
 * '<S201>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table'
 * '<S202>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S203>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S204>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S205>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case1/Subsystem'
 * '<S206>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table'
 * '<S207>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S208>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S209>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S210>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case2/Subsystem'
 * '<S211>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table'
 * '<S212>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table/Sine Lookup'
 * '<S213>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table/Sine Lookup/Sine'
 * '<S214>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S215>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/MATLAB Function'
 * '<S216>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case'
 * '<S217>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case1'
 * '<S218>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case'
 * '<S219>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case1'
 * '<S220>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case/Subsystem'
 * '<S221>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case/cos_lookup_table'
 * '<S222>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S223>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S224>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S225>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case1/Subsystem'
 * '<S226>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case1/cos_lookup_table'
 * '<S227>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S228>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S229>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S230>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case/Subsystem'
 * '<S231>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case/sin_lookup_table'
 * '<S232>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S233>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S234>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S235>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case1/Subsystem'
 * '<S236>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case1/sin_lookup_table'
 * '<S237>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S238>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S239>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S240>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/MATLAB Function'
 * '<S241>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case'
 * '<S242>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case1'
 * '<S243>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case'
 * '<S244>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case1'
 * '<S245>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case/Subsystem'
 * '<S246>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case/cos_lookup_table'
 * '<S247>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S248>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S249>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S250>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case1/Subsystem'
 * '<S251>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table'
 * '<S252>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S253>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S254>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S255>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case/Subsystem'
 * '<S256>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case/sin_lookup_table'
 * '<S257>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S258>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S259>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S260>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case1/Subsystem'
 * '<S261>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table'
 * '<S262>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S263>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S264>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S265>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/MATLAB Function'
 * '<S266>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case'
 * '<S267>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case1'
 * '<S268>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case'
 * '<S269>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case1'
 * '<S270>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case/Subsystem'
 * '<S271>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case/cos_lookup_table'
 * '<S272>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S273>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S274>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S275>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case1/Subsystem'
 * '<S276>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table'
 * '<S277>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S278>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S279>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S280>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case/Subsystem'
 * '<S281>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case/sin_lookup_table'
 * '<S282>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S283>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S284>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S285>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case1/Subsystem'
 * '<S286>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table'
 * '<S287>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S288>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S289>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S290>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/MATLAB Function'
 * '<S291>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case'
 * '<S292>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case1'
 * '<S293>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case'
 * '<S294>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case1'
 * '<S295>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case/Subsystem'
 * '<S296>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case/cos_lookup_table'
 * '<S297>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S298>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S299>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S300>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case1/Subsystem'
 * '<S301>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table'
 * '<S302>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S303>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S304>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S305>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case/Subsystem'
 * '<S306>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case/sin_lookup_table'
 * '<S307>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S308>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S309>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S310>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case1/Subsystem'
 * '<S311>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table'
 * '<S312>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S313>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S314>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S315>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/MATLAB Function'
 * '<S316>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch'
 * '<S317>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler'
 * '<S318>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1'
 * '<S319>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2'
 * '<S320>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3'
 * '<S321>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S322>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case'
 * '<S323>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case1'
 * '<S324>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case2'
 * '<S325>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case'
 * '<S326>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case1'
 * '<S327>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case2'
 * '<S328>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case/Subsystem'
 * '<S329>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table'
 * '<S330>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S331>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S332>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S333>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case1/Subsystem'
 * '<S334>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table'
 * '<S335>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S336>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S337>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S338>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case2/Subsystem'
 * '<S339>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table'
 * '<S340>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table/Cosine Lookup'
 * '<S341>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S342>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S343>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case/Subsystem'
 * '<S344>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table'
 * '<S345>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S346>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S347>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S348>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case1/Subsystem'
 * '<S349>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table'
 * '<S350>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S351>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S352>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S353>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case2/Subsystem'
 * '<S354>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table'
 * '<S355>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table/Sine Lookup'
 * '<S356>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table/Sine Lookup/Sine'
 * '<S357>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_switch_case2/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S358>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/MATLAB Function'
 * '<S359>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case'
 * '<S360>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case1'
 * '<S361>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case'
 * '<S362>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case1'
 * '<S363>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case/Subsystem'
 * '<S364>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case/cos_lookup_table'
 * '<S365>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S366>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S367>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S368>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case1/Subsystem'
 * '<S369>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case1/cos_lookup_table'
 * '<S370>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S371>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S372>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S373>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case/Subsystem'
 * '<S374>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case/sin_lookup_table'
 * '<S375>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S376>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S377>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S378>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case1/Subsystem'
 * '<S379>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case1/sin_lookup_table'
 * '<S380>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S381>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S382>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S383>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/MATLAB Function'
 * '<S384>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case'
 * '<S385>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case1'
 * '<S386>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case'
 * '<S387>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case1'
 * '<S388>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case/Subsystem'
 * '<S389>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case/cos_lookup_table'
 * '<S390>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S391>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S392>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S393>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case1/Subsystem'
 * '<S394>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table'
 * '<S395>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S396>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S397>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S398>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case/Subsystem'
 * '<S399>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case/sin_lookup_table'
 * '<S400>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S401>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S402>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S403>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case1/Subsystem'
 * '<S404>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table'
 * '<S405>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S406>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S407>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S408>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/MATLAB Function'
 * '<S409>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case'
 * '<S410>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case1'
 * '<S411>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case'
 * '<S412>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case1'
 * '<S413>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case/Subsystem'
 * '<S414>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case/cos_lookup_table'
 * '<S415>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S416>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S417>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S418>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case1/Subsystem'
 * '<S419>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table'
 * '<S420>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S421>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S422>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S423>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case/Subsystem'
 * '<S424>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case/sin_lookup_table'
 * '<S425>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S426>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S427>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S428>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case1/Subsystem'
 * '<S429>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table'
 * '<S430>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S431>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S432>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S433>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/MATLAB Function'
 * '<S434>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case'
 * '<S435>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case1'
 * '<S436>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case'
 * '<S437>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case1'
 * '<S438>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case/Subsystem'
 * '<S439>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case/cos_lookup_table'
 * '<S440>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S441>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S442>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S443>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case1/Subsystem'
 * '<S444>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table'
 * '<S445>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S446>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S447>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S448>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case/Subsystem'
 * '<S449>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case/sin_lookup_table'
 * '<S450>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S451>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S452>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S453>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case1/Subsystem'
 * '<S454>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table'
 * '<S455>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S456>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S457>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S458>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation'
 * '<S459>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Switch Case Action Subsystem'
 * '<S460>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case'
 * '<S461>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1'
 * '<S462>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2'
 * '<S463>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3'
 * '<S464>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case/Subsystem'
 * '<S465>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case/sin_lookup_table'
 * '<S466>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S467>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S468>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S469>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1/Subsystem'
 * '<S470>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1/sin_lookup_table'
 * '<S471>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S472>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S473>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S474>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2/Subsystem'
 * '<S475>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2/sin_lookup_table'
 * '<S476>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2/sin_lookup_table/Sine Lookup'
 * '<S477>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2/sin_lookup_table/Sine Lookup/Sine'
 * '<S478>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S479>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3/Subsystem'
 * '<S480>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3/sin_lookup_table'
 * '<S481>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3/sin_lookup_table/Sine Lookup'
 * '<S482>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3/sin_lookup_table/Sine Lookup/Sine'
 * '<S483>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S484>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean'
 * '<S485>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean1'
 * '<S486>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean2'
 * '<S487>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean3'
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
