// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XMLP_H
#define XMLP_H

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
#include "xmlp_hw.h"

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
} XMlp_Config;
#endif

typedef struct {
    u32 Control_BaseAddress;
    u32 IsReady;
} XMlp;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XMlp_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XMlp_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XMlp_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XMlp_ReadReg(BaseAddress, RegOffset) \
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
int XMlp_Initialize(XMlp *InstancePtr, u16 DeviceId);
XMlp_Config* XMlp_LookupConfig(u16 DeviceId);
int XMlp_CfgInitialize(XMlp *InstancePtr, XMlp_Config *ConfigPtr);
#else
int XMlp_Initialize(XMlp *InstancePtr, const char* InstanceName);
int XMlp_Release(XMlp *InstancePtr);
#endif


void XMlp_Set_input_r(XMlp *InstancePtr, u64 Data);
u64 XMlp_Get_input_r(XMlp *InstancePtr);
void XMlp_Set_output_r(XMlp *InstancePtr, u64 Data);
u64 XMlp_Get_output_r(XMlp *InstancePtr);
void XMlp_Set_axiWeightInput(XMlp *InstancePtr, u64 Data);
u64 XMlp_Get_axiWeightInput(XMlp *InstancePtr);
void XMlp_Set_axiBiasInput(XMlp *InstancePtr, u64 Data);
u64 XMlp_Get_axiBiasInput(XMlp *InstancePtr);
void XMlp_Set_axiLayerOutput(XMlp *InstancePtr, u64 Data);
u64 XMlp_Get_axiLayerOutput(XMlp *InstancePtr);
void XMlp_Set_numberInputs(XMlp *InstancePtr, u32 Data);
u32 XMlp_Get_numberInputs(XMlp *InstancePtr);
void XMlp_Set_numberOutputs(XMlp *InstancePtr, u32 Data);
u32 XMlp_Get_numberOutputs(XMlp *InstancePtr);
void XMlp_Set_numberLayers(XMlp *InstancePtr, u32 Data);
u32 XMlp_Get_numberLayers(XMlp *InstancePtr);
void XMlp_Set_numberNeurons(XMlp *InstancePtr, u32 Data);
u32 XMlp_Get_numberNeurons(XMlp *InstancePtr);
void XMlp_Set_loadParameters(XMlp *InstancePtr, u32 Data);
u32 XMlp_Get_loadParameters(XMlp *InstancePtr);
void XMlp_Set_exportLayers(XMlp *InstancePtr, u32 Data);
u32 XMlp_Get_exportLayers(XMlp *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
