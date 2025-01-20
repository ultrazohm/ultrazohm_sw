/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.21
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Fri Jan 17 16:34:11 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "uz_codegen0.h"

extern real_T rt_hypotd(real_T u0, real_T u1);

/* Forward declaration for local functions */
static void factoryConstruct(sSzLoP8tvZHiR1V2perTtWD *obj);
static real_T xnrm2(int32_T n, const real_T x[90], int32_T ix0, DW *rtDW);
static real_T xzlarfg(int32_T n, real_T *alpha1, real_T x[90], int32_T ix0, DW
                      *rtDW);
static void xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau, real_T C[90],
                   int32_T ic0, real_T work[10], DW *rtDW);
static void qrf(real_T A[90], int32_T ia0, int32_T m, int32_T n, int32_T nfxd,
                real_T tau[9], DW *rtDW);
static void qrpf(real_T A[90], int32_T ia0, int32_T m, int32_T n, int32_T nfxd,
                 real_T tau[9], int32_T jpvt[10], DW *rtDW);
static void xzgeqp3(real_T A[90], int32_T ia0, int32_T m, int32_T n, int32_T
                    jpvt[10], real_T tau[9], DW *rtDW);
static void computeQ_(sCS11Pe0E6xKX8jGoaG4cLG *obj, int32_T nrows, DW *rtDW);
static int32_T ComputeNumDependentEq_(sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, DW
  *rtDW);
static void IndexOfDependentEq_(int32_T depIdx[10], int32_T nDep,
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, int32_T mRows, int32_T nCols, DW *rtDW);
static void countsort(int32_T x[10], int32_T xLen, int32_T workspace[10],
                      int32_T xMin, int32_T xMax);
static void moveConstraint_(stxriBK2jD81NCGacZ0b8HD *obj, int32_T
  idx_global_start, int32_T idx_global_dest);
static void removeEqConstr(stxriBK2jD81NCGacZ0b8HD *obj, int32_T idx_global);
static void RemoveDependentEq_(snRDwUdgrIx9qNga56nZ8DE *memspace, int32_T
  *nDepInd, stxriBK2jD81NCGacZ0b8HD *workingset, sCS11Pe0E6xKX8jGoaG4cLG
  *qrmanager, DW *rtDW);
static void removeAllIneqConstr(stxriBK2jD81NCGacZ0b8HD *obj);
static void RemoveDependentIneq_(stxriBK2jD81NCGacZ0b8HD *workingset,
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, snRDwUdgrIx9qNga56nZ8DE *memspace, real_T
  tolfactor, DW *rtDW);
static void factorQR_f(sCS11Pe0E6xKX8jGoaG4cLG *obj, const real_T A[80], int32_T
  mrows, int32_T ncols, int32_T ldA, DW *rtDW);
static void factorQR(sCS11Pe0E6xKX8jGoaG4cLG *obj, int32_T mrows, int32_T ncols,
                     DW *rtDW);
static void xgemv(int32_T m, int32_T n, const real_T A[56], int32_T lda, const
                  real_T x[80], real_T y[10], DW *rtDW);
static void xgemv_p(int32_T m, int32_T n, const real_T A[16], int32_T lda, const
                    real_T x[80], real_T y[10], DW *rtDW);
static real_T maxConstraintViolation(stxriBK2jD81NCGacZ0b8HD *obj, const real_T
  x[80], DW *rtDW);
static void xgemv_py(int32_T m, int32_T n, const real_T A[56], int32_T lda,
                     const real_T x[80], real_T y[10], DW *rtDW);
static void xgemv_pym(int32_T m, int32_T n, const real_T A[16], int32_T lda,
                      const real_T x[80], real_T y[10], DW *rtDW);
static real_T maxConstraintViolation_p(stxriBK2jD81NCGacZ0b8HD *obj, const
  real_T x[80], DW *rtDW);
static void feasibleX0ForWorkingSet(real_T workspace[80], real_T xCurrent[8],
  stxriBK2jD81NCGacZ0b8HD *workingset, sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, DW
  *rtDW);
static void xgemv_pyma(int32_T m, int32_T n, const real_T A[56], int32_T lda,
  const real_T x[8], real_T y[10], DW *rtDW);
static void xgemv_pyma2(int32_T m, int32_T n, const real_T A[16], int32_T lda,
  const real_T x[8], real_T y[10], DW *rtDW);
static real_T maxConstraintViolation_pn(stxriBK2jD81NCGacZ0b8HD *obj, const
  real_T x[8], DW *rtDW);
static void PresolveWorkingSet(sVm5xLhdFDU5OIlGg0pTc4E *solution,
  snRDwUdgrIx9qNga56nZ8DE *memspace, stxriBK2jD81NCGacZ0b8HD *workingset,
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, DW *rtDW);
static void modifyOverheadPhaseOne_(stxriBK2jD81NCGacZ0b8HD *obj);
static void setProblemType(stxriBK2jD81NCGacZ0b8HD *obj, int32_T PROBLEM_TYPE);
static void linearForm_(boolean_T obj_hasLinear, int32_T obj_nvar, real_T
  workspace[80], const real_T H[49], const real_T f[7], const real_T x[8]);
static real_T computeFval(const shohwUBaOGHF036TMzc1KEH *obj, real_T workspace
  [80], const real_T H[49], const real_T f[7], const real_T x[8]);
static void xgemv_pyma2z(int32_T m, int32_T n, const real_T A[49], int32_T lda,
  const real_T x[8], real_T y[7]);
static void computeGrad_StoreHx(shohwUBaOGHF036TMzc1KEH *obj, const real_T H[49],
  const real_T f[7], const real_T x[8]);
static real_T computeFval_ReuseHx(const shohwUBaOGHF036TMzc1KEH *obj, real_T
  workspace[80], const real_T f[7], const real_T x[8]);
static void printHeader(void);
static void printInitialInfo(int32_T PROBLEM_TYPE, real_T solution_fstar,
  int32_T solution_iterations, int32_T workingset_nActiveConstr);
static void xrotg(real_T *a, real_T *b, real_T *c, real_T *s, DW *rtDW);
static void deleteColMoveEnd(sCS11Pe0E6xKX8jGoaG4cLG *obj, int32_T idx, DW *rtDW);
static void computeProjectedHessian(const real_T H[49], sSzLoP8tvZHiR1V2perTtWD *
  cholmanager, const sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, snRDwUdgrIx9qNga56nZ8DE
  *memspace, DW *rtDW);
static int32_T ixamax(int32_T n, const real_T x[81], int32_T incx);
static void fullColLDL2_(sSzLoP8tvZHiR1V2perTtWD *obj, int32_T LD_offset,
  int32_T NColsRemain, real_T REG_PRIMAL);
static void xgemv_pyma2zx(int32_T m, int32_T n, const real_T A[81], int32_T ia0,
  int32_T lda, const real_T x[80], real_T y[8]);
static void compute_deltax(const real_T H[49], sVm5xLhdFDU5OIlGg0pTc4E *solution,
  snRDwUdgrIx9qNga56nZ8DE *memspace, const sCS11Pe0E6xKX8jGoaG4cLG *qrmanager,
  sSzLoP8tvZHiR1V2perTtWD *cholmanager, const shohwUBaOGHF036TMzc1KEH *objective,
  DW *rtDW);
static real_T xnrm2_j(int32_T n, const real_T x[8]);
static void xgemv_pyma2zxi(int32_T m, int32_T n, const real_T A[56], int32_T lda,
  const real_T x[8], real_T y[80]);
static void xgemv_pyma2zxid(int32_T m, int32_T n, const real_T A[56], int32_T
  lda, const real_T x[8], real_T y[80]);
static void ratiotest(const real_T solution_xstar[8], const real_T
                      solution_searchDir[8], real_T workspace[80], int32_T
                      workingset_nVar, int32_T workingset_ldA, const real_T
                      workingset_Aineq[56], const real_T workingset_bineq[7],
                      const real_T workingset_lb[8], const real_T workingset_ub
                      [8], const int32_T workingset_indexLB[8], const int32_T
                      workingset_indexUB[8], const int32_T workingset_sizes[5],
                      const int32_T workingset_isActiveIdx[6], const boolean_T
                      workingset_isActiveConstr[10], const int32_T
                      workingset_nWConstr[5], boolean_T isPhaseOne, real_T
                      tolcon, real_T *toldelta, real_T toltau, real_T *alpha,
                      boolean_T *newBlocking, int32_T *constrType, int32_T
                      *constrIdx, DW *rtDW);
static void feasibleratiotest(const real_T solution_xstar[8], const real_T
  solution_searchDir[8], real_T workspace[80], int32_T workingset_nVar, int32_T
  workingset_ldA, const real_T workingset_Aineq[56], const real_T
  workingset_bineq[7], const real_T workingset_lb[8], const real_T
  workingset_ub[8], const int32_T workingset_indexLB[8], const int32_T
  workingset_indexUB[8], const int32_T workingset_sizes[5], const int32_T
  workingset_isActiveIdx[6], const boolean_T workingset_isActiveConstr[10],
  const int32_T workingset_nWConstr[5], boolean_T isPhaseOne, real_T tolcon,
  real_T *alpha, boolean_T *newBlocking, int32_T *constrType, int32_T *constrIdx,
  DW *rtDW);
static void checkUnboundedOrIllPosed(sVm5xLhdFDU5OIlGg0pTc4E *solution, const
  shohwUBaOGHF036TMzc1KEH *objective);
static void addBoundToActiveSetMatrix_(stxriBK2jD81NCGacZ0b8HD *obj, int32_T
  TYPE, int32_T idx_local);
static void compute_lambda(real_T workspace[80], sVm5xLhdFDU5OIlGg0pTc4E
  *solution, const shohwUBaOGHF036TMzc1KEH *objective, const
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager);
static void checkStoppingAndUpdateFval(int32_T *activeSetChangeID, const real_T
  f[7], sVm5xLhdFDU5OIlGg0pTc4E *solution, snRDwUdgrIx9qNga56nZ8DE *memspace,
  const shohwUBaOGHF036TMzc1KEH *objective, stxriBK2jD81NCGacZ0b8HD *workingset,
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, real_T options_ObjectiveLimit, real_T
  options_ConstraintTolerance, int32_T runTimeOptions_MaxIterations, real_T
  runTimeOptions_ConstrRelTolFact, boolean_T updateFval, DW *rtDW);
static void computeFirstOrderOpt(sVm5xLhdFDU5OIlGg0pTc4E *solution, const
  shohwUBaOGHF036TMzc1KEH *objective, int32_T workingset_nVar, int32_T
  workingset_ldA, const real_T workingset_ATwset[80], int32_T
  workingset_nActiveConstr, real_T workspace[80]);
static void printInfo(boolean_T newBlocking, int32_T PROBLEM_TYPE, real_T alpha,
                      real_T stepNorm, int32_T activeConstrChangedType, int32_T
                      localActiveConstrIdx, int32_T activeSetChangeID, real_T
                      solution_fstar, real_T solution_firstorderopt, real_T
                      solution_maxConstr, int32_T solution_iterations, const
                      int32_T workingset_indexLB[8], const int32_T
                      workingset_indexUB[8], int32_T workingset_nActiveConstr);
static void iterate(const real_T H[49], const real_T f[7],
                    sVm5xLhdFDU5OIlGg0pTc4E *solution, snRDwUdgrIx9qNga56nZ8DE
                    *memspace, stxriBK2jD81NCGacZ0b8HD *workingset,
                    sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, sSzLoP8tvZHiR1V2perTtWD *
                    cholmanager, shohwUBaOGHF036TMzc1KEH *objective, boolean_T
                    options_IterDisplayQP, real_T options_PricingTolerance,
                    real_T options_ObjectiveLimit, real_T
                    options_ConstraintTolerance, real_T options_StepTolerance,
                    const sL9bDKomAYkxZSVrG9w6En runTimeOptions, DW *rtDW);
static void phaseone(const real_T H[49], const real_T f[7],
                     sVm5xLhdFDU5OIlGg0pTc4E *solution, snRDwUdgrIx9qNga56nZ8DE *
                     memspace, stxriBK2jD81NCGacZ0b8HD *workingset,
                     sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, sSzLoP8tvZHiR1V2perTtWD
                     *cholmanager, const sL9bDKomAYkxZSVrG9w6En *runTimeOptions,
                     shohwUBaOGHF036TMzc1KEH *objective, s4lHOiXA0GHbse0IgoBY6ZF
                     *options, DW *rtDW);
static int32_T ComputeNumDependentEq__d(sCS11Pe0E6xKX8jGoaG4cLG *qrmanager,
  const real_T beqf[10], int32_T mConstr, int32_T nVar, real_T tolfactor, DW
  *rtDW);
static void IndexOfDependentEq__i(int32_T depIdx[10], int32_T mFixed, int32_T
  nDep, sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, int32_T mRows, int32_T nCols, DW
  *rtDW);
static int32_T RemoveDependentEq__b(snRDwUdgrIx9qNga56nZ8DE *memspace,
  stxriBK2jD81NCGacZ0b8HD *workingset, sCS11Pe0E6xKX8jGoaG4cLG *qrmanager,
  real_T tolfactor, DW *rtDW);
static void PresolveWorkingSet_l(sVm5xLhdFDU5OIlGg0pTc4E *solution,
  snRDwUdgrIx9qNga56nZ8DE *memspace, stxriBK2jD81NCGacZ0b8HD *workingset,
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, const s4lHOiXA0GHbse0IgoBY6ZF *options, DW
  *rtDW);
static boolean_T strcmp_m(const char_T a[8]);
static void phaseone_j(const real_T H[49], const real_T f[7],
  sVm5xLhdFDU5OIlGg0pTc4E *solution, snRDwUdgrIx9qNga56nZ8DE *memspace,
  stxriBK2jD81NCGacZ0b8HD *workingset, sCS11Pe0E6xKX8jGoaG4cLG *qrmanager,
  sSzLoP8tvZHiR1V2perTtWD *cholmanager, shohwUBaOGHF036TMzc1KEH *objective,
  s4lHOiXA0GHbse0IgoBY6ZF *options, const sL9bDKomAYkxZSVrG9w6En *runTimeOptions,
  DW *rtDW);
static void driver(const real_T H[49], const real_T f[7],
                   sVm5xLhdFDU5OIlGg0pTc4E *solution, snRDwUdgrIx9qNga56nZ8DE
                   *memspace, sSzLoP8tvZHiR1V2perTtWD *cholmanager,
                   sL9bDKomAYkxZSVrG9w6En runTimeOptions,
                   stxriBK2jD81NCGacZ0b8HD *workingset, sCS11Pe0E6xKX8jGoaG4cLG *
                   qrmanager, shohwUBaOGHF036TMzc1KEH *objective, DW *rtDW);
static void linearForm__a(boolean_T obj_hasLinear, int32_T obj_nvar, real_T
  workspace[8], const real_T H[49], const real_T f[7], const real_T x[8]);
static void quadprog(const real_T H[49], const real_T f[7], const real_T x0[7],
                     real_T x[7], real_T *fval, real_T *exitflag, char_T
                     output_algorithm[10], real_T *output_firstorderopt, real_T *
                     output_constrviolation, real_T *output_iterations, DW *rtDW);

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void factoryConstruct(sSzLoP8tvZHiR1V2perTtWD *obj)
{
  obj->ldm = 9;
  obj->ndims = 0;
  obj->info = 0;
  obj->scaleFactor = 1.0;
  obj->ConvexCheck = true;
  obj->regTol_ = 0.0;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real_T xnrm2(int32_T n, const real_T x[90], int32_T ix0, DW *rtDW)
{
  real_T y;
  int32_T k;
  int32_T kend;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      rtDW->scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        rtDW->absxk = fabs(x[k - 1]);
        if (rtDW->absxk > rtDW->scale) {
          rtDW->t = rtDW->scale / rtDW->absxk;
          y = y * rtDW->t * rtDW->t + 1.0;
          rtDW->scale = rtDW->absxk;
        } else {
          rtDW->t = rtDW->absxk / rtDW->scale;
          y += rtDW->t * rtDW->t;
        }
      }

      y = rtDW->scale * sqrt(y);
    }
  }

  return y;
}

real_T rt_hypotd(real_T u0, real_T u1)
{
  real_T a;
  real_T b;
  real_T y;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = sqrt(a * a + 1.0) * b;
  } else if (a > b) {
    b /= a;
    y = sqrt(b * b + 1.0) * a;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real_T xzlarfg(int32_T n, real_T *alpha1, real_T x[90], int32_T ix0, DW
                      *rtDW)
{
  real_T tau;
  int32_T b_k;
  int32_T c_k;
  int32_T knt;
  tau = 0.0;
  if (n > 0) {
    rtDW->xnorm = xnrm2(n - 1, x, ix0, rtDW);
    if (rtDW->xnorm != 0.0) {
      rtDW->xnorm = rt_hypotd(*alpha1, rtDW->xnorm);
      if (*alpha1 >= 0.0) {
        rtDW->xnorm = -rtDW->xnorm;
      }

      if (fabs(rtDW->xnorm) < 1.0020841800044864E-292) {
        knt = -1;
        c_k = (ix0 + n) - 2;
        do {
          knt++;
          for (b_k = ix0; b_k <= c_k; b_k++) {
            x[b_k - 1] *= 9.9792015476736E+291;
          }

          rtDW->xnorm *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while (fabs(rtDW->xnorm) < 1.0020841800044864E-292);

        rtDW->xnorm = rt_hypotd(*alpha1, xnrm2(n - 1, x, ix0, rtDW));
        if (*alpha1 >= 0.0) {
          rtDW->xnorm = -rtDW->xnorm;
        }

        tau = (rtDW->xnorm - *alpha1) / rtDW->xnorm;
        *alpha1 = 1.0 / (*alpha1 - rtDW->xnorm);
        for (b_k = ix0; b_k <= c_k; b_k++) {
          x[b_k - 1] *= *alpha1;
        }

        for (c_k = 0; c_k <= knt; c_k++) {
          rtDW->xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = rtDW->xnorm;
      } else {
        tau = (rtDW->xnorm - *alpha1) / rtDW->xnorm;
        *alpha1 = 1.0 / (*alpha1 - rtDW->xnorm);
        knt = (ix0 + n) - 2;
        for (c_k = ix0; c_k <= knt; c_k++) {
          x[c_k - 1] *= *alpha1;
        }

        *alpha1 = rtDW->xnorm;
      }
    }
  }

  return tau;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau, real_T C[90],
                   int32_T ic0, real_T work[10], DW *rtDW)
{
  int32_T coltop;
  int32_T d;
  int32_T exitg1;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T jy;
  int32_T lastc;
  int32_T lastv;
  boolean_T exitg2;
  if (tau != 0.0) {
    lastv = m;
    lastc = iv0 + m;
    while ((lastv > 0) && (C[lastc - 2] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = n - 1;
    exitg2 = false;
    while ((!exitg2) && (lastc + 1 > 0)) {
      coltop = lastc * 9 + ic0;
      jy = coltop;
      do {
        exitg1 = 0;
        if (jy <= (coltop + lastv) - 1) {
          if (C[jy - 1] != 0.0) {
            exitg1 = 1;
          } else {
            jy++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = -1;
  }

  if (lastv > 0) {
    if (lastc + 1 != 0) {
      for (coltop = 0; coltop <= lastc; coltop++) {
        work[coltop] = 0.0;
      }

      coltop = 0;
      jy = 9 * lastc + ic0;
      for (iac = ic0; iac <= jy; iac += 9) {
        ix = iv0;
        rtDW->c_f = 0.0;
        d = (iac + lastv) - 1;
        for (ia = iac; ia <= d; ia++) {
          rtDW->c_f += C[ia - 1] * C[ix - 1];
          ix++;
        }

        work[coltop] += rtDW->c_f;
        coltop++;
      }
    }

    if (-tau != 0.0) {
      coltop = ic0 - 1;
      jy = 0;
      for (iac = 0; iac <= lastc; iac++) {
        if (work[jy] != 0.0) {
          rtDW->c_f = work[jy] * -tau;
          ix = iv0;
          d = lastv + coltop;
          for (ia = coltop; ia < d; ia++) {
            C[ia] += C[ix - 1] * rtDW->c_f;
            ix++;
          }
        }

        jy++;
        coltop += 9;
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void qrf(real_T A[90], int32_T ia0, int32_T m, int32_T n, int32_T nfxd,
                real_T tau[9], DW *rtDW)
{
  int32_T i;
  int32_T ii;
  int32_T mmi;
  memset(&rtDW->work[0], 0, 10U * sizeof(real_T));
  for (i = 0; i < nfxd; i++) {
    ii = ((i * 9 + ia0) + i) - 1;
    mmi = m - i;
    if (i + 1 < m) {
      rtDW->b_atmp = A[ii];
      tau[i] = xzlarfg(mmi, &rtDW->b_atmp, A, ii + 2, rtDW);
      A[ii] = rtDW->b_atmp;
    } else {
      tau[i] = 0.0;
    }

    if (i + 1 < n) {
      rtDW->b_atmp = A[ii];
      A[ii] = 1.0;
      xzlarf(mmi, (n - i) - 1, ii + 1, tau[i], A, ii + 10, rtDW->work, rtDW);
      A[ii] = rtDW->b_atmp;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void qrpf(real_T A[90], int32_T ia0, int32_T m, int32_T n, int32_T nfxd,
                 real_T tau[9], int32_T jpvt[10], DW *rtDW)
{
  int32_T i;
  int32_T ii_tmp;
  int32_T ix;
  int32_T iy;
  int32_T mmi;
  int32_T nmi;
  int32_T pvt;
  if (m < n) {
    rtDW->minmn_c = m;
  } else {
    rtDW->minmn_c = n;
  }

  memset(&rtDW->work_c[0], 0, 10U * sizeof(real_T));
  memset(&rtDW->vn1[0], 0, 10U * sizeof(real_T));
  memset(&rtDW->vn2[0], 0, 10U * sizeof(real_T));
  i = ia0 + nfxd;
  for (mmi = nfxd; mmi < n; mmi++) {
    rtDW->vn1[mmi] = xnrm2(m - nfxd, A, mmi * 9 + i, rtDW);
    rtDW->vn2[mmi] = rtDW->vn1[mmi];
  }

  for (i = nfxd; i < rtDW->minmn_c; i++) {
    ii_tmp = i * 9 + ia0;
    rtDW->ii = (ii_tmp + i) - 1;
    nmi = n - i;
    mmi = m - i;
    if (nmi < 1) {
      pvt = -1;
    } else {
      pvt = 0;
      if (nmi > 1) {
        ix = i;
        rtDW->smax = fabs(rtDW->vn1[i]);
        for (iy = 2; iy <= nmi; iy++) {
          ix++;
          rtDW->temp2 = fabs(rtDW->vn1[ix]);
          if (rtDW->temp2 > rtDW->smax) {
            pvt = iy - 1;
            rtDW->smax = rtDW->temp2;
          }
        }
      }
    }

    pvt += i;
    if (pvt + 1 != i + 1) {
      ix = (pvt * 9 + ia0) - 1;
      iy = ii_tmp - 1;
      for (ii_tmp = 0; ii_tmp < m; ii_tmp++) {
        rtDW->smax = A[ix];
        A[ix] = A[iy];
        A[iy] = rtDW->smax;
        ix++;
        iy++;
      }

      ix = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = ix;
      rtDW->vn1[pvt] = rtDW->vn1[i];
      rtDW->vn2[pvt] = rtDW->vn2[i];
    }

    if (i + 1 < m) {
      rtDW->smax = A[rtDW->ii];
      tau[i] = xzlarfg(mmi, &rtDW->smax, A, rtDW->ii + 2, rtDW);
      A[rtDW->ii] = rtDW->smax;
    } else {
      tau[i] = 0.0;
    }

    if (i + 1 < n) {
      rtDW->smax = A[rtDW->ii];
      A[rtDW->ii] = 1.0;
      xzlarf(mmi, nmi - 1, rtDW->ii + 1, tau[i], A, rtDW->ii + 10, rtDW->work_c,
             rtDW);
      A[rtDW->ii] = rtDW->smax;
    }

    rtDW->ii = i + 1;
    while (rtDW->ii + 1 <= n) {
      nmi = (ia0 + i) + rtDW->ii * 9;
      if (rtDW->vn1[rtDW->ii] != 0.0) {
        rtDW->smax = fabs(A[nmi - 1]) / rtDW->vn1[rtDW->ii];
        rtDW->smax = 1.0 - rtDW->smax * rtDW->smax;
        if (rtDW->smax < 0.0) {
          rtDW->smax = 0.0;
        }

        rtDW->temp2 = rtDW->vn1[rtDW->ii] / rtDW->vn2[rtDW->ii];
        rtDW->temp2 = rtDW->temp2 * rtDW->temp2 * rtDW->smax;
        if (rtDW->temp2 <= 1.4901161193847656E-8) {
          if (i + 1 < m) {
            rtDW->vn1[rtDW->ii] = xnrm2(mmi - 1, A, nmi + 1, rtDW);
            rtDW->vn2[rtDW->ii] = rtDW->vn1[rtDW->ii];
          } else {
            rtDW->vn1[rtDW->ii] = 0.0;
            rtDW->vn2[rtDW->ii] = 0.0;
          }
        } else {
          rtDW->vn1[rtDW->ii] *= sqrt(rtDW->smax);
        }
      }

      rtDW->ii++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xzgeqp3(real_T A[90], int32_T ia0, int32_T m, int32_T n, int32_T
                    jpvt[10], real_T tau[9], DW *rtDW)
{
  if (m < n) {
    rtDW->minmn = m;
  } else {
    rtDW->minmn = n;
  }

  memset(&tau[0], 0, 9U * sizeof(real_T));
  if (rtDW->minmn < 1) {
    rtDW->minmn = 0;
    while (rtDW->minmn <= n - 1) {
      jpvt[rtDW->minmn] = rtDW->minmn + 1;
      rtDW->minmn++;
    }
  } else {
    rtDW->i_h = -1;
    rtDW->c_j_c = 0;
    while (rtDW->c_j_c <= n - 1) {
      if (jpvt[rtDW->c_j_c] != 0) {
        rtDW->i_h++;
        if (rtDW->c_j_c + 1 != rtDW->i_h + 1) {
          rtDW->ix_m = (rtDW->c_j_c * 9 + ia0) - 1;
          rtDW->iy_m = (rtDW->i_h * 9 + ia0) - 1;
          rtDW->k_j = 0;
          while (rtDW->k_j <= m - 1) {
            rtDW->temp_c = A[rtDW->ix_m];
            A[rtDW->ix_m] = A[rtDW->iy_m];
            A[rtDW->iy_m] = rtDW->temp_c;
            rtDW->ix_m++;
            rtDW->iy_m++;
            rtDW->k_j++;
          }

          jpvt[rtDW->c_j_c] = jpvt[rtDW->i_h];
          jpvt[rtDW->i_h] = rtDW->c_j_c + 1;
        } else {
          jpvt[rtDW->c_j_c] = rtDW->c_j_c + 1;
        }
      } else {
        jpvt[rtDW->c_j_c] = rtDW->c_j_c + 1;
      }

      rtDW->c_j_c++;
    }

    if (rtDW->i_h + 1 < rtDW->minmn) {
      rtDW->i_h++;
    } else {
      rtDW->i_h = rtDW->minmn;
    }

    qrf(A, ia0, m, n, rtDW->i_h, tau, rtDW);
    if (rtDW->i_h < rtDW->minmn) {
      qrpf(A, ia0, m, n, rtDW->i_h, tau, jpvt, rtDW);
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void computeQ_(sCS11Pe0E6xKX8jGoaG4cLG *obj, int32_T nrows, DW *rtDW)
{
  int32_T b_ia;
  int32_T b_ix;
  int32_T coltop;
  int32_T e;
  int32_T exitg1;
  int32_T i;
  int32_T iQR0;
  int32_T ia;
  int32_T iaii;
  int32_T idx;
  int32_T itau;
  int32_T ix;
  int32_T jA;
  int32_T lastc;
  int32_T lastv;
  boolean_T exitg2;
  for (idx = 0; idx < obj->minRowCol; idx++) {
    iQR0 = obj->ldq * idx + idx;
    itau = obj->mrows - idx;
    for (i = 1; i - 1 <= itau - 2; i++) {
      iaii = iQR0 + i;
      obj->Q[iaii] = obj->QR[iaii];
    }
  }

  idx = obj->mrows;
  iQR0 = obj->ldq;
  if (nrows >= 1) {
    for (itau = obj->minRowCol; itau < nrows; itau++) {
      i = itau * iQR0;
      for (iaii = 0; iaii < idx; iaii++) {
        obj->Q[i + iaii] = 0.0;
      }

      obj->Q[i + itau] = 1.0;
    }

    itau = obj->minRowCol - 1;
    memset(&rtDW->work_k[0], 0, 9U * sizeof(real_T));
    for (i = obj->minRowCol; i >= 1; i--) {
      iaii = ((i - 1) * iQR0 + i) - 1;
      if (i < nrows) {
        obj->Q[iaii] = 1.0;
        lastv = idx - i;
        jA = (iaii + iQR0) + 1;
        if (obj->tau[itau] != 0.0) {
          lastc = iaii + lastv;
          while ((lastv + 1 > 0) && (obj->Q[lastc] == 0.0)) {
            lastv--;
            lastc--;
          }

          lastc = (nrows - i) - 1;
          exitg2 = false;
          while ((!exitg2) && (lastc + 1 > 0)) {
            coltop = lastc * iQR0 + jA;
            b_ia = coltop;
            do {
              exitg1 = 0;
              if (b_ia <= coltop + lastv) {
                if (obj->Q[b_ia - 1] != 0.0) {
                  exitg1 = 1;
                } else {
                  b_ia++;
                }
              } else {
                lastc--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          lastv = -1;
          lastc = -1;
        }

        if (lastv + 1 > 0) {
          if (lastc + 1 != 0) {
            for (coltop = 0; coltop <= lastc; coltop++) {
              rtDW->work_k[coltop] = 0.0;
            }

            coltop = 0;
            b_ia = iQR0 * lastc + jA;
            b_ix = jA;
            while (((iQR0 > 0) && (b_ix <= b_ia)) || ((iQR0 < 0) && (b_ix >=
                     b_ia))) {
              ix = iaii;
              rtDW->d_c = 0.0;
              e = b_ix + lastv;
              for (ia = b_ix; ia <= e; ia++) {
                rtDW->d_c += obj->Q[ia - 1] * obj->Q[ix];
                ix++;
              }

              rtDW->work_k[coltop] += rtDW->d_c;
              coltop++;
              b_ix += iQR0;
            }
          }

          if (-obj->tau[itau] != 0.0) {
            coltop = 0;
            for (b_ia = 0; b_ia <= lastc; b_ia++) {
              if (rtDW->work_k[coltop] != 0.0) {
                rtDW->d_c = rtDW->work_k[coltop] * -obj->tau[itau];
                b_ix = iaii;
                ix = lastv + jA;
                for (e = jA; e <= ix; e++) {
                  obj->Q[e - 1] += obj->Q[b_ix] * rtDW->d_c;
                  b_ix++;
                }
              }

              coltop++;
              jA += iQR0;
            }
          }
        }
      }

      if (i < idx) {
        lastv = ((iaii + idx) - i) + 1;
        for (jA = iaii + 1; jA < lastv; jA++) {
          obj->Q[jA] *= -obj->tau[itau];
        }
      }

      obj->Q[iaii] = 1.0 - obj->tau[itau];
      for (lastv = 0; lastv <= i - 2; lastv++) {
        obj->Q[(iaii - lastv) - 1] = 0.0;
      }

      itau--;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static int32_T ComputeNumDependentEq_(sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, DW
  *rtDW)
{
  int32_T numDependent;
  boolean_T exitg1;
  numDependent = 0;
  for (rtDW->idxDiag = 0; rtDW->idxDiag < 7; rtDW->idxDiag++) {
    qrmanager->jpvt[rtDW->idxDiag] = 0;
  }

  qrmanager->usedPivoting = true;
  qrmanager->mrows = 2;
  qrmanager->ncols = 7;
  qrmanager->minRowCol = 2;
  xzgeqp3(qrmanager->QR, 1, 2, 7, qrmanager->jpvt, qrmanager->tau, rtDW);
  rtDW->idxDiag = qrmanager->ldq + 1;
  while ((rtDW->idxDiag + 1 > 0) && (fabs(qrmanager->QR[rtDW->idxDiag]) <
          1.5543122344752192E-13)) {
    rtDW->idxDiag = (rtDW->idxDiag - qrmanager->ldq) - 1;
    numDependent++;
  }

  if (numDependent > 0) {
    computeQ_(qrmanager, qrmanager->mrows, rtDW);
    rtDW->idxDiag = 0;
    exitg1 = false;
    while ((!exitg1) && (rtDW->idxDiag <= numDependent - 1)) {
      if (fabs(qrmanager->Q[(1 - rtDW->idxDiag) * qrmanager->ldq] * 0.5) >=
          1.5543122344752192E-13) {
        numDependent = -1;
        exitg1 = true;
      } else {
        rtDW->idxDiag++;
      }
    }
  }

  return numDependent;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void IndexOfDependentEq_(int32_T depIdx[10], int32_T nDep,
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, int32_T mRows, int32_T nCols, DW *rtDW)
{
  rtDW->b_idx = 0;
  while (rtDW->b_idx <= nCols - 1) {
    qrmanager->jpvt[rtDW->b_idx] = 0;
    rtDW->b_idx++;
  }

  if (mRows * nCols == 0) {
    qrmanager->mrows = mRows;
    qrmanager->ncols = nCols;
    qrmanager->minRowCol = 0;
  } else {
    qrmanager->usedPivoting = true;
    qrmanager->mrows = mRows;
    qrmanager->ncols = nCols;
    if (mRows < nCols) {
      qrmanager->minRowCol = mRows;
    } else {
      qrmanager->minRowCol = nCols;
    }

    xzgeqp3(qrmanager->QR, 1, mRows, nCols, qrmanager->jpvt, qrmanager->tau,
            rtDW);
  }

  rtDW->b_idx = 0;
  while (rtDW->b_idx <= nDep - 1) {
    depIdx[rtDW->b_idx] = qrmanager->jpvt[(nCols - nDep) + rtDW->b_idx];
    rtDW->b_idx++;
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void countsort(int32_T x[10], int32_T xLen, int32_T workspace[10],
                      int32_T xMin, int32_T xMax)
{
  int32_T b_idxW;
  int32_T idxEnd;
  int32_T idxStart;
  int32_T maxOffset_tmp;
  if ((xLen > 1) && (xMax > xMin)) {
    maxOffset_tmp = xMax - xMin;
    for (idxStart = 0; idxStart <= maxOffset_tmp; idxStart++) {
      workspace[idxStart] = 0;
    }

    for (idxStart = 0; idxStart < xLen; idxStart++) {
      idxEnd = x[idxStart] - xMin;
      workspace[idxEnd]++;
    }

    for (idxStart = 1; idxStart < maxOffset_tmp + 1; idxStart++) {
      workspace[idxStart] += workspace[idxStart - 1];
    }

    idxStart = 0;
    idxEnd = workspace[0];
    for (b_idxW = 0; b_idxW < maxOffset_tmp; b_idxW++) {
      while (idxStart + 1 <= idxEnd) {
        x[idxStart] = b_idxW + xMin;
        idxStart++;
      }

      idxStart = workspace[b_idxW];
      idxEnd = workspace[b_idxW + 1];
    }

    while (idxStart + 1 <= idxEnd) {
      x[idxStart] = xMax;
      idxStart++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void moveConstraint_(stxriBK2jD81NCGacZ0b8HD *obj, int32_T
  idx_global_start, int32_T idx_global_dest)
{
  int32_T b_idx;
  obj->Wid[idx_global_dest - 1] = obj->Wid[idx_global_start - 1];
  obj->Wlocalidx[idx_global_dest - 1] = obj->Wlocalidx[idx_global_start - 1];
  for (b_idx = 0; b_idx < obj->nVar; b_idx++) {
    obj->ATwset[b_idx + obj->ldA * (idx_global_dest - 1)] = obj->ATwset
      [(idx_global_start - 1) * obj->ldA + b_idx];
  }

  obj->bwset[idx_global_dest - 1] = obj->bwset[idx_global_start - 1];
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void removeEqConstr(stxriBK2jD81NCGacZ0b8HD *obj, int32_T idx_global)
{
  int32_T TYPE_tmp_tmp;
  int32_T totalEq;
  totalEq = obj->nWConstr[0] + obj->nWConstr[1];
  if ((totalEq != 0) && (idx_global <= totalEq)) {
    if ((obj->nActiveConstr == totalEq) || (idx_global == totalEq)) {
      obj->mEqRemoved++;
      obj->indexEqRemoved[obj->mEqRemoved - 1] = obj->Wlocalidx[idx_global - 1];
      totalEq = obj->Wid[idx_global - 1] - 1;
      obj->isActiveConstr[(obj->isActiveIdx[totalEq] + obj->Wlocalidx[idx_global
                           - 1]) - 2] = false;
      moveConstraint_(obj, obj->nActiveConstr, idx_global);
      obj->nActiveConstr--;
      obj->nWConstr[totalEq]--;
    } else {
      obj->mEqRemoved++;
      TYPE_tmp_tmp = obj->Wid[idx_global - 1] - 1;
      obj->indexEqRemoved[obj->mEqRemoved - 1] = obj->Wlocalidx[idx_global - 1];
      obj->isActiveConstr[(obj->isActiveIdx[obj->Wid[idx_global - 1] - 1] +
                           obj->Wlocalidx[idx_global - 1]) - 2] = false;
      moveConstraint_(obj, totalEq, idx_global);
      moveConstraint_(obj, obj->nActiveConstr, totalEq);
      obj->nActiveConstr--;
      obj->nWConstr[TYPE_tmp_tmp]--;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void RemoveDependentEq_(snRDwUdgrIx9qNga56nZ8DE *memspace, int32_T
  *nDepInd, stxriBK2jD81NCGacZ0b8HD *workingset, sCS11Pe0E6xKX8jGoaG4cLG
  *qrmanager, DW *rtDW)
{
  static const int8_T b_workingset_Aineq[56] = { -1, 0, 0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0 };

  static const int8_T b_workingset_Aeq[16] = { 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0,
    0, 0, 0, -1, 0 };

  static const int8_T b_workingset_ATwset[80] = { 1, 1, 1, 1, 1, 1, 1, 0, 1, 0,
    0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  static const real_T b_workingset_bwset[10] = { 0.5, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0 };

  static const int8_T b_workingset_sizes[5] = { 0, 2, 7, 0, 0 };

  static const int8_T b_workingset_isActiveIdx[6] = { 1, 1, 3, 10, 10, 10 };

  static const int8_T b_workingset_sizesPhaseOne[5] = { 0, 2, 7, 1, 0 };

  static const int8_T b_workingset_sizesRegularized[5] = { 0, 2, 7, 11, 0 };

  static const boolean_T b_workingset_isActiveConstr[10] = { true, true, false,
    false, false, false, false, false, false, false };

  static const int8_T b_workingset_isActiveIdxPhaseOn[6] = { 1, 1, 3, 10, 11, 11
  };

  static const int8_T b_workingset_sizesRegPhaseOne[5] = { 0, 2, 7, 12, 0 };

  static const int8_T b_workingset_Wid[10] = { 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 };

  static const int8_T b_workingset_isActiveIdxRegular[6] = { 1, 1, 3, 10, 21, 21
  };

  static const int8_T b_workingset_nWConstr[5] = { 0, 2, 0, 0, 0 };

  static const int8_T b_workingset_Wlocalidx[10] = { 1, 2, 0, 0, 0, 0, 0, 0, 0,
    0 };

  static const int8_T b_workingset_isActiveIdxRegPhas[6] = { 1, 1, 3, 10, 22, 22
  };

  qrmanager->ldq = 9;
  memset(&qrmanager->QR[0], 0, 90U * sizeof(real_T));
  memset(&qrmanager->Q[0], 0, 81U * sizeof(real_T));
  for (rtDW->i_l = 0; rtDW->i_l < 10; rtDW->i_l++) {
    qrmanager->jpvt[rtDW->i_l] = 0;
  }

  qrmanager->mrows = 0;
  qrmanager->ncols = 0;
  memset(&qrmanager->tau[0], 0, 9U * sizeof(real_T));
  qrmanager->minRowCol = 0;
  qrmanager->usedPivoting = false;
  workingset->mConstr = 9;
  workingset->mConstrOrig = 9;
  workingset->mConstrMax = 10;
  workingset->nVar = 7;
  workingset->nVarOrig = 7;
  workingset->nVarMax = 8;
  workingset->ldA = 8;
  for (rtDW->i_l = 0; rtDW->i_l < 56; rtDW->i_l++) {
    workingset->Aineq[rtDW->i_l] = b_workingset_Aineq[rtDW->i_l];
  }

  for (rtDW->i_l = 0; rtDW->i_l < 7; rtDW->i_l++) {
    workingset->bineq[rtDW->i_l] = 0.0;
  }

  for (rtDW->i_l = 0; rtDW->i_l < 16; rtDW->i_l++) {
    workingset->Aeq[rtDW->i_l] = b_workingset_Aeq[rtDW->i_l];
  }

  workingset->beq[0] = 0.5;
  workingset->beq[1] = 0.0;
  memset(&workingset->lb[0], 0, sizeof(real_T) << 3U);
  memset(&workingset->ub[0], 0, sizeof(real_T) << 3U);
  for (rtDW->i_l = 0; rtDW->i_l < 8; rtDW->i_l++) {
    workingset->indexLB[rtDW->i_l] = 0;
    workingset->indexUB[rtDW->i_l] = 0;
    workingset->indexFixed[rtDW->i_l] = 0;
  }

  workingset->mEqRemoved = 0;
  workingset->indexEqRemoved[0] = 0;
  workingset->indexEqRemoved[1] = 0;
  for (rtDW->i_l = 0; rtDW->i_l < 80; rtDW->i_l++) {
    workingset->ATwset[rtDW->i_l] = b_workingset_ATwset[rtDW->i_l];
  }

  workingset->nActiveConstr = 2;
  for (rtDW->i_l = 0; rtDW->i_l < 10; rtDW->i_l++) {
    workingset->bwset[rtDW->i_l] = b_workingset_bwset[rtDW->i_l];
    workingset->maxConstrWorkspace[rtDW->i_l] = 0.0;
  }

  for (rtDW->i_l = 0; rtDW->i_l < 5; rtDW->i_l++) {
    workingset->sizes[rtDW->i_l] = b_workingset_sizes[rtDW->i_l];
    workingset->sizesNormal[rtDW->i_l] = b_workingset_sizes[rtDW->i_l];
    workingset->sizesPhaseOne[rtDW->i_l] = b_workingset_sizesPhaseOne[rtDW->i_l];
    workingset->sizesRegularized[rtDW->i_l] = b_workingset_sizesRegularized
      [rtDW->i_l];
    workingset->sizesRegPhaseOne[rtDW->i_l] = b_workingset_sizesRegPhaseOne
      [rtDW->i_l];
  }

  for (rtDW->i_l = 0; rtDW->i_l < 6; rtDW->i_l++) {
    workingset->isActiveIdx[rtDW->i_l] = b_workingset_isActiveIdx[rtDW->i_l];
    workingset->isActiveIdxNormal[rtDW->i_l] = b_workingset_isActiveIdx
      [rtDW->i_l];
    workingset->isActiveIdxPhaseOne[rtDW->i_l] =
      b_workingset_isActiveIdxPhaseOn[rtDW->i_l];
    workingset->isActiveIdxRegularized[rtDW->i_l] =
      b_workingset_isActiveIdxRegular[rtDW->i_l];
    workingset->isActiveIdxRegPhaseOne[rtDW->i_l] =
      b_workingset_isActiveIdxRegPhas[rtDW->i_l];
  }

  for (rtDW->i_l = 0; rtDW->i_l < 10; rtDW->i_l++) {
    workingset->isActiveConstr[rtDW->i_l] = b_workingset_isActiveConstr
      [rtDW->i_l];
    workingset->Wid[rtDW->i_l] = b_workingset_Wid[rtDW->i_l];
    workingset->Wlocalidx[rtDW->i_l] = b_workingset_Wlocalidx[rtDW->i_l];
  }

  for (rtDW->i_l = 0; rtDW->i_l < 5; rtDW->i_l++) {
    workingset->nWConstr[rtDW->i_l] = b_workingset_nWConstr[rtDW->i_l];
  }

  workingset->probType = 3;
  workingset->SLACK0 = 0.0;
  for (rtDW->i_l = 0; rtDW->i_l < 2; rtDW->i_l++) {
    for (rtDW->idx_col = 0; rtDW->idx_col < 7; rtDW->idx_col++) {
      qrmanager->QR[rtDW->i_l + 9 * rtDW->idx_col] = b_workingset_ATwset
        [(rtDW->i_l << 3) + rtDW->idx_col];
    }
  }

  *nDepInd = ComputeNumDependentEq_(qrmanager, rtDW);
  if (*nDepInd > 0) {
    for (rtDW->i_l = 0; rtDW->i_l < 2; rtDW->i_l++) {
      rtDW->offsetQR_c = qrmanager->ldq * rtDW->i_l;
      rtDW->offsetATw_o = rtDW->i_l << 3;
      for (rtDW->idx_col = 0; rtDW->idx_col < 7; rtDW->idx_col++) {
        qrmanager->QR[rtDW->offsetQR_c + rtDW->idx_col] =
          b_workingset_ATwset[rtDW->offsetATw_o + rtDW->idx_col];
      }
    }

    IndexOfDependentEq_(memspace->workspace_int, *nDepInd, qrmanager, 7, 2, rtDW);
    countsort(memspace->workspace_int, *nDepInd, memspace->workspace_sort, 1, 2);
    rtDW->i_l = *nDepInd;
    while (rtDW->i_l > 0) {
      removeEqConstr(workingset, memspace->workspace_int[rtDW->i_l - 1]);
      rtDW->i_l--;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void removeAllIneqConstr(stxriBK2jD81NCGacZ0b8HD *obj)
{
  int32_T idx_global;
  for (idx_global = obj->nWConstr[0] + obj->nWConstr[1]; idx_global <
       obj->nActiveConstr; idx_global++) {
    obj->isActiveConstr[(obj->isActiveIdx[obj->Wid[idx_global] - 1] +
                         obj->Wlocalidx[idx_global]) - 2] = false;
  }

  obj->nWConstr[2] = 0;
  obj->nWConstr[3] = 0;
  obj->nWConstr[4] = 0;
  obj->nActiveConstr = obj->nWConstr[0] + obj->nWConstr[1];
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void RemoveDependentIneq_(stxriBK2jD81NCGacZ0b8HD *workingset,
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, snRDwUdgrIx9qNga56nZ8DE *memspace, real_T
  tolfactor, DW *rtDW)
{
  rtDW->nFixedConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  rtDW->nVar_n = workingset->nVar;
  if ((workingset->nWConstr[2] + workingset->nWConstr[3]) + workingset->
      nWConstr[4] > 0) {
    rtDW->tol = tolfactor * (real_T)workingset->nVar * 2.2204460492503131E-16;
    rtDW->nDepIneq = 0;
    while (rtDW->nDepIneq <= rtDW->nFixedConstr - 1) {
      qrmanager->jpvt[rtDW->nDepIneq] = 1;
      rtDW->nDepIneq++;
    }

    rtDW->nDepIneq = rtDW->nFixedConstr + 1;
    while (rtDW->nDepIneq <= workingset->nActiveConstr) {
      qrmanager->jpvt[rtDW->nDepIneq - 1] = 0;
      rtDW->nDepIneq++;
    }

    rtDW->nDepIneq = 0;
    while (rtDW->nDepIneq <= workingset->nActiveConstr - 1) {
      rtDW->i_m = qrmanager->ldq * rtDW->nDepIneq;
      rtDW->idxPosATwset = workingset->ldA * rtDW->nDepIneq;
      rtDW->k = 1;
      while (rtDW->k - 1 <= rtDW->nVar_n - 1) {
        qrmanager->QR[(rtDW->i_m + rtDW->k) - 1] = workingset->ATwset
          [(rtDW->idxPosATwset + rtDW->k) - 1];
        rtDW->k++;
      }

      rtDW->nDepIneq++;
    }

    if (workingset->nVar * workingset->nActiveConstr == 0) {
      qrmanager->mrows = workingset->nVar;
      qrmanager->ncols = workingset->nActiveConstr;
      qrmanager->minRowCol = 0;
    } else {
      qrmanager->usedPivoting = true;
      qrmanager->mrows = workingset->nVar;
      qrmanager->ncols = workingset->nActiveConstr;
      if (workingset->nVar < workingset->nActiveConstr) {
        qrmanager->minRowCol = workingset->nVar;
      } else {
        qrmanager->minRowCol = workingset->nActiveConstr;
      }

      for (rtDW->i_m = 0; rtDW->i_m < 10; rtDW->i_m++) {
        rtDW->jpvt[rtDW->i_m] = qrmanager->jpvt[rtDW->i_m];
      }

      xzgeqp3(qrmanager->QR, 1, workingset->nVar, workingset->nActiveConstr,
              rtDW->jpvt, qrmanager->tau, rtDW);
      for (rtDW->i_m = 0; rtDW->i_m < 10; rtDW->i_m++) {
        qrmanager->jpvt[rtDW->i_m] = rtDW->jpvt[rtDW->i_m];
      }
    }

    rtDW->nDepIneq = -1;
    rtDW->i_m = workingset->nActiveConstr - 1;
    while (rtDW->i_m + 1 > rtDW->nVar_n) {
      rtDW->nDepIneq++;
      memspace->workspace_int[rtDW->nDepIneq] = qrmanager->jpvt[rtDW->i_m];
      rtDW->i_m--;
    }

    if (rtDW->i_m + 1 <= workingset->nVar) {
      rtDW->nVar_n = qrmanager->ldq * rtDW->i_m + rtDW->i_m;
      while ((rtDW->i_m + 1 > rtDW->nFixedConstr) && (fabs(qrmanager->QR
               [rtDW->nVar_n]) < rtDW->tol)) {
        rtDW->nDepIneq++;
        memspace->workspace_int[rtDW->nDepIneq] = qrmanager->jpvt[rtDW->i_m];
        rtDW->i_m--;
        rtDW->nVar_n = (rtDW->nVar_n - qrmanager->ldq) - 1;
      }
    }

    for (rtDW->i_m = 0; rtDW->i_m < 10; rtDW->i_m++) {
      rtDW->jpvt[rtDW->i_m] = memspace->workspace_int[rtDW->i_m];
    }

    countsort(rtDW->jpvt, rtDW->nDepIneq + 1, memspace->workspace_sort,
              rtDW->nFixedConstr + 1, workingset->nActiveConstr);
    for (rtDW->i_m = 0; rtDW->i_m < 10; rtDW->i_m++) {
      memspace->workspace_int[rtDW->i_m] = rtDW->jpvt[rtDW->i_m];
    }

    while (rtDW->nDepIneq + 1 > 0) {
      rtDW->nFixedConstr = workingset->Wid[rtDW->jpvt[rtDW->nDepIneq] - 1] - 1;
      workingset->isActiveConstr[(workingset->isActiveIdx[rtDW->nFixedConstr] +
        workingset->Wlocalidx[rtDW->jpvt[rtDW->nDepIneq] - 1]) - 2] = false;
      moveConstraint_(workingset, workingset->nActiveConstr, rtDW->jpvt
                      [rtDW->nDepIneq]);
      workingset->nActiveConstr--;
      workingset->nWConstr[rtDW->nFixedConstr]--;
      rtDW->nDepIneq--;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void factorQR_f(sCS11Pe0E6xKX8jGoaG4cLG *obj, const real_T A[80], int32_T
  mrows, int32_T ncols, int32_T ldA, DW *rtDW)
{
  int32_T b_idx;
  int32_T i;
  int32_T k;
  boolean_T guard1 = false;
  b_idx = mrows * ncols;
  guard1 = false;
  if (b_idx > 0) {
    for (b_idx = 0; b_idx < ncols; b_idx++) {
      i = ldA * b_idx;
      rtDW->iQR0_m = obj->ldq * b_idx;
      for (k = 1; k - 1 < mrows; k++) {
        obj->QR[(rtDW->iQR0_m + k) - 1] = A[(i + k) - 1];
      }
    }

    guard1 = true;
  } else if (b_idx == 0) {
    obj->mrows = mrows;
    obj->ncols = ncols;
    obj->minRowCol = 0;
  } else {
    guard1 = true;
  }

  if (guard1) {
    obj->usedPivoting = false;
    obj->mrows = mrows;
    obj->ncols = ncols;
    for (b_idx = 0; b_idx < ncols; b_idx++) {
      obj->jpvt[b_idx] = b_idx + 1;
    }

    if (mrows < ncols) {
      b_idx = mrows;
    } else {
      b_idx = ncols;
    }

    obj->minRowCol = b_idx;
    memset(&obj->tau[0], 0, 9U * sizeof(real_T));
    if (b_idx >= 1) {
      qrf(obj->QR, 1, mrows, ncols, b_idx, obj->tau, rtDW);
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void factorQR(sCS11Pe0E6xKX8jGoaG4cLG *obj, int32_T mrows, int32_T ncols,
                     DW *rtDW)
{
  int32_T idx;
  if (mrows * ncols == 0) {
    obj->mrows = mrows;
    obj->ncols = ncols;
    obj->minRowCol = 0;
  } else {
    obj->usedPivoting = false;
    obj->mrows = mrows;
    obj->ncols = ncols;
    for (idx = 0; idx < ncols; idx++) {
      obj->jpvt[idx] = idx + 1;
    }

    if (mrows < ncols) {
      idx = mrows;
    } else {
      idx = ncols;
    }

    obj->minRowCol = idx;
    memset(&obj->tau[0], 0, 9U * sizeof(real_T));
    if (idx >= 1) {
      qrf(obj->QR, 1, mrows, ncols, idx, obj->tau, rtDW);
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv(int32_T m, int32_T n, const real_T A[56], int32_T lda, const
                  real_T x[80], real_T y[10], DW *rtDW)
{
  int32_T b;
  int32_T b_iy;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  if ((m != 0) && (n != 0)) {
    for (b_iy = 0; b_iy < n; b_iy++) {
      y[b_iy] = -y[b_iy];
    }

    iy = 0;
    b_iy = (n - 1) * lda + 1;
    iac = 1;
    while (((lda > 0) && (iac <= b_iy)) || ((lda < 0) && (iac >= b_iy))) {
      ix = 0;
      rtDW->c_l = 0.0;
      b = (iac + m) - 1;
      for (ia = iac; ia <= b; ia++) {
        rtDW->c_l += A[ia - 1] * x[ix];
        ix++;
      }

      y[iy] += rtDW->c_l;
      iy++;
      iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv_p(int32_T m, int32_T n, const real_T A[16], int32_T lda, const
                    real_T x[80], real_T y[10], DW *rtDW)
{
  int32_T b;
  int32_T b_iy;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  if ((m != 0) && (n != 0)) {
    for (b_iy = 0; b_iy < n; b_iy++) {
      y[b_iy] = -y[b_iy];
    }

    iy = 0;
    b_iy = (n - 1) * lda + 1;
    iac = 1;
    while (((lda > 0) && (iac <= b_iy)) || ((lda < 0) && (iac >= b_iy))) {
      ix = 0;
      rtDW->c_g = 0.0;
      b = (iac + m) - 1;
      for (ia = iac; ia <= b; ia++) {
        rtDW->c_g += A[ia - 1] * x[ix];
        ix++;
      }

      y[iy] += rtDW->c_g;
      iy++;
      iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real_T maxConstraintViolation(stxriBK2jD81NCGacZ0b8HD *obj, const real_T
  x[80], DW *rtDW)
{
  real_T v;
  int32_T b_mIneq;
  int32_T h_idx;
  int32_T mEq;
  int32_T mFixed;
  int32_T mIneq;
  int32_T mLB;
  int32_T mUB;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  if (obj->probType == 2) {
    v = 0.0;
    b_mIneq = obj->sizes[2] - 1;
    mEq = obj->sizes[1] - 1;
    for (mIneq = 0; mIneq <= b_mIneq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->bineq[mIneq];
    }

    xgemv(obj->nVarOrig, obj->sizes[2], obj->Aineq, obj->ldA, x,
          obj->maxConstrWorkspace, rtDW);
    for (mIneq = 0; mIneq <= b_mIneq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] -= x[obj->nVarOrig + mIneq];
      v = fmax(v, obj->maxConstrWorkspace[mIneq]);
    }

    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->beq[mIneq];
    }

    xgemv_p(obj->nVarOrig, obj->sizes[1], obj->Aeq, obj->ldA, x,
            obj->maxConstrWorkspace, rtDW);
    b_mIneq = obj->nVarOrig + obj->sizes[2];
    mIneq = b_mIneq + obj->sizes[1];
    for (h_idx = 0; h_idx <= mEq; h_idx++) {
      obj->maxConstrWorkspace[h_idx] = (obj->maxConstrWorkspace[h_idx] -
        x[b_mIneq + h_idx]) + x[mIneq + h_idx];
      v = fmax(v, fabs(obj->maxConstrWorkspace[h_idx]));
    }
  } else {
    v = 0.0;
    mIneq = obj->sizes[2] - 1;
    mEq = obj->sizes[1] - 1;
    for (b_mIneq = 0; b_mIneq <= mIneq; b_mIneq++) {
      obj->maxConstrWorkspace[b_mIneq] = obj->bineq[b_mIneq];
    }

    xgemv(obj->nVar, obj->sizes[2], obj->Aineq, obj->ldA, x,
          obj->maxConstrWorkspace, rtDW);
    for (b_mIneq = 0; b_mIneq <= mIneq; b_mIneq++) {
      v = fmax(v, obj->maxConstrWorkspace[b_mIneq]);
    }

    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->beq[mIneq];
    }

    xgemv_p(obj->nVar, obj->sizes[1], obj->Aeq, obj->ldA, x,
            obj->maxConstrWorkspace, rtDW);
    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      v = fmax(v, fabs(obj->maxConstrWorkspace[mIneq]));
    }
  }

  if (mLB > 0) {
    for (mEq = 0; mEq < mLB; mEq++) {
      v = fmax(v, -x[obj->indexLB[mEq] - 1] - obj->lb[obj->indexLB[mEq] - 1]);
    }
  }

  if (mUB > 0) {
    for (mLB = 0; mLB < mUB; mLB++) {
      v = fmax(v, x[obj->indexUB[mLB] - 1] - obj->ub[obj->indexUB[mLB] - 1]);
    }
  }

  if (mFixed > 0) {
    for (mUB = 0; mUB < mFixed; mUB++) {
      v = fmax(v, fabs(x[obj->indexFixed[mUB] - 1] - obj->ub[obj->indexFixed[mUB]
                       - 1]));
    }
  }

  return v;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv_py(int32_T m, int32_T n, const real_T A[56], int32_T lda,
                     const real_T x[80], real_T y[10], DW *rtDW)
{
  int32_T b;
  int32_T b_iy;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  if ((m != 0) && (n != 0)) {
    for (b_iy = 0; b_iy < n; b_iy++) {
      y[b_iy] = -y[b_iy];
    }

    iy = 0;
    b_iy = (n - 1) * lda + 1;
    iac = 1;
    while (((lda > 0) && (iac <= b_iy)) || ((lda < 0) && (iac >= b_iy))) {
      ix = 10;
      rtDW->c_d = 0.0;
      b = (iac + m) - 1;
      for (ia = iac; ia <= b; ia++) {
        rtDW->c_d += A[ia - 1] * x[ix];
        ix++;
      }

      y[iy] += rtDW->c_d;
      iy++;
      iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv_pym(int32_T m, int32_T n, const real_T A[16], int32_T lda,
                      const real_T x[80], real_T y[10], DW *rtDW)
{
  int32_T b;
  int32_T b_iy;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  if ((m != 0) && (n != 0)) {
    for (b_iy = 0; b_iy < n; b_iy++) {
      y[b_iy] = -y[b_iy];
    }

    iy = 0;
    b_iy = (n - 1) * lda + 1;
    iac = 1;
    while (((lda > 0) && (iac <= b_iy)) || ((lda < 0) && (iac >= b_iy))) {
      ix = 10;
      rtDW->c_j = 0.0;
      b = (iac + m) - 1;
      for (ia = iac; ia <= b; ia++) {
        rtDW->c_j += A[ia - 1] * x[ix];
        ix++;
      }

      y[iy] += rtDW->c_j;
      iy++;
      iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real_T maxConstraintViolation_p(stxriBK2jD81NCGacZ0b8HD *obj, const
  real_T x[80], DW *rtDW)
{
  real_T v;
  int32_T b_mIneq;
  int32_T h_idx;
  int32_T mEq;
  int32_T mFixed;
  int32_T mIneq;
  int32_T mLB;
  int32_T mUB;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  if (obj->probType == 2) {
    v = 0.0;
    b_mIneq = obj->sizes[2] - 1;
    mEq = obj->sizes[1] - 1;
    for (mIneq = 0; mIneq <= b_mIneq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->bineq[mIneq];
    }

    xgemv_py(obj->nVarOrig, obj->sizes[2], obj->Aineq, obj->ldA, x,
             obj->maxConstrWorkspace, rtDW);
    for (mIneq = 0; mIneq <= b_mIneq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] -= x[(obj->nVarOrig + mIneq) + 10];
      v = fmax(v, obj->maxConstrWorkspace[mIneq]);
    }

    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->beq[mIneq];
    }

    xgemv_pym(obj->nVarOrig, obj->sizes[1], obj->Aeq, obj->ldA, x,
              obj->maxConstrWorkspace, rtDW);
    b_mIneq = (obj->nVarOrig + obj->sizes[2]) + 9;
    mIneq = (b_mIneq + obj->sizes[1]) + 1;
    for (h_idx = 0; h_idx <= mEq; h_idx++) {
      obj->maxConstrWorkspace[h_idx] = (obj->maxConstrWorkspace[h_idx] - x
        [(b_mIneq + h_idx) + 1]) + x[mIneq + h_idx];
      v = fmax(v, fabs(obj->maxConstrWorkspace[h_idx]));
    }
  } else {
    v = 0.0;
    mIneq = obj->sizes[2] - 1;
    mEq = obj->sizes[1] - 1;
    for (b_mIneq = 0; b_mIneq <= mIneq; b_mIneq++) {
      obj->maxConstrWorkspace[b_mIneq] = obj->bineq[b_mIneq];
    }

    xgemv_py(obj->nVar, obj->sizes[2], obj->Aineq, obj->ldA, x,
             obj->maxConstrWorkspace, rtDW);
    for (b_mIneq = 0; b_mIneq <= mIneq; b_mIneq++) {
      v = fmax(v, obj->maxConstrWorkspace[b_mIneq]);
    }

    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->beq[mIneq];
    }

    xgemv_pym(obj->nVar, obj->sizes[1], obj->Aeq, obj->ldA, x,
              obj->maxConstrWorkspace, rtDW);
    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      v = fmax(v, fabs(obj->maxConstrWorkspace[mIneq]));
    }
  }

  if (mLB > 0) {
    for (mEq = 0; mEq < mLB; mEq++) {
      v = fmax(v, -x[obj->indexLB[mEq] + 9] - obj->lb[obj->indexLB[mEq] - 1]);
    }
  }

  if (mUB > 0) {
    for (mLB = 0; mLB < mUB; mLB++) {
      v = fmax(v, x[obj->indexUB[mLB] + 9] - obj->ub[obj->indexUB[mLB] - 1]);
    }
  }

  if (mFixed > 0) {
    for (mUB = 0; mUB < mFixed; mUB++) {
      v = fmax(v, fabs(x[obj->indexFixed[mUB] + 9] - obj->ub[obj->indexFixed[mUB]
                       - 1]));
    }
  }

  return v;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void feasibleX0ForWorkingSet(real_T workspace[80], real_T xCurrent[8],
  stxriBK2jD81NCGacZ0b8HD *workingset, sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, DW
  *rtDW)
{
  rtDW->mWConstr = workingset->nActiveConstr - 1;
  rtDW->nVar_j = workingset->nVar;
  if (workingset->nActiveConstr != 0) {
    rtDW->ldq = 0;
    while (rtDW->ldq <= rtDW->mWConstr) {
      workspace[rtDW->ldq] = workingset->bwset[rtDW->ldq];
      workspace[rtDW->ldq + 10] = workingset->bwset[rtDW->ldq];
      rtDW->ldq++;
    }

    rtDW->ldq = workingset->ldA;
    if ((workingset->nVar != 0) && (workingset->nActiveConstr != 0)) {
      rtDW->iy_n = 0;
      rtDW->jBcol = (workingset->nActiveConstr - 1) * workingset->ldA + 1;
      rtDW->ar = 1;
      while (((rtDW->ldq > 0) && (rtDW->ar <= rtDW->jBcol)) || ((rtDW->ldq < 0) &&
              (rtDW->ar >= rtDW->jBcol))) {
        rtDW->ix_o = 0;
        rtDW->c = 0.0;
        rtDW->b_i = (rtDW->ar + rtDW->nVar_j) - 1;
        rtDW->b_ia = rtDW->ar;
        while (rtDW->b_ia <= rtDW->b_i) {
          rtDW->c += workingset->ATwset[rtDW->b_ia - 1] * xCurrent[rtDW->ix_o];
          rtDW->ix_o++;
          rtDW->b_ia++;
        }

        workspace[rtDW->iy_n] += -rtDW->c;
        rtDW->iy_n++;
        rtDW->ar += rtDW->ldq;
      }
    }

    if (workingset->nActiveConstr >= workingset->nVar) {
      rtDW->ldq = 0;
      while (rtDW->ldq <= rtDW->nVar_j - 1) {
        rtDW->jBcol = qrmanager->ldq * rtDW->ldq;
        rtDW->ar = 0;
        while (rtDW->ar <= rtDW->mWConstr) {
          qrmanager->QR[rtDW->ar + rtDW->jBcol] = workingset->ATwset
            [workingset->ldA * rtDW->ar + rtDW->ldq];
          rtDW->ar++;
        }

        rtDW->ldq++;
      }

      factorQR(qrmanager, workingset->nActiveConstr, workingset->nVar, rtDW);
      computeQ_(qrmanager, qrmanager->mrows, rtDW);
      rtDW->ldq = qrmanager->ldq;
      memcpy(&rtDW->B_m[0], &workspace[0], 80U * sizeof(real_T));
      if (workingset->nVar != 0) {
        rtDW->ar = 0;
        while (rtDW->ar + 1 <= rtDW->nVar_j) {
          workspace[rtDW->ar] = 0.0;
          rtDW->ar++;
        }

        rtDW->ar = 10;
        while (rtDW->ar + 1 <= rtDW->nVar_j + 10) {
          workspace[rtDW->ar] = 0.0;
          rtDW->ar++;
        }

        rtDW->ar = -1;
        rtDW->b_i = 0;
        while (rtDW->b_i + 1 <= rtDW->nVar_j) {
          rtDW->c = 0.0;
          rtDW->b_ia = 1;
          while (rtDW->b_ia - 1 <= rtDW->mWConstr) {
            rtDW->c += qrmanager->Q[rtDW->b_ia + rtDW->ar] * rtDW->B_m
              [rtDW->b_ia + -1];
            rtDW->b_ia++;
          }

          workspace[rtDW->b_i] += rtDW->c;
          rtDW->ar += rtDW->ldq;
          rtDW->b_i++;
        }

        rtDW->ar = -1;
        rtDW->b_i = 10;
        while (rtDW->b_i + 1 <= rtDW->nVar_j + 10) {
          rtDW->c = 0.0;
          rtDW->b_ia = 1;
          while (rtDW->b_ia - 1 <= rtDW->mWConstr) {
            rtDW->c += qrmanager->Q[rtDW->b_ia + rtDW->ar] * rtDW->B_m
              [rtDW->b_ia + 9];
            rtDW->b_ia++;
          }

          workspace[rtDW->b_i] += rtDW->c;
          rtDW->ar += rtDW->ldq;
          rtDW->b_i++;
        }
      }

      rtDW->jBcol = workingset->nVar;
      while (rtDW->jBcol > 0) {
        rtDW->ar = (rtDW->jBcol - 1) * rtDW->ldq - 1;
        if (workspace[rtDW->jBcol + -1] != 0.0) {
          workspace[rtDW->jBcol + -1] /= qrmanager->QR[rtDW->jBcol + rtDW->ar];
          rtDW->ix_o = 1;
          while (rtDW->ix_o - 1 <= rtDW->jBcol - 2) {
            workspace[rtDW->ix_o + -1] -= workspace[rtDW->jBcol + -1] *
              qrmanager->QR[rtDW->ix_o + rtDW->ar];
            rtDW->ix_o++;
          }
        }

        rtDW->jBcol--;
      }

      rtDW->jBcol = workingset->nVar;
      while (rtDW->jBcol > 0) {
        rtDW->ar = (rtDW->jBcol - 1) * rtDW->ldq - 1;
        rtDW->c = workspace[rtDW->jBcol + 9];
        if (rtDW->c != 0.0) {
          workspace[rtDW->jBcol + 9] = rtDW->c / qrmanager->QR[rtDW->jBcol +
            rtDW->ar];
          rtDW->ix_o = 1;
          while (rtDW->ix_o - 1 <= rtDW->jBcol - 2) {
            workspace[rtDW->ix_o + 9] -= workspace[rtDW->jBcol + 9] *
              qrmanager->QR[rtDW->ix_o + rtDW->ar];
            rtDW->ix_o++;
          }
        }

        rtDW->jBcol--;
      }
    } else {
      factorQR_f(qrmanager, workingset->ATwset, workingset->nVar,
                 workingset->nActiveConstr, workingset->ldA, rtDW);
      computeQ_(qrmanager, qrmanager->minRowCol, rtDW);
      rtDW->ldq = qrmanager->ldq;
      rtDW->ar = 1;
      while (rtDW->ar - 1 <= rtDW->mWConstr) {
        rtDW->ix_o = (rtDW->ar - 1) * rtDW->ldq - 1;
        rtDW->c = workspace[rtDW->ar + -1];
        rtDW->b_i = 1;
        while (rtDW->b_i - 1 <= rtDW->ar - 2) {
          rtDW->c -= qrmanager->QR[rtDW->b_i + rtDW->ix_o] * workspace[rtDW->b_i
            + -1];
          rtDW->b_i++;
        }

        workspace[rtDW->ar + -1] = rtDW->c / qrmanager->QR[rtDW->ar + rtDW->ix_o];
        rtDW->ar++;
      }

      rtDW->ar = 1;
      while (rtDW->ar - 1 <= rtDW->mWConstr) {
        rtDW->ix_o = (rtDW->ar - 1) * rtDW->ldq - 1;
        rtDW->c = workspace[rtDW->ar + 9];
        rtDW->b_i = 1;
        while (rtDW->b_i - 1 <= rtDW->ar - 2) {
          rtDW->c -= qrmanager->QR[rtDW->b_i + rtDW->ix_o] * workspace[rtDW->b_i
            + 9];
          rtDW->b_i++;
        }

        workspace[rtDW->ar + 9] = rtDW->c / qrmanager->QR[rtDW->ar + rtDW->ix_o];
        rtDW->ar++;
      }

      memcpy(&rtDW->B_m[0], &workspace[0], 80U * sizeof(real_T));
      if (workingset->nVar != 0) {
        rtDW->ar = 0;
        while (rtDW->ar + 1 <= rtDW->nVar_j) {
          workspace[rtDW->ar] = 0.0;
          rtDW->ar++;
        }

        rtDW->ar = 10;
        while (rtDW->ar + 1 <= rtDW->nVar_j + 10) {
          workspace[rtDW->ar] = 0.0;
          rtDW->ar++;
        }

        rtDW->ar = -1;
        rtDW->b_i = 1;
        while (rtDW->b_i <= rtDW->mWConstr + 1) {
          rtDW->b_ia = rtDW->ar;
          rtDW->iy_n = 0;
          while (rtDW->iy_n + 1 <= rtDW->nVar_j) {
            rtDW->b_ia++;
            workspace[rtDW->iy_n] += rtDW->B_m[rtDW->b_i - 1] * qrmanager->
              Q[rtDW->b_ia];
            rtDW->iy_n++;
          }

          rtDW->ar += rtDW->ldq;
          rtDW->b_i++;
        }

        rtDW->ar = -1;
        rtDW->b_i = 11;
        while (rtDW->b_i <= rtDW->mWConstr + 11) {
          rtDW->b_ia = rtDW->ar;
          rtDW->iy_n = 10;
          while (rtDW->iy_n + 1 <= rtDW->nVar_j + 10) {
            rtDW->b_ia++;
            workspace[rtDW->iy_n] += rtDW->B_m[rtDW->b_i - 1] * qrmanager->
              Q[rtDW->b_ia];
            rtDW->iy_n++;
          }

          rtDW->ar += rtDW->ldq;
          rtDW->b_i++;
        }
      }
    }

    if (workingset->nVar >= 1) {
      rtDW->mWConstr = 0;
      while (rtDW->mWConstr <= workingset->nVar - 1) {
        workspace[rtDW->mWConstr] += xCurrent[rtDW->mWConstr];
        rtDW->mWConstr++;
      }
    }

    rtDW->c = maxConstraintViolation(workingset, workspace, rtDW);
    rtDW->constrViolation_basicX = maxConstraintViolation_p(workingset,
      workspace, rtDW);
    if ((rtDW->c <= 2.2204460492503131E-16) || (rtDW->c <
         rtDW->constrViolation_basicX)) {
      rtDW->mWConstr = 0;
      while (rtDW->mWConstr <= rtDW->nVar_j - 1) {
        xCurrent[rtDW->mWConstr] = workspace[rtDW->mWConstr];
        rtDW->mWConstr++;
      }
    } else {
      rtDW->mWConstr = 0;
      while (rtDW->mWConstr <= rtDW->nVar_j - 1) {
        xCurrent[rtDW->mWConstr] = workspace[rtDW->mWConstr + 10];
        rtDW->mWConstr++;
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv_pyma(int32_T m, int32_T n, const real_T A[56], int32_T lda,
  const real_T x[8], real_T y[10], DW *rtDW)
{
  int32_T b;
  int32_T b_iy;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  if ((m != 0) && (n != 0)) {
    for (b_iy = 0; b_iy < n; b_iy++) {
      y[b_iy] = -y[b_iy];
    }

    iy = 0;
    b_iy = (n - 1) * lda + 1;
    iac = 1;
    while (((lda > 0) && (iac <= b_iy)) || ((lda < 0) && (iac >= b_iy))) {
      ix = 0;
      rtDW->c_dy = 0.0;
      b = (iac + m) - 1;
      for (ia = iac; ia <= b; ia++) {
        rtDW->c_dy += A[ia - 1] * x[ix];
        ix++;
      }

      y[iy] += rtDW->c_dy;
      iy++;
      iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv_pyma2(int32_T m, int32_T n, const real_T A[16], int32_T lda,
  const real_T x[8], real_T y[10], DW *rtDW)
{
  int32_T b;
  int32_T b_iy;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  if ((m != 0) && (n != 0)) {
    for (b_iy = 0; b_iy < n; b_iy++) {
      y[b_iy] = -y[b_iy];
    }

    iy = 0;
    b_iy = (n - 1) * lda + 1;
    iac = 1;
    while (((lda > 0) && (iac <= b_iy)) || ((lda < 0) && (iac >= b_iy))) {
      ix = 0;
      rtDW->c_dh = 0.0;
      b = (iac + m) - 1;
      for (ia = iac; ia <= b; ia++) {
        rtDW->c_dh += A[ia - 1] * x[ix];
        ix++;
      }

      y[iy] += rtDW->c_dh;
      iy++;
      iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real_T maxConstraintViolation_pn(stxriBK2jD81NCGacZ0b8HD *obj, const
  real_T x[8], DW *rtDW)
{
  real_T v;
  int32_T b_mIneq;
  int32_T h_idx;
  int32_T mEq;
  int32_T mFixed;
  int32_T mIneq;
  int32_T mLB;
  int32_T mUB;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  if (obj->probType == 2) {
    v = 0.0;
    b_mIneq = obj->sizes[2] - 1;
    mEq = obj->sizes[1] - 1;
    for (mIneq = 0; mIneq <= b_mIneq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->bineq[mIneq];
    }

    xgemv_pyma(obj->nVarOrig, obj->sizes[2], obj->Aineq, obj->ldA, x,
               obj->maxConstrWorkspace, rtDW);
    for (mIneq = 0; mIneq <= b_mIneq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] -= x[obj->nVarOrig + mIneq];
      v = fmax(v, obj->maxConstrWorkspace[mIneq]);
    }

    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->beq[mIneq];
    }

    xgemv_pyma2(obj->nVarOrig, obj->sizes[1], obj->Aeq, obj->ldA, x,
                obj->maxConstrWorkspace, rtDW);
    b_mIneq = obj->nVarOrig + obj->sizes[2];
    mIneq = b_mIneq + obj->sizes[1];
    for (h_idx = 0; h_idx <= mEq; h_idx++) {
      obj->maxConstrWorkspace[h_idx] = (obj->maxConstrWorkspace[h_idx] -
        x[b_mIneq + h_idx]) + x[mIneq + h_idx];
      v = fmax(v, fabs(obj->maxConstrWorkspace[h_idx]));
    }
  } else {
    v = 0.0;
    mIneq = obj->sizes[2] - 1;
    mEq = obj->sizes[1] - 1;
    for (b_mIneq = 0; b_mIneq <= mIneq; b_mIneq++) {
      obj->maxConstrWorkspace[b_mIneq] = obj->bineq[b_mIneq];
    }

    xgemv_pyma(obj->nVar, obj->sizes[2], obj->Aineq, obj->ldA, x,
               obj->maxConstrWorkspace, rtDW);
    for (b_mIneq = 0; b_mIneq <= mIneq; b_mIneq++) {
      v = fmax(v, obj->maxConstrWorkspace[b_mIneq]);
    }

    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->beq[mIneq];
    }

    xgemv_pyma2(obj->nVar, obj->sizes[1], obj->Aeq, obj->ldA, x,
                obj->maxConstrWorkspace, rtDW);
    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      v = fmax(v, fabs(obj->maxConstrWorkspace[mIneq]));
    }
  }

  if (mLB > 0) {
    for (mEq = 0; mEq < mLB; mEq++) {
      v = fmax(v, -x[obj->indexLB[mEq] - 1] - obj->lb[obj->indexLB[mEq] - 1]);
    }
  }

  if (mUB > 0) {
    for (mLB = 0; mLB < mUB; mLB++) {
      v = fmax(v, x[obj->indexUB[mLB] - 1] - obj->ub[obj->indexUB[mLB] - 1]);
    }
  }

  if (mFixed > 0) {
    for (mUB = 0; mUB < mFixed; mUB++) {
      v = fmax(v, fabs(x[obj->indexFixed[mUB] - 1] - obj->ub[obj->indexFixed[mUB]
                       - 1]));
    }
  }

  return v;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void PresolveWorkingSet(sVm5xLhdFDU5OIlGg0pTc4E *solution,
  snRDwUdgrIx9qNga56nZ8DE *memspace, stxriBK2jD81NCGacZ0b8HD *workingset,
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, DW *rtDW)
{
  solution->state = 82;
  RemoveDependentEq_(memspace, &rtDW->b_g, workingset, qrmanager, rtDW);
  if ((rtDW->b_g != -1) && (workingset->nActiveConstr <= qrmanager->ldq)) {
    RemoveDependentIneq_(workingset, qrmanager, memspace, 100.0, rtDW);
    feasibleX0ForWorkingSet(memspace->workspace_double, solution->xstar,
      workingset, qrmanager, rtDW);
    if (workingset->nWConstr[0] + workingset->nWConstr[1] == workingset->nVar) {
      rtDW->constrViolation_m = maxConstraintViolation_pn(workingset,
        solution->xstar, rtDW);
      if (rtDW->constrViolation_m > 1.0E-8) {
        solution->state = -2;
      }
    }
  } else {
    solution->state = -3;
    removeAllIneqConstr(workingset);
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void modifyOverheadPhaseOne_(stxriBK2jD81NCGacZ0b8HD *obj)
{
  int32_T idx;
  int32_T idxEq;
  for (idx = 0; idx < obj->sizes[0]; idx++) {
    obj->ATwset[(obj->nVar + obj->ldA * idx) - 1] = 0.0;
  }

  for (idx = 0; idx < obj->sizes[1]; idx++) {
    idxEq = (obj->ldA * idx + obj->nVar) - 1;
    obj->Aeq[idxEq] = 0.0;
    obj->ATwset[idxEq + obj->ldA * (obj->isActiveIdx[1] - 1)] = 0.0;
  }

  for (idx = 0; idx < obj->sizes[2]; idx++) {
    obj->Aineq[(obj->nVar + obj->ldA * idx) - 1] = -1.0;
  }

  obj->indexLB[obj->sizes[3] - 1] = obj->nVar;
  obj->lb[obj->nVar - 1] = obj->SLACK0;
  for (idx = obj->isActiveIdx[2]; idx <= obj->nActiveConstr; idx++) {
    obj->ATwset[(obj->nVar + obj->ldA * (idx - 1)) - 1] = -1.0;
  }

  if (obj->nWConstr[4] > 0) {
    for (idx = 0; idx <= obj->sizesNormal[4]; idx++) {
      obj->isActiveConstr[(obj->isActiveIdx[4] + idx) - 1] = false;
    }
  }

  obj->isActiveConstr[obj->isActiveIdx[4] - 2] = false;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void setProblemType(stxriBK2jD81NCGacZ0b8HD *obj, int32_T PROBLEM_TYPE)
{
  int32_T colOffsetATw;
  int32_T colOffsetAeq;
  int32_T colOffsetAineq;
  int32_T d_idx_row;
  int32_T offsetEq1;
  int32_T offsetEq1_tmp;
  int32_T offsetEq2;
  int32_T offsetIneq;
  switch (PROBLEM_TYPE) {
   case 3:
    obj->nVar = obj->nVarOrig;
    obj->mConstr = obj->mConstrOrig;
    if (obj->nWConstr[4] > 0) {
      for (offsetIneq = -1; offsetIneq < obj->sizesNormal[4] - 1; offsetIneq++)
      {
        obj->isActiveConstr[obj->isActiveIdxNormal[4] + offsetIneq] =
          obj->isActiveConstr[obj->isActiveIdx[4] + offsetIneq];
      }
    }

    for (offsetEq1 = 0; offsetEq1 < 5; offsetEq1++) {
      obj->sizes[offsetEq1] = obj->sizesNormal[offsetEq1];
    }

    for (offsetEq1 = 0; offsetEq1 < 6; offsetEq1++) {
      obj->isActiveIdx[offsetEq1] = obj->isActiveIdxNormal[offsetEq1];
    }
    break;

   case 1:
    obj->nVar = obj->nVarOrig + 1;
    obj->mConstr = obj->mConstrOrig + 1;
    for (offsetEq1 = 0; offsetEq1 < 5; offsetEq1++) {
      obj->sizes[offsetEq1] = obj->sizesPhaseOne[offsetEq1];
    }

    for (offsetEq1 = 0; offsetEq1 < 6; offsetEq1++) {
      obj->isActiveIdx[offsetEq1] = obj->isActiveIdxPhaseOne[offsetEq1];
    }

    modifyOverheadPhaseOne_(obj);
    break;

   case 2:
    obj->nVar = obj->nVarMax - 1;
    obj->mConstr = obj->mConstrMax - 1;
    for (offsetEq1 = 0; offsetEq1 < 5; offsetEq1++) {
      obj->sizes[offsetEq1] = obj->sizesRegularized[offsetEq1];
    }

    if (obj->probType != 4) {
      offsetIneq = obj->nVarOrig + 1;
      offsetEq1_tmp = obj->nVarOrig + obj->sizes[2];
      offsetEq2 = offsetEq1_tmp + obj->sizes[1];
      for (colOffsetAineq = 0; colOffsetAineq < obj->sizes[0]; colOffsetAineq++)
      {
        colOffsetATw = obj->ldA * colOffsetAineq;
        for (colOffsetAeq = obj->nVarOrig + 1; colOffsetAeq <= obj->nVar;
             colOffsetAeq++) {
          obj->ATwset[(colOffsetAeq + colOffsetATw) - 1] = 0.0;
        }
      }

      for (colOffsetATw = -1; colOffsetATw < obj->sizes[2] - 1; colOffsetATw++)
      {
        colOffsetAineq = (colOffsetATw + 1) * obj->ldA - 1;
        colOffsetAeq = colOffsetATw + offsetIneq;
        for (offsetEq1 = offsetIneq; offsetEq1 <= colOffsetAeq; offsetEq1++) {
          obj->Aineq[offsetEq1 + colOffsetAineq] = 0.0;
        }

        obj->Aineq[(colOffsetAeq + colOffsetAineq) + 1] = -1.0;
        for (colOffsetAeq += 2; colOffsetAeq <= obj->nVar; colOffsetAeq++) {
          obj->Aineq[colOffsetAeq + colOffsetAineq] = 0.0;
        }
      }

      for (colOffsetAineq = 1; colOffsetAineq - 1 < obj->sizes[1];
           colOffsetAineq++) {
        colOffsetAeq = (colOffsetAineq - 1) * obj->ldA - 1;
        colOffsetATw = (obj->isActiveIdx[1] - 1) * obj->ldA + colOffsetAeq;
        for (d_idx_row = offsetIneq; d_idx_row <= offsetEq1_tmp; d_idx_row++) {
          obj->Aeq[d_idx_row + colOffsetAeq] = 0.0;
          obj->ATwset[d_idx_row + colOffsetATw] = 0.0;
        }

        d_idx_row = (offsetEq1_tmp + colOffsetAineq) - 1;
        for (offsetEq1 = offsetEq1_tmp + 1; offsetEq1 <= d_idx_row; offsetEq1++)
        {
          obj->Aeq[offsetEq1 + colOffsetAeq] = 0.0;
          obj->ATwset[offsetEq1 + colOffsetATw] = 0.0;
        }

        obj->Aeq[(offsetEq1_tmp + colOffsetAineq) + colOffsetAeq] = -1.0;
        offsetEq1 = offsetEq1_tmp + colOffsetAineq;
        obj->ATwset[offsetEq1 + colOffsetATw] = -1.0;
        for (d_idx_row = offsetEq1 + 1; d_idx_row <= offsetEq2; d_idx_row++) {
          obj->Aeq[d_idx_row + colOffsetAeq] = 0.0;
          obj->ATwset[d_idx_row + colOffsetATw] = 0.0;
        }

        d_idx_row = (offsetEq2 + colOffsetAineq) - 1;
        for (offsetEq1 = offsetEq2 + 1; offsetEq1 <= d_idx_row; offsetEq1++) {
          obj->Aeq[offsetEq1 + colOffsetAeq] = 0.0;
          obj->ATwset[offsetEq1 + colOffsetATw] = 0.0;
        }

        offsetEq1 = offsetEq2 + colOffsetAineq;
        obj->Aeq[offsetEq1 + colOffsetAeq] = 1.0;
        obj->ATwset[offsetEq1 + colOffsetATw] = 1.0;
        for (d_idx_row = (offsetEq2 + colOffsetAineq) + 1; d_idx_row <=
             obj->nVar; d_idx_row++) {
          obj->Aeq[d_idx_row + colOffsetAeq] = 0.0;
          obj->ATwset[d_idx_row + colOffsetATw] = 0.0;
        }
      }

      offsetEq1 = obj->nVarOrig;
      for (offsetEq2 = obj->sizesNormal[3]; offsetEq2 < obj->sizesRegularized[3];
           offsetEq2++) {
        offsetEq1++;
        obj->indexLB[offsetEq2] = offsetEq1;
      }

      if (obj->nWConstr[4] > 0) {
        for (offsetEq1 = -1; offsetEq1 < obj->sizesRegularized[4] - 1; offsetEq1
             ++) {
          obj->isActiveConstr[(obj->isActiveIdxRegularized[4] + offsetEq1) + 1] =
            obj->isActiveConstr[obj->isActiveIdx[4] + offsetEq1];
        }
      }

      for (offsetEq1 = obj->isActiveIdx[4]; offsetEq1 <
           obj->isActiveIdxRegularized[4]; offsetEq1++) {
        obj->isActiveConstr[offsetEq1 - 1] = false;
      }

      offsetEq1 = (obj->nVarOrig + obj->sizes[2]) + (obj->sizes[1] << 1);
      for (offsetEq2 = obj->nVarOrig; offsetEq2 < offsetEq1; offsetEq2++) {
        obj->lb[offsetEq2] = 0.0;
      }

      for (offsetEq1 = obj->isActiveIdx[2] - 1; offsetEq1 < obj->nActiveConstr;
           offsetEq1++) {
        colOffsetATw = obj->ldA * offsetEq1 - 1;
        if (obj->Wid[offsetEq1] == 3) {
          offsetEq2 = offsetIneq + obj->Wlocalidx[offsetEq1];
          for (colOffsetAineq = offsetIneq; colOffsetAineq <= offsetEq2 - 2;
               colOffsetAineq++) {
            obj->ATwset[colOffsetAineq + colOffsetATw] = 0.0;
          }

          obj->ATwset[((offsetIneq + obj->Wlocalidx[offsetEq1]) + colOffsetATw)
            - 1] = -1.0;
          for (offsetEq2 = offsetIneq + obj->Wlocalidx[offsetEq1]; offsetEq2 <=
               obj->nVar; offsetEq2++) {
            obj->ATwset[offsetEq2 + colOffsetATw] = 0.0;
          }
        } else {
          for (offsetEq2 = offsetIneq; offsetEq2 <= obj->nVar; offsetEq2++) {
            obj->ATwset[offsetEq2 + colOffsetATw] = 0.0;
          }
        }
      }
    }

    for (offsetEq1 = 0; offsetEq1 < 6; offsetEq1++) {
      obj->isActiveIdx[offsetEq1] = obj->isActiveIdxRegularized[offsetEq1];
    }
    break;

   default:
    obj->nVar = obj->nVarMax;
    obj->mConstr = obj->mConstrMax;
    for (offsetEq1 = 0; offsetEq1 < 5; offsetEq1++) {
      obj->sizes[offsetEq1] = obj->sizesRegPhaseOne[offsetEq1];
    }

    for (offsetEq1 = 0; offsetEq1 < 6; offsetEq1++) {
      obj->isActiveIdx[offsetEq1] = obj->isActiveIdxRegPhaseOne[offsetEq1];
    }

    modifyOverheadPhaseOne_(obj);
    break;
  }

  obj->probType = PROBLEM_TYPE;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void linearForm_(boolean_T obj_hasLinear, int32_T obj_nvar, real_T
  workspace[80], const real_T H[49], const real_T f[7], const real_T x[8])
{
  real_T c;
  int32_T b;
  int32_T b_c;
  int32_T fMultiplier;
  int32_T ia;
  int32_T iac;
  int32_T iy;
  fMultiplier = 0;
  if (obj_hasLinear) {
    while (fMultiplier <= obj_nvar - 1) {
      workspace[fMultiplier] = f[fMultiplier];
      fMultiplier++;
    }

    fMultiplier = 1;
  }

  if (obj_nvar != 0) {
    if (fMultiplier != 1) {
      while (fMultiplier <= obj_nvar - 1) {
        workspace[fMultiplier] = 0.0;
        fMultiplier++;
      }
    }

    fMultiplier = 0;
    b_c = (obj_nvar - 1) * obj_nvar + 1;
    iac = 1;
    while (((obj_nvar > 0) && (iac <= b_c)) || ((obj_nvar < 0) && (iac >= b_c)))
    {
      c = 0.5 * x[fMultiplier];
      iy = 0;
      b = (iac + obj_nvar) - 1;
      for (ia = iac; ia <= b; ia++) {
        workspace[iy] += H[ia - 1] * c;
        iy++;
      }

      fMultiplier++;
      iac += obj_nvar;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real_T computeFval(const shohwUBaOGHF036TMzc1KEH *obj, real_T workspace
  [80], const real_T H[49], const real_T f[7], const real_T x[8])
{
  real_T val;
  int32_T b_k;
  val = 0.0;
  switch (obj->objtype) {
   case 5:
    val = x[obj->nvar - 1] * obj->gammaScalar;
    break;

   case 3:
    linearForm_(obj->hasLinear, obj->nvar, workspace, H, f, x);
    if (obj->nvar >= 1) {
      for (b_k = 0; b_k < obj->nvar; b_k++) {
        val += x[b_k] * workspace[b_k];
      }
    }
    break;

   case 4:
    linearForm_(obj->hasLinear, obj->nvar, workspace, H, f, x);
    for (b_k = obj->nvar; b_k < obj->maxVar - 1; b_k++) {
      workspace[b_k] = 0.5 * obj->beta * x[b_k] + obj->rho;
    }

    if (obj->maxVar - 1 >= 1) {
      for (b_k = 0; b_k <= obj->maxVar - 2; b_k++) {
        val += x[b_k] * workspace[b_k];
      }
    }
    break;
  }

  return val;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv_pyma2z(int32_T m, int32_T n, const real_T A[49], int32_T lda,
  const real_T x[8], real_T y[7])
{
  int32_T b;
  int32_T c;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  if ((m != 0) && (n != 0)) {
    for (ix = 0; ix < m; ix++) {
      y[ix] = 0.0;
    }

    ix = 0;
    c = (n - 1) * lda + 1;
    iac = 1;
    while (((lda > 0) && (iac <= c)) || ((lda < 0) && (iac >= c))) {
      iy = 0;
      b = (iac + m) - 1;
      for (ia = iac; ia <= b; ia++) {
        y[iy] += A[ia - 1] * x[ix];
        iy++;
      }

      ix++;
      iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void computeGrad_StoreHx(shohwUBaOGHF036TMzc1KEH *obj, const real_T H[49],
  const real_T f[7], const real_T x[8])
{
  int32_T b_i;
  int32_T d_i;
  int32_T maxRegVar;
  switch (obj->objtype) {
   case 5:
    for (b_i = 0; b_i <= obj->nvar - 2; b_i++) {
      obj->grad[b_i] = 0.0;
    }

    obj->grad[obj->nvar - 1] = obj->gammaScalar;
    break;

   case 3:
    xgemv_pyma2z(obj->nvar, obj->nvar, H, obj->nvar, x, obj->Hx);
    for (maxRegVar = 0; maxRegVar < obj->nvar; maxRegVar++) {
      obj->grad[maxRegVar] = obj->Hx[maxRegVar];
    }

    if (obj->hasLinear && (obj->nvar >= 1)) {
      b_i = obj->nvar - 1;
      for (maxRegVar = 0; maxRegVar <= b_i; maxRegVar++) {
        obj->grad[maxRegVar] += f[maxRegVar];
      }
    }
    break;

   case 4:
    maxRegVar = obj->maxVar - 1;
    xgemv_pyma2z(obj->nvar, obj->nvar, H, obj->nvar, x, obj->Hx);
    for (b_i = obj->nvar; b_i < maxRegVar; b_i++) {
      obj->Hx[b_i] = obj->beta * x[b_i];
    }

    for (d_i = 0; d_i < maxRegVar; d_i++) {
      obj->grad[d_i] = obj->Hx[d_i];
    }

    if (obj->hasLinear && (obj->nvar >= 1)) {
      b_i = obj->nvar - 1;
      for (maxRegVar = 0; maxRegVar <= b_i; maxRegVar++) {
        obj->grad[maxRegVar] += f[maxRegVar];
      }
    }

    b_i = (obj->maxVar - obj->nvar) - 1;
    if (b_i >= 1) {
      maxRegVar = obj->nvar;
      for (d_i = 0; d_i < b_i; d_i++) {
        obj->grad[maxRegVar] += obj->rho;
        maxRegVar++;
      }
    }
    break;
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real_T computeFval_ReuseHx(const shohwUBaOGHF036TMzc1KEH *obj, real_T
  workspace[80], const real_T f[7], const real_T x[8])
{
  real_T val;
  int32_T c_k;
  int32_T k;
  int32_T maxRegVar;
  val = 0.0;
  switch (obj->objtype) {
   case 5:
    val = x[obj->nvar - 1] * obj->gammaScalar;
    break;

   case 3:
    if (obj->hasLinear) {
      for (maxRegVar = 0; maxRegVar < obj->nvar; maxRegVar++) {
        workspace[maxRegVar] = 0.5 * obj->Hx[maxRegVar] + f[maxRegVar];
      }

      if (obj->nvar >= 1) {
        for (maxRegVar = 0; maxRegVar < obj->nvar; maxRegVar++) {
          val += x[maxRegVar] * workspace[maxRegVar];
        }
      }
    } else {
      if (obj->nvar >= 1) {
        for (maxRegVar = 0; maxRegVar < obj->nvar; maxRegVar++) {
          val += x[maxRegVar] * obj->Hx[maxRegVar];
        }
      }

      val *= 0.5;
    }
    break;

   case 4:
    maxRegVar = obj->maxVar - 1;
    if (obj->hasLinear) {
      for (c_k = 0; c_k < obj->nvar; c_k++) {
        workspace[c_k] = f[c_k];
      }

      k = obj->maxVar - obj->nvar;
      for (c_k = 0; c_k <= k - 2; c_k++) {
        workspace[obj->nvar + c_k] = obj->rho;
      }

      for (c_k = 0; c_k < maxRegVar; c_k++) {
        workspace[c_k] += 0.5 * obj->Hx[c_k];
      }

      if (obj->maxVar - 1 >= 1) {
        for (maxRegVar = 0; maxRegVar <= obj->maxVar - 2; maxRegVar++) {
          val += x[maxRegVar] * workspace[maxRegVar];
        }
      }
    } else {
      if (obj->maxVar - 1 >= 1) {
        for (k = 0; k <= obj->maxVar - 2; k++) {
          val += x[k] * obj->Hx[k];
        }
      }

      val *= 0.5;
      for (k = obj->nvar; k < maxRegVar; k++) {
        val += x[k] * obj->rho;
      }
    }
    break;
  }

  return val;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void printHeader(void)
{
  printf("                          First-order                                                                          Active\n");
  fflush(stdout);
  printf(" Iter            Fval      Optimality     Feasibility           alpha    Norm of step           Action     Constraints    Step Type\n");
  fflush(stdout);
  printf("\n");
  fflush(stdout);
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void printInitialInfo(int32_T PROBLEM_TYPE, real_T solution_fstar,
  int32_T solution_iterations, int32_T workingset_nActiveConstr)
{
  int32_T i;
  char_T varargin_4[14];
  char_T stepType_str[13];
  static const char_T b[13] = { 'N', 'o', 'r', 'm', 'a', 'l', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ' };

  static const char_T c[13] = { 'P', 'h', 'a', 's', 'e', ' ', 'O', 'n', 'e', ' ',
    ' ', ' ', ' ' };

  static const char_T d[13] = { 'R', 'e', 'g', 'u', 'l', 'a', 'r', 'i', 'z', 'e',
    'd', ' ', ' ' };

  static const char_T e[13] = { 'P', 'h', 'a', 's', 'e', ' ', 'O', 'n', 'e', ' ',
    'R', 'e', 'g' };

  switch (PROBLEM_TYPE) {
   case 1:
    for (i = 0; i < 13; i++) {
      stepType_str[i] = c[i];
    }
    break;

   case 2:
    for (i = 0; i < 13; i++) {
      stepType_str[i] = d[i];
    }
    break;

   case 4:
    for (i = 0; i < 13; i++) {
      stepType_str[i] = e[i];
    }
    break;

   default:
    for (i = 0; i < 13; i++) {
      stepType_str[i] = b[i];
    }
    break;
  }

  for (i = 0; i < 13; i++) {
    varargin_4[i] = stepType_str[i];
  }

  varargin_4[13] = '\x00';
  printf("%5i  %14.6e                                                                                            %5i    %s",
         solution_iterations, solution_fstar, workingset_nActiveConstr,
         &varargin_4[0]);
  fflush(stdout);
  printf("\n");
  fflush(stdout);
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xrotg(real_T *a, real_T *b, real_T *c, real_T *s, DW *rtDW)
{
  real_T ads;
  real_T bds;
  real_T scale;
  rtDW->roe = *b;
  rtDW->absa = fabs(*a);
  rtDW->absb = fabs(*b);
  if (rtDW->absa > rtDW->absb) {
    rtDW->roe = *a;
  }

  scale = rtDW->absa + rtDW->absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    *b = 0.0;
  } else {
    ads = rtDW->absa / scale;
    bds = rtDW->absb / scale;
    scale *= sqrt(ads * ads + bds * bds);
    if (rtDW->roe < 0.0) {
      scale = -scale;
    }

    *c = *a / scale;
    *s = *b / scale;
    if (rtDW->absa > rtDW->absb) {
      *b = *s;
    } else if (*c != 0.0) {
      *b = 1.0 / *c;
    } else {
      *b = 1.0;
    }
  }

  *a = scale;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void deleteColMoveEnd(sCS11Pe0E6xKX8jGoaG4cLG *obj, int32_T idx, DW *rtDW)
{
  int32_T QRk0;
  int32_T b_ix;
  int32_T d_k;
  int32_T i;
  int32_T idxRotGCol;
  int32_T ix;
  int32_T k;
  if (obj->usedPivoting) {
    i = 1;
    while ((i <= obj->ncols) && (obj->jpvt[i - 1] != idx)) {
      i++;
    }

    idx = i;
  }

  if (idx >= obj->ncols) {
    obj->ncols--;
  } else {
    obj->jpvt[idx - 1] = obj->jpvt[obj->ncols - 1];
    for (i = 0; i < obj->minRowCol; i++) {
      obj->QR[i + obj->ldq * (idx - 1)] = obj->QR[(obj->ncols - 1) * obj->ldq +
        i];
    }

    obj->ncols--;
    if (obj->mrows < obj->ncols) {
      obj->minRowCol = obj->mrows;
    } else {
      obj->minRowCol = obj->ncols;
    }

    if (idx < obj->mrows) {
      if (obj->mrows - 1 < obj->ncols) {
        i = obj->mrows - 1;
      } else {
        i = obj->ncols;
      }

      k = i;
      idxRotGCol = (idx - 1) * obj->ldq;
      while (k >= idx) {
        QRk0 = k + idxRotGCol;
        rtDW->b_temp_g = obj->QR[QRk0 - 1];
        rtDW->e = obj->QR[QRk0];
        xrotg(&rtDW->b_temp_g, &rtDW->e, &rtDW->c_c, &rtDW->b_s, rtDW);
        obj->QR[QRk0 - 1] = rtDW->b_temp_g;
        obj->QR[QRk0] = rtDW->e;
        obj->QR[k + obj->ldq * (k - 1)] = 0.0;
        QRk0 = obj->ldq * idx + k;
        b_ix = obj->ncols - idx;
        if (b_ix >= 1) {
          ix = QRk0 - 1;
          for (d_k = 0; d_k < b_ix; d_k++) {
            rtDW->b_temp_g = rtDW->c_c * obj->QR[ix] + rtDW->b_s * obj->QR[QRk0];
            obj->QR[QRk0] = rtDW->c_c * obj->QR[QRk0] - rtDW->b_s * obj->QR[ix];
            obj->QR[ix] = rtDW->b_temp_g;
            QRk0 += obj->ldq;
            ix += obj->ldq;
          }
        }

        b_ix = (k - 1) * obj->ldq;
        if (obj->mrows >= 1) {
          QRk0 = obj->ldq + b_ix;
          for (ix = 0; ix < obj->mrows; ix++) {
            rtDW->b_temp_g = rtDW->c_c * obj->Q[b_ix] + rtDW->b_s * obj->Q[QRk0];
            obj->Q[QRk0] = rtDW->c_c * obj->Q[QRk0] - rtDW->b_s * obj->Q[b_ix];
            obj->Q[b_ix] = rtDW->b_temp_g;
            QRk0++;
            b_ix++;
          }
        }

        k--;
      }

      for (k = idx + 1; k <= i; k++) {
        QRk0 = k + (k - 1) * obj->ldq;
        rtDW->b_temp_g = obj->QR[QRk0 - 1];
        rtDW->e = obj->QR[QRk0];
        xrotg(&rtDW->b_temp_g, &rtDW->e, &rtDW->c_c, &rtDW->b_s, rtDW);
        obj->QR[QRk0 - 1] = rtDW->b_temp_g;
        obj->QR[QRk0] = rtDW->e;
        QRk0 = (obj->ldq + 1) * k;
        idxRotGCol = obj->ncols - k;
        if (idxRotGCol >= 1) {
          b_ix = QRk0 - 1;
          for (ix = 0; ix < idxRotGCol; ix++) {
            rtDW->b_temp_g = rtDW->c_c * obj->QR[b_ix] + rtDW->b_s * obj->
              QR[QRk0];
            obj->QR[QRk0] = rtDW->c_c * obj->QR[QRk0] - rtDW->b_s * obj->QR[b_ix];
            obj->QR[b_ix] = rtDW->b_temp_g;
            QRk0 += obj->ldq;
            b_ix += obj->ldq;
          }
        }

        idxRotGCol = (k - 1) * obj->ldq;
        if (obj->mrows >= 1) {
          QRk0 = obj->ldq + idxRotGCol;
          for (b_ix = 0; b_ix < obj->mrows; b_ix++) {
            rtDW->b_temp_g = rtDW->c_c * obj->Q[idxRotGCol] + rtDW->b_s * obj->
              Q[QRk0];
            obj->Q[QRk0] = rtDW->c_c * obj->Q[QRk0] - rtDW->b_s * obj->
              Q[idxRotGCol];
            obj->Q[idxRotGCol] = rtDW->b_temp_g;
            QRk0++;
            idxRotGCol++;
          }
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void computeProjectedHessian(const real_T H[49], sSzLoP8tvZHiR1V2perTtWD *
  cholmanager, const sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, snRDwUdgrIx9qNga56nZ8DE
  *memspace, DW *rtDW)
{
  int32_T ar;
  int32_T b_c;
  int32_T b_cr;
  int32_T b_ic;
  int32_T br;
  int32_T c;
  int32_T d;
  int32_T ia;
  int32_T ib;
  int32_T ldQ;
  int32_T ldm;
  int32_T mNull;
  int32_T nVars;
  int32_T nullStart;
  nVars = qrmanager->mrows;
  mNull = qrmanager->mrows - qrmanager->ncols;
  ldm = cholmanager->ldm;
  ldQ = qrmanager->ldq;
  nullStart = qrmanager->ldq * qrmanager->ncols;
  if ((qrmanager->mrows != 0) && (mNull != 0)) {
    b_c = (mNull - 1) * 10;
    for (br = 0; br <= b_c; br += 10) {
      b_cr = br + nVars;
      for (ar = br; ar < b_cr; ar++) {
        memspace->workspace_double[ar] = 0.0;
      }
    }

    br = nullStart;
    for (b_cr = 0; b_cr <= b_c; b_cr += 10) {
      ar = -1;
      c = br + nVars;
      for (ib = br; ib < c; ib++) {
        ia = ar;
        d = b_cr + nVars;
        for (b_ic = b_cr; b_ic < d; b_ic++) {
          ia++;
          memspace->workspace_double[b_ic] += qrmanager->Q[ib] * H[ia];
        }

        ar += nVars;
      }

      br += ldQ;
    }
  }

  if (mNull != 0) {
    b_c = (mNull - 1) * cholmanager->ldm;
    br = 0;
    while (((ldm > 0) && (br <= b_c)) || ((ldm < 0) && (br >= b_c))) {
      b_cr = br + mNull;
      for (ar = br; ar < b_cr; ar++) {
        cholmanager->FMat[ar] = 0.0;
      }

      br += ldm;
    }

    br = -1;
    b_cr = 0;
    while (((ldm > 0) && (b_cr <= b_c)) || ((ldm < 0) && (b_cr >= b_c))) {
      ar = nullStart;
      c = b_cr + mNull;
      for (ib = b_cr; ib < c; ib++) {
        rtDW->b_temp = 0.0;
        for (ia = 1; ia - 1 < nVars; ia++) {
          rtDW->b_temp += qrmanager->Q[(ia + ar) - 1] *
            memspace->workspace_double[ia + br];
        }

        cholmanager->FMat[ib] += rtDW->b_temp;
        ar += ldQ;
      }

      br += 10;
      b_cr += ldm;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static int32_T ixamax(int32_T n, const real_T x[81], int32_T incx)
{
  real_T smax;
  real_T y;
  int32_T idxmax;
  int32_T ix;
  int32_T k;
  if ((n < 1) || (incx < 1)) {
    idxmax = 0;
  } else {
    idxmax = 1;
    if (n > 1) {
      ix = 0;
      smax = fabs(x[0]);
      for (k = 2; k <= n; k++) {
        ix += incx;
        y = fabs(x[ix]);
        if (y > smax) {
          idxmax = k;
          smax = y;
        }
      }
    }
  }

  return idxmax;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void fullColLDL2_(sSzLoP8tvZHiR1V2perTtWD *obj, int32_T LD_offset,
  int32_T NColsRemain, real_T REG_PRIMAL)
{
  real_T neg_D;
  real_T temp;
  int32_T LD_diagOffset;
  int32_T LDimSizeP1;
  int32_T b;
  int32_T ijA;
  int32_T ix;
  int32_T j;
  int32_T jA;
  int32_T jy;
  int32_T k;
  int32_T subMatrixDim;
  LDimSizeP1 = obj->ldm;
  for (k = 0; k < NColsRemain; k++) {
    LD_diagOffset = ((LDimSizeP1 + 1) * k + LD_offset) - 1;
    if (fabs(obj->FMat[LD_diagOffset]) <= obj->regTol_) {
      obj->FMat[LD_diagOffset] += REG_PRIMAL;
    }

    neg_D = -1.0 / obj->FMat[LD_diagOffset];
    subMatrixDim = (NColsRemain - k) - 2;
    for (jA = 0; jA <= subMatrixDim; jA++) {
      obj->workspace_[jA] = obj->FMat[(LD_diagOffset + jA) + 1];
    }

    if (neg_D != 0.0) {
      jA = (LD_diagOffset + LDimSizeP1) + 1;
      jy = 0;
      for (j = 0; j <= subMatrixDim; j++) {
        if (obj->workspace_[jy] != 0.0) {
          temp = obj->workspace_[jy] * neg_D;
          ix = 0;
          b = subMatrixDim + jA;
          for (ijA = jA; ijA < b + 1; ijA++) {
            obj->FMat[ijA] += obj->workspace_[ix] * temp;
            ix++;
          }
        }

        jy++;
        jA += obj->ldm;
      }
    }

    for (jA = 1; jA - 1 <= subMatrixDim; jA++) {
      jy = LD_diagOffset + jA;
      obj->FMat[jy] /= obj->FMat[LD_diagOffset];
    }
  }

  LDimSizeP1 = ((obj->ldm + 1) * (NColsRemain - 1) + LD_offset) - 1;
  if (fabs(obj->FMat[LDimSizeP1]) <= obj->regTol_) {
    obj->FMat[LDimSizeP1] += REG_PRIMAL;
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv_pyma2zx(int32_T m, int32_T n, const real_T A[81], int32_T ia0,
  int32_T lda, const real_T x[80], real_T y[8])
{
  int32_T b;
  int32_T c;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  if ((m != 0) && (n != 0)) {
    for (ix = 0; ix < m; ix++) {
      y[ix] = 0.0;
    }

    ix = 0;
    b = (n - 1) * lda + ia0;
    iac = ia0;
    while (((lda > 0) && (iac <= b)) || ((lda < 0) && (iac >= b))) {
      iy = 0;
      c = (iac + m) - 1;
      for (ia = iac; ia <= c; ia++) {
        y[iy] += A[ia - 1] * x[ix];
        iy++;
      }

      ix++;
      iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void compute_deltax(const real_T H[49], sVm5xLhdFDU5OIlGg0pTc4E *solution,
  snRDwUdgrIx9qNga56nZ8DE *memspace, const sCS11Pe0E6xKX8jGoaG4cLG *qrmanager,
  sSzLoP8tvZHiR1V2perTtWD *cholmanager, const shohwUBaOGHF036TMzc1KEH *objective,
  DW *rtDW)
{
  int32_T exitg1;
  rtDW->nVar_o = qrmanager->mrows - 1;
  rtDW->mNull = qrmanager->mrows - qrmanager->ncols;
  if (rtDW->mNull <= 0) {
    rtDW->mNull = 0;
    while (rtDW->mNull <= rtDW->nVar_o) {
      solution->searchDir[rtDW->mNull] = 0.0;
      rtDW->mNull++;
    }
  } else {
    rtDW->nullStartIdx = 0;
    while (rtDW->nullStartIdx <= rtDW->nVar_o) {
      solution->searchDir[rtDW->nullStartIdx] = -objective->grad
        [rtDW->nullStartIdx];
      rtDW->nullStartIdx++;
    }

    if (qrmanager->ncols <= 0) {
      if (objective->objtype == 3) {
        rtDW->b_SCALED_REG_PRIMAL = 1.4901161193847656E-8 *
          cholmanager->scaleFactor * (real_T)qrmanager->mrows;
        cholmanager->ndims = qrmanager->mrows;
        rtDW->mNull = 0;
        while (rtDW->mNull <= rtDW->nVar_o) {
          rtDW->nullStartIdx = (rtDW->nVar_o + 1) * rtDW->mNull;
          rtDW->b_A_maxDiag_idx = cholmanager->ldm * rtDW->mNull;
          rtDW->b_jjA = 1;
          while (rtDW->b_jjA - 1 <= rtDW->nVar_o) {
            cholmanager->FMat[(rtDW->b_A_maxDiag_idx + rtDW->b_jjA) - 1] = H
              [(rtDW->nullStartIdx + rtDW->b_jjA) - 1];
            rtDW->b_jjA++;
          }

          rtDW->mNull++;
        }

        rtDW->mNull = ixamax(qrmanager->mrows, cholmanager->FMat,
                             cholmanager->ldm + 1) - 1;
        cholmanager->regTol_ = fmax(fabs(cholmanager->FMat[cholmanager->ldm *
          rtDW->mNull + rtDW->mNull]) * 2.2204460492503131E-16, fabs
          (rtDW->b_SCALED_REG_PRIMAL));
        fullColLDL2_(cholmanager, 1, qrmanager->mrows, rtDW->b_SCALED_REG_PRIMAL);
        if (cholmanager->ConvexCheck) {
          rtDW->mNull = 0;
          do {
            exitg1 = 0;
            if (rtDW->mNull <= rtDW->nVar_o) {
              if (cholmanager->FMat[cholmanager->ldm * rtDW->mNull + rtDW->mNull]
                  <= 0.0) {
                cholmanager->info = -rtDW->mNull - 1;
                exitg1 = 1;
              } else {
                rtDW->mNull++;
              }
            } else {
              cholmanager->ConvexCheck = false;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          rtDW->iac = cholmanager->ndims - 1;
          if (cholmanager->ndims != 0) {
            rtDW->nullStartIdx = 0;
            while (rtDW->nullStartIdx <= rtDW->iac) {
              rtDW->nVar_o = rtDW->nullStartIdx * cholmanager->ldm +
                rtDW->nullStartIdx;
              rtDW->b_A_maxDiag_idx = rtDW->iac - rtDW->nullStartIdx;
              rtDW->b_jjA = 1;
              while (rtDW->b_jjA - 1 <= rtDW->b_A_maxDiag_idx - 1) {
                rtDW->b_ix_f = rtDW->nullStartIdx + rtDW->b_jjA;
                solution->searchDir[rtDW->b_ix_f] -= cholmanager->FMat
                  [rtDW->nVar_o + rtDW->b_jjA] * solution->searchDir
                  [rtDW->nullStartIdx];
                rtDW->b_jjA++;
              }

              rtDW->nullStartIdx++;
            }
          }

          rtDW->mNull = 0;
          while (rtDW->mNull <= rtDW->iac) {
            solution->searchDir[rtDW->mNull] /= cholmanager->FMat
              [cholmanager->ldm * rtDW->mNull + rtDW->mNull];
            rtDW->mNull++;
          }

          if (cholmanager->ndims != 0) {
            rtDW->mNull = cholmanager->ndims - 1;
            while (rtDW->mNull + 1 > 0) {
              rtDW->nullStartIdx = rtDW->mNull * cholmanager->ldm;
              rtDW->b_SCALED_REG_PRIMAL = solution->searchDir[rtDW->mNull];
              rtDW->nVar_o = cholmanager->ndims;
              while (rtDW->nVar_o >= rtDW->mNull + 2) {
                rtDW->b_SCALED_REG_PRIMAL -= cholmanager->FMat
                  [(rtDW->nullStartIdx + rtDW->nVar_o) - 1] *
                  solution->searchDir[rtDW->nVar_o - 1];
                rtDW->nVar_o--;
              }

              solution->searchDir[rtDW->mNull] = rtDW->b_SCALED_REG_PRIMAL;
              rtDW->mNull--;
            }
          }
        }
      }
    } else {
      rtDW->nullStartIdx = qrmanager->ldq * qrmanager->ncols + 1;
      if (objective->objtype == 5) {
        rtDW->b_A_maxDiag_idx = 0;
        while (rtDW->b_A_maxDiag_idx <= rtDW->mNull - 1) {
          memspace->workspace_double[rtDW->b_A_maxDiag_idx] = -qrmanager->Q
            [(qrmanager->ncols + rtDW->b_A_maxDiag_idx) * qrmanager->ldq +
            rtDW->nVar_o];
          rtDW->b_A_maxDiag_idx++;
        }

        xgemv_pyma2zx(qrmanager->mrows, rtDW->mNull, qrmanager->Q,
                      rtDW->nullStartIdx, qrmanager->ldq,
                      memspace->workspace_double, solution->searchDir);
      } else {
        if (objective->objtype == 3) {
          computeProjectedHessian(H, cholmanager, qrmanager, memspace, rtDW);
        }

        rtDW->b_SCALED_REG_PRIMAL = 1.4901161193847656E-8 *
          cholmanager->scaleFactor * (real_T)rtDW->mNull;
        cholmanager->ndims = rtDW->mNull;
        rtDW->b_A_maxDiag_idx = ixamax(rtDW->mNull, cholmanager->FMat,
          cholmanager->ldm + 1) - 1;
        cholmanager->regTol_ = fmax(fabs(cholmanager->FMat[cholmanager->ldm *
          rtDW->b_A_maxDiag_idx + rtDW->b_A_maxDiag_idx]) *
          2.2204460492503131E-16, fabs(rtDW->b_SCALED_REG_PRIMAL));
        fullColLDL2_(cholmanager, 1, rtDW->mNull, rtDW->b_SCALED_REG_PRIMAL);
        if (cholmanager->ConvexCheck) {
          rtDW->b_A_maxDiag_idx = 0;
          do {
            exitg1 = 0;
            if (rtDW->b_A_maxDiag_idx <= rtDW->mNull - 1) {
              if (cholmanager->FMat[cholmanager->ldm * rtDW->b_A_maxDiag_idx +
                  rtDW->b_A_maxDiag_idx] <= 0.0) {
                cholmanager->info = -rtDW->b_A_maxDiag_idx - 1;
                exitg1 = 1;
              } else {
                rtDW->b_A_maxDiag_idx++;
              }
            } else {
              cholmanager->ConvexCheck = false;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          rtDW->b_A_maxDiag_idx = qrmanager->ldq;
          if (qrmanager->mrows != 0) {
            rtDW->b_jjA = 0;
            while (rtDW->b_jjA <= rtDW->mNull - 1) {
              memspace->workspace_double[rtDW->b_jjA] = 0.0;
              rtDW->b_jjA++;
            }

            rtDW->b_jjA = 0;
            rtDW->b_ix_f = (rtDW->mNull - 1) * qrmanager->ldq +
              rtDW->nullStartIdx;
            rtDW->iac = rtDW->nullStartIdx;
            while (((rtDW->b_A_maxDiag_idx > 0) && (rtDW->iac <= rtDW->b_ix_f)) ||
                   ((rtDW->b_A_maxDiag_idx < 0) && (rtDW->iac >= rtDW->b_ix_f)))
            {
              rtDW->ix_i = 0;
              rtDW->b_SCALED_REG_PRIMAL = 0.0;
              rtDW->d_f = rtDW->iac + rtDW->nVar_o;
              rtDW->ia_i = rtDW->iac;
              while (rtDW->ia_i <= rtDW->d_f) {
                rtDW->b_SCALED_REG_PRIMAL += qrmanager->Q[rtDW->ia_i - 1] *
                  objective->grad[rtDW->ix_i];
                rtDW->ix_i++;
                rtDW->ia_i++;
              }

              memspace->workspace_double[rtDW->b_jjA] +=
                -rtDW->b_SCALED_REG_PRIMAL;
              rtDW->b_jjA++;
              rtDW->iac += rtDW->b_A_maxDiag_idx;
            }
          }

          rtDW->d_f = cholmanager->ndims - 1;
          if (cholmanager->ndims != 0) {
            rtDW->b_A_maxDiag_idx = 0;
            while (rtDW->b_A_maxDiag_idx <= rtDW->d_f) {
              rtDW->b_jjA = rtDW->b_A_maxDiag_idx * cholmanager->ldm +
                rtDW->b_A_maxDiag_idx;
              rtDW->b_ix_f = rtDW->d_f - rtDW->b_A_maxDiag_idx;
              rtDW->iac = 1;
              while (rtDW->iac - 1 <= rtDW->b_ix_f - 1) {
                rtDW->ix_i = rtDW->b_A_maxDiag_idx + rtDW->iac;
                memspace->workspace_double[rtDW->ix_i] -= cholmanager->FMat
                  [rtDW->b_jjA + rtDW->iac] * memspace->workspace_double
                  [rtDW->b_A_maxDiag_idx];
                rtDW->iac++;
              }

              rtDW->b_A_maxDiag_idx++;
            }
          }

          rtDW->nVar_o = 0;
          while (rtDW->nVar_o <= rtDW->d_f) {
            memspace->workspace_double[rtDW->nVar_o] /= cholmanager->
              FMat[cholmanager->ldm * rtDW->nVar_o + rtDW->nVar_o];
            rtDW->nVar_o++;
          }

          if (cholmanager->ndims != 0) {
            rtDW->nVar_o = cholmanager->ndims - 1;
            while (rtDW->nVar_o + 1 > 0) {
              rtDW->b_A_maxDiag_idx = rtDW->nVar_o * cholmanager->ldm;
              rtDW->b_SCALED_REG_PRIMAL = memspace->workspace_double
                [rtDW->nVar_o];
              rtDW->b_jjA = cholmanager->ndims;
              while (rtDW->b_jjA >= rtDW->nVar_o + 2) {
                rtDW->b_SCALED_REG_PRIMAL -= cholmanager->FMat
                  [(rtDW->b_A_maxDiag_idx + rtDW->b_jjA) - 1] *
                  memspace->workspace_double[rtDW->b_jjA - 1];
                rtDW->b_jjA--;
              }

              memspace->workspace_double[rtDW->nVar_o] =
                rtDW->b_SCALED_REG_PRIMAL;
              rtDW->nVar_o--;
            }
          }

          xgemv_pyma2zx(qrmanager->mrows, rtDW->mNull, qrmanager->Q,
                        rtDW->nullStartIdx, qrmanager->ldq,
                        memspace->workspace_double, solution->searchDir);
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real_T xnrm2_j(int32_T n, const real_T x[8])
{
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[0]);
    } else {
      scale = 3.3121686421112381E-170;
      for (k = 0; k < n; k++) {
        absxk = fabs(x[k]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv_pyma2zxi(int32_T m, int32_T n, const real_T A[56], int32_T lda,
  const real_T x[8], real_T y[80])
{
  real_T c;
  int32_T b;
  int32_T b_iy;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  if ((m != 0) && (n != 0)) {
    for (b_iy = 0; b_iy < n; b_iy++) {
      y[b_iy] = -y[b_iy];
    }

    iy = 0;
    b_iy = (n - 1) * lda + 1;
    iac = 1;
    while (((lda > 0) && (iac <= b_iy)) || ((lda < 0) && (iac >= b_iy))) {
      ix = 0;
      c = 0.0;
      b = (iac + m) - 1;
      for (ia = iac; ia <= b; ia++) {
        c += A[ia - 1] * x[ix];
        ix++;
      }

      y[iy] += c;
      iy++;
      iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv_pyma2zxid(int32_T m, int32_T n, const real_T A[56], int32_T
  lda, const real_T x[8], real_T y[80])
{
  real_T c;
  int32_T b;
  int32_T b_c;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  if ((m != 0) && (n != 0)) {
    for (iy = 11; iy <= n + 10; iy++) {
      y[iy - 1] = 0.0;
    }

    iy = 10;
    b_c = (n - 1) * lda + 1;
    iac = 1;
    while (((lda > 0) && (iac <= b_c)) || ((lda < 0) && (iac >= b_c))) {
      ix = 0;
      c = 0.0;
      b = (iac + m) - 1;
      for (ia = iac; ia <= b; ia++) {
        c += A[ia - 1] * x[ix];
        ix++;
      }

      y[iy] += c;
      iy++;
      iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void ratiotest(const real_T solution_xstar[8], const real_T
                      solution_searchDir[8], real_T workspace[80], int32_T
                      workingset_nVar, int32_T workingset_ldA, const real_T
                      workingset_Aineq[56], const real_T workingset_bineq[7],
                      const real_T workingset_lb[8], const real_T workingset_ub
                      [8], const int32_T workingset_indexLB[8], const int32_T
                      workingset_indexUB[8], const int32_T workingset_sizes[5],
                      const int32_T workingset_isActiveIdx[6], const boolean_T
                      workingset_isActiveConstr[10], const int32_T
                      workingset_nWConstr[5], boolean_T isPhaseOne, real_T
                      tolcon, real_T *toldelta, real_T toltau, real_T *alpha,
                      boolean_T *newBlocking, int32_T *constrType, int32_T
                      *constrIdx, DW *rtDW)
{
  real_T ratio;
  real_T ratio_tmp;
  int32_T b_k;
  int32_T totalIneq;
  totalIneq = workingset_sizes[2] - 1;
  *alpha = 1.0E+30;
  *newBlocking = false;
  *constrType = 0;
  *constrIdx = 0;
  rtDW->p_max = 0.0;
  rtDW->denomTol = 2.2204460492503131E-13 * xnrm2_j(workingset_nVar,
    solution_searchDir);
  if (workingset_nWConstr[2] < workingset_sizes[2]) {
    for (b_k = 0; b_k <= totalIneq; b_k++) {
      workspace[b_k] = workingset_bineq[b_k];
    }

    xgemv_pyma2zxi(workingset_nVar, workingset_sizes[2], workingset_Aineq,
                   workingset_ldA, solution_xstar, workspace);
    xgemv_pyma2zxid(workingset_nVar, workingset_sizes[2], workingset_Aineq,
                    workingset_ldA, solution_searchDir, workspace);
    for (b_k = 0; b_k <= totalIneq; b_k++) {
      rtDW->phaseOneCorrectionX = workspace[b_k + 10];
      if ((rtDW->phaseOneCorrectionX > rtDW->denomTol) &&
          (!workingset_isActiveConstr[(workingset_isActiveIdx[2] + b_k) - 1])) {
        ratio_tmp = tolcon - workspace[b_k];
        ratio = fmin(fabs(workspace[b_k] - *toldelta), ratio_tmp + *toldelta) /
          rtDW->phaseOneCorrectionX;
        if ((ratio <= *alpha) && (fabs(rtDW->phaseOneCorrectionX) > rtDW->p_max))
        {
          *alpha = ratio;
          *constrType = 3;
          *constrIdx = b_k + 1;
          *newBlocking = true;
        }

        ratio = fmin(fabs(workspace[b_k]), ratio_tmp) /
          rtDW->phaseOneCorrectionX;
        if (ratio < *alpha) {
          *alpha = ratio;
          *constrType = 3;
          *constrIdx = b_k + 1;
          *newBlocking = true;
          rtDW->p_max = fabs(workspace[b_k + 10]);
        }
      }
    }
  }

  if (workingset_nWConstr[3] < workingset_sizes[3]) {
    rtDW->phaseOneCorrectionX = solution_xstar[workingset_nVar - 1] * (real_T)
      isPhaseOne;
    rtDW->phaseOneCorrectionP = solution_searchDir[workingset_nVar - 1] *
      (real_T)isPhaseOne;
    for (totalIneq = 0; totalIneq <= workingset_sizes[3] - 2; totalIneq++) {
      rtDW->pk_corrected = -solution_searchDir[workingset_indexLB[totalIneq] - 1]
        - rtDW->phaseOneCorrectionP;
      if ((rtDW->pk_corrected > rtDW->denomTol) && (!workingset_isActiveConstr
           [(workingset_isActiveIdx[3] + totalIneq) - 1])) {
        ratio_tmp = -solution_xstar[workingset_indexLB[totalIneq] - 1] -
          workingset_lb[workingset_indexLB[totalIneq] - 1];
        ratio = (ratio_tmp - *toldelta) - rtDW->phaseOneCorrectionX;
        ratio = fmin(fabs(ratio), tolcon - ratio) / rtDW->pk_corrected;
        if ((ratio <= *alpha) && (fabs(rtDW->pk_corrected) > rtDW->p_max)) {
          *alpha = ratio;
          *constrType = 4;
          *constrIdx = totalIneq + 1;
          *newBlocking = true;
        }

        ratio = ratio_tmp - rtDW->phaseOneCorrectionX;
        ratio = fmin(fabs(ratio), tolcon - ratio) / rtDW->pk_corrected;
        if (ratio < *alpha) {
          *alpha = ratio;
          *constrType = 4;
          *constrIdx = totalIneq + 1;
          *newBlocking = true;
          rtDW->p_max = fabs(rtDW->pk_corrected);
        }
      }
    }

    totalIneq = workingset_indexLB[workingset_sizes[3] - 1] - 1;
    rtDW->phaseOneCorrectionX = solution_searchDir[totalIneq];
    if ((-rtDW->phaseOneCorrectionX > rtDW->denomTol) &&
        (!workingset_isActiveConstr[(workingset_isActiveIdx[3] +
          workingset_sizes[3]) - 2])) {
      ratio_tmp = -solution_xstar[totalIneq] - workingset_lb[totalIneq];
      ratio = ratio_tmp - *toldelta;
      ratio = fmin(fabs(ratio), tolcon - ratio) / -rtDW->phaseOneCorrectionX;
      if ((ratio <= *alpha) && (fabs(rtDW->phaseOneCorrectionX) > rtDW->p_max))
      {
        *alpha = ratio;
        *constrType = 4;
        *constrIdx = workingset_sizes[3];
        *newBlocking = true;
      }

      ratio = fmin(fabs(ratio_tmp), tolcon - ratio_tmp) /
        -rtDW->phaseOneCorrectionX;
      if (ratio < *alpha) {
        *alpha = ratio;
        *constrType = 4;
        *constrIdx = workingset_sizes[3];
        *newBlocking = true;
        rtDW->p_max = fabs(solution_searchDir[totalIneq]);
      }
    }
  }

  if (workingset_nWConstr[4] < workingset_sizes[4]) {
    rtDW->phaseOneCorrectionX = solution_xstar[workingset_nVar - 1] * (real_T)
      isPhaseOne;
    rtDW->phaseOneCorrectionP = solution_searchDir[workingset_nVar - 1] *
      (real_T)isPhaseOne;
    for (totalIneq = 0; totalIneq < workingset_sizes[4]; totalIneq++) {
      rtDW->pk_corrected = solution_searchDir[workingset_indexUB[totalIneq] - 1]
        - rtDW->phaseOneCorrectionP;
      if ((rtDW->pk_corrected > rtDW->denomTol) && (!workingset_isActiveConstr
           [(workingset_isActiveIdx[4] + totalIneq) - 1])) {
        ratio_tmp = solution_xstar[workingset_indexUB[totalIneq] - 1] -
          workingset_ub[workingset_indexUB[totalIneq] - 1];
        ratio = (ratio_tmp - *toldelta) - rtDW->phaseOneCorrectionX;
        ratio = fmin(fabs(ratio), tolcon - ratio) / rtDW->pk_corrected;
        if ((ratio <= *alpha) && (fabs(rtDW->pk_corrected) > rtDW->p_max)) {
          *alpha = ratio;
          *constrType = 5;
          *constrIdx = totalIneq + 1;
          *newBlocking = true;
        }

        ratio = ratio_tmp - rtDW->phaseOneCorrectionX;
        ratio = fmin(fabs(ratio), tolcon - ratio) / rtDW->pk_corrected;
        if (ratio < *alpha) {
          *alpha = ratio;
          *constrType = 5;
          *constrIdx = totalIneq + 1;
          *newBlocking = true;
          rtDW->p_max = fabs(rtDW->pk_corrected);
        }
      }
    }
  }

  *toldelta += toltau;
  if (rtDW->p_max > 0.0) {
    *alpha = fmax(*alpha, toltau / rtDW->p_max);
  }

  if (isPhaseOne) {
    *newBlocking = (((!*newBlocking) || (*alpha <= 1.7976931348623157E+308)) &&
                    (*newBlocking));
    *alpha = fmin(*alpha, 1.7976931348623157E+308);
  } else {
    *newBlocking = (((!*newBlocking) || (*alpha <= 1.0)) && (*newBlocking));
    *alpha = fmin(*alpha, 1.0);
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void feasibleratiotest(const real_T solution_xstar[8], const real_T
  solution_searchDir[8], real_T workspace[80], int32_T workingset_nVar, int32_T
  workingset_ldA, const real_T workingset_Aineq[56], const real_T
  workingset_bineq[7], const real_T workingset_lb[8], const real_T
  workingset_ub[8], const int32_T workingset_indexLB[8], const int32_T
  workingset_indexUB[8], const int32_T workingset_sizes[5], const int32_T
  workingset_isActiveIdx[6], const boolean_T workingset_isActiveConstr[10],
  const int32_T workingset_nWConstr[5], boolean_T isPhaseOne, real_T tolcon,
  real_T *alpha, boolean_T *newBlocking, int32_T *constrType, int32_T *constrIdx,
  DW *rtDW)
{
  real_T pk_corrected;
  real_T ratio;
  int32_T b_k;
  int32_T totalIneq;
  totalIneq = workingset_sizes[2] - 1;
  *alpha = 1.0E+30;
  *newBlocking = false;
  *constrType = 0;
  *constrIdx = 0;
  rtDW->denomTol_n = 2.2204460492503131E-13 * xnrm2_j(workingset_nVar,
    solution_searchDir);
  if (workingset_nWConstr[2] < workingset_sizes[2]) {
    for (b_k = 0; b_k <= totalIneq; b_k++) {
      workspace[b_k] = workingset_bineq[b_k];
    }

    xgemv_pyma2zxi(workingset_nVar, workingset_sizes[2], workingset_Aineq,
                   workingset_ldA, solution_xstar, workspace);
    xgemv_pyma2zxid(workingset_nVar, workingset_sizes[2], workingset_Aineq,
                    workingset_ldA, solution_searchDir, workspace);
    for (b_k = 0; b_k <= totalIneq; b_k++) {
      rtDW->phaseOneCorrectionX_p = workspace[b_k + 10];
      if ((rtDW->phaseOneCorrectionX_p > rtDW->denomTol_n) &&
          (!workingset_isActiveConstr[(workingset_isActiveIdx[2] + b_k) - 1])) {
        ratio = fmin(fabs(workspace[b_k]), tolcon - workspace[b_k]) /
          rtDW->phaseOneCorrectionX_p;
        if (ratio < *alpha) {
          *alpha = ratio;
          *constrType = 3;
          *constrIdx = b_k + 1;
          *newBlocking = true;
        }
      }
    }
  }

  if (workingset_nWConstr[3] < workingset_sizes[3]) {
    rtDW->phaseOneCorrectionX_p = solution_xstar[workingset_nVar - 1] * (real_T)
      isPhaseOne;
    rtDW->phaseOneCorrectionP_l = solution_searchDir[workingset_nVar - 1] *
      (real_T)isPhaseOne;
    for (totalIneq = 0; totalIneq <= workingset_sizes[3] - 2; totalIneq++) {
      pk_corrected = -solution_searchDir[workingset_indexLB[totalIneq] - 1] -
        rtDW->phaseOneCorrectionP_l;
      if ((pk_corrected > rtDW->denomTol_n) && (!workingset_isActiveConstr
           [(workingset_isActiveIdx[3] + totalIneq) - 1])) {
        ratio = (-solution_xstar[workingset_indexLB[totalIneq] - 1] -
                 workingset_lb[workingset_indexLB[totalIneq] - 1]) -
          rtDW->phaseOneCorrectionX_p;
        ratio = fmin(fabs(ratio), tolcon - ratio) / pk_corrected;
        if (ratio < *alpha) {
          *alpha = ratio;
          *constrType = 4;
          *constrIdx = totalIneq + 1;
          *newBlocking = true;
        }
      }
    }

    totalIneq = workingset_indexLB[workingset_sizes[3] - 1] - 1;
    rtDW->phaseOneCorrectionX_p = -solution_searchDir[totalIneq];
    if ((rtDW->phaseOneCorrectionX_p > rtDW->denomTol_n) &&
        (!workingset_isActiveConstr[(workingset_isActiveIdx[3] +
          workingset_sizes[3]) - 2])) {
      ratio = -solution_xstar[totalIneq] - workingset_lb[totalIneq];
      ratio = fmin(fabs(ratio), tolcon - ratio) / rtDW->phaseOneCorrectionX_p;
      if (ratio < *alpha) {
        *alpha = ratio;
        *constrType = 4;
        *constrIdx = workingset_sizes[3];
        *newBlocking = true;
      }
    }
  }

  if (workingset_nWConstr[4] < workingset_sizes[4]) {
    rtDW->phaseOneCorrectionX_p = solution_xstar[workingset_nVar - 1] * (real_T)
      isPhaseOne;
    rtDW->phaseOneCorrectionP_l = solution_searchDir[workingset_nVar - 1] *
      (real_T)isPhaseOne;
    for (totalIneq = 0; totalIneq < workingset_sizes[4]; totalIneq++) {
      pk_corrected = solution_searchDir[workingset_indexUB[totalIneq] - 1] -
        rtDW->phaseOneCorrectionP_l;
      if ((pk_corrected > rtDW->denomTol_n) && (!workingset_isActiveConstr
           [(workingset_isActiveIdx[4] + totalIneq) - 1])) {
        ratio = (solution_xstar[workingset_indexUB[totalIneq] - 1] -
                 workingset_ub[workingset_indexUB[totalIneq] - 1]) -
          rtDW->phaseOneCorrectionX_p;
        ratio = fmin(fabs(ratio), tolcon - ratio) / pk_corrected;
        if (ratio < *alpha) {
          *alpha = ratio;
          *constrType = 5;
          *constrIdx = totalIneq + 1;
          *newBlocking = true;
        }
      }
    }
  }

  if (!isPhaseOne) {
    *newBlocking = (((!*newBlocking) || (*alpha <= 1.0)) && (*newBlocking));
    *alpha = fmin(*alpha, 1.0);
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void checkUnboundedOrIllPosed(sVm5xLhdFDU5OIlGg0pTc4E *solution, const
  shohwUBaOGHF036TMzc1KEH *objective)
{
  if (objective->objtype == 5) {
    if (xnrm2_j(objective->nvar, solution->searchDir) > 100.0 * (real_T)
        objective->nvar * 1.4901161193847656E-8) {
      solution->state = 3;
    } else {
      solution->state = 4;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void addBoundToActiveSetMatrix_(stxriBK2jD81NCGacZ0b8HD *obj, int32_T
  TYPE, int32_T idx_local)
{
  int32_T colOffset;
  int32_T idx;
  int32_T idx_bnd_local;
  obj->nWConstr[TYPE - 1]++;
  obj->isActiveConstr[(obj->isActiveIdx[TYPE - 1] + idx_local) - 2] = true;
  obj->nActiveConstr++;
  obj->Wid[obj->nActiveConstr - 1] = TYPE;
  obj->Wlocalidx[obj->nActiveConstr - 1] = idx_local;
  colOffset = (obj->nActiveConstr - 1) * obj->ldA - 1;
  if (TYPE == 5) {
    idx_bnd_local = obj->indexUB[idx_local - 1];
    obj->bwset[obj->nActiveConstr - 1] = obj->ub[idx_bnd_local - 1];
  } else {
    idx_bnd_local = obj->indexLB[idx_local - 1];
    obj->bwset[obj->nActiveConstr - 1] = obj->lb[idx_bnd_local - 1];
  }

  for (idx = 0; idx <= idx_bnd_local - 2; idx++) {
    obj->ATwset[(idx + colOffset) + 1] = 0.0;
  }

  obj->ATwset[idx_bnd_local + colOffset] = (real_T)(TYPE == 5) * 2.0 - 1.0;
  for (idx_bnd_local++; idx_bnd_local <= obj->nVar; idx_bnd_local++) {
    obj->ATwset[idx_bnd_local + colOffset] = 0.0;
  }

  switch (obj->probType) {
   case 3:
   case 2:
    break;

   default:
    obj->ATwset[obj->nVar + colOffset] = -1.0;
    break;
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void compute_lambda(real_T workspace[80], sVm5xLhdFDU5OIlGg0pTc4E
  *solution, const shohwUBaOGHF036TMzc1KEH *objective, const
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager)
{
  real_T tol;
  int32_T b;
  int32_T c_idx;
  int32_T ia;
  int32_T iac;
  int32_T idxQR;
  int32_T ix;
  int32_T jjA;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T nonDegenerate;
  if (qrmanager->ncols > 0) {
    guard1 = false;
    if (objective->objtype != 4) {
      tol = 100.0 * (real_T)qrmanager->mrows * 2.2204460492503131E-16;
      nonDegenerate = ((qrmanager->mrows > 0) && (qrmanager->ncols > 0));
      if (nonDegenerate) {
        c_idx = qrmanager->ncols;
        guard2 = false;
        if (qrmanager->mrows < qrmanager->ncols) {
          idxQR = (qrmanager->ncols - 1) * qrmanager->ldq + qrmanager->mrows;
          while ((c_idx > qrmanager->mrows) && (fabs(qrmanager->QR[idxQR - 1]) >=
                  tol)) {
            c_idx--;
            idxQR -= qrmanager->ldq;
          }

          nonDegenerate = (c_idx == qrmanager->mrows);
          if (!nonDegenerate) {
          } else {
            guard2 = true;
          }
        } else {
          guard2 = true;
        }

        if (guard2) {
          idxQR = (c_idx - 1) * qrmanager->ldq + c_idx;
          while ((c_idx >= 1) && (fabs(qrmanager->QR[idxQR - 1]) >= tol)) {
            c_idx--;
            idxQR = (idxQR - qrmanager->ldq) - 1;
          }

          nonDegenerate = (c_idx == 0);
        }
      }

      if (!nonDegenerate) {
        solution->state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      c_idx = qrmanager->ldq;
      if ((qrmanager->mrows != 0) && (qrmanager->ncols != 0)) {
        for (idxQR = 0; idxQR < qrmanager->ncols; idxQR++) {
          workspace[idxQR] = 0.0;
        }

        idxQR = 0;
        jjA = (qrmanager->ncols - 1) * qrmanager->ldq + 1;
        iac = 1;
        while (((c_idx > 0) && (iac <= jjA)) || ((c_idx < 0) && (iac >= jjA))) {
          ix = 0;
          tol = 0.0;
          b = (iac + qrmanager->mrows) - 1;
          for (ia = iac; ia <= b; ia++) {
            tol += qrmanager->Q[ia - 1] * objective->grad[ix];
            ix++;
          }

          workspace[idxQR] += tol;
          idxQR++;
          iac += c_idx;
        }
      }

      if (qrmanager->ncols != 0) {
        for (idxQR = qrmanager->ncols - 1; idxQR + 1 > 0; idxQR--) {
          jjA = idxQR * c_idx + idxQR;
          workspace[idxQR] /= qrmanager->QR[jjA];
          for (iac = 1; iac - 1 < idxQR; iac++) {
            ix = idxQR - iac;
            workspace[ix] -= qrmanager->QR[jjA - iac] * workspace[idxQR];
          }
        }
      }

      for (c_idx = 0; c_idx < qrmanager->ncols; c_idx++) {
        solution->lambda[c_idx] = -workspace[c_idx];
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void checkStoppingAndUpdateFval(int32_T *activeSetChangeID, const real_T
  f[7], sVm5xLhdFDU5OIlGg0pTc4E *solution, snRDwUdgrIx9qNga56nZ8DE *memspace,
  const shohwUBaOGHF036TMzc1KEH *objective, stxriBK2jD81NCGacZ0b8HD *workingset,
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, real_T options_ObjectiveLimit, real_T
  options_ConstraintTolerance, int32_T runTimeOptions_MaxIterations, real_T
  runTimeOptions_ConstrRelTolFact, boolean_T updateFval, DW *rtDW)
{
  solution->iterations++;
  rtDW->nVar_tmp_tmp = objective->nvar - 1;
  if ((solution->iterations >= runTimeOptions_MaxIterations) &&
      ((solution->state != 1) || (objective->objtype == 5))) {
    solution->state = 0;
  }

  if (solution->iterations - solution->iterations / 50 * 50 == 0) {
    rtDW->b_p = maxConstraintViolation_pn(workingset, solution->xstar, rtDW);
    solution->maxConstr = rtDW->b_p;
    rtDW->tempMaxConstr = rtDW->b_p;
    if (objective->objtype == 5) {
      rtDW->tempMaxConstr = rtDW->b_p - solution->xstar[objective->nvar - 1];
    }

    if (rtDW->tempMaxConstr > options_ConstraintTolerance *
        runTimeOptions_ConstrRelTolFact) {
      rtDW->b_k = 0;
      while (rtDW->b_k <= rtDW->nVar_tmp_tmp) {
        solution->searchDir[rtDW->b_k] = solution->xstar[rtDW->b_k];
        rtDW->b_k++;
      }

      feasibleX0ForWorkingSet(memspace->workspace_double, solution->searchDir,
        workingset, qrmanager, rtDW);
      *activeSetChangeID = 0;
      rtDW->tempMaxConstr = maxConstraintViolation_pn(workingset,
        solution->searchDir, rtDW);
      if (rtDW->tempMaxConstr < rtDW->b_p) {
        rtDW->b_k = 0;
        while (rtDW->b_k <= rtDW->nVar_tmp_tmp) {
          solution->xstar[rtDW->b_k] = solution->searchDir[rtDW->b_k];
          rtDW->b_k++;
        }

        solution->maxConstr = rtDW->tempMaxConstr;
      }
    }
  }

  if (updateFval) {
    rtDW->b_p = computeFval_ReuseHx(objective, memspace->workspace_double, f,
      solution->xstar);
    solution->fstar = rtDW->b_p;
    if ((rtDW->b_p < options_ObjectiveLimit) && ((solution->state != 0) ||
         (objective->objtype != 5))) {
      solution->state = 2;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void computeFirstOrderOpt(sVm5xLhdFDU5OIlGg0pTc4E *solution, const
  shohwUBaOGHF036TMzc1KEH *objective, int32_T workingset_nVar, int32_T
  workingset_ldA, const real_T workingset_ATwset[80], int32_T
  workingset_nActiveConstr, real_T workspace[80])
{
  real_T smax;
  real_T y;
  int32_T b;
  int32_T b_ix;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  for (ix = 0; ix < workingset_nVar; ix++) {
    workspace[ix] = objective->grad[ix];
  }

  if ((workingset_nVar != 0) && (workingset_nActiveConstr != 0)) {
    ix = 0;
    b_ix = (workingset_nActiveConstr - 1) * workingset_ldA + 1;
    iac = 1;
    while (((workingset_ldA > 0) && (iac <= b_ix)) || ((workingset_ldA < 0) &&
            (iac >= b_ix))) {
      iy = 0;
      b = iac + workingset_nVar;
      for (ia = iac; ia < b; ia++) {
        workspace[iy] += workingset_ATwset[ia - 1] * solution->lambda[ix];
        iy++;
      }

      ix++;
      iac += workingset_ldA;
    }
  }

  if (workingset_nVar < 1) {
    ix = 0;
  } else {
    ix = 1;
    if (workingset_nVar > 1) {
      b_ix = 0;
      smax = fabs(workspace[0]);
      for (iac = 2; iac <= workingset_nVar; iac++) {
        b_ix++;
        y = fabs(workspace[b_ix]);
        if (y > smax) {
          ix = iac;
          smax = y;
        }
      }
    }
  }

  solution->firstorderopt = fabs(workspace[ix - 1]);
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void printInfo(boolean_T newBlocking, int32_T PROBLEM_TYPE, real_T alpha,
                      real_T stepNorm, int32_T activeConstrChangedType, int32_T
                      localActiveConstrIdx, int32_T activeSetChangeID, real_T
                      solution_fstar, real_T solution_firstorderopt, real_T
                      solution_maxConstr, int32_T solution_iterations, const
                      int32_T workingset_indexLB[8], const int32_T
                      workingset_indexUB[8], int32_T workingset_nActiveConstr)
{
  int32_T b_localActiveConstrIdx;
  printf("%5i  %14.6e  %14.6e  %14.6e", solution_iterations, solution_fstar,
         solution_firstorderopt, solution_maxConstr);
  fflush(stdout);
  printf("  ");
  fflush(stdout);
  printf("%14.6e", alpha);
  fflush(stdout);
  printf("  ");
  fflush(stdout);
  printf("%14.6e", stepNorm);
  fflush(stdout);
  printf("    ");
  fflush(stdout);
  if (newBlocking || (activeSetChangeID == -1)) {
    if (newBlocking) {
      activeSetChangeID = 1;
    }

    b_localActiveConstrIdx = localActiveConstrIdx;
    switch (activeSetChangeID) {
     case -1:
      printf("-");
      fflush(stdout);
      break;

     case 1:
      printf("+");
      fflush(stdout);
      break;

     default:
      printf(" ");
      fflush(stdout);
      break;
    }

    switch (activeConstrChangedType) {
     case 3:
      printf("AINEQ");
      fflush(stdout);
      break;

     case 4:
      printf("LOWER");
      fflush(stdout);
      b_localActiveConstrIdx = workingset_indexLB[localActiveConstrIdx - 1];
      break;

     case 5:
      printf("UPPER");
      fflush(stdout);
      b_localActiveConstrIdx = workingset_indexUB[localActiveConstrIdx - 1];
      break;

     default:
      printf("SAME ");
      fflush(stdout);
      b_localActiveConstrIdx = -1;
      break;
    }

    printf("(%-5i)", b_localActiveConstrIdx);
    fflush(stdout);
  } else {
    printf(" SAME ");
    fflush(stdout);
    printf("(%-5i)", -1);
    fflush(stdout);
  }

  printf("           ");
  fflush(stdout);
  printf("%5i", workingset_nActiveConstr);
  fflush(stdout);
  printf("    ");
  fflush(stdout);
  switch (PROBLEM_TYPE) {
   case 1:
    printf("Phase One");
    fflush(stdout);
    break;

   case 2:
    printf("Regularized");
    fflush(stdout);
    break;

   case 4:
    printf("Phase One Reg");
    fflush(stdout);
    break;

   default:
    printf("Normal");
    fflush(stdout);
    break;
  }

  printf("\n");
  fflush(stdout);
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void iterate(const real_T H[49], const real_T f[7],
                    sVm5xLhdFDU5OIlGg0pTc4E *solution, snRDwUdgrIx9qNga56nZ8DE
                    *memspace, stxriBK2jD81NCGacZ0b8HD *workingset,
                    sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, sSzLoP8tvZHiR1V2perTtWD *
                    cholmanager, shohwUBaOGHF036TMzc1KEH *objective, boolean_T
                    options_IterDisplayQP, real_T options_PricingTolerance,
                    real_T options_ObjectiveLimit, real_T
                    options_ConstraintTolerance, real_T options_StepTolerance,
                    const sL9bDKomAYkxZSVrG9w6En runTimeOptions, DW *rtDW)
{
  int32_T exitg1;
  boolean_T guard1 = false;
  boolean_T newBlocking;
  boolean_T subProblemChanged;
  boolean_T updateFval;
  subProblemChanged = true;
  updateFval = true;
  rtDW->activeSetChangeID = 0;
  rtDW->TYPE = objective->objtype;
  rtDW->tolDelta = 6.7434957617430445E-7;
  rtDW->nVar = workingset->nVar;
  rtDW->activeConstrChangedType = 1;
  rtDW->localActiveConstrIdx = 0;
  rtDW->globalActiveConstrIdx = 0;
  computeGrad_StoreHx(objective, H, f, solution->xstar);
  solution->fstar = computeFval_ReuseHx(objective, memspace->workspace_double, f,
    solution->xstar);
  if (solution->iterations < runTimeOptions.MaxIterations) {
    solution->state = -5;
  } else {
    solution->state = 0;
  }

  rtDW->workingIdx = 0;
  while (rtDW->workingIdx <= workingset->mConstrMax - 1) {
    solution->lambda[rtDW->workingIdx] = 0.0;
    rtDW->workingIdx++;
  }

  if ((solution->iterations == 0) && options_IterDisplayQP) {
    printHeader();
    printInitialInfo(workingset->probType, solution->fstar, solution->iterations,
                     workingset->nActiveConstr);
  }

  do {
    exitg1 = 0;
    if (solution->state == -5) {
      newBlocking = false;
      guard1 = false;
      if (subProblemChanged) {
        switch (rtDW->activeSetChangeID) {
         case 1:
          rtDW->workingIdx = (workingset->nActiveConstr - 1) * workingset->ldA;
          if (qrmanager->mrows < qrmanager->ncols + 1) {
            qrmanager->minRowCol = qrmanager->mrows;
          } else {
            qrmanager->minRowCol = qrmanager->ncols + 1;
          }

          rtDW->iQR0 = qrmanager->ldq * qrmanager->ncols;
          rtDW->Qk0 = qrmanager->ldq;
          if (qrmanager->mrows != 0) {
            rtDW->iyend = rtDW->iQR0 + qrmanager->mrows;
            rtDW->c_iy = rtDW->iQR0;
            while (rtDW->c_iy + 1 <= rtDW->iyend) {
              qrmanager->QR[rtDW->c_iy] = 0.0;
              rtDW->c_iy++;
            }

            rtDW->iyend = (qrmanager->mrows - 1) * qrmanager->ldq + 1;
            rtDW->c_iy = 1;
            while (((rtDW->Qk0 > 0) && (rtDW->c_iy <= rtDW->iyend)) ||
                   ((rtDW->Qk0 < 0) && (rtDW->c_iy >= rtDW->iyend))) {
              rtDW->b_ix = rtDW->workingIdx;
              rtDW->normDelta = 0.0;
              rtDW->o = (rtDW->c_iy + qrmanager->mrows) - 1;
              rtDW->ia = rtDW->c_iy;
              while (rtDW->ia <= rtDW->o) {
                rtDW->normDelta += qrmanager->Q[rtDW->ia - 1] *
                  workingset->ATwset[rtDW->b_ix];
                rtDW->b_ix++;
                rtDW->ia++;
              }

              qrmanager->QR[rtDW->iQR0] += rtDW->normDelta;
              rtDW->iQR0++;
              rtDW->c_iy += rtDW->Qk0;
            }
          }

          qrmanager->ncols++;
          qrmanager->jpvt[qrmanager->ncols - 1] = qrmanager->ncols;
          rtDW->workingIdx = qrmanager->mrows - 2;
          while (rtDW->workingIdx + 2 > qrmanager->ncols) {
            rtDW->iQR0 = (qrmanager->ncols - 1) * qrmanager->ldq;
            rtDW->Qk0 = rtDW->workingIdx + rtDW->iQR0;
            rtDW->temp = qrmanager->QR[rtDW->Qk0];
            rtDW->n = qrmanager->QR[rtDW->Qk0 + 1];
            xrotg(&rtDW->temp, &rtDW->n, &rtDW->normDelta, &rtDW->alpha, rtDW);
            qrmanager->QR[rtDW->Qk0] = rtDW->temp;
            qrmanager->QR[(rtDW->workingIdx + rtDW->iQR0) + 1] = rtDW->n;
            rtDW->Qk0 = qrmanager->ldq * rtDW->workingIdx;
            if (qrmanager->mrows >= 1) {
              rtDW->iQR0 = rtDW->Qk0;
              rtDW->Qk0 += qrmanager->ldq;
              rtDW->iyend = 0;
              while (rtDW->iyend <= qrmanager->mrows - 1) {
                rtDW->temp = rtDW->normDelta * qrmanager->Q[rtDW->iQR0] +
                  rtDW->alpha * qrmanager->Q[rtDW->Qk0];
                qrmanager->Q[rtDW->Qk0] = rtDW->normDelta * qrmanager->Q
                  [rtDW->Qk0] - rtDW->alpha * qrmanager->Q[rtDW->iQR0];
                qrmanager->Q[rtDW->iQR0] = rtDW->temp;
                rtDW->Qk0++;
                rtDW->iQR0++;
                rtDW->iyend++;
              }
            }

            rtDW->workingIdx--;
          }
          break;

         case -1:
          deleteColMoveEnd(qrmanager, rtDW->globalActiveConstrIdx, rtDW);
          break;

         default:
          factorQR_f(qrmanager, workingset->ATwset, rtDW->nVar,
                     workingset->nActiveConstr, workingset->ldA, rtDW);
          computeQ_(qrmanager, qrmanager->mrows, rtDW);
          break;
        }

        compute_deltax(H, solution, memspace, qrmanager, cholmanager, objective,
                       rtDW);
        if (solution->state != -5) {
          exitg1 = 1;
        } else {
          rtDW->normDelta = xnrm2_j(rtDW->nVar, solution->searchDir);
          guard1 = true;
        }
      } else {
        rtDW->workingIdx = 0;
        while (rtDW->workingIdx <= rtDW->nVar - 1) {
          solution->searchDir[rtDW->workingIdx] = 0.0;
          rtDW->workingIdx++;
        }

        rtDW->normDelta = 0.0;
        guard1 = true;
      }

      if (guard1) {
        if ((!subProblemChanged) || (rtDW->normDelta < options_StepTolerance) ||
            (workingset->nActiveConstr >= rtDW->nVar)) {
          compute_lambda(memspace->workspace_double, solution, objective,
                         qrmanager);
          if ((solution->state != -7) || (workingset->nActiveConstr > rtDW->nVar))
          {
            rtDW->workingIdx = -1;
            rtDW->alpha = options_PricingTolerance *
              runTimeOptions.ProbRelTolFactor * (real_T)(rtDW->TYPE != 5);
            rtDW->iQR0 = workingset->nWConstr[0] + workingset->nWConstr[1];
            while (rtDW->iQR0 + 1 <= workingset->nActiveConstr) {
              if (solution->lambda[rtDW->iQR0] < rtDW->alpha) {
                rtDW->alpha = solution->lambda[rtDW->iQR0];
                rtDW->workingIdx = rtDW->iQR0;
              }

              rtDW->iQR0++;
            }

            if (rtDW->workingIdx + 1 == 0) {
              solution->state = 1;
            } else {
              rtDW->activeSetChangeID = -1;
              rtDW->globalActiveConstrIdx = rtDW->workingIdx + 1;
              subProblemChanged = true;
              rtDW->activeConstrChangedType = workingset->Wid[rtDW->workingIdx];
              rtDW->localActiveConstrIdx = workingset->Wlocalidx
                [rtDW->workingIdx];
              rtDW->iQR0 = workingset->Wid[rtDW->workingIdx] - 1;
              workingset->isActiveConstr[(workingset->isActiveIdx
                [workingset->Wid[rtDW->workingIdx] - 1] + workingset->
                Wlocalidx[rtDW->workingIdx]) - 2] = false;
              moveConstraint_(workingset, workingset->nActiveConstr,
                              rtDW->workingIdx + 1);
              workingset->nActiveConstr--;
              workingset->nWConstr[rtDW->iQR0]--;
              solution->lambda[rtDW->workingIdx] = 0.0;
            }
          } else {
            rtDW->workingIdx = workingset->nActiveConstr;
            rtDW->activeSetChangeID = 0;
            rtDW->globalActiveConstrIdx = workingset->nActiveConstr;
            subProblemChanged = true;
            rtDW->activeConstrChangedType = workingset->Wid
              [workingset->nActiveConstr - 1];
            rtDW->localActiveConstrIdx = workingset->Wlocalidx
              [workingset->nActiveConstr - 1];
            workingset->isActiveConstr[(workingset->isActiveIdx
              [rtDW->activeConstrChangedType - 1] + rtDW->localActiveConstrIdx)
              - 2] = false;
            moveConstraint_(workingset, workingset->nActiveConstr,
                            rtDW->workingIdx);
            workingset->nActiveConstr--;
            workingset->nWConstr[rtDW->activeConstrChangedType - 1]--;
            solution->lambda[rtDW->workingIdx - 1] = 0.0;
          }

          updateFval = false;
          rtDW->alpha = 0.0;
        } else {
          updateFval = (rtDW->TYPE == 5);
          if (updateFval || runTimeOptions.RemainFeasible) {
            feasibleratiotest(solution->xstar, solution->searchDir,
                              memspace->workspace_double, workingset->nVar,
                              workingset->ldA, workingset->Aineq,
                              workingset->bineq, workingset->lb, workingset->ub,
                              workingset->indexLB, workingset->indexUB,
                              workingset->sizes, workingset->isActiveIdx,
                              workingset->isActiveConstr, workingset->nWConstr,
                              updateFval, options_ConstraintTolerance,
                              &rtDW->alpha, &newBlocking,
                              &rtDW->activeConstrChangedType,
                              &rtDW->localActiveConstrIdx, rtDW);
          } else {
            ratiotest(solution->xstar, solution->searchDir,
                      memspace->workspace_double, workingset->nVar,
                      workingset->ldA, workingset->Aineq, workingset->bineq,
                      workingset->lb, workingset->ub, workingset->indexLB,
                      workingset->indexUB, workingset->sizes,
                      workingset->isActiveIdx, workingset->isActiveConstr,
                      workingset->nWConstr, false, options_ConstraintTolerance,
                      &rtDW->tolDelta, 6.608625846508183E-7, &rtDW->alpha,
                      &newBlocking, &rtDW->activeConstrChangedType,
                      &rtDW->localActiveConstrIdx, rtDW);
          }

          if (newBlocking) {
            switch (rtDW->activeConstrChangedType) {
             case 3:
              workingset->nWConstr[2]++;
              workingset->isActiveConstr[(workingset->isActiveIdx[2] +
                rtDW->localActiveConstrIdx) - 2] = true;
              workingset->nActiveConstr++;
              workingset->Wid[workingset->nActiveConstr - 1] = 3;
              workingset->Wlocalidx[workingset->nActiveConstr - 1] =
                rtDW->localActiveConstrIdx;
              rtDW->activeSetChangeID = (rtDW->localActiveConstrIdx - 1) *
                workingset->ldA;
              rtDW->workingIdx = (workingset->nActiveConstr - 1) *
                workingset->ldA;
              rtDW->iQR0 = 0;
              while (rtDW->iQR0 <= workingset->nVar - 1) {
                workingset->ATwset[rtDW->workingIdx + rtDW->iQR0] =
                  workingset->Aineq[rtDW->activeSetChangeID + rtDW->iQR0];
                rtDW->iQR0++;
              }

              workingset->bwset[workingset->nActiveConstr - 1] =
                workingset->bineq[rtDW->localActiveConstrIdx - 1];
              break;

             case 4:
              addBoundToActiveSetMatrix_(workingset, 4,
                rtDW->localActiveConstrIdx);
              break;

             default:
              addBoundToActiveSetMatrix_(workingset, 5,
                rtDW->localActiveConstrIdx);
              break;
            }

            rtDW->activeSetChangeID = 1;
          } else {
            checkUnboundedOrIllPosed(solution, objective);
            subProblemChanged = false;
            if (workingset->nActiveConstr == 0) {
              solution->state = 1;
            }
          }

          if ((rtDW->nVar >= 1) && (rtDW->alpha != 0.0)) {
            rtDW->workingIdx = 0;
            while (rtDW->workingIdx <= rtDW->nVar - 1) {
              solution->xstar[rtDW->workingIdx] += rtDW->alpha *
                solution->searchDir[rtDW->workingIdx];
              rtDW->workingIdx++;
            }
          }

          computeGrad_StoreHx(objective, H, f, solution->xstar);
          updateFval = true;
        }

        checkStoppingAndUpdateFval(&rtDW->activeSetChangeID, f, solution,
          memspace, objective, workingset, qrmanager, options_ObjectiveLimit,
          options_ConstraintTolerance, runTimeOptions.MaxIterations,
          runTimeOptions.ConstrRelTolFactor, updateFval, rtDW);
        if (options_IterDisplayQP) {
          if (solution->iterations - solution->iterations / 50 * 50 == 0) {
            printHeader();
          } else {
            solution->maxConstr = maxConstraintViolation_pn(workingset,
              solution->xstar, rtDW);
          }

          computeFirstOrderOpt(solution, objective, workingset->nVar,
                               workingset->ldA, workingset->ATwset,
                               workingset->nActiveConstr,
                               memspace->workspace_double);
          printInfo(newBlocking, workingset->probType, rtDW->alpha,
                    rtDW->normDelta, rtDW->activeConstrChangedType,
                    rtDW->localActiveConstrIdx, rtDW->activeSetChangeID,
                    solution->fstar, solution->firstorderopt,
                    solution->maxConstr, solution->iterations,
                    workingset->indexLB, workingset->indexUB,
                    workingset->nActiveConstr);
        }
      }
    } else {
      if (!updateFval) {
        solution->fstar = computeFval_ReuseHx(objective,
          memspace->workspace_double, f, solution->xstar);
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void phaseone(const real_T H[49], const real_T f[7],
                     sVm5xLhdFDU5OIlGg0pTc4E *solution, snRDwUdgrIx9qNga56nZ8DE *
                     memspace, stxriBK2jD81NCGacZ0b8HD *workingset,
                     sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, sSzLoP8tvZHiR1V2perTtWD
                     *cholmanager, const sL9bDKomAYkxZSVrG9w6En *runTimeOptions,
                     shohwUBaOGHF036TMzc1KEH *objective, s4lHOiXA0GHbse0IgoBY6ZF
                     *options, DW *rtDW)
{
  static const char_T d_FiniteDifferenceType[7] = { 'f', 'o', 'r', 'w', 'a', 'r',
    'd' };

  static const char_T d_Algorithm[10] = { 'a', 'c', 't', 'i', 'v', 'e', '-', 's',
    'e', 't' };

  static const char_T d_SolverName[8] = { 'q', 'u', 'a', 'd', 'p', 'r', 'o', 'g'
  };

  static const char_T d_Display[5] = { 'f', 'i', 'n', 'a', 'l' };

  boolean_T exitg1;
  options->InitDamping = 0.01;
  for (rtDW->i_i = 0; rtDW->i_i < 7; rtDW->i_i++) {
    options->FiniteDifferenceType[rtDW->i_i] = d_FiniteDifferenceType[rtDW->i_i];
  }

  options->SpecifyObjectiveGradient = false;
  options->ScaleProblem = false;
  options->SpecifyConstraintGradient = false;
  options->NonFiniteSupport = true;
  options->IterDisplaySQP = false;
  options->FiniteDifferenceStepSize = -1.0;
  options->MaxFunctionEvaluations = -1.0;
  options->IterDisplayQP = false;
  options->PricingTolerance = 0.0;
  for (rtDW->i_i = 0; rtDW->i_i < 10; rtDW->i_i++) {
    options->Algorithm[rtDW->i_i] = d_Algorithm[rtDW->i_i];
  }

  options->ConstraintTolerance = 1.0E-8;
  options->OptimalityTolerance = 1.0E-6;
  options->MaxIterations = 7.0;
  options->FunctionTolerance = 1.7976931348623157E+308;
  for (rtDW->i_i = 0; rtDW->i_i < 8; rtDW->i_i++) {
    options->SolverName[rtDW->i_i] = d_SolverName[rtDW->i_i];
  }

  options->CheckGradients = false;
  options->Diagnostics[0] = 'o';
  options->Diagnostics[1] = 'f';
  options->Diagnostics[2] = 'f';
  options->DiffMaxChange = 1.7976931348623157E+308;
  options->DiffMinChange = 0.0;
  for (rtDW->i_i = 0; rtDW->i_i < 5; rtDW->i_i++) {
    options->Display[rtDW->i_i] = d_Display[rtDW->i_i];
  }

  options->FunValCheck[0] = 'o';
  options->FunValCheck[1] = 'f';
  options->FunValCheck[2] = 'f';
  options->UseParallel = false;
  options->LinearSolver[0] = 'a';
  options->LinearSolver[1] = 'u';
  options->LinearSolver[2] = 't';
  options->LinearSolver[3] = 'o';
  options->SubproblemAlgorithm[0] = 'c';
  options->SubproblemAlgorithm[1] = 'g';
  rtDW->PROBTYPE_ORIG_a = workingset->probType;
  rtDW->nVar_tmp_l = workingset->nVar;
  solution->xstar[workingset->nVar] = solution->maxConstr + 1.0;
  if (workingset->probType == 3) {
    rtDW->i_i = 1;
  } else {
    rtDW->i_i = 4;
  }

  setProblemType(workingset, rtDW->i_i);
  removeAllIneqConstr(workingset);
  memset(&objective->grad[0], 0, sizeof(real_T) << 3U);
  for (rtDW->i_i = 0; rtDW->i_i < 7; rtDW->i_i++) {
    objective->Hx[rtDW->i_i] = 0.0;
  }

  objective->maxVar = 8;
  objective->beta = 0.0;
  objective->rho = 0.0;
  objective->prev_objtype = 3;
  objective->prev_nvar = 7;
  objective->prev_hasLinear = true;
  objective->objtype = 5;
  objective->nvar = rtDW->nVar_tmp_l + 1;
  objective->gammaScalar = 1.0;
  objective->hasLinear = true;
  options->ObjectiveLimit = 1.0E-8 * runTimeOptions->ConstrRelTolFactor;
  solution->fstar = computeFval(objective, memspace->workspace_double, H, f,
    solution->xstar);
  solution->state = 5;
  iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
          objective, false, 0.0, options->ObjectiveLimit, 1.0E-8,
          1.4901161193847657E-10, *runTimeOptions, rtDW);
  if (workingset->isActiveConstr[(workingset->isActiveIdx[3] + workingset->
       sizes[3]) - 2]) {
    rtDW->i_i = workingset->sizes[0] + workingset->sizes[1];
    exitg1 = false;
    while ((!exitg1) && (rtDW->i_i + 1 <= workingset->nActiveConstr)) {
      if ((workingset->Wid[rtDW->i_i] == 4) && (workingset->Wlocalidx[rtDW->i_i]
           == workingset->sizes[3])) {
        rtDW->b_TYPE_a = workingset->Wid[rtDW->i_i] - 1;
        workingset->isActiveConstr[(workingset->isActiveIdx[workingset->Wid
          [rtDW->i_i] - 1] + workingset->Wlocalidx[rtDW->i_i]) - 2] = false;
        moveConstraint_(workingset, workingset->nActiveConstr, rtDW->i_i + 1);
        workingset->nActiveConstr--;
        workingset->nWConstr[rtDW->b_TYPE_a]--;
        exitg1 = true;
      } else {
        rtDW->i_i++;
      }
    }
  }

  rtDW->i_i = workingset->nActiveConstr;
  rtDW->b_TYPE_a = workingset->sizes[0] + workingset->sizes[1];
  while ((rtDW->i_i > rtDW->b_TYPE_a) && (rtDW->i_i > rtDW->nVar_tmp_l)) {
    rtDW->TYPE_tmp_o = workingset->Wid[rtDW->i_i - 1] - 1;
    workingset->isActiveConstr[(workingset->isActiveIdx[rtDW->TYPE_tmp_o] +
      workingset->Wlocalidx[rtDW->i_i - 1]) - 2] = false;
    moveConstraint_(workingset, workingset->nActiveConstr, rtDW->i_i);
    workingset->nActiveConstr--;
    workingset->nWConstr[rtDW->TYPE_tmp_o]--;
    rtDW->i_i--;
  }

  solution->maxConstr = solution->xstar[rtDW->nVar_tmp_l];
  setProblemType(workingset, rtDW->PROBTYPE_ORIG_a);
  objective->objtype = objective->prev_objtype;
  objective->nvar = objective->prev_nvar;
  objective->hasLinear = objective->prev_hasLinear;
  options->ObjectiveLimit = -1.0E+20;
  options->StepTolerance = 1.0E-8;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static int32_T ComputeNumDependentEq__d(sCS11Pe0E6xKX8jGoaG4cLG *qrmanager,
  const real_T beqf[10], int32_T mConstr, int32_T nVar, real_T tolfactor, DW
  *rtDW)
{
  int32_T numDependent;
  boolean_T exitg1;
  numDependent = mConstr - nVar;
  if (0 > numDependent) {
    numDependent = 0;
  }

  rtDW->totalRank = 0;
  while (rtDW->totalRank <= nVar - 1) {
    qrmanager->jpvt[rtDW->totalRank] = 0;
    rtDW->totalRank++;
  }

  if (mConstr * nVar == 0) {
    qrmanager->mrows = mConstr;
    qrmanager->ncols = nVar;
    qrmanager->minRowCol = 0;
  } else {
    qrmanager->usedPivoting = true;
    qrmanager->mrows = mConstr;
    qrmanager->ncols = nVar;
    if (mConstr < nVar) {
      qrmanager->minRowCol = mConstr;
    } else {
      qrmanager->minRowCol = nVar;
    }

    xzgeqp3(qrmanager->QR, 1, mConstr, nVar, qrmanager->jpvt, qrmanager->tau,
            rtDW);
  }

  rtDW->tol_g = tolfactor * (real_T)nVar * 2.2204460492503131E-16;
  if (nVar < mConstr) {
    rtDW->totalRank = nVar;
  } else {
    rtDW->totalRank = mConstr;
  }

  rtDW->totalRank += (rtDW->totalRank - 1) * qrmanager->ldq;
  while ((rtDW->totalRank > 0) && (fabs(qrmanager->QR[rtDW->totalRank - 1]) <
          rtDW->tol_g)) {
    rtDW->totalRank = (rtDW->totalRank - qrmanager->ldq) - 1;
    numDependent++;
  }

  if (numDependent > 0) {
    computeQ_(qrmanager, qrmanager->mrows, rtDW);
    rtDW->totalRank = 0;
    exitg1 = false;
    while ((!exitg1) && (rtDW->totalRank <= numDependent - 1)) {
      rtDW->qtb = 0.0;
      if (mConstr >= 1) {
        rtDW->ix_a = ((mConstr - rtDW->totalRank) - 1) * qrmanager->ldq;
        rtDW->iy_e = 0;
        rtDW->k_c = 0;
        while (rtDW->k_c <= mConstr - 1) {
          rtDW->qtb += qrmanager->Q[rtDW->ix_a] * beqf[rtDW->iy_e];
          rtDW->ix_a++;
          rtDW->iy_e++;
          rtDW->k_c++;
        }
      }

      if (fabs(rtDW->qtb) >= rtDW->tol_g) {
        numDependent = -1;
        exitg1 = true;
      } else {
        rtDW->totalRank++;
      }
    }
  }

  return numDependent;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void IndexOfDependentEq__i(int32_T depIdx[10], int32_T mFixed, int32_T
  nDep, sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, int32_T mRows, int32_T nCols, DW
  *rtDW)
{
  rtDW->b_idx_m = 0;
  while (rtDW->b_idx_m <= mFixed - 1) {
    qrmanager->jpvt[rtDW->b_idx_m] = 1;
    rtDW->b_idx_m++;
  }

  rtDW->b_idx_m = mFixed;
  while (rtDW->b_idx_m + 1 <= nCols) {
    qrmanager->jpvt[rtDW->b_idx_m] = 0;
    rtDW->b_idx_m++;
  }

  if (mRows * nCols == 0) {
    qrmanager->mrows = mRows;
    qrmanager->ncols = nCols;
    qrmanager->minRowCol = 0;
  } else {
    qrmanager->usedPivoting = true;
    qrmanager->mrows = mRows;
    qrmanager->ncols = nCols;
    if (mRows < nCols) {
      qrmanager->minRowCol = mRows;
    } else {
      qrmanager->minRowCol = nCols;
    }

    xzgeqp3(qrmanager->QR, 1, mRows, nCols, qrmanager->jpvt, qrmanager->tau,
            rtDW);
  }

  rtDW->b_idx_m = 0;
  while (rtDW->b_idx_m <= nDep - 1) {
    depIdx[rtDW->b_idx_m] = qrmanager->jpvt[(nCols - nDep) + rtDW->b_idx_m];
    rtDW->b_idx_m++;
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static int32_T RemoveDependentEq__b(snRDwUdgrIx9qNga56nZ8DE *memspace,
  stxriBK2jD81NCGacZ0b8HD *workingset, sCS11Pe0E6xKX8jGoaG4cLG *qrmanager,
  real_T tolfactor, DW *rtDW)
{
  int32_T nDepInd;
  rtDW->nVar_c = workingset->nVar - 1;
  rtDW->mTotalWorkingEq = workingset->nWConstr[0] + workingset->nWConstr[1];
  nDepInd = 0;
  if (rtDW->mTotalWorkingEq > 0) {
    rtDW->idx_row_p = 0;
    while (rtDW->idx_row_p <= rtDW->mTotalWorkingEq - 1) {
      rtDW->offsetQR = 0;
      while (rtDW->offsetQR <= rtDW->nVar_c) {
        qrmanager->QR[rtDW->idx_row_p + qrmanager->ldq * rtDW->offsetQR] =
          workingset->ATwset[workingset->ldA * rtDW->idx_row_p + rtDW->offsetQR];
        rtDW->offsetQR++;
      }

      rtDW->idx_row_p++;
    }

    nDepInd = ComputeNumDependentEq__d(qrmanager, workingset->bwset,
      rtDW->mTotalWorkingEq, workingset->nVar, tolfactor, rtDW);
    if (nDepInd > 0) {
      rtDW->idx_row_p = 0;
      while (rtDW->idx_row_p <= rtDW->mTotalWorkingEq - 1) {
        rtDW->offsetQR = qrmanager->ldq * rtDW->idx_row_p;
        rtDW->offsetATw = workingset->ldA * rtDW->idx_row_p;
        rtDW->k_p = 1;
        while (rtDW->k_p - 1 <= rtDW->nVar_c) {
          qrmanager->QR[(rtDW->offsetQR + rtDW->k_p) - 1] = workingset->ATwset
            [(rtDW->offsetATw + rtDW->k_p) - 1];
          rtDW->k_p++;
        }

        rtDW->idx_row_p++;
      }

      IndexOfDependentEq__i(memspace->workspace_int, workingset->nWConstr[0],
                            nDepInd, qrmanager, workingset->nVar,
                            rtDW->mTotalWorkingEq, rtDW);
      countsort(memspace->workspace_int, nDepInd, memspace->workspace_sort, 1,
                rtDW->mTotalWorkingEq);
      rtDW->nVar_c = nDepInd;
      while (rtDW->nVar_c > 0) {
        removeEqConstr(workingset, memspace->workspace_int[rtDW->nVar_c - 1]);
        rtDW->nVar_c--;
      }
    }
  }

  return nDepInd;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void PresolveWorkingSet_l(sVm5xLhdFDU5OIlGg0pTc4E *solution,
  snRDwUdgrIx9qNga56nZ8DE *memspace, stxriBK2jD81NCGacZ0b8HD *workingset,
  sCS11Pe0E6xKX8jGoaG4cLG *qrmanager, const s4lHOiXA0GHbse0IgoBY6ZF *options, DW
  *rtDW)
{
  solution->state = 82;
  rtDW->b_o = RemoveDependentEq__b(memspace, workingset, qrmanager, 100.0, rtDW);
  if ((rtDW->b_o != -1) && (workingset->nActiveConstr <= qrmanager->ldq)) {
    RemoveDependentIneq_(workingset, qrmanager, memspace, 100.0, rtDW);
    feasibleX0ForWorkingSet(memspace->workspace_double, solution->xstar,
      workingset, qrmanager, rtDW);
    if (workingset->nWConstr[0] + workingset->nWConstr[1] == workingset->nVar) {
      rtDW->constrViolation = maxConstraintViolation_pn(workingset,
        solution->xstar, rtDW);
      if (rtDW->constrViolation > options->ConstraintTolerance) {
        solution->state = -2;
      }
    }
  } else {
    solution->state = -3;
    removeAllIneqConstr(workingset);
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static boolean_T strcmp_m(const char_T a[8])
{
  int32_T kstr;
  boolean_T b_bool;
  static const char_T b[128] = { '\x00', '\x01', '\x02', '\x03', '\x04', '\x05',
    '\x06', '\x07', '\x08', '	', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f',
    '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18',
    '\x19', '\x1a', '\x1b', '\x1c', '\x1d', '\x1e', '\x1f', ' ', '!', '\"', '#',
    '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2',
    '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'a',
    'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[', '\\', ']', '^', '_',
    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}',
    '~', '\x7f' };

  static const char_T c[8] = { 'q', 'u', 'a', 'd', 'p', 'r', 'o', 'g' };

  int32_T exitg1;
  b_bool = false;
  kstr = 0;
  do {
    exitg1 = 0;
    if (kstr < 8) {
      if (b[(uint8_T)a[kstr] & 127] != b[(int32_T)c[kstr]]) {
        exitg1 = 1;
      } else {
        kstr++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return b_bool;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void phaseone_j(const real_T H[49], const real_T f[7],
  sVm5xLhdFDU5OIlGg0pTc4E *solution, snRDwUdgrIx9qNga56nZ8DE *memspace,
  stxriBK2jD81NCGacZ0b8HD *workingset, sCS11Pe0E6xKX8jGoaG4cLG *qrmanager,
  sSzLoP8tvZHiR1V2perTtWD *cholmanager, shohwUBaOGHF036TMzc1KEH *objective,
  s4lHOiXA0GHbse0IgoBY6ZF *options, const sL9bDKomAYkxZSVrG9w6En *runTimeOptions,
  DW *rtDW)
{
  boolean_T exitg1;
  rtDW->PROBTYPE_ORIG = workingset->probType;
  rtDW->nVar_tmp = workingset->nVar;
  solution->xstar[workingset->nVar] = solution->maxConstr + 1.0;
  if (workingset->probType == 3) {
    rtDW->mConstr = 1;
  } else {
    rtDW->mConstr = 4;
  }

  setProblemType(workingset, rtDW->mConstr);
  removeAllIneqConstr(workingset);
  objective->prev_objtype = objective->objtype;
  objective->prev_nvar = objective->nvar;
  objective->prev_hasLinear = objective->hasLinear;
  objective->objtype = 5;
  objective->nvar = rtDW->nVar_tmp + 1;
  objective->gammaScalar = 1.0;
  objective->hasLinear = true;
  rtDW->oldObjLim = options->ObjectiveLimit;
  rtDW->oldTolX = options->StepTolerance;
  options->ObjectiveLimit = options->ConstraintTolerance *
    runTimeOptions->ConstrRelTolFactor;
  options->StepTolerance = 1.4901161193847657E-10;
  solution->fstar = computeFval(objective, memspace->workspace_double, H, f,
    solution->xstar);
  solution->state = 5;
  iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
          objective, options->IterDisplayQP, options->PricingTolerance,
          options->ObjectiveLimit, options->ConstraintTolerance,
          options->StepTolerance, *runTimeOptions, rtDW);
  if (workingset->isActiveConstr[(workingset->isActiveIdx[3] + workingset->
       sizes[3]) - 2]) {
    rtDW->mConstr = workingset->sizes[0] + workingset->sizes[1];
    exitg1 = false;
    while ((!exitg1) && (rtDW->mConstr + 1 <= workingset->nActiveConstr)) {
      if ((workingset->Wid[rtDW->mConstr] == 4) && (workingset->Wlocalidx
           [rtDW->mConstr] == workingset->sizes[3])) {
        rtDW->b_TYPE = workingset->Wid[rtDW->mConstr] - 1;
        workingset->isActiveConstr[(workingset->isActiveIdx[workingset->Wid
          [rtDW->mConstr] - 1] + workingset->Wlocalidx[rtDW->mConstr]) - 2] =
          false;
        moveConstraint_(workingset, workingset->nActiveConstr, rtDW->mConstr + 1);
        workingset->nActiveConstr--;
        workingset->nWConstr[rtDW->b_TYPE]--;
        exitg1 = true;
      } else {
        rtDW->mConstr++;
      }
    }
  }

  rtDW->mConstr = workingset->nActiveConstr;
  rtDW->b_TYPE = workingset->sizes[0] + workingset->sizes[1];
  while ((rtDW->mConstr > rtDW->b_TYPE) && (rtDW->mConstr > rtDW->nVar_tmp)) {
    rtDW->TYPE_tmp = workingset->Wid[rtDW->mConstr - 1] - 1;
    workingset->isActiveConstr[(workingset->isActiveIdx[rtDW->TYPE_tmp] +
      workingset->Wlocalidx[rtDW->mConstr - 1]) - 2] = false;
    moveConstraint_(workingset, workingset->nActiveConstr, rtDW->mConstr);
    workingset->nActiveConstr--;
    workingset->nWConstr[rtDW->TYPE_tmp]--;
    rtDW->mConstr--;
  }

  solution->maxConstr = solution->xstar[rtDW->nVar_tmp];
  setProblemType(workingset, rtDW->PROBTYPE_ORIG);
  objective->objtype = objective->prev_objtype;
  objective->nvar = objective->prev_nvar;
  objective->hasLinear = objective->prev_hasLinear;
  options->ObjectiveLimit = rtDW->oldObjLim;
  options->StepTolerance = rtDW->oldTolX;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void driver(const real_T H[49], const real_T f[7],
                   sVm5xLhdFDU5OIlGg0pTc4E *solution, snRDwUdgrIx9qNga56nZ8DE
                   *memspace, sSzLoP8tvZHiR1V2perTtWD *cholmanager,
                   sL9bDKomAYkxZSVrG9w6En runTimeOptions,
                   stxriBK2jD81NCGacZ0b8HD *workingset, sCS11Pe0E6xKX8jGoaG4cLG *
                   qrmanager, shohwUBaOGHF036TMzc1KEH *objective, DW *rtDW)
{
  static const char_T m_FiniteDifferenceType[7] = { 'f', 'o', 'r', 'w', 'a', 'r',
    'd' };

  static const char_T m_Algorithm[10] = { 'a', 'c', 't', 'i', 'v', 'e', '-', 's',
    'e', 't' };

  static const char_T m_SolverName[8] = { 'q', 'u', 'a', 'd', 'p', 'r', 'o', 'g'
  };

  static const char_T m_Display[5] = { 'f', 'i', 'n', 'a', 'l' };

  boolean_T guard1 = false;
  memset(&objective->grad[0], 0, sizeof(real_T) << 3U);
  for (rtDW->i_j = 0; rtDW->i_j < 7; rtDW->i_j++) {
    objective->Hx[rtDW->i_j] = 0.0;
  }

  objective->hasLinear = true;
  objective->nvar = 7;
  objective->maxVar = 8;
  objective->beta = 0.0;
  objective->rho = 0.0;
  objective->objtype = 3;
  objective->prev_objtype = 3;
  objective->prev_nvar = 0;
  objective->prev_hasLinear = false;
  objective->gammaScalar = 0.0;
  solution->iterations = 0;
  runTimeOptions.RemainFeasible = true;
  PresolveWorkingSet(solution, memspace, workingset, qrmanager, rtDW);
  rtDW->options.InitDamping = 0.01;
  for (rtDW->i_j = 0; rtDW->i_j < 7; rtDW->i_j++) {
    rtDW->options.FiniteDifferenceType[rtDW->i_j] = m_FiniteDifferenceType
      [rtDW->i_j];
  }

  rtDW->options.SpecifyObjectiveGradient = false;
  rtDW->options.ScaleProblem = false;
  rtDW->options.SpecifyConstraintGradient = false;
  rtDW->options.NonFiniteSupport = true;
  rtDW->options.IterDisplaySQP = false;
  rtDW->options.FiniteDifferenceStepSize = -1.0;
  rtDW->options.MaxFunctionEvaluations = -1.0;
  rtDW->options.IterDisplayQP = false;
  rtDW->options.PricingTolerance = 0.0;
  for (rtDW->i_j = 0; rtDW->i_j < 10; rtDW->i_j++) {
    rtDW->options.Algorithm[rtDW->i_j] = m_Algorithm[rtDW->i_j];
  }

  rtDW->options.ObjectiveLimit = -1.0E+20;
  rtDW->options.ConstraintTolerance = 1.0E-8;
  rtDW->options.OptimalityTolerance = 1.0E-6;
  rtDW->options.StepTolerance = 1.0E-8;
  rtDW->options.MaxIterations = 7.0;
  rtDW->options.FunctionTolerance = 1.7976931348623157E+308;
  for (rtDW->i_j = 0; rtDW->i_j < 8; rtDW->i_j++) {
    rtDW->options.SolverName[rtDW->i_j] = m_SolverName[rtDW->i_j];
  }

  rtDW->options.CheckGradients = false;
  rtDW->options.Diagnostics[0] = 'o';
  rtDW->options.Diagnostics[1] = 'f';
  rtDW->options.Diagnostics[2] = 'f';
  rtDW->options.DiffMaxChange = 1.7976931348623157E+308;
  rtDW->options.DiffMinChange = 0.0;
  for (rtDW->i_j = 0; rtDW->i_j < 5; rtDW->i_j++) {
    rtDW->options.Display[rtDW->i_j] = m_Display[rtDW->i_j];
  }

  rtDW->options.FunValCheck[0] = 'o';
  rtDW->options.FunValCheck[1] = 'f';
  rtDW->options.FunValCheck[2] = 'f';
  rtDW->options.UseParallel = false;
  rtDW->options.LinearSolver[0] = 'a';
  rtDW->options.LinearSolver[1] = 'u';
  rtDW->options.LinearSolver[2] = 't';
  rtDW->options.LinearSolver[3] = 'o';
  rtDW->options.SubproblemAlgorithm[0] = 'c';
  rtDW->options.SubproblemAlgorithm[1] = 'g';
  if (solution->state >= 0) {
    solution->iterations = 0;
    rtDW->b = maxConstraintViolation_pn(workingset, solution->xstar, rtDW);
    solution->maxConstr = rtDW->b;
    guard1 = false;
    if (rtDW->b > 1.0E-8 * runTimeOptions.ConstrRelTolFactor) {
      phaseone(H, f, solution, memspace, workingset, qrmanager, cholmanager,
               &runTimeOptions, objective, &rtDW->options, rtDW);
      if (solution->state == 0) {
      } else {
        rtDW->b = maxConstraintViolation_pn(workingset, solution->xstar, rtDW);
        solution->maxConstr = rtDW->b;
        if (rtDW->b > rtDW->options.ConstraintTolerance *
            runTimeOptions.ConstrRelTolFactor) {
          rtDW->i_j = 0;
          while (rtDW->i_j <= workingset->mConstrMax - 1) {
            solution->lambda[rtDW->i_j] = 0.0;
            rtDW->i_j++;
          }

          solution->fstar = computeFval(objective, memspace->workspace_double, H,
            f, solution->xstar);
          solution->state = -2;
        } else {
          if (rtDW->b > 0.0) {
            for (rtDW->i_j = 0; rtDW->i_j < 7; rtDW->i_j++) {
              solution->searchDir[rtDW->i_j] = solution->xstar[rtDW->i_j];
            }

            PresolveWorkingSet_l(solution, memspace, workingset, qrmanager,
                                 &rtDW->options, rtDW);
            rtDW->b = maxConstraintViolation_pn(workingset, solution->xstar,
              rtDW);
            if (rtDW->b >= solution->maxConstr) {
              solution->maxConstr = rtDW->b;
              for (rtDW->i_j = 0; rtDW->i_j < 7; rtDW->i_j++) {
                solution->xstar[rtDW->i_j] = solution->searchDir[rtDW->i_j];
              }
            }
          }

          guard1 = true;
        }
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
              objective, rtDW->options.IterDisplayQP,
              rtDW->options.PricingTolerance, rtDW->options.ObjectiveLimit,
              rtDW->options.ConstraintTolerance, rtDW->options.StepTolerance,
              runTimeOptions, rtDW);
      if (strcmp_m(rtDW->options.SolverName) && (solution->state != -6)) {
        solution->maxConstr = maxConstraintViolation_pn(workingset,
          solution->xstar, rtDW);
        computeFirstOrderOpt(solution, objective, workingset->nVar,
                             workingset->ldA, workingset->ATwset,
                             workingset->nActiveConstr,
                             memspace->workspace_double);
        runTimeOptions.RemainFeasible = false;
        while ((solution->iterations < runTimeOptions.MaxIterations) &&
               ((solution->state == -7) || ((solution->state == 1) &&
                 ((solution->maxConstr > rtDW->options.ConstraintTolerance *
                   runTimeOptions.ConstrRelTolFactor) ||
                  (solution->firstorderopt > rtDW->options.OptimalityTolerance *
                   runTimeOptions.ProbRelTolFactor))))) {
          feasibleX0ForWorkingSet(memspace->workspace_double, solution->xstar,
            workingset, qrmanager, rtDW);
          PresolveWorkingSet_l(solution, memspace, workingset, qrmanager,
                               &rtDW->options, rtDW);
          phaseone_j(H, f, solution, memspace, workingset, qrmanager,
                     cholmanager, objective, &rtDW->options, &runTimeOptions,
                     rtDW);
          iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
                  objective, rtDW->options.IterDisplayQP,
                  rtDW->options.PricingTolerance, rtDW->options.ObjectiveLimit,
                  rtDW->options.ConstraintTolerance, rtDW->options.StepTolerance,
                  runTimeOptions, rtDW);
          solution->maxConstr = maxConstraintViolation_pn(workingset,
            solution->xstar, rtDW);
          computeFirstOrderOpt(solution, objective, workingset->nVar,
                               workingset->ldA, workingset->ATwset,
                               workingset->nActiveConstr,
                               memspace->workspace_double);
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void linearForm__a(boolean_T obj_hasLinear, int32_T obj_nvar, real_T
  workspace[8], const real_T H[49], const real_T f[7], const real_T x[8])
{
  int32_T b;
  int32_T c;
  int32_T fMultiplier;
  int32_T ia;
  int32_T iac;
  int32_T iy;
  fMultiplier = 0;
  if (obj_hasLinear) {
    while (fMultiplier <= obj_nvar - 1) {
      workspace[fMultiplier] = f[fMultiplier];
      fMultiplier++;
    }

    fMultiplier = 1;
  }

  if (obj_nvar != 0) {
    if (fMultiplier != 1) {
      while (fMultiplier <= obj_nvar - 1) {
        workspace[fMultiplier] = 0.0;
        fMultiplier++;
      }
    }

    fMultiplier = 0;
    c = (obj_nvar - 1) * obj_nvar + 1;
    iac = 1;
    while (((obj_nvar > 0) && (iac <= c)) || ((obj_nvar < 0) && (iac >= c))) {
      iy = 0;
      b = (iac + obj_nvar) - 1;
      for (ia = iac; ia <= b; ia++) {
        workspace[iy] += H[ia - 1] * x[fMultiplier];
        iy++;
      }

      fMultiplier++;
      iac += obj_nvar;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void quadprog(const real_T H[49], const real_T f[7], const real_T x0[7],
                     real_T x[7], real_T *fval, real_T *exitflag, char_T
                     output_algorithm[10], real_T *output_firstorderopt, real_T *
                     output_constrviolation, real_T *output_iterations, DW *rtDW)
{
  static const char_T e[10] = { 'a', 'c', 't', 'i', 'v', 'e', '-', 's', 'e', 't'
  };

  rtDW->solution.fstar = 0.0;
  rtDW->solution.firstorderopt = 0.0;
  memset(&rtDW->solution.lambda[0], 0, 10U * sizeof(real_T));
  rtDW->solution.state = 0;
  rtDW->solution.maxConstr = 0.0;
  rtDW->solution.iterations = 0;
  memset(&rtDW->solution.searchDir[0], 0, sizeof(real_T) << 3U);
  factoryConstruct(&rtDW->CholRegManager);
  rtDW->CholRegManager.scaleFactor = 100.0;
  rtDW->H_infnrm = 0.0;
  rtDW->f_infnrm = 0.0;
  for (rtDW->i_a = 0; rtDW->i_a < 7; rtDW->i_a++) {
    rtDW->solution.xstar[rtDW->i_a] = x0[rtDW->i_a];
    rtDW->colSum = 0.0;
    for (rtDW->idx_row = 0; rtDW->idx_row < 7; rtDW->idx_row++) {
      rtDW->colSum += fabs(H[7 * rtDW->i_a + rtDW->idx_row]);
    }

    rtDW->H_infnrm = fmax(rtDW->H_infnrm, rtDW->colSum);
    rtDW->f_infnrm = fmax(rtDW->f_infnrm, fabs(f[rtDW->i_a]));
  }

  rtDW->expl_temp.RemainFeasible = false;
  rtDW->expl_temp.ProbRelTolFactor = fmax(fmax(7.0, rtDW->f_infnrm),
    rtDW->H_infnrm);
  rtDW->expl_temp.ConstrRelTolFactor = 7.0;
  rtDW->expl_temp.MaxIterations = 7;
  driver(H, f, &rtDW->solution, &rtDW->memspace, &rtDW->CholRegManager,
         rtDW->expl_temp, &rtDW->WorkingSet, &rtDW->QRManager,
         &rtDW->QPObjective, rtDW);
  for (rtDW->i_a = 0; rtDW->i_a < 7; rtDW->i_a++) {
    x[rtDW->i_a] = rtDW->solution.xstar[rtDW->i_a];
  }

  if (rtDW->solution.state > 0) {
    *fval = rtDW->solution.fstar;
  } else {
    *fval = computeFval(&rtDW->QPObjective, rtDW->memspace.workspace_double, H,
                        f, rtDW->solution.xstar);
  }

  switch (rtDW->solution.state) {
   case 2:
    rtDW->solution.state = -3;
    break;

   case -3:
    rtDW->solution.state = -2;
    break;

   case 4:
    rtDW->solution.state = -2;
    break;
  }

  *exitflag = rtDW->solution.state;
  if (rtDW->solution.state == -2) {
    rtDW->solution.firstorderopt = 1.7976931348623157E+308;
  } else if (rtDW->solution.state <= 0) {
    rtDW->H_infnrm = maxConstraintViolation_pn(&rtDW->WorkingSet,
      rtDW->solution.xstar, rtDW);
    rtDW->solution.maxConstr = rtDW->H_infnrm;
    if (rtDW->H_infnrm <= 7.0E-8) {
      switch (rtDW->QPObjective.objtype) {
       case 5:
        rtDW->i_a = 0;
        while (rtDW->i_a <= rtDW->QPObjective.nvar - 2) {
          rtDW->QPObjective.grad[rtDW->i_a] = 0.0;
          rtDW->i_a++;
        }

        rtDW->QPObjective.grad[rtDW->QPObjective.nvar - 1] =
          rtDW->QPObjective.gammaScalar;
        break;

       case 3:
        linearForm__a(rtDW->QPObjective.hasLinear, rtDW->QPObjective.nvar,
                      rtDW->QPObjective.grad, H, f, rtDW->solution.xstar);
        break;

       case 4:
        linearForm__a(rtDW->QPObjective.hasLinear, rtDW->QPObjective.nvar,
                      rtDW->QPObjective.grad, H, f, rtDW->solution.xstar);
        rtDW->i_a = rtDW->QPObjective.nvar;
        while (rtDW->i_a + 1 <= rtDW->QPObjective.maxVar - 1) {
          rtDW->QPObjective.grad[rtDW->i_a] = rtDW->QPObjective.beta *
            rtDW->solution.xstar[rtDW->i_a] + rtDW->QPObjective.rho;
          rtDW->i_a++;
        }
        break;
      }

      computeFirstOrderOpt(&rtDW->solution, &rtDW->QPObjective,
                           rtDW->WorkingSet.nVar, rtDW->WorkingSet.ldA,
                           rtDW->WorkingSet.ATwset,
                           rtDW->WorkingSet.nActiveConstr,
                           rtDW->memspace.workspace_double);
    } else {
      rtDW->solution.firstorderopt = 1.7976931348623157E+308;
    }
  }

  for (rtDW->i_a = 0; rtDW->i_a < 10; rtDW->i_a++) {
    output_algorithm[rtDW->i_a] = e[rtDW->i_a];
  }

  *output_firstorderopt = rtDW->solution.firstorderopt;
  *output_constrviolation = fmax(0.0, rtDW->solution.maxConstr);
  *output_iterations = rtDW->solution.iterations;
}

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  int8_T ipiv;
  boolean_T rEQ0;
  static const int8_T h[8] = { 0, 0, 0, 0, 1, 0, 0, 0 };

  static const int8_T g[8] = { 0, 0, 0, 0, 0, 1, 0, 0 };

  static const int8_T f[8] = { 0, 0, 0, 0, 0, 0, 1, 0 };

  static const int8_T e[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };

  static const int8_T l[32] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };

  static const int8_T m[32] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  static const int8_T tmp[24] = { 8, 1, 1, 8, 8, 2, 2, 16, 16, 2, 2, 16, 16, 4,
    4, 32, 32, 4, 4, 32, 32, 1, 1, 8 };

  static const int8_T tmp_0[24] = { 9, 9, 9, 9, 10, 10, 18, 18, 18, 18, 18, 18,
    20, 20, 36, 36, 36, 36, 36, 36, 33, 33, 9, 9 };

  static const int8_T tmp_1[24] = { 41, 11, 11, 11, 11, 26, 26, 26, 26, 22, 22,
    22, 22, 52, 52, 52, 52, 37, 37, 37, 37, 41, 41, 41 };

  static const int8_T tmp_2[24] = { 43, 43, 27, 27, 27, 27, 27, 27, 30, 30, 54,
    54, 54, 54, 54, 54, 53, 53, 45, 45, 45, 45, 45, 45 };

  static const int8_T tmp_3[24] = { 47, 59, 59, 31, 31, 59, 59, 31, 31, 62, 62,
    55, 55, 62, 62, 55, 55, 61, 61, 47, 47, 61, 61, 47 };

  static const real32_T v_alpha_beta_pu[124] = { 0.333333F, -0.166667F,
    0.166667F, -0.166667F, 0.166667F, -0.333333F, 0.0F, 0.288675F, 0.622008F,
    0.122008F, 0.455342F, 0.122008F, 0.455342F, -0.044658F, 0.288675F,
    -0.288675F, 0.044658F, -0.455342F, -0.122008F, -0.455342F, -0.122008F,
    -0.622008F, -0.288675F, 0.0F, 0.333333F, -0.166667F, 0.166667F, -0.166667F,
    0.166667F, -0.333333F, 0.0F, -0.0F, 0.333333F, -0.166667F, 0.166667F,
    -0.166667F, 0.166667F, -0.333333F, -0.0F, 0.288675F, 0.622008F, 0.122008F,
    0.455342F, 0.122008F, 0.455342F, -0.044658F, 0.288675F, -0.288675F,
    0.044658F, -0.455342F, -0.122008F, -0.455342F, -0.122008F, -0.622008F,
    -0.288675F, -0.0F, 0.333333F, -0.166667F, 0.166667F, -0.166667F, 0.166667F,
    -0.333333F, -0.0F, 0.288675F, 0.288675F, -0.288675F, -0.288675F, 0.0F, 0.0F,
    0.166667F, 0.166667F, 0.455342F, 0.455342F, -0.122008F, -0.122008F,
    0.166667F, 0.166667F, 0.166667F, 0.166667F, 0.455342F, 0.455342F, -0.122008F,
    -0.122008F, 0.166667F, 0.166667F, 0.333333F, 0.333333F, 0.622008F, 0.622008F,
    0.044658F, 0.044658F, 0.333333F, 0.333333F, -0.333333F, -0.333333F,
    -0.044658F, -0.044658F, -0.622008F, -0.622008F, -0.333333F, -0.333333F,
    -0.166667F, -0.166667F, 0.122008F, 0.122008F, -0.455342F, -0.455342F,
    -0.166667F, -0.166667F, -0.166667F, -0.166667F, 0.122008F, 0.122008F,
    -0.455342F, -0.455342F, -0.166667F, -0.166667F, -0.0F, -0.0F, 0.288675F,
    0.288675F, -0.288675F, -0.288675F, 0.0F };

  static const real32_T v_X_Y_pu[124] = { 0.333333F, -0.166667F, 0.166667F,
    -0.166667F, 0.166667F, -0.333333F, 0.0F, -0.288675F, 0.044658F, -0.455342F,
    -0.122008F, -0.455342F, -0.122008F, -0.622008F, -0.288675F, 0.288675F,
    0.622008F, 0.122008F, 0.455342F, 0.122008F, 0.455342F, -0.044658F, 0.288675F,
    0.0F, 0.333333F, -0.166667F, 0.166667F, -0.166667F, 0.166667F, -0.333333F,
    0.0F, 0.0F, 0.333333F, -0.166667F, 0.166667F, -0.166667F, 0.166667F,
    -0.333333F, 0.0F, -0.288675F, 0.044658F, -0.455342F, -0.122008F, -0.455342F,
    -0.122008F, -0.622008F, -0.288675F, 0.288675F, 0.622008F, 0.122008F,
    0.455342F, 0.122008F, 0.455342F, -0.044658F, 0.288675F, 0.0F, 0.333333F,
    -0.166667F, 0.166667F, -0.166667F, 0.166667F, -0.333333F, 0.0F, -0.288675F,
    -0.288675F, 0.288675F, 0.288675F, 0.0F, 0.0F, 0.166667F, 0.166667F,
    -0.122008F, -0.122008F, 0.455342F, 0.455342F, 0.166667F, 0.166667F,
    0.166667F, 0.166667F, -0.122008F, -0.122008F, 0.455342F, 0.455342F,
    0.166667F, 0.166667F, 0.333333F, 0.333333F, 0.044658F, 0.044658F, 0.622008F,
    0.622008F, 0.333333F, 0.333333F, -0.333333F, -0.333333F, -0.622008F,
    -0.622008F, -0.044658F, -0.044658F, -0.333333F, -0.333333F, -0.166667F,
    -0.166667F, -0.455342F, -0.455342F, 0.122008F, 0.122008F, -0.166667F,
    -0.166667F, -0.166667F, -0.166667F, -0.455342F, -0.455342F, 0.122008F,
    0.122008F, -0.166667F, -0.166667F, 0.0F, 0.0F, -0.288675F, -0.288675F,
    0.288675F, 0.288675F, 0.0F };

  static const int8_T a[42] = { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1,
    1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
  };

  static const int8_T seq_order_table[144] = { 4, 1, 1, 4, 4, 2, 2, 5, 5, 2, 2,
    5, 5, 3, 3, 6, 6, 3, 3, 6, 6, 1, 1, 4, 1, 4, 4, 1, 2, 4, 5, 2, 2, 5, 5, 2, 3,
    5, 6, 3, 3, 6, 6, 3, 1, 6, 4, 1, 6, 2, 2, 2, 1, 5, 4, 4, 4, 3, 3, 3, 2, 6, 5,
    5, 5, 1, 1, 1, 3, 4, 6, 6, 2, 6, 5, 5, 5, 1, 1, 1, 3, 4, 6, 6, 6, 2, 2, 2, 1,
    5, 4, 4, 4, 3, 3, 3, 3, 5, 6, 3, 3, 6, 6, 3, 1, 6, 4, 1, 1, 4, 4, 1, 2, 4, 5,
    2, 2, 5, 5, 2, 5, 3, 3, 6, 6, 3, 3, 6, 6, 1, 1, 4, 4, 1, 1, 4, 4, 2, 2, 5, 5,
    2, 2, 5 };

  /* Delay: '<S1>/Delay13' */
  if (rtDW->icLoad) {
    for (rtDW->i = 0; rtDW->i < 7; rtDW->i++) {
      rtDW->Delay13_DSTATE[rtDW->i] = 0.14F;
    }
  }

  /* MATLAB Function: '<S1>/v_dqxy' incorporates:
   *  Delay: '<S1>/Delay'
   *  Delay: '<S1>/Delay10'
   *  Delay: '<S1>/Delay11'
   *  Delay: '<S1>/Delay12'
   *  Delay: '<S1>/Delay13'
   *  Delay: '<S1>/Delay9'
   */
  /* MATLAB Function 'uz_codegen/v_dqxy': '<S13>:1' */
  /* '<S13>:1:3' v0 = [single(0.0);single(0.0);single(0.0);single(0.0)]; */
  /* '<S13>:1:4' v_opt = [v0, v1, v2, v3, v4, v5, v0]; */
  /*  calculate v_dqxy */
  /* '<S13>:1:7' v_t0 = v_opt * t_opt; */
  rtDW->r[0] = 0.0F;
  rtDW->r[4] = rtDW->Delay_DSTATE[0];
  rtDW->r[8] = rtDW->Delay9_DSTATE[0];
  rtDW->r[12] = rtDW->Delay10_DSTATE[0];
  rtDW->r[16] = rtDW->Delay11_DSTATE[0];
  rtDW->r[20] = rtDW->Delay12_DSTATE[0];
  rtDW->r[24] = 0.0F;
  rtDW->r[1] = 0.0F;
  rtDW->r[5] = rtDW->Delay_DSTATE[1];
  rtDW->r[9] = rtDW->Delay9_DSTATE[1];
  rtDW->r[13] = rtDW->Delay10_DSTATE[1];
  rtDW->r[17] = rtDW->Delay11_DSTATE[1];
  rtDW->r[21] = rtDW->Delay12_DSTATE[1];
  rtDW->r[25] = 0.0F;
  rtDW->r[2] = 0.0F;
  rtDW->r[6] = rtDW->Delay_DSTATE[2];
  rtDW->r[10] = rtDW->Delay9_DSTATE[2];
  rtDW->r[14] = rtDW->Delay10_DSTATE[2];
  rtDW->r[18] = rtDW->Delay11_DSTATE[2];
  rtDW->r[22] = rtDW->Delay12_DSTATE[2];
  rtDW->r[26] = 0.0F;
  rtDW->r[3] = 0.0F;
  rtDW->r[7] = rtDW->Delay_DSTATE[3];
  rtDW->r[11] = rtDW->Delay9_DSTATE[3];
  rtDW->r[15] = rtDW->Delay10_DSTATE[3];
  rtDW->r[19] = rtDW->Delay11_DSTATE[3];
  rtDW->r[23] = rtDW->Delay12_DSTATE[3];
  rtDW->r[27] = 0.0F;
  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    rtDW->v_t0[rtDW->d_j] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 7; rtDW->iy++) {
      rtDW->v_t0[rtDW->d_j] += rtDW->r[(rtDW->iy << 2) + rtDW->d_j] *
        rtDW->Delay13_DSTATE[rtDW->iy];
    }
  }

  /* End of MATLAB Function: '<S1>/v_dqxy' */

  /* MATLAB Function: '<S1>/Observer' incorporates:
   *  Inport: '<Root>/HC_off_on'
   *  Inport: '<Root>/Ld_over_LB'
   *  Inport: '<Root>/Lq_over_LB'
   *  Inport: '<Root>/Lx_over_LB'
   *  Inport: '<Root>/Ly_over_LB'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/Ts_times_ZB_over_Lx'
   *  Inport: '<Root>/Ts_times_ZB_over_Ly'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/phiPM_h'
   *  Inport: '<Root>/psiPM_h_pu'
   *  Inport: '<Root>/psi_pm_over_psiB'
   *  Inport: '<Root>/theta_el_pos'
   *  MATLAB Function: '<S1>/current_gradient_prediction'
   */
  /*  t_opt already multiplied by 2 */
  /* MATLAB Function 'uz_codegen/MATLAB Function': '<S2>:1' */
  /* '<S2>:1:4' R = single([kalman_R 0 0 0; 0 kalman_R 0 0; 0 0 kalman_R 0; 0 0 0 kalman_R]); */
  /* '<S2>:1:5' Q = single([kalman_Q1 0 0 0 0 0 0 0; 0 kalman_Q1 0 0 0 0 0 0; 0 0 kalman_Q1 0 0 0 0 0; 0 0 0 kalman_Q1 0 0 0 0; 0 0 0 0 kalman_Q2 0 0 0; 0 0 0 0 0 kalman_Q2 0 0; 0 0 0 0 0 0 kalman_Q2 0; 0 0 0 0 0 0 0 kalman_Q2]); */
  /* MATLAB Function 'uz_codegen/Observer': '<S3>:1' */
  /* '<S3>:1:3' i_dq_obs = single([0;0]); */
  /* '<S3>:1:4' i_xy_obs = single([0;0]); */
  /* '<S3>:1:5' d_dq_obs = single([0;0]); */
  /* '<S3>:1:6' d_xy_obs = single([0;0]); */
  /*  system model */
  /* '<S3>:1:9' A = [ 1-Ts_times_ZB_over_Ld*Rs_over_ZB            Ts_times_ZB_over_Ld*Lq_over_LB*w_e_pu   0                                      0                                                  1 0 0 0; */
  /* '<S3>:1:10'       -Ts_times_ZB_over_Lq*Ld_over_LB*w_e_pu     1-Ts_times_ZB_over_Lq*Rs_over_ZB         0                                      0                                                  0 1 0 0; */
  /* '<S3>:1:11'       0                                          0                                        1-Ts_times_ZB_over_Lx*Rs_over_ZB       -Ts_times_ZB_over_Lx*Ly_over_LB*w_e_pu             0 0 1 0; */
  /* '<S3>:1:12'       0                                          0                                        Ts_times_ZB_over_Ly*Lx_over_LB*w_e_pu  1-Ts_times_ZB_over_Ly*Rs_over_ZB                   0 0 0 1; */
  /* '<S3>:1:13'       0 0 0 0 1 0 0 0; */
  /* '<S3>:1:14'       0 0 0 0 0 1 0 0; */
  /* '<S3>:1:15'       0 0 0 0 0 0 1 0; */
  /* '<S3>:1:16'       0 0 0 0 0 0 0 1]; */
  rtDW->A[0] = 1.0F - rtU->Ts_times_ZB_over_Ld * rtU->Rs_over_ZB;
  rtDW->x0_idx_0 = rtU->Ts_times_ZB_over_Ld * rtU->Lq_over_LB * rtU->omega_el_pu;
  rtDW->A[8] = rtDW->x0_idx_0;
  rtDW->A[16] = 0.0F;
  rtDW->A[24] = 0.0F;
  rtDW->A[32] = 1.0F;
  rtDW->A[40] = 0.0F;
  rtDW->A[48] = 0.0F;
  rtDW->A[56] = 0.0F;
  rtDW->x0_idx_1 = -rtU->Ts_times_ZB_over_Lq * rtU->Ld_over_LB *
    rtU->omega_el_pu;
  rtDW->A[1] = rtDW->x0_idx_1;
  rtDW->A[9] = 1.0F - rtU->Ts_times_ZB_over_Lq * rtU->Rs_over_ZB;
  rtDW->A[17] = 0.0F;
  rtDW->A[25] = 0.0F;
  rtDW->A[33] = 0.0F;
  rtDW->A[41] = 1.0F;
  rtDW->A[49] = 0.0F;
  rtDW->A[57] = 0.0F;
  rtDW->A[2] = 0.0F;
  rtDW->A[10] = 0.0F;
  rtDW->A[18] = 1.0F - rtU->Ts_times_ZB_over_Lx * rtU->Rs_over_ZB;
  rtDW->x0_idx_2 = -rtU->Ts_times_ZB_over_Lx * rtU->Ly_over_LB *
    rtU->omega_el_pu;
  rtDW->A[26] = rtDW->x0_idx_2;
  rtDW->A[34] = 0.0F;
  rtDW->A[42] = 0.0F;
  rtDW->A[50] = 1.0F;
  rtDW->A[58] = 0.0F;
  rtDW->A[3] = 0.0F;
  rtDW->A[11] = 0.0F;
  rtDW->x0_idx_3 = rtU->Ts_times_ZB_over_Ly * rtU->Lx_over_LB * rtU->omega_el_pu;
  rtDW->A[19] = rtDW->x0_idx_3;
  rtDW->A[27] = 1.0F - rtU->Ts_times_ZB_over_Ly * rtU->Rs_over_ZB;
  rtDW->A[35] = 0.0F;
  rtDW->A[43] = 0.0F;
  rtDW->A[51] = 0.0F;
  rtDW->A[59] = 1.0F;
  for (rtDW->d_j = 0; rtDW->d_j < 8; rtDW->d_j++) {
    rtDW->sector_ref = rtDW->d_j << 3;
    rtDW->A[rtDW->sector_ref + 4] = h[rtDW->d_j];
    rtDW->A[rtDW->sector_ref + 5] = g[rtDW->d_j];
    rtDW->A[rtDW->sector_ref + 6] = f[rtDW->d_j];
    rtDW->A[rtDW->sector_ref + 7] = e[rtDW->d_j];
  }

  /* '<S3>:1:18' psiPM5 = psiPM_h_pu(1); */
  /* '<S3>:1:19' psiPM7 = psiPM_h_pu(2); */
  /* '<S3>:1:21' phi5 = phiPM_h(1); */
  /* '<S3>:1:22' phi7 = phiPM_h(2); */
  /*  w3theta_el = single(3*theta_el); */
  /* '<S3>:1:25' w6theta_el = single(6*theta_el); */
  rtDW->w6theta_el_tmp = 6.0F * rtU->theta_el_pos;

  /*  w9theta_el = single(9*theta_el); */
  /*  w12theta_el = single(12*theta_el);   */
  /* '<S3>:1:29' B = [Ts_times_ZB_over_Ld    0                       0                       0                       ; */
  /* '<S3>:1:30'      0                      Ts_times_ZB_over_Lq     0                       0                       ; */
  /* '<S3>:1:31'      0                      0                       Ts_times_ZB_over_Lx     0                       ; */
  /* '<S3>:1:32'      0                      0                       0                       Ts_times_ZB_over_Ly     ; */
  /* '<S3>:1:33'      0 0 0 0; */
  /* '<S3>:1:34'      0 0 0 0; */
  /* '<S3>:1:35'      0 0 0 0; */
  /* '<S3>:1:36'      0 0 0 0]; */
  /* '<S3>:1:38' C = [1   0   0   0   0   0   0   0; */
  /* '<S3>:1:39'      0   1   0   0   0   0   0   0; */
  /* '<S3>:1:40'      0   0   1   0   0   0   0   0; */
  /* '<S3>:1:41'      0   0   0   1   0   0   0   0]; */
  /* '<S3>:1:45' switch HC_off_on */
  if (!rtU->HC_off_on) {
    rtDW->d_j = 0;
  } else if (rtU->HC_off_on) {
    rtDW->d_j = 1;
  } else {
    rtDW->d_j = -1;
  }

  switch (rtDW->d_j) {
   case 0:
    /* '<S3>:1:46' case false */
    /* '<S3>:1:47' d_m = [0; -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB; 0; 0; 0; 0; 0; 0]; */
    rtDW->d_m[0] = 0.0F;
    rtDW->d_m[1] = -rtU->omega_el_pu * rtU->Ts_times_ZB_over_Lq *
      rtU->psi_pm_over_psiB;
    rtDW->d_m[2] = 0.0F;
    rtDW->d_m[3] = 0.0F;
    rtDW->d_m[4] = 0.0F;
    rtDW->d_m[5] = 0.0F;
    rtDW->d_m[6] = 0.0F;
    rtDW->d_m[7] = 0.0F;
    break;

   case 1:
    /* '<S3>:1:48' case true */
    /* '<S3>:1:49' d_m = [     0; */
    /* '<S3>:1:50'          -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB; */
    /* '<S3>:1:51'          -w_e_pu*Ts_times_ZB_over_Lx*(psiPM5*sin(w6theta_el+phi5)-psiPM7*sin(w6theta_el+phi7)-psiPM5*6*sin(w6theta_el+phi5)-psiPM7*6*sin(w6theta_el+phi7)); */
    /* '<S3>:1:52'           w_e_pu*Ts_times_ZB_over_Ly*(psiPM5*cos(w6theta_el+phi5)+psiPM7*cos(w6theta_el+phi7)-psiPM5*6*cos(w6theta_el+phi5)+psiPM7*6*cos(w6theta_el+phi7)); */
    /* '<S3>:1:53'           0; */
    /* '<S3>:1:54'           0; */
    /* '<S3>:1:55'           0; */
    /* '<S3>:1:56'           0]; */
    rtDW->SinCos2_o2 = rtDW->w6theta_el_tmp + rtU->phiPM_h[0];
    rtDW->SinCos1_o2 = sinf(rtDW->SinCos2_o2);
    rtDW->w6theta_el = rtDW->w6theta_el_tmp + rtU->phiPM_h[1];
    rtDW->SinCos2_o1 = sinf(rtDW->w6theta_el);
    rtDW->SinCos2_o2 = cosf(rtDW->SinCos2_o2);
    rtDW->w6theta_el = cosf(rtDW->w6theta_el);
    rtDW->d_m[0] = 0.0F;
    rtDW->d_m[1] = -rtU->omega_el_pu * rtU->Ts_times_ZB_over_Lq *
      rtU->psi_pm_over_psiB;
    rtDW->d_m[2] = (((rtU->psiPM_h_pu[0] * rtDW->SinCos1_o2 - rtU->psiPM_h_pu[1]
                      * rtDW->SinCos2_o1) - rtU->psiPM_h_pu[0] * 6.0F *
                     rtDW->SinCos1_o2) - rtU->psiPM_h_pu[1] * 6.0F *
                    rtDW->SinCos2_o1) * (-rtU->omega_el_pu *
      rtU->Ts_times_ZB_over_Lx);
    rtDW->d_m[3] = (((rtU->psiPM_h_pu[0] * rtDW->SinCos2_o2 + rtU->psiPM_h_pu[1]
                      * rtDW->w6theta_el) - rtU->psiPM_h_pu[0] * 6.0F *
                     rtDW->SinCos2_o2) + rtU->psiPM_h_pu[1] * 6.0F *
                    rtDW->w6theta_el) * (rtU->omega_el_pu *
      rtU->Ts_times_ZB_over_Ly);
    rtDW->d_m[4] = 0.0F;
    rtDW->d_m[5] = 0.0F;
    rtDW->d_m[6] = 0.0F;
    rtDW->d_m[7] = 0.0F;
    break;

   default:
    /* '<S3>:1:57' otherwise */
    /* '<S3>:1:58' d_m = [0; -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB; 0; 0; 0; 0; 0; 0]; */
    rtDW->d_m[0] = 0.0F;
    rtDW->d_m[1] = -rtU->omega_el_pu * rtU->Ts_times_ZB_over_Lq *
      rtU->psi_pm_over_psiB;
    rtDW->d_m[2] = 0.0F;
    rtDW->d_m[3] = 0.0F;
    rtDW->d_m[4] = 0.0F;
    rtDW->d_m[5] = 0.0F;
    rtDW->d_m[6] = 0.0F;
    rtDW->d_m[7] = 0.0F;
    break;
  }

  /*  original xy harmonic equations without placing factor outside the */
  /*  brackets */
  /*   -w_e_pu*Ts_times_ZB_over_Lx*(psiPM5*sin(w6theta_el+phi5)-psiPM7*sin(w6theta_el+phi7))-Ts_times_ZB_over_Lx*w_e_pu*(-psiPM5*6*sin(w6theta_el+phi5)-psiPM7*6*sin(w6theta_el+phi7))+e_xy_obs(1); */
  /*    w_e_pu*Ts_times_ZB_over_Ly*(psiPM5*cos(w6theta_el+phi5)+psiPM7*cos(w6theta_el+phi7))-Ts_times_ZB_over_Ly*w_e_pu*(+psiPM5*6*cos(w6theta_el+phi5)-psiPM7*6*cos(w6theta_el+phi7))+e_xy_obs(2) */
  /*  input voltages for kalman DOB */
  /* '<S3>:1:70' u = [v_d; v_q; v_x; v_y]; */
  /* '<S3>:1:74' if isempty(x_e) */
  /* '<S3>:1:80' x = x_e; */
  /* '<S3>:1:82' x_p = A * x + B * u + d_m; */
  rtDW->b_A_tmp[0] = rtU->Ts_times_ZB_over_Ld;
  rtDW->b_A_tmp[8] = 0.0F;
  rtDW->b_A_tmp[16] = 0.0F;
  rtDW->b_A_tmp[24] = 0.0F;
  rtDW->b_A_tmp[1] = 0.0F;
  rtDW->b_A_tmp[9] = rtU->Ts_times_ZB_over_Lq;
  rtDW->b_A_tmp[17] = 0.0F;
  rtDW->b_A_tmp[25] = 0.0F;
  rtDW->b_A_tmp[2] = 0.0F;
  rtDW->b_A_tmp[10] = 0.0F;
  rtDW->b_A_tmp[18] = rtU->Ts_times_ZB_over_Lx;
  rtDW->b_A_tmp[26] = 0.0F;
  rtDW->b_A_tmp[3] = 0.0F;
  rtDW->b_A_tmp[11] = 0.0F;
  rtDW->b_A_tmp[19] = 0.0F;
  rtDW->b_A_tmp[27] = rtU->Ts_times_ZB_over_Ly;
  rtDW->b_A_tmp[4] = 0.0F;
  rtDW->b_A_tmp[5] = 0.0F;
  rtDW->b_A_tmp[6] = 0.0F;
  rtDW->b_A_tmp[7] = 0.0F;
  rtDW->b_A_tmp[12] = 0.0F;
  rtDW->b_A_tmp[13] = 0.0F;
  rtDW->b_A_tmp[14] = 0.0F;
  rtDW->b_A_tmp[15] = 0.0F;
  rtDW->b_A_tmp[20] = 0.0F;
  rtDW->b_A_tmp[21] = 0.0F;
  rtDW->b_A_tmp[22] = 0.0F;
  rtDW->b_A_tmp[23] = 0.0F;
  rtDW->b_A_tmp[28] = 0.0F;
  rtDW->b_A_tmp[29] = 0.0F;
  rtDW->b_A_tmp[30] = 0.0F;
  rtDW->b_A_tmp[31] = 0.0F;
  rtDW->rtb_d_xy_obs_idx_0 = rtDW->v_t0[0];
  rtDW->rtb_d_dq_obs_idx_0 = rtDW->v_t0[1];
  rtDW->rtb_v_t0_idx_2 = rtDW->v_t0[2];
  rtDW->rtb_v_t0_idx_3 = rtDW->v_t0[3];

  /* '<S3>:1:85' P_p = A*P_e*A'+Q; */
  for (rtDW->d_j = 0; rtDW->d_j < 8; rtDW->d_j++) {
    rtDW->A_b[rtDW->d_j] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->ix = rtDW->iy << 3;
      rtDW->sector_ref = rtDW->ix + rtDW->d_j;
      rtDW->A_l[rtDW->sector_ref] = 0.0F;
      for (rtDW->i = 0; rtDW->i < 8; rtDW->i++) {
        rtDW->A_l[rtDW->sector_ref] += rtDW->A[(rtDW->i << 3) + rtDW->d_j] *
          rtDW->P_e[rtDW->ix + rtDW->i];
      }

      rtDW->A_o[rtDW->sector_ref] = 0.0F;
      rtDW->A_b[rtDW->d_j] += rtDW->A[rtDW->sector_ref] * rtDW->x_e[rtDW->iy];
    }

    rtDW->x_p[rtDW->d_j] = (rtDW->A_b[rtDW->d_j] + (rtDW->b_A_tmp[rtDW->d_j + 24]
      * rtDW->rtb_v_t0_idx_3 + (rtDW->b_A_tmp[rtDW->d_j + 16] *
      rtDW->rtb_v_t0_idx_2 + (rtDW->b_A_tmp[rtDW->d_j + 8] *
      rtDW->rtb_d_dq_obs_idx_0 + rtDW->b_A_tmp[rtDW->d_j] *
      rtDW->rtb_d_xy_obs_idx_0)))) + rtDW->d_m[rtDW->d_j];
    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      for (rtDW->i = 0; rtDW->i < 8; rtDW->i++) {
        rtDW->sector_ref = rtDW->i << 3;
        rtDW->ix = (rtDW->iy << 3) + rtDW->d_j;
        rtDW->A_o[rtDW->ix] += rtDW->A_l[rtDW->sector_ref + rtDW->d_j] * rtDW->
          A[rtDW->sector_ref + rtDW->iy];
      }
    }
  }

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/kalman_Q1'
   *  Inport: '<Root>/kalman_Q2'
   */
  rtDW->A_l[0] = rtU->kalman_Q1;
  rtDW->A_l[8] = 0.0F;
  rtDW->A_l[16] = 0.0F;
  rtDW->A_l[24] = 0.0F;
  rtDW->A_l[32] = 0.0F;
  rtDW->A_l[40] = 0.0F;
  rtDW->A_l[48] = 0.0F;
  rtDW->A_l[56] = 0.0F;
  rtDW->A_l[1] = 0.0F;
  rtDW->A_l[9] = rtU->kalman_Q1;
  rtDW->A_l[17] = 0.0F;
  rtDW->A_l[25] = 0.0F;
  rtDW->A_l[33] = 0.0F;
  rtDW->A_l[41] = 0.0F;
  rtDW->A_l[49] = 0.0F;
  rtDW->A_l[57] = 0.0F;
  rtDW->A_l[2] = 0.0F;
  rtDW->A_l[10] = 0.0F;
  rtDW->A_l[18] = rtU->kalman_Q1;
  rtDW->A_l[26] = 0.0F;
  rtDW->A_l[34] = 0.0F;
  rtDW->A_l[42] = 0.0F;
  rtDW->A_l[50] = 0.0F;
  rtDW->A_l[58] = 0.0F;
  rtDW->A_l[3] = 0.0F;
  rtDW->A_l[11] = 0.0F;
  rtDW->A_l[19] = 0.0F;
  rtDW->A_l[27] = rtU->kalman_Q1;
  rtDW->A_l[35] = 0.0F;
  rtDW->A_l[43] = 0.0F;
  rtDW->A_l[51] = 0.0F;
  rtDW->A_l[59] = 0.0F;
  rtDW->A_l[4] = 0.0F;
  rtDW->A_l[12] = 0.0F;
  rtDW->A_l[20] = 0.0F;
  rtDW->A_l[28] = 0.0F;
  rtDW->A_l[36] = rtU->kalman_Q2;
  rtDW->A_l[44] = 0.0F;
  rtDW->A_l[52] = 0.0F;
  rtDW->A_l[60] = 0.0F;
  rtDW->A_l[5] = 0.0F;
  rtDW->A_l[13] = 0.0F;
  rtDW->A_l[21] = 0.0F;
  rtDW->A_l[29] = 0.0F;
  rtDW->A_l[37] = 0.0F;
  rtDW->A_l[45] = rtU->kalman_Q2;
  rtDW->A_l[53] = 0.0F;
  rtDW->A_l[61] = 0.0F;
  rtDW->A_l[6] = 0.0F;
  rtDW->A_l[14] = 0.0F;
  rtDW->A_l[22] = 0.0F;
  rtDW->A_l[30] = 0.0F;
  rtDW->A_l[38] = 0.0F;
  rtDW->A_l[46] = 0.0F;
  rtDW->A_l[54] = rtU->kalman_Q2;
  rtDW->A_l[62] = 0.0F;
  rtDW->A_l[7] = 0.0F;
  rtDW->A_l[15] = 0.0F;
  rtDW->A_l[23] = 0.0F;
  rtDW->A_l[31] = 0.0F;
  rtDW->A_l[39] = 0.0F;
  rtDW->A_l[47] = 0.0F;
  rtDW->A_l[55] = 0.0F;
  rtDW->A_l[63] = rtU->kalman_Q2;

  /* MATLAB Function: '<S1>/Observer' */
  for (rtDW->d_j = 0; rtDW->d_j < 64; rtDW->d_j++) {
    rtDW->A[rtDW->d_j] = rtDW->A_o[rtDW->d_j] + rtDW->A_l[rtDW->d_j];
  }

  /* '<S3>:1:87' K = P_p*C'/(C*P_p*C'+R); */
  for (rtDW->d_j = 0; rtDW->d_j < 32; rtDW->d_j++) {
    rtDW->b_A_tmp_p[rtDW->d_j] = l[rtDW->d_j];
    rtDW->b_A_tmp_e[rtDW->d_j] = m[rtDW->d_j];
  }

  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->sector_ref = rtDW->d_j + (rtDW->iy << 2);
      rtDW->b_A_tmp[rtDW->sector_ref] = 0.0F;
      for (rtDW->i = 0; rtDW->i < 8; rtDW->i++) {
        rtDW->b_A_tmp[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_e[(rtDW->i <<
          2) + rtDW->d_j] * rtDW->A[(rtDW->iy << 3) + rtDW->i];
      }
    }

    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->sector_ref = rtDW->d_j + (rtDW->iy << 2);
      rtDW->B_n[rtDW->sector_ref] = 0.0F;
      for (rtDW->i = 0; rtDW->i < 8; rtDW->i++) {
        rtDW->B_n[rtDW->sector_ref] += rtDW->b_A_tmp[(rtDW->i << 2) + rtDW->d_j]
          * (real32_T)rtDW->b_A_tmp_p[(rtDW->iy << 3) + rtDW->i];
      }
    }
  }

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/kalman_R'
   */
  rtDW->fv[0] = rtU->kalman_R;
  rtDW->fv[4] = 0.0F;
  rtDW->fv[8] = 0.0F;
  rtDW->fv[12] = 0.0F;
  rtDW->fv[1] = 0.0F;
  rtDW->fv[5] = rtU->kalman_R;
  rtDW->fv[9] = 0.0F;
  rtDW->fv[13] = 0.0F;
  rtDW->fv[2] = 0.0F;
  rtDW->fv[6] = 0.0F;
  rtDW->fv[10] = rtU->kalman_R;
  rtDW->fv[14] = 0.0F;
  rtDW->fv[3] = 0.0F;
  rtDW->fv[7] = 0.0F;
  rtDW->fv[11] = 0.0F;
  rtDW->fv[15] = rtU->kalman_R;

  /* MATLAB Function: '<S1>/Observer' incorporates:
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/i_xy_pu'
   */
  for (rtDW->d_j = 0; rtDW->d_j < 16; rtDW->d_j++) {
    rtDW->A_minus_I[rtDW->d_j] = rtDW->B_n[rtDW->d_j] + rtDW->fv[rtDW->d_j];
  }

  rtDW->ipiv[0] = 1;
  rtDW->ipiv[1] = 2;
  rtDW->ipiv[2] = 3;
  rtDW->ipiv[3] = 4;
  for (rtDW->d_j = 0; rtDW->d_j < 3; rtDW->d_j++) {
    rtDW->i = rtDW->d_j * 5;
    rtDW->iy = 0;
    rtDW->ix = rtDW->i;
    rtDW->w6theta_el = fabsf(rtDW->A_minus_I[rtDW->i]);
    rtDW->kBcol = 2;
    while (rtDW->kBcol <= 4 - rtDW->d_j) {
      rtDW->ix++;
      rtDW->SinCos1_o2 = fabsf(rtDW->A_minus_I[rtDW->ix]);
      if (rtDW->SinCos1_o2 > rtDW->w6theta_el) {
        rtDW->iy = rtDW->kBcol - 1;
        rtDW->w6theta_el = rtDW->SinCos1_o2;
      }

      rtDW->kBcol++;
    }

    if (rtDW->A_minus_I[rtDW->i + rtDW->iy] != 0.0F) {
      if (rtDW->iy != 0) {
        rtDW->iy += rtDW->d_j;
        rtDW->ipiv[rtDW->d_j] = (int8_T)(rtDW->iy + 1);
        rtDW->w6theta_el = rtDW->A_minus_I[rtDW->d_j];
        rtDW->A_minus_I[rtDW->d_j] = rtDW->A_minus_I[rtDW->iy];
        rtDW->A_minus_I[rtDW->iy] = rtDW->w6theta_el;
        rtDW->w6theta_el = rtDW->A_minus_I[rtDW->d_j + 4];
        rtDW->A_minus_I[rtDW->d_j + 4] = rtDW->A_minus_I[rtDW->iy + 4];
        rtDW->A_minus_I[rtDW->iy + 4] = rtDW->w6theta_el;
        rtDW->w6theta_el = rtDW->A_minus_I[rtDW->d_j + 8];
        rtDW->A_minus_I[rtDW->d_j + 8] = rtDW->A_minus_I[rtDW->iy + 8];
        rtDW->A_minus_I[rtDW->iy + 8] = rtDW->w6theta_el;
        rtDW->w6theta_el = rtDW->A_minus_I[rtDW->d_j + 12];
        rtDW->A_minus_I[rtDW->d_j + 12] = rtDW->A_minus_I[rtDW->iy + 12];
        rtDW->A_minus_I[rtDW->iy + 12] = rtDW->w6theta_el;
      }

      rtDW->iy = (rtDW->i - rtDW->d_j) + 4;
      rtDW->ix = rtDW->i + 1;
      while (rtDW->ix + 1 <= rtDW->iy) {
        rtDW->A_minus_I[rtDW->ix] /= rtDW->A_minus_I[rtDW->i];
        rtDW->ix++;
      }
    }

    rtDW->iy = rtDW->i;
    rtDW->ix = rtDW->i + 4;
    rtDW->kBcol = 0;
    while (rtDW->kBcol <= 2 - rtDW->d_j) {
      if (rtDW->A_minus_I[rtDW->ix] != 0.0F) {
        rtDW->w6theta_el = -rtDW->A_minus_I[rtDW->ix];
        rtDW->c_ix = rtDW->i + 1;
        rtDW->sector_ref = (rtDW->iy - rtDW->d_j) + 8;
        rtDW->ijA = rtDW->iy + 5;
        while (rtDW->ijA + 1 <= rtDW->sector_ref) {
          rtDW->A_minus_I[rtDW->ijA] += rtDW->A_minus_I[rtDW->c_ix] *
            rtDW->w6theta_el;
          rtDW->c_ix++;
          rtDW->ijA++;
        }
      }

      rtDW->ix += 4;
      rtDW->iy += 4;
      rtDW->kBcol++;
    }
  }

  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->sector_ref = rtDW->d_j << 3;
      rtDW->ix = rtDW->iy + rtDW->sector_ref;
      rtDW->b_A_tmp[rtDW->ix] = 0.0F;
      for (rtDW->i = 0; rtDW->i < 8; rtDW->i++) {
        rtDW->b_A_tmp[rtDW->ix] += rtDW->A[(rtDW->i << 3) + rtDW->iy] *
          (real32_T)rtDW->b_A_tmp_p[rtDW->sector_ref + rtDW->i];
      }
    }
  }

  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    rtDW->i = rtDW->d_j << 3;
    rtDW->iy = rtDW->d_j << 2;
    rtDW->ix = 0;
    while (rtDW->ix <= rtDW->d_j - 1) {
      rtDW->kBcol = rtDW->ix << 3;
      rtDW->w6theta_el = rtDW->A_minus_I[rtDW->ix + rtDW->iy];
      if (rtDW->w6theta_el != 0.0F) {
        for (rtDW->c_ix = 0; rtDW->c_ix < 8; rtDW->c_ix++) {
          rtDW->sector_ref = rtDW->c_ix + rtDW->i;
          rtDW->b_A_tmp[rtDW->sector_ref] -= rtDW->w6theta_el * rtDW->
            b_A_tmp[rtDW->c_ix + rtDW->kBcol];
        }
      }

      rtDW->ix++;
    }

    rtDW->w6theta_el = 1.0F / rtDW->A_minus_I[rtDW->d_j + rtDW->iy];
    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->sector_ref = rtDW->iy + rtDW->i;
      rtDW->b_A_tmp[rtDW->sector_ref] *= rtDW->w6theta_el;
    }
  }

  for (rtDW->d_j = 3; rtDW->d_j >= 0; rtDW->d_j--) {
    rtDW->i = rtDW->d_j << 3;
    rtDW->iy = (rtDW->d_j << 2) - 1;
    rtDW->ix = rtDW->d_j + 2;
    while (rtDW->ix < 5) {
      rtDW->kBcol = (rtDW->ix - 1) << 3;
      rtDW->w6theta_el = rtDW->A_minus_I[rtDW->ix + rtDW->iy];
      if (rtDW->w6theta_el != 0.0F) {
        for (rtDW->c_ix = 0; rtDW->c_ix < 8; rtDW->c_ix++) {
          rtDW->sector_ref = rtDW->c_ix + rtDW->i;
          rtDW->b_A_tmp[rtDW->sector_ref] -= rtDW->w6theta_el * rtDW->
            b_A_tmp[rtDW->c_ix + rtDW->kBcol];
        }
      }

      rtDW->ix++;
    }
  }

  for (rtDW->d_j = 2; rtDW->d_j >= 0; rtDW->d_j--) {
    ipiv = rtDW->ipiv[rtDW->d_j];
    if (rtDW->d_j + 1 != ipiv) {
      for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
        rtDW->i = (rtDW->d_j << 3) + rtDW->iy;
        rtDW->w6theta_el = rtDW->b_A_tmp[rtDW->i];
        rtDW->sector_ref = ((ipiv - 1) << 3) + rtDW->iy;
        rtDW->b_A_tmp[rtDW->i] = rtDW->b_A_tmp[rtDW->sector_ref];
        rtDW->b_A_tmp[rtDW->sector_ref] = rtDW->w6theta_el;
      }
    }
  }

  /* '<S3>:1:89' y=[i_d; i_q; i_x; i_y]; */
  /* '<S3>:1:91' x_e = x_p+K*(y-C*x_p); */
  rtDW->m6[0] = rtU->i_dq_pu[0];
  rtDW->m6[1] = rtU->i_dq_pu[1];
  rtDW->m6[2] = rtU->i_xy_pu[0];
  rtDW->m6[3] = rtU->i_xy_pu[1];
  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    rtDW->v_t0[rtDW->d_j] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->v_t0[rtDW->d_j] += (real32_T)rtDW->b_A_tmp_e[(rtDW->iy << 2) +
        rtDW->d_j] * rtDW->x_p[rtDW->iy];
    }

    rtDW->m2[rtDW->d_j] = rtDW->m6[rtDW->d_j] - rtDW->v_t0[rtDW->d_j];
  }

  /* '<S3>:1:93' P_e = P_p-K*C*P_p; */
  for (rtDW->d_j = 0; rtDW->d_j < 8; rtDW->d_j++) {
    rtDW->rtb_d_xy_obs_idx_0 = rtDW->b_A_tmp[rtDW->d_j + 8];
    rtDW->rtb_d_dq_obs_idx_0 = rtDW->b_A_tmp[rtDW->d_j + 16];
    rtDW->rtb_v_t0_idx_2 = rtDW->b_A_tmp[rtDW->d_j + 24];
    rtDW->x_e[rtDW->d_j] = (((rtDW->rtb_d_xy_obs_idx_0 * rtDW->m2[1] +
      rtDW->b_A_tmp[rtDW->d_j] * rtDW->m2[0]) + rtDW->rtb_d_dq_obs_idx_0 *
      rtDW->m2[2]) + rtDW->rtb_v_t0_idx_2 * rtDW->m2[3]) + rtDW->x_p[rtDW->d_j];
    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->sector_ref = rtDW->d_j + (rtDW->iy << 3);
      rtDW->A_o[rtDW->sector_ref] = 0.0F;
      rtDW->ix = rtDW->iy << 2;
      rtDW->A_o[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_e[rtDW->ix] *
        rtDW->b_A_tmp[rtDW->d_j];
      rtDW->A_o[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_e[rtDW->ix + 1] *
        rtDW->rtb_d_xy_obs_idx_0;
      rtDW->A_o[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_e[rtDW->ix + 2] *
        rtDW->rtb_d_dq_obs_idx_0;
      rtDW->A_o[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_e[rtDW->ix + 3] *
        rtDW->rtb_v_t0_idx_2;
    }

    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->w6theta_el = 0.0F;
      for (rtDW->i = 0; rtDW->i < 8; rtDW->i++) {
        rtDW->w6theta_el += rtDW->A_o[(rtDW->i << 3) + rtDW->d_j] * rtDW->A
          [(rtDW->iy << 3) + rtDW->i];
      }

      rtDW->sector_ref = (rtDW->iy << 3) + rtDW->d_j;
      rtDW->P_e[rtDW->sector_ref] = rtDW->A[rtDW->sector_ref] - rtDW->w6theta_el;
    }
  }

  /* MATLAB Function: '<S1>/delay_compensation_currents' incorporates:
   *  MATLAB Function: '<S1>/Observer'
   *  Switch: '<S1>/Switch1'
   */
  /* '<S3>:1:95' i_dq_obs(1) = x_e(1); */
  /* '<S3>:1:96' i_dq_obs(2) = x_e(2); */
  /* '<S3>:1:97' i_xy_obs(1) = x_e(3); */
  /* '<S3>:1:98' i_xy_obs(2) = x_e(4); */
  /* '<S3>:1:99' d_dq_obs(1) = x_e(5); */
  /* '<S3>:1:100' d_dq_obs(2) = x_e(6); */
  /* '<S3>:1:101' d_xy_obs(1) = x_e(7); */
  /* '<S3>:1:102' d_xy_obs(2) = x_e(8); */
  rtDW->m1[2] = rtDW->x_e[2];

  /* Switch: '<S1>/Switch' incorporates:
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/kalman_off_on'
   *  MATLAB Function: '<S1>/Observer'
   *  Switch: '<S1>/Switch1'
   */
  rtDW->rtb_i_dq_obs_idx_0 = rtDW->x_e[0];
  if (!rtU->kalman_off_on) {
    rtDW->rtb_i_dq_obs_idx_0 = rtU->i_dq_pu[0];

    /* MATLAB Function: '<S1>/delay_compensation_currents' incorporates:
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/i_xy_pu'
     */
    rtDW->m1[2] = rtU->i_xy_pu[0];
  }

  /* MATLAB Function: '<S1>/delay_compensation_currents' incorporates:
   *  MATLAB Function: '<S1>/Observer'
   */
  rtDW->m1[3] = rtDW->x_e[3];

  /* MATLAB Function: '<S1>/Observer' */
  rtDW->rtb_v_1_idx_pu_idx_1 = rtDW->x_e[1];

  /* Switch: '<S1>/Switch' incorporates:
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/kalman_off_on'
   *  Switch: '<S1>/Switch1'
   */
  if (!rtU->kalman_off_on) {
    rtDW->rtb_v_1_idx_pu_idx_1 = rtU->i_dq_pu[1];

    /* MATLAB Function: '<S1>/delay_compensation_currents' incorporates:
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/i_xy_pu'
     */
    rtDW->m1[3] = rtU->i_xy_pu[1];
  }

  /* Delay: '<S1>/Delay1' */
  if (rtDW->icLoad_f) {
    for (rtDW->i = 0; rtDW->i < 7; rtDW->i++) {
      rtDW->Delay1_DSTATE[rtDW->i] = 0.14F;
    }
  }

  /* Delay: '<S1>/Delay3' */
  if (rtDW->icLoad_l) {
    rtDW->Delay3_DSTATE[0] = 0.0F;
    rtDW->Delay3_DSTATE[1] = 0.0F;
    rtDW->Delay3_DSTATE[2] = 0.0F;
    rtDW->Delay3_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay4' */
  if (rtDW->icLoad_a) {
    rtDW->Delay4_DSTATE[0] = 0.0F;
    rtDW->Delay4_DSTATE[1] = 0.0F;
    rtDW->Delay4_DSTATE[2] = 0.0F;
    rtDW->Delay4_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay5' */
  if (rtDW->icLoad_f4) {
    rtDW->Delay5_DSTATE[0] = 0.0F;
    rtDW->Delay5_DSTATE[1] = 0.0F;
    rtDW->Delay5_DSTATE[2] = 0.0F;
    rtDW->Delay5_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay6' */
  if (rtDW->icLoad_ag) {
    rtDW->Delay6_DSTATE[0] = 0.0F;
    rtDW->Delay6_DSTATE[1] = 0.0F;
    rtDW->Delay6_DSTATE[2] = 0.0F;
    rtDW->Delay6_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay7' */
  if (rtDW->icLoad_i) {
    rtDW->Delay7_DSTATE[0] = 0.0F;
    rtDW->Delay7_DSTATE[1] = 0.0F;
    rtDW->Delay7_DSTATE[2] = 0.0F;
    rtDW->Delay7_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay8' */
  if (rtDW->icLoad_ik) {
    rtDW->Delay8_DSTATE[0] = 0.0F;
    rtDW->Delay8_DSTATE[1] = 0.0F;
    rtDW->Delay8_DSTATE[2] = 0.0F;
    rtDW->Delay8_DSTATE[3] = 0.0F;
  }

  /* MATLAB Function: '<S1>/delay_compensation_currents' incorporates:
   *  Delay: '<S1>/Delay1'
   *  Delay: '<S1>/Delay3'
   *  Delay: '<S1>/Delay4'
   *  Delay: '<S1>/Delay5'
   *  Delay: '<S1>/Delay6'
   *  Delay: '<S1>/Delay7'
   *  Delay: '<S1>/Delay8'
   *  Inport: '<Root>/Ts_over_tB'
   */
  /* MATLAB Function 'uz_codegen/delay_compensation_currents': '<S8>:1' */
  /* '<S8>:1:3' i_t0 = single([id0 iq0 ix0 iy0])'; */
  /* '<S8>:1:4' m_opt = single([m0, m1, m2, m3, m4, m5, m0]); */
  /* delay compensation */
  /* '<S8>:1:7' i_t0_delay_comp = single(i_t0 + m_opt * t_opt * Ts_over_tB); */
  rtDW->r[0] = rtDW->Delay3_DSTATE[0];
  rtDW->r[4] = rtDW->Delay4_DSTATE[0];
  rtDW->r[8] = rtDW->Delay5_DSTATE[0];
  rtDW->r[12] = rtDW->Delay6_DSTATE[0];
  rtDW->r[16] = rtDW->Delay7_DSTATE[0];
  rtDW->r[20] = rtDW->Delay8_DSTATE[0];
  rtDW->r[24] = rtDW->Delay3_DSTATE[0];
  rtDW->r[1] = rtDW->Delay3_DSTATE[1];
  rtDW->r[5] = rtDW->Delay4_DSTATE[1];
  rtDW->r[9] = rtDW->Delay5_DSTATE[1];
  rtDW->r[13] = rtDW->Delay6_DSTATE[1];
  rtDW->r[17] = rtDW->Delay7_DSTATE[1];
  rtDW->r[21] = rtDW->Delay8_DSTATE[1];
  rtDW->r[25] = rtDW->Delay3_DSTATE[1];
  rtDW->r[2] = rtDW->Delay3_DSTATE[2];
  rtDW->r[6] = rtDW->Delay4_DSTATE[2];
  rtDW->r[10] = rtDW->Delay5_DSTATE[2];
  rtDW->r[14] = rtDW->Delay6_DSTATE[2];
  rtDW->r[18] = rtDW->Delay7_DSTATE[2];
  rtDW->r[22] = rtDW->Delay8_DSTATE[2];
  rtDW->r[26] = rtDW->Delay3_DSTATE[2];
  rtDW->r[3] = rtDW->Delay3_DSTATE[3];
  rtDW->r[7] = rtDW->Delay4_DSTATE[3];
  rtDW->r[11] = rtDW->Delay5_DSTATE[3];
  rtDW->r[15] = rtDW->Delay6_DSTATE[3];
  rtDW->r[19] = rtDW->Delay7_DSTATE[3];
  rtDW->r[23] = rtDW->Delay8_DSTATE[3];
  rtDW->r[27] = rtDW->Delay3_DSTATE[3];
  rtDW->m1[0] = rtDW->rtb_i_dq_obs_idx_0;
  rtDW->m1[1] = rtDW->rtb_v_1_idx_pu_idx_1;
  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    rtDW->m6[rtDW->d_j] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 7; rtDW->iy++) {
      rtDW->m6[rtDW->d_j] += rtDW->r[(rtDW->iy << 2) + rtDW->d_j] *
        rtDW->Delay1_DSTATE[rtDW->iy];
    }

    rtDW->v_t0[rtDW->d_j] = rtDW->m6[rtDW->d_j] * rtU->Ts_over_tB + rtDW->
      m1[rtDW->d_j];
  }

  /* Switch: '<S1>/Switch3' incorporates:
   *  MATLAB Function: '<S1>/Observer'
   */
  rtDW->rtb_d_xy_obs_idx_0 = rtDW->x_e[6];

  /* Switch: '<S1>/Switch2' incorporates:
   *  MATLAB Function: '<S1>/Observer'
   */
  rtDW->rtb_d_dq_obs_idx_0 = rtDW->x_e[4];

  /* MATLAB Function: '<S1>/Observer' */
  rtDW->rtb_v_t0_idx_2 = rtDW->x_e[7];
  rtDW->rtb_v_t0_idx_3 = rtDW->x_e[5];

  /* Switch: '<S1>/Switch2' incorporates:
   *  Inport: '<Root>/kalman_off_on'
   *  Switch: '<S1>/Switch3'
   */
  if (!rtU->kalman_off_on) {
    rtDW->rtb_d_dq_obs_idx_0 = 0.0F;
    rtDW->rtb_d_xy_obs_idx_0 = 0.0F;
    rtDW->rtb_v_t0_idx_3 = 0.0F;
    rtDW->rtb_v_t0_idx_2 = 0.0F;
  }

  /* Trigonometry: '<S1>/SinCos1' incorporates:
   *  Inport: '<Root>/theta_el_pos'
   */
  rtDW->w6theta_el = sinf(rtU->theta_el_pos);
  rtDW->SinCos1_o2 = cosf(rtU->theta_el_pos);

  /* Trigonometry: '<S1>/SinCos2' incorporates:
   *  Inport: '<Root>/theta_el_neg'
   */
  rtDW->SinCos2_o1 = sinf(rtU->theta_el_neg);
  rtDW->SinCos2_o2 = cosf(rtU->theta_el_neg);

  /* MATLAB Function: '<S1>/seq_2_act_sw_all' */
  for (rtDW->i = 0; rtDW->i < 24; rtDW->i++) {
    rtDW->act_sw_1[rtDW->i] = tmp[rtDW->i];
    rtDW->act_sw_2[rtDW->i] = tmp_0[rtDW->i];
    rtDW->act_sw_3[rtDW->i] = tmp_1[rtDW->i];
    rtDW->act_sw_4[rtDW->i] = tmp_2[rtDW->i];
    rtDW->act_sw_5[rtDW->i] = tmp_3[rtDW->i];
  }

  /* End of MATLAB Function: '<S1>/seq_2_act_sw_all' */

  /* MATLAB Function: '<S1>/deadbeat_solution' incorporates:
   *  Inport: '<Root>/Ld_over_LB'
   *  Inport: '<Root>/Lq_over_LB'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/i_d_ref_pu'
   *  Inport: '<Root>/i_q_ref_pu'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/psi_pm_over_psiB'
   *  Inport: '<Root>/theta_el_pos'
   */
  /* MATLAB Function 'uz_codegen/seq_2_act_sw_all': '<S11>:1' */
  /* '<S11>:1:3' act_sw_1 = single(zeros(24,1)); */
  /* '<S11>:1:4' act_sw_2 = single(zeros(24,1)); */
  /* '<S11>:1:5' act_sw_3 = single(zeros(24,1)); */
  /* '<S11>:1:6' act_sw_4 = single(zeros(24,1)); */
  /* '<S11>:1:7' act_sw_5 = single(zeros(24,1)); */
  /*  row=sequence, columns=active switch postion               */
  /* '<S11>:1:10' seq_table_svm24 = single([   8, 9,41,43,47; */
  /* '<S11>:1:11'                              1, 9,11,43,59; */
  /* '<S11>:1:12'                              1, 9,11,27,59; */
  /* '<S11>:1:13'                              8, 9,11,27,31; */
  /* '<S11>:1:14'                              8,10,11,27,31; */
  /* '<S11>:1:15'                              2,10,26,27,59; */
  /* '<S11>:1:16'                              2,18,26,27,59; */
  /* '<S11>:1:17'                             16,18,26,27,31; */
  /* '<S11>:1:18'                             16,18,26,30,31; */
  /* '<S11>:1:19'                              2,18,22,30,62; */
  /* '<S11>:1:20'                              2,18,22,54,62; */
  /* '<S11>:1:21'                             16,18,22,54,55; */
  /* '<S11>:1:22'                             16,20,22,54,55; */
  /* '<S11>:1:23'                              4,20,52,54,62; */
  /* '<S11>:1:24'                              4,36,52,54,62; */
  /* '<S11>:1:25'                             32,36,52,54,55; */
  /* '<S11>:1:26'                             32,36,52,53,55; */
  /* '<S11>:1:27'                              4,36,37,53,61; */
  /* '<S11>:1:28'                              4,36,37,45,61; */
  /* '<S11>:1:29'                             32,36,37,45,47; */
  /* '<S11>:1:30'                             32,33,37,45,47; */
  /* '<S11>:1:31'                              1,33,41,45,61; */
  /* '<S11>:1:32'                              1, 9,41,45,61; */
  /* '<S11>:1:33'                              8, 9,41,45,47]); */
  /* '<S11>:1:35' act_sw_1 = seq_table_svm24(:,1); */
  /* '<S11>:1:36' act_sw_2 = seq_table_svm24(:,2); */
  /* '<S11>:1:37' act_sw_3 = seq_table_svm24(:,3); */
  /* '<S11>:1:38' act_sw_4 = seq_table_svm24(:,4); */
  /* '<S11>:1:39' act_sw_5 = seq_table_svm24(:,5); */
  /* MATLAB Function 'uz_codegen/deadbeat_solution': '<S7>:1' */
  /* '<S7>:1:3' i_d_pu = i_d_pu + single(d_dq_obs(1)); */
  rtDW->rtb_i_dq_obs_idx_0 += rtDW->rtb_d_dq_obs_idx_0;

  /* '<S7>:1:4' i_q_pu = i_q_pu + single(d_dq_obs(2)); */
  rtDW->rtb_v_1_idx_pu_idx_1 += rtDW->rtb_v_t0_idx_3;

  /* '<S7>:1:6' v_d_ref_pu = (i_d_ref_pu-i_d_pu)/(Ts_times_ZB_over_Ld) + i_d_pu*Rs_over_ZB - omega_el*Lq_over_LB*i_q_pu; */
  /* '<S7>:1:7' v_q_ref_pu = (i_q_ref_pu-i_q_pu)/(Ts_times_ZB_over_Lq) + i_q_pu*Rs_over_ZB + omega_el*(Ld_over_LB*i_d_pu+psi_pm_over_psiB); */
  /*  v_x_ref_pu = (i_x_ref_pu-i_x_pu)/(Ts_times_ZB_over_Lx) + i_x_pu*Rs_over_ZB; */
  /*  v_y_ref_pu = (i_y_ref_pu-i_y_pu)/(Ts_times_ZB_over_Ly) + i_y_pu*Rs_over_ZB; */
  /* '<S7>:1:10' v_x_ref_pu = single(0.0); */
  /* '<S7>:1:11' v_y_ref_pu = single(0.0); */
  /* '<S7>:1:13' angle_ref = mod(atan2(v_q_ref_pu, v_d_ref_pu) + theta_el, 2*pi); */
  rtDW->rtb_i_dq_obs_idx_0 = atan2f(((rtU->i_q_ref_pu -
    rtDW->rtb_v_1_idx_pu_idx_1) / rtU->Ts_times_ZB_over_Lq +
    rtDW->rtb_v_1_idx_pu_idx_1 * rtU->Rs_over_ZB) + (rtU->Ld_over_LB *
    rtDW->rtb_i_dq_obs_idx_0 + rtU->psi_pm_over_psiB) * rtU->omega_el_pu,
    ((rtU->i_d_ref_pu - rtDW->rtb_i_dq_obs_idx_0) / rtU->Ts_times_ZB_over_Ld +
     rtDW->rtb_i_dq_obs_idx_0 * rtU->Rs_over_ZB) - rtU->omega_el_pu *
    rtU->Lq_over_LB * rtDW->rtb_v_1_idx_pu_idx_1) + rtU->theta_el_pos;
  if (rtDW->rtb_i_dq_obs_idx_0 == 0.0F) {
    rtDW->rtb_v_1_idx_pu_idx_1 = 0.0F;
  } else {
    rtDW->rtb_v_1_idx_pu_idx_1 = fmodf(rtDW->rtb_i_dq_obs_idx_0, 6.28318548F);
    rEQ0 = (rtDW->rtb_v_1_idx_pu_idx_1 == 0.0F);
    if (!rEQ0) {
      rtDW->q = fabsf(rtDW->rtb_i_dq_obs_idx_0 / 6.28318548F);
      rEQ0 = (fabsf(rtDW->q - floorf(rtDW->q + 0.5F)) <= 1.1920929E-7F * rtDW->q);
    }

    if (rEQ0) {
      rtDW->rtb_v_1_idx_pu_idx_1 = 0.0F;
    } else if (rtDW->rtb_i_dq_obs_idx_0 < 0.0F) {
      rtDW->rtb_v_1_idx_pu_idx_1 += 6.28318548F;
    }
  }

  /* '<S7>:1:15' sector_ref = 0.0; */
  rtDW->sector_ref = 0;

  /* '<S7>:1:16' if (angle_ref >= 0.0 && angle_ref < pi/180*15) */
  if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 0.0F) && (rtDW->rtb_v_1_idx_pu_idx_1 <
       0.26179938779914941)) {
    /* '<S7>:1:17' sector_ref = 1.0; */
    rtDW->sector_ref = 1;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 0.26179938779914941) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 0.52359877559829882)) {
    /* '<S7>:1:18' elseif (angle_ref >= pi/180*15 && angle_ref < pi/180*30) */
    /* '<S7>:1:19' sector_ref = 2.0; */
    rtDW->sector_ref = 2;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 0.52359877559829882) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 0.78539816339744828)) {
    /* '<S7>:1:20' elseif (angle_ref >= pi/180*30 && angle_ref < pi/180*45) */
    /* '<S7>:1:21' sector_ref = 3.0; */
    rtDW->sector_ref = 3;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 0.78539816339744828) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 1.0471975511965976)) {
    /* '<S7>:1:22' elseif (angle_ref >= pi/180*45 && angle_ref < pi/180*60) */
    /* '<S7>:1:23' sector_ref = 4.0; */
    rtDW->sector_ref = 4;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 1.0471975511965976) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 1.3089969389957472)) {
    /* '<S7>:1:24' elseif (angle_ref >= pi/180*60 && angle_ref < pi/180*75) */
    /* '<S7>:1:25' sector_ref = 5.0; */
    rtDW->sector_ref = 5;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 1.3089969389957472) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 1.5707963267948966)) {
    /* '<S7>:1:26' elseif (angle_ref >= pi/180*75 && angle_ref < pi/180*90) */
    /* '<S7>:1:27' sector_ref = 6.0; */
    rtDW->sector_ref = 6;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 1.5707963267948966) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 1.8325957145940461)) {
    /* '<S7>:1:28' elseif (angle_ref >= pi/180*90 && angle_ref < pi/180*105) */
    /* '<S7>:1:29' sector_ref = 7.0; */
    rtDW->sector_ref = 7;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 1.8325957145940461) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 2.0943951023931953)) {
    /* '<S7>:1:30' elseif (angle_ref >= pi/180*105 && angle_ref < pi/180*120) */
    /* '<S7>:1:31' sector_ref = 8.0; */
    rtDW->sector_ref = 8;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 2.0943951023931953) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 2.3561944901923448)) {
    /* '<S7>:1:32' elseif (angle_ref >= pi/180*120 && angle_ref < pi/180*135) */
    /* '<S7>:1:33' sector_ref = 9.0; */
    rtDW->sector_ref = 9;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 2.3561944901923448) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 2.6179938779914944)) {
    /* '<S7>:1:34' elseif (angle_ref >= pi/180*135 && angle_ref < pi/180*150) */
    /* '<S7>:1:35' sector_ref = 10.0; */
    rtDW->sector_ref = 10;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 2.6179938779914944) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 2.8797932657906435)) {
    /* '<S7>:1:36' elseif (angle_ref >= pi/180*150 && angle_ref < pi/180*165) */
    /* '<S7>:1:37' sector_ref = 11.0; */
    rtDW->sector_ref = 11;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 2.8797932657906435) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 3.1415926535897931)) {
    /* '<S7>:1:38' elseif (angle_ref >= pi/180*165 && angle_ref < pi/180*180) */
    /* '<S7>:1:39' sector_ref = 12.0; */
    rtDW->sector_ref = 12;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 3.1415926535897931) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 3.4033920413889427)) {
    /* '<S7>:1:40' elseif (angle_ref >= pi/180*180 && angle_ref < pi/180*195) */
    /* '<S7>:1:41' sector_ref = 13.0; */
    rtDW->sector_ref = 13;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 3.4033920413889427) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 3.6651914291880923)) {
    /* '<S7>:1:42' elseif (angle_ref >= pi/180*195 && angle_ref < pi/180*210) */
    /* '<S7>:1:43' sector_ref = 14.0; */
    rtDW->sector_ref = 14;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 3.6651914291880923) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 3.9269908169872414)) {
    /* '<S7>:1:44' elseif (angle_ref >= pi/180*210 && angle_ref < pi/180*225) */
    /* '<S7>:1:45' sector_ref = 15.0; */
    rtDW->sector_ref = 15;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 3.9269908169872414) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 4.1887902047863905)) {
    /* '<S7>:1:46' elseif (angle_ref >= pi/180*225 && angle_ref < pi/180*240) */
    /* '<S7>:1:47' sector_ref = 16.0; */
    rtDW->sector_ref = 16;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 4.1887902047863905) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 4.4505895925855405)) {
    /* '<S7>:1:48' elseif (angle_ref >= pi/180*240 && angle_ref < pi/180*255) */
    /* '<S7>:1:49' sector_ref = 17.0; */
    rtDW->sector_ref = 17;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 4.4505895925855405) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 4.71238898038469)) {
    /* '<S7>:1:50' elseif (angle_ref >= pi/180*255 && angle_ref < pi/180*270) */
    /* '<S7>:1:51' sector_ref = 18.0; */
    rtDW->sector_ref = 18;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 4.71238898038469) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 4.9741883681838388)) {
    /* '<S7>:1:52' elseif (angle_ref >= pi/180*270 && angle_ref < pi/180*285) */
    /* '<S7>:1:53' sector_ref = 19.0; */
    rtDW->sector_ref = 19;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 4.9741883681838388) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 5.2359877559829888)) {
    /* '<S7>:1:54' elseif (angle_ref >= pi/180*285 && angle_ref < pi/180*300) */
    /* '<S7>:1:55' sector_ref = 20.0; */
    rtDW->sector_ref = 20;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 5.2359877559829888) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 5.497787143782138)) {
    /* '<S7>:1:56' elseif (angle_ref >= pi/180*300 && angle_ref < pi/180*315) */
    /* '<S7>:1:57' sector_ref = 21.0; */
    rtDW->sector_ref = 21;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 5.497787143782138) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 5.7595865315812871)) {
    /* '<S7>:1:58' elseif (angle_ref >= pi/180*315 && angle_ref < pi/180*330) */
    /* '<S7>:1:59' sector_ref = 22.0; */
    rtDW->sector_ref = 22;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 5.7595865315812871) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 6.0213859193804371)) {
    /* '<S7>:1:60' elseif (angle_ref >= pi/180*330 && angle_ref < pi/180*345) */
    /* '<S7>:1:61' sector_ref = 23.0; */
    rtDW->sector_ref = 23;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 6.0213859193804371) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 6.2831853071795862)) {
    /* '<S7>:1:62' elseif (angle_ref >= pi/180*345 && angle_ref < pi/180*360) */
    /* '<S7>:1:63' sector_ref = 24.0; */
    rtDW->sector_ref = 24;
  }

  /* End of MATLAB Function: '<S1>/deadbeat_solution' */

  /* MATLAB Function: '<S1>/act_sw_2_dqxy_volts_all' incorporates:
   *  Inport: '<Root>/v_DC_pu'
   */
  /*  voltage lookup factors alpha/beta */
  /* MATLAB Function 'uz_codegen/act_sw_2_dqxy_volts_all': '<S4>:1' */
  /*  since zero voltages for switch position 0 and 63 is not needed */
  /*  and matlab does use one based indexing, i simply removed entrys 1  */
  /*  and 64. Therefore, the voltage LUTs below correspond again  */
  /*  to index 1 beeing the voltages for respective switch position  */
  /*  1 (000001b)  */
  /* '<S4>:1:12' v_alpha_beta_pu = single([ */
  /* '<S4>:1:13' %0.0,0.0; */
  /* '<S4>:1:14' 0.333333, -0.000000; */
  /* '<S4>:1:15' -0.166667, 0.288675; */
  /* '<S4>:1:16' 0.166667, 0.288675; */
  /* '<S4>:1:17' -0.166667, -0.288675; */
  /* '<S4>:1:18' 0.166667, -0.288675; */
  /* '<S4>:1:19' -0.333333, 0.000000; */
  /* '<S4>:1:20' 0.000000, 0.000000; */
  /* '<S4>:1:21' 0.288675, 0.166667; */
  /* '<S4>:1:22' 0.622008, 0.166667; */
  /* '<S4>:1:23' 0.122008, 0.455342; */
  /* '<S4>:1:24' 0.455342, 0.455342; */
  /* '<S4>:1:25' 0.122008, -0.122008; */
  /* '<S4>:1:26' 0.455342, -0.122008; */
  /* '<S4>:1:27' -0.044658, 0.166667; */
  /* '<S4>:1:28' 0.288675, 0.166667; */
  /* '<S4>:1:29' -0.288675, 0.166667; */
  /* '<S4>:1:30' 0.044658, 0.166667; */
  /* '<S4>:1:31' -0.455342, 0.455342; */
  /* '<S4>:1:32' -0.122008, 0.455342; */
  /* '<S4>:1:33' -0.455342, -0.122008; */
  /* '<S4>:1:34' -0.122008, -0.122008; */
  /* '<S4>:1:35' -0.622008, 0.166667; */
  /* '<S4>:1:36' -0.288675, 0.166667; */
  /* '<S4>:1:37' 0.000000, 0.333333; */
  /* '<S4>:1:38' 0.333333, 0.333333; */
  /* '<S4>:1:39' -0.166667, 0.622008; */
  /* '<S4>:1:40' 0.166667, 0.622008; */
  /* '<S4>:1:41' -0.166667, 0.044658; */
  /* '<S4>:1:42' 0.166667, 0.044658; */
  /* '<S4>:1:43' -0.333333, 0.333333; */
  /* '<S4>:1:44' 0.000000, 0.333333; */
  /* '<S4>:1:45' -0.000000, -0.333333; */
  /* '<S4>:1:46' 0.333333, -0.333333; */
  /* '<S4>:1:47' -0.166667, -0.044658; */
  /* '<S4>:1:48' 0.166667, -0.044658; */
  /* '<S4>:1:49' -0.166667, -0.622008; */
  /* '<S4>:1:50' 0.166667, -0.622008; */
  /* '<S4>:1:51' -0.333333, -0.333333; */
  /* '<S4>:1:52' -0.000000, -0.333333; */
  /* '<S4>:1:53' 0.288675, -0.166667; */
  /* '<S4>:1:54' 0.622008, -0.166667; */
  /* '<S4>:1:55' 0.122008, 0.122008; */
  /* '<S4>:1:56' 0.455342, 0.122008; */
  /* '<S4>:1:57' 0.122008, -0.455342; */
  /* '<S4>:1:58' 0.455342, -0.455342; */
  /* '<S4>:1:59' -0.044658, -0.166667; */
  /* '<S4>:1:60' 0.288675, -0.166667; */
  /* '<S4>:1:61' -0.288675, -0.166667; */
  /* '<S4>:1:62' 0.044658, -0.166667; */
  /* '<S4>:1:63' -0.455342, 0.122008; */
  /* '<S4>:1:64' -0.122008, 0.122008; */
  /* '<S4>:1:65' -0.455342, -0.455342; */
  /* '<S4>:1:66' -0.122008, -0.455342; */
  /* '<S4>:1:67' -0.622008, -0.166667; */
  /* '<S4>:1:68' -0.288675, -0.166667; */
  /* '<S4>:1:69' -0.000000, -0.000000; */
  /* '<S4>:1:70' 0.333333, -0.000000; */
  /* '<S4>:1:71' -0.166667, 0.288675; */
  /* '<S4>:1:72' 0.166667, 0.288675; */
  /* '<S4>:1:73' -0.166667, -0.288675; */
  /* '<S4>:1:74' 0.166667, -0.288675; */
  /* '<S4>:1:75' -0.333333, 0.000000; */
  /* '<S4>:1:76' % 0.0, 0.0; */
  /* '<S4>:1:77' ]); */
  /* 0.0,0.0; */
  /*  0.0, 0.0; */
  /* '<S4>:1:79' v_X_Y_pu = single([ */
  /* '<S4>:1:80' % 0.0, 0.0; */
  /* '<S4>:1:81' 0.333333,0; */
  /* '<S4>:1:82' -0.166667,-0.288675; */
  /* '<S4>:1:83' 0.166667,-0.288675; */
  /* '<S4>:1:84' -0.166667,0.288675; */
  /* '<S4>:1:85' 0.166667,0.288675; */
  /* '<S4>:1:86' -0.333333,0; */
  /* '<S4>:1:87' 0,0; */
  /* '<S4>:1:88' -0.288675,0.166667; */
  /* '<S4>:1:89' 0.0446580,0.166667; */
  /* '<S4>:1:90' -0.455342,-0.122008; */
  /* '<S4>:1:91' -0.122008,-0.122008; */
  /* '<S4>:1:92' -0.455342,0.455342; */
  /* '<S4>:1:93' -0.122008,0.455342; */
  /* '<S4>:1:94' -0.622008,0.166667; */
  /* '<S4>:1:95' -0.288675,0.166667; */
  /* '<S4>:1:96' 0.288675,0.166667; */
  /* '<S4>:1:97' 0.622008,0.166667; */
  /* '<S4>:1:98' 0.122008,-0.122008; */
  /* '<S4>:1:99' 0.455342,-0.122008; */
  /* '<S4>:1:100' 0.122008,0.455342; */
  /* '<S4>:1:101' 0.455342,0.455342; */
  /* '<S4>:1:102' -0.0446580,0.166667; */
  /* '<S4>:1:103' 0.288675,0.166667; */
  /* '<S4>:1:104' 0,0.333333; */
  /* '<S4>:1:105' 0.333333,0.333333; */
  /* '<S4>:1:106' -0.166667,0.0446580; */
  /* '<S4>:1:107' 0.166667,0.0446580; */
  /* '<S4>:1:108' -0.166667,0.622008; */
  /* '<S4>:1:109' 0.166667,0.622008; */
  /* '<S4>:1:110' -0.333333,0.333333; */
  /* '<S4>:1:111' 0,0.333333; */
  /* '<S4>:1:112' 0,-0.333333; */
  /* '<S4>:1:113' 0.333333,-0.333333; */
  /* '<S4>:1:114' -0.166667,-0.622008; */
  /* '<S4>:1:115' 0.166667,-0.622008; */
  /* '<S4>:1:116' -0.166667,-0.0446580; */
  /* '<S4>:1:117' 0.166667,-0.0446580; */
  /* '<S4>:1:118' -0.333333,-0.333333; */
  /* '<S4>:1:119' 0,-0.333333; */
  /* '<S4>:1:120' -0.288675,-0.166667; */
  /* '<S4>:1:121' 0.0446580,-0.166667; */
  /* '<S4>:1:122' -0.455342,-0.455342; */
  /* '<S4>:1:123' -0.122008,-0.455342; */
  /* '<S4>:1:124' -0.455342,0.122008; */
  /* '<S4>:1:125' -0.122008,0.122008; */
  /* '<S4>:1:126' -0.622008,-0.166667; */
  /* '<S4>:1:127' -0.288675,-0.166667; */
  /* '<S4>:1:128' 0.288675,-0.166667; */
  /* '<S4>:1:129' 0.622008,-0.166667; */
  /* '<S4>:1:130' 0.122008,-0.455342; */
  /* '<S4>:1:131' 0.455342,-0.455342; */
  /* '<S4>:1:132' 0.122008,0.122008; */
  /* '<S4>:1:133' 0.455342,0.122008; */
  /* '<S4>:1:134' -0.0446580,-0.166667; */
  /* '<S4>:1:135' 0.288675,-0.166667; */
  /* '<S4>:1:136' 0,0; */
  /* '<S4>:1:137' 0.333333,0; */
  /* '<S4>:1:138' -0.166667,-0.288675; */
  /* '<S4>:1:139' 0.166667,-0.288675; */
  /* '<S4>:1:140' -0.166667,0.288675; */
  /* '<S4>:1:141' 0.166667,0.288675; */
  /* '<S4>:1:142' -0.333333,0;                 */
  /* '<S4>:1:143' % 0.0, 0.0; */
  /* '<S4>:1:144' ]); */
  /*  0.0, 0.0; */
  /*  0.0, 0.0; */
  /* '<S4>:1:147' vd_1_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_1(idx_opt),1) *  cos_angle_pos + v_alpha_beta_pu(act_sw_1(idx_opt),2) * sin_angle_pos); */
  /* '<S4>:1:148' vq_1_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_1(idx_opt),1) * -sin_angle_pos + v_alpha_beta_pu(act_sw_1(idx_opt),2) * cos_angle_pos); */
  /* '<S4>:1:149' vx_1_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_1(idx_opt),1) * cos_angle_neg + v_X_Y_pu(act_sw_1(idx_opt),2) * sin_angle_neg); */
  /* '<S4>:1:150' vy_1_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_1(idx_opt),1) * -sin_angle_neg + v_X_Y_pu(act_sw_1(idx_opt),2) * cos_angle_neg); */
  /* '<S4>:1:152' vd_2_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_2(idx_opt),1) *  cos_angle_pos + v_alpha_beta_pu(act_sw_2(idx_opt),2) * sin_angle_pos); */
  /* '<S4>:1:153' vq_2_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_2(idx_opt),1) * -sin_angle_pos + v_alpha_beta_pu(act_sw_2(idx_opt),2) * cos_angle_pos); */
  /* '<S4>:1:154' vx_2_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_2(idx_opt),1) * cos_angle_neg + v_X_Y_pu(act_sw_2(idx_opt),2) * sin_angle_neg); */
  /* '<S4>:1:155' vy_2_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_2(idx_opt),1) * -sin_angle_neg + v_X_Y_pu(act_sw_2(idx_opt),2) * cos_angle_neg); */
  /* '<S4>:1:157' vd_3_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_3(idx_opt),1) *  cos_angle_pos + v_alpha_beta_pu(act_sw_3(idx_opt),2) * sin_angle_pos); */
  /* '<S4>:1:158' vq_3_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_3(idx_opt),1) * -sin_angle_pos + v_alpha_beta_pu(act_sw_3(idx_opt),2) * cos_angle_pos); */
  /* '<S4>:1:159' vx_3_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_3(idx_opt),1) * cos_angle_neg + v_X_Y_pu(act_sw_3(idx_opt),2) * sin_angle_neg); */
  /* '<S4>:1:160' vy_3_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_3(idx_opt),1) * -sin_angle_neg + v_X_Y_pu(act_sw_3(idx_opt),2) * cos_angle_neg); */
  /* '<S4>:1:162' vd_4_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_4(idx_opt),1) *  cos_angle_pos + v_alpha_beta_pu(act_sw_4(idx_opt),2) * sin_angle_pos); */
  /* '<S4>:1:163' vq_4_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_4(idx_opt),1) * -sin_angle_pos + v_alpha_beta_pu(act_sw_4(idx_opt),2) * cos_angle_pos); */
  /* '<S4>:1:164' vx_4_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_4(idx_opt),1) * cos_angle_neg + v_X_Y_pu(act_sw_4(idx_opt),2) * sin_angle_neg); */
  /* '<S4>:1:165' vy_4_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_4(idx_opt),1) * -sin_angle_neg + v_X_Y_pu(act_sw_4(idx_opt),2) * cos_angle_neg); */
  /* '<S4>:1:167' vd_5_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_5(idx_opt),1) *  cos_angle_pos + v_alpha_beta_pu(act_sw_5(idx_opt),2) * sin_angle_pos); */
  /* '<S4>:1:168' vq_5_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_5(idx_opt),1) * -sin_angle_pos + v_alpha_beta_pu(act_sw_5(idx_opt),2) * cos_angle_pos); */
  /* '<S4>:1:169' vx_5_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_5(idx_opt),1) * cos_angle_neg + v_X_Y_pu(act_sw_5(idx_opt),2) * sin_angle_neg); */
  /* '<S4>:1:170' vy_5_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_5(idx_opt),1) * -sin_angle_neg + v_X_Y_pu(act_sw_5(idx_opt),2) * cos_angle_neg); */
  /* '<S4>:1:172' v_1_idx_pu = [vd_1_idx_pu; vq_1_idx_pu; vx_1_idx_pu; vy_1_idx_pu]; */
  rtDW->d_j = rtDW->act_sw_1[rtDW->sector_ref - 1];
  rtDW->rtb_v_1_idx_pu_idx_1 = v_alpha_beta_pu[rtDW->d_j - 1];
  rtDW->q = v_alpha_beta_pu[rtDW->d_j + 61];
  rtDW->rtb_i_dq_obs_idx_0 = (rtDW->rtb_v_1_idx_pu_idx_1 * rtDW->SinCos1_o2 +
    rtDW->q * rtDW->w6theta_el) * rtU->v_DC_pu;
  rtDW->rtb_v_1_idx_pu_idx_1 = (rtDW->rtb_v_1_idx_pu_idx_1 * -rtDW->w6theta_el +
    rtDW->q * rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->rtb_v_1_idx_pu_idx_3 = v_X_Y_pu[rtDW->d_j - 1];
  rtDW->rtb_v_2_idx_pu_idx_0 = v_X_Y_pu[rtDW->d_j + 61];
  rtDW->q = (rtDW->rtb_v_1_idx_pu_idx_3 * rtDW->SinCos2_o2 +
             rtDW->rtb_v_2_idx_pu_idx_0 * rtDW->SinCos2_o1) * rtU->v_DC_pu;
  rtDW->rtb_v_1_idx_pu_idx_3 = (rtDW->rtb_v_1_idx_pu_idx_3 * -rtDW->SinCos2_o1 +
    rtDW->rtb_v_2_idx_pu_idx_0 * rtDW->SinCos2_o2) * rtU->v_DC_pu;

  /* '<S4>:1:173' v_2_idx_pu = [vd_2_idx_pu; vq_2_idx_pu; vx_2_idx_pu; vy_2_idx_pu]; */
  rtDW->d_j = rtDW->act_sw_2[rtDW->sector_ref - 1];
  rtDW->rtb_v_2_idx_pu_idx_1 = v_alpha_beta_pu[rtDW->d_j - 1];
  rtDW->rtb_v_2_idx_pu_idx_2 = v_alpha_beta_pu[rtDW->d_j + 61];
  rtDW->rtb_v_2_idx_pu_idx_0 = (rtDW->rtb_v_2_idx_pu_idx_1 * rtDW->SinCos1_o2 +
    rtDW->rtb_v_2_idx_pu_idx_2 * rtDW->w6theta_el) * rtU->v_DC_pu;
  rtDW->rtb_v_2_idx_pu_idx_1 = (rtDW->rtb_v_2_idx_pu_idx_1 * -rtDW->w6theta_el +
    rtDW->rtb_v_2_idx_pu_idx_2 * rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->rtb_v_2_idx_pu_idx_3 = v_X_Y_pu[rtDW->d_j - 1];
  rtDW->rtb_v_3_idx_pu_idx_0 = v_X_Y_pu[rtDW->d_j + 61];
  rtDW->rtb_v_2_idx_pu_idx_2 = (rtDW->rtb_v_2_idx_pu_idx_3 * rtDW->SinCos2_o2 +
    rtDW->rtb_v_3_idx_pu_idx_0 * rtDW->SinCos2_o1) * rtU->v_DC_pu;
  rtDW->rtb_v_2_idx_pu_idx_3 = (rtDW->rtb_v_2_idx_pu_idx_3 * -rtDW->SinCos2_o1 +
    rtDW->rtb_v_3_idx_pu_idx_0 * rtDW->SinCos2_o2) * rtU->v_DC_pu;

  /* '<S4>:1:174' v_3_idx_pu = [vd_3_idx_pu; vq_3_idx_pu; vx_3_idx_pu; vy_3_idx_pu]; */
  rtDW->d_j = rtDW->act_sw_3[rtDW->sector_ref - 1];
  rtDW->rtb_v_3_idx_pu_idx_1 = v_alpha_beta_pu[rtDW->d_j - 1];
  rtDW->rtb_v_3_idx_pu_idx_2 = v_alpha_beta_pu[rtDW->d_j + 61];
  rtDW->rtb_v_3_idx_pu_idx_0 = (rtDW->rtb_v_3_idx_pu_idx_1 * rtDW->SinCos1_o2 +
    rtDW->rtb_v_3_idx_pu_idx_2 * rtDW->w6theta_el) * rtU->v_DC_pu;
  rtDW->rtb_v_3_idx_pu_idx_1 = (rtDW->rtb_v_3_idx_pu_idx_1 * -rtDW->w6theta_el +
    rtDW->rtb_v_3_idx_pu_idx_2 * rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->rtb_v_3_idx_pu_idx_3 = v_X_Y_pu[rtDW->d_j - 1];
  rtDW->rtb_v_4_idx_pu_idx_0 = v_X_Y_pu[rtDW->d_j + 61];
  rtDW->rtb_v_3_idx_pu_idx_2 = (rtDW->rtb_v_3_idx_pu_idx_3 * rtDW->SinCos2_o2 +
    rtDW->rtb_v_4_idx_pu_idx_0 * rtDW->SinCos2_o1) * rtU->v_DC_pu;
  rtDW->rtb_v_3_idx_pu_idx_3 = (rtDW->rtb_v_3_idx_pu_idx_3 * -rtDW->SinCos2_o1 +
    rtDW->rtb_v_4_idx_pu_idx_0 * rtDW->SinCos2_o2) * rtU->v_DC_pu;

  /* '<S4>:1:175' v_4_idx_pu = [vd_4_idx_pu; vq_4_idx_pu; vx_4_idx_pu; vy_4_idx_pu]; */
  rtDW->d_j = rtDW->act_sw_4[rtDW->sector_ref - 1];
  rtDW->rtb_v_4_idx_pu_idx_1 = v_alpha_beta_pu[rtDW->d_j - 1];
  rtDW->rtb_v_4_idx_pu_idx_2 = v_alpha_beta_pu[rtDW->d_j + 61];
  rtDW->rtb_v_4_idx_pu_idx_0 = (rtDW->rtb_v_4_idx_pu_idx_1 * rtDW->SinCos1_o2 +
    rtDW->rtb_v_4_idx_pu_idx_2 * rtDW->w6theta_el) * rtU->v_DC_pu;
  rtDW->rtb_v_4_idx_pu_idx_1 = (rtDW->rtb_v_4_idx_pu_idx_1 * -rtDW->w6theta_el +
    rtDW->rtb_v_4_idx_pu_idx_2 * rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->rtb_v_4_idx_pu_idx_3 = v_X_Y_pu[rtDW->d_j - 1];
  rtDW->rtb_v_5_idx_pu_idx_0 = v_X_Y_pu[rtDW->d_j + 61];
  rtDW->rtb_v_4_idx_pu_idx_2 = (rtDW->rtb_v_4_idx_pu_idx_3 * rtDW->SinCos2_o2 +
    rtDW->rtb_v_5_idx_pu_idx_0 * rtDW->SinCos2_o1) * rtU->v_DC_pu;
  rtDW->rtb_v_4_idx_pu_idx_3 = (rtDW->rtb_v_4_idx_pu_idx_3 * -rtDW->SinCos2_o1 +
    rtDW->rtb_v_5_idx_pu_idx_0 * rtDW->SinCos2_o2) * rtU->v_DC_pu;

  /* '<S4>:1:176' v_5_idx_pu = [vd_5_idx_pu; vq_5_idx_pu; vx_5_idx_pu; vy_5_idx_pu]; */
  rtDW->d_j = rtDW->act_sw_5[rtDW->sector_ref - 1];
  rtDW->rtb_v_5_idx_pu_idx_1 = v_alpha_beta_pu[rtDW->d_j - 1];
  rtDW->rtb_v_5_idx_pu_idx_2 = v_alpha_beta_pu[rtDW->d_j + 61];
  rtDW->rtb_v_5_idx_pu_idx_0 = (rtDW->rtb_v_5_idx_pu_idx_1 * rtDW->SinCos1_o2 +
    rtDW->rtb_v_5_idx_pu_idx_2 * rtDW->w6theta_el) * rtU->v_DC_pu;
  rtDW->rtb_v_5_idx_pu_idx_1 = (rtDW->rtb_v_5_idx_pu_idx_1 * -rtDW->w6theta_el +
    rtDW->rtb_v_5_idx_pu_idx_2 * rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->rtb_v_5_idx_pu_idx_3 = v_X_Y_pu[rtDW->d_j - 1];
  rtDW->SinCos1_o2 = v_X_Y_pu[rtDW->d_j + 61];
  rtDW->rtb_v_5_idx_pu_idx_2 = (rtDW->rtb_v_5_idx_pu_idx_3 * rtDW->SinCos2_o2 +
    rtDW->SinCos1_o2 * rtDW->SinCos2_o1) * rtU->v_DC_pu;
  rtDW->rtb_v_5_idx_pu_idx_3 = (rtDW->rtb_v_5_idx_pu_idx_3 * -rtDW->SinCos2_o1 +
    rtDW->SinCos1_o2 * rtDW->SinCos2_o2) * rtU->v_DC_pu;

  /* MATLAB Function: '<S1>/current_gradient_prediction' incorporates:
   *  Inport: '<Root>/HC_off_on'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/Ts_times_ZB_over_Lx'
   *  Inport: '<Root>/Ts_times_ZB_over_Ly'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/phiPM_h'
   *  Inport: '<Root>/psiPM_h_pu'
   *  Inport: '<Root>/psi_pm_over_psiB'
   *  Inport: '<Root>/tB_over_Ts'
   */
  /* MATLAB Function 'uz_codegen/current_gradient_prediction': '<S5>:1' */
  /* '<S5>:1:3' A_minus_I = [ -Ts_times_ZB_over_Ld*Rs_over_ZB            Ts_times_ZB_over_Ld*Lq_over_LB*w_e_pu   0                                      0; */
  /* '<S5>:1:4'       -Ts_times_ZB_over_Lq*Ld_over_LB*w_e_pu     -Ts_times_ZB_over_Lq*Rs_over_ZB                 0                                      0; */
  /* '<S5>:1:5'       0                                          0                                        -Ts_times_ZB_over_Lx*Rs_over_ZB       -Ts_times_ZB_over_Lx*Ly_over_LB*w_e_pu; */
  /* '<S5>:1:6'       0                                          0                                        Ts_times_ZB_over_Ly*Lx_over_LB*w_e_pu  -Ts_times_ZB_over_Ly*Rs_over_ZB]; */
  rtDW->A_minus_I[0] = -rtU->Ts_times_ZB_over_Ld * rtU->Rs_over_ZB;
  rtDW->A_minus_I[4] = rtDW->x0_idx_0;
  rtDW->A_minus_I[8] = 0.0F;
  rtDW->A_minus_I[12] = 0.0F;
  rtDW->A_minus_I[1] = rtDW->x0_idx_1;
  rtDW->A_minus_I[5] = -rtU->Ts_times_ZB_over_Lq * rtU->Rs_over_ZB;
  rtDW->A_minus_I[9] = 0.0F;
  rtDW->A_minus_I[13] = 0.0F;
  rtDW->A_minus_I[2] = 0.0F;
  rtDW->A_minus_I[6] = 0.0F;
  rtDW->A_minus_I[10] = -rtU->Ts_times_ZB_over_Lx * rtU->Rs_over_ZB;
  rtDW->A_minus_I[14] = rtDW->x0_idx_2;
  rtDW->A_minus_I[3] = 0.0F;
  rtDW->A_minus_I[7] = 0.0F;
  rtDW->A_minus_I[11] = rtDW->x0_idx_3;
  rtDW->A_minus_I[15] = -rtU->Ts_times_ZB_over_Ly * rtU->Rs_over_ZB;

  /* '<S5>:1:8' psiPM5 = psiPM_h_pu(1); */
  /* '<S5>:1:9' psiPM7 = psiPM_h_pu(2); */
  /* '<S5>:1:11' phi5 = phiPM_h(1); */
  /* '<S5>:1:12' phi7 = phiPM_h(2); */
  /*  w3theta_el = single(3*theta_el); */
  /* '<S5>:1:15' w6theta_el = single(6*theta_el); */
  /*  w9theta_el = single(9*theta_el); */
  /*  w12theta_el = single(12*theta_el); */
  /* '<S5>:1:19' B = [Ts_times_ZB_over_Ld    0                       0                       0                       ; */
  /* '<S5>:1:20'      0                      Ts_times_ZB_over_Lq     0                       0                       ; */
  /* '<S5>:1:21'      0                      0                       Ts_times_ZB_over_Lx     0                       ; */
  /* '<S5>:1:22'      0                      0                       0                       Ts_times_ZB_over_Ly     ]; */
  rtDW->B_n[0] = rtU->Ts_times_ZB_over_Ld;
  rtDW->B_n[4] = 0.0F;
  rtDW->B_n[8] = 0.0F;
  rtDW->B_n[12] = 0.0F;
  rtDW->B_n[1] = 0.0F;
  rtDW->B_n[5] = rtU->Ts_times_ZB_over_Lq;
  rtDW->B_n[9] = 0.0F;
  rtDW->B_n[13] = 0.0F;
  rtDW->B_n[2] = 0.0F;
  rtDW->B_n[6] = 0.0F;
  rtDW->B_n[10] = rtU->Ts_times_ZB_over_Lx;
  rtDW->B_n[14] = 0.0F;
  rtDW->B_n[3] = 0.0F;
  rtDW->B_n[7] = 0.0F;
  rtDW->B_n[11] = 0.0F;
  rtDW->B_n[15] = rtU->Ts_times_ZB_over_Ly;

  /*  C = [1   0   0   0; */
  /*       0   1   0   0; */
  /*       0   0   1   0; */
  /*       0   0   0   1]; */
  /* '<S5>:1:30' d_obs = [d_dq_obs(1);d_dq_obs(2);d_xy_obs(1);d_xy_obs(2)]; */
  rtDW->d_obs[0] = rtDW->rtb_d_dq_obs_idx_0;
  rtDW->d_obs[1] = rtDW->rtb_v_t0_idx_3;
  rtDW->d_obs[2] = rtDW->rtb_d_xy_obs_idx_0;
  rtDW->d_obs[3] = rtDW->rtb_v_t0_idx_2;

  /* '<S5>:1:32' d_m = [0; -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB; 0; 0]; */
  rtDW->d_m_h[0] = 0.0F;
  rtDW->x0_idx_0 = -rtU->omega_el_pu * rtU->Ts_times_ZB_over_Lq *
    rtU->psi_pm_over_psiB;
  rtDW->d_m_h[1] = rtDW->x0_idx_0;
  rtDW->d_m_h[2] = 0.0F;
  rtDW->d_m_h[3] = 0.0F;

  /* '<S5>:1:34' d_m_HC = [     0; */
  /* '<S5>:1:35'          -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB; */
  /* '<S5>:1:36'          -w_e_pu*Ts_times_ZB_over_Lx*(psiPM5*sin(w6theta_el+phi5)-psiPM7*sin(w6theta_el+phi7)-psiPM5*6*sin(w6theta_el+phi5)-psiPM7*6*sin(w6theta_el+phi7)); */
  /* '<S5>:1:37'           w_e_pu*Ts_times_ZB_over_Ly*(psiPM5*cos(w6theta_el+phi5)+psiPM7*cos(w6theta_el+phi7)-psiPM5*6*cos(w6theta_el+phi5)+psiPM7*6*cos(w6theta_el+phi7))]; */
  rtDW->SinCos2_o2 = rtDW->w6theta_el_tmp + rtU->phiPM_h[0];
  rtDW->SinCos1_o2 = sinf(rtDW->SinCos2_o2);
  rtDW->w6theta_el = rtDW->w6theta_el_tmp + rtU->phiPM_h[1];
  rtDW->SinCos2_o1 = sinf(rtDW->w6theta_el);
  rtDW->SinCos2_o2 = cosf(rtDW->SinCos2_o2);
  rtDW->w6theta_el = cosf(rtDW->w6theta_el);
  rtDW->d_m_HC[0] = 0.0F;
  rtDW->d_m_HC[1] = rtDW->x0_idx_0;
  rtDW->d_m_HC[2] = (((rtU->psiPM_h_pu[0] * rtDW->SinCos1_o2 - rtU->psiPM_h_pu[1]
                       * rtDW->SinCos2_o1) - rtU->psiPM_h_pu[0] * 6.0F *
                      rtDW->SinCos1_o2) - rtU->psiPM_h_pu[1] * 6.0F *
                     rtDW->SinCos2_o1) * (-rtU->omega_el_pu *
    rtU->Ts_times_ZB_over_Lx);
  rtDW->d_m_HC[3] = (((rtU->psiPM_h_pu[0] * rtDW->SinCos2_o2 + rtU->psiPM_h_pu[1]
                       * rtDW->w6theta_el) - rtU->psiPM_h_pu[0] * 6.0F *
                      rtDW->SinCos2_o2) + rtU->psiPM_h_pu[1] * 6.0F *
                     rtDW->w6theta_el) * (rtU->omega_el_pu *
    rtU->Ts_times_ZB_over_Ly);

  /*  original xy harmonic equations without placing factor outside the */
  /*  brackets */
  /*   -w_e_pu*Ts_times_ZB_over_Lx*(psiPM5*sin(w6theta_el+phi5)-psiPM7*sin(w6theta_el+phi7))-Ts_times_ZB_over_Lx*w_e_pu*(-psiPM5*6*sin(w6theta_el+phi5)-psiPM7*6*sin(w6theta_el+phi7))+e_xy_obs(1); */
  /*    w_e_pu*Ts_times_ZB_over_Ly*(psiPM5*cos(w6theta_el+phi5)+psiPM7*cos(w6theta_el+phi7))-Ts_times_ZB_over_Ly*w_e_pu*(+psiPM5*6*cos(w6theta_el+phi5)-psiPM7*6*cos(w6theta_el+phi7))+e_xy_obs(2) */
  /* '<S5>:1:48' x0 = [id_pu; iq_pu; ix_pu; iy_pu]; */
  rtDW->x0_idx_0 = rtDW->v_t0[0];
  rtDW->x0_idx_1 = rtDW->v_t0[1];
  rtDW->x0_idx_2 = rtDW->v_t0[2];
  rtDW->x0_idx_3 = rtDW->v_t0[3];

  /* '<S5>:1:50' u0 = [0;0;0;0]; */
  /*  zero voltage applied */
  /* '<S5>:1:51' u1 = [v_1_pu(1); v_1_pu(2); v_1_pu(3); v_1_pu(4)]; */
  /*  first active vector */
  /* '<S5>:1:52' u2 = [v_2_pu(1); v_2_pu(2); v_2_pu(3); v_2_pu(4)]; */
  /*  second active vector */
  /* '<S5>:1:53' u3 = [v_3_pu(1); v_3_pu(2); v_3_pu(3); v_3_pu(4)]; */
  /*  third active vector */
  /* '<S5>:1:54' u4 = [v_4_pu(1); v_4_pu(2); v_4_pu(3); v_4_pu(4)]; */
  /*  fourth active vector */
  /* '<S5>:1:55' u5 = [v_5_pu(1); v_5_pu(2); v_5_pu(3); v_5_pu(4)]; */
  /*  fifth active vector */
  /*  calculate the gradients */
  /* '<S5>:1:58' switch HC_off_on */
  if (!rtU->HC_off_on) {
    rtDW->d_j = 0;
  } else if (rtU->HC_off_on) {
    rtDW->d_j = 1;
  } else {
    rtDW->d_j = -1;
  }

  switch (rtDW->d_j) {
   case 0:
    /* '<S5>:1:59' case false */
    /* '<S5>:1:60' m0 = (A_minus_I*x0+B*u0+d_m+d_obs)*tB_over_Ts; */
    /* In order to save 6*16 multiplications i removed C* */
    /* '<S5>:1:61' m1 = (A_minus_I*x0+B*u1+d_m+d_obs)*tB_over_Ts; */
    /* '<S5>:1:62' m2 = (A_minus_I*x0+B*u2+d_m+d_obs)*tB_over_Ts; */
    /* '<S5>:1:63' m3 = (A_minus_I*x0+B*u3+d_m+d_obs)*tB_over_Ts; */
    /* '<S5>:1:64' m4 = (A_minus_I*x0+B*u4+d_m+d_obs)*tB_over_Ts; */
    /* '<S5>:1:65' m5 = (A_minus_I*x0+B*u5+d_m+d_obs)*tB_over_Ts; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->w6theta_el_tmp = rtDW->d_obs[rtDW->d_j];
      rtDW->SinCos2_o1 = rtDW->d_m_h[rtDW->d_j];
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j];
      rtDW->w6theta_el = rtDW->A_minus_I[rtDW->d_j] * rtDW->x0_idx_0;
      rtDW->B_d = rtDW->SinCos2_o2 * rtDW->rtb_i_dq_obs_idx_0;
      rtDW->B_e = rtDW->SinCos2_o2 * rtDW->rtb_v_2_idx_pu_idx_0;
      rtDW->B_b = rtDW->SinCos2_o2 * rtDW->rtb_v_3_idx_pu_idx_0;
      rtDW->B_j = rtDW->SinCos2_o2 * rtDW->rtb_v_4_idx_pu_idx_0;
      rtDW->B_f = rtDW->SinCos2_o2 * rtDW->rtb_v_5_idx_pu_idx_0;
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j + 4];
      rtDW->SinCos1_o2 = rtDW->A_minus_I[rtDW->d_j + 4] * rtDW->x0_idx_1;
      rtDW->B_d += rtDW->SinCos2_o2 * rtDW->rtb_v_1_idx_pu_idx_1;
      rtDW->B_e += rtDW->SinCos2_o2 * rtDW->rtb_v_2_idx_pu_idx_1;
      rtDW->B_b += rtDW->SinCos2_o2 * rtDW->rtb_v_3_idx_pu_idx_1;
      rtDW->B_j += rtDW->SinCos2_o2 * rtDW->rtb_v_4_idx_pu_idx_1;
      rtDW->B_f += rtDW->SinCos2_o2 * rtDW->rtb_v_5_idx_pu_idx_1;
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j + 8];
      rtDW->A_minus_I_tmp = rtDW->A_minus_I[rtDW->d_j + 8] * rtDW->x0_idx_2;
      rtDW->B_d += rtDW->SinCos2_o2 * rtDW->q;
      rtDW->B_e += rtDW->SinCos2_o2 * rtDW->rtb_v_2_idx_pu_idx_2;
      rtDW->B_b += rtDW->SinCos2_o2 * rtDW->rtb_v_3_idx_pu_idx_2;
      rtDW->B_j += rtDW->SinCos2_o2 * rtDW->rtb_v_4_idx_pu_idx_2;
      rtDW->B_f += rtDW->SinCos2_o2 * rtDW->rtb_v_5_idx_pu_idx_2;
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j + 12];
      rtDW->A_minus_I_tmp_b = rtDW->A_minus_I[rtDW->d_j + 12] * rtDW->x0_idx_3;
      rtDW->m6[rtDW->d_j] = (((rtDW->A_minus_I_tmp_b + (rtDW->A_minus_I_tmp +
        (rtDW->SinCos1_o2 + rtDW->w6theta_el))) + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m1[rtDW->d_j] = ((((rtDW->A_minus_I_tmp_b + (rtDW->A_minus_I_tmp +
        (rtDW->SinCos1_o2 + rtDW->w6theta_el))) + (rtDW->SinCos2_o2 *
        rtDW->rtb_v_1_idx_pu_idx_3 + rtDW->B_d)) + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m2[rtDW->d_j] = ((((rtDW->A_minus_I_tmp_b + (rtDW->A_minus_I_tmp +
        (rtDW->SinCos1_o2 + rtDW->w6theta_el))) + (rtDW->SinCos2_o2 *
        rtDW->rtb_v_2_idx_pu_idx_3 + rtDW->B_e)) + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m3[rtDW->d_j] = ((((rtDW->A_minus_I_tmp_b + (rtDW->A_minus_I_tmp +
        (rtDW->SinCos1_o2 + rtDW->w6theta_el))) + (rtDW->SinCos2_o2 *
        rtDW->rtb_v_3_idx_pu_idx_3 + rtDW->B_b)) + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m4[rtDW->d_j] = ((((rtDW->A_minus_I_tmp_b + (rtDW->A_minus_I_tmp +
        (rtDW->SinCos1_o2 + rtDW->w6theta_el))) + (rtDW->SinCos2_o2 *
        rtDW->rtb_v_4_idx_pu_idx_3 + rtDW->B_j)) + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m5[rtDW->d_j] = ((((rtDW->A_minus_I_tmp_b + (rtDW->A_minus_I_tmp +
        (rtDW->SinCos1_o2 + rtDW->w6theta_el))) + (rtDW->SinCos2_o2 *
        rtDW->rtb_v_5_idx_pu_idx_3 + rtDW->B_f)) + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
    }

    /* '<S5>:1:66' m6 = m0; */
    break;

   case 1:
    /* '<S5>:1:67' case true */
    /* '<S5>:1:68' m0 = (A_minus_I*x0+B*u0+d_m_HC+d_obs)*tB_over_Ts; */
    /* '<S5>:1:69' m1 = (A_minus_I*x0+B*u1+d_m_HC+d_obs)*tB_over_Ts; */
    /* '<S5>:1:70' m2 = (A_minus_I*x0+B*u2+d_m_HC+d_obs)*tB_over_Ts; */
    /* '<S5>:1:71' m3 = (A_minus_I*x0+B*u3+d_m_HC+d_obs)*tB_over_Ts; */
    /* '<S5>:1:72' m4 = (A_minus_I*x0+B*u4+d_m_HC+d_obs)*tB_over_Ts; */
    /* '<S5>:1:73' m5 = (A_minus_I*x0+B*u5+d_m_HC+d_obs)*tB_over_Ts; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->w6theta_el_tmp = rtDW->d_obs[rtDW->d_j];
      rtDW->SinCos1_o2 = rtDW->d_m_HC[rtDW->d_j];
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j];
      rtDW->B_d = rtDW->SinCos2_o2 * rtDW->rtb_i_dq_obs_idx_0;
      rtDW->B_e = rtDW->SinCos2_o2 * rtDW->rtb_v_2_idx_pu_idx_0;
      rtDW->B_b = rtDW->SinCos2_o2 * rtDW->rtb_v_3_idx_pu_idx_0;
      rtDW->B_j = rtDW->SinCos2_o2 * rtDW->rtb_v_4_idx_pu_idx_0;
      rtDW->B_f = rtDW->SinCos2_o2 * rtDW->rtb_v_5_idx_pu_idx_0;
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j + 4];
      rtDW->B_d += rtDW->SinCos2_o2 * rtDW->rtb_v_1_idx_pu_idx_1;
      rtDW->B_e += rtDW->SinCos2_o2 * rtDW->rtb_v_2_idx_pu_idx_1;
      rtDW->B_b += rtDW->SinCos2_o2 * rtDW->rtb_v_3_idx_pu_idx_1;
      rtDW->B_j += rtDW->SinCos2_o2 * rtDW->rtb_v_4_idx_pu_idx_1;
      rtDW->B_f += rtDW->SinCos2_o2 * rtDW->rtb_v_5_idx_pu_idx_1;
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j + 8];
      rtDW->B_d += rtDW->SinCos2_o2 * rtDW->q;
      rtDW->B_e += rtDW->SinCos2_o2 * rtDW->rtb_v_2_idx_pu_idx_2;
      rtDW->B_b += rtDW->SinCos2_o2 * rtDW->rtb_v_3_idx_pu_idx_2;
      rtDW->B_j += rtDW->SinCos2_o2 * rtDW->rtb_v_4_idx_pu_idx_2;
      rtDW->B_f += rtDW->SinCos2_o2 * rtDW->rtb_v_5_idx_pu_idx_2;
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j + 12];
      rtDW->w6theta_el = rtDW->A_minus_I[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_minus_I[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_minus_I
          [rtDW->d_j + 4] * rtDW->x0_idx_1 + rtDW->A_minus_I[rtDW->d_j] *
          rtDW->x0_idx_0));
      rtDW->m6[rtDW->d_j] = ((rtDW->w6theta_el + rtDW->SinCos1_o2) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m1[rtDW->d_j] = (((rtDW->w6theta_el + (rtDW->SinCos2_o2 *
        rtDW->rtb_v_1_idx_pu_idx_3 + rtDW->B_d)) + rtDW->SinCos1_o2) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m2[rtDW->d_j] = (((rtDW->w6theta_el + (rtDW->SinCos2_o2 *
        rtDW->rtb_v_2_idx_pu_idx_3 + rtDW->B_e)) + rtDW->SinCos1_o2) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m3[rtDW->d_j] = (((rtDW->w6theta_el + (rtDW->SinCos2_o2 *
        rtDW->rtb_v_3_idx_pu_idx_3 + rtDW->B_b)) + rtDW->SinCos1_o2) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m4[rtDW->d_j] = (((rtDW->w6theta_el + (rtDW->SinCos2_o2 *
        rtDW->rtb_v_4_idx_pu_idx_3 + rtDW->B_j)) + rtDW->SinCos1_o2) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m5[rtDW->d_j] = (((rtDW->w6theta_el + (rtDW->SinCos2_o2 *
        rtDW->rtb_v_5_idx_pu_idx_3 + rtDW->B_f)) + rtDW->SinCos1_o2) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
    }

    /* '<S5>:1:74' m6 = m0; */
    break;

   default:
    /* '<S5>:1:75' otherwise */
    /* '<S5>:1:76' m0 = (A_minus_I*x0+B*u0+d_m+d_obs)*tB_over_Ts; */
    /* '<S5>:1:77' m1 = (A_minus_I*x0+B*u1+d_m+d_obs)*tB_over_Ts; */
    /* '<S5>:1:78' m2 = (A_minus_I*x0+B*u2+d_m+d_obs)*tB_over_Ts; */
    /* '<S5>:1:79' m3 = (A_minus_I*x0+B*u3+d_m+d_obs)*tB_over_Ts; */
    /* '<S5>:1:80' m4 = (A_minus_I*x0+B*u4+d_m+d_obs)*tB_over_Ts; */
    /* '<S5>:1:81' m5 = (A_minus_I*x0+B*u5+d_m+d_obs)*tB_over_Ts; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->w6theta_el_tmp = rtDW->d_obs[rtDW->d_j];
      rtDW->SinCos2_o1 = rtDW->d_m_h[rtDW->d_j];
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j];
      rtDW->w6theta_el = rtDW->SinCos2_o2 * rtDW->rtb_i_dq_obs_idx_0;
      rtDW->B_d = rtDW->SinCos2_o2 * rtDW->rtb_v_2_idx_pu_idx_0;
      rtDW->B_e = rtDW->SinCos2_o2 * rtDW->rtb_v_3_idx_pu_idx_0;
      rtDW->B_b = rtDW->SinCos2_o2 * rtDW->rtb_v_4_idx_pu_idx_0;
      rtDW->B_j = rtDW->SinCos2_o2 * rtDW->rtb_v_5_idx_pu_idx_0;
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j + 4];
      rtDW->w6theta_el += rtDW->SinCos2_o2 * rtDW->rtb_v_1_idx_pu_idx_1;
      rtDW->B_d += rtDW->SinCos2_o2 * rtDW->rtb_v_2_idx_pu_idx_1;
      rtDW->B_e += rtDW->SinCos2_o2 * rtDW->rtb_v_3_idx_pu_idx_1;
      rtDW->B_b += rtDW->SinCos2_o2 * rtDW->rtb_v_4_idx_pu_idx_1;
      rtDW->B_j += rtDW->SinCos2_o2 * rtDW->rtb_v_5_idx_pu_idx_1;
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j + 8];
      rtDW->w6theta_el += rtDW->SinCos2_o2 * rtDW->q;
      rtDW->B_d += rtDW->SinCos2_o2 * rtDW->rtb_v_2_idx_pu_idx_2;
      rtDW->B_e += rtDW->SinCos2_o2 * rtDW->rtb_v_3_idx_pu_idx_2;
      rtDW->B_b += rtDW->SinCos2_o2 * rtDW->rtb_v_4_idx_pu_idx_2;
      rtDW->B_j += rtDW->SinCos2_o2 * rtDW->rtb_v_5_idx_pu_idx_2;
      rtDW->SinCos2_o2 = rtDW->B_n[rtDW->d_j + 12];
      rtDW->SinCos1_o2 = rtDW->A_minus_I[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_minus_I[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_minus_I
          [rtDW->d_j + 4] * rtDW->x0_idx_1 + rtDW->A_minus_I[rtDW->d_j] *
          rtDW->x0_idx_0));
      rtDW->m6[rtDW->d_j] = ((rtDW->SinCos1_o2 + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m1[rtDW->d_j] = ((((rtDW->SinCos2_o2 * rtDW->rtb_v_1_idx_pu_idx_3 +
        rtDW->w6theta_el) + rtDW->SinCos1_o2) + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m2[rtDW->d_j] = ((((rtDW->SinCos2_o2 * rtDW->rtb_v_2_idx_pu_idx_3 +
        rtDW->B_d) + rtDW->SinCos1_o2) + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m3[rtDW->d_j] = ((((rtDW->SinCos2_o2 * rtDW->rtb_v_3_idx_pu_idx_3 +
        rtDW->B_e) + rtDW->SinCos1_o2) + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m4[rtDW->d_j] = ((((rtDW->SinCos2_o2 * rtDW->rtb_v_4_idx_pu_idx_3 +
        rtDW->B_b) + rtDW->SinCos1_o2) + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
      rtDW->m5[rtDW->d_j] = ((((rtDW->SinCos2_o2 * rtDW->rtb_v_5_idx_pu_idx_3 +
        rtDW->B_j) + rtDW->SinCos1_o2) + rtDW->SinCos2_o1) +
        rtDW->w6theta_el_tmp) * rtU->tB_over_Ts;
    }

    /* '<S5>:1:82' m6 = m0; */
    break;
  }

  /* MATLAB Function: '<S1>/formulate_qp' incorporates:
   *  Inport: '<Root>/i_d_ref_pu'
   *  Inport: '<Root>/i_q_ref_pu'
   *  Inport: '<Root>/i_x_ref_pu'
   *  Inport: '<Root>/i_y_ref_pu'
   *  Inport: '<Root>/lambda_dq'
   *  Inport: '<Root>/lambda_xy'
   *  MATLAB Function: '<S1>/current_gradient_prediction'
   */
  /* MATLAB Function 'uz_codegen/formulate_qp': '<S9>:1' */
  /* '<S9>:1:4' lam = [ lambda_dq  0       0       0; */
  /* '<S9>:1:5'         0       lambda_dq  0       0; */
  /* '<S9>:1:6'         0       0       lambda_xy  0; */
  /* '<S9>:1:7'         0       0       0       lambda_xy]; */
  rtDW->A_minus_I[0] = rtU->lambda_dq;
  rtDW->A_minus_I[4] = 0.0F;
  rtDW->A_minus_I[8] = 0.0F;
  rtDW->A_minus_I[12] = 0.0F;
  rtDW->A_minus_I[1] = 0.0F;
  rtDW->A_minus_I[5] = rtU->lambda_dq;
  rtDW->A_minus_I[9] = 0.0F;
  rtDW->A_minus_I[13] = 0.0F;
  rtDW->A_minus_I[2] = 0.0F;
  rtDW->A_minus_I[6] = 0.0F;
  rtDW->A_minus_I[10] = rtU->lambda_xy;
  rtDW->A_minus_I[14] = 0.0F;
  rtDW->A_minus_I[3] = 0.0F;
  rtDW->A_minus_I[7] = 0.0F;
  rtDW->A_minus_I[11] = 0.0F;
  rtDW->A_minus_I[15] = rtU->lambda_xy;

  /* '<S9>:1:9' i_ref = [id_ref iq_ref ix_ref iy_ref]'; */
  /* '<S9>:1:10' e_i = i_ref - i_delay; */
  rtDW->d_obs[0] = rtU->i_d_ref_pu - rtDW->v_t0[0];
  rtDW->d_obs[1] = rtU->i_q_ref_pu - rtDW->v_t0[1];
  rtDW->d_obs[2] = rtU->i_x_ref_pu - rtDW->v_t0[2];
  rtDW->d_obs[3] = rtU->i_y_ref_pu - rtDW->v_t0[3];

  /* '<S9>:1:12' r = [e_i; e_i; e_i; e_i; e_i; e_i; lam*e_i]; */
  /* '<S9>:1:14' zer = zeros(4,1); */
  /* '<S9>:1:15' m0_lam = lam*m0; */
  /* '<S9>:1:16' m1_lam = lam*m1; */
  /* '<S9>:1:17' m2_lam = lam*m2; */
  /* '<S9>:1:18' m3_lam = lam*m3; */
  /* '<S9>:1:19' m4_lam = lam*m4; */
  /* '<S9>:1:20' m5_lam = lam*m5; */
  /* '<S9>:1:21' m6_lam = m0_lam; */
  /* '<S9>:1:23' M = [m0     zer     zer     zer     zer     zer     zer; */
  /* '<S9>:1:24'      m0     m1      zer     zer     zer     zer     zer; */
  /* '<S9>:1:25'      m0     m1      m2      zer     zer     zer     zer; */
  /* '<S9>:1:26'      m0     m1      m2      m3      zer     zer     zer; */
  /* '<S9>:1:27'      m0     m1      m2      m3      m4      zer     zer; */
  /* '<S9>:1:28'      m0     m1      m2      m3      m4      m5      zer; */
  /* '<S9>:1:29'      m0_lam m1_lam  m2_lam  m3_lam  m4_lam  m5_lam  m6_lam]; */
  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    rtDW->r[rtDW->d_j] = rtDW->d_obs[rtDW->d_j];
    rtDW->r[rtDW->d_j + 4] = rtDW->d_obs[rtDW->d_j];
    rtDW->r[rtDW->d_j + 8] = rtDW->d_obs[rtDW->d_j];
    rtDW->r[rtDW->d_j + 12] = rtDW->d_obs[rtDW->d_j];
    rtDW->r[rtDW->d_j + 16] = rtDW->d_obs[rtDW->d_j];
    rtDW->r[rtDW->d_j + 20] = rtDW->d_obs[rtDW->d_j];
    rtDW->x0_idx_1 = rtDW->A_minus_I[rtDW->d_j + 4];
    rtDW->x0_idx_2 = rtDW->A_minus_I[rtDW->d_j + 8];
    rtDW->x0_idx_3 = rtDW->A_minus_I[rtDW->d_j + 12];
    rtDW->r[rtDW->d_j + 24] = rtDW->x0_idx_3 * rtDW->d_obs[3] + (rtDW->x0_idx_2 *
      rtDW->d_obs[2] + (rtDW->x0_idx_1 * rtDW->d_obs[1] + rtDW->A_minus_I
                        [rtDW->d_j] * rtDW->d_obs[0]));
    rtDW->x0_idx_0 = rtDW->A_minus_I[rtDW->d_j];
    rtDW->w6theta_el_tmp = rtDW->x0_idx_3 * rtDW->m6[3] + (rtDW->x0_idx_2 *
      rtDW->m6[2] + (rtDW->x0_idx_1 * rtDW->m6[1] + rtDW->x0_idx_0 * rtDW->m6[0]));
    rtDW->M[rtDW->d_j] = rtDW->m6[rtDW->d_j];
    rtDW->M[rtDW->d_j + 28] = 0.0F;
    rtDW->M[rtDW->d_j + 56] = 0.0F;
    rtDW->M[rtDW->d_j + 84] = 0.0F;
    rtDW->M[rtDW->d_j + 112] = 0.0F;
    rtDW->M[rtDW->d_j + 140] = 0.0F;
    rtDW->M[rtDW->d_j + 168] = 0.0F;
    rtDW->M[rtDW->d_j + 4] = rtDW->m6[rtDW->d_j];
    rtDW->M[rtDW->d_j + 32] = rtDW->m1[rtDW->d_j];
    rtDW->M[rtDW->d_j + 60] = 0.0F;
    rtDW->M[rtDW->d_j + 88] = 0.0F;
    rtDW->M[rtDW->d_j + 116] = 0.0F;
    rtDW->M[rtDW->d_j + 144] = 0.0F;
    rtDW->M[rtDW->d_j + 172] = 0.0F;
    rtDW->M[rtDW->d_j + 8] = rtDW->m6[rtDW->d_j];
    rtDW->M[rtDW->d_j + 36] = rtDW->m1[rtDW->d_j];
    rtDW->M[rtDW->d_j + 64] = rtDW->m2[rtDW->d_j];
    rtDW->M[rtDW->d_j + 92] = 0.0F;
    rtDW->M[rtDW->d_j + 120] = 0.0F;
    rtDW->M[rtDW->d_j + 148] = 0.0F;
    rtDW->M[rtDW->d_j + 176] = 0.0F;
    rtDW->M[rtDW->d_j + 12] = rtDW->m6[rtDW->d_j];
    rtDW->M[rtDW->d_j + 40] = rtDW->m1[rtDW->d_j];
    rtDW->M[rtDW->d_j + 68] = rtDW->m2[rtDW->d_j];
    rtDW->M[rtDW->d_j + 96] = rtDW->m3[rtDW->d_j];
    rtDW->M[rtDW->d_j + 124] = 0.0F;
    rtDW->M[rtDW->d_j + 152] = 0.0F;
    rtDW->M[rtDW->d_j + 180] = 0.0F;
    rtDW->M[rtDW->d_j + 16] = rtDW->m6[rtDW->d_j];
    rtDW->M[rtDW->d_j + 44] = rtDW->m1[rtDW->d_j];
    rtDW->M[rtDW->d_j + 72] = rtDW->m2[rtDW->d_j];
    rtDW->M[rtDW->d_j + 100] = rtDW->m3[rtDW->d_j];
    rtDW->M[rtDW->d_j + 128] = rtDW->m4[rtDW->d_j];
    rtDW->M[rtDW->d_j + 156] = 0.0F;
    rtDW->M[rtDW->d_j + 184] = 0.0F;
    rtDW->M[rtDW->d_j + 20] = rtDW->m6[rtDW->d_j];
    rtDW->M[rtDW->d_j + 48] = rtDW->m1[rtDW->d_j];
    rtDW->M[rtDW->d_j + 76] = rtDW->m2[rtDW->d_j];
    rtDW->M[rtDW->d_j + 104] = rtDW->m3[rtDW->d_j];
    rtDW->M[rtDW->d_j + 132] = rtDW->m4[rtDW->d_j];
    rtDW->M[rtDW->d_j + 160] = rtDW->m5[rtDW->d_j];
    rtDW->M[rtDW->d_j + 188] = 0.0F;
    rtDW->M[rtDW->d_j + 24] = rtDW->w6theta_el_tmp;
    rtDW->M[rtDW->d_j + 52] = rtDW->x0_idx_3 * rtDW->m1[3] + (rtDW->x0_idx_2 *
      rtDW->m1[2] + (rtDW->x0_idx_1 * rtDW->m1[1] + rtDW->x0_idx_0 * rtDW->m1[0]));
    rtDW->M[rtDW->d_j + 80] = rtDW->x0_idx_3 * rtDW->m2[3] + (rtDW->x0_idx_2 *
      rtDW->m2[2] + (rtDW->x0_idx_1 * rtDW->m2[1] + rtDW->x0_idx_0 * rtDW->m2[0]));
    rtDW->M[rtDW->d_j + 108] = rtDW->x0_idx_3 * rtDW->m3[3] + (rtDW->x0_idx_2 *
      rtDW->m3[2] + (rtDW->x0_idx_1 * rtDW->m3[1] + rtDW->x0_idx_0 * rtDW->m3[0]));
    rtDW->M[rtDW->d_j + 136] = rtDW->x0_idx_3 * rtDW->m4[3] + (rtDW->x0_idx_2 *
      rtDW->m4[2] + (rtDW->x0_idx_1 * rtDW->m4[1] + rtDW->x0_idx_0 * rtDW->m4[0]));
    rtDW->M[rtDW->d_j + 164] = rtDW->x0_idx_3 * rtDW->m5[3] + (rtDW->x0_idx_2 *
      rtDW->m5[2] + (rtDW->x0_idx_1 * rtDW->m5[1] + rtDW->x0_idx_0 * rtDW->m5[0]));
    rtDW->M[rtDW->d_j + 192] = rtDW->w6theta_el_tmp;
  }

  /* '<S9>:1:31' H = 2*(M'*M); */
  /* '<S9>:1:32' f = 2*M'*r; */
  /* MATLAB Function 'uz_codegen/qp_solver': '<S10>:1' */
  /* '<S10>:1:3' t_opt = single([0.25 0 0 0 0 0 0.25]'); */
  /* '<S10>:1:5' iter = single(0); */
  /*  contraints */
  /*             t1 t2 t3 t4 t5 t6 t7 */
  /* '<S10>:1:9' A = single([-1  0  0  0  0  0  0;   % t>=0 is converted to -1*t<=0 */
  /* '<S10>:1:10'              0 -1  0  0  0  0  0;   % no row=no of ineq constraints */
  /* '<S10>:1:11'              0  0 -1  0  0  0  0;   % no columns=no of optimization variables */
  /* '<S10>:1:12'              0  0  0 -1  0  0  0; */
  /* '<S10>:1:13'              0  0  0  0 -1  0  0; */
  /* '<S10>:1:14'              0  0  0  0  0 -1  0; */
  /* '<S10>:1:15'              0  0  0  0  0  0 -1]); */
  /*  t>=0 is converted to -1*t<=0 */
  /*  no row=no of ineq constraints */
  /*  no columns=no of optimization variables */
  /* '<S10>:1:17' b = single(zeros(7,1)); */
  /*  Equality constraints */
  /*  force symmetrical zero vectors */
  /* '<S10>:1:22' Aeq = single([1 1 1 1 1 1 1; */
  /* '<S10>:1:23'               1 0 0 0 0 0 -1]); */
  /* '<S10>:1:24' beq =  single([0.5;0]); */
  /*  sum of all duration times  */
  /*  % do not force symmetrical zero vectors */
  /*  Aeq = single([1 1 1 1 1 1 1]); */
  /*  beq =  single(0.5);          % sum of all duration times  */
  /*  define cold start for active-set solver */
  /* '<S10>:1:31' iA0 = false(size(b)); */
  /*  [x_opt,iter] = mpc_solve(H,f,A,b,Aeq,beq,iA0,max_iter,tol); */
  /* '<S10>:1:34' [t_opt,iter] = mpc_quadprog(H,f,A,b,Aeq,beq,x0); */
  /*  set up quadprog solver */
  /* '<S10>:1:65' quadprog_options = optimoptions('quadprog','Algorithm','active-set','OptimalityTolerance',1e-6,'MaxIterations',7); */
  /*  make variables double - quadprog accepts only double */
  /* '<S10>:1:68' H_d = double(H); */
  /* '<S10>:1:69' f_d = double(f); */
  /* '<S10>:1:70' A_d = double(A); */
  /* '<S10>:1:71' b_d = double(b); */
  /* '<S10>:1:72' Aeq_d = double(Aeq); */
  /* '<S10>:1:73' beq_d = double(beq); */
  /* '<S10>:1:74' x0_d = double(x0); */
  /*  define warmstart object */
  /*      ws = optimwarmstart(x0_d,quadprog_options,'MaxLinearEqualities',7,'MaxLinearInequalities',7); */
  /*  without warstart */
  /* '<S10>:1:80' [x_tmp, fval, exitflag, output] = quadprog(H_d,-f_d,A_d,b_d,Aeq_d,beq_d,[],[],x0_d,quadprog_options); */
  for (rtDW->i = 0; rtDW->i < 7; rtDW->i++) {
    /* Delay: '<S1>/Delay2' */
    if (rtDW->icLoad_o) {
      rtDW->Delay2_DSTATE[rtDW->i] = 0.14F;
    }

    /* MATLAB Function: '<S1>/formulate_qp' */
    for (rtDW->d_j = 0; rtDW->d_j < 7; rtDW->d_j++) {
      rtDW->ix = rtDW->i + 7 * rtDW->d_j;
      rtDW->rtb_M_b[rtDW->ix] = 0.0F;
      for (rtDW->iy = 0; rtDW->iy < 28; rtDW->iy++) {
        rtDW->rtb_M_b[rtDW->ix] += rtDW->M[28 * rtDW->i + rtDW->iy] * rtDW->M[28
          * rtDW->d_j + rtDW->iy];
      }
    }
  }

  /* MATLAB Function: '<S1>/qp_solver' incorporates:
   *  Delay: '<S1>/Delay2'
   *  MATLAB Function: '<S1>/formulate_qp'
   */
  for (rtDW->d_j = 0; rtDW->d_j < 49; rtDW->d_j++) {
    rtDW->dv[rtDW->d_j] = 2.0F * rtDW->rtb_M_b[rtDW->d_j];
  }

  for (rtDW->d_j = 0; rtDW->d_j < 7; rtDW->d_j++) {
    rtDW->w6theta_el = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 28; rtDW->iy++) {
      rtDW->w6theta_el += rtDW->M[28 * rtDW->d_j + rtDW->iy] * 2.0F * rtDW->
        r[rtDW->iy];
    }

    rtDW->dv1[rtDW->d_j] = -(real_T)rtDW->w6theta_el;
    rtDW->dv2[rtDW->d_j] = rtDW->Delay2_DSTATE[rtDW->d_j];
  }

  quadprog(rtDW->dv, rtDW->dv1, rtDW->dv2, rtDW->x_tmp, &rtDW->fval,
           &rtDW->exitflag, rtDW->expl_temp_f, &rtDW->expl_temp_c,
           &rtDW->expl_temp_b, &rtDW->output_iterations, rtDW);

  /* Gain: '<S1>/Gain1' incorporates:
   *  MATLAB Function: '<S1>/qp_solver'
   */
  /* '<S10>:1:81' x = single(x_tmp(1:7,1)); */
  /*  with warmstart -> is not faster (actually slower) on embedded target */
  /*  than coldstart */
  /*      [wsout, fval, exitflag, output] = quadprog(H_d,-f_d,A_d,b_d,Aeq_d,beq_d,[],[],ws) */
  /*      x = single(wsout.X(1:7,1)); */
  /* '<S10>:1:88' iter = single(output.iterations); */
  for (rtDW->i = 0; rtDW->i < 7; rtDW->i++) {
    rtDW->Gain1[rtDW->i] = 2.0F * (real32_T)rtDW->x_tmp[rtDW->i];
  }

  /* End of Gain: '<S1>/Gain1' */

  /* Outport: '<Root>/dob_error_estimate' */
  /* MATLAB Function 'uz_codegen/t_to_d': '<S12>:1' */
  /* '<S12>:1:3' I = single([1 0 0 0 0 0; */
  /* '<S12>:1:4'             1 1 0 0 0 0; */
  /* '<S12>:1:5'             1 1 1 0 0 0; */
  /* '<S12>:1:6'             1 1 1 1 0 0; */
  /* '<S12>:1:7'             1 1 1 1 1 0; */
  /* '<S12>:1:8'             1 1 1 1 1 1]); */
  /* '<S12>:1:10' zer6 = single(zeros(6,1)); */
  /* '<S12>:1:12' T = single([I zer6]); */
  /* '<S12>:1:14' d=single(T*t); */
  rtY->dob_error_estimate[0] = rtDW->rtb_d_dq_obs_idx_0;
  rtY->dob_error_estimate[2] = rtDW->rtb_d_xy_obs_idx_0;
  rtY->dob_error_estimate[1] = rtDW->rtb_v_t0_idx_3;
  rtY->dob_error_estimate[3] = rtDW->rtb_v_t0_idx_2;

  /* MATLAB Function 'uz_codegen/d_2_ph': '<S6>:1' */
  /* '<S6>:1:3' seq_order_table = single([4,1,6,2,3,5; */
  /* '<S6>:1:4'     1,4,2,6,5,3; */
  /* '<S6>:1:5'     1,4,2,5,6,3; */
  /* '<S6>:1:6'     4,1,2,5,3,6; */
  /* '<S6>:1:7'     4,2,1,5,3,6; */
  /* '<S6>:1:8'     2,4,5,1,6,3; */
  /* '<S6>:1:9'     2,5,4,1,6,3; */
  /* '<S6>:1:10'     5,2,4,1,3,6; */
  /* '<S6>:1:11'     5,2,4,3,1,6; */
  /* '<S6>:1:12'     2,5,3,4,6,1; */
  /* '<S6>:1:13'     2,5,3,6,4,1; */
  /* '<S6>:1:14'     5,2,3,6,1,4; */
  /* '<S6>:1:15'     5,3,2,6,1,4; */
  /* '<S6>:1:16'     3,5,6,2,4,1; */
  /* '<S6>:1:17'     3,6,5,2,4,1; */
  /* '<S6>:1:18'     6,3,5,2,1,4; */
  /* '<S6>:1:19'     6,3,5,1,2,4; */
  /* '<S6>:1:20'     3,6,1,5,4,2; */
  /* '<S6>:1:21'     3,6,1,4,5,2; */
  /* '<S6>:1:22'     6,3,1,4,2,5; */
  /* '<S6>:1:23'     6,1,3,4,2,5; */
  /* '<S6>:1:24'     1,6,4,3,5,2; */
  /* '<S6>:1:25'     1,4,6,3,5,2; */
  /* '<S6>:1:26'     4,1,6,3,2,5]); */
  /* '<S6>:1:28' t = single(zeros(6,1)); */
  for (rtDW->i = 0; rtDW->i < 6; rtDW->i++) {
    /* MATLAB Function: '<S1>/t_to_d' */
    rtDW->d[rtDW->i] = 0.0F;
    for (rtDW->d_j = 0; rtDW->d_j < 7; rtDW->d_j++) {
      rtDW->d[rtDW->i] += (real32_T)a[6 * rtDW->d_j + rtDW->i] * rtDW->
        Gain1[rtDW->d_j];
    }

    /* End of MATLAB Function: '<S1>/t_to_d' */

    /* MATLAB Function: '<S1>/d_2_ph' */
    rtDW->t_l[rtDW->i] = 0.0F;
  }

  /* MATLAB Function: '<S1>/d_2_ph' */
  /* '<S6>:1:30' for i=1:6 */
  for (rtDW->iy = 0; rtDW->iy < 6; rtDW->iy++) {
    /* '<S6>:1:31' t(seq_order_table(seq_no,i),1) = d(i); */
    rtDW->t_l[seq_order_table[(rtDW->sector_ref + 24 * rtDW->iy) - 1] - 1] =
      rtDW->d[rtDW->iy];
  }

  /* Outport: '<Root>/d_opt' incorporates:
   *  MATLAB Function: '<S1>/d_2_ph'
   */
  /* '<S6>:1:34' da_1 = t(1); */
  /* '<S6>:1:35' db_1 = t(2); */
  /* '<S6>:1:36' dc_1 = t(3); */
  /* '<S6>:1:37' da_2 = t(4); */
  /* '<S6>:1:38' db_2 = t(5); */
  /* '<S6>:1:39' dc_2 = t(6); */
  rtY->d_opt[0] = rtDW->t_l[0];
  rtY->d_opt[1] = rtDW->t_l[1];
  rtY->d_opt[2] = rtDW->t_l[2];
  rtY->d_opt[3] = rtDW->t_l[3];
  rtY->d_opt[4] = rtDW->t_l[4];
  rtY->d_opt[5] = rtDW->t_l[5];

  /* Outport: '<Root>/iterations_qp' incorporates:
   *  MATLAB Function: '<S1>/qp_solver'
   */
  rtY->iterations_qp = (real32_T)rtDW->output_iterations;

  /* Update for Delay: '<S1>/Delay13' */
  rtDW->icLoad = false;

  /* Update for Delay: '<S1>/Delay' */
  rtDW->Delay_DSTATE[0] = rtDW->rtb_i_dq_obs_idx_0;

  /* Update for Delay: '<S1>/Delay9' */
  rtDW->Delay9_DSTATE[0] = rtDW->rtb_v_2_idx_pu_idx_0;

  /* Update for Delay: '<S1>/Delay10' */
  rtDW->Delay10_DSTATE[0] = rtDW->rtb_v_3_idx_pu_idx_0;

  /* Update for Delay: '<S1>/Delay11' */
  rtDW->Delay11_DSTATE[0] = rtDW->rtb_v_4_idx_pu_idx_0;

  /* Update for Delay: '<S1>/Delay12' */
  rtDW->Delay12_DSTATE[0] = rtDW->rtb_v_5_idx_pu_idx_0;

  /* Update for Delay: '<S1>/Delay' */
  rtDW->Delay_DSTATE[1] = rtDW->rtb_v_1_idx_pu_idx_1;

  /* Update for Delay: '<S1>/Delay9' */
  rtDW->Delay9_DSTATE[1] = rtDW->rtb_v_2_idx_pu_idx_1;

  /* Update for Delay: '<S1>/Delay10' */
  rtDW->Delay10_DSTATE[1] = rtDW->rtb_v_3_idx_pu_idx_1;

  /* Update for Delay: '<S1>/Delay11' */
  rtDW->Delay11_DSTATE[1] = rtDW->rtb_v_4_idx_pu_idx_1;

  /* Update for Delay: '<S1>/Delay12' */
  rtDW->Delay12_DSTATE[1] = rtDW->rtb_v_5_idx_pu_idx_1;

  /* Update for Delay: '<S1>/Delay' */
  rtDW->Delay_DSTATE[2] = rtDW->q;

  /* Update for Delay: '<S1>/Delay9' */
  rtDW->Delay9_DSTATE[2] = rtDW->rtb_v_2_idx_pu_idx_2;

  /* Update for Delay: '<S1>/Delay10' */
  rtDW->Delay10_DSTATE[2] = rtDW->rtb_v_3_idx_pu_idx_2;

  /* Update for Delay: '<S1>/Delay11' */
  rtDW->Delay11_DSTATE[2] = rtDW->rtb_v_4_idx_pu_idx_2;

  /* Update for Delay: '<S1>/Delay12' */
  rtDW->Delay12_DSTATE[2] = rtDW->rtb_v_5_idx_pu_idx_2;

  /* Update for Delay: '<S1>/Delay' */
  rtDW->Delay_DSTATE[3] = rtDW->rtb_v_1_idx_pu_idx_3;

  /* Update for Delay: '<S1>/Delay9' */
  rtDW->Delay9_DSTATE[3] = rtDW->rtb_v_2_idx_pu_idx_3;

  /* Update for Delay: '<S1>/Delay10' */
  rtDW->Delay10_DSTATE[3] = rtDW->rtb_v_3_idx_pu_idx_3;

  /* Update for Delay: '<S1>/Delay11' */
  rtDW->Delay11_DSTATE[3] = rtDW->rtb_v_4_idx_pu_idx_3;

  /* Update for Delay: '<S1>/Delay12' */
  rtDW->Delay12_DSTATE[3] = rtDW->rtb_v_5_idx_pu_idx_3;

  /* Update for Delay: '<S1>/Delay1' */
  rtDW->icLoad_f = false;

  /* Update for Delay: '<S1>/Delay3' */
  rtDW->icLoad_l = false;

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->icLoad_a = false;

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->icLoad_f4 = false;

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->icLoad_ag = false;

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->icLoad_i = false;

  /* Update for Delay: '<S1>/Delay8' */
  rtDW->icLoad_ik = false;

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/current_gradient_prediction'
   */
  rtDW->Delay3_DSTATE[0] = rtDW->m6[0];

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->Delay4_DSTATE[0] = rtDW->m1[0];

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->Delay5_DSTATE[0] = rtDW->m2[0];

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->Delay6_DSTATE[0] = rtDW->m3[0];

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->Delay7_DSTATE[0] = rtDW->m4[0];

  /* Update for Delay: '<S1>/Delay8' */
  rtDW->Delay8_DSTATE[0] = rtDW->m5[0];

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/current_gradient_prediction'
   */
  rtDW->Delay3_DSTATE[1] = rtDW->m6[1];

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->Delay4_DSTATE[1] = rtDW->m1[1];

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->Delay5_DSTATE[1] = rtDW->m2[1];

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->Delay6_DSTATE[1] = rtDW->m3[1];

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->Delay7_DSTATE[1] = rtDW->m4[1];

  /* Update for Delay: '<S1>/Delay8' */
  rtDW->Delay8_DSTATE[1] = rtDW->m5[1];

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/current_gradient_prediction'
   */
  rtDW->Delay3_DSTATE[2] = rtDW->m6[2];

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->Delay4_DSTATE[2] = rtDW->m1[2];

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->Delay5_DSTATE[2] = rtDW->m2[2];

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->Delay6_DSTATE[2] = rtDW->m3[2];

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->Delay7_DSTATE[2] = rtDW->m4[2];

  /* Update for Delay: '<S1>/Delay8' */
  rtDW->Delay8_DSTATE[2] = rtDW->m5[2];

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/current_gradient_prediction'
   */
  rtDW->Delay3_DSTATE[3] = rtDW->m6[3];

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->Delay4_DSTATE[3] = rtDW->m1[3];

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->Delay5_DSTATE[3] = rtDW->m2[3];

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->Delay6_DSTATE[3] = rtDW->m3[3];

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->Delay7_DSTATE[3] = rtDW->m4[3];

  /* Update for Delay: '<S1>/Delay8' */
  rtDW->Delay8_DSTATE[3] = rtDW->m5[3];

  /* Update for Delay: '<S1>/Delay2' */
  rtDW->icLoad_o = false;
  for (rtDW->i = 0; rtDW->i < 7; rtDW->i++) {
    /* Update for Delay: '<S1>/Delay13' */
    rtDW->rtb_d_xy_obs_idx_0 = rtDW->Gain1[rtDW->i];
    rtDW->Delay13_DSTATE[rtDW->i] = rtDW->rtb_d_xy_obs_idx_0;

    /* Update for Delay: '<S1>/Delay1' */
    rtDW->Delay1_DSTATE[rtDW->i] = rtDW->rtb_d_xy_obs_idx_0;

    /* Update for Delay: '<S1>/Delay2' */
    rtDW->Delay2_DSTATE[rtDW->i] = rtDW->rtb_d_xy_obs_idx_0;
  }
}

/* Model initialize function */
void uz_codegen0_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  (void) memset((void *)rtY, 0,
                sizeof(ExtY));

  {
    int32_T i;
    static const int8_T b[8] = { 100, 100, 100, 100, 1, 1, 1, 1 };

    /* InitializeConditions for Delay: '<S1>/Delay13' */
    rtDW->icLoad = true;

    /* InitializeConditions for Delay: '<S1>/Delay1' */
    rtDW->icLoad_f = true;

    /* InitializeConditions for Delay: '<S1>/Delay3' */
    rtDW->icLoad_l = true;

    /* InitializeConditions for Delay: '<S1>/Delay4' */
    rtDW->icLoad_a = true;

    /* InitializeConditions for Delay: '<S1>/Delay5' */
    rtDW->icLoad_f4 = true;

    /* InitializeConditions for Delay: '<S1>/Delay6' */
    rtDW->icLoad_ag = true;

    /* InitializeConditions for Delay: '<S1>/Delay7' */
    rtDW->icLoad_i = true;

    /* InitializeConditions for Delay: '<S1>/Delay8' */
    rtDW->icLoad_ik = true;

    /* InitializeConditions for Delay: '<S1>/Delay2' */
    rtDW->icLoad_o = true;

    /* SystemInitialize for MATLAB Function: '<S1>/Observer' */
    /* '<S3>:1:75' x_e = single([0;0;0;0;0;0;0;0]); */
    for (i = 0; i < 8; i++) {
      rtDW->x_e[i] = 0.0F;
    }

    /*     P_e = single(diag([0.1 0.1 0.1 0.1 100 100 100 100])); */
    /* '<S3>:1:77' P_e = single(diag([100 100 100 100 1 1 1 1])); */
    memset(&rtDW->d_o[0], 0, sizeof(int8_T) << 6U);
    for (i = 0; i < 8; i++) {
      rtDW->d_o[i + (i << 3)] = b[i];
    }

    for (i = 0; i < 64; i++) {
      rtDW->P_e[i] = rtDW->d_o[i];
    }

    /* End of SystemInitialize for MATLAB Function: '<S1>/Observer' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
