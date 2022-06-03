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
l_struct_OC_uz_dq_t uz_FOC_SpaceVector_Limitation(l_struct_OC_uz_dq_t llvm_cbe_u_input_Volts, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, bool *llvm_cbe_ext_clamping);
float uz_signals_get_sign_of_value(float );
static l_struct_OC_uz_dq_t aesl_internal_uz_limit_dq_prio_d_axis(float llvm_cbe_u_input_Volts_2e_0, float llvm_cbe_u_input_Volts_2e_1, float llvm_cbe_u_input_Volts_2e_2, float llvm_cbe_U_SV_max);
static l_struct_OC_uz_dq_t aesl_internal_uz_limit_dq_prio_q_axis(float llvm_cbe_u_input_Volts_2e_0, float llvm_cbe_u_input_Volts_2e_1, float llvm_cbe_u_input_Volts_2e_2, float llvm_cbe_U_SV_max);
float uz_FOC_SpaceVector_Limitation_d(l_struct_OC_uz_dq_t llvm_cbe_u_input_Volts, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, bool *llvm_cbe_ext_clamping);
float uz_FOC_SpaceVector_Limitation_q(l_struct_OC_uz_dq_t llvm_cbe_u_input_Volts, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, bool *llvm_cbe_ext_clamping);
float fabsf(float );


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

l_struct_OC_uz_dq_t uz_FOC_SpaceVector_Limitation(l_struct_OC_uz_dq_t llvm_cbe_u_input_Volts, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, bool *llvm_cbe_ext_clamping) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_tmp__1;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_tmp__2;    /* Address-exposed local */
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
  float llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  float *llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  float llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_pow2_count = 0;
  float llvm_cbe_pow2;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  float *llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  float llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_pow24_count = 0;
  float llvm_cbe_pow24;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  float llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  float llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  float llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  float *llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  float llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  float llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_2_count = 0;
  float *llvm_cbe_u_input_Volts_2e_2;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_2_2e_val_count = 0;
  float llvm_cbe_u_input_Volts_2e_2_2e_val;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  float *llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  float llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  float *llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  float llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  float *llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  float llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_23_count = 0;
  float *llvm_cbe_u_input_Volts_2e_23;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_23_2e_val_count = 0;
  float llvm_cbe_u_input_Volts_2e_23_2e_val;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  float *llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  float llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  float *llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  float llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  float *llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  float llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  float llvm_cbe_tmp__26;
  float llvm_cbe_tmp__26__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  float llvm_cbe_tmp__27;
  float llvm_cbe_tmp__27__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  float llvm_cbe_tmp__28;
  float llvm_cbe_tmp__28__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  float *llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  float *llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  float *llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_FOC_SpaceVector_Limitation\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = fdiv float %%V_dc_volts, 0x3FFBB67AE0000000, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_15_count);
  llvm_cbe_tmp__3 = (float )((float )(llvm_cbe_V_dc_volts / 0x1.bb67aep0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__3, *(int*)(&llvm_cbe_tmp__3));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_20_count);
  llvm_cbe_tmp__4 = (float *)(&llvm_cbe_u_input_Volts.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load float* %%4, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_21_count);
  llvm_cbe_tmp__5 = (float )*llvm_cbe_tmp__4;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__5, *(int*)(&llvm_cbe_tmp__5));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow2 = fmul float %%5, %%5, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_pow2_count);
  llvm_cbe_pow2 = (float )((float )(llvm_cbe_tmp__5 * llvm_cbe_tmp__5));
if (AESL_DEBUG_TRACE)
printf("\npow2 = %f,  0x%x\n", llvm_cbe_pow2, *(int*)(&llvm_cbe_pow2));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32 1, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_22_count);
  llvm_cbe_tmp__6 = (float *)(&llvm_cbe_u_input_Volts.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load float* %%6, align 4, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_23_count);
  llvm_cbe_tmp__7 = (float )*llvm_cbe_tmp__6;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__7, *(int*)(&llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow24 = fmul float %%7, %%7, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_pow24_count);
  llvm_cbe_pow24 = (float )((float )(llvm_cbe_tmp__7 * llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\npow24 = %f,  0x%x\n", llvm_cbe_pow24, *(int*)(&llvm_cbe_pow24));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = fadd float %%pow2, %%pow24, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_24_count);
  llvm_cbe_tmp__8 = (float )((float )(llvm_cbe_pow2 + llvm_cbe_pow24));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__8, *(int*)(&llvm_cbe_tmp__8));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = call float @sqrtf(float %%8) nounwind readnone, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_25_count);
  llvm_cbe_tmp__9 = (float )sqrtf(llvm_cbe_tmp__8);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__8, *(int*)(&llvm_cbe_tmp__8));
printf("\nReturn  = %f",llvm_cbe_tmp__9);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = call float @uz_signals_get_sign_of_value(float %%omega_el_rad_per_sec) nounwind, !dbg !5 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_28_count);
  llvm_cbe_tmp__10 = (float )uz_signals_get_sign_of_value(llvm_cbe_omega_el_rad_per_sec);
if (AESL_DEBUG_TRACE) {
printf("\nArgument omega_el_rad_per_sec = %f,  0x%x",llvm_cbe_omega_el_rad_per_sec, *(int*)(&llvm_cbe_omega_el_rad_per_sec));
printf("\nReturn  = %f",llvm_cbe_tmp__10);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32 1, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__11 = (float *)(&llvm_cbe_i_actual_Ampere.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = load float* %%11, align 4, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_30_count);
  llvm_cbe_tmp__12 = (float )*llvm_cbe_tmp__11;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__12, *(int*)(&llvm_cbe_tmp__12));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = call float @uz_signals_get_sign_of_value(float %%12) nounwind, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__13 = (float )uz_signals_get_sign_of_value(llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__12, *(int*)(&llvm_cbe_tmp__12));
printf("\nReturn  = %f",llvm_cbe_tmp__13);
}
  if ((llvm_fcmp_ogt(llvm_cbe_tmp__9, llvm_cbe_tmp__3))) {
    goto llvm_cbe_tmp__32;
  } else {
    goto llvm_cbe_tmp__33;
  }

llvm_cbe_tmp__32:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 true, i1* %%ext_clamping, align 1, !dbg !5 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_37_count);
  *llvm_cbe_ext_clamping = ((1) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1);
  if ((llvm_fcmp_oeq(llvm_cbe_tmp__10, llvm_cbe_tmp__13))) {
    goto llvm_cbe_tmp__34;
  } else {
    goto llvm_cbe_tmp__35;
  }

llvm_cbe_tmp__34:
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.2 = getelementptr %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_2_count);
  llvm_cbe_u_input_Volts_2e_2 = (float *)(&llvm_cbe_u_input_Volts.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.2.val = load float* %%u_input_Volts.2, align  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_2_2e_val_count);
  llvm_cbe_u_input_Volts_2e_2_2e_val = (float )*llvm_cbe_u_input_Volts_2e_2;
if (AESL_DEBUG_TRACE)
printf("\nu_input_Volts.2.val = %f,  0x%x\n", llvm_cbe_u_input_Volts_2e_2_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_2_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  call fastcc void @aesl_internal_uz_limit_dq_prio_d_axis(%%struct.uz_dq_t* sret %%1, float %%5, float %%7, float %%u_input_Volts.2.val, float %%3 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_39_count);
  llvm_cbe_tmp__1 = aesl_internal_uz_limit_dq_prio_d_axis(llvm_cbe_tmp__5, llvm_cbe_tmp__7, llvm_cbe_u_input_Volts_2e_2_2e_val, llvm_cbe_tmp__3);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__5, *(int*)(&llvm_cbe_tmp__5));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__7, *(int*)(&llvm_cbe_tmp__7));
printf("\nArgument u_input_Volts.2.val = %f,  0x%x",llvm_cbe_u_input_Volts_2e_2_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_2_2e_val));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__3, *(int*)(&llvm_cbe_tmp__3));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_40_count);
  llvm_cbe_tmp__14 = (float *)(&llvm_cbe_tmp__1.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = load float* %%18, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_41_count);
  llvm_cbe_tmp__15 = (float )*llvm_cbe_tmp__14;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__15, *(int*)(&llvm_cbe_tmp__15));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_43_count);
  llvm_cbe_tmp__16 = (float *)(&llvm_cbe_tmp__1.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = load float* %%20, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_44_count);
  llvm_cbe_tmp__17 = (float )*llvm_cbe_tmp__16;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__17, *(int*)(&llvm_cbe_tmp__17));
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 2, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__18 = (float *)(&llvm_cbe_tmp__1.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = load float* %%22, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__19 = (float )*llvm_cbe_tmp__18;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__19, *(int*)(&llvm_cbe_tmp__19));
  llvm_cbe_tmp__26__PHI_TEMPORARY = (float )llvm_cbe_tmp__19;   /* for PHI node */
  llvm_cbe_tmp__27__PHI_TEMPORARY = (float )llvm_cbe_tmp__17;   /* for PHI node */
  llvm_cbe_tmp__28__PHI_TEMPORARY = (float )llvm_cbe_tmp__15;   /* for PHI node */
  goto llvm_cbe_tmp__36;

llvm_cbe_tmp__35:
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.23 = getelementptr %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_23_count);
  llvm_cbe_u_input_Volts_2e_23 = (float *)(&llvm_cbe_u_input_Volts.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.23.val = load float* %%u_input_Volts.23, align  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_23_2e_val_count);
  llvm_cbe_u_input_Volts_2e_23_2e_val = (float )*llvm_cbe_u_input_Volts_2e_23;
if (AESL_DEBUG_TRACE)
printf("\nu_input_Volts.23.val = %f,  0x%x\n", llvm_cbe_u_input_Volts_2e_23_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_23_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  call fastcc void @aesl_internal_uz_limit_dq_prio_q_axis(%%struct.uz_dq_t* sret %%2, float %%5, float %%7, float %%u_input_Volts.23.val, float %%3 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_50_count);
  llvm_cbe_tmp__2 = aesl_internal_uz_limit_dq_prio_q_axis(llvm_cbe_tmp__5, llvm_cbe_tmp__7, llvm_cbe_u_input_Volts_2e_23_2e_val, llvm_cbe_tmp__3);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__5, *(int*)(&llvm_cbe_tmp__5));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__7, *(int*)(&llvm_cbe_tmp__7));
printf("\nArgument u_input_Volts.23.val = %f,  0x%x",llvm_cbe_u_input_Volts_2e_23_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_23_2e_val));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__3, *(int*)(&llvm_cbe_tmp__3));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = getelementptr inbounds %%struct.uz_dq_t* %%2, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_51_count);
  llvm_cbe_tmp__20 = (float *)(&llvm_cbe_tmp__2.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = load float* %%25, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_52_count);
  llvm_cbe_tmp__21 = (float )*llvm_cbe_tmp__20;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__21, *(int*)(&llvm_cbe_tmp__21));
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = getelementptr inbounds %%struct.uz_dq_t* %%2, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_54_count);
  llvm_cbe_tmp__22 = (float *)(&llvm_cbe_tmp__2.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = load float* %%27, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_55_count);
  llvm_cbe_tmp__23 = (float )*llvm_cbe_tmp__22;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__23, *(int*)(&llvm_cbe_tmp__23));
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = getelementptr inbounds %%struct.uz_dq_t* %%2, i64 0, i32 2, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_57_count);
  llvm_cbe_tmp__24 = (float *)(&llvm_cbe_tmp__2.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = load float* %%29, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_58_count);
  llvm_cbe_tmp__25 = (float )*llvm_cbe_tmp__24;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__25, *(int*)(&llvm_cbe_tmp__25));
  llvm_cbe_tmp__26__PHI_TEMPORARY = (float )llvm_cbe_tmp__25;   /* for PHI node */
  llvm_cbe_tmp__27__PHI_TEMPORARY = (float )llvm_cbe_tmp__23;   /* for PHI node */
  llvm_cbe_tmp__28__PHI_TEMPORARY = (float )llvm_cbe_tmp__21;   /* for PHI node */
  goto llvm_cbe_tmp__36;

llvm_cbe_tmp__33:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%ext_clamping, align 1, !dbg !5 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_63_count);
  *llvm_cbe_ext_clamping = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
  llvm_cbe_tmp__26__PHI_TEMPORARY = (float )0x0p0;   /* for PHI node */
  llvm_cbe_tmp__27__PHI_TEMPORARY = (float )llvm_cbe_tmp__7;   /* for PHI node */
  llvm_cbe_tmp__28__PHI_TEMPORARY = (float )llvm_cbe_tmp__5;   /* for PHI node */
  goto llvm_cbe_tmp__36;

llvm_cbe_tmp__36:
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = phi float [ 0.000000e+00, %%31 ], [ %%30, %%24 ], [ %%23, %%17  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_65_count);
  llvm_cbe_tmp__26 = (float )llvm_cbe_tmp__26__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__26);
printf("\n = %f",0x0p0);
printf("\n = %f",llvm_cbe_tmp__25);
printf("\n = %f",llvm_cbe_tmp__19);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = phi float [ %%7, %%31 ], [ %%28, %%24 ], [ %%21, %%17  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_66_count);
  llvm_cbe_tmp__27 = (float )llvm_cbe_tmp__27__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__27);
printf("\n = %f",llvm_cbe_tmp__7);
printf("\n = %f",llvm_cbe_tmp__23);
printf("\n = %f",llvm_cbe_tmp__17);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = phi float [ %%5, %%31 ], [ %%26, %%24 ], [ %%19, %%17  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_67_count);
  llvm_cbe_tmp__28 = (float )llvm_cbe_tmp__28__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__28);
printf("\n = %f",llvm_cbe_tmp__5);
printf("\n = %f",llvm_cbe_tmp__21);
printf("\n = %f",llvm_cbe_tmp__15);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_68_count);
  llvm_cbe_tmp__29 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%35, float* %%36, align 4, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_69_count);
  *llvm_cbe_tmp__29 = llvm_cbe_tmp__28;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_70_count);
  llvm_cbe_tmp__30 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%34, float* %%37, align 4, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_71_count);
  *llvm_cbe_tmp__30 = llvm_cbe_tmp__27;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_72_count);
  llvm_cbe_tmp__31 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%33, float* %%38, align 4, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation  --> \n", ++aesl_llvm_cbe_73_count);
  *llvm_cbe_tmp__31 = llvm_cbe_tmp__26;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE)
    printf("\n END @uz_FOC_SpaceVector_Limitation }\n"); 
  return StructReturn;
}


static l_struct_OC_uz_dq_t aesl_internal_uz_limit_dq_prio_d_axis(float llvm_cbe_u_input_Volts_2e_0, float llvm_cbe_u_input_Volts_2e_1, float llvm_cbe_u_input_Volts_2e_2, float llvm_cbe_U_SV_max) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  float llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  float llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  float llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  float llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  float llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  float llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_pow2_count = 0;
  float llvm_cbe_pow2;
  static  unsigned long long aesl_llvm_cbe_pow24_count = 0;
  float llvm_cbe_pow24;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  float llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  float llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  float llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  float llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_pow25_count = 0;
  float llvm_cbe_pow25;
  static  unsigned long long aesl_llvm_cbe_pow26_count = 0;
  float llvm_cbe_pow26;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  float llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  float llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  float llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  float llvm_cbe_tmp__50;
  float llvm_cbe_tmp__50__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  float llvm_cbe_tmp__51;
  float llvm_cbe_tmp__51__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  float *llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  float *llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  float *llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @aesl_internal_uz_limit_dq_prio_d_axis\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call float @fabsf(float %%u_input_Volts.0) nounwind, !dbg !5 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_86_count);
  llvm_cbe_tmp__37 = (float ) /*tail*/ fabsf(llvm_cbe_u_input_Volts_2e_0);
if (AESL_DEBUG_TRACE) {
printf("\nArgument u_input_Volts.0 = %f,  0x%x",llvm_cbe_u_input_Volts_2e_0, *(int*)(&llvm_cbe_u_input_Volts_2e_0));
printf("\nReturn  = %f",llvm_cbe_tmp__37);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = fmul float %%U_SV_max, 0x3FEE666660000000, !dbg !5 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__38 = (float )((float )(llvm_cbe_U_SV_max * 0x1.e66666p-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__38, *(int*)(&llvm_cbe_tmp__38));
  if ((llvm_fcmp_ogt(llvm_cbe_tmp__37, llvm_cbe_tmp__38))) {
    goto llvm_cbe_tmp__55;
  } else {
    goto llvm_cbe_tmp__56;
  }

llvm_cbe_tmp__55:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = tail call float @uz_signals_get_sign_of_value(float %%u_input_Volts.0) nounwind, !dbg !5 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_90_count);
  llvm_cbe_tmp__39 = (float ) /*tail*/ uz_signals_get_sign_of_value(llvm_cbe_u_input_Volts_2e_0);
if (AESL_DEBUG_TRACE) {
printf("\nArgument u_input_Volts.0 = %f,  0x%x",llvm_cbe_u_input_Volts_2e_0, *(int*)(&llvm_cbe_u_input_Volts_2e_0));
printf("\nReturn  = %f",llvm_cbe_tmp__39);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = fmul float %%5, 0x3FEE666660000000, !dbg !5 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_91_count);
  llvm_cbe_tmp__40 = (float )((float )(llvm_cbe_tmp__39 * 0x1.e66666p-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__40, *(int*)(&llvm_cbe_tmp__40));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = fmul float %%6, %%U_SV_max, !dbg !5 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_92_count);
  llvm_cbe_tmp__41 = (float )((float )(llvm_cbe_tmp__40 * llvm_cbe_U_SV_max));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__41, *(int*)(&llvm_cbe_tmp__41));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = tail call float @uz_signals_get_sign_of_value(float %%u_input_Volts.1) nounwind, !dbg !6 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_94_count);
  llvm_cbe_tmp__42 = (float ) /*tail*/ uz_signals_get_sign_of_value(llvm_cbe_u_input_Volts_2e_1);
if (AESL_DEBUG_TRACE) {
printf("\nArgument u_input_Volts.1 = %f,  0x%x",llvm_cbe_u_input_Volts_2e_1, *(int*)(&llvm_cbe_u_input_Volts_2e_1));
printf("\nReturn  = %f",llvm_cbe_tmp__42);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%pow2 = fmul float %%U_SV_max, %%U_SV_max, !dbg !6 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_pow2_count);
  llvm_cbe_pow2 = (float )((float )(llvm_cbe_U_SV_max * llvm_cbe_U_SV_max));
if (AESL_DEBUG_TRACE)
printf("\npow2 = %f,  0x%x\n", llvm_cbe_pow2, *(int*)(&llvm_cbe_pow2));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow24 = fmul float %%7, %%7, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_pow24_count);
  llvm_cbe_pow24 = (float )((float )(llvm_cbe_tmp__41 * llvm_cbe_tmp__41));
if (AESL_DEBUG_TRACE)
printf("\npow24 = %f,  0x%x\n", llvm_cbe_pow24, *(int*)(&llvm_cbe_pow24));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = fsub float %%pow2, %%pow24, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_95_count);
  llvm_cbe_tmp__43 = (float )((float )(llvm_cbe_pow2 - llvm_cbe_pow24));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__43, *(int*)(&llvm_cbe_tmp__43));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = tail call float @sqrtf(float %%9) nounwind readnone, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_96_count);
  llvm_cbe_tmp__44 = (float ) /*tail*/ sqrtf(llvm_cbe_tmp__43);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__43, *(int*)(&llvm_cbe_tmp__43));
printf("\nReturn  = %f",llvm_cbe_tmp__44);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = fmul float %%8, %%10, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_97_count);
  llvm_cbe_tmp__45 = (float )((float )(llvm_cbe_tmp__42 * llvm_cbe_tmp__44));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__45, *(int*)(&llvm_cbe_tmp__45));
  llvm_cbe_tmp__50__PHI_TEMPORARY = (float )llvm_cbe_tmp__45;   /* for PHI node */
  llvm_cbe_tmp__51__PHI_TEMPORARY = (float )llvm_cbe_tmp__41;   /* for PHI node */
  goto llvm_cbe_tmp__57;

llvm_cbe_tmp__56:
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = tail call float @uz_signals_get_sign_of_value(float %%u_input_Volts.1) nounwind, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_101_count);
  llvm_cbe_tmp__46 = (float ) /*tail*/ uz_signals_get_sign_of_value(llvm_cbe_u_input_Volts_2e_1);
if (AESL_DEBUG_TRACE) {
printf("\nArgument u_input_Volts.1 = %f,  0x%x",llvm_cbe_u_input_Volts_2e_1, *(int*)(&llvm_cbe_u_input_Volts_2e_1));
printf("\nReturn  = %f",llvm_cbe_tmp__46);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%pow25 = fmul float %%U_SV_max, %%U_SV_max, !dbg !6 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_pow25_count);
  llvm_cbe_pow25 = (float )((float )(llvm_cbe_U_SV_max * llvm_cbe_U_SV_max));
if (AESL_DEBUG_TRACE)
printf("\npow25 = %f,  0x%x\n", llvm_cbe_pow25, *(int*)(&llvm_cbe_pow25));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow26 = fmul float %%u_input_Volts.0, %%u_input_Volts.0, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_pow26_count);
  llvm_cbe_pow26 = (float )((float )(llvm_cbe_u_input_Volts_2e_0 * llvm_cbe_u_input_Volts_2e_0));
if (AESL_DEBUG_TRACE)
printf("\npow26 = %f,  0x%x\n", llvm_cbe_pow26, *(int*)(&llvm_cbe_pow26));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = fsub float %%pow25, %%pow26, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_102_count);
  llvm_cbe_tmp__47 = (float )((float )(llvm_cbe_pow25 - llvm_cbe_pow26));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__47, *(int*)(&llvm_cbe_tmp__47));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = tail call float @sqrtf(float %%14) nounwind readnone, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_103_count);
  llvm_cbe_tmp__48 = (float ) /*tail*/ sqrtf(llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__47, *(int*)(&llvm_cbe_tmp__47));
printf("\nReturn  = %f",llvm_cbe_tmp__48);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = fmul float %%13, %%15, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_104_count);
  llvm_cbe_tmp__49 = (float )((float )(llvm_cbe_tmp__46 * llvm_cbe_tmp__48));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__49, *(int*)(&llvm_cbe_tmp__49));
  llvm_cbe_tmp__50__PHI_TEMPORARY = (float )llvm_cbe_tmp__49;   /* for PHI node */
  llvm_cbe_tmp__51__PHI_TEMPORARY = (float )llvm_cbe_u_input_Volts_2e_0;   /* for PHI node */
  goto llvm_cbe_tmp__57;

llvm_cbe_tmp__57:
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = phi float [ %%16, %%12 ], [ %%11, %%4  for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_107_count);
  llvm_cbe_tmp__50 = (float )llvm_cbe_tmp__50__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__50);
printf("\n = %f",llvm_cbe_tmp__49);
printf("\n = %f",llvm_cbe_tmp__45);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = phi float [ %%u_input_Volts.0, %%12 ], [ %%7, %%4  for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__51 = (float )llvm_cbe_tmp__51__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__51);
printf("\nu_input_Volts.0 = %f",llvm_cbe_u_input_Volts_2e_0);
printf("\n = %f",llvm_cbe_tmp__41);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_109_count);
  llvm_cbe_tmp__52 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%19, float* %%20, align 4, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_110_count);
  *llvm_cbe_tmp__52 = llvm_cbe_tmp__51;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_111_count);
  llvm_cbe_tmp__53 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%18, float* %%21, align 4, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_112_count);
  *llvm_cbe_tmp__53 = llvm_cbe_tmp__50;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__50);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_113_count);
  llvm_cbe_tmp__54 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* %%22, align 4, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_d_axis  --> \n", ++aesl_llvm_cbe_114_count);
  *llvm_cbe_tmp__54 = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
if (AESL_DEBUG_TRACE)
    printf("\n END @aesl_internal_uz_limit_dq_prio_d_axis }\n"); 
  return StructReturn;
}


static l_struct_OC_uz_dq_t aesl_internal_uz_limit_dq_prio_q_axis(float llvm_cbe_u_input_Volts_2e_0, float llvm_cbe_u_input_Volts_2e_1, float llvm_cbe_u_input_Volts_2e_2, float llvm_cbe_U_SV_max) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
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
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  float llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  float llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  float llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  float llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  float llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  float llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_pow2_count = 0;
  float llvm_cbe_pow2;
  static  unsigned long long aesl_llvm_cbe_pow24_count = 0;
  float llvm_cbe_pow24;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  float llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  float llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  float llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  float llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_pow25_count = 0;
  float llvm_cbe_pow25;
  static  unsigned long long aesl_llvm_cbe_pow26_count = 0;
  float llvm_cbe_pow26;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  float llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  float llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  float llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  float llvm_cbe_tmp__71;
  float llvm_cbe_tmp__71__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  float llvm_cbe_tmp__72;
  float llvm_cbe_tmp__72__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  float *llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  float *llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  float *llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @aesl_internal_uz_limit_dq_prio_q_axis\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call float @fabsf(float %%u_input_Volts.1) nounwind, !dbg !5 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_127_count);
  llvm_cbe_tmp__58 = (float ) /*tail*/ fabsf(llvm_cbe_u_input_Volts_2e_1);
if (AESL_DEBUG_TRACE) {
printf("\nArgument u_input_Volts.1 = %f,  0x%x",llvm_cbe_u_input_Volts_2e_1, *(int*)(&llvm_cbe_u_input_Volts_2e_1));
printf("\nReturn  = %f",llvm_cbe_tmp__58);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = fmul float %%U_SV_max, 0x3FEE666660000000, !dbg !5 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__59 = (float )((float )(llvm_cbe_U_SV_max * 0x1.e66666p-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__59, *(int*)(&llvm_cbe_tmp__59));
  if ((llvm_fcmp_ogt(llvm_cbe_tmp__58, llvm_cbe_tmp__59))) {
    goto llvm_cbe_tmp__76;
  } else {
    goto llvm_cbe_tmp__77;
  }

llvm_cbe_tmp__76:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = tail call float @uz_signals_get_sign_of_value(float %%u_input_Volts.1) nounwind, !dbg !5 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__60 = (float ) /*tail*/ uz_signals_get_sign_of_value(llvm_cbe_u_input_Volts_2e_1);
if (AESL_DEBUG_TRACE) {
printf("\nArgument u_input_Volts.1 = %f,  0x%x",llvm_cbe_u_input_Volts_2e_1, *(int*)(&llvm_cbe_u_input_Volts_2e_1));
printf("\nReturn  = %f",llvm_cbe_tmp__60);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = fmul float %%5, 0x3FEE666660000000, !dbg !5 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__61 = (float )((float )(llvm_cbe_tmp__60 * 0x1.e66666p-1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__61, *(int*)(&llvm_cbe_tmp__61));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = fmul float %%6, %%U_SV_max, !dbg !5 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__62 = (float )((float )(llvm_cbe_tmp__61 * llvm_cbe_U_SV_max));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__62, *(int*)(&llvm_cbe_tmp__62));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = tail call float @uz_signals_get_sign_of_value(float %%u_input_Volts.0) nounwind, !dbg !6 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_135_count);
  llvm_cbe_tmp__63 = (float ) /*tail*/ uz_signals_get_sign_of_value(llvm_cbe_u_input_Volts_2e_0);
if (AESL_DEBUG_TRACE) {
printf("\nArgument u_input_Volts.0 = %f,  0x%x",llvm_cbe_u_input_Volts_2e_0, *(int*)(&llvm_cbe_u_input_Volts_2e_0));
printf("\nReturn  = %f",llvm_cbe_tmp__63);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%pow2 = fmul float %%U_SV_max, %%U_SV_max, !dbg !6 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_pow2_count);
  llvm_cbe_pow2 = (float )((float )(llvm_cbe_U_SV_max * llvm_cbe_U_SV_max));
if (AESL_DEBUG_TRACE)
printf("\npow2 = %f,  0x%x\n", llvm_cbe_pow2, *(int*)(&llvm_cbe_pow2));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow24 = fmul float %%7, %%7, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_pow24_count);
  llvm_cbe_pow24 = (float )((float )(llvm_cbe_tmp__62 * llvm_cbe_tmp__62));
if (AESL_DEBUG_TRACE)
printf("\npow24 = %f,  0x%x\n", llvm_cbe_pow24, *(int*)(&llvm_cbe_pow24));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = fsub float %%pow2, %%pow24, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_136_count);
  llvm_cbe_tmp__64 = (float )((float )(llvm_cbe_pow2 - llvm_cbe_pow24));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__64, *(int*)(&llvm_cbe_tmp__64));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = tail call float @sqrtf(float %%9) nounwind readnone, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_137_count);
  llvm_cbe_tmp__65 = (float ) /*tail*/ sqrtf(llvm_cbe_tmp__64);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__64, *(int*)(&llvm_cbe_tmp__64));
printf("\nReturn  = %f",llvm_cbe_tmp__65);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = fmul float %%8, %%10, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_138_count);
  llvm_cbe_tmp__66 = (float )((float )(llvm_cbe_tmp__63 * llvm_cbe_tmp__65));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__66, *(int*)(&llvm_cbe_tmp__66));
  llvm_cbe_tmp__71__PHI_TEMPORARY = (float )llvm_cbe_tmp__62;   /* for PHI node */
  llvm_cbe_tmp__72__PHI_TEMPORARY = (float )llvm_cbe_tmp__66;   /* for PHI node */
  goto llvm_cbe_tmp__78;

llvm_cbe_tmp__77:
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = tail call float @uz_signals_get_sign_of_value(float %%u_input_Volts.0) nounwind, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_142_count);
  llvm_cbe_tmp__67 = (float ) /*tail*/ uz_signals_get_sign_of_value(llvm_cbe_u_input_Volts_2e_0);
if (AESL_DEBUG_TRACE) {
printf("\nArgument u_input_Volts.0 = %f,  0x%x",llvm_cbe_u_input_Volts_2e_0, *(int*)(&llvm_cbe_u_input_Volts_2e_0));
printf("\nReturn  = %f",llvm_cbe_tmp__67);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%pow25 = fmul float %%U_SV_max, %%U_SV_max, !dbg !6 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_pow25_count);
  llvm_cbe_pow25 = (float )((float )(llvm_cbe_U_SV_max * llvm_cbe_U_SV_max));
if (AESL_DEBUG_TRACE)
printf("\npow25 = %f,  0x%x\n", llvm_cbe_pow25, *(int*)(&llvm_cbe_pow25));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow26 = fmul float %%u_input_Volts.1, %%u_input_Volts.1, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_pow26_count);
  llvm_cbe_pow26 = (float )((float )(llvm_cbe_u_input_Volts_2e_1 * llvm_cbe_u_input_Volts_2e_1));
if (AESL_DEBUG_TRACE)
printf("\npow26 = %f,  0x%x\n", llvm_cbe_pow26, *(int*)(&llvm_cbe_pow26));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = fsub float %%pow25, %%pow26, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_143_count);
  llvm_cbe_tmp__68 = (float )((float )(llvm_cbe_pow25 - llvm_cbe_pow26));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__68, *(int*)(&llvm_cbe_tmp__68));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = tail call float @sqrtf(float %%14) nounwind readnone, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_144_count);
  llvm_cbe_tmp__69 = (float ) /*tail*/ sqrtf(llvm_cbe_tmp__68);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__68, *(int*)(&llvm_cbe_tmp__68));
printf("\nReturn  = %f",llvm_cbe_tmp__69);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = fmul float %%13, %%15, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_145_count);
  llvm_cbe_tmp__70 = (float )((float )(llvm_cbe_tmp__67 * llvm_cbe_tmp__69));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__70, *(int*)(&llvm_cbe_tmp__70));
  llvm_cbe_tmp__71__PHI_TEMPORARY = (float )llvm_cbe_u_input_Volts_2e_1;   /* for PHI node */
  llvm_cbe_tmp__72__PHI_TEMPORARY = (float )llvm_cbe_tmp__70;   /* for PHI node */
  goto llvm_cbe_tmp__78;

llvm_cbe_tmp__78:
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = phi float [ %%u_input_Volts.1, %%12 ], [ %%7, %%4  for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_148_count);
  llvm_cbe_tmp__71 = (float )llvm_cbe_tmp__71__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__71);
printf("\nu_input_Volts.1 = %f",llvm_cbe_u_input_Volts_2e_1);
printf("\n = %f",llvm_cbe_tmp__62);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = phi float [ %%16, %%12 ], [ %%11, %%4  for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_149_count);
  llvm_cbe_tmp__72 = (float )llvm_cbe_tmp__72__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__72);
printf("\n = %f",llvm_cbe_tmp__70);
printf("\n = %f",llvm_cbe_tmp__66);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__73 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%19, float* %%20, align 4, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_151_count);
  *llvm_cbe_tmp__73 = llvm_cbe_tmp__72;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__72);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_152_count);
  llvm_cbe_tmp__74 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%18, float* %%21, align 4, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_153_count);
  *llvm_cbe_tmp__74 = llvm_cbe_tmp__71;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__71);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_154_count);
  llvm_cbe_tmp__75 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* %%22, align 4, !dbg !7 for 0x%I64xth hint within @aesl_internal_uz_limit_dq_prio_q_axis  --> \n", ++aesl_llvm_cbe_155_count);
  *llvm_cbe_tmp__75 = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
if (AESL_DEBUG_TRACE)
    printf("\n END @aesl_internal_uz_limit_dq_prio_q_axis }\n"); 
  return StructReturn;
}


float uz_FOC_SpaceVector_Limitation_d(l_struct_OC_uz_dq_t llvm_cbe_u_input_Volts, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, bool *llvm_cbe_ext_clamping) {
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_tmp__79;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_tmp__80;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  float llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  float *llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  float llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_pow2_count = 0;
  float llvm_cbe_pow2;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  float *llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  float llvm_cbe_tmp__85;
  static  unsigned long long aesl_llvm_cbe_pow24_count = 0;
  float llvm_cbe_pow24;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  float llvm_cbe_tmp__86;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  float llvm_cbe_tmp__87;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  float llvm_cbe_tmp__88;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  float *llvm_cbe_tmp__89;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  float llvm_cbe_tmp__90;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  float llvm_cbe_tmp__91;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_2_count = 0;
  float *llvm_cbe_u_input_Volts_2e_2;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_2_2e_val_count = 0;
  float llvm_cbe_u_input_Volts_2e_2_2e_val;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  float *llvm_cbe_tmp__92;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  float llvm_cbe_tmp__93;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_23_count = 0;
  float *llvm_cbe_u_input_Volts_2e_23;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_23_2e_val_count = 0;
  float llvm_cbe_u_input_Volts_2e_23_2e_val;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  float *llvm_cbe_tmp__94;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  float llvm_cbe_tmp__95;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  float llvm_cbe_tmp__96;
  float llvm_cbe_tmp__96__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_FOC_SpaceVector_Limitation_d\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = fdiv float %%V_dc_volts, 0x3FFBB67AE0000000, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_171_count);
  llvm_cbe_tmp__81 = (float )((float )(llvm_cbe_V_dc_volts / 0x1.bb67aep0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__81, *(int*)(&llvm_cbe_tmp__81));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_176_count);
  llvm_cbe_tmp__82 = (float *)(&llvm_cbe_u_input_Volts.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load float* %%4, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_177_count);
  llvm_cbe_tmp__83 = (float )*llvm_cbe_tmp__82;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__83, *(int*)(&llvm_cbe_tmp__83));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow2 = fmul float %%5, %%5, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_pow2_count);
  llvm_cbe_pow2 = (float )((float )(llvm_cbe_tmp__83 * llvm_cbe_tmp__83));
if (AESL_DEBUG_TRACE)
printf("\npow2 = %f,  0x%x\n", llvm_cbe_pow2, *(int*)(&llvm_cbe_pow2));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32 1, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_178_count);
  llvm_cbe_tmp__84 = (float *)(&llvm_cbe_u_input_Volts.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load float* %%6, align 4, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_179_count);
  llvm_cbe_tmp__85 = (float )*llvm_cbe_tmp__84;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__85, *(int*)(&llvm_cbe_tmp__85));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow24 = fmul float %%7, %%7, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_pow24_count);
  llvm_cbe_pow24 = (float )((float )(llvm_cbe_tmp__85 * llvm_cbe_tmp__85));
if (AESL_DEBUG_TRACE)
printf("\npow24 = %f,  0x%x\n", llvm_cbe_pow24, *(int*)(&llvm_cbe_pow24));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = fadd float %%pow2, %%pow24, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_180_count);
  llvm_cbe_tmp__86 = (float )((float )(llvm_cbe_pow2 + llvm_cbe_pow24));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__86, *(int*)(&llvm_cbe_tmp__86));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = call float @sqrtf(float %%8) nounwind readnone, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_181_count);
  llvm_cbe_tmp__87 = (float )sqrtf(llvm_cbe_tmp__86);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__86, *(int*)(&llvm_cbe_tmp__86));
printf("\nReturn  = %f",llvm_cbe_tmp__87);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = call float @uz_signals_get_sign_of_value(float %%omega_el_rad_per_sec) nounwind, !dbg !5 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_184_count);
  llvm_cbe_tmp__88 = (float )uz_signals_get_sign_of_value(llvm_cbe_omega_el_rad_per_sec);
if (AESL_DEBUG_TRACE) {
printf("\nArgument omega_el_rad_per_sec = %f,  0x%x",llvm_cbe_omega_el_rad_per_sec, *(int*)(&llvm_cbe_omega_el_rad_per_sec));
printf("\nReturn  = %f",llvm_cbe_tmp__88);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32 1, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_185_count);
  llvm_cbe_tmp__89 = (float *)(&llvm_cbe_i_actual_Ampere.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = load float* %%11, align 4, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_186_count);
  llvm_cbe_tmp__90 = (float )*llvm_cbe_tmp__89;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__90, *(int*)(&llvm_cbe_tmp__90));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = call float @uz_signals_get_sign_of_value(float %%12) nounwind, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_187_count);
  llvm_cbe_tmp__91 = (float )uz_signals_get_sign_of_value(llvm_cbe_tmp__90);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__90, *(int*)(&llvm_cbe_tmp__90));
printf("\nReturn  = %f",llvm_cbe_tmp__91);
}
  if ((llvm_fcmp_ogt(llvm_cbe_tmp__87, llvm_cbe_tmp__81))) {
    goto llvm_cbe_tmp__97;
  } else {
    goto llvm_cbe_tmp__98;
  }

llvm_cbe_tmp__97:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 true, i1* %%ext_clamping, align 1, !dbg !5 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_193_count);
  *llvm_cbe_ext_clamping = ((1) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1);
  if ((llvm_fcmp_oeq(llvm_cbe_tmp__88, llvm_cbe_tmp__91))) {
    goto llvm_cbe_tmp__99;
  } else {
    goto llvm_cbe_tmp__100;
  }

llvm_cbe_tmp__99:
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.2 = getelementptr %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_2_count);
  llvm_cbe_u_input_Volts_2e_2 = (float *)(&llvm_cbe_u_input_Volts.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.2.val = load float* %%u_input_Volts.2, align  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_2_2e_val_count);
  llvm_cbe_u_input_Volts_2e_2_2e_val = (float )*llvm_cbe_u_input_Volts_2e_2;
if (AESL_DEBUG_TRACE)
printf("\nu_input_Volts.2.val = %f,  0x%x\n", llvm_cbe_u_input_Volts_2e_2_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_2_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  call fastcc void @aesl_internal_uz_limit_dq_prio_d_axis(%%struct.uz_dq_t* sret %%1, float %%5, float %%7, float %%u_input_Volts.2.val, float %%3 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_195_count);
  llvm_cbe_tmp__79 = aesl_internal_uz_limit_dq_prio_d_axis(llvm_cbe_tmp__83, llvm_cbe_tmp__85, llvm_cbe_u_input_Volts_2e_2_2e_val, llvm_cbe_tmp__81);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__83, *(int*)(&llvm_cbe_tmp__83));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__85, *(int*)(&llvm_cbe_tmp__85));
printf("\nArgument u_input_Volts.2.val = %f,  0x%x",llvm_cbe_u_input_Volts_2e_2_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_2_2e_val));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__81, *(int*)(&llvm_cbe_tmp__81));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_196_count);
  llvm_cbe_tmp__92 = (float *)(&llvm_cbe_tmp__79.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = load float* %%18, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_197_count);
  llvm_cbe_tmp__93 = (float )*llvm_cbe_tmp__92;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__93, *(int*)(&llvm_cbe_tmp__93));
  llvm_cbe_tmp__96__PHI_TEMPORARY = (float )llvm_cbe_tmp__93;   /* for PHI node */
  goto llvm_cbe_tmp__101;

llvm_cbe_tmp__100:
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.23 = getelementptr %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_23_count);
  llvm_cbe_u_input_Volts_2e_23 = (float *)(&llvm_cbe_u_input_Volts.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.23.val = load float* %%u_input_Volts.23, align  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_23_2e_val_count);
  llvm_cbe_u_input_Volts_2e_23_2e_val = (float )*llvm_cbe_u_input_Volts_2e_23;
if (AESL_DEBUG_TRACE)
printf("\nu_input_Volts.23.val = %f,  0x%x\n", llvm_cbe_u_input_Volts_2e_23_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_23_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  call fastcc void @aesl_internal_uz_limit_dq_prio_q_axis(%%struct.uz_dq_t* sret %%2, float %%5, float %%7, float %%u_input_Volts.23.val, float %%3 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_200_count);
  llvm_cbe_tmp__80 = aesl_internal_uz_limit_dq_prio_q_axis(llvm_cbe_tmp__83, llvm_cbe_tmp__85, llvm_cbe_u_input_Volts_2e_23_2e_val, llvm_cbe_tmp__81);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__83, *(int*)(&llvm_cbe_tmp__83));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__85, *(int*)(&llvm_cbe_tmp__85));
printf("\nArgument u_input_Volts.23.val = %f,  0x%x",llvm_cbe_u_input_Volts_2e_23_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_23_2e_val));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__81, *(int*)(&llvm_cbe_tmp__81));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds %%struct.uz_dq_t* %%2, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_201_count);
  llvm_cbe_tmp__94 = (float *)(&llvm_cbe_tmp__80.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = load float* %%21, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_202_count);
  llvm_cbe_tmp__95 = (float )*llvm_cbe_tmp__94;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__95, *(int*)(&llvm_cbe_tmp__95));
  llvm_cbe_tmp__96__PHI_TEMPORARY = (float )llvm_cbe_tmp__95;   /* for PHI node */
  goto llvm_cbe_tmp__101;

llvm_cbe_tmp__98:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%ext_clamping, align 1, !dbg !5 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_206_count);
  *llvm_cbe_ext_clamping = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
  llvm_cbe_tmp__96__PHI_TEMPORARY = (float )llvm_cbe_tmp__83;   /* for PHI node */
  goto llvm_cbe_tmp__101;

llvm_cbe_tmp__101:
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = phi float [ %%5, %%23 ], [ %%22, %%20 ], [ %%19, %%17  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_d  --> \n", ++aesl_llvm_cbe_208_count);
  llvm_cbe_tmp__96 = (float )llvm_cbe_tmp__96__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__96);
printf("\n = %f",llvm_cbe_tmp__83);
printf("\n = %f",llvm_cbe_tmp__95);
printf("\n = %f",llvm_cbe_tmp__93);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @uz_FOC_SpaceVector_Limitation_d}\n");
  return llvm_cbe_tmp__96;
}


float uz_FOC_SpaceVector_Limitation_q(l_struct_OC_uz_dq_t llvm_cbe_u_input_Volts, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, bool *llvm_cbe_ext_clamping) {
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_tmp__102;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_tmp__103;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  float llvm_cbe_tmp__104;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  float *llvm_cbe_tmp__105;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  float llvm_cbe_tmp__106;
  static  unsigned long long aesl_llvm_cbe_pow2_count = 0;
  float llvm_cbe_pow2;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  float *llvm_cbe_tmp__107;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  float llvm_cbe_tmp__108;
  static  unsigned long long aesl_llvm_cbe_pow24_count = 0;
  float llvm_cbe_pow24;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  float llvm_cbe_tmp__109;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  float llvm_cbe_tmp__110;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  float llvm_cbe_tmp__111;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  float *llvm_cbe_tmp__112;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  float llvm_cbe_tmp__113;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  float llvm_cbe_tmp__114;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_2_count = 0;
  float *llvm_cbe_u_input_Volts_2e_2;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_2_2e_val_count = 0;
  float llvm_cbe_u_input_Volts_2e_2_2e_val;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  float *llvm_cbe_tmp__115;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
  float llvm_cbe_tmp__116;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_23_count = 0;
  float *llvm_cbe_u_input_Volts_2e_23;
  static  unsigned long long aesl_llvm_cbe_u_input_Volts_2e_23_2e_val_count = 0;
  float llvm_cbe_u_input_Volts_2e_23_2e_val;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  float *llvm_cbe_tmp__117;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  float llvm_cbe_tmp__118;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  float llvm_cbe_tmp__119;
  float llvm_cbe_tmp__119__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_FOC_SpaceVector_Limitation_q\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = fdiv float %%V_dc_volts, 0x3FFBB67AE0000000, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_224_count);
  llvm_cbe_tmp__104 = (float )((float )(llvm_cbe_V_dc_volts / 0x1.bb67aep0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__104, *(int*)(&llvm_cbe_tmp__104));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32 0, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_229_count);
  llvm_cbe_tmp__105 = (float *)(&llvm_cbe_u_input_Volts.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load float* %%4, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_230_count);
  llvm_cbe_tmp__106 = (float )*llvm_cbe_tmp__105;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__106, *(int*)(&llvm_cbe_tmp__106));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow2 = fmul float %%5, %%5, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_pow2_count);
  llvm_cbe_pow2 = (float )((float )(llvm_cbe_tmp__106 * llvm_cbe_tmp__106));
if (AESL_DEBUG_TRACE)
printf("\npow2 = %f,  0x%x\n", llvm_cbe_pow2, *(int*)(&llvm_cbe_pow2));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32 1, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_231_count);
  llvm_cbe_tmp__107 = (float *)(&llvm_cbe_u_input_Volts.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load float* %%6, align 4, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_232_count);
  llvm_cbe_tmp__108 = (float )*llvm_cbe_tmp__107;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__108, *(int*)(&llvm_cbe_tmp__108));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow24 = fmul float %%7, %%7, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_pow24_count);
  llvm_cbe_pow24 = (float )((float )(llvm_cbe_tmp__108 * llvm_cbe_tmp__108));
if (AESL_DEBUG_TRACE)
printf("\npow24 = %f,  0x%x\n", llvm_cbe_pow24, *(int*)(&llvm_cbe_pow24));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = fadd float %%pow2, %%pow24, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_233_count);
  llvm_cbe_tmp__109 = (float )((float )(llvm_cbe_pow2 + llvm_cbe_pow24));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__109, *(int*)(&llvm_cbe_tmp__109));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = call float @sqrtf(float %%8) nounwind readnone, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_234_count);
  llvm_cbe_tmp__110 = (float )sqrtf(llvm_cbe_tmp__109);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__109, *(int*)(&llvm_cbe_tmp__109));
printf("\nReturn  = %f",llvm_cbe_tmp__110);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = call float @uz_signals_get_sign_of_value(float %%omega_el_rad_per_sec) nounwind, !dbg !5 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_237_count);
  llvm_cbe_tmp__111 = (float )uz_signals_get_sign_of_value(llvm_cbe_omega_el_rad_per_sec);
if (AESL_DEBUG_TRACE) {
printf("\nArgument omega_el_rad_per_sec = %f,  0x%x",llvm_cbe_omega_el_rad_per_sec, *(int*)(&llvm_cbe_omega_el_rad_per_sec));
printf("\nReturn  = %f",llvm_cbe_tmp__111);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32 1, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_238_count);
  llvm_cbe_tmp__112 = (float *)(&llvm_cbe_i_actual_Ampere.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = load float* %%11, align 4, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_239_count);
  llvm_cbe_tmp__113 = (float )*llvm_cbe_tmp__112;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__113, *(int*)(&llvm_cbe_tmp__113));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = call float @uz_signals_get_sign_of_value(float %%12) nounwind, !dbg !8 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_240_count);
  llvm_cbe_tmp__114 = (float )uz_signals_get_sign_of_value(llvm_cbe_tmp__113);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__113, *(int*)(&llvm_cbe_tmp__113));
printf("\nReturn  = %f",llvm_cbe_tmp__114);
}
  if ((llvm_fcmp_ogt(llvm_cbe_tmp__110, llvm_cbe_tmp__104))) {
    goto llvm_cbe_tmp__120;
  } else {
    goto llvm_cbe_tmp__121;
  }

llvm_cbe_tmp__120:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 true, i1* %%ext_clamping, align 1, !dbg !5 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_246_count);
  *llvm_cbe_ext_clamping = ((1) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1);
  if ((llvm_fcmp_oeq(llvm_cbe_tmp__111, llvm_cbe_tmp__114))) {
    goto llvm_cbe_tmp__122;
  } else {
    goto llvm_cbe_tmp__123;
  }

llvm_cbe_tmp__122:
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.2 = getelementptr %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_2_count);
  llvm_cbe_u_input_Volts_2e_2 = (float *)(&llvm_cbe_u_input_Volts.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.2.val = load float* %%u_input_Volts.2, align  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_2_2e_val_count);
  llvm_cbe_u_input_Volts_2e_2_2e_val = (float )*llvm_cbe_u_input_Volts_2e_2;
if (AESL_DEBUG_TRACE)
printf("\nu_input_Volts.2.val = %f,  0x%x\n", llvm_cbe_u_input_Volts_2e_2_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_2_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  call fastcc void @aesl_internal_uz_limit_dq_prio_d_axis(%%struct.uz_dq_t* sret %%1, float %%5, float %%7, float %%u_input_Volts.2.val, float %%3 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_248_count);
  llvm_cbe_tmp__102 = aesl_internal_uz_limit_dq_prio_d_axis(llvm_cbe_tmp__106, llvm_cbe_tmp__108, llvm_cbe_u_input_Volts_2e_2_2e_val, llvm_cbe_tmp__104);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__106, *(int*)(&llvm_cbe_tmp__106));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__108, *(int*)(&llvm_cbe_tmp__108));
printf("\nArgument u_input_Volts.2.val = %f,  0x%x",llvm_cbe_u_input_Volts_2e_2_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_2_2e_val));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__104, *(int*)(&llvm_cbe_tmp__104));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_249_count);
  llvm_cbe_tmp__115 = (float *)(&llvm_cbe_tmp__102.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = load float* %%18, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_250_count);
  llvm_cbe_tmp__116 = (float )*llvm_cbe_tmp__115;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__116, *(int*)(&llvm_cbe_tmp__116));
  llvm_cbe_tmp__119__PHI_TEMPORARY = (float )llvm_cbe_tmp__116;   /* for PHI node */
  goto llvm_cbe_tmp__124;

llvm_cbe_tmp__123:
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.23 = getelementptr %%struct.uz_dq_t* %%u_input_Volts, i64 0, i32  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_23_count);
  llvm_cbe_u_input_Volts_2e_23 = (float *)(&llvm_cbe_u_input_Volts.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%u_input_Volts.23.val = load float* %%u_input_Volts.23, align  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_u_input_Volts_2e_23_2e_val_count);
  llvm_cbe_u_input_Volts_2e_23_2e_val = (float )*llvm_cbe_u_input_Volts_2e_23;
if (AESL_DEBUG_TRACE)
printf("\nu_input_Volts.23.val = %f,  0x%x\n", llvm_cbe_u_input_Volts_2e_23_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_23_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  call fastcc void @aesl_internal_uz_limit_dq_prio_q_axis(%%struct.uz_dq_t* sret %%2, float %%5, float %%7, float %%u_input_Volts.23.val, float %%3 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_253_count);
  llvm_cbe_tmp__103 = aesl_internal_uz_limit_dq_prio_q_axis(llvm_cbe_tmp__106, llvm_cbe_tmp__108, llvm_cbe_u_input_Volts_2e_23_2e_val, llvm_cbe_tmp__104);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__106, *(int*)(&llvm_cbe_tmp__106));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__108, *(int*)(&llvm_cbe_tmp__108));
printf("\nArgument u_input_Volts.23.val = %f,  0x%x",llvm_cbe_u_input_Volts_2e_23_2e_val, *(int*)(&llvm_cbe_u_input_Volts_2e_23_2e_val));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__104, *(int*)(&llvm_cbe_tmp__104));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds %%struct.uz_dq_t* %%2, i64 0, i32 1, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_254_count);
  llvm_cbe_tmp__117 = (float *)(&llvm_cbe_tmp__103.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = load float* %%21, align 4, !dbg !7 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_255_count);
  llvm_cbe_tmp__118 = (float )*llvm_cbe_tmp__117;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__118, *(int*)(&llvm_cbe_tmp__118));
  llvm_cbe_tmp__119__PHI_TEMPORARY = (float )llvm_cbe_tmp__118;   /* for PHI node */
  goto llvm_cbe_tmp__124;

llvm_cbe_tmp__121:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%ext_clamping, align 1, !dbg !5 for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_259_count);
  *llvm_cbe_ext_clamping = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
  llvm_cbe_tmp__119__PHI_TEMPORARY = (float )llvm_cbe_tmp__108;   /* for PHI node */
  goto llvm_cbe_tmp__124;

llvm_cbe_tmp__124:
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = phi float [ %%7, %%23 ], [ %%22, %%20 ], [ %%19, %%17  for 0x%I64xth hint within @uz_FOC_SpaceVector_Limitation_q  --> \n", ++aesl_llvm_cbe_261_count);
  llvm_cbe_tmp__119 = (float )llvm_cbe_tmp__119__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__119);
printf("\n = %f",llvm_cbe_tmp__108);
printf("\n = %f",llvm_cbe_tmp__118);
printf("\n = %f",llvm_cbe_tmp__116);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @uz_FOC_SpaceVector_Limitation_q}\n");
  return llvm_cbe_tmp__119;
}

