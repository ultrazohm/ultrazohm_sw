// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XUZ_PI_CONTROLLER_H
#define XUZ_PI_CONTROLLER_H

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
#include "xuz_pi_controller_hw.h"

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
} XUz_pi_controller_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XUz_pi_controller;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XUz_pi_controller_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XUz_pi_controller_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XUz_pi_controller_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XUz_pi_controller_ReadReg(BaseAddress, RegOffset) \
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
int XUz_pi_controller_Initialize(XUz_pi_controller *InstancePtr, u16 DeviceId);
XUz_pi_controller_Config* XUz_pi_controller_LookupConfig(u16 DeviceId);
int XUz_pi_controller_CfgInitialize(XUz_pi_controller *InstancePtr, XUz_pi_controller_Config *ConfigPtr);
#else
int XUz_pi_controller_Initialize(XUz_pi_controller *InstancePtr, const char* InstanceName);
int XUz_pi_controller_Release(XUz_pi_controller *InstancePtr);
#endif


void XUz_pi_controller_Set_referenceValue(XUz_pi_controller *InstancePtr, u32 Data);
u32 XUz_pi_controller_Get_referenceValue(XUz_pi_controller *InstancePtr);
void XUz_pi_controller_Set_sampletime(XUz_pi_controller *InstancePtr, u32 Data);
u32 XUz_pi_controller_Get_sampletime(XUz_pi_controller *InstancePtr);
void XUz_pi_controller_Set_KI(XUz_pi_controller *InstancePtr, u32 Data);
u32 XUz_pi_controller_Get_KI(XUz_pi_controller *InstancePtr);
void XUz_pi_controller_Set_KP(XUz_pi_controller *InstancePtr, u32 Data);
u32 XUz_pi_controller_Get_KP(XUz_pi_controller *InstancePtr);
void XUz_pi_controller_Set_limit(XUz_pi_controller *InstancePtr, u32 Data);
u32 XUz_pi_controller_Get_limit(XUz_pi_controller *InstancePtr);
void XUz_pi_controller_Set_reset(XUz_pi_controller *InstancePtr, u32 Data);
u32 XUz_pi_controller_Get_reset(XUz_pi_controller *InstancePtr);
u32 XUz_pi_controller_Get_axi_referenceValue(XUz_pi_controller *InstancePtr);
u32 XUz_pi_controller_Get_axi_referenceValue_vld(XUz_pi_controller *InstancePtr);
u32 XUz_pi_controller_Get_axi_actualValue(XUz_pi_controller *InstancePtr);
u32 XUz_pi_controller_Get_axi_actualValue_vld(XUz_pi_controller *InstancePtr);
u32 XUz_pi_controller_Get_error(XUz_pi_controller *InstancePtr);
u32 XUz_pi_controller_Get_error_vld(XUz_pi_controller *InstancePtr);
u32 XUz_pi_controller_Get_P_sum(XUz_pi_controller *InstancePtr);
u32 XUz_pi_controller_Get_P_sum_vld(XUz_pi_controller *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
