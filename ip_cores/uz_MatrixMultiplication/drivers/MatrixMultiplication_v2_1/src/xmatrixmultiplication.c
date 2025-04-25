// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xmatrixmultiplication.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMatrixmultiplication_CfgInitialize(XMatrixmultiplication *InstancePtr, XMatrixmultiplication_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMatrixmultiplication_Start(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL) & 0x80;
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMatrixmultiplication_IsDone(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMatrixmultiplication_IsIdle(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMatrixmultiplication_IsReady(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMatrixmultiplication_EnableAutoRestart(XMatrixmultiplication *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XMatrixmultiplication_DisableAutoRestart(XMatrixmultiplication *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL, 0);
}

void XMatrixmultiplication_Set_A_input(XMatrixmultiplication *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_A_INPUT_DATA, (u32)(Data));
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_A_INPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmultiplication_Get_A_input(XMatrixmultiplication *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_A_INPUT_DATA);
    Data += (u64)XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_A_INPUT_DATA + 4) << 32;
    return Data;
}

void XMatrixmultiplication_Set_B1_input(XMatrixmultiplication *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B1_INPUT_DATA, (u32)(Data));
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B1_INPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmultiplication_Get_B1_input(XMatrixmultiplication *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B1_INPUT_DATA);
    Data += (u64)XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B1_INPUT_DATA + 4) << 32;
    return Data;
}

void XMatrixmultiplication_Set_B2_input(XMatrixmultiplication *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B2_INPUT_DATA, (u32)(Data));
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B2_INPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmultiplication_Get_B2_input(XMatrixmultiplication *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B2_INPUT_DATA);
    Data += (u64)XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B2_INPUT_DATA + 4) << 32;
    return Data;
}

void XMatrixmultiplication_Set_B3_input(XMatrixmultiplication *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B3_INPUT_DATA, (u32)(Data));
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B3_INPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmultiplication_Get_B3_input(XMatrixmultiplication *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B3_INPUT_DATA);
    Data += (u64)XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B3_INPUT_DATA + 4) << 32;
    return Data;
}

void XMatrixmultiplication_Set_B4_input(XMatrixmultiplication *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B4_INPUT_DATA, (u32)(Data));
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B4_INPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmultiplication_Get_B4_input(XMatrixmultiplication *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B4_INPUT_DATA);
    Data += (u64)XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B4_INPUT_DATA + 4) << 32;
    return Data;
}

void XMatrixmultiplication_Set_C_output(XMatrixmultiplication *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUTPUT_DATA, (u32)(Data));
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUTPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmultiplication_Get_C_output(XMatrixmultiplication *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUTPUT_DATA);
    Data += (u64)XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUTPUT_DATA + 4) << 32;
    return Data;
}

void XMatrixmultiplication_Set_copy_mats_flag(XMatrixmultiplication *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_COPY_MATS_FLAG_DATA, Data);
}

u32 XMatrixmultiplication_Get_copy_mats_flag(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_COPY_MATS_FLAG_DATA);
    return Data;
}

void XMatrixmultiplication_Set_A_rows(XMatrixmultiplication *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA, Data);
}

u32 XMatrixmultiplication_Get_A_rows(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA);
    return Data;
}

void XMatrixmultiplication_Set_B1_rows(XMatrixmultiplication *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B1_ROWS_DATA, Data);
}

u32 XMatrixmultiplication_Get_B1_rows(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B1_ROWS_DATA);
    return Data;
}

void XMatrixmultiplication_Set_B1_columns(XMatrixmultiplication *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B1_COLUMNS_DATA, Data);
}

u32 XMatrixmultiplication_Get_B1_columns(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B1_COLUMNS_DATA);
    return Data;
}

void XMatrixmultiplication_Set_B2_columns(XMatrixmultiplication *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B2_COLUMNS_DATA, Data);
}

u32 XMatrixmultiplication_Get_B2_columns(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B2_COLUMNS_DATA);
    return Data;
}

u32 XMatrixmultiplication_Get_copy_flag_out(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_COPY_FLAG_OUT_DATA);
    return Data;
}

u32 XMatrixmultiplication_Get_matrices_updated_out(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_MATRICES_UPDATED_OUT_DATA);
    return Data;
}

void XMatrixmultiplication_InterruptGlobalEnable(XMatrixmultiplication *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_GIE, 1);
}

void XMatrixmultiplication_InterruptGlobalDisable(XMatrixmultiplication *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_GIE, 0);
}

void XMatrixmultiplication_InterruptEnable(XMatrixmultiplication *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_IER);
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_IER, Register | Mask);
}

void XMatrixmultiplication_InterruptDisable(XMatrixmultiplication *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_IER);
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_IER, Register & (~Mask));
}

void XMatrixmultiplication_InterruptClear(XMatrixmultiplication *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_ISR, Mask);
}

u32 XMatrixmultiplication_InterruptGetEnabled(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_IER);
}

u32 XMatrixmultiplication_InterruptGetStatus(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_ISR);
}

