// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XUZ_FOC_SAMPLE_H
#define XUZ_FOC_SAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xuz_foc_sample_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
    u32 Din_BaseAddress;
} XUz_foc_sample_Config;
#endif

typedef struct {
    u32 Control_BaseAddress;
    u32 Din_BaseAddress;
    u32 IsReady;
} XUz_foc_sample;

typedef u32 word_type;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
    u32 word_3;
    u32 word_4;
} XUz_foc_sample_Controller_id;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
    u32 word_3;
    u32 word_4;
} XUz_foc_sample_Controller_iq;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
    u32 word_3;
    u32 word_4;
    u32 word_5;
    u32 word_6;
    u32 word_7;
    u32 word_8;
} XUz_foc_sample_Self_i;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
    u32 word_3;
    u32 word_4;
    u32 word_5;
    u32 word_6;
    u32 word_7;
    u32 word_8;
} XUz_foc_sample_Self_o;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
} XUz_foc_sample_I_actual_ampere;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
} XUz_foc_sample_I_reference_ampere;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XUz_foc_sample_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XUz_foc_sample_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XUz_foc_sample_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XUz_foc_sample_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XUz_foc_sample_Initialize(XUz_foc_sample *InstancePtr, u16 DeviceId);
XUz_foc_sample_Config* XUz_foc_sample_LookupConfig(u16 DeviceId);
int XUz_foc_sample_CfgInitialize(XUz_foc_sample *InstancePtr, XUz_foc_sample_Config *ConfigPtr);
#else
int XUz_foc_sample_Initialize(XUz_foc_sample *InstancePtr, const char* InstanceName);
int XUz_foc_sample_Release(XUz_foc_sample *InstancePtr);
#endif

void XUz_foc_sample_Start(XUz_foc_sample *InstancePtr);
u32 XUz_foc_sample_IsDone(XUz_foc_sample *InstancePtr);
u32 XUz_foc_sample_IsIdle(XUz_foc_sample *InstancePtr);
u32 XUz_foc_sample_IsReady(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_EnableAutoRestart(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_DisableAutoRestart(XUz_foc_sample *InstancePtr);

void XUz_foc_sample_Set_output_volts_d(XUz_foc_sample *InstancePtr, u64 Data);
u64 XUz_foc_sample_Get_output_volts_d(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_Set_output_volts_q(XUz_foc_sample *InstancePtr, u64 Data);
u64 XUz_foc_sample_Get_output_volts_q(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_Set_Controller_id(XUz_foc_sample *InstancePtr, XUz_foc_sample_Controller_id Data);
XUz_foc_sample_Controller_id XUz_foc_sample_Get_Controller_id(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_Set_Controller_iq(XUz_foc_sample *InstancePtr, XUz_foc_sample_Controller_iq Data);
XUz_foc_sample_Controller_iq XUz_foc_sample_Get_Controller_iq(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_Set_self_i(XUz_foc_sample *InstancePtr, XUz_foc_sample_Self_i Data);
XUz_foc_sample_Self_i XUz_foc_sample_Get_self_i(XUz_foc_sample *InstancePtr);
XUz_foc_sample_Self_o XUz_foc_sample_Get_self_o(XUz_foc_sample *InstancePtr);
u32 XUz_foc_sample_Get_self_o_vld(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_Set_i_actual_Ampere(XUz_foc_sample *InstancePtr, XUz_foc_sample_I_actual_ampere Data);
XUz_foc_sample_I_actual_ampere XUz_foc_sample_Get_i_actual_Ampere(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_Set_V_dc_volts(XUz_foc_sample *InstancePtr, u32 Data);
u32 XUz_foc_sample_Get_V_dc_volts(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_Set_omega_el_rad_per_sec(XUz_foc_sample *InstancePtr, u32 Data);
u32 XUz_foc_sample_Get_omega_el_rad_per_sec(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_Set_i_reference_Ampere(XUz_foc_sample *InstancePtr, XUz_foc_sample_I_reference_ampere Data);
XUz_foc_sample_I_reference_ampere XUz_foc_sample_Get_i_reference_Ampere(XUz_foc_sample *InstancePtr);

void XUz_foc_sample_InterruptGlobalEnable(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_InterruptGlobalDisable(XUz_foc_sample *InstancePtr);
void XUz_foc_sample_InterruptEnable(XUz_foc_sample *InstancePtr, u32 Mask);
void XUz_foc_sample_InterruptDisable(XUz_foc_sample *InstancePtr, u32 Mask);
void XUz_foc_sample_InterruptClear(XUz_foc_sample *InstancePtr, u32 Mask);
u32 XUz_foc_sample_InterruptGetEnabled(XUz_foc_sample *InstancePtr);
u32 XUz_foc_sample_InterruptGetStatus(XUz_foc_sample *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
