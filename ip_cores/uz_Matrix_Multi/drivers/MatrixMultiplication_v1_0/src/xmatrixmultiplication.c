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

void XMatrixmultiplication_Set_A_rows(XMatrixmultiplication *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA, (u32)(Data));
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmultiplication_Get_A_rows(XMatrixmultiplication *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA);
    Data += (u64)XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA + 4) << 32;
    return Data;
}

void XMatrixmultiplication_Set_B_rows(XMatrixmultiplication *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B_ROWS_DATA, (u32)(Data));
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B_ROWS_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmultiplication_Get_B_rows(XMatrixmultiplication *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B_ROWS_DATA);
    Data += (u64)XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B_ROWS_DATA + 4) << 32;
    return Data;
}

void XMatrixmultiplication_Set_B_columns(XMatrixmultiplication *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B_COLUMNS_DATA, (u32)(Data));
    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B_COLUMNS_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmultiplication_Get_B_columns(XMatrixmultiplication *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B_COLUMNS_DATA);
    Data += (u64)XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_B_COLUMNS_DATA + 4) << 32;
    return Data;
}

void XMatrixmultiplication_Set_trigger(XMatrixmultiplication *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_TRIGGER_DATA, Data);
}

u32 XMatrixmultiplication_Get_trigger(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_TRIGGER_DATA);
    return Data;
}

void XMatrixmultiplication_Set_is_done_i(XMatrixmultiplication *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmultiplication_WriteReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_IS_DONE_I_DATA, Data);
}

u32 XMatrixmultiplication_Get_is_done_i(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_IS_DONE_I_DATA);
    return Data;
}

u32 XMatrixmultiplication_Get_is_done_o(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_IS_DONE_O_DATA);
    return Data;
}

u32 XMatrixmultiplication_Get_is_done_o_vld(XMatrixmultiplication *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmultiplication_ReadReg(InstancePtr->Control_BaseAddress, XMATRIXMULTIPLICATION_CONTROL_ADDR_IS_DONE_O_CTRL);
    return Data & 0x1;
}

u32 XMatrixmultiplication_Get_A_BaseAddress(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE);
}

u32 XMatrixmultiplication_Get_A_HighAddress(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_HIGH);
}

u32 XMatrixmultiplication_Get_A_TotalBytes(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMATRIXMULTIPLICATION_CONTROL_ADDR_A_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE + 1);
}

u32 XMatrixmultiplication_Get_A_BitWidth(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMATRIXMULTIPLICATION_CONTROL_WIDTH_A;
}

u32 XMatrixmultiplication_Get_A_Depth(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMATRIXMULTIPLICATION_CONTROL_DEPTH_A;
}

u32 XMatrixmultiplication_Write_A_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMATRIXMULTIPLICATION_CONTROL_ADDR_A_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMatrixmultiplication_Read_A_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMATRIXMULTIPLICATION_CONTROL_ADDR_A_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMatrixmultiplication_Write_A_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMATRIXMULTIPLICATION_CONTROL_ADDR_A_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMatrixmultiplication_Read_A_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMATRIXMULTIPLICATION_CONTROL_ADDR_A_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE + offset + i);
    }
    return length;
}

u32 XMatrixmultiplication_Get_C_out_BaseAddress(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE);
}

u32 XMatrixmultiplication_Get_C_out_HighAddress(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_HIGH);
}

u32 XMatrixmultiplication_Get_C_out_TotalBytes(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE + 1);
}

u32 XMatrixmultiplication_Get_C_out_BitWidth(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMATRIXMULTIPLICATION_CONTROL_WIDTH_C_OUT;
}

u32 XMatrixmultiplication_Get_C_out_Depth(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMATRIXMULTIPLICATION_CONTROL_DEPTH_C_OUT;
}

u32 XMatrixmultiplication_Write_C_out_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMatrixmultiplication_Read_C_out_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMatrixmultiplication_Write_C_out_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMatrixmultiplication_Read_C_out_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE + offset + i);
    }
    return length;
}

u32 XMatrixmultiplication_Get_B_BaseAddress(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE);
}

u32 XMatrixmultiplication_Get_B_HighAddress(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_HIGH);
}

u32 XMatrixmultiplication_Get_B_TotalBytes(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMATRIXMULTIPLICATION_CONTROL_ADDR_B_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE + 1);
}

u32 XMatrixmultiplication_Get_B_BitWidth(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMATRIXMULTIPLICATION_CONTROL_WIDTH_B;
}

u32 XMatrixmultiplication_Get_B_Depth(XMatrixmultiplication *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMATRIXMULTIPLICATION_CONTROL_DEPTH_B;
}

u32 XMatrixmultiplication_Write_B_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMATRIXMULTIPLICATION_CONTROL_ADDR_B_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMatrixmultiplication_Read_B_Words(XMatrixmultiplication *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMATRIXMULTIPLICATION_CONTROL_ADDR_B_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMatrixmultiplication_Write_B_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMATRIXMULTIPLICATION_CONTROL_ADDR_B_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMatrixmultiplication_Read_B_Bytes(XMatrixmultiplication *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMATRIXMULTIPLICATION_CONTROL_ADDR_B_HIGH - XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE + offset + i);
    }
    return length;
}

