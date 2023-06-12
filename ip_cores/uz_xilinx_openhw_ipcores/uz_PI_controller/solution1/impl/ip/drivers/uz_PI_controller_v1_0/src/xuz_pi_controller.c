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

void XUz_pi_controller_Set_axi_referenceValue(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_REFERENCEVALUE_DATA, Data);
}

u32 XUz_pi_controller_Get_axi_referenceValue(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_REFERENCEVALUE_DATA);
    return Data;
}

void XUz_pi_controller_Set_axi_sampletime(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_SAMPLETIME_DATA, Data);
}

u32 XUz_pi_controller_Get_axi_sampletime(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_SAMPLETIME_DATA);
    return Data;
}

void XUz_pi_controller_Set_axi_KI(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_KI_DATA, Data);
}

u32 XUz_pi_controller_Get_axi_KI(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_KI_DATA);
    return Data;
}

void XUz_pi_controller_Set_axi_KP(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_KP_DATA, Data);
}

u32 XUz_pi_controller_Get_axi_KP(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_KP_DATA);
    return Data;
}

void XUz_pi_controller_Set_axi_limit(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_LIMIT_DATA, Data);
}

u32 XUz_pi_controller_Get_axi_limit(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_LIMIT_DATA);
    return Data;
}

void XUz_pi_controller_Set_axi_reset(XUz_pi_controller *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_WriteReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_RESET_DATA, Data);
}

u32 XUz_pi_controller_Get_axi_reset(XUz_pi_controller *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_ReadReg(InstancePtr->Control_BaseAddress, XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_RESET_DATA);
    return Data;
}

