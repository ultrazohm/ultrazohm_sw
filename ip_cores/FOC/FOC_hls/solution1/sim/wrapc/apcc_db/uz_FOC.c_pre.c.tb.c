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
typedef struct l_struct_OC_uz_FOC l_struct_OC_uz_FOC;
typedef struct l_struct_OC_uz_PI_Controller_config l_struct_OC_uz_PI_Controller_config;
typedef struct l_struct_OC_uz_PMSM_t l_struct_OC_uz_PMSM_t;
typedef struct l_struct_OC_uz_dq_t l_struct_OC_uz_dq_t;
typedef struct l_struct_OC___cosim_s1__ l_struct_OC___cosim_s1__;

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
  l_struct_OC_uz_PI_Controller_config field3;
  l_struct_OC_uz_PI_Controller_config field4;
  l_struct_OC_uz_PMSM_t field5;
};

struct l_struct_OC_uz_dq_t {
  float field0;
  float field1;
  float field2;
};

struct l_struct_OC___cosim_s1__ {
   char field0[12];
};


/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
void uz_FOC_sample(l_struct_OC_uz_FOC *llvm_cbe_self, l_struct_OC_uz_dq_t llvm_cbe_i_reference_Ampere, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t *llvm_cbe_u_output_Volts);
static l_struct_OC_uz_dq_t aesl_internal_uz_FOC_CurrentControl(l_struct_OC_uz_FOC *llvm_cbe_self, float llvm_cbe_i_reference_Ampere_2e_0, float llvm_cbe_i_reference_Ampere_2e_1, float llvm_cbe_i_reference_Ampere_2e_2, float llvm_cbe_i_actual_Ampere_2e_0, float llvm_cbe_i_actual_Ampere_2e_1, float llvm_cbe_i_actual_Ampere_2e_2);
static l_struct_OC_uz_dq_t aesl_internal_uz_FOC_decoupling(bool llvm_cbe_decoupling_select, l_struct_OC_uz_PMSM_t llvm_cbe_config_PMSM, float llvm_cbe_i_actual_Ampere_2e_0, float llvm_cbe_i_actual_Ampere_2e_1, float llvm_cbe_i_actual_Ampere_2e_2, float llvm_cbe_omega_el_rad_per_sec);
l_struct_OC_uz_dq_t uz_FOC_SpaceVector_Limitation(l_struct_OC_uz_dq_t , float , float , l_struct_OC_uz_dq_t , bool *);
void uz_FOC_sample_hw_stub(l_struct_OC_uz_FOC *llvm_cbe_self, l_struct_OC___cosim_s1__ llvm_cbe_i_reference_Ampere, l_struct_OC___cosim_s1__ llvm_cbe_i_actual_Ampere, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t *llvm_cbe_u_output_Volts);
void apatb_uz_FOC_sample_sw(l_struct_OC_uz_FOC *llvm_cbe_self, l_struct_OC_uz_dq_t llvm_cbe_i_reference_Ampere, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t *llvm_cbe_u_output_Volts);
void apatb_uz_FOC_sample_hw(l_struct_OC_uz_FOC *, l_struct_OC___cosim_s1__ , l_struct_OC___cosim_s1__ , float , float , l_struct_OC_uz_dq_t *);
l_struct_OC_uz_dq_t uz_FOC_linear_decoupling(l_struct_OC_uz_PMSM_t , l_struct_OC_uz_dq_t , float );
float uz_PI_Controller_sample(l_struct_OC_uz_PI_Controller_config *, bool , float , float , bool );


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

void uz_FOC_sample(l_struct_OC_uz_FOC *llvm_cbe_self, l_struct_OC_uz_dq_t llvm_cbe_i_reference_Ampere, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t *llvm_cbe_u_output_Volts) {
  static  unsigned long long aesl_llvm_cbe_u_pre_limit_Volts_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_u_pre_limit_Volts;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_u_decoup_Volts_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_u_decoup_Volts;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_tmp__1;    /* Address-exposed local */
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
  static  unsigned long long aesl_llvm_cbe_i_reference_Ampere_2e_0_count = 0;
  float *llvm_cbe_i_reference_Ampere_2e_0;
  static  unsigned long long aesl_llvm_cbe_i_reference_Ampere_2e_0_2e_val_count = 0;
  float llvm_cbe_i_reference_Ampere_2e_0_2e_val;
  static  unsigned long long aesl_llvm_cbe_i_reference_Ampere_2e_1_count = 0;
  float *llvm_cbe_i_reference_Ampere_2e_1;
  static  unsigned long long aesl_llvm_cbe_i_reference_Ampere_2e_1_2e_val_count = 0;
  float llvm_cbe_i_reference_Ampere_2e_1_2e_val;
  static  unsigned long long aesl_llvm_cbe_i_reference_Ampere_2e_2_count = 0;
  float *llvm_cbe_i_reference_Ampere_2e_2;
  static  unsigned long long aesl_llvm_cbe_i_reference_Ampere_2e_2_2e_val_count = 0;
  float llvm_cbe_i_reference_Ampere_2e_2_2e_val;
  static  unsigned long long aesl_llvm_cbe_i_actual_Ampere_2e_0_count = 0;
  float *llvm_cbe_i_actual_Ampere_2e_0;
  static  unsigned long long aesl_llvm_cbe_i_actual_Ampere_2e_0_2e_val_count = 0;
  float llvm_cbe_i_actual_Ampere_2e_0_2e_val;
  static  unsigned long long aesl_llvm_cbe_i_actual_Ampere_2e_1_count = 0;
  float *llvm_cbe_i_actual_Ampere_2e_1;
  static  unsigned long long aesl_llvm_cbe_i_actual_Ampere_2e_1_2e_val_count = 0;
  float llvm_cbe_i_actual_Ampere_2e_1_2e_val;
  static  unsigned long long aesl_llvm_cbe_i_actual_Ampere_2e_2_count = 0;
  float *llvm_cbe_i_actual_Ampere_2e_2;
  static  unsigned long long aesl_llvm_cbe_i_actual_Ampere_2e_2_2e_val_count = 0;
  float llvm_cbe_i_actual_Ampere_2e_2_2e_val;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  signed int *llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  unsigned int llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  bool llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  l_struct_OC_uz_PMSM_t *llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  float *llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  float llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  float *llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  float llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  float llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  float *llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  float llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  float *llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  float llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  float llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  bool *llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  float *llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  float *llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  float llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  float *llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  float *llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  float llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  float *llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  float *llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  float llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_FOC_sample\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%i_reference_Ampere.0 = getelementptr %%struct.uz_dq_t* %%i_reference_Ampere, i64 0, i32  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_reference_Ampere_2e_0_count);
  llvm_cbe_i_reference_Ampere_2e_0 = (float *)(&llvm_cbe_i_reference_Ampere.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%i_reference_Ampere.0.val = load float* %%i_reference_Ampere.0, align  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_reference_Ampere_2e_0_2e_val_count);
  llvm_cbe_i_reference_Ampere_2e_0_2e_val = (float )*llvm_cbe_i_reference_Ampere_2e_0;
if (AESL_DEBUG_TRACE)
printf("\ni_reference_Ampere.0.val = %f,  0x%x\n", llvm_cbe_i_reference_Ampere_2e_0_2e_val, *(int*)(&llvm_cbe_i_reference_Ampere_2e_0_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  %%i_reference_Ampere.1 = getelementptr %%struct.uz_dq_t* %%i_reference_Ampere, i64 0, i32  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_reference_Ampere_2e_1_count);
  llvm_cbe_i_reference_Ampere_2e_1 = (float *)(&llvm_cbe_i_reference_Ampere.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%i_reference_Ampere.1.val = load float* %%i_reference_Ampere.1, align  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_reference_Ampere_2e_1_2e_val_count);
  llvm_cbe_i_reference_Ampere_2e_1_2e_val = (float )*llvm_cbe_i_reference_Ampere_2e_1;
if (AESL_DEBUG_TRACE)
printf("\ni_reference_Ampere.1.val = %f,  0x%x\n", llvm_cbe_i_reference_Ampere_2e_1_2e_val, *(int*)(&llvm_cbe_i_reference_Ampere_2e_1_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  %%i_reference_Ampere.2 = getelementptr %%struct.uz_dq_t* %%i_reference_Ampere, i64 0, i32  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_reference_Ampere_2e_2_count);
  llvm_cbe_i_reference_Ampere_2e_2 = (float *)(&llvm_cbe_i_reference_Ampere.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%i_reference_Ampere.2.val = load float* %%i_reference_Ampere.2, align  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_reference_Ampere_2e_2_2e_val_count);
  llvm_cbe_i_reference_Ampere_2e_2_2e_val = (float )*llvm_cbe_i_reference_Ampere_2e_2;
if (AESL_DEBUG_TRACE)
printf("\ni_reference_Ampere.2.val = %f,  0x%x\n", llvm_cbe_i_reference_Ampere_2e_2_2e_val, *(int*)(&llvm_cbe_i_reference_Ampere_2e_2_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  %%i_actual_Ampere.0 = getelementptr %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_actual_Ampere_2e_0_count);
  llvm_cbe_i_actual_Ampere_2e_0 = (float *)(&llvm_cbe_i_actual_Ampere.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%i_actual_Ampere.0.val = load float* %%i_actual_Ampere.0, align  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_actual_Ampere_2e_0_2e_val_count);
  llvm_cbe_i_actual_Ampere_2e_0_2e_val = (float )*llvm_cbe_i_actual_Ampere_2e_0;
if (AESL_DEBUG_TRACE)
printf("\ni_actual_Ampere.0.val = %f,  0x%x\n", llvm_cbe_i_actual_Ampere_2e_0_2e_val, *(int*)(&llvm_cbe_i_actual_Ampere_2e_0_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  %%i_actual_Ampere.1 = getelementptr %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_actual_Ampere_2e_1_count);
  llvm_cbe_i_actual_Ampere_2e_1 = (float *)(&llvm_cbe_i_actual_Ampere.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%i_actual_Ampere.1.val = load float* %%i_actual_Ampere.1, align  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_actual_Ampere_2e_1_2e_val_count);
  llvm_cbe_i_actual_Ampere_2e_1_2e_val = (float )*llvm_cbe_i_actual_Ampere_2e_1;
if (AESL_DEBUG_TRACE)
printf("\ni_actual_Ampere.1.val = %f,  0x%x\n", llvm_cbe_i_actual_Ampere_2e_1_2e_val, *(int*)(&llvm_cbe_i_actual_Ampere_2e_1_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  %%i_actual_Ampere.2 = getelementptr %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_actual_Ampere_2e_2_count);
  llvm_cbe_i_actual_Ampere_2e_2 = (float *)(&llvm_cbe_i_actual_Ampere.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%i_actual_Ampere.2.val = load float* %%i_actual_Ampere.2, align  for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_i_actual_Ampere_2e_2_2e_val_count);
  llvm_cbe_i_actual_Ampere_2e_2_2e_val = (float )*llvm_cbe_i_actual_Ampere_2e_2;
if (AESL_DEBUG_TRACE)
printf("\ni_actual_Ampere.2.val = %f,  0x%x\n", llvm_cbe_i_actual_Ampere_2e_2_2e_val, *(int*)(&llvm_cbe_i_actual_Ampere_2e_2_2e_val));
if (AESL_DEBUG_TRACE)
printf("\n  call fastcc void @aesl_internal_uz_FOC_CurrentControl(%%struct.uz_dq_t* sret %%u_pre_limit_Volts, %%struct.uz_FOC* %%self, float %%i_reference_Ampere.0.val, float %%i_reference_Ampere.1.val, float %%i_reference_Ampere.2.val, float %%i_actual_Ampere.0.val, float %%i_actual_Ampere.1.val, float %%i_actual_Ampere.2.val for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_17_count);
  llvm_cbe_u_pre_limit_Volts = aesl_internal_uz_FOC_CurrentControl((l_struct_OC_uz_FOC *)llvm_cbe_self, llvm_cbe_i_reference_Ampere_2e_0_2e_val, llvm_cbe_i_reference_Ampere_2e_1_2e_val, llvm_cbe_i_reference_Ampere_2e_2_2e_val, llvm_cbe_i_actual_Ampere_2e_0_2e_val, llvm_cbe_i_actual_Ampere_2e_1_2e_val, llvm_cbe_i_actual_Ampere_2e_2_2e_val);
if (AESL_DEBUG_TRACE) {
printf("\nArgument i_reference_Ampere.0.val = %f,  0x%x",llvm_cbe_i_reference_Ampere_2e_0_2e_val, *(int*)(&llvm_cbe_i_reference_Ampere_2e_0_2e_val));
printf("\nArgument i_reference_Ampere.1.val = %f,  0x%x",llvm_cbe_i_reference_Ampere_2e_1_2e_val, *(int*)(&llvm_cbe_i_reference_Ampere_2e_1_2e_val));
printf("\nArgument i_reference_Ampere.2.val = %f,  0x%x",llvm_cbe_i_reference_Ampere_2e_2_2e_val, *(int*)(&llvm_cbe_i_reference_Ampere_2e_2_2e_val));
printf("\nArgument i_actual_Ampere.0.val = %f,  0x%x",llvm_cbe_i_actual_Ampere_2e_0_2e_val, *(int*)(&llvm_cbe_i_actual_Ampere_2e_0_2e_val));
printf("\nArgument i_actual_Ampere.1.val = %f,  0x%x",llvm_cbe_i_actual_Ampere_2e_1_2e_val, *(int*)(&llvm_cbe_i_actual_Ampere_2e_1_2e_val));
printf("\nArgument i_actual_Ampere.2.val = %f,  0x%x",llvm_cbe_i_actual_Ampere_2e_2_2e_val, *(int*)(&llvm_cbe_i_actual_Ampere_2e_2_2e_val));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 0, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_19_count);
  llvm_cbe_tmp__2 = (signed int *)(&llvm_cbe_self->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = load i32* %%2, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_20_count);
  llvm_cbe_tmp__3 = (unsigned int )*llvm_cbe_tmp__2;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__3);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = trunc i32 %%3 to i1, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_21_count);
  llvm_cbe_tmp__4 = (bool )((((bool )(llvm_cbe_tmp__3&1U)&1U))&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 5, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_22_count);
  llvm_cbe_tmp__5 = (l_struct_OC_uz_PMSM_t *)(&llvm_cbe_self->field5);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call fastcc void @aesl_internal_uz_FOC_decoupling(%%struct.uz_dq_t* sret %%u_decoup_Volts, i1 zeroext %%4, %%struct.uz_PMSM_t* byval %%5, float %%i_actual_Ampere.0.val, float %%i_actual_Ampere.1.val, float %%i_actual_Ampere.2.val, float %%omega_el_rad_per_sec for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_23_count);
  llvm_cbe_u_decoup_Volts = aesl_internal_uz_FOC_decoupling(llvm_cbe_tmp__4, *(llvm_cbe_tmp__5), llvm_cbe_i_actual_Ampere_2e_0_2e_val, llvm_cbe_i_actual_Ampere_2e_1_2e_val, llvm_cbe_i_actual_Ampere_2e_2_2e_val, llvm_cbe_omega_el_rad_per_sec);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__4);
printf("\nArgument i_actual_Ampere.0.val = %f,  0x%x",llvm_cbe_i_actual_Ampere_2e_0_2e_val, *(int*)(&llvm_cbe_i_actual_Ampere_2e_0_2e_val));
printf("\nArgument i_actual_Ampere.1.val = %f,  0x%x",llvm_cbe_i_actual_Ampere_2e_1_2e_val, *(int*)(&llvm_cbe_i_actual_Ampere_2e_1_2e_val));
printf("\nArgument i_actual_Ampere.2.val = %f,  0x%x",llvm_cbe_i_actual_Ampere_2e_2_2e_val, *(int*)(&llvm_cbe_i_actual_Ampere_2e_2_2e_val));
printf("\nArgument omega_el_rad_per_sec = %f,  0x%x",llvm_cbe_omega_el_rad_per_sec, *(int*)(&llvm_cbe_omega_el_rad_per_sec));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.uz_dq_t* %%u_decoup_Volts, i64 0, i32 0, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_24_count);
  llvm_cbe_tmp__6 = (float *)(&llvm_cbe_u_decoup_Volts.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load float* %%6, align 4, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_25_count);
  llvm_cbe_tmp__7 = (float )*llvm_cbe_tmp__6;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__7, *(int*)(&llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds %%struct.uz_dq_t* %%u_pre_limit_Volts, i64 0, i32 0, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_26_count);
  llvm_cbe_tmp__8 = (float *)(&llvm_cbe_u_pre_limit_Volts.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load float* %%8, align 4, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_27_count);
  llvm_cbe_tmp__9 = (float )*llvm_cbe_tmp__8;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__9, *(int*)(&llvm_cbe_tmp__9));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = fadd float %%9, %%7, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_28_count);
  llvm_cbe_tmp__10 = (float )((float )(llvm_cbe_tmp__9 + llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__10, *(int*)(&llvm_cbe_tmp__10));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%10, float* %%8, align 4, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_29_count);
  *llvm_cbe_tmp__8 = llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__10);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds %%struct.uz_dq_t* %%u_decoup_Volts, i64 0, i32 1, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_30_count);
  llvm_cbe_tmp__11 = (float *)(&llvm_cbe_u_decoup_Volts.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = load float* %%11, align 4, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__12 = (float )*llvm_cbe_tmp__11;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__12, *(int*)(&llvm_cbe_tmp__12));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds %%struct.uz_dq_t* %%u_pre_limit_Volts, i64 0, i32 1, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_32_count);
  llvm_cbe_tmp__13 = (float *)(&llvm_cbe_u_pre_limit_Volts.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = load float* %%13, align 4, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_33_count);
  llvm_cbe_tmp__14 = (float )*llvm_cbe_tmp__13;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__14, *(int*)(&llvm_cbe_tmp__14));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = fadd float %%14, %%12, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__15 = (float )((float )(llvm_cbe_tmp__14 + llvm_cbe_tmp__12));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__15, *(int*)(&llvm_cbe_tmp__15));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%15, float* %%13, align 4, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_35_count);
  *llvm_cbe_tmp__13 = llvm_cbe_tmp__15;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__15);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 2, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__16 = (bool *)(&llvm_cbe_self->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @uz_FOC_SpaceVector_Limitation(%%struct.uz_dq_t* sret %%1, %%struct.uz_dq_t* byval %%u_pre_limit_Volts, float %%V_dc_volts, float %%omega_el_rad_per_sec, %%struct.uz_dq_t* byval %%i_actual_Ampere, i1* %%16) nounwind, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_37_count);
  llvm_cbe_tmp__1 = uz_FOC_SpaceVector_Limitation(llvm_cbe_u_pre_limit_Volts, llvm_cbe_V_dc_volts, llvm_cbe_omega_el_rad_per_sec, llvm_cbe_i_actual_Ampere, (bool *)llvm_cbe_tmp__16);
if (AESL_DEBUG_TRACE) {
printf("\nArgument V_dc_volts = %f,  0x%x",llvm_cbe_V_dc_volts, *(int*)(&llvm_cbe_V_dc_volts));
printf("\nArgument omega_el_rad_per_sec = %f,  0x%x",llvm_cbe_omega_el_rad_per_sec, *(int*)(&llvm_cbe_omega_el_rad_per_sec));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = getelementptr inbounds %%struct.uz_dq_t* %%u_output_Volts, i64 0, i32 0, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_38_count);
  llvm_cbe_tmp__17 = (float *)(&llvm_cbe_u_output_Volts->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 0, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_39_count);
  llvm_cbe_tmp__18 = (float *)(&llvm_cbe_tmp__1.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = load float* %%18, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_40_count);
  llvm_cbe_tmp__19 = (float )*llvm_cbe_tmp__18;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__19, *(int*)(&llvm_cbe_tmp__19));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%19, float* %%17, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_41_count);
  *llvm_cbe_tmp__17 = llvm_cbe_tmp__19;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__19);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds %%struct.uz_dq_t* %%u_output_Volts, i64 0, i32 1, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_42_count);
  llvm_cbe_tmp__20 = (float *)(&llvm_cbe_u_output_Volts->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 1, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_43_count);
  llvm_cbe_tmp__21 = (float *)(&llvm_cbe_tmp__1.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = load float* %%21, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_44_count);
  llvm_cbe_tmp__22 = (float )*llvm_cbe_tmp__21;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__22, *(int*)(&llvm_cbe_tmp__22));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%22, float* %%20, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_45_count);
  *llvm_cbe_tmp__20 = llvm_cbe_tmp__22;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = getelementptr inbounds %%struct.uz_dq_t* %%u_output_Volts, i64 0, i32 2, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__23 = (float *)(&llvm_cbe_u_output_Volts->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 2, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__24 = (float *)(&llvm_cbe_tmp__1.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = load float* %%24, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_48_count);
  llvm_cbe_tmp__25 = (float )*llvm_cbe_tmp__24;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__25, *(int*)(&llvm_cbe_tmp__25));
if (AESL_DEBUG_TRACE)
printf("\n  store float %%25, float* %%23, align 4, !dbg !11 for 0x%I64xth hint within @uz_FOC_sample  --> \n", ++aesl_llvm_cbe_49_count);
  *llvm_cbe_tmp__23 = llvm_cbe_tmp__25;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__25);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @uz_FOC_sample}\n");
  return;
}


static l_struct_OC_uz_dq_t aesl_internal_uz_FOC_CurrentControl(l_struct_OC_uz_FOC *llvm_cbe_self, float llvm_cbe_i_reference_Ampere_2e_0, float llvm_cbe_i_reference_Ampere_2e_1, float llvm_cbe_i_reference_Ampere_2e_2, float llvm_cbe_i_actual_Ampere_2e_0, float llvm_cbe_i_actual_Ampere_2e_1, float llvm_cbe_i_actual_Ampere_2e_2) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  l_struct_OC_uz_PI_Controller_config *llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  bool *llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  bool llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  bool *llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  bool llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  float llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  l_struct_OC_uz_PI_Controller_config *llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  bool llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  bool llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  float llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  float *llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  float *llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  float *llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @aesl_internal_uz_FOC_CurrentControl\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 4, !dbg !12 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_67_count);
  llvm_cbe_tmp__26 = (l_struct_OC_uz_PI_Controller_config *)(&llvm_cbe_self->field4);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 1, !dbg !12 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_68_count);
  llvm_cbe_tmp__27 = (bool *)(&llvm_cbe_self->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = load i1* %%2, align 1, !dbg !12 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_69_count);
  llvm_cbe_tmp__28 = (bool )((*llvm_cbe_tmp__27)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 2, !dbg !12 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_70_count);
  llvm_cbe_tmp__29 = (bool *)(&llvm_cbe_self->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load i1* %%4, align 1, !dbg !12 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_71_count);
  llvm_cbe_tmp__30 = (bool )((*llvm_cbe_tmp__29)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__30);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = tail call float @uz_PI_Controller_sample(%%struct.uz_PI_Controller_config* %%1, i1 zeroext %%3, float %%i_reference_Ampere.1, float %%i_actual_Ampere.1, i1 zeroext %%5) nounwind, !dbg !12 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_72_count);
  llvm_cbe_tmp__31 = (float ) /*tail*/ uz_PI_Controller_sample((l_struct_OC_uz_PI_Controller_config *)llvm_cbe_tmp__26, llvm_cbe_tmp__28, llvm_cbe_i_reference_Ampere_2e_1, llvm_cbe_i_actual_Ampere_2e_1, llvm_cbe_tmp__30);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__28);
printf("\nArgument i_reference_Ampere.1 = %f,  0x%x",llvm_cbe_i_reference_Ampere_2e_1, *(int*)(&llvm_cbe_i_reference_Ampere_2e_1));
printf("\nArgument i_actual_Ampere.1 = %f,  0x%x",llvm_cbe_i_actual_Ampere_2e_1, *(int*)(&llvm_cbe_i_actual_Ampere_2e_1));
printf("\nArgument  = 0x%X",llvm_cbe_tmp__30);
printf("\nReturn  = %f",llvm_cbe_tmp__31);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds %%struct.uz_FOC* %%self, i64 0, i32 3, !dbg !12 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__32 = (l_struct_OC_uz_PI_Controller_config *)(&llvm_cbe_self->field3);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load i1* %%2, align 1, !dbg !12 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__33 = (bool )((*llvm_cbe_tmp__27)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__33);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load i1* %%4, align 1, !dbg !12 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_76_count);
  llvm_cbe_tmp__34 = (bool )((*llvm_cbe_tmp__29)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = tail call float @uz_PI_Controller_sample(%%struct.uz_PI_Controller_config* %%7, i1 zeroext %%8, float %%i_reference_Ampere.0, float %%i_actual_Ampere.0, i1 zeroext %%9) nounwind, !dbg !12 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_77_count);
  llvm_cbe_tmp__35 = (float ) /*tail*/ uz_PI_Controller_sample((l_struct_OC_uz_PI_Controller_config *)llvm_cbe_tmp__32, llvm_cbe_tmp__33, llvm_cbe_i_reference_Ampere_2e_0, llvm_cbe_i_actual_Ampere_2e_0, llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__33);
printf("\nArgument i_reference_Ampere.0 = %f,  0x%x",llvm_cbe_i_reference_Ampere_2e_0, *(int*)(&llvm_cbe_i_reference_Ampere_2e_0));
printf("\nArgument i_actual_Ampere.0 = %f,  0x%x",llvm_cbe_i_actual_Ampere_2e_0, *(int*)(&llvm_cbe_i_actual_Ampere_2e_0));
printf("\nArgument  = 0x%X",llvm_cbe_tmp__34);
printf("\nReturn  = %f",llvm_cbe_tmp__35);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_79_count);
  llvm_cbe_tmp__36 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%10, float* %%11, align 4, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_80_count);
  *llvm_cbe_tmp__36 = llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__35);
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_81_count);
  llvm_cbe_tmp__37 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%6, float* %%12, align 4, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_82_count);
  *llvm_cbe_tmp__37 = llvm_cbe_tmp__31;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__38 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float 0.000000e+00, float* %%13, align 4, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_CurrentControl  --> \n", ++aesl_llvm_cbe_84_count);
  *llvm_cbe_tmp__38 = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x0p0);
if (AESL_DEBUG_TRACE)
    printf("\n END @aesl_internal_uz_FOC_CurrentControl }\n"); 
  return StructReturn;
}


static l_struct_OC_uz_dq_t aesl_internal_uz_FOC_decoupling(bool llvm_cbe_decoupling_select, l_struct_OC_uz_PMSM_t llvm_cbe_config_PMSM, float llvm_cbe_i_actual_Ampere_2e_0, float llvm_cbe_i_actual_Ampere_2e_1, float llvm_cbe_i_actual_Ampere_2e_2, float llvm_cbe_omega_el_rad_per_sec) {
  l_struct_OC_uz_dq_t StructReturn;  /* Struct return temporary */
  l_struct_OC_uz_dq_t *llvm_cbe_agg_2e_result = &StructReturn;
  static  unsigned long long aesl_llvm_cbe_i_actual_Ampere_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe__2e_0_count = 0;
  float *llvm_cbe__2e_0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_1_count = 0;
  float *llvm_cbe__2e_1;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_2_count = 0;
  float *llvm_cbe__2e_2;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  l_struct_OC_uz_dq_t llvm_cbe_tmp__39;    /* Address-exposed local */
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
  float *llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  float llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  float *llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  float llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  float *llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  float llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  float llvm_cbe_tmp__46;
  float llvm_cbe_tmp__46__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  float llvm_cbe_tmp__47;
  float llvm_cbe_tmp__47__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  float llvm_cbe_tmp__48;
  float llvm_cbe_tmp__48__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  float *llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  float *llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  float *llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @aesl_internal_uz_FOC_decoupling\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%.0 = getelementptr %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32  for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe__2e_0_count);
  llvm_cbe__2e_0 = (float *)(&llvm_cbe_i_actual_Ampere.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%i_actual_Ampere.0, float* %%.0, align  for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_86_count);
  *llvm_cbe__2e_0 = llvm_cbe_i_actual_Ampere_2e_0;
if (AESL_DEBUG_TRACE)
printf("\ni_actual_Ampere.0 = %f\n", llvm_cbe_i_actual_Ampere_2e_0);
if (AESL_DEBUG_TRACE)
printf("\n  %%.1 = getelementptr %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32  for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe__2e_1_count);
  llvm_cbe__2e_1 = (float *)(&llvm_cbe_i_actual_Ampere.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%i_actual_Ampere.1, float* %%.1, align  for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_87_count);
  *llvm_cbe__2e_1 = llvm_cbe_i_actual_Ampere_2e_1;
if (AESL_DEBUG_TRACE)
printf("\ni_actual_Ampere.1 = %f\n", llvm_cbe_i_actual_Ampere_2e_1);
if (AESL_DEBUG_TRACE)
printf("\n  %%.2 = getelementptr %%struct.uz_dq_t* %%i_actual_Ampere, i64 0, i32  for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe__2e_2_count);
  llvm_cbe__2e_2 = (float *)(&llvm_cbe_i_actual_Ampere.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%i_actual_Ampere.2, float* %%.2, align  for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_88_count);
  *llvm_cbe__2e_2 = llvm_cbe_i_actual_Ampere_2e_2;
if (AESL_DEBUG_TRACE)
printf("\ni_actual_Ampere.2 = %f\n", llvm_cbe_i_actual_Ampere_2e_2);
  if (llvm_cbe_decoupling_select) {
    goto llvm_cbe_tmp__52;
  } else {
    llvm_cbe_tmp__46__PHI_TEMPORARY = (float )0x0p0;   /* for PHI node */
    llvm_cbe_tmp__47__PHI_TEMPORARY = (float )0x0p0;   /* for PHI node */
    llvm_cbe_tmp__48__PHI_TEMPORARY = (float )0x0p0;   /* for PHI node */
    goto llvm_cbe_tmp__53;
  }

llvm_cbe_tmp__52:
if (AESL_DEBUG_TRACE)
printf("\n  call void @uz_FOC_linear_decoupling(%%struct.uz_dq_t* sret %%1, %%struct.uz_PMSM_t* byval %%config_PMSM, %%struct.uz_dq_t* byval %%i_actual_Ampere, float %%omega_el_rad_per_sec) nounwind, !dbg !11 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_100_count);
  llvm_cbe_tmp__39 = uz_FOC_linear_decoupling(llvm_cbe_config_PMSM, llvm_cbe_i_actual_Ampere, llvm_cbe_omega_el_rad_per_sec);
if (AESL_DEBUG_TRACE) {
printf("\nArgument omega_el_rad_per_sec = %f,  0x%x",llvm_cbe_omega_el_rad_per_sec, *(int*)(&llvm_cbe_omega_el_rad_per_sec));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 0, !dbg !11 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_101_count);
  llvm_cbe_tmp__40 = (float *)(&llvm_cbe_tmp__39.field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load float* %%3, align 4, !dbg !11 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_102_count);
  llvm_cbe_tmp__41 = (float )*llvm_cbe_tmp__40;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__41, *(int*)(&llvm_cbe_tmp__41));
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 1, !dbg !11 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_104_count);
  llvm_cbe_tmp__42 = (float *)(&llvm_cbe_tmp__39.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = load float* %%5, align 4, !dbg !11 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_105_count);
  llvm_cbe_tmp__43 = (float )*llvm_cbe_tmp__42;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__43, *(int*)(&llvm_cbe_tmp__43));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds %%struct.uz_dq_t* %%1, i64 0, i32 2, !dbg !11 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_107_count);
  llvm_cbe_tmp__44 = (float *)(&llvm_cbe_tmp__39.field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load float* %%7, align 4, !dbg !11 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__45 = (float )*llvm_cbe_tmp__44;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__45, *(int*)(&llvm_cbe_tmp__45));
  llvm_cbe_tmp__46__PHI_TEMPORARY = (float )llvm_cbe_tmp__45;   /* for PHI node */
  llvm_cbe_tmp__47__PHI_TEMPORARY = (float )llvm_cbe_tmp__43;   /* for PHI node */
  llvm_cbe_tmp__48__PHI_TEMPORARY = (float )llvm_cbe_tmp__41;   /* for PHI node */
  goto llvm_cbe_tmp__53;

llvm_cbe_tmp__53:
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = phi float [ 0.000000e+00, %%0 ], [ %%8, %%2  for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_111_count);
  llvm_cbe_tmp__46 = (float )llvm_cbe_tmp__46__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__46);
printf("\n = %f",0x0p0);
printf("\n = %f",llvm_cbe_tmp__45);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = phi float [ 0.000000e+00, %%0 ], [ %%6, %%2  for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_112_count);
  llvm_cbe_tmp__47 = (float )llvm_cbe_tmp__47__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__47);
printf("\n = %f",0x0p0);
printf("\n = %f",llvm_cbe_tmp__43);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = phi float [ 0.000000e+00, %%0 ], [ %%4, %%2  for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_113_count);
  llvm_cbe_tmp__48 = (float )llvm_cbe_tmp__48__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__48);
printf("\n = %f",0x0p0);
printf("\n = %f",llvm_cbe_tmp__41);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 0, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__49 = (float *)(&llvm_cbe_agg_2e_result->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%12, float* %%13, align 4, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_115_count);
  *llvm_cbe_tmp__49 = llvm_cbe_tmp__48;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__48);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 1, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_116_count);
  llvm_cbe_tmp__50 = (float *)(&llvm_cbe_agg_2e_result->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%11, float* %%14, align 4, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_117_count);
  *llvm_cbe_tmp__50 = llvm_cbe_tmp__47;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds %%struct.uz_dq_t* %%agg.result, i64 0, i32 2, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_118_count);
  llvm_cbe_tmp__51 = (float *)(&llvm_cbe_agg_2e_result->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store float %%10, float* %%15, align 4, !dbg !13 for 0x%I64xth hint within @aesl_internal_uz_FOC_decoupling  --> \n", ++aesl_llvm_cbe_119_count);
  *llvm_cbe_tmp__51 = llvm_cbe_tmp__46;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
    printf("\n END @aesl_internal_uz_FOC_decoupling }\n"); 
  return StructReturn;
}


void uz_FOC_sample_hw_stub(l_struct_OC_uz_FOC *llvm_cbe_self, l_struct_OC___cosim_s1__ llvm_cbe_i_reference_Ampere, l_struct_OC___cosim_s1__ llvm_cbe_i_actual_Ampere, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t *llvm_cbe_u_output_Volts) {
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  l_struct_OC_uz_dq_t *llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  l_struct_OC_uz_dq_t *llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @uz_FOC_sample_hw_stub\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = bitcast %%struct.__cosim_s1__* %%i_reference_Ampere to %%struct.uz_dq_t*, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample_hw_stub  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__54 = (l_struct_OC_uz_dq_t *)((l_struct_OC_uz_dq_t *)(&llvm_cbe_i_reference_Ampere));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = bitcast %%struct.__cosim_s1__* %%i_actual_Ampere to %%struct.uz_dq_t*, !dbg !12 for 0x%I64xth hint within @uz_FOC_sample_hw_stub  --> \n", ++aesl_llvm_cbe_129_count);
  llvm_cbe_tmp__55 = (l_struct_OC_uz_dq_t *)((l_struct_OC_uz_dq_t *)(&llvm_cbe_i_actual_Ampere));
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @uz_FOC_sample(%%struct.uz_FOC* %%self, %%struct.uz_dq_t* byval %%1, %%struct.uz_dq_t* byval %%2, float %%V_dc_volts, float %%omega_el_rad_per_sec, %%struct.uz_dq_t* %%u_output_Volts), !dbg !12 for 0x%I64xth hint within @uz_FOC_sample_hw_stub  --> \n", ++aesl_llvm_cbe_133_count);
   /*tail*/ uz_FOC_sample((l_struct_OC_uz_FOC *)llvm_cbe_self, *(llvm_cbe_tmp__54), *(llvm_cbe_tmp__55), llvm_cbe_V_dc_volts, llvm_cbe_omega_el_rad_per_sec, (l_struct_OC_uz_dq_t *)llvm_cbe_u_output_Volts);
if (AESL_DEBUG_TRACE) {
printf("\nArgument V_dc_volts = %f,  0x%x",llvm_cbe_V_dc_volts, *(int*)(&llvm_cbe_V_dc_volts));
printf("\nArgument omega_el_rad_per_sec = %f,  0x%x",llvm_cbe_omega_el_rad_per_sec, *(int*)(&llvm_cbe_omega_el_rad_per_sec));
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @uz_FOC_sample_hw_stub}\n");
  return;
}


void apatb_uz_FOC_sample_sw(l_struct_OC_uz_FOC *llvm_cbe_self, l_struct_OC_uz_dq_t llvm_cbe_i_reference_Ampere, l_struct_OC_uz_dq_t llvm_cbe_i_actual_Ampere, float llvm_cbe_V_dc_volts, float llvm_cbe_omega_el_rad_per_sec, l_struct_OC_uz_dq_t *llvm_cbe_u_output_Volts) {
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  l_struct_OC___cosim_s1__ *llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  l_struct_OC___cosim_s1__ *llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @apatb_uz_FOC_sample_sw\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = bitcast %%struct.uz_dq_t* %%i_reference_Ampere to %%struct.__cosim_s1__*, !dbg !12 for 0x%I64xth hint within @apatb_uz_FOC_sample_sw  --> \n", ++aesl_llvm_cbe_142_count);
  llvm_cbe_tmp__56 = (l_struct_OC___cosim_s1__ *)((l_struct_OC___cosim_s1__ *)(&llvm_cbe_i_reference_Ampere));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = bitcast %%struct.uz_dq_t* %%i_actual_Ampere to %%struct.__cosim_s1__*, !dbg !12 for 0x%I64xth hint within @apatb_uz_FOC_sample_sw  --> \n", ++aesl_llvm_cbe_143_count);
  llvm_cbe_tmp__57 = (l_struct_OC___cosim_s1__ *)((l_struct_OC___cosim_s1__ *)(&llvm_cbe_i_actual_Ampere));
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @apatb_uz_FOC_sample_hw(%%struct.uz_FOC* %%self, %%struct.__cosim_s1__* byval %%1, %%struct.__cosim_s1__* byval %%2, float %%V_dc_volts, float %%omega_el_rad_per_sec, %%struct.uz_dq_t* %%u_output_Volts) nounwind, !dbg !12 for 0x%I64xth hint within @apatb_uz_FOC_sample_sw  --> \n", ++aesl_llvm_cbe_147_count);
   /*tail*/ apatb_uz_FOC_sample_hw((l_struct_OC_uz_FOC *)llvm_cbe_self, *(llvm_cbe_tmp__56), *(llvm_cbe_tmp__57), llvm_cbe_V_dc_volts, llvm_cbe_omega_el_rad_per_sec, (l_struct_OC_uz_dq_t *)llvm_cbe_u_output_Volts);
if (AESL_DEBUG_TRACE) {
printf("\nArgument V_dc_volts = %f,  0x%x",llvm_cbe_V_dc_volts, *(int*)(&llvm_cbe_V_dc_volts));
printf("\nArgument omega_el_rad_per_sec = %f,  0x%x",llvm_cbe_omega_el_rad_per_sec, *(int*)(&llvm_cbe_omega_el_rad_per_sec));
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @apatb_uz_FOC_sample_sw}\n");
  return;
}

