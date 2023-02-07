/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_FFTRecordedVoltage_api.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 07-Feb-2023 13:28:43
 */

/* Include Files */
#include "_coder_FFTRecordedVoltage_api.h"
#include "_coder_FFTRecordedVoltage_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131611U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "FFTRecordedVoltage",                                 /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real32_T y[10000]);

static real32_T c_emlrt_marshallIn(const emlrtStack *sp,
                                   const mxArray *sampletime,
                                   const char_T *identifier);

static real32_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId);

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real32_T ret[10000]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *data,
                             const char_T *identifier, real32_T y[10000]);

static const mxArray *emlrt_marshallOut(const real32_T u[5001]);

static real32_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId);

/* Function Definitions */
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real32_T y[10000]
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real32_T y[10000])
{
  e_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *sampletime
 *                const char_T *identifier
 * Return Type  : real32_T
 */
static real32_T c_emlrt_marshallIn(const emlrtStack *sp,
                                   const mxArray *sampletime,
                                   const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real32_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(sampletime), &thisId);
  emlrtDestroyArray(&sampletime);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real32_T
 */
static real32_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId)
{
  real32_T y;
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real32_T ret[10000]
 * Return Type  : void
 */
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real32_T ret[10000])
{
  static const int32_T dims[2] = {1, 10000};
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src,
                          (const char_T *)"single|double", false, 2U,
                          (void *)&dims[0]);
  emlrtImportArrayR2015b((emlrtCTX)sp, src, &ret[0], 4, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *data
 *                const char_T *identifier
 *                real32_T y[10000]
 * Return Type  : void
 */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *data,
                             const char_T *identifier, real32_T y[10000])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(data), &thisId, y);
  emlrtDestroyArray(&data);
}

/*
 * Arguments    : const real32_T u[5001]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real32_T u[5001])
{
  static const int32_T iv[2] = {1, 5001};
  const mxArray *m;
  const mxArray *y;
  int32_T i;
  real32_T *pData;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)emlrtMxGetData(m);
  for (i = 0; i < 5001; i++) {
    pData[i] = u[i];
  }
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real32_T
 */
static real32_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real32_T ret;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src,
                          (const char_T *)"single|double", false, 0U,
                          (void *)&dims);
  emlrtImportArrayR2015b((emlrtCTX)sp, src, &ret, 4, false);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const mxArray * const prhs[2]
 *                int32_T nlhs
 *                const mxArray *plhs[3]
 * Return Type  : void
 */
void FFTRecordedVoltage_api(const mxArray *const prhs[2], int32_T nlhs,
                            const mxArray *plhs[3])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  real32_T data[10000];
  real32_T amplitudes[5001];
  real32_T angles[5001];
  real32_T frequencies[5001];
  real32_T sampletime;
  st.tls = emlrtRootTLSGlobal;
  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "data", data);
  sampletime = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "sampletime");
  /* Invoke the target function */
  FFTRecordedVoltage(data, sampletime, frequencies, amplitudes, angles);
  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(frequencies);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(amplitudes);
  }
  if (nlhs > 2) {
    plhs[2] = emlrt_marshallOut(angles);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void FFTRecordedVoltage_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  FFTRecordedVoltage_xil_terminate();
  FFTRecordedVoltage_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void FFTRecordedVoltage_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void FFTRecordedVoltage_terminate(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_FFTRecordedVoltage_api.c
 *
 * [EOF]
 */
