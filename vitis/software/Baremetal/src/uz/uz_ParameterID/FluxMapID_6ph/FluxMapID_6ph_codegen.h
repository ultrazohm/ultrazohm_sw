/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FluxMapID_6ph_codegen.h
 *
 * Code generated for Simulink model 'FluxMapID_6ph_codegen'.
 *
 * Model version                  : 3.94
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Mon May  1 14:29:48 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "../uz_ParameterID_data.h"

#ifndef RTW_HEADER_FluxMapID_6ph_codegen_h_
#define RTW_HEADER_FluxMapID_6ph_codegen_h_
#include "../rtwtypes.h"
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef FluxMapID_6ph_codegen_COMMON_INCLUDES_
#define FluxMapID_6ph_codegen_COMMON_INCLUDES
#include "../rtwtypes.h"
#endif                      /* FluxMapID_6ph_codegen_COMMON_INCLUDES_ */
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

#define FluxMapID_6ph_codegen_M        (rtFluxMapID_6ph_codegen_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_FluxMapID_6ph_codegen_t RT_MODEL_FluxMapID_6ph_codege_t;

/* Block signals and states (default storage) for system '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
typedef struct {
  real32_T u_d_array[1000];       /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  real32_T u_q_array[1000];       /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  real32_T omega_el_array[1000];  /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  real32_T i_d_array[1000];       /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  real32_T i_q_array[1000];       /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  real32_T PI_d_loc;              /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  real32_T PI_q_loc;              /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  real32_T PI_d_loc_h;            /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  real32_T PI_q_loc_b;            /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uint32_T exitPortIndex;         /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uint32_T NumberOfIDpoints;      /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uint32_T NumberOfPoints;        /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uint32_T counter_time;          /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uint32_T AMMn;                  /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uint32_T AMMj;                  /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uint32_T i;                     /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uint8_T is_c14_Subchart_FluxMapID_refer;
                                  /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
} DW_AMMstateIdentificationDQFl_t;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_AMMstateIdentificationDQFl_t sf_AMMstateIdentificationZeroFl;
                                /* '<S1>/AMMstate.IdentificationZero.Fluxmap' */
  DW_AMMstateIdentificationDQFl_t sf_AMMstateIdentificationXYFlux;
                                  /* '<S1>/AMMstate.IdentificationXY.Fluxmap' */
  DW_AMMstateIdentificationDQFl_t sf_AMMstateIdentificationDQFlux;
                                  /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uz_3ph_dq_t actual_voltages;         /* '<Root>/FluxMapID_6ph_codegen' */
  uz_3ph_dq_t actual_currents;         /* '<Root>/FluxMapID_6ph_codegen' */
  uz_3ph_dq_t actual_voltages_h;       /* '<Root>/FluxMapID_6ph_codegen' */
  uz_3ph_dq_t actual_currents_h;       /* '<Root>/FluxMapID_6ph_codegen' */
  uz_3ph_dq_t actual_voltages_n;       /* '<Root>/FluxMapID_6ph_codegen' */
  uz_3ph_dq_t actual_currents_m;       /* '<Root>/FluxMapID_6ph_codegen' */
  uz_3ph_dq_t mean_voltages;    /* '<S1>/AMMstate.IdentificationZero.Fluxmap' */
  uz_3ph_dq_t mean_currents;    /* '<S1>/AMMstate.IdentificationZero.Fluxmap' */
  uz_3ph_dq_t mean_voltages_a;    /* '<S1>/AMMstate.IdentificationXY.Fluxmap' */
  uz_3ph_dq_t mean_currents_i;    /* '<S1>/AMMstate.IdentificationXY.Fluxmap' */
  uz_3ph_dq_t mean_voltages_o;    /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uz_3ph_dq_t mean_currents_g;    /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uz_ParaID_FluxMapID_output_t FluxMapID_output;/* '<Root>/FluxMapID_6ph_codegen' */
  uz_3ph_dq_t mean_currents_m;         /* '<Root>/FluxMapID_6ph_codegen' */
  uz_3ph_dq_t mean_voltages_c;         /* '<Root>/FluxMapID_6ph_codegen' */
  real32_T R_s_array[50];              /* '<Root>/FluxMapID_6ph_codegen' */
  real32_T omega_el;                   /* '<Root>/FluxMapID_6ph_codegen' */
  real32_T omega_el_f;                 /* '<Root>/FluxMapID_6ph_codegen' */
  real32_T omega_el_b;                 /* '<Root>/FluxMapID_6ph_codegen' */
  real32_T PI_d_ref;            /* '<S1>/AMMstate.IdentificationZero.Fluxmap' */
  real32_T PI_q_ref;            /* '<S1>/AMMstate.IdentificationZero.Fluxmap' */
  real32_T mean_omega_el;       /* '<S1>/AMMstate.IdentificationZero.Fluxmap' */
  real32_T PI_d_ref_i;            /* '<S1>/AMMstate.IdentificationXY.Fluxmap' */
  real32_T PI_q_ref_p;            /* '<S1>/AMMstate.IdentificationXY.Fluxmap' */
  real32_T mean_omega_el_g;       /* '<S1>/AMMstate.IdentificationXY.Fluxmap' */
  real32_T PI_d_ref_f;            /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  real32_T PI_q_ref_a;            /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  real32_T mean_omega_el_a;       /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  real32_T i_d_ref_AMM;                /* '<Root>/FluxMapID_6ph_codegen' */
  real32_T i_q_ref_AMM;                /* '<Root>/FluxMapID_6ph_codegen' */
  real32_T mean_omega_el_k;            /* '<Root>/FluxMapID_6ph_codegen' */
  uint32_T three_sec_transition_counter;/* '<Root>/FluxMapID_6ph_codegen' */
  uint32_T three_sec_transition_counter_o;/* '<Root>/FluxMapID_6ph_codegen' */
  uint32_T three_sec_transition_counter_b;/* '<Root>/FluxMapID_6ph_codegen' */
  uint32_T repetitionCounter;   /* '<S1>/AMMstate.IdentificationZero.Fluxmap' */
  uint32_T repetitionCounter_i;   /* '<S1>/AMMstate.IdentificationXY.Fluxmap' */
  uint32_T repetitionCounter_p;   /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uint32_T exitPortIndex;              /* '<Root>/FluxMapID_6ph_codegen' */
  uint32_T exitPortIndex_i;            /* '<Root>/FluxMapID_6ph_codegen' */
  uint32_T exitPortIndex_o;            /* '<Root>/FluxMapID_6ph_codegen' */
  uint32_T repetition_counter;         /* '<Root>/FluxMapID_6ph_codegen' */
  uint32_T three_sec_transition_counter_c;/* '<Root>/FluxMapID_6ph_codegen' */
  uint16_T activeState;         /* '<S1>/AMMstate.IdentificationZero.Fluxmap' */
  uint16_T activeState_m;         /* '<S1>/AMMstate.IdentificationXY.Fluxmap' */
  uint16_T activeState_l;         /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  uint8_T is_active_c16_FluxMapID_6ph_cod;/* '<Root>/FluxMapID_6ph_codegen' */
  uint8_T is_c16_FluxMapID_6ph_codegen;/* '<Root>/FluxMapID_6ph_codegen' */
  uint8_T is_AMMstate;                 /* '<Root>/FluxMapID_6ph_codegen' */
  uint8_T is_IdentificationDQ;         /* '<Root>/FluxMapID_6ph_codegen' */
  uint8_T is_IdentificationXY;         /* '<Root>/FluxMapID_6ph_codegen' */
  uint8_T is_IdentificationZero;       /* '<Root>/FluxMapID_6ph_codegen' */
  boolean_T finished_calculation;
                                /* '<S1>/AMMstate.IdentificationZero.Fluxmap' */
  boolean_T finished_calculation_c;
                                  /* '<S1>/AMMstate.IdentificationXY.Fluxmap' */
  boolean_T finished_calculation_l;
                                  /* '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  boolean_T finished_calculation_b;    /* '<Root>/FluxMapID_6ph_codegen' */
} DW_FluxMapID_6ph_codegen_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uz_ParaID_FluxMapIDConfig_t FluxMapIDConfig;/* '<Root>/FluxMapIDConfig' */
  uz_ParaID_ActualValues_t ActualValues;/* '<Root>/ActualValues' */
  uz_ParaID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig' */
  uz_ParaID_ControlFlags_t ControlFlags;/* '<Root>/ControlFlags' */
  boolean_T feedback_printed;          /* '<Root>/feedback_printed' */
} ExtU_FluxMapID_6ph_codegen_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T finishedFluxMapID;         /* '<Root>/finishedFluxMapID' */
  boolean_T enteredFluxMapID;          /* '<Root>/enteredFluxMapID' */
  uz_ParaID_Controller_Parameters_output_t FluxMapID_FOC_output;/* '<Root>/FluxMapID_FOC_output' */
  uz_ParaID_FluxMapID_output_t FluxMapID_output;/* '<Root>/FluxMapID_output' */
  uz_ParaID_FluxMapID_extended_controller_output_t extended_controller_output;/* '<Root>/extended_controller_output' */
} ExtY_FluxMapID_6ph_codegen_t;

/* Real-time Model Data Structure */
struct tag_RTM_FluxMapID_6ph_codegen_t {
  ExtU_FluxMapID_6ph_codegen_t *inputs;
  ExtY_FluxMapID_6ph_codegen_t *outputs;
  DW_FluxMapID_6ph_codegen_t *dwork;
};

/* Model entry point functions */
extern void FluxMapID_6ph_codegen_initialize(RT_MODEL_FluxMapID_6ph_codege_t *
  const rtFluxMapID_6ph_codegen_M);
extern void FluxMapID_6ph_codegen_step(RT_MODEL_FluxMapID_6ph_codege_t *const
  rtFluxMapID_6ph_codegen_M);

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
 * hilite_system('uz_ParameterID_6ph/Subsystem Reference1/FluxMapID_6ph_codegen')    - opens subsystem uz_ParameterID_6ph/Subsystem Reference1/FluxMapID_6ph_codegen
 * hilite_system('uz_ParameterID_6ph/Subsystem Reference1/FluxMapID_6ph_codegen/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID_6ph/Subsystem Reference1'
 * '<S1>'   : 'uz_ParameterID_6ph/Subsystem Reference1/FluxMapID_6ph_codegen'
 * '<S2>'   : 'uz_ParameterID_6ph/Subsystem Reference1/FluxMapID_6ph_codegen/AMMstate.IdentificationDQ.Fluxmap'
 * '<S3>'   : 'uz_ParameterID_6ph/Subsystem Reference1/FluxMapID_6ph_codegen/AMMstate.IdentificationXY.Fluxmap'
 * '<S4>'   : 'uz_ParameterID_6ph/Subsystem Reference1/FluxMapID_6ph_codegen/AMMstate.IdentificationZero.Fluxmap'
 */

/*-
 * Requirements for '<Root>': FluxMapID_6ph_codegen
 */
#endif                                 /* RTW_HEADER_FluxMapID_6ph_codegen_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
