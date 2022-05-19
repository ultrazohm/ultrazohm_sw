/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: InterpolationMeshGrid.h
 *
 * Code generated for Simulink model 'InterpolationMeshGrid'.
 *
 * Model version                  : 2.381
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Jan 11 13:33:48 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#include "../../../uz_global_configuration.h"
#include "../../uz_ParameterID_data.h"
#if UZ_PARAMETERID_MAX_INSTANCES > 0U

#ifndef RTW_HEADER_InterpMeshGrid_h_
#define RTW_HEADER_InterpMeshGrid_h_
#include "../../rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef InterpMeshGrid_COMMON_INCLUDES_
#define InterpMeshGrid_COMMON_INCLUDES_
#include "../../rtwtypes.h"
#endif                                 /* InterpMeshGrid_COMMON_INCLUDES_ */

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

#define InterpMeshGrid_M               (rtInterpMeshGrid_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_InterpMeshGrid_t RT_MODEL_InterpMeshGrid_t;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T delta_psi[100];
  real32_T psi_array[10300];
  real32_T psi_array_m[600];
  real32_T c[400];
  real32_T rtb_FluxMapData_psid_grid[400];
  real32_T grid_old[400];
  real32_T N[300];
  real32_T range_psid_X_in[20];
  real32_T range_psid_Y_in[20];
  real32_T range_psiq_X_in[20];
  real32_T range_psiq_Y_in[20];
  real32_T range_id_X_in[20];
  real32_T range_id_Y_in[20];
  real32_T range_iq_X_in[20];
  real32_T range_iq_Y_in[20];
  real32_T range_psid_X_in_tmp[20];
  real32_T range_psid_X_in_tmp_c[20];
  real32_T AC[3];
  real32_T N_sum[3];
  real32_T grid_old_k[400];
  real32_T N_c[300];
  real32_T AC_b[3];
  real32_T N_sum_p[3];
  real32_T c_ex;
  real32_T rtb_FluxMapData_psi_temp_const;
  real32_T range_psid_X_in_c;
  real32_T range_psid_X_in_tmp_f;
  real32_T range_psid_Y_in_tmp;
  int32_T t;
  int32_T i;
  int32_T psi_array_tmp;
  int32_T i2;
  int32_T i2_g;
} DW_InterpMeshGrid_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T psi_array_in[600];          /* '<Root>/psi_array_in' */
  real32_T i_rat;                      /* '<Root>/i_rat' */
  uz_ParaID_OnlineID_output_t OnlineID_input;/* '<Root>/OnlineID_input' */
} ExtU_InterpMeshGrid_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uz_ParaID_FluxMapsData_t FluxMapData;/* '<Root>/FluxMapData' */
} ExtY_InterpMeshGrid_t;

/* Real-time Model Data Structure */
struct tag_RTM_InterpMeshGrid_t {
  ExtU_InterpMeshGrid_t *inputs;
  ExtY_InterpMeshGrid_t *outputs;
  DW_InterpMeshGrid_t *dwork;
};

/* Model entry point functions */
extern void InterpMeshGrid_initialize(RT_MODEL_InterpMeshGrid_t *const
  rtInterpMeshGrid_M);
extern void InterpMeshGrid_step(RT_MODEL_InterpMeshGrid_t *const
  rtInterpMeshGrid_M);

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
 * hilite_system('uz_ParameterID/InterpMeshGrid')    - opens subsystem uz_ParameterID/InterpMeshGrid
 * hilite_system('uz_ParameterID/InterpMeshGrid/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID'
 * '<S1>'   : 'uz_ParameterID/InterpMeshGrid'
 */

/*-
 * Requirements for '<Root>': InterpMeshGrid
 */
#endif                                 /* RTW_HEADER_InterpMeshGrid_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
