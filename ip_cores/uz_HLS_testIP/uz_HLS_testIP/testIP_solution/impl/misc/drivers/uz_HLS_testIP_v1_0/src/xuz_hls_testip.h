// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XUZ_HLS_TESTIP_H
#define XUZ_HLS_TESTIP_H

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
#include "xuz_hls_testip_hw.h"

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
} XUz_hls_testip_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XUz_hls_testip;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XUz_hls_testip_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XUz_hls_testip_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XUz_hls_testip_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XUz_hls_testip_ReadReg(BaseAddress, RegOffset) \
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
int XUz_hls_testip_Initialize(XUz_hls_testip *InstancePtr, u16 DeviceId);
XUz_hls_testip_Config* XUz_hls_testip_LookupConfig(u16 DeviceId);
int XUz_hls_testip_CfgInitialize(XUz_hls_testip *InstancePtr, XUz_hls_testip_Config *ConfigPtr);
#else
int XUz_hls_testip_Initialize(XUz_hls_testip *InstancePtr, const char* InstanceName);
int XUz_hls_testip_Release(XUz_hls_testip *InstancePtr);
#endif


void XUz_hls_testip_Set_a(XUz_hls_testip *InstancePtr, u32 Data);
u32 XUz_hls_testip_Get_a(XUz_hls_testip *InstancePtr);
void XUz_hls_testip_Set_b(XUz_hls_testip *InstancePtr, u32 Data);
u32 XUz_hls_testip_Get_b(XUz_hls_testip *InstancePtr);
u32 XUz_hls_testip_Get_result(XUz_hls_testip *InstancePtr);
u32 XUz_hls_testip_Get_result_vld(XUz_hls_testip *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
