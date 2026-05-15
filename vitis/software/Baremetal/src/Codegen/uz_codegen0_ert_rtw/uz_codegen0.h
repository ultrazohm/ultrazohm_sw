/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 10.5
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Thu May 14 14:56:45 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#ifndef uz_codegen0_h_
#define uz_codegen0_h_
#ifndef uz_codegen0_COMMON_INCLUDES_
#define uz_codegen0_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#include "complex_types.h"
#endif                                 /* uz_codegen0_COMMON_INCLUDES_ */

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

/* Exported data define */

/* Definition for custom storage class: Define */
#define DIVIDE_SQRT_THREE_BY_TWO       0.866025388F              /* Referenced by:
                                                                  * '<S37>/Gain5'
                                                                  * '<S37>/sqrt(3)//2'
                                                                  */
#define DIVIDE_TWO_BY_THREE            0.666666687F              /* Referenced by:
                                                                  * '<S25>/Gain2'
                                                                  * '<S37>/Gain'
                                                                  * '<S37>/Gain1'
                                                                  */
#define GAIN_RADS_TO_HZ                0.159154937F              /* Referenced by: '<S11>/Gain' */
#define GAIN_UMIN_TO_HZ                0.00265258248F            /* Referenced by: '<S8>/Gain' */

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef DEFINED_TYPEDEF_FOR_Soll_Regelungsart_en_
#define DEFINED_TYPEDEF_FOR_Soll_Regelungsart_en_

typedef enum {
  Error = 99,                          /* Default value */
  Drehzahl = 0,
  Trajektorie = 1,
  Strom = 2
} Soll_Regelungsart_en;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Bus_Ctrl_Config_
#define DEFINED_TYPEDEF_FOR_Bus_Ctrl_Config_

typedef struct {
  float Tsample;
  float T_PWM;
  float TNi;
  float KPi;
  float TEi;
  float TNn;
  float KPn;
  float n_hyst_upperlimit;
  float n_hyst_lowerlimit;
  float t_traj;
  float IGBT_dc_min;
  float IGBT_deadtime;
} Bus_Ctrl_Config;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Bus_PMSM_Out_
#define DEFINED_TYPEDEF_FOR_Bus_PMSM_Out_

typedef struct {
  float pmsm_Iuvw[3];
  float pmsm_Omega_mech;
  float pmsm_phi_mech;
  float pmsm_m_mot;
} Bus_PMSM_Out;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Bus_PMSM_In_
#define DEFINED_TYPEDEF_FOR_Bus_PMSM_In_

typedef struct {
  float Last_M;
  float Last_J;
  bool Bremse;
  float Udq[2];
  bool switchUabc_dq;
} Bus_PMSM_In;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Status_Ctrl_
#define DEFINED_TYPEDEF_FOR_Status_Ctrl_

typedef enum {
  Error_Status = 99,                   /* Default value */
  Ready = 0,
  Run = 1,
  En = 2,
  Dis = 3
} Status_Ctrl;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Bus_ZM_In_
#define DEFINED_TYPEDEF_FOR_Bus_ZM_In_

typedef struct {
  float Soll_Drehzahl;
  float Soll_id;
  float Soll_iq;
  float Start_Traj;
  bool Fehlermeldung;
  Status_Ctrl Soll_Status;
  Soll_Regelungsart_en Soll_Regelungsart;
} Bus_ZM_In;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Bus_Ctrl_Out_
#define DEFINED_TYPEDEF_FOR_Bus_Ctrl_Out_

typedef struct {
  float Dutycycle[3];
  bool act_pwm;
  float ctrl_Ualpha;
  float ctrl_Ubeta;
} Bus_Ctrl_Out;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Bus_ZM_Out_
#define DEFINED_TYPEDEF_FOR_Bus_ZM_Out_

typedef struct {
  bool En_Traj;
  bool Pulsfreigabe;
  Status_Ctrl Ist_Status;
  Soll_Regelungsart_en Ist_Regelungsart;
  float Soll_Drehzahl;
  float Soll_id;
  float Soll_iq;
} Bus_ZM_Out;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Auswahl_Inverter_
#define DEFINED_TYPEDEF_FOR_Auswahl_Inverter_

typedef enum {
  PT1 = 0,                             /* Default value */
  IdealeSchalter,
  IGBT
} Auswahl_Inverter;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Bus_Inv_Config_
#define DEFINED_TYPEDEF_FOR_Bus_Inv_Config_

typedef struct {
  Auswahl_Inverter SwitchInv;
  float Udc;
  float PT1_Gain;
  float PT1_Ts;
  float PT1_reset;
} Bus_Inv_Config;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Bus_PMSM_Config_
#define DEFINED_TYPEDEF_FOR_Bus_PMSM_Config_

typedef struct {
  float mot_R1;
  float mot_psi_pm;
  float mot_Ld;
  float mot_Lq;
  float mot_p;
  float mot_J;
  float mot_n_N;
  float mot_M_N;
  float mot_I_max;
} Bus_PMSM_Config;

#endif

/* Block signals and states (default storage) for system '<S8>/Drehzahlregelung' */
typedef struct {
  float UnitDelay_DSTATE;              /* '<S15>/Unit Delay' */
  float UnitDelay_DSTATE_j;            /* '<S13>/Unit Delay' */
} DW_Drehzahlregelung_f;

/* Block signals and states (default storage) for system '<S8>/Trajektorie_Erzeugung' */
typedef struct {
  float UnitDelay1_DSTATE;             /* '<S12>/Unit Delay1' */
  float UnitDelay_DSTATE;              /* '<S12>/Unit Delay' */
  float UnitDelay2_DSTATE;             /* '<S20>/Unit Delay2' */
  bool Memory_PreviousInput;           /* '<S19>/Memory' */
  bool Memory_PreviousInput_n;         /* '<S21>/Memory' */
  bool Trajektorie_Erzeugung_MODE;     /* '<S8>/Trajektorie_Erzeugung' */
} DW_Trajektorie_Erzeugung;

/* Block signals and states (default storage) for system '<S3>/Drehzahlregelung' */
typedef struct {
  DW_Trajektorie_Erzeugung Trajektorie_Erzeugung_b;/* '<S8>/Trajektorie_Erzeugung' */
  DW_Drehzahlregelung_f Drehzahlregelung_p;/* '<S8>/Drehzahlregelung' */
  float Switch1;                       /* '<S12>/Switch1' */
  bool Drehzahlregelung_MODE;          /* '<S3>/Drehzahlregelung' */
} DW_Drehzahlregelung;

/* Block signals and states (default storage) for system '<S9>/IDQCtrl' */
typedef struct {
  float UnitDelay_DSTATE;              /* '<S32>/Unit Delay' */
  float UnitDelay_DSTATE_k;            /* '<S33>/Unit Delay' */
} DW_IDQCtrl;

/* Block signals and states (default storage) for system '<S3>/Stromregelung' */
typedef struct {
  DW_IDQCtrl IDQCtrl_c;                /* '<S9>/IDQCtrl' */
} DW_Stromregelung;

/* Block signals and states (default storage) for system '<S1>/Regelung' */
typedef struct {
  DW_Stromregelung Stromregelung_a;    /* '<S3>/Stromregelung' */
  DW_Drehzahlregelung Drehzahlregelung_hk;/* '<S3>/Drehzahlregelung' */
  float Abschaltenwennn_diff101nN2;
                               /* '<S14>/Abschalten, wenn n_diff < 1.01% nN2' */
  bool Regelung_MODE;                  /* '<S1>/Regelung' */
} DW_Regelung;

/* Block signals and states (default storage) for system '<S4>/state_chart' */
typedef struct {
  uint8_t is_active_c3_uz_codegen0;    /* '<S4>/state_chart' */
  uint8_t is_c3_uz_codegen0;           /* '<S4>/state_chart' */
  uint8_t is_NoError;                  /* '<S4>/state_chart' */
  uint8_t is_Run;                      /* '<S4>/state_chart' */
  uint8_t is_Trapez;                   /* '<S4>/state_chart' */
} DW_state_chart;

/* Block signals and states (default storage) for system '<S1>/Zustandsmaschine' */
typedef struct {
  DW_state_chart sf_state_chart;       /* '<S4>/state_chart' */
} DW_Zustandsmaschine;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_Zustandsmaschine Zustandsmaschine_k;/* '<S1>/Zustandsmaschine' */
  DW_Regelung Regelung_e;              /* '<S1>/Regelung' */
  Bus_ZM_Out Bus_ZM_Out_o;             /* '<S4>/state_chart' */
  float Switch;                        /* '<S9>/Switch' */
  float Switch1;                       /* '<S9>/Switch1' */
  bool Logic[2];                       /* '<S21>/Logic' */
  bool UnitDelay_DSTATE;               /* '<S1>/Unit Delay' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: [0 1;1 0;0 1;0 1;1 0;1 0;0 0;0 0])
   * Referenced by:
   *   '<S19>/Logic'
   *   '<S21>/Logic'
   */
  bool pooled5[16];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  Bus_PMSM_Out PMSM_Out;               /* '<Root>/Bus_Live_Out_PMSM' */
  Bus_PMSM_In PMSM_In;                 /* '<Root>/PMSM_In' */
  Bus_ZM_In ZM_In;                     /* '<Root>/Bus_ZM_In' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  Bus_Ctrl_Out Bus_Ctrl_Out_g;         /* '<Root>/Bus_Ctrl_Out' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

/* External data declarations for dependent source files */
extern const Bus_ZM_In uz_codegen0_rtZBus_ZM_In;/* Bus_ZM_In ground */
extern const Bus_ZM_Out uz_codegen0_rtZBus_ZM_Out;/* Bus_ZM_Out ground */

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern Bus_Ctrl_Config struct_Ctrl_Config;/* Variable: struct_Ctrl_Config
                                           * Referenced by:
                                           *   '<S5>/Constant'
                                           *   '<S5>/Constant2'
                                           *   '<S5>/Switch1'
                                           *   '<S5>/Switch2'
                                           *   '<S5>/Switch3'
                                           *   '<S5>/Switch4'
                                           *   '<S9>/Constant3'
                                           *   '<S12>/Constant1'
                                           *   '<S13>/Constant'
                                           *   '<S13>/Constant3'
                                           *   '<S14>/Constant1'
                                           *   '<S14>/Constant2'
                                           *   '<S15>/Constant3'
                                           *   '<S17>/Constant'
                                           *   '<S18>/Constant'
                                           *   '<S32>/Constant'
                                           *   '<S32>/Constant3'
                                           *   '<S33>/Constant'
                                           *   '<S33>/Constant3'
                                           */
extern Bus_PMSM_Config struct_PMSM_Config;/* Variable: struct_PMSM_Config
                                           * Referenced by:
                                           *   '<S9>/Constant2'
                                           *   '<S11>/Constant'
                                           *   '<S26>/Constant'
                                           *   '<S28>/Gain'
                                           *   '<S30>/Constant'
                                           *   '<S31>/Constant'
                                           *   '<S31>/Constant1'
                                           */
extern Bus_ZM_In struct_ZM_In;         /* Variable: struct_ZM_In
                                        * Referenced by:
                                        *   '<S12>/Saturation'
                                        *   '<S20>/Unit Delay2'
                                        */
extern Bus_Inv_Config struct_Inv_Config;/* Variable: struct_Inv_Config
                                         * Referenced by:
                                         *   '<S2>/Constant'
                                         *   '<S25>/Constant2'
                                         */

/* Model entry point functions */
extern void uz_codegen0_initialize(RT_MODEL *const rtM);
extern void uz_codegen0_step(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S16>/Data Type Duplicate' : Unused code path elimination
 * Block '<S16>/Data Type Propagation' : Unused code path elimination
 * Block '<S13>/Scope' : Unused code path elimination
 * Block '<S20>/Scope' : Unused code path elimination
 * Block '<S35>/Data Type Duplicate' : Unused code path elimination
 * Block '<S35>/Data Type Propagation' : Unused code path elimination
 * Block '<S32>/Scope' : Unused code path elimination
 * Block '<S36>/Data Type Duplicate' : Unused code path elimination
 * Block '<S36>/Data Type Propagation' : Unused code path elimination
 * Block '<S33>/Scope' : Unused code path elimination
 * Block '<S5>/Cast To Single1' : Eliminate redundant data type conversion
 * Block '<S11>/Cast To Single' : Eliminate redundant data type conversion
 * Block '<S11>/Cast To Single1' : Eliminate redundant data type conversion
 * Block '<S13>/Cast To Single' : Eliminate redundant data type conversion
 * Block '<S13>/Cast To Single1' : Eliminate redundant data type conversion
 * Block '<S15>/Cast To Single' : Eliminate redundant data type conversion
 * Block '<S25>/Cast To Single' : Eliminate redundant data type conversion
 * Block '<S25>/Cast To Single1' : Eliminate redundant data type conversion
 * Block '<S32>/Cast To Single' : Eliminate redundant data type conversion
 * Block '<S32>/Cast To Single1' : Eliminate redundant data type conversion
 * Block '<S33>/Cast To Single' : Eliminate redundant data type conversion
 * Block '<S33>/Cast To Single1' : Eliminate redundant data type conversion
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
 * '<S2>'   : 'uz_codegen/uz_codegen/Raumzeigermodulation'
 * '<S3>'   : 'uz_codegen/uz_codegen/Regelung'
 * '<S4>'   : 'uz_codegen/uz_codegen/Zustandsmaschine'
 * '<S5>'   : 'uz_codegen/uz_codegen/Raumzeigermodulation/MinimaleSchaltzeit'
 * '<S6>'   : 'uz_codegen/uz_codegen/Raumzeigermodulation/raumzeigermodulation'
 * '<S7>'   : 'uz_codegen/uz_codegen/Regelung/CMP_Ctrl_n'
 * '<S8>'   : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung'
 * '<S9>'   : 'uz_codegen/uz_codegen/Regelung/Stromregelung'
 * '<S10>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/CMP_Ctrl_Traj'
 * '<S11>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/Drehzahlregelung'
 * '<S12>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/Trajektorie_Erzeugung'
 * '<S13>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/Drehzahlregelung/PI_Drehzahl'
 * '<S14>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/Drehzahlregelung/n_Ctrl_hysterese'
 * '<S15>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/Drehzahlregelung/n_filt'
 * '<S16>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/Drehzahlregelung/PI_Drehzahl/Saturation Dynamic'
 * '<S17>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/Trajektorie_Erzeugung/Compare To Constant'
 * '<S18>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/Trajektorie_Erzeugung/Compare To Constant1'
 * '<S19>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/Trajektorie_Erzeugung/S-R Flip-Flop'
 * '<S20>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/Trajektorie_Erzeugung/Subsystem'
 * '<S21>'  : 'uz_codegen/uz_codegen/Regelung/Drehzahlregelung/Trajektorie_Erzeugung/Subsystem/S-R Flip-Flop1'
 * '<S22>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/Compare To Constant'
 * '<S23>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/Compare To Constant1'
 * '<S24>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/Compare To Constant2'
 * '<S25>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/IDQCtrl'
 * '<S26>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/Ueberstromabschaltung'
 * '<S27>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/abc_zu_dq'
 * '<S28>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/calcIq'
 * '<S29>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/dq_zu_alphabeta'
 * '<S30>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/IDQCtrl/DecouplingD'
 * '<S31>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/IDQCtrl/DecouplingQ'
 * '<S32>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/IDQCtrl/PI-Ctrl Id'
 * '<S33>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/IDQCtrl/PI-Ctrl Iq'
 * '<S34>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/IDQCtrl/volategeLimitation'
 * '<S35>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/IDQCtrl/PI-Ctrl Id/Saturation Dynamic'
 * '<S36>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/IDQCtrl/PI-Ctrl Iq/Saturation Dynamic'
 * '<S37>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/abc_zu_dq/Clarke-Transformation'
 * '<S38>'  : 'uz_codegen/uz_codegen/Regelung/Stromregelung/abc_zu_dq/Park-Transformation'
 * '<S39>'  : 'uz_codegen/uz_codegen/Zustandsmaschine/state_chart'
 */

/*-
 * Requirements for '<Root>': uz_codegen0

 */
#endif                                 /* uz_codegen0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
