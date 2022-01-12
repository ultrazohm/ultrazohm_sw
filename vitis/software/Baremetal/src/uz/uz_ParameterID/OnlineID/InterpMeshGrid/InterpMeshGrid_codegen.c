/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: InterpMeshGrid.c
 *
 * Code generated for Simulink model 'InterpMeshGrid'.
 *
 * Model version                  : 2.382
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Jan 11 14:47:03 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#include "../../../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U

#include "InterpMeshGrid_codegen.h"

/* Forward declaration for local functions */
static void regressionline(const real_T Array[100], real_T rejectOutliers,
  real32_T *b_y1, real32_T *y2);
static real32_T norm(const real32_T x[3]);
static void interpol_flux_scatter_psid(real32_T array[10300], const real32_T
  rangeX[20], const real32_T rangeY[20], real32_T grid[400], DW_InterpMeshGrid_t
  *rtInterpMeshGrid_DW);
static void interpol_flux_scatter_psiq(real32_T array[10300], const real32_T
  rangeX[20], const real32_T rangeY[20], real32_T grid[400], DW_InterpMeshGrid_t
  *rtInterpMeshGrid_DW);
static void minimum(const real32_T x[400], real32_T ex[20]);

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

/*
 * Function for MATLAB Function: '<Root>/InterpMeshGrid'
 * function [y1,y2]=regressionline(Array,rejectOutliers)
 * Evaluation of a linear regression line
 */
static void regressionline(const real_T Array[100], real_T rejectOutliers,
  real32_T *b_y1, real32_T *y2)
{
  real_T tmp;
  real_T tmp_0;
  int32_T k;
  real32_T Xx;
  real32_T Xy;
  real32_T iestSum;
  real32_T measSum;
  real32_T zaehler;

  /* --------initializing--------------------------------------- */
  /* 'regressionline:5' gerade=zeros(2,1); */
  /* 'regressionline:6' zaehler=single(0); */
  zaehler = 0.0F;

  /* 'regressionline:7' measSum=single(0); */
  measSum = 0.0F;

  /* 'regressionline:8' iestSum=single(0); */
  iestSum = 0.0F;

  /* 'regressionline:9' Xy=single(0); */
  Xy = 0.0F;

  /* 'regressionline:10' Xx=single(0); */
  Xx = 0.0F;

  /* 'regressionline:11' meanMeas=single(0); */
  /* 'regressionline:12' meanIest=single(0); */
  /* 'regressionline:13' SS_xy=single(0); */
  /* 'regressionline:14' SS_xx=single(0); */
  /* --------summing up---------------------------------- */
  /* 'regressionline:17' for k=single(2):single(length(Array)-1) */
  for (k = 0; k < 98; k++) {
    /* ----------reject outliers--------------------------- */
    /* 'regressionline:20' if (k >5 && Array(k)>0) */
    if (k + 2 > 5) {
      tmp = Array[k + 1];
      if (tmp > 0.0) {
        /* 'regressionline:21' if(( Array(k)<1.3*Array(k+1) || Array(k)<1.3*Array(k-1) ||rejectOutliers==0 ) && ( Array(k)>Array(k+1)*0.7  || Array(k)>Array(k-1)*0.7) ||rejectOutliers==0 ) */
        tmp_0 = Array[k + 2];
        if ((((tmp < tmp_0 * 1.3) || (tmp < 1.3 * Array[k]) || (rejectOutliers ==
               0.0)) && ((tmp > tmp_0 * 0.7) || (tmp > Array[k] * 0.7))) ||
            (rejectOutliers == 0.0)) {
          /* 'regressionline:22' zaehler=zaehler+1; */
          zaehler++;

          /* 'regressionline:23' measSum=measSum+k; */
          measSum += (real32_T)k + 2.0F;

          /* 'regressionline:24' iestSum=iestSum+Array(k); */
          iestSum += (real32_T)tmp;

          /* 'regressionline:25' Xy=k*Array(k)+Xy; */
          Xy += ((real32_T)k + 2.0F) * (real32_T)Array[k + 1];

          /* 'regressionline:26' Xx=k*k+Xx; */
          Xx += (real32_T)((k + 2) * (k + 2));
        }
      }
    }
  }

  /* -------calculate mean------------------------------- */
  /* 'regressionline:32' meanMeas=measSum/zaehler; */
  measSum /= zaehler;

  /* 'regressionline:33' meanIest=iestSum/zaehler; */
  iestSum /= zaehler;

  /* ----------calculate varianz-------------------------- */
  /* 'regressionline:36' SS_xy = Xy-zaehler*meanMeas*meanIest; */
  zaehler *= measSum;

  /* 'regressionline:37' SS_xx = Xx- zaehler*meanMeas*meanMeas; */
  /* -------viscous friction-------------------------------     */
  /* 'regressionline:40' gerade(1)=single(SS_xy/SS_xx); */
  /* -------Coulomb friction----------------------------- */
  /* 'regressionline:43' gerade(2)=single(meanIest-(SS_xy/SS_xx)*meanMeas); */
  /* 'regressionline:45' y1=single(gerade(1)); */
  *b_y1 = (Xy - zaehler * iestSum) / (Xx - zaehler * measSum);

  /* 'regressionline:46' y2=single(gerade(2)); */
  *y2 = iestSum - *b_y1 * measSum;
}

/* Function for MATLAB Function: '<Root>/InterpMeshGrid' */
static real32_T norm(const real32_T x[3])
{
  real32_T absxk;
  real32_T scale;
  real32_T t;
  real32_T y;
  scale = 1.29246971E-26F;
  absxk = fabsf(x[0]);
  if (absxk > 1.29246971E-26F) {
    y = 1.0F;
    scale = absxk;
  } else {
    t = absxk / 1.29246971E-26F;
    y = t * t;
  }

  absxk = fabsf(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabsf(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * sqrtf(y);
}

/*
 * Function for MATLAB Function: '<Root>/InterpMeshGrid'
 * function [rangeX,rangeY,grid] = interpol_flux_scatter_psid (array,rangeX,rangeY)
 *  Author Philipp Gebhardt
 *  Oktober 2019
 *
 *  This function is an inter- and extrapolation of an inregular scattered x y z measuring data,
 *  which generates a regular grid of a d-flux map of a permanent magnet synchonous machine.
 *  These machines usually have an linear flux map but can differ in
 *  saturation from the linear model. Thats why this function approximates
 *  the scattered data to a linear surface whichs deviation is assumed with
 *  inverse distance weihting from the scattered data.
 *
 *  Input "array" is from type single(100,3) = irregular scattered x y z data
 *  Input "rangeX" is from type single(20,1) = range of x-Axes from new grid = Output also
 *  Input "rangeY" is from type single(20,1) = range of y-Axes from new grid = Output also
 *  Output "grid"  is from type single(20,20) = z values of regular grid
 */
static void interpol_flux_scatter_psid(real32_T array[10300], const real32_T
  rangeX[20], const real32_T rangeY[20], real32_T grid[400], DW_InterpMeshGrid_t
  *rtInterpMeshGrid_DW)
{
  int32_T N_sum_tmp;
  int32_T array_tmp;
  int32_T i3;
  int32_T k;
  int32_T n_curr;
  real32_T N_sum_tmp_0;
  real32_T N_sum_tmp_1;
  real32_T OA_idx_0;
  real32_T OA_idx_1;
  real32_T OA_idx_2;
  real32_T dis_gitter;
  real32_T dis_gitter_alt;
  real32_T f_a_tmp;

  /* initialise variables */
  /* 'interpol_flux_scatter_psid:18' OA=single(zeros(3,1)); */
  OA_idx_0 = 0.0F;
  OA_idx_1 = 0.0F;
  OA_idx_2 = 0.0F;

  /* 'interpol_flux_scatter_psid:19' i1=single(0); */
  /* 'interpol_flux_scatter_psid:20' i2=single(0); */
	rtInterpMeshGrid_DW->i2_g = -1;

  /* 'interpol_flux_scatter_psid:21' i3=single(0); */
  i3 = -1;

  /* 'interpol_flux_scatter_psid:22' e=single(0); */
  /* Find evaluable range of psi array */
  /* initialise counter */
  /* 'interpol_flux_scatter_psid:27' n_curr=single(0); */
  n_curr = -1;

  /* check content of array fields */
  /* 'interpol_flux_scatter_psid:30' for(k=single(1):single(length(array(1,:))) */
  for (k = 0; k < 100; k++) {
    /* 'interpol_flux_scatter_psid:32' if(array(1,k)~=0||array(2,k)~=0||array(3,k)~=0) */
    if (array[103 * k] != 0.0F) {
      /* set counter if content exist  */
      /* 'interpol_flux_scatter_psid:35' n_curr=k; */
      n_curr = k;
    } else if (array[103 * k + 1] != 0.0F) {
      /* set counter if content exist  */
      /* 'interpol_flux_scatter_psid:35' n_curr=k; */
      n_curr = k;
    } else if (array[103 * k + 2] != 0.0F) {
      /* set counter if content exist  */
      /* 'interpol_flux_scatter_psid:35' n_curr=k; */
      n_curr = k;
    }
  }

  /* initialise normal vectors */
  /* 'interpol_flux_scatter_psid:41' N=single(zeros(3,100)); */
  memset(&rtInterpMeshGrid_DW->N_c[0], 0, 300U * sizeof(real32_T));

  /* Create empty grid */
  /* 'interpol_flux_scatter_psid:44' grid=single(zeros(length(rangeX),length(rangeY))); */
  /* Calculate normal vecotr of Triangles between psi array values  */
  /* 'interpol_flux_scatter_psid:48' for(k=single(1):single(n_curr) */
  for (k = 0; k <= n_curr; k++) {
    /* Find nearest neighbours  */
    /* 'interpol_flux_scatter_psid:52' for(t=single(1):single(n_curr) */
    for (array_tmp = 0; array_tmp <= n_curr; array_tmp++) {
      /* Calculate distance */
      /* 'interpol_flux_scatter_psid:55' array(4,t)=( (array(1,t) - array(1,k) )^2  +  ( array(2,t)-array(2,k) )^2    )^0.5; */
      dis_gitter_alt = array[103 * array_tmp] - array[103 * k];
      dis_gitter = array[103 * array_tmp + 1] - array[103 * k + 1];
      array[103 * array_tmp + 3] = sqrtf(dis_gitter_alt * dis_gitter_alt +
        dis_gitter * dis_gitter);
    }

    /* nearest is point itself */
    /* 'interpol_flux_scatter_psid:60' i1=k; */
    /* prevent self identification */
    /* 'interpol_flux_scatter_psid:63' array(4,i1)=2000; */
    array[103 * k + 3] = 2000.0F;

    /* initialize error */
    /* 'interpol_flux_scatter_psid:66' e=single(1000); */
    dis_gitter_alt = 1000.0F;

    /* 'interpol_flux_scatter_psid:68' for(t=single(1):single(n_curr) */
    for (array_tmp = 0; array_tmp <= n_curr; array_tmp++) {
      /* 'interpol_flux_scatter_psid:69' if(abs(array(4,t))<e) */
      dis_gitter = array[103 * array_tmp + 3];
      if (fabsf(dis_gitter) < dis_gitter_alt) {
        /* 'interpol_flux_scatter_psid:70' i2=t; */
				rtInterpMeshGrid_DW->i2_g = array_tmp;

        /* 'interpol_flux_scatter_psid:71' e=array(4,t); */
        dis_gitter_alt = dis_gitter;
      }
    }

    /* Find most appropriate Triangle  */
    /*  -> no small angles in the triangle = Delaunay-Triangulation */
    /* consider all possible triangles between the psi array values */
    /* 'interpol_flux_scatter_psid:82' for(t=single(1):single(n_curr) */
    for (array_tmp = 0; array_tmp <= n_curr; array_tmp++) {
      /* 'interpol_flux_scatter_psid:83' if(t~=i1 && t~=i2) */
			if ((array_tmp != k) && (array_tmp != rtInterpMeshGrid_DW->i2_g)) {
        /*  Calculate scalarproduct of every possible triangle and divide throuh */
        /*  norm of vectors to get cos() of angle */
        /* 'interpol_flux_scatter_psid:88' AB=[array(1,i2)-array(1,i1);array(2,i2)-array(2,i1);array(3,i2)-array(3,i1)]; */
        dis_gitter = array[103 * k];
				rtInterpMeshGrid_DW->N_sum_p[0] = array[103 * rtInterpMeshGrid_DW->i2_g]
          - dis_gitter;
        N_sum_tmp_0 = array[103 * k + 1];
				rtInterpMeshGrid_DW->N_sum_p[1] = array[103 * rtInterpMeshGrid_DW->i2_g
          + 1] - N_sum_tmp_0;
        N_sum_tmp_1 = array[103 * k + 2];
				rtInterpMeshGrid_DW->N_sum_p[2] = array[103 * rtInterpMeshGrid_DW->i2_g
          + 2] - N_sum_tmp_1;

        /* 'interpol_flux_scatter_psid:89' AC=[array(1,t)-array(1,i1);array(2,t)-array(2,i1);array(3,t)-array(3,i1)]; */
        rtInterpMeshGrid_DW->AC_b[0] = array[103 * array_tmp] - dis_gitter;
        rtInterpMeshGrid_DW->AC_b[1] = array[103 * array_tmp + 1] - N_sum_tmp_0;
        rtInterpMeshGrid_DW->AC_b[2] = array[103 * array_tmp + 2] - N_sum_tmp_1;

        /* 'interpol_flux_scatter_psid:91' array(4,t)=abs(dot(AB,AC)/(norm(AB)*norm(AC))); */
        array[103 * array_tmp + 3] = fabsf(((rtInterpMeshGrid_DW->N_sum_p[0] *
          rtInterpMeshGrid_DW->AC_b[0] + rtInterpMeshGrid_DW->N_sum_p[1] *
          rtInterpMeshGrid_DW->AC_b[1]) + rtInterpMeshGrid_DW->N_sum_p[2] *
          rtInterpMeshGrid_DW->AC_b[2]) / (norm(rtInterpMeshGrid_DW->N_sum_p) *
          norm(rtInterpMeshGrid_DW->AC_b)));
      } else {
        /* 'interpol_flux_scatter_psid:92' else */
        /* 'interpol_flux_scatter_psid:93' array(4,t)=1e20; */
        array[103 * array_tmp + 3] = 1.0E+20F;
      }
    }

    /* find smallest cos() of angle because triangle should be as right-angled as */
		/* possible and cos(90°)=0 */
    /* 'interpol_flux_scatter_psid:100' e=single(1e19); */
    dis_gitter_alt = 1.0E+19F;

    /* 'interpol_flux_scatter_psid:101' for(t=single(1):single(n_curr) */
    for (array_tmp = 0; array_tmp <= n_curr; array_tmp++) {
      /* 'interpol_flux_scatter_psid:102' if(abs(array(4,t))<e) */
      dis_gitter = array[103 * array_tmp + 3];
      if (fabsf(dis_gitter) < dis_gitter_alt) {
        /* 'interpol_flux_scatter_psid:103' i3=t; */
        i3 = array_tmp;

        /* 'interpol_flux_scatter_psid:104' e=array(4,t); */
        dis_gitter_alt = dis_gitter;
      }
    }

    /* create triangle vectors */
    /* 'interpol_flux_scatter_psid:110' AB=[array(1,i2)-array(1,i1); array(2,i2)-array(2,i1); array(3,i2)-array(3,i1)]; */
		rtInterpMeshGrid_DW->N_sum_p[0] = array[103 * rtInterpMeshGrid_DW->i2_g] -
      array[103 * k];
    array_tmp = 103 * k + 1;
		rtInterpMeshGrid_DW->N_sum_p[1] = array[103 * rtInterpMeshGrid_DW->i2_g + 1]
      - array[array_tmp];
    N_sum_tmp = 103 * k + 2;
		rtInterpMeshGrid_DW->N_sum_p[2] = array[103 * rtInterpMeshGrid_DW->i2_g + 2]
      - array[N_sum_tmp];

    /* 'interpol_flux_scatter_psid:111' AC=[array(1,i3)-array(1,i1); array(2,i3)-array(2,i1); array(3,i3)-array(3,i1)]; */
    rtInterpMeshGrid_DW->AC_b[0] = array[103 * i3] - array[103 * k];
    rtInterpMeshGrid_DW->AC_b[1] = array[103 * i3 + 1] - array[array_tmp];
    rtInterpMeshGrid_DW->AC_b[2] = array[103 * i3 + 2] - array[N_sum_tmp];

    /* calculate the normal vector */
    /* 'interpol_flux_scatter_psid:114' N(:,k)=cross(AB,AC); */
    rtInterpMeshGrid_DW->N_c[3 * k] = rtInterpMeshGrid_DW->N_sum_p[1] *
      rtInterpMeshGrid_DW->AC_b[2] - rtInterpMeshGrid_DW->AC_b[1] *
      rtInterpMeshGrid_DW->N_sum_p[2];
    array_tmp = 3 * k + 1;
    rtInterpMeshGrid_DW->N_c[array_tmp] = rtInterpMeshGrid_DW->AC_b[0] *
      rtInterpMeshGrid_DW->N_sum_p[2] - rtInterpMeshGrid_DW->N_sum_p[0] *
      rtInterpMeshGrid_DW->AC_b[2];
    N_sum_tmp = 3 * k + 2;
    rtInterpMeshGrid_DW->N_c[N_sum_tmp] = rtInterpMeshGrid_DW->N_sum_p[0] *
      rtInterpMeshGrid_DW->AC_b[1] - rtInterpMeshGrid_DW->AC_b[0] *
      rtInterpMeshGrid_DW->N_sum_p[1];

    /* normalize the normal vector */
    /* 'interpol_flux_scatter_psid:117' abs_N=(N(1,k)*N(1,k)+N(2,k)*N(2,k)+N(3,k)*N(3,k))^0.5; */
    dis_gitter = rtInterpMeshGrid_DW->N_c[array_tmp];
    N_sum_tmp_1 = rtInterpMeshGrid_DW->N_c[3 * k];
    N_sum_tmp_0 = rtInterpMeshGrid_DW->N_c[N_sum_tmp];
    dis_gitter_alt = sqrtf((dis_gitter * dis_gitter + N_sum_tmp_1 * N_sum_tmp_1)
      + N_sum_tmp_0 * N_sum_tmp_0);

    /* 'interpol_flux_scatter_psid:118' N(:,k)=N(:,k)/abs_N; */
    rtInterpMeshGrid_DW->N_c[3 * k] = N_sum_tmp_1 / dis_gitter_alt;
    rtInterpMeshGrid_DW->N_c[array_tmp] = dis_gitter / dis_gitter_alt;
    rtInterpMeshGrid_DW->N_c[N_sum_tmp] = N_sum_tmp_0 / dis_gitter_alt;

    /* Reverse negative normal vectors */
    /* 'interpol_flux_scatter_psid:121' if (N(3,k)<0) */
    if (rtInterpMeshGrid_DW->N_c[N_sum_tmp] < 0.0F) {
      /* 'interpol_flux_scatter_psid:122' N(:,k)=N(:,k)*(-1); */
      dis_gitter = rtInterpMeshGrid_DW->N_c[array_tmp];
      dis_gitter_alt = rtInterpMeshGrid_DW->N_c[N_sum_tmp];
      rtInterpMeshGrid_DW->N_c[3 * k] = -rtInterpMeshGrid_DW->N_c[3 * k];
      rtInterpMeshGrid_DW->N_c[array_tmp] = -dis_gitter;
      rtInterpMeshGrid_DW->N_c[N_sum_tmp] = -dis_gitter_alt;
    }

    /* Prevent unplausible gradients */
    /* 'interpol_flux_scatter_psid:125' if (N(1,k)>0) */
    if (rtInterpMeshGrid_DW->N_c[3 * k] > 0.0F) {
      /* 'interpol_flux_scatter_psid:126' N(1,k)=0; */
      rtInterpMeshGrid_DW->N_c[3 * k] = 0.0F;
    }
  }

  /* optimize grid data  */
  /* repeat for every grid value */
  /* 'interpol_flux_scatter_psid:136' for(m=single(1):single(length(rangeX(1,:))) */
	for (rtInterpMeshGrid_DW->i2_g = 0; rtInterpMeshGrid_DW->i2_g < 20; rtInterpMeshGrid_DW->i2_g++) {
    /* 'interpol_flux_scatter_psid:137' for(n=single(1):single(length(rangeY(1,:))) */
    for (i3 = 0; i3 < 20; i3++) {
      /* initialize variables     */
      /* 'interpol_flux_scatter_psid:140' dis_gitter=single(0); */
      /* 'interpol_flux_scatter_psid:141' dis_gitter_alt=single(1000); */
      dis_gitter_alt = 1000.0F;

      /* 'interpol_flux_scatter_psid:142' N_aver=single(zeros(3,1)); */
      /*  repeat for every psi_array value */
      /* 'interpol_flux_scatter_psid:145' for(k=single(1):single(n_curr) */
      for (k = 0; k <= n_curr; k++) {
        /* Calculate distance to grid data value */
        /* 'interpol_flux_scatter_psid:149' dis_gitter=( (array(1,k)-rangeX(m))^2+(array(2,k)-rangeY(n))^2  )^0.5; */
        N_sum_tmp_0 = array[103 * k];
				dis_gitter = N_sum_tmp_0 - rangeX[rtInterpMeshGrid_DW->i2_g];
        f_a_tmp = array[103 * k + 1];
        N_sum_tmp_1 = f_a_tmp - rangeY[i3];
        dis_gitter = sqrtf(dis_gitter * dis_gitter + N_sum_tmp_1 * N_sum_tmp_1);

        /* 'interpol_flux_scatter_psid:151' if(dis_gitter<dis_gitter_alt) */
        if (dis_gitter < dis_gitter_alt) {
          /* 'interpol_flux_scatter_psid:152' dis_gitter_alt=dis_gitter; */
          dis_gitter_alt = dis_gitter;

          /* 'interpol_flux_scatter_psid:153' OA=[array(1,k); array(2,k); array(3,k)]; */
          OA_idx_0 = N_sum_tmp_0;
          OA_idx_1 = f_a_tmp;
          OA_idx_2 = array[103 * k + 2];

          /*  N_aver=N(:,k); %Use this N_aver if you do not want to use the distance weighting */
        }
      }

      /* Presumption L ~ const, Averageing the gradient with inverse distance weighting     */
      /* Initialize variables */
      /* 'interpol_flux_scatter_psid:163' N_sum=single(zeros(3,1)); */
      rtInterpMeshGrid_DW->N_sum_p[0] = 0.0F;
      rtInterpMeshGrid_DW->N_sum_p[1] = 0.0F;
      rtInterpMeshGrid_DW->N_sum_p[2] = 0.0F;

      /* 'interpol_flux_scatter_psid:164' dis_sum=single(0); */
      dis_gitter_alt = 0.0F;

      /* weighting factor p for consistent gradient of the surface */
      /* the lower p is the more  is the gradient unified  */
      /* 'interpol_flux_scatter_psid:169' p=2; */
      /* =square weighting   */
      /* Sum up normal vectors and weight the vectors by distance to the grid */
      /* point */
      /* 'interpol_flux_scatter_psid:174' for(t=single(1):single(n_curr) */
      for (k = 0; k <= n_curr; k++) {
        /* 'interpol_flux_scatter_psid:175' array(4,t)=( (rangeX(m) - array(1,t) )^2  +  ( rangeY(n)-array(2,t) )^2    )^0.5; */
				dis_gitter = rangeX[rtInterpMeshGrid_DW->i2_g] - array[103 * k];
        N_sum_tmp_1 = rangeY[i3] - array[103 * k + 1];
        array_tmp = 103 * k + 3;
        array[array_tmp] = sqrtf(dis_gitter * dis_gitter + N_sum_tmp_1 *
          N_sum_tmp_1);

        /* 'interpol_flux_scatter_psid:176' N_sum(:,1)=N_sum(:,1)+N(:,t)*(1/array(4,t))^p; */
        N_sum_tmp_0 = 1.0F / array[array_tmp];
        dis_gitter = N_sum_tmp_0 * N_sum_tmp_0;
        rtInterpMeshGrid_DW->N_sum_p[0] += rtInterpMeshGrid_DW->N_c[3 * k] *
          dis_gitter;
        rtInterpMeshGrid_DW->N_sum_p[1] += rtInterpMeshGrid_DW->N_c[3 * k + 1] *
          dis_gitter;
        rtInterpMeshGrid_DW->N_sum_p[2] += rtInterpMeshGrid_DW->N_c[3 * k + 2] *
          dis_gitter;

        /* 'interpol_flux_scatter_psid:177' dis_sum=dis_sum+(1/array(4,t))^p; */
        dis_gitter_alt += N_sum_tmp_0 * N_sum_tmp_0;
      }

      /* Calculate griddata with averaged normal vector starting at the nearest */
      /* measuring points  */
      /* Average N_aver */
      /* 'interpol_flux_scatter_psid:184' N_aver(:)=N_sum(:)/(dis_sum); */
      dis_gitter = rtInterpMeshGrid_DW->N_sum_p[0] / dis_gitter_alt;
      N_sum_tmp_0 = rtInterpMeshGrid_DW->N_sum_p[1] / dis_gitter_alt;
      N_sum_tmp_1 = rtInterpMeshGrid_DW->N_sum_p[2] / dis_gitter_alt;

      /* Normalizing the Vectors N_aver */
      /* 'interpol_flux_scatter_psid:186' abs_N=(N_aver(1)*N_aver(1)+N_aver(2)*N_aver(2)+N_aver(3)*N_aver(3))^0.5; */
      dis_gitter_alt = sqrtf((dis_gitter * dis_gitter + N_sum_tmp_0 *
        N_sum_tmp_0) + N_sum_tmp_1 * N_sum_tmp_1);

      /* 'interpol_flux_scatter_psid:187' N_aver(:)=N_aver(:)/abs_N; */
      N_sum_tmp_0 /= dis_gitter_alt;

      /* 'interpol_flux_scatter_psid:189' grid(n,m)=( dot(N_aver,OA)-N_aver(1)*rangeX(m)-N_aver(2)*rangeY(n))/( N_aver(3) ); */
      dis_gitter /= dis_gitter_alt;
      dis_gitter_alt = N_sum_tmp_1 / dis_gitter_alt;
			grid[i3 + 20 * rtInterpMeshGrid_DW->i2_g] = ((((dis_gitter * OA_idx_0 +
        N_sum_tmp_0 * OA_idx_1) + dis_gitter_alt * OA_idx_2) - dis_gitter *
        rangeX[rtInterpMeshGrid_DW->i2_g])
			                - N_sum_tmp_0 * rangeY[i3]) /
        dis_gitter_alt;
    }
  }

  /* 'interpol_flux_scatter_psid:193' grid_old=grid; */
  memcpy(&rtInterpMeshGrid_DW->grid_old_k[0], &grid[0], 400U * sizeof(real32_T));

  /* Smooth Surface */
  /* 'interpol_flux_scatter_psid:197' for(m=single(1):single(length(rangeX(1,:))) */
  for (n_curr = 0; n_curr < 20; n_curr++) {
    /* 'interpol_flux_scatter_psid:198' for(n=single(1):single(length(rangeY(1,:))) */
		for (rtInterpMeshGrid_DW->i2_g = 0; rtInterpMeshGrid_DW->i2_g < 20; rtInterpMeshGrid_DW->i2_g++) {
      /* 'interpol_flux_scatter_psid:199' grid_sum=single(0); */
      /* 'interpol_flux_scatter_psid:200' grid_count=single(0); */
      /* 'interpol_flux_scatter_psid:202' for(t=single(0):single(2) */
      /* 'interpol_flux_scatter_psid:204' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0) */
      /* 'interpol_flux_scatter_psid:210' if(t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
      /* 'interpol_flux_scatter_psid:216' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0&&t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
      /* 'interpol_flux_scatter_psid:224' if(t==0) */
      /* 'interpol_flux_scatter_psid:225' grid_sum=grid_sum+grid_old(n,m); */
			i3 = 20 * n_curr + rtInterpMeshGrid_DW->i2_g;
      dis_gitter_alt = rtInterpMeshGrid_DW->grid_old_k[i3];

      /* 'interpol_flux_scatter_psid:226' grid_count=grid_count+1; */
      dis_gitter = 1.0F;

      /* 'interpol_flux_scatter_psid:204' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0) */
			if ((rtInterpMeshGrid_DW->i2_g + 2 <= 20) && (rtInterpMeshGrid_DW->i2_g >
           0)) {
        /* 'interpol_flux_scatter_psid:205' grid_sum=grid_sum+grid_old(n+t,m); */
        /* 'interpol_flux_scatter_psid:206' grid_sum=grid_sum+grid_old(n-t,m); */
        dis_gitter_alt = (rtInterpMeshGrid_DW->grid_old_k[i3 + 1] +
                          dis_gitter_alt) + rtInterpMeshGrid_DW->grid_old_k[i3 -
          1];

        /* 'interpol_flux_scatter_psid:207' grid_count=grid_count+2; */
        dis_gitter = 3.0F;
      }

      /* 'interpol_flux_scatter_psid:210' if(t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
      if ((n_curr + 2 <= 20) && (n_curr > 0)) {
        /* 'interpol_flux_scatter_psid:211' grid_sum=grid_sum+grid_old(n,m+t); */
        /* 'interpol_flux_scatter_psid:212' grid_sum=grid_sum+grid_old(n,m-t); */
        dis_gitter_alt = (rtInterpMeshGrid_DW->grid_old_k[(n_curr + 1) * 20 +
                          rtInterpMeshGrid_DW->i2_g] + dis_gitter_alt)
				                +
          rtInterpMeshGrid_DW->grid_old_k[(n_curr - 1) * 20 +
          rtInterpMeshGrid_DW->i2_g];

        /* 'interpol_flux_scatter_psid:213' grid_count=grid_count+2; */
        dis_gitter += 2.0F;
      }

      /* 'interpol_flux_scatter_psid:216' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0&&t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
			if ((rtInterpMeshGrid_DW->i2_g + 2 <= 20) && (rtInterpMeshGrid_DW->i2_g >
           0) && (n_curr + 2 <= 20) && (n_curr > 0)) {
        /* 'interpol_flux_scatter_psid:217' grid_sum=grid_sum+grid_old(n+t,m+t); */
        /* 'interpol_flux_scatter_psid:218' grid_sum=grid_sum+grid_old(n+t,m-t); */
        /* 'interpol_flux_scatter_psid:219' grid_sum=grid_sum+grid_old(n-t,m-t); */
        /* 'interpol_flux_scatter_psid:220' grid_sum=grid_sum+grid_old(n-t,m+t); */
				k = (n_curr - 1) * 20 + rtInterpMeshGrid_DW->i2_g;
				array_tmp = (n_curr + 1) * 20 + rtInterpMeshGrid_DW->i2_g;
        dis_gitter_alt = (((rtInterpMeshGrid_DW->grid_old_k[array_tmp + 1] +
                            dis_gitter_alt) + rtInterpMeshGrid_DW->grid_old_k[k
                           + 1]) + rtInterpMeshGrid_DW->grid_old_k[k - 1]) +
          rtInterpMeshGrid_DW->grid_old_k[array_tmp - 1];

        /* 'interpol_flux_scatter_psid:221' grid_count=grid_count+4; */
        dis_gitter += 4.0F;
      }

      /* 'interpol_flux_scatter_psid:224' if(t==0) */
      /* 'interpol_flux_scatter_psid:204' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0) */
			if ((rtInterpMeshGrid_DW->i2_g + 3 <= 20) && (rtInterpMeshGrid_DW->i2_g -
           1 > 0)) {
        /* 'interpol_flux_scatter_psid:205' grid_sum=grid_sum+grid_old(n+t,m); */
        /* 'interpol_flux_scatter_psid:206' grid_sum=grid_sum+grid_old(n-t,m); */
        dis_gitter_alt = (rtInterpMeshGrid_DW->grid_old_k[i3 + 2] +
                          dis_gitter_alt) + rtInterpMeshGrid_DW->grid_old_k[i3 -
          2];

        /* 'interpol_flux_scatter_psid:207' grid_count=grid_count+2; */
        dis_gitter += 2.0F;
      }

      /* 'interpol_flux_scatter_psid:210' if(t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
      if ((n_curr + 3 <= 20) && (n_curr - 1 > 0)) {
        /* 'interpol_flux_scatter_psid:211' grid_sum=grid_sum+grid_old(n,m+t); */
        /* 'interpol_flux_scatter_psid:212' grid_sum=grid_sum+grid_old(n,m-t); */
        dis_gitter_alt = (rtInterpMeshGrid_DW->grid_old_k[(n_curr + 2) * 20 +
                          rtInterpMeshGrid_DW->i2_g] + dis_gitter_alt)
				                +
          rtInterpMeshGrid_DW->grid_old_k[(n_curr - 2) * 20 +
          rtInterpMeshGrid_DW->i2_g];

        /* 'interpol_flux_scatter_psid:213' grid_count=grid_count+2; */
        dis_gitter += 2.0F;
      }

      /* 'interpol_flux_scatter_psid:216' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0&&t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
			if ((rtInterpMeshGrid_DW->i2_g + 3 <= 20) && (rtInterpMeshGrid_DW->i2_g -
           1 > 0) && (n_curr + 3 <= 20) && (n_curr - 1 > 0)) {
        /* 'interpol_flux_scatter_psid:217' grid_sum=grid_sum+grid_old(n+t,m+t); */
        /* 'interpol_flux_scatter_psid:218' grid_sum=grid_sum+grid_old(n+t,m-t); */
        /* 'interpol_flux_scatter_psid:219' grid_sum=grid_sum+grid_old(n-t,m-t); */
        /* 'interpol_flux_scatter_psid:220' grid_sum=grid_sum+grid_old(n-t,m+t); */
				k = (n_curr - 2) * 20 + rtInterpMeshGrid_DW->i2_g;
				array_tmp = (n_curr + 2) * 20 + rtInterpMeshGrid_DW->i2_g;
        dis_gitter_alt = (((rtInterpMeshGrid_DW->grid_old_k[array_tmp + 2] +
                            dis_gitter_alt) + rtInterpMeshGrid_DW->grid_old_k[k
                           + 2]) + rtInterpMeshGrid_DW->grid_old_k[k - 2]) +
          rtInterpMeshGrid_DW->grid_old_k[array_tmp - 2];

        /* 'interpol_flux_scatter_psid:221' grid_count=grid_count+4; */
        dis_gitter += 4.0F;
      }

      /* 'interpol_flux_scatter_psid:224' if(t==0) */
      /* 'interpol_flux_scatter_psid:230' grid(n,m)=grid_sum/grid_count; */
      grid[i3] = dis_gitter_alt / dis_gitter;
    }
  }
}

/*
 * Function for MATLAB Function: '<Root>/InterpMeshGrid'
 * function [rangeX,rangeY,grid] = interpol_flux_scatter_psiq (array,rangeX,rangeY)
 *  Author Philipp Gebhardt
 *  Oktober 2019
 *
 *  This function is an inter- and extrapolation of an inregular scattered x y z measuring data,
 *  which generates a regular grid of a q-flux map of a permanent magnet synchonous machine.
 *  These machines usually have an linear flux map but can differ in
 *  saturation from the linear model. Thats why this function approximates
 *  the scattered data to a linear surface whichs deviation is assumed with
 *  inverse distance weihting from the scattered data.
 *
 *  Input "array" is from type single(100,3) = irregular scattered x y z data
 *  Input "rangeX" is from type single(20,1) = range of x-Axes from new grid = Output also
 *  Input "rangeY" is from type single(20,1) = range of y-Axes from new grid = Output also
 *  Output "grid"  is from type single(20,20) = z values of regular grid
 */
static void interpol_flux_scatter_psiq(real32_T array[10300], const real32_T
  rangeX[20], const real32_T rangeY[20], real32_T grid[400], DW_InterpMeshGrid_t
  *rtInterpMeshGrid_DW)
{
  int32_T N_sum_tmp_0;
  int32_T array_tmp;
  int32_T i3;
  int32_T k;
  int32_T n_curr;
  real32_T N_sum_tmp;
  real32_T N_sum_tmp_1;
  real32_T OA_idx_0;
  real32_T OA_idx_1;
  real32_T OA_idx_2;
  real32_T dis_gitter;
  real32_T dis_gitter_alt;
  real32_T f_a_tmp;

  /* initialise variables */
  /* 'interpol_flux_scatter_psiq:18' OA=single(zeros(3,1)); */
  OA_idx_0 = 0.0F;
  OA_idx_1 = 0.0F;
  OA_idx_2 = 0.0F;

  /* 'interpol_flux_scatter_psiq:19' i1=single(0); */
  /* 'interpol_flux_scatter_psiq:20' i2=single(0); */
  rtInterpMeshGrid_DW->i2 = -1;

  /* 'interpol_flux_scatter_psiq:21' i3=single(0); */
  i3 = -1;

  /* 'interpol_flux_scatter_psiq:22' e=single(0); */
  /* Find evaluable range of psi array */
  /* initialise counter */
  /* 'interpol_flux_scatter_psiq:27' n_curr=single(0); */
  n_curr = -1;

  /* check content of array fields */
  /* 'interpol_flux_scatter_psiq:30' for(k=single(1):single(length(array(1,:))) */
  for (k = 0; k < 100; k++) {
    /* 'interpol_flux_scatter_psiq:32' if(array(1,k)~=0||array(2,k)~=0||array(3,k)~=0) */
    if (array[103 * k] != 0.0F) {
      /* set counter if content exist  */
      /* 'interpol_flux_scatter_psiq:34' n_curr=k; */
      n_curr = k;
    } else if (array[103 * k + 1] != 0.0F) {
      /* set counter if content exist  */
      /* 'interpol_flux_scatter_psiq:34' n_curr=k; */
      n_curr = k;
    } else if (array[103 * k + 2] != 0.0F) {
      /* set counter if content exist  */
      /* 'interpol_flux_scatter_psiq:34' n_curr=k; */
      n_curr = k;
    }
  }

  /* initialise normal vectors */
  /* 'interpol_flux_scatter_psiq:40' N=single(zeros(3,100)); */
  memset(&rtInterpMeshGrid_DW->N[0], 0, 300U * sizeof(real32_T));

  /* Create empty grid */
  /* 'interpol_flux_scatter_psiq:43' grid=single(zeros(length(rangeX),length(rangeY))); */
  /* Calculate normal vecotr of Triangles between psi array values  */
  /* 'interpol_flux_scatter_psiq:46' for(k=single(1):single(n_curr) */
  for (k = 0; k <= n_curr; k++) {
    /* Find nearest neighbours  */
    /* 'interpol_flux_scatter_psiq:49' for(t=single(1):single(n_curr) */
    for (array_tmp = 0; array_tmp <= n_curr; array_tmp++) {
      /* Calculate distance */
      /* 'interpol_flux_scatter_psiq:52' array(4,t)=( (array(1,t) - array(1,k) )^2  +  ( array(2,t)-array(2,k) )^2    )^0.5; */
      dis_gitter_alt = array[103 * array_tmp] - array[103 * k];
      dis_gitter = array[103 * array_tmp + 1] - array[103 * k + 1];
      array[103 * array_tmp + 3] = sqrtf(dis_gitter_alt * dis_gitter_alt +
        dis_gitter * dis_gitter);
    }

    /* nearest is point itself */
    /* 'interpol_flux_scatter_psiq:57' i1=k; */
    /* prevent self identification */
    /* 'interpol_flux_scatter_psiq:60' array(4,i1)=2000; */
    array[103 * k + 3] = 2000.0F;

    /* initialize error */
    /* 'interpol_flux_scatter_psiq:63' e=single(1000); */
    dis_gitter_alt = 1000.0F;

    /* Find most appropriate Triangle  */
    /*  -> no small angles in the triangle = Delaunay-Triangulation */
    /* consider all possible triangles between the psi array values */
    /* 'interpol_flux_scatter_psiq:69' for(t=single(1):single(n_curr) */
    for (array_tmp = 0; array_tmp <= n_curr; array_tmp++) {
      /* 'interpol_flux_scatter_psiq:70' if(abs(array(4,t))<e) */
      dis_gitter = array[103 * array_tmp + 3];
      if (fabsf(dis_gitter) < dis_gitter_alt) {
        /* 'interpol_flux_scatter_psiq:71' i2=t; */
        rtInterpMeshGrid_DW->i2 = array_tmp;

        /* 'interpol_flux_scatter_psiq:72' e=array(4,t); */
        dis_gitter_alt = dis_gitter;
      }
    }

    /* Find most appropriate Triangle  */
    /*  -> no small angles in the triangle = Delaunay-Triangulation */
    /* consider all possible triangles between the psi array values */
    /* 'interpol_flux_scatter_psiq:81' for(t=single(1):single(n_curr) */
    for (array_tmp = 0; array_tmp <= n_curr; array_tmp++) {
      /* 'interpol_flux_scatter_psiq:82' if(t~=i1 && t~=i2) */
      if ((array_tmp != k) && (array_tmp != rtInterpMeshGrid_DW->i2)) {
        /*  Calculate scalarproduct of every possible triangle and divide throuh */
        /*  norm of vectors to get cos() of angle */
        /* 'interpol_flux_scatter_psiq:86' AB=[array(1,i2)-array(1,i1);array(2,i2)-array(2,i1);array(3,i2)-array(3,i1)]; */
        dis_gitter = array[103 * k];
        rtInterpMeshGrid_DW->N_sum[0] = array[103 * rtInterpMeshGrid_DW->i2] -
          dis_gitter;
        N_sum_tmp = array[103 * k + 1];
        rtInterpMeshGrid_DW->N_sum[1] = array[103 * rtInterpMeshGrid_DW->i2 + 1]
          - N_sum_tmp;
        N_sum_tmp_1 = array[103 * k + 2];
        rtInterpMeshGrid_DW->N_sum[2] = array[103 * rtInterpMeshGrid_DW->i2 + 2]
          - N_sum_tmp_1;

        /* 'interpol_flux_scatter_psiq:87' AC=[array(1,t)-array(1,i1);array(2,t)-array(2,i1);array(3,t)-array(3,i1)]; */
        rtInterpMeshGrid_DW->AC[0] = array[103 * array_tmp] - dis_gitter;
        rtInterpMeshGrid_DW->AC[1] = array[103 * array_tmp + 1] - N_sum_tmp;
        rtInterpMeshGrid_DW->AC[2] = array[103 * array_tmp + 2] - N_sum_tmp_1;

        /* 'interpol_flux_scatter_psiq:89' array(4,t)=abs(dot(AB,AC)/(norm(AB)*norm(AC))); */
        array[103 * array_tmp + 3] = fabsf(((rtInterpMeshGrid_DW->N_sum[0] *
          rtInterpMeshGrid_DW->AC[0] + rtInterpMeshGrid_DW->N_sum[1] *
          rtInterpMeshGrid_DW->AC[1]) + rtInterpMeshGrid_DW->N_sum[2] *
          rtInterpMeshGrid_DW->AC[2]) / (norm(rtInterpMeshGrid_DW->N_sum) * norm
          (rtInterpMeshGrid_DW->AC)));
      } else {
        /* 'interpol_flux_scatter_psiq:90' else */
        /* 'interpol_flux_scatter_psiq:91' array(4,t)=1e20; */
        array[103 * array_tmp + 3] = 1.0E+20F;
      }
    }

    /* finde kleinstes Skalarprodukt */
    /* find smallest cos() of angle because triangle should be as right-angled as */
		/* possible and cos(90°)=0 */
    /* 'interpol_flux_scatter_psiq:101' e=single(1e19); */
    dis_gitter_alt = 1.0E+19F;

    /* 'interpol_flux_scatter_psiq:102' for(t=single(1):single(n_curr) */
    for (array_tmp = 0; array_tmp <= n_curr; array_tmp++) {
      /* 'interpol_flux_scatter_psiq:103' if(abs(array(4,t))<e) */
      dis_gitter = array[103 * array_tmp + 3];
      if (fabsf(dis_gitter) < dis_gitter_alt) {
        /* 'interpol_flux_scatter_psiq:104' i3=t; */
        i3 = array_tmp;

        /* 'interpol_flux_scatter_psiq:105' e=array(4,t); */
        dis_gitter_alt = dis_gitter;
      }
    }

    /* create triangle vectors */
    /* 'interpol_flux_scatter_psiq:111' AB=[array(1,i2)-array(1,i1); array(2,i2)-array(2,i1); array(3,i2)-array(3,i1)]; */
    rtInterpMeshGrid_DW->N_sum[0] = array[103 * rtInterpMeshGrid_DW->i2] -
      array[103 * k];
    array_tmp = 103 * k + 1;
    rtInterpMeshGrid_DW->N_sum[1] = array[103 * rtInterpMeshGrid_DW->i2 + 1] -
      array[array_tmp];
    N_sum_tmp_0 = 103 * k + 2;
    rtInterpMeshGrid_DW->N_sum[2] = array[103 * rtInterpMeshGrid_DW->i2 + 2] -
      array[N_sum_tmp_0];

    /* 'interpol_flux_scatter_psiq:112' AC=[array(1,i3)-array(1,i1); array(2,i3)-array(2,i1); array(3,i3)-array(3,i1)]; */
    rtInterpMeshGrid_DW->AC[0] = array[103 * i3] - array[103 * k];
    rtInterpMeshGrid_DW->AC[1] = array[103 * i3 + 1] - array[array_tmp];
    rtInterpMeshGrid_DW->AC[2] = array[103 * i3 + 2] - array[N_sum_tmp_0];

    /* calculate the normal vector */
    /* 'interpol_flux_scatter_psiq:115' N(:,k)=cross(AB,AC); */
    rtInterpMeshGrid_DW->N[3 * k] = rtInterpMeshGrid_DW->N_sum[1] *
      rtInterpMeshGrid_DW->AC[2] - rtInterpMeshGrid_DW->AC[1] *
      rtInterpMeshGrid_DW->N_sum[2];
    array_tmp = 3 * k + 1;
    rtInterpMeshGrid_DW->N[array_tmp] = rtInterpMeshGrid_DW->AC[0] *
      rtInterpMeshGrid_DW->N_sum[2] - rtInterpMeshGrid_DW->N_sum[0] *
      rtInterpMeshGrid_DW->AC[2];
    N_sum_tmp_0 = 3 * k + 2;
    rtInterpMeshGrid_DW->N[N_sum_tmp_0] = rtInterpMeshGrid_DW->N_sum[0] *
      rtInterpMeshGrid_DW->AC[1] - rtInterpMeshGrid_DW->AC[0] *
      rtInterpMeshGrid_DW->N_sum[1];

    /* normalize the normal vector */
    /* 'interpol_flux_scatter_psiq:118' abs_N=(N(1,k)*N(1,k)+N(2,k)*N(2,k)+N(3,k)*N(3,k))^0.5; */
    dis_gitter = rtInterpMeshGrid_DW->N[array_tmp];
    N_sum_tmp_1 = rtInterpMeshGrid_DW->N[3 * k];
    N_sum_tmp = rtInterpMeshGrid_DW->N[N_sum_tmp_0];
    dis_gitter_alt = sqrtf((dis_gitter * dis_gitter + N_sum_tmp_1 * N_sum_tmp_1)
      + N_sum_tmp * N_sum_tmp);

    /* 'interpol_flux_scatter_psiq:119' N(:,k)=N(:,k)/abs_N; */
    rtInterpMeshGrid_DW->N[3 * k] = N_sum_tmp_1 / dis_gitter_alt;
    rtInterpMeshGrid_DW->N[array_tmp] = dis_gitter / dis_gitter_alt;
    rtInterpMeshGrid_DW->N[N_sum_tmp_0] = N_sum_tmp / dis_gitter_alt;

    /* Reverse negative normal vectors */
    /* 'interpol_flux_scatter_psiq:122' if (N(3,k)<0) */
    if (rtInterpMeshGrid_DW->N[N_sum_tmp_0] < 0.0F) {
      /* 'interpol_flux_scatter_psiq:123' N(:,k)=N(:,k)*(-1); */
      dis_gitter = rtInterpMeshGrid_DW->N[array_tmp];
      dis_gitter_alt = rtInterpMeshGrid_DW->N[N_sum_tmp_0];
      rtInterpMeshGrid_DW->N[3 * k] = -rtInterpMeshGrid_DW->N[3 * k];
      rtInterpMeshGrid_DW->N[array_tmp] = -dis_gitter;
      rtInterpMeshGrid_DW->N[N_sum_tmp_0] = -dis_gitter_alt;
    }

    /* Prevent unplausible gradientsn */
    /* 'interpol_flux_scatter_psiq:126' if (N(2,k)>0) */
    if (rtInterpMeshGrid_DW->N[array_tmp] > 0.0F) {
      /* 'interpol_flux_scatter_psiq:127' N(2,k)=0; */
      rtInterpMeshGrid_DW->N[array_tmp] = 0.0F;
    }
  }

  /* optimize grid data  */
  /* repeat for every grid value */
  /* 'interpol_flux_scatter_psiq:137' for(m=single(1):single(length(rangeX(1,:))) */
  for (rtInterpMeshGrid_DW->i2 = 0; rtInterpMeshGrid_DW->i2 < 20;
       rtInterpMeshGrid_DW->i2++) {
    /* 'interpol_flux_scatter_psiq:138' for(n=single(1):single(length(rangeY(1,:))) */
    for (i3 = 0; i3 < 20; i3++) {
      /* initialize variables      */
      /* 'interpol_flux_scatter_psiq:141' dis_gitter=single(0); */
      /* 'interpol_flux_scatter_psiq:142' dis_gitter_alt=single(1000); */
      dis_gitter_alt = 1000.0F;

      /* 'interpol_flux_scatter_psiq:143' N_aver=single(zeros(3,1)); */
      /*  repeat for every psi_array value */
      /* 'interpol_flux_scatter_psiq:146' for(k=single(1):single(n_curr) */
      for (k = 0; k <= n_curr; k++) {
        /* Calculate distance to grid data value */
        /* 'interpol_flux_scatter_psiq:150' dis_gitter=( (array(1,k)-rangeX(m))^2+(array(2,k)-rangeY(n))^2  )^0.5; */
        N_sum_tmp = array[103 * k];
        dis_gitter = N_sum_tmp - rangeX[rtInterpMeshGrid_DW->i2];
        f_a_tmp = array[103 * k + 1];
        N_sum_tmp_1 = f_a_tmp - rangeY[i3];
        dis_gitter = sqrtf(dis_gitter * dis_gitter + N_sum_tmp_1 * N_sum_tmp_1);

        /* 'interpol_flux_scatter_psiq:152' if(dis_gitter<dis_gitter_alt) */
        if (dis_gitter < dis_gitter_alt) {
          /* 'interpol_flux_scatter_psiq:153' dis_gitter_alt=dis_gitter; */
          dis_gitter_alt = dis_gitter;

          /* 'interpol_flux_scatter_psiq:154' OA=[array(1,k); array(2,k); array(3,k)]; */
          OA_idx_0 = N_sum_tmp;
          OA_idx_1 = f_a_tmp;
          OA_idx_2 = array[103 * k + 2];

          /*  N_aver=N(:,k); %Use this N_aver if you do not want to use the distance weighting */
        }
      }

      /* Presumption L ~ const, Averageing the gradient with inverse distance weighting     */
      /* Initialize variables */
      /* 'interpol_flux_scatter_psiq:164' N_sum=single(zeros(3,1)); */
      rtInterpMeshGrid_DW->N_sum[0] = 0.0F;
      rtInterpMeshGrid_DW->N_sum[1] = 0.0F;
      rtInterpMeshGrid_DW->N_sum[2] = 0.0F;

      /* 'interpol_flux_scatter_psiq:165' dis_sum=single(0); */
      dis_gitter_alt = 0.0F;

      /* weighting factor p for consistent gradient of the surface */
      /* the lower p is the more  is the gradient unified  */
      /* 'interpol_flux_scatter_psiq:170' p=2; */
      /* =square weighting   */
      /* Sum up normal vectors and weight the vectors by distance to the grid */
      /* point */
      /* 'interpol_flux_scatter_psiq:175' for(t=single(1):single(n_curr) */
      for (k = 0; k <= n_curr; k++) {
        /* 'interpol_flux_scatter_psiq:176' array(4,t)=( (rangeX(m) - array(1,t) )^2  +  ( rangeY(n)-array(2,t) )^2    )^0.5; */
        dis_gitter = rangeX[rtInterpMeshGrid_DW->i2] - array[103 * k];
        N_sum_tmp_1 = rangeY[i3] - array[103 * k + 1];
        array_tmp = 103 * k + 3;
        array[array_tmp] = sqrtf(dis_gitter * dis_gitter + N_sum_tmp_1 *
          N_sum_tmp_1);

        /* 'interpol_flux_scatter_psiq:177' N_sum(:,1)=N_sum(:,1)+N(:,t)*(1/array(4,t))^p; */
        N_sum_tmp = 1.0F / array[array_tmp];
        dis_gitter = N_sum_tmp * N_sum_tmp;
        rtInterpMeshGrid_DW->N_sum[0] += rtInterpMeshGrid_DW->N[3 * k] *
          dis_gitter;
        rtInterpMeshGrid_DW->N_sum[1] += rtInterpMeshGrid_DW->N[3 * k + 1] *
          dis_gitter;
        rtInterpMeshGrid_DW->N_sum[2] += rtInterpMeshGrid_DW->N[3 * k + 2] *
          dis_gitter;

        /* 'interpol_flux_scatter_psiq:178' dis_sum=dis_sum+(1/array(4,t))^p; */
        dis_gitter_alt += N_sum_tmp * N_sum_tmp;
      }

      /* Calculate griddata with averaged normal vector starting at the nearest */
      /* measuring points  */
      /* Average N_aver */
      /* 'interpol_flux_scatter_psiq:185' N_aver(:)=N_sum(:)/(dis_sum); */
      dis_gitter = rtInterpMeshGrid_DW->N_sum[0] / dis_gitter_alt;
      N_sum_tmp = rtInterpMeshGrid_DW->N_sum[1] / dis_gitter_alt;
      N_sum_tmp_1 = rtInterpMeshGrid_DW->N_sum[2] / dis_gitter_alt;

      /* Normalizing the Vectors N_aver */
      /* 'interpol_flux_scatter_psiq:187' abs_N=(N_aver(1)*N_aver(1)+N_aver(2)*N_aver(2)+N_aver(3)*N_aver(3))^0.5; */
      dis_gitter_alt = sqrtf((dis_gitter * dis_gitter + N_sum_tmp * N_sum_tmp) +
        N_sum_tmp_1 * N_sum_tmp_1);

      /* 'interpol_flux_scatter_psiq:188' N_aver(:)=N_aver(:)/abs_N; */
      N_sum_tmp /= dis_gitter_alt;

      /* 'interpol_flux_scatter_psiq:190' grid(n,m)=( dot(N_aver,OA)-N_aver(1)*rangeX(m)-N_aver(2)*rangeY(n))/( N_aver(3) ); */
      dis_gitter /= dis_gitter_alt;
      dis_gitter_alt = N_sum_tmp_1 / dis_gitter_alt;
      grid[i3 + 20 * rtInterpMeshGrid_DW->i2] = ((((dis_gitter * OA_idx_0 +
        N_sum_tmp * OA_idx_1) + dis_gitter_alt * OA_idx_2) - dis_gitter *
        rangeX[rtInterpMeshGrid_DW->i2]) - N_sum_tmp * rangeY[i3]) /
        dis_gitter_alt;
    }
  }

  /* 'interpol_flux_scatter_psiq:194' grid_old=grid; */
  memcpy(&rtInterpMeshGrid_DW->grid_old[0], &grid[0], 400U * sizeof(real32_T));

  /* Smooth Surface */
  /* 'interpol_flux_scatter_psiq:199' for(m=single(1):single(length(rangeX(1,:))) */
  for (n_curr = 0; n_curr < 20; n_curr++) {
    /* 'interpol_flux_scatter_psiq:200' for(n=single(1):single(length(rangeY(1,:))) */
    for (rtInterpMeshGrid_DW->i2 = 0; rtInterpMeshGrid_DW->i2 < 20;
         rtInterpMeshGrid_DW->i2++) {
      /* 'interpol_flux_scatter_psiq:201' grid_sum=single(0); */
      /* 'interpol_flux_scatter_psiq:202' grid_count=single(0); */
      /* 'interpol_flux_scatter_psiq:204' for(t=single(0):single(2) */
      /* 'interpol_flux_scatter_psiq:206' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0) */
      /* 'interpol_flux_scatter_psiq:212' if(t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
      /* 'interpol_flux_scatter_psiq:218' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0&&t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
      /* 'interpol_flux_scatter_psiq:226' if(t==0) */
      /* 'interpol_flux_scatter_psiq:227' grid_sum=grid_sum+grid_old(n,m); */
      dis_gitter_alt = rtInterpMeshGrid_DW->grid_old[20 * n_curr +
        rtInterpMeshGrid_DW->i2];

      /* 'interpol_flux_scatter_psiq:228' grid_count=grid_count+1; */
      dis_gitter = 1.0F;

      /* 'interpol_flux_scatter_psiq:206' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0) */
      if ((rtInterpMeshGrid_DW->i2 + 2 <= 20) && (rtInterpMeshGrid_DW->i2 > 0))
      {
        /* 'interpol_flux_scatter_psiq:207' grid_sum=grid_sum+grid_old(n+t,m); */
        /* 'interpol_flux_scatter_psiq:208' grid_sum=grid_sum+grid_old(n-t,m); */
        i3 = 20 * n_curr + rtInterpMeshGrid_DW->i2;
        dis_gitter_alt = (rtInterpMeshGrid_DW->grid_old[i3 + 1] + dis_gitter_alt)
          + rtInterpMeshGrid_DW->grid_old[i3 - 1];

        /* 'interpol_flux_scatter_psiq:209' grid_count=grid_count+2; */
        dis_gitter = 3.0F;
      }

      /* 'interpol_flux_scatter_psiq:212' if(t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
      if ((n_curr + 2 <= 20) && (n_curr > 0)) {
        /* 'interpol_flux_scatter_psiq:213' grid_sum=grid_sum+grid_old(n,m+t); */
        /* 'interpol_flux_scatter_psiq:214' grid_sum=grid_sum+grid_old(n,m-t); */
        dis_gitter_alt = (rtInterpMeshGrid_DW->grid_old[(n_curr + 1) * 20 +
                          rtInterpMeshGrid_DW->i2] + dis_gitter_alt) +
          rtInterpMeshGrid_DW->grid_old[(n_curr - 1) * 20 +
          rtInterpMeshGrid_DW->i2];

        /* 'interpol_flux_scatter_psiq:215' grid_count=grid_count+2; */
        dis_gitter += 2.0F;
      }

      /* 'interpol_flux_scatter_psiq:218' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0&&t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
      if ((rtInterpMeshGrid_DW->i2 + 2 <= 20) && (rtInterpMeshGrid_DW->i2 > 0) &&
          (n_curr + 2 <= 20) && (n_curr > 0)) {
        /* 'interpol_flux_scatter_psiq:219' grid_sum=grid_sum+grid_old(n+t,m+t); */
        /* 'interpol_flux_scatter_psiq:220' grid_sum=grid_sum+grid_old(n+t,m-t); */
        /* 'interpol_flux_scatter_psiq:221' grid_sum=grid_sum+grid_old(n-t,m-t); */
        /* 'interpol_flux_scatter_psiq:222' grid_sum=grid_sum+grid_old(n-t,m+t); */
        i3 = (n_curr - 1) * 20 + rtInterpMeshGrid_DW->i2;
        k = (n_curr + 1) * 20 + rtInterpMeshGrid_DW->i2;
        dis_gitter_alt = (((rtInterpMeshGrid_DW->grid_old[k + 1] +
                            dis_gitter_alt) + rtInterpMeshGrid_DW->grid_old[i3 +
                           1]) + rtInterpMeshGrid_DW->grid_old[i3 - 1]) +
          rtInterpMeshGrid_DW->grid_old[k - 1];

        /* 'interpol_flux_scatter_psiq:223' grid_count=grid_count+4; */
        dis_gitter += 4.0F;
      }

      /* 'interpol_flux_scatter_psiq:226' if(t==0) */
      /* 'interpol_flux_scatter_psiq:206' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0) */
      if ((rtInterpMeshGrid_DW->i2 + 3 <= 20) && (rtInterpMeshGrid_DW->i2 - 1 >
           0)) {
        /* 'interpol_flux_scatter_psiq:207' grid_sum=grid_sum+grid_old(n+t,m); */
        /* 'interpol_flux_scatter_psiq:208' grid_sum=grid_sum+grid_old(n-t,m); */
        i3 = 20 * n_curr + rtInterpMeshGrid_DW->i2;
        dis_gitter_alt = (rtInterpMeshGrid_DW->grid_old[i3 + 2] + dis_gitter_alt)
          + rtInterpMeshGrid_DW->grid_old[i3 - 2];

        /* 'interpol_flux_scatter_psiq:209' grid_count=grid_count+2; */
        dis_gitter += 2.0F;
      }

      /* 'interpol_flux_scatter_psiq:212' if(t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
      if ((n_curr + 3 <= 20) && (n_curr - 1 > 0)) {
        /* 'interpol_flux_scatter_psiq:213' grid_sum=grid_sum+grid_old(n,m+t); */
        /* 'interpol_flux_scatter_psiq:214' grid_sum=grid_sum+grid_old(n,m-t); */
        dis_gitter_alt = (rtInterpMeshGrid_DW->grid_old[(n_curr + 2) * 20 +
                          rtInterpMeshGrid_DW->i2] + dis_gitter_alt) +
          rtInterpMeshGrid_DW->grid_old[(n_curr - 2) * 20 +
          rtInterpMeshGrid_DW->i2];

        /* 'interpol_flux_scatter_psiq:215' grid_count=grid_count+2; */
        dis_gitter += 2.0F;
      }

      /* 'interpol_flux_scatter_psiq:218' if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0&&t+m<=length(rangeX(1,:))&&m-t>0&&t~=0) */
      if ((rtInterpMeshGrid_DW->i2 + 3 <= 20) && (rtInterpMeshGrid_DW->i2 - 1 >
           0) && (n_curr + 3 <= 20) && (n_curr - 1 > 0)) {
        /* 'interpol_flux_scatter_psiq:219' grid_sum=grid_sum+grid_old(n+t,m+t); */
        /* 'interpol_flux_scatter_psiq:220' grid_sum=grid_sum+grid_old(n+t,m-t); */
        /* 'interpol_flux_scatter_psiq:221' grid_sum=grid_sum+grid_old(n-t,m-t); */
        /* 'interpol_flux_scatter_psiq:222' grid_sum=grid_sum+grid_old(n-t,m+t); */
        i3 = (n_curr - 2) * 20 + rtInterpMeshGrid_DW->i2;
        k = (n_curr + 2) * 20 + rtInterpMeshGrid_DW->i2;
        dis_gitter_alt = (((rtInterpMeshGrid_DW->grid_old[k + 2] +
                            dis_gitter_alt) + rtInterpMeshGrid_DW->grid_old[i3 +
                           2]) + rtInterpMeshGrid_DW->grid_old[i3 - 2]) +
          rtInterpMeshGrid_DW->grid_old[k - 2];

        /* 'interpol_flux_scatter_psiq:223' grid_count=grid_count+4; */
        dis_gitter += 4.0F;
      }

      /* 'interpol_flux_scatter_psiq:226' if(t==0) */
      /* 'interpol_flux_scatter_psiq:232' grid(n,m)=grid_sum/grid_count; */
      grid[rtInterpMeshGrid_DW->i2 + 20 * n_curr] = dis_gitter_alt / dis_gitter;
    }
  }
}

/* Function for MATLAB Function: '<Root>/InterpMeshGrid' */
static void minimum(const real32_T x[400], real32_T ex[20])
{
  int32_T i;
  int32_T j;
  real32_T ex_0;
  real32_T tmp;
  for (j = 0; j < 20; j++) {
    ex[j] = x[20 * j];
    for (i = 0; i < 19; i++) {
      ex_0 = ex[j];
      tmp = x[(20 * j + i) + 1];
      if (ex_0 > tmp) {
        ex_0 = tmp;
      }

      ex[j] = ex_0;
    }
  }
}

/* Model step function */
void InterpMeshGrid_step(RT_MODEL_InterpMeshGrid_t *const rtInterpMeshGrid_M)
{
  DW_InterpMeshGrid_t *rtInterpMeshGrid_DW = rtInterpMeshGrid_M->dwork;
  ExtU_InterpMeshGrid_t *rtInterpMeshGrid_U = (ExtU_InterpMeshGrid_t *)
    rtInterpMeshGrid_M->inputs;
  ExtY_InterpMeshGrid_t *rtInterpMeshGrid_Y = (ExtY_InterpMeshGrid_t *)
    rtInterpMeshGrid_M->outputs;

  /* MATLAB Function: '<Root>/InterpMeshGrid' incorporates:
	 *  Inport: '<Root>/OnlineID_input'
	 *  Inport: '<Root>/i_rat'
   *  Inport: '<Root>/psi_array_in'
   */
  /* Author Philipp Gebhardt */
  /*  Oktober 2019 */
  /* MATLAB Function 'InterpMeshGrid': '<S1>:1' */
  /* This function is calculating the regular flux maps out of the irregular scatter data array stored in psi_array_in. The Outputs rangeX are containg the flux maps axis information which range is related to 3 times i_rat input. */
  /* Furthermore the temperature dependency of the permanent flux is calculated if there are enough measuring values stored in the delta_psi_array. The temperature constant as well as the estimated error of permanent flux */
  /* at reference temperature are given out on psi_temp_const and psi_temp_error outputs.  Using this temperature dependency the flux maps are updated with the permanent flux offset caused by the temperature which is given */
  /* in on OnlineID_input.Wtemp input.  */
  /* ----------------------------------------------------------------------------------------------------------------------------------------- */
  /* initalising Outputs */
  /* ----------------------------------------------------------------------------------------------------------------------------------------- */
  /* '<S1>:1:14' psi_array=zeros(6,100); */
  /* '<S1>:1:15' psi_array=psi_array_in; */
  memcpy(&rtInterpMeshGrid_DW->psi_array_m[0], &rtInterpMeshGrid_U->
         psi_array_in[0], 600U * sizeof(real32_T));

  /* '<S1>:1:16' delta_psi=zeros(100,1); */
  memset(&rtInterpMeshGrid_DW->delta_psi[0], 0, 100U * sizeof(real_T));

	/* '<S1>:1:18' FluxMapData.psid_grid=single(zeros(20,20)); */
	/* '<S1>:1:19' FluxMapData.psiq_grid=single(zeros(20,20)); */
	/* '<S1>:1:20' FluxMapData.id_grid=single(zeros(20,20)); */
	/* '<S1>:1:21' FluxMapData.iq_grid=single(zeros(20,20)); */
	/* '<S1>:1:22' FluxMapData.range_id_Y=single(zeros(1,20)); */
	/* '<S1>:1:23' FluxMapData.range_psid_Y=single(zeros(1,20)); */
	/* '<S1>:1:24' FluxMapData.range_psiq_Y=single(zeros(1,20)); */
	/* '<S1>:1:25' FluxMapData.range_psid_X=single(zeros(1,20)); */
	/* '<S1>:1:26' FluxMapData.range_psiq_X=single(zeros(1,20)); */
	/* '<S1>:1:27' FluxMapData.range_iq_Y=single(zeros(1,20)); */
	/* '<S1>:1:28' FluxMapData.range_iq_X=single(zeros(1,20)); */
	/* '<S1>:1:29' FluxMapData.range_id_X=single(zeros(1,20)); */
	/* '<S1>:1:30' FluxMapData.psi_temp_const=single(0.000001); */
	rtInterpMeshGrid_DW->rtb_FluxMapData_psi_temp_const = 1.0E-6F;

	/* '<S1>:1:31' FluxMapData.psi_temp_error=single(0); */
	/* '<S1>:1:35' range_psid_X_in=single(zeros(1,20)); */
	/* '<S1>:1:36' range_psid_Y_in=single(zeros(1,20)); */
	/* '<S1>:1:37' range_psiq_X_in=single(zeros(1,20)); */
	/* '<S1>:1:38' range_psiq_Y_in=single(zeros(1,20)); */
	/* '<S1>:1:39' range_id_X_in=single(zeros(1,20)); */
	/* '<S1>:1:40' range_id_Y_in=single(zeros(1,20)); */
	/* '<S1>:1:41' range_iq_X_in=single(zeros(1,20)); */
	/* '<S1>:1:42' range_iq_Y_in=single(zeros(1,20)); */
  /* initalise range of flux maps axis */
	/* '<S1>:1:46' for t=single(0):single(19) */
  for (rtInterpMeshGrid_DW->t = 0; rtInterpMeshGrid_DW->t < 20;
       rtInterpMeshGrid_DW->t++) {
		/* '<S1>:1:47' range_psid_X_in(t+1)=-3*i_rat+t*4*i_rat/19; */
		rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = (real32_T) rtInterpMeshGrid_DW->t * 4.0F * rtInterpMeshGrid_U->i_rat / 19.0F + -3.0F *
      rtInterpMeshGrid_U->i_rat;
		rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->t] = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;

		/* '<S1>:1:48' range_psid_Y_in(t+1)=-3*i_rat+t*6*i_rat/19; */
		rtInterpMeshGrid_DW->range_psid_Y_in_tmp = (real32_T) rtInterpMeshGrid_DW->t *
      6.0F * rtInterpMeshGrid_U->i_rat / 19.0F + -3.0F *
      rtInterpMeshGrid_U->i_rat;
		rtInterpMeshGrid_DW->range_psid_Y_in[rtInterpMeshGrid_DW->t] = rtInterpMeshGrid_DW->range_psid_Y_in_tmp;

		/* '<S1>:1:49' range_psiq_X_in(t+1)=-3*i_rat+t*4*i_rat/19; */
		rtInterpMeshGrid_DW->range_psiq_X_in[rtInterpMeshGrid_DW->t] = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;

		/* '<S1>:1:50' range_psiq_Y_in(t+1)=-3*i_rat+t*6*i_rat/19; */
		rtInterpMeshGrid_DW->range_psiq_Y_in[rtInterpMeshGrid_DW->t] = rtInterpMeshGrid_DW->range_psid_Y_in_tmp;
  }

  /* Calculate flux deviation from amout of measuring values and counter sum, */
  /* to average a big amount of measuring values  */
	/* '<S1>:1:56' for t=single(1):single(100) */
  for (rtInterpMeshGrid_DW->t = 0; rtInterpMeshGrid_DW->t < 100;
       rtInterpMeshGrid_DW->t++) {
		/* '<S1>:1:57' if (OnlineID_input.delta_psi(t,2)>5) */
		rtInterpMeshGrid_DW->range_psid_X_in_tmp_f =
      rtInterpMeshGrid_U->OnlineID_input.delta_psi[rtInterpMeshGrid_DW->t + 100];
		if (rtInterpMeshGrid_DW->range_psid_X_in_tmp_f > 5.0F) {
			/* '<S1>:1:58' delta_psi(t,1)=OnlineID_input.delta_psi(t,1)/OnlineID_input.delta_psi(t,2); */
      rtInterpMeshGrid_DW->delta_psi[rtInterpMeshGrid_DW->t] =
        rtInterpMeshGrid_U->OnlineID_input.delta_psi[rtInterpMeshGrid_DW->t] /
        rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
    }
  }

	/* Outport: '<Root>/FluxMapData' incorporates:
   *  MATLAB Function: '<Root>/InterpMeshGrid'
   */
  /* Calculate temperature constant with a regressionline, set second input "1" */
  /* to resist outliers greater than 30% (relative to their neighbours) */
	/* '<S1>:1:65' [psi_temp_const_test,FluxMapData.psi_temp_error]=regressionline(delta_psi,1); */
  regressionline(rtInterpMeshGrid_DW->delta_psi, 1.0,
                 &rtInterpMeshGrid_DW->range_psid_Y_in_tmp, &rtInterpMeshGrid_Y->FluxMapData.psi_temp_error);

  /* MATLAB Function: '<Root>/InterpMeshGrid' incorporates:
   *  Inport: '<Root>/OnlineID_input'
   */
  /* check plausibility */
	/* '<S1>:1:68' if(psi_temp_const_test>0&&FluxMapData.psi_temp_const<10) */
	if (rtInterpMeshGrid_DW->range_psid_Y_in_tmp > 0.0F) {
		/* in mVs/°C */
		/* '<S1>:1:69' FluxMapData.psi_temp_const=psi_temp_const_test; */
		rtInterpMeshGrid_DW->rtb_FluxMapData_psi_temp_const = rtInterpMeshGrid_DW->range_psid_Y_in_tmp;
  }

  /* correct temperature offset */
	/* '<S1>:1:74' for k=single(1):single(100) */
  /* Inter- and extrapolation of the flux maps  */
	/* '<S1>:1:86' [FluxMapData.range_psid_X,FluxMapData.range_psid_Y,FluxMapData.psid_grid] = interpol_flux_scatter_psid ([psi_array(1,:);psi_array(2,:);psi_array(5,:);zeros(length(psi_array(1,:)))],range_psid_X_in,range_psid_Y_in); */
  for (rtInterpMeshGrid_DW->t = 0; rtInterpMeshGrid_DW->t < 100;
       rtInterpMeshGrid_DW->t++) {
		/* '<S1>:1:75' if(psi_array(3,k)~=0) */
    if (rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->t + 2] != 0.0F)
    {
			/* '<S1>:1:76' psi_array(5,k)=psi_array(5,k)+(psi_array(4,k)-OnlineID_input.Wtemp)*FluxMapData.psi_temp_const; */
			rtInterpMeshGrid_DW->i = 6 * rtInterpMeshGrid_DW->t + 4;
			rtInterpMeshGrid_DW->psi_array_tmp = 6 * rtInterpMeshGrid_DW->t + 3;
			rtInterpMeshGrid_DW->psi_array_m[rtInterpMeshGrid_DW->i] += (rtInterpMeshGrid_DW->psi_array_m[rtInterpMeshGrid_DW->psi_array_tmp] -
         rtInterpMeshGrid_U->OnlineID_input.Wtemp) *
        rtInterpMeshGrid_DW->rtb_FluxMapData_psi_temp_const;

			/* '<S1>:1:77' psi_array(4,k)=OnlineID_input.Wtemp; */
			rtInterpMeshGrid_DW->psi_array_m[rtInterpMeshGrid_DW->psi_array_tmp] =
        rtInterpMeshGrid_U->OnlineID_input.Wtemp;
    }

    rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->t] =
      rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->t];
    rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->t + 1] =
      rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->t + 1];
    rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->t + 2] =
      rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->t + 4];
  }

  for (rtInterpMeshGrid_DW->t = 0; rtInterpMeshGrid_DW->t < 100;
       rtInterpMeshGrid_DW->t++) {
    memset(&rtInterpMeshGrid_DW->psi_array[rtInterpMeshGrid_DW->t * 103 + 3], 0,
           100U * sizeof(real32_T));
  }

	interpol_flux_scatter_psid(rtInterpMeshGrid_DW->psi_array, rtInterpMeshGrid_DW->range_psid_X_in, rtInterpMeshGrid_DW->range_psid_Y_in, rtInterpMeshGrid_DW->c, rtInterpMeshGrid_DW);

	/* Outport: '<Root>/FluxMapData' incorporates:
   *  MATLAB Function: '<Root>/InterpMeshGrid'
   */
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.range_psid_X[0], &rtInterpMeshGrid_DW->range_psid_X_in[0], 20U * sizeof(real32_T));

  /* MATLAB Function: '<Root>/InterpMeshGrid' */
	memcpy(&rtInterpMeshGrid_DW->rtb_FluxMapData_psid_grid[0], &rtInterpMeshGrid_DW->c[0], 400U * sizeof(real32_T));

	/* '<S1>:1:87' [FluxMapData.range_psiq_X,FluxMapData.range_psiq_Y,FluxMapData.psiq_grid] = interpol_flux_scatter_psiq ([psi_array(1,:);psi_array(2,:);psi_array(6,:);zeros(length(psi_array(1,:)))],range_psiq_X_in,range_psiq_Y_in); */
	for (rtInterpMeshGrid_DW->i = 0; rtInterpMeshGrid_DW->i < 100; rtInterpMeshGrid_DW->i++) {
		rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->i] = rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->i];
		rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->i + 1] = rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->i + 1];
		rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->i + 2] = rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->i + 5];
  }

	for (rtInterpMeshGrid_DW->i = 0; rtInterpMeshGrid_DW->i < 100; rtInterpMeshGrid_DW->i++) {
		memset(&rtInterpMeshGrid_DW->psi_array[rtInterpMeshGrid_DW->i * 103 + 3], 0, 100U * sizeof(real32_T));
  }

	interpol_flux_scatter_psiq(rtInterpMeshGrid_DW->psi_array, rtInterpMeshGrid_DW->range_psiq_X_in, rtInterpMeshGrid_DW->range_psiq_Y_in, rtInterpMeshGrid_DW->c, rtInterpMeshGrid_DW);

	/* Outport: '<Root>/FluxMapData' incorporates:
   *  MATLAB Function: '<Root>/InterpMeshGrid'
   */
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.psiq_grid[0], &rtInterpMeshGrid_DW->c[0], 400U * sizeof(real32_T));

	/* MATLAB Function: '<Root>/InterpMeshGrid' */
  /* initialise range of inverse flux maps axis */
	/* '<S1>:1:90' for t=single(0):single(19) */
	minimum(rtInterpMeshGrid_DW->rtb_FluxMapData_psid_grid, rtInterpMeshGrid_DW->range_psid_X_in_tmp);
	minimum(rtInterpMeshGrid_DW->c, rtInterpMeshGrid_DW->range_psid_X_in_tmp_c);
  for (rtInterpMeshGrid_DW->t = 0; rtInterpMeshGrid_DW->t < 20;
       rtInterpMeshGrid_DW->t++) {
		/* '<S1>:1:91' range_id_X_in(t+1)=min(min(FluxMapData.psid_grid))+t*(max(max(FluxMapData.psid_grid))-min(min(FluxMapData.psid_grid)))/19; */
		rtInterpMeshGrid_DW->range_psid_Y_in_tmp = rtInterpMeshGrid_DW->range_psid_X_in_tmp[0];
		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 19; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in_tmp[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->range_psid_Y_in_tmp > rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->range_psid_Y_in_tmp = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }
    }

		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 20; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp] = rtInterpMeshGrid_DW->rtb_FluxMapData_psid_grid[20 * rtInterpMeshGrid_DW->psi_array_tmp];
      for (rtInterpMeshGrid_DW->i = 0; rtInterpMeshGrid_DW->i < 19;
           rtInterpMeshGrid_DW->i++) {
				rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp];
				rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->rtb_FluxMapData_psid_grid[(20 * rtInterpMeshGrid_DW->psi_array_tmp + rtInterpMeshGrid_DW->i) + 1];
				if (rtInterpMeshGrid_DW->range_psid_X_in_c < rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
					rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
        }

				rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp] = rtInterpMeshGrid_DW->range_psid_X_in_c;
      }
    }

		rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in[0];
		rtInterpMeshGrid_DW->c_ex = rtInterpMeshGrid_DW->range_psid_X_in_tmp[0];
		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 19; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->range_psid_X_in_c < rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }

			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in_tmp[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->c_ex > rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->c_ex = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }
    }

		rtInterpMeshGrid_DW->range_id_X_in[rtInterpMeshGrid_DW->t] = (rtInterpMeshGrid_DW->range_psid_X_in_c - rtInterpMeshGrid_DW->c_ex) * (real32_T) rtInterpMeshGrid_DW->t / 19.0F
		                + rtInterpMeshGrid_DW->range_psid_Y_in_tmp;

		/* '<S1>:1:92' range_id_Y_in(t+1)=min(min(FluxMapData.psiq_grid))+t*(max(max(FluxMapData.psiq_grid))-min(min(FluxMapData.psiq_grid)))/19; */
		rtInterpMeshGrid_DW->range_psid_Y_in_tmp = rtInterpMeshGrid_DW->range_psid_X_in_tmp_c[0];
		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 19; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in_tmp_c[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->range_psid_Y_in_tmp > rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->range_psid_Y_in_tmp = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }
    }

		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 20; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp] = rtInterpMeshGrid_DW->c[20 * rtInterpMeshGrid_DW->psi_array_tmp];
      for (rtInterpMeshGrid_DW->i = 0; rtInterpMeshGrid_DW->i < 19;
           rtInterpMeshGrid_DW->i++) {
				rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp];
				rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->c[(20 * rtInterpMeshGrid_DW->psi_array_tmp + rtInterpMeshGrid_DW->i) + 1];
				if (rtInterpMeshGrid_DW->range_psid_X_in_c < rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
					rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
        }

				rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp] = rtInterpMeshGrid_DW->range_psid_X_in_c;
      }
    }

		rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in[0];
		rtInterpMeshGrid_DW->c_ex = rtInterpMeshGrid_DW->range_psid_X_in_tmp_c[0];
		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 19; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->range_psid_X_in_c < rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }

			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in_tmp_c[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->c_ex > rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->c_ex = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }
    }

		rtInterpMeshGrid_DW->range_id_Y_in[rtInterpMeshGrid_DW->t] = (rtInterpMeshGrid_DW->range_psid_X_in_c - rtInterpMeshGrid_DW->c_ex) * (real32_T) rtInterpMeshGrid_DW->t / 19.0F
		                + rtInterpMeshGrid_DW->range_psid_Y_in_tmp;

		/* '<S1>:1:93' range_iq_X_in(t+1)=min(min(FluxMapData.psid_grid))+t*(max(max(FluxMapData.psid_grid))-min(min(FluxMapData.psid_grid)))/19; */
		rtInterpMeshGrid_DW->range_psid_Y_in_tmp = rtInterpMeshGrid_DW->range_psid_X_in_tmp[0];
		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 19; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in_tmp[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->range_psid_Y_in_tmp > rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->range_psid_Y_in_tmp = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }
    }

		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 20; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp] = rtInterpMeshGrid_DW->rtb_FluxMapData_psid_grid[20 * rtInterpMeshGrid_DW->psi_array_tmp];
      for (rtInterpMeshGrid_DW->i = 0; rtInterpMeshGrid_DW->i < 19;
           rtInterpMeshGrid_DW->i++) {
				rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp];
				rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->rtb_FluxMapData_psid_grid[(20 * rtInterpMeshGrid_DW->psi_array_tmp + rtInterpMeshGrid_DW->i) + 1];
				if (rtInterpMeshGrid_DW->range_psid_X_in_c < rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
					rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
        }

				rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp] = rtInterpMeshGrid_DW->range_psid_X_in_c;
      }
    }

		rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in[0];
		rtInterpMeshGrid_DW->c_ex = rtInterpMeshGrid_DW->range_psid_X_in_tmp[0];
		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 19; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->range_psid_X_in_c < rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }

			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in_tmp[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->c_ex > rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->c_ex = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }
    }

		rtInterpMeshGrid_DW->range_iq_X_in[rtInterpMeshGrid_DW->t] = (rtInterpMeshGrid_DW->range_psid_X_in_c - rtInterpMeshGrid_DW->c_ex) * (real32_T) rtInterpMeshGrid_DW->t / 19.0F
		                + rtInterpMeshGrid_DW->range_psid_Y_in_tmp;

		/* '<S1>:1:94' range_iq_Y_in(t+1)=min(min(FluxMapData.psiq_grid))+t*(max(max(FluxMapData.psiq_grid))-min(min(FluxMapData.psiq_grid)))/19; */
		rtInterpMeshGrid_DW->range_psid_Y_in_tmp = rtInterpMeshGrid_DW->range_psid_X_in_tmp_c[0];
		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 19; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in_tmp_c[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->range_psid_Y_in_tmp > rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->range_psid_Y_in_tmp = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }
    }

		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 20; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp] = rtInterpMeshGrid_DW->c[20 * rtInterpMeshGrid_DW->psi_array_tmp];
      for (rtInterpMeshGrid_DW->i = 0; rtInterpMeshGrid_DW->i < 19;
           rtInterpMeshGrid_DW->i++) {
				rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp];
				rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->c[(20 * rtInterpMeshGrid_DW->psi_array_tmp + rtInterpMeshGrid_DW->i) + 1];
				if (rtInterpMeshGrid_DW->range_psid_X_in_c < rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
					rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
        }

				rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp] = rtInterpMeshGrid_DW->range_psid_X_in_c;
      }
    }

		rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in[0];
		rtInterpMeshGrid_DW->c_ex = rtInterpMeshGrid_DW->range_psid_X_in_tmp_c[0];
		for (rtInterpMeshGrid_DW->psi_array_tmp = 0; rtInterpMeshGrid_DW->psi_array_tmp < 19; rtInterpMeshGrid_DW->psi_array_tmp++) {
			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->range_psid_X_in_c < rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->range_psid_X_in_c = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }

			rtInterpMeshGrid_DW->range_psid_X_in_tmp_f = rtInterpMeshGrid_DW->range_psid_X_in_tmp_c[rtInterpMeshGrid_DW->psi_array_tmp + 1];
			if (rtInterpMeshGrid_DW->c_ex > rtInterpMeshGrid_DW->range_psid_X_in_tmp_f) {
				rtInterpMeshGrid_DW->c_ex = rtInterpMeshGrid_DW->range_psid_X_in_tmp_f;
      }
    }

		rtInterpMeshGrid_DW->range_iq_Y_in[rtInterpMeshGrid_DW->t] = (rtInterpMeshGrid_DW->range_psid_X_in_c - rtInterpMeshGrid_DW->c_ex) * (real32_T) rtInterpMeshGrid_DW->t / 19.0F
		                + rtInterpMeshGrid_DW->range_psid_Y_in_tmp;
  }

  /* Inter and extrapolate inverse flux maps */
	/* '<S1>:1:98' [FluxMapData.range_id_X,FluxMapData.range_id_Y,FluxMapData.id_grid] = interpol_flux_scatter_psid ([psi_array(5,:);psi_array(6,:);psi_array(1,:);zeros(length(psi_array(1,:)))],range_id_X_in,range_id_Y_in); */
	for (rtInterpMeshGrid_DW->i = 0; rtInterpMeshGrid_DW->i < 100; rtInterpMeshGrid_DW->i++) {
		rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->i] = rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->i + 4];
		rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->i + 1] = rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->i + 5];
		rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->i + 2] = rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->i];
  }

	for (rtInterpMeshGrid_DW->i = 0; rtInterpMeshGrid_DW->i < 100; rtInterpMeshGrid_DW->i++) {
		memset(&rtInterpMeshGrid_DW->psi_array[rtInterpMeshGrid_DW->i * 103 + 3], 0, 100U * sizeof(real32_T));
  }

	interpol_flux_scatter_psid(rtInterpMeshGrid_DW->psi_array, rtInterpMeshGrid_DW->range_id_X_in, rtInterpMeshGrid_DW->range_id_Y_in, rtInterpMeshGrid_DW->c, rtInterpMeshGrid_DW);

	/* Outport: '<Root>/FluxMapData' incorporates:
   *  MATLAB Function: '<Root>/InterpMeshGrid'
   */
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.id_grid[0], &rtInterpMeshGrid_DW->c[0], 400U * sizeof(real32_T));

  /* MATLAB Function: '<Root>/InterpMeshGrid' */
	/* '<S1>:1:99' [FluxMapData.range_iq_X,FluxMapData.range_iq_Y,FluxMapData.iq_grid] = interpol_flux_scatter_psiq ([psi_array(5,:);psi_array(6,:);psi_array(2,:);zeros(length(psi_array(1,:)))],range_iq_X_in,range_iq_Y_in); */
	for (rtInterpMeshGrid_DW->i = 0; rtInterpMeshGrid_DW->i < 100; rtInterpMeshGrid_DW->i++) {
		rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->i] = rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->i + 4];
		rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->i + 1] = rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->i + 5];
		rtInterpMeshGrid_DW->psi_array[103 * rtInterpMeshGrid_DW->i + 2] = rtInterpMeshGrid_DW->psi_array_m[6 * rtInterpMeshGrid_DW->i + 1];
  }

	for (rtInterpMeshGrid_DW->i = 0; rtInterpMeshGrid_DW->i < 100; rtInterpMeshGrid_DW->i++) {
		memset(&rtInterpMeshGrid_DW->psi_array[rtInterpMeshGrid_DW->i * 103 + 3], 0, 100U * sizeof(real32_T));
  }

  interpol_flux_scatter_psiq(rtInterpMeshGrid_DW->psi_array,
    rtInterpMeshGrid_DW->range_iq_X_in, rtInterpMeshGrid_DW->range_iq_Y_in, rtInterpMeshGrid_DW->c, rtInterpMeshGrid_DW);

	/* Outport: '<Root>/FluxMapData' incorporates:
   *  MATLAB Function: '<Root>/InterpMeshGrid'
   */
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.psid_grid[0], &rtInterpMeshGrid_DW->rtb_FluxMapData_psid_grid[0], 400U * sizeof(real32_T));
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.iq_grid[0], &rtInterpMeshGrid_DW->c[0], 400U * sizeof(real32_T));
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.range_id_Y[0], &rtInterpMeshGrid_DW->range_id_Y_in[0], 20U * sizeof(real32_T));
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.range_psid_Y[0], &rtInterpMeshGrid_DW->range_psid_Y_in[0], 20U * sizeof(real32_T));
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.range_psiq_Y[0], &rtInterpMeshGrid_DW->range_psiq_Y_in[0], 20U * sizeof(real32_T));
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.range_psiq_X[0], &rtInterpMeshGrid_DW->range_psiq_X_in[0], 20U * sizeof(real32_T));
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.range_iq_Y[0], &rtInterpMeshGrid_DW->range_iq_Y_in[0], 20U * sizeof(real32_T));
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.range_iq_X[0], &rtInterpMeshGrid_DW->range_iq_X_in[0], 20U * sizeof(real32_T));
	memcpy(&rtInterpMeshGrid_Y->FluxMapData.range_id_X[0], &rtInterpMeshGrid_DW->range_id_X_in[0], 20U * sizeof(real32_T));
	rtInterpMeshGrid_Y->FluxMapData.psi_temp_const = rtInterpMeshGrid_DW->rtb_FluxMapData_psi_temp_const;
}

/* Model initialize function */
void InterpMeshGrid_initialize(RT_MODEL_InterpMeshGrid_t *const
  rtInterpMeshGrid_M)
{
  /* (no initialization code required) */
  UNUSED_PARAMETER(rtInterpMeshGrid_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
