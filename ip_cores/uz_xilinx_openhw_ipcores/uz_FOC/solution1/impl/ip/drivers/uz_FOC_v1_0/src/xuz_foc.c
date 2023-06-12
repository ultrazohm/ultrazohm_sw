// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xuz_foc.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XUz_foc_CfgInitialize(XUz_foc *InstancePtr, XUz_foc_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XUz_foc_Set_sampletime(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_SAMPLETIME_DATA, Data);
}

u32 XUz_foc_Get_sampletime(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_SAMPLETIME_DATA);
    return Data;
}

void XUz_foc_Set_set_i_d(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_SET_I_D_DATA, Data);
}

u32 XUz_foc_Get_set_i_d(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_SET_I_D_DATA);
    return Data;
}

void XUz_foc_Set_set_i_q(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_SET_I_Q_DATA, Data);
}

u32 XUz_foc_Get_set_i_q(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_SET_I_Q_DATA);
    return Data;
}

void XUz_foc_Set_KP_d(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_KP_D_DATA, Data);
}

u32 XUz_foc_Get_KP_d(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_KP_D_DATA);
    return Data;
}

void XUz_foc_Set_KI_d(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_KI_D_DATA, Data);
}

u32 XUz_foc_Get_KI_d(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_KI_D_DATA);
    return Data;
}

void XUz_foc_Set_KP_q(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_KP_Q_DATA, Data);
}

u32 XUz_foc_Get_KP_q(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_KP_Q_DATA);
    return Data;
}

void XUz_foc_Set_KI_q(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_KI_Q_DATA, Data);
}

u32 XUz_foc_Get_KI_q(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_KI_Q_DATA);
    return Data;
}

void XUz_foc_Set_reset_PS(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_RESET_PS_DATA, Data);
}

u32 XUz_foc_Get_reset_PS(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_RESET_PS_DATA);
    return Data;
}

void XUz_foc_Set_limit(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_LIMIT_DATA, Data);
}

u32 XUz_foc_Get_limit(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_LIMIT_DATA);
    return Data;
}

u32 XUz_foc_Get_out_KP_d(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_OUT_KP_D_DATA);
    return Data;
}

u32 XUz_foc_Get_out_KP_d_vld(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_OUT_KP_D_CTRL);
    return Data & 0x1;
}

u32 XUz_foc_Get_out_idref(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_OUT_IDREF_DATA);
    return Data;
}

u32 XUz_foc_Get_out_idref_vld(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_OUT_IDREF_CTRL);
    return Data & 0x1;
}

u32 XUz_foc_Get_out_status(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_OUT_STATUS_DATA);
    return Data;
}

u32 XUz_foc_Get_out_status_vld(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_OUT_STATUS_CTRL);
    return Data & 0x1;
}

