// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XUZ_NN_ACC_H
#define XUZ_NN_ACC_H

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
#include "xuz_nn_acc_hw.h"

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
} XUz_nn_acc_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XUz_nn_acc;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XUz_nn_acc_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XUz_nn_acc_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XUz_nn_acc_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XUz_nn_acc_ReadReg(BaseAddress, RegOffset) \
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
int XUz_nn_acc_Initialize(XUz_nn_acc *InstancePtr, u16 DeviceId);
XUz_nn_acc_Config* XUz_nn_acc_LookupConfig(u16 DeviceId);
int XUz_nn_acc_CfgInitialize(XUz_nn_acc *InstancePtr, XUz_nn_acc_Config *ConfigPtr);
#else
int XUz_nn_acc_Initialize(XUz_nn_acc *InstancePtr, const char* InstanceName);
int XUz_nn_acc_Release(XUz_nn_acc *InstancePtr);
#endif

void XUz_nn_acc_Start(XUz_nn_acc *InstancePtr);
u32 XUz_nn_acc_IsDone(XUz_nn_acc *InstancePtr);
u32 XUz_nn_acc_IsIdle(XUz_nn_acc *InstancePtr);
u32 XUz_nn_acc_IsReady(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_EnableAutoRestart(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_DisableAutoRestart(XUz_nn_acc *InstancePtr);

void XUz_nn_acc_Set_Observation_Input(XUz_nn_acc *InstancePtr, u64 Data);
u64 XUz_nn_acc_Get_Observation_Input(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_L_1_Weights_input(XUz_nn_acc *InstancePtr, u64 Data);
u64 XUz_nn_acc_Get_L_1_Weights_input(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_L_2_Weights_input(XUz_nn_acc *InstancePtr, u64 Data);
u64 XUz_nn_acc_Get_L_2_Weights_input(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_L_3_Weights_input(XUz_nn_acc *InstancePtr, u64 Data);
u64 XUz_nn_acc_Get_L_3_Weights_input(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_L_Output_Weights_input(XUz_nn_acc *InstancePtr, u64 Data);
u64 XUz_nn_acc_Get_L_Output_Weights_input(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_Action_output(XUz_nn_acc *InstancePtr, u64 Data);
u64 XUz_nn_acc_Get_Action_output(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_L_1_Bias_input(XUz_nn_acc *InstancePtr, u64 Data);
u64 XUz_nn_acc_Get_L_1_Bias_input(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_L_2_Bias_input(XUz_nn_acc *InstancePtr, u64 Data);
u64 XUz_nn_acc_Get_L_2_Bias_input(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_L_3_Bias_input(XUz_nn_acc *InstancePtr, u64 Data);
u64 XUz_nn_acc_Get_L_3_Bias_input(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_L_Output_Bias_input(XUz_nn_acc *InstancePtr, u64 Data);
u64 XUz_nn_acc_Get_L_Output_Bias_input(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_copy_mats_flag(XUz_nn_acc *InstancePtr, u32 Data);
u32 XUz_nn_acc_Get_copy_mats_flag(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_Observation_size_input(XUz_nn_acc *InstancePtr, u32 Data);
u32 XUz_nn_acc_Get_Observation_size_input(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_Action_size_input(XUz_nn_acc *InstancePtr, u32 Data);
u32 XUz_nn_acc_Get_Action_size_input(XUz_nn_acc *InstancePtr);
u32 XUz_nn_acc_Get_copy_flag_out(XUz_nn_acc *InstancePtr);
u32 XUz_nn_acc_Get_matrices_updated_out(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_Set_compute_flag(XUz_nn_acc *InstancePtr, u32 Data);
u32 XUz_nn_acc_Get_compute_flag(XUz_nn_acc *InstancePtr);

void XUz_nn_acc_InterruptGlobalEnable(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_InterruptGlobalDisable(XUz_nn_acc *InstancePtr);
void XUz_nn_acc_InterruptEnable(XUz_nn_acc *InstancePtr, u32 Mask);
void XUz_nn_acc_InterruptDisable(XUz_nn_acc *InstancePtr, u32 Mask);
void XUz_nn_acc_InterruptClear(XUz_nn_acc *InstancePtr, u32 Mask);
u32 XUz_nn_acc_InterruptGetEnabled(XUz_nn_acc *InstancePtr);
u32 XUz_nn_acc_InterruptGetStatus(XUz_nn_acc *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
