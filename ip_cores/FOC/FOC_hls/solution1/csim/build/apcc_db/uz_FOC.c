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
typedef struct l_struct_OC_uz_PI_Controller_config l_struct_OC_uz_PI_Controller_config;
typedef struct l_struct_OC_uz_FOC l_struct_OC_uz_FOC;
typedef struct l_struct_OC_uz_PMSM_t l_struct_OC_uz_PMSM_t;

/* Structure contents */
struct l_struct_OC_uz_dq_t {
  float field0;
  float field1;
  float field2;
};

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
  bool field0;
  bool field1;
  bool field2;
  l_struct_OC_uz_PMSM_t field3;
};


/* External Global Variable Declarations */
extern l_struct_OC_uz_PI_Controller_config config_id;
extern l_struct_OC_uz_PI_Controller_config config_iq;

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
void uz_FOC_sample(l_struct_OC_uz_FOC *llvm_cbe_self, l_struct_OC_uz_PI_Controller_config *llvm_cbe_Controller_id, l_struct_OC_uz_PI_Controller_config *llvm_cbe_Controller_iq, l_struct_OC_uz_dq_t llvm_cbe_i_reference_Ampere, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, float *llvm_cbe_output_volts_d, float *llvm_cbe_output_volts_q);
l_struct_OC_uz_dq_t uz_FOC_CurrentControl(l_struct_OC_uz_FOC *llvm_cbe_self, l_struct_OC_uz_dq_t llvm_cbe_i_reference_Ampere, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, l_struct_OC_uz_PI_Controller_config *llvm_cbe_Controller_id, l_struct_OC_uz_PI_Controller_config *llvm_cbe_Controller_iq);
l_struct_OC_uz_dq_t uz_FOC_decoupling(bool llvm_cbe_decoupling_select, l_struct_OC_uz_PMSM_t llvm_cbe_config_PMSM, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, float llvm_cbe_omega_el_rad_per_sec);
l_struct_OC_uz_dq_t uz_FOC_SpaceVector_Limitation(l_struct_OC_uz_dq_t , float , float , l_struct_OC_uz_dq_t , bool *);
bool uz_PI_Controller_Clamping_Circuit(float , float , float , float );
float uz_signals_saturation(float , float , float );
l_struct_OC_uz_dq_t uz_FOC_linear_decoupling(l_struct_OC_uz_PMSM_t , l_struct_OC_uz_dq_t , float );


/* Global Variable Definitions and Initialization */
static l_struct_OC_uz_dq_t aesl_internal_uz_FOC_sample_OC_u_pre_limit_Volts;
static l_struct_OC_uz_dq_t aesl_internal_uz_FOC_sample_OC_u_decoup_Volts;
static float aesl_internal_uz_FOC_CurrentControl_OC_I_sum_d;
static float aesl_internal_uz_FOC_CurrentControl_OC_I_sum_q;
l_struct_OC_uz_PI_Controller_config config_id __ATTRIBUTE_WEAK__;
l_struct_OC_uz_PI_Controller_config config_iq __ATTRIBUTE_WEAK__;


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

void uz_FOC_sample(l_struct_OC_uz_FOC *llvm_cbe_self, l_struct_OC_uz_PI_Controller_config *llvm_cbe_Controller_id, l_struct_OC_uz_PI_Controller_config *llvm_cbe_Controller_iq, l_struct_OC_uz_dq_t llvm_cbe_i_reference_Ampere, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, float *llvm_cbe_output_volts_d, float *llvm_cbe_output_volts_q) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_tmp__1;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_tmp__2;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_u_output_Volts_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_u_output_Volts;    /* Address-exposed local */
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
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  float *llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  float llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  float *llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  float llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  float *llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  float llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  bool *llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  bool llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  l_struct_OC_uz_PMSM_t *llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  float *llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  float llvm_cbe_tmp__13;
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
  float llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  float llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  float llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  float llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  bool *llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  float *llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  float llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  float *llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  float llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_FOC_sample\n");
if (AESL_DEBUG_TRACE)
printf("\n  call void @uz_FOC_CurrentControl(%%struct.uz_dq_t* sret %%1, %%struct.uz_FOC* %%self, %%struct.uz_dq_t* byval %%i_reference_Ampere, %%struct.uz_dq_t* byval %%i_actual_Ampere, %%struct.uz_PI_Controller_config* %%Controller_id, %%struct.uz_PI_Controller_config* %%Controller_iq), !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_23_count);
  llvm_cbe_tmp__1 = uz_FOC_CurrentControl((l_struct_OC_uz_FOC *)llvm_cbe_self, llvm_cbe_i_reference_Ampere, llvm_cbe_i_actual_Ampere, (l_struct_OC_uz_PI_Controller_config *)llvm_cbe_Controller_id, (l_struct_OC_uz_PI_Controller_config *)llvm_cbe_Controller_iq);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 0, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_24_count);
  llvm_cbe_tmp__3 = (float *)(&llvm_cbe_tmp__1.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load float* %%3, align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_25_count);
  llvm_cbe_tmp__4 = (float )*llvm_cbe_tmp__3;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__4, *(int*)(&llvm_cbe_tmp__4));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%4, float* getelementptr inbounds (%%struct.uz_dq_t* @aesl_internal_uz_FOC_sample.u_pre_limit_Volts, i64 0, i32 0), align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_26_count);
  *((&aesl_internal_uz_FOC_sample_OC_u_pre_limit_Volts.field0)) = llvm_cbe_tmp__4;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 1, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_27_count);
  llvm_cbe_tmp__5 = (float *)(&llvm_cbe_tmp__1.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = load float* %%5, align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_28_count);
  llvm_cbe_tmp__6 = (float )*llvm_cbe_tmp__5;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__6, *(int*)(&llvm_cbe_tmp__6));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%6, float* getelementptr inbounds (%%struct.uz_dq_t* @aesl_internal_uz_FOC_sample.u_pre_limit_Volts, i64 0, i32 1), align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_29_count);
  *((&aesl_internal_uz_FOC_sample_OC_u_pre_limit_Volts.field1)) = llvm_cbe_tmp__6;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 2, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_30_count);
  llvm_cbe_tmp__7 = (float *)(&llvm_cbe_tmp__1.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load float* %%7, align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__8 = (float )*llvm_cbe_tmp__7;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__8, *(int*)(&llvm_cbe_tmp__8));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%8, float* getelementptr inbounds (%%struct.uz_dq_t* @aesl_internal_uz_FOC_sample.u_pre_limit_Volts, i64 0, i32 2), align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_32_count);
  *((&aesl_internal_uz_FOC_sample_OC_u_pre_limit_Volts.field2)) = llvm_cbe_tmp__8;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__8);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 0, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_33_count);
  llvm_cbe_tmp__9 = (bool *)(&llvm_cbe_self->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = load i1* %%9, align 1, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__10 = (bool )((*llvm_cbe_tmp__9)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__10);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 3, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__11 = (l_struct_OC_uz_PMSM_t *)(&llvm_cbe_self->field3);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @uz_FOC_decoupling(%%struct.uz_dq_t* sret %%2, i1 zeroext %%10, %%struct.uz_PMSM_t* byval %%11, %%struct.uz_dq_t* byval %%i_actual_Ampere, float %%omega_el_rad_per_sec), !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__2 = uz_FOC_decoupling(llvm_cbe_tmp__10, *(llvm_cbe_tmp__11), llvm_cbe_i_actual_Ampere, llvm_cbe_omega_el_rad_per_sec);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__10);
printf("\nArgument omega_el_rad_per_sec = %f,  0x%x",llvm_cbe_omega_el_rad_per_sec, *(int*)(&llvm_cbe_omega_el_rad_per_sec));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = getelementptr inbounds %%struct.uz_dq_t* %%2, i64 0, i32 0, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_37_count);
  llvm_cbe_tmp__12 = (float *)(&llvm_cbe_tmp__2.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = load float* %%12, align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_38_count);
  llvm_cbe_tmp__13 = (float )*llvm_cbe_tmp__12;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__13, *(int*)(&llvm_cbe_tmp__13));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%13, float* getelementptr inbounds (%%struct.uz_dq_t* @aesl_internal_uz_FOC_sample.u_decoup_Volts, i64 0, i32 0), align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_39_count);
  *((&aesl_internal_uz_FOC_sample_OC_u_decoup_Volts.field0)) = llvm_cbe_tmp__13;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds %%struct.uz_dq_t* %%2, i64 0, i32 1, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_40_count);
  llvm_cbe_tmp__14 = (float *)(&llvm_cbe_tmp__2.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load float* %%14, align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_41_count);
  llvm_cbe_tmp__15 = (float )*llvm_cbe_tmp__14;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__15, *(int*)(&llvm_cbe_tmp__15));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%15, float* getelementptr inbounds (%%struct.uz_dq_t* @aesl_internal_uz_FOC_sample.u_decoup_Volts, i64 0, i32 1), align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_42_count);
  *((&aesl_internal_uz_FOC_sample_OC_u_decoup_Volts.field1)) = llvm_cbe_tmp__15;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__15);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds %%struct.uz_dq_t* %%2, i64 0, i32 2, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_43_count);
  llvm_cbe_tmp__16 = (float *)(&llvm_cbe_tmp__2.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load float* %%16, align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_44_count);
  llvm_cbe_tmp__17 = (float )*llvm_cbe_tmp__16;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__17, *(int*)(&llvm_cbe_tmp__17));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%17, float* getelementptr inbounds (%%struct.uz_dq_t* @aesl_internal_uz_FOC_sample.u_decoup_Volts, i64 0, i32 2), align 4, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_45_count);
  *((&aesl_internal_uz_FOC_sample_OC_u_decoup_Volts.field2)) = llvm_cbe_tmp__17;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__17);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = load float* getelementptr inbounds (%%struct.uz_dq_t* @aesl_internal_uz_FOC_sample.u_pre_limit_Volts, i64 0, i32 0), align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__18 = (float )*((&aesl_internal_uz_FOC_sample_OC_u_pre_limit_Volts.field0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__18, *(int*)(&llvm_cbe_tmp__18));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = fadd float %%18, %%13, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__19 = (float )((float )(llvm_cbe_tmp__18 + llvm_cbe_tmp__13));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__19, *(int*)(&llvm_cbe_tmp__19));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%19, float* getelementptr inbounds (%%struct.uz_dq_t* @aesl_internal_uz_FOC_sample.u_pre_limit_Volts, i64 0, i32 0), align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_48_count);
  *((&aesl_internal_uz_FOC_sample_OC_u_pre_limit_Volts.field0)) = llvm_cbe_tmp__19;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__19);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = load float* getelementptr inbounds (%%struct.uz_dq_t* @aesl_internal_uz_FOC_sample.u_pre_limit_Volts, i64 0, i32 1), align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_49_count);
  llvm_cbe_tmp__20 = (float )*((&aesl_internal_uz_FOC_sample_OC_u_pre_limit_Volts.field1));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__20, *(int*)(&llvm_cbe_tmp__20));
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = fadd float %%20, %%15, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_50_count);
  llvm_cbe_tmp__21 = (float )((float )(llvm_cbe_tmp__20 + llvm_cbe_tmp__15));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__21, *(int*)(&llvm_cbe_tmp__21));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%21, float* getelementptr inbounds (%%struct.uz_dq_t* @aesl_internal_uz_FOC_sample.u_pre_limit_Volts, i64 0, i32 1), align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_51_count);
  *((&aesl_internal_uz_FOC_sample_OC_u_pre_limit_Volts.field1)) = llvm_cbe_tmp__21;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__21);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 2, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_53_count);
  llvm_cbe_tmp__22 = (bool *)(&llvm_cbe_self->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @uz_FOC_SpaceVector_Limitation(%%struct.uz_dq_t* sret %%u_output_Volts, %%struct.uz_dq_t* byval @aesl_internal_uz_FOC_sample.u_pre_limit_Volts, float %%V_dc_volts, float %%omega_el_rad_per_sec, %%struct.uz_dq_t* byval %%i_actual_Ampere, i1* %%22) nounwind, !dbg !9 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_54_count);
  llvm_cbe_u_output_Volts = uz_FOC_SpaceVector_Limitation(aesl_internal_uz_FOC_sample_OC_u_pre_limit_Volts, llvm_cbe_V_dc_volts, llvm_cbe_omega_el_rad_per_sec, llvm_cbe_i_actual_Ampere, (bool *)llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE) {
printf("\nArgument V_dc_volts = %f,  0x%x",llvm_cbe_V_dc_volts, *(int*)(&llvm_cbe_V_dc_volts));
printf("\nArgument omega_el_rad_per_sec = %f,  0x%x",llvm_cbe_omega_el_rad_per_sec, *(int*)(&llvm_cbe_omega_el_rad_per_sec));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = getelementptr inbounds %%struct.uz_dq_t* %%u_output_Volts, i64 0, i32 0, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_55_count);
  llvm_cbe_tmp__23 = (float *)(&llvm_cbe_u_output_Volts.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = load float* %%23, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_56_count);
  llvm_cbe_tmp__24 = (float )*llvm_cbe_tmp__23;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__24, *(int*)(&llvm_cbe_tmp__24));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%24, float* %%output_volts_d, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_57_count);
  *llvm_cbe_output_volts_d = llvm_cbe_tmp__24;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__24);
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = getelementptr inbounds %%struct.uz_dq_t* %%u_output_Volts, i64 0, i32 1, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_58_count);
  llvm_cbe_tmp__25 = (float *)(&llvm_cbe_u_output_Volts.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = load float* %%25, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_59_count);
  llvm_cbe_tmp__26 = (float )*llvm_cbe_tmp__25;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__26, *(int*)(&llvm_cbe_tmp__26));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%26, float* %%output_volts_q, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_60_count);
  *llvm_cbe_output_volts_q = llvm_cbe_tmp__26;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__26);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @uz_FOC_sample}\n");
  return;
}


l_struct_OC_uz_dq_t uz_FOC_CurrentControl(l_struct_OC_uz_FOC *llvm_cbe_self, l_struct_OC_uz_dq_t llvm_cbe_i_reference_Ampere, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, l_struct_OC_uz_PI_Controller_config *llvm_cbe_Controller_id, l_struct_OC_uz_PI_Controller_config *llvm_cbe_Controller_iq) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
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
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  float *llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  float llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  float *llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  float llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  float llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  float *llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  float llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  float *llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  float llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  float llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  float llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  float llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  float *llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  float llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  float llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  float *llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  float llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  float llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  float *llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  float llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  float llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  float *llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  float llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  float llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  float llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  float llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  float *llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  float llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  float *llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  float llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  bool llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  float *llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  float llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  float *llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  float llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  bool llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  bool *llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  bool llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  bool llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__count = 0;
  bool llvm_cbe__2e_;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  float llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  float llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  float *llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  float llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  float llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  float llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  float llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge_count = 0;
  float llvm_cbe_storemerge;
  float llvm_cbe_storemerge__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  float llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  float llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  float *llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  float llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  float llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  float llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  float llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  float llvm_cbe_storemerge1;
  float llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  float llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  float llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  float llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  float llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  float llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  float llvm_cbe_tmp__85;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  bool *llvm_cbe_tmp__86;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  bool llvm_cbe_tmp__87;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  float *llvm_cbe_tmp__88;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  float *llvm_cbe_tmp__89;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  float *llvm_cbe_tmp__90;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_FOC_CurrentControl\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.uz_dq_t* %%i_reference_Ampere, i64 0, i32 0, !dbg !13 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_91_count);
  llvm_cbe_tmp__27 = (float *)(&llvm_cbe_i_reference_Ampere.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = load float* %%1, align 4, !dbg !13 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_92_count);
  llvm_cbe_tmp__28 = (float )*llvm_cbe_tmp__27;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__28, *(int*)(&llvm_cbe_tmp__28));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32 0, !dbg !13 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_93_count);
  llvm_cbe_tmp__29 = (float *)(&llvm_cbe_i_actual_Ampere.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load float* %%3, align 4, !dbg !13 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_94_count);
  llvm_cbe_tmp__30 = (float )*llvm_cbe_tmp__29;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__30, *(int*)(&llvm_cbe_tmp__30));
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = fsub float %%2, %%4, !dbg !13 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_95_count);
  llvm_cbe_tmp__31 = (float )((float )(llvm_cbe_tmp__28 - llvm_cbe_tmp__30));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__31, *(int*)(&llvm_cbe_tmp__31));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.uz_dq_t* %%i_reference_Ampere, i64 0, i32 1, !dbg !13 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_99_count);
  llvm_cbe_tmp__32 = (float *)(&llvm_cbe_i_reference_Ampere.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load float* %%6, align 4, !dbg !13 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_100_count);
  llvm_cbe_tmp__33 = (float )*llvm_cbe_tmp__32;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__33, *(int*)(&llvm_cbe_tmp__33));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32 1, !dbg !13 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_101_count);
  llvm_cbe_tmp__34 = (float *)(&llvm_cbe_i_actual_Ampere.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load float* %%8, align 4, !dbg !13 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_102_count);
  llvm_cbe_tmp__35 = (float )*llvm_cbe_tmp__34;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__35, *(int*)(&llvm_cbe_tmp__35));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = fsub float %%7, %%9, !dbg !13 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_103_count);
  llvm_cbe_tmp__36 = (float )((float )(llvm_cbe_tmp__33 - llvm_cbe_tmp__35));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__36, *(int*)(&llvm_cbe_tmp__36));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load float* @aesl_internal_uz_FOC_CurrentControl.I_sum_d, align 4, !dbg !14 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_107_count);
  llvm_cbe_tmp__37 = (float )*(&aesl_internal_uz_FOC_CurrentControl_OC_I_sum_d);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__37, *(int*)(&llvm_cbe_tmp__37));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = load float* @aesl_internal_uz_FOC_CurrentControl.I_sum_q, align 4, !dbg !14 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_110_count);
  llvm_cbe_tmp__38 = (float )*(&aesl_internal_uz_FOC_CurrentControl_OC_I_sum_q);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__38, *(int*)(&llvm_cbe_tmp__38));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%Controller_id, i64 0, i32 1, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_113_count);
  llvm_cbe_tmp__39 = (float *)(&llvm_cbe_Controller_id->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = load float* %%13, align 4, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__40 = (float )*llvm_cbe_tmp__39;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__40, *(int*)(&llvm_cbe_tmp__40));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = fmul float %%5, %%14, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__41 = (float )((float )(llvm_cbe_tmp__31 * llvm_cbe_tmp__40));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__41, *(int*)(&llvm_cbe_tmp__41));
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%Controller_iq, i64 0, i32 1, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_119_count);
  llvm_cbe_tmp__42 = (float *)(&llvm_cbe_Controller_iq->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load float* %%16, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_120_count);
  llvm_cbe_tmp__43 = (float )*llvm_cbe_tmp__42;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__43, *(int*)(&llvm_cbe_tmp__43));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = fmul float %%10, %%17, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_121_count);
  llvm_cbe_tmp__44 = (float )((float )(llvm_cbe_tmp__36 * llvm_cbe_tmp__43));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__44, *(int*)(&llvm_cbe_tmp__44));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%Controller_id, i64 0, i32 0, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__45 = (float *)(&llvm_cbe_Controller_id->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = load float* %%19, align 4, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_126_count);
  llvm_cbe_tmp__46 = (float )*llvm_cbe_tmp__45;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__46, *(int*)(&llvm_cbe_tmp__46));
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = fmul float %%5, %%20, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_127_count);
  llvm_cbe_tmp__47 = (float )((float )(llvm_cbe_tmp__31 * llvm_cbe_tmp__46));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__47, *(int*)(&llvm_cbe_tmp__47));
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%Controller_iq, i64 0, i32 0, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_130_count);
  llvm_cbe_tmp__48 = (float *)(&llvm_cbe_Controller_iq->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = load float* %%22, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__49 = (float )*llvm_cbe_tmp__48;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__49, *(int*)(&llvm_cbe_tmp__49));
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = fmul float %%10, %%23, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__50 = (float )((float )(llvm_cbe_tmp__36 * llvm_cbe_tmp__49));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__50, *(int*)(&llvm_cbe_tmp__50));
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = fadd float %%11, %%21, !dbg !14 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__51 = (float )((float )(llvm_cbe_tmp__37 + llvm_cbe_tmp__47));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__51, *(int*)(&llvm_cbe_tmp__51));
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = fadd float %%12, %%24, !dbg !14 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_139_count);
  llvm_cbe_tmp__52 = (float )((float )(llvm_cbe_tmp__38 + llvm_cbe_tmp__50));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__52, *(int*)(&llvm_cbe_tmp__52));
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%Controller_id, i64 0, i32 3, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_143_count);
  llvm_cbe_tmp__53 = (float *)(&llvm_cbe_Controller_id->field3);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = load float* %%27, align 4, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_144_count);
  llvm_cbe_tmp__54 = (float )*llvm_cbe_tmp__53;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__54, *(int*)(&llvm_cbe_tmp__54));
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%Controller_id, i64 0, i32 4, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_145_count);
  llvm_cbe_tmp__55 = (float *)(&llvm_cbe_Controller_id->field4);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = load float* %%29, align 4, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_146_count);
  llvm_cbe_tmp__56 = (float )*llvm_cbe_tmp__55;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__56, *(int*)(&llvm_cbe_tmp__56));
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = tail call zeroext i1 @uz_PI_Controller_Clamping_Circuit(float %%15, float %%25, float %%28, float %%30) nounwind, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_147_count);
  llvm_cbe_tmp__57 = (bool )(( /*tail*/ uz_PI_Controller_Clamping_Circuit(llvm_cbe_tmp__41, llvm_cbe_tmp__51, llvm_cbe_tmp__54, llvm_cbe_tmp__56))&1);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__41, *(int*)(&llvm_cbe_tmp__41));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__51, *(int*)(&llvm_cbe_tmp__51));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__54, *(int*)(&llvm_cbe_tmp__54));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__56, *(int*)(&llvm_cbe_tmp__56));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__57);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%Controller_iq, i64 0, i32 3, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__58 = (float *)(&llvm_cbe_Controller_iq->field3);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = load float* %%32, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_151_count);
  llvm_cbe_tmp__59 = (float )*llvm_cbe_tmp__58;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__59, *(int*)(&llvm_cbe_tmp__59));
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%Controller_iq, i64 0, i32 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_152_count);
  llvm_cbe_tmp__60 = (float *)(&llvm_cbe_Controller_iq->field4);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = load float* %%34, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_153_count);
  llvm_cbe_tmp__61 = (float )*llvm_cbe_tmp__60;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__61, *(int*)(&llvm_cbe_tmp__61));
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = tail call zeroext i1 @uz_PI_Controller_Clamping_Circuit(float %%18, float %%26, float %%33, float %%35) nounwind, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_154_count);
  llvm_cbe_tmp__62 = (bool )(( /*tail*/ uz_PI_Controller_Clamping_Circuit(llvm_cbe_tmp__44, llvm_cbe_tmp__52, llvm_cbe_tmp__59, llvm_cbe_tmp__61))&1);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__44, *(int*)(&llvm_cbe_tmp__44));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__52, *(int*)(&llvm_cbe_tmp__52));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__59, *(int*)(&llvm_cbe_tmp__59));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__61, *(int*)(&llvm_cbe_tmp__61));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__62);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 2, !dbg !9 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_157_count);
  llvm_cbe_tmp__63 = (bool *)(&llvm_cbe_self->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = load i1* %%37, align 1, !dbg !9 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_158_count);
  llvm_cbe_tmp__64 = (bool )((*llvm_cbe_tmp__63)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__64);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = or i1 %%38, %%31, !dbg !9 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_159_count);
  llvm_cbe_tmp__65 = (bool )((llvm_cbe_tmp__64 | llvm_cbe_tmp__57)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE)
printf("\n  %%. = or i1 %%38, %%36, !dbg !9 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe__2e__count);
  llvm_cbe__2e_ = (bool )((llvm_cbe_tmp__64 | llvm_cbe_tmp__62)&1);
if (AESL_DEBUG_TRACE)
printf("\n. = 0x%X\n", llvm_cbe__2e_);
  if (llvm_cbe_tmp__65) {
    goto llvm_cbe_tmp__91;
  } else {
    goto llvm_cbe_tmp__92;
  }

llvm_cbe_tmp__91:
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = load float* @aesl_internal_uz_FOC_CurrentControl.I_sum_d, align 4, !dbg !15 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_165_count);
  llvm_cbe_tmp__66 = (float )*(&aesl_internal_uz_FOC_CurrentControl_OC_I_sum_d);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__66, *(int*)(&llvm_cbe_tmp__66));
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = fadd float %%41, 0.000000e+00, !dbg !15 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_166_count);
  llvm_cbe_tmp__67 = (float )((float )(llvm_cbe_tmp__66 + 0x0p0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__67, *(int*)(&llvm_cbe_tmp__67));
  llvm_cbe_storemerge__PHI_TEMPORARY = (float )llvm_cbe_tmp__67;   /* for PHI node */
  goto llvm_cbe_tmp__93;

llvm_cbe_tmp__92:
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%Controller_id, i64 0, i32 2, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_168_count);
  llvm_cbe_tmp__68 = (float *)(&llvm_cbe_Controller_id->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = load float* %%44, align 4, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_169_count);
  llvm_cbe_tmp__69 = (float )*llvm_cbe_tmp__68;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__69, *(int*)(&llvm_cbe_tmp__69));
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = fmul float %%15, %%45, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_170_count);
  llvm_cbe_tmp__70 = (float )((float )(llvm_cbe_tmp__41 * llvm_cbe_tmp__69));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__70, *(int*)(&llvm_cbe_tmp__70));
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = load float* @aesl_internal_uz_FOC_CurrentControl.I_sum_d, align 4, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_171_count);
  llvm_cbe_tmp__71 = (float )*(&aesl_internal_uz_FOC_CurrentControl_OC_I_sum_d);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__71, *(int*)(&llvm_cbe_tmp__71));
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = fadd float %%47, %%46, !dbg !10 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_172_count);
  llvm_cbe_tmp__72 = (float )((float )(llvm_cbe_tmp__71 + llvm_cbe_tmp__70));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__72, *(int*)(&llvm_cbe_tmp__72));
  llvm_cbe_storemerge__PHI_TEMPORARY = (float )llvm_cbe_tmp__72;   /* for PHI node */
  goto llvm_cbe_tmp__93;

llvm_cbe_tmp__93:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge = phi float [ %%48, %%43 ], [ %%42, %%40  for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_storemerge_count);
  llvm_cbe_storemerge = (float )llvm_cbe_storemerge__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge = %f",llvm_cbe_storemerge);
printf("\n = %f",llvm_cbe_tmp__72);
printf("\n = %f",llvm_cbe_tmp__67);
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%storemerge, float* @aesl_internal_uz_FOC_CurrentControl.I_sum_d, align 4, !dbg !15 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_174_count);
  *(&aesl_internal_uz_FOC_CurrentControl_OC_I_sum_d) = llvm_cbe_storemerge;
if (AESL_DEBUG_TRACE)
printf("\nstoremerge = %f\n", llvm_cbe_storemerge);
  if (llvm_cbe__2e_) {
    goto llvm_cbe_tmp__94;
  } else {
    goto llvm_cbe_tmp__95;
  }

llvm_cbe_tmp__94:
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = load float* @aesl_internal_uz_FOC_CurrentControl.I_sum_q, align 4, !dbg !16 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_176_count);
  llvm_cbe_tmp__73 = (float )*(&aesl_internal_uz_FOC_CurrentControl_OC_I_sum_q);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__73, *(int*)(&llvm_cbe_tmp__73));
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = fadd float %%51, 0.000000e+00, !dbg !16 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_177_count);
  llvm_cbe_tmp__74 = (float )((float )(llvm_cbe_tmp__73 + 0x0p0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__74, *(int*)(&llvm_cbe_tmp__74));
  llvm_cbe_storemerge1__PHI_TEMPORARY = (float )llvm_cbe_tmp__74;   /* for PHI node */
  goto llvm_cbe_tmp__96;

llvm_cbe_tmp__95:
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = getelementptr inbounds %%struct.uz_PI_Controller_config* %%Controller_iq, i64 0, i32 2, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_179_count);
  llvm_cbe_tmp__75 = (float *)(&llvm_cbe_Controller_iq->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = load float* %%54, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_180_count);
  llvm_cbe_tmp__76 = (float )*llvm_cbe_tmp__75;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__76, *(int*)(&llvm_cbe_tmp__76));
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = fmul float %%18, %%55, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_181_count);
  llvm_cbe_tmp__77 = (float )((float )(llvm_cbe_tmp__44 * llvm_cbe_tmp__76));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__77, *(int*)(&llvm_cbe_tmp__77));
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = load float* @aesl_internal_uz_FOC_CurrentControl.I_sum_q, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_182_count);
  llvm_cbe_tmp__78 = (float )*(&aesl_internal_uz_FOC_CurrentControl_OC_I_sum_q);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__78, *(int*)(&llvm_cbe_tmp__78));
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = fadd float %%57, %%56, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_183_count);
  llvm_cbe_tmp__79 = (float )((float )(llvm_cbe_tmp__78 + llvm_cbe_tmp__77));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__79, *(int*)(&llvm_cbe_tmp__79));
  llvm_cbe_storemerge1__PHI_TEMPORARY = (float )llvm_cbe_tmp__79;   /* for PHI node */
  goto llvm_cbe_tmp__96;

llvm_cbe_tmp__96:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi float [ %%58, %%53 ], [ %%52, %%50  for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (float )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = %f",llvm_cbe_storemerge1);
printf("\n = %f",llvm_cbe_tmp__79);
printf("\n = %f",llvm_cbe_tmp__74);
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%storemerge1, float* @aesl_internal_uz_FOC_CurrentControl.I_sum_q, align 4, !dbg !16 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_185_count);
  *(&aesl_internal_uz_FOC_CurrentControl_OC_I_sum_q) = llvm_cbe_storemerge1;
if (AESL_DEBUG_TRACE)
printf("\nstoremerge1 = %f\n", llvm_cbe_storemerge1);
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = load float* %%27, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_186_count);
  llvm_cbe_tmp__80 = (float )*llvm_cbe_tmp__53;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__80, *(int*)(&llvm_cbe_tmp__80));
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = load float* %%29, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_187_count);
  llvm_cbe_tmp__81 = (float )*llvm_cbe_tmp__55;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__81, *(int*)(&llvm_cbe_tmp__81));
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = tail call float @uz_signals_saturation(float %%25, float %%60, float %%61) nounwind, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_188_count);
  llvm_cbe_tmp__82 = (float ) /*tail*/ uz_signals_saturation(llvm_cbe_tmp__51, llvm_cbe_tmp__80, llvm_cbe_tmp__81);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__51, *(int*)(&llvm_cbe_tmp__51));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__80, *(int*)(&llvm_cbe_tmp__80));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__81, *(int*)(&llvm_cbe_tmp__81));
printf("\nReturn  = %f",llvm_cbe_tmp__82);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%63 = load float* %%32, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_190_count);
  llvm_cbe_tmp__83 = (float )*llvm_cbe_tmp__58;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__83, *(int*)(&llvm_cbe_tmp__83));
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = load float* %%34, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_191_count);
  llvm_cbe_tmp__84 = (float )*llvm_cbe_tmp__60;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__84, *(int*)(&llvm_cbe_tmp__84));
if (AESL_DEBUG_TRACE)
printf("\n  %%65 = tail call float @uz_signals_saturation(float %%26, float %%63, float %%64) nounwind, !dbg !11 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_192_count);
  llvm_cbe_tmp__85 = (float ) /*tail*/ uz_signals_saturation(llvm_cbe_tmp__52, llvm_cbe_tmp__83, llvm_cbe_tmp__84);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__52, *(int*)(&llvm_cbe_tmp__52));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__83, *(int*)(&llvm_cbe_tmp__83));
printf("\nArgument  = %f,  0x%x",llvm_cbe_tmp__84, *(int*)(&llvm_cbe_tmp__84));
printf("\nReturn  = %f",llvm_cbe_tmp__85);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 1, !dbg !9 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_194_count);
  llvm_cbe_tmp__86 = (bool *)(&llvm_cbe_self->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = load i1* %%66, align 1, !dbg !9 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_195_count);
  llvm_cbe_tmp__87 = (bool )((*llvm_cbe_tmp__86)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__87);
  if (llvm_cbe_tmp__87) {
    goto llvm_cbe_tmp__97;
  } else {
    goto llvm_cbe_tmp__98;
  }

llvm_cbe_tmp__97:
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* @aesl_internal_uz_FOC_CurrentControl.I_sum_d, align 4, !dbg !16 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_197_count);
  *(&aesl_internal_uz_FOC_CurrentControl_OC_I_sum_d) = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* @aesl_internal_uz_FOC_CurrentControl.I_sum_q, align 4, !dbg !16 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_198_count);
  *(&aesl_internal_uz_FOC_CurrentControl_OC_I_sum_q) = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
  goto llvm_cbe_tmp__98;

llvm_cbe_tmp__98:
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !17 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_204_count);
  llvm_cbe_tmp__88 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%62, float* %%70, align 4, !dbg !17 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_205_count);
  *llvm_cbe_tmp__88 = llvm_cbe_tmp__82;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__82);
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !17 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_206_count);
  llvm_cbe_tmp__89 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%65, float* %%71, align 4, !dbg !17 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_207_count);
  *llvm_cbe_tmp__89 = llvm_cbe_tmp__85;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__85);
if (AESL_DEBUG_TRACE)
printf("\n  %%72 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !17 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_208_count);
  llvm_cbe_tmp__90 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* %%72, align 4, !dbg !17 for 0x%I64xth hint within @uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_209_count);
  *llvm_cbe_tmp__90 = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
if (AESL_DEBUG_TRACE)
    printf("\n END @uz_FOC_CurrentControl }\n"); 
  return StructReturn;
}


l_struct_OC_uz_dq_t uz_FOC_decoupling(bool llvm_cbe_decoupling_select, l_struct_OC_uz_PMSM_t llvm_cbe_config_PMSM, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, float llvm_cbe_omega_el_rad_per_sec) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_tmp__99;    /* Address-exposed local */
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
  float *llvm_cbe_tmp__100;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  float llvm_cbe_tmp__101;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  float *llvm_cbe_tmp__102;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  float llvm_cbe_tmp__103;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  float *llvm_cbe_tmp__104;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  float llvm_cbe_tmp__105;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  float llvm_cbe_tmp__106;
  float llvm_cbe_tmp__106__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  float llvm_cbe_tmp__107;
  float llvm_cbe_tmp__107__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  float llvm_cbe_tmp__108;
  float llvm_cbe_tmp__108__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  float *llvm_cbe_tmp__109;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  float *llvm_cbe_tmp__110;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  float *llvm_cbe_tmp__111;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_FOC_decoupling\n");
  if (llvm_cbe_decoupling_select) {
    goto llvm_cbe_tmp__112;
  } else {
    llvm_cbe_tmp__106__PHI_TEMPORARY = (float )0x0p0;   /* for PHI node */
    llvm_cbe_tmp__107__PHI_TEMPORARY = (float )0x0p0;   /* for PHI node */
    llvm_cbe_tmp__108__PHI_TEMPORARY = (float )0x0p0;   /* for PHI node */
    goto llvm_cbe_tmp__113;
  }

llvm_cbe_tmp__112:
if (AESL_DEBUG_TRACE)
printf("\n  call void @uz_FOC_linear_decoupling(%%struct.uz_dq_t* sret %%1, %%struct.uz_PMSM_t* byval %%config_PMSM, %%struct.uz_dq_t* byval %%i_actual_Ampere, float %%omega_el_rad_per_sec) nounwind, !dbg !10 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_222_count);
  llvm_cbe_tmp__99 = uz_FOC_linear_decoupling(llvm_cbe_config_PMSM, llvm_cbe_i_actual_Ampere, llvm_cbe_omega_el_rad_per_sec);
if (AESL_DEBUG_TRACE) {
printf("\nArgument omega_el_rad_per_sec = %f,  0x%x",llvm_cbe_omega_el_rad_per_sec, *(int*)(&llvm_cbe_omega_el_rad_per_sec));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 0, !dbg !10 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_223_count);
  llvm_cbe_tmp__100 = (float *)(&llvm_cbe_tmp__99.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load float* %%3, align 4, !dbg !10 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_224_count);
  llvm_cbe_tmp__101 = (float )*llvm_cbe_tmp__100;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__101, *(int*)(&llvm_cbe_tmp__101));
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 1, !dbg !10 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_226_count);
  llvm_cbe_tmp__102 = (float *)(&llvm_cbe_tmp__99.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = load float* %%5, align 4, !dbg !10 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_227_count);
  llvm_cbe_tmp__103 = (float )*llvm_cbe_tmp__102;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__103, *(int*)(&llvm_cbe_tmp__103));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 2, !dbg !10 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_229_count);
  llvm_cbe_tmp__104 = (float *)(&llvm_cbe_tmp__99.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load float* %%7, align 4, !dbg !10 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_230_count);
  llvm_cbe_tmp__105 = (float )*llvm_cbe_tmp__104;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__105, *(int*)(&llvm_cbe_tmp__105));
  llvm_cbe_tmp__106__PHI_TEMPORARY = (float )llvm_cbe_tmp__105;   /* for PHI node */
  llvm_cbe_tmp__107__PHI_TEMPORARY = (float )llvm_cbe_tmp__103;   /* for PHI node */
  llvm_cbe_tmp__108__PHI_TEMPORARY = (float )llvm_cbe_tmp__101;   /* for PHI node */
  goto llvm_cbe_tmp__113;

llvm_cbe_tmp__113:
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = phi float [ 0.000000e+00, %%0 ], [ %%8, %%2  for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_233_count);
  llvm_cbe_tmp__106 = (float )llvm_cbe_tmp__106__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__106);
printf("\n = %f",0x0p0);
printf("\n = %f",llvm_cbe_tmp__105);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = phi float [ 0.000000e+00, %%0 ], [ %%6, %%2  for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_234_count);
  llvm_cbe_tmp__107 = (float )llvm_cbe_tmp__107__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__107);
printf("\n = %f",0x0p0);
printf("\n = %f",llvm_cbe_tmp__103);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = phi float [ 0.000000e+00, %%0 ], [ %%4, %%2  for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_235_count);
  llvm_cbe_tmp__108 = (float )llvm_cbe_tmp__108__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__108);
printf("\n = %f",0x0p0);
printf("\n = %f",llvm_cbe_tmp__101);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !11 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_236_count);
  llvm_cbe_tmp__109 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%12, float* %%13, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_237_count);
  *llvm_cbe_tmp__109 = llvm_cbe_tmp__108;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__108);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !11 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_238_count);
  llvm_cbe_tmp__110 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%11, float* %%14, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_239_count);
  *llvm_cbe_tmp__110 = llvm_cbe_tmp__107;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__107);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !11 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_240_count);
  llvm_cbe_tmp__111 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%10, float* %%15, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_241_count);
  *llvm_cbe_tmp__111 = llvm_cbe_tmp__106;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__106);
if (AESL_DEBUG_TRACE)
    printf("\n END @uz_FOC_decoupling }\n"); 
  return StructReturn;
}

