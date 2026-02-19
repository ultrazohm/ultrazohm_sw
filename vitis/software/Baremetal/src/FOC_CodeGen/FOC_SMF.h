/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_SMF.h
 *
 * Code generated for Simulink model 'FOC_SMF'.
 *
 * Model version                  : 5.64
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Feb 19 10:18:36 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef FOC_SMF_h_
#define FOC_SMF_h_
#ifndef FOC_SMF_COMMON_INCLUDES_
#define FOC_SMF_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* FOC_SMF_COMMON_INCLUDES_ */

#include "FOC_SMF_types.h"
#include <string.h>
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real32_T DataSourceSwitch[3];        /* '<S1>/DataSourceSwitch' */
  real32_T MinMax;                     /* '<S4>/MinMax' */
  real32_T LIMIT_EMotor_Warn_Temp[6];  /* '<S5>/LIMIT_EMotor_Warn_Temp' */
  real32_T LIMIT_WARN_Inverter_Warn_Temp[9];
                                      /* '<S5>/LIMIT_WARN_Inverter_Warn_Temp' */
  real32_T global_reset_errors;        /* '<S1>/FOC_Statemachine' */
  boolean_T KL15_PG_SourceSwitch;      /* '<S1>/KL15_PG_SourceSwitch' */
  boolean_T Compare[9];                /* '<S6>/Compare' */
  boolean_T Compare_m[6];              /* '<S7>/Compare' */
  boolean_T Uk1;                       /* '<S8>/Delay Input1' */
  boolean_T LogicalOperator3;          /* '<S5>/Logical Operator3' */
  boolean_T Compare_m3;                /* '<S11>/Compare' */
  boolean_T FixPtRelationalOperator;   /* '<S8>/FixPt Relational Operator' */
  boolean_T Memory;                    /* '<S12>/Memory' */
  boolean_T Logic[2];                  /* '<S12>/Logic' */
  boolean_T Memory_e;                  /* '<S13>/Memory' */
  boolean_T Logic_f[2];                /* '<S13>/Logic' */
  boolean_T Memory_i;                  /* '<S14>/Memory' */
  boolean_T Logic_e[2];                /* '<S14>/Logic' */
  boolean_T Memory_ej;                 /* '<S15>/Memory' */
  boolean_T Logic_fh[2];               /* '<S15>/Logic' */
  boolean_T Memory_b;                  /* '<S16>/Memory' */
  boolean_T Logic_b[2];                /* '<S16>/Logic' */
  boolean_T Memory_m;                  /* '<S17>/Memory' */
  boolean_T Logic_o[2];                /* '<S17>/Logic' */
  boolean_T Memory_l;                  /* '<S18>/Memory' */
  boolean_T Logic_d[2];                /* '<S18>/Logic' */
  boolean_T Memory_bk;                 /* '<S19>/Memory' */
  boolean_T Logic_bw[2];               /* '<S19>/Logic' */
  boolean_T Memory_a;                  /* '<S20>/Memory' */
  boolean_T Logic_m[2];                /* '<S20>/Logic' */
  boolean_T Memory_mt;                 /* '<S21>/Memory' */
  boolean_T Logic_dm[2];               /* '<S21>/Logic' */
  boolean_T Memory_n;                  /* '<S22>/Memory' */
  boolean_T Logic_bj[2];               /* '<S22>/Logic' */
  boolean_T Memory_as;                 /* '<S23>/Memory' */
  boolean_T Logic_a[2];                /* '<S23>/Logic' */
  boolean_T MinMax_a;                  /* '<S5>/MinMax' */
  boolean_T MinMax1_o;                 /* '<S5>/MinMax1' */
  boolean_T LogicalOperator;           /* '<S5>/Logical Operator' */
} B_FOC_SMF_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  boolean_T DelayInput1_DSTATE;        /* '<S8>/Delay Input1' */
  uint8_T is_active_c1_FOC_SMF;        /* '<S1>/FOC_Statemachine' */
  uint8_T is_c1_FOC_SMF;               /* '<S1>/FOC_Statemachine' */
  uint8_T is_RUN_MODE;                 /* '<S1>/FOC_Statemachine' */
  boolean_T Memory_PreviousInput;      /* '<S12>/Memory' */
  boolean_T Memory_PreviousInput_e;    /* '<S13>/Memory' */
  boolean_T Memory_PreviousInput_k;    /* '<S14>/Memory' */
  boolean_T Memory_PreviousInput_m;    /* '<S15>/Memory' */
  boolean_T Memory_PreviousInput_f;    /* '<S16>/Memory' */
  boolean_T Memory_PreviousInput_j;    /* '<S17>/Memory' */
  boolean_T Memory_PreviousInput_i;    /* '<S18>/Memory' */
  boolean_T Memory_PreviousInput_p;    /* '<S19>/Memory' */
  boolean_T Memory_PreviousInput_n;    /* '<S20>/Memory' */
  boolean_T Memory_PreviousInput_fj;   /* '<S21>/Memory' */
  boolean_T Memory_PreviousInput_nt;   /* '<S22>/Memory' */
  boolean_T Memory_PreviousInput_a;    /* '<S23>/Memory' */
  boolean_T LIMIT_EMotor_Warn_Temp_Mode[6];/* '<S5>/LIMIT_EMotor_Warn_Temp' */
  boolean_T LIMIT_WARN_Inverter_Warn_Temp_M[9];
                                      /* '<S5>/LIMIT_WARN_Inverter_Warn_Temp' */
} DW_FOC_SMF_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  bus_BSW_SMF_t bus_BSW_SMF;           /* '<Root>/bus_BSW_SCF' */
  bus_FCF_t bus_FCF;                   /* '<Root>/bus_FCF' */
} ExtU_FOC_SMF_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  bus_SMF_t bus_SMF;                   /* '<Root>/bus_SMF' */
} ExtY_FOC_SMF_T;

/* Parameters (default storage) */
struct P_FOC_SMF_T_ {
  real_T FOC_RESET_OT_Error;           /* Variable: FOC_RESET_OT_Error
                                        * Referenced by: '<S5>/Reset_OT_Error'
                                        */
  real_T enumState_CTRL_RE_INIT;       /* Variable: enumState_CTRL_RE_INIT
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T FOC_MANUAL_State_Request;   /* Variable: FOC_MANUAL_State_Request
                                        * Referenced by: '<S1>/MANUAL_StateReq'
                                        */
  real32_T FOC_MANUAL_Torque_Request;  /* Variable: FOC_MANUAL_Torque_Request
                                        * Referenced by: '<S1>/Constant'
                                        */
  real32_T LIMIT_EMotor_Over_Temp;     /* Variable: LIMIT_EMotor_Over_Temp
                                        * Referenced by: '<S7>/Constant'
                                        */
  real32_T LIMIT_EMotor_Warn_Temp;     /* Variable: LIMIT_EMotor_Warn_Temp
                                        * Referenced by: '<S5>/LIMIT_EMotor_Warn_Temp'
                                        */
  real32_T LIMIT_Inverter_Over_Temp;   /* Variable: LIMIT_Inverter_Over_Temp
                                        * Referenced by: '<S6>/Constant'
                                        */
  real32_T LIMIT_Inverter_Warn_Temp;   /* Variable: LIMIT_Inverter_Warn_Temp
                                        * Referenced by: '<S5>/LIMIT_WARN_Inverter_Warn_Temp'
                                        */
  real32_T SPEED_CTRL_MANUAL_n_RPM;    /* Variable: SPEED_CTRL_MANUAL_n_RPM
                                        * Referenced by: '<S1>/OmegaRot2'
                                        */
  real32_T enumState_CTRL_IDLE;        /* Variable: enumState_CTRL_IDLE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_CTRL_INIT;        /* Variable: enumState_CTRL_INIT
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_ERROR_MODE;       /* Variable: enumState_ERROR_MODE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_FOC_IDLE;         /* Variable: enumState_FOC_IDLE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_FOC_OFF;          /* Variable: enumState_FOC_OFF
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_FOC_SPEED;        /* Variable: enumState_FOC_SPEED
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_FOC_STANDBY;      /* Variable: enumState_FOC_STANDBY
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_FOC_TORQUE;       /* Variable: enumState_FOC_TORQUE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_RUN_MODE;         /* Variable: enumState_RUN_MODE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_SPEED_MODE;       /* Variable: enumState_SPEED_MODE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_SYS_INIT;         /* Variable: enumState_SYS_INIT
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_TORQUE_MODE;      /* Variable: enumState_TORQUE_MODE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  boolean_T FOC_MANUAL_KL15_PG;        /* Variable: FOC_MANUAL_KL15_PG
                                        * Referenced by: '<S1>/FOC_MANUAL_KL15_PG'
                                        */
  uint8_T SELECT_DataSource;           /* Variable: SELECT_DataSource
                                        * Referenced by: '<S1>/SELECT_DataSource'
                                        */
  uint8_T SELECT_KL15_PG;              /* Variable: SELECT_KL15_PG
                                        * Referenced by: '<S1>/SELECT_KL15_PG'
                                        */
  boolean_T OverTemp_Latching_1_initial_con;
                              /* Mask Parameter: OverTemp_Latching_1_initial_con
                               * Referenced by: '<S12>/Memory'
                               */
  boolean_T OverTemp_Latching_2_initial_con;
                              /* Mask Parameter: OverTemp_Latching_2_initial_con
                               * Referenced by: '<S13>/Memory'
                               */
  boolean_T OverTemp_Latching_3_initial_con;
                              /* Mask Parameter: OverTemp_Latching_3_initial_con
                               * Referenced by: '<S14>/Memory'
                               */
  boolean_T OverTemp_Latching_4_initial_con;
                              /* Mask Parameter: OverTemp_Latching_4_initial_con
                               * Referenced by: '<S15>/Memory'
                               */
  boolean_T OverTemp_Latching_5_initial_con;
                              /* Mask Parameter: OverTemp_Latching_5_initial_con
                               * Referenced by: '<S16>/Memory'
                               */
  boolean_T OverTemp_Latching_6_initial_con;
                              /* Mask Parameter: OverTemp_Latching_6_initial_con
                               * Referenced by: '<S17>/Memory'
                               */
  boolean_T OverTemp_Latching_1_initial_c_c;
                              /* Mask Parameter: OverTemp_Latching_1_initial_c_c
                               * Referenced by: '<S18>/Memory'
                               */
  boolean_T OverTemp_Latching_2_initial_c_i;
                              /* Mask Parameter: OverTemp_Latching_2_initial_c_i
                               * Referenced by: '<S19>/Memory'
                               */
  boolean_T OverTemp_Latching_3_initial_c_j;
                              /* Mask Parameter: OverTemp_Latching_3_initial_c_j
                               * Referenced by: '<S20>/Memory'
                               */
  boolean_T OverTemp_Latching_4_initial_c_e;
                              /* Mask Parameter: OverTemp_Latching_4_initial_c_e
                               * Referenced by: '<S21>/Memory'
                               */
  boolean_T OverTemp_Latching_5_initial_c_l;
                              /* Mask Parameter: OverTemp_Latching_5_initial_c_l
                               * Referenced by: '<S22>/Memory'
                               */
  boolean_T OverTemp_Latching_6_initial_c_g;
                              /* Mask Parameter: OverTemp_Latching_6_initial_c_g
                               * Referenced by: '<S23>/Memory'
                               */
  boolean_T DetectRisePositive_vinit;/* Mask Parameter: DetectRisePositive_vinit
                                      * Referenced by: '<S8>/Delay Input1'
                                      */
  real32_T LIMIT_EMotor_Warn_Temp_OffVal;
                            /* Computed Parameter: LIMIT_EMotor_Warn_Temp_OffVal
                             * Referenced by: '<S5>/LIMIT_EMotor_Warn_Temp'
                             */
  real32_T LIMIT_EMotor_Warn_Temp_YOn;
                               /* Computed Parameter: LIMIT_EMotor_Warn_Temp_YOn
                                * Referenced by: '<S5>/LIMIT_EMotor_Warn_Temp'
                                */
  real32_T LIMIT_EMotor_Warn_Temp_YOff;
                              /* Computed Parameter: LIMIT_EMotor_Warn_Temp_YOff
                               * Referenced by: '<S5>/LIMIT_EMotor_Warn_Temp'
                               */
  real32_T LIMIT_WARN_Inverter_Warn_Temp_O;
                          /* Computed Parameter: LIMIT_WARN_Inverter_Warn_Temp_O
                           * Referenced by: '<S5>/LIMIT_WARN_Inverter_Warn_Temp'
                           */
  real32_T LIMIT_WARN_Inverter_Warn_Temp_Y;
                          /* Computed Parameter: LIMIT_WARN_Inverter_Warn_Temp_Y
                           * Referenced by: '<S5>/LIMIT_WARN_Inverter_Warn_Temp'
                           */
  real32_T LIMIT_WARN_Inverter_Warn_Temp_p;
                          /* Computed Parameter: LIMIT_WARN_Inverter_Warn_Temp_p
                           * Referenced by: '<S5>/LIMIT_WARN_Inverter_Warn_Temp'
                           */
  boolean_T Constant_Value;            /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S11>/Constant'
                                        */
  boolean_T Logic_table[16];           /* Computed Parameter: Logic_table
                                        * Referenced by: '<S12>/Logic'
                                        */
  boolean_T Logic_table_l[16];         /* Computed Parameter: Logic_table_l
                                        * Referenced by: '<S13>/Logic'
                                        */
  boolean_T Logic_table_i[16];         /* Computed Parameter: Logic_table_i
                                        * Referenced by: '<S14>/Logic'
                                        */
  boolean_T Logic_table_k[16];         /* Computed Parameter: Logic_table_k
                                        * Referenced by: '<S15>/Logic'
                                        */
  boolean_T Logic_table_km[16];        /* Computed Parameter: Logic_table_km
                                        * Referenced by: '<S16>/Logic'
                                        */
  boolean_T Logic_table_h[16];         /* Computed Parameter: Logic_table_h
                                        * Referenced by: '<S17>/Logic'
                                        */
  boolean_T Logic_table_g[16];         /* Computed Parameter: Logic_table_g
                                        * Referenced by: '<S18>/Logic'
                                        */
  boolean_T Logic_table_gb[16];        /* Computed Parameter: Logic_table_gb
                                        * Referenced by: '<S19>/Logic'
                                        */
  boolean_T Logic_table_e[16];         /* Computed Parameter: Logic_table_e
                                        * Referenced by: '<S20>/Logic'
                                        */
  boolean_T Logic_table_lq[16];        /* Computed Parameter: Logic_table_lq
                                        * Referenced by: '<S21>/Logic'
                                        */
  boolean_T Logic_table_m[16];         /* Computed Parameter: Logic_table_m
                                        * Referenced by: '<S22>/Logic'
                                        */
  boolean_T Logic_table_g5[16];        /* Computed Parameter: Logic_table_g5
                                        * Referenced by: '<S23>/Logic'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_FOC_SMF_T {
  const char_T * volatile errorStatus;
  B_FOC_SMF_T *blockIO;
  ExtU_FOC_SMF_T *inputs;
  ExtY_FOC_SMF_T *outputs;
  DW_FOC_SMF_T *dwork;
};

/* Block parameters (default storage) */
extern P_FOC_SMF_T FOC_SMF_P;

/* External data declarations for dependent source files */
extern const bus_SMF_t FOC_SMF_rtZbus_SMF_t;/* bus_SMF_t ground */

/* Model entry point functions */
extern void FOC_SMF_initialize(RT_MODEL_FOC_SMF_T *const FOC_SMF_M);
extern void FOC_SMF_step(RT_MODEL_FOC_SMF_T *const FOC_SMF_M);
extern void FOC_SMF_terminate(RT_MODEL_FOC_SMF_T *const FOC_SMF_M);

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
 * hilite_system('MotorControl_HeadModel/Statemachine/FOC_SMF')    - opens subsystem MotorControl_HeadModel/Statemachine/FOC_SMF
 * hilite_system('MotorControl_HeadModel/Statemachine/FOC_SMF/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MotorControl_HeadModel/Statemachine'
 * '<S1>'   : 'MotorControl_HeadModel/Statemachine/FOC_SMF'
 * '<S2>'   : 'MotorControl_HeadModel/Statemachine/FOC_SMF/FOC_Statemachine'
 * '<S3>'   : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum'
 * '<S4>'   : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/GetInvMotTemp_Maximum'
 * '<S5>'   : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection'
 * '<S6>'   : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/Compare To Constant2'
 * '<S7>'   : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/Compare To Constant4'
 * '<S8>'   : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/Detect Rise Positive'
 * '<S9>'   : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/EMotor_OverTemp_Latching'
 * '<S10>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/Inverter_OverTemp_Latching'
 * '<S11>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/Detect Rise Positive/Positive'
 * '<S12>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/EMotor_OverTemp_Latching/OverTemp_Latching_1'
 * '<S13>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/EMotor_OverTemp_Latching/OverTemp_Latching_2'
 * '<S14>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/EMotor_OverTemp_Latching/OverTemp_Latching_3'
 * '<S15>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/EMotor_OverTemp_Latching/OverTemp_Latching_4'
 * '<S16>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/EMotor_OverTemp_Latching/OverTemp_Latching_5'
 * '<S17>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/EMotor_OverTemp_Latching/OverTemp_Latching_6'
 * '<S18>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/Inverter_OverTemp_Latching/OverTemp_Latching_1'
 * '<S19>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/Inverter_OverTemp_Latching/OverTemp_Latching_2'
 * '<S20>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/Inverter_OverTemp_Latching/OverTemp_Latching_3'
 * '<S21>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/Inverter_OverTemp_Latching/OverTemp_Latching_4'
 * '<S22>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/Inverter_OverTemp_Latching/OverTemp_Latching_5'
 * '<S23>'  : 'MotorControl_HeadModel/Statemachine/FOC_SMF/GetInvMotTemp_Maximum/Temperature_Sensor_Error_Detection/Inverter_OverTemp_Latching/OverTemp_Latching_6'
 */
#endif                                 /* FOC_SMF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
