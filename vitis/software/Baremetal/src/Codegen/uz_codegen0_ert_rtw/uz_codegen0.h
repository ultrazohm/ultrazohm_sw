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
 * C/C++ source code generated on : Thu Jan 19 18:04:57 2023
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
  real32_T re_lim_i;                   /* '<S32>/MATLAB Function' */
  real32_T Add1_l;                     /* '<S23>/Add1' */
  real32_T theta_e;                    /* '<S23>/Sum' */
  real32_T Product1_a;                 /* '<S31>/Product1' */
  real32_T im_lim_l;                   /* '<S32>/MATLAB Function' */
  real32_T Merge_oy;                   /* '<S36>/Merge' */
  real32_T Merge1_h;                   /* '<S36>/Merge1' */
  real32_T im_lim_mv;                  /* '<S31>/MATLAB Function' */
  real32_T re_lim_l;                   /* '<S31>/MATLAB Function' */
  real32_T Product_am;                 /* '<S34>/Product' */
  real32_T Strom_kompensiert_l;        /* '<S30>/Strom_kompensiert' */
  real32_T Delay1_c;                   /* '<S33>/Delay1' */
  real32_T im_lim_k;                   /* '<S33>/MATLAB Function' */
  real32_T Merge_gt;                   /* '<S84>/Merge' */
  real32_T Sum_j;                      /* '<S32>/Sum' */
  real32_T re_lim_b;                   /* '<S33>/MATLAB Function' */
  real32_T Delay1_m;                   /* '<S34>/Delay1' */
  real32_T Merge_ac;                   /* '<S103>/Merge' */
  real32_T Sum_o;                      /* '<S33>/Sum' */
  real32_T im_lim_o;                   /* '<S34>/MATLAB Function' */
  real32_T re_lim_g;                   /* '<S34>/MATLAB Function' */
  real32_T Sum_d;                      /* '<S34>/Sum' */
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
  DW_MATLABFunction_m sf_MATLABFunction_e;/* '<S250>/MATLAB Function' */
  DW_Strangstromregler_asymetrisc Strangstromregler_asymetrisch1;
                                    /* '<S10>/Strangstromregler_asymetrisch1' */
  DW_Strangstromregler_asymetrisc Strangstromregler_asymetrisch_h;
                                     /* '<S10>/Strangstromregler_asymetrisch' */
  real32_T Delay_DSTATE_k[20];         /* '<S385>/Delay' */
  real32_T Delay_DSTATE_ki[120];       /* '<S386>/Delay' */
  real32_T Delay_DSTATE_kl[20];        /* '<S387>/Delay' */
  real32_T Delay_DSTATE_b[20];         /* '<S388>/Delay' */
  real32_T I_im;                       /* '<S4>/Merge4' */
  real32_T Merge1;                     /* '<S8>/Merge1' */
  real32_T I_re;                       /* '<S4>/Merge3' */
  real32_T Merge;                      /* '<S8>/Merge' */
  real32_T Merge5;                     /* '<S10>/Merge5' */
  real32_T Merge4;                     /* '<S10>/Merge4' */
  real32_T Merge3;                     /* '<S10>/Merge3' */
  real32_T Delay_DSTATE;               /* '<S3>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S3>/Discrete-Time Integrator' */
  real32_T Accumulator_DSTATE;         /* '<S385>/Accumulator' */
  real32_T Accumulator_DSTATE_d;       /* '<S386>/Accumulator' */
  real32_T Accumulator_DSTATE_f;       /* '<S387>/Accumulator' */
  real32_T Accumulator_DSTATE_n;       /* '<S388>/Accumulator' */
  real32_T Delay_DSTATE_n;             /* '<S14>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_n;/* '<S14>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_h;             /* '<S7>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_f;/* '<S13>/Discrete-Time Integrator' */
  real32_T Delay1_DSTATE;              /* '<S251>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_o;/* '<S251>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_l;             /* '<S251>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S251>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_o;            /* '<S252>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_m;/* '<S252>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_nv;            /* '<S252>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_f;/* '<S252>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_g;            /* '<S253>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_c;/* '<S253>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_a;             /* '<S253>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTAT_o;/* '<S253>/Discrete-Time Integrator1' */
  real32_T Delay1_DSTATE_oi;           /* '<S254>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S254>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_nm;            /* '<S254>/Delay' */
  real32_T DiscreteTimeIntegrator1_DSTA_os;/* '<S254>/Discrete-Time Integrator1' */
  real32_T a;
  real32_T b;
  real32_T c;
  real32_T Gain;                       /* '<S3>/Gain' */
  real32_T Add;                        /* '<S4>/Add' */
  real32_T Delay1;                     /* '<S251>/Delay1' */
  real32_T theta_m;                    /* '<S25>/Sum' */
  real32_T Product1_d;                 /* '<S251>/Product1' */
  real32_T Switch2;                    /* '<S15>/Switch2' */
  real32_T Merge_a;                    /* '<S256>/Merge' */
  real32_T Merge1_m;                   /* '<S256>/Merge1' */
  real32_T Gain1;                      /* '<S13>/Gain1' */
  real32_T Product_d;                  /* '<S254>/Product' */
  real32_T y;                          /* '<S13>/Sum' */
  real32_T Delay1_a;                   /* '<S253>/Delay1' */
  real32_T Merge_g;                    /* '<S304>/Merge' */
  real32_T Sum_a;                      /* '<S252>/Sum' */
  real32_T re_lim;                     /* '<S253>/MATLAB Function' */
  real32_T Delay1_k;                   /* '<S254>/Delay1' */
  real32_T Merge_dn;                   /* '<S323>/Merge' */
  real32_T Sum_cr;                     /* '<S253>/Sum' */
  real32_T im_lim_f;                   /* '<S254>/MATLAB Function' */
  real32_T re_lim_e;                   /* '<S254>/MATLAB Function' */
  real32_T Sum_an;                     /* '<S254>/Sum' */
  real32_T I_im_mit;                   /* '<S250>/MATLAB Function' */
  real32_T I_re_gegen;                 /* '<S250>/MATLAB Function' */
  real32_T I_im_gegen;                 /* '<S250>/MATLAB Function' */
  real32_T I_re_null;                  /* '<S250>/MATLAB Function' */
  real32_T I_im_null;                  /* '<S250>/MATLAB Function' */
  real32_T U_im_k;                     /* '<S252>/Sum6' */
  real32_T Gain1_m;                    /* '<S253>/Gain1' */
  real32_T U_re_n;                     /* '<S253>/Sum5' */
  real32_T U_im_p;                     /* '<S253>/Sum6' */
  real32_T Gain1_j;                    /* '<S254>/Gain1' */
  real32_T U_re_d;                     /* '<S254>/Sum5' */
  real32_T Gain2_i;                    /* '<S254>/Gain2' */
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
   *   '<S368>/Look-Up Table'
   *   '<S373>/Look-Up Table'
   *   '<S378>/Look-Up Table'
   *   '<S383>/Look-Up Table'
   *   '<S43>/Look-Up Table'
   *   '<S45>/Look-Up Table'
   *   '<S51>/Look-Up Table'
   *   '<S53>/Look-Up Table'
   *   '<S59>/Look-Up Table'
   *   '<S61>/Look-Up Table'
   *   '<S70>/Look-Up Table'
   *   '<S72>/Look-Up Table'
   *   '<S78>/Look-Up Table'
   *   '<S80>/Look-Up Table'
   *   '<S89>/Look-Up Table'
   *   '<S91>/Look-Up Table'
   *   '<S97>/Look-Up Table'
   *   '<S99>/Look-Up Table'
   *   '<S108>/Look-Up Table'
   *   '<S110>/Look-Up Table'
   *   '<S116>/Look-Up Table'
   *   '<S118>/Look-Up Table'
   *   '<S127>/Look-Up Table'
   *   '<S129>/Look-Up Table'
   *   '<S135>/Look-Up Table'
   *   '<S137>/Look-Up Table'
   *   '<S153>/Look-Up Table'
   *   '<S155>/Look-Up Table'
   *   '<S161>/Look-Up Table'
   *   '<S163>/Look-Up Table'
   *   '<S169>/Look-Up Table'
   *   '<S171>/Look-Up Table'
   *   '<S180>/Look-Up Table'
   *   '<S182>/Look-Up Table'
   *   '<S188>/Look-Up Table'
   *   '<S190>/Look-Up Table'
   *   '<S199>/Look-Up Table'
   *   '<S201>/Look-Up Table'
   *   '<S207>/Look-Up Table'
   *   '<S209>/Look-Up Table'
   *   '<S218>/Look-Up Table'
   *   '<S220>/Look-Up Table'
   *   '<S226>/Look-Up Table'
   *   '<S228>/Look-Up Table'
   *   '<S237>/Look-Up Table'
   *   '<S239>/Look-Up Table'
   *   '<S245>/Look-Up Table'
   *   '<S247>/Look-Up Table'
   *   '<S263>/Look-Up Table'
   *   '<S265>/Look-Up Table'
   *   '<S271>/Look-Up Table'
   *   '<S273>/Look-Up Table'
   *   '<S279>/Look-Up Table'
   *   '<S281>/Look-Up Table'
   *   '<S290>/Look-Up Table'
   *   '<S292>/Look-Up Table'
   *   '<S298>/Look-Up Table'
   *   '<S300>/Look-Up Table'
   *   '<S309>/Look-Up Table'
   *   '<S311>/Look-Up Table'
   *   '<S317>/Look-Up Table'
   *   '<S319>/Look-Up Table'
   *   '<S328>/Look-Up Table'
   *   '<S330>/Look-Up Table'
   *   '<S336>/Look-Up Table'
   *   '<S338>/Look-Up Table'
   *   '<S347>/Look-Up Table'
   *   '<S349>/Look-Up Table'
   *   '<S355>/Look-Up Table'
   *   '<S357>/Look-Up Table'
   */
  int16_T pooled16[65];
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
                                        *   '<S141>/Gain1'
                                        *   '<S141>/Gain2'
                                        *   '<S251>/Gain1'
                                        *   '<S251>/Gain2'
                                        */
  real32_T K2;                         /* Variable: K2
                                        * Referenced by:
                                        *   '<S32>/Gain1'
                                        *   '<S32>/Gain2'
                                        *   '<S142>/Gain1'
                                        *   '<S142>/Gain2'
                                        *   '<S252>/Gain1'
                                        *   '<S252>/Gain2'
                                        */
  real32_T K4;                         /* Variable: K4
                                        * Referenced by:
                                        *   '<S33>/Gain1'
                                        *   '<S33>/Gain2'
                                        *   '<S143>/Gain1'
                                        *   '<S143>/Gain2'
                                        *   '<S253>/Gain1'
                                        *   '<S253>/Gain2'
                                        */
  real32_T K6;                         /* Variable: K6
                                        * Referenced by:
                                        *   '<S34>/Gain1'
                                        *   '<S34>/Gain2'
                                        *   '<S144>/Gain1'
                                        *   '<S144>/Gain2'
                                        *   '<S254>/Gain1'
                                        *   '<S254>/Gain2'
                                        */
  real32_T Kp;                         /* Variable: Kp
                                        * Referenced by:
                                        *   '<S31>/Gain6'
                                        *   '<S32>/Gain6'
                                        *   '<S33>/Gain6'
                                        *   '<S34>/Gain6'
                                        *   '<S141>/Gain6'
                                        *   '<S142>/Gain6'
                                        *   '<S143>/Gain6'
                                        *   '<S144>/Gain6'
                                        *   '<S251>/Gain6'
                                        *   '<S252>/Gain6'
                                        *   '<S253>/Gain6'
                                        *   '<S254>/Gain6'
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
 * '<S36>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case'
 * '<S37>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1'
 * '<S38>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2'
 * '<S39>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/Subsystem'
 * '<S40>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table'
 * '<S41>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S42>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S43>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S44>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S45>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S46>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S47>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/Subsystem'
 * '<S48>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table'
 * '<S49>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S50>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S51>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S52>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S53>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S54>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S55>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/Subsystem'
 * '<S56>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table'
 * '<S57>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Cosine Lookup'
 * '<S58>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Sine Lookup'
 * '<S59>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S60>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S61>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Sine Lookup/Sine'
 * '<S62>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S63>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/MATLAB Function'
 * '<S64>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case'
 * '<S65>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case1'
 * '<S66>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case/Subsystem'
 * '<S67>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table'
 * '<S68>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S69>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S70>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S71>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S72>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S73>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S74>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case1/Subsystem'
 * '<S75>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table'
 * '<S76>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S77>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S78>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S79>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S80>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S81>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S82>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/MATLAB Function'
 * '<S83>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case'
 * '<S84>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case1'
 * '<S85>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case/Subsystem'
 * '<S86>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table'
 * '<S87>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S88>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S89>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S90>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S91>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S92>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S93>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case1/Subsystem'
 * '<S94>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table'
 * '<S95>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S96>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S97>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S98>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S99>'  : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S100>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S101>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/MATLAB Function'
 * '<S102>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case'
 * '<S103>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case1'
 * '<S104>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case/Subsystem'
 * '<S105>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table'
 * '<S106>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S107>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S108>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S109>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S110>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S111>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S112>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case1/Subsystem'
 * '<S113>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table'
 * '<S114>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S115>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S116>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S117>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S118>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S119>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S120>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/MATLAB Function'
 * '<S121>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case'
 * '<S122>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case1'
 * '<S123>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case/Subsystem'
 * '<S124>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table'
 * '<S125>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S126>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S127>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S128>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S129>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S130>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S131>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case1/Subsystem'
 * '<S132>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table'
 * '<S133>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S134>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S135>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S136>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S137>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S138>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S139>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/MATLAB Function'
 * '<S140>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch'
 * '<S141>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler'
 * '<S142>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1'
 * '<S143>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2'
 * '<S144>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3'
 * '<S145>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S146>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case'
 * '<S147>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1'
 * '<S148>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2'
 * '<S149>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/Subsystem'
 * '<S150>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table'
 * '<S151>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S152>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S153>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S154>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S155>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S156>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S157>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/Subsystem'
 * '<S158>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table'
 * '<S159>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S160>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S161>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S162>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S163>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S164>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S165>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/Subsystem'
 * '<S166>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table'
 * '<S167>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Cosine Lookup'
 * '<S168>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Sine Lookup'
 * '<S169>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S170>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S171>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Sine Lookup/Sine'
 * '<S172>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S173>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/MATLAB Function'
 * '<S174>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case'
 * '<S175>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case1'
 * '<S176>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case/Subsystem'
 * '<S177>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table'
 * '<S178>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S179>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S180>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S181>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S182>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S183>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S184>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case1/Subsystem'
 * '<S185>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table'
 * '<S186>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S187>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S188>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S189>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S190>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S191>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S192>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/MATLAB Function'
 * '<S193>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case'
 * '<S194>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case1'
 * '<S195>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case/Subsystem'
 * '<S196>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table'
 * '<S197>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S198>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S199>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S200>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S201>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S202>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S203>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case1/Subsystem'
 * '<S204>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table'
 * '<S205>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S206>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S207>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S208>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S209>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S210>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S211>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/MATLAB Function'
 * '<S212>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case'
 * '<S213>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case1'
 * '<S214>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case/Subsystem'
 * '<S215>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table'
 * '<S216>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S217>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S218>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S219>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S220>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S221>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S222>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case1/Subsystem'
 * '<S223>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table'
 * '<S224>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S225>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S226>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S227>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S228>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S229>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S230>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/MATLAB Function'
 * '<S231>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case'
 * '<S232>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case1'
 * '<S233>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case/Subsystem'
 * '<S234>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table'
 * '<S235>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S236>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S237>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S238>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S239>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S240>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S241>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case1/Subsystem'
 * '<S242>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table'
 * '<S243>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S244>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S245>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S246>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S247>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S248>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch1/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S249>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/MATLAB Function'
 * '<S250>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch'
 * '<S251>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler'
 * '<S252>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1'
 * '<S253>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2'
 * '<S254>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3'
 * '<S255>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/MATLAB Function'
 * '<S256>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case'
 * '<S257>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1'
 * '<S258>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2'
 * '<S259>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/Subsystem'
 * '<S260>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table'
 * '<S261>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S262>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S263>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S264>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S265>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S266>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S267>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/Subsystem'
 * '<S268>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table'
 * '<S269>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S270>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S271>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S272>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S273>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S274>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S275>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/Subsystem'
 * '<S276>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table'
 * '<S277>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Cosine Lookup'
 * '<S278>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Sine Lookup'
 * '<S279>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S280>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S281>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Sine Lookup/Sine'
 * '<S282>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/Referenzstromerzeugung_asymetrisch/sin_cos_switch_case2/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S283>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/MATLAB Function'
 * '<S284>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case'
 * '<S285>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case1'
 * '<S286>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case/Subsystem'
 * '<S287>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table'
 * '<S288>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S289>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S290>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S291>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S292>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S293>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S294>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case1/Subsystem'
 * '<S295>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table'
 * '<S296>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S297>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S298>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S299>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S300>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S301>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S302>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/MATLAB Function'
 * '<S303>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case'
 * '<S304>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case1'
 * '<S305>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case/Subsystem'
 * '<S306>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table'
 * '<S307>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S308>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S309>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S310>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S311>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S312>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S313>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case1/Subsystem'
 * '<S314>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table'
 * '<S315>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S316>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S317>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S318>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S319>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S320>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler1/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S321>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/MATLAB Function'
 * '<S322>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case'
 * '<S323>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case1'
 * '<S324>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case/Subsystem'
 * '<S325>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table'
 * '<S326>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S327>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S328>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S329>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S330>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S331>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S332>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case1/Subsystem'
 * '<S333>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table'
 * '<S334>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S335>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S336>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S337>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S338>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S339>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler2/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S340>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/MATLAB Function'
 * '<S341>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case'
 * '<S342>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case1'
 * '<S343>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case/Subsystem'
 * '<S344>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table'
 * '<S345>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Cosine Lookup'
 * '<S346>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Sine Lookup'
 * '<S347>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S348>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S349>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine'
 * '<S350>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S351>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case1/Subsystem'
 * '<S352>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table'
 * '<S353>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup'
 * '<S354>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Sine Lookup'
 * '<S355>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine'
 * '<S356>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Cosine Lookup/Cosine/Handle Quarter Symmetry Cosine'
 * '<S357>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine'
 * '<S358>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Subsystem/Strangstromregler_asymetrisch2/resonater-PI-Regler3/sin_cos_switch_case1/cos_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S359>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation'
 * '<S360>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Switch Case Action Subsystem'
 * '<S361>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case'
 * '<S362>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1'
 * '<S363>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2'
 * '<S364>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3'
 * '<S365>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case/Subsystem'
 * '<S366>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case/sin_lookup_table'
 * '<S367>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case/sin_lookup_table/Sine Lookup'
 * '<S368>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case/sin_lookup_table/Sine Lookup/Sine'
 * '<S369>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S370>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1/Subsystem'
 * '<S371>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1/sin_lookup_table'
 * '<S372>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1/sin_lookup_table/Sine Lookup'
 * '<S373>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine'
 * '<S374>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case1/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S375>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2/Subsystem'
 * '<S376>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2/sin_lookup_table'
 * '<S377>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2/sin_lookup_table/Sine Lookup'
 * '<S378>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2/sin_lookup_table/Sine Lookup/Sine'
 * '<S379>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case2/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S380>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3/Subsystem'
 * '<S381>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3/sin_lookup_table'
 * '<S382>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3/sin_lookup_table/Sine Lookup'
 * '<S383>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3/sin_lookup_table/Sine Lookup/Sine'
 * '<S384>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Regelung_asymetrisch/Vorsteuerung_Rastmomentkompensation/Rastmomentkompensation/sin_switch_case3/sin_lookup_table/Sine Lookup/Sine/Handle Quarter Symmetry Sine'
 * '<S385>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean'
 * '<S386>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean1'
 * '<S387>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean2'
 * '<S388>' : 'uz_codegen/uz_codegen/Regelung_Einzelstrang_asymetrisch/Sicherheitsabschaltung/moving mean3'
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
