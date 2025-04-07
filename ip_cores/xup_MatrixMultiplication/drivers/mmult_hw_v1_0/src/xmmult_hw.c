// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xmmult_hw.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMmult_hw_CfgInitialize(XMmult_hw *InstancePtr, XMmult_hw_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMmult_hw_Start(XMmult_hw *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_AP_CTRL) & 0x80;
    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMmult_hw_IsDone(XMmult_hw *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMmult_hw_IsIdle(XMmult_hw *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMmult_hw_IsReady(XMmult_hw *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMmult_hw_EnableAutoRestart(XMmult_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_AP_CTRL, 0x80);
}

void XMmult_hw_DisableAutoRestart(XMmult_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_AP_CTRL, 0);
}

void XMmult_hw_Set_in1(XMmult_hw *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IN1_DATA, (u32)(Data));
    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IN1_DATA + 4, (u32)(Data >> 32));
}

u64 XMmult_hw_Get_in1(XMmult_hw *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IN1_DATA);
    Data += (u64)XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IN1_DATA + 4) << 32;
    return Data;
}

void XMmult_hw_Set_in2(XMmult_hw *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IN2_DATA, (u32)(Data));
    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IN2_DATA + 4, (u32)(Data >> 32));
}

u64 XMmult_hw_Get_in2(XMmult_hw *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IN2_DATA);
    Data += (u64)XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IN2_DATA + 4) << 32;
    return Data;
}

void XMmult_hw_Set_out_r(XMmult_hw *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_OUT_R_DATA, (u32)(Data));
    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_OUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XMmult_hw_Get_out_r(XMmult_hw *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_OUT_R_DATA);
    Data += (u64)XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_OUT_R_DATA + 4) << 32;
    return Data;
}

void XMmult_hw_Set_dim(XMmult_hw *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_DIM_DATA, Data);
}

u32 XMmult_hw_Get_dim(XMmult_hw *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_DIM_DATA);
    return Data;
}

void XMmult_hw_InterruptGlobalEnable(XMmult_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_GIE, 1);
}

void XMmult_hw_InterruptGlobalDisable(XMmult_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_GIE, 0);
}

void XMmult_hw_InterruptEnable(XMmult_hw *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IER);
    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IER, Register | Mask);
}

void XMmult_hw_InterruptDisable(XMmult_hw *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IER);
    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IER, Register & (~Mask));
}

void XMmult_hw_InterruptClear(XMmult_hw *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMmult_hw_WriteReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_ISR, Mask);
}

u32 XMmult_hw_InterruptGetEnabled(XMmult_hw *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_IER);
}

u32 XMmult_hw_InterruptGetStatus(XMmult_hw *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMmult_hw_ReadReg(InstancePtr->Ctrl_BaseAddress, XMMULT_HW_CTRL_ADDR_ISR);
}

