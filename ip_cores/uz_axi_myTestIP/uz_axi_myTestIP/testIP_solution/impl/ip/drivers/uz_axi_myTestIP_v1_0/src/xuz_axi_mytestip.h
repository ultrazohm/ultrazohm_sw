// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XUZ_AXI_MYTESTIP_H
#define XUZ_AXI_MYTESTIP_H

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
#include "xuz_axi_mytestip_hw.h"

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
} XUz_axi_mytestip_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XUz_axi_mytestip;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XUz_axi_mytestip_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XUz_axi_mytestip_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XUz_axi_mytestip_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XUz_axi_mytestip_ReadReg(BaseAddress, RegOffset) \
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
int XUz_axi_mytestip_Initialize(XUz_axi_mytestip *InstancePtr, u16 DeviceId);
XUz_axi_mytestip_Config* XUz_axi_mytestip_LookupConfig(u16 DeviceId);
int XUz_axi_mytestip_CfgInitialize(XUz_axi_mytestip *InstancePtr, XUz_axi_mytestip_Config *ConfigPtr);
#else
int XUz_axi_mytestip_Initialize(XUz_axi_mytestip *InstancePtr, const char* InstanceName);
int XUz_axi_mytestip_Release(XUz_axi_mytestip *InstancePtr);
#endif


void XUz_axi_mytestip_Set_a(XUz_axi_mytestip *InstancePtr, u32 Data);
u32 XUz_axi_mytestip_Get_a(XUz_axi_mytestip *InstancePtr);
void XUz_axi_mytestip_Set_b(XUz_axi_mytestip *InstancePtr, u32 Data);
u32 XUz_axi_mytestip_Get_b(XUz_axi_mytestip *InstancePtr);
u32 XUz_axi_mytestip_Get_result(XUz_axi_mytestip *InstancePtr);
u32 XUz_axi_mytestip_Get_result_vld(XUz_axi_mytestip *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
