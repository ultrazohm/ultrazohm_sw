/*
 * Classroom License -- for classroom instructional use only.  Not for
 * government, commercial, academic research, or other organizational use.
 *
 * File: PI_BLAC_n_Bueh_V6.h
 *
 * Code generated for Simulink model 'PI_BLAC_n_Bueh_V6'.
 *
 * Model version                  : 1.2662
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Apr 19 16:27:44 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ASIC/FPGA->ASIC/FPGA
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PI_BLAC_n_Bueh_V6_h_
#define RTW_HEADER_PI_BLAC_n_Bueh_V6_h_
#include <math.h>
#include <string.h>
#ifndef PI_BLAC_n_Bueh_V6_COMMON_INCLUDES_
# define PI_BLAC_n_Bueh_V6_COMMON_INCLUDES_
#include "rtwtypes_PI_BLAC_n_Bueh_V6.h"
#endif                                 /* PI_BLAC_n_Bueh_V6_COMMON_INCLUDES_ */

#include "PI_BLAC_n_Bueh_V6_types.h"

/* Shared type includes */
#include "multiword_types_PI_BLAC_n_Bueh_V6.h"
//#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S2>/Integrator' */
} DW_PI_BLAC_n_Bueh_V6_T;

/* Parameters (default storage) */
struct P_PI_BLAC_n_Bueh_V6_T_ {
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T Integrator_IC;                /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T ZeroGain_Gain;                /* Expression: 0
                                        * Referenced by: '<S3>/ZeroGain'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S2>/Switch'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_PI_BLAC_n_Bueh_V6_T {
  const char_T * volatile errorStatus;
  P_PI_BLAC_n_Bueh_V6_T *defaultParam;
  DW_PI_BLAC_n_Bueh_V6_T *dwork;
};

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T Imax_AWUP;               /* Variable: Imax_AWUP
                                        * Referenced by:
                                        *   '<S2>/Saturate'
                                        *   '<S3>/DeadZone'
                                        */
extern real_T T_Rn;                    /* Variable: T_Rn
                                        * Referenced by: '<S2>/Integral Gain'
                                        */
extern real_T V_Rn;                    /* Variable: V_Rn
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */

/* Model entry point functions */
extern void PI_BLAC_n_Bueh_V6_initialize(RT_MODEL_PI_BLAC_n_Bueh_V6_T *const
  PI_BLAC_n_Bueh_V6_M, real_T *PI_BLAC_n_Bueh_V6_U_n_ref_rpm, real_T
  *PI_BLAC_n_Bueh_V6_U_n_meas_rpm, real_T *PI_BLAC_n_Bueh_V6_Y_iq_ref);
extern void PI_BLAC_n_Bueh_V6_step(RT_MODEL_PI_BLAC_n_Bueh_V6_T *const
  PI_BLAC_n_Bueh_V6_M, real_T PI_BLAC_n_Bueh_V6_U_n_ref_rpm, real_T
  PI_BLAC_n_Bueh_V6_U_n_meas_rpm, real_T *PI_BLAC_n_Bueh_V6_Y_iq_ref);
extern void PI_BLAC_n_Bueh_V6_terminate(RT_MODEL_PI_BLAC_n_Bueh_V6_T *const
  PI_BLAC_n_Bueh_V6_M);

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
 * hilite_system('FCS_BLAC_V13_Bueh_Master_i_Np1_100kHz_V6_ARM_Speed/PI_BLAC_n_Bueh_V6')    - opens subsystem FCS_BLAC_V13_Bueh_Master_i_Np1_100kHz_V6_ARM_Speed/PI_BLAC_n_Bueh_V6
 * hilite_system('FCS_BLAC_V13_Bueh_Master_i_Np1_100kHz_V6_ARM_Speed/PI_BLAC_n_Bueh_V6/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FCS_BLAC_V13_Bueh_Master_i_Np1_100kHz_V6_ARM_Speed'
 * '<S1>'   : 'FCS_BLAC_V13_Bueh_Master_i_Np1_100kHz_V6_ARM_Speed/PI_BLAC_n_Bueh_V6'
 * '<S2>'   : 'FCS_BLAC_V13_Bueh_Master_i_Np1_100kHz_V6_ARM_Speed/PI_BLAC_n_Bueh_V6/Speed_Controller'
 * '<S3>'   : 'FCS_BLAC_V13_Bueh_Master_i_Np1_100kHz_V6_ARM_Speed/PI_BLAC_n_Bueh_V6/Speed_Controller/Clamping circuit'
 */
#endif                                 /* RTW_HEADER_PI_BLAC_n_Bueh_V6_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
