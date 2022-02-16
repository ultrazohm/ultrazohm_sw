// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XBGD_H
#define XBGD_H

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
#include "xbgd_hw.h"

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
} XBgd_Config;
#endif

typedef struct {
    u32 Control_BaseAddress;
    u32 IsReady;
} XBgd;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XBgd_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XBgd_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XBgd_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XBgd_ReadReg(BaseAddress, RegOffset) \
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
int XBgd_Initialize(XBgd *InstancePtr, u16 DeviceId);
XBgd_Config* XBgd_LookupConfig(u16 DeviceId);
int XBgd_CfgInitialize(XBgd *InstancePtr, XBgd_Config *ConfigPtr);
#else
int XBgd_Initialize(XBgd *InstancePtr, const char* InstanceName);
int XBgd_Release(XBgd *InstancePtr);
#endif

void XBgd_Start(XBgd *InstancePtr);
u32 XBgd_IsDone(XBgd *InstancePtr);
u32 XBgd_IsIdle(XBgd *InstancePtr);
u32 XBgd_IsReady(XBgd *InstancePtr);
void XBgd_EnableAutoRestart(XBgd *InstancePtr);
void XBgd_DisableAutoRestart(XBgd *InstancePtr);

void XBgd_Set_axiMlpResultsInput(XBgd *InstancePtr, u64 Data);
u64 XBgd_Get_axiMlpResultsInput(XBgd *InstancePtr);
void XBgd_Set_axiClassesInput(XBgd *InstancePtr, u64 Data);
u64 XBgd_Get_axiClassesInput(XBgd *InstancePtr);
void XBgd_Set_axiWeightInput(XBgd *InstancePtr, u64 Data);
u64 XBgd_Get_axiWeightInput(XBgd *InstancePtr);
void XBgd_Set_axiBiasInput(XBgd *InstancePtr, u64 Data);
u64 XBgd_Get_axiBiasInput(XBgd *InstancePtr);
void XBgd_Set_axiWeightOutput(XBgd *InstancePtr, u64 Data);
u64 XBgd_Get_axiWeightOutput(XBgd *InstancePtr);
void XBgd_Set_axiBiasOutput(XBgd *InstancePtr, u64 Data);
u64 XBgd_Get_axiBiasOutput(XBgd *InstancePtr);
void XBgd_Set_numberInputs(XBgd *InstancePtr, u32 Data);
u32 XBgd_Get_numberInputs(XBgd *InstancePtr);
void XBgd_Set_numberOutputs(XBgd *InstancePtr, u32 Data);
u32 XBgd_Get_numberOutputs(XBgd *InstancePtr);
void XBgd_Set_numberLayers(XBgd *InstancePtr, u32 Data);
u32 XBgd_Get_numberLayers(XBgd *InstancePtr);
void XBgd_Set_numberNeurons(XBgd *InstancePtr, u32 Data);
u32 XBgd_Get_numberNeurons(XBgd *InstancePtr);
void XBgd_Set_loadParameters(XBgd *InstancePtr, u32 Data);
u32 XBgd_Get_loadParameters(XBgd *InstancePtr);
void XBgd_Set_batchSize(XBgd *InstancePtr, u32 Data);
u32 XBgd_Get_batchSize(XBgd *InstancePtr);
void XBgd_Set_learningRate(XBgd *InstancePtr, u32 Data);
u32 XBgd_Get_learningRate(XBgd *InstancePtr);

void XBgd_InterruptGlobalEnable(XBgd *InstancePtr);
void XBgd_InterruptGlobalDisable(XBgd *InstancePtr);
void XBgd_InterruptEnable(XBgd *InstancePtr, u32 Mask);
void XBgd_InterruptDisable(XBgd *InstancePtr, u32 Mask);
void XBgd_InterruptClear(XBgd *InstancePtr, u32 Mask);
u32 XBgd_InterruptGetEnabled(XBgd *InstancePtr);
u32 XBgd_InterruptGetStatus(XBgd *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
