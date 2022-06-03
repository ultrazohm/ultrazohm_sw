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

/* Structure contents */
struct l_struct_OC_uz_PI_Controller_config {
  float field0;
  float field1;
  float field2;
  float field3;
  float field4;
};


/* External Global Variable Declarations */

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
bool uz_PI_Controller_Clamping_Circuit(float llvm_cbe_preIntegrator, float llvm_cbe_preSat, float llvm_cbe_upper_limit, float llvm_cbe_lower_limit);
float uz_signals_dead_zone(float , float , float );
float uz_signals_get_sign_of_value(float );
float uz_PI_Controller_sample(l_struct_OC_uz_PI_Controller_config *llvm_cbe_self, bool llvm_cbe_I_rst, float llvm_cbe_referenceValue, float llvm_cbe_actualValue, bool llvm_cbe_ext_clamping);
float uz_signals_saturation(float , float , float );


/* Global Variable Definitions and Initialization */
static float aesl_internal_uz_PI_Controller_sample_OC_I_sum;


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

bool uz_PI_Controller_Clamping_Circuit(float llvm_cbe_preIntegrator, float llvm_cbe_preSat, float llvm_cbe_upper_limit, float llvm_cbe_lower_limit) {
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
  float llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  float llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  float llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond_count = 0;
  bool llvm_cbe_or_2e_cond;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_PI_Controller_Clamping_Circuit\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call float @uz_signals_dead_zone(float %%preSat, float %%upper_limit, float %%lower_limit) nounwind, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_Clamping_Circuit  --> \n", ++aesl_llvm_cbe_10_count);
  llvm_cbe_tmp__1 = (float ) /*tail*/ uz_signals_dead_zone(llvm_cbe_preSat, llvm_cbe_upper_limit, llvm_cbe_lower_limit);
if (AESL_DEBUG_TRACE) {
printf("\nArgument preSat = %f,  0x%x",llvm_cbe_preSat, *(int*)(&llvm_cbe_preSat));
printf("\nArgument upper_limit = %f,  0x%x",llvm_cbe_upper_limit, *(int*)(&llvm_cbe_upper_limit));
printf("\nArgument lower_limit = %f,  0x%x",llvm_cbe_lower_limit, *(int*)(&llvm_cbe_lower_limit));
printf("\nReturn  = %f",llvm_cbe_tmp__1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = tail call float @uz_signals_get_sign_of_value(float %%1) nounwind, !dbg !6 for 0x%I64xth hint within @uz_PI_Controller_Clamping_Circuit  --> \n", ++aesl_llvm_cbe_14_count);
  llvm_cbe_tmp__2 = (float ) /*tail*/ uz_signals_get_sign_of_value(llvm_cbe_tmp__1);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__1, *(int*)(&llvm_cbe_tmp__1));
printf("\nReturn  = %f",llvm_cbe_tmp__2);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = tail call float @uz_signals_get_sign_of_value(float %%preIntegrator) nounwind, !dbg !4 for 0x%I64xth hint within @uz_PI_Controller_Clamping_Circuit  --> \n", ++aesl_llvm_cbe_17_count);
  llvm_cbe_tmp__3 = (float ) /*tail*/ uz_signals_get_sign_of_value(llvm_cbe_preIntegrator);
if (AESL_DEBUG_TRACE) {
printf("\nArgument preIntegrator = %f,  0x%x",llvm_cbe_preIntegrator, *(int*)(&llvm_cbe_preIntegrator));
printf("\nReturn  = %f",llvm_cbe_tmp__3);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond = and i1 %%4, %%5, !dbg !6 for 0x%I64xth hint within @uz_PI_Controller_Clamping_Circuit  --> \n", ++aesl_llvm_cbe_or_2e_cond_count);
  llvm_cbe_or_2e_cond = (bool )(((llvm_fcmp_une(llvm_cbe_tmp__1, 0x0p0)) & (llvm_fcmp_oeq(llvm_cbe_tmp__2, llvm_cbe_tmp__3)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond = 0x%X\n", llvm_cbe_or_2e_cond);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @uz_PI_Controller_Clamping_Circuit}\n");
  return llvm_cbe_or_2e_cond;
}


float uz_PI_Controller_sample(l_struct_OC_uz_PI_Controller_config *llvm_cbe_self, bool llvm_cbe_I_rst, float llvm_cbe_referenceValue, float llvm_cbe_actualValue, bool llvm_cbe_ext_clamping) {
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  float llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  float llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  float *llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  float llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  float llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  float *llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  float llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  float llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  float llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  float *llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  float llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  float *llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  float llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  bool llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  bool llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  float llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  float llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  float *llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  float llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  float llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  float llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  float llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge_count = 0;
  float llvm_cbe_storemerge;
  float llvm_cbe_storemerge__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  float llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  float llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  float llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_PI_Controller_sample\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = fsub float %%referenceValue, %%actualValue, !dbg !6 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_42_count);
  llvm_cbe_tmp__4 = (float )((float )(llvm_cbe_referenceValue - llvm_cbe_actualValue));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__4, *(int*)(&llvm_cbe_tmp__4));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = load float* @aesl_internal_uz_PI_Controller_sample.I_sum, align 4, !dbg !7 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__5 = (float )*(&aesl_internal_uz_PI_Controller_sample_OC_I_sum);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__5, *(int*)(&llvm_cbe_tmp__5));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%self, i64 0, i32 1, !dbg !4 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_49_count);
  llvm_cbe_tmp__6 = (float *)(&llvm_cbe_self->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load float* %%3, align 4, !dbg !4 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_50_count);
  llvm_cbe_tmp__7 = (float )*llvm_cbe_tmp__6;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__7, *(int*)(&llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = fmul float %%1, %%4, !dbg !4 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_51_count);
  llvm_cbe_tmp__8 = (float )((float )(llvm_cbe_tmp__4 * llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__8, *(int*)(&llvm_cbe_tmp__8));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%self, i64 0, i32 0, !dbg !4 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_55_count);
  llvm_cbe_tmp__9 = (float *)(&llvm_cbe_self->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load float* %%6, align 4, !dbg !4 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_56_count);
  llvm_cbe_tmp__10 = (float )*llvm_cbe_tmp__9;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__10, *(int*)(&llvm_cbe_tmp__10));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = fmul float %%1, %%7, !dbg !4 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_57_count);
  llvm_cbe_tmp__11 = (float )((float )(llvm_cbe_tmp__4 * llvm_cbe_tmp__10));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__11, *(int*)(&llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = fadd float %%2, %%8, !dbg !7 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_60_count);
  llvm_cbe_tmp__12 = (float )((float )(llvm_cbe_tmp__5 + llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__12, *(int*)(&llvm_cbe_tmp__12));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%self, i64 0, i32 3, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_64_count);
  llvm_cbe_tmp__13 = (float *)(&llvm_cbe_self->field3);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load float* %%10, align 4, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_65_count);
  llvm_cbe_tmp__14 = (float )*llvm_cbe_tmp__13;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__14, *(int*)(&llvm_cbe_tmp__14));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%self, i64 0, i32 4, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_66_count);
  llvm_cbe_tmp__15 = (float *)(&llvm_cbe_self->field4);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = load float* %%12, align 4, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_67_count);
  llvm_cbe_tmp__16 = (float )*llvm_cbe_tmp__15;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__16, *(int*)(&llvm_cbe_tmp__16));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = tail call zeroext i1 @uz_PI_Controller_Clamping_Circuit(float %%5, float %%9, float %%11, float %%13), !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_68_count);
  llvm_cbe_tmp__17 = (bool )(( /*tail*/ uz_PI_Controller_Clamping_Circuit(llvm_cbe_tmp__8, llvm_cbe_tmp__12, llvm_cbe_tmp__14, llvm_cbe_tmp__16))&1);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__8, *(int*)(&llvm_cbe_tmp__8));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__12, *(int*)(&llvm_cbe_tmp__12));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__14, *(int*)(&llvm_cbe_tmp__14));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__16, *(int*)(&llvm_cbe_tmp__16));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__17);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = or i1 %%14, %%ext_clamping, !dbg !6 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_71_count);
  llvm_cbe_tmp__18 = (bool )((llvm_cbe_tmp__17 | llvm_cbe_ext_clamping)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__18);
  if (llvm_cbe_tmp__18) {
    goto llvm_cbe_tmp__29;
  } else {
    goto llvm_cbe_tmp__30;
  }

llvm_cbe_tmp__29:
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load float* @aesl_internal_uz_PI_Controller_sample.I_sum, align 4, !dbg !7 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__19 = (float )*(&aesl_internal_uz_PI_Controller_sample_OC_I_sum);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__19, *(int*)(&llvm_cbe_tmp__19));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = fadd float %%17, 0.000000e+00, !dbg !7 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_76_count);
  llvm_cbe_tmp__20 = (float )((float )(llvm_cbe_tmp__19 + 0x0p0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__20, *(int*)(&llvm_cbe_tmp__20));
  llvm_cbe_storemerge__PHI_TEMPORARY = (float )llvm_cbe_tmp__20;   /* for PHI node */
  goto llvm_cbe_tmp__31;

llvm_cbe_tmp__30:
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%self, i64 0, i32 2, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_78_count);
  llvm_cbe_tmp__21 = (float *)(&llvm_cbe_self->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = load float* %%20, align 4, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_79_count);
  llvm_cbe_tmp__22 = (float )*llvm_cbe_tmp__21;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__22, *(int*)(&llvm_cbe_tmp__22));
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = fmul float %%5, %%21, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_80_count);
  llvm_cbe_tmp__23 = (float )((float )(llvm_cbe_tmp__8 * llvm_cbe_tmp__22));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__23, *(int*)(&llvm_cbe_tmp__23));
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = load float* @aesl_internal_uz_PI_Controller_sample.I_sum, align 4, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_81_count);
  llvm_cbe_tmp__24 = (float )*(&aesl_internal_uz_PI_Controller_sample_OC_I_sum);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__24, *(int*)(&llvm_cbe_tmp__24));
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = fadd float %%23, %%22, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__25 = (float )((float )(llvm_cbe_tmp__24 + llvm_cbe_tmp__23));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__25, *(int*)(&llvm_cbe_tmp__25));
  llvm_cbe_storemerge__PHI_TEMPORARY = (float )llvm_cbe_tmp__25;   /* for PHI node */
  goto llvm_cbe_tmp__31;

llvm_cbe_tmp__31:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge = phi float [ %%24, %%19 ], [ %%18, %%16  for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_storemerge_count);
  llvm_cbe_storemerge = (float )llvm_cbe_storemerge__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge = %f",llvm_cbe_storemerge);
printf("\n = %f",llvm_cbe_tmp__25);
printf("\n = %f",llvm_cbe_tmp__20);
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%storemerge, float* @aesl_internal_uz_PI_Controller_sample.I_sum, align 4, !dbg !7 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_84_count);
  *(&aesl_internal_uz_PI_Controller_sample_OC_I_sum) = llvm_cbe_storemerge;
if (AESL_DEBUG_TRACE)
printf("\nstoremerge = %f\n", llvm_cbe_storemerge);
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = load float* %%10, align 4, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_85_count);
  llvm_cbe_tmp__26 = (float )*llvm_cbe_tmp__13;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__26, *(int*)(&llvm_cbe_tmp__26));
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = load float* %%12, align 4, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_86_count);
  llvm_cbe_tmp__27 = (float )*llvm_cbe_tmp__15;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__27, *(int*)(&llvm_cbe_tmp__27));
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = tail call float @uz_signals_saturation(float %%9, float %%26, float %%27) nounwind, !dbg !5 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__28 = (float ) /*tail*/ uz_signals_saturation(llvm_cbe_tmp__12, llvm_cbe_tmp__26, llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__12, *(int*)(&llvm_cbe_tmp__12));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__26, *(int*)(&llvm_cbe_tmp__26));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__27, *(int*)(&llvm_cbe_tmp__27));
printf("\nReturn  = %f",llvm_cbe_tmp__28);
}
  if (llvm_cbe_I_rst) {
    goto llvm_cbe_tmp__32;
  } else {
    goto llvm_cbe_tmp__33;
  }

llvm_cbe_tmp__32:
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* @aesl_internal_uz_PI_Controller_sample.I_sum, align 4, !dbg !8 for 0x%I64xth hint within @uz_PI_Controller_sample  --> \n", ++aesl_llvm_cbe_91_count);
  *(&aesl_internal_uz_PI_Controller_sample_OC_I_sum) = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
  goto llvm_cbe_tmp__33;

llvm_cbe_tmp__33:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @uz_PI_Controller_sample}\n");
  return llvm_cbe_tmp__28;
}

