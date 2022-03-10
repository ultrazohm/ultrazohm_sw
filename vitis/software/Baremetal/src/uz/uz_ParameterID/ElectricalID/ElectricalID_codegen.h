/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID.h
 *
 * Code generated for Simulink model 'ElectricalID'.
 *
 * Model version                  : 2.60
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Thu Nov 25 15:30:38 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U
#include "../../uz_Transformation/uz_Transformation.h"
#include "../../uz_PMSM_config/uz_PMSM_config.h"

#ifndef RTW_HEADER_ElectricalID_h_
#define RTW_HEADER_ElectricalID_h_
#include "../rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef ElectricalID_COMMON_INCLUDES_
#define ElectricalID_COMMON_INCLUDES_
#include "../rtwtypes.h"
#endif                                 /* ElectricalID_COMMON_INCLUDES_ */

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

#define ElectricalID_M                 (rtElectricalID_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_ElectricalID_t RT_MODEL_ElectricalID_t;

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_ElectricalIDConfig_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_ElectricalIDConfig_t_

/**
 * @brief configuration struct for ElectricalID specific settings
 * 
 */
typedef struct {
  real32_T goertzlFreq; /**< frequency of sine wave for vibration to identify J */
  real32_T dutyCyc; /**< manual input for DutyCycle during identification of thetaOffset, Ld and Lq. If the value is left at 0.0f, the DutyCycle will be identified automatically. */
  real32_T n_ref_measurement; /**< reference speed for identification of Psi_PM */
  boolean_T identLq; /**< flag to enable identification of Lq. If false, Lq=Ld */
  real32_T goertzlAmp; /**< amplitude of sine wave for vibration to identify J */
  real32_T min_n_ratio; /**< minimal ratio of rated speed for automatic DutyCycle identification. i.e. 0.025f @3000rpm rated speed -> 75rpm. If this value is reached, the algorithm assumes the DutyCycle is strong enough to properly turn the rotor. */
} uz_PID_ElectricalIDConfig_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_ActualValues_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_ActualValues_t_

/**
 * @brief struct for the measured values which are needed for the ParameterID
 * 
 */
typedef struct {
  uz_3ph_abc_t V_abc; /**< measured three-phase voltages */ 
  uz_3ph_abc_t I_abc; /**< measured three-phase currents */ 
  uz_3ph_dq_t i_dq; /**< measured dq voltages */ 
  uz_3ph_dq_t v_dq; /**< measured dq currents */ 
  real32_T omega_m; /**< measured mechanical omega */ 
  real32_T omega_el; /**< measured electrical omega */ 
  real32_T theta_m; /**< measured mechanical theta */ 
  real32_T theta_el; /**< measured electrical theta */ 
  real32_T V_DC; /**< measured DC-link voltage */ 
} uz_PID_ActualValues_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_GlobalConfig_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_GlobalConfig_t_

/**
 * @brief Global configuration struct for general settings of the ParameterID 
 * 
 */
typedef struct {
  uz_PMSM_t PMSM_config; /**< motor related parameters. Is needed, if ElectricalID should not be executed */ 
  boolean_T enableParameterID; /**< flag to enable the entire ParameterID */ 
  boolean_T Reset; /**< flag to Reset the entire ParameterID*/ 
  real32_T Kp_id; /**< value for Kp_id, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */ 
  real32_T Kp_iq; /**< value for Kp_iq, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */ 
  real32_T Kp_n; /**< value for Kp_n, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */ 
  real32_T Ki_id; /**< value for Ki_id, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */ 
  real32_T Ki_iq; /**< value for Ki_iq, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */ 
  real32_T Ki_n; /**< value for Ki_n, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */ 
  boolean_T ElectricalID; /**< flag to enable ElectricalID */
  boolean_T FrictionID; /**< flag to enable FrictionID */
  boolean_T TwoMassID; /**< flag to enable TwoMassID */
  boolean_T FluxMapID; /**< flag to enable FluxMapID */
  boolean_T OnlineID; /**< flag to enable OnlineID */
  boolean_T ACCEPT; /**< flag for the ACCEPT button  */
  real32_T sampleTimeISR; /**< sampleTime of the ISR. i.e. sampleTime of the function call uz_ParameterID_step. Very important parameter */
  real32_T ratCurrent; /**< rated current of the motor */
  real32_T ratSpeed; /**< rated speed of the motor */
  uz_3ph_dq_t i_dq_ref; /**< Not needed for ID-states. Can be used to transmit reference currents to a control algorithm. */
  real32_T n_ref; /**< Not needed for ID-states. Can be used to transmit reference speed to a control algorithm. */
} uz_PID_GlobalConfig_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_ControlFlags_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_ControlFlags_t_

/**
 * @brief struct which contains the enable state flags
 * 
 */
typedef struct {
  boolean_T startFrictionID; /**< flag to start FrictionID */
  boolean_T startElectricalID; /**< flag to start ElectricalID */
  boolean_T startTwoMassID; /**< flag to start TwoMassID */
  boolean_T startFluxMapID; /**< flag to start FluxMapID */
  uint16_T transNr; /**< transistion number. 1 transistion number corresponds to one ID-state */
  boolean_T enableOnlineID; /**< flag to start OnlineID */
  boolean_T finished_all_Offline_states; /**< flag to signal, that all OfflineID-state are finished and OnlineID-state can be started*/
} uz_PID_ControlFlags_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_Controller_Parameters_output_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_Controller_Parameters_output_t_

/**
 * @brief struct with config values for a control algorithm
 * 
 */
typedef struct {
  uz_3ph_dq_t i_dq_ref; /**< reference currents for current controller */
  uint16_T activeState; /**< activeState of the ID-states */
  real32_T n_ref_FOC; /**< reference speed for the speed controller */
  boolean_T enableFOC_speed; /**<flag to enable speed controller */
  boolean_T enableFOC_current; /**<flag to enable current controller */
  boolean_T resetIntegrator; /**<flag to reset the integrators used in the control algorithm */
  real32_T PRBS_out; /**<excitation for TwoMassID */ 
  real32_T Kp_id_out; /**<Kp_id for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Kp_iq_out; /**<Kp_iq for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Kp_n_out; /**<Kp_n for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Ki_id_out; /**<Ki_id for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Ki_iq_out; /**<Ki_iq for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Ki_n_out; /**<Ki_n for FOC control. Can be ignored, if another control algorithm is used */
} uz_PID_Controller_Parameters_output_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_ElectricalID_output_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_ElectricalID_output_t_

/**
 * @brief output struct of ElectricalID
 * 
 */
typedef struct {
  real32_T PWM_Switch_0; /**< DutyCycle for PWM Switch 0 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T PWM_Switch_2; /**< DutyCycle for PWM Switch 2 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T PWM_Switch_4; /**< DutyCycle for PWM Switch 4 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  boolean_T enable_TriState[3]; /**< array to signal which halfbridge of the inverter should be in tristate mode. true signals, that the halfbridge should be in tristate mode. (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T thetaOffset; /**< determined offset of theta in rad */
  uz_PMSM_t PMSM_parameters; /**< identified motor parameters */
} uz_PID_ElectricalID_output_t;

#endif

/* Block signals and states (default storage) for system '<Root>' */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T sineCounter;                  /* '<Root>/ElectricalID' */
  real_T d_m;
  real32_T H[4];                       /* '<Root>/ElectricalID' */
  real32_T omega_register[5];          /* '<Root>/ElectricalID' */
  real32_T d[2048];                    /* '<Root>/ElectricalID' */
  real32_T i_est[2048];                /* '<Root>/ElectricalID' */
  real32_T J[4096];                    /* '<Root>/ElectricalID' */
  real32_T Vstep[205];                 /* '<Root>/ElectricalID' */
  real32_T measArray1[1024];           /* '<Root>/ElectricalID' */
  real32_T fv[2048];
  real32_T fv1[2048];
  real32_T fv2[4];
  real32_T fv3[2];
  real32_T fv4[4];
  real32_T fv5[2];
  real32_T e;                          /* '<Root>/ElectricalID' */
  real32_T lambda;                     /* '<Root>/ElectricalID' */
  real32_T V0;                         /* '<Root>/ElectricalID' */
  real32_T R_corr;                     /* '<Root>/ElectricalID' */
  real32_T bandwidthCurrentControl;    /* '<Root>/ElectricalID' */
  real32_T dampingFactor;              /* '<Root>/ElectricalID' */
  real32_T psiOverJ;                   /* '<Root>/ElectricalID' */
  real32_T Kp_iq_loc;                  /* '<Root>/ElectricalID' */
  real32_T omega_sum;                  /* '<Root>/ElectricalID' */
  real32_T ia_sum;                     /* '<Root>/ElectricalID' */
  real32_T DutyCycle;                  /* '<Root>/ElectricalID' */
  int32_T i;
  uint32_T counter;                    /* '<Root>/ElectricalID' */
  uint32_T wait_count;                 /* '<Root>/ElectricalID' */
  uint32_T one_sec_transition_counter; /* '<Root>/ElectricalID' */
  uint16_T n_iters;                    /* '<Root>/ElectricalID' */
  uint16_T z;                          /* '<Root>/ElectricalID' */
  uint8_T is_active_c3_ElectricalID;   /* '<Root>/ElectricalID' */
  uint8_T is_c3_ElectricalID;          /* '<Root>/ElectricalID' */
  uint8_T is_ElectricalID;             /* '<Root>/ElectricalID' */
  boolean_T updateJ;                   /* '<Root>/ElectricalID' */
  boolean_T om_con;                    /* '<Root>/ElectricalID' */
  boolean_T ia_valid;                  /* '<Root>/ElectricalID' */
  boolean_T DC_manual;                 /* '<Root>/ElectricalID' */
} DW_ElectricalID_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uz_PID_ElectricalIDConfig_t ElectricalIDConfig;/* '<Root>/ElectricalIDConfig' */
  uz_PID_ActualValues_t ActualValues;  /* '<Root>/ActualValues' */
  uz_PID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig' */
  uz_PID_ControlFlags_t ControlFlags;  /* '<Root>/ControlFlags' */
} ExtU_ElectricalID_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T enteredElectricalID;       /* '<Root>/enteredElectricalID' */
  boolean_T finishedElectricalID;      /* '<Root>/finishedElectricalID' */
  uz_PID_Controller_Parameters_output_t ElectricalID_FOC_output;/* '<Root>/ElectricalID_FOC_output' */
  uz_PID_ElectricalID_output_t ElectricalID_output;/* '<Root>/ElectricalID_output' */
} ExtY_ElectricalID_t;

/* Real-time Model Data Structure */
struct tag_RTM_ElectricalID_t {
  ExtU_ElectricalID_t *inputs;
  ExtY_ElectricalID_t *outputs;
  DW_ElectricalID_t *dwork;
};

/* Model entry point functions */
extern void ElectricalID_initialize(RT_MODEL_ElectricalID_t *const
  rtElectricalID_M);
extern void ElectricalID_step(RT_MODEL_ElectricalID_t *const rtElectricalID_M);

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
 * hilite_system('uz_ParameterID/ElectricalID')    - opens subsystem uz_ParameterID/ElectricalID
 * hilite_system('uz_ParameterID/ElectricalID/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID'
 * '<S1>'   : 'uz_ParameterID/ElectricalID'
 */

/*-
 * Requirements for '<Root>': ElectricalID
 */
#endif                                 /* RTW_HEADER_ElectricalID_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
