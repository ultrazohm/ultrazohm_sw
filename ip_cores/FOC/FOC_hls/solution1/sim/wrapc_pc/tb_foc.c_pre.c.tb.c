// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/tb_foc.c"
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/tb_foc.c" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 147 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/tb_foc.c" 2
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_FOC.h" 1




# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_piController.h" 1


# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/include\\stdbool.h" 1 3 4
# 4 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_piController.h" 2




typedef struct uz_PI_Controller_config {
 float Kp;
 float Ki;
 float samplingTime_sec;
 float upper_limit;
 float lower_limit;
}uz_PI_Controller_config;
# 25 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_piController.h"
_Bool uz_PI_Controller_Clamping_Circuit(float preIntegrator, float preSat, float upper_limit, float lower_limit);
# 36 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_piController.h"
float uz_PI_Controller_sample(uz_PI_Controller_config* self, _Bool I_rst, float referenceValue, float actualValue, _Bool ext_clamping);
# 6 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_FOC.h" 2
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.h" 1
# 12 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.h"
float uz_signals_dead_zone(float input, float upper_threshold, float lower_threshold);







float uz_signals_get_sign_of_value(float input);
# 30 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.h"
float uz_signals_saturation(float input, float upper_limit, float lower_limit);
# 7 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_FOC.h" 2
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_Transformation.h" 1






struct uz_dq_t{
    float d;
    float q;
    float zero;
};





struct uz_alphabeta_t{
    float alpha;
    float beta;
    float gamma;
};





struct uz_UVW_t{
    float U;
    float V;
    float W;
};
# 40 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_Transformation.h"
struct uz_dq_t uz_dq_transformation(struct uz_UVW_t input, float theta_el_rad);
# 49 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_Transformation.h"
struct uz_UVW_t uz_dq_inverse_transformation(struct uz_dq_t input, float theta_el_rad);







struct uz_alphabeta_t uz_clarke_transformation(struct uz_UVW_t input);







struct uz_UVW_t uz_clarke_inverse_transformation(struct uz_alphabeta_t input);
# 8 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_FOC.h" 2
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_linear_decoupling.h" 1




struct uz_PMSM_t{
    float R_ph_Ohm;
    float Ld_Henry;
    float Lq_Henry;
    float Psi_PM_Vs;
    float polePairs;
    float J_kg_m_squared;
    float I_max_Ampere;
};
# 23 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_linear_decoupling.h"
struct uz_dq_t uz_FOC_linear_decoupling(struct uz_PMSM_t config, struct uz_dq_t i_actual_Ampere, float omega_el_rad_per_sec);
# 9 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_FOC.h" 2
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.h" 1
# 18 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.h"
struct uz_dq_t uz_FOC_SpaceVector_Limitation(struct uz_dq_t u_input_Volts, float V_dc_volts, float omega_el_rad_per_sec, struct uz_dq_t i_actual_Ampere, _Bool* ext_clamping);
# 10 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_FOC.h" 2
# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 1 3
# 10 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
# 10 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3


# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 1 3
# 10 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include/_mingw_mac.h" 1 3
# 10 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 2 3
# 277 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\vadefs.h" 1 3
# 13 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\vadefs.h" 3
# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 1 3
# 674 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include/sdks/_mingw_directx.h" 1 3
# 674 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 2 3

# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include/sdks/_mingw_ddk.h" 1 3
# 675 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 2 3
# 13 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\vadefs.h" 2 3


#pragma pack(push,_CRT_PACKING)








 typedef __builtin_va_list __gnuc_va_list;






  typedef __gnuc_va_list va_list;
# 102 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\vadefs.h" 3
#pragma pack(pop)
# 277 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 2 3


#pragma pack(push,_CRT_PACKING)
# 370 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
__extension__ typedef unsigned long long size_t;
# 380 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
__extension__ typedef long long ssize_t;
# 392 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
__extension__ typedef long long intptr_t;
# 405 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
__extension__ typedef unsigned long long uintptr_t;
# 418 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
__extension__ typedef long long ptrdiff_t;
# 428 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
typedef unsigned short wchar_t;







typedef unsigned short wint_t;
typedef unsigned short wctype_t;
# 456 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
typedef int errno_t;




typedef long __time32_t;




__extension__ typedef long long __time64_t;







typedef __time64_t time_t;
# 607 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct {
  pthreadlocinfo locinfo;
  pthreadmbcinfo mbcinfo;
} _locale_tstruct,*_locale_t;



typedef struct tagLC_ID {
  unsigned short wLanguage;
  unsigned short wCountry;
  unsigned short wCodePage;
} LC_ID,*LPLC_ID;




typedef struct threadlocaleinfostruct {
  int refcount;
  unsigned int lc_codepage;
  unsigned int lc_collate_cp;
  unsigned long lc_handle[6];
  LC_ID lc_id[6];
  struct {
    char *locale;
    wchar_t *wlocale;
    int *refcount;
    int *wrefcount;
  } lc_category[6];
  int lc_clike;
  int mb_cur_max;
  int *lconv_intl_refcount;
  int *lconv_num_refcount;
  int *lconv_mon_refcount;
  struct lconv *lconv;
  int *ctype1_refcount;
  unsigned short *ctype1;
  const unsigned short *pctype;
  const unsigned char *pclmap;
  const unsigned char *pcumap;
  struct __lc_time_data *lc_time_curr;
} threadlocinfo;







const char *__mingw_get_crt_info (void);





#pragma pack(pop)
# 12 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 2 3


struct _exception;

#pragma pack(push,_CRT_PACKING)
# 79 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
 extern double * __imp__HUGE;
# 91 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  struct _exception {
    int type;
    const char *name;
    double arg1;
    double arg2;
    double retval;
  };

  void __mingw_raise_matherr (int typ, const char *name, double a1, double a2,
         double rslt);
  void __mingw_setusermatherr (int (__cdecl *)(struct _exception *));
  __attribute__ ((__dllimport__)) void __setusermatherr(int (__cdecl *)(struct _exception *));



  double __cdecl sin(double _X);
  double __cdecl cos(double _X);
  double __cdecl tan(double _X);
  double __cdecl sinh(double _X);
  double __cdecl cosh(double _X);
  double __cdecl tanh(double _X);
  double __cdecl asin(double _X);
  double __cdecl acos(double _X);
  double __cdecl atan(double _X);
  double __cdecl atan2(double _Y,double _X);
  double __cdecl exp(double _X);
  double __cdecl log(double _X);
  double __cdecl log10(double _X);
  double __cdecl pow(double _X,double _Y);
  double __cdecl sqrt(double _X);
  double __cdecl ceil(double _X);
  double __cdecl floor(double _X);
  double __cdecl fabs(double _X);
# 135 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  double __cdecl ldexp(double _X,int _Y);
  double __cdecl frexp(double _X,int *_Y);
  double __cdecl modf(double _X,double *_Y);
  double __cdecl fmod(double _X,double _Y);

  void __cdecl sincos (double __x, double *p_sin, double *p_cos);
  void __cdecl sincosl (long double __x, long double *p_sin, long double *p_cos);
  void __cdecl sincosf (float __x, float *p_sin, float *p_cos);



  int __cdecl abs(int _X);
  long __cdecl labs(long _X);



  double __cdecl atof(const char *_String);
  double __cdecl _atof_l(const char *_String,_locale_t _Locale);
# 162 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  struct _complex {
    double x;
    double y;
  };


  __attribute__ ((__dllimport__)) double __cdecl _cabs(struct _complex _ComplexA);
  double __cdecl _hypot(double _X,double _Y);
  __attribute__ ((__dllimport__)) double __cdecl _j0(double _X);
  __attribute__ ((__dllimport__)) double __cdecl _j1(double _X);
  __attribute__ ((__dllimport__)) double __cdecl _jn(int _X,double _Y);
  __attribute__ ((__dllimport__)) double __cdecl _y0(double _X);
  __attribute__ ((__dllimport__)) double __cdecl _y1(double _X);
  __attribute__ ((__dllimport__)) double __cdecl _yn(int _X,double _Y);


  __attribute__ ((__dllimport__)) int __cdecl _matherr (struct _exception *);
# 189 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  __attribute__ ((__dllimport__)) double __cdecl _chgsign (double _X);
  __attribute__ ((__dllimport__)) double __cdecl _copysign (double _Number,double _Sign);
  __attribute__ ((__dllimport__)) double __cdecl _logb (double);
  __attribute__ ((__dllimport__)) double __cdecl _nextafter (double, double);
  __attribute__ ((__dllimport__)) double __cdecl _scalb (double, long);
  __attribute__ ((__dllimport__)) int __cdecl _finite (double);
  __attribute__ ((__dllimport__)) int __cdecl _fpclass (double);
  __attribute__ ((__dllimport__)) int __cdecl _isnan (double);






__attribute__ ((__dllimport__)) double __cdecl j0 (double) ;
__attribute__ ((__dllimport__)) double __cdecl j1 (double) ;
__attribute__ ((__dllimport__)) double __cdecl jn (int, double) ;
__attribute__ ((__dllimport__)) double __cdecl y0 (double) ;
__attribute__ ((__dllimport__)) double __cdecl y1 (double) ;
__attribute__ ((__dllimport__)) double __cdecl yn (int, double) ;

__attribute__ ((__dllimport__)) double __cdecl chgsign (double);
# 219 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  __attribute__ ((__dllimport__)) int __cdecl finite (double);
  __attribute__ ((__dllimport__)) int __cdecl fpclass (double);
# 264 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
typedef float float_t;
typedef double double_t;
# 299 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern int __cdecl __fpclassifyl (long double);
  extern int __cdecl __fpclassifyf (float);
  extern int __cdecl __fpclassify (double);
# 335 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern int __cdecl __isnan (double);
  extern int __cdecl __isnanf (float);
  extern int __cdecl __isnanl (long double);
# 376 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern int __cdecl __signbit (double);
  extern int __cdecl __signbitf (float);
  extern int __cdecl __signbitl (long double);
# 404 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern float __cdecl sinf(float _X);
  extern long double __cdecl sinl(long double);

  extern float __cdecl cosf(float _X);
  extern long double __cdecl cosl(long double);

  extern float __cdecl tanf(float _X);
  extern long double __cdecl tanl(long double);
  extern float __cdecl asinf(float _X);
  extern long double __cdecl asinl(long double);

  extern float __cdecl acosf (float);
  extern long double __cdecl acosl (long double);

  extern float __cdecl atanf (float);
  extern long double __cdecl atanl (long double);

  extern float __cdecl atan2f (float, float);
  extern long double __cdecl atan2l (long double, long double);


  extern float __cdecl sinhf(float _X);



  extern long double __cdecl sinhl(long double);

  extern float __cdecl coshf(float _X);



  extern long double __cdecl coshl(long double);

  extern float __cdecl tanhf(float _X);



  extern long double __cdecl tanhl(long double);



  extern double __cdecl acosh (double);
  extern float __cdecl acoshf (float);
  extern long double __cdecl acoshl (long double);


  extern double __cdecl asinh (double);
  extern float __cdecl asinhf (float);
  extern long double __cdecl asinhl (long double);


  extern double __cdecl atanh (double);
  extern float __cdecl atanhf (float);
  extern long double __cdecl atanhl (long double);



  extern float __cdecl expf(float _X);



  extern long double __cdecl expl(long double);


  extern double __cdecl exp2(double);
  extern float __cdecl exp2f(float);
  extern long double __cdecl exp2l(long double);



  extern double __cdecl expm1(double);
  extern float __cdecl expm1f(float);
  extern long double __cdecl expm1l(long double);


  extern float frexpf(float _X,int *_Y);



  extern long double __cdecl frexpl(long double,int *);




  extern int __cdecl ilogb (double);
  extern int __cdecl ilogbf (float);
  extern int __cdecl ilogbl (long double);


  extern float __cdecl ldexpf(float _X,int _Y);



  extern long double __cdecl ldexpl (long double, int);


  extern float __cdecl logf (float);
  extern long double __cdecl logl(long double);


  extern float __cdecl log10f (float);
  extern long double __cdecl log10l(long double);


  extern double __cdecl log1p(double);
  extern float __cdecl log1pf(float);
  extern long double __cdecl log1pl(long double);


  extern double __cdecl log2 (double);
  extern float __cdecl log2f (float);
  extern long double __cdecl log2l (long double);


  extern double __cdecl logb (double);
  extern float __cdecl logbf (float);
  extern long double __cdecl logbl (long double);
# 553 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern float __cdecl modff (float, float*);
  extern long double __cdecl modfl (long double, long double*);


  extern double __cdecl scalbn (double, int);
  extern float __cdecl scalbnf (float, int);
  extern long double __cdecl scalbnl (long double, int);

  extern double __cdecl scalbln (double, long);
  extern float __cdecl scalblnf (float, long);
  extern long double __cdecl scalblnl (long double, long);



  extern double __cdecl cbrt (double);
  extern float __cdecl cbrtf (float);
  extern long double __cdecl cbrtl (long double);


  extern float __cdecl fabsf (float x);
# 583 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern long double __cdecl fabsl (long double);
# 595 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern double __cdecl hypot (double, double) ;
  extern float __cdecl hypotf (float x, float y);



  extern long double __cdecl hypotl (long double, long double);


  extern float __cdecl powf(float _X,float _Y);



  extern long double __cdecl powl (long double, long double);


  extern float __cdecl sqrtf (float);
  extern long double sqrtl(long double);


  extern double __cdecl erf (double);
  extern float __cdecl erff (float);
  extern long double __cdecl erfl (long double);


  extern double __cdecl erfc (double);
  extern float __cdecl erfcf (float);
  extern long double __cdecl erfcl (long double);


  extern double __cdecl lgamma (double);
  extern float __cdecl lgammaf (float);
  extern long double __cdecl lgammal (long double);


  extern double __cdecl tgamma (double);
  extern float __cdecl tgammaf (float);
  extern long double __cdecl tgammal (long double);


  extern float __cdecl ceilf (float);
  extern long double __cdecl ceill (long double);


  extern float __cdecl floorf (float);
  extern long double __cdecl floorl (long double);


  extern double __cdecl nearbyint ( double);
  extern float __cdecl nearbyintf (float);
  extern long double __cdecl nearbyintl (long double);



extern double __cdecl rint (double);
extern float __cdecl rintf (float);
extern long double __cdecl rintl (long double);


extern long __cdecl lrint (double);
extern long __cdecl lrintf (float);
extern long __cdecl lrintl (long double);

__extension__ long long __cdecl llrint (double);
__extension__ long long __cdecl llrintf (float);
__extension__ long long __cdecl llrintl (long double);
# 739 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern double __cdecl round (double);
  extern float __cdecl roundf (float);
  extern long double __cdecl roundl (long double);


  extern long __cdecl lround (double);
  extern long __cdecl lroundf (float);
  extern long __cdecl lroundl (long double);
  __extension__ long long __cdecl llround (double);
  __extension__ long long __cdecl llroundf (float);
  __extension__ long long __cdecl llroundl (long double);



  extern double __cdecl trunc (double);
  extern float __cdecl truncf (float);
  extern long double __cdecl truncl (long double);


  extern float __cdecl fmodf (float, float);
  extern long double __cdecl fmodl (long double, long double);


  extern double __cdecl remainder (double, double);
  extern float __cdecl remainderf (float, float);
  extern long double __cdecl remainderl (long double, long double);


  extern double __cdecl remquo(double, double, int *);
  extern float __cdecl remquof(float, float, int *);
  extern long double __cdecl remquol(long double, long double, int *);


  extern double __cdecl copysign (double, double);
  extern float __cdecl copysignf (float, float);
  extern long double __cdecl copysignl (long double, long double);


  extern double __cdecl nan(const char *tagp);
  extern float __cdecl nanf(const char *tagp);
  extern long double __cdecl nanl(const char *tagp);
# 788 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern double __cdecl nextafter (double, double);
  extern float __cdecl nextafterf (float, float);
  extern long double __cdecl nextafterl (long double, long double);


  extern double __cdecl nexttoward (double, long double);
  extern float __cdecl nexttowardf (float, long double);
  extern long double __cdecl nexttowardl (long double, long double);



  extern double __cdecl fdim (double x, double y);
  extern float __cdecl fdimf (float x, float y);
  extern long double __cdecl fdiml (long double x, long double y);







  extern double __cdecl fmax (double, double);
  extern float __cdecl fmaxf (float, float);
  extern long double __cdecl fmaxl (long double, long double);


  extern double __cdecl fmin (double, double);
  extern float __cdecl fminf (float, float);
  extern long double __cdecl fminl (long double, long double);



  extern double __cdecl fma (double, double, double);
  extern float __cdecl fmaf (float, float, float);
  extern long double __cdecl fmal (long double, long double, long double);
# 871 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
   __attribute__ ((__dllimport__)) float __cdecl _copysignf (float _Number,float _Sign);
   __attribute__ ((__dllimport__)) float __cdecl _chgsignf (float _X);
   __attribute__ ((__dllimport__)) float __cdecl _logbf(float _X);
   __attribute__ ((__dllimport__)) float __cdecl _nextafterf(float _X,float _Y);
   __attribute__ ((__dllimport__)) int __cdecl _finitef(float _X);
   __attribute__ ((__dllimport__)) int __cdecl _isnanf(float _X);
   __attribute__ ((__dllimport__)) int __cdecl _fpclassf(float _X);



   extern long double __cdecl _chgsignl (long double);
# 898 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
#pragma pack(pop)
# 11 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_FOC.h" 2
# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 1 3








# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 1 3
# 9 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 2 3

# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/include\\limits.h" 1 3 4
# 38 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/include\\limits.h" 3 4
# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\limits.h" 1 3 4





# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 1 3 4
# 6 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\limits.h" 2 3 4
# 38 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/include\\limits.h" 2 3 4
# 10 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 2 3


#pragma pack(push,_CRT_PACKING)
# 36 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
 typedef int (__cdecl *_onexit_t)(void);
# 46 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  typedef struct _div_t {
    int quot;
    int rem;
  } div_t;

  typedef struct _ldiv_t {
    long quot;
    long rem;
  } ldiv_t;





#pragma pack(4)
 typedef struct {
    unsigned char ld[10];
  } _LDOUBLE;
#pragma pack()



 typedef struct {
    double x;
  } _CRT_DOUBLE;

  typedef struct {
    float f;
  } _CRT_FLOAT;




  typedef struct {
    long double x;
  } _LONGDOUBLE;



#pragma pack(4)
 typedef struct {
    unsigned char ld12[12];
  } _LDBL12;
#pragma pack()
# 100 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
 extern int * __imp___mb_cur_max;







  extern int* __imp___mbcur_max;
# 132 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  typedef void (__cdecl *_purecall_handler)(void);

  __attribute__ ((__dllimport__)) _purecall_handler __cdecl _set_purecall_handler(_purecall_handler _Handler);
  __attribute__ ((__dllimport__)) _purecall_handler __cdecl _get_purecall_handler(void);

  typedef void (__cdecl *_invalid_parameter_handler)(const wchar_t *,const wchar_t *,const wchar_t *,unsigned int,uintptr_t);
  _invalid_parameter_handler __cdecl _set_invalid_parameter_handler(_invalid_parameter_handler _Handler);
  _invalid_parameter_handler __cdecl _get_invalid_parameter_handler(void);



  __attribute__ ((__dllimport__)) extern int *__cdecl _errno(void);

  errno_t __cdecl _set_errno(int _Value);
  errno_t __cdecl _get_errno(int *_Value);

  __attribute__ ((__dllimport__)) unsigned long *__cdecl __doserrno(void);

  errno_t __cdecl _set_doserrno(unsigned long _Value);
  errno_t __cdecl _get_doserrno(unsigned long *_Value);




  extern __attribute__ ((__dllimport__)) char *_sys_errlist[1];
  extern __attribute__ ((__dllimport__)) int _sys_nerr;
# 172 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  extern int * __imp___argc;







  extern char *** __imp___argv;







  extern wchar_t *** __imp___wargv;
# 200 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  extern char *** __imp__environ;
# 209 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  extern wchar_t *** __imp__wenviron;
# 218 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  extern char ** __imp__pgmptr;
# 227 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  extern wchar_t ** __imp__wpgmptr;



  errno_t __cdecl _get_pgmptr(char **_Value);
  errno_t __cdecl _get_wpgmptr(wchar_t **_Value);




  extern int * __imp__fmode;



  __attribute__ ((__dllimport__)) errno_t __cdecl _set_fmode(int _Mode);
  __attribute__ ((__dllimport__)) errno_t __cdecl _get_fmode(int *_PMode);





  extern unsigned int * __imp__osplatform;
# 257 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  extern unsigned int * __imp__osver;
# 266 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  extern unsigned int * __imp__winver;
# 275 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  extern unsigned int * __imp__winmajor;
# 284 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  extern unsigned int * __imp__winminor;




  errno_t __cdecl _get_osplatform(unsigned int *_Value);
  errno_t __cdecl _get_osver(unsigned int *_Value);
  errno_t __cdecl _get_winver(unsigned int *_Value);
  errno_t __cdecl _get_winmajor(unsigned int *_Value);
  errno_t __cdecl _get_winminor(unsigned int *_Value);
# 307 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  void __cdecl __attribute__ ((__nothrow__)) exit(int _Code) __attribute__ ((__noreturn__));
  __attribute__ ((__dllimport__)) void __cdecl __attribute__ ((__nothrow__)) _exit(int _Code) __attribute__ ((__noreturn__));



  void __cdecl _Exit(int) __attribute__ ((__noreturn__));
# 321 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  void __cdecl __attribute__((noreturn)) abort(void);




  __attribute__ ((__dllimport__)) unsigned int __cdecl _set_abort_behavior(unsigned int _Flags,unsigned int _Mask);







  __extension__ long long __cdecl _abs64(long long);
  int __cdecl atexit(void (__cdecl *)(void));





  int __cdecl atoi(const char *_Str);
  __attribute__ ((__dllimport__)) int __cdecl _atoi_l(const char *_Str,_locale_t _Locale);
  long __cdecl atol(const char *_Str);
  __attribute__ ((__dllimport__)) long __cdecl _atol_l(const char *_Str,_locale_t _Locale);


  void *__cdecl bsearch(const void *_Key,const void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__cdecl *_PtFuncCompare)(const void *,const void *));
  void __cdecl qsort(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__cdecl *_PtFuncCompare)(const void *,const void *));

  unsigned short __cdecl _byteswap_ushort(unsigned short _Short);

  __extension__ unsigned long long __cdecl _byteswap_uint64(unsigned long long _Int64);
  div_t __cdecl div(int _Numerator,int _Denominator);
  char *__cdecl getenv(const char *_VarName) ;
  __attribute__ ((__dllimport__)) char *__cdecl _itoa(int _Value,char *_Dest,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) char *__cdecl _i64toa(long long _Val,char *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) char *__cdecl _ui64toa(unsigned long long _Val,char *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) long long __cdecl _atoi64(const char *_String);
  __extension__ __attribute__ ((__dllimport__)) long long __cdecl _atoi64_l(const char *_String,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) long long __cdecl _strtoi64(const char *_String,char **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) long long __cdecl _strtoi64_l(const char *_String,char **_EndPtr,int _Radix,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __cdecl _strtoui64(const char *_String,char **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __cdecl _strtoui64_l(const char *_String,char **_EndPtr,int _Radix,_locale_t _Locale);
  ldiv_t __cdecl ldiv(long _Numerator,long _Denominator);
  __attribute__ ((__dllimport__)) char *__cdecl _ltoa(long _Value,char *_Dest,int _Radix) ;
  int __cdecl mblen(const char *_Ch,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __cdecl _mblen_l(const char *_Ch,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) size_t __cdecl _mbstrlen(const char *_Str);
  __attribute__ ((__dllimport__)) size_t __cdecl _mbstrlen_l(const char *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) size_t __cdecl _mbstrnlen(const char *_Str,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __cdecl _mbstrnlen_l(const char *_Str,size_t _MaxCount,_locale_t _Locale);
  int __cdecl mbtowc(wchar_t * __restrict__ _DstCh,const char * __restrict__ _SrcCh,size_t _SrcSizeInBytes);
  __attribute__ ((__dllimport__)) int __cdecl _mbtowc_l(wchar_t * __restrict__ _DstCh,const char * __restrict__ _SrcCh,size_t _SrcSizeInBytes,_locale_t _Locale);
  size_t __cdecl mbstowcs(wchar_t * __restrict__ _Dest,const char * __restrict__ _Source,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __cdecl _mbstowcs_l(wchar_t * __restrict__ _Dest,const char * __restrict__ _Source,size_t _MaxCount,_locale_t _Locale);
  int __cdecl rand(void);
  __attribute__ ((__dllimport__)) int __cdecl _set_error_mode(int _Mode);
  void __cdecl srand(unsigned int _Seed);



  double __cdecl __attribute__ ((__nothrow__)) strtod(const char * __restrict__ _Str,char ** __restrict__ _EndPtr);
  float __cdecl __attribute__ ((__nothrow__)) strtof(const char * __restrict__ nptr, char ** __restrict__ endptr);
  long double __cdecl __attribute__ ((__nothrow__)) strtold(const char * __restrict__ , char ** __restrict__ );


  extern double __cdecl __attribute__ ((__nothrow__))
  __strtod (const char * __restrict__ , char ** __restrict__);
# 400 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  float __cdecl __mingw_strtof (const char * __restrict__, char ** __restrict__);
  long double __cdecl __mingw_strtold(const char * __restrict__, char ** __restrict__);

  __attribute__ ((__dllimport__)) double __cdecl _strtod_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,_locale_t _Locale);
  long __cdecl strtol(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) long __cdecl _strtol_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  unsigned long __cdecl strtoul(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) unsigned long __cdecl _strtoul_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);


  int __cdecl system(const char *_Command);

  __attribute__ ((__dllimport__)) char *__cdecl _ultoa(unsigned long _Value,char *_Dest,int _Radix) ;
  int __cdecl wctomb(char *_MbCh,wchar_t _WCh) ;
  __attribute__ ((__dllimport__)) int __cdecl _wctomb_l(char *_MbCh,wchar_t _WCh,_locale_t _Locale) ;
  size_t __cdecl wcstombs(char * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _MaxCount) ;
  __attribute__ ((__dllimport__)) size_t __cdecl _wcstombs_l(char * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _MaxCount,_locale_t _Locale) ;



  void *__cdecl calloc(size_t _NumOfElements,size_t _SizeOfElements);
  void __cdecl free(void *_Memory);
  void *__cdecl malloc(size_t _Size);
  void *__cdecl realloc(void *_Memory,size_t _NewSize);
  __attribute__ ((__dllimport__)) void *__cdecl _recalloc(void *_Memory,size_t _Count,size_t _Size);






  __attribute__ ((__dllimport__)) void __cdecl _aligned_free(void *_Memory);
  __attribute__ ((__dllimport__)) void *__cdecl _aligned_malloc(size_t _Size,size_t _Alignment);



  __attribute__ ((__dllimport__)) void *__cdecl _aligned_offset_malloc(size_t _Size,size_t _Alignment,size_t _Offset);
  __attribute__ ((__dllimport__)) void *__cdecl _aligned_realloc(void *_Memory,size_t _Size,size_t _Alignment);
  __attribute__ ((__dllimport__)) void *__cdecl _aligned_recalloc(void *_Memory,size_t _Count,size_t _Size,size_t _Alignment);
  __attribute__ ((__dllimport__)) void *__cdecl _aligned_offset_realloc(void *_Memory,size_t _Size,size_t _Alignment,size_t _Offset);
  __attribute__ ((__dllimport__)) void *__cdecl _aligned_offset_recalloc(void *_Memory,size_t _Count,size_t _Size,size_t _Alignment,size_t _Offset);





  __attribute__ ((__dllimport__)) wchar_t *__cdecl _itow(int _Value,wchar_t *_Dest,int _Radix) ;
  __attribute__ ((__dllimport__)) wchar_t *__cdecl _ltow(long _Value,wchar_t *_Dest,int _Radix) ;
  __attribute__ ((__dllimport__)) wchar_t *__cdecl _ultow(unsigned long _Value,wchar_t *_Dest,int _Radix) ;
  double __cdecl wcstod(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr);
  float __cdecl wcstof(const wchar_t * __restrict__ nptr, wchar_t ** __restrict__ endptr);

  float __cdecl wcstof( const wchar_t * __restrict__, wchar_t ** __restrict__);
  long double __cdecl wcstold(const wchar_t * __restrict__, wchar_t ** __restrict__);

  __attribute__ ((__dllimport__)) double __cdecl _wcstod_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,_locale_t _Locale);
  long __cdecl wcstol(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) long __cdecl _wcstol_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  unsigned long __cdecl wcstoul(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) unsigned long __cdecl _wcstoul_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  __attribute__ ((__dllimport__)) wchar_t *__cdecl _wgetenv(const wchar_t *_VarName) ;


  __attribute__ ((__dllimport__)) int __cdecl _wsystem(const wchar_t *_Command);

  __attribute__ ((__dllimport__)) double __cdecl _wtof(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) double __cdecl _wtof_l(const wchar_t *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __cdecl _wtoi(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) int __cdecl _wtoi_l(const wchar_t *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) long __cdecl _wtol(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) long __cdecl _wtol_l(const wchar_t *_Str,_locale_t _Locale);

  __extension__ __attribute__ ((__dllimport__)) wchar_t *__cdecl _i64tow(long long _Val,wchar_t *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) wchar_t *__cdecl _ui64tow(unsigned long long _Val,wchar_t *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) long long __cdecl _wtoi64(const wchar_t *_Str);
  __extension__ __attribute__ ((__dllimport__)) long long __cdecl _wtoi64_l(const wchar_t *_Str,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) long long __cdecl _wcstoi64(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) long long __cdecl _wcstoi64_l(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __cdecl _wcstoui64(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __cdecl _wcstoui64_l(const wchar_t *_Str ,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);




  __attribute__ ((__dllimport__)) char *__cdecl _fullpath(char *_FullPath,const char *_Path,size_t _SizeInBytes);
  __attribute__ ((__dllimport__)) char *__cdecl _ecvt(double _Val,int _NumOfDigits,int *_PtDec,int *_PtSign) ;
  __attribute__ ((__dllimport__)) char *__cdecl _fcvt(double _Val,int _NumOfDec,int *_PtDec,int *_PtSign) ;
  __attribute__ ((__dllimport__)) char *__cdecl _gcvt(double _Val,int _NumOfDigits,char *_DstBuf) ;
  __attribute__ ((__dllimport__)) int __cdecl _atodbl(_CRT_DOUBLE *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __cdecl _atoldbl(_LDOUBLE *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __cdecl _atoflt(_CRT_FLOAT *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __cdecl _atodbl_l(_CRT_DOUBLE *_Result,char *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __cdecl _atoldbl_l(_LDOUBLE *_Result,char *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __cdecl _atoflt_l(_CRT_FLOAT *_Result,char *_Str,_locale_t _Locale);





  __extension__ unsigned long long __cdecl _lrotl(unsigned long long _Val,int _Shift);
  __extension__ unsigned long long __cdecl _lrotr(unsigned long long _Val,int _Shift);







  __attribute__ ((__dllimport__)) void __cdecl _makepath(char *_Path,const char *_Drive,const char *_Dir,const char *_Filename,const char *_Ext);
  _onexit_t __cdecl _onexit(_onexit_t _Func);



  void __cdecl perror(const char *_ErrMsg);

  __attribute__ ((__dllimport__)) int __cdecl _putenv(const char *_EnvString);




  __extension__ unsigned long long __cdecl _rotl64(unsigned long long _Val,int _Shift);
  __extension__ unsigned long long __cdecl _rotr64(unsigned long long Value,int Shift);






  unsigned int __cdecl _rotr(unsigned int _Val,int _Shift);
  unsigned int __cdecl _rotl(unsigned int _Val,int _Shift);


  __extension__ unsigned long long __cdecl _rotr64(unsigned long long _Val,int _Shift);
  __attribute__ ((__dllimport__)) void __cdecl _searchenv(const char *_Filename,const char *_EnvVar,char *_ResultPath) ;
  __attribute__ ((__dllimport__)) void __cdecl _splitpath(const char *_FullPath,char *_Drive,char *_Dir,char *_Filename,char *_Ext) ;
  __attribute__ ((__dllimport__)) void __cdecl _swab(char *_Buf1,char *_Buf2,int _SizeInBytes);



  __attribute__ ((__dllimport__)) wchar_t *__cdecl _wfullpath(wchar_t *_FullPath,const wchar_t *_Path,size_t _SizeInWords);
  __attribute__ ((__dllimport__)) void __cdecl _wmakepath(wchar_t *_ResultPath,const wchar_t *_Drive,const wchar_t *_Dir,const wchar_t *_Filename,const wchar_t *_Ext);


  __attribute__ ((__dllimport__)) void __cdecl _wperror(const wchar_t *_ErrMsg);

  __attribute__ ((__dllimport__)) int __cdecl _wputenv(const wchar_t *_EnvString);
  __attribute__ ((__dllimport__)) void __cdecl _wsearchenv(const wchar_t *_Filename,const wchar_t *_EnvVar,wchar_t *_ResultPath) ;
  __attribute__ ((__dllimport__)) void __cdecl _wsplitpath(const wchar_t *_FullPath,wchar_t *_Drive,wchar_t *_Dir,wchar_t *_Filename,wchar_t *_Ext) ;


  __attribute__ ((__dllimport__)) void __cdecl _beep(unsigned _Frequency,unsigned _Duration) __attribute__ ((__deprecated__));

  __attribute__ ((__dllimport__)) void __cdecl _seterrormode(int _Mode) __attribute__ ((__deprecated__));
  __attribute__ ((__dllimport__)) void __cdecl _sleep(unsigned long _Duration) __attribute__ ((__deprecated__));
# 574 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
  char *__cdecl ecvt(double _Val,int _NumOfDigits,int *_PtDec,int *_PtSign) ;
  char *__cdecl fcvt(double _Val,int _NumOfDec,int *_PtDec,int *_PtSign) ;
  char *__cdecl gcvt(double _Val,int _NumOfDigits,char *_DstBuf) ;
  char *__cdecl itoa(int _Val,char *_DstBuf,int _Radix) ;
  char *__cdecl ltoa(long _Val,char *_DstBuf,int _Radix) ;
  int __cdecl putenv(const char *_EnvString) ;
  void __cdecl swab(char *_Buf1,char *_Buf2,int _SizeInBytes) ;
  char *__cdecl ultoa(unsigned long _Val,char *_Dstbuf,int _Radix) ;
  _onexit_t __cdecl onexit(_onexit_t _Func);





  typedef struct { __extension__ long long quot, rem; } lldiv_t;

  __extension__ lldiv_t __cdecl lldiv(long long, long long);

  __extension__ long long __cdecl llabs(long long);




  __extension__ long long __cdecl strtoll(const char * __restrict__, char ** __restrict, int);
  __extension__ unsigned long long __cdecl strtoull(const char * __restrict__, char ** __restrict__, int);


  __extension__ long long __cdecl atoll (const char *);


  __extension__ long long __cdecl wtoll (const wchar_t *);
  __extension__ char *__cdecl lltoa (long long, char *, int);
  __extension__ char *__cdecl ulltoa (unsigned long long , char *, int);
  __extension__ wchar_t *__cdecl lltow (long long, wchar_t *, int);
  __extension__ wchar_t *__cdecl ulltow (unsigned long long, wchar_t *, int);
# 627 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 3
#pragma pack(pop)


# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\sec_api/stdlib_s.h" 1 3








# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 1 3
# 9 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\sec_api/stdlib_s.h" 2 3
# 629 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 2 3

# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\malloc.h" 1 3








# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 1 3
# 9 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\malloc.h" 2 3


#pragma pack(push,_CRT_PACKING)
# 46 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\malloc.h" 3
 typedef struct _heapinfo {
    int *_pentry;
    size_t _size;
    int _useflag;
  } _HEAPINFO;


  extern unsigned int _amblksiz;
# 99 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\malloc.h" 3
void * __mingw_aligned_malloc (size_t _Size, size_t _Alignment);
void __mingw_aligned_free (void *_Memory);
void * __mingw_aligned_offset_realloc (void *_Memory, size_t _Size, size_t _Alignment, size_t _Offset);
void * __mingw_aligned_realloc (void *_Memory, size_t _Size, size_t _Offset);



  __attribute__ ((__dllimport__)) int __cdecl _resetstkoflw (void);
  __attribute__ ((__dllimport__)) unsigned long __cdecl _set_malloc_crt_max_wait(unsigned long _NewValue);

  __attribute__ ((__dllimport__)) void *__cdecl _expand(void *_Memory,size_t _NewSize);
  __attribute__ ((__dllimport__)) size_t __cdecl _msize(void *_Memory);






  __attribute__ ((__dllimport__)) size_t __cdecl _get_sbh_threshold(void);
  __attribute__ ((__dllimport__)) int __cdecl _set_sbh_threshold(size_t _NewValue);
  __attribute__ ((__dllimport__)) errno_t __cdecl _set_amblksiz(size_t _Value);
  __attribute__ ((__dllimport__)) errno_t __cdecl _get_amblksiz(size_t *_Value);
  __attribute__ ((__dllimport__)) int __cdecl _heapadd(void *_Memory,size_t _Size);
  __attribute__ ((__dllimport__)) int __cdecl _heapchk(void);
  __attribute__ ((__dllimport__)) int __cdecl _heapmin(void);
  __attribute__ ((__dllimport__)) int __cdecl _heapset(unsigned int _Fill);
  __attribute__ ((__dllimport__)) int __cdecl _heapwalk(_HEAPINFO *_EntryInfo);
  __attribute__ ((__dllimport__)) size_t __cdecl _heapused(size_t *_Used,size_t *_Commit);
  __attribute__ ((__dllimport__)) intptr_t __cdecl _get_heap_handle(void);
# 140 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\malloc.h" 3
  static __inline void *_MarkAllocaS(void *_Ptr,unsigned int _Marker) {
    if(_Ptr) {
      *((unsigned int*)_Ptr) = _Marker;
      _Ptr = (char*)_Ptr + 16;
    }
    return _Ptr;
  }
# 159 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\malloc.h" 3
  static __inline void __cdecl _freea(void *_Memory) {
    unsigned int _Marker;
    if(_Memory) {
      _Memory = (char*)_Memory - 16;
      _Marker = *(unsigned int *)_Memory;
      if(_Marker==0xDDDD) {
 free(_Memory);
      }





    }
  }
# 205 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\malloc.h" 3
#pragma pack(pop)
# 630 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdlib.h" 2 3
# 12 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_FOC.h" 2



enum uz_FOC_decoupling_select {
 no_decoupling=0,
 linear_decoupling
 };





typedef struct uz_FOC {
 unsigned int decoupling_select;
 _Bool I_rst;
 _Bool ext_clamping;
 uz_PI_Controller_config config_id;
 uz_PI_Controller_config config_iq;
 struct uz_PMSM_t config_PMSM;
}uz_FOC;
# 43 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_FOC.h"
void uz_FOC_sample(uz_FOC* self, struct uz_dq_t i_reference_Ampere, struct uz_dq_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec, struct uz_dq_t* u_output_Volts);
# 2 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/tb_foc.c" 2
# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 1 3








# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 1 3
# 9 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 2 3


# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw_print_push.h" 1 3
# 11 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 2 3


#pragma pack(push,_CRT_PACKING)
# 26 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 3
 struct _iobuf {
    char *_ptr;
    int _cnt;
    char *_base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char *_tmpfname;
  };
  typedef struct _iobuf FILE;
# 84 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 3
  typedef long _off_t;

  typedef long off_t;






  __extension__ typedef long long _off64_t;

  __extension__ typedef long long off64_t;





  __attribute__ ((__dllimport__)) FILE *__cdecl __iob_func(void);
# 120 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 3
  __extension__ typedef long long fpos_t;
# 157 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 3
  __attribute__ ((__dllimport__)) int __cdecl _filbuf(FILE *_File);
  __attribute__ ((__dllimport__)) int __cdecl _flsbuf(int _Ch,FILE *_File);



  __attribute__ ((__dllimport__)) FILE *__cdecl _fsopen(const char *_Filename,const char *_Mode,int _ShFlag);

  void __cdecl clearerr(FILE *_File);
  int __cdecl fclose(FILE *_File);
  __attribute__ ((__dllimport__)) int __cdecl _fcloseall(void);



  __attribute__ ((__dllimport__)) FILE *__cdecl _fdopen(int _FileHandle,const char *_Mode);

  int __cdecl feof(FILE *_File);
  int __cdecl ferror(FILE *_File);
  int __cdecl fflush(FILE *_File);
  int __cdecl fgetc(FILE *_File);
  __attribute__ ((__dllimport__)) int __cdecl _fgetchar(void);
  int __cdecl fgetpos(FILE * __restrict__ _File ,fpos_t * __restrict__ _Pos);
  char *__cdecl fgets(char * __restrict__ _Buf,int _MaxCount,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) int __cdecl _fileno(FILE *_File);



  __attribute__ ((__dllimport__)) char *__cdecl _tempnam(const char *_DirName,const char *_FilePrefix);
  __attribute__ ((__dllimport__)) int __cdecl _flushall(void);
  FILE *__cdecl fopen(const char * __restrict__ _Filename,const char * __restrict__ _Mode) ;
  FILE *fopen64(const char * __restrict__ filename,const char * __restrict__ mode);
  int __cdecl fprintf(FILE * __restrict__ _File,const char * __restrict__ _Format,...);
  int __cdecl fputc(int _Ch,FILE *_File);
  __attribute__ ((__dllimport__)) int __cdecl _fputchar(int _Ch);
  int __cdecl fputs(const char * __restrict__ _Str,FILE * __restrict__ _File);
  size_t __cdecl fread(void * __restrict__ _DstBuf,size_t _ElementSize,size_t _Count,FILE * __restrict__ _File);
  FILE *__cdecl freopen(const char * __restrict__ _Filename,const char * __restrict__ _Mode,FILE * __restrict__ _File) ;
  int __cdecl fscanf(FILE * __restrict__ _File,const char * __restrict__ _Format,...) ;
  int __cdecl _fscanf_l(FILE * __restrict__ _File,const char * __restrict__ _Format,_locale_t locale,...) ;
  int __cdecl fsetpos(FILE *_File,const fpos_t *_Pos);
  int __cdecl fseek(FILE *_File,long _Offset,int _Origin);
  int fseeko64(FILE* stream, _off64_t offset, int whence);
  long __cdecl ftell(FILE *_File);
  _off64_t ftello64(FILE * stream);
  __extension__ int __cdecl _fseeki64(FILE *_File,long long _Offset,int _Origin);
  __extension__ long long __cdecl _ftelli64(FILE *_File);
  size_t __cdecl fwrite(const void * __restrict__ _Str,size_t _Size,size_t _Count,FILE * __restrict__ _File);
  int __cdecl getc(FILE *_File);
  int __cdecl getchar(void);
  __attribute__ ((__dllimport__)) int __cdecl _getmaxstdio(void);
  char *__cdecl gets(char *_Buffer) ;
  int __cdecl _getw(FILE *_File);




  __attribute__ ((__dllimport__)) int __cdecl _pclose(FILE *_File);
  __attribute__ ((__dllimport__)) FILE *__cdecl _popen(const char *_Command,const char *_Mode);




  int __cdecl printf(const char * __restrict__ _Format,...);
  int __cdecl putc(int _Ch,FILE *_File);
  int __cdecl putchar(int _Ch);
  int __cdecl puts(const char *_Str);
  __attribute__ ((__dllimport__)) int __cdecl _putw(int _Word,FILE *_File);


  int __cdecl remove(const char *_Filename);
  int __cdecl rename(const char *_OldFilename,const char *_NewFilename);
  __attribute__ ((__dllimport__)) int __cdecl _unlink(const char *_Filename);

  int __cdecl unlink(const char *_Filename) ;


  void __cdecl rewind(FILE *_File);
  __attribute__ ((__dllimport__)) int __cdecl _rmtmp(void);
  int __cdecl scanf(const char * __restrict__ _Format,...) ;
  int __cdecl _scanf_l(const char * __restrict__ format,_locale_t locale,... ) ;
  void __cdecl setbuf(FILE * __restrict__ _File,char * __restrict__ _Buffer) ;
  __attribute__ ((__dllimport__)) int __cdecl _setmaxstdio(int _Max);
  __attribute__ ((__dllimport__)) unsigned int __cdecl _set_output_format(unsigned int _Format);
  __attribute__ ((__dllimport__)) unsigned int __cdecl _get_output_format(void);
  unsigned int __cdecl __mingw_set_output_format(unsigned int _Format);
  unsigned int __cdecl __mingw_get_output_format(void);




  int __cdecl setvbuf(FILE * __restrict__ _File,char * __restrict__ _Buf,int _Mode,size_t _Size);
  __attribute__ ((__dllimport__)) int __cdecl _scprintf(const char * __restrict__ _Format,...);
  int __cdecl sscanf(const char * __restrict__ _Src,const char * __restrict__ _Format,...) ;
  int __cdecl _sscanf_l(const char * __restrict__ buffer,const char * __restrict__ format,_locale_t locale,...) ;
  __attribute__ ((__dllimport__)) int __cdecl _snscanf(const char * __restrict__ _Src,size_t _MaxCount,const char * __restrict__ _Format,...) ;
  __attribute__ ((__dllimport__)) int __cdecl _snscanf_l(const char * __restrict__ input,size_t length,const char * __restrict__ format,_locale_t locale,...) ;
  FILE *__cdecl tmpfile(void) ;
  char *__cdecl tmpnam(char *_Buffer);
  int __cdecl ungetc(int _Ch,FILE *_File);
  int __cdecl vfprintf(FILE * __restrict__ _File,const char * __restrict__ _Format,va_list _ArgList);
  int __cdecl vprintf(const char * __restrict__ _Format,va_list _ArgList);


  extern
    __attribute__((__format__ (gnu_printf, 3, 0))) __attribute__ ((__nonnull__ (3)))
    int __cdecl __mingw_vsnprintf(char * __restrict__ _DstBuf,size_t _MaxCount,const char * __restrict__ _Format,
      va_list _ArgList);
  extern
    __attribute__((__format__ (gnu_printf, 3, 4))) __attribute__ ((__nonnull__ (3)))
    int __cdecl __mingw_snprintf(char * __restrict__ s, size_t n, const char * __restrict__ format, ...);
  extern
    __attribute__((__format__ (gnu_printf, 1, 2))) __attribute__ ((__nonnull__ (1)))
    int __cdecl __mingw_printf(const char * __restrict__ , ... ) __attribute__ ((__nothrow__));
  extern
    __attribute__((__format__ (gnu_printf, 1, 0))) __attribute__ ((__nonnull__ (1)))
    int __cdecl __mingw_vprintf (const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
  extern
    __attribute__((__format__ (gnu_printf, 2, 3))) __attribute__ ((__nonnull__ (2)))
    int __cdecl __mingw_fprintf (FILE * __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
  extern
    __attribute__((__format__ (gnu_printf, 2, 0))) __attribute__ ((__nonnull__ (2)))
    int __cdecl __mingw_vfprintf (FILE * __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
  extern
    __attribute__((__format__ (gnu_printf, 2, 3))) __attribute__ ((__nonnull__ (2)))
    int __cdecl __mingw_sprintf (char * __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
  extern
    __attribute__((__format__ (gnu_printf, 2, 0))) __attribute__ ((__nonnull__ (2)))
    int __cdecl __mingw_vsprintf (char * __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));

  __attribute__ ((__dllimport__)) int __cdecl _snprintf(char * __restrict__ _Dest,size_t _Count,const char * __restrict__ _Format,...) ;
  __attribute__ ((__dllimport__)) int __cdecl _snprintf_l(char * __restrict__ buffer,size_t count,const char * __restrict__ format,_locale_t locale,...) ;
  __attribute__ ((__dllimport__)) int __cdecl _vsnprintf(char * __restrict__ _Dest,size_t _Count,const char * __restrict__ _Format,va_list _Args) ;
  __attribute__ ((__dllimport__)) int __cdecl _vsnprintf_l(char * __restrict__ buffer,size_t count,const char * __restrict__ format,_locale_t locale,va_list argptr) ;
  int __cdecl sprintf(char * __restrict__ _Dest,const char * __restrict__ _Format,...) ;
  int __cdecl _sprintf_l(char * __restrict__ buffer,const char * __restrict__ format,_locale_t locale,...) ;
  int __cdecl vsprintf(char * __restrict__ _Dest,const char * __restrict__ _Format,va_list _Args) ;







  int __cdecl vsnprintf(char * __restrict__ _DstBuf,size_t _MaxCount,const char * __restrict__ _Format,va_list _ArgList) ;

  int __cdecl snprintf(char * __restrict__ s, size_t n, const char * __restrict__ format, ...);
# 312 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 3
  int __cdecl vscanf(const char * __restrict__ Format, va_list argp);
  int __cdecl vfscanf (FILE * __restrict__ fp, const char * __restrict__ Format,va_list argp);
  int __cdecl vsscanf (const char * __restrict__ _Str,const char * __restrict__ Format,va_list argp);

  __attribute__ ((__dllimport__)) int __cdecl _vscprintf(const char * __restrict__ _Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _set_printf_count_output(int _Value);
  __attribute__ ((__dllimport__)) int __cdecl _get_printf_count_output(void);
# 330 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 3
  __attribute__ ((__dllimport__)) FILE *__cdecl _wfsopen(const wchar_t *_Filename,const wchar_t *_Mode,int _ShFlag);


  wint_t __cdecl fgetwc(FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __cdecl _fgetwchar(void);
  wint_t __cdecl fputwc(wchar_t _Ch,FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __cdecl _fputwchar(wchar_t _Ch);
  wint_t __cdecl getwc(FILE *_File);
  wint_t __cdecl getwchar(void);
  wint_t __cdecl putwc(wchar_t _Ch,FILE *_File);
  wint_t __cdecl putwchar(wchar_t _Ch);
  wint_t __cdecl ungetwc(wint_t _Ch,FILE *_File);
  wchar_t *__cdecl fgetws(wchar_t * __restrict__ _Dst,int _SizeInWords,FILE * __restrict__ _File);
  int __cdecl fputws(const wchar_t * __restrict__ _Str,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) wchar_t *__cdecl _getws(wchar_t *_String) ;
  __attribute__ ((__dllimport__)) int __cdecl _putws(const wchar_t *_Str);
  int __cdecl fwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);
  int __cdecl wprintf(const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __cdecl _scwprintf(const wchar_t * __restrict__ _Format,...);
  int __cdecl vfwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,va_list _ArgList);
  int __cdecl vwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl swprintf(wchar_t * __restrict__ , const wchar_t * __restrict__ , ...) ;
  __attribute__ ((__dllimport__)) int __cdecl _swprintf_l(wchar_t * __restrict__ buffer,size_t count,const wchar_t * __restrict__ format,_locale_t locale,... ) ;
  __attribute__ ((__dllimport__)) int __cdecl vswprintf(wchar_t * __restrict__ , const wchar_t * __restrict__ ,va_list) ;
  __attribute__ ((__dllimport__)) int __cdecl _swprintf_c(wchar_t * __restrict__ _DstBuf,size_t _SizeInWords,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __cdecl _vswprintf_c(wchar_t * __restrict__ _DstBuf,size_t _SizeInWords,const wchar_t * __restrict__ _Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _snwprintf(wchar_t * __restrict__ _Dest,size_t _Count,const wchar_t * __restrict__ _Format,...) ;
  __attribute__ ((__dllimport__)) int __cdecl _vsnwprintf(wchar_t * __restrict__ _Dest,size_t _Count,const wchar_t * __restrict__ _Format,va_list _Args) ;





  int __cdecl snwprintf (wchar_t * __restrict__ s, size_t n, const wchar_t * __restrict__ format, ...);
  int __cdecl vsnwprintf (wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , va_list);
# 373 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 3
  int __cdecl vwscanf (const wchar_t * __restrict__ , va_list);
  int __cdecl vfwscanf (FILE * __restrict__ ,const wchar_t * __restrict__ ,va_list);
  int __cdecl vswscanf (const wchar_t * __restrict__ ,const wchar_t * __restrict__ ,va_list);

  __attribute__ ((__dllimport__)) int __cdecl _fwprintf_p(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __cdecl _wprintf_p(const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __cdecl _vfwprintf_p(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _vwprintf_p(const wchar_t * __restrict__ _Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _swprintf_p(wchar_t * __restrict__ _DstBuf,size_t _MaxCount,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __cdecl _vswprintf_p(wchar_t * __restrict__ _DstBuf,size_t _MaxCount,const wchar_t * __restrict__ _Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _scwprintf_p(const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __cdecl _vscwprintf_p(const wchar_t * __restrict__ _Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _wprintf_l(const wchar_t * __restrict__ _Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __cdecl _wprintf_p_l(const wchar_t * __restrict__ _Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __cdecl _vwprintf_l(const wchar_t * __restrict__ _Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _vwprintf_p_l(const wchar_t * __restrict__ _Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _fwprintf_l(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __cdecl _fwprintf_p_l(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __cdecl _vfwprintf_l(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _vfwprintf_p_l(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _swprintf_c_l(wchar_t * __restrict__ _DstBuf,size_t _MaxCount,const wchar_t * __restrict__ _Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __cdecl _swprintf_p_l(wchar_t * __restrict__ _DstBuf,size_t _MaxCount,const wchar_t * __restrict__ _Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __cdecl _vswprintf_c_l(wchar_t * __restrict__ _DstBuf,size_t _MaxCount,const wchar_t * __restrict__ _Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _vswprintf_p_l(wchar_t * __restrict__ _DstBuf,size_t _MaxCount,const wchar_t * __restrict__ _Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _scwprintf_l(const wchar_t * __restrict__ _Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __cdecl _scwprintf_p_l(const wchar_t * __restrict__ _Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __cdecl _vscwprintf_p_l(const wchar_t * __restrict__ _Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _snwprintf_l(wchar_t * __restrict__ _DstBuf,size_t _MaxCount,const wchar_t * __restrict__ _Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __cdecl _vsnwprintf_l(wchar_t * __restrict__ _DstBuf,size_t _MaxCount,const wchar_t * __restrict__ _Format,_locale_t _Locale,va_list _ArgList) ;
  __attribute__ ((__dllimport__)) int __cdecl _swprintf(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __cdecl _vswprintf(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Format,va_list _Args);
  __attribute__ ((__dllimport__)) int __cdecl __swprintf_l(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Format,_locale_t _Plocinfo,...) ;
  __attribute__ ((__dllimport__)) int __cdecl _vswprintf_l(wchar_t * __restrict__ buffer,size_t count,const wchar_t * __restrict__ format,_locale_t locale,va_list argptr) ;
  __attribute__ ((__dllimport__)) int __cdecl __vswprintf_l(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Format,_locale_t _Plocinfo,va_list _Args) ;
# 417 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 3
  __attribute__ ((__dllimport__)) wchar_t *__cdecl _wtempnam(const wchar_t *_Directory,const wchar_t *_FilePrefix);
  __attribute__ ((__dllimport__)) int __cdecl _vscwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __cdecl _vscwprintf_l(const wchar_t * __restrict__ _Format,_locale_t _Locale,va_list _ArgList);
  int __cdecl fwscanf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...) ;
  __attribute__ ((__dllimport__)) int __cdecl _fwscanf_l(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,_locale_t _Locale,...) ;
  int __cdecl swscanf(const wchar_t * __restrict__ _Src,const wchar_t * __restrict__ _Format,...) ;
  __attribute__ ((__dllimport__)) int __cdecl _swscanf_l(const wchar_t * __restrict__ _Src,const wchar_t * __restrict__ _Format,_locale_t _Locale,...) ;
  __attribute__ ((__dllimport__)) int __cdecl _snwscanf(const wchar_t * __restrict__ _Src,size_t _MaxCount,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __cdecl _snwscanf_l(const wchar_t * __restrict__ _Src,size_t _MaxCount,const wchar_t * __restrict__ _Format,_locale_t _Locale,...);
  int __cdecl wscanf(const wchar_t * __restrict__ _Format,...) ;
  __attribute__ ((__dllimport__)) int __cdecl _wscanf_l(const wchar_t * __restrict__ _Format,_locale_t _Locale,...) ;
  __attribute__ ((__dllimport__)) FILE *__cdecl _wfdopen(int _FileHandle ,const wchar_t *_Mode);
  __attribute__ ((__dllimport__)) FILE *__cdecl _wfopen(const wchar_t * __restrict__ _Filename,const wchar_t *__restrict__ _Mode) ;
  __attribute__ ((__dllimport__)) FILE *__cdecl _wfreopen(const wchar_t * __restrict__ _Filename,const wchar_t * __restrict__ _Mode,FILE * __restrict__ _OldFile) ;





  __attribute__ ((__dllimport__)) FILE *__cdecl _wpopen(const wchar_t *_Command,const wchar_t *_Mode);




  __attribute__ ((__dllimport__)) int __cdecl _wremove(const wchar_t *_Filename);
  __attribute__ ((__dllimport__)) wchar_t *__cdecl _wtmpnam(wchar_t *_Buffer);
  __attribute__ ((__dllimport__)) wint_t __cdecl _fgetwc_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __cdecl _fputwc_nolock(wchar_t _Ch,FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __cdecl _ungetwc_nolock(wint_t _Ch,FILE *_File);
# 475 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 3
  __attribute__ ((__dllimport__)) void __cdecl _lock_file(FILE *_File);
  __attribute__ ((__dllimport__)) void __cdecl _unlock_file(FILE *_File);
  __attribute__ ((__dllimport__)) int __cdecl _fclose_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) int __cdecl _fflush_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) size_t __cdecl _fread_nolock(void * __restrict__ _DstBuf,size_t _ElementSize,size_t _Count,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) int __cdecl _fseek_nolock(FILE *_File,long _Offset,int _Origin);
  __attribute__ ((__dllimport__)) long __cdecl _ftell_nolock(FILE *_File);
  __extension__ __attribute__ ((__dllimport__)) int __cdecl _fseeki64_nolock(FILE *_File,long long _Offset,int _Origin);
  __extension__ __attribute__ ((__dllimport__)) long long __cdecl _ftelli64_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) size_t __cdecl _fwrite_nolock(const void * __restrict__ _DstBuf,size_t _Size,size_t _Count,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) int __cdecl _ungetc_nolock(int _Ch,FILE *_File);





  char *__cdecl tempnam(const char *_Directory,const char *_FilePrefix) ;
  int __cdecl fcloseall(void) ;
  FILE *__cdecl fdopen(int _FileHandle,const char *_Format) ;
  int __cdecl fgetchar(void) ;
  int __cdecl fileno(FILE *_File) ;
  int __cdecl flushall(void) ;
  int __cdecl fputchar(int _Ch) ;
  int __cdecl getw(FILE *_File) ;
  int __cdecl putw(int _Ch,FILE *_File) ;
  int __cdecl rmtmp(void) ;






#pragma pack(pop)


# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\sec_api/stdio_s.h" 1 3








# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 1 3
# 9 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\sec_api/stdio_s.h" 2 3
# 509 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 2 3


# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw_print_pop.h" 1 3
# 511 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdio.h" 2 3
# 3 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/tb_foc.c" 2


typedef union {
 float fval;
 unsigned int rawbits;
} float_union_t;

_Bool approx_eqf(float x, float y, int ulp_err_lim, float abs_err_lim)
    {
     float_union_t lx, ly;
     lx.fval = x;
     ly.fval = y;
     if (((x == 0.0f) ^ (y == 0.0f)) || (__signbit(x) != __signbit(y)))
     {

   if (x != y) {
    printf("\nWARNING: Comparing floating point value against zero ");
    printf("or values w/ differing signs. ");
    printf("Absolute error limit has been used.\n");
   }

   return fabs(x - y) <= fabs(abs_err_lim);
     }

     return abs((int)lx.rawbits - (int)ly.rawbits) <= ulp_err_lim;
    }

#ifndef HLS_FASTSIM
#ifdef __cplusplus
extern "C"
#endif
void apatb_uz_FOC_sample_sw(struct uz_FOC *, struct uz_dq_t, struct uz_dq_t, float, float, struct uz_dq_t *);
# 30 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/tb_foc.c"
int main()
{
 uz_FOC config = {0};
 struct uz_dq_t i_actual_Ampere = {0};
 struct uz_dq_t i_reference_Ampere = {0};
 struct uz_PMSM_t config_PMSM = {0};

 config.config_id.Kp = 6.75f;
 config.config_id.Ki = 2000.0f;
 config.config_id.samplingTime_sec = 0.00001f;
 config.config_id.upper_limit = 10.0f;
 config.config_id.lower_limit = -10.0f;
 config.config_iq.Kp = 6.75f;
 config.config_iq.Ki = 2000.0f;
 config.config_iq.samplingTime_sec = 0.00001f;
 config.config_iq.upper_limit = 10.0f;
 config.config_iq.lower_limit = -10.0f;
 config.config_PMSM.Ld_Henry = 0.00027f;
 config.config_PMSM.Lq_Henry = 0.00027f;
 config.config_PMSM.Psi_PM_Vs = 0.0082f;
 config.decoupling_select = linear_decoupling;
 config.ext_clamping = 0;
 config.I_rst = 0;
 i_actual_Ampere.d = 0.0f;
 i_actual_Ampere.q = 0.0f;
 i_actual_Ampere.zero = 0.0f;
 i_reference_Ampere.d = 1.0f;
 i_reference_Ampere.q = 1.0f;
 i_reference_Ampere.zero = 0.0f;
 float omega_el_rad_per_sec = 0.0f;
 float V_dc_volts = 24.0f;
    float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.76f, 0.819f, 0.863f, 0.895f, 0.919f, 0.937f};
 float values_id[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.899f, 0.924f, 0.943f};
 float values_omega[11]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f, 0.622f, 1.26f, 2.29f, 3.85f, 6.08f, 9.13f};


 float ud_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.756f, 0.588f, 0.461f};
 float uq_out[11]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f, 1.68f, 1.3f, 1.01f, 0.811f, 0.671f, 0.581f};
 printf("\n HW output\r");
 printf(" D-Parameter Q-Parameter\r");
 struct uz_dq_t out[11];
 for(int i=0;i<11;i++){
  i_actual_Ampere.q = values_iq[i];
  i_actual_Ampere.d = values_id[i];
  omega_el_rad_per_sec = values_omega[i];
  
#ifndef HLS_FASTSIM
#define uz_FOC_sample apatb_uz_FOC_sample_sw
#endif
# 75 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/tb_foc.c"
uz_FOC_sample(&config, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, &out[i]);
#undef uz_FOC_sample
# 75 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/tb_foc.c"

  printf(" %f\t %f\r",out[i].d,out[i].q);
 }



    _Bool test;
    printf("\n Comparison for D parameter \r");
 for(int j=0;j<11;j++){
  test = approx_eqf(ud_out[j], out[j].d, 100, 1);
  if(test){
   printf("Test passed D\r");
  }
  else{
   printf("Test failed D %f\r", ud_out[j]-out[j].d);
  }
 }

    _Bool testt;
    printf("\n Comparison for Q parameter \r");
 for(int k=0;k<11;k++){
  testt = approx_eqf(uq_out[k], out[k].q, 100, 1);
  if(testt){
   printf("Test passed Q\r");
  }
  else{
   printf("Test failed Q %f\r", uq_out[k]-out[k].q);
  }
 }
}
#endif
# 104 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/tb_foc.c"

