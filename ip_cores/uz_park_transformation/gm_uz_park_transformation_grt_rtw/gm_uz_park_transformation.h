/*
 * gm_uz_park_transformation.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "gm_uz_park_transformation".
 *
 * Model version              : 1.9
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Thu Aug 11 11:20:48 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ASIC/FPGA->ASIC/FPGA
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_gm_uz_park_transformation_h_
#define RTW_HEADER_gm_uz_park_transformation_h_
#include <math.h>
#include <float.h>
#include <string.h>
#include <stddef.h>
#ifndef gm_uz_park_transformation_COMMON_INCLUDES_
#define gm_uz_park_transformation_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                          /* gm_uz_park_transformation_COMMON_INCLUDES_ */

#include "gm_uz_park_transformation_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T SineWave;                     /* '<Root>/Sine Wave' */
  real_T RateTransition;               /* '<Root>/Rate Transition' */
  real_T SineWave1;                    /* '<Root>/Sine Wave1' */
  real_T RateTransition1;              /* '<Root>/Rate Transition1' */
  real_T Gain;                         /* '<Root>/Gain' */
  real_T RateTransition2;              /* '<Root>/Rate Transition2' */
  real_T RateTransition4;              /* '<Root>/Rate Transition4' */
  int32_T DataTypeConversion;          /* '<Root>/Data Type Conversion' */
  int32_T DataTypeConversion2;         /* '<Root>/Data Type Conversion2' */
  int32_T DataTypeConversion1;         /* '<Root>/Data Type Conversion1' */
  int32_T DataTypeConversion3;         /* '<Root>/Data Type Conversion3' */
  boolean_T trigger;                   /* '<Root>/Rate Transition3' */
} B_gm_uz_park_transformation_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  int32_T delayMatch_DSTATE;           /* '<S1>/delayMatch' */
  int32_T delayMatch1_DSTATE;          /* '<S1>/delayMatch1' */
  int32_T delayMatch2_DSTATE;          /* '<S1>/delayMatch2' */
  int32_T delayMatch3_DSTATE;          /* '<S1>/delayMatch3' */
  int32_T Delay_DSTATE;                /* '<S1>/Delay' */
  int32_T Delay1_DSTATE;               /* '<S1>/Delay1' */
  int32_T Delay4_DSTATE;               /* '<S1>/Delay4' */
  int32_T Delay5_DSTATE;               /* '<S1>/Delay5' */
  int32_T Delay2_DSTATE;               /* '<S1>/Delay2' */
  int32_T Delay6_DSTATE;               /* '<S1>/Delay6' */
  int32_T Delay11_DSTATE;              /* '<S1>/Delay11' */
  int32_T Delay12_DSTATE;              /* '<S1>/Delay12' */
  int32_T Delay10_DSTATE;              /* '<S1>/Delay10' */
  int32_T Delay7_DSTATE;               /* '<S1>/Delay7' */
  int32_T Delay8_DSTATE;               /* '<S1>/Delay8' */
  int32_T Delay9_DSTATE;               /* '<S1>/Delay9' */
  int32_T PipelineRegister_DSTATE;     /* '<S9>/PipelineRegister' */
  int32_T PipelineRegister1_DSTATE;    /* '<S9>/PipelineRegister1' */
  int32_T clockTickCounter;            /* '<Root>/Pulse Generator' */
  uint8_T delayMatch1_DSTATE_i;        /* '<S9>/delayMatch1' */
  boolean_T delayMatch_DSTATE_d;       /* '<S9>/delayMatch' */
  boolean_T Delay13_DSTATE;            /* '<S1>/Delay13' */
  boolean_T Delay3_DSTATE;             /* '<S1>/Delay3' */
  boolean_T DelayInput1_DSTATE;        /* '<S2>/Delay Input1' */
  boolean_T delayMatch4_DSTATE;        /* '<S1>/delayMatch4' */
  boolean_T RateTransition3_Buffer0;   /* '<Root>/Rate Transition3' */
} DW_gm_uz_park_transformation_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: reshape(fi("numerictype",numerictype(1,18,16),"fimath",fimath("RoundingMethod", "Floor","OverflowAction", "Wrap","ProductMode","FullPrecision","SumMode","FullPrecision"),"Value","[0;0.006134033203125;0.01226806640625;0.018402099609375;0.0245361328125;0.030670166015625;0.03680419921875;0.042938232421875;0.049072265625;0.0551910400390625;0.0613250732421875;0.06744384765625;0.0735626220703125;0.079681396484375;0.0858001708984375;0.0919036865234375;0.0980224609375;0.1041259765625;0.1102294921875;0.1163177490234375;0.122406005859375;0.1284942626953125;0.13458251953125;0.140655517578125;0.146728515625;0.152801513671875;0.1588592529296875;0.1649169921875;0.17095947265625;0.177001953125;0.18304443359375;0.1890716552734375;0.1950836181640625;0.20111083984375;0.2071075439453125;0.213104248046875;0.2191009521484375;0.2250823974609375;0.2310638427734375;0.237030029296875;0.24298095703125;0.248931884765625;0.2548675537109375;0.2607879638671875;0.2667083740234375;0.2726287841796875;0.2785186767578125;0.2844085693359375;0.290283203125;0.2961578369140625;0.302001953125;0.3078460693359375;0.3136749267578125;0.3195037841796875;0.3253173828125;0.3311004638671875;0.336883544921875;0.3426666259765625;0.348419189453125;0.354156494140625;0.359893798828125;0.3656158447265625;0.3713226318359375;0.37701416015625;0.3826904296875;0.3883514404296875;0.3939971923828125;0.399627685546875;0.405242919921875;0.4108428955078125;0.4164276123046875;0.4219970703125;0.42755126953125;0.4330902099609375;0.4386138916015625;0.444122314453125;0.449615478515625;0.455078125;0.460540771484375;0.465972900390625;0.4713897705078125;0.476806640625;0.482177734375;0.487548828125;0.4929046630859375;0.49822998046875;0.5035400390625;0.5088348388671875;0.51409912109375;0.5193634033203125;0.52459716796875;0.5298004150390625;0.535003662109375;0.5401763916015625;0.545318603515625;0.5504608154296875;0.555572509765625;0.5606689453125;0.56573486328125;0.5707855224609375;0.5758056640625;0.580810546875;0.5858001708984375;0.59075927734375;0.595703125;0.600616455078125;0.6055145263671875;0.610382080078125;0.615234375;0.62005615234375;0.6248626708984375;0.629638671875;0.6343994140625;0.639129638671875;0.643829345703125;0.6485137939453125;0.653167724609375;0.657806396484375;0.66241455078125;0.6670074462890625;0.6715545654296875;0.67608642578125;0.68060302734375;0.685089111328125;0.689544677734375;0.6939697265625;0.6983795166015625;0.7027587890625;0.7071075439453125;0.71142578125;0.715728759765625;0.720001220703125;0.7242431640625;0.7284698486328125;0.7326507568359375;0.73681640625;0.7409515380859375;0.74505615234375;0.7491302490234375;0.7531890869140625;0.7572021484375;0.761199951171875;0.765167236328125;0.76910400390625;0.77301025390625;0.776885986328125;0.780731201171875;0.7845611572265625;0.7883453369140625;0.7920989990234375;0.79583740234375;0.799530029296875;0.8032073974609375;0.806854248046875;0.810455322265625;0.8140411376953125;0.8175811767578125;0.82110595703125;0.8245849609375;0.8280487060546875;0.8314666748046875;0.834869384765625;0.838226318359375;0.841552734375;0.8448486328125;0.848114013671875;0.851348876953125;0.85455322265625;0.85772705078125;0.860870361328125;0.8639678955078125;0.8670501708984375;0.870086669921875;0.8730926513671875;0.876068115234375;0.8790130615234375;0.881927490234375;0.884796142578125;0.88763427734375;0.89044189453125;0.893218994140625;0.895965576171875;0.898681640625;0.9013519287109375;0.90399169921875;0.9066009521484375;0.9091644287109375;0.911712646484375;0.914215087890625;0.9166717529296875;0.9191131591796875;0.9215087890625;0.9238739013671875;0.92620849609375;0.9285125732421875;0.9307708740234375;0.9329986572265625;0.9351806640625;0.9373321533203125;0.939453125;0.9415435791015625;0.9435882568359375;0.9456024169921875;0.9475860595703125;0.94952392578125;0.9514312744140625;0.95330810546875;0.95513916015625;0.956939697265625;0.958709716796875;0.9604339599609375;0.962127685546875;0.963775634765625;0.96539306640625;0.96697998046875;0.9685211181640625;0.97003173828125;0.97149658203125;0.9729461669921875;0.974334716796875;0.9757080078125;0.9770355224609375;0.9783172607421875;0.9795684814453125;0.9807891845703125;0.981964111328125;0.9831085205078125;0.9842071533203125;0.9852752685546875;0.9863128662109375;0.9873046875;0.988250732421875;0.9891815185546875;0.99005126953125;0.99090576171875;0.9917144775390625;0.9924774169921875;0.9932098388671875;0.9939117431640625;0.99456787109375;0.99517822265625;0.9957733154296875;0.996307373046875;0.996826171875;0.997283935546875;0.9977264404296875;0.9981231689453125;0.99847412109375;0.9987945556640625;0.99908447265625;0.99932861328125;0.9995269775390625;0.99969482421875;0.9998321533203125;0.9999237060546875;0.9999847412109375]"), [1  256]))
   * Referenced by:
   *   '<S9>/Look-Up Table'
   *   '<S9>/Look-Up Table1'
   */
  int32_T pooled6[256];

  /* Pooled Parameter (Expression: fi("numerictype",numerictype(0,10,0),"fimath",fimath("RoundingMethod", "Floor","OverflowAction", "Wrap","ProductMode","FullPrecision","SumMode","FullPrecision"),"Value","[0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255]"))
   * Referenced by:
   *   '<S9>/Look-Up Table'
   *   '<S9>/Look-Up Table1'
   */
  uint16_T pooled11[256];
} ConstP_gm_uz_park_transformat_T;

/* Real-time Model Data Structure */
struct tag_RTM_gm_uz_park_transforma_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Block signals (default storage) */
extern B_gm_uz_park_transformation_T gm_uz_park_transformation_B;

/* Block states (default storage) */
extern DW_gm_uz_park_transformation_T gm_uz_park_transformation_DW;

/* Constant parameters (default storage) */
extern const ConstP_gm_uz_park_transformat_T gm_uz_park_transformatio_ConstP;

/* Model entry point functions */
extern void gm_uz_park_transformation_initialize(void);
extern void gm_uz_park_transformation_step(void);
extern void gm_uz_park_transformation_terminate(void);

/* Real-time Model object */
extern RT_MODEL_gm_uz_park_transform_T *const gm_uz_park_transformation_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'gm_uz_park_transformation'
 * '<S1>'   : 'gm_uz_park_transformation/uz_park_transformation'
 * '<S2>'   : 'gm_uz_park_transformation/uz_park_transformation/Detect Rise Positive'
 * '<S3>'   : 'gm_uz_park_transformation/uz_park_transformation/From'
 * '<S4>'   : 'gm_uz_park_transformation/uz_park_transformation/From1'
 * '<S5>'   : 'gm_uz_park_transformation/uz_park_transformation/From2'
 * '<S6>'   : 'gm_uz_park_transformation/uz_park_transformation/From3'
 * '<S7>'   : 'gm_uz_park_transformation/uz_park_transformation/Goto'
 * '<S8>'   : 'gm_uz_park_transformation/uz_park_transformation/Goto1'
 * '<S9>'   : 'gm_uz_park_transformation/uz_park_transformation/Sine HDL Optimized'
 * '<S10>'  : 'gm_uz_park_transformation/uz_park_transformation/Detect Rise Positive/Positive'
 * '<S11>'  : 'gm_uz_park_transformation/uz_park_transformation/Sine HDL Optimized/RAMDelayBalance'
 * '<S12>'  : 'gm_uz_park_transformation/uz_park_transformation/Sine HDL Optimized/RAMDelayBalance1'
 */
#endif                             /* RTW_HEADER_gm_uz_park_transformation_h_ */
