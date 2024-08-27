/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.11
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Aug 27 18:00:10 2024
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
static void abs_i(const real32_T x[7], real32_T y[7]);
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
static real32_T mtimes_l(const real32_T A_data[], const real32_T B_1[7]);
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
static void abs_i(const real32_T x[7], real32_T y[7])
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
  boolean_T exitg2;
  rtDW->m_j = A_size[0];
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

    rtDW->i_d = 0;
    while (rtDW->i_d <= rtDW->minmn - 1) {
      rtDW->ii = rtDW->i_d * rtDW->minmana + rtDW->i_d;
      rtDW->mmi = rtDW->m_j - rtDW->i_d;
      if (rtDW->i_d + 1 < rtDW->m_j) {
        rtDW->b_atmp = A_data[rtDW->ii];
        tau_data[rtDW->i_d] = 0.0F;
        if (rtDW->mmi > 0) {
          rtDW->beta1 = xnrm2(rtDW->mmi - 1, A_data, rtDW->ii + 2);
          if (rtDW->beta1 != 0.0F) {
            rtDW->beta1 = rt_hypotf(A_data[rtDW->ii], rtDW->beta1);
            if (A_data[rtDW->ii] >= 0.0F) {
              rtDW->beta1 = -rtDW->beta1;
            }

            if (fabsf(rtDW->beta1) < 9.86076132E-32F) {
              knt = -1;
              b_k = rtDW->ii + rtDW->mmi;
              do {
                knt++;
                for (c_k = rtDW->ii + 1; c_k < b_k; c_k++) {
                  A_data[c_k] *= 1.01412048E+31F;
                }

                rtDW->beta1 *= 1.01412048E+31F;
                rtDW->b_atmp *= 1.01412048E+31F;
              } while (fabsf(rtDW->beta1) < 9.86076132E-32F);

              rtDW->beta1 = rt_hypotf(rtDW->b_atmp, xnrm2(rtDW->mmi - 1, A_data,
                rtDW->ii + 2));
              if (rtDW->b_atmp >= 0.0F) {
                rtDW->beta1 = -rtDW->beta1;
              }

              tau_data[rtDW->i_d] = (rtDW->beta1 - rtDW->b_atmp) / rtDW->beta1;
              rtDW->b_atmp = 1.0F / (rtDW->b_atmp - rtDW->beta1);
              b_k = rtDW->ii + rtDW->mmi;
              for (c_k = rtDW->ii + 1; c_k < b_k; c_k++) {
                A_data[c_k] *= rtDW->b_atmp;
              }

              for (c_k = 0; c_k <= knt; c_k++) {
                rtDW->beta1 *= 9.86076132E-32F;
              }

              rtDW->b_atmp = rtDW->beta1;
            } else {
              tau_data[rtDW->i_d] = (rtDW->beta1 - A_data[rtDW->ii]) /
                rtDW->beta1;
              rtDW->b_atmp = 1.0F / (A_data[rtDW->ii] - rtDW->beta1);
              knt = rtDW->ii + rtDW->mmi;
              for (b_k = rtDW->ii + 1; b_k < knt; b_k++) {
                A_data[b_k] *= rtDW->b_atmp;
              }

              rtDW->b_atmp = rtDW->beta1;
            }
          }
        }

        A_data[rtDW->ii] = rtDW->b_atmp;
      } else {
        tau_data[rtDW->i_d] = 0.0F;
      }

      if (rtDW->i_d + 1 < rtDW->n) {
        rtDW->b_atmp = A_data[rtDW->ii];
        A_data[rtDW->ii] = 1.0F;
        c_k = (rtDW->ii + rtDW->minmana) + 1;
        if (tau_data[rtDW->i_d] != 0.0F) {
          rtDW->mmip1 = (rtDW->ii + rtDW->mmi) - 1;
          while ((rtDW->mmi > 0) && (A_data[rtDW->mmip1] == 0.0F)) {
            rtDW->mmi--;
            rtDW->mmip1--;
          }

          rtDW->mmip1 = (rtDW->n - rtDW->i_d) - 1;
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
          xgerc(rtDW->mmi, rtDW->mmip1, -tau_data[rtDW->i_d], rtDW->ii + 1,
                rtDW->work_data, A_data, c_k, rtDW->minmana);
        }

        A_data[rtDW->ii] = rtDW->b_atmp;
      }

      rtDW->i_d++;
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
  boolean_T exitg2;
  if (n >= 1) {
    rtDW->itau = k;
    while (rtDW->itau <= n - 1) {
      rtDW->i_g = rtDW->itau * lda;
      rtDW->iaii = 0;
      while (rtDW->iaii <= m - 1) {
        A_data[rtDW->i_g + rtDW->iaii] = 0.0F;
        rtDW->iaii++;
      }

      A_data[rtDW->i_g + rtDW->itau] = 1.0F;
      rtDW->itau++;
    }

    rtDW->itau = k - 1;
    rtDW->iaii = (int8_T)A_size[1];
    if (0 <= rtDW->iaii - 1) {
      memset(&rtDW->work_data_f[0], 0, rtDW->iaii * sizeof(real32_T));
    }

    rtDW->i_g = k;
    while (rtDW->i_g >= 1) {
      rtDW->iaii = (rtDW->i_g - 1) * lda + rtDW->i_g;
      if (rtDW->i_g < n) {
        A_data[rtDW->iaii - 1] = 1.0F;
        lastc = (m - rtDW->i_g) - 1;
        rtDW->c_c = rtDW->iaii + lda;
        if (tau_data[rtDW->itau] != 0.0F) {
          rtDW->lastv = lastc + 2;
          lastc += rtDW->iaii;
          while ((rtDW->lastv > 0) && (A_data[lastc] == 0.0F)) {
            rtDW->lastv--;
            lastc--;
          }

          lastc = n - rtDW->i_g;
          exitg2 = false;
          while ((!exitg2) && (lastc > 0)) {
            coltop = (lastc - 1) * lda + rtDW->c_c;
            ia = coltop;
            do {
              exitg1 = 0;
              if (ia <= (coltop + rtDW->lastv) - 1) {
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
          rtDW->lastv = 0;
          lastc = 0;
        }

        if (rtDW->lastv > 0) {
          xgemv(rtDW->lastv, lastc, A_data, rtDW->c_c, lda, A_data, rtDW->iaii,
                rtDW->work_data_f);
          xgerc(rtDW->lastv, lastc, -tau_data[rtDW->itau], rtDW->iaii,
                rtDW->work_data_f, A_data, rtDW->c_c, lda);
        }
      }

      if (rtDW->i_g < m) {
        rtDW->c_c = (rtDW->iaii + m) - rtDW->i_g;
        rtDW->lastv = rtDW->iaii;
        while (rtDW->lastv + 1 <= rtDW->c_c) {
          A_data[rtDW->lastv] *= -tau_data[rtDW->itau];
          rtDW->lastv++;
        }
      }

      A_data[rtDW->iaii - 1] = 1.0F - tau_data[rtDW->itau];
      rtDW->c_c = 0;
      while (rtDW->c_c <= rtDW->i_g - 2) {
        A_data[(rtDW->iaii - rtDW->c_c) - 2] = 0.0F;
        rtDW->c_c++;
      }

      rtDW->itau--;
      rtDW->i_g--;
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
static real32_T mtimes_l(const real32_T A_data[], const real32_T B_1[7])
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
  for (rtDW->i_p = 0; rtDW->i_p < 8; rtDW->i_p++) {
    iA[rtDW->i_p] = h[rtDW->i_p];
    lambda[rtDW->i_p] = 0.0F;
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
  for (rtDW->i_p = 0; rtDW->i_p < 8; rtDW->i_p++) {
    rtDW->cTol[rtDW->i_p] = 1.0F;
    rtDW->iC[rtDW->i_p] = 0;
  }

  nA = 0;
  for (rtDW->i_p = 0; rtDW->i_p < 8; rtDW->i_p++) {
    if (iA[rtDW->i_p] == 1) {
      rtDW->lambda_tmp_tmp = nA + 1;
      if (nA + 1 > 32767) {
        rtDW->lambda_tmp_tmp = 32767;
      }

      nA = (int16_T)rtDW->lambda_tmp_tmp;
      rtDW->iC[(int16_T)rtDW->lambda_tmp_tmp - 1] = (int16_T)(rtDW->i_p + 1);
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

    rtDW->i_p = tmp;
    if (0 <= rtDW->i_p - 1) {
      memset(&rtDW->Opt_data[0], 0, rtDW->i_p * sizeof(real32_T));
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
          rtDW->i_p = 1;
          while (rtDW->i_p - 1 <= nA - 1) {
            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_p;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->lambda_tmp_tmp = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->lambda_tmp_tmp = -32768;
            }

            rtDW->Rhs_data[rtDW->lambda_tmp_tmp - 1] = h[rtDW->iC[(int16_T)
              rtDW->i_p - 1] - 1];
            for (kNext = (int16_T)rtDW->i_p; kNext <= nA; kNext++) {
              rtDW->lambda_tmp_tmp = (kNext + rtDW->U_size[0] * ((int16_T)
                rtDW->i_p - 1)) - 1;
              rtDW->U_data[rtDW->lambda_tmp_tmp] = 0.0F;
              rtDW->H = 1;
              while (rtDW->H - 1 <= nA - 1) {
                rtDW->loop_ub = rtDW->RLinv_size[0] * ((int16_T)rtDW->H - 1);
                rtDW->U_data[rtDW->lambda_tmp_tmp] += rtDW->RLinv_data[(kNext +
                  rtDW->loop_ub) - 1] * rtDW->RLinv_data[((int16_T)rtDW->i_p +
                  rtDW->loop_ub) - 1];
                rtDW->H++;
              }

              rtDW->U_data[((int16_T)rtDW->i_p + rtDW->U_size[0] * (kNext - 1))
                - 1] = rtDW->U_data[rtDW->lambda_tmp_tmp];
            }

            rtDW->i_p++;
          }

          rtDW->i_p = 1;
          while (rtDW->i_p - 1 <= n - 1) {
            rtDW->loop_ub = rtDW->H_size[1];
            rtDW->Xnorm0 = 0.0F;
            for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < rtDW->loop_ub;
                 rtDW->lambda_tmp_tmp++) {
              rtDW->Xnorm0 += rtDW->H_data[((int16_T)rtDW->i_p + rtDW->H_size[0]
                * rtDW->lambda_tmp_tmp) - 1] * rtDW->Rhs_data
                [rtDW->lambda_tmp_tmp];
            }

            rtDW->Opt_data[(int16_T)rtDW->i_p - 1] = rtDW->Xnorm0;
            rtDW->H = 1;
            while (rtDW->H - 1 <= nA - 1) {
              rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->H;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->lambda_tmp_tmp = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->lambda_tmp_tmp = -32768;
              }

              rtDW->Opt_data[(int16_T)rtDW->i_p - 1] += rtDW->D_data[((int16_T)
                rtDW->i_p + rtDW->D_size[0] * ((int16_T)rtDW->H - 1)) - 1] *
                rtDW->Rhs_data[rtDW->lambda_tmp_tmp - 1];
              rtDW->H++;
            }

            rtDW->i_p++;
          }

          rtDW->i_p = 1;
          while (rtDW->i_p - 1 <= nA - 1) {
            rtDW->loop_ub = rtDW->D_size[0];
            rtDW->Xnorm0 = 0.0F;
            for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < rtDW->loop_ub;
                 rtDW->lambda_tmp_tmp++) {
              rtDW->Xnorm0 += rtDW->D_data[rtDW->lambda_tmp_tmp + rtDW->D_size[0]
                * ((int16_T)rtDW->i_p - 1)] * rtDW->Rhs_data
                [rtDW->lambda_tmp_tmp];
            }

            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_p;
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

              rtDW->i_l = rtDW->lambda_tmp_tmp;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->i_l = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->i_l = -32768;
              }

              rtDW->i1 = n + (int16_T)rtDW->H;
              if (rtDW->i1 > 32767) {
                rtDW->i1 = 32767;
              } else if (rtDW->i1 < -32768) {
                rtDW->i1 = -32768;
              }

              rtDW->Opt_data[rtDW->loop_ub - 1] = rtDW->U_data[((int16_T)
                rtDW->i_p + rtDW->U_size[0] * ((int16_T)rtDW->H - 1)) - 1] *
                rtDW->Rhs_data[rtDW->i1 - 1] + rtDW->Opt_data[rtDW->i_l - 1];
              rtDW->H++;
            }

            rtDW->i_p++;
          }

          rtDW->Xnorm0 = -1.0E-12F;
          kDrop = 0;
          rtDW->i_p = 1;
          while (rtDW->i_p - 1 <= nA - 1) {
            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_p;
            rtDW->loop_ub = rtDW->lambda_tmp_tmp;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->loop_ub = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->loop_ub = -32768;
            }

            lambda[rtDW->iC[(int16_T)rtDW->i_p - 1] - 1] = rtDW->Opt_data
              [rtDW->loop_ub - 1];
            rtDW->loop_ub = rtDW->lambda_tmp_tmp;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->loop_ub = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->loop_ub = -32768;
            }

            if ((rtDW->Opt_data[rtDW->loop_ub - 1] < rtDW->Xnorm0) && ((int16_T)
                 rtDW->i_p <= nA - 1)) {
              kDrop = (int16_T)rtDW->i_p;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->lambda_tmp_tmp = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->lambda_tmp_tmp = -32768;
              }

              rtDW->Xnorm0 = rtDW->Opt_data[rtDW->lambda_tmp_tmp - 1];
            }

            rtDW->i_p++;
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
          for (rtDW->i_p = 0; rtDW->i_p < 8; rtDW->i_p++) {
            lambda[rtDW->i_p] = 0.0F;
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
      for (rtDW->i_p = 0; rtDW->i_p < 7; rtDW->i_p++) {
        rtDW->t_n = rtDW->cTol[rtDW->i_p];
        if (!cTolComputed) {
          for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < 7;
               rtDW->lambda_tmp_tmp++) {
            rtDW->AcRow[rtDW->lambda_tmp_tmp] = (real32_T)Ac[rtDW->i_p +
              (rtDW->lambda_tmp_tmp << 3)] * x_data[rtDW->lambda_tmp_tmp];
          }

          abs_i(rtDW->AcRow, rtDW->z_data);
          rtDW->t_n = fmaxf(rtDW->t_n, maximum(rtDW->z_data));
        }

        if (iA[rtDW->i_p] == 0) {
          rtDW->cVal = 0.0F;
          for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < 7;
               rtDW->lambda_tmp_tmp++) {
            rtDW->cVal += (real32_T)Ac[rtDW->i_p + (rtDW->lambda_tmp_tmp << 3)] *
              x_data[rtDW->lambda_tmp_tmp];
          }

          rtDW->cVal /= rtDW->t_n;
          if (rtDW->cVal < rtDW->cMin) {
            rtDW->cMin = rtDW->cVal;
            kNext = (int16_T)(rtDW->i_p + 1);
          }
        }

        rtDW->cTol[rtDW->i_p] = rtDW->t_n;
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
                rtDW->i_p = 1;
                while (rtDW->i_p - 1 <= nA - 1) {
                  rtDW->t_n = 0.0F;
                  for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < 7;
                       rtDW->lambda_tmp_tmp++) {
                    rtDW->t_n += rtDW->D_data[rtDW->lambda_tmp_tmp +
                      rtDW->D_size[0] * ((int16_T)rtDW->i_p - 1)] * rtDW->
                      AcRow[rtDW->lambda_tmp_tmp];
                  }

                  rtDW->r_data[(int16_T)rtDW->i_p - 1] = rtDW->t_n;
                  rtDW->i_p++;
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
                rtDW->i_p = 0;
                exitg4 = false;
                while ((!exitg4) && (rtDW->i_p <= nA - 2)) {
                  if (rtDW->r_data[rtDW->i_p] >= 1.0E-12F) {
                    ColdReset = false;
                    exitg4 = true;
                  } else {
                    rtDW->i_p++;
                  }
                }
              }

              if ((nA != 1) && (!ColdReset)) {
                rtDW->lambda_tmp_tmp = nA - 1;
                if (nA - 1 < -32768) {
                  rtDW->lambda_tmp_tmp = -32768;
                }

                rtDW->i_p = 1;
                while (rtDW->i_p - 1 <= (int16_T)rtDW->lambda_tmp_tmp - 1) {
                  rtDW->cVal = rtDW->r_data[(int16_T)rtDW->i_p - 1];
                  if (rtDW->cVal > 1.0E-12F) {
                    rtDW->cVal = lambda[rtDW->iC[(int16_T)rtDW->i_p - 1] - 1] /
                      rtDW->cVal;
                    if ((kDrop == 0) || (rtDW->cVal < rtDW->rMin)) {
                      rtDW->rMin = rtDW->cVal;
                      kDrop = (int16_T)rtDW->i_p;
                    }
                  }

                  rtDW->i_p++;
                }

                if (kDrop > 0) {
                  rtDW->cMin = rtDW->rMin;
                  DualFeasible = false;
                }
              }

              rtDW->cVal = mtimes_l(rtDW->z_data, rtDW->AcRow);
              if (rtDW->cVal <= 0.0F) {
                rtDW->cVal = 0.0F;
                ColdReset = true;
              } else {
                rtDW->t_n = 0.0F;
                for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < 7;
                     rtDW->lambda_tmp_tmp++) {
                  rtDW->t_n += rtDW->AcRow[rtDW->lambda_tmp_tmp] * x_data
                    [rtDW->lambda_tmp_tmp];
                }

                rtDW->cVal = (-0.0F - rtDW->t_n) / rtDW->cVal;
                ColdReset = false;
              }

              if (DualFeasible && ColdReset) {
                *status = -1.0F;
                exitg1 = 1;
              } else {
                if (ColdReset) {
                  rtDW->t_n = rtDW->cMin;
                } else if (DualFeasible) {
                  rtDW->t_n = rtDW->cVal;
                } else {
                  rtDW->t_n = fminf(rtDW->cMin, rtDW->cVal);
                }

                rtDW->i_p = 1;
                while (rtDW->i_p - 1 <= nA - 1) {
                  rtDW->lambda_tmp_tmp = rtDW->iC[(int16_T)rtDW->i_p - 1];
                  lambda[rtDW->lambda_tmp_tmp - 1] -= rtDW->r_data[(int16_T)
                    rtDW->i_p - 1] * rtDW->t_n;
                  if ((rtDW->lambda_tmp_tmp <= 7) && (lambda
                       [rtDW->lambda_tmp_tmp - 1] < 0.0F)) {
                    lambda[rtDW->lambda_tmp_tmp - 1] = 0.0F;
                  }

                  rtDW->i_p++;
                }

                lambda[kNext - 1] += rtDW->t_n;
                if (rtDW->t_n == rtDW->cMin) {
                  DropConstraint(kDrop, iA, &nA, rtDW->iC);
                }

                if (!ColdReset) {
                  rtDW->loop_ub = *x_size;
                  for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp <
                       rtDW->loop_ub; rtDW->lambda_tmp_tmp++) {
                    x_data[rtDW->lambda_tmp_tmp] += rtDW->t_n * rtDW->
                      z_data[rtDW->lambda_tmp_tmp];
                  }

                  if (rtDW->t_n == rtDW->cVal) {
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
  for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
    rtDW->v_t0[rtDW->ijA] = 0.0F;
    for (rtDW->c = 0; rtDW->c < 7; rtDW->c++) {
      rtDW->v_t0[rtDW->ijA] += rtDW->r[(rtDW->c << 2) + rtDW->ijA] *
        rtDW->Delay13_DSTATE[rtDW->c];
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
   *  Inport: '<Root>/psi_pm_over_psiB'
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
  rtDW->x0_idx_2 = -rtU->Ly_over_LB * rtU->omega_el_pu;
  rtDW->A[26] = rtDW->x0_idx_2;
  rtDW->A[34] = 0.0F;
  rtDW->A[42] = 0.0F;
  rtDW->A[50] = 1.0F;
  rtDW->A[58] = 0.0F;
  rtDW->A[3] = 0.0F;
  rtDW->A[11] = 0.0F;
  rtDW->x0_idx_3 = rtU->Lx_over_LB * rtU->omega_el_pu;
  rtDW->A[19] = rtDW->x0_idx_3;
  rtDW->A[27] = 1.0F - rtU->Ts_times_ZB_over_Ly * rtU->Rs_over_ZB;
  rtDW->A[35] = 0.0F;
  rtDW->A[43] = 0.0F;
  rtDW->A[51] = 0.0F;
  rtDW->A[59] = 1.0F;
  for (rtDW->ijA = 0; rtDW->ijA < 8; rtDW->ijA++) {
    rtDW->sector_ref = rtDW->ijA << 3;
    rtDW->A[rtDW->sector_ref + 4] = h[rtDW->ijA];
    rtDW->A[rtDW->sector_ref + 5] = g[rtDW->ijA];
    rtDW->A[rtDW->sector_ref + 6] = f[rtDW->ijA];
    rtDW->A[rtDW->sector_ref + 7] = e[rtDW->ijA];
  }

  /* '<S3>:1:18' B = [Ts_times_ZB_over_Ld    0                       0                       0                       ; */
  /* '<S3>:1:19'      0                      Ts_times_ZB_over_Lq     0                       0                       ; */
  /* '<S3>:1:20'      0                      0                       Ts_times_ZB_over_Lx     0                       ; */
  /* '<S3>:1:21'      0                      0                       0                       Ts_times_ZB_over_Ly     ; */
  /* '<S3>:1:22'      0 0 0 0; */
  /* '<S3>:1:23'      0 0 0 0; */
  /* '<S3>:1:24'      0 0 0 0; */
  /* '<S3>:1:25'      0 0 0 0]; */
  /* '<S3>:1:27' C = [1   0   0   0   0   0   0   0; */
  /* '<S3>:1:28'      0   1   0   0   0   0   0   0; */
  /* '<S3>:1:29'      0   0   1   0   0   0   0   0; */
  /* '<S3>:1:30'      0   0   0   1   0   0   0   0]; */
  /* '<S3>:1:32' D = [0; -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB; 0; 0; 0; 0; 0; 0]; */
  /*  parameters for kalman */
  /* '<S3>:1:35' u = [v_d; v_q; v_x; v_y]; */
  /* '<S3>:1:39' if isempty(x_e) */
  /* '<S3>:1:44' x = x_e; */
  /* '<S3>:1:46' x_p = A * x + B * u + D; */
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
  rtDW->A_me = -rtU->omega_el_pu * rtU->Ts_times_ZB_over_Lq *
    rtU->psi_pm_over_psiB;
  rtDW->fv1[1] = rtDW->A_me;
  rtDW->fv1[2] = 0.0F;
  rtDW->fv1[3] = 0.0F;
  rtDW->fv1[4] = 0.0F;
  rtDW->fv1[5] = 0.0F;
  rtDW->fv1[6] = 0.0F;
  rtDW->fv1[7] = 0.0F;

  /* '<S3>:1:48' P_p = A*P_e*A'+Q; */
  for (rtDW->ijA = 0; rtDW->ijA < 8; rtDW->ijA++) {
    rtDW->A_b[rtDW->ijA] = 0.0F;
    for (rtDW->c = 0; rtDW->c < 8; rtDW->c++) {
      rtDW->i = rtDW->c << 3;
      rtDW->sector_ref = rtDW->i + rtDW->ijA;
      rtDW->A_m[rtDW->sector_ref] = 0.0F;
      for (rtDW->b_ix = 0; rtDW->b_ix < 8; rtDW->b_ix++) {
        rtDW->A_m[rtDW->sector_ref] += rtDW->A[(rtDW->b_ix << 3) + rtDW->ijA] *
          rtDW->P_e[rtDW->i + rtDW->b_ix];
      }

      rtDW->A_c[rtDW->sector_ref] = 0.0F;
      rtDW->A_b[rtDW->ijA] += rtDW->A[rtDW->sector_ref] * rtDW->x_e[rtDW->c];
    }

    rtDW->x_p[rtDW->ijA] = (rtDW->A_b[rtDW->ijA] + (rtDW->b_A_tmp[rtDW->ijA + 24]
      * rtDW->rtb_v_1_idx_pu_idx_3 + (rtDW->b_A_tmp[rtDW->ijA + 16] * rtDW->q +
      (rtDW->b_A_tmp[rtDW->ijA + 8] * rtDW->rtb_v_1_idx_pu_idx_1 + rtDW->
       b_A_tmp[rtDW->ijA] * rtDW->rtb_i_dq_obs_idx_0)))) + rtDW->fv1[rtDW->ijA];
    for (rtDW->c = 0; rtDW->c < 8; rtDW->c++) {
      for (rtDW->b_ix = 0; rtDW->b_ix < 8; rtDW->b_ix++) {
        rtDW->sector_ref = rtDW->b_ix << 3;
        rtDW->i = (rtDW->c << 3) + rtDW->ijA;
        rtDW->A_c[rtDW->i] += rtDW->A_m[rtDW->sector_ref + rtDW->ijA] * rtDW->
          A[rtDW->sector_ref + rtDW->c];
      }
    }
  }

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/kalman_Q1'
   *  Inport: '<Root>/kalman_Q2'
   */
  rtDW->A_m[0] = rtU->kalman_Q1;
  rtDW->A_m[8] = 0.0F;
  rtDW->A_m[16] = 0.0F;
  rtDW->A_m[24] = 0.0F;
  rtDW->A_m[32] = 0.0F;
  rtDW->A_m[40] = 0.0F;
  rtDW->A_m[48] = 0.0F;
  rtDW->A_m[56] = 0.0F;
  rtDW->A_m[1] = 0.0F;
  rtDW->A_m[9] = rtU->kalman_Q1;
  rtDW->A_m[17] = 0.0F;
  rtDW->A_m[25] = 0.0F;
  rtDW->A_m[33] = 0.0F;
  rtDW->A_m[41] = 0.0F;
  rtDW->A_m[49] = 0.0F;
  rtDW->A_m[57] = 0.0F;
  rtDW->A_m[2] = 0.0F;
  rtDW->A_m[10] = 0.0F;
  rtDW->A_m[18] = rtU->kalman_Q1;
  rtDW->A_m[26] = 0.0F;
  rtDW->A_m[34] = 0.0F;
  rtDW->A_m[42] = 0.0F;
  rtDW->A_m[50] = 0.0F;
  rtDW->A_m[58] = 0.0F;
  rtDW->A_m[3] = 0.0F;
  rtDW->A_m[11] = 0.0F;
  rtDW->A_m[19] = 0.0F;
  rtDW->A_m[27] = rtU->kalman_Q1;
  rtDW->A_m[35] = 0.0F;
  rtDW->A_m[43] = 0.0F;
  rtDW->A_m[51] = 0.0F;
  rtDW->A_m[59] = 0.0F;
  rtDW->A_m[4] = 0.0F;
  rtDW->A_m[12] = 0.0F;
  rtDW->A_m[20] = 0.0F;
  rtDW->A_m[28] = 0.0F;
  rtDW->A_m[36] = rtU->kalman_Q2;
  rtDW->A_m[44] = 0.0F;
  rtDW->A_m[52] = 0.0F;
  rtDW->A_m[60] = 0.0F;
  rtDW->A_m[5] = 0.0F;
  rtDW->A_m[13] = 0.0F;
  rtDW->A_m[21] = 0.0F;
  rtDW->A_m[29] = 0.0F;
  rtDW->A_m[37] = 0.0F;
  rtDW->A_m[45] = rtU->kalman_Q2;
  rtDW->A_m[53] = 0.0F;
  rtDW->A_m[61] = 0.0F;
  rtDW->A_m[6] = 0.0F;
  rtDW->A_m[14] = 0.0F;
  rtDW->A_m[22] = 0.0F;
  rtDW->A_m[30] = 0.0F;
  rtDW->A_m[38] = 0.0F;
  rtDW->A_m[46] = 0.0F;
  rtDW->A_m[54] = rtU->kalman_Q2;
  rtDW->A_m[62] = 0.0F;
  rtDW->A_m[7] = 0.0F;
  rtDW->A_m[15] = 0.0F;
  rtDW->A_m[23] = 0.0F;
  rtDW->A_m[31] = 0.0F;
  rtDW->A_m[39] = 0.0F;
  rtDW->A_m[47] = 0.0F;
  rtDW->A_m[55] = 0.0F;
  rtDW->A_m[63] = rtU->kalman_Q2;

  /* MATLAB Function: '<S1>/Observer' */
  for (rtDW->ijA = 0; rtDW->ijA < 64; rtDW->ijA++) {
    rtDW->A[rtDW->ijA] = rtDW->A_c[rtDW->ijA] + rtDW->A_m[rtDW->ijA];
  }

  /* '<S3>:1:50' K = P_p*C'/(C*P_p*C'+R); */
  for (rtDW->ijA = 0; rtDW->ijA < 32; rtDW->ijA++) {
    rtDW->b_A_tmp_l[rtDW->ijA] = l[rtDW->ijA];
    rtDW->b_A_tmp_d[rtDW->ijA] = m[rtDW->ijA];
  }

  for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
    for (rtDW->c = 0; rtDW->c < 8; rtDW->c++) {
      rtDW->sector_ref = rtDW->ijA + (rtDW->c << 2);
      rtDW->b_A_tmp[rtDW->sector_ref] = 0.0F;
      for (rtDW->b_ix = 0; rtDW->b_ix < 8; rtDW->b_ix++) {
        rtDW->b_A_tmp[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_d[(rtDW->b_ix
          << 2) + rtDW->ijA] * rtDW->A[(rtDW->c << 3) + rtDW->b_ix];
      }
    }

    for (rtDW->c = 0; rtDW->c < 4; rtDW->c++) {
      rtDW->sector_ref = rtDW->ijA + (rtDW->c << 2);
      rtDW->B_c[rtDW->sector_ref] = 0.0F;
      for (rtDW->b_ix = 0; rtDW->b_ix < 8; rtDW->b_ix++) {
        rtDW->B_c[rtDW->sector_ref] += rtDW->b_A_tmp[(rtDW->b_ix << 2) +
          rtDW->ijA] * (real32_T)rtDW->b_A_tmp_l[(rtDW->c << 3) + rtDW->b_ix];
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
  for (rtDW->ijA = 0; rtDW->ijA < 16; rtDW->ijA++) {
    rtDW->A_k[rtDW->ijA] = rtDW->B_c[rtDW->ijA] + rtDW->fv[rtDW->ijA];
  }

  rtDW->ipiv[0] = 1;
  rtDW->ipiv[1] = 2;
  rtDW->ipiv[2] = 3;
  rtDW->ipiv[3] = 4;
  for (rtDW->i = 0; rtDW->i < 3; rtDW->i++) {
    rtDW->c = rtDW->i * 5;
    rtDW->iy = 0;
    rtDW->ix = rtDW->c;
    rtDW->smax = fabsf(rtDW->A_k[rtDW->c]);
    rtDW->b_ix = 2;
    while (rtDW->b_ix <= 4 - rtDW->i) {
      rtDW->ix++;
      rtDW->SinCos1_o2 = fabsf(rtDW->A_k[rtDW->ix]);
      if (rtDW->SinCos1_o2 > rtDW->smax) {
        rtDW->iy = rtDW->b_ix - 1;
        rtDW->smax = rtDW->SinCos1_o2;
      }

      rtDW->b_ix++;
    }

    if (rtDW->A_k[rtDW->c + rtDW->iy] != 0.0F) {
      if (rtDW->iy != 0) {
        rtDW->sector_ref = rtDW->i + rtDW->iy;
        rtDW->ipiv[rtDW->i] = (int8_T)(rtDW->sector_ref + 1);
        rtDW->smax = rtDW->A_k[rtDW->i];
        rtDW->A_k[rtDW->i] = rtDW->A_k[rtDW->sector_ref];
        rtDW->A_k[rtDW->sector_ref] = rtDW->smax;
        rtDW->smax = rtDW->A_k[rtDW->i + 4];
        rtDW->A_k[rtDW->i + 4] = rtDW->A_k[rtDW->sector_ref + 4];
        rtDW->A_k[rtDW->sector_ref + 4] = rtDW->smax;
        rtDW->smax = rtDW->A_k[rtDW->i + 8];
        rtDW->A_k[rtDW->i + 8] = rtDW->A_k[rtDW->sector_ref + 8];
        rtDW->A_k[rtDW->sector_ref + 8] = rtDW->smax;
        rtDW->smax = rtDW->A_k[rtDW->i + 12];
        rtDW->A_k[rtDW->i + 12] = rtDW->A_k[rtDW->sector_ref + 12];
        rtDW->A_k[rtDW->sector_ref + 12] = rtDW->smax;
      }

      rtDW->ix = (rtDW->c - rtDW->i) + 4;
      rtDW->b_ix = rtDW->c + 1;
      while (rtDW->b_ix + 1 <= rtDW->ix) {
        rtDW->A_k[rtDW->b_ix] /= rtDW->A_k[rtDW->c];
        rtDW->b_ix++;
      }
    }

    rtDW->ix = rtDW->c;
    rtDW->iy = rtDW->c + 4;
    rtDW->kBcol = 0;
    while (rtDW->kBcol <= 2 - rtDW->i) {
      if (rtDW->A_k[rtDW->iy] != 0.0F) {
        rtDW->smax = -rtDW->A_k[rtDW->iy];
        rtDW->c_ix = rtDW->c + 1;
        rtDW->b_ix = (rtDW->ix - rtDW->i) + 8;
        rtDW->ijA = rtDW->ix + 5;
        while (rtDW->ijA + 1 <= rtDW->b_ix) {
          rtDW->A_k[rtDW->ijA] += rtDW->A_k[rtDW->c_ix] * rtDW->smax;
          rtDW->c_ix++;
          rtDW->ijA++;
        }
      }

      rtDW->iy += 4;
      rtDW->ix += 4;
      rtDW->kBcol++;
    }
  }

  for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
    for (rtDW->c = 0; rtDW->c < 8; rtDW->c++) {
      rtDW->sector_ref = rtDW->ijA << 3;
      rtDW->i = rtDW->c + rtDW->sector_ref;
      rtDW->b_A_tmp[rtDW->i] = 0.0F;
      for (rtDW->b_ix = 0; rtDW->b_ix < 8; rtDW->b_ix++) {
        rtDW->b_A_tmp[rtDW->i] += rtDW->A[(rtDW->b_ix << 3) + rtDW->c] *
          (real32_T)rtDW->b_A_tmp_l[rtDW->sector_ref + rtDW->b_ix];
      }
    }
  }

  for (rtDW->i = 0; rtDW->i < 4; rtDW->i++) {
    rtDW->ix = rtDW->i << 3;
    rtDW->iy = rtDW->i << 2;
    rtDW->b_ix = 0;
    while (rtDW->b_ix <= rtDW->i - 1) {
      rtDW->kBcol = rtDW->b_ix << 3;
      rtDW->rtb_i_dq_obs_idx_0 = rtDW->A_k[rtDW->b_ix + rtDW->iy];
      if (rtDW->rtb_i_dq_obs_idx_0 != 0.0F) {
        for (rtDW->c = 0; rtDW->c < 8; rtDW->c++) {
          rtDW->sector_ref = rtDW->c + rtDW->ix;
          rtDW->b_A_tmp[rtDW->sector_ref] -= rtDW->rtb_i_dq_obs_idx_0 *
            rtDW->b_A_tmp[rtDW->c + rtDW->kBcol];
        }
      }

      rtDW->b_ix++;
    }

    rtDW->smax = 1.0F / rtDW->A_k[rtDW->i + rtDW->iy];
    for (rtDW->c = 0; rtDW->c < 8; rtDW->c++) {
      rtDW->sector_ref = rtDW->c + rtDW->ix;
      rtDW->b_A_tmp[rtDW->sector_ref] *= rtDW->smax;
    }
  }

  for (rtDW->i = 3; rtDW->i >= 0; rtDW->i--) {
    rtDW->b_ix = rtDW->i << 3;
    rtDW->iy = (rtDW->i << 2) - 1;
    rtDW->ix = rtDW->i + 2;
    while (rtDW->ix < 5) {
      rtDW->kBcol = (rtDW->ix - 1) << 3;
      if (rtDW->A_k[rtDW->ix + rtDW->iy] != 0.0F) {
        for (rtDW->c = 0; rtDW->c < 8; rtDW->c++) {
          rtDW->sector_ref = rtDW->c + rtDW->b_ix;
          rtDW->b_A_tmp[rtDW->sector_ref] -= rtDW->A_k[rtDW->ix + rtDW->iy] *
            rtDW->b_A_tmp[rtDW->c + rtDW->kBcol];
        }
      }

      rtDW->ix++;
    }
  }

  for (rtDW->i = 2; rtDW->i >= 0; rtDW->i--) {
    ipiv = rtDW->ipiv[rtDW->i];
    if (rtDW->i + 1 != ipiv) {
      for (rtDW->c = 0; rtDW->c < 8; rtDW->c++) {
        rtDW->ijA = (rtDW->i << 3) + rtDW->c;
        rtDW->smax = rtDW->b_A_tmp[rtDW->ijA];
        rtDW->sector_ref = ((ipiv - 1) << 3) + rtDW->c;
        rtDW->b_A_tmp[rtDW->ijA] = rtDW->b_A_tmp[rtDW->sector_ref];
        rtDW->b_A_tmp[rtDW->sector_ref] = rtDW->smax;
      }
    }
  }

  /* '<S3>:1:52' y=[i_d; i_q; i_x; i_y]; */
  /* '<S3>:1:54' x_e = x_p+K*(y-C*x_p); */
  rtDW->m6[0] = rtU->i_dq_pu[0];
  rtDW->m6[1] = rtU->i_dq_pu[1];
  rtDW->m6[2] = rtU->i_xy_pu[0];
  rtDW->m6[3] = rtU->i_xy_pu[1];
  for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
    rtDW->v_t0[rtDW->ijA] = 0.0F;
    for (rtDW->c = 0; rtDW->c < 8; rtDW->c++) {
      rtDW->v_t0[rtDW->ijA] += (real32_T)rtDW->b_A_tmp_d[(rtDW->c << 2) +
        rtDW->ijA] * rtDW->x_p[rtDW->c];
    }

    rtDW->m2[rtDW->ijA] = rtDW->m6[rtDW->ijA] - rtDW->v_t0[rtDW->ijA];
  }

  /* '<S3>:1:56' P_e = P_p-K*C*P_p; */
  for (rtDW->ijA = 0; rtDW->ijA < 8; rtDW->ijA++) {
    rtDW->rtb_i_dq_obs_idx_0 = rtDW->b_A_tmp[rtDW->ijA + 8];
    rtDW->rtb_v_1_idx_pu_idx_1 = rtDW->b_A_tmp[rtDW->ijA + 16];
    rtDW->q = rtDW->b_A_tmp[rtDW->ijA + 24];
    rtDW->x_e[rtDW->ijA] = (((rtDW->rtb_i_dq_obs_idx_0 * rtDW->m2[1] +
      rtDW->b_A_tmp[rtDW->ijA] * rtDW->m2[0]) + rtDW->rtb_v_1_idx_pu_idx_1 *
      rtDW->m2[2]) + rtDW->q * rtDW->m2[3]) + rtDW->x_p[rtDW->ijA];
    for (rtDW->c = 0; rtDW->c < 8; rtDW->c++) {
      rtDW->sector_ref = rtDW->ijA + (rtDW->c << 3);
      rtDW->A_c[rtDW->sector_ref] = 0.0F;
      rtDW->i = rtDW->c << 2;
      rtDW->A_c[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_d[rtDW->i] *
        rtDW->b_A_tmp[rtDW->ijA];
      rtDW->A_c[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_d[rtDW->i + 1] *
        rtDW->rtb_i_dq_obs_idx_0;
      rtDW->A_c[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_d[rtDW->i + 2] *
        rtDW->rtb_v_1_idx_pu_idx_1;
      rtDW->A_c[rtDW->sector_ref] += (real32_T)rtDW->b_A_tmp_d[rtDW->i + 3] *
        rtDW->q;
    }

    for (rtDW->c = 0; rtDW->c < 8; rtDW->c++) {
      rtDW->rtb_i_dq_obs_idx_0 = 0.0F;
      for (rtDW->b_ix = 0; rtDW->b_ix < 8; rtDW->b_ix++) {
        rtDW->rtb_i_dq_obs_idx_0 += rtDW->A_c[(rtDW->b_ix << 3) + rtDW->ijA] *
          rtDW->A[(rtDW->c << 3) + rtDW->b_ix];
      }

      rtDW->sector_ref = (rtDW->c << 3) + rtDW->ijA;
      rtDW->P_e[rtDW->sector_ref] = rtDW->A[rtDW->sector_ref] -
        rtDW->rtb_i_dq_obs_idx_0;
    }
  }

  /* MATLAB Function: '<S1>/delay_compensation_currents' incorporates:
   *  MATLAB Function: '<S1>/Observer'
   *  Switch: '<S1>/Switch1'
   */
  /* '<S3>:1:58' i_dq_obs(1) = x_e(1); */
  /* '<S3>:1:59' i_dq_obs(2) = x_e(2); */
  /* '<S3>:1:60' i_xy_obs(1) = x_e(3); */
  /* '<S3>:1:61' i_xy_obs(2) = x_e(4); */
  /* '<S3>:1:62' e_dq_obs(1) = x_e(5); */
  /* '<S3>:1:63' e_dq_obs(2) = x_e(6); */
  /* '<S3>:1:64' e_xy_obs(1) = x_e(7); */
  /* '<S3>:1:65' e_xy_obs(2) = x_e(8); */
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
  if (rtDW->icLoad_p) {
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
  if (rtDW->icLoad_h) {
    rtDW->Delay4_DSTATE[0] = 0.0F;
    rtDW->Delay4_DSTATE[1] = 0.0F;
    rtDW->Delay4_DSTATE[2] = 0.0F;
    rtDW->Delay4_DSTATE[3] = 0.0F;
  }

  /* Delay: '<S1>/Delay5' */
  if (rtDW->icLoad_b) {
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
  if (rtDW->icLoad_bq) {
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
  for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
    rtDW->m6[rtDW->ijA] = 0.0F;
    for (rtDW->c = 0; rtDW->c < 7; rtDW->c++) {
      rtDW->m6[rtDW->ijA] += rtDW->r[(rtDW->c << 2) + rtDW->ijA] *
        rtDW->Delay1_DSTATE[rtDW->c];
    }

    rtDW->v_t0[rtDW->ijA] = rtDW->m1[rtDW->ijA] + rtDW->m6[rtDW->ijA];
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
  rtDW->rtb_e_xy_obs_g = rtDW->x_e[7];
  rtDW->rtb_e_dq_obs_g = rtDW->x_e[5];

  /* Switch: '<S1>/Switch2' incorporates:
   *  Inport: '<Root>/kalman_off_on'
   *  Switch: '<S1>/Switch3'
   */
  if (!rtU->kalman_off_on) {
    rtDW->rtb_e_dq_obs_idx_0 = 0.0F;
    rtDW->rtb_e_xy_obs_idx_0 = 0.0F;
    rtDW->rtb_e_dq_obs_g = 0.0F;
    rtDW->rtb_e_xy_obs_g = 0.0F;
  }

  /* Trigonometry: '<S1>/SinCos1' incorporates:
   *  Inport: '<Root>/theta_el_pos'
   */
  rtDW->smax = sinf(rtU->theta_el_pos);
  rtDW->SinCos1_o2 = cosf(rtU->theta_el_pos);

  /* Trigonometry: '<S1>/SinCos2' incorporates:
   *  Inport: '<Root>/theta_el_neg'
   */
  rtDW->SinCos2_o1 = sinf(rtU->theta_el_neg);
  rtDW->SinCos2_o2 = cosf(rtU->theta_el_neg);

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
  rtDW->rtb_v_1_idx_pu_idx_1 += rtDW->rtb_e_dq_obs_g;

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
  rtDW->ijA = rtDW->act_sw_1[rtDW->sector_ref - 1];
  rtDW->rtb_v_1_idx_pu_idx_1 = v_alpha_beta_pu[rtDW->ijA - 1];
  rtDW->q = v_alpha_beta_pu[rtDW->ijA + 61];
  rtDW->rtb_i_dq_obs_idx_0 = (rtDW->rtb_v_1_idx_pu_idx_1 * rtDW->SinCos1_o2 +
    rtDW->q * rtDW->smax) * rtU->v_DC_pu;
  rtDW->rtb_v_1_idx_pu_idx_1 = (rtDW->rtb_v_1_idx_pu_idx_1 * -rtDW->smax +
    rtDW->q * rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->rtb_v_1_idx_pu_idx_3 = v_X_Y_pu[rtDW->ijA - 1];
  rtDW->rtb_v_2_idx_pu_idx_0 = v_X_Y_pu[rtDW->ijA + 61];
  rtDW->q = (rtDW->rtb_v_1_idx_pu_idx_3 * rtDW->SinCos2_o2 +
             rtDW->rtb_v_2_idx_pu_idx_0 * rtDW->SinCos2_o1) * rtU->v_DC_pu;
  rtDW->rtb_v_1_idx_pu_idx_3 = (rtDW->rtb_v_1_idx_pu_idx_3 * -rtDW->SinCos2_o1 +
    rtDW->rtb_v_2_idx_pu_idx_0 * rtDW->SinCos2_o2) * rtU->v_DC_pu;

  /* '<S4>:1:167' v_2_idx_pu = [vd_2_idx_pu; vq_2_idx_pu; vx_2_idx_pu; vy_2_idx_pu]; */
  rtDW->ijA = rtDW->act_sw_2[rtDW->sector_ref - 1];
  rtDW->rtb_v_2_idx_pu_idx_1 = v_alpha_beta_pu[rtDW->ijA - 1];
  rtDW->rtb_v_2_idx_pu_idx_2 = v_alpha_beta_pu[rtDW->ijA + 61];
  rtDW->rtb_v_2_idx_pu_idx_0 = (rtDW->rtb_v_2_idx_pu_idx_1 * rtDW->SinCos1_o2 +
    rtDW->rtb_v_2_idx_pu_idx_2 * rtDW->smax) * rtU->v_DC_pu;
  rtDW->rtb_v_2_idx_pu_idx_1 = (rtDW->rtb_v_2_idx_pu_idx_1 * -rtDW->smax +
    rtDW->rtb_v_2_idx_pu_idx_2 * rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->rtb_v_2_idx_pu_idx_3 = v_X_Y_pu[rtDW->ijA - 1];
  rtDW->rtb_v_3_idx_pu_idx_0 = v_X_Y_pu[rtDW->ijA + 61];
  rtDW->rtb_v_2_idx_pu_idx_2 = (rtDW->rtb_v_2_idx_pu_idx_3 * rtDW->SinCos2_o2 +
    rtDW->rtb_v_3_idx_pu_idx_0 * rtDW->SinCos2_o1) * rtU->v_DC_pu;
  rtDW->rtb_v_2_idx_pu_idx_3 = (rtDW->rtb_v_2_idx_pu_idx_3 * -rtDW->SinCos2_o1 +
    rtDW->rtb_v_3_idx_pu_idx_0 * rtDW->SinCos2_o2) * rtU->v_DC_pu;

  /* '<S4>:1:168' v_3_idx_pu = [vd_3_idx_pu; vq_3_idx_pu; vx_3_idx_pu; vy_3_idx_pu]; */
  rtDW->ijA = rtDW->act_sw_3[rtDW->sector_ref - 1];
  rtDW->rtb_v_3_idx_pu_idx_1 = v_alpha_beta_pu[rtDW->ijA - 1];
  rtDW->rtb_v_3_idx_pu_idx_2 = v_alpha_beta_pu[rtDW->ijA + 61];
  rtDW->rtb_v_3_idx_pu_idx_0 = (rtDW->rtb_v_3_idx_pu_idx_1 * rtDW->SinCos1_o2 +
    rtDW->rtb_v_3_idx_pu_idx_2 * rtDW->smax) * rtU->v_DC_pu;
  rtDW->rtb_v_3_idx_pu_idx_1 = (rtDW->rtb_v_3_idx_pu_idx_1 * -rtDW->smax +
    rtDW->rtb_v_3_idx_pu_idx_2 * rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->rtb_v_3_idx_pu_idx_3 = v_X_Y_pu[rtDW->ijA - 1];
  rtDW->rtb_v_4_idx_pu_idx_0 = v_X_Y_pu[rtDW->ijA + 61];
  rtDW->rtb_v_3_idx_pu_idx_2 = (rtDW->rtb_v_3_idx_pu_idx_3 * rtDW->SinCos2_o2 +
    rtDW->rtb_v_4_idx_pu_idx_0 * rtDW->SinCos2_o1) * rtU->v_DC_pu;
  rtDW->rtb_v_3_idx_pu_idx_3 = (rtDW->rtb_v_3_idx_pu_idx_3 * -rtDW->SinCos2_o1 +
    rtDW->rtb_v_4_idx_pu_idx_0 * rtDW->SinCos2_o2) * rtU->v_DC_pu;

  /* '<S4>:1:169' v_4_idx_pu = [vd_4_idx_pu; vq_4_idx_pu; vx_4_idx_pu; vy_4_idx_pu]; */
  rtDW->ijA = rtDW->act_sw_4[rtDW->sector_ref - 1];
  rtDW->rtb_v_4_idx_pu_idx_1 = v_alpha_beta_pu[rtDW->ijA - 1];
  rtDW->rtb_v_4_idx_pu_idx_2 = v_alpha_beta_pu[rtDW->ijA + 61];
  rtDW->rtb_v_4_idx_pu_idx_0 = (rtDW->rtb_v_4_idx_pu_idx_1 * rtDW->SinCos1_o2 +
    rtDW->rtb_v_4_idx_pu_idx_2 * rtDW->smax) * rtU->v_DC_pu;
  rtDW->rtb_v_4_idx_pu_idx_1 = (rtDW->rtb_v_4_idx_pu_idx_1 * -rtDW->smax +
    rtDW->rtb_v_4_idx_pu_idx_2 * rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->rtb_v_4_idx_pu_idx_3 = v_X_Y_pu[rtDW->ijA - 1];
  rtDW->rtb_v_5_idx_pu_idx_0 = v_X_Y_pu[rtDW->ijA + 61];
  rtDW->rtb_v_4_idx_pu_idx_2 = (rtDW->rtb_v_4_idx_pu_idx_3 * rtDW->SinCos2_o2 +
    rtDW->rtb_v_5_idx_pu_idx_0 * rtDW->SinCos2_o1) * rtU->v_DC_pu;
  rtDW->rtb_v_4_idx_pu_idx_3 = (rtDW->rtb_v_4_idx_pu_idx_3 * -rtDW->SinCos2_o1 +
    rtDW->rtb_v_5_idx_pu_idx_0 * rtDW->SinCos2_o2) * rtU->v_DC_pu;

  /* '<S4>:1:170' v_5_idx_pu = [vd_5_idx_pu; vq_5_idx_pu; vx_5_idx_pu; vy_5_idx_pu]; */
  rtDW->ijA = rtDW->act_sw_5[rtDW->sector_ref - 1];
  rtDW->rtb_v_5_idx_pu_idx_1 = v_alpha_beta_pu[rtDW->ijA - 1];
  rtDW->rtb_v_5_idx_pu_idx_2 = v_alpha_beta_pu[rtDW->ijA + 61];
  rtDW->rtb_v_5_idx_pu_idx_0 = (rtDW->rtb_v_5_idx_pu_idx_1 * rtDW->SinCos1_o2 +
    rtDW->rtb_v_5_idx_pu_idx_2 * rtDW->smax) * rtU->v_DC_pu;
  rtDW->rtb_v_5_idx_pu_idx_1 = (rtDW->rtb_v_5_idx_pu_idx_1 * -rtDW->smax +
    rtDW->rtb_v_5_idx_pu_idx_2 * rtDW->SinCos1_o2) * rtU->v_DC_pu;
  rtDW->smax = v_X_Y_pu[rtDW->ijA - 1];
  rtDW->SinCos1_o2 = v_X_Y_pu[rtDW->ijA + 61];
  rtDW->rtb_v_5_idx_pu_idx_2 = (rtDW->smax * rtDW->SinCos2_o2 + rtDW->SinCos1_o2
    * rtDW->SinCos2_o1) * rtU->v_DC_pu;
  rtDW->rtb_v_5_idx_pu_idx_3 = (rtDW->smax * -rtDW->SinCos2_o1 +
    rtDW->SinCos1_o2 * rtDW->SinCos2_o2) * rtU->v_DC_pu;

  /* MATLAB Function: '<S1>/state_space_mdl' incorporates:
   *  Inport: '<Root>/HC_off_on'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/Ts_times_ZB_over_Lx'
   *  Inport: '<Root>/Ts_times_ZB_over_Ly'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/phiPM_h'
   *  Inport: '<Root>/psiPM_h_pu'
   *  Inport: '<Root>/theta_el_neg'
   */
  /* MATLAB Function 'uz_codegen/state_space_mdl': '<S10>:1' */
  /* '<S10>:1:3' A = [ -Ts_times_ZB_over_Ld*Rs_over_ZB            Ts_times_ZB_over_Ld*Lq_over_LB*w_e_pu   0                                      0                               ; */
  /* '<S10>:1:4'       -Ts_times_ZB_over_Lq*Ld_over_LB*w_e_pu    -Ts_times_ZB_over_Lq*Rs_over_ZB          0                                      0                               ; */
  /* '<S10>:1:5'       0                                          0                                       -Ts_times_ZB_over_Lx*Rs_over_ZB        -Ly_over_LB*w_e_pu              ; */
  /* '<S10>:1:6'       0                                          0                                        Lx_over_LB*w_e_pu                     -Ts_times_ZB_over_Ly*Rs_over_ZB]; */
  rtDW->A_k[0] = -rtU->Ts_times_ZB_over_Ld * rtU->Rs_over_ZB;
  rtDW->A_k[4] = rtDW->x0_idx_0;
  rtDW->A_k[8] = 0.0F;
  rtDW->A_k[12] = 0.0F;
  rtDW->A_k[1] = rtDW->x0_idx_1;
  rtDW->A_k[5] = -rtU->Ts_times_ZB_over_Lq * rtU->Rs_over_ZB;
  rtDW->A_k[9] = 0.0F;
  rtDW->A_k[13] = 0.0F;
  rtDW->A_k[2] = 0.0F;
  rtDW->A_k[6] = 0.0F;
  rtDW->A_k[10] = -rtU->Ts_times_ZB_over_Lx * rtU->Rs_over_ZB;
  rtDW->A_k[14] = rtDW->x0_idx_2;
  rtDW->A_k[3] = 0.0F;
  rtDW->A_k[7] = 0.0F;
  rtDW->A_k[11] = rtDW->x0_idx_3;
  rtDW->A_k[15] = -rtU->Ts_times_ZB_over_Ly * rtU->Rs_over_ZB;

  /* '<S10>:1:8' psiPM5 = psiPM_h_pu(1); */
  /* '<S10>:1:9' psiPM7 = psiPM_h_pu(2); */
  /* '<S10>:1:11' phi5 = phiPM_h(1); */
  /* '<S10>:1:12' phi7 = phiPM_h(2); */
  /*  w3theta_el = single(3*theta_el); */
  /* '<S10>:1:15' w6theta_el = single(6*theta_el); */
  rtDW->SinCos2_o2 = 6.0F * rtU->theta_el_neg;

  /*  w9theta_el = single(9*theta_el); */
  /*  w12theta_el = single(12*theta_el); */
  /* '<S10>:1:19' B = [Ts_times_ZB_over_Ld    0                       0                       0                       ; */
  /* '<S10>:1:20'      0                      Ts_times_ZB_over_Lq     0                       0                       ; */
  /* '<S10>:1:21'      0                      0                       Ts_times_ZB_over_Lx     0                       ; */
  /* '<S10>:1:22'      0                      0                       0                       Ts_times_ZB_over_Ly     ]; */
  rtDW->B_c[0] = rtU->Ts_times_ZB_over_Ld;
  rtDW->B_c[4] = 0.0F;
  rtDW->B_c[8] = 0.0F;
  rtDW->B_c[12] = 0.0F;
  rtDW->B_c[1] = 0.0F;
  rtDW->B_c[5] = rtU->Ts_times_ZB_over_Lq;
  rtDW->B_c[9] = 0.0F;
  rtDW->B_c[13] = 0.0F;
  rtDW->B_c[2] = 0.0F;
  rtDW->B_c[6] = 0.0F;
  rtDW->B_c[10] = rtU->Ts_times_ZB_over_Lx;
  rtDW->B_c[14] = 0.0F;
  rtDW->B_c[3] = 0.0F;
  rtDW->B_c[7] = 0.0F;
  rtDW->B_c[11] = 0.0F;
  rtDW->B_c[15] = rtU->Ts_times_ZB_over_Ly;

  /* '<S10>:1:24' C = [1   0   0   0; */
  /* '<S10>:1:25'      0   1   0   0; */
  /* '<S10>:1:26'      0   0   1   0; */
  /* '<S10>:1:27'      0   0   0   1]; */
  /* '<S10>:1:29' D = [    e_dq_obs(1); */
  /* '<S10>:1:30'          -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB + e_dq_obs(2); */
  /* '<S10>:1:31'          e_xy_obs(1); */
  /* '<S10>:1:32'          e_xy_obs(2)]; */
  rtDW->D[0] = rtDW->rtb_e_dq_obs_idx_0;
  rtDW->x0_idx_0 = rtDW->A_me + rtDW->rtb_e_dq_obs_g;
  rtDW->D[1] = rtDW->x0_idx_0;
  rtDW->D[2] = rtDW->rtb_e_xy_obs_idx_0;
  rtDW->D[3] = rtDW->rtb_e_xy_obs_g;

  /* '<S10>:1:34' E = [    e_dq_obs(1); */
  /* '<S10>:1:35'          -w_e_pu*Ts_times_ZB_over_Lq*psi_pm_over_psiB + e_dq_obs(2); */
  /* '<S10>:1:36'          -w_e_pu*(psiPM5*sin(w6theta_el+phi5) - psiPM7*sin(w6theta_el+phi7)-psiPM5*6*sin(w6theta_el+phi5) - psiPM7*6*sin(w6theta_el+phi7)) + e_xy_obs(1); */
  /* '<S10>:1:37'          -w_e_pu*(psiPM5*cos(w6theta_el+phi5) + psiPM7*cos(w6theta_el+phi7) + psiPM5*6*cos(w6theta_el+phi5) - psiPM7*6*cos(w6theta_el+phi7)) + e_xy_obs(2)]; */
  rtDW->x0_idx_1 = rtDW->SinCos2_o2 + rtU->phiPM_h[0];
  rtDW->smax = sinf(rtDW->x0_idx_1);
  rtDW->x0_idx_2 = rtDW->SinCos2_o2 + rtU->phiPM_h[1];
  rtDW->SinCos1_o2 = sinf(rtDW->x0_idx_2);
  rtDW->SinCos2_o1 = cosf(rtDW->x0_idx_1);
  rtDW->SinCos2_o2 = cosf(rtDW->x0_idx_2);
  rtDW->E[0] = rtDW->rtb_e_dq_obs_idx_0;
  rtDW->E[1] = rtDW->x0_idx_0;
  rtDW->E[2] = (((rtU->psiPM_h_pu[0] * rtDW->smax - rtU->psiPM_h_pu[1] *
                  rtDW->SinCos1_o2) - rtU->psiPM_h_pu[0] * 6.0F * rtDW->smax) -
                rtU->psiPM_h_pu[1] * 6.0F * rtDW->SinCos1_o2) *
    -rtU->omega_el_pu + rtDW->rtb_e_xy_obs_idx_0;
  rtDW->E[3] = (((rtU->psiPM_h_pu[0] * rtDW->SinCos2_o1 + rtU->psiPM_h_pu[1] *
                  rtDW->SinCos2_o2) + rtU->psiPM_h_pu[0] * 6.0F *
                 rtDW->SinCos2_o1) - rtU->psiPM_h_pu[1] * 6.0F *
                rtDW->SinCos2_o2) * -rtU->omega_el_pu + rtDW->rtb_e_xy_obs_g;

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
    rtDW->ijA = 0;
  } else if (rtU->HC_off_on) {
    rtDW->ijA = 1;
  } else {
    rtDW->ijA = -1;
  }

  switch (rtDW->ijA) {
   case 0:
    /* '<S10>:1:52' case false */
    /* '<S10>:1:53' m0 = C*(A*x0+B*u0+D).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->E_p[rtDW->ijA] = (rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + rtDW->D
        [rtDW->ijA];
    }

    /* '<S10>:1:54' m1 = C*(A*x0+B*u1+D).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m6[rtDW->ijA] = ((real32_T)b[rtDW->ijA + 12] * rtDW->E_p[3] +
        ((real32_T)b[rtDW->ijA + 8] * rtDW->E_p[2] + ((real32_T)b[rtDW->ijA + 4]
        * rtDW->E_p[1] + (real32_T)b[rtDW->ijA] * rtDW->E_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->ijA] = ((rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + (rtDW->
        B_c[rtDW->ijA + 12] * rtDW->rtb_v_1_idx_pu_idx_3 + (rtDW->B_c[rtDW->ijA
        + 8] * rtDW->q + (rtDW->B_c[rtDW->ijA + 4] * rtDW->rtb_v_1_idx_pu_idx_1
                          + rtDW->B_c[rtDW->ijA] * rtDW->rtb_i_dq_obs_idx_0))))
        + rtDW->D[rtDW->ijA];
    }

    /* '<S10>:1:55' m2 = C*(A*x0+B*u2+D).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m1[rtDW->ijA] = ((real32_T)b[rtDW->ijA + 12] * rtDW->E_c[3] +
        ((real32_T)b[rtDW->ijA + 8] * rtDW->E_c[2] + ((real32_T)b[rtDW->ijA + 4]
        * rtDW->E_c[1] + (real32_T)b[rtDW->ijA] * rtDW->E_c[0]))) * 2.0F;
      rtDW->E_p[rtDW->ijA] = ((rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + (rtDW->
        B_c[rtDW->ijA + 12] * rtDW->rtb_v_2_idx_pu_idx_3 + (rtDW->B_c[rtDW->ijA
        + 8] * rtDW->rtb_v_2_idx_pu_idx_2 + (rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_2_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_2_idx_pu_idx_0)))) + rtDW->D[rtDW->ijA];
    }

    /* '<S10>:1:56' m3 = C*(A*x0+B*u3+D).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m2[rtDW->ijA] = ((real32_T)b[rtDW->ijA + 12] * rtDW->E_p[3] +
        ((real32_T)b[rtDW->ijA + 8] * rtDW->E_p[2] + ((real32_T)b[rtDW->ijA + 4]
        * rtDW->E_p[1] + (real32_T)b[rtDW->ijA] * rtDW->E_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->ijA] = ((rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + (rtDW->
        B_c[rtDW->ijA + 12] * rtDW->rtb_v_3_idx_pu_idx_3 + (rtDW->B_c[rtDW->ijA
        + 8] * rtDW->rtb_v_3_idx_pu_idx_2 + (rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_3_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_3_idx_pu_idx_0)))) + rtDW->D[rtDW->ijA];
    }

    /* '<S10>:1:57' m4 = C*(A*x0+B*u4+D).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m3[rtDW->ijA] = ((real32_T)b[rtDW->ijA + 12] * rtDW->E_c[3] +
        ((real32_T)b[rtDW->ijA + 8] * rtDW->E_c[2] + ((real32_T)b[rtDW->ijA + 4]
        * rtDW->E_c[1] + (real32_T)b[rtDW->ijA] * rtDW->E_c[0]))) * 2.0F;
      rtDW->E_p[rtDW->ijA] = ((rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + (rtDW->
        B_c[rtDW->ijA + 12] * rtDW->rtb_v_4_idx_pu_idx_3 + (rtDW->B_c[rtDW->ijA
        + 8] * rtDW->rtb_v_4_idx_pu_idx_2 + (rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_4_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_4_idx_pu_idx_0)))) + rtDW->D[rtDW->ijA];
    }

    /* '<S10>:1:58' m5 = C*(A*x0+B*u5+D).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m4[rtDW->ijA] = ((real32_T)b[rtDW->ijA + 12] * rtDW->E_p[3] +
        ((real32_T)b[rtDW->ijA + 8] * rtDW->E_p[2] + ((real32_T)b[rtDW->ijA + 4]
        * rtDW->E_p[1] + (real32_T)b[rtDW->ijA] * rtDW->E_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->ijA] = ((rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + (rtDW->
        B_c[rtDW->ijA + 12] * rtDW->rtb_v_5_idx_pu_idx_3 + (rtDW->B_c[rtDW->ijA
        + 8] * rtDW->rtb_v_5_idx_pu_idx_2 + (rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_5_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_5_idx_pu_idx_0)))) + rtDW->D[rtDW->ijA];
    }

    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->E[rtDW->ijA] = ((real32_T)b[rtDW->ijA + 12] * rtDW->E_c[3] +
                            ((real32_T)b[rtDW->ijA + 8] * rtDW->E_c[2] +
        ((real32_T)b[rtDW->ijA + 4] * rtDW->E_c[1] + (real32_T)b[rtDW->ijA] *
         rtDW->E_c[0]))) * 2.0F;
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
    for (rtDW->ijA = 0; rtDW->ijA < 16; rtDW->ijA++) {
      rtDW->rtb_m6_tmp[rtDW->ijA] = b[rtDW->ijA];
    }

    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->E_p[rtDW->ijA] = (rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + rtDW->E
        [rtDW->ijA];
    }

    /* '<S10>:1:69' m1 = C*(A*x0+B*u1+E).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m6[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
        rtDW->E_p[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 8] * rtDW->E_p[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] * rtDW->
                           E_p[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] *
                           rtDW->E_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->ijA] = ((rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + (rtDW->
        B_c[rtDW->ijA + 12] * rtDW->rtb_v_1_idx_pu_idx_3 + (rtDW->B_c[rtDW->ijA
        + 8] * rtDW->q + (rtDW->B_c[rtDW->ijA + 4] * rtDW->rtb_v_1_idx_pu_idx_1
                          + rtDW->B_c[rtDW->ijA] * rtDW->rtb_i_dq_obs_idx_0))))
        + rtDW->E[rtDW->ijA];
    }

    /* '<S10>:1:70' m2 = C*(A*x0+B*u2+E).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m1[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
        rtDW->E_c[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 8] * rtDW->E_c[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] * rtDW->
                           E_c[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] *
                           rtDW->E_c[0]))) * 2.0F;
      rtDW->E_p[rtDW->ijA] = ((rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + (rtDW->
        B_c[rtDW->ijA + 12] * rtDW->rtb_v_2_idx_pu_idx_3 + (rtDW->B_c[rtDW->ijA
        + 8] * rtDW->rtb_v_2_idx_pu_idx_2 + (rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_2_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_2_idx_pu_idx_0)))) + rtDW->E[rtDW->ijA];
    }

    /* '<S10>:1:71' m3 = C*(A*x0+B*u3+E).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m2[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
        rtDW->E_p[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 8] * rtDW->E_p[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] * rtDW->
                           E_p[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] *
                           rtDW->E_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->ijA] = ((rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + (rtDW->
        B_c[rtDW->ijA + 12] * rtDW->rtb_v_3_idx_pu_idx_3 + (rtDW->B_c[rtDW->ijA
        + 8] * rtDW->rtb_v_3_idx_pu_idx_2 + (rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_3_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_3_idx_pu_idx_0)))) + rtDW->E[rtDW->ijA];
    }

    /* '<S10>:1:72' m4 = C*(A*x0+B*u4+E).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m3[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
        rtDW->E_c[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 8] * rtDW->E_c[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] * rtDW->
                           E_c[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] *
                           rtDW->E_c[0]))) * 2.0F;
      rtDW->E_p[rtDW->ijA] = ((rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + (rtDW->
        B_c[rtDW->ijA + 12] * rtDW->rtb_v_4_idx_pu_idx_3 + (rtDW->B_c[rtDW->ijA
        + 8] * rtDW->rtb_v_4_idx_pu_idx_2 + (rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_4_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_4_idx_pu_idx_0)))) + rtDW->E[rtDW->ijA];
    }

    /* '<S10>:1:73' m5 = C*(A*x0+B*u5+E).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m4[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
        rtDW->E_p[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 8] * rtDW->E_p[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] * rtDW->
                           E_p[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] *
                           rtDW->E_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->ijA] = ((rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
        rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0))) + (rtDW->
        B_c[rtDW->ijA + 12] * rtDW->rtb_v_5_idx_pu_idx_3 + (rtDW->B_c[rtDW->ijA
        + 8] * rtDW->rtb_v_5_idx_pu_idx_2 + (rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_5_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_5_idx_pu_idx_0)))) + rtDW->E[rtDW->ijA];
    }

    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->E[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
                            rtDW->E_c[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA
        + 8] * rtDW->E_c[2] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] *
        rtDW->E_c[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] * rtDW->E_c[0]))) *
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
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->E[rtDW->ijA] = rtDW->A_k[rtDW->ijA + 12] * rtDW->x0_idx_3 +
        (rtDW->A_k[rtDW->ijA + 8] * rtDW->x0_idx_2 + (rtDW->A_k[rtDW->ijA + 4] *
          rtDW->x0_idx_1 + rtDW->A_k[rtDW->ijA] * rtDW->x0_idx_0));
    }

    for (rtDW->ijA = 0; rtDW->ijA < 16; rtDW->ijA++) {
      rtDW->rtb_m6_tmp[rtDW->ijA] = b[rtDW->ijA];
    }

    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->E_p[rtDW->ijA] = rtDW->E[rtDW->ijA] + rtDW->D[rtDW->ijA];
    }

    /* '<S10>:1:84' m1 = C*(A*x0+B*u1+D).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m6[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
        rtDW->E_p[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 8] * rtDW->E_p[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] * rtDW->
                           E_p[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] *
                           rtDW->E_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->ijA] = ((((rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_1_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_i_dq_obs_idx_0) + rtDW->B_c[rtDW->ijA + 8] * rtDW->q) +
        rtDW->B_c[rtDW->ijA + 12] * rtDW->rtb_v_1_idx_pu_idx_3) + rtDW->E
        [rtDW->ijA]) + rtDW->D[rtDW->ijA];
    }

    /* '<S10>:1:85' m2 = C*(A*x0+B*u2+D).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m1[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
        rtDW->E_c[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 8] * rtDW->E_c[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] * rtDW->
                           E_c[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] *
                           rtDW->E_c[0]))) * 2.0F;
      rtDW->E_p[rtDW->ijA] = ((((rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_2_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_2_idx_pu_idx_0) + rtDW->B_c[rtDW->ijA + 8] *
        rtDW->rtb_v_2_idx_pu_idx_2) + rtDW->B_c[rtDW->ijA + 12] *
        rtDW->rtb_v_2_idx_pu_idx_3) + rtDW->E[rtDW->ijA]) + rtDW->D[rtDW->ijA];
    }

    /* '<S10>:1:86' m3 = C*(A*x0+B*u3+D).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m2[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
        rtDW->E_p[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 8] * rtDW->E_p[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] * rtDW->
                           E_p[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] *
                           rtDW->E_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->ijA] = ((((rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_3_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_3_idx_pu_idx_0) + rtDW->B_c[rtDW->ijA + 8] *
        rtDW->rtb_v_3_idx_pu_idx_2) + rtDW->B_c[rtDW->ijA + 12] *
        rtDW->rtb_v_3_idx_pu_idx_3) + rtDW->E[rtDW->ijA]) + rtDW->D[rtDW->ijA];
    }

    /* '<S10>:1:87' m4 = C*(A*x0+B*u4+D).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m3[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
        rtDW->E_c[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 8] * rtDW->E_c[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] * rtDW->
                           E_c[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] *
                           rtDW->E_c[0]))) * 2.0F;
      rtDW->E_p[rtDW->ijA] = ((((rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_4_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_4_idx_pu_idx_0) + rtDW->B_c[rtDW->ijA + 8] *
        rtDW->rtb_v_4_idx_pu_idx_2) + rtDW->B_c[rtDW->ijA + 12] *
        rtDW->rtb_v_4_idx_pu_idx_3) + rtDW->E[rtDW->ijA]) + rtDW->D[rtDW->ijA];
    }

    /* '<S10>:1:88' m5 = C*(A*x0+B*u5+D).*2; */
    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->m4[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
        rtDW->E_p[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 8] * rtDW->E_p[2]
                        + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] * rtDW->
                           E_p[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] *
                           rtDW->E_p[0]))) * 2.0F;
      rtDW->E_c[rtDW->ijA] = ((((rtDW->B_c[rtDW->ijA + 4] *
        rtDW->rtb_v_5_idx_pu_idx_1 + rtDW->B_c[rtDW->ijA] *
        rtDW->rtb_v_5_idx_pu_idx_0) + rtDW->B_c[rtDW->ijA + 8] *
        rtDW->rtb_v_5_idx_pu_idx_2) + rtDW->B_c[rtDW->ijA + 12] *
        rtDW->rtb_v_5_idx_pu_idx_3) + rtDW->E[rtDW->ijA]) + rtDW->D[rtDW->ijA];
    }

    for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
      rtDW->E[rtDW->ijA] = ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 12] *
                            rtDW->E_c[3] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA
        + 8] * rtDW->E_c[2] + ((real32_T)rtDW->rtb_m6_tmp[rtDW->ijA + 4] *
        rtDW->E_c[1] + (real32_T)rtDW->rtb_m6_tmp[rtDW->ijA] * rtDW->E_c[0]))) *
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
  rtDW->A_k[0] = rtU->lambda;
  rtDW->A_k[4] = 0.0F;
  rtDW->A_k[8] = 0.0F;
  rtDW->A_k[12] = 0.0F;
  rtDW->A_k[1] = 0.0F;
  rtDW->A_k[5] = rtU->lambda;
  rtDW->A_k[9] = 0.0F;
  rtDW->A_k[13] = 0.0F;
  rtDW->A_k[2] = 0.0F;
  rtDW->A_k[6] = 0.0F;
  rtDW->A_k[10] = rtU->lambda;
  rtDW->A_k[14] = 0.0F;
  rtDW->A_k[3] = 0.0F;
  rtDW->A_k[7] = 0.0F;
  rtDW->A_k[11] = 0.0F;
  rtDW->A_k[15] = rtU->lambda;

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
  for (rtDW->ijA = 0; rtDW->ijA < 4; rtDW->ijA++) {
    rtDW->r[rtDW->ijA] = rtDW->D[rtDW->ijA];
    rtDW->r[rtDW->ijA + 4] = rtDW->D[rtDW->ijA];
    rtDW->r[rtDW->ijA + 8] = rtDW->D[rtDW->ijA];
    rtDW->r[rtDW->ijA + 12] = rtDW->D[rtDW->ijA];
    rtDW->r[rtDW->ijA + 16] = rtDW->D[rtDW->ijA];
    rtDW->r[rtDW->ijA + 20] = rtDW->D[rtDW->ijA];
    rtDW->x0_idx_2 = rtDW->A_k[rtDW->ijA + 4];
    rtDW->x0_idx_3 = rtDW->A_k[rtDW->ijA + 8];
    rtDW->A_me = rtDW->A_k[rtDW->ijA + 12];
    rtDW->r[rtDW->ijA + 24] = rtDW->A_me * rtDW->D[3] + (rtDW->x0_idx_3 *
      rtDW->D[2] + (rtDW->x0_idx_2 * rtDW->D[1] + rtDW->A_k[rtDW->ijA] * rtDW->
                    D[0]));
    rtDW->x0_idx_0 = rtDW->A_k[rtDW->ijA];
    rtDW->x0_idx_1 = rtDW->A_me * rtDW->m6[3] + (rtDW->x0_idx_3 * rtDW->m6[2] +
      (rtDW->x0_idx_2 * rtDW->m6[1] + rtDW->x0_idx_0 * rtDW->m6[0]));
    rtDW->M[rtDW->ijA] = rtDW->m6[rtDW->ijA];
    rtDW->M[rtDW->ijA + 28] = 0.0F;
    rtDW->M[rtDW->ijA + 56] = 0.0F;
    rtDW->M[rtDW->ijA + 84] = 0.0F;
    rtDW->M[rtDW->ijA + 112] = 0.0F;
    rtDW->M[rtDW->ijA + 140] = 0.0F;
    rtDW->M[rtDW->ijA + 168] = 0.0F;
    rtDW->M[rtDW->ijA + 4] = rtDW->m6[rtDW->ijA];
    rtDW->M[rtDW->ijA + 32] = rtDW->m1[rtDW->ijA];
    rtDW->M[rtDW->ijA + 60] = 0.0F;
    rtDW->M[rtDW->ijA + 88] = 0.0F;
    rtDW->M[rtDW->ijA + 116] = 0.0F;
    rtDW->M[rtDW->ijA + 144] = 0.0F;
    rtDW->M[rtDW->ijA + 172] = 0.0F;
    rtDW->M[rtDW->ijA + 8] = rtDW->m6[rtDW->ijA];
    rtDW->M[rtDW->ijA + 36] = rtDW->m1[rtDW->ijA];
    rtDW->M[rtDW->ijA + 64] = rtDW->m2[rtDW->ijA];
    rtDW->M[rtDW->ijA + 92] = 0.0F;
    rtDW->M[rtDW->ijA + 120] = 0.0F;
    rtDW->M[rtDW->ijA + 148] = 0.0F;
    rtDW->M[rtDW->ijA + 176] = 0.0F;
    rtDW->M[rtDW->ijA + 12] = rtDW->m6[rtDW->ijA];
    rtDW->M[rtDW->ijA + 40] = rtDW->m1[rtDW->ijA];
    rtDW->M[rtDW->ijA + 68] = rtDW->m2[rtDW->ijA];
    rtDW->M[rtDW->ijA + 96] = rtDW->m3[rtDW->ijA];
    rtDW->M[rtDW->ijA + 124] = 0.0F;
    rtDW->M[rtDW->ijA + 152] = 0.0F;
    rtDW->M[rtDW->ijA + 180] = 0.0F;
    rtDW->M[rtDW->ijA + 16] = rtDW->m6[rtDW->ijA];
    rtDW->M[rtDW->ijA + 44] = rtDW->m1[rtDW->ijA];
    rtDW->M[rtDW->ijA + 72] = rtDW->m2[rtDW->ijA];
    rtDW->M[rtDW->ijA + 100] = rtDW->m3[rtDW->ijA];
    rtDW->M[rtDW->ijA + 128] = rtDW->m4[rtDW->ijA];
    rtDW->M[rtDW->ijA + 156] = 0.0F;
    rtDW->M[rtDW->ijA + 184] = 0.0F;
    rtDW->M[rtDW->ijA + 20] = rtDW->m6[rtDW->ijA];
    rtDW->M[rtDW->ijA + 48] = rtDW->m1[rtDW->ijA];
    rtDW->M[rtDW->ijA + 76] = rtDW->m2[rtDW->ijA];
    rtDW->M[rtDW->ijA + 104] = rtDW->m3[rtDW->ijA];
    rtDW->M[rtDW->ijA + 132] = rtDW->m4[rtDW->ijA];
    rtDW->M[rtDW->ijA + 160] = rtDW->E[rtDW->ijA];
    rtDW->M[rtDW->ijA + 188] = 0.0F;
    rtDW->M[rtDW->ijA + 24] = rtDW->x0_idx_1;
    rtDW->M[rtDW->ijA + 52] = rtDW->A_me * rtDW->m1[3] + (rtDW->x0_idx_3 *
      rtDW->m1[2] + (rtDW->x0_idx_2 * rtDW->m1[1] + rtDW->x0_idx_0 * rtDW->m1[0]));
    rtDW->M[rtDW->ijA + 80] = rtDW->A_me * rtDW->m2[3] + (rtDW->x0_idx_3 *
      rtDW->m2[2] + (rtDW->x0_idx_2 * rtDW->m2[1] + rtDW->x0_idx_0 * rtDW->m2[0]));
    rtDW->M[rtDW->ijA + 108] = rtDW->A_me * rtDW->m3[3] + (rtDW->x0_idx_3 *
      rtDW->m3[2] + (rtDW->x0_idx_2 * rtDW->m3[1] + rtDW->x0_idx_0 * rtDW->m3[0]));
    rtDW->M[rtDW->ijA + 136] = rtDW->A_me * rtDW->m4[3] + (rtDW->x0_idx_3 *
      rtDW->m4[2] + (rtDW->x0_idx_2 * rtDW->m4[1] + rtDW->x0_idx_0 * rtDW->m4[0]));
    rtDW->M[rtDW->ijA + 164] = rtDW->A_me * rtDW->E[3] + (rtDW->x0_idx_3 *
      rtDW->E[2] + (rtDW->x0_idx_2 * rtDW->E[1] + rtDW->x0_idx_0 * rtDW->E[0]));
    rtDW->M[rtDW->ijA + 192] = rtDW->x0_idx_1;
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
  /* '<S8>:1:25' [x_opt,iter] = mpc_solve(H,f,A,b,Aeq,beq,iA0,max_iter,tol); */
  /* '<S8>:1:30' x = single([0 0 0 0 0 0 0]'); */
  /* '<S8>:1:31' iter = single(0); */
  /*  set up solver */
  /* '<S8>:1:33' options = mpcActiveSetOptions('single'); */
  /* '<S8>:1:34' options.MaxIterations = max_iter; */
  /* '<S8>:1:35' options.ConstriantTolerance = tol; */
  /* '<S8>:1:36' options.UseHessianAsInput = false; */
  /* '<S8>:1:37' options.IntegrityChecks = false; */
  /* '<S8>:1:40' x_tmp = single([0.5 0 0 0 0 0 0.5]'); */
  /* '<S8>:1:41' exitflag = single(0); */
  /*  calculate inverse of H */
  /* '<S8>:1:43' [L,~] = chol(H,'lower'); */
  for (rtDW->ijA = 0; rtDW->ijA < 7; rtDW->ijA++) {
    for (rtDW->c = 0; rtDW->c < 7; rtDW->c++) {
      rtDW->i = rtDW->ijA + 7 * rtDW->c;
      rtDW->Linv_data[rtDW->i] = 0.0F;
      for (rtDW->b_ix = 0; rtDW->b_ix < 28; rtDW->b_ix++) {
        rtDW->Linv_data[rtDW->i] += rtDW->M[28 * rtDW->ijA + rtDW->b_ix] *
          rtDW->M[28 * rtDW->c + rtDW->b_ix];
      }
    }
  }

  /* MATLAB Function: '<S1>/qp_solver' incorporates:
   *  Inport: '<Root>/max_iter'
   *  MATLAB Function: '<S1>/formulate_qp'
   */
  for (rtDW->ijA = 0; rtDW->ijA < 49; rtDW->ijA++) {
    rtDW->Hinv_data[rtDW->ijA] = rtDW->Linv_data[rtDW->ijA] * 2.0F;
  }

  rtDW->c = 0;
  rtDW->i = 0;
  exitg1 = false;
  while ((!exitg1) && (rtDW->i < 7)) {
    rtDW->kBcol = rtDW->i * 7 + rtDW->i;
    rtDW->smax = 0.0F;
    if (rtDW->i >= 1) {
      rtDW->b_ix = rtDW->i;
      rtDW->iy = rtDW->i;
      rtDW->ix = 0;
      while (rtDW->ix <= rtDW->i - 1) {
        rtDW->smax += rtDW->Hinv_data[rtDW->b_ix] * rtDW->Hinv_data[rtDW->iy];
        rtDW->b_ix += 7;
        rtDW->iy += 7;
        rtDW->ix++;
      }
    }

    rtDW->smax = rtDW->Hinv_data[rtDW->kBcol] - rtDW->smax;
    if (rtDW->smax > 0.0F) {
      rtDW->smax = sqrtf(rtDW->smax);
      rtDW->Hinv_data[rtDW->kBcol] = rtDW->smax;
      if (rtDW->i + 1 < 7) {
        if (rtDW->i != 0) {
          rtDW->ix = rtDW->i;
          rtDW->b_ix = ((rtDW->i - 1) * 7 + rtDW->i) + 2;
          rtDW->c_ix = rtDW->i + 2;
          while (rtDW->c_ix <= rtDW->b_ix) {
            rtDW->SinCos1_o2 = -rtDW->Hinv_data[rtDW->ix];
            rtDW->iy = rtDW->kBcol + 1;
            rtDW->ijA = (rtDW->c_ix - rtDW->i) + 5;
            rtDW->ia = rtDW->c_ix;
            while (rtDW->ia <= rtDW->ijA) {
              rtDW->Hinv_data[rtDW->iy] += rtDW->Hinv_data[rtDW->ia - 1] *
                rtDW->SinCos1_o2;
              rtDW->iy++;
              rtDW->ia++;
            }

            rtDW->ix += 7;
            rtDW->c_ix += 7;
          }
        }

        rtDW->smax = 1.0F / rtDW->smax;
        rtDW->ix = (rtDW->kBcol - rtDW->i) + 7;
        rtDW->b_ix = rtDW->kBcol + 1;
        while (rtDW->b_ix + 1 <= rtDW->ix) {
          rtDW->Hinv_data[rtDW->b_ix] *= rtDW->smax;
          rtDW->b_ix++;
        }
      }

      rtDW->i++;
    } else {
      rtDW->Hinv_data[rtDW->kBcol] = rtDW->smax;
      rtDW->c = rtDW->i + 1;
      exitg1 = true;
    }
  }

  if (rtDW->c == 0) {
    rtDW->b_ix = 7;
  } else {
    rtDW->b_ix = rtDW->c - 1;
  }

  rtDW->i = 1;
  while (rtDW->i + 1 <= rtDW->b_ix) {
    rtDW->c = 0;
    while (rtDW->c <= rtDW->i - 1) {
      rtDW->Hinv_data[rtDW->c + 7 * rtDW->i] = 0.0F;
      rtDW->c++;
    }

    rtDW->i++;
  }

  if (1 > rtDW->b_ix) {
    rtDW->ijA = -1;
    rtDW->c = -1;
    rtDW->iy = -1;
  } else {
    rtDW->ijA = rtDW->b_ix - 1;
    rtDW->c = rtDW->b_ix - 1;
    rtDW->iy = rtDW->b_ix - 1;
  }

  rtDW->ix = rtDW->c + 1;
  for (rtDW->b_ix = 0; rtDW->b_ix <= rtDW->iy; rtDW->b_ix++) {
    for (rtDW->i = 0; rtDW->i < rtDW->ix; rtDW->i++) {
      rtDW->Hinv_data[rtDW->i + (rtDW->ijA + 1) * rtDW->b_ix] = rtDW->
        Hinv_data[rtDW->i + 7 * rtDW->b_ix];
    }
  }

  rtDW->Hinv_size[0] = rtDW->ijA + 1;
  rtDW->Hinv_size[1] = rtDW->iy + 1;

  /* '<S8>:1:44' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
  if ((int8_T)(rtDW->c + 1) < (int8_T)(rtDW->iy + 1)) {
    rtDW->i = (int8_T)(rtDW->c + 1);
  } else {
    rtDW->i = (int8_T)(rtDW->iy + 1);
  }

  rtDW->kBcol = (int8_T)(rtDW->ijA + 1);
  rtDW->ix = (int8_T)(rtDW->ijA + 1) * (int8_T)(rtDW->iy + 1) - 1;
  if (0 <= rtDW->ix) {
    memset(&rtDW->b_I_data[0], 0, (rtDW->ix + 1) * sizeof(int8_T));
  }

  if (rtDW->i > 0) {
    rtDW->b_ix = 0;
    while (rtDW->b_ix <= rtDW->i - 1) {
      rtDW->b_I_data[rtDW->b_ix + (int8_T)(rtDW->ijA + 1) * rtDW->b_ix] = 1;
      rtDW->b_ix++;
    }
  }

  if (rtDW->ijA + 1 < rtDW->iy + 1) {
    rtDW->ijA++;
  } else {
    rtDW->ijA = rtDW->iy + 1;
  }

  rtDW->Linv_size[0] = (int8_T)(rtDW->iy + 1);
  rtDW->Linv_size[1] = (int8_T)(rtDW->iy + 1);
  rtDW->i = 0;
  while (rtDW->i <= (int8_T)(rtDW->iy + 1) - 1) {
    rtDW->c = 0;
    while (rtDW->c <= rtDW->ijA - 1) {
      rtDW->Linv_data[rtDW->c + (int8_T)(rtDW->iy + 1) * rtDW->i] =
        rtDW->b_I_data[rtDW->c + rtDW->kBcol * rtDW->i];
      rtDW->c++;
    }

    rtDW->c = rtDW->ijA;
    while (rtDW->c + 1 <= rtDW->iy + 1) {
      rtDW->Linv_data[rtDW->c + (int8_T)(rtDW->iy + 1) * rtDW->i] = 0.0F;
      rtDW->c++;
    }

    rtDW->i++;
  }

  trisolve(rtDW->Hinv_data, rtDW->Hinv_size, rtDW->Linv_data, rtDW->Linv_size);

  /*  solve QP */
  /* '<S8>:1:46' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
  rtDW->iy = rtDW->Linv_size[1];
  rtDW->Hinv_size[0] = rtDW->Linv_size[1];
  rtDW->Hinv_size[1] = rtDW->Linv_size[1];
  rtDW->i = 0;
  while (rtDW->i <= rtDW->Linv_size[1] - 1) {
    rtDW->kBcol = rtDW->i * rtDW->iy;
    rtDW->c_ix = rtDW->i * rtDW->Linv_size[0];
    rtDW->c = 0;
    while (rtDW->c <= rtDW->iy - 1) {
      rtDW->Hinv_data[rtDW->kBcol + rtDW->c] = 0.0F;
      rtDW->c++;
    }

    rtDW->ix = 0;
    while (rtDW->ix <= rtDW->Linv_size[0] - 1) {
      rtDW->smax = rtDW->Linv_data[rtDW->c_ix + rtDW->ix];
      rtDW->b_ix = 0;
      while (rtDW->b_ix <= rtDW->iy - 1) {
        rtDW->ijA = rtDW->kBcol + rtDW->b_ix;
        rtDW->Hinv_data[rtDW->ijA] += rtDW->Linv_data[rtDW->b_ix *
          rtDW->Linv_size[0] + rtDW->ix] * rtDW->smax;
        rtDW->b_ix++;
      }

      rtDW->ix++;
    }

    rtDW->i++;
  }

  for (rtDW->ijA = 0; rtDW->ijA < 7; rtDW->ijA++) {
    rtDW->A_me = 0.0F;
    for (rtDW->c = 0; rtDW->c < 28; rtDW->c++) {
      rtDW->A_me += rtDW->M[28 * rtDW->ijA + rtDW->c] * 2.0F * rtDW->r[rtDW->c];
    }

    rtDW->fv2[rtDW->ijA] = -rtDW->A_me;
  }

  rtDW->A_me = roundf(rtU->max_iter);
  if (rtDW->A_me < 32768.0F) {
    if (rtDW->A_me >= -32768.0F) {
      tmp = (int16_T)rtDW->A_me;
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
         rtDW->fv2, tmp, (int16_T)rtDW->Linv_size[0], rtDW->x_data,
         &rtDW->x_size, rtDW->x_p, &rtY->iterations_qp, rtDW->iA1, rtDW);

  /* '<S8>:1:47' x = single(x_tmp(1:7,1)); */
  /* '<S8>:1:48' iter = single(exitflag); */
  /*  J1 = x1'*(M1'*M1)*x1-2*r1'*M1*x1; */
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
    /* MATLAB Function: '<S1>/tz' incorporates:
     *  MATLAB Function: '<S1>/qp_solver'
     */
    rtDW->tz[rtDW->i] = 0.0F;
    for (rtDW->ijA = 0; rtDW->ijA < 7; rtDW->ijA++) {
      rtDW->tz[rtDW->i] += (real32_T)a[6 * rtDW->ijA + rtDW->i] * rtDW->
        x_data[rtDW->ijA];
    }

    /* End of MATLAB Function: '<S1>/tz' */

    /* MATLAB Function: '<S1>/tz_2_tph' */
    rtDW->t[rtDW->i] = 0.0F;
  }

  /* MATLAB Function: '<S1>/tz_2_tph' */
  /* '<S12>:1:30' for i=1:6 */
  for (rtDW->c = 0; rtDW->c < 6; rtDW->c++) {
    /* '<S12>:1:31' t(seq_order_table(seq_no,i),1) = tz(i); */
    rtDW->t[seq_order_table[(rtDW->sector_ref + 24 * rtDW->c) - 1] - 1] =
      rtDW->tz[rtDW->c];
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
  rtY->d_opt[0] = rtDW->t[0];
  rtY->d_opt[1] = rtDW->t[1];
  rtY->d_opt[2] = rtDW->t[2];
  rtY->d_opt[3] = rtDW->t[3];
  rtY->d_opt[4] = rtDW->t[4];
  rtY->d_opt[5] = rtDW->t[5];

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
  rtDW->icLoad_p = false;
  for (rtDW->ijA = 0; rtDW->ijA < 7; rtDW->ijA++) {
    /* MATLAB Function: '<S1>/qp_solver' */
    rtDW->rtb_i_dq_obs_idx_0 = rtDW->x_data[rtDW->ijA];

    /* Update for Delay: '<S1>/Delay13' incorporates:
     *  MATLAB Function: '<S1>/qp_solver'
     */
    rtDW->Delay13_DSTATE[rtDW->ijA] = rtDW->rtb_i_dq_obs_idx_0;

    /* Update for Delay: '<S1>/Delay1' incorporates:
     *  MATLAB Function: '<S1>/qp_solver'
     */
    rtDW->Delay1_DSTATE[rtDW->ijA] = rtDW->rtb_i_dq_obs_idx_0;
  }

  /* Update for Delay: '<S1>/Delay3' */
  rtDW->icLoad_l = false;

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->icLoad_h = false;

  /* Update for Delay: '<S1>/Delay5' */
  rtDW->icLoad_b = false;

  /* Update for Delay: '<S1>/Delay6' */
  rtDW->icLoad_n = false;

  /* Update for Delay: '<S1>/Delay7' */
  rtDW->icLoad_bq = false;

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
    rtDW->icLoad_p = true;

    /* InitializeConditions for Delay: '<S1>/Delay3' */
    rtDW->icLoad_l = true;

    /* InitializeConditions for Delay: '<S1>/Delay4' */
    rtDW->icLoad_h = true;

    /* InitializeConditions for Delay: '<S1>/Delay5' */
    rtDW->icLoad_b = true;

    /* InitializeConditions for Delay: '<S1>/Delay6' */
    rtDW->icLoad_n = true;

    /* InitializeConditions for Delay: '<S1>/Delay7' */
    rtDW->icLoad_bq = true;

    /* InitializeConditions for Delay: '<S1>/Delay8' */
    rtDW->icLoad_d = true;

    /* SystemInitialize for MATLAB Function: '<S1>/Observer' */
    /* '<S3>:1:40' x_e = single([0;0;0;0;0;0;0;0]); */
    for (i = 0; i < 8; i++) {
      rtDW->x_e[i] = 0.0F;
    }

    /* '<S3>:1:41' P_e = single(diag([0.1 0.1 0.1 0.1 100 100 100 100])); */
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
