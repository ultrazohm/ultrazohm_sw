/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_komplex.h
 *
 * Code generated for Simulink model 'FOC_komplex'.
 *
 * Model version                  : 2.22
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Aug 10 16:05:37 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_FOC_komplex_h_
#define RTW_HEADER_FOC_komplex_h_
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef FOC_komplex_COMMON_INCLUDES_
#define FOC_komplex_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_komplex_COMMON_INCLUDES_ */

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

#define FOC_komplex_M                  (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef DEFINED_TYPEDEF_FOR_struct_JzxjSLV8uywa9J407DybhG_
#define DEFINED_TYPEDEF_FOR_struct_JzxjSLV8uywa9J407DybhG_

typedef struct {
  real32_T Id_Ref;
  real32_T Iq_Ref;
  real32_T Ud_Ref;
  real32_T Uq_Ref;
  uint8_T Voltage_Limit;
  uint8_T error_speed_limit;
} struct_JzxjSLV8uywa9J407DybhG;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T Delay_DSTATE_j[50];         /* '<S31>/Delay' */
  real32_T Delay_DSTATE_m[200];        /* '<S32>/Delay' */
  real32_T Ref_Id;                     /* '<S4>/Merge' */
  real32_T Ref_Iq;                     /* '<S4>/Merge1' */
  real32_T Delay_DSTATE;               /* '<S3>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S3>/Discrete-Time Integrator' */
  real32_T Accumulator_DSTATE;         /* '<S31>/Accumulator' */
  real32_T Accumulator_DSTATE_o;       /* '<S32>/Accumulator' */
  real32_T Delay1_DSTATE;              /* '<S9>/Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE_k;/* '<S20>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_a;             /* '<S9>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_l;/* '<S21>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_i;             /* '<S14>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_o;/* '<S14>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_b;             /* '<S8>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_a;/* '<S13>/Discrete-Time Integrator' */
  real32_T U_q_lim;
  int_T idxDelay;
  int8_T switch_case_power_ActiveSubsyst;/* '<S1>/switch_case_power' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S4>/Switch Case' */
  uint8_T error_speed_limit_h;         /* '<S8>/function_Eckdrehzahl' */
  uint8_T Delay_DSTATE_bl;             /* '<S4>/Delay' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Act_Iu;                     /* '<Root>/Act_Iu' */
  real32_T Act_Iv;                     /* '<Root>/Act_Iv' */
  real32_T Act_Iw;                     /* '<Root>/Act_Iw' */
  real32_T Act_theta_el;               /* '<Root>/Act_theta_el' */
  real32_T Act_w_el;                   /* '<Root>/Act_w_el' */
  real32_T Act_U_ZK;                   /* '<Root>/Act_U_ZK' */
  real32_T Act_n;                      /* '<Root>/Act_n' */
  real32_T Ref_n;                      /* '<Root>/Ref_n' */
  real32_T Ref_Id_ext;                 /* '<Root>/Ref_Id_ext' */
  real32_T Ref_Iq_ext;                 /* '<Root>/Ref_Iq_ext' */
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
  real32_T Id_Act;                     /* '<Root>/Id_Act' */
  real32_T Iq_Act;                     /* '<Root>/Iq_Act' */
  real32_T Id_Ref;                     /* '<Root>/Id_Ref' */
  real32_T Iq_Ref;                     /* '<Root>/Iq_Ref' */
  real32_T Ud_Ref;                     /* '<Root>/Ud_Ref' */
  real32_T Uq_Ref;                     /* '<Root>/Uq_Ref' */
  uint8_T Voltage_Limit;               /* '<Root>/Voltage_Limit' */
  uint8_T error_speed_limit;           /* '<Root>/error_speed_limit' */
  real32_T fault_peak_current;         /* '<Root>/fault_peak_current' */
  real32_T fault_max_current;          /* '<Root>/fault_max_current' */
  real32_T fault_peak_speed;           /* '<Root>/fault_peak_speed' */
  real32_T fault_max_speed;            /* '<Root>/fault_max_speed' */
} ExtY;

/* Parameters (default storage) */
struct P_ {
  real_T T_VF_n;                       /* Variable: T_VF_n
                                        * Referenced by: '<S14>/Gain'
                                        */
  real32_T Kis_id;                     /* Variable: Kis_id
                                        * Referenced by: '<S20>/Gain1'
                                        */
  real32_T Kis_iq;                     /* Variable: Kis_iq
                                        * Referenced by: '<S21>/Gain1'
                                        */
  real32_T Kis_n;                      /* Variable: Kis_n
                                        * Referenced by: '<S13>/Gain1'
                                        */
  real32_T Kp_id;                      /* Variable: Kp_id
                                        * Referenced by: '<S20>/Gain'
                                        */
  real32_T Kp_iq;                      /* Variable: Kp_iq
                                        * Referenced by: '<S21>/Gain'
                                        */
  real32_T Kp_n;                       /* Variable: Kp_n
                                        * Referenced by: '<S13>/Gain'
                                        */
  real32_T L_d;                        /* Variable: L_d
                                        * Referenced by:
                                        *   '<S8>/Function_Feldschwaeche'
                                        *   '<S22>/Gain1'
                                        */
  real32_T L_q;                        /* Variable: L_q
                                        * Referenced by:
                                        *   '<S8>/function_Eckdrehzahl'
                                        *   '<S22>/Gain'
                                        */
  real32_T Psi_PM;                     /* Variable: Psi_PM
                                        * Referenced by:
                                        *   '<S8>/Function_Feldschwaeche'
                                        *   '<S8>/function_Eckdrehzahl'
                                        *   '<S22>/Constant'
                                        */
  real32_T R;                          /* Variable: R
                                        * Referenced by: '<S8>/function_Eckdrehzahl'
                                        */
  real32_T T_R;                        /* Variable: T_R
                                        * Referenced by:
                                        *   '<S3>/Gain'
                                        *   '<S11>/Winkelwahl'
                                        *   '<S13>/Gain1'
                                        *   '<S14>/Gain'
                                        *   '<S20>/Gain1'
                                        *   '<S21>/Gain1'
                                        */
  real32_T i_max;                      /* Variable: i_max
                                        * Referenced by: '<S5>/Constant1'
                                        */
  real32_T i_max_peak;                 /* Variable: i_max_peak
                                        * Referenced by: '<S5>/Constant'
                                        */
  real32_T i_ref_max;                  /* Variable: i_ref_max
                                        * Referenced by:
                                        *   '<S8>/function_Eckdrehzahl'
                                        *   '<S8>/Constant'
                                        *   '<S10>/Constant'
                                        */
  real32_T n_max;                      /* Variable: n_max
                                        * Referenced by: '<S5>/Constant3'
                                        */
  real32_T n_max_peak;                 /* Variable: n_max_peak
                                        * Referenced by: '<S5>/Constant2'
                                        */
  real32_T n_ref_max;                  /* Variable: n_ref_max
                                        * Referenced by: '<S8>/function_Eckdrehzahl'
                                        */
  real32_T p;                          /* Variable: p
                                        * Referenced by: '<S8>/function_Eckdrehzahl'
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
extern void FOC_komplex_initialize(RT_MODEL *const rtM);
extern void FOC_komplex_step(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S15>/Data Type Duplicate' : Unused code path elimination
 * Block '<S15>/Data Type Propagation' : Unused code path elimination
 * Block '<S16>/Data Type Duplicate' : Unused code path elimination
 * Block '<S16>/Data Type Propagation' : Unused code path elimination
 * Block '<S8>/Scope' : Unused code path elimination
 * Block '<S9>/Id' : Unused code path elimination
 * Block '<S9>/Iq' : Unused code path elimination
 * Block '<S9>/Lim_U_D' : Unused code path elimination
 * Block '<S9>/Lim_U_Q' : Unused code path elimination
 * Block '<S9>/U_q_parts' : Unused code path elimination
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
 * hilite_system('uz_codegen_FOC/FOC_komplex')    - opens subsystem uz_codegen_FOC/FOC_komplex
 * hilite_system('uz_codegen_FOC/FOC_komplex/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen_FOC'
 * '<S1>'   : 'uz_codegen_FOC/FOC_komplex'
 * '<S2>'   : 'uz_codegen_FOC/FOC_komplex/Geo-Summe'
 * '<S3>'   : 'uz_codegen_FOC/FOC_komplex/PT1'
 * '<S4>'   : 'uz_codegen_FOC/FOC_komplex/Regelung'
 * '<S5>'   : 'uz_codegen_FOC/FOC_komplex/Sicherheitsabschaltung'
 * '<S6>'   : 'uz_codegen_FOC/FOC_komplex/Strang-Rotor'
 * '<S7>'   : 'uz_codegen_FOC/FOC_komplex/aus'
 * '<S8>'   : 'uz_codegen_FOC/FOC_komplex/Regelung/Drehzahlregler'
 * '<S9>'   : 'uz_codegen_FOC/FOC_komplex/Regelung/Stromregler diskret'
 * '<S10>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Stromvorgabe_extern'
 * '<S11>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Tastgradumwandlung'
 * '<S12>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Drehzahlregler/Function_Feldschwaeche'
 * '<S13>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Drehzahlregler/PI_for_Limiter'
 * '<S14>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Drehzahlregler/PT1_V_n'
 * '<S15>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Drehzahlregler/Saturation Dynamic'
 * '<S16>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Drehzahlregler/Saturation Dynamic1'
 * '<S17>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Drehzahlregler/function_Eckdrehzahl'
 * '<S18>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Stromregler diskret/Entkopplung'
 * '<S19>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Stromregler diskret/Function_Spannungsbegrenzung'
 * '<S20>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Stromregler diskret/Regler_I_d'
 * '<S21>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Stromregler diskret/Regler_I_q'
 * '<S22>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Stromregler diskret/Entkopplung/Switch Case Action Subsystem'
 * '<S23>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Stromregler diskret/Entkopplung/Switch Case Action Subsystem1'
 * '<S24>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Stromvorgabe_extern/Function_I_limit'
 * '<S25>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Tastgradumwandlung/Rotor-Strang'
 * '<S26>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Tastgradumwandlung/Symmetrierung'
 * '<S27>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Tastgradumwandlung/Tastgradbestimmung'
 * '<S28>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Tastgradumwandlung/Winkelwahl'
 * '<S29>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Tastgradumwandlung/Rotor-Strang/Inverse-Clark-Transformation'
 * '<S30>'  : 'uz_codegen_FOC/FOC_komplex/Regelung/Tastgradumwandlung/Rotor-Strang/Inverse-Park-Transormation'
 * '<S31>'  : 'uz_codegen_FOC/FOC_komplex/Sicherheitsabschaltung/moving mean'
 * '<S32>'  : 'uz_codegen_FOC/FOC_komplex/Sicherheitsabschaltung/moving mean1'
 * '<S33>'  : 'uz_codegen_FOC/FOC_komplex/Strang-Rotor/Clarke-Transformation'
 * '<S34>'  : 'uz_codegen_FOC/FOC_komplex/Strang-Rotor/Park-Transformation'
 */

/*-
 * Requirements for '<Root>': FOC_komplex
 */
#endif                                 /* RTW_HEADER_FOC_komplex_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
