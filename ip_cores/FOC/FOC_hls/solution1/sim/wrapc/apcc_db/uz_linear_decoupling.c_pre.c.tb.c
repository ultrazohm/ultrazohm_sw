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
typedef struct l_struct_OC_uz_dq_t l_struct_OC_uz_dq_t;
typedef struct l_struct_OC_uz_PMSM_t l_struct_OC_uz_PMSM_t;

/* Structure contents */
struct l_struct_OC_uz_dq_t {
  float field0;
  float field1;
  float field2;
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


/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
l_struct_OC_uz_dq_t uz_FOC_linear_decoupling(l_struct_OC_uz_PMSM_t llvm_cbe_config, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, float llvm_cbe_omega_el_rad_per_sec);


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

l_struct_OC_uz_dq_t uz_FOC_linear_decoupling(l_struct_OC_uz_PMSM_t llvm_cbe_config, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, float llvm_cbe_omega_el_rad_per_sec) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  float *llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  float llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  float llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  float *llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  float llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  float llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  float llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  float *llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  float llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  float *llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  float llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  float llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  float *llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  float llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  float llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  float llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  float *llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  float *llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  float *llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_FOC_linear_decoupling\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32 1, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_9_count);
  llvm_cbe_tmp__1 = (float *)(&llvm_cbe_i_actual_Ampere.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = load float* %%1, align 4, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_10_count);
  llvm_cbe_tmp__2 = (float )*llvm_cbe_tmp__1;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__2, *(int*)(&llvm_cbe_tmp__2));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = fmul float %%2, -1.000000e+00, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_11_count);
  llvm_cbe_tmp__3 = (float )((float )(llvm_cbe_tmp__2 * -0x1p0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__3, *(int*)(&llvm_cbe_tmp__3));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds %%struct.uz_PMSM_t* %%config, i64 0, i32 2, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_12_count);
  llvm_cbe_tmp__4 = (float *)(&llvm_cbe_config.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load float* %%4, align 4, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_13_count);
  llvm_cbe_tmp__5 = (float )*llvm_cbe_tmp__4;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__5, *(int*)(&llvm_cbe_tmp__5));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = fmul float %%3, %%5, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_14_count);
  llvm_cbe_tmp__6 = (float )((float )(llvm_cbe_tmp__3 * llvm_cbe_tmp__5));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__6, *(int*)(&llvm_cbe_tmp__6));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = fmul float %%6, %%omega_el_rad_per_sec, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_15_count);
  llvm_cbe_tmp__7 = (float )((float )(llvm_cbe_tmp__6 * llvm_cbe_omega_el_rad_per_sec));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__7, *(int*)(&llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32 0, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_17_count);
  llvm_cbe_tmp__8 = (float *)(&llvm_cbe_i_actual_Ampere.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load float* %%8, align 4, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_18_count);
  llvm_cbe_tmp__9 = (float )*llvm_cbe_tmp__8;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__9, *(int*)(&llvm_cbe_tmp__9));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds %%struct.uz_PMSM_t* %%config, i64 0, i32 1, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_19_count);
  llvm_cbe_tmp__10 = (float *)(&llvm_cbe_config.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load float* %%10, align 4, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_20_count);
  llvm_cbe_tmp__11 = (float )*llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__11, *(int*)(&llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = fmul float %%9, %%11, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_21_count);
  llvm_cbe_tmp__12 = (float )((float )(llvm_cbe_tmp__9 * llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__12, *(int*)(&llvm_cbe_tmp__12));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds %%struct.uz_PMSM_t* %%config, i64 0, i32 3, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_22_count);
  llvm_cbe_tmp__13 = (float *)(&llvm_cbe_config.field3);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = load float* %%13, align 4, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_23_count);
  llvm_cbe_tmp__14 = (float )*llvm_cbe_tmp__13;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__14, *(int*)(&llvm_cbe_tmp__14));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = fadd float %%12, %%14, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_24_count);
  llvm_cbe_tmp__15 = (float )((float )(llvm_cbe_tmp__12 + llvm_cbe_tmp__14));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__15, *(int*)(&llvm_cbe_tmp__15));
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = fmul float %%15, %%omega_el_rad_per_sec, !dbg !4 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_25_count);
  llvm_cbe_tmp__16 = (float )((float )(llvm_cbe_tmp__15 * llvm_cbe_omega_el_rad_per_sec));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__16, *(int*)(&llvm_cbe_tmp__16));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !5 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_27_count);
  llvm_cbe_tmp__17 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%7, float* %%17, align 4, !dbg !5 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_28_count);
  *llvm_cbe_tmp__17 = llvm_cbe_tmp__7;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__7);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !5 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__18 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%16, float* %%18, align 4, !dbg !5 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_30_count);
  *llvm_cbe_tmp__18 = llvm_cbe_tmp__16;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__16);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !5 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__19 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* %%19, align 4, !dbg !5 for 0x%I64xth hint within @uz_FOC_linear_decoupling  --> \n", ++aesl_llvm_cbe_32_count);
  *llvm_cbe_tmp__19 = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
if (AESL_DEBUG_TRACE)
    printf("\n END @uz_FOC_linear_decoupling }\n"); 
  return StructReturn;
}

