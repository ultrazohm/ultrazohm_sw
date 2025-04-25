// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XUZ_NN_H
#define XUZ_NN_H

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
#include "xuz_nn_hw.h"

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
} XUz_nn_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XUz_nn;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XUz_nn_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XUz_nn_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XUz_nn_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XUz_nn_ReadReg(BaseAddress, RegOffset) \
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
int XUz_nn_Initialize(XUz_nn *InstancePtr, u16 DeviceId);
XUz_nn_Config* XUz_nn_LookupConfig(u16 DeviceId);
int XUz_nn_CfgInitialize(XUz_nn *InstancePtr, XUz_nn_Config *ConfigPtr);
#else
int XUz_nn_Initialize(XUz_nn *InstancePtr, const char* InstanceName);
int XUz_nn_Release(XUz_nn *InstancePtr);
#endif

void XUz_nn_Start(XUz_nn *InstancePtr);
u32 XUz_nn_IsDone(XUz_nn *InstancePtr);
u32 XUz_nn_IsIdle(XUz_nn *InstancePtr);
u32 XUz_nn_IsReady(XUz_nn *InstancePtr);
void XUz_nn_EnableAutoRestart(XUz_nn *InstancePtr);
void XUz_nn_DisableAutoRestart(XUz_nn *InstancePtr);

void XUz_nn_Set_A_input(XUz_nn *InstancePtr, u64 Data);
u64 XUz_nn_Get_A_input(XUz_nn *InstancePtr);
void XUz_nn_Set_B1_input(XUz_nn *InstancePtr, u64 Data);
u64 XUz_nn_Get_B1_input(XUz_nn *InstancePtr);
void XUz_nn_Set_B2_input(XUz_nn *InstancePtr, u64 Data);
u64 XUz_nn_Get_B2_input(XUz_nn *InstancePtr);
void XUz_nn_Set_B3_input(XUz_nn *InstancePtr, u64 Data);
u64 XUz_nn_Get_B3_input(XUz_nn *InstancePtr);
void XUz_nn_Set_B4_input(XUz_nn *InstancePtr, u64 Data);
u64 XUz_nn_Get_B4_input(XUz_nn *InstancePtr);
void XUz_nn_Set_C_output(XUz_nn *InstancePtr, u64 Data);
u64 XUz_nn_Get_C_output(XUz_nn *InstancePtr);
void XUz_nn_Set_Bias1_input(XUz_nn *InstancePtr, u64 Data);
u64 XUz_nn_Get_Bias1_input(XUz_nn *InstancePtr);
void XUz_nn_Set_Bias2_input(XUz_nn *InstancePtr, u64 Data);
u64 XUz_nn_Get_Bias2_input(XUz_nn *InstancePtr);
void XUz_nn_Set_Bias3_input(XUz_nn *InstancePtr, u64 Data);
u64 XUz_nn_Get_Bias3_input(XUz_nn *InstancePtr);
void XUz_nn_Set_Bias4_input(XUz_nn *InstancePtr, u64 Data);
u64 XUz_nn_Get_Bias4_input(XUz_nn *InstancePtr);
void XUz_nn_Set_copy_mats_flag(XUz_nn *InstancePtr, u32 Data);
u32 XUz_nn_Get_copy_mats_flag(XUz_nn *InstancePtr);
void XUz_nn_Set_A_rows(XUz_nn *InstancePtr, u32 Data);
u32 XUz_nn_Get_A_rows(XUz_nn *InstancePtr);
void XUz_nn_Set_B1_rows(XUz_nn *InstancePtr, u32 Data);
u32 XUz_nn_Get_B1_rows(XUz_nn *InstancePtr);
void XUz_nn_Set_B1_columns(XUz_nn *InstancePtr, u32 Data);
u32 XUz_nn_Get_B1_columns(XUz_nn *InstancePtr);
void XUz_nn_Set_B2_columns(XUz_nn *InstancePtr, u32 Data);
u32 XUz_nn_Get_B2_columns(XUz_nn *InstancePtr);
u32 XUz_nn_Get_copy_flag_out(XUz_nn *InstancePtr);
u32 XUz_nn_Get_matrices_updated_out(XUz_nn *InstancePtr);

void XUz_nn_InterruptGlobalEnable(XUz_nn *InstancePtr);
void XUz_nn_InterruptGlobalDisable(XUz_nn *InstancePtr);
void XUz_nn_InterruptEnable(XUz_nn *InstancePtr, u32 Mask);
void XUz_nn_InterruptDisable(XUz_nn *InstancePtr, u32 Mask);
void XUz_nn_InterruptClear(XUz_nn *InstancePtr, u32 Mask);
u32 XUz_nn_InterruptGetEnabled(XUz_nn *InstancePtr);
u32 XUz_nn_InterruptGetStatus(XUz_nn *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
