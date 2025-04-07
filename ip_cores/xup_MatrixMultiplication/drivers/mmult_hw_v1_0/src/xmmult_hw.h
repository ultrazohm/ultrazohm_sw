// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XMMULT_HW_H
#define XMMULT_HW_H

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
#include "xmmult_hw_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Ctrl_BaseAddress;
} XMmult_hw_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XMmult_hw;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XMmult_hw_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XMmult_hw_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XMmult_hw_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XMmult_hw_ReadReg(BaseAddress, RegOffset) \
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
int XMmult_hw_Initialize(XMmult_hw *InstancePtr, u16 DeviceId);
XMmult_hw_Config* XMmult_hw_LookupConfig(u16 DeviceId);
int XMmult_hw_CfgInitialize(XMmult_hw *InstancePtr, XMmult_hw_Config *ConfigPtr);
#else
int XMmult_hw_Initialize(XMmult_hw *InstancePtr, const char* InstanceName);
int XMmult_hw_Release(XMmult_hw *InstancePtr);
#endif

void XMmult_hw_Start(XMmult_hw *InstancePtr);
u32 XMmult_hw_IsDone(XMmult_hw *InstancePtr);
u32 XMmult_hw_IsIdle(XMmult_hw *InstancePtr);
u32 XMmult_hw_IsReady(XMmult_hw *InstancePtr);
void XMmult_hw_EnableAutoRestart(XMmult_hw *InstancePtr);
void XMmult_hw_DisableAutoRestart(XMmult_hw *InstancePtr);

void XMmult_hw_Set_in1(XMmult_hw *InstancePtr, u64 Data);
u64 XMmult_hw_Get_in1(XMmult_hw *InstancePtr);
void XMmult_hw_Set_in2(XMmult_hw *InstancePtr, u64 Data);
u64 XMmult_hw_Get_in2(XMmult_hw *InstancePtr);
void XMmult_hw_Set_out_r(XMmult_hw *InstancePtr, u64 Data);
u64 XMmult_hw_Get_out_r(XMmult_hw *InstancePtr);
void XMmult_hw_Set_dim(XMmult_hw *InstancePtr, u32 Data);
u32 XMmult_hw_Get_dim(XMmult_hw *InstancePtr);

void XMmult_hw_InterruptGlobalEnable(XMmult_hw *InstancePtr);
void XMmult_hw_InterruptGlobalDisable(XMmult_hw *InstancePtr);
void XMmult_hw_InterruptEnable(XMmult_hw *InstancePtr, u32 Mask);
void XMmult_hw_InterruptDisable(XMmult_hw *InstancePtr, u32 Mask);
void XMmult_hw_InterruptClear(XMmult_hw *InstancePtr, u32 Mask);
u32 XMmult_hw_InterruptGetEnabled(XMmult_hw *InstancePtr);
u32 XMmult_hw_InterruptGetStatus(XMmult_hw *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
