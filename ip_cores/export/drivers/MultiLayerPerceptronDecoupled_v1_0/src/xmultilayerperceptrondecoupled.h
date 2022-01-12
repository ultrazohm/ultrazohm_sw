// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XMULTILAYERPERCEPTRONDECOUPLED_H
#define XMULTILAYERPERCEPTRONDECOUPLED_H

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
#include "xmultilayerperceptrondecoupled_hw.h"

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
    u32 Configuration_BaseAddress;
} XMultilayerperceptrondecoupled_Config;
#endif

typedef struct {
    u32 Control_BaseAddress;
    u32 Configuration_BaseAddress;
    u32 IsReady;
} XMultilayerperceptrondecoupled;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XMultilayerperceptrondecoupled_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XMultilayerperceptrondecoupled_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XMultilayerperceptrondecoupled_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XMultilayerperceptrondecoupled_ReadReg(BaseAddress, RegOffset) \
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
int XMultilayerperceptrondecoupled_Initialize(XMultilayerperceptrondecoupled *InstancePtr, u16 DeviceId);
XMultilayerperceptrondecoupled_Config* XMultilayerperceptrondecoupled_LookupConfig(u16 DeviceId);
int XMultilayerperceptrondecoupled_CfgInitialize(XMultilayerperceptrondecoupled *InstancePtr, XMultilayerperceptrondecoupled_Config *ConfigPtr);
#else
int XMultilayerperceptrondecoupled_Initialize(XMultilayerperceptrondecoupled *InstancePtr, const char* InstanceName);
int XMultilayerperceptrondecoupled_Release(XMultilayerperceptrondecoupled *InstancePtr);
#endif

void XMultilayerperceptrondecoupled_Start(XMultilayerperceptrondecoupled *InstancePtr);
u32 XMultilayerperceptrondecoupled_IsDone(XMultilayerperceptrondecoupled *InstancePtr);
u32 XMultilayerperceptrondecoupled_IsIdle(XMultilayerperceptrondecoupled *InstancePtr);
u32 XMultilayerperceptrondecoupled_IsReady(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_EnableAutoRestart(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_DisableAutoRestart(XMultilayerperceptrondecoupled *InstancePtr);

void XMultilayerperceptrondecoupled_Set_input_r(XMultilayerperceptrondecoupled *InstancePtr, u64 Data);
u64 XMultilayerperceptrondecoupled_Get_input_r(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_Set_output_r(XMultilayerperceptrondecoupled *InstancePtr, u64 Data);
u64 XMultilayerperceptrondecoupled_Get_output_r(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_Set_axiWeightInput(XMultilayerperceptrondecoupled *InstancePtr, u64 Data);
u64 XMultilayerperceptrondecoupled_Get_axiWeightInput(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_Set_axiBiasInput(XMultilayerperceptrondecoupled *InstancePtr, u64 Data);
u64 XMultilayerperceptrondecoupled_Get_axiBiasInput(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_Set_axiWeightOutput(XMultilayerperceptrondecoupled *InstancePtr, u64 Data);
u64 XMultilayerperceptrondecoupled_Get_axiWeightOutput(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_Set_axiBiasOutput(XMultilayerperceptrondecoupled *InstancePtr, u64 Data);
u64 XMultilayerperceptrondecoupled_Get_axiBiasOutput(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_Set_numberInputs(XMultilayerperceptrondecoupled *InstancePtr, u32 Data);
u32 XMultilayerperceptrondecoupled_Get_numberInputs(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_Set_numberOutputs(XMultilayerperceptrondecoupled *InstancePtr, u32 Data);
u32 XMultilayerperceptrondecoupled_Get_numberOutputs(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_Set_numberLayers(XMultilayerperceptrondecoupled *InstancePtr, u32 Data);
u32 XMultilayerperceptrondecoupled_Get_numberLayers(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_Set_numberNeurons(XMultilayerperceptrondecoupled *InstancePtr, u32 Data);
u32 XMultilayerperceptrondecoupled_Get_numberNeurons(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_Set_loadParameters(XMultilayerperceptrondecoupled *InstancePtr, u32 Data);
u32 XMultilayerperceptrondecoupled_Get_loadParameters(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_Set_exportLayers(XMultilayerperceptrondecoupled *InstancePtr, u32 Data);
u32 XMultilayerperceptrondecoupled_Get_exportLayers(XMultilayerperceptrondecoupled *InstancePtr);

void XMultilayerperceptrondecoupled_InterruptGlobalEnable(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_InterruptGlobalDisable(XMultilayerperceptrondecoupled *InstancePtr);
void XMultilayerperceptrondecoupled_InterruptEnable(XMultilayerperceptrondecoupled *InstancePtr, u32 Mask);
void XMultilayerperceptrondecoupled_InterruptDisable(XMultilayerperceptrondecoupled *InstancePtr, u32 Mask);
void XMultilayerperceptrondecoupled_InterruptClear(XMultilayerperceptrondecoupled *InstancePtr, u32 Mask);
u32 XMultilayerperceptrondecoupled_InterruptGetEnabled(XMultilayerperceptrondecoupled *InstancePtr);
u32 XMultilayerperceptrondecoupled_InterruptGetStatus(XMultilayerperceptrondecoupled *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
