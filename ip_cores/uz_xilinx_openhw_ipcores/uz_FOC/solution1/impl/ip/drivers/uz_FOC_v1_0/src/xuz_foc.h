// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XUZ_FOC_H
#define XUZ_FOC_H

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
#include "xuz_foc_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_BaseAddress;
} XUz_foc_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XUz_foc;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XUz_foc_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XUz_foc_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XUz_foc_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XUz_foc_ReadReg(BaseAddress, RegOffset) \
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
int XUz_foc_Initialize(XUz_foc *InstancePtr, u16 DeviceId);
XUz_foc_Config* XUz_foc_LookupConfig(u16 DeviceId);
int XUz_foc_CfgInitialize(XUz_foc *InstancePtr, XUz_foc_Config *ConfigPtr);
#else
int XUz_foc_Initialize(XUz_foc *InstancePtr, const char* InstanceName);
int XUz_foc_Release(XUz_foc *InstancePtr);
#endif


void XUz_foc_Set_sampletime(XUz_foc *InstancePtr, u32 Data);
u32 XUz_foc_Get_sampletime(XUz_foc *InstancePtr);
void XUz_foc_Set_set_i_d(XUz_foc *InstancePtr, u32 Data);
u32 XUz_foc_Get_set_i_d(XUz_foc *InstancePtr);
void XUz_foc_Set_set_i_q(XUz_foc *InstancePtr, u32 Data);
u32 XUz_foc_Get_set_i_q(XUz_foc *InstancePtr);
void XUz_foc_Set_KP_d(XUz_foc *InstancePtr, u32 Data);
u32 XUz_foc_Get_KP_d(XUz_foc *InstancePtr);
void XUz_foc_Set_KI_d(XUz_foc *InstancePtr, u32 Data);
u32 XUz_foc_Get_KI_d(XUz_foc *InstancePtr);
void XUz_foc_Set_KP_q(XUz_foc *InstancePtr, u32 Data);
u32 XUz_foc_Get_KP_q(XUz_foc *InstancePtr);
void XUz_foc_Set_KI_q(XUz_foc *InstancePtr, u32 Data);
u32 XUz_foc_Get_KI_q(XUz_foc *InstancePtr);
void XUz_foc_Set_reset_PS(XUz_foc *InstancePtr, u32 Data);
u32 XUz_foc_Get_reset_PS(XUz_foc *InstancePtr);
void XUz_foc_Set_limit(XUz_foc *InstancePtr, u32 Data);
u32 XUz_foc_Get_limit(XUz_foc *InstancePtr);
u32 XUz_foc_Get_out_KP_d(XUz_foc *InstancePtr);
u32 XUz_foc_Get_out_KP_d_vld(XUz_foc *InstancePtr);
u32 XUz_foc_Get_out_idref(XUz_foc *InstancePtr);
u32 XUz_foc_Get_out_idref_vld(XUz_foc *InstancePtr);
u32 XUz_foc_Get_out_status(XUz_foc *InstancePtr);
u32 XUz_foc_Get_out_status_vld(XUz_foc *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
