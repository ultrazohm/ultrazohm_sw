/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ControlState.c
 *
 * Code generated for Simulink model 'ControlState'.
 *
 * Model version                  : 2.60
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Thu Nov 25 15:36:53 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */


#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U

#include "ControlState_codegen.h"

/* Named constants for Chart: '<Root>/ControlState' */
#define IN_ControlState                ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_Waiting                     ((uint8_T)2U)
#define IN_activateElectricalID        ((uint8_T)1U)
#define IN_activateFluxMapID           ((uint8_T)2U)
#define IN_activateFrictionID          ((uint8_T)3U)
#define IN_activateTwoMassID           ((uint8_T)4U)
#define IN_decideMotorID               ((uint8_T)5U)
#define IN_duringElectricalID          ((uint8_T)6U)
#define IN_duringFluxMapID             ((uint8_T)7U)
#define IN_duringFrictionID            ((uint8_T)8U)
#define IN_duringTwoMassID             ((uint8_T)9U)
#define IN_finishedElectricalID        ((uint8_T)10U)
#define IN_finishedFluxMapID           ((uint8_T)11U)
#define IN_finishedFrictionID          ((uint8_T)12U)
#define IN_finishedTwoMassID           ((uint8_T)13U)

/* Forward declaration for local functions */
static void initParams(ExtU_ControlState_t *rtControlState_U,
  ExtY_ControlState_t *rtControlState_Y, DW_ControlState_t *rtControlState_DW);
static void decideIDstates(ExtU_ControlState_t *rtControlState_U,
  ExtY_ControlState_t *rtControlState_Y, DW_ControlState_t *rtControlState_DW);

/*
 * Function for Chart: '<Root>/ControlState'
 * function initParams
 * Initialize Variables
 */
static void initParams(ExtU_ControlState_t *rtControlState_U,
  ExtY_ControlState_t *rtControlState_Y, DW_ControlState_t *rtControlState_DW)
{
  /* MATLAB Function 'initParams': '<S1>:732' */
  /* '<S1>:732:3' finishedElectricalID_loc=uint16(0); */
  rtControlState_DW->finishedElectricalID_loc = 0U;

  /* '<S1>:732:4' finishedFrictionID_loc=uint16(0); */
  rtControlState_DW->finishedFrictionID_loc = 0U;

  /* '<S1>:732:5' finishedTwoMassID_loc=uint16(0); */
  rtControlState_DW->finishedTwoMassID_loc = 0U;

  /* '<S1>:732:6' finishedFluxMapID_loc=uint16(0); */
  rtControlState_DW->finishedFluxMapID_loc = 0U;

  /* Outport: '<Root>/ControlFlags' */
  /* Initialize Outputs */
  /* '<S1>:732:9' ControlFlags.startFrictionID             = boolean(0); */
  rtControlState_Y->ControlFlags.startFrictionID = false;

  /* '<S1>:732:10' ControlFlags.startElectricalID           = boolean(0); */
  rtControlState_Y->ControlFlags.startElectricalID = false;

  /* '<S1>:732:11' ControlFlags.startTwoMassID              = boolean(0); */
  rtControlState_Y->ControlFlags.startTwoMassID = false;

  /* '<S1>:732:12' ControlFlags.startFluxMapID              = boolean(0); */
  rtControlState_Y->ControlFlags.startFluxMapID = false;

  /* Outport: '<Root>/GlobalConfig_out' incorporates:
   *  Inport: '<Root>/GlobalConfig_in'
   */
  /* '<S1>:732:13' GlobalConfig_out                         = GlobalConfig_in; */
  rtControlState_Y->GlobalConfig_out = rtControlState_U->GlobalConfig_in;

  /* Outport: '<Root>/ControlFlags' */
  /* '<S1>:732:14' ControlFlags.enableOnlineID              = boolean(0); */
  rtControlState_Y->ControlFlags.enableOnlineID = false;

  /* '<S1>:732:15' ControlFlags.transNr                     = uint16(0); */
  rtControlState_Y->ControlFlags.transNr = 0U;

  /* '<S1>:732:16' ControlFlags.finished_all_Offline_states = boolean(0); */
  rtControlState_Y->ControlFlags.finished_all_Offline_states = false;
}

/*
 * Function for Chart: '<Root>/ControlState'
 * function decideIDstates
 * If the specific Identification Part is not selected (==0), treat it, as if
 * it has finished
 */
static void decideIDstates(ExtU_ControlState_t *rtControlState_U,
  ExtY_ControlState_t *rtControlState_Y, DW_ControlState_t *rtControlState_DW)
{
  /* Inport: '<Root>/GlobalConfig_in' incorporates:
   *  Inport: '<Root>/finishedElectricalID'
   *  Inport: '<Root>/finishedFluxMapID'
   *  Inport: '<Root>/finishedFrictionID'
   *  Inport: '<Root>/finishedTwoMassID'
   */
  /* MATLAB Function 'decideIDstates': '<S1>:709' */
  /* '<S1>:709:4' if(GlobalConfig_in.ElectricalID==0) */
  if (!rtControlState_U->GlobalConfig_in.ElectricalID) {
    /* '<S1>:709:5' finishedElectricalID_loc=uint16(1); */
    rtControlState_DW->finishedElectricalID_loc = 1U;
  } else if (rtControlState_U->finishedElectricalID) {
    /* '<S1>:709:6' elseif(finishedElectricalID==1) */
    /* '<S1>:709:7' finishedElectricalID_loc=uint16(2); */
    rtControlState_DW->finishedElectricalID_loc = 2U;
  }

  /* '<S1>:709:10' if(GlobalConfig_in.FrictionID==0) */
  if (!rtControlState_U->GlobalConfig_in.FrictionID) {
    /* '<S1>:709:11' finishedFrictionID_loc=uint16(1); */
    rtControlState_DW->finishedFrictionID_loc = 1U;
  } else if (rtControlState_U->finishedFrictionID) {
    /* '<S1>:709:12' elseif(finishedFrictionID==1) */
    /* '<S1>:709:13' finishedFrictionID_loc=uint16(2); */
    rtControlState_DW->finishedFrictionID_loc = 2U;
  }

  /* '<S1>:709:16' if(GlobalConfig_in.TwoMassID==0) */
  if (!rtControlState_U->GlobalConfig_in.TwoMassID) {
    /* '<S1>:709:17' finishedTwoMassID_loc=uint16(1); */
    rtControlState_DW->finishedTwoMassID_loc = 1U;
  } else if (rtControlState_U->finishedTwoMassID) {
    /* '<S1>:709:18' elseif(finishedTwoMassID==1) */
    /* '<S1>:709:19' finishedTwoMassID_loc=uint16(2); */
    rtControlState_DW->finishedTwoMassID_loc = 2U;
  }

  /* '<S1>:709:22' if(GlobalConfig_in.FluxMapID==0) */
  if (!rtControlState_U->GlobalConfig_in.FluxMapID) {
    /* '<S1>:709:23' finishedFluxMapID_loc=uint16(1); */
    rtControlState_DW->finishedFluxMapID_loc = 1U;
  } else if (rtControlState_U->finishedFluxMapID) {
    /* '<S1>:709:24' elseif(finishedFluxMapID==1) */
    /* '<S1>:709:25' finishedFluxMapID_loc=uint16(2); */
    rtControlState_DW->finishedFluxMapID_loc = 2U;
  }

  /* Outport: '<Root>/ControlFlags' incorporates:
   *  Inport: '<Root>/GlobalConfig_in'
   *  Inport: '<Root>/enteredElectricalID'
   *  Inport: '<Root>/enteredFluxMapID'
   *  Inport: '<Root>/enteredFrictionID'
   *  Inport: '<Root>/enteredTwoMassID'
   *  Inport: '<Root>/finishedElectricalID'
   *  Inport: '<Root>/finishedFluxMapID'
   *  Inport: '<Root>/finishedFrictionID'
   *  Inport: '<Root>/finishedTwoMassID'
   */
  /* '<S1>:709:28' if(ControlFlags.finished_all_Offline_states == 0) */
  if (!rtControlState_Y->ControlFlags.finished_all_Offline_states) {
    /* Determine path through the ElectricalID-Stateflows */
    /* '<S1>:709:30' if(GlobalConfig_in.ElectricalID==1 && enteredElectricalID==0 && finishedElectricalID_loc~=2 && finishedElectricalID==0) */
    if (rtControlState_U->GlobalConfig_in.ElectricalID &&
        (!rtControlState_U->enteredElectricalID) &&
        (rtControlState_DW->finishedElectricalID_loc != 2) &&
        (!rtControlState_U->finishedElectricalID)) {
      /* '<S1>:709:31' ControlFlags.transNr=uint16(1); */
      rtControlState_Y->ControlFlags.transNr = 1U;

      /* '<S1>:709:32' finishedElectricalID_loc = uint16(0); */
      rtControlState_DW->finishedElectricalID_loc = 0U;
    }

    /* Determine path through the TwoMassID-Stateflows */
    /* '<S1>:709:36' if(GlobalConfig_in.TwoMassID==1 && enteredTwoMassID==0 && finishedElectricalID_loc~=0 && finishedTwoMassID_loc~=2 && finishedTwoMassID==0) */
    if (rtControlState_U->GlobalConfig_in.TwoMassID &&
        (!rtControlState_U->enteredTwoMassID) &&
        (rtControlState_DW->finishedElectricalID_loc != 0) &&
        (rtControlState_DW->finishedTwoMassID_loc != 2) &&
        (!rtControlState_U->finishedTwoMassID)) {
      /* '<S1>:709:37' ControlFlags.transNr=uint16(2); */
      rtControlState_Y->ControlFlags.transNr = 2U;

      /* '<S1>:709:38' finishedTwoMassID_loc = uint16(0); */
      rtControlState_DW->finishedTwoMassID_loc = 0U;
    }

    /* Determine path through the FrictionID-Stateflows */
    /* '<S1>:709:42' if(GlobalConfig_in.FrictionID==1 && enteredFrictionID==0 && finishedElectricalID_loc~=0.... */
    /* '<S1>:709:43'        && finishedTwoMassID_loc~=0 && finishedFrictionID_loc~=2 && finishedFrictionID==0) */
    if (rtControlState_U->GlobalConfig_in.FrictionID &&
        (!rtControlState_U->enteredFrictionID) &&
        (rtControlState_DW->finishedElectricalID_loc != 0) &&
        (rtControlState_DW->finishedTwoMassID_loc != 0) &&
        (rtControlState_DW->finishedFrictionID_loc != 2) &&
        (!rtControlState_U->finishedFrictionID)) {
      /* '<S1>:709:44' ControlFlags.transNr=uint16(3); */
      rtControlState_Y->ControlFlags.transNr = 3U;

      /* '<S1>:709:45' finishedFrictionID_loc = uint16(0); */
      rtControlState_DW->finishedFrictionID_loc = 0U;
    }

    /* Determine path through the FluxMapID-Stateflows */
    /* '<S1>:709:49' if(GlobalConfig_in.FluxMapID==1 && enteredFluxMapID==0 && finishedElectricalID_loc~=0.... */
    /* '<S1>:709:50'       && finishedTwoMassID_loc~=0 && finishedFrictionID_loc~=0 && finishedFluxMapID_loc~=2 && finishedFluxMapID==0) */
    if (rtControlState_U->GlobalConfig_in.FluxMapID &&
        (!rtControlState_U->enteredFluxMapID) &&
        (rtControlState_DW->finishedElectricalID_loc != 0) &&
        (rtControlState_DW->finishedTwoMassID_loc != 0) &&
        (rtControlState_DW->finishedFrictionID_loc != 0) &&
        (rtControlState_DW->finishedFluxMapID_loc != 2) &&
        (!rtControlState_U->finishedFluxMapID)) {
      /* '<S1>:709:51' ControlFlags.transNr=uint16(4); */
      rtControlState_Y->ControlFlags.transNr = 4U;

      /* '<S1>:709:52' finishedFluxMapID_loc = uint16(0); */
      rtControlState_DW->finishedFluxMapID_loc = 0U;
    }
  }

  /* '<S1>:709:56' if(finishedElectricalID_loc~=0 && finishedTwoMassID_loc~=0 && .... */
  /* '<S1>:709:57'         finishedFrictionID_loc~=0 && finishedFluxMapID_loc~=0) */
  if ((rtControlState_DW->finishedElectricalID_loc != 0) &&
      (rtControlState_DW->finishedTwoMassID_loc != 0) &&
      (rtControlState_DW->finishedFrictionID_loc != 0) &&
      (rtControlState_DW->finishedFluxMapID_loc != 0)) {
    /* Outport: '<Root>/ControlFlags' */
    /* . */
    /* '<S1>:709:58' ControlFlags.finished_all_Offline_states = boolean(1); */
    rtControlState_Y->ControlFlags.finished_all_Offline_states = true;
  }
}

/* Model step function */
void ControlState_step(RT_MODEL_ControlState_t *const rtControlState_M)
{
  DW_ControlState_t *rtControlState_DW = rtControlState_M->dwork;
  ExtU_ControlState_t *rtControlState_U = (ExtU_ControlState_t *)
    rtControlState_M->inputs;
  ExtY_ControlState_t *rtControlState_Y = (ExtY_ControlState_t *)
    rtControlState_M->outputs;

  /* Chart: '<Root>/ControlState' incorporates:
   *  Inport: '<Root>/ElectricalID_FOC_output'
   *  Inport: '<Root>/ElectricalID_output'
   *  Inport: '<Root>/GlobalConfig_in'
   *  Inport: '<Root>/enteredElectricalID'
   *  Inport: '<Root>/enteredFluxMapID'
   *  Inport: '<Root>/enteredFrictionID'
   *  Inport: '<Root>/enteredTwoMassID'
   *  Inport: '<Root>/finishedElectricalID'
   *  Inport: '<Root>/finishedFluxMapID'
   *  Inport: '<Root>/finishedFrictionID'
   *  Inport: '<Root>/finishedTwoMassID'
   *  Outport: '<Root>/ControlFlags'
   *  Outport: '<Root>/GlobalConfig_out'
   */
  /* Gateway: ControlState */
  /* During: ControlState */
  if (rtControlState_DW->is_active_c8_ControlState == 0U) {
    /* Entry: ControlState */
    rtControlState_DW->is_active_c8_ControlState = 1U;

    /* Entry Internal: ControlState */
    /* Transition: '<S1>:731' */
    rtControlState_DW->is_c8_ControlState = IN_Waiting;

    /* Entry 'Waiting': '<S1>:726' */
    /* '<S1>:726:3' initParams; */
    initParams(rtControlState_U, rtControlState_Y, rtControlState_DW);

    /* wait for activation of */
    /* FrictionID */
    /* donothing */
  } else if (rtControlState_DW->is_c8_ControlState == IN_ControlState) {
    /* During 'ControlState': '<S1>:39' */
    /* '<S1>:722:1' sf_internal_predicateOutput = GlobalConfig_in.Reset==1 ||.... */
    /* '<S1>:722:2'  GlobalConfig_in.enableParameterID==0; */
    /* . */
    if (rtControlState_U->GlobalConfig_in.Reset ||
        (!rtControlState_U->GlobalConfig_in.enableParameterID)) {
      /* Transition: '<S1>:722' */
      /* Exit Internal 'ControlState': '<S1>:39' */
      switch (rtControlState_DW->is_ControlState) {
       case IN_activateElectricalID:
        /* Exit 'activateElectricalID': '<S1>:617' */
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_activateFluxMapID:
        /* Exit 'activateFluxMapID': '<S1>:684' */
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_activateFrictionID:
        /* Exit 'activateFrictionID': '<S1>:655' */
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_activateTwoMassID:
        /* Exit 'activateTwoMassID': '<S1>:628' */
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_decideMotorID:
        /* Exit 'decideMotorID': '<S1>:605' */
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_duringElectricalID:
        /* Exit 'duringElectricalID': '<S1>:624' */
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_duringFluxMapID:
        /* Exit 'duringFluxMapID': '<S1>:685' */
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_duringFrictionID:
        /* Exit 'duringFrictionID': '<S1>:656' */
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_duringTwoMassID:
        /* Exit 'duringTwoMassID': '<S1>:632' */
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_finishedElectricalID:
        /* Exit 'finishedElectricalID': '<S1>:626' */
        /* '<S1>:626:6' ControlFlags.transNr=uint16(0); */
        rtControlState_Y->ControlFlags.transNr = 0U;
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_finishedFluxMapID:
        /* Exit 'finishedFluxMapID': '<S1>:686' */
        /* '<S1>:686:6' ControlFlags.transNr=uint16(0); */
        rtControlState_Y->ControlFlags.transNr = 0U;
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_finishedFrictionID:
        /* Exit 'finishedFrictionID': '<S1>:654' */
        /* '<S1>:654:6' ControlFlags.transNr=uint16(0); */
        rtControlState_Y->ControlFlags.transNr = 0U;
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;

       case IN_finishedTwoMassID:
        /* Exit 'finishedTwoMassID': '<S1>:636' */
        /* '<S1>:636:6' ControlFlags.transNr=uint16(0); */
        rtControlState_Y->ControlFlags.transNr = 0U;
        rtControlState_DW->is_ControlState = IN_NO_ACTIVE_CHILD;
        break;
      }

      rtControlState_DW->is_c8_ControlState = IN_Waiting;

      /* Entry 'Waiting': '<S1>:726' */
      /* '<S1>:726:3' initParams; */
      initParams(rtControlState_U, rtControlState_Y, rtControlState_DW);

      /* wait for activation of */
      /* FrictionID */
      /* donothing */
    } else {
      /* '<S1>:39:4' GlobalConfig_out.Reset = GlobalConfig_in.Reset; */
      rtControlState_Y->GlobalConfig_out.Reset =
        rtControlState_U->GlobalConfig_in.Reset;

      /* '<S1>:39:5' GlobalConfig_out.ACCEPT = GlobalConfig_in.ACCEPT; */
      rtControlState_Y->GlobalConfig_out.ACCEPT =
        rtControlState_U->GlobalConfig_in.ACCEPT;

      /* '<S1>:39:6' GlobalConfig_out.enableParameterID = GlobalConfig_in.enableParameterID; */
      rtControlState_Y->GlobalConfig_out.enableParameterID =
        rtControlState_U->GlobalConfig_in.enableParameterID;

      /* '<S1>:39:7' GlobalConfig_out.VibOn = GlobalConfig_in.VibOn; */
      rtControlState_Y->GlobalConfig_out.VibOn =
        rtControlState_U->GlobalConfig_in.VibOn;

      /* '<S1>:39:8' GlobalConfig_out.VibAmp = GlobalConfig_in.VibAmp; */
      rtControlState_Y->GlobalConfig_out.VibAmp =
        rtControlState_U->GlobalConfig_in.VibAmp;

      /* '<S1>:39:9' GlobalConfig_out.VibFreq = GlobalConfig_in.VibFreq; */
      rtControlState_Y->GlobalConfig_out.VibFreq =
        rtControlState_U->GlobalConfig_in.VibFreq;

      /* '<S1>:39:10' GlobalConfig_out.ElectricalID = GlobalConfig_in.ElectricalID; */
      rtControlState_Y->GlobalConfig_out.ElectricalID =
        rtControlState_U->GlobalConfig_in.ElectricalID;

      /* '<S1>:39:11' GlobalConfig_out.FrictionID = GlobalConfig_in.FrictionID */
      rtControlState_Y->GlobalConfig_out.FrictionID =
        rtControlState_U->GlobalConfig_in.FrictionID;

      /* '<S1>:39:12' GlobalConfig_out.TwoMassID = GlobalConfig_in.TwoMassID; */
      rtControlState_Y->GlobalConfig_out.TwoMassID =
        rtControlState_U->GlobalConfig_in.TwoMassID;

      /* '<S1>:39:13' GlobalConfig_out.FluxMapID = GlobalConfig_in.FluxMapID; */
      rtControlState_Y->GlobalConfig_out.FluxMapID =
        rtControlState_U->GlobalConfig_in.FluxMapID;

      /* '<S1>:39:14' GlobalConfig_out.OnlineID = GlobalConfig_in.OnlineID; */
      rtControlState_Y->GlobalConfig_out.OnlineID =
        rtControlState_U->GlobalConfig_in.OnlineID;
      switch (rtControlState_DW->is_ControlState) {
       case IN_activateElectricalID:
        /* During 'activateElectricalID': '<S1>:617' */
        /* '<S1>:625:1' sf_internal_predicateOutput = enteredElectricalID==1; */
        if (rtControlState_U->enteredElectricalID) {
          /* Transition: '<S1>:625' */
          /* Exit 'activateElectricalID': '<S1>:617' */
          rtControlState_DW->is_ControlState = IN_duringElectricalID;

          /* Entry 'duringElectricalID': '<S1>:624' */
          /* '<S1>:624:3' ControlFlags.startElectricalID=boolean(0); */
          rtControlState_Y->ControlFlags.startElectricalID = false;

          /* '<S1>:718:1' sf_internal_predicateOutput = GlobalConfig_in.ElectricalID==0; */
        } else if (!rtControlState_U->GlobalConfig_in.ElectricalID) {
          /* Transition: '<S1>:718' */
          /* '<S1>:718:2' ControlFlags.transNr = 0 */
          rtControlState_Y->ControlFlags.transNr = 0U;

          /* Exit 'activateElectricalID': '<S1>:617' */
          rtControlState_DW->is_ControlState = IN_decideMotorID;

          /* Entry 'decideMotorID': '<S1>:605' */
        }
        break;

       case IN_activateFluxMapID:
        /* During 'activateFluxMapID': '<S1>:684' */
        /* '<S1>:687:1' sf_internal_predicateOutput = enteredFluxMapID==1; */
        if (rtControlState_U->enteredFluxMapID) {
          /* Transition: '<S1>:687' */
          /* Exit 'activateFluxMapID': '<S1>:684' */
          rtControlState_DW->is_ControlState = IN_duringFluxMapID;

          /* Entry 'duringFluxMapID': '<S1>:685' */
          /* '<S1>:685:3' ControlFlags.startFluxMapID=boolean(0); */
          rtControlState_Y->ControlFlags.startFluxMapID = false;

          /* '<S1>:715:1' sf_internal_predicateOutput = GlobalConfig_in.FluxMapID==0; */
        } else if (!rtControlState_U->GlobalConfig_in.FluxMapID) {
          /* Transition: '<S1>:715' */
          /* '<S1>:715:2' ControlFlags.transNr = 0 */
          rtControlState_Y->ControlFlags.transNr = 0U;

          /* Exit 'activateFluxMapID': '<S1>:684' */
          rtControlState_DW->is_ControlState = IN_decideMotorID;

          /* Entry 'decideMotorID': '<S1>:605' */
        }
        break;

       case IN_activateFrictionID:
        /* During 'activateFrictionID': '<S1>:655' */
        /* '<S1>:653:1' sf_internal_predicateOutput = enteredFrictionID==1; */
        if (rtControlState_U->enteredFrictionID) {
          /* Transition: '<S1>:653' */
          /* Exit 'activateFrictionID': '<S1>:655' */
          rtControlState_DW->is_ControlState = IN_duringFrictionID;

          /* Entry 'duringFrictionID': '<S1>:656' */
          /* '<S1>:656:3' ControlFlags.startFrictionID=boolean(0); */
          rtControlState_Y->ControlFlags.startFrictionID = false;

          /* '<S1>:716:1' sf_internal_predicateOutput = GlobalConfig_in.FrictionID==0; */
        } else if (!rtControlState_U->GlobalConfig_in.FrictionID) {
          /* Transition: '<S1>:716' */
          /* '<S1>:716:2' ControlFlags.transNr = 0 */
          rtControlState_Y->ControlFlags.transNr = 0U;

          /* Exit 'activateFrictionID': '<S1>:655' */
          rtControlState_DW->is_ControlState = IN_decideMotorID;

          /* Entry 'decideMotorID': '<S1>:605' */
        }
        break;

       case IN_activateTwoMassID:
        /* During 'activateTwoMassID': '<S1>:628' */
        /* '<S1>:633:1' sf_internal_predicateOutput = enteredTwoMassID==1; */
        if (rtControlState_U->enteredTwoMassID) {
          /* Transition: '<S1>:633' */
          /* Exit 'activateTwoMassID': '<S1>:628' */
          rtControlState_DW->is_ControlState = IN_duringTwoMassID;

          /* Entry 'duringTwoMassID': '<S1>:632' */
          /* '<S1>:632:3' ControlFlags.startTwoMassID=boolean(0); */
          rtControlState_Y->ControlFlags.startTwoMassID = false;

          /* '<S1>:717:1' sf_internal_predicateOutput = GlobalConfig_in.TwoMassID==0; */
        } else if (!rtControlState_U->GlobalConfig_in.TwoMassID) {
          /* Transition: '<S1>:717' */
          /* '<S1>:717:2' ControlFlags.transNr = 0 */
          rtControlState_Y->ControlFlags.transNr = 0U;

          /* Exit 'activateTwoMassID': '<S1>:628' */
          rtControlState_DW->is_ControlState = IN_decideMotorID;

          /* Entry 'decideMotorID': '<S1>:605' */
        }
        break;

       case IN_decideMotorID:
        /* During 'decideMotorID': '<S1>:605' */
        /* '<S1>:618:1' sf_internal_predicateOutput = ControlFlags.transNr==1 && finishedElectricalID_loc==0; */
        if ((rtControlState_Y->ControlFlags.transNr == 1) &&
            (rtControlState_DW->finishedElectricalID_loc == 0)) {
          /* Transition: '<S1>:618' */
          /* Exit 'decideMotorID': '<S1>:605' */
          rtControlState_DW->is_ControlState = IN_activateElectricalID;

          /* Entry 'activateElectricalID': '<S1>:617' */
          /* '<S1>:617:3' ControlFlags.startElectricalID=boolean(1); */
          rtControlState_Y->ControlFlags.startElectricalID = true;

          /* '<S1>:682:1' sf_internal_predicateOutput = ControlFlags.transNr==4 && finishedFluxMapID_loc==0; */
        } else if ((rtControlState_Y->ControlFlags.transNr == 4) &&
                   (rtControlState_DW->finishedFluxMapID_loc == 0)) {
          /* Transition: '<S1>:682' */
          /* Exit 'decideMotorID': '<S1>:605' */
          rtControlState_DW->is_ControlState = IN_activateFluxMapID;

          /* Entry 'activateFluxMapID': '<S1>:684' */
          /* '<S1>:684:3' ControlFlags.startFluxMapID=boolean(1); */
          rtControlState_Y->ControlFlags.startFluxMapID = true;

          /* '<S1>:672:1' sf_internal_predicateOutput = ControlFlags.transNr==2 && finishedTwoMassID_loc==0; */
        } else if ((rtControlState_Y->ControlFlags.transNr == 2) &&
                   (rtControlState_DW->finishedTwoMassID_loc == 0)) {
          /* Transition: '<S1>:672' */
          /* Exit 'decideMotorID': '<S1>:605' */
          rtControlState_DW->is_ControlState = IN_activateTwoMassID;

          /* Entry 'activateTwoMassID': '<S1>:628' */
          /* '<S1>:628:3' ControlFlags.startTwoMassID=boolean(1); */
          rtControlState_Y->ControlFlags.startTwoMassID = true;

          /* '<S1>:678:1' sf_internal_predicateOutput = ControlFlags.transNr==3 && finishedFrictionID_loc==0; */
        } else if ((rtControlState_Y->ControlFlags.transNr == 3) &&
                   (rtControlState_DW->finishedFrictionID_loc == 0)) {
          /* Transition: '<S1>:678' */
          /* Exit 'decideMotorID': '<S1>:605' */
          rtControlState_DW->is_ControlState = IN_activateFrictionID;

          /* Entry 'activateFrictionID': '<S1>:655' */
          /* '<S1>:655:3' ControlFlags.startFrictionID=boolean(1); */
          rtControlState_Y->ControlFlags.startFrictionID = true;
        } else {
          /* '<S1>:605:4' if (GlobalConfig_in.ACCEPT == 1) */
          if (rtControlState_U->GlobalConfig_in.ACCEPT) {
            /* '<S1>:605:5' decideIDstates; */
            decideIDstates(rtControlState_U, rtControlState_Y, rtControlState_DW);
          }

          /* '<S1>:605:7' if(ControlFlags.finished_all_Offline_states == 1 && GlobalConfig_in.OnlineID==1) */
          if (rtControlState_Y->ControlFlags.finished_all_Offline_states &&
              rtControlState_U->GlobalConfig_in.OnlineID) {
            /* '<S1>:605:8' ControlFlags.enableOnlineID=boolean(1); */
            rtControlState_Y->ControlFlags.enableOnlineID = true;
          } else if (rtControlState_Y->ControlFlags.finished_all_Offline_states &&
                     (!rtControlState_U->GlobalConfig_in.OnlineID)) {
            /* '<S1>:605:9' elseif (ControlFlags.finished_all_Offline_states == 1 && GlobalConfig_in.OnlineID==0) */
            /* '<S1>:605:10' ControlFlags.enableOnlineID=boolean(0); */
            rtControlState_Y->ControlFlags.enableOnlineID = false;
          }
        }
        break;

       case IN_duringElectricalID:
        /* During 'duringElectricalID': '<S1>:624' */
        /* '<S1>:627:1' sf_internal_predicateOutput = finishedElectricalID==1; */
        if (rtControlState_U->finishedElectricalID) {
          /* Transition: '<S1>:627' */
          /* Exit 'duringElectricalID': '<S1>:624' */
          rtControlState_DW->is_ControlState = IN_finishedElectricalID;

          /* Entry 'finishedElectricalID': '<S1>:626' */
          /* '<S1>:626:3' finishedElectricalID_loc=uint16(2); */
          rtControlState_DW->finishedElectricalID_loc = 2U;

          /* '<S1>:710:1' sf_internal_predicateOutput = GlobalConfig_in.ElectricalID==0; */
        } else if (!rtControlState_U->GlobalConfig_in.ElectricalID) {
          /* Transition: '<S1>:710' */
          /* '<S1>:710:2' ControlFlags.transNr = 0 */
          rtControlState_Y->ControlFlags.transNr = 0U;

          /* Exit 'duringElectricalID': '<S1>:624' */
          rtControlState_DW->is_ControlState = IN_decideMotorID;

          /* Entry 'decideMotorID': '<S1>:605' */
        } else {
          /* '<S1>:624:5' GlobalConfig_out.PMSM_config.Ld_Henry=ElectricalID_output.PMSM_parameters.Ld_Henry; */
          rtControlState_Y->GlobalConfig_out.PMSM_config.Ld_Henry =
            rtControlState_U->ElectricalID_output.PMSM_parameters.Ld_Henry;

          /* '<S1>:624:6' GlobalConfig_out.PMSM_config.Lq_Henry=ElectricalID_output.PMSM_parameters.Lq_Henry; */
          rtControlState_Y->GlobalConfig_out.PMSM_config.Lq_Henry =
            rtControlState_U->ElectricalID_output.PMSM_parameters.Lq_Henry;

          /* '<S1>:624:7' GlobalConfig_out.PMSM_config.R_ph_Ohm=ElectricalID_output.PMSM_parameters.R_ph_Ohm; */
          rtControlState_Y->GlobalConfig_out.PMSM_config.R_ph_Ohm =
            rtControlState_U->ElectricalID_output.PMSM_parameters.R_ph_Ohm;

          /* '<S1>:624:8' GlobalConfig_out.PMSM_config.Psi_PM_Vs=ElectricalID_output.PMSM_parameters.Psi_PM_Vs; */
          rtControlState_Y->GlobalConfig_out.PMSM_config.Psi_PM_Vs =
            rtControlState_U->ElectricalID_output.PMSM_parameters.Psi_PM_Vs;

          /* '<S1>:624:9' GlobalConfig_out.PMSM_config.polePairs=ElectricalID_output.PMSM_parameters.polePairs; */
          rtControlState_Y->GlobalConfig_out.PMSM_config.polePairs =
            rtControlState_U->ElectricalID_output.PMSM_parameters.polePairs;

          /* '<S1>:624:10' GlobalConfig_out.PMSM_config.J_kg_m_squared=.... */
          /* '<S1>:624:11'     ElectricalID_output.PMSM_parameters.J_kg_m_squared; */
          rtControlState_Y->GlobalConfig_out.PMSM_config.J_kg_m_squared =
            rtControlState_U->ElectricalID_output.PMSM_parameters.J_kg_m_squared;

          /* . */
          /* '<S1>:624:12' GlobalConfig_out.Kp_id=ElectricalID_FOC_output.Kp_id_out; */
          rtControlState_Y->GlobalConfig_out.Kp_id =
            rtControlState_U->ElectricalID_FOC_output.Kp_id_out;

          /* '<S1>:624:13' GlobalConfig_out.Kp_iq=ElectricalID_FOC_output.Kp_iq_out; */
          rtControlState_Y->GlobalConfig_out.Kp_iq =
            rtControlState_U->ElectricalID_FOC_output.Kp_iq_out;

          /* '<S1>:624:14' GlobalConfig_out.Kp_n=ElectricalID_FOC_output.Kp_n_out; */
          rtControlState_Y->GlobalConfig_out.Kp_n =
            rtControlState_U->ElectricalID_FOC_output.Kp_n_out;

          /* '<S1>:624:15' GlobalConfig_out.Ki_id=ElectricalID_FOC_output.Ki_id_out; */
          rtControlState_Y->GlobalConfig_out.Ki_id =
            rtControlState_U->ElectricalID_FOC_output.Ki_id_out;

          /* '<S1>:624:16' GlobalConfig_out.Ki_iq=ElectricalID_FOC_output.Ki_iq_out; */
          rtControlState_Y->GlobalConfig_out.Ki_iq =
            rtControlState_U->ElectricalID_FOC_output.Ki_iq_out;

          /* '<S1>:624:17' GlobalConfig_out.Ki_n=ElectricalID_FOC_output.Ki_n_out; */
          rtControlState_Y->GlobalConfig_out.Ki_n =
            rtControlState_U->ElectricalID_FOC_output.Ki_n_out;
        }
        break;

       case IN_duringFluxMapID:
        /* During 'duringFluxMapID': '<S1>:685' */
        /* '<S1>:683:1' sf_internal_predicateOutput = finishedFluxMapID==1; */
        if (rtControlState_U->finishedFluxMapID) {
          /* Transition: '<S1>:683' */
          /* Exit 'duringFluxMapID': '<S1>:685' */
          rtControlState_DW->is_ControlState = IN_finishedFluxMapID;

          /* Entry 'finishedFluxMapID': '<S1>:686' */
          /* '<S1>:686:3' finishedFluxMapID_loc=uint16(2); */
          rtControlState_DW->finishedFluxMapID_loc = 2U;

          /* '<S1>:711:1' sf_internal_predicateOutput = GlobalConfig_in.FluxMapID==0; */
        } else if (!rtControlState_U->GlobalConfig_in.FluxMapID) {
          /* Transition: '<S1>:711' */
          /* '<S1>:711:2' ControlFlags.transNr = 0 */
          rtControlState_Y->ControlFlags.transNr = 0U;

          /* Exit 'duringFluxMapID': '<S1>:685' */
          rtControlState_DW->is_ControlState = IN_decideMotorID;

          /* Entry 'decideMotorID': '<S1>:605' */
        }
        break;

       case IN_duringFrictionID:
        /* During 'duringFrictionID': '<S1>:656' */
        /* '<S1>:652:1' sf_internal_predicateOutput = finishedFrictionID==1; */
        if (rtControlState_U->finishedFrictionID) {
          /* Transition: '<S1>:652' */
          /* Exit 'duringFrictionID': '<S1>:656' */
          rtControlState_DW->is_ControlState = IN_finishedFrictionID;

          /* Entry 'finishedFrictionID': '<S1>:654' */
          /* '<S1>:654:3' finishedFrictionID_loc=uint16(2); */
          rtControlState_DW->finishedFrictionID_loc = 2U;

          /* '<S1>:713:1' sf_internal_predicateOutput = GlobalConfig_in.FrictionID==0; */
        } else if (!rtControlState_U->GlobalConfig_in.FrictionID) {
          /* Transition: '<S1>:713' */
          /* '<S1>:713:2' ControlFlags.transNr = 0 */
          rtControlState_Y->ControlFlags.transNr = 0U;

          /* Exit 'duringFrictionID': '<S1>:656' */
          rtControlState_DW->is_ControlState = IN_decideMotorID;

          /* Entry 'decideMotorID': '<S1>:605' */
        }
        break;

       case IN_duringTwoMassID:
        /* During 'duringTwoMassID': '<S1>:632' */
        /* '<S1>:637:1' sf_internal_predicateOutput = finishedTwoMassID==1; */
        if (rtControlState_U->finishedTwoMassID) {
          /* Transition: '<S1>:637' */
          /* Exit 'duringTwoMassID': '<S1>:632' */
          rtControlState_DW->is_ControlState = IN_finishedTwoMassID;

          /* Entry 'finishedTwoMassID': '<S1>:636' */
          /* '<S1>:636:3' finishedTwoMassID_loc=uint16(2); */
          rtControlState_DW->finishedTwoMassID_loc = 2U;

          /* '<S1>:712:1' sf_internal_predicateOutput = GlobalConfig_in.TwoMassID==0; */
        } else if (!rtControlState_U->GlobalConfig_in.TwoMassID) {
          /* Transition: '<S1>:712' */
          /* '<S1>:712:2' ControlFlags.transNr = 0 */
          rtControlState_Y->ControlFlags.transNr = 0U;

          /* Exit 'duringTwoMassID': '<S1>:632' */
          rtControlState_DW->is_ControlState = IN_decideMotorID;

          /* Entry 'decideMotorID': '<S1>:605' */
        }
        break;

       case IN_finishedElectricalID:
        /* During 'finishedElectricalID': '<S1>:626' */
        /* Transition: '<S1>:673' */
        /* Exit 'finishedElectricalID': '<S1>:626' */
        /* '<S1>:626:6' ControlFlags.transNr=uint16(0); */
        rtControlState_Y->ControlFlags.transNr = 0U;
        rtControlState_DW->is_ControlState = IN_decideMotorID;

        /* Entry 'decideMotorID': '<S1>:605' */
        break;

       case IN_finishedFluxMapID:
        /* During 'finishedFluxMapID': '<S1>:686' */
        /* Transition: '<S1>:690' */
        /* Exit 'finishedFluxMapID': '<S1>:686' */
        /* '<S1>:686:6' ControlFlags.transNr=uint16(0); */
        rtControlState_Y->ControlFlags.transNr = 0U;
        rtControlState_DW->is_ControlState = IN_decideMotorID;

        /* Entry 'decideMotorID': '<S1>:605' */
        break;

       case IN_finishedFrictionID:
        /* During 'finishedFrictionID': '<S1>:654' */
        /* Transition: '<S1>:679' */
        /* Exit 'finishedFrictionID': '<S1>:654' */
        /* '<S1>:654:6' ControlFlags.transNr=uint16(0); */
        rtControlState_Y->ControlFlags.transNr = 0U;
        rtControlState_DW->is_ControlState = IN_decideMotorID;

        /* Entry 'decideMotorID': '<S1>:605' */
        break;

       default:
        /* During 'finishedTwoMassID': '<S1>:636' */
        /* Transition: '<S1>:677' */
        /* Exit 'finishedTwoMassID': '<S1>:636' */
        /* '<S1>:636:6' ControlFlags.transNr=uint16(0); */
        rtControlState_Y->ControlFlags.transNr = 0U;
        rtControlState_DW->is_ControlState = IN_decideMotorID;

        /* Entry 'decideMotorID': '<S1>:605' */
        break;
      }
    }

    /* During 'Waiting': '<S1>:726' */
    /* '<S1>:723:1' sf_internal_predicateOutput = GlobalConfig_in.enableParameterID==1 && .... */
    /* '<S1>:723:2' GlobalConfig_in.Reset==0; */
    /* . */
  } else if (rtControlState_U->GlobalConfig_in.enableParameterID &&
             (!rtControlState_U->GlobalConfig_in.Reset)) {
    /* Transition: '<S1>:723' */
    rtControlState_DW->is_c8_ControlState = IN_ControlState;

    /* Entry 'ControlState': '<S1>:39' */
    /* Entry Internal 'ControlState': '<S1>:39' */
    /* Transition: '<S1>:606' */
    rtControlState_DW->is_ControlState = IN_decideMotorID;

    /* Entry 'decideMotorID': '<S1>:605' */

    /* '<S1>:725:1' sf_internal_predicateOutput = GlobalConfig_in.Reset==1; */
  } else if (rtControlState_U->GlobalConfig_in.Reset) {
    /* Transition: '<S1>:725' */
    rtControlState_DW->is_c8_ControlState = IN_Waiting;

    /* Entry 'Waiting': '<S1>:726' */
    /* '<S1>:726:3' initParams; */
    initParams(rtControlState_U, rtControlState_Y, rtControlState_DW);

    /* wait for activation of */
    /* FrictionID */
    /* donothing */
  }

  /* End of Chart: '<Root>/ControlState' */
}

/* Model initialize function */
void ControlState_initialize(RT_MODEL_ControlState_t *const rtControlState_M)
{
  ExtY_ControlState_t *rtControlState_Y = (ExtY_ControlState_t *)
    rtControlState_M->outputs;

  /* SystemInitialize for Chart: '<Root>/ControlState' incorporates:
   *  Outport: '<Root>/ControlFlags'
   *  Outport: '<Root>/GlobalConfig_out'
   */
  rtControlState_Y->GlobalConfig_out.PMSM_config.R_ph_Ohm = 0.0F;
  rtControlState_Y->GlobalConfig_out.PMSM_config.Ld_Henry = 0.0F;
  rtControlState_Y->GlobalConfig_out.PMSM_config.Lq_Henry = 0.0F;
  rtControlState_Y->GlobalConfig_out.PMSM_config.Psi_PM_Vs = 0.0F;
  rtControlState_Y->GlobalConfig_out.PMSM_config.polePairs = 0.0F;
  rtControlState_Y->GlobalConfig_out.PMSM_config.J_kg_m_squared = 0.0F;
  rtControlState_Y->GlobalConfig_out.PMSM_config.I_max_Ampere = 0.0F;
  rtControlState_Y->GlobalConfig_out.enableParameterID = false;
  rtControlState_Y->GlobalConfig_out.Reset = false;
  rtControlState_Y->GlobalConfig_out.Kp_id = 0.0F;
  rtControlState_Y->GlobalConfig_out.Kp_iq = 0.0F;
  rtControlState_Y->GlobalConfig_out.Kp_n = 0.0F;
  rtControlState_Y->GlobalConfig_out.Ki_id = 0.0F;
  rtControlState_Y->GlobalConfig_out.Ki_iq = 0.0F;
  rtControlState_Y->GlobalConfig_out.Ki_n = 0.0F;
  rtControlState_Y->GlobalConfig_out.ElectricalID = false;
  rtControlState_Y->GlobalConfig_out.FrictionID = false;
  rtControlState_Y->GlobalConfig_out.TwoMassID = false;
  rtControlState_Y->GlobalConfig_out.FluxMapID = false;
  rtControlState_Y->GlobalConfig_out.OnlineID = false;
  rtControlState_Y->GlobalConfig_out.ACCEPT = false;
  rtControlState_Y->GlobalConfig_out.sampleTimeISR = 0.0F;
  rtControlState_Y->GlobalConfig_out.ratCurrent = 0.0F;
  rtControlState_Y->GlobalConfig_out.ratSpeed = 0.0F;
  rtControlState_Y->GlobalConfig_out.VibAmp = 0.0F;
  rtControlState_Y->GlobalConfig_out.VibOn = false;
  rtControlState_Y->GlobalConfig_out.VibFreq = 0U;
  rtControlState_Y->GlobalConfig_out.i_dq_ref.d = 0.0F;
  rtControlState_Y->GlobalConfig_out.i_dq_ref.q = 0.0F;
  rtControlState_Y->GlobalConfig_out.i_dq_ref.zero = 0.0F;
  rtControlState_Y->GlobalConfig_out.n_ref = 0.0F;
  rtControlState_Y->ControlFlags.startFrictionID = false;
  rtControlState_Y->ControlFlags.startElectricalID = false;
  rtControlState_Y->ControlFlags.startTwoMassID = false;
  rtControlState_Y->ControlFlags.startFluxMapID = false;
  rtControlState_Y->ControlFlags.transNr = 0U;
  rtControlState_Y->ControlFlags.enableOnlineID = false;
  rtControlState_Y->ControlFlags.finished_all_Offline_states = false;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
