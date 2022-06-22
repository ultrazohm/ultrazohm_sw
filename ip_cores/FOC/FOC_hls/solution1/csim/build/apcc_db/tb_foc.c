/* Provide Declarations */
#include <stdarg.h>
#include <setjmp.h>
#include <limits.h>
#ifdef NEED_CBEAPINT
#include <autopilot_cbe.h>
#else
#define aesl_fopen fopen
#define aesl_freopen freopen
#define aesl_tmpfile tmpfile
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef __STRICT_ANSI__
#define inline __inline__
#define typeof __typeof__ 
#endif
#define __isoc99_fscanf fscanf
#define __isoc99_sscanf sscanf
#undef ferror
#undef feof
/* get a declaration for alloca */
#if defined(__CYGWIN__) || defined(__MINGW32__)
#define  alloca(x) __builtin_alloca((x))
#define _alloca(x) __builtin_alloca((x))
#elif defined(__APPLE__)
extern void *__builtin_alloca(unsigned long);
#define alloca(x) __builtin_alloca(x)
#define longjmp _longjmp
#define setjmp _setjmp
#elif defined(__sun__)
#if defined(__sparcv9)
extern void *__builtin_alloca(unsigned long);
#else
extern void *__builtin_alloca(unsigned int);
#endif
#define alloca(x) __builtin_alloca(x)
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__arm__)
#define alloca(x) __builtin_alloca(x)
#elif defined(_MSC_VER)
#define inline _inline
#define alloca(x) _alloca(x)
#else
#include <alloca.h>
#endif

#ifndef __GNUC__  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif

#if defined(__GNUC__) && defined(__APPLE_CC__)
#define __EXTERNAL_WEAK__ __attribute__((weak_import))
#elif defined(__GNUC__)
#define __EXTERNAL_WEAK__ __attribute__((weak))
#else
#define __EXTERNAL_WEAK__
#endif

#if defined(__GNUC__) && (defined(__APPLE_CC__) || defined(__CYGWIN__) || defined(__MINGW32__))
#define __ATTRIBUTE_WEAK__
#elif defined(__GNUC__)
#define __ATTRIBUTE_WEAK__ __attribute__((weak))
#else
#define __ATTRIBUTE_WEAK__
#endif

#if defined(__GNUC__)
#define __HIDDEN__ __attribute__((visibility("hidden")))
#endif

#ifdef __GNUC__
#define LLVM_NAN(NanStr)   __builtin_nan(NanStr)   /* Double */
#define LLVM_NANF(NanStr)  __builtin_nanf(NanStr)  /* Float */
#define LLVM_NANS(NanStr)  __builtin_nans(NanStr)  /* Double */
#define LLVM_NANSF(NanStr) __builtin_nansf(NanStr) /* Float */
#define LLVM_INF           __builtin_inf()         /* Double */
#define LLVM_INFF          __builtin_inff()        /* Float */
#define LLVM_PREFETCH(addr,rw,locality) __builtin_prefetch(addr,rw,locality)
#define __ATTRIBUTE_CTOR__ __attribute__((constructor))
#define __ATTRIBUTE_DTOR__ __attribute__((destructor))
#define LLVM_ASM           __asm__
#else
#define LLVM_NAN(NanStr)   ((double)0.0)           /* Double */
#define LLVM_NANF(NanStr)  0.0F                    /* Float */
#define LLVM_NANS(NanStr)  ((double)0.0)           /* Double */
#define LLVM_NANSF(NanStr) 0.0F                    /* Float */
#define LLVM_INF           ((double)0.0)           /* Double */
#define LLVM_INFF          0.0F                    /* Float */
#define LLVM_PREFETCH(addr,rw,locality)            /* PREFETCH */
#define __ATTRIBUTE_CTOR__
#define __ATTRIBUTE_DTOR__
#define LLVM_ASM(X)
#endif

#if __GNUC__ < 4 /* Old GCC's, or compilers not GCC */ 
#define __builtin_stack_save() 0   /* not implemented */
#define __builtin_stack_restore(X) /* noop */
#endif

#if __GNUC__ && __LP64__ /* 128-bit integer types */
typedef int __attribute__((mode(TI))) llvmInt128;
typedef unsigned __attribute__((mode(TI))) llvmUInt128;
#endif

#define CODE_FOR_MAIN() /* Any target-specific code for main()*/

#ifndef __cplusplus
typedef unsigned char bool;
#endif


/* Support for floating point constants */
typedef unsigned long long ConstantDoubleTy;
typedef unsigned int        ConstantFloatTy;
typedef struct { unsigned long long f1; unsigned short f2; unsigned short pad[3]; } ConstantFP80Ty;
typedef struct { unsigned long long f1; unsigned long long f2; } ConstantFP128Ty;


/* Global Declarations */
/* Helper union for bitcasts */
typedef union {
  unsigned int Int32;
  unsigned long long Int64;
  float Float;
  double Double;
} llvmBitCastUnion;
/* Structure forward decls */
typedef struct l_struct_OC_uz_PI_Controller_config l_struct_OC_uz_PI_Controller_config;
typedef struct l_struct_OC_uz_FOC l_struct_OC_uz_FOC;
typedef struct l_struct_OC_uz_PMSM_t l_struct_OC_uz_PMSM_t;
typedef struct l_struct_OC_uz_dq_t l_struct_OC_uz_dq_t;

/* Structure contents */
struct l_struct_OC_uz_PI_Controller_config {
  float field0;
  float field1;
  float field2;
  float field3;
  float field4;
};

struct l_struct_OC_uz_PMSM_t {
  float field0;
  float field1;
  float field2;
  float field3;
  float field4;
  float field5;
  float field6;
};

struct l_struct_OC_uz_FOC {
  unsigned int field0;
  bool field1;
  bool field2;
  l_struct_OC_uz_PMSM_t field3;
};

struct l_struct_OC_uz_dq_t {
  float field0;
  float field1;
  float field2;
};


/* External Global Variable Declarations */
extern l_struct_OC_uz_PI_Controller_config config_id;
extern l_struct_OC_uz_PI_Controller_config config_iq;

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
bool approx_eqf(float llvm_cbe_x, float llvm_cbe_y, signed int llvm_cbe_ulp_err_lim, float llvm_cbe_abs_err_lim);
signed int __signbit(double );
signed int main(void);
void uz_FOC_sample(l_struct_OC_uz_FOC *, l_struct_OC_uz_PI_Controller_config *, l_struct_OC_uz_PI_Controller_config *, l_struct_OC_uz_dq_t , l_struct_OC_uz_dq_t , float , float , float *, float *);


/* Global Variable Definitions and Initialization */
static  char aesl_internal__OC_str[55] = "\nWARNING: Comparing floating point value against zero ";
static  char aesl_internal__OC_str1[31] = "or values w/ differing signs. ";
static float aesl_internal_main_OC_values_iq[11] = { 0x0p0, 0x1.fdf3b6p-3, 0x1.be76c8p-2, 0x1.276c8cp-1, 0x1.5d2f1ap-1, 0x1.851eb8p-1, 0x1.a353f8p-1, 0x1.b9db22p-1, 0x1.ca3d7p-1, 0x1.d6872cp-1, 0x1.dfbe76p-1 };
static float aesl_internal_main_OC_values_id[11] = { 0x0p0, 0x1.fdf3b6p-3, 0x1.be76c8p-2, 0x1.276c8cp-1, 0x1.5d2f1ap-1, 0x1.85a1cap-1, 0x1.a3d70ap-1, 0x1.bae148p-1, 0x1.cc49bap-1, 0x1.d91688p-1, 0x1.e2d0e6p-1 };
static float aesl_internal_main_OC_values_omega[11] = { 0x0p0, 0x0p0, 0x1.23a29cp-6, 0x1.66cf42p-4, 0x1.0e5604p-2, 0x1.3e76c8p-1, 0x1.428f5cp0, 0x1.251eb8p1, 0x1.ecccccp1, 0x1.851eb8p2, 0x1.2428f6p3 };
static  char aesl_internal__OC_str6[31] = "\n Comparison for D parameter \r";
static float aesl_internal_main_OC_ud_out[11] = { 0x1.bp2, 0x1.45b646p2, 0x1.ebc73ep1, 0x1.736588p1, 0x1.19c148p1, 0x1.ac9b2p0, 0x1.47d6c8p0, 0x1.f5deep-1, 0x1.818bd6p-1, 0x1.2be25p-1, 0x1.d52d24p-2 };
static float aesl_internal_main_OC_uq_out[11] = { 0x1.bp2, 0x1.45b646p2, 0x1.ebcc2ap1, 0x1.737dfap1, 0x1.1a0b7p1, 0x1.afb48p0, 0x1.4c5c24p0, 0x1.037b7cp0, 0x1.a087a8p-1, 0x1.58525p-1, 0x1.28296cp-1 };
static  char aesl_internal__OC_str3[13] = "\n HW output\r";
static  char aesl_internal__OC_str4[26] = " D-Parameter Q-Parameter\r";
static  char aesl_internal__OC_str5[9] = " %f\t %f\r";
static  char aesl_internal__OC_str7[15] = "Test passed D\r";
static  char aesl_internal__OC_str8[18] = "Test failed D %f\r";
static  char aesl_internal__OC_str9[31] = "\n Comparison for Q parameter \r";
static  char aesl_internal__OC_str11[18] = "Test failed Q %f\r";
static  char aesl_internal_str[36] = "Absolute error limit has been used.";
l_struct_OC_uz_PI_Controller_config config_iq __ATTRIBUTE_WEAK__;
static  char aesl_internal__OC_str10[15] = "Test passed Q\r";
l_struct_OC_uz_PI_Controller_config config_id __ATTRIBUTE_WEAK__;


/* Function Bodies */
static inline int llvm_fcmp_ord(double X, double Y) { return X == X && Y == Y; }
static inline int llvm_fcmp_uno(double X, double Y) { return X != X || Y != Y; }
static inline int llvm_fcmp_ueq(double X, double Y) { return X == Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_une(double X, double Y) { return X != Y; }
static inline int llvm_fcmp_ult(double X, double Y) { return X <  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ugt(double X, double Y) { return X >  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ule(double X, double Y) { return X <= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_uge(double X, double Y) { return X >= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_oeq(double X, double Y) { return X == Y ; }
static inline int llvm_fcmp_one(double X, double Y) { return X != Y && llvm_fcmp_ord(X, Y); }
static inline int llvm_fcmp_olt(double X, double Y) { return X <  Y ; }
static inline int llvm_fcmp_ogt(double X, double Y) { return X >  Y ; }
static inline int llvm_fcmp_ole(double X, double Y) { return X <= Y ; }
static inline int llvm_fcmp_oge(double X, double Y) { return X >= Y ; }

bool approx_eqf(float llvm_cbe_x, float llvm_cbe_y, signed int llvm_cbe_ulp_err_lim, float llvm_cbe_abs_err_lim) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  bool llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  double llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  unsigned int llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  double llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  unsigned int llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  unsigned int llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  unsigned int llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_puts_count = 0;
  unsigned int llvm_cbe_puts;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  float llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  double llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  double llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  double llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  double llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  unsigned int llvm_cbe_tmp__13;
  llvmBitCastUnion llvm_cbe_tmp__13__BITCAST_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  unsigned int llvm_cbe_tmp__14;
  llvmBitCastUnion llvm_cbe_tmp__14__BITCAST_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  unsigned int llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_ispos_count = 0;
  static  unsigned long long aesl_llvm_cbe_neg_count = 0;
  unsigned int llvm_cbe_neg;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  unsigned int llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge_count = 0;
  bool llvm_cbe_storemerge;
  bool llvm_cbe_storemerge__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @approx_eqf\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = xor i1 %%1, %%2, !dbg !5 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_19_count);
  llvm_cbe_tmp__1 = (bool )(((llvm_fcmp_oeq(llvm_cbe_x, 0x0p0)) ^ (llvm_fcmp_oeq(llvm_cbe_y, 0x0p0)))&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__1);
  if (llvm_cbe_tmp__1) {
    goto llvm_cbe_tmp__17;
  } else {
    goto llvm_cbe_tmp__18;
  }

llvm_cbe_tmp__18:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = fpext float %%x to double, !dbg !6 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_21_count);
  llvm_cbe_tmp__2 = (double )((double )llvm_cbe_x);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__2, *(long long*)(&llvm_cbe_tmp__2));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = tail call i32 @__signbit(double %%5) nounwind, !dbg !6 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_22_count);
  llvm_cbe_tmp__3 = (unsigned int ) /*tail*/ __signbit(llvm_cbe_tmp__2);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__2, *(long long*)(&llvm_cbe_tmp__2));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__3);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = fpext float %%y to double, !dbg !6 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_23_count);
  llvm_cbe_tmp__4 = (double )((double )llvm_cbe_y);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__4, *(long long*)(&llvm_cbe_tmp__4));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = tail call i32 @__signbit(double %%7) nounwind, !dbg !6 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_24_count);
  llvm_cbe_tmp__5 = (unsigned int ) /*tail*/ __signbit(llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__4, *(long long*)(&llvm_cbe_tmp__4));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__5);
}
  if (((llvm_cbe_tmp__3&4294967295U) == (llvm_cbe_tmp__5&4294967295U))) {
    goto llvm_cbe_tmp__19;
  } else {
    goto llvm_cbe_tmp__17;
  }

llvm_cbe_tmp__17:
  if ((llvm_fcmp_une(llvm_cbe_x, llvm_cbe_y))) {
    goto llvm_cbe_tmp__20;
  } else {
    goto llvm_cbe_tmp__21;
  }

llvm_cbe_tmp__20:
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([55 x i8]* @aesl_internal_.str, i64 0, i64 0)) nounwind, !dbg !7 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_29_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 55
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__6);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([31 x i8]* @aesl_internal_.str1, i64 0, i64 0)) nounwind, !dbg !7 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_30_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str1[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 31
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__7);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%puts = tail call i32 @puts(i8* getelementptr inbounds ([36 x i8]* @aesl_internal_str, i64 0, i64 0)), !dbg !7 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_puts_count);
   /*tail*/ puts(( char *)((&aesl_internal_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 36
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn puts = 0x%X",llvm_cbe_puts);
}
  goto llvm_cbe_tmp__21;

llvm_cbe_tmp__21:
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = fsub float %%x, %%y, !dbg !6 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_32_count);
  llvm_cbe_tmp__8 = (float )((float )(llvm_cbe_x - llvm_cbe_y));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__8, *(int*)(&llvm_cbe_tmp__8));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = fpext float %%16 to double, !dbg !6 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_33_count);
  llvm_cbe_tmp__9 = (double )((double )llvm_cbe_tmp__8);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__9, *(long long*)(&llvm_cbe_tmp__9));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = tail call double @fabs(double %%17) nounwind, !dbg !6 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__10 = (double ) /*tail*/ fabs(llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__9, *(long long*)(&llvm_cbe_tmp__9));
printf("\nReturn  = %lf",llvm_cbe_tmp__10);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = fpext float %%abs_err_lim to double, !dbg !7 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__11 = (double )((double )llvm_cbe_abs_err_lim);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = tail call double @fabs(double %%19) nounwind, !dbg !7 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__12 = (double ) /*tail*/ fabs(llvm_cbe_tmp__11);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
printf("\nReturn  = %lf",llvm_cbe_tmp__12);
}
  llvm_cbe_storemerge__PHI_TEMPORARY = (bool )(llvm_fcmp_ole(llvm_cbe_tmp__10, llvm_cbe_tmp__12));   /* for PHI node */
  goto llvm_cbe_tmp__22;

llvm_cbe_tmp__19:
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = bitcast float %%x to i32, !dbg !7 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_39_count);
  llvm_cbe_tmp__13 = (unsigned int )(llvm_cbe_tmp__13__BITCAST_TEMPORARY.Float = llvm_cbe_x, llvm_cbe_tmp__13__BITCAST_TEMPORARY.Int32);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = bitcast float %%y to i32, !dbg !7 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_40_count);
  llvm_cbe_tmp__14 = (unsigned int )(llvm_cbe_tmp__14__BITCAST_TEMPORARY.Float = llvm_cbe_y, llvm_cbe_tmp__14__BITCAST_TEMPORARY.Int32);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__14);
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = sub nsw i32 %%23, %%24, !dbg !7 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_41_count);
  llvm_cbe_tmp__15 = (unsigned int )((unsigned int )(llvm_cbe_tmp__13&4294967295ull)) - ((unsigned int )(llvm_cbe_tmp__14&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__15&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%neg = sub i32 0, %%25, !dbg !7 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_neg_count);
  llvm_cbe_neg = (unsigned int )-(llvm_cbe_tmp__15);
if (AESL_DEBUG_TRACE)
printf("\nneg = 0x%X\n", ((unsigned int )(llvm_cbe_neg&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = select i1 %%ispos, i32 %%25, i32 %%neg, !dbg !7 for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_42_count);
  llvm_cbe_tmp__16 = (unsigned int )(((((signed int )llvm_cbe_tmp__15) > ((signed int )4294967295u))) ? ((unsigned int )llvm_cbe_tmp__15) : ((unsigned int )llvm_cbe_neg));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__16);
  llvm_cbe_storemerge__PHI_TEMPORARY = (bool )(((signed int )llvm_cbe_tmp__16) <= ((signed int )llvm_cbe_ulp_err_lim));   /* for PHI node */
  goto llvm_cbe_tmp__22;

llvm_cbe_tmp__22:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge = phi i1 [ %%21, %%15 ], [ %%27, %%22  for 0x%I64xth hint within @approx_eqf  --> \n", ++aesl_llvm_cbe_storemerge_count);
  llvm_cbe_storemerge = (bool )((llvm_cbe_storemerge__PHI_TEMPORARY)&1);
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge = 0x%X",llvm_cbe_storemerge);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @approx_eqf}\n");
  return llvm_cbe_storemerge;
}


signed int main(void) {
  static  unsigned long long aesl_llvm_cbe_config_count = 0;
  l_struct_OC_uz_FOC llvm_cbe_config;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_i_actual_Ampere_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_i_reference_Ampere_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_i_reference_Ampere;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_config_id_count = 0;
  l_struct_OC_uz_PI_Controller_config llvm_cbe_config_id;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_config_iq_count = 0;
  l_struct_OC_uz_PI_Controller_config llvm_cbe_config_iq;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_out_d_count = 0;
  float llvm_cbe_out_d[11];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_out_q_count = 0;
  float llvm_cbe_out_q[11];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  signed int *llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  bool *llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  bool *llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  float *llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  float *llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  float *llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  float *llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  float *llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
   char *llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
   char *llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  float *llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  float *llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  float *llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  float *llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  float *llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  float *llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  float *llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  float *llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  float *llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  float *llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  float *llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
   char *llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
   char *llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  float *llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  float *llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  float *llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  float *llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
   char *llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
   char *llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  unsigned int llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  unsigned int llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge5_count = 0;
  unsigned int llvm_cbe_storemerge5;
  unsigned int llvm_cbe_storemerge5__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  unsigned long long llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  float *llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  float llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  float *llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  float llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  float *llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  float llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  float *llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  float *llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  float llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  double llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  float llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  double llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  unsigned int llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  unsigned int llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond7_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  unsigned int llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge14_count = 0;
  unsigned int llvm_cbe_storemerge14;
  unsigned int llvm_cbe_storemerge14__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  unsigned long long llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  float *llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  float llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  float *llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  float llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  bool llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  unsigned int llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  float llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  float llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  double llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  unsigned int llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  unsigned int llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond6_count = 0;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  unsigned int llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge23_count = 0;
  unsigned int llvm_cbe_storemerge23;
  unsigned int llvm_cbe_storemerge23__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  unsigned long long llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  float *llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  float llvm_cbe_tmp__85;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  float *llvm_cbe_tmp__86;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  float llvm_cbe_tmp__87;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  bool llvm_cbe_tmp__88;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  unsigned int llvm_cbe_tmp__89;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  float llvm_cbe_tmp__90;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  float llvm_cbe_tmp__91;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  double llvm_cbe_tmp__92;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  unsigned int llvm_cbe_tmp__93;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  unsigned int llvm_cbe_tmp__94;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;

  CODE_FOR_MAIN();
const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @main\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.uz_FOC* %%config, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__23 = (signed int *)(&llvm_cbe_config.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds %%struct.uz_FOC* %%config, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_48_count);
  llvm_cbe_tmp__24 = (bool *)(&llvm_cbe_config.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.uz_FOC* %%config, i64 0, i32 2, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_49_count);
  llvm_cbe_tmp__25 = (bool *)(&llvm_cbe_config.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds %%struct.uz_FOC* %%config, i64 0, i32 3, i32 0, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_50_count);
  llvm_cbe_tmp__26 = (float *)(&llvm_cbe_config.field3.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds %%struct.uz_FOC* %%config, i64 0, i32 3, i32 1, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_51_count);
  llvm_cbe_tmp__27 = (float *)(&llvm_cbe_config.field3.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.uz_FOC* %%config, i64 0, i32 3, i32 2, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_52_count);
  llvm_cbe_tmp__28 = (float *)(&llvm_cbe_config.field3.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds %%struct.uz_FOC* %%config, i64 0, i32 3, i32 3, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_53_count);
  llvm_cbe_tmp__29 = (float *)(&llvm_cbe_config.field3.field3);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32 0, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_55_count);
  llvm_cbe_tmp__30 = (float *)(&llvm_cbe_i_actual_Ampere.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = bitcast float* %%4 to i8*, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_56_count);
  llvm_cbe_tmp__31 = ( char *)(( char *)llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = call i8* @memset(i8* %%9, i32 0, i64 28 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_57_count);
  ( char *)memset(( char *)llvm_cbe_tmp__31, 0u, 28ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",28ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__32);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32 1, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_58_count);
  llvm_cbe_tmp__33 = (float *)(&llvm_cbe_i_actual_Ampere.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = getelementptr inbounds %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32 2, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_59_count);
  llvm_cbe_tmp__34 = (float *)(&llvm_cbe_i_actual_Ampere.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds %%struct.uz_dq_t* %%i_reference_Ampere, i64 0, i32 0, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_61_count);
  llvm_cbe_tmp__35 = (float *)(&llvm_cbe_i_reference_Ampere.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds %%struct.uz_dq_t* %%i_reference_Ampere, i64 0, i32 1, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_62_count);
  llvm_cbe_tmp__36 = (float *)(&llvm_cbe_i_reference_Ampere.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds %%struct.uz_dq_t* %%i_reference_Ampere, i64 0, i32 2, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_63_count);
  llvm_cbe_tmp__37 = (float *)(&llvm_cbe_i_reference_Ampere.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%config_id, i64 0, i32 0, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_66_count);
  llvm_cbe_tmp__38 = (float *)(&llvm_cbe_config_id.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%config_id, i64 0, i32 1, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_67_count);
  llvm_cbe_tmp__39 = (float *)(&llvm_cbe_config_id.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%config_id, i64 0, i32 2, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_68_count);
  llvm_cbe_tmp__40 = (float *)(&llvm_cbe_config_id.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%config_id, i64 0, i32 3, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_69_count);
  llvm_cbe_tmp__41 = (float *)(&llvm_cbe_config_id.field3);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%config_id, i64 0, i32 4, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_70_count);
  llvm_cbe_tmp__42 = (float *)(&llvm_cbe_config_id.field4);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%config_iq, i64 0, i32 0, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_72_count);
  llvm_cbe_tmp__43 = (float *)(&llvm_cbe_config_iq.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = bitcast %%struct.uz_PI_Controller_config* %%config_id to i8*, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_73_count);
  llvm_cbe_tmp__44 = ( char *)(( char *)(&llvm_cbe_config_id));
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = call i8* @memset(i8* %%22, i32 0, i64 16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_74_count);
  ( char *)memset(( char *)llvm_cbe_tmp__44, 0u, 16ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",16ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__45);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%config_iq, i64 0, i32 1, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__46 = (float *)(&llvm_cbe_config_iq.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%config_iq, i64 0, i32 2, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_76_count);
  llvm_cbe_tmp__47 = (float *)(&llvm_cbe_config_iq.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%config_iq, i64 0, i32 3, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_77_count);
  llvm_cbe_tmp__48 = (float *)(&llvm_cbe_config_iq.field3);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%config_iq, i64 0, i32 4, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_78_count);
  llvm_cbe_tmp__49 = (float *)(&llvm_cbe_config_iq.field4);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = bitcast %%struct.uz_PI_Controller_config* %%config_iq to i8*, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_79_count);
  llvm_cbe_tmp__50 = ( char *)(( char *)(&llvm_cbe_config_iq));
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = call i8* @memset(i8* %%28, i32 0, i64 16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_80_count);
  ( char *)memset(( char *)llvm_cbe_tmp__50, 0u, 16ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",16ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__51);
}
if (AESL_DEBUG_TRACE)
printf("\n  store float 6.750000e+00, float* %%16, align 4, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_81_count);
  *llvm_cbe_tmp__38 = 0x1.bp2;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1.bp2);
if (AESL_DEBUG_TRACE)
printf("\n  store float 2.000000e+03, float* %%17, align 4, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_82_count);
  *llvm_cbe_tmp__39 = 0x1.f4p10;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1.f4p10);
if (AESL_DEBUG_TRACE)
printf("\n  store float 0x3EE4F8B580000000, float* %%18, align 4, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_83_count);
  *llvm_cbe_tmp__40 = 0x1.4f8b58p-17;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1.4f8b58p-17);
if (AESL_DEBUG_TRACE)
printf("\n  store float 1.000000e+01, float* %%19, align 4, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_84_count);
  *llvm_cbe_tmp__41 = 0x1.4p3;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1.4p3);
if (AESL_DEBUG_TRACE)
printf("\n  store float -1.000000e+01, float* %%20, align 4, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_85_count);
  *llvm_cbe_tmp__42 = -0x1.4p3;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", -0x1.4p3);
if (AESL_DEBUG_TRACE)
printf("\n  store float 6.750000e+00, float* %%21, align 4, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_86_count);
  *llvm_cbe_tmp__43 = 0x1.bp2;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1.bp2);
if (AESL_DEBUG_TRACE)
printf("\n  store float 2.000000e+03, float* %%24, align 4, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_87_count);
  *llvm_cbe_tmp__46 = 0x1.f4p10;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1.f4p10);
if (AESL_DEBUG_TRACE)
printf("\n  store float 0x3EE4F8B580000000, float* %%25, align 4, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_88_count);
  *llvm_cbe_tmp__47 = 0x1.4f8b58p-17;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1.4f8b58p-17);
if (AESL_DEBUG_TRACE)
printf("\n  store float 1.000000e+01, float* %%26, align 4, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_89_count);
  *llvm_cbe_tmp__48 = 0x1.4p3;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1.4p3);
if (AESL_DEBUG_TRACE)
printf("\n  store float -1.000000e+01, float* %%27, align 4, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_90_count);
  *llvm_cbe_tmp__49 = -0x1.4p3;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", -0x1.4p3);
if (AESL_DEBUG_TRACE)
printf("\n  store float 0x3F31B1D920000000, float* %%5, align 4, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_91_count);
  *llvm_cbe_tmp__27 = 0x1.1b1d92p-12;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1.1b1d92p-12);
if (AESL_DEBUG_TRACE)
printf("\n  store float 0x3F31B1D920000000, float* %%6, align 4, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_92_count);
  *llvm_cbe_tmp__28 = 0x1.1b1d92p-12;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1.1b1d92p-12);
if (AESL_DEBUG_TRACE)
printf("\n  store float 0x3F80CB2960000000, float* %%7, align 4, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_93_count);
  *llvm_cbe_tmp__29 = 0x1.0cb296p-7;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1.0cb296p-7);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 1, i32* %%1, align 4, !dbg !11 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_94_count);
  *llvm_cbe_tmp__23 = 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1u);
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%3, align 1, !dbg !11 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_95_count);
  *llvm_cbe_tmp__25 = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%2, align 4, !dbg !11 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_96_count);
  *llvm_cbe_tmp__24 = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* %%8, align 4, !dbg !11 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_97_count);
  *llvm_cbe_tmp__30 = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* %%11, align 4, !dbg !11 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_98_count);
  *llvm_cbe_tmp__33 = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* %%12, align 4, !dbg !11 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_99_count);
  *llvm_cbe_tmp__34 = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
if (AESL_DEBUG_TRACE)
printf("\n  store float 1.000000e+00, float* %%13, align 4, !dbg !11 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_100_count);
  *llvm_cbe_tmp__35 = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  store float 1.000000e+00, float* %%14, align 4, !dbg !11 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_101_count);
  *llvm_cbe_tmp__36 = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* %%15, align 4, !dbg !11 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_102_count);
  *llvm_cbe_tmp__37 = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([13 x i8]* @aesl_internal_.str3, i64 0, i64 0)) nounwind, !dbg !14 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_111_count);
  printf(( char *)((&aesl_internal__OC_str3[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 13
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__52);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([26 x i8]* @aesl_internal_.str4, i64 0, i64 0)) nounwind, !dbg !14 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_112_count);
  printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 26
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__53);
}
  llvm_cbe_storemerge5__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__95;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__95:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge5 = phi i32 [ 0, %%0 ], [ %%47, %%32  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_storemerge5_count);
  llvm_cbe_storemerge5 = (unsigned int )llvm_cbe_storemerge5__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge5 = 0x%X",llvm_cbe_storemerge5);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__68);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = sext i32 %%storemerge5 to i64, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_126_count);
  llvm_cbe_tmp__54 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge5);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = getelementptr inbounds [11 x float]* @aesl_internal_main.values_iq, i64 0, i64 %%33, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_127_count);
  llvm_cbe_tmp__55 = (float *)(&aesl_internal_main_OC_values_iq[(((signed long long )llvm_cbe_tmp__54))
#ifdef AESL_BC_SIM
 % 11
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__54));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__54) < 11)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_main.values_iq' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = load float* %%34, align 4, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__56 = (float )*llvm_cbe_tmp__55;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__56, *(int*)(&llvm_cbe_tmp__56));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%35, float* %%11, align 4, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_129_count);
  *llvm_cbe_tmp__33 = llvm_cbe_tmp__56;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__56);
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = getelementptr inbounds [11 x float]* @aesl_internal_main.values_id, i64 0, i64 %%33, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_130_count);
  llvm_cbe_tmp__57 = (float *)(&aesl_internal_main_OC_values_id[(((signed long long )llvm_cbe_tmp__54))
#ifdef AESL_BC_SIM
 % 11
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__54));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__54) < 11)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_main.values_id' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = load float* %%36, align 4, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__58 = (float )*llvm_cbe_tmp__57;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__58, *(int*)(&llvm_cbe_tmp__58));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%37, float* %%8, align 4, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_132_count);
  *llvm_cbe_tmp__30 = llvm_cbe_tmp__58;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__58);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = getelementptr inbounds [11 x float]* @aesl_internal_main.values_omega, i64 0, i64 %%33, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__59 = (float *)(&aesl_internal_main_OC_values_omega[(((signed long long )llvm_cbe_tmp__54))
#ifdef AESL_BC_SIM
 % 11
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__54));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__54) < 11)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_main.values_omega' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = load float* %%38, align 4, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__60 = (float )*llvm_cbe_tmp__59;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__60, *(int*)(&llvm_cbe_tmp__60));
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = getelementptr inbounds [11 x float]* %%out_d, i64 0, i64 %%33, !dbg !12 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_137_count);
  llvm_cbe_tmp__61 = (float *)(&llvm_cbe_out_d[(((signed long long )llvm_cbe_tmp__54))
#ifdef AESL_BC_SIM
 % 11
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__54));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = getelementptr inbounds [11 x float]* %%out_q, i64 0, i64 %%33, !dbg !12 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_138_count);
  llvm_cbe_tmp__62 = (float *)(&llvm_cbe_out_q[(((signed long long )llvm_cbe_tmp__54))
#ifdef AESL_BC_SIM
 % 11
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__54));
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @uz_FOC_sample(%%struct.uz_FOC* %%config, %%struct.uz_PI_Controller_config* %%config_id, %%struct.uz_PI_Controller_config* %%config_iq, %%struct.uz_dq_t* byval %%i_reference_Ampere, %%struct.uz_dq_t* byval %%i_actual_Ampere, float 2.400000e+01, float %%39, float* %%40, float* %%41) nounwind, !dbg !12 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_139_count);
  uz_FOC_sample((l_struct_OC_uz_FOC *)(&llvm_cbe_config), (l_struct_OC_uz_PI_Controller_config *)(&llvm_cbe_config_id), (l_struct_OC_uz_PI_Controller_config *)(&llvm_cbe_config_iq), llvm_cbe_i_reference_Ampere, llvm_cbe_i_actual_Ampere, 0x1.8p4, llvm_cbe_tmp__60, (float *)llvm_cbe_tmp__61, (float *)llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f",0x1.8p4);
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__60, *(int*)(&llvm_cbe_tmp__60));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__54) < 11)) fprintf(stderr, "%s:%d: warning: Read access out of array 'out_d' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = load float* %%40, align 4, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_140_count);
  llvm_cbe_tmp__63 = (float )*llvm_cbe_tmp__61;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__63, *(int*)(&llvm_cbe_tmp__63));
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = fpext float %%42 to double, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_141_count);
  llvm_cbe_tmp__64 = (double )((double )llvm_cbe_tmp__63);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__64, *(long long*)(&llvm_cbe_tmp__64));

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__54) < 11)) fprintf(stderr, "%s:%d: warning: Read access out of array 'out_q' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = load float* %%41, align 4, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_142_count);
  llvm_cbe_tmp__65 = (float )*llvm_cbe_tmp__62;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__65, *(int*)(&llvm_cbe_tmp__65));
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = fpext float %%44 to double, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_143_count);
  llvm_cbe_tmp__66 = (double )((double )llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__66, *(long long*)(&llvm_cbe_tmp__66));
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([9 x i8]* @aesl_internal_.str5, i64 0, i64 0), double %%43, double %%45) nounwind, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_144_count);
  printf(( char *)((&aesl_internal__OC_str5[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 9
#endif
])), llvm_cbe_tmp__64, llvm_cbe_tmp__66);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__64, *(long long*)(&llvm_cbe_tmp__64));
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__66, *(long long*)(&llvm_cbe_tmp__66));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__67);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = add nsw i32 %%storemerge5, 1, !dbg !15 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_145_count);
  llvm_cbe_tmp__68 = (unsigned int )((unsigned int )(llvm_cbe_storemerge5&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__68&4294967295ull)));
  if (((llvm_cbe_tmp__68&4294967295U) == (11u&4294967295U))) {
    goto llvm_cbe_tmp__96;
  } else {
    llvm_cbe_storemerge5__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__68;   /* for PHI node */
    goto llvm_cbe_tmp__95;
  }

  } while (1); /* end of syntactic loop '' */
llvm_cbe_tmp__96:
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([31 x i8]* @aesl_internal_.str6, i64 0, i64 0)) nounwind, !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_157_count);
  printf(( char *)((&aesl_internal__OC_str6[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 31
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__69);
}
  llvm_cbe_storemerge14__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__97;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__97:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge14 = phi i32 [ 0, %%48 ], [ %%65, %%64  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_storemerge14_count);
  llvm_cbe_storemerge14 = (unsigned int )llvm_cbe_storemerge14__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__81);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = sext i32 %%storemerge14 to i64, !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_166_count);
  llvm_cbe_tmp__70 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge14);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__70);
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = getelementptr inbounds [11 x float]* @aesl_internal_main.ud_out, i64 0, i64 %%51, !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_167_count);
  llvm_cbe_tmp__71 = (float *)(&aesl_internal_main_OC_ud_out[(((signed long long )llvm_cbe_tmp__70))
#ifdef AESL_BC_SIM
 % 11
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__70));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__70) < 11)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_main.ud_out' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = load float* %%52, align 4, !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_168_count);
  llvm_cbe_tmp__72 = (float )*llvm_cbe_tmp__71;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__72, *(int*)(&llvm_cbe_tmp__72));
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = getelementptr inbounds [11 x float]* %%out_d, i64 0, i64 %%51, !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_169_count);
  llvm_cbe_tmp__73 = (float *)(&llvm_cbe_out_d[(((signed long long )llvm_cbe_tmp__70))
#ifdef AESL_BC_SIM
 % 11
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__70));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__70) < 11)) fprintf(stderr, "%s:%d: warning: Read access out of array 'out_d' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = load float* %%54, align 4, !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_170_count);
  llvm_cbe_tmp__74 = (float )*llvm_cbe_tmp__73;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__74, *(int*)(&llvm_cbe_tmp__74));
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = call zeroext i1 @approx_eqf(float %%53, float %%55, i32 10000, float 1.000000e+03), !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_171_count);
  llvm_cbe_tmp__75 = (bool )((approx_eqf(llvm_cbe_tmp__72, llvm_cbe_tmp__74, 10000u, 0x1.f4p9))&1);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__72, *(int*)(&llvm_cbe_tmp__72));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__74, *(int*)(&llvm_cbe_tmp__74));
printf("\nArgument  = 0x%X",10000u);
printf("\nArgument  = %f",0x1.f4p9);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__75);
}
  if (llvm_cbe_tmp__75) {
    goto llvm_cbe_tmp__98;
  } else {
    goto llvm_cbe_tmp__99;
  }

llvm_cbe_tmp__100:
if (AESL_DEBUG_TRACE)
printf("\n  %%65 = add nsw i32 %%storemerge14, 1, !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_182_count);
  llvm_cbe_tmp__81 = (unsigned int )((unsigned int )(llvm_cbe_storemerge14&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__81&4294967295ull)));
  if (((llvm_cbe_tmp__81&4294967295U) == (11u&4294967295U))) {
    goto llvm_cbe_tmp__101;
  } else {
    llvm_cbe_storemerge14__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__81;   /* for PHI node */
    goto llvm_cbe_tmp__97;
  }

llvm_cbe_tmp__98:
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([15 x i8]* @aesl_internal_.str7, i64 0, i64 0)) nounwind, !dbg !17 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_175_count);
  printf(( char *)((&aesl_internal__OC_str7[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 15
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__76);
}
  goto llvm_cbe_tmp__100;

llvm_cbe_tmp__99:

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__70) < 11)) fprintf(stderr, "%s:%d: warning: Read access out of array 'out_d' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = load float* %%54, align 4, !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_177_count);
  llvm_cbe_tmp__77 = (float )*llvm_cbe_tmp__73;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__77, *(int*)(&llvm_cbe_tmp__77));
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = fsub float %%53, %%60, !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_178_count);
  llvm_cbe_tmp__78 = (float )((float )(llvm_cbe_tmp__72 - llvm_cbe_tmp__77));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__78, *(int*)(&llvm_cbe_tmp__78));
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = fpext float %%61 to double, !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_179_count);
  llvm_cbe_tmp__79 = (double )((double )llvm_cbe_tmp__78);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__79, *(long long*)(&llvm_cbe_tmp__79));
if (AESL_DEBUG_TRACE)
printf("\n  %%63 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([18 x i8]* @aesl_internal_.str8, i64 0, i64 0), double %%62) nounwind, !dbg !16 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_180_count);
  printf(( char *)((&aesl_internal__OC_str8[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 18
#endif
])), llvm_cbe_tmp__79);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__79, *(long long*)(&llvm_cbe_tmp__79));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__80);
}
  goto llvm_cbe_tmp__100;

  } while (1); /* end of syntactic loop '' */
llvm_cbe_tmp__101:
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([31 x i8]* @aesl_internal_.str9, i64 0, i64 0)) nounwind, !dbg !17 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_191_count);
  printf(( char *)((&aesl_internal__OC_str9[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 31
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__82);
}
  llvm_cbe_storemerge23__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__102;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__102:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge23 = phi i32 [ 0, %%66 ], [ %%83, %%82  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_storemerge23_count);
  llvm_cbe_storemerge23 = (unsigned int )llvm_cbe_storemerge23__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge23 = 0x%X",llvm_cbe_storemerge23);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__94);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%69 = sext i32 %%storemerge23 to i64, !dbg !17 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_200_count);
  llvm_cbe_tmp__83 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge23);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__83);
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = getelementptr inbounds [11 x float]* @aesl_internal_main.uq_out, i64 0, i64 %%69, !dbg !17 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_201_count);
  llvm_cbe_tmp__84 = (float *)(&aesl_internal_main_OC_uq_out[(((signed long long )llvm_cbe_tmp__83))
#ifdef AESL_BC_SIM
 % 11
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__83));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__83) < 11)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_main.uq_out' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = load float* %%70, align 4, !dbg !17 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_202_count);
  llvm_cbe_tmp__85 = (float )*llvm_cbe_tmp__84;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__85, *(int*)(&llvm_cbe_tmp__85));
if (AESL_DEBUG_TRACE)
printf("\n  %%72 = getelementptr inbounds [11 x float]* %%out_q, i64 0, i64 %%69, !dbg !17 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_203_count);
  llvm_cbe_tmp__86 = (float *)(&llvm_cbe_out_q[(((signed long long )llvm_cbe_tmp__83))
#ifdef AESL_BC_SIM
 % 11
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__83));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__83) < 11)) fprintf(stderr, "%s:%d: warning: Read access out of array 'out_q' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%73 = load float* %%72, align 4, !dbg !17 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_204_count);
  llvm_cbe_tmp__87 = (float )*llvm_cbe_tmp__86;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__87, *(int*)(&llvm_cbe_tmp__87));
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = call zeroext i1 @approx_eqf(float %%71, float %%73, i32 10000, float 1.000000e+03), !dbg !17 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_205_count);
  llvm_cbe_tmp__88 = (bool )((approx_eqf(llvm_cbe_tmp__85, llvm_cbe_tmp__87, 10000u, 0x1.f4p9))&1);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__85, *(int*)(&llvm_cbe_tmp__85));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__87, *(int*)(&llvm_cbe_tmp__87));
printf("\nArgument  = 0x%X",10000u);
printf("\nArgument  = %f",0x1.f4p9);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__88);
}
  if (llvm_cbe_tmp__88) {
    goto llvm_cbe_tmp__103;
  } else {
    goto llvm_cbe_tmp__104;
  }

llvm_cbe_tmp__105:
if (AESL_DEBUG_TRACE)
printf("\n  %%83 = add nsw i32 %%storemerge23, 1, !dbg !18 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_216_count);
  llvm_cbe_tmp__94 = (unsigned int )((unsigned int )(llvm_cbe_storemerge23&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__94&4294967295ull)));
  if (((llvm_cbe_tmp__94&4294967295U) == (11u&4294967295U))) {
    goto llvm_cbe_tmp__106;
  } else {
    llvm_cbe_storemerge23__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__94;   /* for PHI node */
    goto llvm_cbe_tmp__102;
  }

llvm_cbe_tmp__103:
if (AESL_DEBUG_TRACE)
printf("\n  %%76 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([15 x i8]* @aesl_internal_.str10, i64 0, i64 0)) nounwind, !dbg !18 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_209_count);
  printf(( char *)((&aesl_internal__OC_str10[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 15
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__89);
}
  goto llvm_cbe_tmp__105;

llvm_cbe_tmp__104:

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__83) < 11)) fprintf(stderr, "%s:%d: warning: Read access out of array 'out_q' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%78 = load float* %%72, align 4, !dbg !18 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_211_count);
  llvm_cbe_tmp__90 = (float )*llvm_cbe_tmp__86;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__90, *(int*)(&llvm_cbe_tmp__90));
if (AESL_DEBUG_TRACE)
printf("\n  %%79 = fsub float %%71, %%78, !dbg !18 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_212_count);
  llvm_cbe_tmp__91 = (float )((float )(llvm_cbe_tmp__85 - llvm_cbe_tmp__90));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__91, *(int*)(&llvm_cbe_tmp__91));
if (AESL_DEBUG_TRACE)
printf("\n  %%80 = fpext float %%79 to double, !dbg !18 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_213_count);
  llvm_cbe_tmp__92 = (double )((double )llvm_cbe_tmp__91);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__92, *(long long*)(&llvm_cbe_tmp__92));
if (AESL_DEBUG_TRACE)
printf("\n  %%81 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([18 x i8]* @aesl_internal_.str11, i64 0, i64 0), double %%80) nounwind, !dbg !18 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_214_count);
  printf(( char *)((&aesl_internal__OC_str11[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 18
#endif
])), llvm_cbe_tmp__92);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__92, *(long long*)(&llvm_cbe_tmp__92));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__93);
}
  goto llvm_cbe_tmp__105;

  } while (1); /* end of syntactic loop '' */
llvm_cbe_tmp__106:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @main}\n");
  return 0u;
}

