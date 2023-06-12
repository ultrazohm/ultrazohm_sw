// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
# 1 "C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_PI_controller/uz_PI_controller.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_PI_controller/uz_PI_controller.cpp"
# 1 "C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_PI_controller/uz_PI_controller.h" 1
# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/6.2.0/include/stdint.h" 1 3 4
# 10 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/6.2.0/include/stdint.h" 3 4
# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/stdint.h" 1 3 4
# 29 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/stdint.h" 3 4
# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 1 3 4
# 11 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 3 4
# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 1 3 4
# 13 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3 4
# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw_mac.h" 1 3 4
# 89 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw_mac.h" 3 4
             
# 98 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw_mac.h" 3 4
             
# 14 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3 4
# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw_secapi.h" 1 3 4
# 45 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw_secapi.h" 3 4

# 45 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw_secapi.h" 3 4
extern "C++" {
template <bool __test, typename __dsttype>
  struct __if_array;
template <typename __dsttype>
  struct __if_array <true, __dsttype> {
    typedef __dsttype __type;
};
}
# 15 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3 4
# 276 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3 4
# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/vadefs.h" 1 3 4
# 10 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/vadefs.h" 3 4
# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 1 3 4
# 566 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3 4
# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/sdks/_mingw_directx.h" 1 3 4
# 567 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3 4
# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/sdks/_mingw_ddk.h" 1 3 4
# 568 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3 4
# 11 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/vadefs.h" 2 3 4




#pragma pack(push,_CRT_PACKING)



extern "C" {





  typedef __builtin_va_list __gnuc_va_list;






  typedef __gnuc_va_list va_list;
# 100 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/vadefs.h" 3 4
}



#pragma pack(pop)
# 277 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3 4
# 535 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3 4
extern "C" {




void __attribute__((__cdecl__)) __debugbreak(void);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __debugbreak(void)
{
  __asm__ __volatile__("int {$}3":);
}




const char *__mingw_get_crt_info (void);


}
# 12 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 2 3 4




#pragma pack(push,_CRT_PACKING)
# 36 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 3 4
__extension__ typedef unsigned long long size_t;
# 46 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 3 4
__extension__ typedef long long ssize_t;






typedef size_t rsize_t;
# 63 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 3 4
__extension__ typedef long long intptr_t;
# 76 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 3 4
__extension__ typedef unsigned long long uintptr_t;
# 89 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 3 4
__extension__ typedef long long ptrdiff_t;
# 107 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 3 4
typedef unsigned short wint_t;
typedef unsigned short wctype_t;





typedef int errno_t;




typedef long __time32_t;




__extension__ typedef long long __time64_t;
# 139 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 3 4
typedef __time64_t time_t;
# 423 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 3 4
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







#pragma pack(pop)
# 30 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/stdint.h" 2 3 4



# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/6.2.0/include/stddef.h" 1 3 4

# 1 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/stddef.h" 1 3 4
# 14 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/stddef.h" 3 4
extern "C" {




  __attribute__ ((__dllimport__)) extern int *__attribute__((__cdecl__)) _errno(void);

  errno_t __attribute__((__cdecl__)) _set_errno(int _Value);
  errno_t __attribute__((__cdecl__)) _get_errno(int *_Value);


  __attribute__ ((__dllimport__)) extern unsigned long __attribute__((__cdecl__)) __threadid(void);

  __attribute__ ((__dllimport__)) extern uintptr_t __attribute__((__cdecl__)) __threadhandle(void);


}
# 3 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/6.2.0/include/stddef.h" 2 3 4
# 428 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/6.2.0/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;






  typedef decltype(nullptr) nullptr_t;
# 34 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/x86_64-w64-mingw32/include/stdint.h" 2 3 4


typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned uint32_t;
__extension__ typedef long long int64_t;
__extension__ typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef short int_least16_t;
typedef unsigned short uint_least16_t;
typedef int int_least32_t;
typedef unsigned uint_least32_t;
__extension__ typedef long long int_least64_t;
__extension__ typedef unsigned long long uint_least64_t;





typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef short int_fast16_t;
typedef unsigned short uint_fast16_t;
typedef int int_fast32_t;
typedef unsigned int uint_fast32_t;
__extension__ typedef long long int_fast64_t;
__extension__ typedef unsigned long long uint_fast64_t;


__extension__ typedef long long intmax_t;
__extension__ typedef unsigned long long uintmax_t;
# 11 "C:/Xilinx/Vitis_HLS/2022.2/tps/win64/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/6.2.0/include/stdint.h" 2 3 4
# 2 "C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_PI_controller/uz_PI_controller.h" 2

# 2 "C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_PI_controller/uz_PI_controller.h"
float limit_value(float value, float limit);
float uz_PI_controller(float referenceValue, float actualValue, float sampletime, float KI, float KP, float limit, bool reset, float *axi_referenceValue, float *axi_actualValue, float *error, float *P_sum);
# 2 "C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_PI_controller/uz_PI_controller.cpp" 2
float uz_PI_controller(float referenceValue, float actualValue, float sampletime, float KI, float KP, float limit, bool reset, float *axi_referenceValue, float *axi_actualValue, float *error, float *P_sum){
#pragma HLS INTERFACE mode=s_axilite port=referenceValue
#pragma HLS INTERFACE mode=ap_none port=actualValue
#pragma HLS INTERFACE mode=s_axilite port=sampletime
#pragma HLS INTERFACE mode=s_axilite port=KI
#pragma HLS INTERFACE mode=s_axilite port=KP
#pragma HLS INTERFACE mode=s_axilite port=limit
#pragma HLS INTERFACE mode=s_axilite port=reset
#pragma HLS INTERFACE mode=s_axilite port=axi_referenceValue
#pragma HLS INTERFACE mode=s_axilite port=axi_actualValue
#pragma HLS INTERFACE mode=s_axilite port=error
#pragma HLS INTERFACE mode=s_axilite port=P_sum
#pragma HLS INTERFACE mode=ap_none port=return

 static float I_sum;
 float out;
 if(reset){
  I_sum = 0.0f;
  out = 0.0f;
 }else{
  *error = referenceValue - actualValue;
  *P_sum = *error * KP;
  float preIntegrator = *error * KI;
  out = limit_value(I_sum+*P_sum, limit);
  I_sum += preIntegrator * sampletime;
 }
*axi_referenceValue = referenceValue;
*axi_actualValue = actualValue;
 return out;
}
#ifndef HLS_FASTSIM
#ifdef __cplusplus
extern "C"
#endif
float apatb_uz_PI_controller_ir(float, float, float, float, float, float, bool, float *, float *, float *, float *);
#ifdef __cplusplus
extern "C"
#endif
float uz_PI_controller_hw_stub(float referenceValue, float actualValue, float sampletime, float KI, float KP, float limit, bool reset, float *axi_referenceValue, float *axi_actualValue, float *error, float *P_sum){
float _ret = uz_PI_controller(referenceValue, actualValue, sampletime, KI, KP, limit, reset, axi_referenceValue, axi_actualValue, error, P_sum);
return _ret;
}
#ifdef __cplusplus
extern "C"
#endif
float apatb_uz_PI_controller_sw(float referenceValue, float actualValue, float sampletime, float KI, float KP, float limit, bool reset, float *axi_referenceValue, float *axi_actualValue, float *error, float *P_sum){
float _ret = apatb_uz_PI_controller_ir(referenceValue, actualValue, sampletime, KI, KP, limit, reset, axi_referenceValue, axi_actualValue, error, P_sum);
return _ret;
}
#endif
# 31 "C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_PI_controller/uz_PI_controller.cpp"


float limit_value(float value, float limit){
 if(value > limit)
  value = limit;
 else if(value < -1*limit){
  value = -1*limit;
 }
 return value;
}
