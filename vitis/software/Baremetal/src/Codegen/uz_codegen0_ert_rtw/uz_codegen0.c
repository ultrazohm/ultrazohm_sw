/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.7
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Jul 29 14:01:24 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "uz_codegen0.h"

extern real32_T rt_hypotf(real32_T u0, real32_T u1);

/* Forward declaration for local functions */
static void trisolve(const real32_T A_data[], const int32_T A_size[2], real32_T
                     B_data[], const int32_T B_size[2]);
static void Unconstrained(const real32_T Hinv_data[], const int32_T Hinv_size[2],
  const real32_T f[7], real32_T x_data[], int16_T n);
static real32_T norm(const real32_T x_data[], const int32_T *x_size);
static void abs_d(const real32_T x[7], real32_T y[7]);
static real32_T maximum(const real32_T x[7]);
static void maximum2(const real32_T x[8], real32_T ex[8]);
static real32_T xnrm2(int32_T n, const real32_T x_data[], int32_T ix0);
static void xgemv(int32_T m, int32_T n, const real32_T A_data[], int32_T ia0,
                  int32_T lda, const real32_T x_data[], int32_T ix0, real32_T
                  y_data[]);
static void xgerc(int32_T m, int32_T n, real32_T alpha1, int32_T ix0, const
                  real32_T y_data[], real32_T A_data[], int32_T ia0, int32_T lda);
static void xgeqrf(real32_T A_data[], const int32_T A_size[2], real32_T
                   tau_data[], int32_T *tau_size, DW *rtDW);
static void xorgqr(int32_T m, int32_T n, int32_T k, real32_T A_data[], const
                   int32_T A_size[2], int32_T lda, const real32_T tau_data[], DW
                   *rtDW);
static void mtimes(const real32_T A_data[], const int32_T A_size[2], const
                   real32_T B_0[7], real32_T C_data[], int32_T *C_size);
static real32_T KWIKfactor(const int16_T iC[8], int16_T nA, const real32_T
  Linv_data[], const int32_T Linv_size[2], real32_T RLinv_data[], const int32_T
  RLinv_size[2], real32_T D_data[], const int32_T D_size[2], real32_T H_data[],
  const int32_T H_size[2], int16_T n, DW *rtDW);
static real32_T mtimes_k(const real32_T A_data[], const real32_T B_1[7]);
static void DropConstraint(int16_T kDrop, int16_T iA[8], int16_T *nA, int16_T
  iC[8]);
static void ResetToColdStart(int16_T iA[8], int16_T iC[8]);
static void qpkwik(const real32_T Linv_data[], const int32_T Linv_size[2], const
                   real32_T Hinv_data[], const int32_T Hinv_size[2], const
                   real32_T f[7], int16_T maxiter, int16_T n, real32_T x_data[],
                   int32_T *x_size, real32_T lambda[8], real32_T *status,
                   int16_T iA[8], DW *rtDW);

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void trisolve(const real32_T A_data[], const int32_T A_size[2], real32_T
                     B_data[], const int32_T B_size[2])
{
  int32_T i;
  int32_T j;
  int32_T jBcol;
  int32_T k;
  int32_T kAcol;
  int32_T mB;
  int32_T n;
  int32_T nB;
  int32_T tmp;
  int32_T tmp_0;
  mB = B_size[0];
  nB = B_size[1] - 1;
  if (A_size[0] < A_size[1]) {
    n = A_size[0];
  } else {
    n = A_size[1];
  }

  if (n >= B_size[0]) {
    n = B_size[0];
  }

  if ((B_size[1] != 0) && ((B_size[0] != 0) && (B_size[1] != 0))) {
    for (j = 0; j <= nB; j++) {
      jBcol = mB * j - 1;
      for (k = 1; k - 1 < n; k++) {
        kAcol = (k - 1) * A_size[0] - 1;
        tmp = k + jBcol;
        if (B_data[tmp] != 0.0F) {
          B_data[tmp] /= A_data[k + kAcol];
          for (i = k + 1; i <= n; i++) {
            tmp_0 = i + jBcol;
            B_data[tmp_0] -= B_data[tmp] * A_data[i + kAcol];
          }
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void Unconstrained(const real32_T Hinv_data[], const int32_T Hinv_size[2],
  const real32_T f[7], real32_T x_data[], int16_T n)
{
  int32_T i;
  int32_T i_0;
  real32_T Hinv;
  for (i = 1; i - 1 < n; i++) {
    Hinv = 0.0F;
    for (i_0 = 0; i_0 < 7; i_0++) {
      Hinv += -Hinv_data[((int16_T)i + Hinv_size[0] * i_0) - 1] * f[i_0];
    }

    x_data[(int16_T)i - 1] = Hinv;
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real32_T norm(const real32_T x_data[], const int32_T *x_size)
{
  int32_T k;
  real32_T absxk;
  real32_T scale;
  real32_T t;
  real32_T y;
  if (*x_size == 0) {
    y = 0.0F;
  } else {
    y = 0.0F;
    if (*x_size == 1) {
      y = fabsf(x_data[0]);
    } else {
      scale = 1.29246971E-26F;
      for (k = 0; k < *x_size; k++) {
        absxk = fabsf(x_data[k]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrtf(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void abs_d(const real32_T x[7], real32_T y[7])
{
  int32_T k;
  for (k = 0; k < 7; k++) {
    y[k] = fabsf(x[k]);
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real32_T maximum(const real32_T x[7])
{
  int32_T k;
  real32_T ex;
  real32_T tmp;
  ex = x[0];
  for (k = 0; k < 6; k++) {
    tmp = x[k + 1];
    if (ex < tmp) {
      ex = tmp;
    }
  }

  return ex;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void maximum2(const real32_T x[8], real32_T ex[8])
{
  int32_T k;
  for (k = 0; k < 8; k++) {
    ex[k] = fmaxf(x[k], 1.0F);
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real32_T xnrm2(int32_T n, const real32_T x_data[], int32_T ix0)
{
  int32_T k;
  int32_T kend;
  real32_T absxk;
  real32_T scale;
  real32_T t;
  real32_T y;
  y = 0.0F;
  if (n >= 1) {
    if (n == 1) {
      y = fabsf(x_data[ix0 - 1]);
    } else {
      scale = 1.29246971E-26F;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabsf(x_data[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrtf(y);
    }
  }

  return y;
}

real32_T rt_hypotf(real32_T u0, real32_T u1)
{
  real32_T a;
  real32_T b;
  real32_T y;
  a = fabsf(u0);
  b = fabsf(u1);
  if (a < b) {
    a /= b;
    y = sqrtf(a * a + 1.0F) * b;
  } else if (a > b) {
    b /= a;
    y = sqrtf(b * b + 1.0F) * a;
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgemv(int32_T m, int32_T n, const real32_T A_data[], int32_T ia0,
                  int32_T lda, const real32_T x_data[], int32_T ix0, real32_T
                  y_data[])
{
  int32_T b;
  int32_T b_iy;
  int32_T d;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  real32_T c;
  if (n != 0) {
    for (b_iy = 0; b_iy < n; b_iy++) {
      y_data[b_iy] = 0.0F;
    }

    b_iy = 0;
    b = (n - 1) * lda + ia0;
    iac = ia0;
    while (((lda > 0) && (iac <= b)) || ((lda < 0) && (iac >= b))) {
      ix = ix0;
      c = 0.0F;
      d = (iac + m) - 1;
      for (ia = iac; ia <= d; ia++) {
        c += A_data[ia - 1] * x_data[ix - 1];
        ix++;
      }

      y_data[b_iy] += c;
      b_iy++;
      iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgerc(int32_T m, int32_T n, real32_T alpha1, int32_T ix0, const
                  real32_T y_data[], real32_T A_data[], int32_T ia0, int32_T lda)
{
  int32_T b;
  int32_T ijA;
  int32_T ix;
  int32_T j;
  int32_T jA;
  int32_T jy;
  real32_T temp;
  if (alpha1 != 0.0F) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 0; j < n; j++) {
      if (y_data[jy] != 0.0F) {
        temp = y_data[jy] * alpha1;
        ix = ix0;
        b = m + jA;
        for (ijA = jA; ijA < b; ijA++) {
          A_data[ijA] += A_data[ix - 1] * temp;
          ix++;
        }
      }

      jy++;
      jA += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xgeqrf(real32_T A_data[], const int32_T A_size[2], real32_T
                   tau_data[], int32_T *tau_size, DW *rtDW)
{
  int32_T b_k;
  int32_T c_k;
  int32_T exitg1;
  int32_T knt;
  real32_T beta1;
  boolean_T exitg2;
  rtDW->m_n = A_size[0];
  rtDW->n = A_size[1];
  if (A_size[0] < A_size[1]) {
    rtDW->minmana = A_size[0];
  } else {
    rtDW->minmana = A_size[1];
  }

  if (A_size[0] < A_size[1]) {
    rtDW->minmn = A_size[0];
  } else {
    rtDW->minmn = A_size[1];
  }

  *tau_size = rtDW->minmana;
  if (0 <= rtDW->minmana - 1) {
    memset(&tau_data[0], 0, rtDW->minmana * sizeof(real32_T));
  }

  if ((A_size[0] != 0) && (A_size[1] != 0) && (rtDW->minmn >= 1)) {
    *tau_size = rtDW->minmana;
    if (0 <= rtDW->minmana - 1) {
      memset(&tau_data[0], 0, rtDW->minmana * sizeof(real32_T));
    }

    rtDW->minmana = A_size[0];
    rtDW->ii = A_size[1];
    if (0 <= rtDW->ii - 1) {
      memset(&rtDW->work_data[0], 0, rtDW->ii * sizeof(real32_T));
    }

    rtDW->i_p = 0;
    while (rtDW->i_p <= rtDW->minmn - 1) {
      rtDW->ii = rtDW->i_p * rtDW->minmana + rtDW->i_p;
      rtDW->mmi = rtDW->m_n - rtDW->i_p;
      if (rtDW->i_p + 1 < rtDW->m_n) {
        rtDW->b_atmp = A_data[rtDW->ii];
        tau_data[rtDW->i_p] = 0.0F;
        if (rtDW->mmi > 0) {
          beta1 = xnrm2(rtDW->mmi - 1, A_data, rtDW->ii + 2);
          if (beta1 != 0.0F) {
            beta1 = rt_hypotf(A_data[rtDW->ii], beta1);
            if (A_data[rtDW->ii] >= 0.0F) {
              beta1 = -beta1;
            }

            if (fabsf(beta1) < 9.86076132E-32F) {
              knt = -1;
              b_k = rtDW->ii + rtDW->mmi;
              do {
                knt++;
                for (c_k = rtDW->ii + 1; c_k < b_k; c_k++) {
                  A_data[c_k] *= 1.01412048E+31F;
                }

                beta1 *= 1.01412048E+31F;
                rtDW->b_atmp *= 1.01412048E+31F;
              } while (fabsf(beta1) < 9.86076132E-32F);

              beta1 = rt_hypotf(rtDW->b_atmp, xnrm2(rtDW->mmi - 1, A_data,
                rtDW->ii + 2));
              if (rtDW->b_atmp >= 0.0F) {
                beta1 = -beta1;
              }

              tau_data[rtDW->i_p] = (beta1 - rtDW->b_atmp) / beta1;
              rtDW->b_atmp = 1.0F / (rtDW->b_atmp - beta1);
              b_k = rtDW->ii + rtDW->mmi;
              for (c_k = rtDW->ii + 1; c_k < b_k; c_k++) {
                A_data[c_k] *= rtDW->b_atmp;
              }

              for (c_k = 0; c_k <= knt; c_k++) {
                beta1 *= 9.86076132E-32F;
              }

              rtDW->b_atmp = beta1;
            } else {
              tau_data[rtDW->i_p] = (beta1 - A_data[rtDW->ii]) / beta1;
              rtDW->b_atmp = 1.0F / (A_data[rtDW->ii] - beta1);
              knt = rtDW->ii + rtDW->mmi;
              for (b_k = rtDW->ii + 1; b_k < knt; b_k++) {
                A_data[b_k] *= rtDW->b_atmp;
              }

              rtDW->b_atmp = beta1;
            }
          }
        }

        A_data[rtDW->ii] = rtDW->b_atmp;
      } else {
        tau_data[rtDW->i_p] = 0.0F;
      }

      if (rtDW->i_p + 1 < rtDW->n) {
        rtDW->b_atmp = A_data[rtDW->ii];
        A_data[rtDW->ii] = 1.0F;
        c_k = (rtDW->ii + rtDW->minmana) + 1;
        if (tau_data[rtDW->i_p] != 0.0F) {
          rtDW->mmip1 = (rtDW->ii + rtDW->mmi) - 1;
          while ((rtDW->mmi > 0) && (A_data[rtDW->mmip1] == 0.0F)) {
            rtDW->mmi--;
            rtDW->mmip1--;
          }

          rtDW->mmip1 = (rtDW->n - rtDW->i_p) - 1;
          exitg2 = false;
          while ((!exitg2) && (rtDW->mmip1 > 0)) {
            knt = (rtDW->mmip1 - 1) * rtDW->minmana + c_k;
            b_k = knt;
            do {
              exitg1 = 0;
              if (b_k <= (knt + rtDW->mmi) - 1) {
                if (A_data[b_k - 1] != 0.0F) {
                  exitg1 = 1;
                } else {
                  b_k++;
                }
              } else {
                rtDW->mmip1--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          rtDW->mmi = 0;
          rtDW->mmip1 = 0;
        }

        if (rtDW->mmi > 0) {
          xgemv(rtDW->mmi, rtDW->mmip1, A_data, c_k, rtDW->minmana, A_data,
                rtDW->ii + 1, rtDW->work_data);
          xgerc(rtDW->mmi, rtDW->mmip1, -tau_data[rtDW->i_p], rtDW->ii + 1,
                rtDW->work_data, A_data, c_k, rtDW->minmana);
        }

        A_data[rtDW->ii] = rtDW->b_atmp;
      }

      rtDW->i_p++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void xorgqr(int32_T m, int32_T n, int32_T k, real32_T A_data[], const
                   int32_T A_size[2], int32_T lda, const real32_T tau_data[], DW
                   *rtDW)
{
  int32_T coltop;
  int32_T exitg1;
  int32_T ia;
  int32_T lastc;
  int32_T lastv;
  boolean_T exitg2;
  if (n >= 1) {
    rtDW->itau = k;
    while (rtDW->itau <= n - 1) {
      rtDW->i_l = rtDW->itau * lda;
      rtDW->iaii = 0;
      while (rtDW->iaii <= m - 1) {
        A_data[rtDW->i_l + rtDW->iaii] = 0.0F;
        rtDW->iaii++;
      }

      A_data[rtDW->i_l + rtDW->itau] = 1.0F;
      rtDW->itau++;
    }

    rtDW->itau = k - 1;
    rtDW->iaii = (int8_T)A_size[1];
    if (0 <= rtDW->iaii - 1) {
      memset(&rtDW->work_data_f[0], 0, rtDW->iaii * sizeof(real32_T));
    }

    rtDW->i_l = k;
    while (rtDW->i_l >= 1) {
      rtDW->iaii = (rtDW->i_l - 1) * lda + rtDW->i_l;
      if (rtDW->i_l < n) {
        A_data[rtDW->iaii - 1] = 1.0F;
        lastc = (m - rtDW->i_l) - 1;
        rtDW->c_c = rtDW->iaii + lda;
        if (tau_data[rtDW->itau] != 0.0F) {
          lastv = lastc + 2;
          lastc += rtDW->iaii;
          while ((lastv > 0) && (A_data[lastc] == 0.0F)) {
            lastv--;
            lastc--;
          }

          lastc = n - rtDW->i_l;
          exitg2 = false;
          while ((!exitg2) && (lastc > 0)) {
            coltop = (lastc - 1) * lda + rtDW->c_c;
            ia = coltop;
            do {
              exitg1 = 0;
              if (ia <= (coltop + lastv) - 1) {
                if (A_data[ia - 1] != 0.0F) {
                  exitg1 = 1;
                } else {
                  ia++;
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
          lastc = 0;
        }

        if (lastv > 0) {
          xgemv(lastv, lastc, A_data, rtDW->c_c, lda, A_data, rtDW->iaii,
                rtDW->work_data_f);
          xgerc(lastv, lastc, -tau_data[rtDW->itau], rtDW->iaii,
                rtDW->work_data_f, A_data, rtDW->c_c, lda);
        }
      }

      if (rtDW->i_l < m) {
        rtDW->c_c = (rtDW->iaii + m) - rtDW->i_l;
        for (lastv = rtDW->iaii; lastv < rtDW->c_c; lastv++) {
          A_data[lastv] *= -tau_data[rtDW->itau];
        }
      }

      A_data[rtDW->iaii - 1] = 1.0F - tau_data[rtDW->itau];
      rtDW->c_c = 0;
      while (rtDW->c_c <= rtDW->i_l - 2) {
        A_data[(rtDW->iaii - rtDW->c_c) - 2] = 0.0F;
        rtDW->c_c++;
      }

      rtDW->itau--;
      rtDW->i_l--;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void mtimes(const real32_T A_data[], const int32_T A_size[2], const
                   real32_T B_0[7], real32_T C_data[], int32_T *C_size)
{
  int32_T aoffset;
  int32_T b_i;
  int32_T i;
  int32_T m;
  m = A_size[0] - 1;
  *C_size = A_size[0];
  for (i = 0; i <= m; i++) {
    C_data[i] = 0.0F;
  }

  for (i = 0; i < A_size[1]; i++) {
    aoffset = i * A_size[0];
    for (b_i = 0; b_i <= m; b_i++) {
      C_data[b_i] += A_data[aoffset + b_i] * B_0[i];
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real32_T KWIKfactor(const int16_T iC[8], int16_T nA, const real32_T
  Linv_data[], const int32_T Linv_size[2], real32_T RLinv_data[], const int32_T
  RLinv_size[2], real32_T D_data[], const int32_T D_size[2], real32_T H_data[],
  const int32_T H_size[2], int16_T n, DW *rtDW)
{
  real32_T Status;
  int16_T b_j;
  int16_T c_k;
  static const int8_T Ac[56] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
    0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1 };

  int32_T exitg1;
  rtDW->TL_size_idx_0 = Linv_size[0];
  Status = 1.0F;
  rtDW->b_n = RLinv_size[0];
  rtDW->RLinv = RLinv_size[1];
  for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
    for (rtDW->m = 0; rtDW->m < rtDW->b_n; rtDW->m++) {
      RLinv_data[rtDW->m + RLinv_size[0] * rtDW->h_j] = 0.0F;
    }
  }

  rtDW->m = 1;
  while (rtDW->m - 1 <= nA - 1) {
    rtDW->b_n = iC[(int16_T)rtDW->m - 1];
    for (rtDW->h_j = 0; rtDW->h_j < 7; rtDW->h_j++) {
      rtDW->Ac[rtDW->h_j] = Ac[((rtDW->h_j << 3) + rtDW->b_n) - 1];
    }

    mtimes(Linv_data, Linv_size, rtDW->Ac, rtDW->tau_data, &rtDW->tau_size);
    rtDW->RLinv = rtDW->tau_size;
    for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
      RLinv_data[rtDW->h_j + RLinv_size[0] * ((int16_T)rtDW->m - 1)] =
        rtDW->tau_data[rtDW->h_j];
    }

    rtDW->m++;
  }

  rtDW->m = RLinv_size[0] - 1;
  rtDW->b_n = RLinv_size[1];
  rtDW->Q_size[0] = (int8_T)RLinv_size[0];
  rtDW->Q_size[1] = (int8_T)RLinv_size[0];
  rtDW->R_size_idx_0 = RLinv_size[0];
  if (RLinv_size[0] > RLinv_size[1]) {
    rtDW->h_j = 0;
    while (rtDW->h_j <= rtDW->b_n - 1) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->m) {
        rtDW->Q_data[rtDW->RLinv + rtDW->Q_size[0] * rtDW->h_j] =
          RLinv_data[rtDW->RLinv + RLinv_size[0] * rtDW->h_j];
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    rtDW->h_j = RLinv_size[1];
    while (rtDW->h_j + 1 <= rtDW->m + 1) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->m) {
        rtDW->Q_data[rtDW->RLinv + rtDW->Q_size[0] * rtDW->h_j] = 0.0F;
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    xgeqrf(rtDW->Q_data, rtDW->Q_size, rtDW->tau_data, &rtDW->tau_size, rtDW);
    rtDW->h_j = 0;
    while (rtDW->h_j <= rtDW->b_n - 1) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->h_j) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] =
          rtDW->Q_data[rtDW->RLinv + rtDW->Q_size[0] * rtDW->h_j];
        rtDW->RLinv++;
      }

      rtDW->RLinv = rtDW->h_j + 1;
      while (rtDW->RLinv + 1 <= rtDW->m + 1) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] = 0.0F;
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    xorgqr(RLinv_size[0], RLinv_size[0], RLinv_size[1], rtDW->Q_data,
           rtDW->Q_size, RLinv_size[0], rtDW->tau_data, rtDW);
  } else {
    rtDW->A_size[0] = RLinv_size[0];
    rtDW->A_size[1] = RLinv_size[1];
    rtDW->RLinv = RLinv_size[0] * RLinv_size[1];
    if (0 <= rtDW->RLinv - 1) {
      memcpy(&rtDW->A_data[0], &RLinv_data[0], rtDW->RLinv * sizeof(real32_T));
    }

    xgeqrf(rtDW->A_data, rtDW->A_size, rtDW->tau_data, &rtDW->tau_size, rtDW);
    rtDW->h_j = 0;
    while (rtDW->h_j <= rtDW->m) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->h_j) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] =
          rtDW->A_data[rtDW->RLinv + rtDW->A_size[0] * rtDW->h_j];
        rtDW->RLinv++;
      }

      rtDW->RLinv = rtDW->h_j + 1;
      while (rtDW->RLinv + 1 <= rtDW->m + 1) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] = 0.0F;
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    rtDW->h_j = RLinv_size[0];
    while (rtDW->h_j + 1 <= rtDW->b_n) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->m) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] =
          rtDW->A_data[rtDW->RLinv + rtDW->A_size[0] * rtDW->h_j];
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    xorgqr(RLinv_size[0], RLinv_size[0], RLinv_size[0], rtDW->A_data,
           rtDW->A_size, RLinv_size[0], rtDW->tau_data, rtDW);
    rtDW->b_n = 0;
    while (rtDW->b_n <= rtDW->m) {
      rtDW->h_j = 0;
      while (rtDW->h_j <= rtDW->m) {
        rtDW->Q_data[rtDW->h_j + rtDW->Q_size[0] * rtDW->b_n] = rtDW->
          A_data[rtDW->h_j + rtDW->A_size[0] * rtDW->b_n];
        rtDW->h_j++;
      }

      rtDW->b_n++;
    }
  }

  rtDW->m = 1;
  do {
    exitg1 = 0;
    if (rtDW->m - 1 <= nA - 1) {
      if (fabsf(rtDW->R_data[((int16_T)rtDW->m + rtDW->R_size_idx_0 * ((int16_T)
             rtDW->m - 1)) - 1]) < 1.0E-12F) {
        Status = -2.0F;
        exitg1 = 1;
      } else {
        rtDW->m++;
      }
    } else {
      rtDW->m = 1;
      while (rtDW->m - 1 <= n - 1) {
        rtDW->b_n = 1;
        while (rtDW->b_n - 1 <= n - 1) {
          rtDW->RLinv = Linv_size[0];
          rtDW->Linv = 0.0F;
          for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
            rtDW->Linv += Linv_data[rtDW->h_j + Linv_size[0] * ((int16_T)rtDW->m
              - 1)] * rtDW->Q_data[rtDW->h_j + rtDW->Q_size[0] * ((int16_T)
              rtDW->b_n - 1)];
          }

          rtDW->TL_data[((int16_T)rtDW->m + rtDW->TL_size_idx_0 * ((int16_T)
            rtDW->b_n - 1)) - 1] = rtDW->Linv;
          rtDW->b_n++;
        }

        rtDW->m++;
      }

      rtDW->b_n = RLinv_size[0];
      rtDW->RLinv = RLinv_size[1];
      for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
        for (rtDW->m = 0; rtDW->m < rtDW->b_n; rtDW->m++) {
          RLinv_data[rtDW->m + RLinv_size[0] * rtDW->h_j] = 0.0F;
        }
      }

      for (b_j = nA; b_j > 0; b_j--) {
        RLinv_data[(b_j + RLinv_size[0] * (b_j - 1)) - 1] = 1.0F;
        for (c_k = b_j; c_k <= nA; c_k++) {
          rtDW->RLinv = (b_j + RLinv_size[0] * (c_k - 1)) - 1;
          RLinv_data[rtDW->RLinv] /= rtDW->R_data[(b_j + rtDW->R_size_idx_0 *
            (b_j - 1)) - 1];
        }

        if (b_j > 1) {
          rtDW->m = 1;
          while (rtDW->m - 1 <= b_j - 2) {
            for (c_k = b_j; c_k <= nA; c_k++) {
              rtDW->RLinv = RLinv_size[0] * (c_k - 1);
              rtDW->h_j = ((int16_T)rtDW->m + rtDW->RLinv) - 1;
              RLinv_data[rtDW->h_j] -= rtDW->R_data[((int16_T)rtDW->m +
                rtDW->R_size_idx_0 * (b_j - 1)) - 1] * RLinv_data[(b_j +
                rtDW->RLinv) - 1];
            }

            rtDW->m++;
          }
        }
      }

      rtDW->m = 1;
      while (rtDW->m - 1 <= n - 1) {
        for (b_j = (int16_T)rtDW->m; b_j <= n; b_j++) {
          rtDW->RLinv = ((int16_T)rtDW->m + H_size[0] * (b_j - 1)) - 1;
          H_data[rtDW->RLinv] = 0.0F;
          rtDW->h_j = nA + 1;
          if (nA + 1 > 32767) {
            rtDW->h_j = 32767;
          }

          for (c_k = (int16_T)rtDW->h_j; c_k <= n; c_k++) {
            rtDW->h_j = rtDW->TL_size_idx_0 * (c_k - 1);
            H_data[rtDW->RLinv] -= rtDW->TL_data[((int16_T)rtDW->m + rtDW->h_j)
              - 1] * rtDW->TL_data[(b_j + rtDW->h_j) - 1];
          }

          H_data[(b_j + H_size[0] * ((int16_T)rtDW->m - 1)) - 1] = H_data
            [rtDW->RLinv];
        }

        rtDW->m++;
      }

      rtDW->m = 1;
      while (rtDW->m - 1 <= nA - 1) {
        rtDW->b_n = 1;
        while (rtDW->b_n - 1 <= n - 1) {
          rtDW->RLinv = ((int16_T)rtDW->b_n + D_size[0] * ((int16_T)rtDW->m - 1))
            - 1;
          D_data[rtDW->RLinv] = 0.0F;
          for (b_j = (int16_T)rtDW->m; b_j <= nA; b_j++) {
            D_data[rtDW->RLinv] += rtDW->TL_data[((int16_T)rtDW->b_n +
              rtDW->TL_size_idx_0 * (b_j - 1)) - 1] * RLinv_data[((int16_T)
              rtDW->m + RLinv_size[0] * (b_j - 1)) - 1];
          }

          rtDW->b_n++;
        }

        rtDW->m++;
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static real32_T mtimes_k(const real32_T A_data[], const real32_T B_1[7])
{
  int32_T k;
  real32_T C;
  C = 0.0F;
  for (k = 0; k < 7; k++) {
    C += A_data[k] * B_1[k];
  }

  return C;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void DropConstraint(int16_T kDrop, int16_T iA[8], int16_T *nA, int16_T
  iC[8])
{
  int32_T tmp;
  int16_T i;
  iA[iC[kDrop - 1] - 1] = 0;
  if (kDrop < *nA) {
    tmp = *nA - 1;
    if (*nA - 1 < -32768) {
      tmp = -32768;
    }

    for (i = kDrop; i <= (int16_T)tmp; i++) {
      iC[i - 1] = iC[i];
    }
  }

  iC[*nA - 1] = 0;
  tmp = *nA - 1;
  if (*nA - 1 < -32768) {
    tmp = -32768;
  }

  *nA = (int16_T)tmp;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void ResetToColdStart(int16_T iA[8], int16_T iC[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    iA[i] = 0;
    iC[i] = 0;
  }

  iA[7] = 1;
  iC[0] = 8;
}

/* Function for MATLAB Function: '<S1>/qp_solver' */
static void qpkwik(const real32_T Linv_data[], const int32_T Linv_size[2], const
                   real32_T Hinv_data[], const int32_T Hinv_size[2], const
                   real32_T f[7], int16_T maxiter, int16_T n, real32_T x_data[],
                   int32_T *x_size, real32_T lambda[8], real32_T *status,
                   int16_T iA[8], DW *rtDW)
{
  int16_T kDrop;
  int16_T kNext;
  int16_T nA;
  int16_T tmp;
  int16_T tmp_0;
  boolean_T ColdReset;
  boolean_T DualFeasible;
  boolean_T cTolComputed;
  static const int8_T h[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };

  static const int8_T Ac[56] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
    0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1 };

  static const real32_T varargin_1[8] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 1.0F };

  int32_T exitg1;
  int32_T exitg3;
  boolean_T exitg2;
  boolean_T exitg4;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  *status = 1.0F;
  for (rtDW->i_g = 0; rtDW->i_g < 8; rtDW->i_g++) {
    iA[rtDW->i_g] = h[rtDW->i_g];
    lambda[rtDW->i_g] = 0.0F;
  }

  *x_size = n;
  rtDW->loop_ub = n;
  if (0 <= rtDW->loop_ub - 1) {
    memset(&x_data[0], 0, rtDW->loop_ub * sizeof(real32_T));
  }

  rtDW->loop_ub = n;
  if (0 <= rtDW->loop_ub - 1) {
    memset(&rtDW->r_data[0], 0, rtDW->loop_ub * sizeof(real32_T));
  }

  rtDW->rMin = 0.0F;
  rtDW->RLinv_size[0] = Linv_size[0];
  rtDW->RLinv_size[1] = Linv_size[1];
  rtDW->D_size[0] = Linv_size[0];
  rtDW->D_size[1] = Linv_size[1];
  rtDW->H_size[0] = Linv_size[0];
  rtDW->H_size[1] = Linv_size[1];
  rtDW->U_size[0] = Linv_size[0];
  cTolComputed = false;
  for (rtDW->i_g = 0; rtDW->i_g < 8; rtDW->i_g++) {
    rtDW->cTol[rtDW->i_g] = 1.0F;
    rtDW->iC[rtDW->i_g] = 0;
  }

  nA = 0;
  for (rtDW->i_g = 0; rtDW->i_g < 8; rtDW->i_g++) {
    if (iA[rtDW->i_g] == 1) {
      rtDW->lambda_tmp_tmp = nA + 1;
      if (nA + 1 > 32767) {
        rtDW->lambda_tmp_tmp = 32767;
      }

      nA = (int16_T)rtDW->lambda_tmp_tmp;
      rtDW->iC[(int16_T)rtDW->lambda_tmp_tmp - 1] = (int16_T)(rtDW->i_g + 1);
    }
  }

  guard1 = false;
  if (nA > 0) {
    if (n > 16383) {
      tmp = MAX_int16_T;
    } else if (n <= -16384) {
      tmp = MIN_int16_T;
    } else {
      tmp = (int16_T)(n << 1);
    }

    rtDW->i_g = tmp;
    if (0 <= rtDW->i_g - 1) {
      memset(&rtDW->Opt_data[0], 0, rtDW->i_g * sizeof(real32_T));
    }

    for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < 7;
         rtDW->lambda_tmp_tmp++) {
      rtDW->Rhs_data[rtDW->lambda_tmp_tmp] = f[rtDW->lambda_tmp_tmp];
    }

    rtDW->loop_ub = n;
    if (0 <= rtDW->loop_ub - 1) {
      memset(&rtDW->Rhs_data[7], 0, rtDW->loop_ub * sizeof(real32_T));
    }

    DualFeasible = false;
    ColdReset = false;
    do {
      exitg3 = 0;
      if ((!DualFeasible) && (nA > 0) && ((int32_T)*status <= maxiter)) {
        rtDW->Xnorm0 = KWIKfactor(rtDW->iC, nA, Linv_data, Linv_size,
          rtDW->RLinv_data, rtDW->RLinv_size, rtDW->D_data, rtDW->D_size,
          rtDW->H_data, rtDW->H_size, n, rtDW);
        if (rtDW->Xnorm0 < 0.0F) {
          if (ColdReset) {
            *status = -2.0F;
            exitg3 = 2;
          } else {
            ResetToColdStart(iA, rtDW->iC);
            nA = 1;
            ColdReset = true;
          }
        } else {
          rtDW->i_g = 1;
          while (rtDW->i_g - 1 <= nA - 1) {
            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_g;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->lambda_tmp_tmp = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->lambda_tmp_tmp = -32768;
            }

            rtDW->Rhs_data[rtDW->lambda_tmp_tmp - 1] = h[rtDW->iC[(int16_T)
              rtDW->i_g - 1] - 1];
            for (kNext = (int16_T)rtDW->i_g; kNext <= nA; kNext++) {
              rtDW->lambda_tmp_tmp = (kNext + rtDW->U_size[0] * ((int16_T)
                rtDW->i_g - 1)) - 1;
              rtDW->U_data[rtDW->lambda_tmp_tmp] = 0.0F;
              rtDW->H = 1;
              while (rtDW->H - 1 <= nA - 1) {
                rtDW->loop_ub = rtDW->RLinv_size[0] * ((int16_T)rtDW->H - 1);
                rtDW->U_data[rtDW->lambda_tmp_tmp] += rtDW->RLinv_data[(kNext +
                  rtDW->loop_ub) - 1] * rtDW->RLinv_data[((int16_T)rtDW->i_g +
                  rtDW->loop_ub) - 1];
                rtDW->H++;
              }

              rtDW->U_data[((int16_T)rtDW->i_g + rtDW->U_size[0] * (kNext - 1))
                - 1] = rtDW->U_data[rtDW->lambda_tmp_tmp];
            }

            rtDW->i_g++;
          }

          rtDW->i_g = 1;
          while (rtDW->i_g - 1 <= n - 1) {
            rtDW->loop_ub = rtDW->H_size[1];
            rtDW->Xnorm0 = 0.0F;
            for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < rtDW->loop_ub;
                 rtDW->lambda_tmp_tmp++) {
              rtDW->Xnorm0 += rtDW->H_data[((int16_T)rtDW->i_g + rtDW->H_size[0]
                * rtDW->lambda_tmp_tmp) - 1] * rtDW->Rhs_data
                [rtDW->lambda_tmp_tmp];
            }

            rtDW->Opt_data[(int16_T)rtDW->i_g - 1] = rtDW->Xnorm0;
            rtDW->H = 1;
            while (rtDW->H - 1 <= nA - 1) {
              rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->H;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->lambda_tmp_tmp = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->lambda_tmp_tmp = -32768;
              }

              rtDW->Opt_data[(int16_T)rtDW->i_g - 1] += rtDW->D_data[((int16_T)
                rtDW->i_g + rtDW->D_size[0] * ((int16_T)rtDW->H - 1)) - 1] *
                rtDW->Rhs_data[rtDW->lambda_tmp_tmp - 1];
              rtDW->H++;
            }

            rtDW->i_g++;
          }

          rtDW->i_g = 1;
          while (rtDW->i_g - 1 <= nA - 1) {
            rtDW->loop_ub = rtDW->D_size[0];
            rtDW->Xnorm0 = 0.0F;
            for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < rtDW->loop_ub;
                 rtDW->lambda_tmp_tmp++) {
              rtDW->Xnorm0 += rtDW->D_data[rtDW->lambda_tmp_tmp + rtDW->D_size[0]
                * ((int16_T)rtDW->i_g - 1)] * rtDW->Rhs_data
                [rtDW->lambda_tmp_tmp];
            }

            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_g;
            rtDW->loop_ub = rtDW->lambda_tmp_tmp;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->loop_ub = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->loop_ub = -32768;
            }

            rtDW->Opt_data[rtDW->loop_ub - 1] = rtDW->Xnorm0;
            rtDW->H = 1;
            while (rtDW->H - 1 <= nA - 1) {
              rtDW->loop_ub = rtDW->lambda_tmp_tmp;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->loop_ub = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->loop_ub = -32768;
              }

              rtDW->i_m = rtDW->lambda_tmp_tmp;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->i_m = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->i_m = -32768;
              }

              rtDW->i1 = n + (int16_T)rtDW->H;
              if (rtDW->i1 > 32767) {
                rtDW->i1 = 32767;
              } else if (rtDW->i1 < -32768) {
                rtDW->i1 = -32768;
              }

              rtDW->Opt_data[rtDW->loop_ub - 1] = rtDW->U_data[((int16_T)
                rtDW->i_g + rtDW->U_size[0] * ((int16_T)rtDW->H - 1)) - 1] *
                rtDW->Rhs_data[rtDW->i1 - 1] + rtDW->Opt_data[rtDW->i_m - 1];
              rtDW->H++;
            }

            rtDW->i_g++;
          }

          rtDW->Xnorm0 = -1.0E-12F;
          kDrop = 0;
          rtDW->i_g = 1;
          while (rtDW->i_g - 1 <= nA - 1) {
            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_g;
            rtDW->loop_ub = rtDW->lambda_tmp_tmp;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->loop_ub = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->loop_ub = -32768;
            }

            lambda[rtDW->iC[(int16_T)rtDW->i_g - 1] - 1] = rtDW->Opt_data
              [rtDW->loop_ub - 1];
            rtDW->loop_ub = rtDW->lambda_tmp_tmp;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->loop_ub = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->loop_ub = -32768;
            }

            if ((rtDW->Opt_data[rtDW->loop_ub - 1] < rtDW->Xnorm0) && ((int16_T)
                 rtDW->i_g <= nA - 1)) {
              kDrop = (int16_T)rtDW->i_g;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->lambda_tmp_tmp = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->lambda_tmp_tmp = -32768;
              }

              rtDW->Xnorm0 = rtDW->Opt_data[rtDW->lambda_tmp_tmp - 1];
            }

            rtDW->i_g++;
          }

          if (kDrop <= 0) {
            DualFeasible = true;
            if (1 > n) {
              rtDW->loop_ub = -1;
            } else {
              rtDW->loop_ub = n - 1;
            }

            *x_size = rtDW->loop_ub + 1;
            if (0 <= rtDW->loop_ub) {
              memcpy(&x_data[0], &rtDW->Opt_data[0], (rtDW->loop_ub + 1) *
                     sizeof(real32_T));
            }
          } else {
            (*status)++;
            if (*status > 5.0F) {
              ResetToColdStart(iA, rtDW->iC);
              nA = 1;
              ColdReset = true;
            } else {
              lambda[rtDW->iC[kDrop - 1] - 1] = 0.0F;
              DropConstraint(kDrop, iA, &nA, rtDW->iC);
            }
          }
        }
      } else {
        if (nA <= 0) {
          for (rtDW->i_g = 0; rtDW->i_g < 8; rtDW->i_g++) {
            lambda[rtDW->i_g] = 0.0F;
          }

          Unconstrained(Hinv_data, Hinv_size, f, x_data, n);
        }

        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    Unconstrained(Hinv_data, Hinv_size, f, x_data, n);
    guard1 = true;
  }

  if (guard1) {
    rtDW->Xnorm0 = norm(x_data, x_size);
    exitg2 = false;
    while ((!exitg2) && ((int32_T)*status <= maxiter)) {
      rtDW->cMin = -1.0E-6F;
      kNext = 0;
      for (rtDW->i_g = 0; rtDW->i_g < 7; rtDW->i_g++) {
        rtDW->t_g = rtDW->cTol[rtDW->i_g];
        if (!cTolComputed) {
          for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < 7;
               rtDW->lambda_tmp_tmp++) {
            rtDW->AcRow[rtDW->lambda_tmp_tmp] = (real32_T)Ac[rtDW->i_g +
              (rtDW->lambda_tmp_tmp << 3)] * x_data[rtDW->lambda_tmp_tmp];
          }

          abs_d(rtDW->AcRow, rtDW->z_data);
          rtDW->t_g = fmaxf(rtDW->t_g, maximum(rtDW->z_data));
        }

        if (iA[rtDW->i_g] == 0) {
          rtDW->cVal = 0.0F;
          for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < 7;
               rtDW->lambda_tmp_tmp++) {
            rtDW->cVal += (real32_T)Ac[rtDW->i_g + (rtDW->lambda_tmp_tmp << 3)] *
              x_data[rtDW->lambda_tmp_tmp];
          }

          rtDW->cVal /= rtDW->t_g;
          if (rtDW->cVal < rtDW->cMin) {
            rtDW->cMin = rtDW->cVal;
            kNext = (int16_T)(rtDW->i_g + 1);
          }
        }

        rtDW->cTol[rtDW->i_g] = rtDW->t_g;
      }

      cTolComputed = true;
      if (kNext <= 0) {
        exitg2 = true;
      } else if ((int32_T)*status == maxiter) {
        *status = 0.0F;
        exitg2 = true;
      } else {
        do {
          exitg1 = 0;
          if ((kNext > 0) && ((int32_T)*status <= maxiter)) {
            for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < 7;
                 rtDW->lambda_tmp_tmp++) {
              rtDW->AcRow[rtDW->lambda_tmp_tmp] = Ac[((rtDW->lambda_tmp_tmp << 3)
                + kNext) - 1];
            }

            guard2 = false;
            if (nA == 0) {
              mtimes(Hinv_data, Hinv_size, rtDW->AcRow, rtDW->z_data,
                     &rtDW->z_size);
              guard2 = true;
            } else {
              rtDW->cMin = KWIKfactor(rtDW->iC, nA, Linv_data, Linv_size,
                rtDW->RLinv_data, rtDW->RLinv_size, rtDW->D_data, rtDW->D_size,
                rtDW->H_data, rtDW->H_size, n, rtDW);
              if (rtDW->cMin <= 0.0F) {
                *status = -2.0F;
                exitg1 = 1;
              } else {
                rtDW->U_size[0] = rtDW->H_size[0];
                rtDW->U_size[1] = rtDW->H_size[1];
                rtDW->loop_ub = rtDW->H_size[0] * rtDW->H_size[1];
                for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp <
                     rtDW->loop_ub; rtDW->lambda_tmp_tmp++) {
                  rtDW->U_data[rtDW->lambda_tmp_tmp] = -rtDW->H_data
                    [rtDW->lambda_tmp_tmp];
                }

                mtimes(rtDW->U_data, rtDW->U_size, rtDW->AcRow, rtDW->z_data,
                       &rtDW->z_size);
                rtDW->i_g = 1;
                while (rtDW->i_g - 1 <= nA - 1) {
                  rtDW->t_g = 0.0F;
                  for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < 7;
                       rtDW->lambda_tmp_tmp++) {
                    rtDW->t_g += rtDW->D_data[rtDW->lambda_tmp_tmp +
                      rtDW->D_size[0] * ((int16_T)rtDW->i_g - 1)] * rtDW->
                      AcRow[rtDW->lambda_tmp_tmp];
                  }

                  rtDW->r_data[(int16_T)rtDW->i_g - 1] = rtDW->t_g;
                  rtDW->i_g++;
                }

                guard2 = true;
              }
            }

            if (guard2) {
              kDrop = 0;
              rtDW->cMin = 0.0F;
              DualFeasible = true;
              ColdReset = true;
              if (nA > 1) {
                rtDW->i_g = 0;
                exitg4 = false;
                while ((!exitg4) && (rtDW->i_g <= nA - 2)) {
                  if (rtDW->r_data[rtDW->i_g] >= 1.0E-12F) {
                    ColdReset = false;
                    exitg4 = true;
                  } else {
                    rtDW->i_g++;
                  }
                }
              }

              if ((nA != 1) && (!ColdReset)) {
                rtDW->lambda_tmp_tmp = nA - 1;
                if (nA - 1 < -32768) {
                  rtDW->lambda_tmp_tmp = -32768;
                }

                rtDW->i_g = 1;
                while (rtDW->i_g - 1 <= (int16_T)rtDW->lambda_tmp_tmp - 1) {
                  rtDW->cVal = rtDW->r_data[(int16_T)rtDW->i_g - 1];
                  if (rtDW->cVal > 1.0E-12F) {
                    rtDW->cVal = lambda[rtDW->iC[(int16_T)rtDW->i_g - 1] - 1] /
                      rtDW->cVal;
                    if ((kDrop == 0) || (rtDW->cVal < rtDW->rMin)) {
                      rtDW->rMin = rtDW->cVal;
                      kDrop = (int16_T)rtDW->i_g;
                    }
                  }

                  rtDW->i_g++;
                }

                if (kDrop > 0) {
                  rtDW->cMin = rtDW->rMin;
                  DualFeasible = false;
                }
              }

              rtDW->cVal = mtimes_k(rtDW->z_data, rtDW->AcRow);
              if (rtDW->cVal <= 0.0F) {
                rtDW->cVal = 0.0F;
                ColdReset = true;
              } else {
                rtDW->t_g = 0.0F;
                for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < 7;
                     rtDW->lambda_tmp_tmp++) {
                  rtDW->t_g += rtDW->AcRow[rtDW->lambda_tmp_tmp] * x_data
                    [rtDW->lambda_tmp_tmp];
                }

                rtDW->cVal = (-0.0F - rtDW->t_g) / rtDW->cVal;
                ColdReset = false;
              }

              if (DualFeasible && ColdReset) {
                *status = -1.0F;
                exitg1 = 1;
              } else {
                if (ColdReset) {
                  rtDW->t_g = rtDW->cMin;
                } else if (DualFeasible) {
                  rtDW->t_g = rtDW->cVal;
                } else {
                  rtDW->t_g = fminf(rtDW->cMin, rtDW->cVal);
                }

                rtDW->i_g = 1;
                while (rtDW->i_g - 1 <= nA - 1) {
                  rtDW->lambda_tmp_tmp = rtDW->iC[(int16_T)rtDW->i_g - 1];
                  lambda[rtDW->lambda_tmp_tmp - 1] -= rtDW->r_data[(int16_T)
                    rtDW->i_g - 1] * rtDW->t_g;
                  if ((rtDW->lambda_tmp_tmp <= 7) && (lambda
                       [rtDW->lambda_tmp_tmp - 1] < 0.0F)) {
                    lambda[rtDW->lambda_tmp_tmp - 1] = 0.0F;
                  }

                  rtDW->i_g++;
                }

                lambda[kNext - 1] += rtDW->t_g;
                if (rtDW->t_g == rtDW->cMin) {
                  DropConstraint(kDrop, iA, &nA, rtDW->iC);
                }

                if (!ColdReset) {
                  rtDW->loop_ub = *x_size;
                  for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp <
                       rtDW->loop_ub; rtDW->lambda_tmp_tmp++) {
                    x_data[rtDW->lambda_tmp_tmp] += rtDW->t_g * rtDW->
                      z_data[rtDW->lambda_tmp_tmp];
                  }

                  if (rtDW->t_g == rtDW->cVal) {
                    if (nA == n) {
                      *status = -1.0F;
                      exitg1 = 1;
                    } else {
                      rtDW->lambda_tmp_tmp = nA + 1;
                      if (nA + 1 > 32767) {
                        rtDW->lambda_tmp_tmp = 32767;
                      }

                      nA = (int16_T)rtDW->lambda_tmp_tmp;
                      rtDW->iC[(int16_T)rtDW->lambda_tmp_tmp - 1] = kNext;
                      kDrop = (int16_T)rtDW->lambda_tmp_tmp;
                      exitg4 = false;
                      while ((!exitg4) && (kDrop > 1)) {
                        tmp = rtDW->iC[kDrop - 1];
                        tmp_0 = rtDW->iC[kDrop - 2];
                        if (tmp > tmp_0) {
                          exitg4 = true;
                        } else {
                          rtDW->iC[kDrop - 1] = tmp_0;
                          rtDW->iC[kDrop - 2] = tmp;
                          kDrop--;
                        }
                      }

                      iA[kNext - 1] = 1;
                      kNext = 0;
                      (*status)++;
                    }
                  } else {
                    (*status)++;
                  }
                } else {
                  (*status)++;
                }
              }
            }
          } else {
            rtDW->cMin = norm(x_data, x_size);
            if (fabsf(rtDW->cMin - rtDW->Xnorm0) > 0.001F) {
              rtDW->Xnorm0 = rtDW->cMin;
              maximum2(varargin_1, rtDW->cTol);
              cTolComputed = false;
            }

            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    }
  }
}

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  int16_T tmp;
  boolean_T rEQ0;
  static const int8_T tmp_0[24] = { 8, 1, 1, 8, 8, 2, 2, 16, 16, 2, 2, 16, 16, 4,
    4, 32, 32, 4, 4, 32, 32, 1, 1, 8 };

  static const int8_T tmp_1[24] = { 9, 9, 9, 9, 10, 10, 18, 18, 18, 18, 18, 18,
    20, 20, 36, 36, 36, 36, 36, 36, 33, 33, 9, 9 };

  static const int8_T tmp_2[24] = { 41, 11, 11, 11, 11, 26, 26, 26, 26, 22, 22,
    22, 22, 52, 52, 52, 52, 37, 37, 37, 37, 41, 41, 41 };

  static const int8_T tmp_3[24] = { 43, 43, 27, 27, 27, 27, 27, 27, 30, 30, 54,
    54, 54, 54, 54, 54, 53, 53, 45, 45, 45, 45, 45, 45 };

  static const int8_T tmp_4[24] = { 47, 59, 59, 31, 31, 59, 59, 31, 31, 62, 62,
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

  boolean_T exitg1;

  /* Trigonometry: '<S1>/SinCos1' incorporates:
   *  Inport: '<Root>/theta_el'
   */
  rtDW->SinCos1_o1 = sinf(rtU->theta_el);
  rtDW->SinCos1_o2 = cosf(rtU->theta_el);

  /* MATLAB Function: '<S1>/seq_2_act_sw_all' */
  for (rtDW->i = 0; rtDW->i < 24; rtDW->i++) {
    rtDW->act_sw_1[rtDW->i] = tmp_0[rtDW->i];
    rtDW->act_sw_2[rtDW->i] = tmp_1[rtDW->i];
    rtDW->act_sw_3[rtDW->i] = tmp_2[rtDW->i];
    rtDW->act_sw_4[rtDW->i] = tmp_3[rtDW->i];
    rtDW->act_sw_5[rtDW->i] = tmp_4[rtDW->i];
  }

  /* End of MATLAB Function: '<S1>/seq_2_act_sw_all' */

  /* MATLAB Function: '<S1>/deadbeat_solution' incorporates:
   *  Inport: '<Root>/Ld_over_LB'
   *  Inport: '<Root>/Lq_over_LB'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/i_d_ref_pu'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/i_q_ref_pu'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/psi_pm_over_psiB'
   *  Inport: '<Root>/theta_el'
   */
  /* MATLAB Function 'uz_codegen/seq_2_act_sw_all': '<S7>:1' */
  /* '<S7>:1:3' act_sw_1 = single(zeros(24,1)); */
  /* '<S7>:1:4' act_sw_2 = single(zeros(24,1)); */
  /* '<S7>:1:5' act_sw_3 = single(zeros(24,1)); */
  /* '<S7>:1:6' act_sw_4 = single(zeros(24,1)); */
  /* '<S7>:1:7' act_sw_5 = single(zeros(24,1)); */
  /*  columns=sequence, rows=active switch postion               */
  /* '<S7>:1:10' seq_table_svm24 = single([   8, 9,41,43,47; */
  /* '<S7>:1:11'                              1, 9,11,43,59; */
  /* '<S7>:1:12'                              1, 9,11,27,59; */
  /* '<S7>:1:13'                              8, 9,11,27,31; */
  /* '<S7>:1:14'                              8,10,11,27,31; */
  /* '<S7>:1:15'                              2,10,26,27,59; */
  /* '<S7>:1:16'                              2,18,26,27,59; */
  /* '<S7>:1:17'                             16,18,26,27,31; */
  /* '<S7>:1:18'                             16,18,26,30,31; */
  /* '<S7>:1:19'                              2,18,22,30,62; */
  /* '<S7>:1:20'                              2,18,22,54,62; */
  /* '<S7>:1:21'                             16,18,22,54,55; */
  /* '<S7>:1:22'                             16,20,22,54,55; */
  /* '<S7>:1:23'                              4,20,52,54,62; */
  /* '<S7>:1:24'                              4,36,52,54,62; */
  /* '<S7>:1:25'                             32,36,52,54,55; */
  /* '<S7>:1:26'                             32,36,52,53,55; */
  /* '<S7>:1:27'                              4,36,37,53,61; */
  /* '<S7>:1:28'                              4,36,37,45,61; */
  /* '<S7>:1:29'                             32,36,37,45,47; */
  /* '<S7>:1:30'                             32,33,37,45,47; */
  /* '<S7>:1:31'                              1,33,41,45,61; */
  /* '<S7>:1:32'                              1, 9,41,45,61; */
  /* '<S7>:1:33'                              8, 9,41,45,47]); */
  /* '<S7>:1:35' act_sw_1 = seq_table_svm24(:,1); */
  /* '<S7>:1:36' act_sw_2 = seq_table_svm24(:,2); */
  /* '<S7>:1:37' act_sw_3 = seq_table_svm24(:,3); */
  /* '<S7>:1:38' act_sw_4 = seq_table_svm24(:,4); */
  /* '<S7>:1:39' act_sw_5 = seq_table_svm24(:,5); */
  /* MATLAB Function 'uz_codegen/deadbeat_solution': '<S3>:1' */
  /* '<S3>:1:4' v_d_ref_pu = (i_d_ref_pu-i_d_pu)/(Ts_times_ZB_over_Ld) + i_d_pu*Rs_over_ZB - omega_el*Lq_over_LB*i_q_pu; */
  /* '<S3>:1:5' v_q_ref_pu = (i_q_ref_pu-i_q_pu)/(Ts_times_ZB_over_Lq) + i_q_pu*Rs_over_ZB + omega_el*(Ld_over_LB*i_d_pu+psi_pm_over_psiB); */
  /* '<S3>:1:7' angle_ref = mod(atan2(v_q_ref_pu, v_d_ref_pu) + theta_el, 2*pi); */
  rtDW->x = atan2f(((rtU->i_q_ref_pu - rtU->i_dq_pu[1]) /
                    rtU->Ts_times_ZB_over_Lq + rtU->i_dq_pu[1] * rtU->Rs_over_ZB)
                   + (rtU->Ld_over_LB * rtU->i_dq_pu[0] + rtU->psi_pm_over_psiB)
                   * rtU->omega_el_pu, ((rtU->i_d_ref_pu - rtU->i_dq_pu[0]) /
    rtU->Ts_times_ZB_over_Ld + rtU->i_dq_pu[0] * rtU->Rs_over_ZB) -
                   rtU->omega_el_pu * rtU->Lq_over_LB * rtU->i_dq_pu[1]) +
    rtU->theta_el;
  if (rtDW->x == 0.0F) {
    rtDW->w6theta_el = 0.0F;
  } else {
    rtDW->w6theta_el = fmodf(rtDW->x, 6.28318548F);
    rEQ0 = (rtDW->w6theta_el == 0.0F);
    if (!rEQ0) {
      rtDW->q = fabsf(rtDW->x / 6.28318548F);
      rEQ0 = (fabsf(rtDW->q - floorf(rtDW->q + 0.5F)) <= 1.1920929E-7F * rtDW->q);
    }

    if (rEQ0) {
      rtDW->w6theta_el = 0.0F;
    } else if (rtDW->x < 0.0F) {
      rtDW->w6theta_el += 6.28318548F;
    }
  }

  /* '<S3>:1:9' sector_ref = 0.0; */
  rtDW->sector_ref = 0;

  /* '<S3>:1:10' if (angle_ref >= 0.0 && angle_ref < pi/180*15) */
  if ((rtDW->w6theta_el >= 0.0F) && (rtDW->w6theta_el < 0.26179938779914941)) {
    /* '<S3>:1:11' sector_ref = 1.0; */
    rtDW->sector_ref = 1;
  } else if ((rtDW->w6theta_el >= 0.26179938779914941) && (rtDW->w6theta_el <
              0.52359877559829882)) {
    /* '<S3>:1:12' elseif (angle_ref >= pi/180*15 && angle_ref < pi/180*30) */
    /* '<S3>:1:13' sector_ref = 2.0; */
    rtDW->sector_ref = 2;
  } else if ((rtDW->w6theta_el >= 0.52359877559829882) && (rtDW->w6theta_el <
              0.78539816339744828)) {
    /* '<S3>:1:14' elseif (angle_ref >= pi/180*30 && angle_ref < pi/180*45) */
    /* '<S3>:1:15' sector_ref = 3.0; */
    rtDW->sector_ref = 3;
  } else if ((rtDW->w6theta_el >= 0.78539816339744828) && (rtDW->w6theta_el <
              1.0471975511965976)) {
    /* '<S3>:1:16' elseif (angle_ref >= pi/180*45 && angle_ref < pi/180*60) */
    /* '<S3>:1:17' sector_ref = 4.0; */
    rtDW->sector_ref = 4;
  } else if ((rtDW->w6theta_el >= 1.0471975511965976) && (rtDW->w6theta_el <
              1.3089969389957472)) {
    /* '<S3>:1:18' elseif (angle_ref >= pi/180*60 && angle_ref < pi/180*75) */
    /* '<S3>:1:19' sector_ref = 5.0; */
    rtDW->sector_ref = 5;
  } else if ((rtDW->w6theta_el >= 1.3089969389957472) && (rtDW->w6theta_el <
              1.5707963267948966)) {
    /* '<S3>:1:20' elseif (angle_ref >= pi/180*75 && angle_ref < pi/180*90) */
    /* '<S3>:1:21' sector_ref = 6.0; */
    rtDW->sector_ref = 6;
  } else if ((rtDW->w6theta_el >= 1.5707963267948966) && (rtDW->w6theta_el <
              1.8325957145940461)) {
    /* '<S3>:1:22' elseif (angle_ref >= pi/180*90 && angle_ref < pi/180*105) */
    /* '<S3>:1:23' sector_ref = 7.0; */
    rtDW->sector_ref = 7;
  } else if ((rtDW->w6theta_el >= 1.8325957145940461) && (rtDW->w6theta_el <
              2.0943951023931953)) {
    /* '<S3>:1:24' elseif (angle_ref >= pi/180*105 && angle_ref < pi/180*120) */
    /* '<S3>:1:25' sector_ref = 8.0; */
    rtDW->sector_ref = 8;
  } else if ((rtDW->w6theta_el >= 2.0943951023931953) && (rtDW->w6theta_el <
              2.3561944901923448)) {
    /* '<S3>:1:26' elseif (angle_ref >= pi/180*120 && angle_ref < pi/180*135) */
    /* '<S3>:1:27' sector_ref = 9.0; */
    rtDW->sector_ref = 9;
  } else if ((rtDW->w6theta_el >= 2.3561944901923448) && (rtDW->w6theta_el <
              2.6179938779914944)) {
    /* '<S3>:1:28' elseif (angle_ref >= pi/180*135 && angle_ref < pi/180*150) */
    /* '<S3>:1:29' sector_ref = 10.0; */
    rtDW->sector_ref = 10;
  } else if ((rtDW->w6theta_el >= 2.6179938779914944) && (rtDW->w6theta_el <
              2.8797932657906435)) {
    /* '<S3>:1:30' elseif (angle_ref >= pi/180*150 && angle_ref < pi/180*165) */
    /* '<S3>:1:31' sector_ref = 11.0; */
    rtDW->sector_ref = 11;
  } else if ((rtDW->w6theta_el >= 2.8797932657906435) && (rtDW->w6theta_el <
              3.1415926535897931)) {
    /* '<S3>:1:32' elseif (angle_ref >= pi/180*165 && angle_ref < pi/180*180) */
    /* '<S3>:1:33' sector_ref = 12.0; */
    rtDW->sector_ref = 12;
  } else if ((rtDW->w6theta_el >= 3.1415926535897931) && (rtDW->w6theta_el <
              3.4033920413889427)) {
    /* '<S3>:1:34' elseif (angle_ref >= pi/180*180 && angle_ref < pi/180*195) */
    /* '<S3>:1:35' sector_ref = 13.0; */
    rtDW->sector_ref = 13;
  } else if ((rtDW->w6theta_el >= 3.4033920413889427) && (rtDW->w6theta_el <
              3.6651914291880923)) {
    /* '<S3>:1:36' elseif (angle_ref >= pi/180*195 && angle_ref < pi/180*210) */
    /* '<S3>:1:37' sector_ref = 14.0; */
    rtDW->sector_ref = 14;
  } else if ((rtDW->w6theta_el >= 3.6651914291880923) && (rtDW->w6theta_el <
              3.9269908169872414)) {
    /* '<S3>:1:38' elseif (angle_ref >= pi/180*210 && angle_ref < pi/180*225) */
    /* '<S3>:1:39' sector_ref = 15.0; */
    rtDW->sector_ref = 15;
  } else if ((rtDW->w6theta_el >= 3.9269908169872414) && (rtDW->w6theta_el <
              4.1887902047863905)) {
    /* '<S3>:1:40' elseif (angle_ref >= pi/180*225 && angle_ref < pi/180*240) */
    /* '<S3>:1:41' sector_ref = 16.0; */
    rtDW->sector_ref = 16;
  } else if ((rtDW->w6theta_el >= 4.1887902047863905) && (rtDW->w6theta_el <
              4.4505895925855405)) {
    /* '<S3>:1:42' elseif (angle_ref >= pi/180*240 && angle_ref < pi/180*255) */
    /* '<S3>:1:43' sector_ref = 17.0; */
    rtDW->sector_ref = 17;
  } else if ((rtDW->w6theta_el >= 4.4505895925855405) && (rtDW->w6theta_el <
              4.71238898038469)) {
    /* '<S3>:1:44' elseif (angle_ref >= pi/180*255 && angle_ref < pi/180*270) */
    /* '<S3>:1:45' sector_ref = 18.0; */
    rtDW->sector_ref = 18;
  } else if ((rtDW->w6theta_el >= 4.71238898038469) && (rtDW->w6theta_el <
              4.9741883681838388)) {
    /* '<S3>:1:46' elseif (angle_ref >= pi/180*270 && angle_ref < pi/180*285) */
    /* '<S3>:1:47' sector_ref = 19.0; */
    rtDW->sector_ref = 19;
  } else if ((rtDW->w6theta_el >= 4.9741883681838388) && (rtDW->w6theta_el <
              5.2359877559829888)) {
    /* '<S3>:1:48' elseif (angle_ref >= pi/180*285 && angle_ref < pi/180*300) */
    /* '<S3>:1:49' sector_ref = 20.0; */
    rtDW->sector_ref = 20;
  } else if ((rtDW->w6theta_el >= 5.2359877559829888) && (rtDW->w6theta_el <
              5.497787143782138)) {
    /* '<S3>:1:50' elseif (angle_ref >= pi/180*300 && angle_ref < pi/180*315) */
    /* '<S3>:1:51' sector_ref = 21.0; */
    rtDW->sector_ref = 21;
  } else if ((rtDW->w6theta_el >= 5.497787143782138) && (rtDW->w6theta_el <
              5.7595865315812871)) {
    /* '<S3>:1:52' elseif (angle_ref >= pi/180*315 && angle_ref < pi/180*330) */
    /* '<S3>:1:53' sector_ref = 22.0; */
    rtDW->sector_ref = 22;
  } else if ((rtDW->w6theta_el >= 5.7595865315812871) && (rtDW->w6theta_el <
              6.0213859193804371)) {
    /* '<S3>:1:54' elseif (angle_ref >= pi/180*330 && angle_ref < pi/180*345) */
    /* '<S3>:1:55' sector_ref = 23.0; */
    rtDW->sector_ref = 23;
  } else if ((rtDW->w6theta_el >= 6.0213859193804371) && (rtDW->w6theta_el <
              6.2831853071795862)) {
    /* '<S3>:1:56' elseif (angle_ref >= pi/180*345 && angle_ref < pi/180*360) */
    /* '<S3>:1:57' sector_ref = 24.0; */
    rtDW->sector_ref = 24;
  }

  /* End of MATLAB Function: '<S1>/deadbeat_solution' */

  /* MATLAB Function: '<S1>/act_sw_2_dqxy_volts_all' incorporates:
   *  Inport: '<Root>/v_DC_pu'
   */
  /*  voltage lookup factors alpha/beta */
  /* MATLAB Function 'uz_codegen/act_sw_2_dqxy_volts_all': '<S2>:1' */
  /*  since zero voltages for switch position 0 and 63 is not needed */
  /*  and matlab does use one based indexing, i simply removed entrys 1  */
  /*  and 64. Therefore, the voltage LUTs below correspond again  */
  /*  to index 1 beeing the voltages for respective switch position  */
  /*  1 (000001b)  */
  /* '<S2>:1:12' v_alpha_beta_pu = single([ %0.0,0.0; */
  /* '<S2>:1:13' 0.333333, -0.000000; */
  /* '<S2>:1:14' -0.166667, 0.288675; */
  /* '<S2>:1:15' 0.166667, 0.288675; */
  /* '<S2>:1:16' -0.166667, -0.288675; */
  /* '<S2>:1:17' 0.166667, -0.288675; */
  /* '<S2>:1:18' -0.333333, 0.000000; */
  /* '<S2>:1:19' 0.000000, 0.000000; */
  /* '<S2>:1:20' 0.288675, 0.166667; */
  /* '<S2>:1:21' 0.622008, 0.166667; */
  /* '<S2>:1:22' 0.122008, 0.455342; */
  /* '<S2>:1:23' 0.455342, 0.455342; */
  /* '<S2>:1:24' 0.122008, -0.122008; */
  /* '<S2>:1:25' 0.455342, -0.122008; */
  /* '<S2>:1:26' -0.044658, 0.166667; */
  /* '<S2>:1:27' 0.288675, 0.166667; */
  /* '<S2>:1:28' -0.288675, 0.166667; */
  /* '<S2>:1:29' 0.044658, 0.166667; */
  /* '<S2>:1:30' -0.455342, 0.455342; */
  /* '<S2>:1:31' -0.122008, 0.455342; */
  /* '<S2>:1:32' -0.455342, -0.122008; */
  /* '<S2>:1:33' -0.122008, -0.122008; */
  /* '<S2>:1:34' -0.622008, 0.166667; */
  /* '<S2>:1:35' -0.288675, 0.166667; */
  /* '<S2>:1:36' 0.000000, 0.333333; */
  /* '<S2>:1:37' 0.333333, 0.333333; */
  /* '<S2>:1:38' -0.166667, 0.622008; */
  /* '<S2>:1:39' 0.166667, 0.622008; */
  /* '<S2>:1:40' -0.166667, 0.044658; */
  /* '<S2>:1:41' 0.166667, 0.044658; */
  /* '<S2>:1:42' -0.333333, 0.333333; */
  /* '<S2>:1:43' 0.000000, 0.333333; */
  /* '<S2>:1:44' -0.000000, -0.333333; */
  /* '<S2>:1:45' 0.333333, -0.333333; */
  /* '<S2>:1:46' -0.166667, -0.044658; */
  /* '<S2>:1:47' 0.166667, -0.044658; */
  /* '<S2>:1:48' -0.166667, -0.622008; */
  /* '<S2>:1:49' 0.166667, -0.622008; */
  /* '<S2>:1:50' -0.333333, -0.333333; */
  /* '<S2>:1:51' -0.000000, -0.333333; */
  /* '<S2>:1:52' 0.288675, -0.166667; */
  /* '<S2>:1:53' 0.622008, -0.166667; */
  /* '<S2>:1:54' 0.122008, 0.122008; */
  /* '<S2>:1:55' 0.455342, 0.122008; */
  /* '<S2>:1:56' 0.122008, -0.455342; */
  /* '<S2>:1:57' 0.455342, -0.455342; */
  /* '<S2>:1:58' -0.044658, -0.166667; */
  /* '<S2>:1:59' 0.288675, -0.166667; */
  /* '<S2>:1:60' -0.288675, -0.166667; */
  /* '<S2>:1:61' 0.044658, -0.166667; */
  /* '<S2>:1:62' -0.455342, 0.122008; */
  /* '<S2>:1:63' -0.122008, 0.122008; */
  /* '<S2>:1:64' -0.455342, -0.455342; */
  /* '<S2>:1:65' -0.122008, -0.455342; */
  /* '<S2>:1:66' -0.622008, -0.166667; */
  /* '<S2>:1:67' -0.288675, -0.166667; */
  /* '<S2>:1:68' -0.000000, -0.000000; */
  /* '<S2>:1:69' 0.333333, -0.000000; */
  /* '<S2>:1:70' -0.166667, 0.288675; */
  /* '<S2>:1:71' 0.166667, 0.288675; */
  /* '<S2>:1:72' -0.166667, -0.288675; */
  /* '<S2>:1:73' 0.166667, -0.288675; */
  /* '<S2>:1:74' -0.333333, 0.000000]); */
  /* 0.0,0.0; */
  /*  0.0, 0.0 */
  /* '<S2>:1:77' v_X_Y_pu = single([% 0.0, 0.0; */
  /* '<S2>:1:78' 0.333333,0; */
  /* '<S2>:1:79' -0.166667,-0.288675; */
  /* '<S2>:1:80' 0.166667,-0.288675; */
  /* '<S2>:1:81' -0.166667,0.288675; */
  /* '<S2>:1:82' 0.166667,0.288675; */
  /* '<S2>:1:83' -0.333333,0; */
  /* '<S2>:1:84' 0,0; */
  /* '<S2>:1:85' -0.288675,0.166667; */
  /* '<S2>:1:86' 0.0446580,0.166667; */
  /* '<S2>:1:87' -0.455342,-0.122008; */
  /* '<S2>:1:88' -0.122008,-0.122008; */
  /* '<S2>:1:89' -0.455342,0.455342; */
  /* '<S2>:1:90' -0.122008,0.455342; */
  /* '<S2>:1:91' -0.622008,0.166667; */
  /* '<S2>:1:92' -0.288675,0.166667; */
  /* '<S2>:1:93' 0.288675,0.166667; */
  /* '<S2>:1:94' 0.622008,0.166667; */
  /* '<S2>:1:95' 0.122008,-0.122008; */
  /* '<S2>:1:96' 0.455342,-0.122008; */
  /* '<S2>:1:97' 0.122008,0.455342; */
  /* '<S2>:1:98' 0.455342,0.455342; */
  /* '<S2>:1:99' -0.0446580,0.166667; */
  /* '<S2>:1:100' 0.288675,0.166667; */
  /* '<S2>:1:101' 0,0.333333; */
  /* '<S2>:1:102' 0.333333,0.333333; */
  /* '<S2>:1:103' -0.166667,0.0446580; */
  /* '<S2>:1:104' 0.166667,0.0446580; */
  /* '<S2>:1:105' -0.166667,0.622008; */
  /* '<S2>:1:106' 0.166667,0.622008; */
  /* '<S2>:1:107' -0.333333,0.333333; */
  /* '<S2>:1:108' 0,0.333333;0,-0.333333; */
  /* '<S2>:1:109' 0.333333,-0.333333; */
  /* '<S2>:1:110' -0.166667,-0.622008; */
  /* '<S2>:1:111' 0.166667,-0.622008; */
  /* '<S2>:1:112' -0.166667,-0.0446580; */
  /* '<S2>:1:113' 0.166667,-0.0446580; */
  /* '<S2>:1:114' -0.333333,-0.333333; */
  /* '<S2>:1:115' 0,-0.333333; */
  /* '<S2>:1:116' -0.288675,-0.166667; */
  /* '<S2>:1:117' 0.0446580,-0.166667; */
  /* '<S2>:1:118' -0.455342,-0.455342; */
  /* '<S2>:1:119' -0.122008,-0.455342; */
  /* '<S2>:1:120' -0.455342,0.122008; */
  /* '<S2>:1:121' -0.122008,0.122008; */
  /* '<S2>:1:122' -0.622008,-0.166667; */
  /* '<S2>:1:123' -0.288675,-0.166667; */
  /* '<S2>:1:124' 0.288675,-0.166667; */
  /* '<S2>:1:125' 0.622008,-0.166667; */
  /* '<S2>:1:126' 0.122008,-0.455342; */
  /* '<S2>:1:127' 0.455342,-0.455342; */
  /* '<S2>:1:128' 0.122008,0.122008; */
  /* '<S2>:1:129' 0.455342,0.122008; */
  /* '<S2>:1:130' -0.0446580,-0.166667; */
  /* '<S2>:1:131' 0.288675,-0.166667; */
  /* '<S2>:1:132' 0,0;0.333333,0; */
  /* '<S2>:1:133' -0.166667,-0.288675; */
  /* '<S2>:1:134' 0.166667,-0.288675; */
  /* '<S2>:1:135' -0.166667,0.288675; */
  /* '<S2>:1:136' 0.166667,0.288675; */
  /* '<S2>:1:137' -0.333333,0]); */
  /*  0.0, 0.0; */
  /*  0.0, 0.0 */
  /* '<S2>:1:141' vd_1_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_1(idx_opt),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(idx_opt),2) * sin_angle); */
  /* '<S2>:1:142' vq_1_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_1(idx_opt),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(idx_opt),2) * cos_angle); */
  /* '<S2>:1:143' vx_1_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_1(idx_opt),1) * cos_angle + v_X_Y_pu(act_sw_1(idx_opt),2) * -sin_angle); */
  /* '<S2>:1:144' vy_1_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_1(idx_opt),1) * sin_angle + v_X_Y_pu(act_sw_1(idx_opt),2) * cos_angle); */
  /* '<S2>:1:146' vd_2_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_2(idx_opt),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(idx_opt),2) * sin_angle); */
  /* '<S2>:1:147' vq_2_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_2(idx_opt),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(idx_opt),2) * cos_angle); */
  /* '<S2>:1:148' vx_2_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_2(idx_opt),1) * cos_angle + v_X_Y_pu(act_sw_2(idx_opt),2) * -sin_angle); */
  /* '<S2>:1:149' vy_2_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_2(idx_opt),1) * sin_angle + v_X_Y_pu(act_sw_2(idx_opt),2) * cos_angle); */
  /* '<S2>:1:151' vd_3_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_3(idx_opt),1) *  cos_angle + v_alpha_beta_pu(act_sw_3(idx_opt),2) * sin_angle); */
  /* '<S2>:1:152' vq_3_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_3(idx_opt),1) * -sin_angle + v_alpha_beta_pu(act_sw_3(idx_opt),2) * cos_angle); */
  /* '<S2>:1:153' vx_3_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_3(idx_opt),1) * cos_angle + v_X_Y_pu(act_sw_3(idx_opt),2) * -sin_angle); */
  /* '<S2>:1:154' vy_3_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_3(idx_opt),1) * sin_angle + v_X_Y_pu(act_sw_3(idx_opt),2) * cos_angle); */
  /* '<S2>:1:156' vd_4_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_4(idx_opt),1) *  cos_angle + v_alpha_beta_pu(act_sw_4(idx_opt),2) * sin_angle); */
  /* '<S2>:1:157' vq_4_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_4(idx_opt),1) * -sin_angle + v_alpha_beta_pu(act_sw_4(idx_opt),2) * cos_angle); */
  /* '<S2>:1:158' vx_4_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_4(idx_opt),1) * cos_angle + v_X_Y_pu(act_sw_4(idx_opt),2) * -sin_angle); */
  /* '<S2>:1:159' vy_4_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_4(idx_opt),1) * sin_angle + v_X_Y_pu(act_sw_4(idx_opt),2) * cos_angle); */
  /* '<S2>:1:161' vd_5_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_5(idx_opt),1) *  cos_angle + v_alpha_beta_pu(act_sw_5(idx_opt),2) * sin_angle); */
  /* '<S2>:1:162' vq_5_idx_pu = v_DC_pu * (v_alpha_beta_pu(act_sw_5(idx_opt),1) * -sin_angle + v_alpha_beta_pu(act_sw_5(idx_opt),2) * cos_angle); */
  /* '<S2>:1:163' vx_5_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_5(idx_opt),1) * cos_angle + v_X_Y_pu(act_sw_5(idx_opt),2) * -sin_angle); */
  /* '<S2>:1:164' vy_5_idx_pu = v_DC_pu * (v_X_Y_pu(act_sw_5(idx_opt),1) * sin_angle + v_X_Y_pu(act_sw_5(idx_opt),2) * cos_angle); */
  /* '<S2>:1:166' v_1_idx_pu = [vd_1_idx_pu; vq_1_idx_pu; vx_1_idx_pu; vy_1_idx_pu]; */
  rtDW->iy = rtDW->act_sw_1[rtDW->sector_ref - 1];
  rtDW->x = v_alpha_beta_pu[rtDW->iy - 1];
  rtDW->w6theta_el = v_alpha_beta_pu[rtDW->iy + 61];
  rtDW->v_1_idx_pu[0] = (rtDW->x * rtDW->SinCos1_o2 + rtDW->w6theta_el *
    rtDW->SinCos1_o1) * rtU->v_DC_pu;
  rtDW->v_1_idx_pu[1] = (rtDW->x * -rtDW->SinCos1_o1 + rtDW->w6theta_el *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->x = v_X_Y_pu[rtDW->iy - 1];
  rtDW->w6theta_el = v_X_Y_pu[rtDW->iy + 61];
  rtDW->v_1_idx_pu[2] = (rtDW->x * rtDW->SinCos1_o2 + rtDW->w6theta_el *
    -rtDW->SinCos1_o1) * rtU->v_DC_pu;
  rtDW->v_1_idx_pu[3] = (rtDW->x * rtDW->SinCos1_o1 + rtDW->w6theta_el *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;

  /* '<S2>:1:167' v_2_idx_pu = [vd_2_idx_pu; vq_2_idx_pu; vx_2_idx_pu; vy_2_idx_pu]; */
  rtDW->iy = rtDW->act_sw_2[rtDW->sector_ref - 1];
  rtDW->x = v_alpha_beta_pu[rtDW->iy - 1];
  rtDW->w6theta_el = v_alpha_beta_pu[rtDW->iy + 61];
  rtDW->v_2_idx_pu[0] = (rtDW->x * rtDW->SinCos1_o2 + rtDW->w6theta_el *
    rtDW->SinCos1_o1) * rtU->v_DC_pu;
  rtDW->v_2_idx_pu[1] = (rtDW->x * -rtDW->SinCos1_o1 + rtDW->w6theta_el *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->x = v_X_Y_pu[rtDW->iy - 1];
  rtDW->w6theta_el = v_X_Y_pu[rtDW->iy + 61];
  rtDW->v_2_idx_pu[2] = (rtDW->x * rtDW->SinCos1_o2 + rtDW->w6theta_el *
    -rtDW->SinCos1_o1) * rtU->v_DC_pu;
  rtDW->v_2_idx_pu[3] = (rtDW->x * rtDW->SinCos1_o1 + rtDW->w6theta_el *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;

  /* '<S2>:1:168' v_3_idx_pu = [vd_3_idx_pu; vq_3_idx_pu; vx_3_idx_pu; vy_3_idx_pu]; */
  rtDW->iy = rtDW->act_sw_3[rtDW->sector_ref - 1];
  rtDW->x = v_alpha_beta_pu[rtDW->iy - 1];
  rtDW->w6theta_el = v_alpha_beta_pu[rtDW->iy + 61];
  rtDW->v_3_idx_pu[0] = (rtDW->x * rtDW->SinCos1_o2 + rtDW->w6theta_el *
    rtDW->SinCos1_o1) * rtU->v_DC_pu;
  rtDW->v_3_idx_pu[1] = (rtDW->x * -rtDW->SinCos1_o1 + rtDW->w6theta_el *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->x = v_X_Y_pu[rtDW->iy - 1];
  rtDW->w6theta_el = v_X_Y_pu[rtDW->iy + 61];
  rtDW->v_3_idx_pu[2] = (rtDW->x * rtDW->SinCos1_o2 + rtDW->w6theta_el *
    -rtDW->SinCos1_o1) * rtU->v_DC_pu;
  rtDW->v_3_idx_pu[3] = (rtDW->x * rtDW->SinCos1_o1 + rtDW->w6theta_el *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;

  /* '<S2>:1:169' v_4_idx_pu = [vd_4_idx_pu; vq_4_idx_pu; vx_4_idx_pu; vy_4_idx_pu]; */
  rtDW->iy = rtDW->act_sw_4[rtDW->sector_ref - 1];
  rtDW->x = v_alpha_beta_pu[rtDW->iy - 1];
  rtDW->w6theta_el = v_alpha_beta_pu[rtDW->iy + 61];
  rtDW->v_4_idx_pu[0] = (rtDW->x * rtDW->SinCos1_o2 + rtDW->w6theta_el *
    rtDW->SinCos1_o1) * rtU->v_DC_pu;
  rtDW->v_4_idx_pu[1] = (rtDW->x * -rtDW->SinCos1_o1 + rtDW->w6theta_el *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->x = v_X_Y_pu[rtDW->iy - 1];
  rtDW->w6theta_el = v_X_Y_pu[rtDW->iy + 61];
  rtDW->v_4_idx_pu[2] = (rtDW->x * rtDW->SinCos1_o2 + rtDW->w6theta_el *
    -rtDW->SinCos1_o1) * rtU->v_DC_pu;
  rtDW->v_4_idx_pu[3] = (rtDW->x * rtDW->SinCos1_o1 + rtDW->w6theta_el *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;

  /* '<S2>:1:170' v_5_idx_pu = [vd_5_idx_pu; vq_5_idx_pu; vx_5_idx_pu; vy_5_idx_pu]; */
  rtDW->iy = rtDW->act_sw_5[rtDW->sector_ref - 1];
  rtDW->x = v_alpha_beta_pu[rtDW->iy - 1];
  rtDW->w6theta_el = v_alpha_beta_pu[rtDW->iy + 61];
  rtDW->v_5_idx_pu[0] = (rtDW->x * rtDW->SinCos1_o2 + rtDW->w6theta_el *
    rtDW->SinCos1_o1) * rtU->v_DC_pu;
  rtDW->v_5_idx_pu[1] = (rtDW->x * -rtDW->SinCos1_o1 + rtDW->w6theta_el *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->x = v_X_Y_pu[rtDW->iy - 1];
  rtDW->w6theta_el = v_X_Y_pu[rtDW->iy + 61];
  rtDW->v_5_idx_pu[2] = (rtDW->x * rtDW->SinCos1_o2 + rtDW->w6theta_el *
    -rtDW->SinCos1_o1) * rtU->v_DC_pu;
  rtDW->v_5_idx_pu[3] = (rtDW->x * rtDW->SinCos1_o1 + rtDW->w6theta_el *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;

  /* MATLAB Function: '<S1>/state_space_mdl' incorporates:
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
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/i_xy_pu'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/phiPM_h'
   *  Inport: '<Root>/psiPM_h_pu'
   *  Inport: '<Root>/psi_pm_over_psiB'
   *  Inport: '<Root>/theta_el'
   */
  /* MATLAB Function 'uz_codegen/state_space_mdl': '<S8>:1' */
  /* '<S8>:1:3' A = [ -Ts_times_ZB_over_Ld*Rs_over_ZB            Ts_times_ZB_over_Ld*Lq_over_LB*w_e_pu   0                                      0                               0; */
  /* '<S8>:1:4'       -Ts_times_ZB_over_Lq*Ld_over_LB*w_e_pu    -Ts_times_ZB_over_Lq*Rs_over_ZB          0                                      0                               -Ts_times_ZB_over_Lq*psi_pm_over_psiB; */
  /* '<S8>:1:5'       0                                          0                                       -Ts_times_ZB_over_Lx*Rs_over_ZB        -Ly_over_LB*w_e_pu              0; */
  /* '<S8>:1:6'       0                                          0                                        Lx_over_LB*w_e_pu                     -Ts_times_ZB_over_Ly*Rs_over_ZB 0]; */
  rtDW->A[0] = -rtU->Ts_times_ZB_over_Ld * rtU->Rs_over_ZB;
  rtDW->A[4] = rtU->Ts_times_ZB_over_Ld * rtU->Lq_over_LB * rtU->omega_el_pu;
  rtDW->A[8] = 0.0F;
  rtDW->A[12] = 0.0F;
  rtDW->A[16] = 0.0F;
  rtDW->A[1] = -rtU->Ts_times_ZB_over_Lq * rtU->Ld_over_LB * rtU->omega_el_pu;
  rtDW->A[5] = -rtU->Ts_times_ZB_over_Lq * rtU->Rs_over_ZB;
  rtDW->A[9] = 0.0F;
  rtDW->A[13] = 0.0F;
  rtDW->A[17] = -rtU->Ts_times_ZB_over_Lq * rtU->psi_pm_over_psiB;
  rtDW->A[2] = 0.0F;
  rtDW->A[6] = 0.0F;
  rtDW->A[10] = -rtU->Ts_times_ZB_over_Lx * rtU->Rs_over_ZB;
  rtDW->A[14] = -rtU->Ly_over_LB * rtU->omega_el_pu;
  rtDW->A[18] = 0.0F;
  rtDW->A[3] = 0.0F;
  rtDW->A[7] = 0.0F;
  rtDW->A[11] = rtU->Lx_over_LB * rtU->omega_el_pu;
  rtDW->A[15] = -rtU->Ts_times_ZB_over_Ly * rtU->Rs_over_ZB;
  rtDW->A[19] = 0.0F;

  /* '<S8>:1:8' psiPM5 = psiPM_h_pu(1); */
  /* '<S8>:1:9' psiPM7 = psiPM_h_pu(2); */
  /* '<S8>:1:11' phi5 = phiPM_h(1); */
  /* '<S8>:1:12' phi7 = phiPM_h(2); */
  /*  w3theta_el = single(3*theta_el); */
  /* '<S8>:1:15' w6theta_el = single(6*theta_el); */
  rtDW->w6theta_el = 6.0F * rtU->theta_el;

  /*  w9theta_el = single(9*theta_el); */
  /*  w12theta_el = single(12*theta_el); */
  /* '<S8>:1:19' B = [Ts_times_ZB_over_Ld    0                       0                       0                       0; */
  /* '<S8>:1:20'      0                      Ts_times_ZB_over_Lq     0                       0                       0; */
  /* '<S8>:1:21'      0                      0                       Ts_times_ZB_over_Lx     0                       0; */
  /* '<S8>:1:22'      0                      0                       0                       Ts_times_ZB_over_Ly     0]; */
  rtDW->B_m[0] = rtU->Ts_times_ZB_over_Ld;
  rtDW->B_m[4] = 0.0F;
  rtDW->B_m[8] = 0.0F;
  rtDW->B_m[12] = 0.0F;
  rtDW->B_m[16] = 0.0F;
  rtDW->B_m[1] = 0.0F;
  rtDW->B_m[5] = rtU->Ts_times_ZB_over_Lq;
  rtDW->B_m[9] = 0.0F;
  rtDW->B_m[13] = 0.0F;
  rtDW->B_m[17] = 0.0F;
  rtDW->B_m[2] = 0.0F;
  rtDW->B_m[6] = 0.0F;
  rtDW->B_m[10] = rtU->Ts_times_ZB_over_Lx;
  rtDW->B_m[14] = 0.0F;
  rtDW->B_m[18] = 0.0F;
  rtDW->B_m[3] = 0.0F;
  rtDW->B_m[7] = 0.0F;
  rtDW->B_m[11] = 0.0F;
  rtDW->B_m[15] = rtU->Ts_times_ZB_over_Ly;
  rtDW->B_m[19] = 0.0F;

  /* '<S8>:1:24' C = [1   0   0   0; */
  /* '<S8>:1:25'      0   1   0   0; */
  /* '<S8>:1:26'      0   0   1   0; */
  /* '<S8>:1:27'      0   0   0   1]; */
  /* '<S8>:1:29' E = [    0; */
  /* '<S8>:1:30'          0; */
  /* '<S8>:1:31'          -w_e_pu*(psiPM5*sin(w6theta_el+phi5) - psiPM7*sin(w6theta_el+phi7)-psiPM5*6*sin(w6theta_el+phi5) - psiPM7*6*sin(w6theta_el+phi7)); */
  /* '<S8>:1:32'          -w_e_pu*(psiPM5*cos(w6theta_el+phi5) + psiPM7*cos(w6theta_el+phi7) + psiPM5*6*cos(w6theta_el+phi5) - psiPM7*6*cos(w6theta_el+phi7))]; */
  rtDW->x = rtDW->w6theta_el + rtU->phiPM_h[0];
  rtDW->SinCos1_o1 = sinf(rtDW->x);
  rtDW->w6theta_el += rtU->phiPM_h[1];
  rtDW->SinCos1_o2 = sinf(rtDW->w6theta_el);
  rtDW->x = cosf(rtDW->x);
  rtDW->w6theta_el = cosf(rtDW->w6theta_el);
  rtDW->E[0] = 0.0F;
  rtDW->E[1] = 0.0F;
  rtDW->E[2] = (((rtU->psiPM_h_pu[0] * rtDW->SinCos1_o1 - rtU->psiPM_h_pu[1] *
                  rtDW->SinCos1_o2) - rtU->psiPM_h_pu[0] * 6.0F *
                 rtDW->SinCos1_o1) - rtU->psiPM_h_pu[1] * 6.0F *
                rtDW->SinCos1_o2) * -rtU->omega_el_pu;
  rtDW->E[3] = (((rtU->psiPM_h_pu[0] * rtDW->x + rtU->psiPM_h_pu[1] *
                  rtDW->w6theta_el) + rtU->psiPM_h_pu[0] * 6.0F * rtDW->x) -
                rtU->psiPM_h_pu[1] * 6.0F * rtDW->w6theta_el) *
    -rtU->omega_el_pu;

  /* '<S8>:1:34' x0 = [id_pu; iq_pu; ix_pu; iy_pu; w_e_pu]; */
  rtDW->x0[0] = rtU->i_dq_pu[0];
  rtDW->x0[1] = rtU->i_dq_pu[1];
  rtDW->x0[2] = rtU->i_xy_pu[0];
  rtDW->x0[3] = rtU->i_xy_pu[1];
  rtDW->x0[4] = rtU->omega_el_pu;

  /* '<S8>:1:36' u0 = [0;0;0;0;0]; */
  /*  zero voltage applied */
  /* '<S8>:1:37' u1 = [v_1_pu(1); v_1_pu(2); v_1_pu(3); v_1_pu(4); 0]; */
  /*  first active vector */
  /* '<S8>:1:38' u2 = [v_2_pu(1); v_2_pu(2); v_2_pu(3); v_2_pu(4); 0]; */
  /*  second active vector */
  /* '<S8>:1:39' u3 = [v_3_pu(1); v_3_pu(2); v_3_pu(3); v_3_pu(4); 0]; */
  /*  third active vector */
  /* '<S8>:1:40' u4 = [v_4_pu(1); v_4_pu(2); v_4_pu(3); v_4_pu(4); 0]; */
  /*  fourth active vector */
  /* '<S8>:1:41' u5 = [v_5_pu(1); v_5_pu(2); v_5_pu(3); v_5_pu(4); 0]; */
  /*  fifth active vector */
  /*  calculate the gradients */
  /*  .*2 because we calculate current evolution only for half of the */
  /*  period and mirror it???  */
  /* '<S8>:1:46' switch HC_off_on */
  if (!rtU->HC_off_on) {
    rtDW->iy = 0;
  } else if (rtU->HC_off_on) {
    rtDW->iy = 1;
  } else {
    rtDW->iy = -1;
  }

  switch (rtDW->iy) {
   case 0:
    /* '<S8>:1:47' case false */
    /* '<S8>:1:48' m0 = C*(A*x0+B*u0).*2; */
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->E_c[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->E_c[rtDW->iy] += rtDW->A[(rtDW->b_j << 2) + rtDW->iy] * rtDW->
          x0[rtDW->b_j];
      }

      rtDW->E_cv[rtDW->iy] = rtDW->E_c[rtDW->iy];
    }

    /* '<S8>:1:49' m1 = C*(A*x0+B*u1).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_1_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_1_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_1_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_1_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->m6[rtDW->iy] = ((real32_T)b[rtDW->iy + 12] * rtDW->E_cv[3] +
                            ((real32_T)b[rtDW->iy + 8] * rtDW->E_cv[2] +
        ((real32_T)b[rtDW->iy + 4] * rtDW->E_cv[1] + (real32_T)b[rtDW->iy] *
         rtDW->E_cv[0]))) * 2.0F;
      rtDW->E_c[rtDW->iy] = 0.0F;
      rtDW->B_b[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->i = (rtDW->b_j << 2) + rtDW->iy;
        rtDW->E_c[rtDW->iy] += rtDW->A[rtDW->i] * rtDW->x0[rtDW->b_j];
        rtDW->B_b[rtDW->iy] += rtDW->B_m[rtDW->i] * rtDW->rtb_v_1_idx_pu_k
          [rtDW->b_j];
      }

      rtDW->A_p[rtDW->iy] = rtDW->E_c[rtDW->iy] + rtDW->B_b[rtDW->iy];
    }

    /* '<S8>:1:50' m2 = C*(A*x0+B*u2).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_2_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_2_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_2_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_2_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->m1[rtDW->iy] = ((real32_T)b[rtDW->iy + 12] * rtDW->A_p[3] +
                            ((real32_T)b[rtDW->iy + 8] * rtDW->A_p[2] +
        ((real32_T)b[rtDW->iy + 4] * rtDW->A_p[1] + (real32_T)b[rtDW->iy] *
         rtDW->A_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->iy] = 0.0F;
      rtDW->B_b[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->i = (rtDW->b_j << 2) + rtDW->iy;
        rtDW->E_c[rtDW->iy] += rtDW->A[rtDW->i] * rtDW->x0[rtDW->b_j];
        rtDW->B_b[rtDW->iy] += rtDW->B_m[rtDW->i] * rtDW->rtb_v_1_idx_pu_k
          [rtDW->b_j];
      }

      rtDW->E_cv[rtDW->iy] = rtDW->E_c[rtDW->iy] + rtDW->B_b[rtDW->iy];
    }

    /* '<S8>:1:51' m3 = C*(A*x0+B*u3).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_3_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_3_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_3_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_3_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_1_idx_pu[rtDW->iy] = ((real32_T)b[rtDW->iy + 12] * rtDW->E_cv[3] +
        ((real32_T)b[rtDW->iy + 8] * rtDW->E_cv[2] + ((real32_T)b[rtDW->iy + 4] *
        rtDW->E_cv[1] + (real32_T)b[rtDW->iy] * rtDW->E_cv[0]))) * 2.0F;
      rtDW->E_c[rtDW->iy] = 0.0F;
      rtDW->B_b[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->i = (rtDW->b_j << 2) + rtDW->iy;
        rtDW->E_c[rtDW->iy] += rtDW->A[rtDW->i] * rtDW->x0[rtDW->b_j];
        rtDW->B_b[rtDW->iy] += rtDW->B_m[rtDW->i] * rtDW->rtb_v_1_idx_pu_k
          [rtDW->b_j];
      }

      rtDW->A_p[rtDW->iy] = rtDW->E_c[rtDW->iy] + rtDW->B_b[rtDW->iy];
    }

    /* '<S8>:1:52' m4 = C*(A*x0+B*u4).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_4_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_4_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_4_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_4_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_2_idx_pu[rtDW->iy] = ((real32_T)b[rtDW->iy + 12] * rtDW->A_p[3] +
        ((real32_T)b[rtDW->iy + 8] * rtDW->A_p[2] + ((real32_T)b[rtDW->iy + 4] *
        rtDW->A_p[1] + (real32_T)b[rtDW->iy] * rtDW->A_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->iy] = 0.0F;
      rtDW->B_b[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->i = (rtDW->b_j << 2) + rtDW->iy;
        rtDW->E_c[rtDW->iy] += rtDW->A[rtDW->i] * rtDW->x0[rtDW->b_j];
        rtDW->B_b[rtDW->iy] += rtDW->B_m[rtDW->i] * rtDW->rtb_v_1_idx_pu_k
          [rtDW->b_j];
      }

      rtDW->E_cv[rtDW->iy] = rtDW->E_c[rtDW->iy] + rtDW->B_b[rtDW->iy];
    }

    /* '<S8>:1:53' m5 = C*(A*x0+B*u5).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_5_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_5_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_5_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_5_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_3_idx_pu[rtDW->iy] = ((real32_T)b[rtDW->iy + 12] * rtDW->E_cv[3] +
        ((real32_T)b[rtDW->iy + 8] * rtDW->E_cv[2] + ((real32_T)b[rtDW->iy + 4] *
        rtDW->E_cv[1] + (real32_T)b[rtDW->iy] * rtDW->E_cv[0]))) * 2.0F;
      rtDW->E_c[rtDW->iy] = 0.0F;
      rtDW->B_b[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->i = (rtDW->b_j << 2) + rtDW->iy;
        rtDW->E_c[rtDW->iy] += rtDW->A[rtDW->i] * rtDW->x0[rtDW->b_j];
        rtDW->B_b[rtDW->iy] += rtDW->B_m[rtDW->i] * rtDW->rtb_v_1_idx_pu_k
          [rtDW->b_j];
      }

      rtDW->A_p[rtDW->iy] = rtDW->E_c[rtDW->iy] + rtDW->B_b[rtDW->iy];
    }

    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_4_idx_pu[rtDW->iy] = ((real32_T)b[rtDW->iy + 12] * rtDW->A_p[3] +
        ((real32_T)b[rtDW->iy + 8] * rtDW->A_p[2] + ((real32_T)b[rtDW->iy + 4] *
        rtDW->A_p[1] + (real32_T)b[rtDW->iy] * rtDW->A_p[0]))) * 2.0F;
    }

    /* '<S8>:1:54' m6 = m0; */
    break;

   case 1:
    /* '<S8>:1:55' case true */
    /* '<S8>:1:56' m0 = C*(A*x0+B*u0+E).*2; */
    for (rtDW->iy = 0; rtDW->iy < 16; rtDW->iy++) {
      rtDW->lam[rtDW->iy] = b[rtDW->iy];
    }

    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->E_c[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->E_c[rtDW->iy] += rtDW->A[(rtDW->b_j << 2) + rtDW->iy] * rtDW->
          x0[rtDW->b_j];
      }

      rtDW->E_cv[rtDW->iy] = rtDW->E_c[rtDW->iy] + rtDW->E[rtDW->iy];
    }

    /* '<S8>:1:57' m1 = C*(A*x0+B*u1+E).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_1_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_1_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_1_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_1_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->m6[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->E_cv[3] +
                            (rtDW->lam[rtDW->iy + 8] * rtDW->E_cv[2] +
        (rtDW->lam[rtDW->iy + 4] * rtDW->E_cv[1] + rtDW->lam[rtDW->iy] *
         rtDW->E_cv[0]))) * 2.0F;
      rtDW->E_c[rtDW->iy] = 0.0F;
      rtDW->B_b[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->i = (rtDW->b_j << 2) + rtDW->iy;
        rtDW->E_c[rtDW->iy] += rtDW->A[rtDW->i] * rtDW->x0[rtDW->b_j];
        rtDW->B_b[rtDW->iy] += rtDW->B_m[rtDW->i] * rtDW->rtb_v_1_idx_pu_k
          [rtDW->b_j];
      }

      rtDW->A_p[rtDW->iy] = (rtDW->E_c[rtDW->iy] + rtDW->B_b[rtDW->iy]) +
        rtDW->E[rtDW->iy];
    }

    /* '<S8>:1:58' m2 = C*(A*x0+B*u2+E).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_2_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_2_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_2_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_2_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->m1[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->A_p[3] + (rtDW->
        lam[rtDW->iy + 8] * rtDW->A_p[2] + (rtDW->lam[rtDW->iy + 4] * rtDW->A_p
        [1] + rtDW->lam[rtDW->iy] * rtDW->A_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->iy] = 0.0F;
      rtDW->B_b[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->i = (rtDW->b_j << 2) + rtDW->iy;
        rtDW->E_c[rtDW->iy] += rtDW->A[rtDW->i] * rtDW->x0[rtDW->b_j];
        rtDW->B_b[rtDW->iy] += rtDW->B_m[rtDW->i] * rtDW->rtb_v_1_idx_pu_k
          [rtDW->b_j];
      }

      rtDW->E_cv[rtDW->iy] = (rtDW->E_c[rtDW->iy] + rtDW->B_b[rtDW->iy]) +
        rtDW->E[rtDW->iy];
    }

    /* '<S8>:1:59' m3 = C*(A*x0+B*u3+E).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_3_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_3_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_3_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_3_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_1_idx_pu[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->E_cv[3] +
        (rtDW->lam[rtDW->iy + 8] * rtDW->E_cv[2] + (rtDW->lam[rtDW->iy + 4] *
        rtDW->E_cv[1] + rtDW->lam[rtDW->iy] * rtDW->E_cv[0]))) * 2.0F;
      rtDW->E_c[rtDW->iy] = 0.0F;
      rtDW->B_b[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->i = (rtDW->b_j << 2) + rtDW->iy;
        rtDW->E_c[rtDW->iy] += rtDW->A[rtDW->i] * rtDW->x0[rtDW->b_j];
        rtDW->B_b[rtDW->iy] += rtDW->B_m[rtDW->i] * rtDW->rtb_v_1_idx_pu_k
          [rtDW->b_j];
      }

      rtDW->A_p[rtDW->iy] = (rtDW->E_c[rtDW->iy] + rtDW->B_b[rtDW->iy]) +
        rtDW->E[rtDW->iy];
    }

    /* '<S8>:1:60' m4 = C*(A*x0+B*u4+E).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_4_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_4_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_4_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_4_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_2_idx_pu[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->A_p[3] +
        (rtDW->lam[rtDW->iy + 8] * rtDW->A_p[2] + (rtDW->lam[rtDW->iy + 4] *
        rtDW->A_p[1] + rtDW->lam[rtDW->iy] * rtDW->A_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->iy] = 0.0F;
      rtDW->B_b[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->i = (rtDW->b_j << 2) + rtDW->iy;
        rtDW->E_c[rtDW->iy] += rtDW->A[rtDW->i] * rtDW->x0[rtDW->b_j];
        rtDW->B_b[rtDW->iy] += rtDW->B_m[rtDW->i] * rtDW->rtb_v_1_idx_pu_k
          [rtDW->b_j];
      }

      rtDW->E_cv[rtDW->iy] = (rtDW->E_c[rtDW->iy] + rtDW->B_b[rtDW->iy]) +
        rtDW->E[rtDW->iy];
    }

    /* '<S8>:1:61' m5 = C*(A*x0+B*u5+E).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_5_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_5_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_5_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_5_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_3_idx_pu[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->E_cv[3] +
        (rtDW->lam[rtDW->iy + 8] * rtDW->E_cv[2] + (rtDW->lam[rtDW->iy + 4] *
        rtDW->E_cv[1] + rtDW->lam[rtDW->iy] * rtDW->E_cv[0]))) * 2.0F;
      rtDW->E_c[rtDW->iy] = 0.0F;
      rtDW->B_b[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->i = (rtDW->b_j << 2) + rtDW->iy;
        rtDW->E_c[rtDW->iy] += rtDW->A[rtDW->i] * rtDW->x0[rtDW->b_j];
        rtDW->B_b[rtDW->iy] += rtDW->B_m[rtDW->i] * rtDW->rtb_v_1_idx_pu_k
          [rtDW->b_j];
      }

      rtDW->A_p[rtDW->iy] = (rtDW->E_c[rtDW->iy] + rtDW->B_b[rtDW->iy]) +
        rtDW->E[rtDW->iy];
    }

    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_4_idx_pu[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->A_p[3] +
        (rtDW->lam[rtDW->iy + 8] * rtDW->A_p[2] + (rtDW->lam[rtDW->iy + 4] *
        rtDW->A_p[1] + rtDW->lam[rtDW->iy] * rtDW->A_p[0]))) * 2.0F;
    }

    /* '<S8>:1:62' m6 = m0; */
    break;

   default:
    /* '<S8>:1:63' otherwise */
    /* '<S8>:1:64' m0 = C*(A*x0+B*u0).*2; */
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->E[rtDW->iy] = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->E[rtDW->iy] += rtDW->A[(rtDW->b_j << 2) + rtDW->iy] * rtDW->
          x0[rtDW->b_j];
      }
    }

    for (rtDW->iy = 0; rtDW->iy < 16; rtDW->iy++) {
      rtDW->lam[rtDW->iy] = b[rtDW->iy];
    }

    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->E_c[rtDW->iy] = rtDW->E[rtDW->iy];
    }

    /* '<S8>:1:65' m1 = C*(A*x0+B*u1).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_1_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_1_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_1_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_1_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->m6[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->E_c[3] + (rtDW->
        lam[rtDW->iy + 8] * rtDW->E_c[2] + (rtDW->lam[rtDW->iy + 4] * rtDW->E_c
        [1] + rtDW->lam[rtDW->iy] * rtDW->E_c[0]))) * 2.0F;
      rtDW->SinCos1_o1 = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->SinCos1_o1 += rtDW->B_m[(rtDW->b_j << 2) + rtDW->iy] *
          rtDW->rtb_v_1_idx_pu_k[rtDW->b_j];
      }

      rtDW->E_cv[rtDW->iy] = rtDW->E[rtDW->iy] + rtDW->SinCos1_o1;
    }

    /* '<S8>:1:66' m2 = C*(A*x0+B*u2).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_2_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_2_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_2_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_2_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->m1[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->E_cv[3] +
                            (rtDW->lam[rtDW->iy + 8] * rtDW->E_cv[2] +
        (rtDW->lam[rtDW->iy + 4] * rtDW->E_cv[1] + rtDW->lam[rtDW->iy] *
         rtDW->E_cv[0]))) * 2.0F;
      rtDW->SinCos1_o1 = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->SinCos1_o1 += rtDW->B_m[(rtDW->b_j << 2) + rtDW->iy] *
          rtDW->rtb_v_1_idx_pu_k[rtDW->b_j];
      }

      rtDW->E_c[rtDW->iy] = rtDW->E[rtDW->iy] + rtDW->SinCos1_o1;
    }

    /* '<S8>:1:67' m3 = C*(A*x0+B*u3).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_3_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_3_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_3_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_3_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_1_idx_pu[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->E_c[3] +
        (rtDW->lam[rtDW->iy + 8] * rtDW->E_c[2] + (rtDW->lam[rtDW->iy + 4] *
        rtDW->E_c[1] + rtDW->lam[rtDW->iy] * rtDW->E_c[0]))) * 2.0F;
      rtDW->SinCos1_o1 = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->SinCos1_o1 += rtDW->B_m[(rtDW->b_j << 2) + rtDW->iy] *
          rtDW->rtb_v_1_idx_pu_k[rtDW->b_j];
      }

      rtDW->E_cv[rtDW->iy] = rtDW->E[rtDW->iy] + rtDW->SinCos1_o1;
    }

    /* '<S8>:1:68' m4 = C*(A*x0+B*u4).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_4_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_4_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_4_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_4_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_2_idx_pu[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->E_cv[3] +
        (rtDW->lam[rtDW->iy + 8] * rtDW->E_cv[2] + (rtDW->lam[rtDW->iy + 4] *
        rtDW->E_cv[1] + rtDW->lam[rtDW->iy] * rtDW->E_cv[0]))) * 2.0F;
      rtDW->SinCos1_o1 = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->SinCos1_o1 += rtDW->B_m[(rtDW->b_j << 2) + rtDW->iy] *
          rtDW->rtb_v_1_idx_pu_k[rtDW->b_j];
      }

      rtDW->E_c[rtDW->iy] = rtDW->E[rtDW->iy] + rtDW->SinCos1_o1;
    }

    /* '<S8>:1:69' m5 = C*(A*x0+B*u5).*2; */
    rtDW->rtb_v_1_idx_pu_k[0] = rtDW->v_5_idx_pu[0];
    rtDW->rtb_v_1_idx_pu_k[1] = rtDW->v_5_idx_pu[1];
    rtDW->rtb_v_1_idx_pu_k[2] = rtDW->v_5_idx_pu[2];
    rtDW->rtb_v_1_idx_pu_k[3] = rtDW->v_5_idx_pu[3];
    rtDW->rtb_v_1_idx_pu_k[4] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_3_idx_pu[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->E_c[3] +
        (rtDW->lam[rtDW->iy + 8] * rtDW->E_c[2] + (rtDW->lam[rtDW->iy + 4] *
        rtDW->E_c[1] + rtDW->lam[rtDW->iy] * rtDW->E_c[0]))) * 2.0F;
      rtDW->SinCos1_o1 = 0.0F;
      for (rtDW->b_j = 0; rtDW->b_j < 5; rtDW->b_j++) {
        rtDW->SinCos1_o1 += rtDW->B_m[(rtDW->b_j << 2) + rtDW->iy] *
          rtDW->rtb_v_1_idx_pu_k[rtDW->b_j];
      }

      rtDW->E_cv[rtDW->iy] = rtDW->E[rtDW->iy] + rtDW->SinCos1_o1;
    }

    for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
      rtDW->v_4_idx_pu[rtDW->iy] = (rtDW->lam[rtDW->iy + 12] * rtDW->E_cv[3] +
        (rtDW->lam[rtDW->iy + 8] * rtDW->E_cv[2] + (rtDW->lam[rtDW->iy + 4] *
        rtDW->E_cv[1] + rtDW->lam[rtDW->iy] * rtDW->E_cv[0]))) * 2.0F;
    }

    /* '<S8>:1:70' m6 = m0; */
    break;
  }

  /* Delay: '<S1>/Delay1' */
  if (rtDW->icLoad) {
    for (rtDW->i = 0; rtDW->i < 7; rtDW->i++) {
      rtDW->Delay1_DSTATE[rtDW->i] = 0.14F;
    }
  }

  /* Delay: '<S1>/Delay3' */
  if (rtDW->icLoad_a) {
    rtDW->Delay3_DSTATE[0] = 0.0F;
    rtDW->Delay3_DSTATE[1] = 0.0F;
    rtDW->Delay3_DSTATE[2] = 0.0F;
    rtDW->Delay3_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay4' */
  if (rtDW->icLoad_f) {
    rtDW->Delay4_DSTATE[0] = 0.0F;
    rtDW->Delay4_DSTATE[1] = 0.0F;
    rtDW->Delay4_DSTATE[2] = 0.0F;
    rtDW->Delay4_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay5' */
  if (rtDW->icLoad_k) {
    rtDW->Delay5_DSTATE[0] = 0.0F;
    rtDW->Delay5_DSTATE[1] = 0.0F;
    rtDW->Delay5_DSTATE[2] = 0.0F;
    rtDW->Delay5_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay6' */
  if (rtDW->icLoad_n) {
    rtDW->Delay6_DSTATE[0] = 0.0F;
    rtDW->Delay6_DSTATE[1] = 0.0F;
    rtDW->Delay6_DSTATE[2] = 0.0F;
    rtDW->Delay6_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay7' */
  if (rtDW->icLoad_l) {
    rtDW->Delay7_DSTATE[0] = 0.0F;
    rtDW->Delay7_DSTATE[1] = 0.0F;
    rtDW->Delay7_DSTATE[2] = 0.0F;
    rtDW->Delay7_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay8' */
  if (rtDW->icLoad_ly) {
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
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/i_xy_pu'
   */
  /* MATLAB Function 'uz_codegen/delay_compensation_currents': '<S4>:1' */
  /* '<S4>:1:3' i_t0 = [id0 iq0 ix0 iy0]'; */
  /* '<S4>:1:5' m_opt = [m0, m1, m2, m3, m4, m5, m0]; */
  /* delay compensation */
  /* '<S4>:1:7' i_t0_delay_comp = i_t0 + 0.5 * m_opt * x_opt; */
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
  rtDW->E_c[0] = rtU->i_dq_pu[0];
  rtDW->E_c[1] = rtU->i_dq_pu[1];
  rtDW->E_c[2] = rtU->i_xy_pu[0];
  rtDW->E_c[3] = rtU->i_xy_pu[1];
  for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
    rtDW->E_cv[rtDW->iy] = 0.0F;
    for (rtDW->b_j = 0; rtDW->b_j < 7; rtDW->b_j++) {
      rtDW->E_cv[rtDW->iy] += rtDW->r[(rtDW->b_j << 2) + rtDW->iy] *
        rtDW->Delay1_DSTATE[rtDW->b_j];
    }

    rtDW->v_5_idx_pu[rtDW->iy] = rtDW->E_c[rtDW->iy] + rtDW->E_cv[rtDW->iy];
  }

  /* End of MATLAB Function: '<S1>/delay_compensation_currents' */

  /* MATLAB Function: '<S1>/formulate_qp' incorporates:
   *  Inport: '<Root>/i_d_ref_pu'
   *  Inport: '<Root>/i_q_ref_pu'
   *  Inport: '<Root>/i_x_ref_pu'
   *  Inport: '<Root>/i_y_ref_pu'
   *  Inport: '<Root>/lambda'
   *  MATLAB Function: '<S1>/state_space_mdl'
   */
  /* MATLAB Function 'uz_codegen/formulate_qp': '<S5>:1' */
  /* '<S5>:1:4' lam = [ lambda  0       0       0; */
  /* '<S5>:1:5'         0       lambda  0       0; */
  /* '<S5>:1:6'         0       0       lambda       0; */
  /* '<S5>:1:7'         0       0       0       lambda]; */
  rtDW->lam[0] = rtU->lambda;
  rtDW->lam[4] = 0.0F;
  rtDW->lam[8] = 0.0F;
  rtDW->lam[12] = 0.0F;
  rtDW->lam[1] = 0.0F;
  rtDW->lam[5] = rtU->lambda;
  rtDW->lam[9] = 0.0F;
  rtDW->lam[13] = 0.0F;
  rtDW->lam[2] = 0.0F;
  rtDW->lam[6] = 0.0F;
  rtDW->lam[10] = rtU->lambda;
  rtDW->lam[14] = 0.0F;
  rtDW->lam[3] = 0.0F;
  rtDW->lam[7] = 0.0F;
  rtDW->lam[11] = 0.0F;
  rtDW->lam[15] = rtU->lambda;

  /* '<S5>:1:9' i_t0 = [id0 iq0 ix0 iy0]'; */
  /* '<S5>:1:10' i_ref = [id_ref iq_ref ix_ref iy_ref]'; */
  /*  e_i = i_ref - i_t0; */
  /* '<S5>:1:12' e_i = i_ref - i_delay; */
  rtDW->E[0] = rtU->i_d_ref_pu - rtDW->v_5_idx_pu[0];
  rtDW->E[1] = rtU->i_q_ref_pu - rtDW->v_5_idx_pu[1];
  rtDW->E[2] = rtU->i_x_ref_pu - rtDW->v_5_idx_pu[2];
  rtDW->E[3] = rtU->i_y_ref_pu - rtDW->v_5_idx_pu[3];

  /* '<S5>:1:14' r = [e_i; e_i; e_i; e_i; e_i; e_i; lam*e_i]; */
  /* '<S5>:1:16' zer = zeros(4,1); */
  /* '<S5>:1:17' m0_lam = lam*m0; */
  /* '<S5>:1:18' m1_lam = lam*m1; */
  /* '<S5>:1:19' m2_lam = lam*m2; */
  /* '<S5>:1:20' m3_lam = lam*m3; */
  /* '<S5>:1:21' m4_lam = lam*m4; */
  /* '<S5>:1:22' m5_lam = lam*m5; */
  /* '<S5>:1:23' m6_lam = m0_lam; */
  /* '<S5>:1:25' M = [m0     zer     zer     zer     zer     zer     zer; */
  /* '<S5>:1:26'      m0     m1      zer     zer     zer     zer     zer; */
  /* '<S5>:1:27'      m0     m1      m2      zer     zer     zer     zer; */
  /* '<S5>:1:28'      m0     m1      m2      m3      zer     zer     zer; */
  /* '<S5>:1:29'      m0     m1      m2      m3      m4      zer     zer; */
  /* '<S5>:1:30'      m0     m1      m2      m3      m4      m5      zer; */
  /* '<S5>:1:31'      m0_lam m1_lam  m2_lam  m3_lam  m4_lam  m5_lam  m6_lam]; */
  for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
    rtDW->r[rtDW->iy] = rtDW->E[rtDW->iy];
    rtDW->r[rtDW->iy + 4] = rtDW->E[rtDW->iy];
    rtDW->r[rtDW->iy + 8] = rtDW->E[rtDW->iy];
    rtDW->r[rtDW->iy + 12] = rtDW->E[rtDW->iy];
    rtDW->r[rtDW->iy + 16] = rtDW->E[rtDW->iy];
    rtDW->r[rtDW->iy + 20] = rtDW->E[rtDW->iy];
    rtDW->x = rtDW->lam[rtDW->iy + 4];
    rtDW->w6theta_el = rtDW->lam[rtDW->iy + 8];
    rtDW->q = rtDW->lam[rtDW->iy + 12];
    rtDW->r[rtDW->iy + 24] = rtDW->q * rtDW->E[3] + (rtDW->w6theta_el * rtDW->E
      [2] + (rtDW->x * rtDW->E[1] + rtDW->lam[rtDW->iy] * rtDW->E[0]));
    rtDW->SinCos1_o1 = rtDW->lam[rtDW->iy];
    rtDW->SinCos1_o2 = rtDW->q * rtDW->m6[3] + (rtDW->w6theta_el * rtDW->m6[2] +
      (rtDW->x * rtDW->m6[1] + rtDW->SinCos1_o1 * rtDW->m6[0]));
    rtDW->M[rtDW->iy] = rtDW->m6[rtDW->iy];
    rtDW->M[rtDW->iy + 28] = 0.0F;
    rtDW->M[rtDW->iy + 56] = 0.0F;
    rtDW->M[rtDW->iy + 84] = 0.0F;
    rtDW->M[rtDW->iy + 112] = 0.0F;
    rtDW->M[rtDW->iy + 140] = 0.0F;
    rtDW->M[rtDW->iy + 168] = 0.0F;
    rtDW->M[rtDW->iy + 4] = rtDW->m6[rtDW->iy];
    rtDW->M[rtDW->iy + 32] = rtDW->m1[rtDW->iy];
    rtDW->M[rtDW->iy + 60] = 0.0F;
    rtDW->M[rtDW->iy + 88] = 0.0F;
    rtDW->M[rtDW->iy + 116] = 0.0F;
    rtDW->M[rtDW->iy + 144] = 0.0F;
    rtDW->M[rtDW->iy + 172] = 0.0F;
    rtDW->M[rtDW->iy + 8] = rtDW->m6[rtDW->iy];
    rtDW->M[rtDW->iy + 36] = rtDW->m1[rtDW->iy];
    rtDW->M[rtDW->iy + 64] = rtDW->v_1_idx_pu[rtDW->iy];
    rtDW->M[rtDW->iy + 92] = 0.0F;
    rtDW->M[rtDW->iy + 120] = 0.0F;
    rtDW->M[rtDW->iy + 148] = 0.0F;
    rtDW->M[rtDW->iy + 176] = 0.0F;
    rtDW->M[rtDW->iy + 12] = rtDW->m6[rtDW->iy];
    rtDW->M[rtDW->iy + 40] = rtDW->m1[rtDW->iy];
    rtDW->M[rtDW->iy + 68] = rtDW->v_1_idx_pu[rtDW->iy];
    rtDW->M[rtDW->iy + 96] = rtDW->v_2_idx_pu[rtDW->iy];
    rtDW->M[rtDW->iy + 124] = 0.0F;
    rtDW->M[rtDW->iy + 152] = 0.0F;
    rtDW->M[rtDW->iy + 180] = 0.0F;
    rtDW->M[rtDW->iy + 16] = rtDW->m6[rtDW->iy];
    rtDW->M[rtDW->iy + 44] = rtDW->m1[rtDW->iy];
    rtDW->M[rtDW->iy + 72] = rtDW->v_1_idx_pu[rtDW->iy];
    rtDW->M[rtDW->iy + 100] = rtDW->v_2_idx_pu[rtDW->iy];
    rtDW->M[rtDW->iy + 128] = rtDW->v_3_idx_pu[rtDW->iy];
    rtDW->M[rtDW->iy + 156] = 0.0F;
    rtDW->M[rtDW->iy + 184] = 0.0F;
    rtDW->M[rtDW->iy + 20] = rtDW->m6[rtDW->iy];
    rtDW->M[rtDW->iy + 48] = rtDW->m1[rtDW->iy];
    rtDW->M[rtDW->iy + 76] = rtDW->v_1_idx_pu[rtDW->iy];
    rtDW->M[rtDW->iy + 104] = rtDW->v_2_idx_pu[rtDW->iy];
    rtDW->M[rtDW->iy + 132] = rtDW->v_3_idx_pu[rtDW->iy];
    rtDW->M[rtDW->iy + 160] = rtDW->v_4_idx_pu[rtDW->iy];
    rtDW->M[rtDW->iy + 188] = 0.0F;
    rtDW->M[rtDW->iy + 24] = rtDW->SinCos1_o2;
    rtDW->M[rtDW->iy + 52] = rtDW->q * rtDW->m1[3] + (rtDW->w6theta_el *
      rtDW->m1[2] + (rtDW->x * rtDW->m1[1] + rtDW->SinCos1_o1 * rtDW->m1[0]));
    rtDW->M[rtDW->iy + 80] = rtDW->q * rtDW->v_1_idx_pu[3] + (rtDW->w6theta_el *
      rtDW->v_1_idx_pu[2] + (rtDW->x * rtDW->v_1_idx_pu[1] + rtDW->SinCos1_o1 *
      rtDW->v_1_idx_pu[0]));
    rtDW->M[rtDW->iy + 108] = rtDW->q * rtDW->v_2_idx_pu[3] + (rtDW->w6theta_el *
      rtDW->v_2_idx_pu[2] + (rtDW->x * rtDW->v_2_idx_pu[1] + rtDW->SinCos1_o1 *
      rtDW->v_2_idx_pu[0]));
    rtDW->M[rtDW->iy + 136] = rtDW->q * rtDW->v_3_idx_pu[3] + (rtDW->w6theta_el *
      rtDW->v_3_idx_pu[2] + (rtDW->x * rtDW->v_3_idx_pu[1] + rtDW->SinCos1_o1 *
      rtDW->v_3_idx_pu[0]));
    rtDW->M[rtDW->iy + 164] = rtDW->q * rtDW->v_4_idx_pu[3] + (rtDW->w6theta_el *
      rtDW->v_4_idx_pu[2] + (rtDW->x * rtDW->v_4_idx_pu[1] + rtDW->SinCos1_o1 *
      rtDW->v_4_idx_pu[0]));
    rtDW->M[rtDW->iy + 192] = rtDW->SinCos1_o2;
  }

  /* '<S5>:1:33' H = 2*(M'*M); */
  /* '<S5>:1:34' f = 2*M'*r; */
  /* MATLAB Function 'uz_codegen/qp_solver': '<S6>:1' */
  /* '<S6>:1:3' x_opt = single([0.5 0 0 0 0 0 0.5]'); */
  /* '<S6>:1:5' iter = single(0); */
  /*  contraints */
  /*             t1 t2 t3 t4 t5 t6 t7 */
  /* '<S6>:1:9' A = single([-1  0  0  0  0  0  0;   % t>=0 is converted to -1<=0 */
  /* '<S6>:1:10'              0 -1  0  0  0  0  0;   % no row=no of ineq constraints */
  /* '<S6>:1:11'              0  0 -1  0  0  0  0;   % no columns=no of optimization variables */
  /* '<S6>:1:12'              0  0  0 -1  0  0  0; */
  /* '<S6>:1:13'              0  0  0  0 -1  0  0; */
  /* '<S6>:1:14'              0  0  0  0  0 -1  0; */
  /* '<S6>:1:15'              0  0  0  0  0  0 -1]); */
  /*  t>=0 is converted to -1<=0 */
  /*  no row=no of ineq constraints */
  /*  no columns=no of optimization variables */
  /* '<S6>:1:17' b = single(zeros(7,1)); */
  /* '<S6>:1:19' Aeq = single([1 1 1 1 1 1 1]); */
  /* '<S6>:1:20' beq =  single([1]); */
  /*  sum of all duration times  */
  /*  define cold start for active-set solver */
  /* '<S6>:1:23' iA0 = false(size(b)); */
  /* '<S6>:1:25' [x_opt,iter] = mpc_solve(H,f,A,b,Aeq,beq,iA0,max_iter,tol); */
  /* '<S6>:1:30' x = single([0 0 0 0 0 0 0]'); */
  /* '<S6>:1:31' iter = single(0); */
  /*  set up solver */
  /* '<S6>:1:33' options = mpcActiveSetOptions('single'); */
  /* '<S6>:1:34' options.MaxIterations = max_iter; */
  /* '<S6>:1:35' options.ConstriantTolerance = tol; */
  /* '<S6>:1:36' options.UseHessianAsInput = false; */
  /* '<S6>:1:37' options.IntegrityChecks = false; */
  /* '<S6>:1:40' x_tmp = single([0.5 0 0 0 0 0 0.5]'); */
  /* '<S6>:1:41' exitflag = single(0); */
  /*  calculate inverse of H */
  /* '<S6>:1:43' [L,~] = chol(H,'lower'); */
  for (rtDW->iy = 0; rtDW->iy < 7; rtDW->iy++) {
    for (rtDW->b_j = 0; rtDW->b_j < 7; rtDW->b_j++) {
      rtDW->i = rtDW->iy + 7 * rtDW->b_j;
      rtDW->Linv_data[rtDW->i] = 0.0F;
      for (rtDW->idxAjj = 0; rtDW->idxAjj < 28; rtDW->idxAjj++) {
        rtDW->Linv_data[rtDW->i] += rtDW->M[28 * rtDW->iy + rtDW->idxAjj] *
          rtDW->M[28 * rtDW->b_j + rtDW->idxAjj];
      }
    }
  }

  /* MATLAB Function: '<S1>/qp_solver' incorporates:
   *  Inport: '<Root>/max_iter'
   *  MATLAB Function: '<S1>/formulate_qp'
   */
  for (rtDW->iy = 0; rtDW->iy < 49; rtDW->iy++) {
    rtDW->Hinv_data[rtDW->iy] = rtDW->Linv_data[rtDW->iy] * 2.0F;
  }

  rtDW->i = 0;
  rtDW->b_j = 0;
  exitg1 = false;
  while ((!exitg1) && (rtDW->b_j < 7)) {
    rtDW->idxAjj = rtDW->b_j * 7 + rtDW->b_j;
    rtDW->SinCos1_o1 = 0.0F;
    if (rtDW->b_j >= 1) {
      rtDW->b_ix = rtDW->b_j;
      rtDW->b_iy = rtDW->b_j;
      rtDW->b_k = 0;
      while (rtDW->b_k <= rtDW->b_j - 1) {
        rtDW->SinCos1_o1 += rtDW->Hinv_data[rtDW->b_ix] * rtDW->Hinv_data
          [rtDW->b_iy];
        rtDW->b_ix += 7;
        rtDW->b_iy += 7;
        rtDW->b_k++;
      }
    }

    rtDW->SinCos1_o1 = rtDW->Hinv_data[rtDW->idxAjj] - rtDW->SinCos1_o1;
    if (rtDW->SinCos1_o1 > 0.0F) {
      rtDW->SinCos1_o1 = sqrtf(rtDW->SinCos1_o1);
      rtDW->Hinv_data[rtDW->idxAjj] = rtDW->SinCos1_o1;
      if (rtDW->b_j + 1 < 7) {
        if (rtDW->b_j != 0) {
          rtDW->b_ix = rtDW->b_j;
          rtDW->b_iy = ((rtDW->b_j - 1) * 7 + rtDW->b_j) + 2;
          rtDW->b_k = rtDW->b_j + 2;
          while (rtDW->b_k <= rtDW->b_iy) {
            rtDW->SinCos1_o2 = -rtDW->Hinv_data[rtDW->b_ix];
            rtDW->iy = rtDW->idxAjj + 1;
            rtDW->e = (rtDW->b_k - rtDW->b_j) + 5;
            rtDW->ia = rtDW->b_k;
            while (rtDW->ia <= rtDW->e) {
              rtDW->Hinv_data[rtDW->iy] += rtDW->Hinv_data[rtDW->ia - 1] *
                rtDW->SinCos1_o2;
              rtDW->iy++;
              rtDW->ia++;
            }

            rtDW->b_ix += 7;
            rtDW->b_k += 7;
          }
        }

        rtDW->SinCos1_o1 = 1.0F / rtDW->SinCos1_o1;
        rtDW->b_ix = (rtDW->idxAjj - rtDW->b_j) + 7;
        rtDW->idxAjj++;
        while (rtDW->idxAjj + 1 <= rtDW->b_ix) {
          rtDW->Hinv_data[rtDW->idxAjj] *= rtDW->SinCos1_o1;
          rtDW->idxAjj++;
        }
      }

      rtDW->b_j++;
    } else {
      rtDW->Hinv_data[rtDW->idxAjj] = rtDW->SinCos1_o1;
      rtDW->i = rtDW->b_j + 1;
      exitg1 = true;
    }
  }

  if (rtDW->i == 0) {
    rtDW->i = 7;
  } else {
    rtDW->i--;
  }

  rtDW->b_j = 1;
  while (rtDW->b_j + 1 <= rtDW->i) {
    rtDW->idxAjj = 0;
    while (rtDW->idxAjj <= rtDW->b_j - 1) {
      rtDW->Hinv_data[rtDW->idxAjj + 7 * rtDW->b_j] = 0.0F;
      rtDW->idxAjj++;
    }

    rtDW->b_j++;
  }

  if (1 > rtDW->i) {
    rtDW->iy = -1;
    rtDW->b_j = -1;
    rtDW->b_ix = -1;
  } else {
    rtDW->iy = rtDW->i - 1;
    rtDW->b_j = rtDW->i - 1;
    rtDW->b_ix = rtDW->i - 1;
  }

  rtDW->b_iy = rtDW->b_j + 1;
  for (rtDW->idxAjj = 0; rtDW->idxAjj <= rtDW->b_ix; rtDW->idxAjj++) {
    for (rtDW->i = 0; rtDW->i < rtDW->b_iy; rtDW->i++) {
      rtDW->Hinv_data[rtDW->i + (rtDW->iy + 1) * rtDW->idxAjj] = rtDW->
        Hinv_data[rtDW->i + 7 * rtDW->idxAjj];
    }
  }

  rtDW->Hinv_size[0] = rtDW->iy + 1;
  rtDW->Hinv_size[1] = rtDW->b_ix + 1;

  /* '<S6>:1:44' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
  if ((int8_T)(rtDW->b_j + 1) < (int8_T)(rtDW->b_ix + 1)) {
    rtDW->i = (int8_T)(rtDW->b_j + 1);
  } else {
    rtDW->i = (int8_T)(rtDW->b_ix + 1);
  }

  rtDW->b_k = (int8_T)(rtDW->iy + 1);
  rtDW->b_iy = (int8_T)(rtDW->iy + 1) * (int8_T)(rtDW->b_ix + 1) - 1;
  if (0 <= rtDW->b_iy) {
    memset(&rtDW->b_I_data[0], 0, (rtDW->b_iy + 1) * sizeof(int8_T));
  }

  if (rtDW->i > 0) {
    rtDW->b_j = 0;
    while (rtDW->b_j <= rtDW->i - 1) {
      rtDW->b_I_data[rtDW->b_j + (int8_T)(rtDW->iy + 1) * rtDW->b_j] = 1;
      rtDW->b_j++;
    }
  }

  if (rtDW->iy + 1 < rtDW->b_ix + 1) {
    rtDW->iy++;
  } else {
    rtDW->iy = rtDW->b_ix + 1;
  }

  rtDW->Linv_size[0] = (int8_T)(rtDW->b_ix + 1);
  rtDW->Linv_size[1] = (int8_T)(rtDW->b_ix + 1);
  rtDW->b_j = 0;
  while (rtDW->b_j <= (int8_T)(rtDW->b_ix + 1) - 1) {
    rtDW->idxAjj = 0;
    while (rtDW->idxAjj <= rtDW->iy - 1) {
      rtDW->Linv_data[rtDW->idxAjj + (int8_T)(rtDW->b_ix + 1) * rtDW->b_j] =
        rtDW->b_I_data[rtDW->idxAjj + rtDW->b_k * rtDW->b_j];
      rtDW->idxAjj++;
    }

    rtDW->idxAjj = rtDW->iy;
    while (rtDW->idxAjj + 1 <= rtDW->b_ix + 1) {
      rtDW->Linv_data[rtDW->idxAjj + (int8_T)(rtDW->b_ix + 1) * rtDW->b_j] =
        0.0F;
      rtDW->idxAjj++;
    }

    rtDW->b_j++;
  }

  trisolve(rtDW->Hinv_data, rtDW->Hinv_size, rtDW->Linv_data, rtDW->Linv_size);

  /*  solve QP */
  /* '<S6>:1:46' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
  rtDW->i = rtDW->Linv_size[1];
  rtDW->Hinv_size[0] = rtDW->Linv_size[1];
  rtDW->Hinv_size[1] = rtDW->Linv_size[1];
  rtDW->b_j = 0;
  while (rtDW->b_j <= rtDW->Linv_size[1] - 1) {
    rtDW->idxAjj = rtDW->b_j * rtDW->i;
    rtDW->b_ix = rtDW->b_j * rtDW->Linv_size[0];
    rtDW->b_iy = 0;
    while (rtDW->b_iy <= rtDW->i - 1) {
      rtDW->Hinv_data[rtDW->idxAjj + rtDW->b_iy] = 0.0F;
      rtDW->b_iy++;
    }

    rtDW->b_iy = 0;
    while (rtDW->b_iy <= rtDW->Linv_size[0] - 1) {
      rtDW->SinCos1_o1 = rtDW->Linv_data[rtDW->b_ix + rtDW->b_iy];
      rtDW->b_k = 0;
      while (rtDW->b_k <= rtDW->i - 1) {
        rtDW->iy = rtDW->idxAjj + rtDW->b_k;
        rtDW->Hinv_data[rtDW->iy] += rtDW->Linv_data[rtDW->b_k * rtDW->
          Linv_size[0] + rtDW->b_iy] * rtDW->SinCos1_o1;
        rtDW->b_k++;
      }

      rtDW->b_iy++;
    }

    rtDW->b_j++;
  }

  for (rtDW->iy = 0; rtDW->iy < 7; rtDW->iy++) {
    rtDW->SinCos1_o1 = 0.0F;
    for (rtDW->b_j = 0; rtDW->b_j < 28; rtDW->b_j++) {
      rtDW->SinCos1_o1 += rtDW->M[28 * rtDW->iy + rtDW->b_j] * 2.0F * rtDW->
        r[rtDW->b_j];
    }

    rtDW->fv[rtDW->iy] = -rtDW->SinCos1_o1;
  }

  rtDW->SinCos1_o1 = roundf(rtU->max_iter);
  if (rtDW->SinCos1_o1 < 32768.0F) {
    if (rtDW->SinCos1_o1 >= -32768.0F) {
      tmp = (int16_T)rtDW->SinCos1_o1;
    } else {
      tmp = MIN_int16_T;
    }
  } else {
    tmp = MAX_int16_T;
  }

  /* Outport: '<Root>/iterations_qp' incorporates:
   *  MATLAB Function: '<S1>/qp_solver'
   */
  qpkwik(rtDW->Linv_data, rtDW->Linv_size, rtDW->Hinv_data, rtDW->Hinv_size,
         rtDW->fv, tmp, (int16_T)rtDW->Linv_size[0], rtDW->x_data, &rtDW->x_size,
         rtDW->lam_c, &rtY->iterations_qp, rtDW->iA1, rtDW);

  /* '<S6>:1:47' x = single(x_tmp(1:7,1)); */
  /* '<S6>:1:48' iter = single(exitflag); */
  /*  J1 = x1'*(M1'*M1)*x1-2*r1'*M1*x1; */
  /* MATLAB Function 'uz_codegen/tz': '<S9>:1' */
  /* '<S9>:1:3' I = single([1 0 0 0 0 0; */
  /* '<S9>:1:4'             1 1 0 0 0 0; */
  /* '<S9>:1:5'             1 1 1 0 0 0; */
  /* '<S9>:1:6'             1 1 1 1 0 0; */
  /* '<S9>:1:7'             1 1 1 1 1 0; */
  /* '<S9>:1:8'             1 1 1 1 1 1]); */
  /* '<S9>:1:10' zer6 = single(zeros(6,1)); */
  /* '<S9>:1:12' T = single([I zer6]); */
  /* '<S9>:1:14' tz=single(T*x); */
  /* MATLAB Function 'uz_codegen/tz_2_tph': '<S10>:1' */
  /* '<S10>:1:3' seq_order_table = single([4,1,6,2,3,5; */
  /* '<S10>:1:4'     1,4,2,6,5,3; */
  /* '<S10>:1:5'     1,4,2,5,6,3; */
  /* '<S10>:1:6'     4,1,2,5,3,6; */
  /* '<S10>:1:7'     4,2,1,5,3,6; */
  /* '<S10>:1:8'     2,4,5,1,6,3; */
  /* '<S10>:1:9'     2,5,4,1,6,3; */
  /* '<S10>:1:10'     5,2,4,1,3,6; */
  /* '<S10>:1:11'     5,2,4,3,1,6; */
  /* '<S10>:1:12'     2,5,3,4,6,1; */
  /* '<S10>:1:13'     2,5,3,6,4,1; */
  /* '<S10>:1:14'     5,2,3,6,1,4; */
  /* '<S10>:1:15'     5,3,2,6,1,4; */
  /* '<S10>:1:16'     3,5,6,2,4,1; */
  /* '<S10>:1:17'     3,6,5,2,4,1; */
  /* '<S10>:1:18'     6,3,5,2,1,4; */
  /* '<S10>:1:19'     6,3,5,1,2,4; */
  /* '<S10>:1:20'     3,6,1,5,4,2; */
  /* '<S10>:1:21'     3,6,1,4,5,2; */
  /* '<S10>:1:22'     6,3,1,4,2,5; */
  /* '<S10>:1:23'     6,1,3,4,2,5; */
  /* '<S10>:1:24'     1,6,4,3,5,2; */
  /* '<S10>:1:25'     1,4,6,3,5,2; */
  /* '<S10>:1:26'     4,1,6,3,2,5]); */
  /* '<S10>:1:28' t = single(zeros(6,1)); */
  for (rtDW->i = 0; rtDW->i < 6; rtDW->i++) {
    /* MATLAB Function: '<S1>/tz' incorporates:
     *  MATLAB Function: '<S1>/qp_solver'
     */
    rtDW->tz[rtDW->i] = 0.0F;
    for (rtDW->iy = 0; rtDW->iy < 7; rtDW->iy++) {
      rtDW->tz[rtDW->i] += (real32_T)a[6 * rtDW->iy + rtDW->i] * rtDW->
        x_data[rtDW->iy];
    }

    /* End of MATLAB Function: '<S1>/tz' */

    /* MATLAB Function: '<S1>/tz_2_tph' */
    rtDW->t[rtDW->i] = 0.0F;
  }

  /* MATLAB Function: '<S1>/tz_2_tph' */
  /* '<S10>:1:30' for i=1:6 */
  for (rtDW->idxAjj = 0; rtDW->idxAjj < 6; rtDW->idxAjj++) {
    /* '<S10>:1:31' t(seq_order_table(seq_no,i),1) = tz(i); */
    rtDW->t[seq_order_table[(rtDW->sector_ref + 24 * rtDW->idxAjj) - 1] - 1] =
      rtDW->tz[rtDW->idxAjj];
  }

  /* Outport: '<Root>/d_opt' incorporates:
   *  MATLAB Function: '<S1>/tz_2_tph'
   */
  /* '<S10>:1:34' ta_1 = t(1); */
  /* '<S10>:1:35' tb_1 = t(2); */
  /* '<S10>:1:36' tc_1 = t(3); */
  /* '<S10>:1:37' ta_2 = t(4); */
  /* '<S10>:1:38' tb_2 = t(5); */
  /* '<S10>:1:39' tc_2 = t(6); */
  rtY->d_opt[0] = rtDW->t[0];
  rtY->d_opt[1] = rtDW->t[1];
  rtY->d_opt[2] = rtDW->t[2];
  rtY->d_opt[3] = rtDW->t[3];
  rtY->d_opt[4] = rtDW->t[4];
  rtY->d_opt[5] = rtDW->t[5];

  /* Update for Delay: '<S1>/Delay1' incorporates:
   *  MATLAB Function: '<S1>/qp_solver'
   */
  rtDW->icLoad = false;
  for (rtDW->iy = 0; rtDW->iy < 7; rtDW->iy++) {
    rtDW->Delay1_DSTATE[rtDW->iy] = rtDW->x_data[rtDW->iy];
  }

  /* End of Update for Delay: '<S1>/Delay1' */

  /* Update for Delay: '<S1>/Delay3' */
  rtDW->icLoad_a = false;

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->icLoad_f = false;

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->icLoad_k = false;

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->icLoad_n = false;

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->icLoad_l = false;

  /* Update for Delay: '<S1>/Delay8' */
  rtDW->icLoad_ly = false;

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/state_space_mdl'
   */
  rtDW->Delay3_DSTATE[0] = rtDW->m6[0];

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->Delay4_DSTATE[0] = rtDW->m1[0];

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->Delay5_DSTATE[0] = rtDW->v_1_idx_pu[0];

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->Delay6_DSTATE[0] = rtDW->v_2_idx_pu[0];

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->Delay7_DSTATE[0] = rtDW->v_3_idx_pu[0];

  /* Update for Delay: '<S1>/Delay8' */
  rtDW->Delay8_DSTATE[0] = rtDW->v_4_idx_pu[0];

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/state_space_mdl'
   */
  rtDW->Delay3_DSTATE[1] = rtDW->m6[1];

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->Delay4_DSTATE[1] = rtDW->m1[1];

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->Delay5_DSTATE[1] = rtDW->v_1_idx_pu[1];

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->Delay6_DSTATE[1] = rtDW->v_2_idx_pu[1];

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->Delay7_DSTATE[1] = rtDW->v_3_idx_pu[1];

  /* Update for Delay: '<S1>/Delay8' */
  rtDW->Delay8_DSTATE[1] = rtDW->v_4_idx_pu[1];

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/state_space_mdl'
   */
  rtDW->Delay3_DSTATE[2] = rtDW->m6[2];

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->Delay4_DSTATE[2] = rtDW->m1[2];

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->Delay5_DSTATE[2] = rtDW->v_1_idx_pu[2];

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->Delay6_DSTATE[2] = rtDW->v_2_idx_pu[2];

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->Delay7_DSTATE[2] = rtDW->v_3_idx_pu[2];

  /* Update for Delay: '<S1>/Delay8' */
  rtDW->Delay8_DSTATE[2] = rtDW->v_4_idx_pu[2];

  /* Update for Delay: '<S1>/Delay3' incorporates:
   *  MATLAB Function: '<S1>/state_space_mdl'
   */
  rtDW->Delay3_DSTATE[3] = rtDW->m6[3];

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->Delay4_DSTATE[3] = rtDW->m1[3];

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->Delay5_DSTATE[3] = rtDW->v_1_idx_pu[3];

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->Delay6_DSTATE[3] = rtDW->v_2_idx_pu[3];

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->Delay7_DSTATE[3] = rtDW->v_3_idx_pu[3];

  /* Update for Delay: '<S1>/Delay8' */
  rtDW->Delay8_DSTATE[3] = rtDW->v_4_idx_pu[3];
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

  /* InitializeConditions for Delay: '<S1>/Delay1' */
  rtDW->icLoad = true;

  /* InitializeConditions for Delay: '<S1>/Delay3' */
  rtDW->icLoad_a = true;

  /* InitializeConditions for Delay: '<S1>/Delay4' */
  rtDW->icLoad_f = true;

  /* InitializeConditions for Delay: '<S1>/Delay5' */
  rtDW->icLoad_k = true;

  /* InitializeConditions for Delay: '<S1>/Delay6' */
  rtDW->icLoad_n = true;

  /* InitializeConditions for Delay: '<S1>/Delay7' */
  rtDW->icLoad_l = true;

  /* InitializeConditions for Delay: '<S1>/Delay8' */
  rtDW->icLoad_ly = true;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
