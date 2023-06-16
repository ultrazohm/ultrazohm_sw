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

void XUz_foc_Set_axi_id_reference(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_ID_REFERENCE_DATA, Data);
}

u32 XUz_foc_Get_axi_id_reference(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_ID_REFERENCE_DATA);
    return Data;
}

void XUz_foc_Set_axi_iq_reference(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_IQ_REFERENCE_DATA, Data);
}

u32 XUz_foc_Get_axi_iq_reference(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_IQ_REFERENCE_DATA);
    return Data;
}

void XUz_foc_Set_axi_sampletime(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_SAMPLETIME_DATA, Data);
}

u32 XUz_foc_Get_axi_sampletime(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_SAMPLETIME_DATA);
    return Data;
}

void XUz_foc_Set_axi_id_KI(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_ID_KI_DATA, Data);
}

u32 XUz_foc_Get_axi_id_KI(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_ID_KI_DATA);
    return Data;
}

void XUz_foc_Set_axi_id_KP(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_ID_KP_DATA, Data);
}

u32 XUz_foc_Get_axi_id_KP(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_ID_KP_DATA);
    return Data;
}

void XUz_foc_Set_axi_iq_KI(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_IQ_KI_DATA, Data);
}

u32 XUz_foc_Get_axi_iq_KI(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_IQ_KI_DATA);
    return Data;
}

void XUz_foc_Set_axi_iq_KP(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_IQ_KP_DATA, Data);
}

u32 XUz_foc_Get_axi_iq_KP(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_IQ_KP_DATA);
    return Data;
}

void XUz_foc_Set_axi_limit(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_LIMIT_DATA, Data);
}

u32 XUz_foc_Get_axi_limit(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_LIMIT_DATA);
    return Data;
}

void XUz_foc_Set_axi_reset(XUz_foc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_RESET_DATA, Data);
}

u32 XUz_foc_Get_axi_reset(XUz_foc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_CONTROL_ADDR_AXI_RESET_DATA);
    return Data;
}

