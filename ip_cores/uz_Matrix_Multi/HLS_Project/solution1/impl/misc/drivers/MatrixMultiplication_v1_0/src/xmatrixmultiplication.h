// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XMATRIXMULTIPLICATION_H
#define XMATRIXMULTIPLICATION_H

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
#include "xmatrixmultiplication_hw.h"

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
} XMatrixmultiplication_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XMatrixmultiplication;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XMatrixmultiplication_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XMatrixmultiplication_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XMatrixmultiplication_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XMatrixmultiplication_ReadReg(BaseAddress, RegOffset) \
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
int XMatrixmultiplication_Initialize(XMatrixmultiplication *InstancePtr, u16 DeviceId);
XMatrixmultiplication_Config* XMatrixmultiplication_LookupConfig(u16 DeviceId);
int XMatrixmultiplication_CfgInitialize(XMatrixmultiplication *InstancePtr, XMatrixmultiplication_Config *ConfigPtr);
#else
int XMatrixmultiplication_Initialize(XMatrixmultiplication *InstancePtr, const char* InstanceName);
int XMatrixmultiplication_Release(XMatrixmultiplication *InstancePtr);
#endif

void XMatrixmultiplication_Start(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_IsDone(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_IsIdle(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_IsReady(XMatrixmultiplication *InstancePtr);
void XMatrixmultiplication_Continue(XMatrixmultiplication *InstancePtr);
void XMatrixmultiplication_EnableAutoRestart(XMatrixmultiplication *InstancePtr);
void XMatrixmultiplication_DisableAutoRestart(XMatrixmultiplication *InstancePtr);

void XMatrixmultiplication_Set_A_rows(XMatrixmultiplication *InstancePtr, u64 Data);
u64 XMatrixmultiplication_Get_A_rows(XMatrixmultiplication *InstancePtr);
void XMatrixmultiplication_Set_B_rows(XMatrixmultiplication *InstancePtr, u64 Data);
u64 XMatrixmultiplication_Get_B_rows(XMatrixmultiplication *InstancePtr);
void XMatrixmultiplication_Set_B_columns(XMatrixmultiplication *InstancePtr, u64 Data);
u64 XMatrixmultiplication_Get_B_columns(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_A_BaseAddress(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_A_HighAddress(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_A_TotalBytes(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_A_BitWidth(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_A_Depth(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Write_A_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length);
u32 XMatrixmultiplication_Read_A_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length);
u32 XMatrixmultiplication_Write_A_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length);
u32 XMatrixmultiplication_Read_A_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length);
u32 XMatrixmultiplication_Get_C_out_BaseAddress(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_C_out_HighAddress(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_C_out_TotalBytes(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_C_out_BitWidth(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_C_out_Depth(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Write_C_out_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length);
u32 XMatrixmultiplication_Read_C_out_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length);
u32 XMatrixmultiplication_Write_C_out_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length);
u32 XMatrixmultiplication_Read_C_out_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length);
u32 XMatrixmultiplication_Get_B_BaseAddress(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_B_HighAddress(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_B_TotalBytes(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_B_BitWidth(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Get_B_Depth(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_Write_B_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length);
u32 XMatrixmultiplication_Read_B_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length);
u32 XMatrixmultiplication_Write_B_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length);
u32 XMatrixmultiplication_Read_B_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length);

void XMatrixmultiplication_InterruptGlobalEnable(XMatrixmultiplication *InstancePtr);
void XMatrixmultiplication_InterruptGlobalDisable(XMatrixmultiplication *InstancePtr);
void XMatrixmultiplication_InterruptEnable(XMatrixmultiplication *InstancePtr, u32 Mask);
void XMatrixmultiplication_InterruptDisable(XMatrixmultiplication *InstancePtr, u32 Mask);
void XMatrixmultiplication_InterruptClear(XMatrixmultiplication *InstancePtr, u32 Mask);
u32 XMatrixmultiplication_InterruptGetEnabled(XMatrixmultiplication *InstancePtr);
u32 XMatrixmultiplication_InterruptGetStatus(XMatrixmultiplication *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
