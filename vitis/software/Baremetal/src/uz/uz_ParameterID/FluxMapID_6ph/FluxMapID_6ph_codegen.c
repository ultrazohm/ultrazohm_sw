/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FluxMapID_6ph_codegen.c
 *
 * Code generated for Simulink model 'FluxMapID_6ph_codegen'.
 *
 * Model version                  : 3.104
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Fri May  5 10:57:27 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "FluxMapID_6ph_codegen.h"
#include "../mean_GqoxPyM9.h"
#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U

/* Named constants for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
#define IN_AMMcollectData              ((uint8_T)1U)
#define IN_AMMcooling                  ((uint8_T)2U)
#define IN_AMMheating                  ((uint8_T)3U)
#define IN_AMMnewRef                   ((uint8_T)4U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_initAMM                     ((uint8_T)5U)
#define IN_outputData                  ((uint8_T)6U)
#define IN_waitIdentR                  ((uint8_T)7U)

/* Named constants for Chart: '<Root>/FluxMapID_6ph_codegen' */
#define IN_AMMstate                    ((uint8_T)1U)
#define IN_Fluxmap                     ((uint8_T)1U)
#define IN_IdentificationDQ            ((uint8_T)1U)
#define IN_IdentificationXY            ((uint8_T)2U)
#define IN_IdentificationZero          ((uint8_T)3U)
#define IN_NO_ACTIVE_CHILD_a           ((uint8_T)0U)
#define IN_Wait_select_subsystem       ((uint8_T)4U)
#define IN_Waiting                     ((uint8_T)2U)
#define IN_waitState                   ((uint8_T)2U)
#define TEMP_COEFFICIENT               (0.00393F)

/* Exported functions */
extern uint32_T Fluxmap_getExitPortIndex(DW_AMMstateIdentificationDQFl_t
  *localDW);
extern void Fluxmap_during(uint16_T *activeState, real32_T *PI_d_ref, real32_T
  *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig, uint32_T
  three_sec_transition_counter, uz_ParaID_FluxMapID_output_t *FluxMapID_output,
  const uz_3ph_dq_t *actual_voltages, real32_T omega_el, uz_3ph_dq_t
  *mean_voltages, real32_T *mean_omega_el, uz_3ph_dq_t *mean_currents, uint32_T *
  repetitionCounter, const uz_3ph_dq_t *actual_currents, boolean_T
  *finished_calculation, DW_AMMstateIdentificationDQFl_t *localDW);
extern void Fluxmap_enter(uint16_T *activeState, real32_T *PI_d_ref, real32_T
  *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig,
  DW_AMMstateIdentificationDQFl_t *localDW);
extern void Fluxmap_exit(real32_T *PI_d_ref, real32_T *PI_q_ref,
  uz_ParaID_FluxMapID_output_t *FluxMapID_output, boolean_T
  *finished_calculation, DW_AMMstateIdentificationDQFl_t *localDW);
extern void Fluxmap_init(DW_AMMstateIdentificationDQFl_t *localDW);

/* Forward declaration for local functions */
static void AMMcollectData(uint16_T *activeState, uz_ParaID_FluxMapID_output_t
  *FluxMapID_output, const uz_3ph_dq_t *actual_voltages, real32_T omega_el,
  uz_3ph_dq_t *mean_voltages, real32_T *mean_omega_el, uz_3ph_dq_t
  *mean_currents, const uint32_T *repetitionCounter, const uz_3ph_dq_t
  *actual_currents, boolean_T *finished_calculation,
  DW_AMMstateIdentificationDQFl_t *localDW);
static void enter_atomic_AMMnewRef(uint16_T *activeState, real32_T *PI_d_ref,
  real32_T *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig,
  DW_AMMstateIdentificationDQFl_t *localDW);

/* Forward declaration for local functions */
static void reset_FOC_out(ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y);
static void reset_logging_out(DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW);
static void init(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
                 ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
                 DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW);
static void RefreshDataRegister(DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW);
static real32_T identRes(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW);
static void exit_atomic_Wait_select_subsyst(ExtU_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_U, ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y);
static void Wait_select_subsystem(ExtU_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_U, ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y, DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW);
static real32_T flux(real32_T u, real32_T i, real32_T omega_el, real32_T Rs);
static void AMMstate(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
                     ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
                     DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW);

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
uint32_T Fluxmap_getExitPortIndex(DW_AMMstateIdentificationDQFl_t *localDW)
{
  uint32_T b;
  b = localDW->exitPortIndex;
  localDW->exitPortIndex = 0U;
  return b;
}

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
static void AMMcollectData(uint16_T *activeState, uz_ParaID_FluxMapID_output_t
  *FluxMapID_output, const uz_3ph_dq_t *actual_voltages, real32_T omega_el,
  uz_3ph_dq_t *mean_voltages, real32_T *mean_omega_el, uz_3ph_dq_t
  *mean_currents, const uint32_T *repetitionCounter, const uz_3ph_dq_t
  *actual_currents, boolean_T *finished_calculation,
  DW_AMMstateIdentificationDQFl_t *localDW)
{
  int32_T k;

  /* During 'AMMcollectData': '<S2>:99' */
  /* '<S2>:174:1' sf_internal_predicateOutput = FluxMapID_output.array_index == repetitionCounter; */
  if (FluxMapID_output->array_index == *repetitionCounter) {
    /* Transition: '<S2>:174' */
    /* Exit 'AMMcollectData': '<S2>:99' */
    /* '<S2>:99:45' FluxMapID_output.external_Measurement_Flag=boolean(0); */
    FluxMapID_output->external_Measurement_Flag = false;

    /* '<S2>:99:46' finished_calculation = false; */
    *finished_calculation = false;
    localDW->is_c14_Subchart_FluxMapID_refer = IN_outputData;

    /* Entry 'outputData': '<S2>:170' */
    /* '<S2>:170:3' activeState = uint16(404); */
    *activeState = 404U;

    /* '<S2>:170:4' counter_time = uint32(1); */
    localDW->counter_time = 1U;

    /* '<S2>:99:14' if(i>=array_size+1) */
  } else if (localDW->i >= 1001U) {
    /* '<S2>:99:15' switch i */
    switch (localDW->i) {
     case 1001U:
      {
        real32_T x;
        uint32_T qY;

        /* '<S2>:99:16' case array_size+1 */
        /* '<S2>:99:17' mean_voltages.d = mean(u_d_array); */
        x = localDW->u_d_array[0];
        for (k = 0; k < 999; k++) {
          x += localDW->u_d_array[k + 1];
        }

        mean_voltages->d = x / 1000.0F;

        /* '<S2>:99:18' i = i+1; */
        qY = localDW->i + /*MW:OvSatOk*/ 1U;
        if (localDW->i + 1U < localDW->i) {
          qY = MAX_uint32_T;
        }

        localDW->i = qY;
      }
      break;

     case 1002U:
      {
        real32_T x;
        uint32_T qY;

        /* '<S2>:99:19' case array_size+2 */
        /* '<S2>:99:20' mean_voltages.q = mean(u_q_array); */
        x = localDW->u_q_array[0];
        for (k = 0; k < 999; k++) {
          x += localDW->u_q_array[k + 1];
        }

        mean_voltages->q = x / 1000.0F;

        /* '<S2>:99:21' i = i+1; */
        qY = localDW->i + /*MW:OvSatOk*/ 1U;
        if (localDW->i + 1U < localDW->i) {
          qY = MAX_uint32_T;
        }

        localDW->i = qY;
      }
      break;

     case 1003U:
      {
        real32_T x;
        uint32_T qY;

        /* '<S2>:99:22' case array_size+3 */
        /* '<S2>:99:23' mean_omega_el = mean(omega_el_array); */
        x = localDW->omega_el_array[0];
        for (k = 0; k < 999; k++) {
          x += localDW->omega_el_array[k + 1];
        }

        *mean_omega_el = x / 1000.0F;

        /* '<S2>:99:24' i = i+1; */
        qY = localDW->i + /*MW:OvSatOk*/ 1U;
        if (localDW->i + 1U < localDW->i) {
          qY = MAX_uint32_T;
        }

        localDW->i = qY;
      }
      break;

     case 1004U:
      {
        real32_T x;
        uint32_T qY;

        /* '<S2>:99:25' case array_size+4 */
        /* '<S2>:99:26' mean_currents.d = mean(i_d_array); */
        x = localDW->i_d_array[0];
        for (k = 0; k < 999; k++) {
          x += localDW->i_d_array[k + 1];
        }

        mean_currents->d = x / 1000.0F;

        /* '<S2>:99:27' i = i+1; */
        qY = localDW->i + /*MW:OvSatOk*/ 1U;
        if (localDW->i + 1U < localDW->i) {
          qY = MAX_uint32_T;
        }

        localDW->i = qY;
      }
      break;

     case 1005U:
      {
        real32_T x;
        uint32_T qY;

        /* '<S2>:99:28' case array_size+5 */
        /* '<S2>:99:29' mean_currents.q = mean(i_q_array); */
        x = localDW->i_q_array[0];
        for (k = 0; k < 999; k++) {
          x += localDW->i_q_array[k + 1];
        }

        mean_currents->q = x / 1000.0F;

        /* '<S2>:99:30' finished_calculation = true; */
        *finished_calculation = true;

        /* '<S2>:99:31' i = i+1; */
        qY = localDW->i + /*MW:OvSatOk*/ 1U;
        if (localDW->i + 1U < localDW->i) {
          qY = MAX_uint32_T;
        }

        localDW->i = qY;
      }
      break;
    }
  } else {
    uint32_T qY;

    /* '<S2>:99:33' else */
    /* '<S2>:99:34' counter_time = counter_time +1; */
    qY = localDW->counter_time + /*MW:OvSatOk*/ 1U;
    if (localDW->counter_time + 1U < localDW->counter_time) {
      qY = MAX_uint32_T;
    }

    localDW->counter_time = qY;

    /* '<S2>:99:35' if((mod(counter_time,20)==0)&&i<=array_size) */
    if ((localDW->counter_time - localDW->counter_time / 20U * 20U == 0U) &&
        (localDW->i <= 1000U)) {
      /* '<S2>:99:36' i_d_array(i) = actual_currents.d; */
      localDW->i_d_array[(int32_T)localDW->i - 1] = actual_currents->d;

      /* '<S2>:99:37' i_q_array(i) = actual_currents.q; */
      localDW->i_q_array[(int32_T)localDW->i - 1] = actual_currents->q;

      /* '<S2>:99:38' u_d_array(i) = actual_voltages.d; */
      localDW->u_d_array[(int32_T)localDW->i - 1] = actual_voltages->d;

      /* '<S2>:99:39' u_q_array(i) = actual_voltages.q; */
      localDW->u_q_array[(int32_T)localDW->i - 1] = actual_voltages->q;

      /* '<S2>:99:40' omega_el_array(i) = omega_el; */
      localDW->omega_el_array[(int32_T)localDW->i - 1] = omega_el;

      /* '<S2>:99:41' i = i+1; */
      qY = localDW->i + /*MW:OvSatOk*/ 1U;
      if (localDW->i + 1U < localDW->i) {
        qY = MAX_uint32_T;
      }

      localDW->i = qY;
    }
  }
}

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
static void enter_atomic_AMMnewRef(uint16_T *activeState, real32_T *PI_d_ref,
  real32_T *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig,
  DW_AMMstateIdentificationDQFl_t *localDW)
{
  real32_T y;

  /* Entry 'AMMnewRef': '<S2>:93' */
  /* '<S2>:93:4' counter_time = uint32(1); */
  localDW->counter_time = 1U;

  /* '<S2>:93:5' activeState = uint16(402); */
  *activeState = 402U;

  /* '<S2>:93:6' if((FluxMapIDConfig.IDstart + single(AMMn) * FluxMapIDConfig.IDstepsize) <= FluxMapIDConfig.IDstop) */
  y = (real32_T)localDW->AMMn * FluxMapIDConfig->IDstepsize +
    FluxMapIDConfig->IDstart;
  if (y <= FluxMapIDConfig->IDstop) {
    real32_T r;

    /* '<S2>:93:7' PI_d_ref = single(FluxMapIDConfig.IDstart + single(AMMn) * FluxMapIDConfig.IDstepsize); */
    *PI_d_ref = y;

    /* '<S2>:93:8' if(mod(single(AMMn),((abs(FluxMapIDConfig.IDstop-FluxMapIDConfig.IDstart))/FluxMapIDConfig.IDstepsize)+1) == 0) */
    y = fabsf(FluxMapIDConfig->IDstop - FluxMapIDConfig->IDstart) /
      FluxMapIDConfig->IDstepsize + 1.0F;
    r = (real32_T)localDW->AMMn;
    if (y == 0.0F) {
      if (localDW->AMMn == 0.0F) {
        r = y;
      }
    } else if (localDW->AMMn == 0.0F) {
      r = 0.0F / y;
    } else {
      boolean_T rEQ0;
      r = fmodf((real32_T)localDW->AMMn, y);
      rEQ0 = (r == 0.0F);
      if ((!rEQ0) && (y > floorf(y))) {
        real32_T q;
        q = fabsf((real32_T)localDW->AMMn / y);
        rEQ0 = (fabsf(q - floorf(q + 0.5F)) <= 1.1920929E-7F * q);
      }

      if (rEQ0) {
        r = 0.0F;
      } else if (y < 0.0F) {
        r += y;
      }
    }

    if (r == 0.0F) {
      /* '<S2>:93:9' if((FluxMapIDConfig.IQstart + single(AMMj) * FluxMapIDConfig.IQstepsize) <= FluxMapIDConfig.IQstop) */
      y = (real32_T)localDW->AMMj * FluxMapIDConfig->IQstepsize +
        FluxMapIDConfig->IQstart;
      if (y <= FluxMapIDConfig->IQstop) {
        uint32_T qY;

        /* '<S2>:93:10' PI_q_ref = single(FluxMapIDConfig.IQstart + single(AMMj) * FluxMapIDConfig.IQstepsize); */
        *PI_q_ref = y;

        /* '<S2>:93:11' AMMj = AMMj + 1; */
        qY = localDW->AMMj + /*MW:OvSatOk*/ 1U;
        if (localDW->AMMj + 1U < localDW->AMMj) {
          qY = MAX_uint32_T;
        }

        localDW->AMMj = qY;
      } else {
        /* '<S2>:93:12' else */
        /* '<S2>:93:13' PI_d_ref = single(0.0); */
        *PI_d_ref = 0.0F;

        /* '<S2>:93:14' PI_q_ref = single(0.0); */
        *PI_q_ref = 0.0F;
      }
    }
  }
}

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
void Fluxmap_during(uint16_T *activeState, real32_T *PI_d_ref, real32_T
                    *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t
                    *FluxMapIDConfig, uint32_T three_sec_transition_counter,
                    uz_ParaID_FluxMapID_output_t *FluxMapID_output, const
                    uz_3ph_dq_t *actual_voltages, real32_T omega_el, uz_3ph_dq_t
                    *mean_voltages, real32_T *mean_omega_el, uz_3ph_dq_t
                    *mean_currents, uint32_T *repetitionCounter, const
                    uz_3ph_dq_t *actual_currents, boolean_T
                    *finished_calculation, DW_AMMstateIdentificationDQFl_t
                    *localDW)
{
  boolean_T guard1 = false;

  /* During: Fluxmap */
  guard1 = false;
  switch (localDW->is_c14_Subchart_FluxMapID_refer) {
   case IN_AMMcollectData:
    AMMcollectData(activeState, FluxMapID_output, actual_voltages, omega_el,
                   mean_voltages, mean_omega_el, mean_currents,
                   repetitionCounter, actual_currents, finished_calculation,
                   localDW);
    break;

   case IN_AMMcooling:
    /* During 'AMMcooling': '<S2>:94' */
    /* '<S2>:105:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp <= FluxMapIDConfig.upper_meas_temp; */
    if (FluxMapID_output->WindingTemp <= FluxMapIDConfig->upper_meas_temp) {
      /* Transition: '<S2>:105' */
      /* Exit 'AMMcooling': '<S2>:94' */
      /* '<S2>:94:10' PI_d_ref = PI_d_loc; */
      *PI_d_ref = localDW->PI_d_loc_h;

      /* '<S2>:94:11' PI_q_ref = PI_q_loc; */
      *PI_q_ref = localDW->PI_q_loc_b;
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
      enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref, FluxMapIDConfig,
        localDW);
    }
    break;

   case IN_AMMheating:
    /* During 'AMMheating': '<S2>:88' */
    /* '<S2>:106:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >= FluxMapIDConfig.lower_meas_temp; */
    if (FluxMapID_output->WindingTemp >= FluxMapIDConfig->lower_meas_temp) {
      /* Transition: '<S2>:106' */
      /* Exit 'AMMheating': '<S2>:88' */
      /* '<S2>:88:10' PI_d_ref = PI_d_loc; */
      *PI_d_ref = localDW->PI_d_loc;

      /* '<S2>:88:11' PI_q_ref = PI_q_loc; */
      *PI_q_ref = localDW->PI_q_loc;
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
      enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref, FluxMapIDConfig,
        localDW);
    }
    break;

   case IN_AMMnewRef:
    {
      /* During 'AMMnewRef': '<S2>:93' */
      /* '<S2>:109:1' sf_internal_predicateOutput = three_sec_transition_counter == counter_time; */
      if (three_sec_transition_counter == localDW->counter_time) {
        uint32_T qY;

        /* Transition: '<S2>:109' */
        localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMcollectData;

        /* Entry 'AMMcollectData': '<S2>:99' */
        localDW->i = 1U;
        memset(&localDW->u_d_array[0], 0, 1000U * sizeof(real32_T));
        memset(&localDW->u_q_array[0], 0, 1000U * sizeof(real32_T));
        memset(&localDW->omega_el_array[0], 0, 1000U * sizeof(real32_T));
        memset(&localDW->i_d_array[0], 0, 1000U * sizeof(real32_T));
        memset(&localDW->i_q_array[0], 0, 1000U * sizeof(real32_T));

        /* '<S2>:99:4' counter_time = uint32(1); */
        localDW->counter_time = 1U;

        /* '<S2>:99:5' activeState = uint16(403); */
        *activeState = 403U;

        /* '<S2>:99:6' repetitionCounter = repetitionCounter + 1; */
        qY = *repetitionCounter + /*MW:OvSatOk*/ 1U;
        if (*repetitionCounter + 1U < *repetitionCounter) {
          qY = MAX_uint32_T;
        }

        *repetitionCounter = qY;

        /* '<S2>:99:7' if(AMMn >= (NumberOfIDpoints-1)) */
        qY = localDW->NumberOfIDpoints - /*MW:OvSatOk*/ 1U;
        if (localDW->NumberOfIDpoints - 1U > localDW->NumberOfIDpoints) {
          qY = 0U;
        }

        if (localDW->AMMn >= qY) {
          /* '<S2>:99:8' AMMn = uint32(0); */
          localDW->AMMn = 0U;
        } else {
          /* '<S2>:99:9' else */
          /* '<S2>:99:10' AMMn = AMMn + 1; */
          qY = localDW->AMMn + /*MW:OvSatOk*/ 1U;
          if (localDW->AMMn + 1U < localDW->AMMn) {
            qY = MAX_uint32_T;
          }

          localDW->AMMn = qY;
        }

        /* '<S2>:99:12' FluxMapID_output.external_Measurement_Flag=boolean(1); */
        FluxMapID_output->external_Measurement_Flag = true;
      } else {
        uint32_T qY;

        /* '<S2>:93:18' counter_time = counter_time +1; */
        qY = localDW->counter_time + /*MW:OvSatOk*/ 1U;
        if (localDW->counter_time + 1U < localDW->counter_time) {
          qY = MAX_uint32_T;
        }

        localDW->counter_time = qY;
      }
    }
    break;

   case IN_initAMM:
    /* During 'initAMM': '<S2>:90' */
    /* '<S2>:181:1' sf_internal_predicateOutput = FluxMapIDConfig.start_FM_ID==1 && FluxMapIDConfig.identR == 0; */
    if (FluxMapIDConfig->start_FM_ID && (!FluxMapIDConfig->identR)) {
      /* Transition: '<S2>:181' */
      /* '<S2>:98:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp > FluxMapIDConfig.upper_meas_temp; */
      if (FluxMapID_output->WindingTemp > FluxMapIDConfig->upper_meas_temp) {
        /* Transition: '<S2>:98' */
        localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMcooling;

        /* Entry 'AMMcooling': '<S2>:94' */
        localDW->PI_d_loc_h = 0.0F;

        /* '<S2>:94:4' activeState = uint16(410); */
        *activeState = 410U;

        /* '<S2>:94:5' PI_q_loc = PI_d_ref; */
        /* '<S2>:94:6' PI_q_loc = PI_q_ref; */
        localDW->PI_q_loc_b = *PI_q_ref;

        /* '<S2>:94:7' PI_d_ref = single(0); */
        *PI_d_ref = 0.0F;

        /* '<S2>:94:8' PI_q_ref = single(0); */
        *PI_q_ref = 0.0F;

        /* '<S2>:100:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp < FluxMapIDConfig.lower_meas_temp; */
      } else if (FluxMapID_output->WindingTemp <
                 FluxMapIDConfig->lower_meas_temp) {
        /* Transition: '<S2>:100' */
        localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMheating;

        /* Entry 'AMMheating': '<S2>:88' */
        /* '<S2>:88:4' activeState = uint16(420); */
        *activeState = 420U;

        /* '<S2>:88:5' PI_d_loc = PI_d_ref; */
        localDW->PI_d_loc = *PI_d_ref;

        /* '<S2>:88:6' PI_q_loc = PI_q_ref; */
        localDW->PI_q_loc = *PI_q_ref;

        /* '<S2>:88:7' PI_d_ref = FluxMapIDConfig.IDstart; */
        *PI_d_ref = FluxMapIDConfig->IDstart;

        /* '<S2>:88:8' PI_q_ref = FluxMapIDConfig.IQstop; */
        *PI_q_ref = FluxMapIDConfig->IQstop;

        /* '<S2>:102:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >=FluxMapIDConfig.lower_meas_temp && .... */
        /* '<S2>:102:2' FluxMapID_output.WindingTemp <=FluxMapIDConfig.upper_meas_temp; */
        /* . */
      } else if ((FluxMapID_output->WindingTemp >=
                  FluxMapIDConfig->lower_meas_temp) &&
                 (FluxMapID_output->WindingTemp <=
                  FluxMapIDConfig->upper_meas_temp)) {
        /* Transition: '<S2>:102' */
        localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
        enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref, FluxMapIDConfig,
          localDW);
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    break;

   case IN_outputData:
    {
      /* During 'outputData': '<S2>:170' */
      /* '<S2>:177:1' sf_internal_predicateOutput = counter_time == uint32(100); */
      if (localDW->counter_time == 100U) {
        /* Transition: '<S2>:177' */
        /* '<S2>:165:1' sf_internal_predicateOutput = repetitionCounter>=NumberOfPoints; */
        if (*repetitionCounter >= localDW->NumberOfPoints) {
          /* Transition: '<S2>:165' */
          /* '<S2>:165:1' PI_d_ref=single(0); */
          *PI_d_ref = 0.0F;

          /* '<S2>:165:1' PI_q_ref=single(0); */
          *PI_q_ref = 0.0F;
          localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
          localDW->exitPortIndex = 2U;

          /* '<S2>:178:1' sf_internal_predicateOutput = repetitionCounter < NumberOfPoints; */
        } else if (*repetitionCounter < localDW->NumberOfPoints) {
          /* Transition: '<S2>:178' */
          /* '<S2>:107:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp > FluxMapIDConfig.upper_meas_temp; */
          if (FluxMapID_output->WindingTemp > FluxMapIDConfig->upper_meas_temp)
          {
            /* Transition: '<S2>:107' */
            localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMcooling;

            /* Entry 'AMMcooling': '<S2>:94' */
            localDW->PI_d_loc_h = 0.0F;

            /* '<S2>:94:4' activeState = uint16(410); */
            *activeState = 410U;

            /* '<S2>:94:5' PI_q_loc = PI_d_ref; */
            /* '<S2>:94:6' PI_q_loc = PI_q_ref; */
            localDW->PI_q_loc_b = *PI_q_ref;

            /* '<S2>:94:7' PI_d_ref = single(0); */
            *PI_d_ref = 0.0F;

            /* '<S2>:94:8' PI_q_ref = single(0); */
            *PI_q_ref = 0.0F;

            /* '<S2>:104:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >=FluxMapIDConfig.lower_meas_temp && FluxMapID_output.WindingTemp <= FluxMapIDConfig.upper_meas_temp; */
          } else if ((FluxMapID_output->WindingTemp >=
                      FluxMapIDConfig->lower_meas_temp) &&
                     (FluxMapID_output->WindingTemp <=
                      FluxMapIDConfig->upper_meas_temp)) {
            /* Transition: '<S2>:104' */
            localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
            enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref,
              FluxMapIDConfig, localDW);

            /* '<S2>:101:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp < FluxMapIDConfig.lower_meas_temp; */
          } else if (FluxMapID_output->WindingTemp <
                     FluxMapIDConfig->lower_meas_temp) {
            /* Transition: '<S2>:101' */
            localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMheating;

            /* Entry 'AMMheating': '<S2>:88' */
            /* '<S2>:88:4' activeState = uint16(420); */
            *activeState = 420U;

            /* '<S2>:88:5' PI_d_loc = PI_d_ref; */
            localDW->PI_d_loc = *PI_d_ref;

            /* '<S2>:88:6' PI_q_loc = PI_q_ref; */
            localDW->PI_q_loc = *PI_q_ref;

            /* '<S2>:88:7' PI_d_ref = FluxMapIDConfig.IDstart; */
            *PI_d_ref = FluxMapIDConfig->IDstart;

            /* '<S2>:88:8' PI_q_ref = FluxMapIDConfig.IQstop; */
            *PI_q_ref = FluxMapIDConfig->IQstop;
          } else {
            uint32_T qY;

            /* '<S2>:170:6' counter_time = counter_time + 1; */
            qY = localDW->counter_time + /*MW:OvSatOk*/ 1U;
            if (localDW->counter_time + 1U < localDW->counter_time) {
              qY = MAX_uint32_T;
            }

            localDW->counter_time = qY;
          }
        } else {
          uint32_T qY;

          /* '<S2>:170:6' counter_time = counter_time + 1; */
          qY = localDW->counter_time + /*MW:OvSatOk*/ 1U;
          if (localDW->counter_time + 1U < localDW->counter_time) {
            qY = MAX_uint32_T;
          }

          localDW->counter_time = qY;
        }
      } else {
        uint32_T qY;

        /* '<S2>:170:6' counter_time = counter_time + 1; */
        qY = localDW->counter_time + /*MW:OvSatOk*/ 1U;
        if (localDW->counter_time + 1U < localDW->counter_time) {
          qY = MAX_uint32_T;
        }

        localDW->counter_time = qY;
      }
    }
    break;

   default:
    {
      uint64_T tmp;

      /* During 'waitIdentR': '<S2>:182' */
      /* '<S2>:184:1' sf_internal_predicateOutput = uint32(10)*three_sec_transition_counter == counter_time; */
      tmp = 10ULL * three_sec_transition_counter;
      if (tmp > 4294967295ULL) {
        tmp = 4294967295ULL;
      }

      if ((uint32_T)tmp == localDW->counter_time) {
        /* Transition: '<S2>:184' */
        /* '<S2>:98:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp > FluxMapIDConfig.upper_meas_temp; */
        if (FluxMapID_output->WindingTemp > FluxMapIDConfig->upper_meas_temp) {
          /* Transition: '<S2>:98' */
          localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMcooling;

          /* Entry 'AMMcooling': '<S2>:94' */
          localDW->PI_d_loc_h = 0.0F;

          /* '<S2>:94:4' activeState = uint16(410); */
          *activeState = 410U;

          /* '<S2>:94:5' PI_q_loc = PI_d_ref; */
          /* '<S2>:94:6' PI_q_loc = PI_q_ref; */
          localDW->PI_q_loc_b = *PI_q_ref;

          /* '<S2>:94:7' PI_d_ref = single(0); */
          *PI_d_ref = 0.0F;

          /* '<S2>:94:8' PI_q_ref = single(0); */
          *PI_q_ref = 0.0F;

          /* '<S2>:100:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp < FluxMapIDConfig.lower_meas_temp; */
        } else if (FluxMapID_output->WindingTemp <
                   FluxMapIDConfig->lower_meas_temp) {
          /* Transition: '<S2>:100' */
          localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMheating;

          /* Entry 'AMMheating': '<S2>:88' */
          /* '<S2>:88:4' activeState = uint16(420); */
          *activeState = 420U;

          /* '<S2>:88:5' PI_d_loc = PI_d_ref; */
          localDW->PI_d_loc = *PI_d_ref;

          /* '<S2>:88:6' PI_q_loc = PI_q_ref; */
          localDW->PI_q_loc = *PI_q_ref;

          /* '<S2>:88:7' PI_d_ref = FluxMapIDConfig.IDstart; */
          *PI_d_ref = FluxMapIDConfig->IDstart;

          /* '<S2>:88:8' PI_q_ref = FluxMapIDConfig.IQstop; */
          *PI_q_ref = FluxMapIDConfig->IQstop;

          /* '<S2>:102:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >=FluxMapIDConfig.lower_meas_temp && .... */
          /* '<S2>:102:2' FluxMapID_output.WindingTemp <=FluxMapIDConfig.upper_meas_temp; */
          /* . */
        } else if ((FluxMapID_output->WindingTemp >=
                    FluxMapIDConfig->lower_meas_temp) &&
                   (FluxMapID_output->WindingTemp <=
                    FluxMapIDConfig->upper_meas_temp)) {
          /* Transition: '<S2>:102' */
          localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
          enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref,
            FluxMapIDConfig, localDW);
        } else {
          uint32_T qY;

          /* '<S2>:182:6' counter_time = counter_time +1; */
          qY = localDW->counter_time + /*MW:OvSatOk*/ 1U;
          if (localDW->counter_time + 1U < localDW->counter_time) {
            qY = MAX_uint32_T;
          }

          localDW->counter_time = qY;
        }
      } else {
        uint32_T qY;

        /* '<S2>:182:6' counter_time = counter_time +1; */
        qY = localDW->counter_time + /*MW:OvSatOk*/ 1U;
        if (localDW->counter_time + 1U < localDW->counter_time) {
          qY = MAX_uint32_T;
        }

        localDW->counter_time = qY;
      }
    }
    break;
  }

  if (guard1) {
    /* '<S2>:183:1' sf_internal_predicateOutput = FluxMapIDConfig.start_FM_ID==1 && FluxMapIDConfig.identR == 1; */
    if (FluxMapIDConfig->start_FM_ID && FluxMapIDConfig->identR) {
      /* Transition: '<S2>:183' */
      localDW->is_c14_Subchart_FluxMapID_refer = IN_waitIdentR;

      /* Entry 'waitIdentR': '<S2>:182' */
      /* '<S2>:182:3' activeState = uint16(415); */
      *activeState = 415U;

      /* '<S2>:182:4' counter_time = uint32(1); */
      localDW->counter_time = 1U;
    }
  }
}

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
void Fluxmap_enter(uint16_T *activeState, real32_T *PI_d_ref, real32_T *PI_q_ref,
                   const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig,
                   DW_AMMstateIdentificationDQFl_t *localDW)
{
  uint64_T tmp;
  real32_T tmp_0;
  uint32_T tmp_1;
  localDW->AMMn = 0U;
  localDW->AMMj = 0U;

  /* Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  /* Entry: Fluxmap */
  /* Entry Internal: Fluxmap */
  /* Transition: '<S2>:97' */
  localDW->is_c14_Subchart_FluxMapID_refer = IN_initAMM;

  /* Entry 'initAMM': '<S2>:90' */
  /* '<S2>:90:4' activeState = uint16(401); */
  *activeState = 401U;

  /* '<S2>:90:5' NumberOfIDpoints = uint32(abs(FluxMapIDConfig.IDstop-FluxMapIDConfig.IDstart)/FluxMapIDConfig.IDstepsize+1); */
  tmp_0 = roundf(fabsf(FluxMapIDConfig->IDstop - FluxMapIDConfig->IDstart) /
                 FluxMapIDConfig->IDstepsize + 1.0F);
  if (tmp_0 < 4.2949673E+9F) {
    if (tmp_0 >= 0.0F) {
      localDW->NumberOfIDpoints = (uint32_T)tmp_0;
    } else {
      localDW->NumberOfIDpoints = 0U;
    }
  } else {
    localDW->NumberOfIDpoints = MAX_uint32_T;
  }

  /* '<S2>:90:6' NumberOfIQpoints = uint32(abs(FluxMapIDConfig.IQstop-FluxMapIDConfig.IQstart)/FluxMapIDConfig.IQstepsize+1); */
  /* '<S2>:90:7' NumberOfPoints = uint32(NumberOfIDpoints*NumberOfIQpoints); */
  tmp_0 = roundf(fabsf(FluxMapIDConfig->IQstop - FluxMapIDConfig->IQstart) /
                 FluxMapIDConfig->IQstepsize + 1.0F);
  if (tmp_0 < 4.2949673E+9F) {
    if (tmp_0 >= 0.0F) {
      tmp_1 = (uint32_T)tmp_0;
    } else {
      tmp_1 = 0U;
    }
  } else {
    tmp_1 = MAX_uint32_T;
  }

  tmp = (uint64_T)localDW->NumberOfIDpoints * tmp_1;
  if (tmp > 4294967295ULL) {
    tmp = 4294967295ULL;
  }

  localDW->NumberOfPoints = (uint32_T)tmp;

  /* '<S2>:90:8' PI_d_ref = single(0); */
  *PI_d_ref = 0.0F;

  /* '<S2>:90:9' PI_q_ref = single(0); */
  *PI_q_ref = 0.0F;

  /* '<S2>:90:10' counter_time = uint32(1); */
  localDW->counter_time = 1U;

  /* End of Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
}

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
void Fluxmap_exit(real32_T *PI_d_ref, real32_T *PI_q_ref,
                  uz_ParaID_FluxMapID_output_t *FluxMapID_output, boolean_T
                  *finished_calculation, DW_AMMstateIdentificationDQFl_t
                  *localDW)
{
  /* Exit Internal: Fluxmap */
  switch (localDW->is_c14_Subchart_FluxMapID_refer) {
   case IN_AMMcollectData:
    /* Exit 'AMMcollectData': '<S2>:99' */
    /* '<S2>:99:45' FluxMapID_output.external_Measurement_Flag=boolean(0); */
    FluxMapID_output->external_Measurement_Flag = false;

    /* '<S2>:99:46' finished_calculation = false; */
    *finished_calculation = false;
    localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
    break;

   case IN_AMMcooling:
    /* Exit 'AMMcooling': '<S2>:94' */
    /* '<S2>:94:10' PI_d_ref = PI_d_loc; */
    *PI_d_ref = localDW->PI_d_loc_h;

    /* '<S2>:94:11' PI_q_ref = PI_q_loc; */
    *PI_q_ref = localDW->PI_q_loc_b;
    localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
    break;

   case IN_AMMheating:
    /* Exit 'AMMheating': '<S2>:88' */
    /* '<S2>:88:10' PI_d_ref = PI_d_loc; */
    *PI_d_ref = localDW->PI_d_loc;

    /* '<S2>:88:11' PI_q_ref = PI_q_loc; */
    *PI_q_ref = localDW->PI_q_loc;
    localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
    break;

   default:
    localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
    break;
  }
}

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
void Fluxmap_init(DW_AMMstateIdentificationDQFl_t *localDW)
{
  localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
  localDW->NumberOfIDpoints = 0U;
  localDW->NumberOfPoints = 0U;
  localDW->counter_time = 0U;
  localDW->AMMn = 0U;
  localDW->AMMj = 0U;
  localDW->PI_d_loc = 0.0F;
  localDW->PI_q_loc = 0.0F;
  localDW->PI_d_loc_h = 0.0F;
  localDW->PI_q_loc_b = 0.0F;
  localDW->i = 1U;
  memset(&localDW->u_d_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->u_q_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->omega_el_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->i_d_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->i_q_array[0], 0, 1000U * sizeof(real32_T));
}

/*
 * Function for Chart: '<Root>/FluxMapID_6ph_codegen'
 * function reset_FOC_out
 */
static void reset_FOC_out(ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y)
{
  /* Outport: '<Root>/FluxMapID_FOC_output' */
  /* MATLAB Function 'reset_FOC_out': '<S1>:870' */
  /* '<S1>:870:2' FluxMapID_FOC_output.setpoint_filter = 0x0000; */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.setpoint_filter = 0U;

  /* '<S1>:870:3' FluxMapID_FOC_output.i_dq_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.d = 0.0F;

  /* '<S1>:870:4' FluxMapID_FOC_output.i_dq_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.q = 0.0F;

  /* '<S1>:870:5' FluxMapID_FOC_output.i_xy_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.d = 0.0F;

  /* '<S1>:870:6' FluxMapID_FOC_output.i_xy_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.q = 0.0F;

  /* '<S1>:870:7' FluxMapID_FOC_output.i_zero_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_zero_ref.d = 0.0F;

  /* '<S1>:870:8' FluxMapID_FOC_output.i_zero_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_zero_ref.q = 0.0F;

  /* '<S1>:870:9' FluxMapID_FOC_output.PI_subsystem = 0x0000; */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.PI_subsystem = 0U;

  /* '<S1>:870:10' FluxMapID_FOC_output.resonant_subsystem = 0x0000; */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resonant_subsystem = 0U;

  /* '<S1>:870:11' FluxMapID_FOC_output.enableFOC_current = false; */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_current = false;
}

/*
 * Function for Chart: '<Root>/FluxMapID_6ph_codegen'
 * function reset_logging_out
 */
static void reset_logging_out(DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW)
{
  /* MATLAB Function 'reset_logging_out': '<S1>:873' */
  /* '<S1>:873:2' FluxMapID_output.psi_array(1)=single(0); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[0] = 0.0F;

  /* '<S1>:873:3' FluxMapID_output.psi_array(2)=single(0); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[1] = 0.0F;

  /* '<S1>:873:4' FluxMapID_output.psi_array(3)=single(0); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[2] = 0.0F;

  /* '<S1>:873:5' FluxMapID_output.psi_array(4)=single(0); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[3] = 0.0F;

  /* '<S1>:873:6' FluxMapID_output.array_index =uint32(0); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.array_index = 0U;
}

/*
 * Function for Chart: '<Root>/FluxMapID_6ph_codegen'
 * function init
 */
static void init(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
                 ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
                 DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW)
{
  real32_T tmp;

  /* Outport: '<Root>/FluxMapID_FOC_output' */
  /* MATLAB Function 'init': '<S1>:868' */
  /* '<S1>:868:2' FluxMapID_FOC_output.enableFOC_current=boolean(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_current = false;

  /* '<S1>:868:3' FluxMapID_output.psi_array = single([0;0;0;0]); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[0] = 0.0F;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[1] = 0.0F;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[2] = 0.0F;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[3] = 0.0F;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:868:4' one_sec_transition_counter = uint32(1/GlobalConfig.sampleTimeISR); */
  /* '<S1>:868:5' three_sec_transition_counter = uint32(3/GlobalConfig.sampleTimeISR); */
  tmp = roundf(3.0F / rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c = (uint32_T)tmp;
    } else {
      rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c = 0U;
    }
  } else {
    rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c = MAX_uint32_T;
  }

  /* '<S1>:868:6' reset_FOC_out; */
  reset_FOC_out(rtFluxMapID_6ph_codegen_Y);

  /* '<S1>:868:7' reset_logging_out; */
  reset_logging_out(rtFluxMapID_6ph_codegen_DW);

  /* Outport: '<Root>/FluxMapID_FOC_output' */
  /* '<S1>:868:8' FluxMapID_FOC_output.activeState = uint16(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 0U;
}

/*
 * Function for Chart: '<Root>/FluxMapID_6ph_codegen'
 * function RefreshDataRegister
 */
static void RefreshDataRegister(DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW)
{
  uint16_T k;

  /* MATLAB Function 'RefreshDataRegister': '<S1>:896' */
  /* '<S1>:896:3' m=length(fun_R_s_array); */
  /* '<S1>:896:4' for k= uint16(0):uint16(m-2) */
  for (k = 0; k < 19; k++) {
    /* '<S1>:896:5' fun_R_s_array(m-k)=fun_R_s_array(m-(k+1)); */
    rtFluxMapID_6ph_codegen_DW->fun_R_s_array[19 - k] =
      rtFluxMapID_6ph_codegen_DW->fun_R_s_array[18 - k];
  }
}

/*
 * Function for Chart: '<Root>/FluxMapID_6ph_codegen'
 * function fun = identRes
 */
static real32_T identRes(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW)
{
  int32_T k;
  real32_T fun_v1_counter_tmp;
  real32_T tmp;
  uint32_T qY;

  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'identRes': '<S1>:888' */
  /* '<S1>:888:3' if(fun_counter <= uint32(0.5/GlobalConfig.sampleTimeISR)) */
  fun_v1_counter_tmp = roundf(0.5F /
    rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
  if (fun_v1_counter_tmp < 4.2949673E+9F) {
    if (fun_v1_counter_tmp >= 0.0F) {
      qY = (uint32_T)fun_v1_counter_tmp;
    } else {
      qY = 0U;
    }
  } else {
    qY = MAX_uint32_T;
  }

  if (rtFluxMapID_6ph_codegen_DW->fun_counter <= qY) {
    /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
    /* meas */
    /* '<S1>:888:4' fun_i_R_online = single(-FluxMapIDConfig.identRAmp); */
    rtFluxMapID_6ph_codegen_DW->fun_i_R_online =
      -rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identRAmp;

    /* Inport: '<Root>/GlobalConfig' */
    /* '<S1>:888:5' if(fun_counter >= uint32(0.4/GlobalConfig.sampleTimeISR) && fun_counter < uint32(0.5/GlobalConfig.sampleTimeISR)) */
    tmp = roundf(0.4F /
                 rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
    if (tmp < 4.2949673E+9F) {
      if (tmp >= 0.0F) {
        qY = (uint32_T)tmp;
      } else {
        qY = 0U;
      }
    } else {
      qY = MAX_uint32_T;
    }

    if (rtFluxMapID_6ph_codegen_DW->fun_counter >= qY) {
      if (fun_v1_counter_tmp < 4.2949673E+9F) {
        if (fun_v1_counter_tmp >= 0.0F) {
          qY = (uint32_T)fun_v1_counter_tmp;
        } else {
          qY = 0U;
        }
      } else {
        qY = MAX_uint32_T;
      }

      if (rtFluxMapID_6ph_codegen_DW->fun_counter < qY) {
        /* '<S1>:888:6' fun_v1_counter = fun_v1_counter + fun_actual_v; */
        rtFluxMapID_6ph_codegen_DW->fun_v1_counter +=
          rtFluxMapID_6ph_codegen_DW->fun_actual_v;

        /* '<S1>:888:7' fun_i1_counter = fun_i1_counter + fun_actual_i; */
        rtFluxMapID_6ph_codegen_DW->fun_i1_counter +=
          rtFluxMapID_6ph_codegen_DW->fun_actual_i;
      }
    }
  }

  /* '<S1>:888:11' if(fun_counter > uint32(0.5/GlobalConfig.sampleTimeISR) && fun_counter <= uint32(1.0/GlobalConfig.sampleTimeISR)) */
  if (fun_v1_counter_tmp < 4.2949673E+9F) {
    if (fun_v1_counter_tmp >= 0.0F) {
      qY = (uint32_T)fun_v1_counter_tmp;
    } else {
      qY = 0U;
    }
  } else {
    qY = MAX_uint32_T;
  }

  if (rtFluxMapID_6ph_codegen_DW->fun_counter > qY) {
    /* Inport: '<Root>/GlobalConfig' */
    fun_v1_counter_tmp = roundf(1.0F /
      rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
    if (fun_v1_counter_tmp < 4.2949673E+9F) {
      if (fun_v1_counter_tmp >= 0.0F) {
        qY = (uint32_T)fun_v1_counter_tmp;
      } else {
        qY = 0U;
      }
    } else {
      qY = MAX_uint32_T;
    }

    if (rtFluxMapID_6ph_codegen_DW->fun_counter <= qY) {
      /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
      /* '<S1>:888:12' fun_i_R_online = single(FluxMapIDConfig.identRAmp); */
      rtFluxMapID_6ph_codegen_DW->fun_i_R_online =
        rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identRAmp;

      /* Inport: '<Root>/GlobalConfig' */
      /* '<S1>:888:13' if(fun_counter >= uint32(0.9/GlobalConfig.sampleTimeISR) && fun_counter < uint32(1.0/GlobalConfig.sampleTimeISR)) */
      tmp = roundf(0.9F /
                   rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
      if (tmp < 4.2949673E+9F) {
        if (tmp >= 0.0F) {
          qY = (uint32_T)tmp;
        } else {
          qY = 0U;
        }
      } else {
        qY = MAX_uint32_T;
      }

      if (rtFluxMapID_6ph_codegen_DW->fun_counter >= qY) {
        if (fun_v1_counter_tmp < 4.2949673E+9F) {
          if (fun_v1_counter_tmp >= 0.0F) {
            qY = (uint32_T)fun_v1_counter_tmp;
          } else {
            qY = 0U;
          }
        } else {
          qY = MAX_uint32_T;
        }

        if (rtFluxMapID_6ph_codegen_DW->fun_counter < qY) {
          /* '<S1>:888:14' fun_v2_counter = fun_v2_counter + fun_actual_v; */
          rtFluxMapID_6ph_codegen_DW->fun_v2_counter +=
            rtFluxMapID_6ph_codegen_DW->fun_actual_v;

          /* '<S1>:888:15' fun_i2_counter = fun_i2_counter + fun_actual_i; */
          rtFluxMapID_6ph_codegen_DW->fun_i2_counter +=
            rtFluxMapID_6ph_codegen_DW->fun_actual_i;
        }
      }
    }
  }

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:888:19' if(fun_counter == uint32(0.4/GlobalConfig.sampleTimeISR + 1) ) */
  fun_v1_counter_tmp = roundf(0.4F /
    rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR + 1.0F);
  if (fun_v1_counter_tmp < 4.2949673E+9F) {
    if (fun_v1_counter_tmp >= 0.0F) {
      qY = (uint32_T)fun_v1_counter_tmp;
    } else {
      qY = 0U;
    }
  } else {
    qY = MAX_uint32_T;
  }

  if (rtFluxMapID_6ph_codegen_DW->fun_counter == qY) {
    /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
    /* '<S1>:888:20' fun_i_R_online = single(-FluxMapIDConfig.identRAmp); */
    rtFluxMapID_6ph_codegen_DW->fun_i_R_online =
      -rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identRAmp;

    /* Inport: '<Root>/GlobalConfig' */
    /* '<S1>:888:21' fun_v1_counter=fun_v1_counter/(0.1/GlobalConfig.sampleTimeISR); */
    fun_v1_counter_tmp = 0.1F /
      rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR;
    rtFluxMapID_6ph_codegen_DW->fun_v1_counter /= fun_v1_counter_tmp;

    /* '<S1>:888:22' fun_i1_counter=fun_i1_counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtFluxMapID_6ph_codegen_DW->fun_i1_counter /= fun_v1_counter_tmp;

    /* '<S1>:888:23' fun_v2_counter=fun_v2_counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtFluxMapID_6ph_codegen_DW->fun_v2_counter /= fun_v1_counter_tmp;

    /* '<S1>:888:24' fun_i2_counter=fun_i2_counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtFluxMapID_6ph_codegen_DW->fun_i2_counter /= fun_v1_counter_tmp;

    /* '<S1>:888:25' fun_R_s_array(1,1) = single((fun_v2_counter-fun_v1_counter)/(fun_i2_counter-fun_i1_counter)); */
    rtFluxMapID_6ph_codegen_DW->fun_R_s_array[0] =
      (rtFluxMapID_6ph_codegen_DW->fun_v2_counter -
       rtFluxMapID_6ph_codegen_DW->fun_v1_counter) /
      (rtFluxMapID_6ph_codegen_DW->fun_i2_counter -
       rtFluxMapID_6ph_codegen_DW->fun_i1_counter);

    /* '<S1>:888:26' RefreshDataRegister; */
    RefreshDataRegister(rtFluxMapID_6ph_codegen_DW);

    /* '<S1>:888:27' FluxMapID_output.R_s = mean(fun_R_s_array); */
    fun_v1_counter_tmp = rtFluxMapID_6ph_codegen_DW->fun_R_s_array[0];
    for (k = 0; k < 19; k++) {
      fun_v1_counter_tmp += rtFluxMapID_6ph_codegen_DW->fun_R_s_array[k + 1];
    }

    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s = fun_v1_counter_tmp /
      20.0F;

    /* '<S1>:888:28' fun_counter = uint32(1); */
    rtFluxMapID_6ph_codegen_DW->fun_counter = 1U;

    /* '<S1>:888:29' fun_v1_counter = single(0); */
    rtFluxMapID_6ph_codegen_DW->fun_v1_counter = 0.0F;

    /* '<S1>:888:30' fun_v2_counter = single(0); */
    rtFluxMapID_6ph_codegen_DW->fun_v2_counter = 0.0F;

    /* '<S1>:888:31' fun_i1_counter = single(0); */
    rtFluxMapID_6ph_codegen_DW->fun_i1_counter = 0.0F;

    /* '<S1>:888:32' fun_i2_counter = single(0); */
    rtFluxMapID_6ph_codegen_DW->fun_i2_counter = 0.0F;
  }

  /* '<S1>:888:35' fun_counter = fun_counter + 1; */
  qY = rtFluxMapID_6ph_codegen_DW->fun_counter + /*MW:OvSatOk*/ 1U;
  if (rtFluxMapID_6ph_codegen_DW->fun_counter + 1U <
      rtFluxMapID_6ph_codegen_DW->fun_counter) {
    qY = MAX_uint32_T;
  }

  rtFluxMapID_6ph_codegen_DW->fun_counter = qY;

  /* '<S1>:888:36' fun = single(FluxMapID_output.R_s); */
  return rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s;
}

/* Function for Chart: '<Root>/FluxMapID_6ph_codegen' */
static void exit_atomic_Wait_select_subsyst(ExtU_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_U, ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y)
{
  /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
  /* Exit 'Wait_select_subsystem': '<S1>:762' */
  /* '<S1>:762:11' switch (FluxMapIDConfig.selected_subsystem) */
  switch (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.selected_subsystem) {
   case 1U:
    /* Outport: '<Root>/FluxMapID_FOC_output' */
    /* '<S1>:762:12' case 1 */
    /* '<S1>:762:13' FluxMapID_FOC_output.PI_subsystem = 0x0003; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.PI_subsystem = 3U;

    /* '<S1>:762:14' FluxMapID_FOC_output.resonant_subsystem = 0x0001; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resonant_subsystem = 1U;

    /* '<S1>:762:15' FluxMapID_FOC_output.setpoint_filter = 0x0001; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.setpoint_filter = 1U;
    break;

   case 2U:
    /* Outport: '<Root>/FluxMapID_FOC_output' */
    /* '<S1>:762:16' case 2 */
    /* '<S1>:762:17' FluxMapID_FOC_output.PI_subsystem = 0x0003; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.PI_subsystem = 3U;

    /* '<S1>:762:18' FluxMapID_FOC_output.resonant_subsystem = 0x0002; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resonant_subsystem = 2U;

    /* '<S1>:762:19' FluxMapID_FOC_output.setpoint_filter = 0x0002 */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.setpoint_filter = 2U;
    break;

   case 3U:
    /* Outport: '<Root>/FluxMapID_FOC_output' */
    /* '<S1>:762:20' case 3 */
    /* '<S1>:762:21' FluxMapID_FOC_output.PI_subsystem = 0x0004; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.PI_subsystem = 4U;

    /* '<S1>:762:22' FluxMapID_FOC_output.resonant_subsystem = 0x0004; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resonant_subsystem = 4U;

    /* '<S1>:762:23' FluxMapID_FOC_output.setpoint_filter = 0x0004; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.setpoint_filter = 4U;
    break;

   default:
    /* Outport: '<Root>/FluxMapID_FOC_output' */
    /* '<S1>:762:24' otherwise */
    /* '<S1>:762:25' FluxMapID_FOC_output.PI_subsystem = 0x0000; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.PI_subsystem = 0U;

    /* '<S1>:762:26' FluxMapID_FOC_output.resonant_subsystem = 0x0000; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resonant_subsystem = 0U;
    break;
  }

  /* End of SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
}

/* Function for Chart: '<Root>/FluxMapID_6ph_codegen' */
static void Wait_select_subsystem(ExtU_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_U, ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y, DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW)
{
  /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  /* During 'Wait_select_subsystem': '<S1>:762' */
  /* '<S1>:757:1' sf_internal_predicateOutput = FluxMapIDConfig.selected_subsystem == 2 && GlobalConfig.ACCEPT==1; */
  if ((rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.selected_subsystem == 2) &&
      rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S1>:757' */
    exit_atomic_Wait_select_subsyst(rtFluxMapID_6ph_codegen_U,
      rtFluxMapID_6ph_codegen_Y);
    rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_IdentificationXY;

    /* Entry 'IdentificationXY': '<S1>:736' */
    /* '<S1>:736:3' FluxMapID_output.psi_array = [0;0;0;0]; */
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[0] = 0.0F;
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[1] = 0.0F;
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[2] = 0.0F;
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[3] = 0.0F;

    /* Outport: '<Root>/FluxMapID_FOC_output' */
    /* '<S1>:736:4' FluxMapID_FOC_output.resetIntegrator = false; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = false;

    /* '<S1>:736:5' FluxMapID_FOC_output.enableFOC_current = true; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_current = true;

    /* Entry Internal 'IdentificationXY': '<S1>:736' */
    /* Transition: '<S1>:749' */
    rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_Fluxmap;

    /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
     *  Inport: '<Root>/ActualValues'
     */
    Fluxmap_enter(&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
                  &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                  &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                  &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
                  &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);

    /* '<S1>:754:1' sf_internal_predicateOutput = FluxMapIDConfig.selected_subsystem == 1 && GlobalConfig.ACCEPT==1; */
  } else if ((rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.selected_subsystem == 1)
             && rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S1>:754' */
    exit_atomic_Wait_select_subsyst(rtFluxMapID_6ph_codegen_U,
      rtFluxMapID_6ph_codegen_Y);
    rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_IdentificationDQ;

    /* Entry 'IdentificationDQ': '<S1>:717' */
    /* '<S1>:717:3' FluxMapID_output.psi_array = [0;0;0;0]; */
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[0] = 0.0F;
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[1] = 0.0F;
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[2] = 0.0F;
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[3] = 0.0F;

    /* Outport: '<Root>/FluxMapID_FOC_output' */
    /* '<S1>:717:4' FluxMapID_FOC_output.resetIntegrator = false; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = false;

    /* '<S1>:717:5' FluxMapID_FOC_output.enableFOC_current = true; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_current = true;

    /* Entry Internal 'IdentificationDQ': '<S1>:717' */
    /* Transition: '<S1>:733' */
    rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_Fluxmap;

    /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
     *  Inport: '<Root>/ActualValues'
     */
    Fluxmap_enter(&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
                  &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                  &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                  &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
                  &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);

    /* '<S1>:837:1' sf_internal_predicateOutput = FluxMapIDConfig.selected_subsystem == 3 && GlobalConfig.ACCEPT==1; */
  } else if ((rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.selected_subsystem == 3)
             && rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S1>:837' */
    exit_atomic_Wait_select_subsyst(rtFluxMapID_6ph_codegen_U,
      rtFluxMapID_6ph_codegen_Y);
    rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_IdentificationZero;

    /* Entry 'IdentificationZero': '<S1>:817' */
    /* '<S1>:817:3' FluxMapID_output.psi_array = [0;0;0;0]; */
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[0] = 0.0F;
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[1] = 0.0F;
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[2] = 0.0F;
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[3] = 0.0F;

    /* Outport: '<Root>/FluxMapID_FOC_output' */
    /* '<S1>:817:4' FluxMapID_FOC_output.resetIntegrator = false; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = false;

    /* '<S1>:817:5' FluxMapID_FOC_output.enableFOC_current = true; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_current = true;

    /* Entry Internal 'IdentificationZero': '<S1>:817' */
    /* Transition: '<S1>:835' */
    rtFluxMapID_6ph_codegen_DW->is_IdentificationZero = IN_Fluxmap;

    /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
     *  Inport: '<Root>/ActualValues'
     */
    Fluxmap_enter(&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
                  &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                  &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                  &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
                  &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
  }

  /* End of SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
}

/*
 * Function for Chart: '<Root>/FluxMapID_6ph_codegen'
 * function psi = flux(u, i, omega_el, Rs)
 */
static real32_T flux(real32_T u, real32_T i, real32_T omega_el, real32_T Rs)
{
  /* MATLAB Function 'flux': '<S1>:857' */
  /* '<S1>:857:2' psi = (u-Rs*i)/omega_el; */
  return (u - Rs * i) / omega_el;
}

/* Function for Chart: '<Root>/FluxMapID_6ph_codegen' */
static void AMMstate(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
                     ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
                     DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW)
{
  /* Inport: '<Root>/GlobalConfig' */
  /* During 'AMMstate': '<S1>:590' */
  /* '<S1>:667:1' sf_internal_predicateOutput = GlobalConfig.Reset==1 || GlobalConfig.FluxMapID==0.... */
  /* '<S1>:667:2' || GlobalConfig.enableParameterID==0; */
  if (rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Reset ||
      (!rtFluxMapID_6ph_codegen_U->GlobalConfig_out.FluxMapID) ||
      (!rtFluxMapID_6ph_codegen_U->GlobalConfig_out.enableParameterID)) {
    /* Transition: '<S1>:667' */
    /* '<S1>:667:3' enteredFluxMapID=boolean(0); */
    /* Exit Internal 'AMMstate': '<S1>:590' */
    switch (rtFluxMapID_6ph_codegen_DW->is_AMMstate) {
     case IN_IdentificationDQ:
      /* Exit Internal 'IdentificationDQ': '<S1>:717' */
      if (rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ == IN_Fluxmap) {
        /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/FluxMapIDConfig'
         */
        Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                     &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                     &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
        rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_NO_ACTIVE_CHILD_a;
      } else {
        rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_NO_ACTIVE_CHILD_a;
      }

      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_a;
      break;

     case IN_IdentificationXY:
      /* Exit Internal 'IdentificationXY': '<S1>:736' */
      if (rtFluxMapID_6ph_codegen_DW->is_IdentificationXY == IN_Fluxmap) {
        /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/FluxMapIDConfig'
         */
        Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                     &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                     &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
        rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_NO_ACTIVE_CHILD_a;
      } else {
        rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_NO_ACTIVE_CHILD_a;
      }

      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_a;
      break;

     case IN_IdentificationZero:
      /* Exit Internal 'IdentificationZero': '<S1>:817' */
      if (rtFluxMapID_6ph_codegen_DW->is_IdentificationZero == IN_Fluxmap) {
        /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/FluxMapIDConfig'
         */
        Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                     &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                     &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
        rtFluxMapID_6ph_codegen_DW->is_IdentificationZero = IN_NO_ACTIVE_CHILD_a;
      } else {
        rtFluxMapID_6ph_codegen_DW->is_IdentificationZero = IN_NO_ACTIVE_CHILD_a;
      }

      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_a;
      break;

     case IN_Wait_select_subsystem:
      exit_atomic_Wait_select_subsyst(rtFluxMapID_6ph_codegen_U,
        rtFluxMapID_6ph_codegen_Y);
      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_a;
      break;

     default:
      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_a;
      break;
    }

    /* Outport: '<Root>/finishedFluxMapID' */
    /* Exit 'AMMstate': '<S1>:590' */
    /* '<S1>:590:63' counter = uint32(1); */
    /* '<S1>:590:64' finishedFluxMapID=boolean(1); */
    rtFluxMapID_6ph_codegen_Y->finishedFluxMapID = true;

    /* Outport: '<Root>/enteredFluxMapID' */
    /* '<S1>:590:65' enteredFluxMapID = boolean(0); */
    rtFluxMapID_6ph_codegen_Y->enteredFluxMapID = false;
    rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:652' */
    /* wait for activation of */
    /* FluxMapID */
    /* '<S1>:652:5' init; */
    init(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
         rtFluxMapID_6ph_codegen_DW);
  } else {
    /* SystemInitialize for Inport: '<Root>/ActualValues' */
    /* '<S1>:590:8' FluxMapID_output.WindingTemp = ActualValues.average_winding_temp; */
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp =
      rtFluxMapID_6ph_codegen_U->ActualValues.average_winding_temp;

    /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
    /* '<S1>:590:9' if(FluxMapIDConfig.start_FM_ID==1) */
    if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
      /* '<S1>:590:10' if(FluxMapIDConfig.identR == 1) */
      if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identR) {
        /* Outport: '<Root>/FluxMapID_FOC_output' */
        /* '<S1>:590:11' if(FluxMapID_FOC_output.activeState ~= 403) */
        if (rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState != 403)
        {
          /* '<S1>:590:12' FluxMapID_output.R_s = identRes; */
          rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s = identRes
            (rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_DW);
        } else {
          /* '<S1>:590:13' else */
          /* '<S1>:590:14' fun_i_R_online = single(0); */
          rtFluxMapID_6ph_codegen_DW->fun_i_R_online = 0.0F;
        }

        /* '<S1>:590:16' if(FluxMapIDConfig.R_s_ref ~= 0.0 && FluxMapIDConfig.Temp_ref ~= 0.0) */
        if ((rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.R_s_ref != 0.0F) &&
            (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.Temp_ref != 0.0F)) {
          /* '<S1>:590:17' FluxMapID_output.WindingTemp = ((FluxMapID_output.R_s/FluxMapIDConfig.R_s_ref)-1).... */
          /* '<S1>:590:18'                 *254.453+FluxMapIDConfig.Temp_ref; */
          rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp =
            (rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s /
             rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.R_s_ref - 1.0F) *
            254.453F + rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.Temp_ref;

          /* . */
        }
      }

      /* '<S1>:590:21' if(FluxMapIDConfig.identR == 0) */
      if (!rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identR) {
        /* '<S1>:590:22' fun_i_R_online = single(0.0); */
        rtFluxMapID_6ph_codegen_DW->fun_i_R_online = 0.0F;

        /* '<S1>:590:23' FluxMapID_output.WindingTemp= FluxMapIDConfig.lower_meas_temp; */
        rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp =
          rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.lower_meas_temp;
      }

      /* '<S1>:590:25' switch(FluxMapIDConfig.ident_R_component) */
      switch (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.ident_R_component) {
       case 1U:
        /* Outport: '<Root>/FluxMapID_FOC_output' */
        /* '<S1>:590:26' case 1 */
        /* '<S1>:590:27' FluxMapID_FOC_output.i_dq_ref.d = FluxMapID_FOC_output.i_dq_ref.d+fun_i_R_online; */
        rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.d +=
          rtFluxMapID_6ph_codegen_DW->fun_i_R_online;

        /* SystemInitialize for Inport: '<Root>/ActualValues' */
        /* '<S1>:590:28' fun_actual_v=ActualValues.v_dq.d; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_v =
          rtFluxMapID_6ph_codegen_U->ActualValues.v_dq.d;

        /* '<S1>:590:29' fun_actual_i=ActualValues.i_dq.d; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_i =
          rtFluxMapID_6ph_codegen_U->ActualValues.i_dq.d;
        break;

       case 2U:
        /* Outport: '<Root>/FluxMapID_FOC_output' */
        /* '<S1>:590:30' case 2 */
        /* '<S1>:590:31' FluxMapID_FOC_output.i_dq_ref.q = FluxMapID_FOC_output.i_dq_ref.q+fun_i_R_online; */
        rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.q +=
          rtFluxMapID_6ph_codegen_DW->fun_i_R_online;

        /* SystemInitialize for Inport: '<Root>/ActualValues' */
        /* '<S1>:590:32' fun_actual_v=ActualValues.v_dq.q; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_v =
          rtFluxMapID_6ph_codegen_U->ActualValues.v_dq.q;

        /* '<S1>:590:33' fun_actual_i=ActualValues.i_dq.q; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_i =
          rtFluxMapID_6ph_codegen_U->ActualValues.i_dq.q;
        break;

       case 3U:
        /* Outport: '<Root>/FluxMapID_FOC_output' */
        /* '<S1>:590:34' case 3 */
        /* '<S1>:590:35' FluxMapID_FOC_output.i_xy_ref.d = FluxMapID_FOC_output.i_xy_ref.d+fun_i_R_online; */
        rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.d +=
          rtFluxMapID_6ph_codegen_DW->fun_i_R_online;

        /* SystemInitialize for Inport: '<Root>/ActualValues' */
        /* '<S1>:590:36' fun_actual_v=ActualValues.v_xy_rotating.d; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_v =
          rtFluxMapID_6ph_codegen_U->ActualValues.v_xy_rotating.d;

        /* '<S1>:590:37' fun_actual_i=ActualValues.i_xy_rotating.d; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_i =
          rtFluxMapID_6ph_codegen_U->ActualValues.i_xy_rotating.d;
        break;

       case 4U:
        /* Outport: '<Root>/FluxMapID_FOC_output' */
        /* '<S1>:590:38' case 4 */
        /* '<S1>:590:39' FluxMapID_FOC_output.i_xy_ref.d = FluxMapID_FOC_output.i_xy_ref.q+fun_i_R_online; */
        rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.d =
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.q +
          rtFluxMapID_6ph_codegen_DW->fun_i_R_online;

        /* SystemInitialize for Inport: '<Root>/ActualValues' */
        /* '<S1>:590:40' fun_actual_v=ActualValues.v_xy_rotating.q; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_v =
          rtFluxMapID_6ph_codegen_U->ActualValues.v_xy_rotating.q;

        /* '<S1>:590:41' fun_actual_i=ActualValues.i_xy_rotating.q; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_i =
          rtFluxMapID_6ph_codegen_U->ActualValues.i_xy_rotating.q;
        break;

       case 5U:
        /* Outport: '<Root>/FluxMapID_FOC_output' */
        /* '<S1>:590:42' case 5 */
        /* '<S1>:590:43' FluxMapID_FOC_output.i_zero_ref.d = FluxMapID_FOC_output.i_zero_ref.d+fun_i_R_online; */
        rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_zero_ref.d +=
          rtFluxMapID_6ph_codegen_DW->fun_i_R_online;

        /* SystemInitialize for Inport: '<Root>/ActualValues' */
        /* '<S1>:590:44' fun_actual_v=ActualValues.v_zero_rotating.d; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_v =
          rtFluxMapID_6ph_codegen_U->ActualValues.v_zero_rotating.d;

        /* '<S1>:590:45' fun_actual_i=ActualValues.i_zero_rotating.d; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_i =
          rtFluxMapID_6ph_codegen_U->ActualValues.i_zero_rotating.d;
        break;

       case 6U:
        /* Outport: '<Root>/FluxMapID_FOC_output' */
        /* '<S1>:590:46' case 6 */
        /* '<S1>:590:47' FluxMapID_FOC_output.i_zero_ref.q = FluxMapID_FOC_output.i_zero_ref.q+fun_i_R_online; */
        rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_zero_ref.q +=
          rtFluxMapID_6ph_codegen_DW->fun_i_R_online;

        /* SystemInitialize for Inport: '<Root>/ActualValues' */
        /* '<S1>:590:48' fun_actual_v=ActualValues.v_zero_rotating.q; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_v =
          rtFluxMapID_6ph_codegen_U->ActualValues.v_zero_rotating.q;

        /* '<S1>:590:49' fun_actual_i=ActualValues.i_zero_rotating.q; */
        rtFluxMapID_6ph_codegen_DW->fun_actual_i =
          rtFluxMapID_6ph_codegen_U->ActualValues.i_zero_rotating.q;
        break;
      }
    } else {
      /* '<S1>:590:51' else */
      /* '<S1>:590:52' FluxMapID_output.R_s = FluxMapIDConfig.R_s_ref*... */
      /* '<S1>:590:53'         (single(1)+TEMP_COEFFICIENT*(FluxMapID_output.WindingTemp - FluxMapIDConfig.Temp_ref)); */
      rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s =
        ((rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp -
          rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.Temp_ref) *
         TEMP_COEFFICIENT + 1.0F) *
        rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.R_s_ref;

      /* '<S1>:590:54' fun_i_R_online = single(0); */
      rtFluxMapID_6ph_codegen_DW->fun_i_R_online = 0.0F;

      /* Outport: '<Root>/FluxMapID_FOC_output' */
      /* '<S1>:590:55' FluxMapID_FOC_output.i_dq_ref.d = single(0); */
      rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.d = 0.0F;

      /* '<S1>:590:56' FluxMapID_FOC_output.i_dq_ref.q = single(0); */
      rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.q = 0.0F;

      /* '<S1>:590:57' FluxMapID_FOC_output.i_xy_ref.d = single(0); */
      rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.d = 0.0F;

      /* '<S1>:590:58' FluxMapID_FOC_output.i_xy_ref.q = single(0); */
      rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.q = 0.0F;

      /* '<S1>:590:59' FluxMapID_FOC_output.i_zero_ref.d = single(0); */
      rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_zero_ref.d = 0.0F;

      /* '<S1>:590:60' FluxMapID_FOC_output.i_zero_ref.q = single(0); */
      rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_zero_ref.q = 0.0F;
    }

    switch (rtFluxMapID_6ph_codegen_DW->is_AMMstate) {
     case IN_IdentificationDQ:
      {
        /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
        /* During 'IdentificationDQ': '<S1>:717' */
        /* '<S1>:866:1' sf_internal_predicateOutput = FluxMapIDConfig.start_FM_ID==0 && FluxMapIDConfig.selected_subsystem == 0; */
        if ((!rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) &&
            (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.selected_subsystem == 0))
        {
          /* Transition: '<S1>:866' */
          /* Exit Internal 'IdentificationDQ': '<S1>:717' */
          if (rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ == IN_Fluxmap) {
            /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
             *  Inport: '<Root>/ActualValues'
             */
            Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                         &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                         &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
            rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ =
              IN_NO_ACTIVE_CHILD_a;
          } else {
            rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ =
              IN_NO_ACTIVE_CHILD_a;
          }

          rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;

          /* Outport: '<Root>/FluxMapID_FOC_output' */
          /* Entry 'Wait_select_subsystem': '<S1>:762' */
          /* '<S1>:762:3' FluxMapID_FOC_output.activeState = uint16(400); */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 400U;

          /* '<S1>:762:4' FluxMapID_FOC_output.resetIntegrator = true; */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = true;

          /* '<S1>:762:5' i_q_ref_AMM = single(0); */
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

          /* '<S1>:762:6' i_d_ref_AMM = single(0); */
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;

          /* '<S1>:762:7' repetition_counter = uint32(0); */
          rtFluxMapID_6ph_codegen_DW->repetition_counter = 0U;

          /* '<S1>:762:8' reset_FOC_out; */
          reset_FOC_out(rtFluxMapID_6ph_codegen_Y);

          /* '<S1>:762:9' reset_logging_out; */
          reset_logging_out(rtFluxMapID_6ph_codegen_DW);
        } else {
          /* '<S1>:717:7' if(FluxMapIDConfig.start_FM_ID==true) */
          if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
            /* Outport: '<Root>/FluxMapID_FOC_output' */
            /* '<S1>:717:8' FluxMapID_FOC_output.i_dq_ref.d=i_d_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.d =
              rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM;

            /* '<S1>:717:9' FluxMapID_FOC_output.i_dq_ref.q=i_q_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.q =
              rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM;
          }

          /* '<S1>:717:11' if(finished_calculation) */
          if (rtFluxMapID_6ph_codegen_DW->finished_calculation_b) {
            /* '<S1>:717:12' FluxMapID_output.psi_array(1)=mean_currents.d; */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[0] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_mb.d;

            /* '<S1>:717:13' FluxMapID_output.psi_array(2)=mean_currents.q; */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[1] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_mb.q;

            /* '<S1>:717:14' FluxMapID_output.psi_array(3)=flux(mean_voltages.q, mean_currents.q,... */
            /* '<S1>:717:15'         mean_omega_el, FluxMapID_output.R_s); */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[2] = flux
              (rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q,
               rtFluxMapID_6ph_codegen_DW->mean_currents_mb.q,
               rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
               rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s);

            /* '<S1>:717:16' FluxMapID_output.psi_array(4)=single(-1)*flux(mean_voltages.d, mean_currents.d,... */
            /* '<S1>:717:17'         mean_omega_el, FluxMapID_output.R_s); */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[3] = -flux
              (rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d,
               rtFluxMapID_6ph_codegen_DW->mean_currents_mb.d,
               rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
               rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s);

            /* '<S1>:717:18' FluxMapID_output.array_index = repetition_counter; */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.array_index =
              rtFluxMapID_6ph_codegen_DW->repetition_counter;
          }

          if (rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ == IN_Fluxmap) {
            uint32_T exitPortIndex;

            /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
             *  Inport: '<Root>/ActualValues'
             */
            /* During 'Fluxmap': '<S1>:704' */
            Fluxmap_during
              (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
               &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
               &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
               &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
               rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c,
               &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
               &rtFluxMapID_6ph_codegen_U->ActualValues.v_dq,
               rtFluxMapID_6ph_codegen_U->ActualValues.omega_el,
               &rtFluxMapID_6ph_codegen_DW->mean_voltages_c,
               &rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
               &rtFluxMapID_6ph_codegen_DW->mean_currents_mb,
               &rtFluxMapID_6ph_codegen_DW->repetition_counter,
               &rtFluxMapID_6ph_codegen_U->ActualValues.i_dq,
               &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
               &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
            exitPortIndex = Fluxmap_getExitPortIndex
              (&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
            if (exitPortIndex == 2U) {
              /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
               *  Inport: '<Root>/ActualValues'
               */
              /* Transition: '<S1>:877' */
              Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                           &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                           &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                           &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                           &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
              rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_waitState;

              /* Outport: '<Root>/FluxMapID_FOC_output' */
              /* Entry 'waitState': '<S1>:878' */
              /* '<S1>:878:3' FluxMapID_FOC_output.activeState = uint16(405); */
              rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 405U;
            }
          } else {
            /* During 'waitState': '<S1>:878' */
          }
        }
      }
      break;

     case IN_IdentificationXY:
      {
        /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
        /* During 'IdentificationXY': '<S1>:736' */
        /* '<S1>:867:1' sf_internal_predicateOutput = FluxMapIDConfig.start_FM_ID==0 && FluxMapIDConfig.selected_subsystem == 0; */
        if ((!rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) &&
            (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.selected_subsystem == 0))
        {
          /* Transition: '<S1>:867' */
          /* Exit Internal 'IdentificationXY': '<S1>:736' */
          if (rtFluxMapID_6ph_codegen_DW->is_IdentificationXY == IN_Fluxmap) {
            /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
             *  Inport: '<Root>/ActualValues'
             */
            Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                         &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                         &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
            rtFluxMapID_6ph_codegen_DW->is_IdentificationXY =
              IN_NO_ACTIVE_CHILD_a;
          } else {
            rtFluxMapID_6ph_codegen_DW->is_IdentificationXY =
              IN_NO_ACTIVE_CHILD_a;
          }

          rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;

          /* Outport: '<Root>/FluxMapID_FOC_output' */
          /* Entry 'Wait_select_subsystem': '<S1>:762' */
          /* '<S1>:762:3' FluxMapID_FOC_output.activeState = uint16(400); */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 400U;

          /* '<S1>:762:4' FluxMapID_FOC_output.resetIntegrator = true; */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = true;

          /* '<S1>:762:5' i_q_ref_AMM = single(0); */
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

          /* '<S1>:762:6' i_d_ref_AMM = single(0); */
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;

          /* '<S1>:762:7' repetition_counter = uint32(0); */
          rtFluxMapID_6ph_codegen_DW->repetition_counter = 0U;

          /* '<S1>:762:8' reset_FOC_out; */
          reset_FOC_out(rtFluxMapID_6ph_codegen_Y);

          /* '<S1>:762:9' reset_logging_out; */
          reset_logging_out(rtFluxMapID_6ph_codegen_DW);
        } else {
          /* '<S1>:736:7' if(FluxMapIDConfig.start_FM_ID==true) */
          if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
            /* Outport: '<Root>/FluxMapID_FOC_output' */
            /* '<S1>:736:8' FluxMapID_FOC_output.i_xy_ref.d=i_d_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.d =
              rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM;

            /* '<S1>:736:9' FluxMapID_FOC_output.i_xy_ref.q=i_q_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.q =
              rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM;
          }

          /* '<S1>:736:11' if(finished_calculation) */
          if (rtFluxMapID_6ph_codegen_DW->finished_calculation_b) {
            /* '<S1>:736:12' FluxMapID_output.psi_array(1)=mean_currents.d; */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[0] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_mb.d;

            /* '<S1>:736:13' FluxMapID_output.psi_array(2)=mean_currents.q; */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[1] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_mb.q;

            /* '<S1>:736:14' FluxMapID_output.psi_array(3)=single(-1)*flux(mean_voltages.q, mean_currents.q, ... */
            /* '<S1>:736:15'         mean_omega_el, FluxMapID_output.R_s); */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[2] = -flux
              (rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q,
               rtFluxMapID_6ph_codegen_DW->mean_currents_mb.q,
               rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
               rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s);

            /* '<S1>:736:16' FluxMapID_output.psi_array(4)=flux(mean_voltages.d, mean_currents.d, ... */
            /* '<S1>:736:17'         mean_omega_el, FluxMapID_output.R_s); */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[3] = flux
              (rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d,
               rtFluxMapID_6ph_codegen_DW->mean_currents_mb.d,
               rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
               rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s);

            /* '<S1>:736:18' FluxMapID_output.array_index = repetition_counter; */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.array_index =
              rtFluxMapID_6ph_codegen_DW->repetition_counter;
          }

          if (rtFluxMapID_6ph_codegen_DW->is_IdentificationXY == IN_Fluxmap) {
            uint32_T exitPortIndex;

            /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
             *  Inport: '<Root>/ActualValues'
             */
            /* During 'Fluxmap': '<S1>:748' */
            Fluxmap_during
              (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
               &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
               &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
               &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
               rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c,
               &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
               &rtFluxMapID_6ph_codegen_U->ActualValues.v_xy_rotating,
               rtFluxMapID_6ph_codegen_U->ActualValues.omega_el,
               &rtFluxMapID_6ph_codegen_DW->mean_voltages_c,
               &rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
               &rtFluxMapID_6ph_codegen_DW->mean_currents_mb,
               &rtFluxMapID_6ph_codegen_DW->repetition_counter,
               &rtFluxMapID_6ph_codegen_U->ActualValues.i_xy_rotating,
               &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
               &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
            exitPortIndex = Fluxmap_getExitPortIndex
              (&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
            if (exitPortIndex == 2U) {
              /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
               *  Inport: '<Root>/ActualValues'
               */
              /* Transition: '<S1>:882' */
              Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                           &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                           &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                           &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                           &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
              rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_waitState;

              /* Outport: '<Root>/FluxMapID_FOC_output' */
              /* Entry 'waitState': '<S1>:881' */
              /* '<S1>:881:3' FluxMapID_FOC_output.activeState = uint16(405); */
              rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 405U;
            }
          } else {
            /* During 'waitState': '<S1>:881' */
          }
        }
      }
      break;

     case IN_IdentificationZero:
      {
        /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
        /* During 'IdentificationZero': '<S1>:817' */
        /* '<S1>:865:1' sf_internal_predicateOutput = FluxMapIDConfig.start_FM_ID==0 && FluxMapIDConfig.selected_subsystem == 0; */
        if ((!rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) &&
            (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.selected_subsystem == 0))
        {
          /* Transition: '<S1>:865' */
          /* Exit Internal 'IdentificationZero': '<S1>:817' */
          if (rtFluxMapID_6ph_codegen_DW->is_IdentificationZero == IN_Fluxmap) {
            /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
             *  Inport: '<Root>/ActualValues'
             */
            Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                         &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                         &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
            rtFluxMapID_6ph_codegen_DW->is_IdentificationZero =
              IN_NO_ACTIVE_CHILD_a;
          } else {
            rtFluxMapID_6ph_codegen_DW->is_IdentificationZero =
              IN_NO_ACTIVE_CHILD_a;
          }

          rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;

          /* Outport: '<Root>/FluxMapID_FOC_output' */
          /* Entry 'Wait_select_subsystem': '<S1>:762' */
          /* '<S1>:762:3' FluxMapID_FOC_output.activeState = uint16(400); */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 400U;

          /* '<S1>:762:4' FluxMapID_FOC_output.resetIntegrator = true; */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = true;

          /* '<S1>:762:5' i_q_ref_AMM = single(0); */
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

          /* '<S1>:762:6' i_d_ref_AMM = single(0); */
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;

          /* '<S1>:762:7' repetition_counter = uint32(0); */
          rtFluxMapID_6ph_codegen_DW->repetition_counter = 0U;

          /* '<S1>:762:8' reset_FOC_out; */
          reset_FOC_out(rtFluxMapID_6ph_codegen_Y);

          /* '<S1>:762:9' reset_logging_out; */
          reset_logging_out(rtFluxMapID_6ph_codegen_DW);
        } else {
          /* '<S1>:817:7' if(FluxMapIDConfig.start_FM_ID==true) */
          if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
            /* Outport: '<Root>/FluxMapID_FOC_output' */
            /* '<S1>:817:8' FluxMapID_FOC_output.i_zero_ref.d=i_d_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_zero_ref.d =
              rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM;

            /* '<S1>:817:9' FluxMapID_FOC_output.i_zero_ref.q=i_q_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_zero_ref.q =
              rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM;
          }

          /* '<S1>:817:11' if(finished_calculation) */
          if (rtFluxMapID_6ph_codegen_DW->finished_calculation_b) {
            /* '<S1>:817:12' FluxMapID_output.psi_array(1)=mean_currents.d; */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[0] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_mb.d;

            /* '<S1>:817:13' FluxMapID_output.psi_array(2)=mean_currents.q; */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[1] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_mb.q;

            /* '<S1>:817:14' FluxMapID_output.psi_array(3)=flux(mean_voltages.q, mean_currents.q, ... */
            /* '<S1>:817:15'         mean_omega_el, FluxMapID_output.R_s)/single(3); */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[2] = flux
              (rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q,
               rtFluxMapID_6ph_codegen_DW->mean_currents_mb.q,
               rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
               rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s) / 3.0F;

            /* '<S1>:817:16' FluxMapID_output.psi_array(4)=single(-1)*flux(mean_voltages.d, mean_currents.d, ... */
            /* '<S1>:817:17'         mean_omega_el, FluxMapID_output.R_s)/single(3); */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[3] = -flux
              (rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d,
               rtFluxMapID_6ph_codegen_DW->mean_currents_mb.d,
               rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
               rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s) / 3.0F;

            /* '<S1>:817:18' FluxMapID_output.array_index = repetition_counter; */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.array_index =
              rtFluxMapID_6ph_codegen_DW->repetition_counter;
          }

          if (rtFluxMapID_6ph_codegen_DW->is_IdentificationZero == IN_Fluxmap) {
            uint32_T exitPortIndex;

            /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
             *  Inport: '<Root>/ActualValues'
             */
            /* During 'Fluxmap': '<S1>:830' */
            Fluxmap_during
              (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
               &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
               &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
               &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
               rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c,
               &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
               &rtFluxMapID_6ph_codegen_U->ActualValues.v_zero_rotating,
               rtFluxMapID_6ph_codegen_U->ActualValues.omega_el,
               &rtFluxMapID_6ph_codegen_DW->mean_voltages_c,
               &rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
               &rtFluxMapID_6ph_codegen_DW->mean_currents_mb,
               &rtFluxMapID_6ph_codegen_DW->repetition_counter,
               &rtFluxMapID_6ph_codegen_U->ActualValues.i_zero_rotating,
               &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
               &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
            exitPortIndex = Fluxmap_getExitPortIndex
              (&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
            if (exitPortIndex == 2U) {
              /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
               *  Inport: '<Root>/ActualValues'
               */
              /* Transition: '<S1>:884' */
              Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                           &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                           &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                           &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                           &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
              rtFluxMapID_6ph_codegen_DW->is_IdentificationZero = IN_waitState;

              /* Outport: '<Root>/FluxMapID_FOC_output' */
              /* Entry 'waitState': '<S1>:883' */
              /* '<S1>:883:3' FluxMapID_FOC_output.activeState = uint16(405); */
              rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 405U;
            }
          } else {
            /* During 'waitState': '<S1>:883' */
          }
        }
      }
      break;

     default:
      Wait_select_subsystem(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
                            rtFluxMapID_6ph_codegen_DW);
      break;
    }
  }

  /* End of Inport: '<Root>/GlobalConfig' */
}

/* Model step function */
void FluxMapID_6ph_codegen_step(RT_MODEL_FluxMapID_6ph_codege_t *const
  rtFluxMapID_6ph_codegen_M)
{
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW =
    rtFluxMapID_6ph_codegen_M->dwork;
  ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U =
    (ExtU_FluxMapID_6ph_codegen_t *) rtFluxMapID_6ph_codegen_M->inputs;
  ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y =
    (ExtY_FluxMapID_6ph_codegen_t *) rtFluxMapID_6ph_codegen_M->outputs;
  int32_T i;

  /* Chart: '<Root>/FluxMapID_6ph_codegen' incorporates:
   *  Inport: '<Root>/ControlFlags'
   *  Inport: '<Root>/FluxMapIDConfig'
   *  Inport: '<Root>/GlobalConfig'
   *  Outport: '<Root>/FluxMapID_FOC_output'
   */
  /* Gateway: FluxMapID_6ph_codegen */
  /* During: FluxMapID_6ph_codegen */
  if (rtFluxMapID_6ph_codegen_DW->is_active_c16_FluxMapID_6ph_cod == 0U) {
    /* Entry: FluxMapID_6ph_codegen */
    rtFluxMapID_6ph_codegen_DW->is_active_c16_FluxMapID_6ph_cod = 1U;

    /* Entry Internal: FluxMapID_6ph_codegen */
    /* Transition: '<S1>:597' */
    rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:652' */
    /* wait for activation of */
    /* FluxMapID */
    /* '<S1>:652:5' init; */
    init(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
         rtFluxMapID_6ph_codegen_DW);
  } else if (rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen ==
             IN_AMMstate) {
    AMMstate(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
             rtFluxMapID_6ph_codegen_DW);

    /* During 'Waiting': '<S1>:652' */
    /* '<S1>:656:1' sf_internal_predicateOutput = ControlFlags.startFluxMapID==1 && .... */
    /* '<S1>:656:2' GlobalConfig.Reset==0 && GlobalConfig.ACCEPT==1; */
    /* . */
  } else if (rtFluxMapID_6ph_codegen_U->ControlFlags.startFluxMapID &&
             (!rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Reset) &&
             rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S1>:656' */
    rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_AMMstate;

    /* Entry 'AMMstate': '<S1>:590' */
    rtFluxMapID_6ph_codegen_DW->fun_i_R_online = 0.0F;
    rtFluxMapID_6ph_codegen_DW->fun_counter = 0U;
    rtFluxMapID_6ph_codegen_DW->fun_v1_counter = 0.0F;
    rtFluxMapID_6ph_codegen_DW->fun_v2_counter = 0.0F;
    rtFluxMapID_6ph_codegen_DW->fun_i2_counter = 0.0F;
    rtFluxMapID_6ph_codegen_DW->fun_i1_counter = 0.0F;
    rtFluxMapID_6ph_codegen_DW->fun_actual_v = 0.0F;
    rtFluxMapID_6ph_codegen_DW->fun_actual_i = 0.0F;

    /* Outport: '<Root>/finishedFluxMapID' */
    /* '<S1>:590:4' finishedFluxMapID=false; */
    rtFluxMapID_6ph_codegen_Y->finishedFluxMapID = false;

    /* Outport: '<Root>/enteredFluxMapID' */
    /* '<S1>:590:5' enteredFluxMapID = true; */
    rtFluxMapID_6ph_codegen_Y->enteredFluxMapID = true;

    /* '<S1>:590:6' fun_R_s_array(:)=FluxMapIDConfig.R_s_ref; */
    for (i = 0; i < 20; i++) {
      rtFluxMapID_6ph_codegen_DW->fun_R_s_array[i] =
        rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.R_s_ref;
    }

    /* Entry Internal 'AMMstate': '<S1>:590' */
    /* Transition: '<S1>:763' */
    rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;

    /* Entry 'Wait_select_subsystem': '<S1>:762' */
    /* '<S1>:762:3' FluxMapID_FOC_output.activeState = uint16(400); */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 400U;

    /* '<S1>:762:4' FluxMapID_FOC_output.resetIntegrator = true; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = true;

    /* '<S1>:762:5' i_q_ref_AMM = single(0); */
    rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

    /* '<S1>:762:6' i_d_ref_AMM = single(0); */
    rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;

    /* '<S1>:762:7' repetition_counter = uint32(0); */
    rtFluxMapID_6ph_codegen_DW->repetition_counter = 0U;

    /* '<S1>:762:8' reset_FOC_out; */
    reset_FOC_out(rtFluxMapID_6ph_codegen_Y);

    /* '<S1>:762:9' reset_logging_out; */
    reset_logging_out(rtFluxMapID_6ph_codegen_DW);

    /* '<S1>:680:1' sf_internal_predicateOutput = GlobalConfig.Reset==1; */
  } else if (rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Reset) {
    /* Outport: '<Root>/finishedFluxMapID' */
    /* Transition: '<S1>:680' */
    /* '<S1>:680:1' finishedFluxMapID=boolean(0); */
    rtFluxMapID_6ph_codegen_Y->finishedFluxMapID = false;

    /* Outport: '<Root>/enteredFluxMapID' */
    /* '<S1>:680:2' enteredFluxMapID=boolean(0); */
    rtFluxMapID_6ph_codegen_Y->enteredFluxMapID = false;
    rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:652' */
    /* wait for activation of */
    /* FluxMapID */
    /* '<S1>:652:5' init; */
    init(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
         rtFluxMapID_6ph_codegen_DW);
  }

  /* End of Chart: '<Root>/FluxMapID_6ph_codegen' */

  /* Outport: '<Root>/FluxMapID_output' */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_output =
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output;
}

/* Model initialize function */
void FluxMapID_6ph_codegen_initialize(RT_MODEL_FluxMapID_6ph_codege_t *const
  rtFluxMapID_6ph_codegen_M)
{
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW =
    rtFluxMapID_6ph_codegen_M->dwork;
  ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U =
    (ExtU_FluxMapID_6ph_codegen_t *) rtFluxMapID_6ph_codegen_M->inputs;
  ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y =
    (ExtY_FluxMapID_6ph_codegen_t *) rtFluxMapID_6ph_codegen_M->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtFluxMapID_6ph_codegen_DW, 0,
                sizeof(DW_FluxMapID_6ph_codegen_t));

  /* external inputs */
  (void)memset(rtFluxMapID_6ph_codegen_U, 0, sizeof(ExtU_FluxMapID_6ph_codegen_t));

  /* external outputs */
  (void)memset(rtFluxMapID_6ph_codegen_Y, 0, sizeof(ExtY_FluxMapID_6ph_codegen_t));

  /* SystemInitialize for Chart: '<Root>/FluxMapID_6ph_codegen' incorporates:
   *  Inport: '<Root>/ActualValues'
   *  Inport: '<Root>/FluxMapIDConfig'
   *  Outport: '<Root>/FluxMapID_FOC_output'
   */
  Fluxmap_init(&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
  Fluxmap_init(&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
  Fluxmap_init(&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
  rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_a;
  rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_NO_ACTIVE_CHILD_a;
  rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_NO_ACTIVE_CHILD_a;
  rtFluxMapID_6ph_codegen_DW->is_IdentificationZero = IN_NO_ACTIVE_CHILD_a;
  rtFluxMapID_6ph_codegen_DW->is_active_c16_FluxMapID_6ph_cod = 0U;
  rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen =
    IN_NO_ACTIVE_CHILD_a;
  rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c = 0U;
  rtFluxMapID_6ph_codegen_DW->mean_omega_el_k = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_voltages_c.zero = 0.0F;
  rtFluxMapID_6ph_codegen_DW->finished_calculation_b = false;
  rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;
  rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_currents_mb.d = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_currents_mb.q = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_currents_mb.zero = 0.0F;
  rtFluxMapID_6ph_codegen_DW->repetition_counter = 0U;
  rtFluxMapID_6ph_codegen_DW->fun_i_R_online = 0.0F;
  rtFluxMapID_6ph_codegen_DW->fun_counter = 0U;
  rtFluxMapID_6ph_codegen_DW->fun_v1_counter = 0.0F;
  rtFluxMapID_6ph_codegen_DW->fun_v2_counter = 0.0F;
  rtFluxMapID_6ph_codegen_DW->fun_i2_counter = 0.0F;
  rtFluxMapID_6ph_codegen_DW->fun_i1_counter = 0.0F;
  memset(&rtFluxMapID_6ph_codegen_DW->fun_R_s_array[0], 0, 20U * sizeof(real32_T));
  rtFluxMapID_6ph_codegen_DW->fun_actual_v = 0.0F;
  rtFluxMapID_6ph_codegen_DW->fun_actual_i = 0.0F;

  /* SystemInitialize for Outport: '<Root>/finishedFluxMapID' incorporates:
   *  Chart: '<Root>/FluxMapID_6ph_codegen'
   */
  rtFluxMapID_6ph_codegen_Y->finishedFluxMapID = false;

  /* SystemInitialize for Outport: '<Root>/enteredFluxMapID' incorporates:
   *  Chart: '<Root>/FluxMapID_6ph_codegen'
   */
  rtFluxMapID_6ph_codegen_Y->enteredFluxMapID = false;

  /* SystemInitialize for Chart: '<Root>/FluxMapID_6ph_codegen' incorporates:
   *  Outport: '<Root>/FluxMapID_FOC_output'
   */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.d = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.q = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.zero = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 0U;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.n_ref_FOC = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_speed = false;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_current = false;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = false;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Kp_id_out = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Kp_iq_out = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Kp_n_out = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Ki_id_out = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Ki_iq_out = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Ki_n_out = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.d = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.q = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_xy_ref.zero = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_zero_ref.d = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_zero_ref.q = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_zero_ref.zero = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resonant_subsystem = 0U;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.PI_subsystem = 0U;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.setpoint_filter = 0U;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.external_Measurement_Flag = false;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s = 0.0F;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp = 0.0F;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[0] = 0.0F;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[1] = 0.0F;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[2] = 0.0F;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.psi_array[3] = 0.0F;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.array_index = 0U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
#endif