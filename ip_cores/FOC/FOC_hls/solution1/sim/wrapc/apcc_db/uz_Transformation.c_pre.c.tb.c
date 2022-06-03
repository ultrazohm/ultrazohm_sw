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

/* Structure contents */
struct l_struct_OC_uz_dq_t {
  float field0;
  float field1;
  float field2;
};


/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
l_struct_OC_uz_dq_t uz_dq_transformation(l_struct_OC_uz_dq_t llvm_cbe_input, float llvm_cbe_theta_el_rad);
l_struct_OC_uz_dq_t uz_clarke_transformation(l_struct_OC_uz_dq_t llvm_cbe_input);
l_struct_OC_uz_dq_t uz_dq_inverse_transformation(l_struct_OC_uz_dq_t llvm_cbe_input, float llvm_cbe_theta_el_rad);
l_struct_OC_uz_dq_t uz_clarke_inverse_transformation(l_struct_OC_uz_dq_t llvm_cbe_input);


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

l_struct_OC_uz_dq_t uz_dq_transformation(l_struct_OC_uz_dq_t llvm_cbe_input, float llvm_cbe_theta_el_rad) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
  static  unsigned long long aesl_llvm_cbe_ab_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_ab;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  float llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  float llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  float *llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  float llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  float llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  float *llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  float llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  float llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  float llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  float llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  float llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  float llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  float llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  float *llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  float llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  float *llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  float *llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  float *llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_dq_transformation\n");
if (AESL_DEBUG_TRACE)
printf("\n  call void @uz_clarke_transformation(%%struct.uz_dq_t* sret %%ab, %%struct.uz_dq_t* byval %%input), !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_6_count);
  llvm_cbe_ab = uz_clarke_transformation(llvm_cbe_input);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = call float @sinf(float %%theta_el_rad) nounwind readnone, !dbg !5 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_7_count);
  llvm_cbe_tmp__1 = (float )sinf(llvm_cbe_theta_el_rad);
if (AESL_DEBUG_TRACE) {
printf("\nArgument theta_el_rad = %f,  0x%x",llvm_cbe_theta_el_rad, *(int*)(&llvm_cbe_theta_el_rad));
printf("\nReturn  = %f",llvm_cbe_tmp__1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = call float @cosf(float %%theta_el_rad) nounwind readnone, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_11_count);
  llvm_cbe_tmp__2 = (float )cosf(llvm_cbe_theta_el_rad);
if (AESL_DEBUG_TRACE) {
printf("\nArgument theta_el_rad = %f,  0x%x",llvm_cbe_theta_el_rad, *(int*)(&llvm_cbe_theta_el_rad));
printf("\nReturn  = %f",llvm_cbe_tmp__2);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.uz_dq_t* %%ab, i64 0, i32 0, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_15_count);
  llvm_cbe_tmp__3 = (float *)(&llvm_cbe_ab.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load float* %%3, align 4, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_16_count);
  llvm_cbe_tmp__4 = (float )*llvm_cbe_tmp__3;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__4, *(int*)(&llvm_cbe_tmp__4));
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = fmul float %%2, %%4, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_17_count);
  llvm_cbe_tmp__5 = (float )((float )(llvm_cbe_tmp__2 * llvm_cbe_tmp__4));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__5, *(int*)(&llvm_cbe_tmp__5));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.uz_dq_t* %%ab, i64 0, i32 1, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_18_count);
  llvm_cbe_tmp__6 = (float *)(&llvm_cbe_ab.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load float* %%6, align 4, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_19_count);
  llvm_cbe_tmp__7 = (float )*llvm_cbe_tmp__6;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__7, *(int*)(&llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = fmul float %%1, %%7, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_20_count);
  llvm_cbe_tmp__8 = (float )((float )(llvm_cbe_tmp__1 * llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__8, *(int*)(&llvm_cbe_tmp__8));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = fadd float %%5, %%8, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_21_count);
  llvm_cbe_tmp__9 = (float )((float )(llvm_cbe_tmp__5 + llvm_cbe_tmp__8));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__9, *(int*)(&llvm_cbe_tmp__9));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = fsub float -0.000000e+00, %%1, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_23_count);
  llvm_cbe_tmp__10 = (float )((float )(-(llvm_cbe_tmp__1)));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__10, *(int*)(&llvm_cbe_tmp__10));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = fmul float %%4, %%10, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_24_count);
  llvm_cbe_tmp__11 = (float )((float )(llvm_cbe_tmp__4 * llvm_cbe_tmp__10));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__11, *(int*)(&llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = fmul float %%2, %%7, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_25_count);
  llvm_cbe_tmp__12 = (float )((float )(llvm_cbe_tmp__2 * llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__12, *(int*)(&llvm_cbe_tmp__12));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = fadd float %%11, %%12, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_26_count);
  llvm_cbe_tmp__13 = (float )((float )(llvm_cbe_tmp__11 + llvm_cbe_tmp__12));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__13, *(int*)(&llvm_cbe_tmp__13));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds %%struct.uz_dq_t* %%ab, i64 0, i32 2, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_28_count);
  llvm_cbe_tmp__14 = (float *)(&llvm_cbe_ab.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load float* %%14, align 4, !dbg !6 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__15 = (float )*llvm_cbe_tmp__14;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__15, *(int*)(&llvm_cbe_tmp__15));
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__16 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%9, float* %%16, align 4, !dbg !7 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_32_count);
  *llvm_cbe_tmp__16 = llvm_cbe_tmp__9;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_33_count);
  llvm_cbe_tmp__17 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%13, float* %%17, align 4, !dbg !7 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_34_count);
  *llvm_cbe_tmp__17 = llvm_cbe_tmp__13;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !7 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__18 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%15, float* %%18, align 4, !dbg !7 for 0x%I64xth hint within @uz_dq_transformation  --> \n", ++aesl_llvm_cbe_36_count);
  *llvm_cbe_tmp__18 = llvm_cbe_tmp__15;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__15);
if (AESL_DEBUG_TRACE)
    printf("\n END @uz_dq_transformation }\n"); 
  return StructReturn;
}


l_struct_OC_uz_dq_t uz_clarke_transformation(l_struct_OC_uz_dq_t llvm_cbe_input) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  float *llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  float llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  float *llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  float llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  float llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  float llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  float *llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  float llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  float llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  float llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  float llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  float llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  float llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  float llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  float llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  float llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  float llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  float llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  float *llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  float *llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  float *llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_clarke_transformation\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.uz_dq_t* %%input, i64 0, i32 0, !dbg !5 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_39_count);
  llvm_cbe_tmp__19 = (float *)(&llvm_cbe_input.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = load float* %%1, align 4, !dbg !5 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_40_count);
  llvm_cbe_tmp__20 = (float )*llvm_cbe_tmp__19;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__20, *(int*)(&llvm_cbe_tmp__20));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.uz_dq_t* %%input, i64 0, i32 1, !dbg !5 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_41_count);
  llvm_cbe_tmp__21 = (float *)(&llvm_cbe_input.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load float* %%3, align 4, !dbg !5 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_42_count);
  llvm_cbe_tmp__22 = (float )*llvm_cbe_tmp__21;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__22, *(int*)(&llvm_cbe_tmp__22));
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = fmul float %%4, 5.000000e-01, !dbg !5 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_43_count);
  llvm_cbe_tmp__23 = (float )((float )(llvm_cbe_tmp__22 * 0x1p-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__23, *(int*)(&llvm_cbe_tmp__23));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = fsub float %%2, %%5, !dbg !5 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_44_count);
  llvm_cbe_tmp__24 = (float )((float )(llvm_cbe_tmp__20 - llvm_cbe_tmp__23));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__24, *(int*)(&llvm_cbe_tmp__24));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds %%struct.uz_dq_t* %%input, i64 0, i32 2, !dbg !5 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_45_count);
  llvm_cbe_tmp__25 = (float *)(&llvm_cbe_input.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load float* %%7, align 4, !dbg !5 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__26 = (float )*llvm_cbe_tmp__25;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__26, *(int*)(&llvm_cbe_tmp__26));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = fmul float %%8, 5.000000e-01, !dbg !5 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__27 = (float )((float )(llvm_cbe_tmp__26 * 0x1p-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__27, *(int*)(&llvm_cbe_tmp__27));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = fsub float %%6, %%9, !dbg !5 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_48_count);
  llvm_cbe_tmp__28 = (float )((float )(llvm_cbe_tmp__24 - llvm_cbe_tmp__27));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__28, *(int*)(&llvm_cbe_tmp__28));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = fmul float %%10, 0x3FE5555560000000, !dbg !5 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_49_count);
  llvm_cbe_tmp__29 = (float )((float )(llvm_cbe_tmp__28 * 0x1.555556p-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__29, *(int*)(&llvm_cbe_tmp__29));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = fmul float %%4, 0x3FEBB67AE0000000, !dbg !6 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_51_count);
  llvm_cbe_tmp__30 = (float )((float )(llvm_cbe_tmp__22 * 0x1.bb67aep-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__30, *(int*)(&llvm_cbe_tmp__30));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = fmul float %%8, 0x3FEBB67AE0000000, !dbg !6 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_52_count);
  llvm_cbe_tmp__31 = (float )((float )(llvm_cbe_tmp__26 * 0x1.bb67aep-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__31, *(int*)(&llvm_cbe_tmp__31));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = fsub float %%12, %%13, !dbg !6 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_53_count);
  llvm_cbe_tmp__32 = (float )((float )(llvm_cbe_tmp__30 - llvm_cbe_tmp__31));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__32, *(int*)(&llvm_cbe_tmp__32));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = fmul float %%14, 0x3FE5555560000000, !dbg !6 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_54_count);
  llvm_cbe_tmp__33 = (float )((float )(llvm_cbe_tmp__32 * 0x1.555556p-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__33, *(int*)(&llvm_cbe_tmp__33));
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = fadd float %%2, %%4, !dbg !6 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_56_count);
  llvm_cbe_tmp__34 = (float )((float )(llvm_cbe_tmp__20 + llvm_cbe_tmp__22));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__34, *(int*)(&llvm_cbe_tmp__34));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = fadd float %%16, %%8, !dbg !6 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_57_count);
  llvm_cbe_tmp__35 = (float )((float )(llvm_cbe_tmp__34 + llvm_cbe_tmp__26));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__35, *(int*)(&llvm_cbe_tmp__35));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = fmul float %%17, 0x3FD5555560000000, !dbg !6 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_58_count);
  llvm_cbe_tmp__36 = (float )((float )(llvm_cbe_tmp__35 * 0x1.555556p-2));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__36, *(int*)(&llvm_cbe_tmp__36));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_60_count);
  llvm_cbe_tmp__37 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%11, float* %%19, align 4, !dbg !7 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_61_count);
  *llvm_cbe_tmp__37 = llvm_cbe_tmp__29;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__29);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_62_count);
  llvm_cbe_tmp__38 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%15, float* %%20, align 4, !dbg !7 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_63_count);
  *llvm_cbe_tmp__38 = llvm_cbe_tmp__33;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__33);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !7 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_64_count);
  llvm_cbe_tmp__39 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%18, float* %%21, align 4, !dbg !7 for 0x%I64xth hint within @uz_clarke_transformation  --> \n", ++aesl_llvm_cbe_65_count);
  *llvm_cbe_tmp__39 = llvm_cbe_tmp__36;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
    printf("\n END @uz_clarke_transformation }\n"); 
  return StructReturn;
}


l_struct_OC_uz_dq_t uz_dq_inverse_transformation(l_struct_OC_uz_dq_t llvm_cbe_input, float llvm_cbe_theta_el_rad) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
  static  unsigned long long aesl_llvm_cbe_ab_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_ab;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_output_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_output;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  float llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  float llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  float *llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  float *llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  float llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  float llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  float *llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  float llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  float llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  float llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  float *llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  float llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  float llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  float llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  float *llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  float *llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  float llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  float *llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  float *llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  float llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  float *llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  float *llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  float llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  float *llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  float *llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  float llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_dq_inverse_transformation\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = call float @sinf(float %%theta_el_rad) nounwind readnone, !dbg !5 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_70_count);
  llvm_cbe_tmp__40 = (float )sinf(llvm_cbe_theta_el_rad);
if (AESL_DEBUG_TRACE) {
printf("\nArgument theta_el_rad = %f,  0x%x",llvm_cbe_theta_el_rad, *(int*)(&llvm_cbe_theta_el_rad));
printf("\nReturn  = %f",llvm_cbe_tmp__40);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = call float @cosf(float %%theta_el_rad) nounwind readnone, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__41 = (float )cosf(llvm_cbe_theta_el_rad);
if (AESL_DEBUG_TRACE) {
printf("\nArgument theta_el_rad = %f,  0x%x",llvm_cbe_theta_el_rad, *(int*)(&llvm_cbe_theta_el_rad));
printf("\nReturn  = %f",llvm_cbe_tmp__41);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.uz_dq_t* %%ab, i64 0, i32 0, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_80_count);
  llvm_cbe_tmp__42 = (float *)(&llvm_cbe_ab.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds %%struct.uz_dq_t* %%input, i64 0, i32 0, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_81_count);
  llvm_cbe_tmp__43 = (float *)(&llvm_cbe_input.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load float* %%4, align 4, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__44 = (float )*llvm_cbe_tmp__43;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__44, *(int*)(&llvm_cbe_tmp__44));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = fmul float %%2, %%5, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__45 = (float )((float )(llvm_cbe_tmp__41 * llvm_cbe_tmp__44));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__45, *(int*)(&llvm_cbe_tmp__45));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds %%struct.uz_dq_t* %%input, i64 0, i32 1, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_84_count);
  llvm_cbe_tmp__46 = (float *)(&llvm_cbe_input.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load float* %%7, align 4, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_85_count);
  llvm_cbe_tmp__47 = (float )*llvm_cbe_tmp__46;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__47, *(int*)(&llvm_cbe_tmp__47));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = fmul float %%1, %%8, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_86_count);
  llvm_cbe_tmp__48 = (float )((float )(llvm_cbe_tmp__40 * llvm_cbe_tmp__47));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__48, *(int*)(&llvm_cbe_tmp__48));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = fsub float %%6, %%9, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__49 = (float )((float )(llvm_cbe_tmp__45 - llvm_cbe_tmp__48));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__49, *(int*)(&llvm_cbe_tmp__49));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%10, float* %%3, align 4, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_88_count);
  *llvm_cbe_tmp__42 = llvm_cbe_tmp__49;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__49);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds %%struct.uz_dq_t* %%ab, i64 0, i32 1, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_89_count);
  llvm_cbe_tmp__50 = (float *)(&llvm_cbe_ab.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = fmul float %%1, %%5, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_90_count);
  llvm_cbe_tmp__51 = (float )((float )(llvm_cbe_tmp__40 * llvm_cbe_tmp__44));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__51, *(int*)(&llvm_cbe_tmp__51));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = fmul float %%2, %%8, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_91_count);
  llvm_cbe_tmp__52 = (float )((float )(llvm_cbe_tmp__41 * llvm_cbe_tmp__47));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__52, *(int*)(&llvm_cbe_tmp__52));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = fadd float %%12, %%13, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_92_count);
  llvm_cbe_tmp__53 = (float )((float )(llvm_cbe_tmp__51 + llvm_cbe_tmp__52));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__53, *(int*)(&llvm_cbe_tmp__53));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%14, float* %%11, align 4, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_93_count);
  *llvm_cbe_tmp__50 = llvm_cbe_tmp__53;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__53);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds %%struct.uz_dq_t* %%ab, i64 0, i32 2, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_94_count);
  llvm_cbe_tmp__54 = (float *)(&llvm_cbe_ab.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds %%struct.uz_dq_t* %%input, i64 0, i32 2, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_95_count);
  llvm_cbe_tmp__55 = (float *)(&llvm_cbe_input.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load float* %%16, align 4, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_96_count);
  llvm_cbe_tmp__56 = (float )*llvm_cbe_tmp__55;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__56, *(int*)(&llvm_cbe_tmp__56));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%17, float* %%15, align 4, !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_97_count);
  *llvm_cbe_tmp__54 = llvm_cbe_tmp__56;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__56);
if (AESL_DEBUG_TRACE)
printf("\n  call void @uz_clarke_inverse_transformation(%%struct.uz_dq_t* sret %%output, %%struct.uz_dq_t* byval %%ab), !dbg !6 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_99_count);
  llvm_cbe_output = uz_clarke_inverse_transformation(llvm_cbe_ab);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_100_count);
  llvm_cbe_tmp__57 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = getelementptr inbounds %%struct.uz_dq_t* %%output, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_101_count);
  llvm_cbe_tmp__58 = (float *)(&llvm_cbe_output.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = load float* %%19, align 4, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_102_count);
  llvm_cbe_tmp__59 = (float )*llvm_cbe_tmp__58;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__59, *(int*)(&llvm_cbe_tmp__59));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%20, float* %%18, align 4, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_103_count);
  *llvm_cbe_tmp__57 = llvm_cbe_tmp__59;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_104_count);
  llvm_cbe_tmp__60 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = getelementptr inbounds %%struct.uz_dq_t* %%output, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_105_count);
  llvm_cbe_tmp__61 = (float *)(&llvm_cbe_output.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = load float* %%22, align 4, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_106_count);
  llvm_cbe_tmp__62 = (float )*llvm_cbe_tmp__61;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__62, *(int*)(&llvm_cbe_tmp__62));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%23, float* %%21, align 4, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_107_count);
  *llvm_cbe_tmp__60 = llvm_cbe_tmp__62;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__63 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = getelementptr inbounds %%struct.uz_dq_t* %%output, i64 0, i32 2, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_109_count);
  llvm_cbe_tmp__64 = (float *)(&llvm_cbe_output.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = load float* %%25, align 4, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_110_count);
  llvm_cbe_tmp__65 = (float )*llvm_cbe_tmp__64;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__65, *(int*)(&llvm_cbe_tmp__65));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%26, float* %%24, align 4, !dbg !7 for 0x%I64xth hint within @uz_dq_inverse_transformation  --> \n", ++aesl_llvm_cbe_111_count);
  *llvm_cbe_tmp__63 = llvm_cbe_tmp__65;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE)
    printf("\n END @uz_dq_inverse_transformation }\n"); 
  return StructReturn;
}


l_struct_OC_uz_dq_t uz_clarke_inverse_transformation(l_struct_OC_uz_dq_t llvm_cbe_input) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  float *llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  float llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  float *llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  float llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  float llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  float llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  float *llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  float llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  float llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  float llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  float llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  float llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  float llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  float llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  float *llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  float *llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  float *llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_clarke_inverse_transformation\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.uz_dq_t* %%input, i64 0, i32 0, !dbg !5 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__66 = (float *)(&llvm_cbe_input.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = load float* %%1, align 4, !dbg !5 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__67 = (float )*llvm_cbe_tmp__66;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__67, *(int*)(&llvm_cbe_tmp__67));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.uz_dq_t* %%input, i64 0, i32 2, !dbg !5 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_116_count);
  llvm_cbe_tmp__68 = (float *)(&llvm_cbe_input.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load float* %%3, align 4, !dbg !5 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_117_count);
  llvm_cbe_tmp__69 = (float )*llvm_cbe_tmp__68;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__69, *(int*)(&llvm_cbe_tmp__69));
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = fadd float %%2, %%4, !dbg !5 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_118_count);
  llvm_cbe_tmp__70 = (float )((float )(llvm_cbe_tmp__67 + llvm_cbe_tmp__69));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__70, *(int*)(&llvm_cbe_tmp__70));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = fmul float %%2, -5.000000e-01, !dbg !5 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_120_count);
  llvm_cbe_tmp__71 = (float )((float )(llvm_cbe_tmp__67 * -0x1p-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__71, *(int*)(&llvm_cbe_tmp__71));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds %%struct.uz_dq_t* %%input, i64 0, i32 1, !dbg !5 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_121_count);
  llvm_cbe_tmp__72 = (float *)(&llvm_cbe_input.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load float* %%7, align 4, !dbg !5 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_122_count);
  llvm_cbe_tmp__73 = (float )*llvm_cbe_tmp__72;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__73, *(int*)(&llvm_cbe_tmp__73));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = fmul float %%8, 0x3FEBB67AE0000000, !dbg !6 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_123_count);
  llvm_cbe_tmp__74 = (float )((float )(llvm_cbe_tmp__73 * 0x1.bb67aep-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__74, *(int*)(&llvm_cbe_tmp__74));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = fadd float %%6, %%9, !dbg !6 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__75 = (float )((float )(llvm_cbe_tmp__71 + llvm_cbe_tmp__74));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__75, *(int*)(&llvm_cbe_tmp__75));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = fadd float %%10, %%4, !dbg !6 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__76 = (float )((float )(llvm_cbe_tmp__75 + llvm_cbe_tmp__69));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__76, *(int*)(&llvm_cbe_tmp__76));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = fmul float %%8, 0xBFEBB67AE0000000, !dbg !6 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_127_count);
  llvm_cbe_tmp__77 = (float )((float )(llvm_cbe_tmp__73 * -0x1.bb67aep-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__77, *(int*)(&llvm_cbe_tmp__77));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = fadd float %%6, %%12, !dbg !6 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__78 = (float )((float )(llvm_cbe_tmp__71 + llvm_cbe_tmp__77));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__78, *(int*)(&llvm_cbe_tmp__78));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = fadd float %%13, %%4, !dbg !6 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_129_count);
  llvm_cbe_tmp__79 = (float )((float )(llvm_cbe_tmp__78 + llvm_cbe_tmp__69));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__79, *(int*)(&llvm_cbe_tmp__79));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__80 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%5, float* %%15, align 4, !dbg !7 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_132_count);
  *llvm_cbe_tmp__80 = llvm_cbe_tmp__70;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__70);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__81 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%11, float* %%16, align 4, !dbg !7 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_134_count);
  *llvm_cbe_tmp__81 = llvm_cbe_tmp__76;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__76);
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !7 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_135_count);
  llvm_cbe_tmp__82 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%14, float* %%17, align 4, !dbg !7 for 0x%I64xth hint within @uz_clarke_inverse_transformation  --> \n", ++aesl_llvm_cbe_136_count);
  *llvm_cbe_tmp__82 = llvm_cbe_tmp__79;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__79);
if (AESL_DEBUG_TRACE)
    printf("\n END @uz_clarke_inverse_transformation }\n"); 
  return StructReturn;
}

