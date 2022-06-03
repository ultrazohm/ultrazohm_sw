# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.c"
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.c" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 147 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.c" 2
# 17 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.c"
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.h" 1


# 1 "C:/Xilinx/Vitis/2020.1/win64/tools/clang/bin/../lib/clang/3.1/include\\stdbool.h" 1 3 4
# 4 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.h" 2

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
# 6 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.h" 2
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.h" 1
# 12 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.h"
float uz_signals_dead_zone(float input, float upper_threshold, float lower_threshold);







float uz_signals_get_sign_of_value(float input);
# 30 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.h"
float uz_signals_saturation(float input, float upper_limit, float lower_limit);
# 7 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.h" 2
# 18 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.h"
struct uz_dq_t uz_FOC_SpaceVector_Limitation(struct uz_dq_t u_input_Volts, float V_dc_volts, float omega_el_rad_per_sec, struct uz_dq_t i_actual_Ampere, _Bool* ext_clamping);
# 18 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.c" 2
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
# 19 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_space_vector_limitation.c" 2
static struct uz_dq_t uz_limit_dq_prio_d_axis(struct uz_dq_t u_input_Volts, float U_SV_max);
static struct uz_dq_t uz_limit_dq_prio_q_axis(struct uz_dq_t u_input_Volts, float U_SV_max);
struct uz_dq_t uz_FOC_SpaceVector_Limitation(struct uz_dq_t u_input_Volts, float V_dc_volts, float omega_el_rad_per_sec, struct uz_dq_t i_actual_Ampere, _Bool* ext_clamping){


 struct uz_dq_t u_output_Volts = {0};
   float U_SV_max =V_dc_volts / sqrtf(3.0f);
 float U_SV_abs = sqrtf(powf(u_input_Volts.d, 2.0f) + powf(u_input_Volts.q, 2.0f) );
 _Bool if_omega_equal_q_current = (uz_signals_get_sign_of_value(omega_el_rad_per_sec) == uz_signals_get_sign_of_value(i_actual_Ampere.q));

 if ( U_SV_abs > U_SV_max ){

  *ext_clamping = 1;
  if (if_omega_equal_q_current == 1) {
   u_output_Volts = uz_limit_dq_prio_d_axis(u_input_Volts, U_SV_max);
  } else {
   u_output_Volts = uz_limit_dq_prio_q_axis(u_input_Volts, U_SV_max);
  }
 } else {
  u_output_Volts.d = u_input_Volts.d;
  u_output_Volts.q = u_input_Volts.q;
  *ext_clamping = 0;
 }
 return (u_output_Volts);
}

static struct uz_dq_t uz_limit_dq_prio_d_axis(struct uz_dq_t u_input_Volts, float U_SV_max){
 struct uz_dq_t u_output_Volts = {0};
 if ( (fabsf(u_input_Volts.d) ) > (0.95f * U_SV_max) ) {
  u_output_Volts.d = uz_signals_get_sign_of_value(u_input_Volts.d) * 0.95f * U_SV_max;
  u_output_Volts.q = uz_signals_get_sign_of_value(u_input_Volts.q) * sqrtf(powf(U_SV_max, 2.0f) - powf(u_output_Volts.d, 2.0f));
 } else {
  u_output_Volts.d = u_input_Volts.d;
  u_output_Volts.q = uz_signals_get_sign_of_value(u_input_Volts.q) * sqrtf(powf(U_SV_max, 2.0f) - powf(u_output_Volts.d, 2.0f));
 }
 return(u_output_Volts);
}

static struct uz_dq_t uz_limit_dq_prio_q_axis(struct uz_dq_t u_input_Volts, float U_SV_max){
 struct uz_dq_t u_output_Volts = {0};
 if ( (fabsf(u_input_Volts.q) ) > (0.95f * U_SV_max) ) {
  u_output_Volts.q = uz_signals_get_sign_of_value(u_input_Volts.q) * 0.95f * U_SV_max;
  u_output_Volts.d = uz_signals_get_sign_of_value(u_input_Volts.d) * sqrtf(powf(U_SV_max, 2.0f) - powf(u_output_Volts.q, 2.0f));
 } else {
  u_output_Volts.q = u_input_Volts.q;
  u_output_Volts.d = uz_signals_get_sign_of_value(u_input_Volts.d) * sqrtf(powf(U_SV_max, 2.0f) - powf(u_output_Volts.q, 2.0f));
 }
 return(u_output_Volts);
}
