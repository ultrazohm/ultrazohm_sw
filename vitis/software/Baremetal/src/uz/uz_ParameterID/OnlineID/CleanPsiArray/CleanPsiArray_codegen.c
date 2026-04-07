/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CleanPsiArray.c
 *
 * Code generated for Simulink model 'CleanPsiArray'.
 *
 * Model version                  : 2.381
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Jan 11 13:27:09 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#include "CleanPsiArray_codegen.h"
#include "../../../uz_global_configuration.h"
#if UZ_PARAMETERID_MAX_INSTANCES > 0U



/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

/* Model step function */
void CleanPsiArray_step(RT_MODEL_CleanPsiArray_t *const rtCleanPsiArray_M)
{
  DW_CleanPsiArray_t *rtCleanPsiArray_DW = rtCleanPsiArray_M->dwork;
  ExtU_CleanPsiArray_t *rtCleanPsiArray_U = (ExtU_CleanPsiArray_t *)
    rtCleanPsiArray_M->inputs;
  ExtY_CleanPsiArray_t *rtCleanPsiArray_Y = (ExtY_CleanPsiArray_t *)
    rtCleanPsiArray_M->outputs;
  int32_T b_a_tmp;
  int32_T b_a_tmp_0;
  int32_T eta_count;
  int32_T i;
  int32_T i_0;
  int32_T t;
  int32_T tmp;
  real32_T a;
  real32_T a_tmp;
  real32_T a_tmp_0;
  real32_T b_a;
  real32_T clean_curr_count;
  boolean_T exitg1;

  /* Outport: '<Root>/n_flux_points' incorporates:
   *  MATLAB Function: '<Root>/CleanPsiArray'
   */
  /*  Author Philipp Gebhardt */
  /*  Oktober 2019 */
  /* MATLAB Function 'CleanPsiArray': '<S1>:1' */
  /* This function is cleaning the array storing the measurement values, which always consits of a d-q-current combination a winding temperature and a speed value such as a d-q-flux combination */
  /* The function is searching for measuring pairs which are closer than eta_c to their neighbours. In this case it is averaging these similar pairs to avoid measuring values storing the same information.  */
  /* This is essential for calculating a wide ranging flux maps out of this array. */
  /* Furthermore there is an output n_flux_points giving back the amount of independent measuring pairs */
  /* Initialising Outputs */
  /* '<S1>:1:12' n_flux_points=single(1); */
  rtCleanPsiArray_Y->n_flux_points = 1.0F;

  /* MATLAB Function: '<Root>/CleanPsiArray' incorporates:
   *  Inport: '<Root>/OnlineID_output'
   */
  /* '<S1>:1:13' psi_array_out=single(zeros(6,100)); */
  for (i = 0; i < 600; i++) {
    rtCleanPsiArray_DW->OnlineID_output_psi_array[i] =
      rtCleanPsiArray_U->OnlineID_output.psi_array[i];
    rtCleanPsiArray_DW->psi_array_out[i] = 0.0F;
  }

  /* '<S1>:1:14' clean_curr_count=single(0); */
  clean_curr_count = 0.0F;

  /* Outport: '<Root>/array_cleaned_flag' incorporates:
   *  MATLAB Function: '<Root>/CleanPsiArray'
   */
  /* '<S1>:1:15' array_cleaned_flag=boolean(0); */
  rtCleanPsiArray_Y->array_cleaned_flag = false;

  /* MATLAB Function: '<Root>/CleanPsiArray' incorporates:
   *  Inport: '<Root>/OnlineID_output'
   */
  /* '<S1>:1:17' if(OnlineID_output.clean_array == 1) */
  if (rtCleanPsiArray_U->OnlineID_output.clean_array) {
    /*  Searching for similar Datapairs */
    /* '<S1>:1:19' for(k=single(1):single(length(OnlineID_output.psi_array(1,:))) */
    for (i = 0; i < 100; i++) {
      /* '<S1>:1:20' eta_count=0; */
      eta_count = 0;

      /* '<S1>:1:22' if (OnlineID_output.psi_array(3,k)~=0) */
      tmp = 6 * i + 2;
      if (rtCleanPsiArray_DW->OnlineID_output_psi_array[tmp] != 0.0F) {
        /* '<S1>:1:23' for(t=single(1):single(length(OnlineID_output.psi_array(1,:))) */
        t = 0;
        exitg1 = false;
        while ((!exitg1) && (t < 100)) {
          /* '<S1>:1:24' if (OnlineID_output.psi_array(3,t)~=0) */
          i_0 = 6 * t + 2;
          if ((rtCleanPsiArray_DW->OnlineID_output_psi_array[i_0] != 0.0F) && (i
               < t)) {
            /* '<S1>:1:25' if(k<t) */
            /* '<S1>:1:26' if( (    (OnlineID_output.psi_array(1,k)-OnlineID_output.psi_array(1,t))^2  +... */
            /* '<S1>:1:27'                         (OnlineID_output.psi_array(2,k)-OnlineID_output.psi_array(2,t))^2     )^0.5 < eta_c ) */
            a_tmp = rtCleanPsiArray_DW->OnlineID_output_psi_array[6 * i];
            a_tmp_0 = rtCleanPsiArray_DW->OnlineID_output_psi_array[6 * t];
            a = a_tmp - a_tmp_0;
            b_a_tmp = 6 * i + 1;
            b_a_tmp_0 = 6 * t + 1;
            b_a = rtCleanPsiArray_DW->OnlineID_output_psi_array[b_a_tmp] -
              rtCleanPsiArray_DW->OnlineID_output_psi_array[b_a_tmp_0];
            if (sqrtf(a * a + b_a * b_a) < rtCleanPsiArray_U->eta_c) {
              /* Averaging Datapairs if they are to close to each other */
              /* '<S1>:1:30' OnlineID_output.psi_array(1,t)=(OnlineID_output.psi_array(1,k)+OnlineID_output.psi_array(1,t))*0.5; */
              rtCleanPsiArray_DW->OnlineID_output_psi_array[6 * t] = (a_tmp +
                a_tmp_0) * 0.5F;

              /* '<S1>:1:31' OnlineID_output.psi_array(2,t)=(OnlineID_output.psi_array(2,k)+OnlineID_output.psi_array(2,t))*0.5; */
              rtCleanPsiArray_DW->OnlineID_output_psi_array[b_a_tmp_0] =
                (rtCleanPsiArray_DW->OnlineID_output_psi_array[b_a_tmp] +
                 rtCleanPsiArray_DW->OnlineID_output_psi_array[b_a_tmp_0]) *
                0.5F;

              /* '<S1>:1:32' OnlineID_output.psi_array(3,t)=(OnlineID_output.psi_array(3,k)+OnlineID_output.psi_array(3,t))*0.5; */
              rtCleanPsiArray_DW->OnlineID_output_psi_array[i_0] =
                (rtCleanPsiArray_DW->OnlineID_output_psi_array[tmp] +
                 rtCleanPsiArray_DW->OnlineID_output_psi_array[i_0]) * 0.5F;

              /* '<S1>:1:33' OnlineID_output.psi_array(4,t)=(OnlineID_output.psi_array(4,k)+OnlineID_output.psi_array(4,t))*0.5; */
              eta_count = 6 * t + 3;
              rtCleanPsiArray_DW->OnlineID_output_psi_array[eta_count] =
                (rtCleanPsiArray_DW->OnlineID_output_psi_array[6 * i + 3] +
                 rtCleanPsiArray_DW->OnlineID_output_psi_array[eta_count]) *
                0.5F;

              /* '<S1>:1:34' OnlineID_output.psi_array(5,t)=(OnlineID_output.psi_array(5,k)+OnlineID_output.psi_array(5,t))*0.5; */
              eta_count = 6 * t + 4;
              rtCleanPsiArray_DW->OnlineID_output_psi_array[eta_count] =
                (rtCleanPsiArray_DW->OnlineID_output_psi_array[6 * i + 4] +
                 rtCleanPsiArray_DW->OnlineID_output_psi_array[eta_count]) *
                0.5F;

              /* '<S1>:1:35' OnlineID_output.psi_array(6,t)=(OnlineID_output.psi_array(6,k)+OnlineID_output.psi_array(6,t))*0.5; */
              eta_count = 6 * t + 5;
              rtCleanPsiArray_DW->OnlineID_output_psi_array[eta_count] =
                (rtCleanPsiArray_DW->OnlineID_output_psi_array[6 * i + 5] +
                 rtCleanPsiArray_DW->OnlineID_output_psi_array[eta_count]) *
                0.5F;

              /* '<S1>:1:36' OnlineID_output.psi_array(1:6,k)=0; */
              for (i_0 = 0; i_0 < 6; i_0++) {
                rtCleanPsiArray_DW->OnlineID_output_psi_array[i_0 + 6 * i] =
                  0.0F;
              }

              /* '<S1>:1:37' eta_count=1; */
              eta_count = 1;
            }
          }

          /* '<S1>:1:42' if eta_count==1 */
          if (eta_count == 1) {
            exitg1 = true;
          } else {
            t++;
          }
        }

        /* '<S1>:1:46' if(eta_count==0) */
        if (eta_count == 0) {
          /* Accept values if there is enough distance between them */
          /* '<S1>:1:48' clean_curr_count=clean_curr_count+1; */
          clean_curr_count++;

          /* '<S1>:1:49' psi_array_out(1,clean_curr_count)=OnlineID_output.psi_array(1,k); */
          t = 6 * ((int32_T)clean_curr_count - 1);
          rtCleanPsiArray_DW->psi_array_out[t] =
            rtCleanPsiArray_DW->OnlineID_output_psi_array[6 * i];

          /* '<S1>:1:50' psi_array_out(2,clean_curr_count)=OnlineID_output.psi_array(2,k); */
          rtCleanPsiArray_DW->psi_array_out[t + 1] =
            rtCleanPsiArray_DW->OnlineID_output_psi_array[6 * i + 1];

          /* '<S1>:1:51' psi_array_out(3,clean_curr_count)=OnlineID_output.psi_array(3,k); */
          rtCleanPsiArray_DW->psi_array_out[t + 2] =
            rtCleanPsiArray_DW->OnlineID_output_psi_array[tmp];

          /* '<S1>:1:52' psi_array_out(4,clean_curr_count)=OnlineID_output.psi_array(4,k); */
          rtCleanPsiArray_DW->psi_array_out[t + 3] =
            rtCleanPsiArray_DW->OnlineID_output_psi_array[6 * i + 3];

          /* '<S1>:1:53' psi_array_out(5,clean_curr_count)=OnlineID_output.psi_array(5,k); */
          rtCleanPsiArray_DW->psi_array_out[t + 4] =
            rtCleanPsiArray_DW->OnlineID_output_psi_array[6 * i + 4];

          /* '<S1>:1:54' psi_array_out(6,clean_curr_count)=OnlineID_output.psi_array(6,k); */
          rtCleanPsiArray_DW->psi_array_out[t + 5] =
            rtCleanPsiArray_DW->OnlineID_output_psi_array[6 * i + 5];
        }
      }
    }

    /*  Count flux points */
    /* '<S1>:1:60' for(k=single(1):single(length(psi_array_out(1,:))) */
    for (i = 0; i < 100; i++) {
      /* '<S1>:1:61' if(psi_array_out(1,k)~=0||psi_array_out(2,k)~=0||psi_array_out(3,k)~=0) */
      if (rtCleanPsiArray_DW->psi_array_out[6 * i] != 0.0F) {
        /* Outport: '<Root>/n_flux_points' */
        /* '<S1>:1:62' n_flux_points=k; */
        rtCleanPsiArray_Y->n_flux_points = (real32_T)i + 1.0F;
      } else if (rtCleanPsiArray_DW->psi_array_out[6 * i + 1] != 0.0F) {
        /* Outport: '<Root>/n_flux_points' */
        /* '<S1>:1:62' n_flux_points=k; */
        rtCleanPsiArray_Y->n_flux_points = (real32_T)i + 1.0F;
      } else if (rtCleanPsiArray_DW->psi_array_out[6 * i + 2] != 0.0F) {
        /* Outport: '<Root>/n_flux_points' */
        /* '<S1>:1:62' n_flux_points=k; */
        rtCleanPsiArray_Y->n_flux_points = (real32_T)i + 1.0F;
      }
    }

    /* Outport: '<Root>/array_cleaned_flag' */
    /* '<S1>:1:66' array_cleaned_flag=boolean(1); */
    rtCleanPsiArray_Y->array_cleaned_flag = true;
  }

  /* Outport: '<Root>/psi_array_out' */
  memcpy(&rtCleanPsiArray_Y->psi_array_out[0],
         &rtCleanPsiArray_DW->psi_array_out[0], 600U * sizeof(real32_T));
}

/* Model initialize function */
void CleanPsiArray_initialize(RT_MODEL_CleanPsiArray_t *const rtCleanPsiArray_M)
{
  /* (no initialization code required) */
  UNUSED_PARAMETER(rtCleanPsiArray_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
