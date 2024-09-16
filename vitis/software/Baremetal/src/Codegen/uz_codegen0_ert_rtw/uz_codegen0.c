/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.15
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Sep 16 13:52:28 2024
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
static void factoryConstruct(s1hK3o0EyOqKKjEgDlbhqfF *obj);
static real_T xnrm2(int32_T n, const real_T x[72], int32_T ix0, DW *rtDW);
static real_T xzlarfg(int32_T n, real_T *alpha1, real_T x[72], int32_T ix0, DW
                      *rtDW);
static void xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau, real_T C[72],
                   int32_T ic0, real_T work[9], DW *rtDW);
static void qrf(real_T A[72], int32_T ia0, int32_T m, int32_T n, int32_T nfxd,
                real_T tau[8], DW *rtDW);
static void xzgeqp3(real_T A[72], int32_T ia0, int32_T m, int32_T n, int32_T
                    jpvt[9], real_T tau[8], DW *rtDW);
static void computeQ_(sQyCFUyu0YXOk1LARsZMzaD *obj, int32_T nrows, DW *rtDW);
static int32_T ComputeNumDependentEq_(sQyCFUyu0YXOk1LARsZMzaD *qrmanager, DW
  *rtDW);
static void countsort(int32_T x[9], int32_T xLen, int32_T workspace[9], int32_T
                      xMin, int32_T xMax);
static void moveConstraint_(swcr9qLPQBiG4lNhaNdYq5G *obj, int32_T
  idx_global_start, int32_T idx_global_dest);
static void removeEqConstr(swcr9qLPQBiG4lNhaNdYq5G *obj, int32_T idx_global);
static void RemoveDependentEq_(s9NoAX0P67ji2P1ZBafS3UG *memspace, int32_T
  *nDepInd, swcr9qLPQBiG4lNhaNdYq5G *workingset, sQyCFUyu0YXOk1LARsZMzaD
  *qrmanager, DW *rtDW);
static void removeAllIneqConstr(swcr9qLPQBiG4lNhaNdYq5G *obj);
static void RemoveDependentIneq_(swcr9qLPQBiG4lNhaNdYq5G *workingset,
  sQyCFUyu0YXOk1LARsZMzaD *qrmanager, s9NoAX0P67ji2P1ZBafS3UG *memspace, real_T
  tolfactor, DW *rtDW);
static void factorQR_f(sQyCFUyu0YXOk1LARsZMzaD *obj, const real_T A[72], int32_T
  mrows, int32_T ncols, int32_T ldA, DW *rtDW);
static void factorQR(sQyCFUyu0YXOk1LARsZMzaD *obj, int32_T mrows, int32_T ncols,
                     DW *rtDW);
static void xgemv(int32_T m, int32_T n, const real_T A[56], int32_T lda, const
                  real_T x[72], real_T y[9], DW *rtDW);
static void xgemv_n(int32_T m, int32_T n, const real_T A[8], int32_T lda, const
                    real_T x[72], real_T y[9], DW *rtDW);
static real_T maxConstraintViolation(swcr9qLPQBiG4lNhaNdYq5G *obj, const real_T
  x[72], DW *rtDW);
static void xgemv_nh(int32_T m, int32_T n, const real_T A[56], int32_T lda,
                     const real_T x[72], real_T y[9], DW *rtDW);
static void xgemv_nhu(int32_T m, int32_T n, const real_T A[8], int32_T lda,
                      const real_T x[72], real_T y[9], DW *rtDW);
static real_T maxConstraintViolation_e(swcr9qLPQBiG4lNhaNdYq5G *obj, const
  real_T x[72], DW *rtDW);
static void feasibleX0ForWorkingSet(real_T workspace[72], real_T xCurrent[8],
  swcr9qLPQBiG4lNhaNdYq5G *workingset, sQyCFUyu0YXOk1LARsZMzaD *qrmanager, DW
  *rtDW);
static void xgemv_nhum(int32_T m, int32_T n, const real_T A[56], int32_T lda,
  const real_T x[8], real_T y[9], DW *rtDW);
static void xgemv_nhumt(int32_T m, int32_T n, const real_T A[8], int32_T lda,
  const real_T x[8], real_T y[9], DW *rtDW);
static real_T maxConstraintViolation_eo(swcr9qLPQBiG4lNhaNdYq5G *obj, const
  real_T x[8], DW *rtDW);
static void PresolveWorkingSet(svV6yPD1e8CTJu8b18IprLB *solution,
  s9NoAX0P67ji2P1ZBafS3UG *memspace, swcr9qLPQBiG4lNhaNdYq5G *workingset,
  sQyCFUyu0YXOk1LARsZMzaD *qrmanager, DW *rtDW);
static void modifyOverheadPhaseOne_(swcr9qLPQBiG4lNhaNdYq5G *obj);
static void setProblemType(swcr9qLPQBiG4lNhaNdYq5G *obj, int32_T PROBLEM_TYPE);
static void linearForm_(boolean_T obj_hasLinear, int32_T obj_nvar, real_T
  workspace[72], const real_T H[49], const real_T f[7], const real_T x[8]);
static real_T computeFval(const shohwUBaOGHF036TMzc1KEH *obj, real_T workspace
  [72], const real_T H[49], const real_T f[7], const real_T x[8]);
static void xgemv_nhumth(int32_T m, int32_T n, const real_T A[49], int32_T lda,
  const real_T x[8], real_T y[7]);
static void computeGrad_StoreHx(shohwUBaOGHF036TMzc1KEH *obj, const real_T H[49],
  const real_T f[7], const real_T x[8]);
static real_T computeFval_ReuseHx(const shohwUBaOGHF036TMzc1KEH *obj, real_T
  workspace[72], const real_T f[7], const real_T x[8]);
static void printHeader(void);
static void printInitialInfo(int32_T PROBLEM_TYPE, real_T solution_fstar,
  int32_T solution_iterations, int32_T workingset_nActiveConstr);
static void xrotg(real_T *a, real_T *b, real_T *c, real_T *s, DW *rtDW);
static void deleteColMoveEnd(sQyCFUyu0YXOk1LARsZMzaD *obj, int32_T idx, DW *rtDW);
static void computeProjectedHessian(const real_T H[49], s1hK3o0EyOqKKjEgDlbhqfF *
  cholmanager, const sQyCFUyu0YXOk1LARsZMzaD *qrmanager, s9NoAX0P67ji2P1ZBafS3UG
  *memspace, DW *rtDW);
static int32_T ixamax(int32_T n, const real_T x[64], int32_T incx);
static void fullColLDL2_(s1hK3o0EyOqKKjEgDlbhqfF *obj, int32_T LD_offset,
  int32_T NColsRemain, real_T REG_PRIMAL);
static void xgemv_nhumtht(int32_T m, int32_T n, const real_T A[64], int32_T ia0,
  int32_T lda, const real_T x[72], real_T y[8]);
static void compute_deltax(const real_T H[49], svV6yPD1e8CTJu8b18IprLB *solution,
  s9NoAX0P67ji2P1ZBafS3UG *memspace, const sQyCFUyu0YXOk1LARsZMzaD *qrmanager,
  s1hK3o0EyOqKKjEgDlbhqfF *cholmanager, const shohwUBaOGHF036TMzc1KEH *objective,
  DW *rtDW);
static real_T xnrm2_l(int32_T n, const real_T x[8]);
static void xgemv_nhumthtw(int32_T m, int32_T n, const real_T A[56], int32_T lda,
  const real_T x[8], real_T y[72]);
static void xgemv_nhumthtwu(int32_T m, int32_T n, const real_T A[56], int32_T
  lda, const real_T x[8], real_T y[72]);
static void ratiotest(const real_T solution_xstar[8], const real_T
                      solution_searchDir[8], real_T workspace[72], int32_T
                      workingset_nVar, int32_T workingset_ldA, const real_T
                      workingset_Aineq[56], const real_T workingset_bineq[7],
                      const real_T workingset_lb[8], const real_T workingset_ub
                      [8], const int32_T workingset_indexLB[8], const int32_T
                      workingset_indexUB[8], const int32_T workingset_sizes[5],
                      const int32_T workingset_isActiveIdx[6], const boolean_T
                      workingset_isActiveConstr[9], const int32_T
                      workingset_nWConstr[5], boolean_T isPhaseOne, real_T
                      tolcon, real_T *toldelta, real_T toltau, real_T *alpha,
                      boolean_T *newBlocking, int32_T *constrType, int32_T
                      *constrIdx, DW *rtDW);
static void feasibleratiotest(const real_T solution_xstar[8], const real_T
  solution_searchDir[8], real_T workspace[72], int32_T workingset_nVar, int32_T
  workingset_ldA, const real_T workingset_Aineq[56], const real_T
  workingset_bineq[7], const real_T workingset_lb[8], const real_T
  workingset_ub[8], const int32_T workingset_indexLB[8], const int32_T
  workingset_indexUB[8], const int32_T workingset_sizes[5], const int32_T
  workingset_isActiveIdx[6], const boolean_T workingset_isActiveConstr[9], const
  int32_T workingset_nWConstr[5], boolean_T isPhaseOne, real_T tolcon, real_T
  *alpha, boolean_T *newBlocking, int32_T *constrType, int32_T *constrIdx, DW
  *rtDW);
static void checkUnboundedOrIllPosed(svV6yPD1e8CTJu8b18IprLB *solution, const
  shohwUBaOGHF036TMzc1KEH *objective);
static void addBoundToActiveSetMatrix_(swcr9qLPQBiG4lNhaNdYq5G *obj, int32_T
  TYPE, int32_T idx_local);
static void compute_lambda(real_T workspace[72], svV6yPD1e8CTJu8b18IprLB
  *solution, const shohwUBaOGHF036TMzc1KEH *objective, const
  sQyCFUyu0YXOk1LARsZMzaD *qrmanager);
static void checkStoppingAndUpdateFval(int32_T *activeSetChangeID, const real_T
  f[7], svV6yPD1e8CTJu8b18IprLB *solution, s9NoAX0P67ji2P1ZBafS3UG *memspace,
  const shohwUBaOGHF036TMzc1KEH *objective, swcr9qLPQBiG4lNhaNdYq5G *workingset,
  sQyCFUyu0YXOk1LARsZMzaD *qrmanager, real_T options_ObjectiveLimit, real_T
  options_ConstraintTolerance, int32_T runTimeOptions_MaxIterations, real_T
  runTimeOptions_ConstrRelTolFact, boolean_T updateFval, DW *rtDW);
static void computeFirstOrderOpt(svV6yPD1e8CTJu8b18IprLB *solution, const
  shohwUBaOGHF036TMzc1KEH *objective, int32_T workingset_nVar, int32_T
  workingset_ldA, const real_T workingset_ATwset[72], int32_T
  workingset_nActiveConstr, real_T workspace[72]);
static void printInfo(boolean_T newBlocking, int32_T PROBLEM_TYPE, real_T alpha,
                      real_T stepNorm, int32_T activeConstrChangedType, int32_T
                      localActiveConstrIdx, int32_T activeSetChangeID, real_T
                      solution_fstar, real_T solution_firstorderopt, real_T
                      solution_maxConstr, int32_T solution_iterations, const
                      int32_T workingset_indexLB[8], const int32_T
                      workingset_indexUB[8], int32_T workingset_nActiveConstr);
static void iterate(const real_T H[49], const real_T f[7],
                    svV6yPD1e8CTJu8b18IprLB *solution, s9NoAX0P67ji2P1ZBafS3UG
                    *memspace, swcr9qLPQBiG4lNhaNdYq5G *workingset,
                    sQyCFUyu0YXOk1LARsZMzaD *qrmanager, s1hK3o0EyOqKKjEgDlbhqfF *
                    cholmanager, shohwUBaOGHF036TMzc1KEH *objective, boolean_T
                    options_IterDisplayQP, real_T options_PricingTolerance,
                    real_T options_ObjectiveLimit, real_T
                    options_ConstraintTolerance, real_T options_StepTolerance,
                    const sL9bDKomAYkxZSVrG9w6En runTimeOptions, DW *rtDW);
static void phaseone(const real_T H[49], const real_T f[7],
                     svV6yPD1e8CTJu8b18IprLB *solution, s9NoAX0P67ji2P1ZBafS3UG *
                     memspace, swcr9qLPQBiG4lNhaNdYq5G *workingset,
                     sQyCFUyu0YXOk1LARsZMzaD *qrmanager, s1hK3o0EyOqKKjEgDlbhqfF
                     *cholmanager, const sL9bDKomAYkxZSVrG9w6En *runTimeOptions,
                     shohwUBaOGHF036TMzc1KEH *objective, s4lHOiXA0GHbse0IgoBY6ZF
                     *options, DW *rtDW);
static int32_T ComputeNumDependentEq__j(sQyCFUyu0YXOk1LARsZMzaD *qrmanager,
  const real_T beqf[9], int32_T mConstr, int32_T nVar, real_T tolfactor, DW
  *rtDW);
static int32_T RemoveDependentEq__a(s9NoAX0P67ji2P1ZBafS3UG *memspace,
  swcr9qLPQBiG4lNhaNdYq5G *workingset, sQyCFUyu0YXOk1LARsZMzaD *qrmanager,
  real_T tolfactor, DW *rtDW);
static void PresolveWorkingSet_m(svV6yPD1e8CTJu8b18IprLB *solution,
  s9NoAX0P67ji2P1ZBafS3UG *memspace, swcr9qLPQBiG4lNhaNdYq5G *workingset,
  sQyCFUyu0YXOk1LARsZMzaD *qrmanager, const s4lHOiXA0GHbse0IgoBY6ZF *options, DW
  *rtDW);
static boolean_T strcmp_o(const char_T a[8]);
static void phaseone_k(const real_T H[49], const real_T f[7],
  svV6yPD1e8CTJu8b18IprLB *solution, s9NoAX0P67ji2P1ZBafS3UG *memspace,
  swcr9qLPQBiG4lNhaNdYq5G *workingset, sQyCFUyu0YXOk1LARsZMzaD *qrmanager,
  s1hK3o0EyOqKKjEgDlbhqfF *cholmanager, shohwUBaOGHF036TMzc1KEH *objective,
  s4lHOiXA0GHbse0IgoBY6ZF *options, const sL9bDKomAYkxZSVrG9w6En *runTimeOptions,
  DW *rtDW);
static void driver(const real_T H[49], const real_T f[7],
                   svV6yPD1e8CTJu8b18IprLB *solution, s9NoAX0P67ji2P1ZBafS3UG
                   *memspace, s1hK3o0EyOqKKjEgDlbhqfF *cholmanager,
                   sL9bDKomAYkxZSVrG9w6En runTimeOptions,
                   swcr9qLPQBiG4lNhaNdYq5G *workingset, sQyCFUyu0YXOk1LARsZMzaD *
                   qrmanager, shohwUBaOGHF036TMzc1KEH *objective, DW *rtDW);
static void linearForm__e(boolean_T obj_hasLinear, int32_T obj_nvar, real_T
  workspace[8], const real_T H[49], const real_T f[7], const real_T x[8]);
static void quadprog(const real_T H[49], const real_T f[7], const real_T x0[7],
                     real_T x[7], real_T *fval, real_T *exitflag, char_T
                     output_algorithm[10], real_T *output_firstorderopt, real_T *
                     output_constrviolation, real_T *output_iterations, DW *rtDW);

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void factoryConstruct(s1hK3o0EyOqKKjEgDlbhqfF *obj)
{
  obj->ldm = 8;
  obj->ndims = 0;
  obj->info = 0;
  obj->scaleFactor = 1.0;
  obj->ConvexCheck = true;
  obj->regTol_ = 0.0;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real_T xnrm2(int32_T n, const real_T x[72], int32_T ix0, DW *rtDW)
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
static real_T xzlarfg(int32_T n, real_T *alpha1, real_T x[72], int32_T ix0, DW
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
static void xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau, real_T C[72],
                   int32_T ic0, real_T work[9], DW *rtDW)
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
      coltop = (lastc << 3) + ic0;
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
      jy = (lastc << 3) + ic0;
      for (iac = ic0; iac <= jy; iac += 8) {
        ix = iv0;
        rtDW->c_c = 0.0;
        d = (iac + lastv) - 1;
        for (ia = iac; ia <= d; ia++) {
          rtDW->c_c += C[ia - 1] * C[ix - 1];
          ix++;
        }

        work[coltop] += rtDW->c_c;
        coltop++;
      }
    }

    if (-tau != 0.0) {
      coltop = ic0 - 1;
      jy = 0;
      for (iac = 0; iac <= lastc; iac++) {
        if (work[jy] != 0.0) {
          rtDW->c_c = work[jy] * -tau;
          ix = iv0;
          d = lastv + coltop;
          for (ia = coltop; ia < d; ia++) {
            C[ia] += C[ix - 1] * rtDW->c_c;
            ix++;
          }
        }

        jy++;
        coltop += 8;
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void qrf(real_T A[72], int32_T ia0, int32_T m, int32_T n, int32_T nfxd,
                real_T tau[8], DW *rtDW)
{
  int32_T i;
  int32_T ii;
  int32_T mmi;
  memset(&rtDW->work[0], 0, 9U * sizeof(real_T));
  for (i = 0; i < nfxd; i++) {
    ii = (((i << 3) + ia0) + i) - 1;
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
      xzlarf(mmi, (n - i) - 1, ii + 1, tau[i], A, ii + 9, rtDW->work, rtDW);
      A[ii] = rtDW->b_atmp;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xzgeqp3(real_T A[72], int32_T ia0, int32_T m, int32_T n, int32_T
                    jpvt[9], real_T tau[8], DW *rtDW)
{
  int32_T b_iy;
  int32_T i;
  int32_T ii_tmp;
  int32_T minmn_tmp;
  if (m < n) {
    minmn_tmp = m;
  } else {
    minmn_tmp = n;
  }

  memset(&tau[0], 0, sizeof(real_T) << 3U);
  if (minmn_tmp < 1) {
    for (minmn_tmp = 0; minmn_tmp < n; minmn_tmp++) {
      jpvt[minmn_tmp] = minmn_tmp + 1;
    }
  } else {
    rtDW->nfxd = -1;
    for (i = 0; i < n; i++) {
      if (jpvt[i] != 0) {
        rtDW->nfxd++;
        if (i + 1 != rtDW->nfxd + 1) {
          rtDW->nmi = ((i << 3) + ia0) - 1;
          rtDW->pvt = ((rtDW->nfxd << 3) + ia0) - 1;
          rtDW->b_ix_j = 0;
          while (rtDW->b_ix_j <= m - 1) {
            rtDW->smax = A[rtDW->nmi];
            A[rtDW->nmi] = A[rtDW->pvt];
            A[rtDW->pvt] = rtDW->smax;
            rtDW->nmi++;
            rtDW->pvt++;
            rtDW->b_ix_j++;
          }

          jpvt[i] = jpvt[rtDW->nfxd];
          jpvt[rtDW->nfxd] = i + 1;
        } else {
          jpvt[i] = i + 1;
        }
      } else {
        jpvt[i] = i + 1;
      }
    }

    if (rtDW->nfxd + 1 < minmn_tmp) {
      rtDW->nfxd++;
    } else {
      rtDW->nfxd = minmn_tmp;
    }

    qrf(A, ia0, m, n, rtDW->nfxd, tau, rtDW);
    if (rtDW->nfxd < minmn_tmp) {
      memset(&rtDW->work_c[0], 0, 9U * sizeof(real_T));
      memset(&rtDW->vn1[0], 0, 9U * sizeof(real_T));
      memset(&rtDW->vn2[0], 0, 9U * sizeof(real_T));
      i = ia0 + rtDW->nfxd;
      rtDW->ii = rtDW->nfxd;
      while (rtDW->ii + 1 <= n) {
        rtDW->vn1[rtDW->ii] = xnrm2(m - rtDW->nfxd, A, (rtDW->ii << 3) + i, rtDW);
        rtDW->vn2[rtDW->ii] = rtDW->vn1[rtDW->ii];
        rtDW->ii++;
      }

      while (rtDW->nfxd + 1 <= minmn_tmp) {
        ii_tmp = (rtDW->nfxd << 3) + ia0;
        rtDW->ii = (ii_tmp + rtDW->nfxd) - 1;
        rtDW->nmi = n - rtDW->nfxd;
        i = m - rtDW->nfxd;
        if (rtDW->nmi < 1) {
          rtDW->pvt = -1;
        } else {
          rtDW->pvt = 0;
          if (rtDW->nmi > 1) {
            rtDW->b_ix_j = rtDW->nfxd;
            rtDW->smax = fabs(rtDW->vn1[rtDW->nfxd]);
            for (b_iy = 2; b_iy <= rtDW->nmi; b_iy++) {
              rtDW->b_ix_j++;
              rtDW->temp2 = fabs(rtDW->vn1[rtDW->b_ix_j]);
              if (rtDW->temp2 > rtDW->smax) {
                rtDW->pvt = b_iy - 1;
                rtDW->smax = rtDW->temp2;
              }
            }
          }
        }

        rtDW->pvt += rtDW->nfxd;
        if (rtDW->pvt + 1 != rtDW->nfxd + 1) {
          rtDW->b_ix_j = ((rtDW->pvt << 3) + ia0) - 1;
          b_iy = ii_tmp - 1;
          for (ii_tmp = 0; ii_tmp < m; ii_tmp++) {
            rtDW->smax = A[rtDW->b_ix_j];
            A[rtDW->b_ix_j] = A[b_iy];
            A[b_iy] = rtDW->smax;
            rtDW->b_ix_j++;
            b_iy++;
          }

          rtDW->b_ix_j = jpvt[rtDW->pvt];
          jpvt[rtDW->pvt] = jpvt[rtDW->nfxd];
          jpvt[rtDW->nfxd] = rtDW->b_ix_j;
          rtDW->vn1[rtDW->pvt] = rtDW->vn1[rtDW->nfxd];
          rtDW->vn2[rtDW->pvt] = rtDW->vn2[rtDW->nfxd];
        }

        if (rtDW->nfxd + 1 < m) {
          rtDW->smax = A[rtDW->ii];
          tau[rtDW->nfxd] = xzlarfg(i, &rtDW->smax, A, rtDW->ii + 2, rtDW);
          A[rtDW->ii] = rtDW->smax;
        } else {
          tau[rtDW->nfxd] = 0.0;
        }

        if (rtDW->nfxd + 1 < n) {
          rtDW->smax = A[rtDW->ii];
          A[rtDW->ii] = 1.0;
          xzlarf(i, rtDW->nmi - 1, rtDW->ii + 1, tau[rtDW->nfxd], A, rtDW->ii +
                 9, rtDW->work_c, rtDW);
          A[rtDW->ii] = rtDW->smax;
        }

        rtDW->ii = rtDW->nfxd + 1;
        while (rtDW->ii + 1 <= n) {
          rtDW->nmi = (ia0 + rtDW->nfxd) + (rtDW->ii << 3);
          if (rtDW->vn1[rtDW->ii] != 0.0) {
            rtDW->smax = fabs(A[rtDW->nmi - 1]) / rtDW->vn1[rtDW->ii];
            rtDW->smax = 1.0 - rtDW->smax * rtDW->smax;
            if (rtDW->smax < 0.0) {
              rtDW->smax = 0.0;
            }

            rtDW->temp2 = rtDW->vn1[rtDW->ii] / rtDW->vn2[rtDW->ii];
            rtDW->temp2 = rtDW->temp2 * rtDW->temp2 * rtDW->smax;
            if (rtDW->temp2 <= 1.4901161193847656E-8) {
              if (rtDW->nfxd + 1 < m) {
                rtDW->vn1[rtDW->ii] = xnrm2(i - 1, A, rtDW->nmi + 1, rtDW);
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

        rtDW->nfxd++;
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void computeQ_(sQyCFUyu0YXOk1LARsZMzaD *obj, int32_T nrows, DW *rtDW)
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
    memset(&rtDW->work_k[0], 0, sizeof(real_T) << 3U);
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
static int32_T ComputeNumDependentEq_(sQyCFUyu0YXOk1LARsZMzaD *qrmanager, DW
  *rtDW)
{
  int32_T numDependent;
  boolean_T exitg1;
  numDependent = 0;
  for (rtDW->idxDiag = 0; rtDW->idxDiag < 7; rtDW->idxDiag++) {
    qrmanager->jpvt[rtDW->idxDiag] = 0;
  }

  qrmanager->usedPivoting = true;
  qrmanager->mrows = 1;
  qrmanager->ncols = 7;
  qrmanager->minRowCol = 1;
  xzgeqp3(qrmanager->QR, 1, 1, 7, qrmanager->jpvt, qrmanager->tau, rtDW);
  rtDW->idxDiag = 1;
  while ((rtDW->idxDiag > 0) && (fabs(qrmanager->QR[rtDW->idxDiag - 1]) <
          1.5543122344752192E-13)) {
    rtDW->idxDiag = (rtDW->idxDiag - qrmanager->ldq) - 1;
    numDependent++;
  }

  if (numDependent > 0) {
    computeQ_(qrmanager, qrmanager->mrows, rtDW);
    rtDW->idxDiag = 0;
    exitg1 = false;
    while ((!exitg1) && (rtDW->idxDiag <= numDependent - 1)) {
      if (fabs(qrmanager->Q[qrmanager->ldq * -rtDW->idxDiag]) >=
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
static void countsort(int32_T x[9], int32_T xLen, int32_T workspace[9], int32_T
                      xMin, int32_T xMax)
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
static void moveConstraint_(swcr9qLPQBiG4lNhaNdYq5G *obj, int32_T
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
static void removeEqConstr(swcr9qLPQBiG4lNhaNdYq5G *obj, int32_T idx_global)
{
  int32_T TYPE_tmp_tmp;
  int32_T totalEq;
  totalEq = obj->nWConstr[0] + obj->nWConstr[1];
  if ((totalEq != 0) && (idx_global <= totalEq)) {
    if ((obj->nActiveConstr == totalEq) || (idx_global == totalEq)) {
      obj->mEqRemoved++;
      obj->indexEqRemoved = obj->Wlocalidx[idx_global - 1];
      totalEq = obj->Wid[idx_global - 1] - 1;
      obj->isActiveConstr[(obj->isActiveIdx[totalEq] + obj->Wlocalidx[idx_global
                           - 1]) - 2] = false;
      moveConstraint_(obj, obj->nActiveConstr, idx_global);
      obj->nActiveConstr--;
      obj->nWConstr[totalEq]--;
    } else {
      obj->mEqRemoved++;
      TYPE_tmp_tmp = obj->Wid[idx_global - 1] - 1;
      obj->indexEqRemoved = obj->Wlocalidx[idx_global - 1];
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
static void RemoveDependentEq_(s9NoAX0P67ji2P1ZBafS3UG *memspace, int32_T
  *nDepInd, swcr9qLPQBiG4lNhaNdYq5G *workingset, sQyCFUyu0YXOk1LARsZMzaD
  *qrmanager, DW *rtDW)
{
  static const int8_T b_workingset_Aineq[56] = { -1, 0, 0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0 };

  static const int8_T b_workingset_Aeq[8] = { 1, 1, 1, 1, 1, 1, 1, 0 };

  static const int8_T b_workingset_ATwset[72] = { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  static const int8_T b_workingset_bwset[9] = { 1, 0, 0, 0, 0, 0, 0, 0, 0 };

  static const int8_T b_workingset_sizes[5] = { 0, 1, 7, 0, 0 };

  static const int8_T b_workingset_isActiveIdx[6] = { 1, 1, 2, 9, 9, 9 };

  static const int8_T b_workingset_sizesPhaseOne[5] = { 0, 1, 7, 1, 0 };

  static const int8_T b_workingset_sizesRegularized[5] = { 0, 1, 7, 9, 0 };

  static const boolean_T b_workingset_isActiveConstr[9] = { true, false, false,
    false, false, false, false, false, false };

  static const int8_T b_workingset_isActiveIdxPhaseOn[6] = { 1, 1, 2, 9, 10, 10
  };

  static const int8_T b_workingset_sizesRegPhaseOne[5] = { 0, 1, 7, 10, 0 };

  static const int8_T b_workingset_Wid[9] = { 2, 0, 0, 0, 0, 0, 0, 0, 0 };

  static const int8_T b_workingset_isActiveIdxRegular[6] = { 1, 1, 2, 9, 18, 18
  };

  static const int8_T b_workingset_nWConstr[5] = { 0, 1, 0, 0, 0 };

  static const int8_T b_workingset_isActiveIdxRegPhas[6] = { 1, 1, 2, 9, 19, 19
  };

  qrmanager->ldq = 8;
  memset(&qrmanager->QR[0], 0, 72U * sizeof(real_T));
  memset(&qrmanager->Q[0], 0, sizeof(real_T) << 6U);
  for (rtDW->i_c = 0; rtDW->i_c < 9; rtDW->i_c++) {
    qrmanager->jpvt[rtDW->i_c] = 0;
  }

  qrmanager->mrows = 0;
  qrmanager->ncols = 0;
  memset(&qrmanager->tau[0], 0, sizeof(real_T) << 3U);
  qrmanager->minRowCol = 0;
  qrmanager->usedPivoting = false;
  workingset->mConstr = 8;
  workingset->mConstrOrig = 8;
  workingset->mConstrMax = 9;
  workingset->nVar = 7;
  workingset->nVarOrig = 7;
  workingset->nVarMax = 8;
  workingset->ldA = 8;
  for (rtDW->i_c = 0; rtDW->i_c < 56; rtDW->i_c++) {
    workingset->Aineq[rtDW->i_c] = b_workingset_Aineq[rtDW->i_c];
  }

  for (rtDW->i_c = 0; rtDW->i_c < 7; rtDW->i_c++) {
    workingset->bineq[rtDW->i_c] = 0.0;
  }

  workingset->beq = 1.0;
  for (rtDW->i_c = 0; rtDW->i_c < 8; rtDW->i_c++) {
    workingset->Aeq[rtDW->i_c] = b_workingset_Aeq[rtDW->i_c];
    workingset->lb[rtDW->i_c] = 0.0;
    workingset->ub[rtDW->i_c] = 0.0;
    workingset->indexLB[rtDW->i_c] = 0;
    workingset->indexUB[rtDW->i_c] = 0;
    workingset->indexFixed[rtDW->i_c] = 0;
  }

  workingset->mEqRemoved = 0;
  workingset->indexEqRemoved = 0;
  for (rtDW->i_c = 0; rtDW->i_c < 72; rtDW->i_c++) {
    workingset->ATwset[rtDW->i_c] = b_workingset_ATwset[rtDW->i_c];
  }

  workingset->nActiveConstr = 1;
  for (rtDW->i_c = 0; rtDW->i_c < 9; rtDW->i_c++) {
    workingset->bwset[rtDW->i_c] = b_workingset_bwset[rtDW->i_c];
    workingset->maxConstrWorkspace[rtDW->i_c] = 0.0;
  }

  for (rtDW->i_c = 0; rtDW->i_c < 5; rtDW->i_c++) {
    workingset->sizes[rtDW->i_c] = b_workingset_sizes[rtDW->i_c];
    workingset->sizesNormal[rtDW->i_c] = b_workingset_sizes[rtDW->i_c];
    workingset->sizesPhaseOne[rtDW->i_c] = b_workingset_sizesPhaseOne[rtDW->i_c];
    workingset->sizesRegularized[rtDW->i_c] = b_workingset_sizesRegularized
      [rtDW->i_c];
    workingset->sizesRegPhaseOne[rtDW->i_c] = b_workingset_sizesRegPhaseOne
      [rtDW->i_c];
  }

  for (rtDW->i_c = 0; rtDW->i_c < 6; rtDW->i_c++) {
    workingset->isActiveIdx[rtDW->i_c] = b_workingset_isActiveIdx[rtDW->i_c];
    workingset->isActiveIdxNormal[rtDW->i_c] = b_workingset_isActiveIdx
      [rtDW->i_c];
    workingset->isActiveIdxPhaseOne[rtDW->i_c] =
      b_workingset_isActiveIdxPhaseOn[rtDW->i_c];
    workingset->isActiveIdxRegularized[rtDW->i_c] =
      b_workingset_isActiveIdxRegular[rtDW->i_c];
    workingset->isActiveIdxRegPhaseOne[rtDW->i_c] =
      b_workingset_isActiveIdxRegPhas[rtDW->i_c];
  }

  for (rtDW->i_c = 0; rtDW->i_c < 9; rtDW->i_c++) {
    workingset->isActiveConstr[rtDW->i_c] = b_workingset_isActiveConstr
      [rtDW->i_c];
    workingset->Wid[rtDW->i_c] = b_workingset_Wid[rtDW->i_c];
    workingset->Wlocalidx[rtDW->i_c] = b_workingset_bwset[rtDW->i_c];
  }

  for (rtDW->i_c = 0; rtDW->i_c < 5; rtDW->i_c++) {
    workingset->nWConstr[rtDW->i_c] = b_workingset_nWConstr[rtDW->i_c];
  }

  workingset->probType = 3;
  workingset->SLACK0 = 0.0;
  for (rtDW->i_c = 0; rtDW->i_c < 7; rtDW->i_c++) {
    qrmanager->QR[rtDW->i_c << 3] = b_workingset_ATwset[rtDW->i_c];
  }

  *nDepInd = ComputeNumDependentEq_(qrmanager, rtDW);
  if (*nDepInd > 0) {
    for (rtDW->i_c = 0; rtDW->i_c < 7; rtDW->i_c++) {
      qrmanager->QR[rtDW->i_c] = b_workingset_ATwset[rtDW->i_c];
    }

    qrmanager->jpvt[0] = 0;
    qrmanager->usedPivoting = true;
    qrmanager->mrows = 7;
    qrmanager->ncols = 1;
    qrmanager->minRowCol = 1;
    for (rtDW->i_c = 0; rtDW->i_c < 9; rtDW->i_c++) {
      rtDW->jpvt_j[rtDW->i_c] = qrmanager->jpvt[rtDW->i_c];
    }

    xzgeqp3(qrmanager->QR, 1, 7, 1, rtDW->jpvt_j, qrmanager->tau, rtDW);
    for (rtDW->i_c = 0; rtDW->i_c < 9; rtDW->i_c++) {
      qrmanager->jpvt[rtDW->i_c] = rtDW->jpvt_j[rtDW->i_c];
    }

    rtDW->i_c = 0;
    while (rtDW->i_c <= *nDepInd - 1) {
      memspace->workspace_int[rtDW->i_c] = rtDW->jpvt_j[(rtDW->i_c - *nDepInd) +
        1];
      rtDW->i_c++;
    }

    for (rtDW->i_c = 0; rtDW->i_c < 9; rtDW->i_c++) {
      rtDW->jpvt_j[rtDW->i_c] = memspace->workspace_sort[rtDW->i_c];
    }

    countsort(memspace->workspace_int, *nDepInd, rtDW->jpvt_j, 1, 1);
    for (rtDW->i_c = 0; rtDW->i_c < 9; rtDW->i_c++) {
      memspace->workspace_sort[rtDW->i_c] = rtDW->jpvt_j[rtDW->i_c];
    }

    rtDW->i_c = *nDepInd;
    while (rtDW->i_c > 0) {
      removeEqConstr(workingset, memspace->workspace_int[rtDW->i_c - 1]);
      rtDW->i_c--;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void removeAllIneqConstr(swcr9qLPQBiG4lNhaNdYq5G *obj)
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
static void RemoveDependentIneq_(swcr9qLPQBiG4lNhaNdYq5G *workingset,
  sQyCFUyu0YXOk1LARsZMzaD *qrmanager, s9NoAX0P67ji2P1ZBafS3UG *memspace, real_T
  tolfactor, DW *rtDW)
{
  rtDW->nFixedConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  rtDW->nVar_o = workingset->nVar;
  if ((workingset->nWConstr[2] + workingset->nWConstr[3]) + workingset->
      nWConstr[4] > 0) {
    rtDW->tol_g = tolfactor * (real_T)workingset->nVar * 2.2204460492503131E-16;
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
      rtDW->i_f = qrmanager->ldq * rtDW->nDepIneq;
      rtDW->idxPosATwset = workingset->ldA * rtDW->nDepIneq;
      rtDW->k_i = 1;
      while (rtDW->k_i - 1 <= rtDW->nVar_o - 1) {
        qrmanager->QR[(rtDW->i_f + rtDW->k_i) - 1] = workingset->ATwset
          [(rtDW->idxPosATwset + rtDW->k_i) - 1];
        rtDW->k_i++;
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

      for (rtDW->i_f = 0; rtDW->i_f < 9; rtDW->i_f++) {
        rtDW->jpvt_f[rtDW->i_f] = qrmanager->jpvt[rtDW->i_f];
      }

      xzgeqp3(qrmanager->QR, 1, workingset->nVar, workingset->nActiveConstr,
              rtDW->jpvt_f, qrmanager->tau, rtDW);
      for (rtDW->i_f = 0; rtDW->i_f < 9; rtDW->i_f++) {
        qrmanager->jpvt[rtDW->i_f] = rtDW->jpvt_f[rtDW->i_f];
      }
    }

    rtDW->nDepIneq = -1;
    rtDW->i_f = workingset->nActiveConstr - 1;
    while (rtDW->i_f + 1 > rtDW->nVar_o) {
      rtDW->nDepIneq++;
      memspace->workspace_int[rtDW->nDepIneq] = qrmanager->jpvt[rtDW->i_f];
      rtDW->i_f--;
    }

    if (rtDW->i_f + 1 <= workingset->nVar) {
      rtDW->nVar_o = qrmanager->ldq * rtDW->i_f + rtDW->i_f;
      while ((rtDW->i_f + 1 > rtDW->nFixedConstr) && (fabs(qrmanager->QR
               [rtDW->nVar_o]) < rtDW->tol_g)) {
        rtDW->nDepIneq++;
        memspace->workspace_int[rtDW->nDepIneq] = qrmanager->jpvt[rtDW->i_f];
        rtDW->i_f--;
        rtDW->nVar_o = (rtDW->nVar_o - qrmanager->ldq) - 1;
      }
    }

    for (rtDW->i_f = 0; rtDW->i_f < 9; rtDW->i_f++) {
      rtDW->jpvt_f[rtDW->i_f] = memspace->workspace_int[rtDW->i_f];
    }

    countsort(rtDW->jpvt_f, rtDW->nDepIneq + 1, memspace->workspace_sort,
              rtDW->nFixedConstr + 1, workingset->nActiveConstr);
    for (rtDW->i_f = 0; rtDW->i_f < 9; rtDW->i_f++) {
      memspace->workspace_int[rtDW->i_f] = rtDW->jpvt_f[rtDW->i_f];
    }

    while (rtDW->nDepIneq + 1 > 0) {
      rtDW->nFixedConstr = workingset->Wid[rtDW->jpvt_f[rtDW->nDepIneq] - 1] - 1;
      workingset->isActiveConstr[(workingset->isActiveIdx[rtDW->nFixedConstr] +
        workingset->Wlocalidx[rtDW->jpvt_f[rtDW->nDepIneq] - 1]) - 2] = false;
      moveConstraint_(workingset, workingset->nActiveConstr, rtDW->jpvt_f
                      [rtDW->nDepIneq]);
      workingset->nActiveConstr--;
      workingset->nWConstr[rtDW->nFixedConstr]--;
      rtDW->nDepIneq--;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void factorQR_f(sQyCFUyu0YXOk1LARsZMzaD *obj, const real_T A[72], int32_T
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
      rtDW->iQR0_i = obj->ldq * b_idx;
      for (k = 1; k - 1 < mrows; k++) {
        obj->QR[(rtDW->iQR0_i + k) - 1] = A[(i + k) - 1];
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
    memset(&obj->tau[0], 0, sizeof(real_T) << 3U);
    if (b_idx >= 1) {
      qrf(obj->QR, 1, mrows, ncols, b_idx, obj->tau, rtDW);
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void factorQR(sQyCFUyu0YXOk1LARsZMzaD *obj, int32_T mrows, int32_T ncols,
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
    memset(&obj->tau[0], 0, sizeof(real_T) << 3U);
    if (idx >= 1) {
      qrf(obj->QR, 1, mrows, ncols, idx, obj->tau, rtDW);
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv(int32_T m, int32_T n, const real_T A[56], int32_T lda, const
                  real_T x[72], real_T y[9], DW *rtDW)
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
static void xgemv_n(int32_T m, int32_T n, const real_T A[8], int32_T lda, const
                    real_T x[72], real_T y[9], DW *rtDW)
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
static real_T maxConstraintViolation(swcr9qLPQBiG4lNhaNdYq5G *obj, const real_T
  x[72], DW *rtDW)
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
      obj->maxConstrWorkspace[mIneq] = obj->beq;
    }

    xgemv_n(obj->nVarOrig, obj->sizes[1], obj->Aeq, obj->ldA, x,
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
      obj->maxConstrWorkspace[mIneq] = obj->beq;
    }

    xgemv_n(obj->nVar, obj->sizes[1], obj->Aeq, obj->ldA, x,
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
static void xgemv_nh(int32_T m, int32_T n, const real_T A[56], int32_T lda,
                     const real_T x[72], real_T y[9], DW *rtDW)
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
      ix = 9;
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
static void xgemv_nhu(int32_T m, int32_T n, const real_T A[8], int32_T lda,
                      const real_T x[72], real_T y[9], DW *rtDW)
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
      ix = 9;
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
static real_T maxConstraintViolation_e(swcr9qLPQBiG4lNhaNdYq5G *obj, const
  real_T x[72], DW *rtDW)
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

    xgemv_nh(obj->nVarOrig, obj->sizes[2], obj->Aineq, obj->ldA, x,
             obj->maxConstrWorkspace, rtDW);
    for (mIneq = 0; mIneq <= b_mIneq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] -= x[(obj->nVarOrig + mIneq) + 9];
      v = fmax(v, obj->maxConstrWorkspace[mIneq]);
    }

    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->beq;
    }

    xgemv_nhu(obj->nVarOrig, obj->sizes[1], obj->Aeq, obj->ldA, x,
              obj->maxConstrWorkspace, rtDW);
    b_mIneq = (obj->nVarOrig + obj->sizes[2]) + 8;
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

    xgemv_nh(obj->nVar, obj->sizes[2], obj->Aineq, obj->ldA, x,
             obj->maxConstrWorkspace, rtDW);
    for (b_mIneq = 0; b_mIneq <= mIneq; b_mIneq++) {
      v = fmax(v, obj->maxConstrWorkspace[b_mIneq]);
    }

    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->beq;
    }

    xgemv_nhu(obj->nVar, obj->sizes[1], obj->Aeq, obj->ldA, x,
              obj->maxConstrWorkspace, rtDW);
    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      v = fmax(v, fabs(obj->maxConstrWorkspace[mIneq]));
    }
  }

  if (mLB > 0) {
    for (mEq = 0; mEq < mLB; mEq++) {
      v = fmax(v, -x[obj->indexLB[mEq] + 8] - obj->lb[obj->indexLB[mEq] - 1]);
    }
  }

  if (mUB > 0) {
    for (mLB = 0; mLB < mUB; mLB++) {
      v = fmax(v, x[obj->indexUB[mLB] + 8] - obj->ub[obj->indexUB[mLB] - 1]);
    }
  }

  if (mFixed > 0) {
    for (mUB = 0; mUB < mFixed; mUB++) {
      v = fmax(v, fabs(x[obj->indexFixed[mUB] + 8] - obj->ub[obj->indexFixed[mUB]
                       - 1]));
    }
  }

  return v;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void feasibleX0ForWorkingSet(real_T workspace[72], real_T xCurrent[8],
  swcr9qLPQBiG4lNhaNdYq5G *workingset, sQyCFUyu0YXOk1LARsZMzaD *qrmanager, DW
  *rtDW)
{
  rtDW->mWConstr = workingset->nActiveConstr - 1;
  rtDW->nVar_j = workingset->nVar;
  if (workingset->nActiveConstr != 0) {
    rtDW->ldq = 0;
    while (rtDW->ldq <= rtDW->mWConstr) {
      workspace[rtDW->ldq] = workingset->bwset[rtDW->ldq];
      workspace[rtDW->ldq + 9] = workingset->bwset[rtDW->ldq];
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
      memcpy(&rtDW->B_m[0], &workspace[0], 72U * sizeof(real_T));
      if (workingset->nVar != 0) {
        rtDW->ar = 0;
        while (rtDW->ar + 1 <= rtDW->nVar_j) {
          workspace[rtDW->ar] = 0.0;
          rtDW->ar++;
        }

        rtDW->ar = 9;
        while (rtDW->ar + 1 <= rtDW->nVar_j + 9) {
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
        rtDW->b_i = 9;
        while (rtDW->b_i + 1 <= rtDW->nVar_j + 9) {
          rtDW->c = 0.0;
          rtDW->b_ia = 1;
          while (rtDW->b_ia - 1 <= rtDW->mWConstr) {
            rtDW->c += qrmanager->Q[rtDW->b_ia + rtDW->ar] * rtDW->B_m
              [rtDW->b_ia + 8];
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
        rtDW->c = workspace[rtDW->jBcol + 8];
        if (rtDW->c != 0.0) {
          workspace[rtDW->jBcol + 8] = rtDW->c / qrmanager->QR[rtDW->jBcol +
            rtDW->ar];
          rtDW->ix_o = 1;
          while (rtDW->ix_o - 1 <= rtDW->jBcol - 2) {
            workspace[rtDW->ix_o + 8] -= workspace[rtDW->jBcol + 8] *
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
        rtDW->c = workspace[rtDW->ar + 8];
        rtDW->b_i = 1;
        while (rtDW->b_i - 1 <= rtDW->ar - 2) {
          rtDW->c -= qrmanager->QR[rtDW->b_i + rtDW->ix_o] * workspace[rtDW->b_i
            + 8];
          rtDW->b_i++;
        }

        workspace[rtDW->ar + 8] = rtDW->c / qrmanager->QR[rtDW->ar + rtDW->ix_o];
        rtDW->ar++;
      }

      memcpy(&rtDW->B_m[0], &workspace[0], 72U * sizeof(real_T));
      if (workingset->nVar != 0) {
        rtDW->ar = 0;
        while (rtDW->ar + 1 <= rtDW->nVar_j) {
          workspace[rtDW->ar] = 0.0;
          rtDW->ar++;
        }

        rtDW->ar = 9;
        while (rtDW->ar + 1 <= rtDW->nVar_j + 9) {
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
        rtDW->b_i = 10;
        while (rtDW->b_i <= rtDW->mWConstr + 10) {
          rtDW->b_ia = rtDW->ar;
          rtDW->iy_n = 9;
          while (rtDW->iy_n + 1 <= rtDW->nVar_j + 9) {
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
    rtDW->constrViolation_basicX = maxConstraintViolation_e(workingset,
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
        xCurrent[rtDW->mWConstr] = workspace[rtDW->mWConstr + 9];
        rtDW->mWConstr++;
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv_nhum(int32_T m, int32_T n, const real_T A[56], int32_T lda,
  const real_T x[8], real_T y[9], DW *rtDW)
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
static void xgemv_nhumt(int32_T m, int32_T n, const real_T A[8], int32_T lda,
  const real_T x[8], real_T y[9], DW *rtDW)
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
static real_T maxConstraintViolation_eo(swcr9qLPQBiG4lNhaNdYq5G *obj, const
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

    xgemv_nhum(obj->nVarOrig, obj->sizes[2], obj->Aineq, obj->ldA, x,
               obj->maxConstrWorkspace, rtDW);
    for (mIneq = 0; mIneq <= b_mIneq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] -= x[obj->nVarOrig + mIneq];
      v = fmax(v, obj->maxConstrWorkspace[mIneq]);
    }

    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->beq;
    }

    xgemv_nhumt(obj->nVarOrig, obj->sizes[1], obj->Aeq, obj->ldA, x,
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

    xgemv_nhum(obj->nVar, obj->sizes[2], obj->Aineq, obj->ldA, x,
               obj->maxConstrWorkspace, rtDW);
    for (b_mIneq = 0; b_mIneq <= mIneq; b_mIneq++) {
      v = fmax(v, obj->maxConstrWorkspace[b_mIneq]);
    }

    for (mIneq = 0; mIneq <= mEq; mIneq++) {
      obj->maxConstrWorkspace[mIneq] = obj->beq;
    }

    xgemv_nhumt(obj->nVar, obj->sizes[1], obj->Aeq, obj->ldA, x,
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
static void PresolveWorkingSet(svV6yPD1e8CTJu8b18IprLB *solution,
  s9NoAX0P67ji2P1ZBafS3UG *memspace, swcr9qLPQBiG4lNhaNdYq5G *workingset,
  sQyCFUyu0YXOk1LARsZMzaD *qrmanager, DW *rtDW)
{
  solution->state = 82;
  RemoveDependentEq_(memspace, &rtDW->b_h, workingset, qrmanager, rtDW);
  if ((rtDW->b_h != -1) && (workingset->nActiveConstr <= qrmanager->ldq)) {
    RemoveDependentIneq_(workingset, qrmanager, memspace, 100.0, rtDW);
    feasibleX0ForWorkingSet(memspace->workspace_double, solution->xstar,
      workingset, qrmanager, rtDW);
    if (workingset->nWConstr[0] + workingset->nWConstr[1] == workingset->nVar) {
      rtDW->constrViolation_f = maxConstraintViolation_eo(workingset,
        solution->xstar, rtDW);
      if (rtDW->constrViolation_f > 1.0E-8) {
        solution->state = -2;
      }
    }
  } else {
    solution->state = -3;
    removeAllIneqConstr(workingset);
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void modifyOverheadPhaseOne_(swcr9qLPQBiG4lNhaNdYq5G *obj)
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
static void setProblemType(swcr9qLPQBiG4lNhaNdYq5G *obj, int32_T PROBLEM_TYPE)
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
  workspace[72], const real_T H[49], const real_T f[7], const real_T x[8])
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
  [72], const real_T H[49], const real_T f[7], const real_T x[8])
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
static void xgemv_nhumth(int32_T m, int32_T n, const real_T A[49], int32_T lda,
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
    xgemv_nhumth(obj->nvar, obj->nvar, H, obj->nvar, x, obj->Hx);
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
    xgemv_nhumth(obj->nvar, obj->nvar, H, obj->nvar, x, obj->Hx);
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
  workspace[72], const real_T f[7], const real_T x[8])
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
static void deleteColMoveEnd(sQyCFUyu0YXOk1LARsZMzaD *obj, int32_T idx, DW *rtDW)
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
        rtDW->b_temp_m = obj->QR[QRk0 - 1];
        rtDW->e = obj->QR[QRk0];
        xrotg(&rtDW->b_temp_m, &rtDW->e, &rtDW->c_c_g, &rtDW->b_s, rtDW);
        obj->QR[QRk0 - 1] = rtDW->b_temp_m;
        obj->QR[QRk0] = rtDW->e;
        obj->QR[k + obj->ldq * (k - 1)] = 0.0;
        QRk0 = obj->ldq * idx + k;
        b_ix = obj->ncols - idx;
        if (b_ix >= 1) {
          ix = QRk0 - 1;
          for (d_k = 0; d_k < b_ix; d_k++) {
            rtDW->b_temp_m = rtDW->c_c_g * obj->QR[ix] + rtDW->b_s * obj->
              QR[QRk0];
            obj->QR[QRk0] = rtDW->c_c_g * obj->QR[QRk0] - rtDW->b_s * obj->QR[ix];
            obj->QR[ix] = rtDW->b_temp_m;
            QRk0 += obj->ldq;
            ix += obj->ldq;
          }
        }

        b_ix = (k - 1) * obj->ldq;
        if (obj->mrows >= 1) {
          QRk0 = obj->ldq + b_ix;
          for (ix = 0; ix < obj->mrows; ix++) {
            rtDW->b_temp_m = rtDW->c_c_g * obj->Q[b_ix] + rtDW->b_s * obj->
              Q[QRk0];
            obj->Q[QRk0] = rtDW->c_c_g * obj->Q[QRk0] - rtDW->b_s * obj->Q[b_ix];
            obj->Q[b_ix] = rtDW->b_temp_m;
            QRk0++;
            b_ix++;
          }
        }

        k--;
      }

      for (k = idx + 1; k <= i; k++) {
        QRk0 = k + (k - 1) * obj->ldq;
        rtDW->b_temp_m = obj->QR[QRk0 - 1];
        rtDW->e = obj->QR[QRk0];
        xrotg(&rtDW->b_temp_m, &rtDW->e, &rtDW->c_c_g, &rtDW->b_s, rtDW);
        obj->QR[QRk0 - 1] = rtDW->b_temp_m;
        obj->QR[QRk0] = rtDW->e;
        QRk0 = (obj->ldq + 1) * k;
        idxRotGCol = obj->ncols - k;
        if (idxRotGCol >= 1) {
          b_ix = QRk0 - 1;
          for (ix = 0; ix < idxRotGCol; ix++) {
            rtDW->b_temp_m = rtDW->c_c_g * obj->QR[b_ix] + rtDW->b_s * obj->
              QR[QRk0];
            obj->QR[QRk0] = rtDW->c_c_g * obj->QR[QRk0] - rtDW->b_s * obj->
              QR[b_ix];
            obj->QR[b_ix] = rtDW->b_temp_m;
            QRk0 += obj->ldq;
            b_ix += obj->ldq;
          }
        }

        idxRotGCol = (k - 1) * obj->ldq;
        if (obj->mrows >= 1) {
          QRk0 = obj->ldq + idxRotGCol;
          for (b_ix = 0; b_ix < obj->mrows; b_ix++) {
            rtDW->b_temp_m = rtDW->c_c_g * obj->Q[idxRotGCol] + rtDW->b_s *
              obj->Q[QRk0];
            obj->Q[QRk0] = rtDW->c_c_g * obj->Q[QRk0] - rtDW->b_s * obj->
              Q[idxRotGCol];
            obj->Q[idxRotGCol] = rtDW->b_temp_m;
            QRk0++;
            idxRotGCol++;
          }
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void computeProjectedHessian(const real_T H[49], s1hK3o0EyOqKKjEgDlbhqfF *
  cholmanager, const sQyCFUyu0YXOk1LARsZMzaD *qrmanager, s9NoAX0P67ji2P1ZBafS3UG
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
    b_c = (mNull - 1) * 9;
    for (br = 0; br <= b_c; br += 9) {
      b_cr = br + nVars;
      for (ar = br; ar < b_cr; ar++) {
        memspace->workspace_double[ar] = 0.0;
      }
    }

    br = nullStart;
    for (b_cr = 0; b_cr <= b_c; b_cr += 9) {
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

      br += 9;
      b_cr += ldm;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static int32_T ixamax(int32_T n, const real_T x[64], int32_T incx)
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
static void fullColLDL2_(s1hK3o0EyOqKKjEgDlbhqfF *obj, int32_T LD_offset,
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
static void xgemv_nhumtht(int32_T m, int32_T n, const real_T A[64], int32_T ia0,
  int32_T lda, const real_T x[72], real_T y[8])
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
static void compute_deltax(const real_T H[49], svV6yPD1e8CTJu8b18IprLB *solution,
  s9NoAX0P67ji2P1ZBafS3UG *memspace, const sQyCFUyu0YXOk1LARsZMzaD *qrmanager,
  s1hK3o0EyOqKKjEgDlbhqfF *cholmanager, const shohwUBaOGHF036TMzc1KEH *objective,
  DW *rtDW)
{
  int32_T exitg1;
  rtDW->nVar_a = qrmanager->mrows - 1;
  rtDW->mNull = qrmanager->mrows - qrmanager->ncols;
  if (rtDW->mNull <= 0) {
    rtDW->mNull = 0;
    while (rtDW->mNull <= rtDW->nVar_a) {
      solution->searchDir[rtDW->mNull] = 0.0;
      rtDW->mNull++;
    }
  } else {
    rtDW->nullStartIdx = 0;
    while (rtDW->nullStartIdx <= rtDW->nVar_a) {
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
        while (rtDW->mNull <= rtDW->nVar_a) {
          rtDW->nullStartIdx = (rtDW->nVar_a + 1) * rtDW->mNull;
          rtDW->b_A_maxDiag_idx = cholmanager->ldm * rtDW->mNull;
          rtDW->b_jjA = 1;
          while (rtDW->b_jjA - 1 <= rtDW->nVar_a) {
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
            if (rtDW->mNull <= rtDW->nVar_a) {
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
              rtDW->nVar_a = rtDW->nullStartIdx * cholmanager->ldm +
                rtDW->nullStartIdx;
              rtDW->b_A_maxDiag_idx = rtDW->iac - rtDW->nullStartIdx;
              rtDW->b_jjA = 1;
              while (rtDW->b_jjA - 1 <= rtDW->b_A_maxDiag_idx - 1) {
                rtDW->b_ix_o = rtDW->nullStartIdx + rtDW->b_jjA;
                solution->searchDir[rtDW->b_ix_o] -= cholmanager->FMat
                  [rtDW->nVar_a + rtDW->b_jjA] * solution->searchDir
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
              rtDW->nVar_a = cholmanager->ndims;
              while (rtDW->nVar_a >= rtDW->mNull + 2) {
                rtDW->b_SCALED_REG_PRIMAL -= cholmanager->FMat
                  [(rtDW->nullStartIdx + rtDW->nVar_a) - 1] *
                  solution->searchDir[rtDW->nVar_a - 1];
                rtDW->nVar_a--;
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
            rtDW->nVar_a];
          rtDW->b_A_maxDiag_idx++;
        }

        xgemv_nhumtht(qrmanager->mrows, rtDW->mNull, qrmanager->Q,
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
            rtDW->b_ix_o = (rtDW->mNull - 1) * qrmanager->ldq +
              rtDW->nullStartIdx;
            rtDW->iac = rtDW->nullStartIdx;
            while (((rtDW->b_A_maxDiag_idx > 0) && (rtDW->iac <= rtDW->b_ix_o)) ||
                   ((rtDW->b_A_maxDiag_idx < 0) && (rtDW->iac >= rtDW->b_ix_o)))
            {
              rtDW->ix_a = 0;
              rtDW->b_SCALED_REG_PRIMAL = 0.0;
              rtDW->d_i = rtDW->iac + rtDW->nVar_a;
              rtDW->ia_l = rtDW->iac;
              while (rtDW->ia_l <= rtDW->d_i) {
                rtDW->b_SCALED_REG_PRIMAL += qrmanager->Q[rtDW->ia_l - 1] *
                  objective->grad[rtDW->ix_a];
                rtDW->ix_a++;
                rtDW->ia_l++;
              }

              memspace->workspace_double[rtDW->b_jjA] +=
                -rtDW->b_SCALED_REG_PRIMAL;
              rtDW->b_jjA++;
              rtDW->iac += rtDW->b_A_maxDiag_idx;
            }
          }

          rtDW->d_i = cholmanager->ndims - 1;
          if (cholmanager->ndims != 0) {
            rtDW->b_A_maxDiag_idx = 0;
            while (rtDW->b_A_maxDiag_idx <= rtDW->d_i) {
              rtDW->b_jjA = rtDW->b_A_maxDiag_idx * cholmanager->ldm +
                rtDW->b_A_maxDiag_idx;
              rtDW->b_ix_o = rtDW->d_i - rtDW->b_A_maxDiag_idx;
              rtDW->iac = 1;
              while (rtDW->iac - 1 <= rtDW->b_ix_o - 1) {
                rtDW->ix_a = rtDW->b_A_maxDiag_idx + rtDW->iac;
                memspace->workspace_double[rtDW->ix_a] -= cholmanager->FMat
                  [rtDW->b_jjA + rtDW->iac] * memspace->workspace_double
                  [rtDW->b_A_maxDiag_idx];
                rtDW->iac++;
              }

              rtDW->b_A_maxDiag_idx++;
            }
          }

          rtDW->nVar_a = 0;
          while (rtDW->nVar_a <= rtDW->d_i) {
            memspace->workspace_double[rtDW->nVar_a] /= cholmanager->
              FMat[cholmanager->ldm * rtDW->nVar_a + rtDW->nVar_a];
            rtDW->nVar_a++;
          }

          if (cholmanager->ndims != 0) {
            rtDW->nVar_a = cholmanager->ndims - 1;
            while (rtDW->nVar_a + 1 > 0) {
              rtDW->b_A_maxDiag_idx = rtDW->nVar_a * cholmanager->ldm;
              rtDW->b_SCALED_REG_PRIMAL = memspace->workspace_double
                [rtDW->nVar_a];
              rtDW->b_jjA = cholmanager->ndims;
              while (rtDW->b_jjA >= rtDW->nVar_a + 2) {
                rtDW->b_SCALED_REG_PRIMAL -= cholmanager->FMat
                  [(rtDW->b_A_maxDiag_idx + rtDW->b_jjA) - 1] *
                  memspace->workspace_double[rtDW->b_jjA - 1];
                rtDW->b_jjA--;
              }

              memspace->workspace_double[rtDW->nVar_a] =
                rtDW->b_SCALED_REG_PRIMAL;
              rtDW->nVar_a--;
            }
          }

          xgemv_nhumtht(qrmanager->mrows, rtDW->mNull, qrmanager->Q,
                        rtDW->nullStartIdx, qrmanager->ldq,
                        memspace->workspace_double, solution->searchDir);
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real_T xnrm2_l(int32_T n, const real_T x[8])
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
static void xgemv_nhumthtw(int32_T m, int32_T n, const real_T A[56], int32_T lda,
  const real_T x[8], real_T y[72])
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
static void xgemv_nhumthtwu(int32_T m, int32_T n, const real_T A[56], int32_T
  lda, const real_T x[8], real_T y[72])
{
  real_T c;
  int32_T b;
  int32_T b_c;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  int32_T iy;
  if ((m != 0) && (n != 0)) {
    for (iy = 10; iy <= n + 9; iy++) {
      y[iy - 1] = 0.0;
    }

    iy = 9;
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
                      solution_searchDir[8], real_T workspace[72], int32_T
                      workingset_nVar, int32_T workingset_ldA, const real_T
                      workingset_Aineq[56], const real_T workingset_bineq[7],
                      const real_T workingset_lb[8], const real_T workingset_ub
                      [8], const int32_T workingset_indexLB[8], const int32_T
                      workingset_indexUB[8], const int32_T workingset_sizes[5],
                      const int32_T workingset_isActiveIdx[6], const boolean_T
                      workingset_isActiveConstr[9], const int32_T
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
  rtDW->denomTol = 2.2204460492503131E-13 * xnrm2_l(workingset_nVar,
    solution_searchDir);
  if (workingset_nWConstr[2] < workingset_sizes[2]) {
    for (b_k = 0; b_k <= totalIneq; b_k++) {
      workspace[b_k] = workingset_bineq[b_k];
    }

    xgemv_nhumthtw(workingset_nVar, workingset_sizes[2], workingset_Aineq,
                   workingset_ldA, solution_xstar, workspace);
    xgemv_nhumthtwu(workingset_nVar, workingset_sizes[2], workingset_Aineq,
                    workingset_ldA, solution_searchDir, workspace);
    for (b_k = 0; b_k <= totalIneq; b_k++) {
      rtDW->phaseOneCorrectionX = workspace[b_k + 9];
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
          rtDW->p_max = fabs(workspace[b_k + 9]);
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
  solution_searchDir[8], real_T workspace[72], int32_T workingset_nVar, int32_T
  workingset_ldA, const real_T workingset_Aineq[56], const real_T
  workingset_bineq[7], const real_T workingset_lb[8], const real_T
  workingset_ub[8], const int32_T workingset_indexLB[8], const int32_T
  workingset_indexUB[8], const int32_T workingset_sizes[5], const int32_T
  workingset_isActiveIdx[6], const boolean_T workingset_isActiveConstr[9], const
  int32_T workingset_nWConstr[5], boolean_T isPhaseOne, real_T tolcon, real_T
  *alpha, boolean_T *newBlocking, int32_T *constrType, int32_T *constrIdx, DW
  *rtDW)
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
  rtDW->denomTol_n = 2.2204460492503131E-13 * xnrm2_l(workingset_nVar,
    solution_searchDir);
  if (workingset_nWConstr[2] < workingset_sizes[2]) {
    for (b_k = 0; b_k <= totalIneq; b_k++) {
      workspace[b_k] = workingset_bineq[b_k];
    }

    xgemv_nhumthtw(workingset_nVar, workingset_sizes[2], workingset_Aineq,
                   workingset_ldA, solution_xstar, workspace);
    xgemv_nhumthtwu(workingset_nVar, workingset_sizes[2], workingset_Aineq,
                    workingset_ldA, solution_searchDir, workspace);
    for (b_k = 0; b_k <= totalIneq; b_k++) {
      rtDW->phaseOneCorrectionX_p = workspace[b_k + 9];
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
static void checkUnboundedOrIllPosed(svV6yPD1e8CTJu8b18IprLB *solution, const
  shohwUBaOGHF036TMzc1KEH *objective)
{
  if (objective->objtype == 5) {
    if (xnrm2_l(objective->nvar, solution->searchDir) > 100.0 * (real_T)
        objective->nvar * 1.4901161193847656E-8) {
      solution->state = 3;
    } else {
      solution->state = 4;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void addBoundToActiveSetMatrix_(swcr9qLPQBiG4lNhaNdYq5G *obj, int32_T
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
static void compute_lambda(real_T workspace[72], svV6yPD1e8CTJu8b18IprLB
  *solution, const shohwUBaOGHF036TMzc1KEH *objective, const
  sQyCFUyu0YXOk1LARsZMzaD *qrmanager)
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
  f[7], svV6yPD1e8CTJu8b18IprLB *solution, s9NoAX0P67ji2P1ZBafS3UG *memspace,
  const shohwUBaOGHF036TMzc1KEH *objective, swcr9qLPQBiG4lNhaNdYq5G *workingset,
  sQyCFUyu0YXOk1LARsZMzaD *qrmanager, real_T options_ObjectiveLimit, real_T
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
    rtDW->b_p = maxConstraintViolation_eo(workingset, solution->xstar, rtDW);
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
      rtDW->tempMaxConstr = maxConstraintViolation_eo(workingset,
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
static void computeFirstOrderOpt(svV6yPD1e8CTJu8b18IprLB *solution, const
  shohwUBaOGHF036TMzc1KEH *objective, int32_T workingset_nVar, int32_T
  workingset_ldA, const real_T workingset_ATwset[72], int32_T
  workingset_nActiveConstr, real_T workspace[72])
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
                    svV6yPD1e8CTJu8b18IprLB *solution, s9NoAX0P67ji2P1ZBafS3UG
                    *memspace, swcr9qLPQBiG4lNhaNdYq5G *workingset,
                    sQyCFUyu0YXOk1LARsZMzaD *qrmanager, s1hK3o0EyOqKKjEgDlbhqfF *
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
          rtDW->normDelta = xnrm2_l(rtDW->nVar, solution->searchDir);
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
            solution->maxConstr = maxConstraintViolation_eo(workingset,
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
                     svV6yPD1e8CTJu8b18IprLB *solution, s9NoAX0P67ji2P1ZBafS3UG *
                     memspace, swcr9qLPQBiG4lNhaNdYq5G *workingset,
                     sQyCFUyu0YXOk1LARsZMzaD *qrmanager, s1hK3o0EyOqKKjEgDlbhqfF
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
  for (rtDW->i_p = 0; rtDW->i_p < 7; rtDW->i_p++) {
    options->FiniteDifferenceType[rtDW->i_p] = d_FiniteDifferenceType[rtDW->i_p];
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
  for (rtDW->i_p = 0; rtDW->i_p < 10; rtDW->i_p++) {
    options->Algorithm[rtDW->i_p] = d_Algorithm[rtDW->i_p];
  }

  options->ConstraintTolerance = 1.0E-8;
  options->OptimalityTolerance = 1.0E-6;
  options->MaxIterations = 20.0;
  options->FunctionTolerance = 1.7976931348623157E+308;
  for (rtDW->i_p = 0; rtDW->i_p < 8; rtDW->i_p++) {
    options->SolverName[rtDW->i_p] = d_SolverName[rtDW->i_p];
  }

  options->CheckGradients = false;
  options->Diagnostics[0] = 'o';
  options->Diagnostics[1] = 'f';
  options->Diagnostics[2] = 'f';
  options->DiffMaxChange = 1.7976931348623157E+308;
  options->DiffMinChange = 0.0;
  for (rtDW->i_p = 0; rtDW->i_p < 5; rtDW->i_p++) {
    options->Display[rtDW->i_p] = d_Display[rtDW->i_p];
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
  rtDW->PROBTYPE_ORIG_c = workingset->probType;
  rtDW->nVar_tmp_a = workingset->nVar;
  solution->xstar[workingset->nVar] = solution->maxConstr + 1.0;
  if (workingset->probType == 3) {
    rtDW->i_p = 1;
  } else {
    rtDW->i_p = 4;
  }

  setProblemType(workingset, rtDW->i_p);
  removeAllIneqConstr(workingset);
  memset(&objective->grad[0], 0, sizeof(real_T) << 3U);
  for (rtDW->i_p = 0; rtDW->i_p < 7; rtDW->i_p++) {
    objective->Hx[rtDW->i_p] = 0.0;
  }

  objective->maxVar = 8;
  objective->beta = 0.0;
  objective->rho = 0.0;
  objective->prev_objtype = 3;
  objective->prev_nvar = 7;
  objective->prev_hasLinear = true;
  objective->objtype = 5;
  objective->nvar = rtDW->nVar_tmp_a + 1;
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
    rtDW->i_p = workingset->sizes[0] + workingset->sizes[1];
    exitg1 = false;
    while ((!exitg1) && (rtDW->i_p + 1 <= workingset->nActiveConstr)) {
      if ((workingset->Wid[rtDW->i_p] == 4) && (workingset->Wlocalidx[rtDW->i_p]
           == workingset->sizes[3])) {
        rtDW->b_TYPE_p = workingset->Wid[rtDW->i_p] - 1;
        workingset->isActiveConstr[(workingset->isActiveIdx[workingset->Wid
          [rtDW->i_p] - 1] + workingset->Wlocalidx[rtDW->i_p]) - 2] = false;
        moveConstraint_(workingset, workingset->nActiveConstr, rtDW->i_p + 1);
        workingset->nActiveConstr--;
        workingset->nWConstr[rtDW->b_TYPE_p]--;
        exitg1 = true;
      } else {
        rtDW->i_p++;
      }
    }
  }

  rtDW->i_p = workingset->nActiveConstr;
  rtDW->b_TYPE_p = workingset->sizes[0] + workingset->sizes[1];
  while ((rtDW->i_p > rtDW->b_TYPE_p) && (rtDW->i_p > rtDW->nVar_tmp_a)) {
    rtDW->TYPE_tmp_e = workingset->Wid[rtDW->i_p - 1] - 1;
    workingset->isActiveConstr[(workingset->isActiveIdx[rtDW->TYPE_tmp_e] +
      workingset->Wlocalidx[rtDW->i_p - 1]) - 2] = false;
    moveConstraint_(workingset, workingset->nActiveConstr, rtDW->i_p);
    workingset->nActiveConstr--;
    workingset->nWConstr[rtDW->TYPE_tmp_e]--;
    rtDW->i_p--;
  }

  solution->maxConstr = solution->xstar[rtDW->nVar_tmp_a];
  setProblemType(workingset, rtDW->PROBTYPE_ORIG_c);
  objective->objtype = objective->prev_objtype;
  objective->nvar = objective->prev_nvar;
  objective->hasLinear = objective->prev_hasLinear;
  options->ObjectiveLimit = -1.0E+20;
  options->StepTolerance = 1.0E-8;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static int32_T ComputeNumDependentEq__j(sQyCFUyu0YXOk1LARsZMzaD *qrmanager,
  const real_T beqf[9], int32_T mConstr, int32_T nVar, real_T tolfactor, DW
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

  rtDW->tol = tolfactor * (real_T)nVar * 2.2204460492503131E-16;
  if (nVar < mConstr) {
    rtDW->totalRank = nVar;
  } else {
    rtDW->totalRank = mConstr;
  }

  rtDW->totalRank += (rtDW->totalRank - 1) * qrmanager->ldq;
  while ((rtDW->totalRank > 0) && (fabs(qrmanager->QR[rtDW->totalRank - 1]) <
          rtDW->tol)) {
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
        rtDW->ix_c = ((mConstr - rtDW->totalRank) - 1) * qrmanager->ldq;
        rtDW->iy_m = 0;
        rtDW->k_m = 0;
        while (rtDW->k_m <= mConstr - 1) {
          rtDW->qtb += qrmanager->Q[rtDW->ix_c] * beqf[rtDW->iy_m];
          rtDW->ix_c++;
          rtDW->iy_m++;
          rtDW->k_m++;
        }
      }

      if (fabs(rtDW->qtb) >= rtDW->tol) {
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
static int32_T RemoveDependentEq__a(s9NoAX0P67ji2P1ZBafS3UG *memspace,
  swcr9qLPQBiG4lNhaNdYq5G *workingset, sQyCFUyu0YXOk1LARsZMzaD *qrmanager,
  real_T tolfactor, DW *rtDW)
{
  int32_T nDepInd;
  rtDW->nVar_n = workingset->nVar - 1;
  rtDW->mTotalWorkingEq = workingset->nWConstr[0] + workingset->nWConstr[1];
  nDepInd = 0;
  if (rtDW->mTotalWorkingEq > 0) {
    rtDW->idx_row_m = 0;
    while (rtDW->idx_row_m <= rtDW->mTotalWorkingEq - 1) {
      rtDW->offsetQR = 0;
      while (rtDW->offsetQR <= rtDW->nVar_n) {
        qrmanager->QR[rtDW->idx_row_m + qrmanager->ldq * rtDW->offsetQR] =
          workingset->ATwset[workingset->ldA * rtDW->idx_row_m + rtDW->offsetQR];
        rtDW->offsetQR++;
      }

      rtDW->idx_row_m++;
    }

    nDepInd = ComputeNumDependentEq__j(qrmanager, workingset->bwset,
      rtDW->mTotalWorkingEq, workingset->nVar, tolfactor, rtDW);
    if (nDepInd > 0) {
      rtDW->idx_row_m = 0;
      while (rtDW->idx_row_m <= rtDW->mTotalWorkingEq - 1) {
        rtDW->offsetQR = qrmanager->ldq * rtDW->idx_row_m;
        rtDW->offsetATw = workingset->ldA * rtDW->idx_row_m;
        rtDW->k = 1;
        while (rtDW->k - 1 <= rtDW->nVar_n) {
          qrmanager->QR[(rtDW->offsetQR + rtDW->k) - 1] = workingset->ATwset
            [(rtDW->offsetATw + rtDW->k) - 1];
          rtDW->k++;
        }

        rtDW->idx_row_m++;
      }

      rtDW->nVar_n = 0;
      while (rtDW->nVar_n <= workingset->nWConstr[0] - 1) {
        qrmanager->jpvt[rtDW->nVar_n] = 1;
        rtDW->nVar_n++;
      }

      rtDW->nVar_n = workingset->nWConstr[0];
      while (rtDW->nVar_n + 1 <= rtDW->mTotalWorkingEq) {
        qrmanager->jpvt[rtDW->nVar_n] = 0;
        rtDW->nVar_n++;
      }

      if (workingset->nVar * rtDW->mTotalWorkingEq == 0) {
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = rtDW->mTotalWorkingEq;
        qrmanager->minRowCol = 0;
      } else {
        qrmanager->usedPivoting = true;
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = rtDW->mTotalWorkingEq;
        if (workingset->nVar < rtDW->mTotalWorkingEq) {
          qrmanager->minRowCol = workingset->nVar;
        } else {
          qrmanager->minRowCol = rtDW->mTotalWorkingEq;
        }

        for (rtDW->nVar_n = 0; rtDW->nVar_n < 9; rtDW->nVar_n++) {
          rtDW->jpvt[rtDW->nVar_n] = qrmanager->jpvt[rtDW->nVar_n];
        }

        xzgeqp3(qrmanager->QR, 1, workingset->nVar, rtDW->mTotalWorkingEq,
                rtDW->jpvt, qrmanager->tau, rtDW);
        for (rtDW->nVar_n = 0; rtDW->nVar_n < 9; rtDW->nVar_n++) {
          qrmanager->jpvt[rtDW->nVar_n] = rtDW->jpvt[rtDW->nVar_n];
        }
      }

      rtDW->nVar_n = 0;
      while (rtDW->nVar_n <= nDepInd - 1) {
        memspace->workspace_int[rtDW->nVar_n] = qrmanager->jpvt
          [(rtDW->mTotalWorkingEq - nDepInd) + rtDW->nVar_n];
        rtDW->nVar_n++;
      }

      for (rtDW->nVar_n = 0; rtDW->nVar_n < 9; rtDW->nVar_n++) {
        rtDW->jpvt[rtDW->nVar_n] = memspace->workspace_sort[rtDW->nVar_n];
      }

      countsort(memspace->workspace_int, nDepInd, rtDW->jpvt, 1,
                rtDW->mTotalWorkingEq);
      for (rtDW->nVar_n = 0; rtDW->nVar_n < 9; rtDW->nVar_n++) {
        memspace->workspace_sort[rtDW->nVar_n] = rtDW->jpvt[rtDW->nVar_n];
      }

      rtDW->mTotalWorkingEq = nDepInd;
      while (rtDW->mTotalWorkingEq > 0) {
        removeEqConstr(workingset, memspace->workspace_int[rtDW->mTotalWorkingEq
                       - 1]);
        rtDW->mTotalWorkingEq--;
      }
    }
  }

  return nDepInd;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void PresolveWorkingSet_m(svV6yPD1e8CTJu8b18IprLB *solution,
  s9NoAX0P67ji2P1ZBafS3UG *memspace, swcr9qLPQBiG4lNhaNdYq5G *workingset,
  sQyCFUyu0YXOk1LARsZMzaD *qrmanager, const s4lHOiXA0GHbse0IgoBY6ZF *options, DW
  *rtDW)
{
  solution->state = 82;
  rtDW->b_o = RemoveDependentEq__a(memspace, workingset, qrmanager, 100.0, rtDW);
  if ((rtDW->b_o != -1) && (workingset->nActiveConstr <= qrmanager->ldq)) {
    RemoveDependentIneq_(workingset, qrmanager, memspace, 100.0, rtDW);
    feasibleX0ForWorkingSet(memspace->workspace_double, solution->xstar,
      workingset, qrmanager, rtDW);
    if (workingset->nWConstr[0] + workingset->nWConstr[1] == workingset->nVar) {
      rtDW->constrViolation = maxConstraintViolation_eo(workingset,
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
static boolean_T strcmp_o(const char_T a[8])
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
static void phaseone_k(const real_T H[49], const real_T f[7],
  svV6yPD1e8CTJu8b18IprLB *solution, s9NoAX0P67ji2P1ZBafS3UG *memspace,
  swcr9qLPQBiG4lNhaNdYq5G *workingset, sQyCFUyu0YXOk1LARsZMzaD *qrmanager,
  s1hK3o0EyOqKKjEgDlbhqfF *cholmanager, shohwUBaOGHF036TMzc1KEH *objective,
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
                   svV6yPD1e8CTJu8b18IprLB *solution, s9NoAX0P67ji2P1ZBafS3UG
                   *memspace, s1hK3o0EyOqKKjEgDlbhqfF *cholmanager,
                   sL9bDKomAYkxZSVrG9w6En runTimeOptions,
                   swcr9qLPQBiG4lNhaNdYq5G *workingset, sQyCFUyu0YXOk1LARsZMzaD *
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
  rtDW->options.MaxIterations = 20.0;
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
    rtDW->b = maxConstraintViolation_eo(workingset, solution->xstar, rtDW);
    solution->maxConstr = rtDW->b;
    guard1 = false;
    if (rtDW->b > 1.0E-8 * runTimeOptions.ConstrRelTolFactor) {
      phaseone(H, f, solution, memspace, workingset, qrmanager, cholmanager,
               &runTimeOptions, objective, &rtDW->options, rtDW);
      if (solution->state == 0) {
      } else {
        rtDW->b = maxConstraintViolation_eo(workingset, solution->xstar, rtDW);
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

            PresolveWorkingSet_m(solution, memspace, workingset, qrmanager,
                                 &rtDW->options, rtDW);
            rtDW->b = maxConstraintViolation_eo(workingset, solution->xstar,
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
      if (strcmp_o(rtDW->options.SolverName) && (solution->state != -6)) {
        solution->maxConstr = maxConstraintViolation_eo(workingset,
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
          PresolveWorkingSet_m(solution, memspace, workingset, qrmanager,
                               &rtDW->options, rtDW);
          phaseone_k(H, f, solution, memspace, workingset, qrmanager,
                     cholmanager, objective, &rtDW->options, &runTimeOptions,
                     rtDW);
          iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
                  objective, rtDW->options.IterDisplayQP,
                  rtDW->options.PricingTolerance, rtDW->options.ObjectiveLimit,
                  rtDW->options.ConstraintTolerance, rtDW->options.StepTolerance,
                  runTimeOptions, rtDW);
          solution->maxConstr = maxConstraintViolation_eo(workingset,
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
static void linearForm__e(boolean_T obj_hasLinear, int32_T obj_nvar, real_T
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
  memset(&rtDW->solution.lambda[0], 0, 9U * sizeof(real_T));
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
  rtDW->expl_temp.MaxIterations = 20;
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
    rtDW->H_infnrm = maxConstraintViolation_eo(&rtDW->WorkingSet,
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
        linearForm__e(rtDW->QPObjective.hasLinear, rtDW->QPObjective.nvar,
                      rtDW->QPObjective.grad, H, f, rtDW->solution.xstar);
        break;

       case 4:
        linearForm__e(rtDW->QPObjective.hasLinear, rtDW->QPObjective.nvar,
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

  static const int8_T b[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

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
  /* '<S13>:1:5' v_opt = [v0, v1, v2, v3, v4, v5, v0]; */
  /* delay compensation */
  /* '<S13>:1:7' v_t0 = v_opt * x_opt; */
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
   *  Inport: '<Root>/theta_el_neg'
   *  MATLAB Function: '<S1>/state_space_mdl'
   */
  /* MATLAB Function 'uz_codegen/MATLAB Function': '<S2>:1' */
  /* '<S2>:1:4' R = single([kalman_R 0 0 0; 0 kalman_R 0 0; 0 0 kalman_R 0; 0 0 0 kalman_R]); */
  /* '<S2>:1:5' Q = single([kalman_Q1 0 0 0 0 0 0 0; 0 kalman_Q1 0 0 0 0 0 0; 0 0 kalman_Q1 0 0 0 0 0; 0 0 0 kalman_Q1 0 0 0 0; 0 0 0 0 kalman_Q2 0 0 0; 0 0 0 0 0 kalman_Q2 0 0; 0 0 0 0 0 0 kalman_Q2 0; 0 0 0 0 0 0 0 kalman_Q2]); */
  /* MATLAB Function 'uz_codegen/Observer': '<S3>:1' */
  /* '<S3>:1:3' i_dq_obs = single([0;0]); */
  /* '<S3>:1:4' i_xy_obs = single([0;0]); */
  /* '<S3>:1:5' e_dq_obs = single([0;0]); */
  /* '<S3>:1:6' e_xy_obs = single([0;0]); */
  /*  system model */
  /* '<S3>:1:9' A = [ 1-Ts_times_ZB_over_Ld*Rs_over_ZB            Ts_times_ZB_over_Ld*Lq_over_LB*w_e_pu   0                                      0                                1 0 0 0; */
  /* '<S3>:1:10'       -Ts_times_ZB_over_Lq*Ld_over_LB*w_e_pu     1-Ts_times_ZB_over_Lq*Rs_over_ZB          0                                      0                               0 1 0 0; */
  /* '<S3>:1:11'       0                                          0                                        1-Ts_times_ZB_over_Lx*Rs_over_ZB        -Ly_over_LB*w_e_pu              0 0 1 0; */
  /* '<S3>:1:12'       0                                          0                                        Lx_over_LB*w_e_pu                      1-Ts_times_ZB_over_Ly*Rs_over_ZB 0 0 0 1; */
  /* '<S3>:1:13'       0 0 0 0 1 0 0 0; */
  /* '<S3>:1:14'       0 0 0 0 0 1 0 0; */
  /* '<S3>:1:15'       0 0 0 0 0 0 1 0; */
  /* '<S3>:1:16'       0 0 0 0 0 0 0 1]; */
  rtDW->A[0] = 1.0F - rtU->Ts_times_ZB_over_Ld * rtU->Rs_over_ZB;
  rtDW->x0_idx_1 = rtU->Ts_times_ZB_over_Ld * rtU->Lq_over_LB * rtU->omega_el_pu;
  rtDW->A[8] = rtDW->x0_idx_1;
  rtDW->A[16] = 0.0F;
  rtDW->A[24] = 0.0F;
  rtDW->A[32] = 1.0F;
  rtDW->A[40] = 0.0F;
  rtDW->A[48] = 0.0F;
  rtDW->A[56] = 0.0F;
  rtDW->x0_idx_2 = -rtU->Ts_times_ZB_over_Lq * rtU->Ld_over_LB *
    rtU->omega_el_pu;
  rtDW->A[1] = rtDW->x0_idx_2;
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
  rtDW->x0_idx_3 = -rtU->Ly_over_LB * rtU->omega_el_pu;
  rtDW->A[26] = rtDW->x0_idx_3;
  rtDW->A[34] = 0.0F;
  rtDW->A[42] = 0.0F;
  rtDW->A[50] = 1.0F;
  rtDW->A[58] = 0.0F;
  rtDW->A[3] = 0.0F;
  rtDW->A[11] = 0.0F;
  rtDW->A_tmp = rtU->Lx_over_LB * rtU->omega_el_pu;
  rtDW->A[19] = rtDW->A_tmp;
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
  rtDW->x0_idx_0 = 6.0F * rtU->theta_el_neg;

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
  /*  D = [0; -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB; 0; 0; 0; 0; 0; 0]; */
  /* '<S3>:1:45' E = [     0; */
  /* '<S3>:1:46'          -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB; */
  /* '<S3>:1:47'          -w_e_pu*(psiPM5*sin(w6theta_el+phi5) - psiPM7*sin(w6theta_el+phi7)-psiPM5*6*sin(w6theta_el+phi5) - psiPM7*6*sin(w6theta_el+phi7)); */
  /* '<S3>:1:48'          -w_e_pu*(psiPM5*cos(w6theta_el+phi5) + psiPM7*cos(w6theta_el+phi7) + psiPM5*6*cos(w6theta_el+phi5) - psiPM7*6*cos(w6theta_el+phi7)); */
  /* '<S3>:1:49'           0; */
  /* '<S3>:1:50'           0; */
  /* '<S3>:1:51'           0; */
  /* '<S3>:1:52'           0]; */
  /*  parameters for kalman */
  /* '<S3>:1:56' u = [v_d; v_q; v_x; v_y]; */
  /* '<S3>:1:60' if isempty(x_e) */
  /* '<S3>:1:65' x = x_e; */
  /*  x_p = A * x + B * u + D; */
  /* '<S3>:1:68' x_p = A * x + B * u + E; */
  rtDW->rtb_SinCos2_o2_tmp = rtDW->x0_idx_0 + rtU->phiPM_h[0];
  rtDW->SinCos1_o2 = sinf(rtDW->rtb_SinCos2_o2_tmp);
  rtDW->x0_idx_0 += rtU->phiPM_h[1];
  rtDW->SinCos2_o1 = sinf(rtDW->x0_idx_0);
  rtDW->SinCos2_o2 = cosf(rtDW->rtb_SinCos2_o2_tmp);
  rtDW->w6theta_el = cosf(rtDW->x0_idx_0);
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
  rtDW->rtb_i_dq_obs_idx_0 = rtDW->v_t0[0];
  rtDW->rtb_v_1_idx_pu_idx_1 = rtDW->v_t0[1];
  rtDW->q = rtDW->v_t0[2];
  rtDW->rtb_v_1_idx_pu_idx_3 = rtDW->v_t0[3];
  rtDW->fv1[0] = 0.0F;
  rtDW->rtb_SinCos2_o1_tmp = -rtU->omega_el_pu * rtU->Ts_times_ZB_over_Lq *
    rtU->psi_pm_over_psiB;
  rtDW->fv1[1] = rtDW->rtb_SinCos2_o1_tmp;
  rtDW->fv1[2] = (((rtU->psiPM_h_pu[0] * rtDW->SinCos1_o2 - rtU->psiPM_h_pu[1] *
                    rtDW->SinCos2_o1) - rtU->psiPM_h_pu[0] * 6.0F *
                   rtDW->SinCos1_o2) - rtU->psiPM_h_pu[1] * 6.0F *
                  rtDW->SinCos2_o1) * -rtU->omega_el_pu;
  rtDW->fv1[3] = (((rtU->psiPM_h_pu[0] * rtDW->SinCos2_o2 + rtU->psiPM_h_pu[1] *
                    rtDW->w6theta_el) + rtU->psiPM_h_pu[0] * 6.0F *
                   rtDW->SinCos2_o2) - rtU->psiPM_h_pu[1] * 6.0F *
                  rtDW->w6theta_el) * -rtU->omega_el_pu;
  rtDW->fv1[4] = 0.0F;
  rtDW->fv1[5] = 0.0F;
  rtDW->fv1[6] = 0.0F;
  rtDW->fv1[7] = 0.0F;

  /* '<S3>:1:70' P_p = A*P_e*A'+Q; */
  for (rtDW->d_j = 0; rtDW->d_j < 8; rtDW->d_j++) {
    rtDW->A_ln[rtDW->d_j] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->ix = rtDW->iy << 3;
      rtDW->sector_ref = rtDW->ix + rtDW->d_j;
      rtDW->A_l[rtDW->sector_ref] = 0.0F;
      for (rtDW->i = 0; rtDW->i < 8; rtDW->i++) {
        rtDW->A_l[rtDW->sector_ref] += rtDW->A[(rtDW->i << 3) + rtDW->d_j] *
          rtDW->P_e[rtDW->ix + rtDW->i];
      }

      rtDW->A_o[rtDW->sector_ref] = 0.0F;
      rtDW->A_ln[rtDW->d_j] += rtDW->A[rtDW->sector_ref] * rtDW->x_e[rtDW->iy];
    }

    rtDW->x_p[rtDW->d_j] = (rtDW->A_ln[rtDW->d_j] + (rtDW->b_A_tmp[rtDW->d_j +
      24] * rtDW->rtb_v_1_idx_pu_idx_3 + (rtDW->b_A_tmp[rtDW->d_j + 16] *
      rtDW->q + (rtDW->b_A_tmp[rtDW->d_j + 8] * rtDW->rtb_v_1_idx_pu_idx_1 +
                 rtDW->b_A_tmp[rtDW->d_j] * rtDW->rtb_i_dq_obs_idx_0)))) +
      rtDW->fv1[rtDW->d_j];
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

  /* '<S3>:1:72' K = P_p*C'/(C*P_p*C'+R); */
  for (rtDW->d_j = 0; rtDW->d_j < 32; rtDW->d_j++) {
    rtDW->b_A_tmp_g[rtDW->d_j] = l[rtDW->d_j];
    rtDW->b_A_tmp_c[rtDW->d_j] = m[rtDW->d_j];
  }

  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->sector_ref = rtDW->d_j + (rtDW->iy << 2);
      rtDW->b_A_tmp[rtDW->sector_ref] = 0.0F;
      for (rtDW->i = 0; rtDW->i < 8; rtDW->i++) {
        rtDW->b_A_tmp[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_c[(rtDW->i <<
          2) + rtDW->d_j] * rtDW->A[(rtDW->iy << 3) + rtDW->i];
      }
    }

    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->sector_ref = rtDW->d_j + (rtDW->iy << 2);
      rtDW->B_b[rtDW->sector_ref] = 0.0F;
      for (rtDW->i = 0; rtDW->i < 8; rtDW->i++) {
        rtDW->B_b[rtDW->sector_ref] += rtDW->b_A_tmp[(rtDW->i << 2) + rtDW->d_j]
          * (real32_T)rtDW->b_A_tmp_g[(rtDW->iy << 3) + rtDW->i];
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
    rtDW->A_n[rtDW->d_j] = rtDW->B_b[rtDW->d_j] + rtDW->fv[rtDW->d_j];
  }

  rtDW->ipiv[0] = 1;
  rtDW->ipiv[1] = 2;
  rtDW->ipiv[2] = 3;
  rtDW->ipiv[3] = 4;
  for (rtDW->d_j = 0; rtDW->d_j < 3; rtDW->d_j++) {
    rtDW->i = rtDW->d_j * 5;
    rtDW->iy = 0;
    rtDW->ix = rtDW->i;
    rtDW->w6theta_el = fabsf(rtDW->A_n[rtDW->i]);
    rtDW->kBcol = 2;
    while (rtDW->kBcol <= 4 - rtDW->d_j) {
      rtDW->ix++;
      rtDW->SinCos1_o2 = fabsf(rtDW->A_n[rtDW->ix]);
      if (rtDW->SinCos1_o2 > rtDW->w6theta_el) {
        rtDW->iy = rtDW->kBcol - 1;
        rtDW->w6theta_el = rtDW->SinCos1_o2;
      }

      rtDW->kBcol++;
    }

    if (rtDW->A_n[rtDW->i + rtDW->iy] != 0.0F) {
      if (rtDW->iy != 0) {
        rtDW->iy += rtDW->d_j;
        rtDW->ipiv[rtDW->d_j] = (int8_T)(rtDW->iy + 1);
        rtDW->w6theta_el = rtDW->A_n[rtDW->d_j];
        rtDW->A_n[rtDW->d_j] = rtDW->A_n[rtDW->iy];
        rtDW->A_n[rtDW->iy] = rtDW->w6theta_el;
        rtDW->w6theta_el = rtDW->A_n[rtDW->d_j + 4];
        rtDW->A_n[rtDW->d_j + 4] = rtDW->A_n[rtDW->iy + 4];
        rtDW->A_n[rtDW->iy + 4] = rtDW->w6theta_el;
        rtDW->w6theta_el = rtDW->A_n[rtDW->d_j + 8];
        rtDW->A_n[rtDW->d_j + 8] = rtDW->A_n[rtDW->iy + 8];
        rtDW->A_n[rtDW->iy + 8] = rtDW->w6theta_el;
        rtDW->w6theta_el = rtDW->A_n[rtDW->d_j + 12];
        rtDW->A_n[rtDW->d_j + 12] = rtDW->A_n[rtDW->iy + 12];
        rtDW->A_n[rtDW->iy + 12] = rtDW->w6theta_el;
      }

      rtDW->iy = (rtDW->i - rtDW->d_j) + 4;
      rtDW->ix = rtDW->i + 1;
      while (rtDW->ix + 1 <= rtDW->iy) {
        rtDW->A_n[rtDW->ix] /= rtDW->A_n[rtDW->i];
        rtDW->ix++;
      }
    }

    rtDW->iy = rtDW->i;
    rtDW->ix = rtDW->i + 4;
    rtDW->kBcol = 0;
    while (rtDW->kBcol <= 2 - rtDW->d_j) {
      if (rtDW->A_n[rtDW->ix] != 0.0F) {
        rtDW->w6theta_el = -rtDW->A_n[rtDW->ix];
        rtDW->c_ix = rtDW->i + 1;
        rtDW->sector_ref = (rtDW->iy - rtDW->d_j) + 8;
        rtDW->ijA = rtDW->iy + 5;
        while (rtDW->ijA + 1 <= rtDW->sector_ref) {
          rtDW->A_n[rtDW->ijA] += rtDW->A_n[rtDW->c_ix] * rtDW->w6theta_el;
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
          (real32_T)rtDW->b_A_tmp_g[rtDW->sector_ref + rtDW->i];
      }
    }
  }

  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    rtDW->i = rtDW->d_j << 3;
    rtDW->iy = rtDW->d_j << 2;
    rtDW->ix = 0;
    while (rtDW->ix <= rtDW->d_j - 1) {
      rtDW->kBcol = rtDW->ix << 3;
      rtDW->rtb_i_dq_obs_idx_0 = rtDW->A_n[rtDW->ix + rtDW->iy];
      if (rtDW->rtb_i_dq_obs_idx_0 != 0.0F) {
        for (rtDW->c_ix = 0; rtDW->c_ix < 8; rtDW->c_ix++) {
          rtDW->sector_ref = rtDW->c_ix + rtDW->i;
          rtDW->b_A_tmp[rtDW->sector_ref] -= rtDW->rtb_i_dq_obs_idx_0 *
            rtDW->b_A_tmp[rtDW->c_ix + rtDW->kBcol];
        }
      }

      rtDW->ix++;
    }

    rtDW->w6theta_el = 1.0F / rtDW->A_n[rtDW->d_j + rtDW->iy];
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
      rtDW->rtb_i_dq_obs_idx_0 = rtDW->A_n[rtDW->ix + rtDW->iy];
      if (rtDW->rtb_i_dq_obs_idx_0 != 0.0F) {
        for (rtDW->c_ix = 0; rtDW->c_ix < 8; rtDW->c_ix++) {
          rtDW->sector_ref = rtDW->c_ix + rtDW->i;
          rtDW->b_A_tmp[rtDW->sector_ref] -= rtDW->rtb_i_dq_obs_idx_0 *
            rtDW->b_A_tmp[rtDW->c_ix + rtDW->kBcol];
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

  /* '<S3>:1:74' y=[i_d; i_q; i_x; i_y]; */
  /* '<S3>:1:76' x_e = x_p+K*(y-C*x_p); */
  rtDW->m6[0] = rtU->i_dq_pu[0];
  rtDW->m6[1] = rtU->i_dq_pu[1];
  rtDW->m6[2] = rtU->i_xy_pu[0];
  rtDW->m6[3] = rtU->i_xy_pu[1];
  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    rtDW->v_t0[rtDW->d_j] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->v_t0[rtDW->d_j] += (real32_T)rtDW->b_A_tmp_c[(rtDW->iy << 2) +
        rtDW->d_j] * rtDW->x_p[rtDW->iy];
    }

    rtDW->m2[rtDW->d_j] = rtDW->m6[rtDW->d_j] - rtDW->v_t0[rtDW->d_j];
  }

  /* '<S3>:1:78' P_e = P_p-K*C*P_p; */
  for (rtDW->d_j = 0; rtDW->d_j < 8; rtDW->d_j++) {
    rtDW->rtb_i_dq_obs_idx_0 = rtDW->b_A_tmp[rtDW->d_j + 8];
    rtDW->SinCos2_o1 = rtDW->b_A_tmp[rtDW->d_j + 16];
    rtDW->rtb_v_1_idx_pu_idx_1 = rtDW->b_A_tmp[rtDW->d_j + 24];
    rtDW->x_e[rtDW->d_j] = (((rtDW->rtb_i_dq_obs_idx_0 * rtDW->m2[1] +
      rtDW->b_A_tmp[rtDW->d_j] * rtDW->m2[0]) + rtDW->SinCos2_o1 * rtDW->m2[2])
      + rtDW->rtb_v_1_idx_pu_idx_1 * rtDW->m2[3]) + rtDW->x_p[rtDW->d_j];
    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->sector_ref = rtDW->d_j + (rtDW->iy << 3);
      rtDW->A_o[rtDW->sector_ref] = 0.0F;
      rtDW->ix = rtDW->iy << 2;
      rtDW->A_o[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_c[rtDW->ix] *
        rtDW->b_A_tmp[rtDW->d_j];
      rtDW->A_o[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_c[rtDW->ix + 1] *
        rtDW->rtb_i_dq_obs_idx_0;
      rtDW->A_o[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_c[rtDW->ix + 2] *
        rtDW->SinCos2_o1;
      rtDW->A_o[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_c[rtDW->ix + 3] *
        rtDW->rtb_v_1_idx_pu_idx_1;
    }

    for (rtDW->iy = 0; rtDW->iy < 8; rtDW->iy++) {
      rtDW->rtb_i_dq_obs_idx_0 = 0.0F;
      for (rtDW->i = 0; rtDW->i < 8; rtDW->i++) {
        rtDW->rtb_i_dq_obs_idx_0 += rtDW->A_o[(rtDW->i << 3) + rtDW->d_j] *
          rtDW->A[(rtDW->iy << 3) + rtDW->i];
      }

      rtDW->sector_ref = (rtDW->iy << 3) + rtDW->d_j;
      rtDW->P_e[rtDW->sector_ref] = rtDW->A[rtDW->sector_ref] -
        rtDW->rtb_i_dq_obs_idx_0;
    }
  }

  /* MATLAB Function: '<S1>/delay_compensation_currents' incorporates:
   *  MATLAB Function: '<S1>/Observer'
   *  Switch: '<S1>/Switch1'
   */
  /* '<S3>:1:80' i_dq_obs(1) = x_e(1); */
  /* '<S3>:1:81' i_dq_obs(2) = x_e(2); */
  /* '<S3>:1:82' i_xy_obs(1) = x_e(3); */
  /* '<S3>:1:83' i_xy_obs(2) = x_e(4); */
  /* '<S3>:1:84' e_dq_obs(1) = x_e(5); */
  /* '<S3>:1:85' e_dq_obs(2) = x_e(6); */
  /* '<S3>:1:86' e_xy_obs(1) = x_e(7); */
  /* '<S3>:1:87' e_xy_obs(2) = x_e(8); */
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
  if (rtDW->icLoad_e) {
    for (rtDW->i = 0; rtDW->i < 7; rtDW->i++) {
      rtDW->Delay1_DSTATE[rtDW->i] = 0.14F;
    }
  }

  /* Delay: '<S1>/Delay3' */
  if (rtDW->icLoad_b) {
    rtDW->Delay3_DSTATE[0] = 0.0F;
    rtDW->Delay3_DSTATE[1] = 0.0F;
    rtDW->Delay3_DSTATE[2] = 0.0F;
    rtDW->Delay3_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay4' */
  if (rtDW->icLoad_h) {
    rtDW->Delay4_DSTATE[0] = 0.0F;
    rtDW->Delay4_DSTATE[1] = 0.0F;
    rtDW->Delay4_DSTATE[2] = 0.0F;
    rtDW->Delay4_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay5' */
  if (rtDW->icLoad_c) {
    rtDW->Delay5_DSTATE[0] = 0.0F;
    rtDW->Delay5_DSTATE[1] = 0.0F;
    rtDW->Delay5_DSTATE[2] = 0.0F;
    rtDW->Delay5_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay6' */
  if (rtDW->icLoad_bb) {
    rtDW->Delay6_DSTATE[0] = 0.0F;
    rtDW->Delay6_DSTATE[1] = 0.0F;
    rtDW->Delay6_DSTATE[2] = 0.0F;
    rtDW->Delay6_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay7' */
  if (rtDW->icLoad_o) {
    rtDW->Delay7_DSTATE[0] = 0.0F;
    rtDW->Delay7_DSTATE[1] = 0.0F;
    rtDW->Delay7_DSTATE[2] = 0.0F;
    rtDW->Delay7_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay8' */
  if (rtDW->icLoad_d) {
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
   */
  /* MATLAB Function 'uz_codegen/delay_compensation_currents': '<S6>:1' */
  /* '<S6>:1:3' i_t0 = single([id0 iq0 ix0 iy0])'; */
  /* '<S6>:1:5' m_opt = single([m0, m1, m2, m3, m4, m5, m0]); */
  /* delay compensation */
  /*  i_t0_delay_comp = single(i_t0 + 1.0 * m_opt * x_opt); */
  /* '<S6>:1:8' i_t0_delay_comp = single(i_t0 + 0.5 * m_opt * x_opt); */
  rtDW->r[0] = 0.5F * rtDW->Delay3_DSTATE[0];
  rtDW->r[4] = 0.5F * rtDW->Delay4_DSTATE[0];
  rtDW->r[8] = 0.5F * rtDW->Delay5_DSTATE[0];
  rtDW->r[12] = 0.5F * rtDW->Delay6_DSTATE[0];
  rtDW->r[16] = 0.5F * rtDW->Delay7_DSTATE[0];
  rtDW->r[20] = 0.5F * rtDW->Delay8_DSTATE[0];
  rtDW->r[24] = 0.5F * rtDW->Delay3_DSTATE[0];
  rtDW->r[1] = 0.5F * rtDW->Delay3_DSTATE[1];
  rtDW->r[5] = 0.5F * rtDW->Delay4_DSTATE[1];
  rtDW->r[9] = 0.5F * rtDW->Delay5_DSTATE[1];
  rtDW->r[13] = 0.5F * rtDW->Delay6_DSTATE[1];
  rtDW->r[17] = 0.5F * rtDW->Delay7_DSTATE[1];
  rtDW->r[21] = 0.5F * rtDW->Delay8_DSTATE[1];
  rtDW->r[25] = 0.5F * rtDW->Delay3_DSTATE[1];
  rtDW->r[2] = 0.5F * rtDW->Delay3_DSTATE[2];
  rtDW->r[6] = 0.5F * rtDW->Delay4_DSTATE[2];
  rtDW->r[10] = 0.5F * rtDW->Delay5_DSTATE[2];
  rtDW->r[14] = 0.5F * rtDW->Delay6_DSTATE[2];
  rtDW->r[18] = 0.5F * rtDW->Delay7_DSTATE[2];
  rtDW->r[22] = 0.5F * rtDW->Delay8_DSTATE[2];
  rtDW->r[26] = 0.5F * rtDW->Delay3_DSTATE[2];
  rtDW->r[3] = 0.5F * rtDW->Delay3_DSTATE[3];
  rtDW->r[7] = 0.5F * rtDW->Delay4_DSTATE[3];
  rtDW->r[11] = 0.5F * rtDW->Delay5_DSTATE[3];
  rtDW->r[15] = 0.5F * rtDW->Delay6_DSTATE[3];
  rtDW->r[19] = 0.5F * rtDW->Delay7_DSTATE[3];
  rtDW->r[23] = 0.5F * rtDW->Delay8_DSTATE[3];
  rtDW->r[27] = 0.5F * rtDW->Delay3_DSTATE[3];
  rtDW->m1[0] = rtDW->rtb_i_dq_obs_idx_0;
  rtDW->m1[1] = rtDW->rtb_v_1_idx_pu_idx_1;
  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    rtDW->m6[rtDW->d_j] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 7; rtDW->iy++) {
      rtDW->m6[rtDW->d_j] += rtDW->r[(rtDW->iy << 2) + rtDW->d_j] *
        rtDW->Delay1_DSTATE[rtDW->iy];
    }

    rtDW->v_t0[rtDW->d_j] = rtDW->m1[rtDW->d_j] + rtDW->m6[rtDW->d_j];
  }

  /* Switch: '<S1>/Switch3' incorporates:
   *  MATLAB Function: '<S1>/Observer'
   */
  rtDW->rtb_e_xy_obs_idx_0 = rtDW->x_e[6];

  /* Switch: '<S1>/Switch2' incorporates:
   *  MATLAB Function: '<S1>/Observer'
   */
  rtDW->rtb_e_dq_obs_idx_0 = rtDW->x_e[4];

  /* MATLAB Function: '<S1>/Observer' */
  rtDW->rtb_e_xy_obs_b = rtDW->x_e[7];
  rtDW->rtb_e_dq_obs_e = rtDW->x_e[5];

  /* Switch: '<S1>/Switch2' incorporates:
   *  Inport: '<Root>/kalman_off_on'
   *  Switch: '<S1>/Switch3'
   */
  if (!rtU->kalman_off_on) {
    rtDW->rtb_e_dq_obs_idx_0 = 0.0F;
    rtDW->rtb_e_xy_obs_idx_0 = 0.0F;
    rtDW->rtb_e_dq_obs_e = 0.0F;
    rtDW->rtb_e_xy_obs_b = 0.0F;
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
  /* MATLAB Function 'uz_codegen/seq_2_act_sw_all': '<S9>:1' */
  /* '<S9>:1:3' act_sw_1 = single(zeros(24,1)); */
  /* '<S9>:1:4' act_sw_2 = single(zeros(24,1)); */
  /* '<S9>:1:5' act_sw_3 = single(zeros(24,1)); */
  /* '<S9>:1:6' act_sw_4 = single(zeros(24,1)); */
  /* '<S9>:1:7' act_sw_5 = single(zeros(24,1)); */
  /*  columns=sequence, rows=active switch postion               */
  /* '<S9>:1:10' seq_table_svm24 = single([   8, 9,41,43,47; */
  /* '<S9>:1:11'                              1, 9,11,43,59; */
  /* '<S9>:1:12'                              1, 9,11,27,59; */
  /* '<S9>:1:13'                              8, 9,11,27,31; */
  /* '<S9>:1:14'                              8,10,11,27,31; */
  /* '<S9>:1:15'                              2,10,26,27,59; */
  /* '<S9>:1:16'                              2,18,26,27,59; */
  /* '<S9>:1:17'                             16,18,26,27,31; */
  /* '<S9>:1:18'                             16,18,26,30,31; */
  /* '<S9>:1:19'                              2,18,22,30,62; */
  /* '<S9>:1:20'                              2,18,22,54,62; */
  /* '<S9>:1:21'                             16,18,22,54,55; */
  /* '<S9>:1:22'                             16,20,22,54,55; */
  /* '<S9>:1:23'                              4,20,52,54,62; */
  /* '<S9>:1:24'                              4,36,52,54,62; */
  /* '<S9>:1:25'                             32,36,52,54,55; */
  /* '<S9>:1:26'                             32,36,52,53,55; */
  /* '<S9>:1:27'                              4,36,37,53,61; */
  /* '<S9>:1:28'                              4,36,37,45,61; */
  /* '<S9>:1:29'                             32,36,37,45,47; */
  /* '<S9>:1:30'                             32,33,37,45,47; */
  /* '<S9>:1:31'                              1,33,41,45,61; */
  /* '<S9>:1:32'                              1, 9,41,45,61; */
  /* '<S9>:1:33'                              8, 9,41,45,47]); */
  /* '<S9>:1:35' act_sw_1 = seq_table_svm24(:,1); */
  /* '<S9>:1:36' act_sw_2 = seq_table_svm24(:,2); */
  /* '<S9>:1:37' act_sw_3 = seq_table_svm24(:,3); */
  /* '<S9>:1:38' act_sw_4 = seq_table_svm24(:,4); */
  /* '<S9>:1:39' act_sw_5 = seq_table_svm24(:,5); */
  /* MATLAB Function 'uz_codegen/deadbeat_solution': '<S5>:1' */
  /* '<S5>:1:3' i_d_pu = i_d_pu + single(e_dq_obs(1)); */
  rtDW->rtb_i_dq_obs_idx_0 += rtDW->rtb_e_dq_obs_idx_0;

  /* '<S5>:1:4' i_q_pu = i_q_pu + single(e_dq_obs(2)); */
  rtDW->rtb_v_1_idx_pu_idx_1 += rtDW->rtb_e_dq_obs_e;

  /* '<S5>:1:6' v_d_ref_pu = (i_d_ref_pu-i_d_pu)/(Ts_times_ZB_over_Ld) + i_d_pu*Rs_over_ZB - omega_el*Lq_over_LB*i_q_pu; */
  /* '<S5>:1:7' v_q_ref_pu = (i_q_ref_pu-i_q_pu)/(Ts_times_ZB_over_Lq) + i_q_pu*Rs_over_ZB + omega_el*(Ld_over_LB*i_d_pu+psi_pm_over_psiB); */
  /*  v_x_ref_pu = (i_x_ref_pu-i_x_pu)/(Ts_times_ZB_over_Lx) + i_x_pu*Rs_over_ZB; */
  /*  v_y_ref_pu = (i_y_ref_pu-i_y_pu)/(Ts_times_ZB_over_Ly) + i_y_pu*Rs_over_ZB; */
  /* '<S5>:1:10' v_x_ref_pu = single(0.0); */
  /* '<S5>:1:11' v_y_ref_pu = single(0.0); */
  /* '<S5>:1:13' angle_ref = mod(atan2(v_q_ref_pu, v_d_ref_pu) + theta_el, 2*pi); */
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

  /* '<S5>:1:15' sector_ref = 0.0; */
  rtDW->sector_ref = 0;

  /* '<S5>:1:16' if (angle_ref >= 0.0 && angle_ref < pi/180*15) */
  if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 0.0F) && (rtDW->rtb_v_1_idx_pu_idx_1 <
       0.26179938779914941)) {
    /* '<S5>:1:17' sector_ref = 1.0; */
    rtDW->sector_ref = 1;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 0.26179938779914941) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 0.52359877559829882)) {
    /* '<S5>:1:18' elseif (angle_ref >= pi/180*15 && angle_ref < pi/180*30) */
    /* '<S5>:1:19' sector_ref = 2.0; */
    rtDW->sector_ref = 2;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 0.52359877559829882) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 0.78539816339744828)) {
    /* '<S5>:1:20' elseif (angle_ref >= pi/180*30 && angle_ref < pi/180*45) */
    /* '<S5>:1:21' sector_ref = 3.0; */
    rtDW->sector_ref = 3;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 0.78539816339744828) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 1.0471975511965976)) {
    /* '<S5>:1:22' elseif (angle_ref >= pi/180*45 && angle_ref < pi/180*60) */
    /* '<S5>:1:23' sector_ref = 4.0; */
    rtDW->sector_ref = 4;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 1.0471975511965976) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 1.3089969389957472)) {
    /* '<S5>:1:24' elseif (angle_ref >= pi/180*60 && angle_ref < pi/180*75) */
    /* '<S5>:1:25' sector_ref = 5.0; */
    rtDW->sector_ref = 5;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 1.3089969389957472) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 1.5707963267948966)) {
    /* '<S5>:1:26' elseif (angle_ref >= pi/180*75 && angle_ref < pi/180*90) */
    /* '<S5>:1:27' sector_ref = 6.0; */
    rtDW->sector_ref = 6;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 1.5707963267948966) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 1.8325957145940461)) {
    /* '<S5>:1:28' elseif (angle_ref >= pi/180*90 && angle_ref < pi/180*105) */
    /* '<S5>:1:29' sector_ref = 7.0; */
    rtDW->sector_ref = 7;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 1.8325957145940461) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 2.0943951023931953)) {
    /* '<S5>:1:30' elseif (angle_ref >= pi/180*105 && angle_ref < pi/180*120) */
    /* '<S5>:1:31' sector_ref = 8.0; */
    rtDW->sector_ref = 8;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 2.0943951023931953) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 2.3561944901923448)) {
    /* '<S5>:1:32' elseif (angle_ref >= pi/180*120 && angle_ref < pi/180*135) */
    /* '<S5>:1:33' sector_ref = 9.0; */
    rtDW->sector_ref = 9;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 2.3561944901923448) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 2.6179938779914944)) {
    /* '<S5>:1:34' elseif (angle_ref >= pi/180*135 && angle_ref < pi/180*150) */
    /* '<S5>:1:35' sector_ref = 10.0; */
    rtDW->sector_ref = 10;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 2.6179938779914944) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 2.8797932657906435)) {
    /* '<S5>:1:36' elseif (angle_ref >= pi/180*150 && angle_ref < pi/180*165) */
    /* '<S5>:1:37' sector_ref = 11.0; */
    rtDW->sector_ref = 11;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 2.8797932657906435) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 3.1415926535897931)) {
    /* '<S5>:1:38' elseif (angle_ref >= pi/180*165 && angle_ref < pi/180*180) */
    /* '<S5>:1:39' sector_ref = 12.0; */
    rtDW->sector_ref = 12;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 3.1415926535897931) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 3.4033920413889427)) {
    /* '<S5>:1:40' elseif (angle_ref >= pi/180*180 && angle_ref < pi/180*195) */
    /* '<S5>:1:41' sector_ref = 13.0; */
    rtDW->sector_ref = 13;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 3.4033920413889427) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 3.6651914291880923)) {
    /* '<S5>:1:42' elseif (angle_ref >= pi/180*195 && angle_ref < pi/180*210) */
    /* '<S5>:1:43' sector_ref = 14.0; */
    rtDW->sector_ref = 14;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 3.6651914291880923) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 3.9269908169872414)) {
    /* '<S5>:1:44' elseif (angle_ref >= pi/180*210 && angle_ref < pi/180*225) */
    /* '<S5>:1:45' sector_ref = 15.0; */
    rtDW->sector_ref = 15;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 3.9269908169872414) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 4.1887902047863905)) {
    /* '<S5>:1:46' elseif (angle_ref >= pi/180*225 && angle_ref < pi/180*240) */
    /* '<S5>:1:47' sector_ref = 16.0; */
    rtDW->sector_ref = 16;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 4.1887902047863905) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 4.4505895925855405)) {
    /* '<S5>:1:48' elseif (angle_ref >= pi/180*240 && angle_ref < pi/180*255) */
    /* '<S5>:1:49' sector_ref = 17.0; */
    rtDW->sector_ref = 17;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 4.4505895925855405) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 4.71238898038469)) {
    /* '<S5>:1:50' elseif (angle_ref >= pi/180*255 && angle_ref < pi/180*270) */
    /* '<S5>:1:51' sector_ref = 18.0; */
    rtDW->sector_ref = 18;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 4.71238898038469) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 4.9741883681838388)) {
    /* '<S5>:1:52' elseif (angle_ref >= pi/180*270 && angle_ref < pi/180*285) */
    /* '<S5>:1:53' sector_ref = 19.0; */
    rtDW->sector_ref = 19;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 4.9741883681838388) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 5.2359877559829888)) {
    /* '<S5>:1:54' elseif (angle_ref >= pi/180*285 && angle_ref < pi/180*300) */
    /* '<S5>:1:55' sector_ref = 20.0; */
    rtDW->sector_ref = 20;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 5.2359877559829888) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 5.497787143782138)) {
    /* '<S5>:1:56' elseif (angle_ref >= pi/180*300 && angle_ref < pi/180*315) */
    /* '<S5>:1:57' sector_ref = 21.0; */
    rtDW->sector_ref = 21;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 5.497787143782138) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 5.7595865315812871)) {
    /* '<S5>:1:58' elseif (angle_ref >= pi/180*315 && angle_ref < pi/180*330) */
    /* '<S5>:1:59' sector_ref = 22.0; */
    rtDW->sector_ref = 22;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 5.7595865315812871) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 6.0213859193804371)) {
    /* '<S5>:1:60' elseif (angle_ref >= pi/180*330 && angle_ref < pi/180*345) */
    /* '<S5>:1:61' sector_ref = 23.0; */
    rtDW->sector_ref = 23;
  } else if ((rtDW->rtb_v_1_idx_pu_idx_1 >= 6.0213859193804371) &&
             (rtDW->rtb_v_1_idx_pu_idx_1 < 6.2831853071795862)) {
    /* '<S5>:1:62' elseif (angle_ref >= pi/180*345 && angle_ref < pi/180*360) */
    /* '<S5>:1:63' sector_ref = 24.0; */
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
  /* '<S4>:1:12' v_alpha_beta_pu = single([ %0.0,0.0; */
  /* '<S4>:1:13' 0.333333, -0.000000; */
  /* '<S4>:1:14' -0.166667, 0.288675; */
  /* '<S4>:1:15' 0.166667, 0.288675; */
  /* '<S4>:1:16' -0.166667, -0.288675; */
  /* '<S4>:1:17' 0.166667, -0.288675; */
  /* '<S4>:1:18' -0.333333, 0.000000; */
  /* '<S4>:1:19' 0.000000, 0.000000; */
  /* '<S4>:1:20' 0.288675, 0.166667; */
  /* '<S4>:1:21' 0.622008, 0.166667; */
  /* '<S4>:1:22' 0.122008, 0.455342; */
  /* '<S4>:1:23' 0.455342, 0.455342; */
  /* '<S4>:1:24' 0.122008, -0.122008; */
  /* '<S4>:1:25' 0.455342, -0.122008; */
  /* '<S4>:1:26' -0.044658, 0.166667; */
  /* '<S4>:1:27' 0.288675, 0.166667; */
  /* '<S4>:1:28' -0.288675, 0.166667; */
  /* '<S4>:1:29' 0.044658, 0.166667; */
  /* '<S4>:1:30' -0.455342, 0.455342; */
  /* '<S4>:1:31' -0.122008, 0.455342; */
  /* '<S4>:1:32' -0.455342, -0.122008; */
  /* '<S4>:1:33' -0.122008, -0.122008; */
  /* '<S4>:1:34' -0.622008, 0.166667; */
  /* '<S4>:1:35' -0.288675, 0.166667; */
  /* '<S4>:1:36' 0.000000, 0.333333; */
  /* '<S4>:1:37' 0.333333, 0.333333; */
  /* '<S4>:1:38' -0.166667, 0.622008; */
  /* '<S4>:1:39' 0.166667, 0.622008; */
  /* '<S4>:1:40' -0.166667, 0.044658; */
  /* '<S4>:1:41' 0.166667, 0.044658; */
  /* '<S4>:1:42' -0.333333, 0.333333; */
  /* '<S4>:1:43' 0.000000, 0.333333; */
  /* '<S4>:1:44' -0.000000, -0.333333; */
  /* '<S4>:1:45' 0.333333, -0.333333; */
  /* '<S4>:1:46' -0.166667, -0.044658; */
  /* '<S4>:1:47' 0.166667, -0.044658; */
  /* '<S4>:1:48' -0.166667, -0.622008; */
  /* '<S4>:1:49' 0.166667, -0.622008; */
  /* '<S4>:1:50' -0.333333, -0.333333; */
  /* '<S4>:1:51' -0.000000, -0.333333; */
  /* '<S4>:1:52' 0.288675, -0.166667; */
  /* '<S4>:1:53' 0.622008, -0.166667; */
  /* '<S4>:1:54' 0.122008, 0.122008; */
  /* '<S4>:1:55' 0.455342, 0.122008; */
  /* '<S4>:1:56' 0.122008, -0.455342; */
  /* '<S4>:1:57' 0.455342, -0.455342; */
  /* '<S4>:1:58' -0.044658, -0.166667; */
  /* '<S4>:1:59' 0.288675, -0.166667; */
  /* '<S4>:1:60' -0.288675, -0.166667; */
  /* '<S4>:1:61' 0.044658, -0.166667; */
  /* '<S4>:1:62' -0.455342, 0.122008; */
  /* '<S4>:1:63' -0.122008, 0.122008; */
  /* '<S4>:1:64' -0.455342, -0.455342; */
  /* '<S4>:1:65' -0.122008, -0.455342; */
  /* '<S4>:1:66' -0.622008, -0.166667; */
  /* '<S4>:1:67' -0.288675, -0.166667; */
  /* '<S4>:1:68' -0.000000, -0.000000; */
  /* '<S4>:1:69' 0.333333, -0.000000; */
  /* '<S4>:1:70' -0.166667, 0.288675; */
  /* '<S4>:1:71' 0.166667, 0.288675; */
  /* '<S4>:1:72' -0.166667, -0.288675; */
  /* '<S4>:1:73' 0.166667, -0.288675; */
  /* '<S4>:1:74' -0.333333, 0.000000]); */
  /* 0.0,0.0; */
  /*  0.0, 0.0 */
  /* '<S4>:1:77' v_X_Y_pu = single([% 0.0, 0.0; */
  /* '<S4>:1:78' 0.333333,0; */
  /* '<S4>:1:79' -0.166667,-0.288675; */
  /* '<S4>:1:80' 0.166667,-0.288675; */
  /* '<S4>:1:81' -0.166667,0.288675; */
  /* '<S4>:1:82' 0.166667,0.288675; */
  /* '<S4>:1:83' -0.333333,0; */
  /* '<S4>:1:84' 0,0; */
  /* '<S4>:1:85' -0.288675,0.166667; */
  /* '<S4>:1:86' 0.0446580,0.166667; */
  /* '<S4>:1:87' -0.455342,-0.122008; */
  /* '<S4>:1:88' -0.122008,-0.122008; */
  /* '<S4>:1:89' -0.455342,0.455342; */
  /* '<S4>:1:90' -0.122008,0.455342; */
  /* '<S4>:1:91' -0.622008,0.166667; */
  /* '<S4>:1:92' -0.288675,0.166667; */
  /* '<S4>:1:93' 0.288675,0.166667; */
  /* '<S4>:1:94' 0.622008,0.166667; */
  /* '<S4>:1:95' 0.122008,-0.122008; */
  /* '<S4>:1:96' 0.455342,-0.122008; */
  /* '<S4>:1:97' 0.122008,0.455342; */
  /* '<S4>:1:98' 0.455342,0.455342; */
  /* '<S4>:1:99' -0.0446580,0.166667; */
  /* '<S4>:1:100' 0.288675,0.166667; */
  /* '<S4>:1:101' 0,0.333333; */
  /* '<S4>:1:102' 0.333333,0.333333; */
  /* '<S4>:1:103' -0.166667,0.0446580; */
  /* '<S4>:1:104' 0.166667,0.0446580; */
  /* '<S4>:1:105' -0.166667,0.622008; */
  /* '<S4>:1:106' 0.166667,0.622008; */
  /* '<S4>:1:107' -0.333333,0.333333; */
  /* '<S4>:1:108' 0,0.333333;0,-0.333333; */
  /* '<S4>:1:109' 0.333333,-0.333333; */
  /* '<S4>:1:110' -0.166667,-0.622008; */
  /* '<S4>:1:111' 0.166667,-0.622008; */
  /* '<S4>:1:112' -0.166667,-0.0446580; */
  /* '<S4>:1:113' 0.166667,-0.0446580; */
  /* '<S4>:1:114' -0.333333,-0.333333; */
  /* '<S4>:1:115' 0,-0.333333; */
  /* '<S4>:1:116' -0.288675,-0.166667; */
  /* '<S4>:1:117' 0.0446580,-0.166667; */
  /* '<S4>:1:118' -0.455342,-0.455342; */
  /* '<S4>:1:119' -0.122008,-0.455342; */
  /* '<S4>:1:120' -0.455342,0.122008; */
  /* '<S4>:1:121' -0.122008,0.122008; */
  /* '<S4>:1:122' -0.622008,-0.166667; */
  /* '<S4>:1:123' -0.288675,-0.166667; */
  /* '<S4>:1:124' 0.288675,-0.166667; */
  /* '<S4>:1:125' 0.622008,-0.166667; */
  /* '<S4>:1:126' 0.122008,-0.455342; */
  /* '<S4>:1:127' 0.455342,-0.455342; */
  /* '<S4>:1:128' 0.122008,0.122008; */
  /* '<S4>:1:129' 0.455342,0.122008; */
  /* '<S4>:1:130' -0.0446580,-0.166667; */
  /* '<S4>:1:131' 0.288675,-0.166667; */
  /* '<S4>:1:132' 0,0;0.333333,0; */
  /* '<S4>:1:133' -0.166667,-0.288675; */
  /* '<S4>:1:134' 0.166667,-0.288675; */
  /* '<S4>:1:135' -0.166667,0.288675; */
  /* '<S4>:1:136' 0.166667,0.288675; */
  /* '<S4>:1:137' -0.333333,0]); */
  /*  0.0, 0.0; */
  /*  0.0, 0.0 */
  /* '<S4>:1:141' vd_1_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_1(idx_opt),1) *  cos_angle_pos + v_alpha_beta_pu(act_sw_1(idx_opt),2) * sin_angle_pos); */
  /* '<S4>:1:142' vq_1_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_1(idx_opt),1) * -sin_angle_pos + v_alpha_beta_pu(act_sw_1(idx_opt),2) * cos_angle_pos); */
  /* '<S4>:1:143' vx_1_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_1(idx_opt),1) * cos_angle_neg + v_X_Y_pu(act_sw_1(idx_opt),2) * sin_angle_neg); */
  /* '<S4>:1:144' vy_1_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_1(idx_opt),1) * -sin_angle_neg + v_X_Y_pu(act_sw_1(idx_opt),2) * cos_angle_neg); */
  /* '<S4>:1:146' vd_2_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_2(idx_opt),1) *  cos_angle_pos + v_alpha_beta_pu(act_sw_2(idx_opt),2) * sin_angle_pos); */
  /* '<S4>:1:147' vq_2_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_2(idx_opt),1) * -sin_angle_pos + v_alpha_beta_pu(act_sw_2(idx_opt),2) * cos_angle_pos); */
  /* '<S4>:1:148' vx_2_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_2(idx_opt),1) * cos_angle_neg + v_X_Y_pu(act_sw_2(idx_opt),2) * sin_angle_neg); */
  /* '<S4>:1:149' vy_2_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_2(idx_opt),1) * -sin_angle_neg + v_X_Y_pu(act_sw_2(idx_opt),2) * cos_angle_neg); */
  /* '<S4>:1:151' vd_3_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_3(idx_opt),1) *  cos_angle_pos + v_alpha_beta_pu(act_sw_3(idx_opt),2) * sin_angle_pos); */
  /* '<S4>:1:152' vq_3_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_3(idx_opt),1) * -sin_angle_pos + v_alpha_beta_pu(act_sw_3(idx_opt),2) * cos_angle_pos); */
  /* '<S4>:1:153' vx_3_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_3(idx_opt),1) * cos_angle_neg + v_X_Y_pu(act_sw_3(idx_opt),2) * sin_angle_neg); */
  /* '<S4>:1:154' vy_3_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_3(idx_opt),1) * -sin_angle_neg + v_X_Y_pu(act_sw_3(idx_opt),2) * cos_angle_neg); */
  /* '<S4>:1:156' vd_4_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_4(idx_opt),1) *  cos_angle_pos + v_alpha_beta_pu(act_sw_4(idx_opt),2) * sin_angle_pos); */
  /* '<S4>:1:157' vq_4_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_4(idx_opt),1) * -sin_angle_pos + v_alpha_beta_pu(act_sw_4(idx_opt),2) * cos_angle_pos); */
  /* '<S4>:1:158' vx_4_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_4(idx_opt),1) * cos_angle_neg + v_X_Y_pu(act_sw_4(idx_opt),2) * sin_angle_neg); */
  /* '<S4>:1:159' vy_4_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_4(idx_opt),1) * -sin_angle_neg + v_X_Y_pu(act_sw_4(idx_opt),2) * cos_angle_neg); */
  /* '<S4>:1:161' vd_5_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_5(idx_opt),1) *  cos_angle_pos + v_alpha_beta_pu(act_sw_5(idx_opt),2) * sin_angle_pos); */
  /* '<S4>:1:162' vq_5_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_5(idx_opt),1) * -sin_angle_pos + v_alpha_beta_pu(act_sw_5(idx_opt),2) * cos_angle_pos); */
  /* '<S4>:1:163' vx_5_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_5(idx_opt),1) * cos_angle_neg + v_X_Y_pu(act_sw_5(idx_opt),2) * sin_angle_neg); */
  /* '<S4>:1:164' vy_5_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_5(idx_opt),1) * -sin_angle_neg + v_X_Y_pu(act_sw_5(idx_opt),2) * cos_angle_neg); */
  /* '<S4>:1:166' v_1_idx_pu = [vd_1_idx_pu; vq_1_idx_pu; vx_1_idx_pu; vy_1_idx_pu]; */
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

  /* '<S4>:1:167' v_2_idx_pu = [vd_2_idx_pu; vq_2_idx_pu; vx_2_idx_pu; vy_2_idx_pu]; */
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

  /* '<S4>:1:168' v_3_idx_pu = [vd_3_idx_pu; vq_3_idx_pu; vx_3_idx_pu; vy_3_idx_pu]; */
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

  /* '<S4>:1:169' v_4_idx_pu = [vd_4_idx_pu; vq_4_idx_pu; vx_4_idx_pu; vy_4_idx_pu]; */
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

  /* '<S4>:1:170' v_5_idx_pu = [vd_5_idx_pu; vq_5_idx_pu; vx_5_idx_pu; vy_5_idx_pu]; */
  rtDW->d_j = rtDW->act_sw_5[rtDW->sector_ref - 1];
  rtDW->rtb_v_5_idx_pu_idx_1 = v_alpha_beta_pu[rtDW->d_j - 1];
  rtDW->rtb_v_5_idx_pu_idx_2 = v_alpha_beta_pu[rtDW->d_j + 61];
  rtDW->rtb_v_5_idx_pu_idx_0 = (rtDW->rtb_v_5_idx_pu_idx_1 * rtDW->SinCos1_o2 +
    rtDW->rtb_v_5_idx_pu_idx_2 * rtDW->w6theta_el) * rtU->v_DC_pu;
  rtDW->rtb_v_5_idx_pu_idx_1 = (rtDW->rtb_v_5_idx_pu_idx_1 * -rtDW->w6theta_el +
    rtDW->rtb_v_5_idx_pu_idx_2 * rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->SinCos1_o2 = v_X_Y_pu[rtDW->d_j - 1];
  rtDW->w6theta_el = v_X_Y_pu[rtDW->d_j + 61];
  rtDW->rtb_v_5_idx_pu_idx_2 = (rtDW->SinCos1_o2 * rtDW->SinCos2_o2 +
    rtDW->w6theta_el * rtDW->SinCos2_o1) * rtU->v_DC_pu;
  rtDW->rtb_v_5_idx_pu_idx_3 = (rtDW->SinCos1_o2 * -rtDW->SinCos2_o1 +
    rtDW->w6theta_el * rtDW->SinCos2_o2) * rtU->v_DC_pu;

  /* MATLAB Function: '<S1>/state_space_mdl' incorporates:
   *  Inport: '<Root>/HC_off_on'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/Ts_times_ZB_over_Lx'
   *  Inport: '<Root>/Ts_times_ZB_over_Ly'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/psiPM_h_pu'
   */
  /* MATLAB Function 'uz_codegen/state_space_mdl': '<S10>:1' */
  /* '<S10>:1:3' A = [ -Ts_times_ZB_over_Ld*Rs_over_ZB            Ts_times_ZB_over_Ld*Lq_over_LB*w_e_pu   0                                      0                               ; */
  /* '<S10>:1:4'       -Ts_times_ZB_over_Lq*Ld_over_LB*w_e_pu    -Ts_times_ZB_over_Lq*Rs_over_ZB          0                                      0                               ; */
  /* '<S10>:1:5'       0                                          0                                       -Ts_times_ZB_over_Lx*Rs_over_ZB        -Ly_over_LB*w_e_pu              ; */
  /* '<S10>:1:6'       0                                          0                                        Lx_over_LB*w_e_pu                     -Ts_times_ZB_over_Ly*Rs_over_ZB]; */
  rtDW->A_n[0] = -rtU->Ts_times_ZB_over_Ld * rtU->Rs_over_ZB;
  rtDW->A_n[4] = rtDW->x0_idx_1;
  rtDW->A_n[8] = 0.0F;
  rtDW->A_n[12] = 0.0F;
  rtDW->A_n[1] = rtDW->x0_idx_2;
  rtDW->A_n[5] = -rtU->Ts_times_ZB_over_Lq * rtU->Rs_over_ZB;
  rtDW->A_n[9] = 0.0F;
  rtDW->A_n[13] = 0.0F;
  rtDW->A_n[2] = 0.0F;
  rtDW->A_n[6] = 0.0F;
  rtDW->A_n[10] = -rtU->Ts_times_ZB_over_Lx * rtU->Rs_over_ZB;
  rtDW->A_n[14] = rtDW->x0_idx_3;
  rtDW->A_n[3] = 0.0F;
  rtDW->A_n[7] = 0.0F;
  rtDW->A_n[11] = rtDW->A_tmp;
  rtDW->A_n[15] = -rtU->Ts_times_ZB_over_Ly * rtU->Rs_over_ZB;

  /* '<S10>:1:8' psiPM5 = psiPM_h_pu(1); */
  /* '<S10>:1:9' psiPM7 = psiPM_h_pu(2); */
  /* '<S10>:1:11' phi5 = phiPM_h(1); */
  /* '<S10>:1:12' phi7 = phiPM_h(2); */
  /*  w3theta_el = single(3*theta_el); */
  /* '<S10>:1:15' w6theta_el = single(6*theta_el); */
  /*  w9theta_el = single(9*theta_el); */
  /*  w12theta_el = single(12*theta_el); */
  /* '<S10>:1:19' B = [Ts_times_ZB_over_Ld    0                       0                       0                       ; */
  /* '<S10>:1:20'      0                      Ts_times_ZB_over_Lq     0                       0                       ; */
  /* '<S10>:1:21'      0                      0                       Ts_times_ZB_over_Lx     0                       ; */
  /* '<S10>:1:22'      0                      0                       0                       Ts_times_ZB_over_Ly     ]; */
  rtDW->B_b[0] = rtU->Ts_times_ZB_over_Ld;
  rtDW->B_b[4] = 0.0F;
  rtDW->B_b[8] = 0.0F;
  rtDW->B_b[12] = 0.0F;
  rtDW->B_b[1] = 0.0F;
  rtDW->B_b[5] = rtU->Ts_times_ZB_over_Lq;
  rtDW->B_b[9] = 0.0F;
  rtDW->B_b[13] = 0.0F;
  rtDW->B_b[2] = 0.0F;
  rtDW->B_b[6] = 0.0F;
  rtDW->B_b[10] = rtU->Ts_times_ZB_over_Lx;
  rtDW->B_b[14] = 0.0F;
  rtDW->B_b[3] = 0.0F;
  rtDW->B_b[7] = 0.0F;
  rtDW->B_b[11] = 0.0F;
  rtDW->B_b[15] = rtU->Ts_times_ZB_over_Ly;

  /* '<S10>:1:24' C = [1   0   0   0; */
  /* '<S10>:1:25'      0   1   0   0; */
  /* '<S10>:1:26'      0   0   1   0; */
  /* '<S10>:1:27'      0   0   0   1]; */
  /* '<S10>:1:29' D = [    e_dq_obs(1); */
  /* '<S10>:1:30'          -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB + e_dq_obs(2); */
  /* '<S10>:1:31'          e_xy_obs(1); */
  /* '<S10>:1:32'          e_xy_obs(2)]; */
  rtDW->D[0] = rtDW->rtb_e_dq_obs_idx_0;
  rtDW->x0_idx_1 = rtDW->rtb_SinCos2_o1_tmp + rtDW->rtb_e_dq_obs_e;
  rtDW->D[1] = rtDW->x0_idx_1;
  rtDW->D[2] = rtDW->rtb_e_xy_obs_idx_0;
  rtDW->D[3] = rtDW->rtb_e_xy_obs_b;

  /* '<S10>:1:34' E = [    e_dq_obs(1); */
  /* '<S10>:1:35'          -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB + e_dq_obs(2); */
  /* '<S10>:1:36'          -w_e_pu*(psiPM5*sin(w6theta_el+phi5) - psiPM7*sin(w6theta_el+phi7)-psiPM5*6*sin(w6theta_el+phi5) - psiPM7*6*sin(w6theta_el+phi7)) + e_xy_obs(1); */
  /* '<S10>:1:37'          -w_e_pu*(psiPM5*cos(w6theta_el+phi5) + psiPM7*cos(w6theta_el+phi7) + psiPM5*6*cos(w6theta_el+phi5) - psiPM7*6*cos(w6theta_el+phi7)) + e_xy_obs(2)]; */
  rtDW->SinCos1_o2 = sinf(rtDW->rtb_SinCos2_o2_tmp);
  rtDW->SinCos2_o1 = sinf(rtDW->x0_idx_0);
  rtDW->SinCos2_o2 = cosf(rtDW->rtb_SinCos2_o2_tmp);
  rtDW->w6theta_el = cosf(rtDW->x0_idx_0);
  rtDW->E[0] = rtDW->rtb_e_dq_obs_idx_0;
  rtDW->E[1] = rtDW->x0_idx_1;
  rtDW->E[2] = (((rtU->psiPM_h_pu[0] * rtDW->SinCos1_o2 - rtU->psiPM_h_pu[1] *
                  rtDW->SinCos2_o1) - rtU->psiPM_h_pu[0] * 6.0F *
                 rtDW->SinCos1_o2) - rtU->psiPM_h_pu[1] * 6.0F *
                rtDW->SinCos2_o1) * -rtU->omega_el_pu + rtDW->rtb_e_xy_obs_idx_0;
  rtDW->E[3] = (((rtU->psiPM_h_pu[0] * rtDW->SinCos2_o2 + rtU->psiPM_h_pu[1] *
                  rtDW->w6theta_el) + rtU->psiPM_h_pu[0] * 6.0F *
                 rtDW->SinCos2_o2) - rtU->psiPM_h_pu[1] * 6.0F *
                rtDW->w6theta_el) * -rtU->omega_el_pu + rtDW->rtb_e_xy_obs_b;

  /* '<S10>:1:39' x0 = [id_pu; iq_pu; ix_pu; iy_pu]; */
  rtDW->x0_idx_0 = rtDW->v_t0[0];
  rtDW->x0_idx_1 = rtDW->v_t0[1];
  rtDW->x0_idx_2 = rtDW->v_t0[2];
  rtDW->x0_idx_3 = rtDW->v_t0[3];

  /* '<S10>:1:41' u0 = [0;0;0;0]; */
  /*  zero voltage applied */
  /* '<S10>:1:42' u1 = [v_1_pu(1); v_1_pu(2); v_1_pu(3); v_1_pu(4)]; */
  /*  first active vector */
  /* '<S10>:1:43' u2 = [v_2_pu(1); v_2_pu(2); v_2_pu(3); v_2_pu(4)]; */
  /*  second active vector */
  /* '<S10>:1:44' u3 = [v_3_pu(1); v_3_pu(2); v_3_pu(3); v_3_pu(4)]; */
  /*  third active vector */
  /* '<S10>:1:45' u4 = [v_4_pu(1); v_4_pu(2); v_4_pu(3); v_4_pu(4)]; */
  /*  fourth active vector */
  /* '<S10>:1:46' u5 = [v_5_pu(1); v_5_pu(2); v_5_pu(3); v_5_pu(4)]; */
  /*  fifth active vector */
  /*  calculate the gradients */
  /*  .*2 because we calculate current evolution only for half of the */
  /*  period and mirror it???  */
  /* '<S10>:1:51' switch HC_off_on */
  if (!rtU->HC_off_on) {
    rtDW->d_j = 0;
  } else if (rtU->HC_off_on) {
    rtDW->d_j = 1;
  } else {
    rtDW->d_j = -1;
  }

  switch (rtDW->d_j) {
   case 0:
    /* '<S10>:1:52' case false */
    /* '<S10>:1:53' m0 = C*(A*x0+B*u0+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->E_b[rtDW->d_j] = (rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + rtDW->D
        [rtDW->d_j];
    }

    /* '<S10>:1:54' m1 = C*(A*x0+B*u1+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m6[rtDW->d_j] = ((real32_T)b[rtDW->d_j + 12] * rtDW->E_b[3] +
        ((real32_T)b[rtDW->d_j + 8] * rtDW->E_b[2] + ((real32_T)b[rtDW->d_j + 4]
        * rtDW->E_b[1] + (real32_T)b[rtDW->d_j] * rtDW->E_b[0]))) * 2.0F;
      rtDW->E_d[rtDW->d_j] = ((rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + (rtDW->
        B_b[rtDW->d_j + 12] * rtDW->rtb_v_1_idx_pu_idx_3 + (rtDW->B_b[rtDW->d_j
        + 8] * rtDW->q + (rtDW->B_b[rtDW->d_j + 4] * rtDW->rtb_v_1_idx_pu_idx_1
                          + rtDW->B_b[rtDW->d_j] * rtDW->rtb_i_dq_obs_idx_0))))
        + rtDW->D[rtDW->d_j];
    }

    /* '<S10>:1:55' m2 = C*(A*x0+B*u2+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m1[rtDW->d_j] = ((real32_T)b[rtDW->d_j + 12] * rtDW->E_d[3] +
        ((real32_T)b[rtDW->d_j + 8] * rtDW->E_d[2] + ((real32_T)b[rtDW->d_j + 4]
        * rtDW->E_d[1] + (real32_T)b[rtDW->d_j] * rtDW->E_d[0]))) * 2.0F;
      rtDW->E_b[rtDW->d_j] = ((rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + (rtDW->
        B_b[rtDW->d_j + 12] * rtDW->rtb_v_2_idx_pu_idx_3 + (rtDW->B_b[rtDW->d_j
        + 8] * rtDW->rtb_v_2_idx_pu_idx_2 + (rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_2_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_2_idx_pu_idx_0)))) + rtDW->D[rtDW->d_j];
    }

    /* '<S10>:1:56' m3 = C*(A*x0+B*u3+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m2[rtDW->d_j] = ((real32_T)b[rtDW->d_j + 12] * rtDW->E_b[3] +
        ((real32_T)b[rtDW->d_j + 8] * rtDW->E_b[2] + ((real32_T)b[rtDW->d_j + 4]
        * rtDW->E_b[1] + (real32_T)b[rtDW->d_j] * rtDW->E_b[0]))) * 2.0F;
      rtDW->E_d[rtDW->d_j] = ((rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + (rtDW->
        B_b[rtDW->d_j + 12] * rtDW->rtb_v_3_idx_pu_idx_3 + (rtDW->B_b[rtDW->d_j
        + 8] * rtDW->rtb_v_3_idx_pu_idx_2 + (rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_3_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_3_idx_pu_idx_0)))) + rtDW->D[rtDW->d_j];
    }

    /* '<S10>:1:57' m4 = C*(A*x0+B*u4+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m3[rtDW->d_j] = ((real32_T)b[rtDW->d_j + 12] * rtDW->E_d[3] +
        ((real32_T)b[rtDW->d_j + 8] * rtDW->E_d[2] + ((real32_T)b[rtDW->d_j + 4]
        * rtDW->E_d[1] + (real32_T)b[rtDW->d_j] * rtDW->E_d[0]))) * 2.0F;
      rtDW->E_b[rtDW->d_j] = ((rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + (rtDW->
        B_b[rtDW->d_j + 12] * rtDW->rtb_v_4_idx_pu_idx_3 + (rtDW->B_b[rtDW->d_j
        + 8] * rtDW->rtb_v_4_idx_pu_idx_2 + (rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_4_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_4_idx_pu_idx_0)))) + rtDW->D[rtDW->d_j];
    }

    /* '<S10>:1:58' m5 = C*(A*x0+B*u5+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m4[rtDW->d_j] = ((real32_T)b[rtDW->d_j + 12] * rtDW->E_b[3] +
        ((real32_T)b[rtDW->d_j + 8] * rtDW->E_b[2] + ((real32_T)b[rtDW->d_j + 4]
        * rtDW->E_b[1] + (real32_T)b[rtDW->d_j] * rtDW->E_b[0]))) * 2.0F;
      rtDW->E_d[rtDW->d_j] = ((rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + (rtDW->
        B_b[rtDW->d_j + 12] * rtDW->rtb_v_5_idx_pu_idx_3 + (rtDW->B_b[rtDW->d_j
        + 8] * rtDW->rtb_v_5_idx_pu_idx_2 + (rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_5_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_5_idx_pu_idx_0)))) + rtDW->D[rtDW->d_j];
    }

    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->E[rtDW->d_j] = ((real32_T)b[rtDW->d_j + 12] * rtDW->E_d[3] +
                            ((real32_T)b[rtDW->d_j + 8] * rtDW->E_d[2] +
        ((real32_T)b[rtDW->d_j + 4] * rtDW->E_d[1] + (real32_T)b[rtDW->d_j] *
         rtDW->E_d[0]))) * 2.0F;
    }

    /* '<S10>:1:59' m6 = m0; */
    /*  m0 = C*(A*x0+B*u0+D);  */
    /*  m1 = C*(A*x0+B*u1+D); */
    /*  m2 = C*(A*x0+B*u2+D); */
    /*  m3 = C*(A*x0+B*u3+D); */
    /*  m4 = C*(A*x0+B*u4+D); */
    /*  m5 = C*(A*x0+B*u5+D); */
    /*  m6 = m0; */
    break;

   case 1:
    /* '<S10>:1:67' case true */
    /* '<S10>:1:68' m0 = C*(A*x0+B*u0+E).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 16; rtDW->d_j++) {
      rtDW->rtb_m6_tmp[rtDW->d_j] = b[rtDW->d_j];
    }

    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->E_b[rtDW->d_j] = (rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + rtDW->E
        [rtDW->d_j];
    }

    /* '<S10>:1:69' m1 = C*(A*x0+B*u1+E).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m6[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
        rtDW->E_b[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 8] * rtDW->E_b[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] * rtDW->
                           E_b[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] *
                           rtDW->E_b[0]))) * 2.0F;
      rtDW->E_d[rtDW->d_j] = ((rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + (rtDW->
        B_b[rtDW->d_j + 12] * rtDW->rtb_v_1_idx_pu_idx_3 + (rtDW->B_b[rtDW->d_j
        + 8] * rtDW->q + (rtDW->B_b[rtDW->d_j + 4] * rtDW->rtb_v_1_idx_pu_idx_1
                          + rtDW->B_b[rtDW->d_j] * rtDW->rtb_i_dq_obs_idx_0))))
        + rtDW->E[rtDW->d_j];
    }

    /* '<S10>:1:70' m2 = C*(A*x0+B*u2+E).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m1[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
        rtDW->E_d[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 8] * rtDW->E_d[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] * rtDW->
                           E_d[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] *
                           rtDW->E_d[0]))) * 2.0F;
      rtDW->E_b[rtDW->d_j] = ((rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + (rtDW->
        B_b[rtDW->d_j + 12] * rtDW->rtb_v_2_idx_pu_idx_3 + (rtDW->B_b[rtDW->d_j
        + 8] * rtDW->rtb_v_2_idx_pu_idx_2 + (rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_2_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_2_idx_pu_idx_0)))) + rtDW->E[rtDW->d_j];
    }

    /* '<S10>:1:71' m3 = C*(A*x0+B*u3+E).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m2[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
        rtDW->E_b[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 8] * rtDW->E_b[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] * rtDW->
                           E_b[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] *
                           rtDW->E_b[0]))) * 2.0F;
      rtDW->E_d[rtDW->d_j] = ((rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + (rtDW->
        B_b[rtDW->d_j + 12] * rtDW->rtb_v_3_idx_pu_idx_3 + (rtDW->B_b[rtDW->d_j
        + 8] * rtDW->rtb_v_3_idx_pu_idx_2 + (rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_3_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_3_idx_pu_idx_0)))) + rtDW->E[rtDW->d_j];
    }

    /* '<S10>:1:72' m4 = C*(A*x0+B*u4+E).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m3[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
        rtDW->E_d[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 8] * rtDW->E_d[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] * rtDW->
                           E_d[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] *
                           rtDW->E_d[0]))) * 2.0F;
      rtDW->E_b[rtDW->d_j] = ((rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + (rtDW->
        B_b[rtDW->d_j + 12] * rtDW->rtb_v_4_idx_pu_idx_3 + (rtDW->B_b[rtDW->d_j
        + 8] * rtDW->rtb_v_4_idx_pu_idx_2 + (rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_4_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_4_idx_pu_idx_0)))) + rtDW->E[rtDW->d_j];
    }

    /* '<S10>:1:73' m5 = C*(A*x0+B*u5+E).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m4[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
        rtDW->E_b[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 8] * rtDW->E_b[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] * rtDW->
                           E_b[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] *
                           rtDW->E_b[0]))) * 2.0F;
      rtDW->E_d[rtDW->d_j] = ((rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
        rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0))) + (rtDW->
        B_b[rtDW->d_j + 12] * rtDW->rtb_v_5_idx_pu_idx_3 + (rtDW->B_b[rtDW->d_j
        + 8] * rtDW->rtb_v_5_idx_pu_idx_2 + (rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_5_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_5_idx_pu_idx_0)))) + rtDW->E[rtDW->d_j];
    }

    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->E[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
                            rtDW->E_d[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j
        + 8] * rtDW->E_d[2] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] *
        rtDW->E_d[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] * rtDW->E_d[0]))) *
        2.0F;
    }

    /* '<S10>:1:74' m6 = m0; */
    /*  m0 = C*(A*x0+B*u0+E);  */
    /*  m1 = C*(A*x0+B*u1+E); */
    /*  m2 = C*(A*x0+B*u2+E); */
    /*  m3 = C*(A*x0+B*u3+E); */
    /*  m4 = C*(A*x0+B*u4+E); */
    /*  m5 = C*(A*x0+B*u5+E); */
    /*  m6 = m0; */
    break;

   default:
    /* '<S10>:1:82' otherwise */
    /* '<S10>:1:83' m0 = C*(A*x0+B*u0+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->E[rtDW->d_j] = rtDW->A_n[rtDW->d_j + 12] * rtDW->x0_idx_3 +
        (rtDW->A_n[rtDW->d_j + 8] * rtDW->x0_idx_2 + (rtDW->A_n[rtDW->d_j + 4] *
          rtDW->x0_idx_1 + rtDW->A_n[rtDW->d_j] * rtDW->x0_idx_0));
    }

    for (rtDW->d_j = 0; rtDW->d_j < 16; rtDW->d_j++) {
      rtDW->rtb_m6_tmp[rtDW->d_j] = b[rtDW->d_j];
    }

    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->E_b[rtDW->d_j] = rtDW->E[rtDW->d_j] + rtDW->D[rtDW->d_j];
    }

    /* '<S10>:1:84' m1 = C*(A*x0+B*u1+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m6[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
        rtDW->E_b[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 8] * rtDW->E_b[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] * rtDW->
                           E_b[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] *
                           rtDW->E_b[0]))) * 2.0F;
      rtDW->E_d[rtDW->d_j] = ((((rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_1_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_i_dq_obs_idx_0) + rtDW->B_b[rtDW->d_j + 8] * rtDW->q) +
        rtDW->B_b[rtDW->d_j + 12] * rtDW->rtb_v_1_idx_pu_idx_3) + rtDW->E
        [rtDW->d_j]) + rtDW->D[rtDW->d_j];
    }

    /* '<S10>:1:85' m2 = C*(A*x0+B*u2+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m1[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
        rtDW->E_d[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 8] * rtDW->E_d[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] * rtDW->
                           E_d[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] *
                           rtDW->E_d[0]))) * 2.0F;
      rtDW->E_b[rtDW->d_j] = ((((rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_2_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_2_idx_pu_idx_0) + rtDW->B_b[rtDW->d_j + 8] *
        rtDW->rtb_v_2_idx_pu_idx_2) + rtDW->B_b[rtDW->d_j + 12] *
        rtDW->rtb_v_2_idx_pu_idx_3) + rtDW->E[rtDW->d_j]) + rtDW->D[rtDW->d_j];
    }

    /* '<S10>:1:86' m3 = C*(A*x0+B*u3+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m2[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
        rtDW->E_b[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 8] * rtDW->E_b[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] * rtDW->
                           E_b[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] *
                           rtDW->E_b[0]))) * 2.0F;
      rtDW->E_d[rtDW->d_j] = ((((rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_3_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_3_idx_pu_idx_0) + rtDW->B_b[rtDW->d_j + 8] *
        rtDW->rtb_v_3_idx_pu_idx_2) + rtDW->B_b[rtDW->d_j + 12] *
        rtDW->rtb_v_3_idx_pu_idx_3) + rtDW->E[rtDW->d_j]) + rtDW->D[rtDW->d_j];
    }

    /* '<S10>:1:87' m4 = C*(A*x0+B*u4+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m3[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
        rtDW->E_d[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 8] * rtDW->E_d[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] * rtDW->
                           E_d[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] *
                           rtDW->E_d[0]))) * 2.0F;
      rtDW->E_b[rtDW->d_j] = ((((rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_4_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_4_idx_pu_idx_0) + rtDW->B_b[rtDW->d_j + 8] *
        rtDW->rtb_v_4_idx_pu_idx_2) + rtDW->B_b[rtDW->d_j + 12] *
        rtDW->rtb_v_4_idx_pu_idx_3) + rtDW->E[rtDW->d_j]) + rtDW->D[rtDW->d_j];
    }

    /* '<S10>:1:88' m5 = C*(A*x0+B*u5+D).*2; */
    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->m4[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
        rtDW->E_b[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 8] * rtDW->E_b[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] * rtDW->
                           E_b[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] *
                           rtDW->E_b[0]))) * 2.0F;
      rtDW->E_d[rtDW->d_j] = ((((rtDW->B_b[rtDW->d_j + 4] *
        rtDW->rtb_v_5_idx_pu_idx_1 + rtDW->B_b[rtDW->d_j] *
        rtDW->rtb_v_5_idx_pu_idx_0) + rtDW->B_b[rtDW->d_j + 8] *
        rtDW->rtb_v_5_idx_pu_idx_2) + rtDW->B_b[rtDW->d_j + 12] *
        rtDW->rtb_v_5_idx_pu_idx_3) + rtDW->E[rtDW->d_j]) + rtDW->D[rtDW->d_j];
    }

    for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
      rtDW->E[rtDW->d_j] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 12] *
                            rtDW->E_d[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j
        + 8] * rtDW->E_d[2] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->d_j + 4] *
        rtDW->E_d[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->d_j] * rtDW->E_d[0]))) *
        2.0F;
    }

    /* '<S10>:1:89' m6 = m0; */
    /*  m0 = C*(A*x0+B*u0+D);  */
    /*  m1 = C*(A*x0+B*u1+D); */
    /*  m2 = C*(A*x0+B*u2+D); */
    /*  m3 = C*(A*x0+B*u3+D); */
    /*  m4 = C*(A*x0+B*u4+D); */
    /*  m5 = C*(A*x0+B*u5+D); */
    /*  m6 = m0; */
    break;
  }

  /* MATLAB Function: '<S1>/formulate_qp' incorporates:
   *  Inport: '<Root>/i_d_ref_pu'
   *  Inport: '<Root>/i_q_ref_pu'
   *  Inport: '<Root>/i_x_ref_pu'
   *  Inport: '<Root>/i_y_ref_pu'
   *  Inport: '<Root>/lambda'
   *  MATLAB Function: '<S1>/state_space_mdl'
   */
  /* MATLAB Function 'uz_codegen/formulate_qp': '<S7>:1' */
  /* '<S7>:1:4' lam = [ lambda  0       0       0; */
  /* '<S7>:1:5'         0       lambda  0       0; */
  /* '<S7>:1:6'         0       0       lambda  0; */
  /* '<S7>:1:7'         0       0       0       lambda]; */
  rtDW->A_n[0] = rtU->lambda;
  rtDW->A_n[4] = 0.0F;
  rtDW->A_n[8] = 0.0F;
  rtDW->A_n[12] = 0.0F;
  rtDW->A_n[1] = 0.0F;
  rtDW->A_n[5] = rtU->lambda;
  rtDW->A_n[9] = 0.0F;
  rtDW->A_n[13] = 0.0F;
  rtDW->A_n[2] = 0.0F;
  rtDW->A_n[6] = 0.0F;
  rtDW->A_n[10] = rtU->lambda;
  rtDW->A_n[14] = 0.0F;
  rtDW->A_n[3] = 0.0F;
  rtDW->A_n[7] = 0.0F;
  rtDW->A_n[11] = 0.0F;
  rtDW->A_n[15] = rtU->lambda;

  /* '<S7>:1:9' i_ref = [id_ref iq_ref ix_ref iy_ref]'; */
  /* '<S7>:1:10' e_i = i_ref - i_delay; */
  rtDW->D[0] = rtU->i_d_ref_pu - rtDW->v_t0[0];
  rtDW->D[1] = rtU->i_q_ref_pu - rtDW->v_t0[1];
  rtDW->D[2] = rtU->i_x_ref_pu - rtDW->v_t0[2];
  rtDW->D[3] = rtU->i_y_ref_pu - rtDW->v_t0[3];

  /* '<S7>:1:12' r = [e_i; e_i; e_i; e_i; e_i; e_i; lam*e_i]; */
  /* '<S7>:1:14' zer = zeros(4,1); */
  /* '<S7>:1:15' m0_lam = lam*m0; */
  /* '<S7>:1:16' m1_lam = lam*m1; */
  /* '<S7>:1:17' m2_lam = lam*m2; */
  /* '<S7>:1:18' m3_lam = lam*m3; */
  /* '<S7>:1:19' m4_lam = lam*m4; */
  /* '<S7>:1:20' m5_lam = lam*m5; */
  /* '<S7>:1:21' m6_lam = m0_lam; */
  /* '<S7>:1:23' M = [m0     zer     zer     zer     zer     zer     zer; */
  /* '<S7>:1:24'      m0     m1      zer     zer     zer     zer     zer; */
  /* '<S7>:1:25'      m0     m1      m2      zer     zer     zer     zer; */
  /* '<S7>:1:26'      m0     m1      m2      m3      zer     zer     zer; */
  /* '<S7>:1:27'      m0     m1      m2      m3      m4      zer     zer; */
  /* '<S7>:1:28'      m0     m1      m2      m3      m4      m5      zer; */
  /* '<S7>:1:29'      m0_lam m1_lam  m2_lam  m3_lam  m4_lam  m5_lam  m6_lam]; */
  for (rtDW->d_j = 0; rtDW->d_j < 4; rtDW->d_j++) {
    rtDW->r[rtDW->d_j] = rtDW->D[rtDW->d_j];
    rtDW->r[rtDW->d_j + 4] = rtDW->D[rtDW->d_j];
    rtDW->r[rtDW->d_j + 8] = rtDW->D[rtDW->d_j];
    rtDW->r[rtDW->d_j + 12] = rtDW->D[rtDW->d_j];
    rtDW->r[rtDW->d_j + 16] = rtDW->D[rtDW->d_j];
    rtDW->r[rtDW->d_j + 20] = rtDW->D[rtDW->d_j];
    rtDW->x0_idx_2 = rtDW->A_n[rtDW->d_j + 4];
    rtDW->x0_idx_3 = rtDW->A_n[rtDW->d_j + 8];
    rtDW->A_tmp = rtDW->A_n[rtDW->d_j + 12];
    rtDW->r[rtDW->d_j + 24] = rtDW->A_tmp * rtDW->D[3] + (rtDW->x0_idx_3 *
      rtDW->D[2] + (rtDW->x0_idx_2 * rtDW->D[1] + rtDW->A_n[rtDW->d_j] * rtDW->
                    D[0]));
    rtDW->x0_idx_0 = rtDW->A_n[rtDW->d_j];
    rtDW->x0_idx_1 = rtDW->A_tmp * rtDW->m6[3] + (rtDW->x0_idx_3 * rtDW->m6[2] +
      (rtDW->x0_idx_2 * rtDW->m6[1] + rtDW->x0_idx_0 * rtDW->m6[0]));
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
    rtDW->M[rtDW->d_j + 160] = rtDW->E[rtDW->d_j];
    rtDW->M[rtDW->d_j + 188] = 0.0F;
    rtDW->M[rtDW->d_j + 24] = rtDW->x0_idx_1;
    rtDW->M[rtDW->d_j + 52] = rtDW->A_tmp * rtDW->m1[3] + (rtDW->x0_idx_3 *
      rtDW->m1[2] + (rtDW->x0_idx_2 * rtDW->m1[1] + rtDW->x0_idx_0 * rtDW->m1[0]));
    rtDW->M[rtDW->d_j + 80] = rtDW->A_tmp * rtDW->m2[3] + (rtDW->x0_idx_3 *
      rtDW->m2[2] + (rtDW->x0_idx_2 * rtDW->m2[1] + rtDW->x0_idx_0 * rtDW->m2[0]));
    rtDW->M[rtDW->d_j + 108] = rtDW->A_tmp * rtDW->m3[3] + (rtDW->x0_idx_3 *
      rtDW->m3[2] + (rtDW->x0_idx_2 * rtDW->m3[1] + rtDW->x0_idx_0 * rtDW->m3[0]));
    rtDW->M[rtDW->d_j + 136] = rtDW->A_tmp * rtDW->m4[3] + (rtDW->x0_idx_3 *
      rtDW->m4[2] + (rtDW->x0_idx_2 * rtDW->m4[1] + rtDW->x0_idx_0 * rtDW->m4[0]));
    rtDW->M[rtDW->d_j + 164] = rtDW->A_tmp * rtDW->E[3] + (rtDW->x0_idx_3 *
      rtDW->E[2] + (rtDW->x0_idx_2 * rtDW->E[1] + rtDW->x0_idx_0 * rtDW->E[0]));
    rtDW->M[rtDW->d_j + 192] = rtDW->x0_idx_1;
  }

  /* '<S7>:1:31' H = 2*(M'*M); */
  /* '<S7>:1:32' f = 2*M'*r; */
  /* MATLAB Function 'uz_codegen/qp_solver': '<S8>:1' */
  /* '<S8>:1:3' x_opt = single([0.5 0 0 0 0 0 0.5]'); */
  /* '<S8>:1:5' iter = single(0); */
  /*  contraints */
  /*             t1 t2 t3 t4 t5 t6 t7 */
  /* '<S8>:1:9' A = single([-1  0  0  0  0  0  0;   % t>=0 is converted to -1<=0 */
  /* '<S8>:1:10'              0 -1  0  0  0  0  0;   % no row=no of ineq constraints */
  /* '<S8>:1:11'              0  0 -1  0  0  0  0;   % no columns=no of optimization variables */
  /* '<S8>:1:12'              0  0  0 -1  0  0  0; */
  /* '<S8>:1:13'              0  0  0  0 -1  0  0; */
  /* '<S8>:1:14'              0  0  0  0  0 -1  0; */
  /* '<S8>:1:15'              0  0  0  0  0  0 -1]); */
  /*  t>=0 is converted to -1<=0 */
  /*  no row=no of ineq constraints */
  /*  no columns=no of optimization variables */
  /* '<S8>:1:17' b = single(zeros(7,1)); */
  /* '<S8>:1:19' Aeq = single([1 1 1 1 1 1 1]); */
  /* '<S8>:1:20' beq =  single([1]); */
  /*  sum of all duration times  */
  /*  define cold start for active-set solver */
  /* '<S8>:1:23' iA0 = false(size(b)); */
  /*  [x_opt,iter] = mpc_solve(H,f,A,b,Aeq,beq,iA0,max_iter,tol); */
  /* '<S8>:1:26' [x_opt,iter] = mpc_quadprog(H,f,A,b,Aeq,beq,max_iter,tol,x0); */
  /*  set up quadprog solver */
  /* '<S8>:1:59' quadprog_options = optimoptions('quadprog','Algorithm','active-set','OptimalityTolerance',1e-6,'MaxIterations',20); */
  /*  make variables double */
  /* '<S8>:1:62' H_d = double(H); */
  /* '<S8>:1:63' f_d = double(f); */
  /* '<S8>:1:64' A_d = double(A); */
  /* '<S8>:1:65' b_d = double(b); */
  /* '<S8>:1:66' Aeq_d = double(Aeq); */
  /* '<S8>:1:67' beq_d = double(beq); */
  /* '<S8>:1:68' x0_d = double(x0); */
  /* '<S8>:1:70' [x_tmp, fval, exitflag, output] = quadprog(H_d,-f_d,A_d,b_d,Aeq_d,beq_d,[],[],x0_d,quadprog_options); */
  for (rtDW->i = 0; rtDW->i < 7; rtDW->i++) {
    /* Delay: '<S1>/Delay2' */
    if (rtDW->icLoad_p) {
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
    rtDW->rtb_SinCos2_o1_tmp = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 28; rtDW->iy++) {
      rtDW->rtb_SinCos2_o1_tmp += rtDW->M[28 * rtDW->d_j + rtDW->iy] * 2.0F *
        rtDW->r[rtDW->iy];
    }

    rtDW->dv1[rtDW->d_j] = -(real_T)rtDW->rtb_SinCos2_o1_tmp;
    rtDW->dv2[rtDW->d_j] = rtDW->Delay2_DSTATE[rtDW->d_j];
  }

  quadprog(rtDW->dv, rtDW->dv1, rtDW->dv2, rtDW->x_tmp, &rtDW->fval,
           &rtDW->exitflag, rtDW->expl_temp_f, &rtDW->expl_temp_c,
           &rtDW->expl_temp_b, &rtDW->output_iterations, rtDW);

  /* '<S8>:1:72' x = single(x_tmp(1:7,1)); */
  /* '<S8>:1:73' iter = single(output.iterations); */
  for (rtDW->i = 0; rtDW->i < 7; rtDW->i++) {
    rtDW->x_opt[rtDW->i] = (real32_T)rtDW->x_tmp[rtDW->i];
  }

  /* MATLAB Function 'uz_codegen/tz': '<S11>:1' */
  /* '<S11>:1:3' I = single([1 0 0 0 0 0; */
  /* '<S11>:1:4'             1 1 0 0 0 0; */
  /* '<S11>:1:5'             1 1 1 0 0 0; */
  /* '<S11>:1:6'             1 1 1 1 0 0; */
  /* '<S11>:1:7'             1 1 1 1 1 0; */
  /* '<S11>:1:8'             1 1 1 1 1 1]); */
  /* '<S11>:1:10' zer6 = single(zeros(6,1)); */
  /* '<S11>:1:12' T = single([I zer6]); */
  /* '<S11>:1:14' tz=single(T*x); */
  /* MATLAB Function 'uz_codegen/tz_2_tph': '<S12>:1' */
  /* '<S12>:1:3' seq_order_table = single([4,1,6,2,3,5; */
  /* '<S12>:1:4'     1,4,2,6,5,3; */
  /* '<S12>:1:5'     1,4,2,5,6,3; */
  /* '<S12>:1:6'     4,1,2,5,3,6; */
  /* '<S12>:1:7'     4,2,1,5,3,6; */
  /* '<S12>:1:8'     2,4,5,1,6,3; */
  /* '<S12>:1:9'     2,5,4,1,6,3; */
  /* '<S12>:1:10'     5,2,4,1,3,6; */
  /* '<S12>:1:11'     5,2,4,3,1,6; */
  /* '<S12>:1:12'     2,5,3,4,6,1; */
  /* '<S12>:1:13'     2,5,3,6,4,1; */
  /* '<S12>:1:14'     5,2,3,6,1,4; */
  /* '<S12>:1:15'     5,3,2,6,1,4; */
  /* '<S12>:1:16'     3,5,6,2,4,1; */
  /* '<S12>:1:17'     3,6,5,2,4,1; */
  /* '<S12>:1:18'     6,3,5,2,1,4; */
  /* '<S12>:1:19'     6,3,5,1,2,4; */
  /* '<S12>:1:20'     3,6,1,5,4,2; */
  /* '<S12>:1:21'     3,6,1,4,5,2; */
  /* '<S12>:1:22'     6,3,1,4,2,5; */
  /* '<S12>:1:23'     6,1,3,4,2,5; */
  /* '<S12>:1:24'     1,6,4,3,5,2; */
  /* '<S12>:1:25'     1,4,6,3,5,2; */
  /* '<S12>:1:26'     4,1,6,3,2,5]); */
  /* '<S12>:1:28' t = single(zeros(6,1)); */
  for (rtDW->i = 0; rtDW->i < 6; rtDW->i++) {
    /* MATLAB Function: '<S1>/tz' */
    rtDW->tz[rtDW->i] = 0.0F;
    for (rtDW->d_j = 0; rtDW->d_j < 7; rtDW->d_j++) {
      rtDW->tz[rtDW->i] += (real32_T)a[6 * rtDW->d_j + rtDW->i] * rtDW->
        x_opt[rtDW->d_j];
    }

    /* End of MATLAB Function: '<S1>/tz' */

    /* MATLAB Function: '<S1>/tz_2_tph' */
    rtDW->t_h[rtDW->i] = 0.0F;
  }

  /* MATLAB Function: '<S1>/tz_2_tph' */
  /* '<S12>:1:30' for i=1:6 */
  for (rtDW->iy = 0; rtDW->iy < 6; rtDW->iy++) {
    /* '<S12>:1:31' t(seq_order_table(seq_no,i),1) = tz(i); */
    rtDW->t_h[seq_order_table[(rtDW->sector_ref + 24 * rtDW->iy) - 1] - 1] =
      rtDW->tz[rtDW->iy];
  }

  /* Outport: '<Root>/d_opt' incorporates:
   *  MATLAB Function: '<S1>/tz_2_tph'
   */
  /* '<S12>:1:34' ta_1 = t(1); */
  /* '<S12>:1:35' tb_1 = t(2); */
  /* '<S12>:1:36' tc_1 = t(3); */
  /* '<S12>:1:37' ta_2 = t(4); */
  /* '<S12>:1:38' tb_2 = t(5); */
  /* '<S12>:1:39' tc_2 = t(6); */
  rtY->d_opt[0] = rtDW->t_h[0];
  rtY->d_opt[1] = rtDW->t_h[1];
  rtY->d_opt[2] = rtDW->t_h[2];
  rtY->d_opt[3] = rtDW->t_h[3];
  rtY->d_opt[4] = rtDW->t_h[4];
  rtY->d_opt[5] = rtDW->t_h[5];

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
  rtDW->icLoad_e = false;

  /* Update for Delay: '<S1>/Delay3' */
  rtDW->icLoad_b = false;

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->icLoad_h = false;

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->icLoad_c = false;

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->icLoad_bb = false;

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->icLoad_o = false;

  /* Update for Delay: '<S1>/Delay8' */
  rtDW->icLoad_d = false;

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/state_space_mdl'
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
  rtDW->Delay8_DSTATE[0] = rtDW->E[0];

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/state_space_mdl'
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
  rtDW->Delay8_DSTATE[1] = rtDW->E[1];

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/state_space_mdl'
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
  rtDW->Delay8_DSTATE[2] = rtDW->E[2];

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/state_space_mdl'
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
  rtDW->Delay8_DSTATE[3] = rtDW->E[3];

  /* Update for Delay: '<S1>/Delay2' */
  rtDW->icLoad_p = false;
  for (rtDW->i = 0; rtDW->i < 7; rtDW->i++) {
    /* Update for Delay: '<S1>/Delay13' */
    rtDW->x0_idx_0 = rtDW->x_opt[rtDW->i];
    rtDW->Delay13_DSTATE[rtDW->i] = rtDW->x0_idx_0;

    /* Update for Delay: '<S1>/Delay1' */
    rtDW->Delay1_DSTATE[rtDW->i] = rtDW->x0_idx_0;

    /* Update for Delay: '<S1>/Delay2' */
    rtDW->Delay2_DSTATE[rtDW->i] = rtDW->x0_idx_0;
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
    static const real_T b[8] = { 0.1, 0.1, 0.1, 0.1, 100.0, 100.0, 100.0, 100.0
    };

    /* InitializeConditions for Delay: '<S1>/Delay13' */
    rtDW->icLoad = true;

    /* InitializeConditions for Delay: '<S1>/Delay1' */
    rtDW->icLoad_e = true;

    /* InitializeConditions for Delay: '<S1>/Delay3' */
    rtDW->icLoad_b = true;

    /* InitializeConditions for Delay: '<S1>/Delay4' */
    rtDW->icLoad_h = true;

    /* InitializeConditions for Delay: '<S1>/Delay5' */
    rtDW->icLoad_c = true;

    /* InitializeConditions for Delay: '<S1>/Delay6' */
    rtDW->icLoad_bb = true;

    /* InitializeConditions for Delay: '<S1>/Delay7' */
    rtDW->icLoad_o = true;

    /* InitializeConditions for Delay: '<S1>/Delay8' */
    rtDW->icLoad_d = true;

    /* InitializeConditions for Delay: '<S1>/Delay2' */
    rtDW->icLoad_p = true;

    /* SystemInitialize for MATLAB Function: '<S1>/Observer' */
    /* '<S3>:1:61' x_e = single([0;0;0;0;0;0;0;0]); */
    for (i = 0; i < 8; i++) {
      rtDW->x_e[i] = 0.0F;
    }

    /* '<S3>:1:62' P_e = single(diag([0.1 0.1 0.1 0.1 100 100 100 100])); */
    memset(&rtDW->d[0], 0, sizeof(real_T) << 6U);
    for (i = 0; i < 8; i++) {
      rtDW->d[i + (i << 3)] = b[i];
    }

    for (i = 0; i < 64; i++) {
      rtDW->P_e[i] = (real32_T)rtDW->d[i];
    }

    /* End of SystemInitialize for MATLAB Function: '<S1>/Observer' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
