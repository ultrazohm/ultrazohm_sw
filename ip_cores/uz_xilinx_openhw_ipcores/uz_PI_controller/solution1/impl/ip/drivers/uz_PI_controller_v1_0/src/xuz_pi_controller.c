// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xuz_pi_controller.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XUz_pi_controller_CfgInitialize(XUz_pi_controller *InstancePtr, XUz_pi_controller_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XUz_pi_controller_Set_referenceValue(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_REFERENCEVALUE_DATA, Data);
}

u32 XUz_pi_controller_Get_referenceValue(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_REFERENCEVALUE_DATA);
    return Data;
}

void XUz_pi_controller_Set_sampletime(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_SAMPLETIME_DATA, Data);
}

u32 XUz_pi_controller_Get_sampletime(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_SAMPLETIME_DATA);
    return Data;
}

void XUz_pi_controller_Set_KI(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_KI_DATA, Data);
}

u32 XUz_pi_controller_Get_KI(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_KI_DATA);
    return Data;
}

void XUz_pi_controller_Set_KP(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_KP_DATA, Data);
}

u32 XUz_pi_controller_Get_KP(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_KP_DATA);
    return Data;
}

void XUz_pi_controller_Set_limit(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_LIMIT_DATA, Data);
}

u32 XUz_pi_controller_Get_limit(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_LIMIT_DATA);
    return Data;
}

void XUz_pi_controller_Set_reset(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_RESET_DATA, Data);
}

u32 XUz_pi_controller_Get_reset(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_RESET_DATA);
    return Data;
}

u32 XUz_pi_controller_Get_axi_referenceValue(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_REFERENCEVALUE_DATA);
    return Data;
}

u32 XUz_pi_controller_Get_axi_referenceValue_vld(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_REFERENCEVALUE_CTRL);
    return Data & 0x1;
}

u32 XUz_pi_controller_Get_axi_actualValue(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_ACTUALVALUE_DATA);
    return Data;
}

u32 XUz_pi_controller_Get_axi_actualValue_vld(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_ACTUALVALUE_CTRL);
    return Data & 0x1;
}

u32 XUz_pi_controller_Get_error(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_ERROR_DATA);
    return Data;
}

u32 XUz_pi_controller_Get_error_vld(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_ERROR_CTRL);
    return Data & 0x1;
}

u32 XUz_pi_controller_Get_P_sum(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_P_SUM_DATA);
    return Data;
}

u32 XUz_pi_controller_Get_P_sum_vld(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_P_SUM_CTRL);
    return Data & 0x1;
}

